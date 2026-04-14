#include "dapp_dec_asn.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../util/alg_ds/alg/defer.h"

#include "../../../lib/sm/dec/dec_ue_id.h"
#include "../../../lib/sm/dec/dec_cell_global_id.h"

#include "../ie/asn/E2SM-DAPP-EventTrigger.h"
#include "../ie/asn/E2SM-DAPP-EventTrigger-Format1.h"

#include "../ie/asn/E2SM-DAPP-ActionDefinition.h"
#include "../ie/asn/E2SM-DAPP-ActionDefinition-Format1.h"

#include "../ie/asn/E2SM-DAPP-IndicationHeader.h"
#include "../ie/asn/E2SM-DAPP-IndicationHeader-Format1.h"
#include "../ie/asn/E2SM-DAPP-IndicationHeader-Format2.h"

#include "../ie/asn/E2SM-DAPP-IndicationMessage.h"
#include "../ie/asn/E2SM-DAPP-IndicationMessage-Format1.h"
#include "../ie/asn/E2SM-DAPP-IndicationMessage-Format2.h"

#include "../ie/asn/E2SM-DAPP-ControlHeader.h"
#include "../ie/asn/E2SM-DAPP-ControlHeader-Format1.h"

#include "../ie/asn/E2SM-DAPP-ControlMessage.h"
#include "../ie/asn/E2SM-DAPP-ControlMessage-Format1.h"

#include "../ie/asn/E2SM-DAPP-ControlOutcome.h"
#include "../ie/asn/E2SM-DAPP-ControlOutcome-Format1.h"

#include "../ie/asn/E2SM-DAPP-RANFunctionDefinition.h"

#include "../ie/asn/RANFunctionDefinition-EventTrigger.h"

#include "../ie/asn/RANFunctionDefinition-Report.h"
#include "../ie/asn/RANFunctionDefinition-Report-Item.h"

#include "../ie/asn/RANFunctionDefinition-Control.h"
#include "../ie/asn/RANFunctionDefinition-Control-Item.h"

#include "../ie/asn/DAppE3Subscription-Item.h"
#include "../ie/asn/DAppE3Subscription-List.h"

static inline byte_array_t copy_ostring_to_ba(OCTET_STRING_t os)
{
  byte_array_t ba = {.len = os.size};
  ba.buf = malloc(ba.len);
  assert(ba.buf != NULL && "Memory exhausyed");
  memcpy(ba.buf, os.buf, ba.len);
  return ba;
}

static dapp_e3_subscription_list_t dec_dapp_e3_subscription_list(DAppE3Subscription_List_t const* src)
{
  assert(src != NULL);

  dapp_e3_subscription_list_t dst = {0};

  size_t n = src->list.count;
  assert(n < 256);

  dst.sz_dapp_e3_subscriptions = n;

  if (n == 0) {
    dst.dapp_e3_subscriptions = NULL;
    return dst;
  }

  dst.dapp_e3_subscriptions = calloc(n, sizeof(dapp_e3_subscription_item_t));
  assert(dst.dapp_e3_subscriptions != NULL && "Memory exhausted");

  for (size_t i = 0; i < n; ++i) {
    DAppE3Subscription_Item_t* item = src->list.array[i];
    assert(item != NULL);

    dst.dapp_e3_subscriptions[i].dapp_id = (uint32_t)item->dapp_id;

    size_t nrf = item->subscribed_e3_ran_functions.list.count;
    dst.dapp_e3_subscriptions[i].sz_subscribed_e3_ran_functions = nrf;

    if (nrf > 0) {
      assert(nrf < 64);
      dst.dapp_e3_subscriptions[i].subscribed_e3_ran_functions = calloc(nrf, sizeof(uint32_t));
      assert(dst.dapp_e3_subscriptions[i].subscribed_e3_ran_functions != NULL && "Memory exhausted");

      for (size_t j = 0; j < nrf; ++j) {
        dst.dapp_e3_subscriptions[i].subscribed_e3_ran_functions[j] = (uint32_t)*item->subscribed_e3_ran_functions.list.array[j];
      }
    }
  }

  return dst;
}

static e2sm_dapp_ev_trg_frmt_1_t dec_dapp_ev_trigger_format_1(E2SM_DAPP_EventTrigger_Format1_t const* src)
{
  assert(src != NULL);
  e2sm_dapp_ev_trg_frmt_1_t dst = {};
  return dst;
}

