#include "../../../../src/util/alg_ds/ds/lock_guard/lock_guard.h"
#include "../../../../src/xApp/e42_xapp_api.h"
#include "../../../../src/util/time_now_us.h"
#include "../../../../src/util/e.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <unistd.h>
#include <pthread.h>
#include <inttypes.h>
#include <signal.h>
#include <pthread.h>

int const DAPP_SM_ID = 255;

enum {
  RAN_FUNC_ID_SPECTRUM = 1,
};

/* Global termination flag, set by signal handler */
static volatile sig_atomic_t g_terminate = 0;

static void* signal_thread(void* arg)
{
  sigset_t* set = (sigset_t*)arg;
  int sig;

  // Wait for SIGINT or SIGTERM
  if (sigwait(set, &sig) == 0) {
    g_terminate = 1;
  }
  return NULL;
}

/**
 * @brief Indication callback for the DAPP service model.
 *
 * This function is registered as the report callback for the DAPP SM.
 * It:
 *  - Verifies that the received message is a DAPP indication in format 0.
 *  - Retrieves the indication header, message, and E3 payload.
 *  - Prints a summary of the payload depending on the E3 SM type:
 *      * DAPP_E3_SM_SPECTRUM: prints the list of (up to 15) PRBs.
 *  - Logs an error message if the payload type is unexpected.
 */
static void sm_cb_dapp(sm_ag_if_rd_t const* rd)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.dapp.ind.msg.format == FORMAT_0_E2SM_DAPP_IND_MSG);

  const e2sm_dapp_ind_hdr_frmt_0_t* hdr = &rd->ind.dapp.ind.hdr.frmt_0;
  const e2sm_dapp_ind_msg_frmt_0_t* msg = &rd->ind.dapp.ind.msg.frmt_0;
  const dapp_e3_ind_payload_t* e3 = &rd->ind.dapp.ind.e3;

  if (msg->data == NULL || msg->data_size == 0) {
    printf("[DAPP][SM_CB] Payload: <empty>\n");
    return;
  }

  if(e3->type == DAPP_E3_SM_SPECTRUM){
    const spectrum_sm_report_t* rep = &e3->u.spectrum;

    printf("[DAPP][SM_CB] Indication: ran_function_id=%u, data_size=%u\n", hdr->ran_function_id, (unsigned)msg->data_size);
    printf("[DAPP][SM_CB] Spectrum E3 payload: prb_count=%ld\n", rep->prb_count);

    printf("[DAPP][SM_CB] %ld PRBs:", rep->prb_count);
    for (long i = 0; i < rep->prb_count; ++i) {
      printf(" %u", rep->prbs[i]);
    }
    printf("\n");
  }
}

/**
 * @brief Send a DAPP control message to all connected E2 nodes.
 *
 * This helper:
 *  - Builds a dapp_ctrl_req_data_t with:
 *      * Control header: RAN function ID and dApp ID.
 *      * Empty control message body (E2SM DAPP format 0).
 *      * E3 payload passed by the caller.
 *  - Uses control_sm_xapp_api() to send the control request to each E2 node.
 *  - Asserts that every control operation succeeds.
 *  - Frees any memory dynamically owned by ctrl via free_dapp_ctrl_req_data().
 */
static void send_control_message(e2_node_arr_xapp_t nodes,
                                 int SM_ID,
                                 uint32_t ran_function_id,
                                 uint32_t dapp_id,
                                 const dapp_e3_ctrl_payload_t* e3_payload)
{
  dapp_ctrl_req_data_t ctrl = (dapp_ctrl_req_data_t){0};

  ctrl.hdr.format = FORMAT_0_E2SM_DAPP_CTRL_HDR;
  ctrl.hdr.frmt_0.ran_function_id = ran_function_id;
  ctrl.hdr.frmt_0.dapp_id = dapp_id;

  ctrl.msg.format = FORMAT_0_E2SM_DAPP_CTRL_MSG;
  ctrl.msg.frmt_0.data = NULL;
  ctrl.msg.frmt_0.data_size = 0;

  ctrl.e3 = *e3_payload;

  for (int i = 0; i < nodes.len; i++) {
    sm_ans_xapp_t ans = control_sm_xapp_api(&nodes.n[i].id, SM_ID, &ctrl);
    assert(ans.success == true);
  }

  free_dapp_ctrl_req_data(&ctrl);
}

