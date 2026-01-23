#include "seq_ins_ind.h"

#include <assert.h>
#include <stdlib.h>

void free_seq_ins_ind_dapp_sm(seq_ins_ind_dapp_sm_t* src)
{
  assert(src != NULL);

  assert(src->id > 0);

  assert(src->name.len > 0 && src->name.len < 151);
  free_byte_array(src->name);
}

bool eq_seq_ins_ind_dapp_sm(seq_ins_ind_dapp_sm_t const* m0, seq_ins_ind_dapp_sm_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  assert(m0->id > 0);
  assert(m1->id > 0);
  if (m0->id != m1->id)
    return false;

  assert(m0->name.len > 0 && m0->name.len < 151);
  assert(m1->name.len > 0 && m1->name.len < 151);
  if (eq_byte_array(&m0->name, &m1->name) == false)
    return false;

  return true;
}

seq_ins_ind_dapp_sm_t cp_seq_ins_ind_dapp_sm(seq_ins_ind_dapp_sm_t const* src)
{
  assert(src != NULL);
  seq_ins_ind_dapp_sm_t dst = {0};

  assert(src->id > 0);
  dst.id = src->id;

  assert(src->name.len > 0 && src->name.len < 151);
  dst.name = copy_byte_array(src->name);

  return dst;
}
