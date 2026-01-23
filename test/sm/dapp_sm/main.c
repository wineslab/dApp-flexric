#include "../../rnd/fill_rnd_data_dapp.h"
#include "../../../src/util/alg_ds/alg/defer.h"
#include "../../../src/sm/dapp_sm/dapp_sm_agent.h"
#include "../../../src/sm/dapp_sm/dapp_sm_ric.h"
#include "../../../src/sm/dapp_sm/ie/dapp_data_ie.h"
#include "../../../src/sm/dapp_sm/dapp_sm_id.h"


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

//
// Functions 

/////
// AGENT
////

// For testing purposes
static
dapp_ind_data_t cp_ind;

static
dapp_e2_setup_t cp_e2_setup; 

static
bool read_ind_dapp(void* read)
{
  assert(read != NULL);

  dapp_rd_ind_data_t* dapp = (dapp_rd_ind_data_t*)read;

  dapp->ind = fill_rnd_dapp_ind_data();
  cp_ind = cp_dapp_ind_data(&dapp->ind);

  assert(eq_dapp_ind_data(&dapp->ind, &cp_ind) == true);
  return true;
}

static
void read_setup_dapp(void* read)
{
  assert(read != NULL);

  dapp_e2_setup_t* dapp = (dapp_e2_setup_t*) read;
  dapp->ran_func_def = fill_dapp_ran_func_def();
  cp_e2_setup.ran_func_def = cp_e2sm_dapp_func_def(&dapp->ran_func_def);
  assert(eq_e2sm_dapp_func_def(&cp_e2_setup.ran_func_def, &dapp->ran_func_def) == true);
}

// For testing purposes
static
dapp_sub_data_t cp_dapp_sub; 

static
dapp_ctrl_req_data_t cp_dapp_ctrl; 

static
e2sm_dapp_ctrl_out_t cp_dapp_ctrl_out; 


static 
sm_ag_if_ans_t write_ctrl_dapp(void const* data)
{
  assert(data != NULL); 

  dapp_ctrl_req_data_t const* ctrl = (dapp_ctrl_req_data_t const*)data;

  // RAN Input
  cp_dapp_ctrl = cp_dapp_ctrl_req_data(ctrl);

  // RAN Output
  sm_ag_if_ans_t ans = {.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0};
  ans.ctrl_out.type = DAPP_V1_3_AGENT_IF_CTRL_ANS_V0;
  ans.ctrl_out.dapp = fill_dapp_ctrl_out();
  cp_dapp_ctrl_out = cp_e2sm_dapp_ctrl_out( &ans.ctrl_out.dapp );

  return ans;
}

static
void free_aperiodic_subscription(uint32_t ric_req_id)
{
  (void)ric_req_id;
}

static 
sm_ag_if_ans_t write_subs_dapp(void const* data)
{
  assert(data != NULL); 

  wr_dapp_sub_data_t const* wr_dapp = (wr_dapp_sub_data_t const*)data;

  cp_dapp_sub = cp_dapp_sub_data(&wr_dapp->dapp);

  sm_ag_if_ans_t ans = {.type = SUBS_OUTCOME_SM_AG_IF_ANS_V0 };
  ans.subs_out.type = APERIODIC_SUBSCRIPTION_FLRC;
  ans.subs_out.aper.free_aper_subs = free_aperiodic_subscription;
  return ans;
}

/*
static 
sm_ag_if_ans_t write_RAN(sm_ag_if_wr_t const* data)
{
  assert(data != NULL); 

  sm_ag_if_ans_t ans = {.type = NONE_SM_AG_IF_ANS_V0};

  if(data->type == SUBSCRIPTION_SM_AG_IF_WR){
    assert(data->subs.type == DAPP_SUBS_V1_03); 
    cp_dapp_sub = cp_dapp_sub_data(&data->subs.wr_dapp.dapp);

  } else if(data->type == CONTROL_SM_AG_IF_WR){
    assert(data->ctrl.type == DAPP_CTRL_V1_03);
    
    // RAN Input
    cp_dapp_ctrl = cp_dapp_ctrl_req_data(&data->ctrl.dapp_ctrl);

    // RAN Output
    ans.type = CTRL_OUTCOME_SM_AG_IF_ANS_V0; 
    ans.ctrl_out.type = DAPP_V1_3_AGENT_IF_CTRL_ANS_V0;
    ans.ctrl_out.dapp = fill_dapp_ctrl_out();
    cp_dapp_ctrl_out = cp_e2sm_dapp_ctrl_out( &ans.ctrl_out.dapp );

  } else {
    assert(0!=0 && "Unknown type");
  }

  return ans;
}
*/


/////////////////////////////
// Check Functions
// //////////////////////////

/*
static
void check_eq_ran_function(sm_agent_t const* ag, sm_ric_t const* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);


  assert(ag->ran_func_id == ric->ran_func_id);
}

*/

