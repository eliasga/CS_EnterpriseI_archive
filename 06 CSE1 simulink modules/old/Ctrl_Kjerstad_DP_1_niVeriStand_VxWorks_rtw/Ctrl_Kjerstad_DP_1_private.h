/*
 * Ctrl_Kjerstad_DP_1_private.h
 *
 * Code generation for model "Ctrl_Kjerstad_DP_1".
 *
 * Model version              : 1.8
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Feb 04 12:24:04 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Ctrl_Kjerstad_DP_1_private_h_
#define RTW_HEADER_Ctrl_Kjerstad_DP_1_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#endif                                 /* __RTWTYPES_H__ */

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern void Ctrl_Kjerstad_DP_1_diag3x3(real_T rtu_u, real_T rtu_u_n, real_T
  rtu_u_h, B_diag3x3_Ctrl_Kjerstad_DP_1_T *localB);

/* private model entry point functions */
extern void Ctrl_Kjerstad_DP_1_derivatives(void);

#endif                                 /* RTW_HEADER_Ctrl_Kjerstad_DP_1_private_h_ */
