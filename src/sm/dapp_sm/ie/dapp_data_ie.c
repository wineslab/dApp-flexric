#include "dapp_data_ie.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

void free_e2sm_dapp_event_trigger(e2sm_dapp_event_trigger_t* src)
{
  assert(src != NULL);

  if (src->format == FORMAT_0_E2SM_DAPP_EV_TRIGGER_FORMAT) {
    free_e2sm_dapp_ev_trg_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Not implemented");
  }
}

bool eq_e2sm_dapp_event_trigger(e2sm_dapp_event_trigger_t const* m0, e2sm_dapp_event_trigger_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->format == FORMAT_0_E2SM_DAPP_EV_TRIGGER_FORMAT) {
    return eq_e2sm_dapp_ev_trg_frmt_0(&m0->frmt_0, &m1->frmt_0);

  } else {
    assert(0 != 0 && "Not implemented");
  }

  assert(0 != 0 && "Impossible path");
  return false;
}

e2sm_dapp_event_trigger_t cp_e2sm_dapp_event_trigger(e2sm_dapp_event_trigger_t const* src)
{
  assert(src != NULL);

  e2sm_dapp_event_trigger_t dst = {0};
  dst.format = src->format;

  if (src->format == FORMAT_0_E2SM_DAPP_EV_TRIGGER_FORMAT) {
    dst.frmt_0 = cp_e2sm_dapp_ev_trg_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Not implemented");
  }

  return dst;
}

//////////////////////////////////////
// RIC Action Definition
/////////////////////////////////////

void free_e2sm_dapp_action_def(e2sm_dapp_action_def_t* src)
{
  assert(src != NULL);

  if (src->format == FORMAT_0_E2SM_DAPP_ACT_DEF) {
    free_e2sm_dapp_act_def_frmt_0(&src->frmt_0);

  } else {
    assert("Unknown format");
  }
}

e2sm_dapp_action_def_t cp_e2sm_dapp_action_def(e2sm_dapp_action_def_t const* src)
{
  assert(src != NULL);

  e2sm_dapp_action_def_t dst = {0};

  dst.ric_style_type = src->ric_style_type;

  dst.format = src->format;
  if (dst.format == FORMAT_0_E2SM_DAPP_ACT_DEF) {
    dst.frmt_0 = cp_e2sm_dapp_act_def_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format");
  }

  return dst;
}

bool eq_e2sm_dapp_action_def(e2sm_dapp_action_def_t* m0, e2sm_dapp_action_def_t* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->ric_style_type != m1->ric_style_type)
    return false;

  if (m0->format != m1->format)
    return false;

  if (m0->format == FORMAT_0_E2SM_DAPP_ACT_DEF) {
    return eq_e2sm_dapp_act_def_frmt_0(&m0->frmt_0, &m1->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format type");
  }

  assert(0 != 0 && "Impossible path");
  return true;
}

//////////////////////////////////////
// RIC Indication Header
/////////////////////////////////////

void free_e2sm_dapp_ind_hdr(e2sm_dapp_ind_hdr_t* src)
{
  assert(src != NULL);

  if (src->format == FORMAT_0_E2SM_DAPP_IND_HDR) {
    free_e2sm_dapp_ind_hdr_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown type");
  }
}

e2sm_dapp_ind_hdr_t cp_e2sm_dapp_ind_hdr(e2sm_dapp_ind_hdr_t const* src)
{
  assert(src != NULL);
  e2sm_dapp_ind_hdr_t dst = {.format = src->format};

  if (src->format == FORMAT_0_E2SM_DAPP_IND_HDR) {
    dst.frmt_0 = cp_e2sm_dapp_ind_hdr_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown type");
  }

  return dst;
}

bool eq_e2sm_dapp_ind_hdr(e2sm_dapp_ind_hdr_t const* m0, e2sm_dapp_ind_hdr_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->format != m1->format)
    return false;

  if (m0->format == FORMAT_0_E2SM_DAPP_IND_HDR) {
    return eq_e2sm_dapp_ind_hdr_frmt_0(&m0->frmt_0, &m1->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format");
  }

  assert(0 != 0 && "Not implemented");

  return true;
}

//////////////////////////////////////
// RIC Indication Message
/////////////////////////////////////

void free_e2sm_dapp_ind_msg(e2sm_dapp_ind_msg_t* src)
{
  assert(src != NULL);

  if (src->format == FORMAT_0_E2SM_DAPP_IND_MSG) {
    free_e2sm_dapp_ind_msg_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format");
  }
}

