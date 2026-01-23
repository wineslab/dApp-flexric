#include "e2sm_dapp_ctrl_hdr_frmt_0.h"
#include <assert.h>
#include <string.h>

void free_e2sm_dapp_ctrl_hdr_frmt_0(e2sm_dapp_ctrl_hdr_frmt_0_t* src)
{
  assert(src != NULL);
}

bool eq_e2sm_dapp_ctrl_hdr_frmt_0(e2sm_dapp_ctrl_hdr_frmt_0_t const* m0, e2sm_dapp_ctrl_hdr_frmt_0_t const* m1)
{
  if (m0 == m1)
    return true;
  if (!m0 || !m1)
    return false;

  return (m0->ran_function_id == m1->ran_function_id) && (m0->dapp_id == m1->dapp_id);
}

e2sm_dapp_ctrl_hdr_frmt_0_t cp_e2sm_dapp_ctrl_hdr_frmt_0(e2sm_dapp_ctrl_hdr_frmt_0_t const* src)
{
  assert(src != NULL);

  e2sm_dapp_ctrl_hdr_frmt_0_t dst;
  dst.ran_function_id = src->ran_function_id;
  dst.dapp_id = src->dapp_id;
  return dst;
}
