#include "decoder.h"

#include "defs/compiled_output/Spectrum-PRBBlacklistReport.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

bool spectrum_sm_dec_report(const uint8_t* buf, size_t len, spectrum_sm_report_t* out)
{
  assert(out != NULL);

  if (buf == NULL || len == 0)
    return false;

  Spectrum_PRBBlacklistReport_t asn;
  memset(&asn, 0, sizeof(asn));

  Spectrum_PRBBlacklistReport_t* asn_ref = &asn;

  // Decode APER-encoded Spectrum-Report
  asn_dec_rval_t ret = aper_decode(NULL, &asn_DEF_Spectrum_PRBBlacklistReport,
                                  (void**)&asn_ref, buf, len, 0, 0);
  if (ret.code != RC_OK) {
    ASN_STRUCT_RESET(asn_DEF_Spectrum_PRBBlacklistReport, &asn);
    return false;
  }

  out->prb_count = 0;
  out->prbs = NULL;

  const int n = asn.blacklistedPRBs.list.count;
  if (n < 0 || n > 273) {
    ASN_STRUCT_RESET(asn_DEF_Spectrum_PRBBlacklistReport, &asn);
    return false;
  }

  out->prb_count = (uint32_t)n;

  if (out->prb_count == 0) {
    ASN_STRUCT_RESET(asn_DEF_Spectrum_PRBBlacklistReport, &asn);
    return true;
  }

  out->prbs = (uint16_t*)malloc((size_t)out->prb_count * sizeof(uint16_t));
  assert(out->prbs != NULL && "Memory exhausted in spectrum_sm_dec_report");

  for (int i = 0; i < n; ++i) {
    if (asn.blacklistedPRBs.list.array[i] == NULL) {
      out->prbs[i] = 0;
      continue;
    }

    long v = *(asn.blacklistedPRBs.list.array[i]);

    if (v < 0 || v > 272) {
      ASN_STRUCT_RESET(asn_DEF_Spectrum_PRBBlacklistReport, &asn);
      free(out->prbs);
      out->prbs = NULL;
      out->prb_count = 0;
      return false;
    }

    out->prbs[i] = (uint16_t)v;
  }

  ASN_STRUCT_RESET(asn_DEF_Spectrum_PRBBlacklistReport, &asn);
  return true;
}
