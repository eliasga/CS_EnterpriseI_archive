/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define ctrl_P_P                      ctrl_P_P DataSection(".NIVS.defaultparams")
#endif

/*
 * ctrl_P_data.c
 *
 * Code generation for model "ctrl_P".
 *
 * Model version              : 1.3
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Jan 27 16:34:41 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "ctrl_P.h"
#include "ctrl_P_private.h"

/* Block parameters (auto storage) */
P_ctrl_P_T ctrl_P_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/desired_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/desired_psi'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/desired_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/desired_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/desired_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/desired_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/error_psi_gain'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/error_psi_gain'
                                        */
  10.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/error_psi_gain'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/error_psi_gain'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/error_psi_gain'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/error_psi_gain'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<Root>/Gain'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_BT'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/u_BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_X'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_X'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/error_VSPu_gain'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/error_VSPu_gain'
                                        */
  11.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/error_VSPu_gain'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/error_VSPu_gain'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/error_VSPu_gain'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/error_VSPu_gain'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/desired_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/desired_X'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/desired_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/desired_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/desired_X'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/desired_X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/desired_Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/desired_Y'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/desired_Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/desired_Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/desired_Y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/desired_Y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/u_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_VSP1'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/u_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/u_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/u_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/u_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/u_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_VSP2'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/u_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/u_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/u_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/u_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<Root>/Gain2'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<Root>/Gain1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/error_alpha_gain'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/error_alpha_gain'
                                        */
  12.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/error_alpha_gain'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/error_alpha_gain'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/error_alpha_gain'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/error_alpha_gain'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/alpha_VSP1'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/alpha_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/alpha_VSP2'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/alpha_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/error_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/error_x'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/error_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/error_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/error_x'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/error_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/error_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/error_y'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/error_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/error_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/error_y'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/error_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/error_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/error_psi'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/error_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/error_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/error_psi'
                                        */
  0.0                                  /* Expression: btype
                                        * Referenced by: '<Root>/error_psi'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_ctrl_P_T_sizes[] DataSection(".NIVS.defaultparamsizes") = {
  { sizeof(P_ctrl_P_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
