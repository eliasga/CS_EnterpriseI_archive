/*
 * rt_rem_snf.c
 *
 * Real-Time Workshop code generation for Simulink model "NLPID.mdl".
 *
 * Model Version              : 1.31
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Mon Mar 17 14:05:33 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 */

#include "rt_rem_snf.h"
#include "rt_nonfinite.h"
#include <float.h>
#include <math.h>
#include "rt_round_snf.h"

/* Function: rt_rem_snf =======================================================
 * Abstract:
 *   Calls double-precision version of REM, with guard against domain error
 *   and guards against non-finites
 */
real_T rt_rem_snf(const real_T xr, const real_T yr)
{
  real_T zr, yrf, tr, trf, wr;
  if (yr == 0.0 || rtIsInf(xr) || rtIsInf(yr) || rtIsNaN(xr) || rtIsNaN(yr)) {
    zr = (rtNaN);
  } else {
    yrf = (yr < 0.0) ? ceil(yr) : floor(yr);
    tr = xr/yr;
    if (yr == yrf) {
      /* Integer denominator.  Use conventional formula.*/
      trf = (tr < 0.0) ? ceil(tr) : floor(tr);
      zr = xr - trf*yr;
    } else {
      /* Noninteger denominator. Check for nearly integer quotient.*/
      wr = rt_round_snf(tr);
      if (fabs(tr - wr) <= ((DBL_EPSILON)*fabs(tr))) {
        zr = 0.0;
      } else {
        trf = (tr < 0.0) ? ceil(tr) : floor(tr);
        zr = (tr - trf)*yr;
      }
    }
  }

  return zr;
}                                      /* end rt_rem_snf */
