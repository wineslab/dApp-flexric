cmake_minimum_required(VERSION 3.15) # setting this is required
project(dapp_sm)            # this sets the project name

set(SM_ENCODING_DAPP_SRC
  ../sm_proc_data.c 
  dapp_sm_agent.c 
  dapp_sm_ric.c 
  ../../util/byte_array.c 
  ../../util/alg_ds/alg/defer.c 
  ../../util/alg_ds/alg/eq_float.c 
  ../../util/alg_ds/ds/seq_container/seq_arr.c 
  ../../util/alg_ds/ds/seq_container/seq_ring.c 
  ../../util/alg_ds/ds/assoc_container/assoc_rb_tree.c
  ../../util/alg_ds/ds/assoc_container/bimap.c
  ie/dapp_data_ie.c 
  )

if(SM_ENCODING_DAPP STREQUAL "ASN")
  add_subdirectory(ie/asn)
  add_subdirectory(ie/ir)
  add_subdirectory(e3)

  set(SM_ENCODING_DAPP_SRC_ASN
    ${SM_ENCODING_DAPP_SRC}
    enc/dapp_enc_asn.c 
    dec/dapp_dec_asn.c 
    # This dependency sucks!
    $<TARGET_OBJECTS:e2ap_ran_func_obj>
    $<TARGET_OBJECTS:e2sm_dapp_asn1_obj>
    $<TARGET_OBJECTS:e2sm_dapp_ir_obj>
    $<TARGET_OBJECTS:e2_conv_obj>
    $<TARGET_OBJECTS:3gpp_derived_ie_obj>
    $<TARGET_OBJECTS:sm_common_ie_obj>
    )

if(E3_AGENT)
  list(APPEND SM_ENCODING_DAPP_SRC_ASN $<TARGET_OBJECTS:e3sm_obj>)
endif()

  # Shared 
  add_library(dapp_sm SHARED ${SM_ENCODING_DAPP_SRC_ASN})

  target_include_directories(dapp_sm PRIVATE 
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie"
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie/ir"
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie/asn"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../util"
                                "${CMAKE_CURRENT_SOURCE_DIR}/e3"
                              )
  target_compile_options(dapp_sm PRIVATE "-DASN_DISABLE_OER_SUPPORT" "-DASN_DISABLE_JER_SUPPORT" )
  target_compile_options(dapp_sm PRIVATE -fPIC -Wno-missing-field-initializers -Wno-unused-parameter -fvisibility=hidden)

  target_link_libraries(dapp_sm PRIVATE 
                          -lm
                          e2sm_dapp_e3_spectrum_asn1_obj
                        )

  # Static
  add_library(dapp_sm_static STATIC ${SM_ENCODING_DAPP_SRC_ASN})
  target_include_directories(dapp_sm_static PRIVATE 
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie"
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie/ir"
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie/asn"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../util"
                                "${CMAKE_CURRENT_SOURCE_DIR}/e3"
                              )
  target_compile_options(dapp_sm_static PRIVATE "-DASN_DISABLE_JER_SUPPORT" "-DASN_DISABLE_OER_SUPPORT")
  target_compile_options(dapp_sm_static PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fvisibility=hidden )
  target_link_libraries(dapp_sm_static PRIVATE -lm)  
elseif(SM_ENCODING_DAPP STREQUAL "PLAIN" )
  add_subdirectory(ie/ir)

  set(SM_ENCODING_DAPP_SRC_PLAIN
    ${SM_ENCODING_DAPP_SRC}
    enc/dapp_enc_plain.c 
    dec/dapp_dec_plain.c 
    # This dependency sucks!
    $<TARGET_OBJECTS:e2ap_ran_func_obj>
    $<TARGET_OBJECTS:e2sm_dapp_ir_obj>
    $<TARGET_OBJECTS:e2_conv_obj>

    $<TARGET_OBJECTS:3gpp_derived_ie_obj>
    $<TARGET_OBJECTS:sm_common_ie_obj>
    )


  # Shared 
  add_library(dapp_sm SHARED ${SM_ENCODING_DAPP_SRC_PLAIN})
  target_include_directories(dapp_sm PRIVATE 
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie"
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie/ir"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../util"
                              )
  target_compile_options(dapp_sm PRIVATE -fPIC -Wno-missing-field-initializers -Wno-unused-parameter -fvisibility=hidden)
  target_link_libraries(dapp_sm PRIVATE -lm)  


  # Static
  add_library(dapp_sm_static STATIC ${SM_ENCODING_DAPP_SRC_PLAIN})
  target_include_directories(dapp_sm_static PRIVATE 
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie"
                                "${CMAKE_CURRENT_SOURCE_DIR}/ie/ir"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../util"
                              )
  target_compile_options(dapp_sm_static PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter -fvisibility=hidden )
  target_link_libraries(dapp_sm_static PRIVATE -lm)  

elseif(SM_ENCODING_DAPP STREQUAL "FLATBUFFERS" )
  message(FATAL_ERROR "DAPP SM FB not implemented")
  add_library(dapp_sm SHARED
                     ${SM_ENCODING_DAPP_SRC}
                      enc/dapp_enc_fb.c 
                      dec/dapp_dec_fb.c 
                      )
else()
  message(FATAL_ERROR "Unknown SM encoding type ")
endif()

target_compile_definitions(dapp_sm PUBLIC ${SM_ENCODING_DAPP} ${E2AP_VERSION} ${KPM_VERSION}  )
target_compile_definitions(dapp_sm_static PUBLIC ${SM_ENCODING_DAPP} ${E2AP_VERSION} ${KPM_VERSION}   )

