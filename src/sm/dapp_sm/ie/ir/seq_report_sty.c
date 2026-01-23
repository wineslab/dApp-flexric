#include "seq_report_sty.h"

#include <assert.h>

void free_seq_report_sty_dapp_sm(seq_report_sty_dapp_sm_t* src)
{
  assert(src != NULL);
  assert(src->name.len > 0 && src->name.len < 151);
  free_byte_array(src->name);

}

seq_report_sty_dapp_sm_t cp_seq_report_sty_dapp_sm(seq_report_sty_dapp_sm_t const* src)
{
  assert(src != NULL);
  seq_report_sty_dapp_sm_t dst = {0};

  dst.report_type = src->report_type;

  assert(src->name.len > 0 && src->name.len < 151);
  dst.name = copy_byte_array(src->name);

  dst.ev_trig_type = src->ev_trig_type;

  dst.act_frmt_type = src->act_frmt_type;

  dst.ind_hdr_type = src->ind_hdr_type;

  dst.ind_msg_type = src->ind_msg_type;

  return dst;
}

bool eq_seq_report_sty_dapp_sm(seq_report_sty_dapp_sm_t const* m0, seq_report_sty_dapp_sm_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->report_type != m1->report_type)
    return false;

  assert(m0->name.len > 0 && m0->name.len < 151);
  assert(m1->name.len > 0 && m1->name.len < 151);
  if (eq_byte_array(&m0->name, &m1->name) == false)
    return false;

  if (m0->ev_trig_type != m1->ev_trig_type)
    return false;

  if (m0->act_frmt_type != m1->act_frmt_type)
    return false;

  if (m0->ind_hdr_type != m1->ind_hdr_type)
    return false;

  if (m0->ind_msg_type != m1->ind_msg_type)
    return false;

  return true;
}