e2sm_dapp_ind_msg_t cp_e2sm_dapp_ind_msg(e2sm_dapp_ind_msg_t const* src)
{
  assert(src != NULL);

  e2sm_dapp_ind_msg_t dst = {.format = src->format};

  if (src->format == FORMAT_0_E2SM_DAPP_IND_MSG) {
    dst.frmt_0 = cp_e2sm_dapp_ind_msg_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format");
  }

  return dst;
}

bool eq_e2sm_dapp_ind_msg(e2sm_dapp_ind_msg_t const* m0, e2sm_dapp_ind_msg_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->format != m1->format)
    return false;

  if (m0->format == FORMAT_0_E2SM_DAPP_IND_MSG) {
    return eq_e2sm_dapp_ind_msg_frmt_0(&m0->frmt_0, &m1->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format");
  }

  assert(0 != 0 && "Impossible path");

  return true;
}

//////////////////////////////////////
// RIC Control Header
/////////////////////////////////////

void free_e2sm_dapp_ctrl_hdr(e2sm_dapp_ctrl_hdr_t* src)
{
  assert(src != NULL);
  if (src->format == FORMAT_0_E2SM_DAPP_CTRL_HDR) {
    free_e2sm_dapp_ctrl_hdr_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown type");
  }
}

e2sm_dapp_ctrl_hdr_t cp_e2sm_dapp_ctrl_hdr(e2sm_dapp_ctrl_hdr_t const* src)
{
  assert(src != NULL);
  e2sm_dapp_ctrl_hdr_t dst = {.format = src->format};

  if (dst.format == FORMAT_0_E2SM_DAPP_CTRL_HDR) {
    dst.frmt_0 = cp_e2sm_dapp_ctrl_hdr_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format type");
  }

  return dst;
}

bool eq_e2sm_dapp_ctrl_hdr(e2sm_dapp_ctrl_hdr_t const* m0, e2sm_dapp_ctrl_hdr_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->format != m1->format)
    return false;

  if (m0->format == FORMAT_0_E2SM_DAPP_CTRL_HDR) {
    if (eq_e2sm_dapp_ctrl_hdr_frmt_0(&m0->frmt_0, &m1->frmt_0) == false)
      return false;

  } else {
    assert(0 != 0 && "Unknown type");
  }

  return true;
}

//////////////////////////////////////
// RIC Control Message
/////////////////////////////////////

void free_e2sm_dapp_ctrl_msg(e2sm_dapp_ctrl_msg_t* src)
{
  assert(src != NULL);

  if (src->format == FORMAT_0_E2SM_DAPP_CTRL_MSG) {
    free_e2sm_dapp_ctrl_msg_frmt_0(&src->frmt_0);

  } else {
    assert(0 && "Unknown format");
  }
}

e2sm_dapp_ctrl_msg_t cp_e2sm_dapp_ctrl_msg(e2sm_dapp_ctrl_msg_t const* src)
{
  assert(src != NULL);

  e2sm_dapp_ctrl_msg_t dst = {.format = src->format};

  if (src->format == FORMAT_0_E2SM_DAPP_CTRL_MSG) {
    dst.frmt_0 = cp_e2sm_dapp_ctrl_msg_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format");
  }

  return dst;
  ;
}

bool eq_e2sm_dapp_ctrl_msg(e2sm_dapp_ctrl_msg_t const* m0, e2sm_dapp_ctrl_msg_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->format != m1->format)
    return false;

  if (m0->format == FORMAT_0_E2SM_DAPP_CTRL_MSG) {
    if (eq_e2sm_dapp_ctrl_msg_frmt_0(&m0->frmt_0, &m1->frmt_0) == false)
      return false;

  } else {
    assert(0 && "Unknown format");
  }

  return true;
}

//////////////////////////////////////
// RIC Control Outcome
/////////////////////////////////////

void free_e2sm_dapp_ctrl_out(e2sm_dapp_ctrl_out_t* src)
{
  assert(src != NULL);

  if (src->format == FORMAT_0_E2SM_DAPP_CTRL_OUT) {
    free_e2sm_dapp_ctrl_out_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format");
  }
}

e2sm_dapp_ctrl_out_t cp_e2sm_dapp_ctrl_out(e2sm_dapp_ctrl_out_t const* src)
{
  assert(src != NULL);

  e2sm_dapp_ctrl_out_t dst = {.format = src->format};

  if (dst.format == FORMAT_0_E2SM_DAPP_CTRL_OUT) {
    dst.frmt_0 = cp_e2sm_dapp_ctrl_out_frmt_0(&src->frmt_0);

  } else {
    assert(0 != 0 && "Unknown format");
  }

  return dst;
}

