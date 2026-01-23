#include "dapp_enc_asn.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../lib/sm/enc/enc_cell_global_id.h"
#include "../../../lib/sm/enc/enc_ue_id.h"

#include "../../../util/alg_ds/alg/defer.h"
#include "../../../../util/byte_array.h"

#include "../ie/asn/E2SM-DAPP-EventTrigger.h"
#include "../ie/asn/E2SM-DAPP-EventTrigger-Format0.h"

#include "../ie/asn/E2SM-DAPP-ActionDefinition.h"
#include "../ie/asn/E2SM-DAPP-ActionDefinition-Format0.h"

#include "../ie/asn/E2SM-DAPP-IndicationHeader.h"
#include "../ie/asn/E2SM-DAPP-IndicationHeader-Format0.h"

#include "../ie/asn/E2SM-DAPP-IndicationMessage.h"
#include "../ie/asn/E2SM-DAPP-IndicationMessage-Format0.h"

#include "../ie/asn/E2SM-DAPP-ControlHeader.h"
#include "../ie/asn/E2SM-DAPP-ControlHeader-Format0.h"

#include "../ie/asn/E2SM-DAPP-ControlMessage.h"
#include "../ie/asn/E2SM-DAPP-ControlMessage-Format0.h"

#include "../ie/asn/E2SM-DAPP-ControlOutcome.h"
#include "../ie/asn/E2SM-DAPP-ControlOutcome-Format0.h"

#include "../ie/asn/E2SM-DAPP-RANFunctionDefinition.h"

#include "../ie/asn/RANFunctionDefinition-EventTrigger.h"

#include "../ie/asn/RANFunctionDefinition-Report.h"
#include "../ie/asn/RANFunctionDefinition-Report-Item.h"

#include "../ie/asn/RANFunctionDefinition-Control.h"
#include "../ie/asn/RANFunctionDefinition-Control-Item.h"

static inline OCTET_STRING_t copy_ba_to_ostring(byte_array_t ba)
{
  OCTET_STRING_t os = {.size = ba.len};
  os.buf = malloc(ba.len);
  memcpy(os.buf, ba.buf, ba.len);
  return os;
}

static E2SM_DAPP_EventTrigger_Format0_t* cp_dapp_ev_trigger_format_0(e2sm_dapp_ev_trg_frmt_0_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_EventTrigger_Format0_t* dst = calloc(1, sizeof(E2SM_DAPP_EventTrigger_Format0_t));
  assert(dst != NULL && "Memory exhausted");

  return dst;
}

