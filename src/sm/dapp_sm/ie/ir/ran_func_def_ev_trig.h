#ifndef RAN_FUNC_DEF_EV_TRIG_DAPP_SM_H
#define RAN_FUNC_DEF_EV_TRIG_DAPP_SM_H

#include <stdbool.h>
#include <stddef.h>
#include "seq_ev_trg_style.h"

typedef struct {
  size_t sz_seq_ev_trg_style;
  seq_ev_trg_style_dapp_sm_t* seq_ev_trg_style;
} ran_func_def_ev_trig_dapp_sm_t;

void free_ran_func_def_ev_trig_dapp_sm(ran_func_def_ev_trig_dapp_sm_t* src);

bool eq_ran_func_def_ev_trig_dapp_sm(ran_func_def_ev_trig_dapp_sm_t const* m0, ran_func_def_ev_trig_dapp_sm_t const* m1);

ran_func_def_ev_trig_dapp_sm_t cp_ran_func_def_ev_trig_dapp_sm(ran_func_def_ev_trig_dapp_sm_t const* src);

#endif
