#include "dapp_sm_ric.h"
#include "dapp_sm_id.h"

#include <assert.h>
#include <stdlib.h>

#include "ie/dapp_data_ie.h"
#include "e3/dapp_dec_e3.h"
#include "e3/dapp_enc_e3.h"

#include "enc/dapp_enc_generic.h"
#include "dec/dapp_dec_generic.h"

typedef struct {
  sm_ric_t base;

#ifdef ASN
  dapp_enc_asn_t enc;
#elif FLATBUFFERS
  dapp_enc_fb_t enc;
#elif PLAIN
  dapp_enc_plain_t enc;
#else
  static_assert(false, "No encoding type selected");
#endif
} sm_dapp_ric_t;

/**
 * @brief Build an E2 subscription for the DAPP SM on the RIC.
 *
 * - Takes a high-level dapp_sub_data_t (event trigger + action def).
 * - Encodes the event trigger and a single action definition into byte arrays.
 * - Returns an sm_subs_data_t ready to be sent over E2AP.
 */
static sm_subs_data_t on_subscription_dapp_sm_ric(sm_ric_t const* sm_ric, void* cmd)
{
  assert(sm_ric != NULL);
  assert(cmd != NULL);
  dapp_sub_data_t const* src = cmd;
  sm_dapp_ric_t* sm = (sm_dapp_ric_t*)sm_ric;
  sm_subs_data_t dst = {0};

  /* Encode E2SM-DAPP event trigger */
  const byte_array_t ba = dapp_enc_event_trigger(&sm->enc, &src->et);
  dst.event_trigger = ba.buf;
  dst.len_et = ba.len;

  /* Currently only one Action Definition is supported */
  assert(src->sz_ad > 0 && src->sz_ad == 1 && "Only one action definition supported");
  assert(src->ad != NULL);

  /* Encode E2SM-DAPP Action Definition */
  const byte_array_t ba_ad = dapp_enc_action_def(&sm->enc, src->ad);
  assert(ba_ad.len < 10 * 1024 && "Really encoding so much data?");
  dst.action_def = ba_ad.buf;
  dst.len_ad = ba_ad.len;

  return dst;
}

/**
 * @brief RIC-side indication handler for the DAPP service model.
 *
 * This function is called when the RIC receives an indication message
 * for the DAPP SM from the E2 agent. It performs a two-stage decode:
 *
 *  1) E2SM-DAPP layer:
 *     - Decodes the indication header and message using the DAPP encoder/decoder
 *       context stored in @p sm_ric (sm_dapp_ric_t).
 *     - Fills dst.dapp.ind.hdr and dst.dapp.ind.msg accordingly.
 *
 *  2) Inner E3 payload:
 *     - Assumes the indication message is in FORMAT_0_E2SM_DAPP_IND_MSG.
 *     - Extracts the RAN function ID from the decoded header.
 *     - If msg.format-0 carries a non-empty data buffer, it calls
 *       dapp_dec_e3_indication() to decode the inner E3 payload into
 *       dst.dapp.ind.e3.
 *     - If no data is present, sets dst.dapp.ind.e3.type = DAPP_E3_SM_NONE.
 *
 * The function returns a fully-populated sm_ag_if_rd_ind_t structure of
 * type DAPP_STATS_V0, which is then consumed by the upper layers in the RIC.
 *
 * @param sm_ric  Pointer to the RIC-side DAPP SM instance (base + codec state).
 * @param src     Raw indication data received from the E2 agent.
 *
 * @return Decoded indication container ready for consumption by the RIC logic.
 */