byte_array_t dapp_enc_event_trigger_asn(e2sm_dapp_event_trigger_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_EventTrigger_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_EventTrigger, &dst); });

  if (src->format == FORMAT_0_E2SM_DAPP_EV_TRIGGER_FORMAT) {
    dst.ric_eventTrigger_formats.present = E2SM_DAPP_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format0;
    dst.ric_eventTrigger_formats.choice.eventTrigger_Format0 = cp_dapp_ev_trigger_format_0(&src->frmt_0);
  } else {
    assert(0 != 0 && "Unknown format");
  }

  byte_array_t ba = {.buf = malloc(512 * 1024), .len = 512 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_EventTrigger, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_ActionDefinition_Format0_t* cp_act_def_frmt_0(e2sm_dapp_act_def_frmt_0_t const* src)
{
  assert(src != NULL);
  E2SM_DAPP_ActionDefinition_Format0_t* dst = calloc(1, sizeof(E2SM_DAPP_ActionDefinition_Format0_t));
  assert(dst != NULL);
  return dst;
}

byte_array_t dapp_enc_action_def_asn(e2sm_dapp_action_def_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ActionDefinition_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ActionDefinition, &dst); });

  dst.ric_Style_Type = src->ric_style_type;

  if (src->format == FORMAT_0_E2SM_DAPP_ACT_DEF) {
    dst.ric_actionDefinition_formats.present = E2SM_DAPP_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format0;
    dst.ric_actionDefinition_formats.choice.actionDefinition_Format0 = cp_act_def_frmt_0(&src->frmt_0);
  } else {
    assert(0 != 0 && "not implemented");
  }

  byte_array_t ba = {.buf = malloc(512 * 1024), .len = 512 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_ActionDefinition, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_IndicationHeader_Format0_t* cp_ind_hdr_frmt_0(e2sm_dapp_ind_hdr_frmt_0_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_IndicationHeader_Format0_t* dst = calloc(1, sizeof(E2SM_DAPP_IndicationHeader_Format0_t));
  assert(dst != NULL && "Memory exhausted");

  dst->ran_function_id = (long)src->ran_function_id;
  dst->dapp_id = (long)src->dapp_id;

  return dst;
}

byte_array_t dapp_enc_ind_hdr_asn(e2sm_dapp_ind_hdr_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_IndicationHeader_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_IndicationHeader, &dst); });

  if (src->format == FORMAT_0_E2SM_DAPP_IND_HDR) {
    dst.ric_indicationHeader_formats.present = E2SM_DAPP_IndicationHeader__ric_indicationHeader_formats_PR_indicationHeader_Format0;
    dst.ric_indicationHeader_formats.choice.indicationHeader_Format0 = cp_ind_hdr_frmt_0(&src->frmt_0);
  } else {
    assert(0 != 0 && "unknown format type");
  }

  byte_array_t ba = {.buf = malloc(1024), .len = 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_IndicationHeader, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_IndicationMessage_Format0_t* enc_ind_msg_frmt_0(const e2sm_dapp_ind_msg_frmt_0_t* src)
{
  assert(src != NULL);
  assert(src->data_size > 0);
  assert(src->data != NULL);

  E2SM_DAPP_IndicationMessage_Format0_t* dst = CALLOC(1, sizeof(*dst));
  assert(dst != NULL && "Memory exhausted");

  dst->data_size = (long)src->data_size;

  int ret = OCTET_STRING_fromBuf(&dst->data, (const char*)src->data, src->data_size);
  assert(ret == 0 && "OCTET_STRING_fromBuf failed");

  return dst;
}

byte_array_t dapp_enc_ind_msg_asn(e2sm_dapp_ind_msg_t const* src)
{
  assert(src != NULL);
  E2SM_DAPP_IndicationMessage_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_IndicationMessage, &dst); });

  if (src->format == FORMAT_0_E2SM_DAPP_IND_MSG) {
    dst.ric_indicationMessage_formats.present =
        E2SM_DAPP_IndicationMessage__ric_indicationMessage_formats_PR_indicationMessage_Format0;
    dst.ric_indicationMessage_formats.choice.indicationMessage_Format0 = enc_ind_msg_frmt_0(&src->frmt_0);
  } else {
    assert(0 != 0 && "Unknown format type");
  }

  byte_array_t ba = {.buf = malloc(128 * 1024), .len = 128 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_IndicationMessage, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_ControlHeader_Format0_t* enc_ctrl_hdr_frmt_0(e2sm_dapp_ctrl_hdr_frmt_0_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlHeader_Format0_t* dst = calloc(1, sizeof(E2SM_DAPP_ControlHeader_Format0_t));
  assert(dst != NULL && "Memory exhausted");

  dst->ran_function_id = (long)src->ran_function_id;
  dst->dapp_id = (long)src->dapp_id;

  return dst;
}

byte_array_t dapp_enc_ctrl_hdr_asn(e2sm_dapp_ctrl_hdr_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlHeader_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ControlHeader, &dst); });

  if (src->format == FORMAT_0_E2SM_DAPP_CTRL_HDR) {
    dst.ric_controlHeader_formats.present = E2SM_DAPP_ControlHeader__ric_controlHeader_formats_PR_controlHeader_Format0;
    dst.ric_controlHeader_formats.choice.controlHeader_Format0 = enc_ctrl_hdr_frmt_0(&src->frmt_0);
  } else {
    assert(0 != 0 && "Unknown format");
  }

  byte_array_t ba = {.buf = malloc(16 * 1024), .len = 16 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_ControlHeader, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_ControlMessage_Format0_t* enc_ctrl_msg_frmt_0(e2sm_dapp_ctrl_msg_frmt_0_t const* src)
{
  assert(src != NULL);
  assert(src->data_size > 0);
  assert(src->data != NULL);

  E2SM_DAPP_ControlMessage_Format0_t* dst = CALLOC(1, sizeof(*dst));
  assert(dst != NULL && "Memory exhausted");

  dst->data_size = (long)src->data_size;

  int ret = OCTET_STRING_fromBuf(&dst->data, (const char*)src->data, src->data_size);
  assert(ret == 0 && "OCTET_STRING_fromBuf failed");

  return dst;
}

byte_array_t dapp_enc_ctrl_msg_asn(e2sm_dapp_ctrl_msg_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlMessage_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ControlMessage, &dst); });

  if (src->format == FORMAT_0_E2SM_DAPP_CTRL_MSG) {
    dst.ric_controlMessage_formats.present = E2SM_DAPP_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format0;

    dst.ric_controlMessage_formats.choice.controlMessage_Format0 = calloc(1, sizeof(E2SM_DAPP_ControlMessage_Format0_t));
    assert(dst.ric_controlMessage_formats.choice.controlMessage_Format0 != NULL && "Memory exhausted");

    dst.ric_controlMessage_formats.choice.controlMessage_Format0 = enc_ctrl_msg_frmt_0(&src->frmt_0);
  } else {
    assert(0 != 0 && "Unknown format type");
  }

  byte_array_t ba = {.buf = malloc(16 * 1024), .len = 16 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_ControlMessage, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static E2SM_DAPP_ControlOutcome_Format0_t* enc_ctrl_out_frmt_0(e2sm_dapp_ctrl_out_frmt_0_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlOutcome_Format0_t* dst = calloc(1, sizeof(E2SM_DAPP_ControlOutcome_Format0_t));
  assert(dst != NULL && "Memory exhausted");

  return dst;
}

byte_array_t dapp_enc_ctrl_out_asn(e2sm_dapp_ctrl_out_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_ControlOutcome_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_ControlOutcome, &dst); });

  if (src->format == FORMAT_0_E2SM_DAPP_CTRL_OUT) {
    dst.ric_controlOutcome_formats.present = E2SM_DAPP_ControlOutcome__ric_controlOutcome_formats_PR_controlOutcome_Format0;
    dst.ric_controlOutcome_formats.choice.controlOutcome_Format0 = enc_ctrl_out_frmt_0(&src->frmt_0);
  } else {
    assert(0 != 0 && "Unknown format");
  }

  byte_array_t ba = {.buf = malloc(16 * 1024), .len = 16 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_ControlOutcome, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}

