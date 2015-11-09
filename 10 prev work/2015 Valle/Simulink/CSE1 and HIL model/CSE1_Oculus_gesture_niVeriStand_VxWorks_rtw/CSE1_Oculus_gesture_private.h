/*
 * CSE1_Oculus_gesture_private.h
 *
 * Code generation for model "CSE1_Oculus_gesture".
 *
 * Model version              : 1.30
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Thu Apr 23 10:29:55 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_CSE1_Oculus_gesture_private_h_
#define RTW_HEADER_CSE1_Oculus_gesture_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#endif                                 /* __RTWTYPES_H__ */

extern real_T rt_roundd_snf(real_T u);
extern real_T rt_remd_snf(real_T u0, real_T u1);
extern real_T rt_atan2d_snf(real_T u0, real_T u1);
int_T rt_WriteMat4FileHeader(FILE *fp,
  int32_T m,
  int32_T n,
  const char_T *name);
extern void CSE1_Oculus_gesture_w_dw_d(const real_T rtu_w_d[9],
  B_w_dw_d_CSE1_Oculus_gesture_T *localB);
extern void CSE1_Oculus_gesture_w_dw_d1(const real_T rtu_w_d[9], const real_T
  rtu_zeta[9], B_w_dw_d1_CSE1_Oculus_gesture_T *localB);
extern void CSE1_Oculus_gesture_w_d2(const real_T rtu_w_d[9],
  B_w_d2_CSE1_Oculus_gesture_T *localB);
extern void CSE1_Oculus_gesture_w_d3(const real_T rtu_w_d[9],
  B_w_d3_CSE1_Oculus_gesture_T *localB);
extern void CSE1_Oculus_gest_MATLABFunction(real_T rtu_K_p1, real_T rtu_K_p1_f,
  real_T rtu_K_p1_m, B_MATLABFunction_CSE1_Oculus__T *localB);
extern void CSE1_Oculus_gesture_diag(real_T rtu_w_d_vector, real_T
  rtu_w_d_vector_l, real_T rtu_w_d_vector_e, B_diag_CSE1_Oculus_gesture_T
  *localB);
extern void CSE1_Oculus_gesture_diag1(real_T rtu_zeta_vector, real_T
  rtu_zeta_vector_p, real_T rtu_zeta_vector_pm, B_diag1_CSE1_Oculus_gesture_T
  *localB);
extern void CSE1_Oculus_gesture_diag2vector(const real_T rtu_u[9],
  B_diag2vector_CSE1_Oculus_ges_T *localB);

/* private model entry point functions */
extern void CSE1_Oculus_gesture_derivatives(void);

#endif                                 /* RTW_HEADER_CSE1_Oculus_gesture_private_h_ */
