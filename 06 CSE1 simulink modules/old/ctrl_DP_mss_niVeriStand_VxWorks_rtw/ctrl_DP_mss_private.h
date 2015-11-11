/*
 * ctrl_DP_mss_private.h
 *
 * Code generation for model "ctrl_DP_mss".
 *
 * Model version              : 1.10
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Jan 28 18:35:59 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_ctrl_DP_mss_private_h_
#define RTW_HEADER_ctrl_DP_mss_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#endif                                 /* __RTWTYPES_H__ */

extern real_T rt_roundd_snf(real_T u);
extern real_T rt_remd_snf(real_T u0, real_T u1);
extern real_T rt_atan2d_snf(real_T u0, real_T u1);

/* private model entry point functions */
extern void ctrl_DP_mss_derivatives(void);

#endif                                 /* RTW_HEADER_ctrl_DP_mss_private_h_ */
