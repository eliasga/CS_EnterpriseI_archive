/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define HIL_model_P                   HIL_model_P DataSection(".NIVS.defaultparams")
#endif

/*
 * HIL_model_data.c
 *
 * Code generation for model "HIL_model".
 *
 * Model version              : 1.6
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Mon Jan 26 15:48:33 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "HIL_model.h"
#include "HIL_model_private.h"

/* Block parameters (auto storage) */
P_HIL_model_T HIL_model_P = {
  /*  Expression: [0 0 0]'
   * Referenced by: '<Root>/Integrator1'
   */
  { 0.0, 0.0, 0.0 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/eta_N'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/eta_N'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/eta_N'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/eta_N'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/eta_N'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/eta_N'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/tau_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/tau_X'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/tau_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/tau_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/tau_X'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/tau_X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/eta_E'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/eta_E'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/eta_E'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/eta_E'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/eta_E'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/eta_E'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/tau_Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/tau_Y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/tau_Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/tau_Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/tau_Y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/tau_Y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/eta_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/eta_psi'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/eta_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/eta_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/eta_psi'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/eta_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/tau_N'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/tau_N'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/tau_N'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/tau_N'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/tau_N'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/tau_N'
                                        */

  /*  Expression: [0 0 0]'
   * Referenced by: '<Root>/Integrator'
   */
  { 0.0, 0.0, 0.0 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/nu_u'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/nu_u'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/nu_u'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/nu_u'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/nu_u'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/nu_u'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/nu_v'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/nu_v'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/nu_v'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/nu_v'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/nu_v'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/nu_v'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/nu_r'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/nu_r'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/nu_r'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/nu_r'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/nu_r'
                                        */
  0.0                                  /* Expression: btype
                                        * Referenced by: '<Root>/nu_r'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_HIL_model_T_sizes[] DataSection(".NIVS.defaultparamsizes") =
{
  { sizeof(P_HIL_model_T), 1 },

  { sizeof(real_T), 3, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 3, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },
};

#endif
