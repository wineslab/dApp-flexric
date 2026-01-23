#ifndef DAPP_DECRYPTION_GENERIC
#define DAPP_DECRYPTION_GENERIC

#include "dapp_dec_asn.h"
#include "dapp_dec_fb.h"
#include "dapp_dec_plain.h"

#define dapp_dec_event_trigger(T, U, V)                 \
  _Generic((T),                                         \
      dapp_enc_plain_t *: dapp_dec_event_trigger_plain, \
      dapp_enc_asn_t *: dapp_dec_event_trigger_asn,     \
      dapp_enc_fb_t *: dapp_dec_event_trigger_fb,       \
      default: dapp_dec_event_trigger_plain)(U, V)

#define dapp_dec_action_def(T, U, V)                 \
  _Generic((T),                                      \
      dapp_enc_plain_t *: dapp_dec_action_def_plain, \
      dapp_enc_asn_t *: dapp_dec_action_def_asn,     \
      dapp_enc_fb_t *: dapp_dec_action_def_fb,       \
      default: dapp_dec_action_def_plain)(U, V)

#define dapp_dec_ind_hdr(T, U, V)                 \
  _Generic((T),                                   \
      dapp_enc_plain_t *: dapp_dec_ind_hdr_plain, \
      dapp_enc_asn_t *: dapp_dec_ind_hdr_asn,     \
      dapp_enc_fb_t *: dapp_dec_ind_hdr_fb,       \
      default: dapp_dec_ind_hdr_plain)(U, V)

#define dapp_dec_ind_msg(T, U, V)                 \
  _Generic((T),                                   \
      dapp_enc_plain_t *: dapp_dec_ind_msg_plain, \
      dapp_enc_asn_t *: dapp_dec_ind_msg_asn,     \
      dapp_enc_fb_t *: dapp_dec_ind_msg_fb,       \
      default: dapp_dec_ind_msg_plain)(U, V)

#define dapp_dec_ctrl_hdr(T, U, V)                 \
  _Generic((T),                                    \
      dapp_enc_plain_t *: dapp_dec_ctrl_hdr_plain, \
      dapp_enc_asn_t *: dapp_dec_ctrl_hdr_asn,     \
      dapp_enc_fb_t *: dapp_dec_ctrl_hdr_fb,       \
      default: dapp_dec_ctrl_hdr_plain)(U, V)

#define dapp_dec_ctrl_msg(T, U, V)                 \
  _Generic((T),                                    \
      dapp_enc_plain_t *: dapp_dec_ctrl_msg_plain, \
      dapp_enc_asn_t *: dapp_dec_ctrl_msg_asn,     \
      dapp_enc_fb_t *: dapp_dec_ctrl_msg_fb,       \
      default: dapp_dec_ctrl_msg_plain)(U, V)

#define dapp_dec_ctrl_out(T, U, V)                 \
  _Generic((T),                                    \
      dapp_enc_plain_t *: dapp_dec_ctrl_out_plain, \
      dapp_enc_asn_t *: dapp_dec_ctrl_out_asn,     \
      dapp_enc_fb_t *: dapp_dec_ctrl_out_fb,       \
      default: dapp_dec_ctrl_out_plain)(U, V)

#define dapp_dec_func_def(T, U, V)                 \
  _Generic((T),                                    \
      dapp_enc_plain_t *: dapp_dec_func_def_plain, \
      dapp_enc_asn_t *: dapp_dec_func_def_asn,     \
      dapp_enc_fb_t *: dapp_dec_func_def_fb,       \
      default: dapp_dec_func_def_plain)(U, V)

#endif