static RANfunction_Name_t enc_ran_func_name(ran_function_name_t const* src)
{
  assert(src != NULL);

  RANfunction_Name_t dst = {0};

  dst.ranFunction_ShortName = copy_ba_to_ostring(src->name);

  dst.ranFunction_E2SM_OID = copy_ba_to_ostring(src->oid);

  dst.ranFunction_Description = copy_ba_to_ostring(src->description);

  assert(src->instance == NULL && "not implemented");

  return dst;
}

static RANFunctionDefinition_EventTrigger_t enc_ran_func_def_ev_trg(ran_func_def_ev_trig_dapp_sm_t const* src)
{
  assert(src != NULL);
  RANFunctionDefinition_EventTrigger_t dst = {0};
  return dst;
}

static RANFunctionDefinition_Report_t enc_ran_func_def_report(ran_func_def_report_dapp_sm_t const* src)
{
  assert(src != NULL);

  RANFunctionDefinition_Report_t dst = {0};

  for (size_t i = 0; i < src->sz_seq_report_sty; ++i) {
    const seq_report_sty_dapp_sm_t* ir = &src->seq_report_sty[i];

    RANFunctionDefinition_Report_Item_t* item = CALLOC(1, sizeof(*item));
    assert(item != NULL && "Memory exhausted");

    item->ric_ReportStyle_Type = ir->report_type;

    item->ric_ReportStyle_Name = copy_ba_to_ostring(ir->name);

    item->ric_SupportedEventTriggerStyle_Type = ir->ev_trig_type;

    item->ric_ReportActionFormat_Type = ir->act_frmt_type;

    item->ric_IndicationHeaderFormat_Type = ir->ind_hdr_type;

    item->ric_IndicationMessageFormat_Type = ir->ind_msg_type;

    int rc = ASN_SEQUENCE_ADD(&dst.ric_ReportStyle_List.list, item);
    assert(rc == 0 && "ASN_SEQUENCE_ADD failed for ReportStyle_List");
  }

  return dst;
}

