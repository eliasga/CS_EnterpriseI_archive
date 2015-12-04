/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define CSE1_HIL_tau_P                CSE1_HIL_tau_P DataSection(".NIVS.defaultparams")
#endif

/*
 * CSE1_HIL_tau_data.c
 *
 * Code generation for model "CSE1_HIL_tau".
 *
 * Model version              : 1.153
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Apr 14 18:13:38 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "CSE1_HIL_tau.h"
#include "CSE1_HIL_tau_private.h"

/* Block parameters (auto storage) */
P_CSE1_HIL_tau_T CSE1_HIL_tau_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/integrator_reset'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/integrator_reset'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/integrator_reset'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/integrator_reset'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/integrator_reset'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/integrator_reset'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Memory3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Memory4'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Memory5'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/x'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/y'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/psi'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/psi'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/psi'
                                        */

  /*  Expression: [0 0 0]'
   * Referenced by: '<Root>/Integrator'
   */
  { 0.0, 0.0, 0.0 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/u'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/u'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/u'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/u'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/u'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/u'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/v'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/v'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/v'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/v'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/v'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/v'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/r'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/r'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/r'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/r'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/r'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/r'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/psi_0'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/psi_0'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/psi_0'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/psi_0'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/psi_0'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/psi_0'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/x_0'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/x_0'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/x_0'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/x_0'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/x_0'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/x_0'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/y_0'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/y_0'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/y_0'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/y_0'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/y_0'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/y_0'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Memory'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Memory1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Memory2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/X'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/X'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/Y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/Y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/Y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/N'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/N'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/N'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/N'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/N'
                                        */
  1.0                                  /* Expression: btype
                                        * Referenced by: '<S6>/N'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_CSE1_HIL_tau_T_sizes[] DataSection(".NIVS.defaultparamsizes")
  = {
  { sizeof(P_CSE1_HIL_tau_T), 1 },

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

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },
};

#endif
