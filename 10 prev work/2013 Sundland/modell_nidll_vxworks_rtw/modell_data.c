/*
 * modell_data.c
 *
 * Real-Time Workshop code generation for Simulink model "modell.mdl".
 *
 * Model Version              : 1.149
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Tue Mar 12 15:06:47 2013
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "modell.h"
#include "modell_private.h"

/* Block parameters (auto storage) */
Parameters_modell modell_P = {
  0.0,                                 /* reset_eta_hil_Value : '<S2>/reset_eta_hil'
                                        */
  0.0,                                 /* Constant_Value : '<Root>/Constant'
                                        */

  /*  initial_nu_hil_Value : '<S2>/initial_nu_hil'
   */
  { 0.0, 0.0, 0.0 },
  1.0,                                 /* nu_surge_hil_Gain : '<S2>/nu_surge_hil'
                                        */
  1.0,                                 /* nu_sway_hil_Gain : '<S2>/nu_sway_hil'
                                        */
  1.0,                                 /* nu_yaw_hil_Gain : '<S2>/nu_yaw_hil'
                                        */
  -0.1,                                /* TransferFcn_A : '<S5>/Transfer Fcn'
                                        */
  0.1,                                 /* TransferFcn_C : '<S5>/Transfer Fcn'
                                        */
  -0.1,                                /* TransferFcn1_A : '<S5>/Transfer Fcn1'
                                        */
  0.1,                                 /* TransferFcn1_C : '<S5>/Transfer Fcn1'
                                        */
  -0.1,                                /* TransferFcn2_A : '<S5>/Transfer Fcn2'
                                        */
  0.1,                                 /* TransferFcn2_C : '<S5>/Transfer Fcn2'
                                        */

  /*  initialposition_Value : '<S3>/initial position'
   */
  { 0.0, 0.0, 0.0 },
  0.0,                                 /* Integrator2_IC : '<S3>/Integrator2'
                                        */

  /*  T_zero_Value : '<S44>/T_zero'
   */
  { 0.0, 0.0, 0.0 },
  0.0,                                 /* Towlinelength_Value : '<S44>/Towline length'
                                        */

  /*  pos_diff_Value : '<S12>/pos_diff'
   */
  { 0.0, 0.0, 0.0 },

  /*  K_tow_Value : '<S44>/K_tow'
   */
  { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
  14000.0,                             /* T_cr_Value : '<S44>/T_cr'
                                        */

  /*  IC_Value : '<S12>/IC'
   */
  { 0.0, 0.0, 0.0 },
  0.0,                                 /* Integrator_IC : '<S13>/Integrator'
                                        */
  0.0,                                 /* zero_Value : '<S13>/zero'
                                        */
  0.0,                                 /* wavehat_IC : '<S8>/wave hat'
                                        */

  /*  C_w_Gain : '<S8>/C_w'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 1.0 },
  0.0,                                 /* eta_hat_IC : '<S8>/eta_hat'
                                        */
  0.0,                                 /* nu_hat_IC : '<S8>/nu_hat'
                                        */
  0.0,                                 /* wavehat_IC_l : '<S7>/wave hat'
                                        */

  /*  C_w_Gain_d : '<S7>/C_w'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 1.0 },
  0.0,                                 /* eta_hat_IC_g : '<S7>/eta_hat'
                                        */
  0.0,                                 /* nu_hat_IC_c : '<S7>/nu_hat'
                                        */
  2.0,                                 /* MODE_Value : '<Root>/MODE'
                                        */
  2.0,                                 /* Constant_Value_j : '<S14>/Constant'
                                        */
  0.0,                                 /* Constant2_Value : '<S33>/Constant2'
                                        */
  -3229.0,                             /* PS3_L_JS_Y_Value : '<S9>/PS3_L_JS_Y'
                                        */
  10000.0,                             /* limit_L_JS_Y_Value : '<S9>/limit_L_JS_Y'
                                        */
  3.0603501040519036E-005,             /* Gain1_Gain : '<S9>/Gain1'
                                        */
  0.0,                                 /* Constant2_Value_j : '<S32>/Constant2'
                                        */
  3229.0,                              /* PS3_L_JS_X_Value : '<S9>/PS3_L_JS_X'
                                        */
  10000.0,                             /* limit_L_JS_X_Value : '<S9>/limit_L_JS_X'
                                        */
  3.0603501040519036E-005,             /* Gain_Gain : '<S9>/Gain'
                                        */
  0.0,                                 /* Constant2_Value_f : '<S35>/Constant2'
                                        */
  -3229.0,                             /* PS3_R_JS_Y_Value : '<S9>/PS3_R_JS_Y'
                                        */
  10000.0,                             /* limit_R_JS_Y_Value : '<S9>/limit_R_JS_Y'
                                        */
  3.0603501040519036E-005,             /* Gain3_Gain : '<S9>/Gain3'
                                        */
  0.0,                                 /* Constant2_Value_o : '<S34>/Constant2'
                                        */
  3229.0,                              /* PS3_R_JS_X_Value : '<S9>/PS3_R_JS_X'
                                        */
  10000.0,                             /* limit_R_JS_X_Value : '<S9>/limit_R_JS_X'
                                        */
  3.0603501040519036E-005,             /* Gain2_Gain : '<S9>/Gain2'
                                        */
  -1.0,                                /* PS3_L2_Value : '<S9>/PS3_L2'
                                        */
  -179.0,                              /* Constant_Value_o : '<S9>/Constant'
                                        */
  5.5865921787709499E-003,             /* g1_Gain : '<S9>/g1'
                                        */
  179.0,                               /* PS3_R2_Value : '<S9>/PS3_R2'
                                        */
  -179.0,                              /* Constant1_Value : '<S9>/Constant1'
                                        */
  -5.5865921787709499E-003,            /* g2_Gain : '<S9>/g2'
                                        */
  0.0,                                 /* BT_saturation_Value : '<S5>/BT_saturation'
                                        */
  0.0,                                 /* VSP_speeds_Value : '<S5>/VSP_speeds'
                                        */

  /*  Ke1_Value : '<S4>/Ke^-1'
   */
  { 0.78125, 0.0, 0.0, 0.0, 0.0, 0.0, 9.5238095238095233E-001, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.78125, 0.0, 0.0, 0.0, 0.0, 0.0, 9.5238095238095233E-001, 0.0,
    0.0, 0.0, 0.0, 0.0, 4.6728971962616822E-001 },

  /*  Te_Value : '<S4>/Te^+'
   */
  { 4.9999999999999978E-001, 0.0, 4.9999999999999989E-001, 0.0, 0.0,
    1.6738377584216601E-002, 2.4811977472277608E-001, -1.6738377584216601E-002,
    2.4811977472277608E-001, 5.0376045055444796E-001, 1.1543708678770064E-001,
    -5.8767971455556722E-001, -1.1543708678770064E-001, -5.8767971455556711E-001,
    1.1753594291111342E+000 },
  1.0,                                 /* joystick_gain_surge_Gain : '<S4>/joystick_gain_surge'
                                        */
  1.0,                                 /* joystick_gain_sway_Gain : '<S4>/joystick_gain_sway'
                                        */
  1.0,                                 /* joystick_gain_yaw_Gain : '<S4>/joystick_gain_yaw'
                                        */
  1.0,                                 /* Saturation_UpperSat : '<S4>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat : '<S4>/Saturation'
                                        */
  0.4,                                 /* VSP_speeds_Value_n : '<S4>/VSP_speeds'
                                        */
  0.5,                                 /* BT_power_limit_Value : '<S4>/BT_power_limit'
                                        */

  /*  Ke1_Value_c : '<S11>/Ke^-1'
   */
  { 0.78125, 0.0, 0.0, 0.0, 0.0, 0.0, 9.5238095238095233E-001, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.78125, 0.0, 0.0, 0.0, 0.0, 0.0, 9.5238095238095233E-001, 0.0,
    0.0, 0.0, 0.0, 0.0, 4.6728971962616822E-001 },

  /*  Te_Value_h : '<S11>/Te^+'
   */
  { 4.9999999999999978E-001, 0.0, 4.9999999999999989E-001, 0.0, 0.0,
    1.6738377584216601E-002, 2.4811977472277608E-001, -1.6738377584216601E-002,
    2.4811977472277608E-001, 5.0376045055444796E-001, 1.1543708678770064E-001,
    -5.8767971455556722E-001, -1.1543708678770064E-001, -5.8767971455556711E-001,
    1.1753594291111342E+000 },
  0.4,                                 /* VSP_speeds_Value_k : '<S11>/VSP_speeds'
                                        */
  0.5,                                 /* BT_power_limit_Value_f : '<S11>/BT_power_limit'
                                        */
  1.0,                                 /* BT_power_Gain : '<S2>/BT_power'
                                        */

  /*  Constant_Value_e : '<S2>/Constant'
   */
  { 1.0, 0.0, 0.055, 0.0, 1.0, -0.425, 1.0, 0.0, -0.055, 0.0, 1.0, -0.425, 0.0,
    1.0, 0.415 },

  /*  Constant1_Value_o : '<S2>/Constant1'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },

  /*  D_Gain : '<S2>/D'
   */
  { 2.0, 0.0, 0.0, 0.0, 7.0, 0.1, 0.0, 0.1, 0.5 },
  1.0,                                 /* u1_hil_Gain : '<S2>/u1_hil'
                                        */
  1.0,                                 /* u2_hil_Gain : '<S2>/u2_hil'
                                        */
  1.0,                                 /* u3_hil_Gain : '<S2>/u3_hil'
                                        */
  1.0,                                 /* u4_hil_Gain : '<S2>/u4_hil'
                                        */
  0.1,                                 /* sampletime_WtEt : '<S21>/sample time'
                                        */
  0.0,                                 /* DelayInput2_X0 : '<S21>/Delay Input2'
                                        */
  -1.0,                                /* neg_Gain : '<S2>/neg'
                                        */
  1.0,                                 /* u5_hil_Gain : '<S2>/u5_hil'
                                        */
  1.0,                                 /* tau_surge_hil_Gain : '<S2>/tau_surge_hil'
                                        */
  1.0,                                 /* tau_sway_hil_Gain : '<S2>/tau_sway_hil'
                                        */
  1.0,                                 /* tau_yaw_hil_Gain : '<S2>/tau_yaw_hil'
                                        */
  1.0,                                 /* VIS_HIL_E_Gain : '<S2>/VIS_HIL_E'
                                        */
  1.0,                                 /* VIS_HIL_N_Gain : '<S2>/VIS_HIL_N'
                                        */
  1.0,                                 /* VIS_HIL_PIS_Gain : '<S2>/VIS_HIL_PIS'
                                        */
  5.7295779513082323E+001,             /* VSP_angle_deg_port_Gain : '<S2>/VSP_angle_deg_port'
                                        */
  5.7295779513082323E+001,             /* VSP_angle_deg_stbd_Gain : '<S2>/VSP_angle_deg_stbd'
                                        */

  /*  invM_Gain : '<S2>/inv(M)'
   */
  { 3.8759689922480620E-002, 0.0, 0.0, 0.0, 2.9913878026449566E-002,
    -1.0963002762229616E-002, 0.0, -1.0963002762229616E-002,
    3.6633662220796931E-001 },

  /*  D_Gain_d : '<S3>/D'
   */
  { 2.0, 0.0, 0.0, 0.0, 7.0, 0.1, 0.0, 0.1, 0.5 },
  2.0,                                 /* Saturation_UpperSat_n : '<S25>/Saturation'
                                        */
  -2.0,                                /* Saturation_LowerSat_j : '<S25>/Saturation'
                                        */
  1.5,                                 /* Saturation1_UpperSat : '<S25>/Saturation1'
                                        */
  -1.5,                                /* Saturation1_LowerSat : '<S25>/Saturation1'
                                        */
  1.5,                                 /* Saturation2_UpperSat : '<S25>/Saturation2'
                                        */
  -1.5,                                /* Saturation2_LowerSat : '<S25>/Saturation2'
                                        */
  0.0,                                 /* Integrator1_IC : '<S13>/Integrator1'
                                        */

  /*  invM_Gain_d : '<S3>/inv(M)'
   */
  { 3.8759689922480620E-002, 0.0, 0.0, 0.0, 2.9913878026449566E-002,
    -1.0963002762229616E-002, 0.0, -1.0963002762229616E-002,
    3.6633662220796931E-001 },
  -1.0,                                /* eta_d_E_Value : '<S5>/eta_d_E'
                                        */
  2.0,                                 /* eta_d_N_Value : '<S5>/eta_d_N'
                                        */
  0.0,                                 /* eta_d_Psi_Value : '<S5>/eta_d_Psi'
                                        */

  /*  A_w_Gain : '<S7>/A_w'
   */
  { 0.0, 0.0, 0.0, -6.4000000000000012E-001, -0.0, -0.0, 0.0, 0.0, 0.0, -0.0,
    -6.4000000000000012E-001, -0.0, 0.0, 0.0, 0.0, -0.0, -0.0,
    -6.4000000000000012E-001, 1.0, 0.0, 0.0, -1.6000000000000003E-001, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, -1.6000000000000003E-001, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    -1.6000000000000003E-001 },

  /*  D_Gain_h : '<S7>/D'
   */
  { 2.0, 0.0, 0.0, 0.0, 7.0, 0.1, 0.0, 0.1, 0.5 },

  /*  K_1_Gain : '<S7>/K_1'
   */
  { -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0,
    0.0, 0.0, 0.0 },

  /*  K_2_Gain : '<S7>/K_2'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  K_3_Gain : '<S7>/K_3'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  K_4_Gain : '<S7>/K_4'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
  0.0,                                 /* bias_hat_integrator_IC : '<S7>/bias_hat_integrator'
                                        */

  /*  M_inv_Gain : '<S7>/M_inv'
   */
  { 3.8759689922480620E-002, 0.0, 0.0, 0.0, 2.9913878026449566E-002,
    -1.0963002762229616E-002, 0.0, -1.0963002762229616E-002,
    3.6633662220796931E-001 },

  /*  T_inv_Gain : '<S7>/T_inv'
   */
  { 0.001, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.001 },

  /*  A_w_Gain_p : '<S8>/A_w'
   */
  { 0.0, 0.0, 0.0, -6.4000000000000012E-001, -0.0, -0.0, 0.0, 0.0, 0.0, -0.0,
    -6.4000000000000012E-001, -0.0, 0.0, 0.0, 0.0, -0.0, -0.0,
    -6.4000000000000012E-001, 1.0, 0.0, 0.0, -1.6000000000000003E-001, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, -1.6000000000000003E-001, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    -1.6000000000000003E-001 },

  /*  D_Gain_e : '<S8>/D'
   */
  { 2.0, 0.0, 0.0, 0.0, 7.0, 0.1, 0.0, 0.1, 0.5 },

  /*  K_1_Gain_k : '<S8>/K_1'
   */
  { -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0,
    0.0, 0.0, 0.0 },

  /*  K_2_Gain_m : '<S8>/K_2'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  K_3_Gain_f : '<S8>/K_3'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  K_4_Gain_m : '<S8>/K_4'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
  0.0,                                 /* bias_hat_integrator_IC_f : '<S8>/bias_hat_integrator'
                                        */

  /*  M_inv_Gain_h : '<S8>/M_inv'
   */
  { 3.8759689922480620E-002, 0.0, 0.0, 0.0, 2.9913878026449566E-002,
    -1.0963002762229616E-002, 0.0, -1.0963002762229616E-002,
    3.6633662220796931E-001 },

  /*  T_inv_Gain_d : '<S8>/T_inv'
   */
  { 0.001, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.001 },
  0.0,                                 /* WhiteNoise_Mean : '<S51>/White Noise'
                                        */
  1.0,                                 /* WhiteNoise_StdDev : '<S51>/White Noise'
                                        */
  23341.0,                             /* WhiteNoise_Seed : '<S51>/White Noise'
                                        */

  /*  Output_Gain : '<S51>/Output'
   */
  { 3.1622776601683794E-001, 3.1622776601683794E-001, 9.9999999999999992E-002 },

  /*  E_b_i_Gain : '<S13>/E_b_i'
   */
  { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 },

  /*  E_b_s_Gain : '<S13>/E_b_s'
   */
  { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 },

  /*  T_s_inv_Gain : '<S13>/T_s_inv'
   */
  { 0.001, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.001 },

  /*  T_i_inv_Gain : '<S13>/T_i_inv'
   */
  { 0.001, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.001 },
  1.0,                                 /* SignalProbe_P1 : '<Root>/SignalProbe'
                                        */
  1.0,                                 /* Saturation_UpperSat_c : '<S11>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat_e : '<S11>/Saturation'
                                        */
  1.0,                                 /* U1_Gain : '<S6>/U1'
                                        */
  1.0,                                 /* U2_Gain : '<S6>/U2'
                                        */
  1.0,                                 /* U3_Gain : '<S6>/U3'
                                        */
  1.0,                                 /* U4_Gain : '<S6>/U4'
                                        */
  1.0,                                 /* U5_Gain : '<S6>/U5'
                                        */
  0.0,                                 /* Integrator_IC_l : '<S15>/Integrator'
                                        */

  /*  Kd_Gain : '<S15>/Kd'
   */
  { 4.1280000000000010E+000, 0.0, 0.0, 0.0, 5.408, 1.6184000000000004E-001, 0.0,
    1.6184000000000004E-001, 4.4160000000000005E-001 },
  9.0909090909090895E-001,             /* Kd_scale_Value : '<S15>/Kd_scale'
                                        */

  /*  Ki_Gain : '<S15>/Ki'
   */
  { 2.5800000000000007E-003, 0.0, 0.0, 0.0, 0.00338, 1.0115000000000002E-004,
    0.0, 1.0115000000000002E-004, 2.7600000000000004E-004 },
  0.0,                                 /* Ki_scale_Value : '<S15>/Ki_scale'
                                        */
  1.0E+010,                            /* Saturation_UpperSat_i : '<S18>/Saturation'
                                        */
  -1.0E+010,                           /* Saturation_LowerSat_b : '<S18>/Saturation'
                                        */
  3.1415926535897931E+000,             /* Gain_Gain_i : '<S18>/Gain'
                                        */
  6.2831853071795862E+000,             /* Constant_Value_jb : '<S18>/Constant'
                                        */
  1.0,                                 /* Reg_e_N_hil_Gain : '<S15>/Reg_e_N_hil'
                                        */
  1.0,                                 /* Reg_e_E_hil_Gain : '<S15>/Reg_e_E_hil'
                                        */
  1.0,                                 /* Reg_e_Psi_hil_Gain : '<S15>/Reg_e_Psi_hil'
                                        */
  1.0E+010,                            /* Saturation_UpperSat_e : '<S17>/Saturation'
                                        */
  -1.0E+010,                           /* Saturation_LowerSat_n : '<S17>/Saturation'
                                        */
  3.1415926535897931E+000,             /* Gain_Gain_k : '<S17>/Gain'
                                        */
  6.2831853071795862E+000,             /* Constant_Value_f : '<S17>/Constant'
                                        */

  /*  Kp_Gain : '<S15>/Kp'
   */
  { 2.5800000000000006E-001, 0.0, 0.0, 0.0, 0.338, 1.0115000000000002E-002, 0.0,
    1.0115000000000002E-002, 2.7600000000000003E-002 },
  5.1948051948051899E-001,             /* Kp_scale_Value : '<S15>/Kp_scale'
                                        */
  1U,                                  /* Constant_Value_ow : '<S52>/Constant'
                                        */
  1U,                                  /* SwitchControl_Threshold : '<S52>/SwitchControl'
                                        */
  1U,                                  /* Constant_Value_b : '<S53>/Constant'
                                        */
  0U                                   /* SwitchControl_Threshold_a : '<S53>/SwitchControl'
                                        */
};
