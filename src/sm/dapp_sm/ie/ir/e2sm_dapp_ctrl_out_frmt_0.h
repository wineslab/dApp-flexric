#ifndef E2SM_DAPP_CTRL_OUT_FRMT_0_H
#define E2SM_DAPP_CTRL_OUT_FRMT_0_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
} e2sm_dapp_ctrl_out_frmt_0_t;

void free_e2sm_dapp_ctrl_out_frmt_0(e2sm_dapp_ctrl_out_frmt_0_t* src);

e2sm_dapp_ctrl_out_frmt_0_t cp_e2sm_dapp_ctrl_out_frmt_0(e2sm_dapp_ctrl_out_frmt_0_t const* src);

bool eq_e2sm_dapp_ctrl_out_frmt_0(e2sm_dapp_ctrl_out_frmt_0_t const* m0, e2sm_dapp_ctrl_out_frmt_0_t const* m1);

#endif
