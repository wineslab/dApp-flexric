set(ASN1_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/e3sm_spectrum.asn)

set(ASN1C_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/compiled_output)

file(MAKE_DIRECTORY ${ASN1C_OUTPUT_DIR})

execute_process(
  COMMAND /opt/asn1c/bin/asn1c -pdu=all -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-JER -fno-include-deps -fcompound-names -findirect-choice -no-gen-example -D ${ASN1C_OUTPUT_DIR} ${ASN1_SOURCE}
  RESULT_VARIABLE ASN1C_RESULT
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_QUIET
  ERROR_QUIET
)

if(NOT ASN1C_RESULT EQUAL 0)
  message(FATAL_ERROR "ASN.1 code generation failed with exit code ${ASN1C_RESULT}")
endif()

file(GLOB ASN_DAPP_XAPP_SRC
  ${ASN1C_OUTPUT_DIR}/Spectrum-PRBBlacklistReport.c
  ${ASN1C_OUTPUT_DIR}/Spectrum-PRBWhitelistControl.c
  ${ASN1C_OUTPUT_DIR}/PRB-Index.c
)

add_library(e2sm_dapp_e3_spectrum_asn1_obj STATIC ${ASN_DAPP_XAPP_SRC})

target_include_directories(e2sm_dapp_e3_spectrum_asn1_obj PUBLIC ${ASN1C_OUTPUT_DIR})

target_compile_options(e2sm_dapp_e3_spectrum_asn1_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(e2sm_dapp_e3_spectrum_asn1_obj PUBLIC "-DASN_DISABLE_JER_SUPPORT")
target_compile_options(e2sm_dapp_e3_spectrum_asn1_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC -fvisibility=hidden)
