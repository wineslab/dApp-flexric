#include "ran_func_def_ev_trig.h"

#include <assert.h>
#include <stdlib.h>

void free_ran_func_def_ev_trig_dapp_sm(ran_func_def_ev_trig_dapp_sm_t* src)
{
  assert(src != NULL);

  assert(src->sz_seq_ev_trg_style > 0 && src->sz_seq_ev_trg_style < 64);
  for (size_t i = 0; i < src->sz_seq_ev_trg_style; ++i) {
    free_seq_ev_trg_style_dapp_sm(&src->seq_ev_trg_style[i]);
  }
  free(src->seq_ev_trg_style);

}

bool eq_ran_func_def_ev_trig_dapp_sm(ran_func_def_ev_trig_dapp_sm_t const* m0, ran_func_def_ev_trig_dapp_sm_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  assert(m0->sz_seq_ev_trg_style > 0 && m0->sz_seq_ev_trg_style < 64);
  assert(m1->sz_seq_ev_trg_style > 0 && m1->sz_seq_ev_trg_style < 64);
  if (m0->sz_seq_ev_trg_style != m1->sz_seq_ev_trg_style) {
    assert(0 != 0);
    return false;
  }

  for (size_t i = 0; i < m0->sz_seq_ev_trg_style; ++i) {
    if (eq_seq_ev_trg_style_dapp_sm(&m0->seq_ev_trg_style[i], &m1->seq_ev_trg_style[i]) == false) {
      assert(0 != 0);
      return false;
    }
  }

  return true;
}

ran_func_def_ev_trig_dapp_sm_t cp_ran_func_def_ev_trig_dapp_sm(ran_func_def_ev_trig_dapp_sm_t const* src)
{
  assert(src != NULL);
  ran_func_def_ev_trig_dapp_sm_t dst = {0};

  assert(src->sz_seq_ev_trg_style > 0 && src->sz_seq_ev_trg_style < 64);
  dst.sz_seq_ev_trg_style = src->sz_seq_ev_trg_style;
  dst.seq_ev_trg_style = calloc(dst.sz_seq_ev_trg_style, sizeof(seq_ev_trg_style_dapp_sm_t));
  assert(dst.seq_ev_trg_style != NULL && "memory exhausted");

  for (size_t i = 0; i < src->sz_seq_ev_trg_style; ++i) {
    dst.seq_ev_trg_style[i] = cp_seq_ev_trg_style_dapp_sm(&src->seq_ev_trg_style[i]);
  }

  return dst;
}
