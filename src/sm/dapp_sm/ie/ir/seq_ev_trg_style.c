
#include "seq_ev_trg_style.h"

#include <assert.h>
#include <stdlib.h>

void free_seq_ev_trg_style_dapp_sm(seq_ev_trg_style_dapp_sm_t* src)
{
  assert(src != NULL);
  assert(src->name.len > 0 && src->name.len < 151);
  free_byte_array(src->name);
}

bool eq_seq_ev_trg_style_dapp_sm(seq_ev_trg_style_dapp_sm_t const* m0, seq_ev_trg_style_dapp_sm_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->style != m1->style)
    return false;

  assert(m0->name.len > 0 && m0->name.len < 151);
  assert(m1->name.len > 0 && m1->name.len < 151);

  if (eq_byte_array(&m0->name, &m1->name) == false)
    return false;

  if (m0->format != m1->format)
    return false;

  return true;
}

seq_ev_trg_style_dapp_sm_t cp_seq_ev_trg_style_dapp_sm(seq_ev_trg_style_dapp_sm_t const* src)
{
  assert(src != NULL);
  seq_ev_trg_style_dapp_sm_t dst = {0};

  dst.style = src->style;

  assert(src->name.len > 0 && src->name.len < 151);
  dst.name = copy_byte_array(src->name);

  dst.format = src->format;

  return dst;
}
