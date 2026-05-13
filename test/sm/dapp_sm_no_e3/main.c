#include "../../rnd/fill_rnd_data_dapp.h"
#include "../../../src/util/alg_ds/alg/defer.h"
#include "../../../src/sm/dapp_sm/dapp_sm_agent.h"
#include "../../../src/sm/dapp_sm/dapp_sm_id.h"
#include "../../../src/sm/dapp_sm/enc/dapp_enc_asn.h"
#include "../../../src/sm/dapp_sm/dec/dapp_dec_asn.h"
#include "../../../src/sm/dapp_sm/ie/dapp_data_ie.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static bool fail_read_ind(void* read)
{
  (void)read;
  assert(0 != 0 && "read_ind must NOT be called when E3_AGENT is undefined");
  return false;
}

static void fail_read_setup(void* read)
{
  (void)read;
  assert(0 != 0 && "read_setup must NOT be called when E3_AGENT is undefined");
}

static sm_ag_if_ans_t fail_write_ctrl(void const* data)
{
  (void)data;
  assert(0 != 0 && "write_ctrl must NOT be called when E3_AGENT is undefined");
  sm_ag_if_ans_t ans = {0};
  return ans;
}

static sm_ag_if_ans_t fail_write_subs(void const* data)
{
  (void)data;
  assert(0 != 0 && "write_subs must NOT be called when E3_AGENT is undefined");
  sm_ag_if_ans_t ans = {0};
  return ans;
}

static void check_subscription_no_e3(sm_agent_t* ag)
{
  dapp_sub_data_t dapp = fill_rnd_dapp_subscription();
  defer({ free_dapp_sub_data(&dapp); });

  byte_array_t ba_et = dapp_enc_event_trigger_asn(&dapp.et);
  defer({ free_byte_array(ba_et); });

  byte_array_t ba_ad = dapp_enc_action_def_asn(dapp.action_def);
  defer({ free_byte_array(ba_ad); });

  sm_subs_data_t data = {.event_trigger = ba_et.buf,
                         .len_et = ba_et.len,
                         .action_def = ba_ad.buf,
                         .len_ad = ba_ad.len};

  sm_ag_if_ans_subs_t subs = ag->proc.on_subscription(ag, &data);
  /* No-E3 path: the answer is zero-initialized. */
  assert(subs.type == 0);
  assert(subs.aper.free_aper_subs == NULL);
}

static void check_ctrl_no_e3(sm_agent_t* ag)
{
  e2sm_dapp_ctrl_hdr_t hdr = fill_rnd_dapp_ctrl_hdr();
  defer({ free_e2sm_dapp_ctrl_hdr(&hdr); });

  e2sm_dapp_ctrl_msg_t msg = fill_rnd_dapp_ctrl_msg();
  defer({ free_e2sm_dapp_ctrl_msg(&msg); });

  byte_array_t ba_hdr = dapp_enc_ctrl_hdr_asn(&hdr);
  defer({ free_byte_array(ba_hdr); });

  byte_array_t ba_msg = dapp_enc_ctrl_msg_asn(&msg);
  defer({ free_byte_array(ba_msg); });

  sm_ctrl_req_data_t req = {.ctrl_hdr = ba_hdr.buf,
                            .len_hdr = ba_hdr.len,
                            .ctrl_msg = ba_msg.buf,
                            .len_msg = ba_msg.len};

  sm_ctrl_out_data_t out = ag->proc.on_control(ag, &req);

  assert(out.ctrl_out == NULL);
  assert(out.len_out == 0);
}

static void check_e2_setup_no_e3(sm_agent_t* ag)
{
  sm_e2_setup_data_t data = ag->proc.on_e2_setup(ag);
  defer({ free_sm_e2_setup(&data); });

  assert(data.ran_fun_def != NULL);
  assert(data.len_rfd > 0);

  e2sm_dapp_func_def_t out = dapp_dec_func_def_asn(data.len_rfd, data.ran_fun_def);
  defer({ free_e2sm_dapp_func_def(&out); });

  byte_array_t expected_name = cp_str_to_ba(SM_DAPP_SHORT_NAME);
  defer({ free_byte_array(expected_name); });
  byte_array_t expected_oid = cp_str_to_ba(SM_DAPP_OID);
  defer({ free_byte_array(expected_oid); });
  byte_array_t expected_desc = cp_str_to_ba(SM_DAPP_DESCRIPTION);
  defer({ free_byte_array(expected_desc); });

  assert(eq_byte_array(&out.name.name, &expected_name) == true);
  assert(eq_byte_array(&out.name.oid, &expected_oid) == true);
  assert(eq_byte_array(&out.name.description, &expected_desc) == true);
}

int main(void)
{
  srand((unsigned)time(NULL));

  sm_io_ag_ran_t io_ag = {0};

  io_ag.read_ind_tbl[DAPP_STATS_V0] = fail_read_ind;
  io_ag.read_setup_tbl[DAPP_AGENT_IF_E2_SETUP_ANS_V0] = fail_read_setup;
  io_ag.write_ctrl_tbl[DAPP_CTRL_V0] = fail_write_ctrl;
  io_ag.write_subs_tbl[DAPP_SUBS_V0] = fail_write_subs;

  sm_agent_t* sm_ag = make_dapp_sm_agent(io_ag);

  printf("Running DAPP SM agent test with E3_AGENT undefined.\n");
  for (int i = 0; i < 256; ++i) {
    check_subscription_no_e3(sm_ag);
    check_ctrl_no_e3(sm_ag);
    check_e2_setup_no_e3(sm_ag);
  }

  sm_ag->free_sm(sm_ag);

  printf("DAPP SM no-E3 stub-path test passed\n");
  return EXIT_SUCCESS;
}
