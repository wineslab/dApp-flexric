#ifndef DAPP_ENCODE_GENERIC_H
#define DAPP_ENCODE_GENERIC_H

#include "dapp_enc_asn.h"
#include "dapp_enc_fb.h"
#include "dapp_enc_plain.h"

#define dapp_enc_event_trigger(T, U)                    \
  _Generic((T),                                         \
      dapp_enc_plain_t *: dapp_enc_event_trigger_plain, \
      dapp_enc_asn_t *: dapp_enc_event_trigger_asn,     \
      dapp_enc_fb_t *: dapp_enc_event_trigger_fb,       \
      default: dapp_enc_event_trigger_plain)(U)

#define dapp_enc_action_def(T, U)                    \
  _Generic((T),                                      \
      dapp_enc_plain_t *: dapp_enc_action_def_plain, \
      dapp_enc_asn_t *: dapp_enc_action_def_asn,     \
      dapp_enc_fb_t *: dapp_enc_action_def_fb,       \
      default: dapp_enc_action_def_plain)(U)

#define dapp_enc_ind_hdr(T, U)                    \
  _Generic((T),                                   \
      dapp_enc_plain_t *: dapp_enc_ind_hdr_plain, \
      dapp_enc_asn_t *: dapp_enc_ind_hdr_asn,     \
      dapp_enc_fb_t *: dapp_enc_ind_hdr_fb,       \
      default: dapp_enc_ind_hdr_plain)(U)

#define dapp_enc_ind_msg(T, U)                    \
  _Generic((T),                                   \
      dapp_enc_plain_t *: dapp_enc_ind_msg_plain, \
      dapp_enc_asn_t *: dapp_enc_ind_msg_asn,     \
      dapp_enc_fb_t *: dapp_enc_ind_msg_fb,       \
      default: dapp_enc_ind_msg_plain)(U)

#define dapp_enc_ctrl_hdr(T, U)                    \
  _Generic((T),                                    \
      dapp_enc_plain_t *: dapp_enc_ctrl_hdr_plain, \
      dapp_enc_asn_t *: dapp_enc_ctrl_hdr_asn,     \
      dapp_enc_fb_t *: dapp_enc_ctrl_hdr_fb,       \
      default: dapp_enc_ctrl_hdr_plain)(U)

#define dapp_enc_ctrl_msg(T, U)                    \
  _Generic((T),                                    \
      dapp_enc_plain_t *: dapp_enc_ctrl_msg_plain, \
      dapp_enc_asn_t *: dapp_enc_ctrl_msg_asn,     \
      dapp_enc_fb_t *: dapp_enc_ctrl_msg_fb,       \
      default: dapp_enc_ctrl_msg_plain)(U)

#define dapp_enc_ctrl_out(T, U)                    \
  _Generic((T),                                    \
      dapp_enc_plain_t *: dapp_enc_ctrl_out_plain, \
      dapp_enc_asn_t *: dapp_enc_ctrl_out_asn,     \
      dapp_enc_fb_t *: dapp_enc_ctrl_out_fb,       \
      default: dapp_enc_ctrl_out_plain)(U)

#define dapp_enc_func_def(T, U)                    \
  _Generic((T),                                    \
      dapp_enc_plain_t *: dapp_enc_func_def_plain, \
      dapp_enc_asn_t *: dapp_enc_func_def_asn,     \
      dapp_enc_fb_t *: dapp_enc_func_def_fb,       \
      default: dapp_enc_func_def_plain)(U)

#endif
