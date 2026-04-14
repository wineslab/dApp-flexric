# ASN.1 source file
set(ASN1_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/e2sm_dapp_v0_standard.asn)

# Output directory
set(ASN1C_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Run ASN.1 code generation at configuration time
execute_process(
  COMMAND /opt/asn1c/bin/asn1c
    -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-JER
    -fcompound-names -no-gen-example -findirect-choice -fno-include-deps
    -D ${ASN1C_OUTPUT_DIR}
    ${ASN1_SOURCE}
  RESULT_VARIABLE ASN1C_RESULT
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_QUIET
  ERROR_QUIET
)

# Fail if ASN.1 generation failed
if(NOT ASN1C_RESULT EQUAL 0)
  message(FATAL_ERROR "ASN.1 code generation failed with exit code ${ASN1C_RESULT}")
endif()

file(GLOB ASN_DAPP_SRC
  ${ASN1C_OUTPUT_DIR}/ANY_aper.c
  ${ASN1C_OUTPUT_DIR}/ANY.c
  ${ASN1C_OUTPUT_DIR}/ANY_xer.c
  ${ASN1C_OUTPUT_DIR}/aper_decoder.c
  ${ASN1C_OUTPUT_DIR}/aper_encoder.c
  ${ASN1C_OUTPUT_DIR}/aper_opentype.c
  ${ASN1C_OUTPUT_DIR}/aper_support.c
  ${ASN1C_OUTPUT_DIR}/asn_application.c
  ${ASN1C_OUTPUT_DIR}/asn_bit_data.c
  ${ASN1C_OUTPUT_DIR}/asn_codecs_prim.c
  ${ASN1C_OUTPUT_DIR}/asn_codecs_prim_xer.c
  ${ASN1C_OUTPUT_DIR}/asn_internal.c
  ${ASN1C_OUTPUT_DIR}/asn_random_fill.c
  ${ASN1C_OUTPUT_DIR}/asn_SEQUENCE_OF.c
  ${ASN1C_OUTPUT_DIR}/asn_SET_OF.c
  ${ASN1C_OUTPUT_DIR}/ber_tlv_length.c
  ${ASN1C_OUTPUT_DIR}/ber_tlv_tag.c
  ${ASN1C_OUTPUT_DIR}/BIT_STRING.c
  ${ASN1C_OUTPUT_DIR}/BIT_STRING_print.c
  ${ASN1C_OUTPUT_DIR}/BIT_STRING_rfill.c
  ${ASN1C_OUTPUT_DIR}/BIT_STRING_xer.c
  ${ASN1C_OUTPUT_DIR}/BOOLEAN_aper.c
  ${ASN1C_OUTPUT_DIR}/BOOLEAN_print.c
  ${ASN1C_OUTPUT_DIR}/BOOLEAN_rfill.c
  ${ASN1C_OUTPUT_DIR}/BOOLEAN_xer.c
  ${ASN1C_OUTPUT_DIR}/BOOLEAN.c
  ${ASN1C_OUTPUT_DIR}/constraints.c
  ${ASN1C_OUTPUT_DIR}/constr_CHOICE_aper.c
  ${ASN1C_OUTPUT_DIR}/constr_CHOICE.c
  ${ASN1C_OUTPUT_DIR}/constr_CHOICE_print.c
  ${ASN1C_OUTPUT_DIR}/constr_CHOICE_rfill.c
  ${ASN1C_OUTPUT_DIR}/constr_CHOICE_xer.c
  ${ASN1C_OUTPUT_DIR}/constr_SEQUENCE_aper.c
  ${ASN1C_OUTPUT_DIR}/constr_SEQUENCE.c
  ${ASN1C_OUTPUT_DIR}/constr_SEQUENCE_OF_aper.c
  ${ASN1C_OUTPUT_DIR}/constr_SEQUENCE_OF.c
  ${ASN1C_OUTPUT_DIR}/constr_SEQUENCE_OF_xer.c
  ${ASN1C_OUTPUT_DIR}/constr_SEQUENCE_print.c
  ${ASN1C_OUTPUT_DIR}/constr_SEQUENCE_rfill.c
  ${ASN1C_OUTPUT_DIR}/constr_SEQUENCE_xer.c
  ${ASN1C_OUTPUT_DIR}/constr_SET_OF_aper.c
  ${ASN1C_OUTPUT_DIR}/constr_SET_OF.c
  ${ASN1C_OUTPUT_DIR}/constr_SET_OF_print.c
  ${ASN1C_OUTPUT_DIR}/constr_SET_OF_rfill.c
  ${ASN1C_OUTPUT_DIR}/constr_SET_OF_xer.c
  ${ASN1C_OUTPUT_DIR}/constr_TYPE.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-ControlHeader.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-ControlHeader-Format1.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-ControlMessage.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-ControlMessage-Format1.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-ControlOutcome.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-ControlOutcome-Format1.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-EventTrigger.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-EventTrigger-Format1.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-ActionDefinition.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-ActionDefinition-Format1.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-IndicationHeader.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-IndicationHeader-Format1.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-IndicationHeader-Format2.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-IndicationMessage.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-IndicationMessage-Format1.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-IndicationMessage-Format2.c
  ${ASN1C_OUTPUT_DIR}/E2SM-DAPP-RANFunctionDefinition.c
  ${ASN1C_OUTPUT_DIR}/EXTERNAL.c
  ${ASN1C_OUTPUT_DIR}/GraphicString.c
  ${ASN1C_OUTPUT_DIR}/INTEGER_aper.c
  ${ASN1C_OUTPUT_DIR}/INTEGER.c
  ${ASN1C_OUTPUT_DIR}/INTEGER_print.c
  ${ASN1C_OUTPUT_DIR}/INTEGER_rfill.c
  ${ASN1C_OUTPUT_DIR}/INTEGER_xer.c
  ${ASN1C_OUTPUT_DIR}/NativeInteger_aper.c
  ${ASN1C_OUTPUT_DIR}/NativeInteger.c
  ${ASN1C_OUTPUT_DIR}/NativeInteger_print.c
  ${ASN1C_OUTPUT_DIR}/NativeInteger_rfill.c
  ${ASN1C_OUTPUT_DIR}/NativeInteger_xer.c
  ${ASN1C_OUTPUT_DIR}/ObjectDescriptor.c
  ${ASN1C_OUTPUT_DIR}/OBJECT_IDENTIFIER.c
  ${ASN1C_OUTPUT_DIR}/OBJECT_IDENTIFIER_print.c
  ${ASN1C_OUTPUT_DIR}/OBJECT_IDENTIFIER_rfill.c
  ${ASN1C_OUTPUT_DIR}/OBJECT_IDENTIFIER_xer.c
  ${ASN1C_OUTPUT_DIR}/OCTET_STRING_aper.c
  ${ASN1C_OUTPUT_DIR}/OCTET_STRING.c
  ${ASN1C_OUTPUT_DIR}/OCTET_STRING_print.c
  ${ASN1C_OUTPUT_DIR}/OCTET_STRING_rfill.c
  ${ASN1C_OUTPUT_DIR}/OCTET_STRING_xer.c
  ${ASN1C_OUTPUT_DIR}/OPEN_TYPE_aper.c
  ${ASN1C_OUTPUT_DIR}/OPEN_TYPE.c
  ${ASN1C_OUTPUT_DIR}/OPEN_TYPE_xer.c
  ${ASN1C_OUTPUT_DIR}/per_decoder.c
  ${ASN1C_OUTPUT_DIR}/per_encoder.c
  ${ASN1C_OUTPUT_DIR}/per_opentype.c
  ${ASN1C_OUTPUT_DIR}/per_support.c
  ${ASN1C_OUTPUT_DIR}/PrintableString.c
  ${ASN1C_OUTPUT_DIR}/RANFunctionDefinition-Control.c
  ${ASN1C_OUTPUT_DIR}/RANFunctionDefinition-Control-Item.c
  ${ASN1C_OUTPUT_DIR}/RANFunctionDefinition-EventTrigger.c
  ${ASN1C_OUTPUT_DIR}/RANFunctionDefinition-Report.c
  ${ASN1C_OUTPUT_DIR}/RANFunctionDefinition-Report-Item.c
  ${ASN1C_OUTPUT_DIR}/DAppE3Subscription-Item.c
  ${ASN1C_OUTPUT_DIR}/DAppE3Subscription-List.c
  ${ASN1C_OUTPUT_DIR}/SubscribedE3RANFunction-ID.c
  ${ASN1C_OUTPUT_DIR}/RANfunction-Name.c
  ${ASN1C_OUTPUT_DIR}/RIC-Format-Type.c
  ${ASN1C_OUTPUT_DIR}/RIC-Style-Name.c
  ${ASN1C_OUTPUT_DIR}/RIC-Style-Type.c
  ${ASN1C_OUTPUT_DIR}/xer_decoder.c
  ${ASN1C_OUTPUT_DIR}/xer_encoder.c
  ${ASN1C_OUTPUT_DIR}/xer_support.c
)

add_library(e2sm_dapp_asn1_obj OBJECT ${ASN_DAPP_SRC})

target_include_directories(e2sm_dapp_asn1_obj PUBLIC ${ASN1C_OUTPUT_DIR})

target_compile_options(e2sm_dapp_asn1_obj PUBLIC "-DASN_DISABLE_OER_SUPPORT")
target_compile_options(e2sm_dapp_asn1_obj PUBLIC "-DASN_DISABLE_JER_SUPPORT")
target_compile_options(e2sm_dapp_asn1_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fPIC -fvisibility=hidden)
