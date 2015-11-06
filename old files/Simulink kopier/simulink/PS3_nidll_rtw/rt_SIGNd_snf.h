/*
 * rt_SIGNd_snf.h
 *
 * Real-Time Workshop code generation for Simulink model "PS3.mdl".
 *
 * Model Version              : 1.6
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 16:16:32 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rt_SIGNd_snf_h_
#define RTW_HEADER_rt_SIGNd_snf_h_
#include "rt_nonfinite.h"
#define rt_SIGNd_snf(a)                ( ((a) < 0.0) ? -1.0 : ((a) > 0.0) ? 1.0 : ((a) == 0.0) ? 0.0 : (rtNaN) )
#endif                                 /* RTW_HEADER_rt_SIGNd_snf_h_ */
