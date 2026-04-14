#include "dapp_enc_asn.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../lib/sm/enc/enc_cell_global_id.h"
#include "../../../lib/sm/enc/enc_ue_id.h"

#include "../../../util/alg_ds/alg/defer.h"
#include "../../../../util/byte_array.h"

#include "../ie/asn/E2SM-DAPP-EventTrigger.h"
#include "../ie/asn/E2SM-DAPP-EventTrigger-Format1.h"

#include "../ie/asn/E2SM-DAPP-ActionDefinition.h"
#include "../ie/asn/E2SM-DAPP-ActionDefinition-Format1.h"

#include "../ie/asn/E2SM-DAPP-IndicationHeader.h"
#include "../ie/asn/E2SM-DAPP-IndicationHeader-Format1.h"
#include "../ie/asn/E2SM-DAPP-IndicationHeader-Format2.h"

#include "../ie/asn/E2SM-DAPP-IndicationMessage.h"
#include "../ie/asn/E2SM-DAPP-IndicationMessage-Format1.h"
#include "../ie/asn/E2SM-DAPP-IndicationMessage-Format2.h"

#include "../ie/asn/E2SM-DAPP-ControlHeader.h"
#include "../ie/asn/E2SM-DAPP-ControlHeader-Format1.h"

#include "../ie/asn/E2SM-DAPP-ControlMessage.h"
#include "../ie/asn/E2SM-DAPP-ControlMessage-Format1.h"

#include "../ie/asn/E2SM-DAPP-ControlOutcome.h"
#include "../ie/asn/E2SM-DAPP-ControlOutcome-Format1.h"

#include "../ie/asn/E2SM-DAPP-RANFunctionDefinition.h"

#include "../ie/asn/RANFunctionDefinition-EventTrigger.h"

#include "../ie/asn/RANFunctionDefinition-Report.h"
#include "../ie/asn/RANFunctionDefinition-Report-Item.h"

#include "../ie/asn/RANFunctionDefinition-Control.h"
#include "../ie/asn/RANFunctionDefinition-Control-Item.h"

#include "../ie/asn/DAppE3Subscription-Item.h"
#include "../ie/asn/DAppE3Subscription-List.h"

static inline OCTET_STRING_t copy_ba_to_ostring(byte_array_t ba)
{
  OCTET_STRING_t os = {.size = ba.len};
  os.buf = malloc(ba.len);
  memcpy(os.buf, ba.buf, ba.len);
  return os;
}

static E2SM_DAPP_EventTrigger_Format1_t* cp_dapp_ev_trigger_format_1(e2sm_dapp_ev_trg_frmt_1_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_EventTrigger_Format1_t* dst = calloc(1, sizeof(E2SM_DAPP_EventTrigger_Format1_t));
  assert(dst != NULL && "Memory exhausted");

  return dst;
}

