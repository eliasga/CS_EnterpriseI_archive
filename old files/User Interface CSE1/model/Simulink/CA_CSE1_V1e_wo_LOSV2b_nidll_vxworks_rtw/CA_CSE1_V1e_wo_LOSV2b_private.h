/*
 * CA_CSE1_V1e_wo_LOSV2b_private.h
 *
 * Real-Time Workshop code generation for Simulink model "CA_CSE1_V1e_wo_LOSV2b.mdl".
 *
 * Model Version              : 1.193
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Fri Sep 20 14:51:46 2013
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_CA_CSE1_V1e_wo_LOSV2b_private_h_
#define RTW_HEADER_CA_CSE1_V1e_wo_LOSV2b_private_h_
#include "rtwtypes.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I32L32N32F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I32L32N32F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   /* do nothing */
# else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

/* private model entry point functions */
extern void CA_CSE1_V1e_wo_LOSV2b_derivatives(void);
int_T rt_WriteMat4FileHeader(FILE *fp,
  int32_T m,
  int32_T n,
  const char_T *name);
void MWDSPCG_Pseudoinverse_D(real_T pS[], real_T pU[], real_T pV[], real_T pX[],
  const int32_T M, const int32_T N);

#endif                                 /* RTW_HEADER_CA_CSE1_V1e_wo_LOSV2b_private_h_ */
