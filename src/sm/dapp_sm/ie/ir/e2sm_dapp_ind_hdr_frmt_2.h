#ifndef E2SM_DAPP_INDICATION_HEADER_FORMAT_2_H
#define E2SM_DAPP_INDICATION_HEADER_FORMAT_2_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
  uint8_t node_type;
  uint8_t node_plmn_id[3];
  uint32_t node_nb_id;

  bool node_cu_du_id_present;
  uint64_t node_cu_du_id;

} e2sm_dapp_ind_hdr_frmt_2_t;

e2sm_dapp_ind_hdr_frmt_2_t cp_e2sm_dapp_ind_hdr_frmt_2(e2sm_dapp_ind_hdr_frmt_2_t const* src);

void free_e2sm_dapp_ind_hdr_frmt_2(e2sm_dapp_ind_hdr_frmt_2_t* src);

bool eq_e2sm_dapp_ind_hdr_frmt_2(e2sm_dapp_ind_hdr_frmt_2_t const* m0, e2sm_dapp_ind_hdr_frmt_2_t const* m1);

#endif
