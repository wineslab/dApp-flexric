#ifndef DAPP_ENCRYPTION_FLATBUFFERS_H
#define DAPP_ENCRYPTION_FLATBUFFERS_H

#include "../../../util/byte_array.h"
#include "../ie/dapp_data_ie.h"

// Currently flatbuffer encoding is not implemented

typedef struct {
} dapp_enc_fb_t;

byte_array_t dapp_enc_event_trigger_fb(e2sm_dapp_event_trigger_t const* event_trigger);

byte_array_t dapp_enc_action_def_fb(e2sm_dapp_action_def_t const*);

byte_array_t dapp_enc_ind_hdr_fb(e2sm_dapp_ind_hdr_t const*);

byte_array_t dapp_enc_ind_msg_fb(e2sm_dapp_ind_msg_t const*);

byte_array_t dapp_enc_ctrl_hdr_fb(e2sm_dapp_ctrl_hdr_t const*);

byte_array_t dapp_enc_ctrl_msg_fb(e2sm_dapp_ctrl_msg_t const*);

byte_array_t dapp_enc_ctrl_out_fb(e2sm_dapp_ctrl_out_t const*);

byte_array_t dapp_enc_func_def_fb(e2sm_dapp_func_def_t const*);

#endif
