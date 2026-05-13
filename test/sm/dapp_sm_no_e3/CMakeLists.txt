if(SM_ENCODING_DAPP STREQUAL "ASN")
  add_executable(test_dapp_sm_no_e3
                      main.c
                      $<TARGET_OBJECTS:dapp_sm_agent_no_e3_obj>
                      ../../rnd/fill_rnd_data_dapp.c
                      ../../../src/util/time_now_us.c
                      ../../../src/util/alg_ds/alg/defer.c
                      )

  target_compile_definitions(test_dapp_sm_no_e3 PUBLIC ${SM_ENCODING_DAPP})
  target_link_libraries(test_dapp_sm_no_e3 PUBLIC dapp_sm_static e2sm_dapp_e3_spectrum_asn1_obj -pthread -lm)

  enable_testing()
  add_test(Unit_test_DAPP_no_E3 test_dapp_sm_no_e3)
endif()