bool eq_e2sm_dapp_ctrl_out(e2sm_dapp_ctrl_out_t const* m0, e2sm_dapp_ctrl_out_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (m0->format != m1->format)
    return false;

  if (m0->format == FORMAT_0_E2SM_DAPP_CTRL_OUT) {
    if (eq_e2sm_dapp_ctrl_out_frmt_0(&m0->frmt_0, &m1->frmt_0) == false)
      return false;

  } else {
    assert(0 != 0 && "Unknown format");
  }

  return true;
}

//////////////////////////////////////
// RAN Function Definition
/////////////////////////////////////

void free_e2sm_dapp_func_def(e2sm_dapp_func_def_t* src)
{
  assert(src != NULL);
  //  RAN Function Name
  free_ran_function_name(&src->name);

  // RAN Function Definition for EVENT TRIGGER
  if (src->ev_trig != NULL) {
    free_ran_func_def_ev_trig_dapp_sm(src->ev_trig);
    free(src->ev_trig);
  }

  // RAN Function Definition for REPORT
  if (src->report != NULL) {
    free_ran_func_def_report_dapp_sm(src->report);
    free(src->report);
  }

  // RAN Function Definition for CONTROL
  if (src->ctrl != NULL) {
    free_ran_func_def_ctrl_dapp_sm(src->ctrl);
    free(src->ctrl);
  }
}

e2sm_dapp_func_def_t cp_e2sm_dapp_func_def(e2sm_dapp_func_def_t const* src)
{
  assert(src != NULL);

  e2sm_dapp_func_def_t dst = {0};

  //  RAN Function Name
  dst.name = cp_ran_function_name(&src->name);

  // RAN Function Definition for EVENT TRIGGER
  if (src->ev_trig != NULL) {
    dst.ev_trig = calloc(1, sizeof(ran_func_def_ev_trig_dapp_sm_t));
    assert(dst.ev_trig != NULL && "Memory exhausted");
    *dst.ev_trig = cp_ran_func_def_ev_trig_dapp_sm(src->ev_trig);
  }

  // RAN Function Definition for REPORT
  if (src->report != NULL) {
    dst.report = calloc(1, sizeof(ran_func_def_report_dapp_sm_t));
    assert(dst.report != NULL && "Memory exhausted");
    *dst.report = cp_ran_func_def_report_dapp_sm(src->report);
  }

  // RAN Function Definition for CONTROL
  if (src->ctrl != NULL) {
    dst.ctrl = calloc(1, sizeof(ran_func_def_ctrl_dapp_sm_t));
    assert(dst.ctrl != NULL && "Memory exhausted");
    *dst.ctrl = cp_ran_func_def_ctrl_dapp_sm(src->ctrl);
  }

  return dst;
}

bool eq_e2sm_dapp_func_def(e2sm_dapp_func_def_t const* m0, e2sm_dapp_func_def_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  //  RAN Function Name
  if (eq_ran_function_name(&m0->name, &m1->name) == false)
    return false;

  // RAN Function Definition for EVENT TRIGGER
  if (eq_ran_func_def_ev_trig_dapp_sm(m0->ev_trig, m1->ev_trig) == false)
    return false;

  // RAN Function Definition for REPORT
  if (eq_ran_func_def_report_dapp_sm(m0->report, m1->report) == false)
    return false;

  // RAN Function Definition for CONTROL
  if (eq_ran_func_def_ctrl_dapp_sm(m0->ctrl, m1->ctrl) == false)
    return false;

  return true;
}

///////////////
/// RIC Subscription
///////////////

void free_dapp_sub_data(dapp_sub_data_t* src)
{
  assert(src != NULL);

  free_e2sm_dapp_event_trigger(&src->et);

  assert(src->sz_ad > 0 && src->sz_ad < 17);
  for (size_t i = 0; i < src->sz_ad; ++i) {
    free_e2sm_dapp_action_def(&src->ad[i]);
  }
  free(src->ad);
}

bool eq_dapp_sub_data(dapp_sub_data_t const* m0, dapp_sub_data_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (eq_e2sm_dapp_event_trigger(&m0->et, &m1->et) == false)
    return false;

  assert(m0->sz_ad > 0 && m0->sz_ad < 17);
  assert(m1->sz_ad > 0 && m1->sz_ad < 17);
  if (m0->sz_ad != m1->sz_ad)
    return false;

  for (size_t i = 0; i < m0->sz_ad; ++i) {
    if (eq_e2sm_dapp_action_def(&m0->ad[i], &m1->ad[i]) == false) {
      assert(0 != 0 && "debug");
      return false;
    }
  }

  return true;
}

