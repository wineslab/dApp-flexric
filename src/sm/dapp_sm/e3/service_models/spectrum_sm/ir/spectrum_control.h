#ifndef SPECTRUM_CONTROL_IR
#define SPECTRUM_CONTROL_IR

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

/**
 * @brief In-memory representation of a Spectrum SM control command.
 *
 * This IR (intermediate representation) is used on the E3 side to express
 * which PRBs should *not* be blocked by the dApp/gNB.
 */
typedef struct {
  long prb_count;
  uint16_t* whitelistedPRBs;
} spectrum_sm_control_t;

/**
 * @brief Free all dynamic memory owned by a spectrum_sm_control_t.
 * The container itself is not freed, only the internal buffer it owns.
 */
void free_spectrum_sm_control(spectrum_sm_control_t* src);

/**
 * @brief Compare two Spectrum SM control structures for equality.
 *
 * @param m0  First control structure.
 * @param m1  Second control structure.
 * @return true if they are equal, false otherwise.
 */
bool eq_spectrum_sm_control(spectrum_sm_control_t const* m0, spectrum_sm_control_t const* m1);

/**
 * @brief Deep copy a Spectrum SM control structure.
 *
 * @param src  Source control structure to copy.
 * @return A deep copy of @p src.
 */
spectrum_sm_control_t cp_spectrum_sm_control(spectrum_sm_control_t const* src);

#endif