/**
 * @brief Build and send a test Spectrum SM control message.
 *
 * This function:
 *  - Allocates and fills a spectrum_sm_control_t with a small list of PRBs
 *    that should NOT be blocked by the gNB (whitelist).
 *  - Wraps this in a dapp_e3_ctrl_payload_t of type DAPP_E3_SM_SPECTRUM.
 *  - Sends the control to all E2 nodes using the generic send_control_message()
 *    helper with the Spectrum RAN function ID.
 */
static void generate_control_message_spectrum(e2_node_arr_xapp_t nodes)
{
  spectrum_sm_control_t ctrl = (spectrum_sm_control_t){0};
  ctrl.prb_count = 4;
  ctrl.whitelistedPRBs = calloc(ctrl.prb_count, sizeof(uint16_t));

  assert(ctrl.whitelistedPRBs != NULL && "Failed to allocate PRB list");

  ctrl.whitelistedPRBs[0] = 1;
  ctrl.whitelistedPRBs[1] = 3;
  ctrl.whitelistedPRBs[2] = 6;
  ctrl.whitelistedPRBs[3] = 9;

  dapp_e3_ctrl_payload_t payload = (dapp_e3_ctrl_payload_t){0};
  payload.type = DAPP_E3_SM_SPECTRUM;
  payload.u.spectrum = ctrl;

  uint32_t ran_function_id = RAN_FUNC_ID_SPECTRUM; // Spectrum SM
  uint32_t dapp_id = 1; // dApp id

  send_control_message(nodes, DAPP_SM_ID, ran_function_id, dapp_id, &payload);
}

/**
 * @brief Generate a minimal DAPP subscription structure.
 *
 * Given a DAPP RAN function definition, this:
 *  - Initializes an event trigger in format 0 with default values
 *    (no specific filtering is set here).
 *  - Allocates a single action definition in format 0, style type 1.
 *  - Returns a dapp_sub_data_t ready to be passed to report_sm_xapp_api().
 *
 * The caller is responsible for freeing it with free_dapp_sub_data().
 */
static dapp_sub_data_t gen_dapp_subs(e2sm_dapp_func_def_t const* ran_func)
{
  assert(ran_func != NULL);
  dapp_sub_data_t dapp_sub = (dapp_sub_data_t){0};

  dapp_sub.et.format = FORMAT_0_E2SM_DAPP_EV_TRIGGER_FORMAT;
  dapp_sub.et.frmt_0 = (e2sm_dapp_ev_trg_frmt_0_t){};

  dapp_sub.sz_ad = 1;
  dapp_sub.ad = calloc(1, sizeof(e2sm_dapp_action_def_t));
  assert(dapp_sub.ad != NULL);

  dapp_sub.ad[0].ric_style_type = 1;
  dapp_sub.ad[0].format = FORMAT_0_E2SM_DAPP_ACT_DEF;

  dapp_sub.ad[0].frmt_0 = (e2sm_dapp_act_def_frmt_0_t){};

  return dapp_sub;
}

/**
 * @brief Find the index of a RAN function in an array by predicate.
 *
 * This generic helper:
 *  - Iterates over an array of sm_ran_function_t objects.
 *  - Applies the predicate f(elem, id) to each element.
 *  - Returns the index of the first element for which f() is true.
 *  - Asserts (and aborts) if no match is found.
 *
 * In this file, it is used to locate the DAPP SM by its SM ID.
 */
static size_t find_sm_idx(sm_ran_function_t* rf, size_t sz, bool (*f)(sm_ran_function_t const*, int const), int const id)
{
  for (size_t i = 0; i < sz; i++) {
    if (f(&rf[i], id))
      return i;
  }

  assert(0 != 0 && "SM ID could not be found in the RAN Function List");
}

