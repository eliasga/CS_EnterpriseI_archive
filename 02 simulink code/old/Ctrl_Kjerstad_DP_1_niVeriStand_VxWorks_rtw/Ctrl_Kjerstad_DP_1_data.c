/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define Ctrl_Kjerstad_DP_1_P          Ctrl_Kjerstad_DP_1_P DataSection(".NIVS.defaultparams")
#endif

/*
 * Ctrl_Kjerstad_DP_1_data.c
 *
 * Code generation for model "Ctrl_Kjerstad_DP_1".
 *
 * Model version              : 1.8
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Feb 04 12:24:04 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Ctrl_Kjerstad_DP_1.h"
#include "Ctrl_Kjerstad_DP_1_private.h"

/* Block parameters (auto storage) */
P_Ctrl_Kjerstad_DP_1_T Ctrl_Kjerstad_DP_1_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S11>/Constant'
                                        */
  0.3,                                 /* Expression: 0.3
                                        * Referenced by: '<S11>/Constant1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/Ctrl_K_p_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/Ctrl_K_p_psi'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/Ctrl_K_p_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/Ctrl_K_p_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/Ctrl_K_p_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/Ctrl_K_p_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/Ctrl_K_p_x'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/Ctrl_K_p_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/Ctrl_K_p_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/Ctrl_K_p_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/Ctrl_K_p_y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/Ctrl_K_p_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/Ctrl_K_p_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/Ctrl_K_p_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/Ctrl_K_p_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_ON//OFF'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_ON//OFF'
                                        */
  10.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_ON//OFF'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_ON//OFF'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_ON//OFF'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_ON//OFF'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_d_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_d_X'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_d_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_d_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_d_X'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_d_X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_d_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_d_psi'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_d_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_d_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_d_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_d_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_d_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_d_y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_d_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_d_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_d_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_d_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_u_surge'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_v_sway'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_r_yawrate'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/Ctrl_K_i_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/Ctrl_K_i_psi'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/Ctrl_K_i_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/Ctrl_K_i_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/Ctrl_K_i_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/Ctrl_K_i_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/Ctrl_K_i_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/Ctrl_K_i_x'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/Ctrl_K_i_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/Ctrl_K_i_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/Ctrl_K_i_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/Ctrl_K_i_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/Ctrl_K_i_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/Ctrl_K_i_y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/Ctrl_K_i_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/Ctrl_K_i_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/Ctrl_K_i_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/Ctrl_K_i_y'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Integrator'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/CTRL_tau_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/CTRL_tau_x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/CTRL_tau_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/CTRL_tau_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/CTRL_tau_x'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/CTRL_tau_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/CTRL_tau_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/CTRL_tau_y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/CTRL_tau_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/CTRL_tau_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/CTRL_tau_y'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/CTRL_tau_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/CTRL_tau_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/CTRL_tau_psi'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/CTRL_tau_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/CTRL_tau_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/CTRL_tau_psi'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/CTRL_tau_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/CTRL_psi_ref'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/CTRL_psi_ref'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/CTRL_psi_ref'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/CTRL_psi_ref'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/CTRL_psi_ref'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/CTRL_psi_ref'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/CTRL_x_ref'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/CTRL_x_ref'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/CTRL_x_ref'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/CTRL_x_ref'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/CTRL_x_ref'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/CTRL_x_ref'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/CTRL_y_ref'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/CTRL_y_ref'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/CTRL_y_ref'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/CTRL_y_ref'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/CTRL_y_ref'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/CTRL_y_ref'
                                        */
  0.42,                                /* Expression: 0.42
                                        * Referenced by: '<S2>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  10.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  11.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S11>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S11>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S11>/Bool_VSP_omega_on_off'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S11>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S11>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S11>/Bool_VSP_omega_on_off'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  12.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  13.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/omega_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/omega_d'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/omega_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/omega_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/omega_d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/omega_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/zeta'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/zeta'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/zeta'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/zeta'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/zeta'
                                        */
  1.0                                  /* Expression: btype
                                        * Referenced by: '<S1>/zeta'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_Ctrl_Kjerstad_DP_1_T_sizes[] DataSection(
  ".NIVS.defaultparamsizes") = {
  { sizeof(P_Ctrl_Kjerstad_DP_1_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
