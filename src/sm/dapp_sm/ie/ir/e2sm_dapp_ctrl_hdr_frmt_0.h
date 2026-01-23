#ifndef E2SM_DAPP_CTRL_HDR_FRMT_0_E2SM_DAPP_H
#define E2SM_DAPP_CTRL_HDR_FRMT_0_E2SM_DAPP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint32_t ran_function_id;
  uint32_t dapp_id;
} e2sm_dapp_ctrl_hdr_frmt_0_t;

void free_e2sm_dapp_ctrl_hdr_frmt_0(e2sm_dapp_ctrl_hdr_frmt_0_t* src);

bool eq_e2sm_dapp_ctrl_hdr_frmt_0(e2sm_dapp_ctrl_hdr_frmt_0_t const* m0, e2sm_dapp_ctrl_hdr_frmt_0_t const* m1);

e2sm_dapp_ctrl_hdr_frmt_0_t cp_e2sm_dapp_ctrl_hdr_frmt_0(e2sm_dapp_ctrl_hdr_frmt_0_t const* src);

#endif
