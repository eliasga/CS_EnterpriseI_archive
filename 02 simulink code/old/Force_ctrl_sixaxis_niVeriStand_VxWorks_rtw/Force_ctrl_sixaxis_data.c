/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define Force_ctrl_sixaxis_P          Force_ctrl_sixaxis_P DataSection(".NIVS.defaultparams")
#endif

/*
 * Force_ctrl_sixaxis_data.c
 *
 * Code generation for model "Force_ctrl_sixaxis".
 *
 * Model version              : 1.7
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Feb 25 10:55:22 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Force_ctrl_sixaxis.h"
#include "Force_ctrl_sixaxis_private.h"

/* Block parameters (auto storage) */
P_Force_ctrl_sixaxis_T Force_ctrl_sixaxis_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Sixaxis_alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Sixaxis_alpha_1'
                                        */
  1.0,                                 /* Expression: portnum
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
                                        * Referenced by: '<Root>/Sixaxis_u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Sixaxis_u_1'
                                        */
  2.0,                                 /* Expression: portnum
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
  4.0,                                 /* Expression: portnum
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
  5.0,                                 /* Expression: portnum
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
                                        * Referenced by: '<Root>/VSP_on'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/VSP_on'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/VSP_on'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/VSP_on'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/VSP_on'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/VSP_on'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Force_ctrl_U_bt'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Force_ctrl_U_bt'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Force_ctrl_U_bt'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Force_ctrl_U_bt'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Force_ctrl_U_bt'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Force_ctrl_U_bt'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_1'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_2'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Force_ctrl_omega_VSP_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Force_ctrl_U_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Force_ctrl_U_1'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Force_ctrl_U_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Force_ctrl_U_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Force_ctrl_U_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Force_ctrl_U_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Force_ctrl_U_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Force_ctrl_U_2'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Force_ctrl_U_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Force_ctrl_U_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Force_ctrl_U_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Force_ctrl_U_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Force_ctrl_alpah_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Force_ctrl_alpah_1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Force_ctrl_alpah_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Force_ctrl_alpah_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Force_ctrl_alpah_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Force_ctrl_alpah_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Force_ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Force_ctrl_alpha_2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Force_ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Force_ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Force_ctrl_alpha_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Force_ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/force_ctrl_tau_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/force_ctrl_tau_x'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/force_ctrl_tau_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/force_ctrl_tau_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/force_ctrl_tau_x'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/force_ctrl_tau_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/force_ctrl_tau_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/force_ctrl_tau_y'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/force_ctrl_tau_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/force_ctrl_tau_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/force_ctrl_tau_y'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/force_ctrl_tau_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/force_ctrl_tau_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/force_ctrl_tau_psi'
                                        */
  10.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/force_ctrl_tau_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/force_ctrl_tau_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/force_ctrl_tau_psi'
                                        */
  0.0                                  /* Expression: btype
                                        * Referenced by: '<Root>/force_ctrl_tau_psi'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_Force_ctrl_sixaxis_T_sizes[] DataSection(
  ".NIVS.defaultparamsizes") = {
  { sizeof(P_Force_ctrl_sixaxis_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