// RIC -> E2
static
void check_subscription(sm_agent_t* ag, sm_ric_t* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);

  dapp_sub_data_t dapp = fill_rnd_dapp_subscription();
  defer({ free_dapp_sub_data(&dapp); });

  sm_subs_data_t data = ric->proc.on_subscription(ric, &dapp);
  defer({ free_sm_subs_data(&data); });

  sm_ag_if_ans_subs_t const subs = ag->proc.on_subscription(ag, &data); 
  assert(subs.type == APERIODIC_SUBSCRIPTION_FLRC);
  assert(subs.aper.free_aper_subs != NULL);

  defer({  free_dapp_sub_data(&cp_dapp_sub); });

  assert(eq_dapp_sub_data(&dapp, &cp_dapp_sub) == true);
}

// E2 -> RIC
static
void check_indication(sm_agent_t* ag, sm_ric_t* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);

  dapp_ind_data_t* d = calloc(1, sizeof(dapp_ind_data_t)); 
  assert(d != NULL && "Memory exhausted");
  *d = fill_rnd_dapp_ind_data();
  cp_ind = cp_dapp_ind_data(d);

  exp_ind_data_t exp = ag->proc.on_indication(ag, d);
  assert(exp.has_value == true);
  defer({ free_exp_ind_data(&exp); }); 
  defer({ free_dapp_ind_data(&cp_ind); });

  sm_ag_if_rd_ind_t msg = ric->proc.on_indication(ric, &exp.data);
  assert(msg.type == DAPP_STATS_V1_03);
  defer({ free_dapp_ind_data(&msg.dapp.ind); });

  dapp_ind_data_t const* data = &msg.dapp.ind;

  assert(eq_dapp_ind_data(&cp_ind, data) == true);
}


static
void check_ctrl(sm_agent_t* ag, sm_ric_t* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);

  dapp_ctrl_req_data_t dapp_ctrl = fill_dapp_ctrl();
  defer({ free_dapp_ctrl_req_data(&dapp_ctrl); });

  sm_ctrl_req_data_t ctrl_req = ric->proc.on_control_req(ric, &dapp_ctrl);
  defer({ free_sm_ctrl_req_data(&ctrl_req); });

  sm_ctrl_out_data_t out_data = ag->proc.on_control(ag, &ctrl_req);
  defer({ free_sm_ctrl_out_data(&out_data); });
  defer({ free_dapp_ctrl_req_data(&cp_dapp_ctrl); });

  assert(eq_dapp_ctrl_req_data(&dapp_ctrl, &cp_dapp_ctrl));

  sm_ag_if_ans_ctrl_t ans = ric->proc.on_control_out(ric, &out_data);
  assert(ans.type == DAPP_V1_3_AGENT_IF_CTRL_ANS_V0);
  defer({ free_e2sm_dapp_ctrl_out(&ans.dapp); });
  defer({ free_e2sm_dapp_ctrl_out(&cp_dapp_ctrl_out); });

  assert(eq_e2sm_dapp_ctrl_out(&ans.dapp, &cp_dapp_ctrl_out));
}

void check_e2_setup(sm_agent_t* ag, sm_ric_t* ric)
{
  assert(ag != NULL);
  assert(ric != NULL);

  sm_e2_setup_data_t data = ag->proc.on_e2_setup(ag);
  defer({ free_sm_e2_setup(&data); });

  sm_ag_if_rd_e2setup_t out = ric->proc.on_e2_setup(ric, &data);
  assert(out.type == DAPP_AGENT_IF_E2_SETUP_ANS);
  defer({ free_e2sm_dapp_func_def(&out.dapp.ran_func_def); });

  assert(eq_e2sm_dapp_func_def(&out.dapp.ran_func_def, &cp_e2_setup.ran_func_def) == true);
  free_e2sm_dapp_func_def(&cp_e2_setup.ran_func_def);
}

int main()
{
  srand(time(0)); 

  sm_io_ag_ran_t io_ag = {0}; //.read = read_RAN, .write = write_RAN};  
  // Read 
  io_ag.read_ind_tbl[DAPP_STATS_V1_03] = read_ind_dapp; 
  io_ag.read_setup_tbl[DAPP_AGENT_IF_E2_SETUP_ANS] = read_setup_dapp; 

  // Write
  io_ag.write_ctrl_tbl[DAPP_CTRL_V1_03] =  write_ctrl_dapp;
  io_ag.write_subs_tbl[DAPP_SUBS_V1_03] =  write_subs_dapp;

  sm_agent_t* sm_ag = make_dapp_sm_agent(io_ag);
  sm_ric_t* sm_ric = make_dapp_sm_ric();

  printf("Running RAN Control SM test. Patience. \n");
  for(int i =0 ; i < 1024; ++i){
    // check_eq_ran_function(sm_ag, sm_ric);
    check_indication(sm_ag, sm_ric);
    check_subscription(sm_ag, sm_ric);
    check_ctrl(sm_ag, sm_ric);
    check_e2_setup(sm_ag, sm_ric);
    // check_ric_service_update(sm_ag, sm_ric);
  }

  sm_ag->free_sm(sm_ag);
  sm_ric->free_sm(sm_ric);

  printf("RAN Control (DAPP-SM) version 1.3 Release 3 run with success\n");
  return EXIT_SUCCESS;
}