static sm_ag_if_rd_ind_t on_indication_dapp_sm_ric(sm_ric_t const* sm_ric, sm_ind_data_t const* src)
{
  assert(sm_ric != NULL);
  assert(src != NULL);
  sm_dapp_ric_t* sm = (sm_dapp_ric_t*)sm_ric;

  sm_ag_if_rd_ind_t dst = {.type = DAPP_STATS_V0};

  /* Decode E2SM-DAPP indication header and message */
  dst.dapp.ind.hdr = dapp_dec_ind_hdr(&sm->enc, src->len_hdr, src->ind_hdr);
  dst.dapp.ind.msg = dapp_dec_ind_msg(&sm->enc, src->len_msg, src->ind_msg);
  dst.dapp.act_def = NULL;
  dst.dapp.ric_id = 0;

  /* Decode inner E3 payload (from DAPP IndicationMessage format 0) */
  assert(dst.dapp.ind.msg.format == FORMAT_0_E2SM_DAPP_IND_MSG);

  e2sm_dapp_ind_msg_frmt_0_t* m0 = &dst.dapp.ind.msg.frmt_0;
  uint32_t ran_function_id = dst.dapp.ind.hdr.frmt_0.ran_function_id;

  if (m0->data_size > 0 && m0->data != NULL) {
    bool ok = dapp_dec_e3_indication(ran_function_id, m0->data, m0->data_size, &dst.dapp.ind.e3);
    if (!ok) {
      assert(0 && "Failed to decode inner E3 payload");
    }
  } else {
    dst.dapp.ind.e3.type = DAPP_E3_SM_NONE;
  }

  return dst;
}

/**
 * @brief RIC-side handler for DAPP SM control requests.
 *
 * This function is called when the RIC plugin receives a control request
 * for the DAPP SM from the xApp side.
 *
 * High-level behavior:
 *  - Interprets @p ctrl as a dapp_ctrl_req_data_t (E2SM-DAPP control IR).
 *  - If the request carries a non-empty E3 control payload (tmp.e3.type !=
 *    DAPP_E3_SM_NONE) and the E2SM-DAPP ControlMessage (format 0) currently
 *    has no inner data (data == NULL, data_size == 0), it:
 *      1) Encodes the E3 control payload into a binary buffer using
 *         dapp_enc_e3_control(), based on the ran_function_id in the header.
 *      2) Injects the encoded E3 buffer into tmp.msg.frmt_0.data / data_size.
 *      3) Encodes the DAPP ControlHeader and ControlMessage into byte arrays
 *         using dapp_enc_ctrl_hdr() and dapp_enc_ctrl_msg().
 *  - Fills a sm_ctrl_req_data_t structure with:
 *      * ctrl_hdr / len_hdr: encoded E2SM-DAPP ControlHeader
 *      * ctrl_msg / len_msg: encoded E2SM-DAPP ControlMessage
 *  - Returns the filled sm_ctrl_req_data_t, which the FlexRIC core then
 *    forwards over the E2 interface.
 *
 * @param sm_ric  Pointer to the RIC-side DAPP SM instance (codec context).
 * @param ctrl    Pointer to a dapp_ctrl_req_data_t describing the control.
 *
 * @return Encoded control header and message ready to be sent over E2.
 */
static sm_ctrl_req_data_t ric_on_control_req_dapp_sm_ric(sm_ric_t const* sm_ric, void* ctrl)
{
  assert(sm_ric != NULL);
  assert(ctrl != NULL);

  sm_dapp_ric_t* sm = (sm_dapp_ric_t*)sm_ric;

  dapp_ctrl_req_data_t const* req = (dapp_ctrl_req_data_t const*)ctrl;
  sm_ctrl_req_data_t dst = (sm_ctrl_req_data_t){0};

  dapp_ctrl_req_data_t tmp = *req;

  if (tmp.e3.type != DAPP_E3_SM_NONE && tmp.msg.format == FORMAT_0_E2SM_DAPP_CTRL_MSG && tmp.msg.frmt_0.data == NULL
      && tmp.msg.frmt_0.data_size == 0) {
    uint8_t* e3_buf = NULL;
    size_t e3_len = 0;

    bool ok = dapp_enc_e3_control(tmp.hdr.frmt_0.ran_function_id, &tmp.e3, &e3_buf, &e3_len);
    if (!ok) {
      fprintf(stderr, "[DAPP][RIC] Failed to encode E3 control payload\n");
      assert(0 && "E3 control encoding failed");
    }

    tmp.msg.frmt_0.data = e3_buf;
    tmp.msg.frmt_0.data_size = (uint32_t)e3_len;

    byte_array_t ba_hdr = dapp_enc_ctrl_hdr(&sm->enc, &tmp.hdr);
    dst.ctrl_hdr = ba_hdr.buf;
    dst.len_hdr = ba_hdr.len;

    byte_array_t ba_msg = dapp_enc_ctrl_msg(&sm->enc, &tmp.msg);
    dst.ctrl_msg = ba_msg.buf;
    dst.len_msg = ba_msg.len;
  }

  return dst;
}

