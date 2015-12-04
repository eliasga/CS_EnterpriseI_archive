/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define power_P                       power_P DataSection(".NIVS.defaultparams")
#endif

/*
 * power_data.c
 *
 * Code generation for model "power".
 *
 * Model version              : 1.25
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Fri Dec 04 14:47:29 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "power.h"
#include "power_private.h"

/* Block parameters (auto storage) */
P_power_T power_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/alpha_VSP1,d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/alpha_VSP1,d'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/alpha_VSP1,d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/alpha_VSP1,d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/alpha_VSP1,d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/alpha_VSP1,d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/u_VSP1,d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/u_VSP1,d'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/u_VSP1,d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/u_VSP1,d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/u_VSP1,d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/u_VSP1,d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/alpha_VSP2,d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/alpha_VSP2,d'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/alpha_VSP2,d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/alpha_VSP2,d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/alpha_VSP2,d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/alpha_VSP2,d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/u_VSP2,d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/u_VSP2,d'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/u_VSP2,d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/u_VSP2,d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/u_VSP2,d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/u_VSP2,d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/u_BT,d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/u_BT,d'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/u_BT,d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/u_BT,d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/u_BT,d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/u_BT,d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/omega_VSP1,d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/omega_VSP1,d'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/omega_VSP1,d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/omega_VSP1,d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/omega_VSP1,d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/omega_VSP1,d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/omega_VSP2,d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/omega_VSP2,d'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/omega_VSP2,d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/omega_VSP2,d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/omega_VSP2,d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/omega_VSP2,d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/omega_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/omega_VSP2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/omega_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/u_BT'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/u_BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/alpha_VSP2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/alpha_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/u_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/u_VSP2'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/u_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/u_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/u_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/u_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/u_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/u_VSP1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/u_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/u_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/u_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/u_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/alpha_VSP1'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/alpha_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/alpha_VSP1'
                                        */
  1.0                                  /* Expression: 1
                                        * Referenced by: '<Root>/NIVeriStandSignalProbe'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_power_T_sizes[] DataSection(".NIVS.defaultparamsizes") = {
  { sizeof(P_power_T), 1 },

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
