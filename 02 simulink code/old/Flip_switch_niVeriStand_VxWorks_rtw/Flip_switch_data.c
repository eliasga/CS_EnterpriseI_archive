/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define Flip_switch_P                 Flip_switch_P DataSection(".NIVS.defaultparams")
#endif

/*
 * Flip_switch_data.c
 *
 * Code generation for model "Flip_switch".
 *
 * Model version              : 1.15
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Mon Feb 02 16:58:03 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Flip_switch.h"
#include "Flip_switch_private.h"

/* Block parameters (auto storage) */
P_Flip_switch_T Flip_switch_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_Switch signal1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_Switch signal1'
                                        */
  14.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_Switch signal1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_Switch signal1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_Switch signal1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_Switch signal1'
                                        */
  0.05,                                /* Computed Parameter: DiscreteTimeIntegrator_gainval
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Indicator'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Indicator'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Indicator'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Indicator'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Indicator'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Indicator'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Sixaxis_Switch signal'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Sixaxis_Switch signal'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Sixaxis_Switch signal'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Sixaxis_Switch signal'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Sixaxis_Switch signal'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Sixaxis_Switch signal'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Sixaxis_alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Sixaxis_alpha_1'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Sixaxis_alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Sixaxis_alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Sixaxis_alpha_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Sixaxis_alpha_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_u_1'
                                        */
  11.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_u_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_u_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_u_2'
                                        */
  12.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_u_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_u_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_u_BT2'
                                        */
  13.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_u_BT2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_u_BT2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_omega_VSP1'
                                        */
  10.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_omega_VSP2'
                                        */
  15.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Sixaxis_u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Sixaxis_u_1'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Sixaxis_u_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Sixaxis_u_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Sixaxis_u_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Sixaxis_u_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Sixaxis_alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Sixaxis_alpha_2'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Sixaxis_alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Sixaxis_alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Sixaxis_alpha_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Sixaxis_alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Sixaxis_u_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Sixaxis_u_2'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Sixaxis_u_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Sixaxis_u_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Sixaxis_u_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Sixaxis_u_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Sixaxis_u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Sixaxis_u_BT'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Sixaxis_u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Sixaxis_u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Sixaxis_u_BT'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Sixaxis_u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Sixaxis_omega_VSP'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Sixaxis_omega_VSP'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Sixaxis_omega_VSP'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Sixaxis_omega_VSP'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Sixaxis_omega_VSP'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Sixaxis_omega_VSP'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/u_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/u_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/u_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/u_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/u_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_2'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/u_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/u_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/u_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/u_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/U_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/U_BT'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/U_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/U_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/U_BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/U_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/omega_VSP_2'
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

NI_ParamSizeWidth P_Flip_switch_T_sizes[] DataSection(".NIVS.defaultparamsizes")
  = {
  { sizeof(P_Flip_switch_T), 1 },

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
