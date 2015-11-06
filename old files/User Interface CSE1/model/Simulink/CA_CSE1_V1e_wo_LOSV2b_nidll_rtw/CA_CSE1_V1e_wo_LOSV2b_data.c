/*
 * CA_CSE1_V1e_wo_LOSV2b_data.c
 *
 * Real-Time Workshop code generation for Simulink model "CA_CSE1_V1e_wo_LOSV2b.mdl".
 *
 * Model Version              : 1.193
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Fri Sep 20 14:52:12 2013
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CA_CSE1_V1e_wo_LOSV2b.h"
#include "CA_CSE1_V1e_wo_LOSV2b_private.h"

/* Block parameters (auto storage) */
Parameters_CA_CSE1_V1e_wo_LOSV2 CA_CSE1_V1e_wo_LOSV2b_P = {
  0.0,                                 /* ControlMode_Value : '<S1>/Control Mode'
                                        */
  0.0,                                 /* u1_Value : '<S26>/u1'
                                        */
  1.0,                                 /* Accuracyu_1_Gain : '<S26>/Accuracy u_1'
                                        */
  0.0,                                 /* u2_Value : '<S26>/u2'
                                        */
  1.0,                                 /* Accuracyu_2_Gain : '<S26>/Accuracy u_2'
                                        */
  0.0,                                 /* u3_Value : '<S26>/u3'
                                        */
  1.0,                                 /* Accuracyu_3_Gain : '<S26>/Accuracy u_3'
                                        */
  0.0,                                 /* u4_Value : '<S26>/u4'
                                        */
  1.0,                                 /* Accuracyu_4_Gain : '<S26>/Accuracy u_4'
                                        */
  0.0,                                 /* u5_Value : '<S26>/u5'
                                        */
  1.0,                                 /* Accuracyu_5_Gain : '<S26>/Accuracy u_5'
                                        */
  0.0,                                 /* AccuracyBTpower_Value : '<S26>/Accuracy  BT power'
                                        */
  0.0,                                 /* AccuracyVSPspeed_Value : '<S26>/Accuracy  VSP speed'
                                        */
  0.0,                                 /* JS_L_Y_Value : '<S30>/JS_L_Y'
                                        */
  3.0518509475997192E-005,             /* Scaling_JS_L_Y_Gain : '<S30>/Scaling_JS_L_Y'
                                        */
  1.0,                                 /* PS3u_1_Gain : '<S9>/PS3 u_1'
                                        */
  0.0,                                 /* JS_L_X_Value : '<S30>/JS_L_X'
                                        */
  3.0518509475997192E-005,             /* Scaling_JS_L_X_Gain : '<S30>/Scaling_JS_L_X'
                                        */
  1.0,                                 /* PS3u_2_Gain : '<S9>/PS3 u_2'
                                        */
  0.0,                                 /* JS_R_Y_Value : '<S30>/JS_R_Y'
                                        */
  3.0518509475997192E-005,             /* Scaling_JS_R_Y_Gain : '<S30>/Scaling_JS_R_Y'
                                        */
  1.0,                                 /* PS3u_3_Gain : '<S9>/PS3 u_3'
                                        */
  0.0,                                 /* JS_R_X_Value : '<S30>/JS_R_X'
                                        */
  3.0518509475997192E-005,             /* Scaling_JS_R_X_Gain : '<S30>/Scaling_JS_R_X'
                                        */
  1.0,                                 /* PS3u_4_Gain : '<S9>/PS3 u_4'
                                        */
  0.0,                                 /* L2_Value : '<S30>/L2'
                                        */
  0.0,                                 /* R2_Value : '<S30>/R2'
                                        */
  1.0,                                 /* PS3u_5_Gain : '<S9>/PS3 u_5'
                                        */
  0.0,                                 /* PS3_BT_Power_Value : '<S28>/PS3_BT_Power'
                                        */
  0.0,                                 /* PS3_VSP_Speed_Value : '<S28>/PS3_VSP_Speed'
                                        */
  1.0,                                 /* K_e1_joystick_Value : '<S23>/K_e1_joystick'
                                        */
  1.0,                                 /* GainK_e1_joystick_Gain : '<S23>/Gain K_e1_joystick'
                                        */
  0.0,                                 /* Constant_Value : '<S23>/Constant'
                                        */
  1.0,                                 /* K_e2_joystick_Value : '<S23>/K_e2_joystick'
                                        */
  1.0,                                 /* GainK_e2_joystick_Gain : '<S23>/Gain K_e2_joystick'
                                        */
  1.0,                                 /* K_e3_joystick_Value : '<S23>/K_e3_joystick'
                                        */
  1.0,                                 /* GainK_e3_joystick_Gain : '<S23>/Gain K_e3_joystick'
                                        */
  1.0,                                 /* K_e4_joystick_Value : '<S23>/K_e4_joystick'
                                        */
  1.0,                                 /* GainK_e4_joystick_Gain : '<S23>/Gain K_e4_joystick'
                                        */
  1.0,                                 /* K_e5_joystick_Value : '<S23>/K_e5_joystick'
                                        */
  1.0,                                 /* GainK_e5_joystick_Gain : '<S23>/Gain K_e5_joystick'
                                        */
  1.0,                                 /* T_e11_Value : '<S24>/T_e11'
                                        */
  0.0,                                 /* T_e21_Value : '<S24>/T_e21'
                                        */
  0.055,                               /* l_y1_Value : '<S24>/l_y1'
                                        */
  0.0,                                 /* T_e12_Value : '<S24>/T_e12'
                                        */
  1.0,                                 /* T_e22_Value : '<S24>/T_e22'
                                        */
  0.425,                               /* l_x1_Value : '<S24>/l_x1'
                                        */
  -1.0,                                /* l_x1_Gain : '<S24>/-l_x1'
                                        */
  1.0,                                 /* T_e13_Value : '<S24>/T_e13'
                                        */
  0.0,                                 /* T_e23_Value : '<S24>/T_e23'
                                        */
  0.055,                               /* l_y2_Value : '<S24>/l_y2'
                                        */
  -1.0,                                /* l_y2_Gain : '<S24>/-l_y2'
                                        */
  0.0,                                 /* T_e14_Value : '<S24>/T_e14'
                                        */
  1.0,                                 /* T_e24_Value : '<S24>/T_e24'
                                        */
  0.425,                               /* l_x2_Value : '<S24>/l_x2'
                                        */
  -1.0,                                /* l_x2_Gain : '<S24>/-l_x2'
                                        */
  0.0,                                 /* T_e15_Value : '<S24>/T_e15'
                                        */
  1.0,                                 /* T_e25_Value : '<S24>/T_e25'
                                        */
  0.425,                               /* l_x3_Value : '<S24>/l_x3'
                                        */
  1.0,                                 /* Joysticktau_surge_Gain : '<S8>/Joystick tau_surge'
                                        */
  1.0,                                 /* Saturation1_UpperSat : '<S8>/Saturation1'
                                        */
  -1.0,                                /* Saturation1_LowerSat : '<S8>/Saturation1'
                                        */
  1.0,                                 /* Joysticktau_sway_Gain : '<S8>/Joystick tau_sway'
                                        */
  1.0,                                 /* Saturation2_UpperSat : '<S8>/Saturation2'
                                        */
  -1.0,                                /* Saturation2_LowerSat : '<S8>/Saturation2'
                                        */
  1.0,                                 /* Joysticktau_yaw_Gain : '<S8>/Joystick tau_yaw'
                                        */
  1.0,                                 /* Saturation3_UpperSat : '<S8>/Saturation3'
                                        */
  -1.0,                                /* Saturation3_LowerSat : '<S8>/Saturation3'
                                        */
  1.0,                                 /* Saturation_UpperSat : '<S8>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat : '<S8>/Saturation'
                                        */
  1.0,                                 /* Joysticku_1_Gain : '<S8>/Joystick u_1'
                                        */
  1.0,                                 /* Joysticku_2_Gain : '<S8>/Joystick u_2'
                                        */
  1.0,                                 /* Joysticku_3_Gain : '<S8>/Joystick u_3'
                                        */
  1.0,                                 /* Joysticku_4_Gain : '<S8>/Joystick u_4'
                                        */
  1.0,                                 /* Joysticku_5_Gain : '<S8>/Joystick u_5'
                                        */
  0.0,                                 /* Enableeta_dLPF_Value : '<S25>/Enable eta_d LPF'
                                        */
  0.0,                                 /* x_d_Value : '<S27>/x_d'
                                        */
  0.0,                                 /* y_d_Value : '<S27>/y_d'
                                        */
  0.0,                                 /* psi_d_Value : '<S27>/psi_d'
                                        */
  1.7453292519943295E-002,             /* Gain1_Gain : '<S29>/Gain1'
                                        */
  -0.1,                                /* TransferFcn_A : '<S25>/Transfer Fcn'
                                        */
  0.1,                                 /* TransferFcn_C : '<S25>/Transfer Fcn'
                                        */
  -0.1,                                /* TransferFcn1_A : '<S25>/Transfer Fcn1'
                                        */
  0.1,                                 /* TransferFcn1_C : '<S25>/Transfer Fcn1'
                                        */
  -0.1,                                /* TransferFcn2_A : '<S25>/Transfer Fcn2'
                                        */
  0.1,                                 /* TransferFcn2_C : '<S25>/Transfer Fcn2'
                                        */
  1.0,                                 /* eta_dDPN_Gain : '<S25>/eta_d DP N'
                                        */
  1.0,                                 /* eta_dDPE_Gain : '<S25>/eta_d DP E'
                                        */
  1.0,                                 /* eta_dDPPsi_Gain : '<S25>/eta_d DP Psi'
                                        */
  0.0,                                 /* ControllerInputSelector_Value : '<S4>/Controller Input Selector'
                                        */
  9.0,                                 /* QTMIn_P1 : '<S31>/QTM In'
                                        */
  1.0,                                 /* QTMIn_P2 : '<S31>/QTM In'
                                        */
  1.0,                                 /* QTMIn_P3 : '<S31>/QTM In'
                                        */
  -1.0,                                /* QTMIn_P4 : '<S31>/QTM In'
                                        */
  1.0,                                 /* QTMIn_P5 : '<S31>/QTM In'
                                        */
  1.0,                                 /* QTMIn_P6 : '<S31>/QTM In'
                                        */
  1.0,                                 /* QTMIn3_Gain : '<S31>/QTM In3'
                                        */
  0.001,                               /* mm2mx_Gain : '<S31>/mm2m x'
                                        */
  1.0,                                 /* QTMIn4_Gain : '<S31>/QTM In4'
                                        */
  0.001,                               /* mm2my_Gain : '<S31>/mm2m y'
                                        */
  1.0,                                 /* QTMIn6_Gain : '<S31>/QTM In6'
                                        */
  1.7453292519943295E-002,             /* d2ryaw_Gain : '<S31>/d2r yaw'
                                        */
  0.0,                                 /* EnableLinearSimulator_Value : '<S5>/Enable Linear Simulator'
                                        */
  1.0,                                 /* eta_surge_Gain : '<S4>/eta_surge'
                                        */
  1.0,                                 /* eta_sway_Gain : '<S4>/eta_sway'
                                        */
  1.0,                                 /* eta_yaw_Gain : '<S4>/eta_yaw'
                                        */
  1.0,                                 /* QTMIn8_Gain : '<S31>/QTM In8'
                                        */
  1.7453292519943295E-002,             /* d2rroll_Gain : '<S31>/d2r roll'
                                        */
  1.0,                                 /* QTMIn7_Gain : '<S31>/QTM In7'
                                        */
  1.7453292519943295E-002,             /* d2rpitch_Gain : '<S31>/d2r pitch'
                                        */

  /*  Constant1_Value : '<S31>/Constant1'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
  1.0,                                 /* QTMIn5_Gain : '<S31>/QTM In5'
                                        */
  0.001,                               /* mm2mz_Gain : '<S31>/mm2m z'
                                        */
  1.0,                                 /* nu_surge_Gain : '<S4>/nu_surge'
                                        */
  1.0,                                 /* nu_sway_Gain : '<S4>/nu_sway'
                                        */
  1.0,                                 /* nu_yaw_Gain : '<S4>/nu_yaw'
                                        */
  3.0,                                 /* Constant_Value_c : '<S10>/Constant'
                                        */
  1.0,                                 /* Saturation_UpperSat_m : '<S1>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat_f : '<S1>/Saturation'
                                        */
  1.0,                                 /* QTMIn9Residual_Gain : '<S31>/QTM In9 Residual'
                                        */
  5.7295779513082323E+001,             /* eta_dPsideg_Gain : '<S25>/eta_d Psi deg'
                                        */
  1.0,                                 /* psi_d_Gain : '<S2>/psi_d'
                                        */
  1.0,                                 /* x_d_Gain : '<S2>/x_d'
                                        */
  1.0,                                 /* y_d_Gain : '<S2>/y_d'
                                        */
  -1.0,                                /* SITzAI0_P1 : '<S3>/SIT zAI0'
                                        */
  1.0,                                 /* SITzAI0_P2 : '<S3>/SIT zAI0'
                                        */
  1.0,                                 /* SITzAI0_P3 : '<S3>/SIT zAI0'
                                        */
  -1.0,                                /* SITzAI0_P4 : '<S3>/SIT zAI0'
                                        */
  1.0,                                 /* SITzAI0_P5 : '<S3>/SIT zAI0'
                                        */
  1.0,                                 /* SITzAI0_P6 : '<S3>/SIT zAI0'
                                        */
  1.0,                                 /* BatteryBowThruster_Gain : '<S3>/Battery Bow Thruster'
                                        */
  -1.0,                                /* SITzAI1_P1 : '<S3>/SIT zAI1'
                                        */
  1.0,                                 /* SITzAI1_P2 : '<S3>/SIT zAI1'
                                        */
  2.0,                                 /* SITzAI1_P3 : '<S3>/SIT zAI1'
                                        */
  -1.0,                                /* SITzAI1_P4 : '<S3>/SIT zAI1'
                                        */
  1.0,                                 /* SITzAI1_P5 : '<S3>/SIT zAI1'
                                        */
  1.0,                                 /* SITzAI1_P6 : '<S3>/SIT zAI1'
                                        */
  1.0,                                 /* BatteryServo_Gain : '<S3>/Battery Servo'
                                        */
  -1.0,                                /* SITzAI2_P1 : '<S3>/SIT zAI2'
                                        */
  1.0,                                 /* SITzAI2_P2 : '<S3>/SIT zAI2'
                                        */
  3.0,                                 /* SITzAI2_P3 : '<S3>/SIT zAI2'
                                        */
  -1.0,                                /* SITzAI2_P4 : '<S3>/SIT zAI2'
                                        */
  1.0,                                 /* SITzAI2_P5 : '<S3>/SIT zAI2'
                                        */
  1.0,                                 /* SITzAI2_P6 : '<S3>/SIT zAI2'
                                        */
  1.0,                                 /* BatteryMain_Gain : '<S3>/Battery Main'
                                        */
  1.0,                                 /* QTMIn1FPS_Gain : '<S31>/QTM In1 FPS'
                                        */
  1.0,                                 /* QTMIn2Error_Gain : '<S31>/QTM In2 Error'
                                        */
  1.0,                                 /* u_1plant_Gain : '<S5>/u_1 plant'
                                        */
  1.0,                                 /* u_2plant_Gain : '<S5>/u_2 plant'
                                        */
  1.0,                                 /* u_3plant_Gain : '<S5>/u_3 plant'
                                        */
  1.0,                                 /* u_4plant_Gain : '<S5>/u_4 plant'
                                        */
  1.0,                                 /* u_5plant_Gain : '<S5>/u_5 plant'
                                        */
  1.0,                                 /* BTpowerlimitplant_Gain : '<S5>/BT power limit plant'
                                        */
  1.0,                                 /* VSPspeedplant_Gain : '<S5>/VSP speed plant'
                                        */
  0.0,                                 /* EnableCSE1_Value : '<S5>/Enable CSE1'
                                        */
  1.0,                                 /* SignalProbe_P1 : '<Root>/SignalProbe'
                                        */

  /*  Thruster_Command_DP_Y0 : '<S7>/Thruster_Command_DP'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
  0.0,                                 /* Integrator1_IC : '<S13>/Integrator1'
                                        */
  0.5,                                 /* BT_power_limit_Value : '<S7>/BT_power_limit'
                                        */
  0.0,                                 /* EnableFilter_Value : '<S7>/Enable Filter'
                                        */
  0.0,                                 /* Integrator_IC : '<S13>/Integrator'
                                        */
  1.0E+010,                            /* Saturation_UpperSat_g : '<S21>/Saturation'
                                        */
  -1.0E+010,                           /* Saturation_LowerSat_l : '<S21>/Saturation'
                                        */
  3.1415926535897931E+000,             /* Gain_Gain : '<S21>/Gain'
                                        */
  6.2831853071795862E+000,             /* Constant_Value_e : '<S21>/Constant'
                                        */
  1.0,                                 /* etaN_Gain : '<S11>/eta N'
                                        */
  1.0,                                 /* etaE_Gain : '<S11>/eta E'
                                        */
  1.0,                                 /* etaPsi_Gain : '<S11>/eta Psi'
                                        */
  1.0,                                 /* Reg_e_N_hil_Gain : '<S11>/Reg_e_N_hil'
                                        */
  1.0,                                 /* Reg_e_E_hil_Gain : '<S11>/Reg_e_E_hil'
                                        */
  1.0,                                 /* Reg_e_Psi_hil_Gain : '<S11>/Reg_e_Psi_hil'
                                        */
  0.0,                                 /* Reset_DP_integrator_Value : '<S11>/Reset_DP_integrator'
                                        */
  0.0,                                 /* Integrator_IC_d : '<S11>/Integrator'
                                        */
  0.0,                                 /* Integrator4_IC : '<S13>/Integrator4'
                                        */

  /*  Kd_Gain : '<S11>/Kd'
   */
  { 4.1280000000000010E+000, 0.0, 0.0, 0.0, 5.408, 1.6184000000000004E-001, 0.0,
    1.6184000000000004E-001, 4.4160000000000005E-001 },
  1.0,                                 /* Kd_scale_Value : '<S11>/Kd_scale'
                                        */
  1.0,                                 /* K_d1_Gain : '<S11>/K_d 1'
                                        */
  1.0,                                 /* K_d2_Gain : '<S11>/K_d 2'
                                        */
  1.0,                                 /* K_d3_Gain : '<S11>/K_d 3'
                                        */
  5.7295779513082323E+001,             /* K_d3deg_Gain : '<S11>/K_d 3 deg'
                                        */

  /*  Ki_Gain : '<S11>/Ki'
   */
  { 2.5800000000000007E-003, 0.0, 0.0, 0.0, 0.00338, 1.0115000000000002E-004,
    0.0, 1.0115000000000002E-004, 2.7600000000000004E-004 },
  1.0,                                 /* Ki_scale_Value : '<S11>/Ki_scale'
                                        */
  1.0,                                 /* K_i1_Gain : '<S11>/K_i 1'
                                        */
  1.0,                                 /* K_i2_Gain : '<S11>/K_i 2'
                                        */
  1.0,                                 /* K_i3_Gain : '<S11>/K_i 3'
                                        */
  5.7295779513082323E+001,             /* K_i3deg_Gain : '<S11>/K_i 3 deg'
                                        */
  1.0,                                 /* Kp_scale_Value : '<S11>/Kp_scale'
                                        */
  1.0E+010,                            /* Saturation_UpperSat_o : '<S17>/Saturation'
                                        */
  -1.0E+010,                           /* Saturation_LowerSat_n : '<S17>/Saturation'
                                        */
  3.1415926535897931E+000,             /* Gain_Gain_d : '<S17>/Gain'
                                        */
  6.2831853071795862E+000,             /* Constant_Value_g : '<S17>/Constant'
                                        */
  1.0E+010,                            /* Saturation_UpperSat_d : '<S16>/Saturation'
                                        */
  -1.0E+010,                           /* Saturation_LowerSat_h : '<S16>/Saturation'
                                        */
  3.1415926535897931E+000,             /* Gain_Gain_e : '<S16>/Gain'
                                        */
  6.2831853071795862E+000,             /* Constant_Value_i : '<S16>/Constant'
                                        */

  /*  Kp_Gain : '<S11>/Kp'
   */
  { 2.5800000000000006E-001, 0.0, 0.0, 0.0, 0.338, 1.0115000000000002E-002, 0.0,
    1.0115000000000002E-002, 2.7600000000000003E-002 },
  1.0,                                 /* K_p1_Gain : '<S11>/K_p 1'
                                        */
  1.0,                                 /* K_p2_Gain : '<S11>/K_p 2'
                                        */
  1.0,                                 /* K_p3_Gain : '<S11>/K_p 3'
                                        */
  5.7295779513082323E+001,             /* K_p3deg_Gain : '<S11>/K_p 3 deg'
                                        */
  5.7295779513082323E+001,             /* Reg_e_Psi_deg_Gain : '<S11>/Reg_e_Psi_deg'
                                        */
  5.7295779513082323E+001,             /* etaPsideg_Gain : '<S11>/eta Psi deg'
                                        */
  1.0,                                 /* DPtau_surge_Gain : '<S7>/DP tau_surge'
                                        */
  1.0,                                 /* DPtau_sway_Gain : '<S7>/DP tau_sway'
                                        */
  1.0,                                 /* DPtau_yaw_Gain : '<S7>/DP tau_yaw'
                                        */
  1.0,                                 /* K_e1_DP_Value : '<S12>/K_e1_DP'
                                        */
  1.0,                                 /* GainK_e1_DP_Gain : '<S12>/Gain K_e1_DP'
                                        */
  0.0,                                 /* Constant_Value_cb : '<S12>/Constant'
                                        */
  1.0,                                 /* K_e2_DP_Value : '<S12>/K_e2_DP'
                                        */
  1.0,                                 /* GainK_e2_DP_Gain : '<S12>/Gain K_e2_DP'
                                        */
  1.0,                                 /* K_e3_DP_Value : '<S12>/K_e3_DP'
                                        */
  1.0,                                 /* GainK_e3_DP_Gain : '<S12>/Gain K_e3_DP'
                                        */
  1.0,                                 /* K_e4_DP_Value : '<S12>/K_e4_DP'
                                        */
  1.0,                                 /* GainK_e4_DP_Gain : '<S12>/Gain K_e4_DP'
                                        */
  1.0,                                 /* K_e5_DP_Value : '<S12>/K_e5_DP'
                                        */
  1.0,                                 /* GainK_e5_DP_Gain : '<S12>/Gain K_e5_DP'
                                        */
  1.0,                                 /* T_e11_Value_p : '<S14>/T_e11'
                                        */
  0.0,                                 /* T_e21_Value_c : '<S14>/T_e21'
                                        */
  0.055,                               /* l_y1_Value_b : '<S14>/l_y1'
                                        */
  0.0,                                 /* T_e12_Value_i : '<S14>/T_e12'
                                        */
  1.0,                                 /* T_e22_Value_o : '<S14>/T_e22'
                                        */
  0.425,                               /* l_x1_Value_l : '<S14>/l_x1'
                                        */
  -1.0,                                /* l_x1_Gain_a : '<S14>/-l_x1'
                                        */
  1.0,                                 /* T_e13_Value_d : '<S14>/T_e13'
                                        */
  0.0,                                 /* T_e23_Value_i : '<S14>/T_e23'
                                        */
  0.055,                               /* l_y2_Value_o : '<S14>/l_y2'
                                        */
  -1.0,                                /* l_y2_Gain_j : '<S14>/-l_y2'
                                        */
  0.0,                                 /* T_e14_Value_o : '<S14>/T_e14'
                                        */
  1.0,                                 /* T_e24_Value_h : '<S14>/T_e24'
                                        */
  0.425,                               /* l_x2_Value_o : '<S14>/l_x2'
                                        */
  -1.0,                                /* l_x2_Gain_b : '<S14>/-l_x2'
                                        */
  0.0,                                 /* T_e15_Value_g : '<S14>/T_e15'
                                        */
  1.0,                                 /* T_e25_Value_f : '<S14>/T_e25'
                                        */
  0.425,                               /* l_x3_Value_h : '<S14>/l_x3'
                                        */
  1.0,                                 /* DPu_1_Gain : '<S7>/DP u_1'
                                        */
  1.0,                                 /* DPu_2_Gain : '<S7>/DP u_2'
                                        */
  1.0,                                 /* DPu_3_Gain : '<S7>/DP u_3'
                                        */
  1.0,                                 /* DPu_4_Gain : '<S7>/DP u_4'
                                        */
  1.0,                                 /* DPu_5_Gain : '<S7>/DP u_5'
                                        */

  /*  Gain1_Gain_m : '<S13>/Gain1'
   */
  { 1.6000000000000003E-001, 0.0, 0.0, 0.0, 1.6000000000000003E-001, 0.0, 0.0,
    0.0, 1.6000000000000003E-001 },
  0.0,                                 /* Integrator2_IC : '<S13>/Integrator2'
                                        */

  /*  Gain2_Gain : '<S13>/Gain2'
   */
  { 6.4000000000000012E-001, 0.0, 0.0, 0.0, 6.4000000000000012E-001, 0.0, 0.0,
    0.0, 6.4000000000000012E-001 },
  1.0E+010,                            /* Saturation_UpperSat_a : '<S22>/Saturation'
                                        */
  -1.0E+010,                           /* Saturation_LowerSat_fw : '<S22>/Saturation'
                                        */
  3.1415926535897931E+000,             /* Gain_Gain_g : '<S22>/Gain'
                                        */
  6.2831853071795862E+000,             /* Constant_Value_h : '<S22>/Constant'
                                        */

  /*  K4_Gain : '<S13>/K4'
   */
  { 0.1, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 1.0000000000000002E-002 },
  0.0,                                 /* Integrator3_IC : '<S13>/Integrator3'
                                        */

  /*  Gain6_Gain : '<S13>/Gain6'
   */
  { 2.0, 0.0, 0.0, 0.0, 7.0, 0.1, 0.0, 0.1, 0.5 },

  /*  Gain3_Gain : '<S13>/Gain3'
   */
  { 3.8759689922480620E-002, 0.0, 0.0, 0.0, 2.9913878026449566E-002,
    -1.0963002762229616E-002, 0.0, -1.0963002762229616E-002,
    3.6633662220796931E-001 },

  /*  K11_Gain : '<S13>/K11'
   */
  { -2.3400000000000003E+000, 0.0, 0.0, 0.0, -2.3400000000000003E+000, 0.0, 0.0,
    0.0, -2.3400000000000003E+000 },

  /*  K12_Gain : '<S13>/K12'
   */
  { 1.4400000000000002E+000, 0.0, 0.0, 0.0, 1.4400000000000002E+000, 0.0, 0.0,
    0.0, 1.4400000000000002E+000 },

  /*  K2_Gain : '<S13>/K2'
   */
  { 1.04, 0.0, 0.0, 0.0, 1.04, 0.0, 0.0, 0.0, 1.04 },

  /*  K3_Gain : '<S13>/K3'
   */
  { 0.1, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 1.0000000000000002E-002 },

  /*  invT_b_Gain : '<S13>/inv(T_b)'
   */
  { 0.01, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.01 },
  1.0,                                 /* Saturation_UpperSat_ga : '<S7>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat_o : '<S7>/Saturation'
                                        */
  0.4,                                 /* VSP_speeds_Value : '<S7>/VSP_speeds'
                                        */
  -1.0,                                /* SITOut5BT_P1 : '<S35>/SIT Out5 BT'
                                        */
  1.0,                                 /* SITOut5BT_P2 : '<S35>/SIT Out5 BT'
                                        */
  1.0,                                 /* SITOut5BT_P3 : '<S35>/SIT Out5 BT'
                                        */
  -1.0,                                /* SITOut5BT_P4 : '<S35>/SIT Out5 BT'
                                        */
  1.0,                                 /* SITOut5BT_P5 : '<S35>/SIT Out5 BT'
                                        */
  0.0,                                 /* SITOut5BT_P6 : '<S35>/SIT Out5 BT'
                                        */
  0.02,                                /* BT_D_Gain1_Gain : '<S35>/BT_D_Gain1'
                                        */
  0.05,                                /* BT_Power_Offset1_Value : '<S35>/BT_Power_Offset1'
                                        */
  0.02,                                /* BT_D_Gain2_Gain : '<S35>/BT_D_Gain2'
                                        */
  0.02,                                /* BT_L_Gain1_Gain : '<S35>/BT_L_Gain1'
                                        */
  -0.02,                               /* BT_L_Gain2_Gain : '<S35>/BT_L_Gain2'
                                        */
  0.05,                                /* BT_Power_Offset2_Value : '<S35>/BT_Power_Offset2'
                                        */
  0.05,                                /* BT_Power_Offset3_Value : '<S35>/BT_Power_Offset3'
                                        */
  0.0,                                 /* Constant_Value_ef : '<S35>/Constant'
                                        */
  0.0,                                 /* Constant1_Value_n : '<S35>/Constant1'
                                        */
  -1.0,                                /* Neg_Gain : '<S35>/Neg'
                                        */
  -1.0,                                /* SITOut1Servo1_P1 : '<S38>/SIT Out1 Servo1'
                                        */
  1.0,                                 /* SITOut1Servo1_P2 : '<S38>/SIT Out1 Servo1'
                                        */
  1.0,                                 /* SITOut1Servo1_P3 : '<S38>/SIT Out1 Servo1'
                                        */
  -1.0,                                /* SITOut1Servo1_P4 : '<S38>/SIT Out1 Servo1'
                                        */
  1.0,                                 /* SITOut1Servo1_P5 : '<S38>/SIT Out1 Servo1'
                                        */
  0.0,                                 /* SITOut1Servo1_P6 : '<S38>/SIT Out1 Servo1'
                                        */
  -1.0,                                /* SITOut2Servo2_P1 : '<S38>/SIT Out2 Servo2'
                                        */
  1.0,                                 /* SITOut2Servo2_P2 : '<S38>/SIT Out2 Servo2'
                                        */
  2.0,                                 /* SITOut2Servo2_P3 : '<S38>/SIT Out2 Servo2'
                                        */
  -1.0,                                /* SITOut2Servo2_P4 : '<S38>/SIT Out2 Servo2'
                                        */
  1.0,                                 /* SITOut2Servo2_P5 : '<S38>/SIT Out2 Servo2'
                                        */
  0.0,                                 /* SITOut2Servo2_P6 : '<S38>/SIT Out2 Servo2'
                                        */
  -1.0,                                /* SITOut3Servo3_P1 : '<S38>/SIT Out3 Servo3'
                                        */
  1.0,                                 /* SITOut3Servo3_P2 : '<S38>/SIT Out3 Servo3'
                                        */
  3.0,                                 /* SITOut3Servo3_P3 : '<S38>/SIT Out3 Servo3'
                                        */
  -1.0,                                /* SITOut3Servo3_P4 : '<S38>/SIT Out3 Servo3'
                                        */
  1.0,                                 /* SITOut3Servo3_P5 : '<S38>/SIT Out3 Servo3'
                                        */
  0.0,                                 /* SITOut3Servo3_P6 : '<S38>/SIT Out3 Servo3'
                                        */
  -1.0,                                /* SITOut4Servo4_P1 : '<S38>/SIT Out4 Servo4'
                                        */
  1.0,                                 /* SITOut4Servo4_P2 : '<S38>/SIT Out4 Servo4'
                                        */
  4.0,                                 /* SITOut4Servo4_P3 : '<S38>/SIT Out4 Servo4'
                                        */
  -1.0,                                /* SITOut4Servo4_P4 : '<S38>/SIT Out4 Servo4'
                                        */
  1.0,                                 /* SITOut4Servo4_P5 : '<S38>/SIT Out4 Servo4'
                                        */
  0.0,                                 /* SITOut4Servo4_P6 : '<S38>/SIT Out4 Servo4'
                                        */
  -1.0,                                /* SITOut6VSPSPort_P1 : '<S38>/SIT Out6 VSPS Port'
                                        */
  1.0,                                 /* SITOut6VSPSPort_P2 : '<S38>/SIT Out6 VSPS Port'
                                        */
  5.0,                                 /* SITOut6VSPSPort_P3 : '<S38>/SIT Out6 VSPS Port'
                                        */
  -1.0,                                /* SITOut6VSPSPort_P4 : '<S38>/SIT Out6 VSPS Port'
                                        */
  1.0,                                 /* SITOut6VSPSPort_P5 : '<S38>/SIT Out6 VSPS Port'
                                        */
  0.0,                                 /* SITOut6VSPSPort_P6 : '<S38>/SIT Out6 VSPS Port'
                                        */
  -1.0,                                /* SITOut7VSPSStarboard_P1 : '<S38>/SIT Out7 VSPS Starboard'
                                        */
  1.0,                                 /* SITOut7VSPSStarboard_P2 : '<S38>/SIT Out7 VSPS Starboard'
                                        */
  6.0,                                 /* SITOut7VSPSStarboard_P3 : '<S38>/SIT Out7 VSPS Starboard'
                                        */
  -1.0,                                /* SITOut7VSPSStarboard_P4 : '<S38>/SIT Out7 VSPS Starboard'
                                        */
  1.0,                                 /* SITOut7VSPSStarboard_P5 : '<S38>/SIT Out7 VSPS Starboard'
                                        */
  0.0,                                 /* SITOut7VSPSStarboard_P6 : '<S38>/SIT Out7 VSPS Starboard'
                                        */
  -1.0,                                /* x_Gain : '<S38>/-x'
                                        */
  -1.0,                                /* y_Gain : '<S38>/-y'
                                        */
  5.7295779513082323E+001,             /* Gain_Gain_k : '<S44>/Gain'
                                        */
  5.7295779513082323E+001,             /* Gain_Gain_o : '<S45>/Gain'
                                        */

  /*  Servo1_RowIdx : '<S38>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo1_ColIdx : '<S38>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo1_Table : '<S38>/Servo1'
   */
  { 0.06, 0.0495363, 0.043301, 0.06, 0.052446, 0.043301, 0.06, 0.0541518,
    0.043301 },

  /*  Servo2_RowIdx : '<S38>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo2_ColIdx : '<S38>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo2_Table : '<S38>/Servo2'
   */
  { 0.0386088, 0.0386088, 0.0386088, 0.0459941, 0.0477243, 0.0500953, 0.057,
    0.057, 0.057 },

  /*  Servo3_RowIdx : '<S38>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo3_ColIdx : '<S38>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo3_Table : '<S38>/Servo3'
   */
  { 0.0640809, 0.0640809, 0.0640809, 0.0539629, 0.0541315, 0.0556492, 0.0442664,
    0.0442664, 0.0442664 },

  /*  Servo4_RowIdx : '<S38>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo4_ColIdx : '<S38>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo4_Table : '<S38>/Servo4'
   */
  { 0.0602867, 0.0470489, 0.0403879, 0.0602867, 0.049747, 0.0403879, 0.0602867,
    0.0526138, 0.0403879 },
  -0.02,                               /* VPS_Speed_Gain_Gain : '<S38>/VPS_Speed_Gain'
                                        */
  0.05,                                /* VPS_Power_Offset_Value : '<S38>/VPS_Power_Offset'
                                        */
  1.0,                                 /* VSPSPort_Gain : '<S38>/VSPS Port'
                                        */
  1.0,                                 /* VSPSStarboard_Gain : '<S38>/VSPS Starboard'
                                        */
  1.0,                                 /* T_e11_Value_i : '<S37>/T_e11'
                                        */
  0.0,                                 /* T_e21_Value_p : '<S37>/T_e21'
                                        */
  0.055,                               /* l_y1_Value_a : '<S37>/l_y1'
                                        */
  0.0,                                 /* T_e12_Value_o : '<S37>/T_e12'
                                        */
  1.0,                                 /* T_e22_Value_p : '<S37>/T_e22'
                                        */
  0.425,                               /* l_x1_Value_j : '<S37>/l_x1'
                                        */
  -1.0,                                /* l_x1_Gain_f : '<S37>/-l_x1'
                                        */
  1.0,                                 /* T_e13_Value_l : '<S37>/T_e13'
                                        */
  0.0,                                 /* T_e23_Value_c : '<S37>/T_e23'
                                        */
  0.055,                               /* l_y2_Value_g : '<S37>/l_y2'
                                        */
  -1.0,                                /* l_y2_Gain_c : '<S37>/-l_y2'
                                        */
  0.0,                                 /* T_e14_Value_g : '<S37>/T_e14'
                                        */
  1.0,                                 /* T_e24_Value_i : '<S37>/T_e24'
                                        */
  0.425,                               /* l_x2_Value_f : '<S37>/l_x2'
                                        */
  -1.0,                                /* l_x2_Gain_j : '<S37>/-l_x2'
                                        */
  0.0,                                 /* T_e15_Value_c : '<S37>/T_e15'
                                        */
  1.0,                                 /* T_e25_Value_j : '<S37>/T_e25'
                                        */
  0.425,                               /* l_x3_Value_m : '<S37>/l_x3'
                                        */
  1.0,                                 /* K_e1_CSE1_Value : '<S36>/K_e1_CSE1'
                                        */
  1.0,                                 /* GainK_e1_CSE1_Gain : '<S36>/Gain K_e1_CSE1'
                                        */
  0.0,                                 /* Constant_Value_o : '<S36>/Constant'
                                        */
  1.0,                                 /* K_e2_CSE1_Value : '<S36>/K_e2_CSE1'
                                        */
  1.0,                                 /* GainK_e2_CSE1_Gain : '<S36>/Gain K_e2_CSE1'
                                        */
  1.0,                                 /* K_e3_CSE1_Value : '<S36>/K_e3_CSE1'
                                        */
  1.0,                                 /* GainK_e3_CSE1_Gain : '<S36>/Gain K_e3_CSE1'
                                        */
  1.0,                                 /* K_e4_CSE1_Value : '<S36>/K_e4_CSE1'
                                        */
  1.0,                                 /* GainK_e4_CSE1_Gain : '<S36>/Gain K_e4_CSE1'
                                        */
  1.0,                                 /* K_e5_CSE1_Value : '<S36>/K_e5_CSE1'
                                        */
  1.0,                                 /* GainK_e5_CSE1_Gain : '<S36>/Gain K_e5_CSE1'
                                        */
  1.0,                                 /* CSE1tau_surge_Gain : '<S33>/CSE1 tau_surge'
                                        */
  1.0,                                 /* CSE1tau_sway_Gain : '<S33>/CSE1 tau_sway'
                                        */
  1.0,                                 /* CSE1tau_yaw_Gain : '<S33>/CSE1 tau_yaw'
                                        */
  1.0,                                 /* Gainu_1_Gain : '<S47>/Gain u_1'
                                        */
  1.0,                                 /* Gainu_2_Gain : '<S47>/Gain u_2'
                                        */
  1.0,                                 /* Gainu_3_Gain : '<S47>/Gain u_3'
                                        */
  1.0,                                 /* Gainu_4_Gain : '<S47>/Gain u_4'
                                        */
  1.0,                                 /* GainBTpower_Gain : '<S47>/Gain BT power'
                                        */
  -1.0,                                /* Neg_Gain_o : '<S47>/Neg'
                                        */
  1.0,                                 /* Gainu_5_Gain : '<S47>/Gain u_5'
                                        */
  1.0,                                 /* tau_surge_hil_Gain : '<S47>/tau_surge_hil'
                                        */
  1.0,                                 /* tau_sway_hil_Gain : '<S47>/tau_sway_hil'
                                        */
  1.0,                                 /* tau_yaw_hil_Gain : '<S47>/tau_yaw_hil'
                                        */
  5.7295779513082323E+001,             /* VSP_angle_deg_port_Gain : '<S47>/VSP_angle_deg_port'
                                        */
  5.7295779513082323E+001,             /* VSP_angle_deg_stbd_Gain : '<S47>/VSP_angle_deg_stbd'
                                        */
  -1.9,                                /* N_r_Value : '<S48>/N_r'
                                        */
  -1.0,                                /* N_r_Gain : '<S48>/-N_r'
                                        */
  0.0313,                              /* N_v_Value : '<S48>/N_v'
                                        */
  -1.0,                                /* N_v_Gain : '<S48>/-N_v'
                                        */
  -0.72253,                            /* X_u_Value : '<S48>/X_u'
                                        */
  -1.0,                                /* X_u_Gain : '<S48>/-X_u'
                                        */
  -0.889656,                           /* Y_v_Value : '<S48>/Y_v'
                                        */
  -1.0,                                /* Y_v_Gain : '<S48>/-Y_v'
                                        */
  -7.25,                               /* Y_r_Value : '<S48>/Y_r'
                                        */
  -1.0,                                /* Y_vr_Gain : '<S48>/-Y_vr'
                                        */
  0.0,                                 /* D_L_12_Value : '<S48>/D_L_12'
                                        */
  0.0,                                 /* D_L_13_Value : '<S48>/D_L_13'
                                        */
  0.0,                                 /* D_L_21_Value : '<S48>/D_L_21'
                                        */
  0.0,                                 /* D_L_31_Value : '<S48>/D_L_31'
                                        */
  0.0,                                 /* psi_0_Value : '<S49>/psi_0'
                                        */
  0.0,                                 /* x_0_Value : '<S49>/x_0'
                                        */
  0.0,                                 /* y_0_Value : '<S49>/y_0'
                                        */
  0.0,                                 /* r_0_Value : '<S50>/r_0'
                                        */
  0.0,                                 /* u_0_Value : '<S50>/u_0'
                                        */
  0.0,                                 /* v_0_Value : '<S50>/v_0'
                                        */
  0.0,                                 /* ResetLinearSimulatorintegrator_ : '<S46>/Reset Linear Simulator integrator'
                                        */
  1.76,                                /* I_z_Value : '<S51>/I_z'
                                        */
  14.1,                                /* m_Value : '<S51>/m'
                                        */
  -2.0,                                /* X_udot_Value : '<S51>/X_udot'
                                        */
  0.0,                                 /* M_21_Value : '<S51>/M_21'
                                        */
  0.0,                                 /* M_31_Value : '<S51>/M_31'
                                        */
  0.0,                                 /* M_12_Value : '<S51>/M_12'
                                        */
  -10.0,                               /* Y_vdot_Value : '<S51>/Y_vdot'
                                        */
  0.03,                                /* x_g_Value : '<S51>/x_g'
                                        */
  0.0,                                 /* N_vdot_Value : '<S51>/N_vdot'
                                        */
  0.0,                                 /* M_13_Value : '<S51>/M_13'
                                        */
  0.0,                                 /* Y_rdot_Value : '<S51>/Y_rdot'
                                        */
  -1.0,                                /* N_rdot_Value : '<S51>/N_rdot'
                                        */
  1.0,                                 /* T_e11_Value_o : '<S57>/T_e11'
                                        */
  0.0,                                 /* T_e21_Value_l : '<S57>/T_e21'
                                        */
  0.055,                               /* l_y1_Value_n : '<S57>/l_y1'
                                        */
  0.0,                                 /* T_e12_Value_p : '<S57>/T_e12'
                                        */
  1.0,                                 /* T_e22_Value_k : '<S57>/T_e22'
                                        */
  0.425,                               /* l_x1_Value_d : '<S57>/l_x1'
                                        */
  -1.0,                                /* l_x1_Gain_o : '<S57>/-l_x1'
                                        */
  1.0,                                 /* T_e13_Value_k : '<S57>/T_e13'
                                        */
  0.0,                                 /* T_e23_Value_e : '<S57>/T_e23'
                                        */
  0.055,                               /* l_y2_Value_j : '<S57>/l_y2'
                                        */
  -1.0,                                /* l_y2_Gain_h : '<S57>/-l_y2'
                                        */
  0.0,                                 /* T_e14_Value_d : '<S57>/T_e14'
                                        */
  1.0,                                 /* T_e24_Value_g : '<S57>/T_e24'
                                        */
  0.425,                               /* l_x2_Value_k : '<S57>/l_x2'
                                        */
  -1.0,                                /* l_x2_Gain_c : '<S57>/-l_x2'
                                        */
  0.0,                                 /* T_e15_Value_p : '<S57>/T_e15'
                                        */
  1.0,                                 /* T_e25_Value_o : '<S57>/T_e25'
                                        */
  0.425,                               /* l_x3_Value_b : '<S57>/l_x3'
                                        */
  1.0,                                 /* K_e1_hil_Value : '<S55>/K_e1_hil'
                                        */
  1.0,                                 /* GainK_e1_hil_Gain : '<S55>/Gain K_e1_hil'
                                        */
  0.0,                                 /* Constant41_Value : '<S55>/Constant41'
                                        */
  1.0,                                 /* K_e2_hil_Value : '<S55>/K_e2_hil'
                                        */
  1.0,                                 /* GainK_e2_hil_Gain : '<S55>/Gain K_e2_hil'
                                        */
  1.0,                                 /* K_e3_hil_Value : '<S55>/K_e3_hil'
                                        */
  1.0,                                 /* GainK_e3_hil_Gain : '<S55>/Gain K_e3_hil'
                                        */
  1.0,                                 /* K_e4_hil_Value : '<S55>/K_e4_hil'
                                        */
  1.0,                                 /* GainK_e4_hil_Gain : '<S55>/Gain K_e4_hil'
                                        */
  1.0,                                 /* K_e5_hil_Value : '<S55>/K_e5_hil'
                                        */
  1.0,                                 /* GainK_e5_hil_Gain : '<S55>/Gain K_e5_hil'
                                        */
  0.1,                                 /* sampletime_WtEt : '<S56>/sample time'
                                        */
  0.0,                                 /* DelayInput2_X0 : '<S56>/Delay Input2'
                                        */
  0.0,                                 /* R31_Value : '<S52>/R31'
                                        */
  0.0,                                 /* R32_Value : '<S52>/R32'
                                        */
  0.0,                                 /* R13_Value : '<S52>/R13'
                                        */
  0.0,                                 /* R23_Value : '<S52>/R23'
                                        */
  1.0,                                 /* R33_Value : '<S52>/R33'
                                        */
  1.0,                                 /* eta_surge_hil_Gain : '<S34>/eta_surge_hil'
                                        */
  1.0,                                 /* eta_sway_hil_Gain : '<S34>/eta_sway_hil'
                                        */
  1.0,                                 /* eta_yaw_hil_Gain : '<S34>/eta_yaw_hil'
                                        */
  1.0,                                 /* etadot_surge_hil_Gain : '<S34>/etadot_surge_hil'
                                        */
  1.0,                                 /* etadot_sway_hil_Gain : '<S34>/etadot_sway_hil'
                                        */
  1.0,                                 /* etadot_yaw_hil_Gain : '<S34>/etadot_yaw_hil'
                                        */
  1.0,                                 /* nu_surge_hil_Gain : '<S34>/nu_surge_hil'
                                        */
  1.0,                                 /* nu_sway_hil_Gain : '<S34>/nu_sway_hil'
                                        */
  1.0                                  /* nu_yaw_hil_Gain : '<S34>/nu_yaw_hil'
                                        */
};
