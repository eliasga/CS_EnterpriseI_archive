/*
 * rt_rand.h
 *
 * Real-Time Workshop code generation for Simulink model "modell.mdl".
 *
 * Model Version              : 1.149
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Tue Mar 12 15:06:30 2013
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rt_rand_h_
#define RTW_HEADER_rt_rand_h_
#include <math.h>
#include "rtwtypes.h"
# define MAXSEED                       2147483646                /* 2^31-2 */
# define SEED0                         1144108930                /* Seed #6, starting from seed = 1 */
# define RT_BIT16                      32768                     /* 2^15   */

extern real_T rt_Urand(uint32_T *seed);
extern real_T rt_NormalRand(uint32_T *seed);

#endif                                 /* RTW_HEADER_rt_rand_h_ */