/**
 * @brief Predicate that checks whether a RAN function has a given SM ID.
 *
 * Returns true if elem->id == id, false otherwise.
 * Used together with find_sm_idx() to locate the DAPP SM in the RF list.
 */
static bool eq_sm(sm_ran_function_t const* elem, int const id)
{
  if (elem->id == id)
    return true;

  return false;
}

/**
 * @brief Print human-readable information about a DAPP RAN function.
 *
 * Given an E2 node and an index into its RAN function list, this:
 *  - Checks that the entry is a DAPP RAN function.
 *  - Prints:
 *      * SM ID
 *      * Name, description, and OID (if present)
 *      * Whether an event trigger is present
 *      * All configured report styles (if any)
 *      * All configured control styles (if any)
 *
 * This is mainly for debugging/inspection of the DAPP function definition.
 */
static void print_dapp_sm_info(size_t idx, e2_node_connected_xapp_t const* n)
{
  assert(n != NULL);
  assert(idx < n->len_rf);

  const sm_ran_function_t* rf = &n->rf[idx];

  assert(rf->defn.type == DAPP_RAN_FUNC_DEF_E);

  const e2sm_dapp_func_def_t* d = &rf->defn.dapp;

  printf("[DAPP xApp] RAN function @idx=%zu\n", idx);
  printf("  SM ID: %d\n", rf->id);

  if (d->name.name.buf && d->name.name.len > 0) {
    printf("  Name: %.*s\n", (int)d->name.name.len, (const char*)d->name.name.buf);
  }

  if (d->name.description.buf && d->name.description.len > 0) {
    printf("  Description: %.*s\n", (int)d->name.description.len, (const char*)d->name.description.buf);
  }

  if (d->name.oid.buf && d->name.oid.len > 0) {
    printf("  OID: %.*s\n", (int)d->name.oid.len, (const char*)d->name.oid.buf);
  }

  if (d->ev_trig == NULL) {
    printf("  Event trigger: none\n");
  } else {
    printf("  Event trigger: present (details omitted)\n");
  }

  if (d->report != NULL && d->report->sz_seq_report_sty > 0 && d->report->seq_report_sty != NULL) {
    printf("  Report styles (%zu):\n", d->report->sz_seq_report_sty);

    for (size_t i = 0; i < d->report->sz_seq_report_sty; ++i) {
      const seq_report_sty_dapp_sm_t* s = &d->report->seq_report_sty[i];

      printf(
          "    - report_type=%u, name=%.*s, "
          "ev_trig_type=%u, act_frmt_type=%u, ind_hdr_type=%u, ind_msg_type=%u\n",
          s->report_type,
          (int)s->name.len,
          (const char*)s->name.buf,
          s->ev_trig_type,
          s->act_frmt_type,
          s->ind_hdr_type,
          s->ind_msg_type);
    }
  } else {
    printf("  Report styles: none\n");
  }

  if (d->ctrl != NULL && d->ctrl->sz_seq_ctrl_style > 0 && d->ctrl->seq_ctrl_style != NULL) {
    printf("  Control styles (%zu):\n", d->ctrl->sz_seq_ctrl_style);

    for (size_t i = 0; i < d->ctrl->sz_seq_ctrl_style; ++i) {
      const seq_ctrl_style_dapp_sm_t* s = &d->ctrl->seq_ctrl_style[i];

      printf(
          "    - style_type=%u, name=%.*s, "
          "hdr_type=%u, msg_type=%u, out_frmt_type=%u\n",
          s->style_type,
          (int)s->name.len,
          (const char*)s->name.buf,
          s->hdr,
          s->msg,
          s->out_frmt);
    }
  } else {
    printf("  Control styles: none\n");
  }
}

/**
 * @brief Subscribe to the DAPP SM on all connected E2 nodes.
 *
 * For each node:
 *  - Finds the DAPP SM in the RAN function list using find_sm_idx()/eq_sm().
 *  - Verifies that the RAN function is of DAPP type.
 *  - Prints debug information about the RAN function.
 *  - Builds a minimal subscription (event trigger + action definition).
 *  - Calls report_sm_xapp_api() to install the report subscription
 *    and registers sm_cb_dapp as the indication callback.
 *  - Stores the subscription handle in hndl[i].
 *
 * The caller must later remove these subscriptions with delete_subscriptions().
 */
