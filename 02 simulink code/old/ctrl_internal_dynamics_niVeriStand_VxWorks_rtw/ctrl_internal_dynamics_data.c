/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define ctrl_internal_dynamics_P      ctrl_internal_dynamics_P DataSection(".NIVS.defaultparams")
#endif

/*
 * ctrl_internal_dynamics_data.c
 *
 * Code generation for model "ctrl_internal_dynamics".
 *
 * Model version              : 1.148
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Feb 25 09:52:00 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "ctrl_internal_dynamics.h"
#include "ctrl_internal_dynamics_private.h"

/* Block parameters (auto storage) */
P_ctrl_internal_dynamics_T ctrl_internal_dynamics_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory6'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory4'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory5'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory10'
                                        */
  0.01,                                /* Computed Parameter: DiscreteTimeIntegrator_gainval
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory7'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory8'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory9'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory11'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory12'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory13'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/timwe1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory14'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Memory15'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_p_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/Ctrl_K_p_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Ctrl_K_d_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Ctrl_K_d_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_e1_N'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta0_1_ctrl'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_e2_E'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta0_2_ctrl'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_e2_X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta0_3_ctrl'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_e2_Y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_u0'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_path_d_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_l_y1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_path_d_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_l_y2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_tau_r'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_reset_ctrl'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_tau_u'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_xc'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_tau_v'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_yc'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  10.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta_1_ctrl'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  11.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta_2_ctrl'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  12.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_eta_3_ctrl'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  13.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_nu_1_ctrl'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  14.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_nu_2_ctrl'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  15.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/HIL_nu_3_ctrl'
                                        */
  1.0                                  /* Expression: 1
                                        * Referenced by: '<Root>/timwe'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_ctrl_internal_dynamics_T_sizes[] DataSection(
  ".NIVS.defaultparamsizes") = {
  { sizeof(P_ctrl_internal_dynamics_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