e2sm_dapp_event_trigger_t dapp_dec_event_trigger_asn(size_t len, uint8_t const buf[len])
{
  assert(buf != NULL);
  assert(len != 0);

  E2SM_DAPP_EventTrigger_t src = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_EventTrigger, &src); });
  E2SM_DAPP_EventTrigger_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_DAPP_EventTrigger, (void**)&src_ref, buf, len, 0, 0);
  assert(ret.code == RC_OK);

  e2sm_dapp_event_trigger_t dst = {0};

  if (src.ric_eventTrigger_formats.present == E2SM_DAPP_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format1) {
    dst.format = FORMAT_1_E2SM_DAPP_EV_TRIGGER_FORMAT;
    dst.frmt_1 = dec_dapp_ev_trigger_format_1(src.ric_eventTrigger_formats.choice.eventTrigger_Format1);

  } else {
    assert(0 != 0 && "Unknown format");
  }

  return dst;
}

static e2sm_dapp_action_def_frmt_1_t dec_action_def_frmt_1(E2SM_DAPP_ActionDefinition_Format1_t const* src)
{
  assert(src != NULL);
  e2sm_dapp_action_def_frmt_1_t dst = {};
  return dst;
}

e2sm_dapp_action_def_t dapp_dec_action_def_asn(size_t len, uint8_t const buf[len])
{
  assert(buf != NULL);
  assert(len != 0);

  E2SM_DAPP_ActionDefinition_t src = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ActionDefinition, &src); });
  E2SM_DAPP_ActionDefinition_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_DAPP_ActionDefinition, (void**)&src_ref, buf, len, 0, 0);
  assert(ret.code == RC_OK);

  e2sm_dapp_action_def_t dst = {0};

  dst.ric_style_type = (uint32_t)src.ric_Style_Type;

  if (src.actionDefinition_formats.present == E2SM_DAPP_ActionDefinition__actionDefinition_formats_PR_actionDefinition_Format1) {
    dst.format = FORMAT_1_E2SM_DAPP_ACTION_DEF;
    dst.frmt_1 = dec_action_def_frmt_1(src.actionDefinition_formats.choice.actionDefinition_Format1);
  } else {
    assert(0 != 0 && "Unknown action definition format");
  }

  return dst;
}

static e2sm_dapp_ind_hdr_frmt_2_t dec_ind_hdr_frmt_2(E2SM_DAPP_IndicationHeader_Format2_t const* src)
{
  assert(src != NULL);
  e2sm_dapp_ind_hdr_frmt_2_t dst = {0};

  dst.node_type = (uint8_t)src->node_type;
  dst.node_nb_id = (uint32_t)src->node_nb_id;

  assert(src->node_plmn_id.size == 3);
  memcpy(dst.node_plmn_id, src->node_plmn_id.buf, 3);

  if (src->node_cu_du_id != NULL) {
    dst.node_cu_du_id_present = true;
    dst.node_cu_du_id = (uint64_t)*src->node_cu_du_id;
  } else {
    dst.node_cu_du_id_present = false;
    dst.node_cu_du_id = 0;
  }

  return dst;
}

static e2sm_dapp_ind_hdr_frmt_1_t dec_ind_hdr_frmt_1(E2SM_DAPP_IndicationHeader_Format1_t const* src)
{
  assert(src != NULL);
  e2sm_dapp_ind_hdr_frmt_1_t dst = {0};

  dst.ran_function_id = (uint32_t)src->ran_function_id;
  dst.dapp_id = (uint32_t)src->dapp_id;

  dst.node_type = (uint8_t)src->node_type;
  dst.node_nb_id = (uint32_t)src->node_nb_id;

  assert(src->node_plmn_id.size == 3);
  memcpy(dst.node_plmn_id, src->node_plmn_id.buf, 3);

  if (src->node_cu_du_id != NULL) {
    dst.node_cu_du_id_present = true;
    dst.node_cu_du_id = (uint64_t)*src->node_cu_du_id;
  } else {
    dst.node_cu_du_id_present = false;
    dst.node_cu_du_id = 0;
  }

  return dst;
}