/**
 * @brief Decode a DAPP control outcome received at the RIC.
 *
 * - Takes raw control outcome bytes from the agent.
 * - Decodes them into the dapp-specific control outcome structure.
 */
static sm_ag_if_ans_ctrl_t ric_on_control_out_dapp_sm_ric(sm_ric_t const* sm_ric, const sm_ctrl_out_data_t* src)
{
  assert(sm_ric != NULL);
  assert(src != NULL);
  sm_dapp_ric_t* sm = (sm_dapp_ric_t*)sm_ric;

  /* Decode E2SM-DAPP control outcome */
  sm_ag_if_ans_ctrl_t dst = {.type = DAPP_AGENT_IF_CTRL_ANS_V0};
  dst.dapp = dapp_dec_ctrl_out(&sm->enc, src->len_out, src->ctrl_out);

  return dst;
}

/**
 * @brief Decode the E2 Setup Response for the DAPP SM at the RIC.
 *
 * - Parses the RAN function definition from the E2 setup data.
 * - Wraps it into an sm_ag_if_rd_e2setup_t with type DAPP_AGENT_IF_E2_SETUP_ANS_V0.
 */
static sm_ag_if_rd_e2setup_t ric_on_e2_setup_dapp_sm_ric(sm_ric_t const* sm_ric, sm_e2_setup_data_t const* src)
{
  assert(sm_ric != NULL);
  assert(src != NULL);
  sm_dapp_ric_t* sm = (sm_dapp_ric_t*)sm_ric;

  sm_ag_if_rd_e2setup_t dst = {.type = DAPP_AGENT_IF_E2_SETUP_ANS_V0};

  dst.dapp.ran_func_def = dapp_dec_func_def(&sm->enc, src->len_rfd, src->ran_fun_def);

  return dst;
}
/**
 * @brief Handle RIC Service Update messages for the DAPP SM.
 *
 * Currently a placeholder that returns an empty sm_ag_if_rd_rsu_t.
 */
static sm_ag_if_rd_rsu_t on_ric_service_update_dapp_sm_ric(sm_ric_t const* sm_ric, sm_ric_service_update_data_t const* src)
{
  assert(sm_ric != NULL);
  assert(src != NULL);
  sm_ag_if_rd_rsu_t dst = {0};
  return dst;
}

/**
 * @brief Free resources associated with the DAPP SM RIC instance.
 *
 * Currently there is no dynamically allocated state inside sm_dapp_ric_t
 * beyond the structure itself, so this is a no-op.
 */
static void free_dapp_sm_ric(sm_ric_t* sm_ric)
{
  assert(sm_ric != NULL);
}

/**
 * @brief Free subscription-related data for the DAPP SM at the RIC.
 *
 * This is a placeholder and will abort if called, as the corresponding
 * allocation logic is not implemented yet.
 */
static void free_subs_data_dapp_sm_ric(void* msg)
{
  assert(msg != NULL);
  assert(0 != 0 && "Not implemented");
}

/**
 * @brief Free indication data for the DAPP SM at the RIC.
 *
 * Currently a no-op, as ownership and lifetime of indication data
 * are managed by the caller.
 */
