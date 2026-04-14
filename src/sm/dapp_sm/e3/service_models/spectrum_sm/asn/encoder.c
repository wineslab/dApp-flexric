#include "encoder.h"

#include "defs/compiled_output/Spectrum-PRBBlockedControl.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "asn_application.h"
#include "per_encoder.h"

bool spectrum_sm_enc_control(const spectrum_sm_control_t* ctrl, uint8_t** out_buf, size_t* out_size)
{
  assert(out_buf != NULL);
  assert(out_size != NULL);

  *out_buf = NULL;
  *out_size = 0;

  if (ctrl == NULL)
    return false;

  if (ctrl->prb_count < 0 || ctrl->prb_count > 273)
    return false;

  Spectrum_PRBBlockedControl_t asn;
  memset(&asn, 0, sizeof(asn));

  for (long i = 0; i < ctrl->prb_count; ++i) {
    const uint16_t v = ctrl->blockedPRBs[i];

    if (v > 272) {
      ASN_STRUCT_RESET(asn_DEF_Spectrum_PRBBlockedControl, &asn);
      return false;
    }

    PRB_Index_t* elem = (PRB_Index_t*)calloc(1, sizeof(*elem));
    assert(elem != NULL && "Memory exhausted in spectrum_sm_enc_control");

    *elem = (PRB_Index_t)v;

    if (ASN_SEQUENCE_ADD(&asn.blockedPRBs.list, elem) != 0) {
      free(elem);
      ASN_STRUCT_RESET(asn_DEF_Spectrum_PRBBlockedControl, &asn);
      return false;
    }
  }

  uint8_t tmp[2048];
  asn_enc_rval_t er = aper_encode_to_buffer(&asn_DEF_Spectrum_PRBBlockedControl, NULL, &asn, tmp, sizeof(tmp));

  if (er.encoded <= 0) {
    ASN_STRUCT_RESET(asn_DEF_Spectrum_PRBBlockedControl, &asn);
    return false;
  }

  const size_t encoded_bytes = (size_t)((er.encoded + 7) / 8);
  uint8_t* out = (uint8_t*)malloc(encoded_bytes);
  assert(out != NULL && "Memory exhausted in spectrum_sm_enc_control memcpy");

  memcpy(out, tmp, encoded_bytes);

  *out_buf = out;
  *out_size = encoded_bytes;

  ASN_STRUCT_RESET(asn_DEF_Spectrum_PRBBlockedControl, &asn);
  return true;
}