/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define ctrl_DP_mss_P                 ctrl_DP_mss_P DataSection(".NIVS.defaultparams")
#endif

/*
 * ctrl_DP_mss_data.c
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
#include "ctrl_DP_mss.h"
#include "ctrl_DP_mss_private.h"

/* Block parameters (auto storage) */
P_ctrl_DP_mss_T ctrl_DP_mss_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Constant'
                                        */
  0.3,                                 /* Expression: 0.3
                                        * Referenced by: '<S12>/Constant1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_K_p_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_K_p_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_K_p_y'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant8'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant10'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant6'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant11'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant7'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant9'
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
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S8>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S8>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S8>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S8>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_X_ref'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_Y_ref'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_PSI_ref'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S7>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S7>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S7>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S7>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_i_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_i_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_i_y'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Constant14'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Constant16'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Constant12'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Constant17'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Constant13'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Constant15'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Reset_integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Ctrl_K_d_X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Ctrl_K_d_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Ctrl_K_d_y'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant4'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant5'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant3'
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
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_tau_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_tau_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_tau_psi'
                                        */
  0.42,                                /* Expression: 0.42
                                        * Referenced by: '<S2>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  4.0,                                 /* Expression: portnum
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
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S12>/Bool_VSP_omega_on_off'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  5.0,                                 /* Expression: portnum
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
  6.0,                                 /* Expression: portnum
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
  0.0                                  /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_ctrl_DP_mss_T_sizes[] DataSection(".NIVS.defaultparamsizes")
  = {
  { sizeof(P_ctrl_DP_mss_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