dapp_sub_data_t cp_dapp_sub_data(dapp_sub_data_t const* src)
{
  assert(src != NULL);
  dapp_sub_data_t dst = {0};

  dst.et = cp_e2sm_dapp_event_trigger(&src->et);

  assert(src->sz_ad > 0 && src->sz_ad < 17);
  assert(src->sz_ad == 1 && "Only one supported");
  dst.sz_ad = src->sz_ad;

  dst.ad = calloc(dst.sz_ad, sizeof(e2sm_dapp_action_def_t));
  assert(dst.ad != NULL && "Memory exhausted");

  for (size_t i = 0; i < dst.sz_ad; ++i) {
    dst.ad[i] = cp_e2sm_dapp_action_def(&src->ad[i]);
  }

  return dst;
}

///////////////
// RIC Indication
///////////////

void free_dapp_ind_data(dapp_ind_data_t* ind)
{
  assert(ind != NULL);

  free_e2sm_dapp_ind_hdr(&ind->hdr);
  free_e2sm_dapp_ind_msg(&ind->msg);

  switch (ind->e3.type) {
    case DAPP_E3_SM_SPECTRUM:
      free_spectrum_sm_report(&ind->e3.u.spectrum);
      break;
    case DAPP_E3_SM_NONE:
    default:
      break;
  }

  ind->e3.type = DAPP_E3_SM_NONE;
}

bool eq_dapp_ind_data(dapp_ind_data_t const* m0, dapp_ind_data_t const* m1)
{
  if (m0 == m1)
    return true;

  if (m0 == NULL || m1 == NULL)
    return false;

  if (eq_e2sm_dapp_ind_hdr(&m0->hdr, &m1->hdr) == false) {
    assert(0 != 0 && "Debug hdr");
    return false;
  }

  if (eq_e2sm_dapp_ind_msg(&m0->msg, &m1->msg) == false) {
    assert(0 != 0 && "Debug msg");
    return false;
  }

  if (m0->e3.type != m1->e3.type)
    return false;

  switch (m0->e3.type) {
    case DAPP_E3_SM_NONE:
      break;

    case DAPP_E3_SM_SPECTRUM:
      if (!eq_spectrum_sm_report(&m0->e3.u.spectrum, &m1->e3.u.spectrum)) {
        assert(0 != 0 && "Debug spectrum payload");
        return false;
      }
      break;

    default:
      assert(0 != 0 && "Unknown DAPP E3 SM type");
      return false;
  }


  return true;
}

dapp_ind_data_t cp_dapp_ind_data(dapp_ind_data_t const* src)
{
  assert(src != NULL);
  dapp_ind_data_t dst = {0};

  dst.hdr = cp_e2sm_dapp_ind_hdr(&src->hdr);
  dst.msg = cp_e2sm_dapp_ind_msg(&src->msg);

  dst.e3.type = src->e3.type;
  switch (src->e3.type) {
    case DAPP_E3_SM_SPECTRUM:
      dst.e3.u.spectrum = cp_spectrum_sm_report(&src->e3.u.spectrum);
      break;

    case DAPP_E3_SM_NONE:
    default:
      break;
  }

  return dst;
}

///////////////
// RIC Control
///////////////

void free_dapp_ctrl_req_data(dapp_ctrl_req_data_t* src)
{
  assert(src != NULL);

  free_e2sm_dapp_ctrl_hdr(&src->hdr);
  free_e2sm_dapp_ctrl_msg(&src->msg);

  switch (src->e3.type) {
    case DAPP_E3_SM_SPECTRUM:
      free_spectrum_sm_control(&src->e3.u.spectrum);
      break;

    case DAPP_E3_SM_NONE:
    default:
      break;
  }

  src->e3.type = DAPP_E3_SM_NONE;
}

bool eq_dapp_ctrl_req_data(dapp_ctrl_req_data_t const* m0, dapp_ctrl_req_data_t const* m1)
{
  if (m0 == m1)
    return true;

  if (!m0 || !m1)
    return false;

  if (!eq_e2sm_dapp_ctrl_hdr(&m0->hdr, &m1->hdr))
    return false;

  if (!eq_e2sm_dapp_ctrl_msg(&m0->msg, &m1->msg))
    return false;

  if (m0->e3.type != m1->e3.type)
    return false;

  switch (m0->e3.type) {
    case DAPP_E3_SM_NONE:
      return true;

    case DAPP_E3_SM_SPECTRUM:
      return eq_spectrum_sm_control(&m0->e3.u.spectrum, &m1->e3.u.spectrum);

    default:
      assert(0 != 0 && "Unknown DAPP E3 SM type");
      return false;
  }
}