static void subscribe_sm(e2_node_arr_xapp_t nodes, sm_ans_xapp_t* hndl)
{
  for (size_t i = 0; i < nodes.len; ++i) {
    e2_node_connected_xapp_t* n = &nodes.n[i];

    size_t const idx = find_sm_idx(n->rf, n->len_rf, eq_sm, DAPP_SM_ID);
    assert(n->rf[idx].defn.type == DAPP_RAN_FUNC_DEF_E && "DAPP is not the received RAN Function");

    if (n->rf[idx].defn.dapp.name.name.buf != NULL) {
      print_dapp_sm_info(idx, n);

      dapp_sub_data_t dapp_sub = gen_dapp_subs(&n->rf[idx].defn.dapp);

      hndl[i] = report_sm_xapp_api(&n->id, DAPP_SM_ID, &dapp_sub, sm_cb_dapp);
      assert(hndl[i].success == true);

      free_dapp_sub_data(&dapp_sub);
    }
  }
}

/**
 * @brief Remove DAPP SM subscriptions from all E2 nodes.
 *
 * This function:
 *  - Iterates over the array of subscription answers.
 *  - For each successful subscription, calls rm_report_sm_xapp_api()
 *    with the stored handle to remove the subscription from the RIC.
 */
static void delete_subscriptions(sm_ans_xapp_t* hndl, e2_node_arr_xapp_t nodes)
{
  for (int i = 0; i < nodes.len; ++i) {
    if (hndl[i].success == true) {
      rm_report_sm_xapp_api(hndl[i].u.handle);
    }
  }
}

/**
 * @brief Entry point for the DAPP “RC” xApp demo.
 *
 * High-level behavior:
 *  - Parses command-line arguments and initializes the xApp API.
 *  - Retrieves the list of connected E2 nodes.
 *  - Subscribes to the DAPP SM on each node, registering sm_cb_dapp().
 *  - Sends one Spectrum control message to all nodes.
 *  - Sleeps for 600 seconds, during which indications are received and
 *    handled by sm_cb_dapp() in the background.
 *  - Cleans up:
 *      * Removes subscriptions.
 *      * Stops the xApp API loop.
 *      * Frees node and handle resources.
 *  - Prints a final success message before exiting.
 */
int main(int argc, char* argv[])
{
  fr_args_t args = init_fr_args(argc, argv);

  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  sigaddset(&set, SIGTERM);

  int rc = pthread_sigmask(SIG_BLOCK, &set, NULL);
  assert(rc == 0);

  // 2) Start the signal-handling thread
  pthread_t sig_thr;
  rc = pthread_create(&sig_thr, NULL, signal_thread, &set);
  assert(rc == 0);

  init_xapp_api(&args);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  assert(nodes.len > 0);

  printf("[DAPP RC]: Connected E2 nodes = %d\n", nodes.len);

  sm_ans_xapp_t* hndl = calloc(nodes.len, sizeof(sm_ans_xapp_t));
  assert(hndl != NULL);

  subscribe_sm(nodes, hndl);

  generate_control_message_spectrum(nodes);

  /* Wait up to 600 seconds, or until CTRL+C / SIGTERM arrives */
  const unsigned max_runtime_sec = 600;
  unsigned elapsed = 0;

  while (!g_terminate && elapsed < max_runtime_sec) {
    sleep(1);
    ++elapsed;
  }

  if (g_terminate) {
    printf("[DAPP RC]: Termination signal received, shutting down...\n");
  } else {
    printf("[DAPP RC]: Max runtime reached, shutting down...\n");
  }

  /* Clean up: unsubscribe, free memory, stop xApp API */
  delete_subscriptions(hndl, nodes);
  free(hndl);

  sleep(1);

  while (try_stop_xapp_api() == false)
    usleep(1000);

  free_e2_node_arr_xapp(&nodes);

  printf("[DAPP RC]: Test xApp run SUCCESSFULLY\n");
}