e2sm_dapp_ind_hdr_t dapp_dec_ind_hdr_asn(size_t len, uint8_t const ind_hdr[len])
{
  assert(ind_hdr != NULL);
  assert(len != 0);

  E2SM_DAPP_IndicationHeader_t src = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_IndicationHeader, &src); });
  E2SM_DAPP_IndicationHeader_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_DAPP_IndicationHeader, (void**)&src_ref, ind_hdr, len, 0, 0);
  assert(ret.code == RC_OK);

  e2sm_dapp_ind_hdr_t dst = {0};

  if (src.ric_indicationHeader_formats.present
      == E2SM_DAPP_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format1) {
    dst.format = FORMAT_1_E2SM_DAPP_IND_HDR;
    dst.frmt_1 = dec_ind_hdr_frmt_1(src.ric_indicationHeader_formats.choice.indicationHeader_Format1);
  } else if (src.ric_indicationHeader_formats.present
             == E2SM_DAPP_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format2) {
    dst.format = FORMAT_2_E2SM_DAPP_IND_HDR;
    dst.frmt_2 = dec_ind_hdr_frmt_2(src.ric_indicationHeader_formats.choice.indicationHeader_Format2);
  } else {
    assert(0 != 0 && "Unknown format");
  }

  return dst;
}

static e2sm_dapp_ind_msg_frmt_2_t dec_ind_msg_frmt_2(const E2SM_DAPP_IndicationMessage_Format2_t* src)
{
  assert(src != NULL);
  e2sm_dapp_ind_msg_frmt_2_t dst = {0};

  dst.dapp_e3_subs = dec_dapp_e3_subscription_list(&src->dappE3Subscriptions);

  return dst;
}

static e2sm_dapp_ind_msg_frmt_1_t dec_ind_msg_frmt_1(const E2SM_DAPP_IndicationMessage_Format1_t* src)
{
  assert(src != NULL);
  e2sm_dapp_ind_msg_frmt_1_t dst = {0};
  dst.data_size = src->data.size;

  if (dst.data_size > 0) {
    assert(src->data.buf != NULL);

    dst.data = malloc(dst.data_size);
    assert(dst.data != NULL);

    memcpy(dst.data, src->data.buf, dst.data_size);
  } else {
    dst.data = NULL;
  }

  return dst;
}

e2sm_dapp_ind_msg_t dapp_dec_ind_msg_asn(size_t len, uint8_t const ind_msg[len])
{
  assert(ind_msg != NULL);
  assert(len != 0);

  E2SM_DAPP_IndicationMessage_t src = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_IndicationMessage, &src); });
  E2SM_DAPP_IndicationMessage_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_DAPP_IndicationMessage, (void**)&src_ref, ind_msg, len, 0, 0);
  assert(ret.code == RC_OK);

  e2sm_dapp_ind_msg_t dst = {0};

  if (src.ric_indicationMessage_formats.present
      == E2SM_DAPP_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format1) {
    dst.format = FORMAT_1_E2SM_DAPP_IND_MSG;
    dst.frmt_1 = dec_ind_msg_frmt_1(src.ric_indicationMessage_formats.choice.indicationMessage_Format1);
  } else if (src.ric_indicationMessage_formats.present
             == E2SM_DAPP_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format2) {
    dst.format = FORMAT_2_E2SM_DAPP_IND_MSG;
    dst.frmt_2 = dec_ind_msg_frmt_2(src.ric_indicationMessage_formats.choice.indicationMessage_Format2);
  } else {
    assert(0 != 0 && "Unknown format type");
  }

  return dst;
}

static e2sm_dapp_ctrl_hdr_frmt_1_t dec_ctrl_hdr_frmt_1(E2SM_DAPP_ControlHeader_Format1_t const* src)
{
  assert(src != NULL);
  e2sm_dapp_ctrl_hdr_frmt_1_t dst = {0};

  dst.ran_function_id = (uint32_t)src->ran_function_id;
  dst.dapp_id = (uint32_t)src->dapp_id;

  return dst;
}

e2sm_dapp_ctrl_hdr_t dapp_dec_ctrl_hdr_asn(size_t len, uint8_t const ctrl_hdr[len])
{
  assert(ctrl_hdr != NULL);

  E2SM_DAPP_ControlHeader_t src = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ControlHeader, &src); });
  E2SM_DAPP_ControlHeader_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_DAPP_ControlHeader, (void**)&src_ref, ctrl_hdr, len, 0, 0);
  assert(ret.code == RC_OK);

  e2sm_dapp_ctrl_hdr_t dst = {0};

  if (src.ric_controlHeader_formats.present == E2SM_DAPP_ControlHeader__ric_controlHeader_formats_PR_controlHeader_Format1) {
    dst.format = FORMAT_1_E2SM_DAPP_CTRL_HDR;
    dst.frmt_1 = dec_ctrl_hdr_frmt_1(src.ric_controlHeader_formats.choice.controlHeader_Format1);
  } else {
    assert(0 != 0 && "Unknown format type");
  }

  return dst;
}