static void free_ind_data_dapp_sm_ric(void* msg)
{
  assert(msg != NULL);
}

/**
 * @brief Free control request data for the DAPP SM at the RIC.
 *
 * This is a placeholder and will abort if called, as the corresponding
 * allocation logic is not implemented yet.
 */
static void free_ctrl_req_data_dapp_sm_ric(void* msg)
{
  assert(msg != NULL);
  assert(0 != 0 && "Not implemented");
}

/**
 * @brief Free control outcome data for the DAPP SM at the RIC.
 *
 * This is a placeholder and will abort if called, as the corresponding
 * allocation logic is not implemented yet.
 */
static void free_ctrl_out_data_dapp_sm_ric(void* msg)
{
  assert(msg != NULL);
  assert(0 != 0 && "Not implemented");
}

/**
 * @brief Free E2 Setup data for the DAPP SM at the RIC.
 *
 * This is a placeholder and will abort if called, as the corresponding
 * allocation logic is not implemented yet.
 */
static void free_e2_setup_dapp_sm_ric(void* msg)
{
  assert(msg != NULL);
  assert(0 != 0 && "Not implemented");
}

/**
 * @brief Free RIC Service Update data for the DAPP SM at the RIC.
 *
 * This is a placeholder and will abort if called, as the corresponding
 * allocation logic is not implemented yet.
 */
static void free_ric_service_update_dapp_sm_ric(void* msg)
{
  assert(msg != NULL);
  assert(0 != 0 && "Not implemented");
}

/**
 * @brief Allocate and initialize the DAPP Service Model instance at the RIC.
 *
 * - Allocates sm_dapp_ric_t.
 * - Sets the RAN function ID, name, and all function pointers for
 *   subscription, indication, control, E2 setup, and service update handlers.
 */
sm_ric_t* make_dapp_sm_ric(void)
{
  sm_dapp_ric_t* sm = calloc(1, sizeof(sm_dapp_ric_t));
  assert(sm != NULL && "Memory exhausted");

  *((uint16_t*)&sm->base.ran_func_id) = SM_DAPP_ID;

  sm->base.free_sm = free_dapp_sm_ric;

  sm->base.alloc.free_subs_data_msg = free_subs_data_dapp_sm_ric;
  sm->base.alloc.free_ind_data = free_ind_data_dapp_sm_ric;
  sm->base.alloc.free_ctrl_req_data = free_ctrl_req_data_dapp_sm_ric;
  sm->base.alloc.free_ctrl_out_data = free_ctrl_out_data_dapp_sm_ric;

  sm->base.alloc.free_e2_setup = free_e2_setup_dapp_sm_ric;
  sm->base.alloc.free_ric_service_update = free_ric_service_update_dapp_sm_ric;

  sm->base.proc.on_subscription = on_subscription_dapp_sm_ric;
  sm->base.proc.on_indication = on_indication_dapp_sm_ric;

  sm->base.proc.on_control_req = ric_on_control_req_dapp_sm_ric;
  sm->base.proc.on_control_out = ric_on_control_out_dapp_sm_ric;

  sm->base.proc.on_e2_setup = ric_on_e2_setup_dapp_sm_ric;
  sm->base.proc.on_ric_service_update = on_ric_service_update_dapp_sm_ric;
  sm->base.handle = NULL;

  assert(strlen(SM_DAPP_SHORT_NAME) < sizeof(sm->base.ran_func_name));
  memcpy(sm->base.ran_func_name, SM_DAPP_SHORT_NAME, strlen(SM_DAPP_SHORT_NAME));

  return &sm->base;
}

/**
 * @brief Return the RAN function ID for the given DAPP SM RIC instance.
 */
uint16_t id_sm_dapp_ric(sm_ric_t const* sm_ric)
{
  assert(sm_ric != NULL);
  sm_dapp_ric_t* sm = (sm_dapp_ric_t*)sm_ric;
  return sm->base.ran_func_id;
}
