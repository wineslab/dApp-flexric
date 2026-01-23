#include "seq_ctrl_style.h"

#include <assert.h>

void free_seq_ctrl_style_dapp_sm(seq_ctrl_style_dapp_sm_t* src)
{
  assert(src != NULL);

  if (src->name.buf != NULL) {
    free(src->name.buf);
    src->name.buf = NULL;
    src->name.len = 0;
  }

}

bool eq_seq_ctrl_style_dapp_sm(seq_ctrl_style_dapp_sm_t const* m0, seq_ctrl_style_dapp_sm_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->style_type != m1->style_type)
    return false;

  if (m0->name.len != m1->name.len)
    return false;

  if (m0->name.len > 0) {
    assert(m0->name.buf != NULL);
    assert(m1->name.buf != NULL);
    if (memcmp(m0->name.buf, m1->name.buf, m0->name.len) != 0)
      return false;
  }

  if (m0->hdr != m1->hdr)
    return false;

  if (m0->msg != m1->msg)
    return false;

  if (m0->out_frmt != m1->out_frmt)
    return false;

  return true;
}

seq_ctrl_style_dapp_sm_t cp_seq_ctrl_style_dapp_sm(seq_ctrl_style_dapp_sm_t const* src)
{
  assert(src != NULL);

  seq_ctrl_style_dapp_sm_t dst = {0};

  dst.style_type = src->style_type;

  dst.name.len = src->name.len;
  if (src->name.len > 0) {
    assert(src->name.buf != NULL);
    dst.name.buf = malloc(src->name.len);
    assert(dst.name.buf != NULL && "Memory exhausted while copying name");
    memcpy(dst.name.buf, src->name.buf, src->name.len);
  } else {
    dst.name.buf = NULL;
  }

  dst.hdr = src->hdr;

  dst.msg = src->msg;

  dst.out_frmt = src->out_frmt;

  return dst;
}
