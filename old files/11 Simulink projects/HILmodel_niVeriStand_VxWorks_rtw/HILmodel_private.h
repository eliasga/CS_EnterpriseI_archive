/*
 * HILmodel_private.h
 *
 * Code generation for model "HILmodel".
 *
 * Model version              : 1.12
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sat Jan 10 18:08:25 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_HILmodel_private_h_
#define RTW_HEADER_HILmodel_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#endif                                 /* __RTWTYPES_H__ */

extern void rt_mldivide_U1d6x6_U2d_4sw8yi9v(const real_T u0[36], const real_T
  u1[6], real_T y[6]);

/* private model entry point functions */
extern void HILmodel_derivatives(void);

#endif                                 /* RTW_HEADER_HILmodel_private_h_ */