static e2sm_dapp_ctrl_msg_frmt_1_t dec_ctrl_msg_frmt_1(E2SM_DAPP_ControlMessage_Format1_t const* src)
{
  assert(src != NULL);

  e2sm_dapp_ctrl_msg_frmt_1_t dst = {0};

  dst.data_size = src->data.size;

  if (dst.data_size > 0) {
    assert(src->data.buf != NULL);

    dst.data = malloc(dst.data_size);
    assert(dst.data != NULL);

    memcpy(dst.data, src->data.buf, dst.data_size);
  } else {
    dst.data = NULL;
  }

  return dst;
}

e2sm_dapp_ctrl_msg_t dapp_dec_ctrl_msg_asn(size_t len, uint8_t const ctrl_msg[len])
{
  assert(ctrl_msg != NULL);
  assert(len > 0);

  E2SM_DAPP_ControlMessage_t src = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ControlMessage, &src); });
  E2SM_DAPP_ControlMessage_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_DAPP_ControlMessage, (void**)&src_ref, ctrl_msg, len, 0, 0);
  assert(ret.code == RC_OK);

  e2sm_dapp_ctrl_msg_t dst = {0};

  if (src.ric_controlMessage_formats.present == E2SM_DAPP_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format1) {
    dst.format = FORMAT_1_E2SM_DAPP_CTRL_MSG;
    dst.frmt_1 = dec_ctrl_msg_frmt_1(src.ric_controlMessage_formats.choice.controlMessage_Format1);
  } else {
    assert(0 && "Unknown format");
  }

  return dst;
}

static e2sm_dapp_ctrl_out_frmt_1_t dec_ctrl_out_frmt_1(E2SM_DAPP_ControlOutcome_Format1_t const* src)
{
  assert(src != NULL);
  e2sm_dapp_ctrl_out_frmt_1_t dst = {};
  return dst;
}

e2sm_dapp_ctrl_out_t dapp_dec_ctrl_out_asn(size_t len, uint8_t const ctrl_out[len])
{
  assert(ctrl_out != NULL);
  assert(len > 0);

  E2SM_DAPP_ControlOutcome_t src = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ControlOutcome, &src); });
  E2SM_DAPP_ControlOutcome_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_DAPP_ControlOutcome, (void**)&src_ref, ctrl_out, len, 0, 0);
  assert(ret.code == RC_OK);

  e2sm_dapp_ctrl_out_t dst = {0};
  if (src.ric_controlOutcome_formats.present == E2SM_DAPP_ControlOutcome__ric_controlOutcome_formats_PR_controlOutcome_Format1) {
    dst.format = FORMAT_1_E2SM_DAPP_CTRL_OUT;
    dst.frmt_1 = dec_ctrl_out_frmt_1(src.ric_controlOutcome_formats.choice.controlOutcome_Format1);
  } else {
    assert(0 != 0 && "Unknown format");
  }

  return dst;
}

static ran_function_name_t dec_ran_func_name(RANfunction_Name_t const* src)
{
  assert(src != NULL);

  ran_function_name_t dst = {0};

  dst.name = copy_ostring_to_ba(src->ranFunction_ShortName);

  dst.oid = copy_ostring_to_ba(src->ranFunction_E2SM_OID);

  dst.description = copy_ostring_to_ba(src->ranFunction_Description);

  return dst;
}

static ran_func_def_ev_trig_dapp_sm_t dec_ran_fun_def_ev_trg(RANFunctionDefinition_EventTrigger_t const* src)
{
  assert(src != NULL);
  ran_func_def_ev_trig_dapp_sm_t dst = {};
  return dst;
}