static RANFunctionDefinition_Control_t enc_ran_func_def_ctrl(ran_func_def_ctrl_dapp_sm_t const* src)
{
  assert(src != NULL);

  RANFunctionDefinition_Control_t dst = {0};

  for (size_t i = 0; i < src->sz_seq_ctrl_style; ++i) {
    const seq_ctrl_style_dapp_sm_t* ir = &src->seq_ctrl_style[i];

    RANFunctionDefinition_Control_Item_t* item = CALLOC(1, sizeof(*item));
    assert(item != NULL && "Memory exhausted");

    item->ric_ControlStyle_Type = ir->style_type;

    item->ric_ControlStyle_Name = copy_ba_to_ostring(ir->name);

    item->ric_ControlHeaderFormat_Type = ir->hdr;

    item->ric_ControlMessageFormat_Type = ir->msg;

    item->ric_ControlOutcomeFormat_Type = ir->out_frmt;

    int rc = ASN_SEQUENCE_ADD(&dst.ric_ControlStyle_List.list, item);
    assert(rc == 0 && "ASN_SEQUENCE_ADD failed for ControlStyle_List");
  }

  return dst;
}

byte_array_t dapp_enc_func_def_asn(e2sm_dapp_func_def_t const* src)
{
  assert(src != NULL);

  E2SM_DAPP_RANFunctionDefinition_t dst = {0};
  defer({ ASN_STRUCT_RESET(asn_DEF_E2SM_DAPP_RANFunctionDefinition, &dst); });

  dst.ranFunction_Name = enc_ran_func_name(&src->name);

  if (src->ev_trig != NULL) {
    dst.ranFunctionDefinition_EventTrigger = calloc(1, sizeof(RANFunctionDefinition_EventTrigger_t));
    assert(dst.ranFunctionDefinition_EventTrigger != NULL && "Memory exhausted");
    *dst.ranFunctionDefinition_EventTrigger = enc_ran_func_def_ev_trg(src->ev_trig);
  }

  if (src->report != NULL) {
    dst.ranFunctionDefinition_Report = calloc(1, sizeof(RANFunctionDefinition_Report_t));
    assert(dst.ranFunctionDefinition_Report != NULL && "Memory exhausted");
    *dst.ranFunctionDefinition_Report = enc_ran_func_def_report(src->report);
  }

  if (src->ctrl != NULL) {
    dst.ranFunctionDefinition_Control = calloc(1, sizeof(RANFunctionDefinition_Control_t));
    assert(dst.ranFunctionDefinition_Control != NULL && "Memory exhausted");
    *dst.ranFunctionDefinition_Control = enc_ran_func_def_ctrl(src->ctrl);
  }

  byte_array_t ba = {.buf = malloc(16 * 1024), .len = 16 * 1024};
  const enum asn_transfer_syntax syntax = ATS_ALIGNED_BASIC_PER;
  asn_enc_rval_t er = asn_encode_to_buffer(NULL, syntax, &asn_DEF_E2SM_DAPP_RANFunctionDefinition, &dst, ba.buf, ba.len);
  assert(er.encoded > -1 && (size_t)er.encoded <= ba.len);
  ba.len = er.encoded;

  return ba;
}
