#include <assert.h>

#include "e2sm_dapp_ev_trg_frmt_0.h"

void free_e2sm_dapp_ev_trg_frmt_0(e2sm_dapp_ev_trg_frmt_0_t* src)
{
  assert(src != NULL);
}

bool eq_e2sm_dapp_ev_trg_frmt_0(e2sm_dapp_ev_trg_frmt_0_t const* m0, e2sm_dapp_ev_trg_frmt_0_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  return true;
}

e2sm_dapp_ev_trg_frmt_0_t cp_e2sm_dapp_ev_trg_frmt_0(e2sm_dapp_ev_trg_frmt_0_t const* src)
{
  assert(src != NULL);

  e2sm_dapp_ev_trg_frmt_0_t dst = {};

  return dst;
}
