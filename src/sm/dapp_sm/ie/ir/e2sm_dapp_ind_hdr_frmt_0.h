#ifndef E2SM_DAPP_INDICATION_HEADER_FORMAT_0_H
#define E2SM_DAPP_INDICATION_HEADER_FORMAT_0_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
  uint32_t ran_function_id;
  uint32_t dapp_id;
} e2sm_dapp_ind_hdr_frmt_0_t;

e2sm_dapp_ind_hdr_frmt_0_t cp_e2sm_dapp_ind_hdr_frmt_0(e2sm_dapp_ind_hdr_frmt_0_t const* src);

void free_e2sm_dapp_ind_hdr_frmt_0(e2sm_dapp_ind_hdr_frmt_0_t* src);

bool eq_e2sm_dapp_ind_hdr_frmt_0(e2sm_dapp_ind_hdr_frmt_0_t const* m0, e2sm_dapp_ind_hdr_frmt_0_t const* m1);

#endif
