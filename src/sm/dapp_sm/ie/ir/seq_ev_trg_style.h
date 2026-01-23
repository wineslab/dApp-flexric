#ifndef SEQ_EV_TRG_STYLE_E2SM_DAPP_H
#define SEQ_EV_TRG_STYLE_E2SM_DAPP_H

#include "../../../../util/byte_array.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint32_t style;
  byte_array_t name;
  uint32_t format;

} seq_ev_trg_style_dapp_sm_t;

void free_seq_ev_trg_style_dapp_sm(seq_ev_trg_style_dapp_sm_t* src);

bool eq_seq_ev_trg_style_dapp_sm(seq_ev_trg_style_dapp_sm_t const* m0, seq_ev_trg_style_dapp_sm_t const* m1);

seq_ev_trg_style_dapp_sm_t cp_seq_ev_trg_style_dapp_sm(seq_ev_trg_style_dapp_sm_t const* src);

#endif
