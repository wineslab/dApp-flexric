set (IR_DAPP_SRC
  e2sm_dapp_act_def_frmt_0.c
  e2sm_dapp_ctrl_hdr_frmt_0.c
  e2sm_dapp_ctrl_msg_frmt_0.c
  e2sm_dapp_ctrl_out_frmt_0.c
  e2sm_dapp_ev_trg_frmt_0.c
  e2sm_dapp_ind_hdr_frmt_0.c
  e2sm_dapp_ind_msg_frmt_0.c
  ran_func_def_ctrl.c
  ran_func_def_ev_trig.c
  ran_func_def_report.c
  seq_ctrl_style.c
  seq_ev_trg_style.c
  seq_report_sty.c
  )

add_library(e2sm_dapp_ir_obj OBJECT ${IR_DAPP_SRC})
target_include_directories(e2sm_dapp_ir_obj
                          PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           )

target_compile_options(e2sm_dapp_ir_obj PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter  -fPIC -fvisibility=hidden )


