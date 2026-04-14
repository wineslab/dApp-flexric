#ifndef E2SM_DAPP_INDICATION_HEADER_FORMAT_1_H
#define E2SM_DAPP_INDICATION_HEADER_FORMAT_1_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
  uint32_t ran_function_id;
  uint32_t dapp_id;

  uint8_t node_type;
  uint8_t node_plmn_id[3];
  uint32_t node_nb_id;

  bool node_cu_du_id_present;
  uint64_t node_cu_du_id;

} e2sm_dapp_ind_hdr_frmt_1_t;

e2sm_dapp_ind_hdr_frmt_1_t cp_e2sm_dapp_ind_hdr_frmt_1(e2sm_dapp_ind_hdr_frmt_1_t const* src);

void free_e2sm_dapp_ind_hdr_frmt_1(e2sm_dapp_ind_hdr_frmt_1_t* src);

bool eq_e2sm_dapp_ind_hdr_frmt_1(e2sm_dapp_ind_hdr_frmt_1_t const* m0, e2sm_dapp_ind_hdr_frmt_1_t const* m1);

#endif
