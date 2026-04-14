#ifndef E2SM_DAPP_CTRL_OUT_FRMT_1_H
#define E2SM_DAPP_CTRL_OUT_FRMT_1_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
} e2sm_dapp_ctrl_out_frmt_1_t;

void free_e2sm_dapp_ctrl_out_frmt_1(e2sm_dapp_ctrl_out_frmt_1_t* src);

e2sm_dapp_ctrl_out_frmt_1_t cp_e2sm_dapp_ctrl_out_frmt_1(e2sm_dapp_ctrl_out_frmt_1_t const* src);

bool eq_e2sm_dapp_ctrl_out_frmt_1(e2sm_dapp_ctrl_out_frmt_1_t const* m0, e2sm_dapp_ctrl_out_frmt_1_t const* m1);

#endif