dapp_ctrl_req_data_t cp_dapp_ctrl_req_data(dapp_ctrl_req_data_t const* src)
{
  assert(src != NULL);
  dapp_ctrl_req_data_t dst = {0};

  dst.hdr = cp_e2sm_dapp_ctrl_hdr(&src->hdr);
  dst.msg = cp_e2sm_dapp_ctrl_msg(&src->msg);

  dst.e3.type = src->e3.type;
  switch (src->e3.type) {
    case DAPP_E3_SM_SPECTRUM:
      dst.e3.u.spectrum = cp_spectrum_sm_control(&src->e3.u.spectrum);
      break;

    case DAPP_E3_SM_NONE:
    default:
      break;
  }

  assert(eq_dapp_ctrl_req_data(src, &dst) == true);
  return dst;
}

//////////////////////////////////////
// DAPP E3 Indication Payload
/////////////////////////////////////

void free_dapp_e3_ind_payload(dapp_e3_ind_payload_t* src)
{
  assert(src != NULL);

  switch (src->type) {
    case DAPP_E3_SM_SPECTRUM:
      free_spectrum_sm_report(&src->u.spectrum);
      break;

    case DAPP_E3_SM_NONE:
    default:
      break;
  }
}

dapp_e3_ind_payload_t cp_dapp_e3_ind_payload(dapp_e3_ind_payload_t const* src)
{
  assert(src != NULL);
  dapp_e3_ind_payload_t dst = {0};
  
  dst.type = src->type;
  
  switch (src->type) {
    case DAPP_E3_SM_SPECTRUM:
      dst.u.spectrum = cp_spectrum_sm_report(&src->u.spectrum);
      break;

    case DAPP_E3_SM_NONE:
    default:
      break;
  }
  
  return dst;
}

bool eq_dapp_e3_ind_payload(dapp_e3_ind_payload_t const* m0, dapp_e3_ind_payload_t const* m1)
{
  if (m0 == m1)
    return true;
  
  if (m0 == NULL || m1 == NULL)
    return false;
  
  if (m0->type != m1->type)
    return false;
  
  switch (m0->type) {
    case DAPP_E3_SM_NONE:
      break;

    case DAPP_E3_SM_SPECTRUM:
      if (!eq_spectrum_sm_report(&m0->u.spectrum, &m1->u.spectrum))
        return false;
      break;

    default:
      assert(0 != 0 && "Unknown DAPP E3 SM type");
      return false;
  }
  
  return true;
}

//////////////////////////////////////
// DAPP E3 Control Payload
/////////////////////////////////////

void free_dapp_e3_ctrl_payload(dapp_e3_ctrl_payload_t* src)
{
  assert(src != NULL);

  switch (src->type) {
    case DAPP_E3_SM_SPECTRUM:
      free_spectrum_sm_control(&src->u.spectrum);
      break;

    case DAPP_E3_SM_NONE:
    default:
      break;
  }
}

dapp_e3_ctrl_payload_t cp_dapp_e3_ctrl_payload(dapp_e3_ctrl_payload_t const* src)
{
  assert(src != NULL);
  dapp_e3_ctrl_payload_t dst = {0};
  
  dst.type = src->type;
  
  switch (src->type) {
    case DAPP_E3_SM_SPECTRUM:
      dst.u.spectrum = cp_spectrum_sm_control(&src->u.spectrum);
      break;

    case DAPP_E3_SM_NONE:
    default:
      break;
  }
  
  return dst;
}

bool eq_dapp_e3_ctrl_payload(dapp_e3_ctrl_payload_t const* m0, dapp_e3_ctrl_payload_t const* m1)
{
  if (m0 == m1)
    return true;
  
  if (m0 == NULL || m1 == NULL)
    return false;
  
  if (m0->type != m1->type)
    return false;
  
  switch (m0->type) {
    case DAPP_E3_SM_NONE:
      break;

    case DAPP_E3_SM_SPECTRUM:
      if (!eq_spectrum_sm_control(&m0->u.spectrum, &m1->u.spectrum))
        return false;
      break;

    default:
      assert(0 != 0 && "Unknown DAPP E3 SM type");
      return false;
  }
  
  return true;
}