byte_array_t dapp_enc_event_trigger_asn(e2sm_dapp_event_trigger_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_EventTrigger_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_EventTrigger, &dst); });

  if (src->format == FORMAT_1_E2SM_DAPP_EV_TRIGGER_FORMAT) {
    dst.ric_eventTrigger_formats.present = E2SM_DAPP_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format1;
    dst.ric_eventTrigger_formats.choice.eventTrigger_Format1 = cp_dapp_ev_trigger_format_1(&src->frmt_1);
  } else {
    assert(0 != 0 && "Unknown format");
  }

  byte_array_t ba = {.buf = malloc(512 * 1024), .len = 512 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_EventTrigger, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_ActionDefinition_Format1_t* enc_action_def_frmt_1(e2sm_dapp_action_def_frmt_1_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ActionDefinition_Format1_t* dst = calloc(1, sizeof(*dst));
  assert(dst != NULL && "Memory exhausted");

  return dst;
}

byte_array_t dapp_enc_action_def_asn(e2sm_dapp_action_def_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ActionDefinition_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ActionDefinition, &dst); });

  dst.ric_Style_Type = (long)src->ric_style_type;

  if (src->format == FORMAT_1_E2SM_DAPP_ACTION_DEF) {
    dst.actionDefinition_formats.present = E2SM_DAPP_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1;
    dst.actionDefinition_formats.choice.actionDefinition_Format1 = enc_action_def_frmt_1(&src->frmt_1);
  } else {
    assert(0 != 0 && "Unknown action definition format");
  }

  byte_array_t ba = {.buf = malloc(1024), .len = 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_ActionDefinition, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_IndicationHeader_Format2_t* cp_ind_hdr_frmt_2(e2sm_dapp_ind_hdr_frmt_2_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_IndicationHeader_Format2_t* dst = calloc(1, sizeof(E2SM_DAPP_IndicationHeader_Format2_t));
  assert(dst != NULL && "Memory exhausted");

  dst->node_type = (long)src->node_type;
  dst->node_nb_id = (long)src->node_nb_id;

  int ret = OCTET_STRING_fromBuf(&dst->node_plmn_id, (const char*)src->node_plmn_id, 3);
  assert(ret == 0 && "OCTET_STRING_fromBuf failed for node_plmn_id");

  if (src->node_cu_du_id_present) {
    dst->node_cu_du_id = calloc(1, sizeof(long));
    assert(dst->node_cu_du_id != NULL && "Memory exhausted");
    *dst->node_cu_du_id = (long)src->node_cu_du_id;
  }

  return dst;
}

static E2SM_DAPP_IndicationHeader_Format1_t* cp_ind_hdr_frmt_1(e2sm_dapp_ind_hdr_frmt_1_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_IndicationHeader_Format1_t* dst = calloc(1, sizeof(E2SM_DAPP_IndicationHeader_Format1_t));
  assert(dst != NULL && "Memory exhausted");

  dst->ran_function_id = (long)src->ran_function_id;
  dst->dapp_id = (long)src->dapp_id;

  dst->node_type = (long)src->node_type;
  dst->node_nb_id = (long)src->node_nb_id;

  int ret = OCTET_STRING_fromBuf(&dst->node_plmn_id, (const char*)src->node_plmn_id, 3);
  assert(ret == 0 && "OCTET_STRING_fromBuf failed for node_plmn_id");

  if (src->node_cu_du_id_present) {
    dst->node_cu_du_id = calloc(1, sizeof(long));
    assert(dst->node_cu_du_id != NULL && "Memory exhausted");
    *dst->node_cu_du_id = (long)src->node_cu_du_id;
  }

  return dst;
}

byte_array_t dapp_enc_ind_hdr_asn(e2sm_dapp_ind_hdr_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_IndicationHeader_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_IndicationHeader, &dst); });

  if (src->format == FORMAT_1_E2SM_DAPP_IND_HDR) {
    dst.ric_indicationHeader_formats.present = E2SM_DAPP_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format1;
    dst.ric_indicationHeader_formats.choice.indicationHeader_Format1 = cp_ind_hdr_frmt_1(&src->frmt_1);
  } else if (src->format == FORMAT_2_E2SM_DAPP_IND_HDR) {
    dst.ric_indicationHeader_formats.present = E2SM_DAPP_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format2;
    dst.ric_indicationHeader_formats.choice.indicationHeader_Format2 = cp_ind_hdr_frmt_2(&src->frmt_2);
  } else {
    assert(0 != 0 && "unknown format type");
  }

  byte_array_t ba = {.buf = malloc(1024), .len = 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_IndicationHeader, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_IndicationMessage_Format2_t* enc_ind_msg_frmt_2(const e2sm_dapp_ind_msg_frmt_2_t* src)
{
  assert(src != NULL);

  E2SM_DAPP_IndicationMessage_Format2_t* dst = calloc(1, sizeof(*dst));
  assert(dst != NULL && "Memory exhausted");

  const dapp_e3_subscription_list_t* subs = &src->dapp_e3_subs;
  for (size_t i = 0; i < subs->sz_dapp_e3_subscriptions; ++i) {
    const dapp_e3_subscription_item_t* ir = &subs->dapp_e3_subscriptions[i];

    DAppE3Subscription_Item_t* item = CALLOC(1, sizeof(*item));
    assert(item != NULL && "Memory exhausted");

    item->dapp_id = (long)ir->dapp_id;

    for (size_t j = 0; j < ir->sz_subscribed_e3_ran_functions; ++j) {
      unsigned long* rf = CALLOC(1, sizeof(unsigned long));
      assert(rf != NULL && "Memory exhausted");
      *rf = (unsigned long)ir->subscribed_e3_ran_functions[j];

      int rc = ASN_SEQUENCE_ADD(&item->subscribed_e3_ran_functions, rf);
      assert(rc == 0 && "ASN_SEQUENCE_ADD failed");
    }

    int rc = ASN_SEQUENCE_ADD(&dst->dappE3Subscriptions, item);
    assert(rc == 0 && "ASN_SEQUENCE_ADD failed");
  }

  return dst;
}

static E2SM_DAPP_IndicationMessage_Format1_t* enc_ind_msg_frmt_1(const e2sm_dapp_ind_msg_frmt_1_t* src)
{
  assert(src != NULL);
  assert(src->data_size > 0);
  assert(src->data != NULL);

  E2SM_DAPP_IndicationMessage_Format1_t* dst = CALLOC(1, sizeof(*dst));
  assert(dst != NULL && "Memory exhausted");

  dst->data_size = (long)src->data_size;

  int ret = OCTET_STRING_fromBuf(&dst->data, (const char*)src->data, src->data_size);
  assert(ret == 0 && "OCTET_STRING_fromBuf failed");

  return dst;
}

byte_array_t dapp_enc_ind_msg_asn(e2sm_dapp_ind_msg_t const* src)
{
  assert(src != NULL);
  E2SM_DAPP_IndicationMessage_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_IndicationMessage, &dst); });

  if (src->format == FORMAT_1_E2SM_DAPP_IND_MSG) {
    dst.ric_indicationMessage_formats.present =
        E2SM_DAPP_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format1;
    dst.ric_indicationMessage_formats.choice.indicationMessage_Format1 = enc_ind_msg_frmt_1(&src->frmt_1);
  } else if (src->format == FORMAT_2_E2SM_DAPP_IND_MSG) {
    dst.ric_indicationMessage_formats.present =
        E2SM_DAPP_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format2;
    dst.ric_indicationMessage_formats.choice.indicationMessage_Format2 = enc_ind_msg_frmt_2(&src->frmt_2);
  } else {
    assert(0 != 0 && "Unknown format type");
  }

  byte_array_t ba = {.buf = malloc(128 * 1024), .len = 128 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_IndicationMessage, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_ControlHeader_Format1_t* enc_ctrl_hdr_frmt_1(e2sm_dapp_ctrl_hdr_frmt_1_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlHeader_Format1_t* dst = calloc(1, sizeof(E2SM_DAPP_ControlHeader_Format1_t));
  assert(dst != NULL && "Memory exhausted");

  dst->ran_function_id = (long)src->ran_function_id;
  dst->dapp_id = (long)src->dapp_id;

  return dst;
}

byte_array_t dapp_enc_ctrl_hdr_asn(e2sm_dapp_ctrl_hdr_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlHeader_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ControlHeader, &dst); });

  if (src->format == FORMAT_1_E2SM_DAPP_CTRL_HDR) {
    dst.ric_controlHeader_formats.present = E2SM_DAPP_ControlHeader__ric_controlHeader_formats_PR_controlHeader_Format1;
    dst.ric_controlHeader_formats.choice.controlHeader_Format1 = enc_ctrl_hdr_frmt_1(&src->frmt_1);
  } else {
    assert(0 != 0 && "Unknown format");
  }

  byte_array_t ba = {.buf = malloc(16 * 1024), .len = 16 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_ControlHeader, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_ControlMessage_Format1_t* enc_ctrl_msg_frmt_1(e2sm_dapp_ctrl_msg_frmt_1_t const* src)
{
  assert(src != NULL);
  assert(src->data_size > 0);
  assert(src->data != NULL);

  E2SM_DAPP_ControlMessage_Format1_t* dst = CALLOC(1, sizeof(*dst));
  assert(dst != NULL && "Memory exhausted");

  dst->data_size = (long)src->data_size;

  int ret = OCTET_STRING_fromBuf(&dst->data, (const char*)src->data, src->data_size);
  assert(ret == 0 && "OCTET_STRING_fromBuf failed");

  return dst;
}

byte_array_t dapp_enc_ctrl_msg_asn(e2sm_dapp_ctrl_msg_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlMessage_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ControlMessage, &dst); });

  if (src->format == FORMAT_1_E2SM_DAPP_CTRL_MSG) {
    dst.ric_controlMessage_formats.present = E2SM_DAPP_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format1;

    dst.ric_controlMessage_formats.choice.controlMessage_Format1 = calloc(1, sizeof(E2SM_DAPP_ControlMessage_Format1_t));
    assert(dst.ric_controlMessage_formats.choice.controlMessage_Format1 != NULL && "Memory exhausted");

    dst.ric_controlMessage_formats.choice.controlMessage_Format1 = enc_ctrl_msg_frmt_1(&src->frmt_1);
  } else {
    assert(0 != 0 && "Unknown format type");
  }

  byte_array_t ba = {.buf = malloc(16 * 1024), .len = 16 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_ControlMessage, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_ControlOutcome_Format1_t* enc_ctrl_out_frmt_1(e2sm_dapp_ctrl_out_frmt_1_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlOutcome_Format1_t* dst = calloc(1, sizeof(E2SM_DAPP_ControlOutcome_Format1_t));
  assert(dst != NULL && "Memory exhausted");

  return dst;
}

byte_array_t dapp_enc_ctrl_out_asn(e2sm_dapp_ctrl_out_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlOutcome_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ControlOutcome, &dst); });

  if (src->format == FORMAT_1_E2SM_DAPP_CTRL_OUT) {
    dst.ric_controlOutcome_formats.present = E2SM_DAPP_ControlOutcome__ric_controlOutcome_formats_PR_controlOutcome_Format1;
    dst.ric_controlOutcome_formats.choice.controlOutcome_Format1 = enc_ctrl_out_frmt_1(&src->frmt_1);
  } else {
    assert(0 != 0 && "Unknown format");
  }

  byte_array_t ba = {.buf = malloc(16 * 1024), .len = 16 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_ControlOutcome, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static RANfunction_Name_t enc_ran_func_name(ran_function_name_t const* src)
{
  assert(src != NULL);

  RANfunction_Name_t dst = {0};

  dst.ranFunction_ShortName = copy_ba_to_ostring(src->name);

  dst.ranFunction_E2SM_OID = copy_ba_to_ostring(src->oid);

  dst.ranFunction_Description = copy_ba_to_ostring(src->description);

  assert(src->instance == NULL && "not implemented");

  return dst;
}

static RANFunctionDefinition_EventTrigger_t enc_ran_func_def_ev_trg(ran_func_def_ev_trig_dapp_sm_t const* src)
{
  assert(src != NULL);
  RANFunctionDefinition_EventTrigger_t dst = {0};
  return dst;
}

static DAppE3Subscription_List_t* enc_dapp_e3_subscription_list(dapp_e3_subscription_list_t const* src)
{
  assert(src != NULL);
  assert(src->sz_dapp_e3_subscriptions > 0 && src->sz_dapp_e3_subscriptions < 256);

  DAppE3Subscription_List_t* dst = calloc(1, sizeof(DAppE3Subscription_List_t));
  assert(dst != NULL && "Memory exhausted");

  for (size_t i = 0; i < src->sz_dapp_e3_subscriptions; ++i) {
    const dapp_e3_subscription_item_t* ir = &src->dapp_e3_subscriptions[i];

    DAppE3Subscription_Item_t* item = CALLOC(1, sizeof(*item));
    assert(item != NULL && "Memory exhausted");

    item->dapp_id = (long)ir->dapp_id;

    for (size_t j = 0; j < ir->sz_subscribed_e3_ran_functions; ++j) {
      unsigned long* rf = CALLOC(1, sizeof(unsigned long));
      assert(rf != NULL && "Memory exhausted");
      *rf = (unsigned long)ir->subscribed_e3_ran_functions[j];

      int rc = ASN_SEQUENCE_ADD(&item->subscribed_e3_ran_functions, rf);
      assert(rc == 0 && "ASN_SEQUENCE_ADD failed for subscribed_e3_ran_functions");
    }

    int rc = ASN_SEQUENCE_ADD(dst, item);
    assert(rc == 0 && "ASN_SEQUENCE_ADD failed for DAppE3Subscription_List");
  }

  return dst;
}

static RANFunctionDefinition_Report_t enc_ran_func_def_report(ran_func_def_report_dapp_sm_t const* src)
{
  assert(src != NULL);

  RANFunctionDefinition_Report_t dst = {0};

  for (size_t i = 0; i < src->sz_seq_report_sty; ++i) {
    const seq_report_sty_dapp_sm_t* ir = &src->seq_report_sty[i];

    RANFunctionDefinition_Report_Item_t* item = CALLOC(1, sizeof(*item));
    assert(item != NULL && "Memory exhausted");

    item->ric_ReportStyle_Type = ir->report_type;

    item->ric_ReportStyle_Name = copy_ba_to_ostring(ir->name);

    item->ric_IndicationHeaderFormat_Type = ir->ind_hdr_type;

    item->ric_IndicationMessageFormat_Type = ir->ind_msg_type;

    if (ir->dapp_e3_subs != NULL) {
      item->dappE3Subscriptions = enc_dapp_e3_subscription_list(ir->dapp_e3_subs);
    }

    int rc = ASN_SEQUENCE_ADD(&dst.ric_ReportStyle_List.list, item);
    assert(rc == 0 && "ASN_SEQUENCE_ADD failed for ReportStyle_List");
  }

  return dst;
}

static RANFunctionDefinition_Control_t enc_ran_func_def_ctrl(ran_func_def_ctrl_dapp_sm_t const* src)
{
  assert(src != NULL);

  RANFunctionDefinition_Control_t dst = {0};

  for (size_t i = 0; i < src->sz_seq_ctrl_style; ++i) {
    const seq_ctrl_style_dapp_sm_t* ir = &src->seq_ctrl_style[i];

    RANFunctionDefinition_Control_Item_t* item = CALLOC(1, sizeof(*item));
    assert(item != NULL && "Memory exhausted");

    item->ric_ControlStyle_Type = ir->style_type;

    item->ric_ControlStyle_Name = copy_ba_to_ostring(ir->name);

    item->ric_ControlHeaderFormat_Type = ir->hdr;

    item->ric_ControlMessageFormat_Type = ir->msg;

    item->ric_ControlOutcomeFormat_Type = ir->out_frmt;

    if (ir->dapp_e3_subs != NULL) {
      item->dappE3Subscriptions = enc_dapp_e3_subscription_list(ir->dapp_e3_subs);
    }

    int rc = ASN_SEQUENCE_ADD(&dst.ric_ControlStyle_List.list, item);
    assert(rc == 0 && "ASN_SEQUENCE_ADD failed for ControlStyle_List");
  }

  return dst;
}

byte_array_t dapp_enc_func_def_asn(e2sm_dapp_func_def_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_RANFunctionDefinition_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_RANFunctionDefinition, &dst); });

  dst.ranFunction_Name = enc_ran_func_name(&src->name);

  if (src->ev_trig != NULL) {
    dst.ranFunctionDefinition_EventTrigger = calloc(1, sizeof(RANFunctionDefinition_EventTrigger_t));
    assert(dst.ranFunctionDefinition_EventTrigger != NULL && "Memory exhausted");
    *dst.ranFunctionDefinition_EventTrigger = enc_ran_func_def_ev_trg(src->ev_trig);
  }

  if (src->report != NULL) {
    dst.ranFunctionDefinition_Report = calloc(1, sizeof(RANFunctionDefinition_Report_t));
    assert(dst.ranFunctionDefinition_Report != NULL && "Memory exhausted");
    *dst.ranFunctionDefinition_Report = enc_ran_func_def_report(src->report);
  }

  if (src->ctrl != NULL) {
    dst.ranFunctionDefinition_Control = calloc(1, sizeof(RANFunctionDefinition_Control_t));
    assert(dst.ranFunctionDefinition_Control != NULL && "Memory exhausted");
    *dst.ranFunctionDefinition_Control = enc_ran_func_def_ctrl(src->ctrl);
  }

  byte_array_t ba = {.buf = malloc(16 * 1024), .len = 16 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_RANFunctionDefinition, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}
