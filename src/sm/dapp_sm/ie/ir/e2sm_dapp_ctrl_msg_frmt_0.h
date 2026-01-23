#ifndef E2SM_DAPP_CTRL_MSG_FRMT_0_H
#define E2SM_DAPP_CTRL_MSG_FRMT_0_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint32_t data_size;
  uint8_t* data;
} e2sm_dapp_ctrl_msg_frmt_0_t;

void free_e2sm_dapp_ctrl_msg_frmt_0(e2sm_dapp_ctrl_msg_frmt_0_t* src);

bool eq_e2sm_dapp_ctrl_msg_frmt_0(e2sm_dapp_ctrl_msg_frmt_0_t const* m0, e2sm_dapp_ctrl_msg_frmt_0_t const* m1);

e2sm_dapp_ctrl_msg_frmt_0_t cp_e2sm_dapp_ctrl_msg_frmt_0(e2sm_dapp_ctrl_msg_frmt_0_t const* src);

#endif
