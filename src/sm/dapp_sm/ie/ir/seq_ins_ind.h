#ifndef SEQ_INS_IND_E2SM_DAPP_H
#define SEQ_INS_IND_E2SM_DAPP_H

#include "../../../../util/byte_array.h"

typedef struct {
  uint16_t id;
  byte_array_t name;
} seq_ins_ind_dapp_sm_t;

void free_seq_ins_ind_dapp_sm(seq_ins_ind_dapp_sm_t* src);

bool eq_seq_ins_ind_dapp_sm(seq_ins_ind_dapp_sm_t const* m0, seq_ins_ind_dapp_sm_t const* m1);

seq_ins_ind_dapp_sm_t cp_seq_ins_ind_dapp_sm(seq_ins_ind_dapp_sm_t const* src);

#endif
