/*
 * rt_atan2_snf.c
 *
 * Real-Time Workshop code generation for Simulink model "LgV2.mdl".
 *
 * Model Version              : 1.198
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Wed Nov 27 14:51:41 2013
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 */

#include "rt_atan2_snf.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include <math.h>

/* Function: rt_atan2_snf =======================================================
 * Abstract:
 *   Calls ATAN2, with guards against domain error and non-finites
 */
real_T rt_atan2_snf(real_T a, real_T b)
{
  real_T retValue;
  if (rtIsNaN(a) || rtIsNaN(b)) {
    retValue = (rtNaN);
  } else {
    if (rtIsInf(a) && rtIsInf(b)) {
      if (b > 0.0) {
        b = 1.0;
      } else {
        b = -1.0;
      }

      if (a > 0.0) {
        a = 1.0;
      } else {
        a = -1.0;
      }

      retValue = atan2(a,b);
    } else if (b == 0.0) {
      if (a > 0.0) {
        retValue = (RT_PI)/2.0;
      } else if (a < 0.0) {
        retValue = -(RT_PI)/2.0;
      } else {
        retValue = 0.0;
      }
    } else {
      retValue = atan2(a,b);
    }
  }

  return retValue;
}                                      /* end rt_atan2_snf */
