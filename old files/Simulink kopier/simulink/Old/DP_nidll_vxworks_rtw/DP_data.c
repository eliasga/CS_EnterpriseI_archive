/*
 * DP_data.c
 *
 * Real-Time Workshop code generation for Simulink model "DP.mdl".
 *
 * Model Version              : 1.21
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 18:56:13 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DP.h"
#include "DP_private.h"

/* Block parameters (auto storage) */
Parameters_DP DP_P = {
  0.0,                                 /* ControllerInputSelector_Value : '<S4>/Controller Input Selector'
                                        */
  9.0,                                 /* QTMIn_P1 : '<S40>/QTM In'
                                        */
  1.0,                                 /* QTMIn_P2 : '<S40>/QTM In'
                                        */
  1.0,                                 /* QTMIn_P3 : '<S40>/QTM In'
                                        */
  -1.0,                                /* QTMIn_P4 : '<S40>/QTM In'
                                        */
  1.0,                                 /* QTMIn_P5 : '<S40>/QTM In'
                                        */
  1.0,                                 /* QTMIn_P6 : '<S40>/QTM In'
                                        */
  1.0,                                 /* QTMIn2Error_Gain : '<S40>/QTM In2 Error'
                                        */
  1.0,                                 /* QTMIn9Residual_Gain : '<S40>/QTM In9 Residual'
                                        */
  1.0,                                 /* QTMIn3_Gain : '<S40>/QTM In3'
                                        */
  0.001,                               /* mm2mx_Gain : '<S40>/mm2m x'
                                        */
  1.0,                                 /* QTMIn4_Gain : '<S40>/QTM In4'
                                        */
  0.001,                               /* mm2my_Gain : '<S40>/mm2m y'
                                        */
  1.0,                                 /* QTMIn6_Gain : '<S40>/QTM In6'
                                        */
  1.7453292519943295E-002,             /* d2ryaw_Gain : '<S40>/d2r yaw'
                                        */
  0.0,                                 /* EnableLinearSimulator_Value : '<S5>/Enable Linear Simulator'
                                        */
  1.0,                                 /* etadot_surge_Gain : '<S4>/etadot_surge'
                                        */
  1.0,                                 /* etadot_sway_Gain : '<S4>/etadot_sway'
                                        */
  1.0,                                 /* etadot_yaw_Gain : '<S4>/etadot_yaw'
                                        */
  1.0,                                 /* eta_surge_Gain : '<S4>/eta_surge'
                                        */
  1.0,                                 /* eta_sway_Gain : '<S4>/eta_sway'
                                        */
  1.0,                                 /* eta_yaw_Gain : '<S4>/eta_yaw'
                                        */
  1.0,                                 /* QTMIn8_Gain : '<S40>/QTM In8'
                                        */
  1.7453292519943295E-002,             /* d2rroll_Gain : '<S40>/d2r roll'
                                        */
  1.0,                                 /* QTMIn7_Gain : '<S40>/QTM In7'
                                        */
  1.7453292519943295E-002,             /* d2rpitch_Gain : '<S40>/d2r pitch'
                                        */

  /*  Constant1_Value : '<S40>/Constant1'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
  1.0,                                 /* QTMIn5_Gain : '<S40>/QTM In5'
                                        */
  0.001,                               /* mm2mz_Gain : '<S40>/mm2m z'
                                        */
  1.0,                                 /* nu_surge_Gain : '<S4>/nu_surge'
                                        */
  1.0,                                 /* nu_sway_Gain : '<S4>/nu_sway'
                                        */
  1.0,                                 /* nu_yaw_Gain : '<S4>/nu_yaw'
                                        */
  0.0,                                 /* x_d_Value : '<S38>/x_d'
                                        */
  1.0,                                 /* eta_dDPN_Gain : '<S37>/eta_d DP N'
                                        */
  0.0,                                 /* y_d_Value : '<S38>/y_d'
                                        */
  1.0,                                 /* eta_dDPE_Gain : '<S37>/eta_d DP E'
                                        */
  0.0,                                 /* psi_d_Value : '<S38>/psi_d'
                                        */
  1.7453292519943295E-002,             /* Gain1_Gain : '<S39>/Gain1'
                                        */
  1.0,                                 /* eta_dDPPsi_Gain : '<S37>/eta_d DP Psi'
                                        */
  0.0,                                 /* ControlMode_Value : '<S1>/Control Mode'
                                        */
  0.0,                                 /* AS_LY_Value : '<S7>/AS_LY'
                                        */
  3.0518509475997192E-005,             /* ScalingLY_Gain : '<S7>/ScalingLY'
                                        */
  1.0,                                 /* PS3u_1_Gain : '<S8>/PS3 u_1'
                                        */
  0.0,                                 /* AS_LX_Value : '<S7>/AS_LX'
                                        */
  3.0518509475997192E-005,             /* ScalingLX_Gain : '<S7>/ScalingLX'
                                        */
  1.0,                                 /* PS3u_2_Gain : '<S8>/PS3 u_2'
                                        */
  0.0,                                 /* AS_RY_Value : '<S7>/AS_RY'
                                        */
  3.0518509475997192E-005,             /* ScalingRY_Gain : '<S7>/ScalingRY'
                                        */
  1.0,                                 /* PS3u_3_Gain : '<S8>/PS3 u_3'
                                        */
  0.0,                                 /* AS_RX_Value : '<S7>/AS_RX'
                                        */
  3.0518509475997192E-005,             /* Scaling_RX_Gain : '<S7>/Scaling_RX'
                                        */
  1.0,                                 /* PS3u_4_Gain : '<S8>/PS3 u_4'
                                        */
  0.0,                                 /* L2_Value : '<S7>/L2'
                                        */
  0.0,                                 /* R2_Value : '<S7>/R2'
                                        */
  1.0,                                 /* PS3u_5_Gain : '<S8>/PS3 u_5'
                                        */
  0.0,                                 /* PS3_BT_Power_Value : '<S7>/PS3_BT_Power'
                                        */
  0.0,                                 /* PS3_VSP_Speed_Value : '<S7>/PS3_VSP_Speed'
                                        */
  1.0,                                 /* T_e11_Value : '<S36>/T_e11'
                                        */
  0.0,                                 /* T_e21_Value : '<S36>/T_e21'
                                        */
  0.055,                               /* l_y1_Value : '<S36>/l_y1'
                                        */
  0.0,                                 /* T_e12_Value : '<S36>/T_e12'
                                        */
  1.0,                                 /* T_e22_Value : '<S36>/T_e22'
                                        */
  0.45,                                /* l_x1_Value : '<S36>/l_x1'
                                        */
  -1.0,                                /* l_x1_Gain : '<S36>/-l_x1'
                                        */
  1.0,                                 /* T_e13_Value : '<S36>/T_e13'
                                        */
  0.0,                                 /* T_e23_Value : '<S36>/T_e23'
                                        */
  0.055,                               /* l_y2_Value : '<S36>/l_y2'
                                        */
  -1.0,                                /* l_y2_Gain : '<S36>/-l_y2'
                                        */
  0.0,                                 /* T_e14_Value : '<S36>/T_e14'
                                        */
  1.0,                                 /* T_e24_Value : '<S36>/T_e24'
                                        */
  0.45,                                /* l_x2_Value : '<S36>/l_x2'
                                        */
  -1.0,                                /* l_x2_Gain : '<S36>/-l_x2'
                                        */
  0.0,                                 /* T_e15_Value : '<S36>/T_e15'
                                        */
  1.0,                                 /* T_e25_Value : '<S36>/T_e25'
                                        */
  0.385,                               /* l_x3_Value : '<S36>/l_x3'
                                        */
  1.0E+010,                            /* Saturation_UpperSat : '<S13>/Saturation'
                                        */
  -1.0E+010,                           /* Saturation_LowerSat : '<S13>/Saturation'
                                        */
  3.1415926535897931E+000,             /* Gain_Gain : '<S13>/Gain'
                                        */
  6.2831853071795862E+000,             /* Constant_Value : '<S13>/Constant'
                                        */
  1.0E+010,                            /* Saturation_UpperSat_j : '<S12>/Saturation'
                                        */
  -1.0E+010,                           /* Saturation_LowerSat_g : '<S12>/Saturation'
                                        */
  3.1415926535897931E+000,             /* Gain_Gain_i : '<S12>/Gain'
                                        */
  6.2831853071795862E+000,             /* Constant_Value_i : '<S12>/Constant'
                                        */

  /*  Kp_Gain : '<S9>/Kp'
   */
  { 2.5800000000000006E-001, 0.0, 0.0, 0.0, 0.338, 1.0115000000000002E-002, 0.0,
    1.0115000000000002E-002, 2.7600000000000003E-002 },
  1.0,                                 /* K_p_surge_scale_Gain : '<S9>/K_p_surge_scale'
                                        */
  1.0,                                 /* K_p_sway_scale_Gain : '<S9>/K_p_sway_scale'
                                        */
  1.0,                                 /* K_p_yaw_scale_Gain : '<S9>/K_p_yaw_scale'
                                        */
  0.0,                                 /* Reset_DP_integrator_Value : '<S9>/Reset_DP_integrator'
                                        */
  0.0,                                 /* Integrator_IC : '<S9>/Integrator'
                                        */

  /*  Ki_Gain : '<S9>/Ki'
   */
  { 2.5800000000000007E-003, 0.0, 0.0, 0.0, 0.00338, 1.0115000000000002E-004,
    0.0, 1.0115000000000002E-004, 2.7600000000000004E-004 },
  1.0,                                 /* K_i_surge_scale_Gain : '<S9>/K_i_surge_scale'
                                        */
  1.0,                                 /* K_i_sway_scale_Gain : '<S9>/K_i_sway_scale'
                                        */
  1.0,                                 /* K_i_yaw_scale_Gain : '<S9>/K_i_yaw_scale'
                                        */

  /*  Kd_Gain : '<S9>/Kd'
   */
  { 4.1280000000000010E+000, 0.0, 0.0, 0.0, 5.408, 1.6184000000000004E-001, 0.0,
    1.6184000000000004E-001, 4.4160000000000005E-001 },
  1.0,                                 /* K_d_surge_scale_Gain : '<S9>/K_d_surge_scale'
                                        */
  1.0,                                 /* K_d_sway_scale_Gain : '<S9>/K_d_sway_scale'
                                        */
  1.0,                                 /* K_d_yaw_scale_Gain : '<S9>/K_d_yaw_scale'
                                        */
  -0.001,                              /* DeadZone_Start : '<S16>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End : '<S16>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value_b : '<S21>/Constant'
                                        */
  0.0,                                 /* Constant_Value_p : '<S22>/Constant'
                                        */

  /*  f_10_XData : '<S16>/f_1 < 0'
   */
  { -1.324, -1.169, -0.919, -0.703, -0.535, -0.292, -0.165, -0.06, 0.0 },

  /*  f_10_YData : '<S16>/f_1 < 0'
   */
  { -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2089 },
  0.0,                                 /* f_10_Value : '<S16>/f_1 = 0'
                                        */

  /*  f_10_XData_f : '<S16>/f_1 > 0'
   */
  { 0.0, 0.051, 0.153, 0.308, 0.48, 0.663, 0.911, 1.057, 1.221, 1.374 },

  /*  f_10_YData_o : '<S16>/f_1 > 0'
   */
  { 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 },
  -0.001,                              /* DeadZone_Start_e : '<S17>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End_p : '<S17>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value_l : '<S24>/Constant'
                                        */
  0.0,                                 /* Constant_Value_f : '<S25>/Constant'
                                        */
  0.0,                                 /* Constant_Value_a : '<S26>/Constant'
                                        */

  /*  f_20_XData : '<S17>/f_2 < 0'
   */
  { -0.766, -0.649, -0.522, -0.411, -0.323, -0.246, -0.156, -0.075, -0.018,
    -0.006, 0.0 },

  /*  f_20_YData : '<S17>/f_2 < 0'
   */
  { -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, -0.0466 },
  0.0,                                 /* f_20_Value : '<S17>/f_2 = 0'
                                        */

  /*  f_20_XData_d : '<S17>/f_2 > 0'
   */
  { 0.0, 0.052, 0.207, 0.331, 0.509, 0.689, 0.829, 0.961, 1.079, 1.12 },

  /*  f_20_YData_l : '<S17>/f_2 > 0'
   */
  { 0.1665, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },
  -0.001,                              /* DeadZone_Start_o : '<S18>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End_h : '<S18>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value_n : '<S27>/Constant'
                                        */
  0.0,                                 /* Constant_Value_j : '<S28>/Constant'
                                        */

  /*  f_30_XData : '<S18>/f_3 < 0'
   */
  { -1.291, -1.088, -0.885, -0.618, -0.403, -0.211, -0.034, 0.0 },

  /*  f_30_YData : '<S18>/f_3 < 0'
   */
  { -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2809 },
  0.0,                                 /* f_30_Value : '<S18>/f_3 = 0'
                                        */

  /*  f_30_XData_h : '<S18>/f_3 > 0'
   */
  { 0.0, 0.014, 0.04, 0.147, 0.302, 0.494, 0.68, 0.968, 1.111, 1.289, 1.339 },

  /*  f_30_YData_a : '<S18>/f_3 > 0'
   */
  { 0.0452, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },
  -0.001,                              /* DeadZone_Start_a : '<S19>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End_k : '<S19>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value_h : '<S30>/Constant'
                                        */
  0.0,                                 /* Constant_Value_ff : '<S31>/Constant'
                                        */

  /*  f_40_XData : '<S19>/f_4 < 0'
   */
  { -1.249, -1.225, -1.094, -0.896, -0.696, -0.502, -0.314, -0.169, -0.042, 0.0
  },

  /*  f_40_YData : '<S19>/f_4 < 0'
   */
  { -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, -0.0674 },
  0.0,                                 /* f_40_Value : '<S19>/f_4 = 0'
                                        */

  /*  f_40_XData_h : '<S19>/f_4 > 0'
   */
  { 0.0, 0.063, 0.107, 0.274, 0.441, 0.599, 0.731 },

  /*  f_40_YData_g : '<S19>/f_4 > 0'
   */
  { 0.3588, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },
  -0.001,                              /* DeadZone_Start_i : '<S20>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End_pv : '<S20>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value_ac : '<S33>/Constant'
                                        */
  0.0,                                 /* Constant_Value_k : '<S34>/Constant'
                                        */

  /*  f_50_XData : '<S20>/f_5 < 0'
   */
  { -1.263, -1.0309, -0.3808 },

  /*  f_50_YData : '<S20>/f_5 < 0'
   */
  { -0.3, -0.2, -0.1 },
  0.0,                                 /* f_50_Value : '<S20>/f_5 = 0'
                                        */

  /*  f_50_XData_k : '<S20>/f_5 > 0'
   */
  { 0.348, 0.829, 1.093 },

  /*  f_50_YData_h : '<S20>/f_5 > 0'
   */
  { 0.1, 0.2, 0.3 },
  1.0,                                 /* Saturation_UpperSat_c : '<S6>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat_d : '<S6>/Saturation'
                                        */
  0.5,                                 /* BT_power_limit_Value : '<S6>/BT_power_limit'
                                        */
  0.4,                                 /* VSP_speeds_Value : '<S6>/VSP_speeds'
                                        */
  1.0,                                 /* Saturation_UpperSat_f : '<S1>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat_i : '<S1>/Saturation'
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
  2.0,                                 /* BatteryMain_Gain : '<S3>/Battery Main'
                                        */
  1.0,                                 /* QTMIn1FPS_Gain : '<S40>/QTM In1 FPS'
                                        */
  3.0,                                 /* Saturation_UpperSat_e : '<S44>/Saturation'
                                        */
  -2.6,                                /* Saturation_LowerSat_j : '<S44>/Saturation'
                                        */
  3.0,                                 /* Saturation1_UpperSat : '<S44>/Saturation1'
                                        */
  -3.5,                                /* Saturation1_LowerSat : '<S44>/Saturation1'
                                        */
  1.6,                                 /* Saturation2_UpperSat : '<S44>/Saturation2'
                                        */
  -1.5,                                /* Saturation2_LowerSat : '<S44>/Saturation2'
                                        */
  1.0,                                 /* planttau_surge_Gain : '<S44>/plant tau_surge'
                                        */
  1.0,                                 /* planttau_sway_Gain : '<S44>/plant tau_sway'
                                        */
  1.0,                                 /* planttau_yaw_Gain : '<S44>/plant tau_yaw'
                                        */
  1.0,                                 /* plantu_1_Gain : '<S5>/plant u_1'
                                        */
  1.0,                                 /* plantu_2_Gain : '<S5>/plant u_2'
                                        */
  1.0,                                 /* plantu_3_Gain : '<S5>/plant u_3'
                                        */
  1.0,                                 /* plantu_4_Gain : '<S5>/plant u_4'
                                        */
  1.0,                                 /* plantu_5_Gain : '<S5>/plant u_5'
                                        */
  1.0,                                 /* plantBTpower_Gain : '<S5>/plant BT power'
                                        */
  1.0,                                 /* plantVSPspeed_Gain : '<S5>/plant VSP speed'
                                        */
  0.0,                                 /* EnableCSE1_Value : '<S5>/Enable CSE1'
                                        */
  1.0,                                 /* SignalProbe_P1 : '<Root>/SignalProbe'
                                        */
  -1.0,                                /* SITPWM0BT_P1 : '<S45>/SIT PWM0 BT'
                                        */
  1.0,                                 /* SITPWM0BT_P2 : '<S45>/SIT PWM0 BT'
                                        */
  1.0,                                 /* SITPWM0BT_P3 : '<S45>/SIT PWM0 BT'
                                        */
  -1.0,                                /* SITPWM0BT_P4 : '<S45>/SIT PWM0 BT'
                                        */
  1.0,                                 /* SITPWM0BT_P5 : '<S45>/SIT PWM0 BT'
                                        */
  0.0,                                 /* SITPWM0BT_P6 : '<S45>/SIT PWM0 BT'
                                        */
  0.02,                                /* BT_D_Gain1_Gain : '<S45>/BT_D_Gain1'
                                        */
  0.05,                                /* BT_Power_Offset1_Value : '<S45>/BT_Power_Offset1'
                                        */
  0.02,                                /* BT_D_Gain2_Gain : '<S45>/BT_D_Gain2'
                                        */
  0.02,                                /* BT_L_Gain1_Gain : '<S45>/BT_L_Gain1'
                                        */
  -0.02,                               /* BT_L_Gain2_Gain : '<S45>/BT_L_Gain2'
                                        */
  0.05,                                /* BT_Power_Offset2_Value : '<S45>/BT_Power_Offset2'
                                        */
  0.05,                                /* BT_Power_Offset3_Value : '<S45>/BT_Power_Offset3'
                                        */
  0.0,                                 /* Constant_Value_m : '<S45>/Constant'
                                        */
  0.0,                                 /* Constant1_Value_j : '<S45>/Constant1'
                                        */
  -1.0,                                /* Neg_Gain : '<S45>/Neg'
                                        */
  -1.0,                                /* SITPWM4Servo1_P1 : '<S46>/SIT PWM4 Servo1'
                                        */
  1.0,                                 /* SITPWM4Servo1_P2 : '<S46>/SIT PWM4 Servo1'
                                        */
  1.0,                                 /* SITPWM4Servo1_P3 : '<S46>/SIT PWM4 Servo1'
                                        */
  -1.0,                                /* SITPWM4Servo1_P4 : '<S46>/SIT PWM4 Servo1'
                                        */
  1.0,                                 /* SITPWM4Servo1_P5 : '<S46>/SIT PWM4 Servo1'
                                        */
  0.0,                                 /* SITPWM4Servo1_P6 : '<S46>/SIT PWM4 Servo1'
                                        */
  -1.0,                                /* SITPWM5Servo2_P1 : '<S46>/SIT PWM5 Servo2'
                                        */
  1.0,                                 /* SITPWM5Servo2_P2 : '<S46>/SIT PWM5 Servo2'
                                        */
  2.0,                                 /* SITPWM5Servo2_P3 : '<S46>/SIT PWM5 Servo2'
                                        */
  -1.0,                                /* SITPWM5Servo2_P4 : '<S46>/SIT PWM5 Servo2'
                                        */
  1.0,                                 /* SITPWM5Servo2_P5 : '<S46>/SIT PWM5 Servo2'
                                        */
  0.0,                                 /* SITPWM5Servo2_P6 : '<S46>/SIT PWM5 Servo2'
                                        */
  -1.0,                                /* SITPWM6Servo3_P1 : '<S46>/SIT PWM6 Servo3'
                                        */
  1.0,                                 /* SITPWM6Servo3_P2 : '<S46>/SIT PWM6 Servo3'
                                        */
  3.0,                                 /* SITPWM6Servo3_P3 : '<S46>/SIT PWM6 Servo3'
                                        */
  -1.0,                                /* SITPWM6Servo3_P4 : '<S46>/SIT PWM6 Servo3'
                                        */
  1.0,                                 /* SITPWM6Servo3_P5 : '<S46>/SIT PWM6 Servo3'
                                        */
  0.0,                                 /* SITPWM6Servo3_P6 : '<S46>/SIT PWM6 Servo3'
                                        */
  -1.0,                                /* SITPWM7Servo4_P1 : '<S46>/SIT PWM7 Servo4'
                                        */
  1.0,                                 /* SITPWM7Servo4_P2 : '<S46>/SIT PWM7 Servo4'
                                        */
  4.0,                                 /* SITPWM7Servo4_P3 : '<S46>/SIT PWM7 Servo4'
                                        */
  -1.0,                                /* SITPWM7Servo4_P4 : '<S46>/SIT PWM7 Servo4'
                                        */
  1.0,                                 /* SITPWM7Servo4_P5 : '<S46>/SIT PWM7 Servo4'
                                        */
  0.0,                                 /* SITPWM7Servo4_P6 : '<S46>/SIT PWM7 Servo4'
                                        */
  -1.0,                                /* SITPWM1VSPSPort_P1 : '<S46>/SIT PWM1 VSPS Port'
                                        */
  1.0,                                 /* SITPWM1VSPSPort_P2 : '<S46>/SIT PWM1 VSPS Port'
                                        */
  5.0,                                 /* SITPWM1VSPSPort_P3 : '<S46>/SIT PWM1 VSPS Port'
                                        */
  -1.0,                                /* SITPWM1VSPSPort_P4 : '<S46>/SIT PWM1 VSPS Port'
                                        */
  1.0,                                 /* SITPWM1VSPSPort_P5 : '<S46>/SIT PWM1 VSPS Port'
                                        */
  0.0,                                 /* SITPWM1VSPSPort_P6 : '<S46>/SIT PWM1 VSPS Port'
                                        */
  -1.0,                                /* SITPWM2VSPSStarboard_P1 : '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  1.0,                                 /* SITPWM2VSPSStarboard_P2 : '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  6.0,                                 /* SITPWM2VSPSStarboard_P3 : '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  -1.0,                                /* SITPWM2VSPSStarboard_P4 : '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  1.0,                                 /* SITPWM2VSPSStarboard_P5 : '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  0.0,                                 /* SITPWM2VSPSStarboard_P6 : '<S46>/SIT PWM2 VSPS Starboard'
                                        */
  -1.0,                                /* x_Gain : '<S46>/-x'
                                        */
  -1.0,                                /* y_Gain : '<S46>/-y'
                                        */

  /*  Servo1_RowIdx : '<S46>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo1_ColIdx : '<S46>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo1_Table : '<S46>/Servo1'
   */
  { 0.06, 0.0495363, 0.043301, 0.06, 0.052446, 0.043301, 0.06, 0.0541518,
    0.043301 },

  /*  Servo2_RowIdx : '<S46>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo2_ColIdx : '<S46>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo2_Table : '<S46>/Servo2'
   */
  { 0.0386088, 0.0386088, 0.0386088, 0.0459941, 0.0477243, 0.0500953, 0.057,
    0.057, 0.057 },

  /*  Servo3_RowIdx : '<S46>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo3_ColIdx : '<S46>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo3_Table : '<S46>/Servo3'
   */
  { 0.0640809, 0.0640809, 0.0640809, 0.0539629, 0.0541315, 0.0556492, 0.0442664,
    0.0442664, 0.0442664 },

  /*  Servo4_RowIdx : '<S46>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo4_ColIdx : '<S46>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo4_Table : '<S46>/Servo4'
   */
  { 0.0602867, 0.0470489, 0.0403879, 0.0602867, 0.049747, 0.0403879, 0.0602867,
    0.0526138, 0.0403879 },
  -0.02,                               /* VPS_Speed_Gain_Gain : '<S46>/VPS_Speed_Gain'
                                        */
  0.05,                                /* VPS_Power_Offset_Value : '<S46>/VPS_Power_Offset'
                                        */
  1.0,                                 /* VSPSPort_Gain : '<S46>/VSPS Port'
                                        */
  1.0,                                 /* VSPSStarboard_Gain : '<S46>/VSPS Starboard'
                                        */
  -1.9,                                /* N_r_Value : '<S51>/N_r'
                                        */
  -1.0,                                /* N_r_Gain : '<S51>/-N_r'
                                        */
  0.1814,                              /* N_v_Value : '<S51>/N_v'
                                        */
  -1.0,                                /* N_v_Gain : '<S51>/-N_v'
                                        */
  -0.59739,                            /* X_u_Value : '<S51>/X_u'
                                        */
  -1.0,                                /* X_u_Gain : '<S51>/-X_u'
                                        */
  -3.50625,                            /* Y_v_Value : '<S51>/Y_v'
                                        */
  -1.0,                                /* Y_v_Gain : '<S51>/-Y_v'
                                        */
  -7.25,                               /* Y_r_Value : '<S51>/Y_r'
                                        */
  -1.0,                                /* Y_vr_Gain : '<S51>/-Y_vr'
                                        */
  0.0,                                 /* D_L_12_Value : '<S51>/D_L_12'
                                        */
  0.0,                                 /* D_L_13_Value : '<S51>/D_L_13'
                                        */
  0.0,                                 /* D_L_21_Value : '<S51>/D_L_21'
                                        */
  0.0,                                 /* D_L_31_Value : '<S51>/D_L_31'
                                        */
  0.0,                                 /* psi_0_Value : '<S52>/psi_0'
                                        */
  0.0,                                 /* x_0_Value : '<S52>/x_0'
                                        */
  0.0,                                 /* y_0_Value : '<S52>/y_0'
                                        */
  0.0,                                 /* r_0_Value : '<S53>/r_0'
                                        */
  0.0,                                 /* u_0_Value : '<S53>/u_0'
                                        */
  0.0,                                 /* v_0_Value : '<S53>/v_0'
                                        */
  0.0,                                 /* ResetLinearSimulatorintegrator_ : '<S50>/Reset Linear Simulator integrator'
                                        */
  1.76,                                /* I_z_Value : '<S54>/I_z'
                                        */
  17.6,                                /* m_Value : '<S54>/m'
                                        */
  -2.0,                                /* X_udot_Value : '<S54>/X_udot'
                                        */
  0.0,                                 /* M_21_Value : '<S54>/M_21'
                                        */
  0.0,                                 /* M_31_Value : '<S54>/M_31'
                                        */
  0.0,                                 /* M_12_Value : '<S54>/M_12'
                                        */
  -10.0,                               /* Y_vdot_Value : '<S54>/Y_vdot'
                                        */
  0.03,                                /* x_g_Value : '<S54>/x_g'
                                        */
  0.0,                                 /* N_vdot_Value : '<S54>/N_vdot'
                                        */
  0.0,                                 /* M_13_Value : '<S54>/M_13'
                                        */
  0.0,                                 /* Y_rdot_Value : '<S54>/Y_rdot'
                                        */
  -1.0,                                /* N_rdot_Value : '<S54>/N_rdot'
                                        */
  0.0,                                 /* R31_Value : '<S55>/R31'
                                        */
  0.0,                                 /* R32_Value : '<S55>/R32'
                                        */
  0.0,                                 /* R13_Value : '<S55>/R13'
                                        */
  0.0,                                 /* R23_Value : '<S55>/R23'
                                        */
  1.0,                                 /* R33_Value : '<S55>/R33'
                                        */
  1.0,                                 /* eta_surge_hil_Gain : '<S43>/eta_surge_hil'
                                        */
  1.0,                                 /* eta_sway_hil_Gain : '<S43>/eta_sway_hil'
                                        */
  1.0,                                 /* eta_yaw_hil_Gain : '<S43>/eta_yaw_hil'
                                        */
  1.0,                                 /* etadot_surge_hil_Gain : '<S43>/etadot_surge_hil'
                                        */
  1.0,                                 /* etadot_sway_hil_Gain : '<S43>/etadot_sway_hil'
                                        */
  1.0,                                 /* etadot_yaw_hil_Gain : '<S43>/etadot_yaw_hil'
                                        */
  1.0,                                 /* nu_surge_hil_Gain : '<S43>/nu_surge_hil'
                                        */
  1.0,                                 /* nu_sway_hil_Gain : '<S43>/nu_sway_hil'
                                        */
  1.0,                                 /* nu_yaw_hil_Gain : '<S43>/nu_yaw_hil'
                                        */
  128U,                                /* Gain_Gain_e : '<S16>/Gain'
                                        */
  192U,                                /* Gain1_Gain_i : '<S16>/Gain1'
                                        */
  128U,                                /* Gain_Gain_h : '<S17>/Gain'
                                        */
  192U,                                /* Gain1_Gain_a : '<S17>/Gain1'
                                        */
  128U,                                /* Gain_Gain_f : '<S18>/Gain'
                                        */
  192U,                                /* Gain1_Gain_o : '<S18>/Gain1'
                                        */
  128U,                                /* Gain_Gain_o : '<S19>/Gain'
                                        */
  192U,                                /* Gain1_Gain_it : '<S19>/Gain1'
                                        */
  128U,                                /* Gain_Gain_k : '<S20>/Gain'
                                        */
  192U                                 /* Gain1_Gain_aq : '<S20>/Gain1'
                                        */
};
