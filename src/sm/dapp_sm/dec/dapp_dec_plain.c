#include "dapp_dec_plain.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

e2sm_dapp_event_trigger_t dapp_dec_event_trigger_plain(size_t len, uint8_t const ev_tr[len])
{
  assert(0 != 0 && "Not implemented");
  assert(ev_tr != NULL);
  assert(len > 0);
  e2sm_dapp_event_trigger_t ev = {0};
  return ev;
}

e2sm_dapp_action_def_t dapp_dec_action_def_plain(size_t len, uint8_t const action_def[len])
{
  assert(0 != 0 && "Not implemented");
  assert(action_def != NULL);
  assert(len > 0);
  e2sm_dapp_action_def_t act_def = {0};
  return act_def;
}

e2sm_dapp_ind_hdr_t dapp_dec_ind_hdr_plain(size_t len, uint8_t const ind_hdr[len])
{
  assert(0 != 0 && "Not implemented");
  assert(ind_hdr != NULL);
  assert(len > 0);
  e2sm_dapp_ind_hdr_t ret = {0};
  return ret;
}

e2sm_dapp_ind_msg_t dapp_dec_ind_msg_plain(size_t len, uint8_t const ind_msg[len])
{
  assert(0 != 0 && "Not implemented");
  assert(ind_msg != NULL);
  assert(len > 0);
  e2sm_dapp_ind_msg_t ret = {0};
  return ret;
}

e2sm_dapp_ctrl_hdr_t dapp_dec_ctrl_hdr_plain(size_t len, uint8_t const ctrl_hdr[len])
{
  assert(0 != 0 && "Not implemented");
  assert(ctrl_hdr != NULL);
  assert(len > 0);
  e2sm_dapp_ctrl_hdr_t ret = {0};
  return ret;
}

e2sm_dapp_ctrl_msg_t dapp_dec_ctrl_msg_plain(size_t len, uint8_t const ctrl_msg[len])
{
  assert(0 != 0 && "Not implemented");
  assert(ctrl_msg != NULL);
  assert(len > 0);
  e2sm_dapp_ctrl_msg_t ret = {0};
  return ret;
}

e2sm_dapp_ctrl_out_t dapp_dec_ctrl_out_plain(size_t len, uint8_t const ctrl_out[len])
{
  assert(0 != 0 && "Not implemented");
  assert(ctrl_out != NULL);
  assert(len > 0);
  e2sm_dapp_ctrl_out_t out = {0};
  return out;
}

e2sm_dapp_func_def_t dapp_dec_func_def_plain(size_t len, const uint8_t buf[len])
{
  assert(0 != 0 && "Not implemented");
  assert(buf != NULL);
  assert(len > 0);
  e2sm_dapp_func_def_t out = {0};
  return out;
}
