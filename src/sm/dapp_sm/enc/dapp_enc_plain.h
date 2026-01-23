#ifndef DAPP_ENCRYPTION_PLAIN_H
#define DAPP_ENCRYPTION_PLAIN_H

#include "../../../util/byte_array.h"
#include "../ie/dapp_data_ie.h"

// Currently plain encoding is not implemented

typedef struct {
} dapp_enc_plain_t;

byte_array_t dapp_enc_event_trigger_plain(e2sm_dapp_event_trigger_t const* event_trigger);

byte_array_t dapp_enc_action_def_plain(e2sm_dapp_action_def_t const*);

byte_array_t dapp_enc_ind_hdr_plain(e2sm_dapp_ind_hdr_t const*);

byte_array_t dapp_enc_ind_msg_plain(e2sm_dapp_ind_msg_t const*);

byte_array_t dapp_enc_ctrl_hdr_plain(e2sm_dapp_ctrl_hdr_t const*);

byte_array_t dapp_enc_ctrl_msg_plain(e2sm_dapp_ctrl_msg_t const*);

byte_array_t dapp_enc_ctrl_out_plain(e2sm_dapp_ctrl_out_t const*);

byte_array_t dapp_enc_func_def_plain(e2sm_dapp_func_def_t const*);

#endif
