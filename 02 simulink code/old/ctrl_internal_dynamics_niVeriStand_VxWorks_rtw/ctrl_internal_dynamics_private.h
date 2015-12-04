/*
 * ctrl_internal_dynamics_private.h
 *
 * Code generation for model "ctrl_internal_dynamics".
 *
 * Model version              : 1.148
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Feb 25 09:52:00 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_ctrl_internal_dynamics_private_h_
#define RTW_HEADER_ctrl_internal_dynamics_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#endif                                 /* __RTWTYPES_H__ */

extern void ctrl_internal_dynamics_diag2x2(real_T rtu_u, real_T rtu_u_j,
  B_diag2x2_ctrl_internal_dynam_T *localB);

#endif                                 /* RTW_HEADER_ctrl_internal_dynamics_private_h_ */
