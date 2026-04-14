#ifndef DAPP_DECRYPTION_PLAIN_H
#define DAPP_DECRYPTION_PLAIN_H

#include <stddef.h>
#include "../ie/dapp_data_ie.h"

// Currently plain decoding is not implemented

typedef struct {
} dapp_dec_plain_t;

e2sm_dapp_event_trigger_t dapp_dec_event_trigger_plain(size_t len, uint8_t const ev_tr[len]);

e2sm_dapp_action_def_t dapp_dec_action_def_plain(size_t len, uint8_t const buf[len]);

e2sm_dapp_ind_hdr_t dapp_dec_ind_hdr_plain(size_t len, uint8_t const ind_hdr[len]);

e2sm_dapp_ind_msg_t dapp_dec_ind_msg_plain(size_t len, uint8_t const ind_msg[len]);

e2sm_dapp_ctrl_hdr_t dapp_dec_ctrl_hdr_plain(size_t len, uint8_t const ctrl_hdr[len]);

e2sm_dapp_ctrl_msg_t dapp_dec_ctrl_msg_plain(size_t len, uint8_t const ctrl_msg[len]);

e2sm_dapp_ctrl_out_t dapp_dec_ctrl_out_plain(size_t len, uint8_t const ctrl_out[len]);

e2sm_dapp_func_def_t dapp_dec_func_def_plain(size_t len, uint8_t const func_def[len]);

#endif
