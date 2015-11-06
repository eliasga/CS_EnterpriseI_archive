/*
 * rt_SIGNd_snf.h
 *
 * Real-Time Workshop code generation for Simulink model "Template_test.mdl".
 *
 * Model Version              : 1.13
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Thu Mar 20 15:08:38 2014
 *
 * Target selection: nidll_vxworks.tlc
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