static ran_func_def_report_dapp_sm_t dec_ran_func_def_report(RANFunctionDefinition_Report_t const* src)
{
  assert(src != NULL);

  ran_func_def_report_dapp_sm_t dst = {0};

  size_t n = src->ric_ReportStyle_List.list.count;
  dst.sz_seq_report_sty = n;

  if (n == 0) {
    dst.seq_report_sty = NULL;
    return dst;
  }

  dst.seq_report_sty = calloc(n, sizeof(seq_report_sty_dapp_sm_t));
  assert(dst.seq_report_sty != NULL && "Memory exhausted");

  for (size_t i = 0; i < n; ++i) {
    RANFunctionDefinition_Report_Item_t* item = src->ric_ReportStyle_List.list.array[i];
    assert(item != NULL);

    seq_report_sty_dapp_sm_t* out = &dst.seq_report_sty[i];

    out->report_type = item->ric_ReportStyle_Type;

    out->name = copy_ostring_to_ba(item->ric_ReportStyle_Name);

    out->ind_hdr_type = item->ric_IndicationHeaderFormat_Type;

    out->ind_msg_type = item->ric_IndicationMessageFormat_Type;

    if (item->dappE3Subscriptions != NULL) {
      out->dapp_e3_subs = calloc(1, sizeof(dapp_e3_subscription_list_t));
      assert(out->dapp_e3_subs != NULL && "Memory exhausted");
      *out->dapp_e3_subs = dec_dapp_e3_subscription_list(item->dappE3Subscriptions);
    }
  }

  return dst;
}

static ran_func_def_ctrl_dapp_sm_t dec_ran_func_def_ctrl(RANFunctionDefinition_Control_t const* src)
{
  assert(src != NULL);

  ran_func_def_ctrl_dapp_sm_t dst = {0};

  size_t n = src->ric_ControlStyle_List.list.count;
  dst.sz_seq_ctrl_style = n;

  if (n == 0) {
    dst.seq_ctrl_style = NULL;
    return dst;
  }

  dst.seq_ctrl_style = calloc(n, sizeof(seq_ctrl_style_dapp_sm_t));
  assert(dst.seq_ctrl_style != NULL && "Memory exhausted");

  for (size_t i = 0; i < n; ++i) {
    RANFunctionDefinition_Control_Item_t* item = src->ric_ControlStyle_List.list.array[i];
    assert(item != NULL);

    seq_ctrl_style_dapp_sm_t* out = &dst.seq_ctrl_style[i];

    out->style_type = item->ric_ControlStyle_Type;

    out->name = copy_ostring_to_ba(item->ric_ControlStyle_Name);

    out->hdr = item->ric_ControlHeaderFormat_Type;

    out->msg = item->ric_ControlMessageFormat_Type;

    out->out_frmt = item->ric_ControlOutcomeFormat_Type;

    if (item->dappE3Subscriptions != NULL) {
      out->dapp_e3_subs = calloc(1, sizeof(dapp_e3_subscription_list_t));
      assert(out->dapp_e3_subs != NULL && "Memory exhausted");
      *out->dapp_e3_subs = dec_dapp_e3_subscription_list(item->dappE3Subscriptions);
    }
  }

  return dst;
}

e2sm_dapp_func_def_t dapp_dec_func_def_asn(size_t len, uint8_t const func_def[len])
{
  assert(func_def != NULL);
  assert(len > 0);

  E2SM_DAPP_RANFunctionDefinition_t src = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_RANFunctionDefinition, &src); });
  E2SM_DAPP_RANFunctionDefinition_t* src_ref = &src;

  asn_dec_rval_t const ret = aper_decode(NULL, &asn_DEF_E2SM_DAPP_RANFunctionDefinition, (void**)&src_ref, func_def, len, 0, 0);
  assert(ret.code == RC_OK);

  e2sm_dapp_func_def_t dst = {0};

  dst.name = dec_ran_func_name(&src.ranFunction_Name);

  if (src.ranFunctionDefinition_EventTrigger != NULL) {
    dst.ev_trig = calloc(1, sizeof(ran_func_def_ev_trig_dapp_sm_t));
    assert(dst.ev_trig != NULL && "Memory exhausted");
    *dst.ev_trig = dec_ran_fun_def_ev_trg(src.ranFunctionDefinition_EventTrigger);
  }

  if (src.ranFunctionDefinition_Report != NULL) {
    dst.report = calloc(1, sizeof(ran_func_def_report_dapp_sm_t));
    assert(dst.report != NULL && "Memory exhausted");
    *dst.report = dec_ran_func_def_report(src.ranFunctionDefinition_Report);
  }

  if (src.ranFunctionDefinition_Control != NULL) {
    dst.ctrl = calloc(1, sizeof(ran_func_def_ctrl_dapp_sm_t));
    assert(dst.ctrl != NULL && "Memory exhausted");
    *dst.ctrl = dec_ran_func_def_ctrl(src.ranFunctionDefinition_Control);
  }

  return dst;
}
