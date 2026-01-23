#ifndef E2SM_DAPP_INDICATION_MSG_FORMAT_0_H
#define E2SM_DAPP_INDICATION_MSG_FORMAT_0_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  size_t   data_size;
  uint8_t* data;
} e2sm_dapp_ind_msg_frmt_0_t;

void free_e2sm_dapp_ind_msg_frmt_0(e2sm_dapp_ind_msg_frmt_0_t* src);

bool eq_e2sm_dapp_ind_msg_frmt_0(e2sm_dapp_ind_msg_frmt_0_t const* m0, e2sm_dapp_ind_msg_frmt_0_t const* m1);

e2sm_dapp_ind_msg_frmt_0_t cp_e2sm_dapp_ind_msg_frmt_0(e2sm_dapp_ind_msg_frmt_0_t const* src);

#endif
