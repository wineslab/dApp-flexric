#ifndef DAPP_EVENT_TRIGGER_FORMAT_0_SM_DAPP_SM_H
#define DAPP_EVENT_TRIGGER_FORMAT_0_SM_DAPP_SM_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
} e2sm_dapp_ev_trg_frmt_0_t;

void free_e2sm_dapp_ev_trg_frmt_0(e2sm_dapp_ev_trg_frmt_0_t* src);

bool eq_e2sm_dapp_ev_trg_frmt_0(e2sm_dapp_ev_trg_frmt_0_t const* m0, e2sm_dapp_ev_trg_frmt_0_t const* m1);

e2sm_dapp_ev_trg_frmt_0_t cp_e2sm_dapp_ev_trg_frmt_0(e2sm_dapp_ev_trg_frmt_0_t const* src);

#endif
