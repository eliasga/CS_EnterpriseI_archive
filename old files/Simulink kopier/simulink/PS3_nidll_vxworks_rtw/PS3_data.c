/*
 * PS3_data.c
 *
 * Real-Time Workshop code generation for Simulink model "PS3.mdl".
 *
 * Model Version              : 1.6
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 16:15:49 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PS3.h"
#include "PS3_private.h"

/* Block parameters (auto storage) */
Parameters_PS3 PS3_P = {
  0.0,                                 /* ControlMode_Value : '<S1>/Control Mode'
                                        */
  0.0,                                 /* AS_LY_Value : '<S4>/AS_LY'
                                        */
  3.0518509475997192E-005,             /* ScalingLY_Gain : '<S4>/ScalingLY'
                                        */
  1.0,                                 /* PS3u_1_Gain : '<S6>/PS3 u_1'
                                        */
  0.0,                                 /* AS_LX_Value : '<S4>/AS_LX'
                                        */
  3.0518509475997192E-005,             /* ScalingLX_Gain : '<S4>/ScalingLX'
                                        */
  1.0,                                 /* PS3u_2_Gain : '<S6>/PS3 u_2'
                                        */
  0.0,                                 /* AS_RY_Value : '<S4>/AS_RY'
                                        */
  3.0518509475997192E-005,             /* ScalingRY_Gain : '<S4>/ScalingRY'
                                        */
  1.0,                                 /* PS3u_3_Gain : '<S6>/PS3 u_3'
                                        */
  0.0,                                 /* AS_RX_Value : '<S4>/AS_RX'
                                        */
  3.0518509475997192E-005,             /* Scaling_RX_Gain : '<S4>/Scaling_RX'
                                        */
  1.0,                                 /* PS3u_4_Gain : '<S6>/PS3 u_4'
                                        */
  0.0,                                 /* L2_Value : '<S4>/L2'
                                        */
  0.0,                                 /* R2_Value : '<S4>/R2'
                                        */
  1.0,                                 /* PS3u_5_Gain : '<S6>/PS3 u_5'
                                        */
  0.0,                                 /* PS3_BT_Power_Value : '<S4>/PS3_BT_Power'
                                        */
  0.0,                                 /* PS3_VSP_Speed_Value : '<S4>/PS3_VSP_Speed'
                                        */
  1.0,                                 /* T_e11_Value : '<S30>/T_e11'
                                        */
  0.0,                                 /* T_e21_Value : '<S30>/T_e21'
                                        */
  0.055,                               /* l_y1_Value : '<S30>/l_y1'
                                        */
  0.0,                                 /* T_e12_Value : '<S30>/T_e12'
                                        */
  1.0,                                 /* T_e22_Value : '<S30>/T_e22'
                                        */
  0.45,                                /* l_x1_Value : '<S30>/l_x1'
                                        */
  -1.0,                                /* l_x1_Gain : '<S30>/-l_x1'
                                        */
  1.0,                                 /* T_e13_Value : '<S30>/T_e13'
                                        */
  0.0,                                 /* T_e23_Value : '<S30>/T_e23'
                                        */
  0.055,                               /* l_y2_Value : '<S30>/l_y2'
                                        */
  -1.0,                                /* l_y2_Gain : '<S30>/-l_y2'
                                        */
  0.0,                                 /* T_e14_Value : '<S30>/T_e14'
                                        */
  1.0,                                 /* T_e24_Value : '<S30>/T_e24'
                                        */
  0.45,                                /* l_x2_Value : '<S30>/l_x2'
                                        */
  -1.0,                                /* l_x2_Gain : '<S30>/-l_x2'
                                        */
  0.0,                                 /* T_e15_Value : '<S30>/T_e15'
                                        */
  1.0,                                 /* T_e25_Value : '<S30>/T_e25'
                                        */
  0.385,                               /* l_x3_Value : '<S30>/l_x3'
                                        */
  1.0,                                 /* tau_surge_Gain : '<S5>/tau_surge'
                                        */
  1.0,                                 /* tau_sway_Gain : '<S5>/tau_sway'
                                        */
  1.0,                                 /* tau_yaw_Gain : '<S5>/tau_yaw'
                                        */
  -0.001,                              /* DeadZone_Start : '<S10>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End : '<S10>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value : '<S15>/Constant'
                                        */
  0.0,                                 /* Constant_Value_h : '<S16>/Constant'
                                        */

  /*  f_10_XData : '<S10>/f_1 < 0'
   */
  { -1.324, -1.169, -0.919, -0.703, -0.535, -0.292, -0.165, -0.06, 0.0 },

  /*  f_10_YData : '<S10>/f_1 < 0'
   */
  { -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2089 },
  0.0,                                 /* f_10_Value : '<S10>/f_1 = 0'
                                        */

  /*  f_10_XData_h : '<S10>/f_1 > 0'
   */
  { 0.0, 0.051, 0.153, 0.308, 0.48, 0.663, 0.911, 1.057, 1.221, 1.374 },

  /*  f_10_YData_p : '<S10>/f_1 > 0'
   */
  { 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 },
  -0.001,                              /* DeadZone_Start_p : '<S11>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End_b : '<S11>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value_l : '<S18>/Constant'
                                        */
  0.0,                                 /* Constant_Value_n : '<S19>/Constant'
                                        */
  0.0,                                 /* Constant_Value_b : '<S20>/Constant'
                                        */

  /*  f_20_XData : '<S11>/f_2 < 0'
   */
  { -0.766, -0.649, -0.522, -0.411, -0.323, -0.246, -0.156, -0.075, -0.018,
    -0.006, 0.0 },

  /*  f_20_YData : '<S11>/f_2 < 0'
   */
  { -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, -0.0466 },
  0.0,                                 /* f_20_Value : '<S11>/f_2 = 0'
                                        */

  /*  f_20_XData_n : '<S11>/f_2 > 0'
   */
  { 0.0, 0.052, 0.207, 0.331, 0.509, 0.689, 0.829, 0.961, 1.079, 1.12 },

  /*  f_20_YData_p : '<S11>/f_2 > 0'
   */
  { 0.1665, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },
  -0.001,                              /* DeadZone_Start_d : '<S12>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End_a : '<S12>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value_a : '<S21>/Constant'
                                        */
  0.0,                                 /* Constant_Value_o : '<S22>/Constant'
                                        */

  /*  f_30_XData : '<S12>/f_3 < 0'
   */
  { -1.291, -1.088, -0.885, -0.618, -0.403, -0.211, -0.034, 0.0 },

  /*  f_30_YData : '<S12>/f_3 < 0'
   */
  { -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2809 },
  0.0,                                 /* f_30_Value : '<S12>/f_3 = 0'
                                        */

  /*  f_30_XData_k : '<S12>/f_3 > 0'
   */
  { 0.0, 0.014, 0.04, 0.147, 0.302, 0.494, 0.68, 0.968, 1.111, 1.289, 1.339 },

  /*  f_30_YData_j : '<S12>/f_3 > 0'
   */
  { 0.0452, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },
  -0.001,                              /* DeadZone_Start_a : '<S13>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End_p : '<S13>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value_bv : '<S24>/Constant'
                                        */
  0.0,                                 /* Constant_Value_bb : '<S25>/Constant'
                                        */

  /*  f_40_XData : '<S13>/f_4 < 0'
   */
  { -1.249, -1.225, -1.094, -0.896, -0.696, -0.502, -0.314, -0.169, -0.042, 0.0
  },

  /*  f_40_YData : '<S13>/f_4 < 0'
   */
  { -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, -0.0674 },
  0.0,                                 /* f_40_Value : '<S13>/f_4 = 0'
                                        */

  /*  f_40_XData_e : '<S13>/f_4 > 0'
   */
  { 0.0, 0.063, 0.107, 0.274, 0.441, 0.599, 0.731 },

  /*  f_40_YData_l : '<S13>/f_4 > 0'
   */
  { 0.3588, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 },
  -0.001,                              /* DeadZone_Start_dk : '<S14>/Dead Zone'
                                        */
  0.001,                               /* DeadZone_End_d : '<S14>/Dead Zone'
                                        */
  0.0,                                 /* Constant_Value_g : '<S27>/Constant'
                                        */
  0.0,                                 /* Constant_Value_ny : '<S28>/Constant'
                                        */

  /*  f_50_XData : '<S14>/f_5 < 0'
   */
  { -1.263, -1.0309, -0.3808 },

  /*  f_50_YData : '<S14>/f_5 < 0'
   */
  { -0.3, -0.2, -0.1 },
  0.0,                                 /* f_50_Value : '<S14>/f_5 = 0'
                                        */

  /*  f_50_XData_p : '<S14>/f_5 > 0'
   */
  { 0.348, 0.829, 1.093 },

  /*  f_50_YData_d : '<S14>/f_5 > 0'
   */
  { 0.1, 0.2, 0.3 },
  1.0,                                 /* Saturation_UpperSat : '<S5>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat : '<S5>/Saturation'
                                        */
  1.0,                                 /* Joysticku_1_Gain : '<S5>/Joystick u_1'
                                        */
  1.0,                                 /* Joysticku_2_Gain : '<S5>/Joystick u_2'
                                        */
  1.0,                                 /* Joysticku_3_Gain : '<S5>/Joystick u_3'
                                        */
  1.0,                                 /* Joysticku_4_Gain : '<S5>/Joystick u_4'
                                        */
  1.0,                                 /* Joysticku_5_Gain : '<S5>/Joystick u_5'
                                        */
  1.0,                                 /* Saturation_UpperSat_l : '<S1>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat_b : '<S1>/Saturation'
                                        */
  1.0,                                 /* plantu_1_Gain : '<S3>/plant u_1'
                                        */
  1.0,                                 /* plantu_2_Gain : '<S3>/plant u_2'
                                        */
  1.0,                                 /* plantu_3_Gain : '<S3>/plant u_3'
                                        */
  1.0,                                 /* plantu_4_Gain : '<S3>/plant u_4'
                                        */
  1.0,                                 /* plantu_5_Gain : '<S3>/plant u_5'
                                        */
  1.0,                                 /* plantBTpower_Gain : '<S3>/plant BT power'
                                        */
  1.0,                                 /* plantVSPspeed_Gain : '<S3>/plant VSP speed'
                                        */
  0.0,                                 /* EnableCSE1_Value : '<S3>/Enable CSE1'
                                        */
  -1.0,                                /* SITzAI0_P1 : '<S2>/SIT zAI0'
                                        */
  1.0,                                 /* SITzAI0_P2 : '<S2>/SIT zAI0'
                                        */
  1.0,                                 /* SITzAI0_P3 : '<S2>/SIT zAI0'
                                        */
  -1.0,                                /* SITzAI0_P4 : '<S2>/SIT zAI0'
                                        */
  1.0,                                 /* SITzAI0_P5 : '<S2>/SIT zAI0'
                                        */
  1.0,                                 /* SITzAI0_P6 : '<S2>/SIT zAI0'
                                        */
  1.0,                                 /* BatteryBowThruster_Gain : '<S2>/Battery Bow Thruster'
                                        */
  -1.0,                                /* SITzAI1_P1 : '<S2>/SIT zAI1'
                                        */
  1.0,                                 /* SITzAI1_P2 : '<S2>/SIT zAI1'
                                        */
  2.0,                                 /* SITzAI1_P3 : '<S2>/SIT zAI1'
                                        */
  -1.0,                                /* SITzAI1_P4 : '<S2>/SIT zAI1'
                                        */
  1.0,                                 /* SITzAI1_P5 : '<S2>/SIT zAI1'
                                        */
  1.0,                                 /* SITzAI1_P6 : '<S2>/SIT zAI1'
                                        */
  1.0,                                 /* BatteryServo_Gain : '<S2>/Battery Servo'
                                        */
  -1.0,                                /* SITzAI2_P1 : '<S2>/SIT zAI2'
                                        */
  1.0,                                 /* SITzAI2_P2 : '<S2>/SIT zAI2'
                                        */
  3.0,                                 /* SITzAI2_P3 : '<S2>/SIT zAI2'
                                        */
  -1.0,                                /* SITzAI2_P4 : '<S2>/SIT zAI2'
                                        */
  1.0,                                 /* SITzAI2_P5 : '<S2>/SIT zAI2'
                                        */
  1.0,                                 /* SITzAI2_P6 : '<S2>/SIT zAI2'
                                        */
  2.0,                                 /* BatteryMain_Gain : '<S2>/Battery Main'
                                        */
  1.0,                                 /* SignalProbe_P1 : '<Root>/SignalProbe'
                                        */
  -1.0,                                /* SITPWM0BT_P1 : '<S32>/SIT PWM0 BT'
                                        */
  1.0,                                 /* SITPWM0BT_P2 : '<S32>/SIT PWM0 BT'
                                        */
  1.0,                                 /* SITPWM0BT_P3 : '<S32>/SIT PWM0 BT'
                                        */
  -1.0,                                /* SITPWM0BT_P4 : '<S32>/SIT PWM0 BT'
                                        */
  1.0,                                 /* SITPWM0BT_P5 : '<S32>/SIT PWM0 BT'
                                        */
  0.0,                                 /* SITPWM0BT_P6 : '<S32>/SIT PWM0 BT'
                                        */
  0.02,                                /* BT_D_Gain1_Gain : '<S32>/BT_D_Gain1'
                                        */
  0.05,                                /* BT_Power_Offset1_Value : '<S32>/BT_Power_Offset1'
                                        */
  0.02,                                /* BT_D_Gain2_Gain : '<S32>/BT_D_Gain2'
                                        */
  0.02,                                /* BT_L_Gain1_Gain : '<S32>/BT_L_Gain1'
                                        */
  -0.02,                               /* BT_L_Gain2_Gain : '<S32>/BT_L_Gain2'
                                        */
  0.05,                                /* BT_Power_Offset2_Value : '<S32>/BT_Power_Offset2'
                                        */
  0.05,                                /* BT_Power_Offset3_Value : '<S32>/BT_Power_Offset3'
                                        */
  0.0,                                 /* Constant_Value_al : '<S32>/Constant'
                                        */
  0.0,                                 /* Constant1_Value : '<S32>/Constant1'
                                        */
  -1.0,                                /* Neg_Gain : '<S32>/Neg'
                                        */
  -1.0,                                /* SITPWM4Servo1_P1 : '<S33>/SIT PWM4 Servo1'
                                        */
  1.0,                                 /* SITPWM4Servo1_P2 : '<S33>/SIT PWM4 Servo1'
                                        */
  1.0,                                 /* SITPWM4Servo1_P3 : '<S33>/SIT PWM4 Servo1'
                                        */
  -1.0,                                /* SITPWM4Servo1_P4 : '<S33>/SIT PWM4 Servo1'
                                        */
  1.0,                                 /* SITPWM4Servo1_P5 : '<S33>/SIT PWM4 Servo1'
                                        */
  0.0,                                 /* SITPWM4Servo1_P6 : '<S33>/SIT PWM4 Servo1'
                                        */
  -1.0,                                /* SITPWM5Servo2_P1 : '<S33>/SIT PWM5 Servo2'
                                        */
  1.0,                                 /* SITPWM5Servo2_P2 : '<S33>/SIT PWM5 Servo2'
                                        */
  2.0,                                 /* SITPWM5Servo2_P3 : '<S33>/SIT PWM5 Servo2'
                                        */
  -1.0,                                /* SITPWM5Servo2_P4 : '<S33>/SIT PWM5 Servo2'
                                        */
  1.0,                                 /* SITPWM5Servo2_P5 : '<S33>/SIT PWM5 Servo2'
                                        */
  0.0,                                 /* SITPWM5Servo2_P6 : '<S33>/SIT PWM5 Servo2'
                                        */
  -1.0,                                /* SITPWM6Servo3_P1 : '<S33>/SIT PWM6 Servo3'
                                        */
  1.0,                                 /* SITPWM6Servo3_P2 : '<S33>/SIT PWM6 Servo3'
                                        */
  3.0,                                 /* SITPWM6Servo3_P3 : '<S33>/SIT PWM6 Servo3'
                                        */
  -1.0,                                /* SITPWM6Servo3_P4 : '<S33>/SIT PWM6 Servo3'
                                        */
  1.0,                                 /* SITPWM6Servo3_P5 : '<S33>/SIT PWM6 Servo3'
                                        */
  0.0,                                 /* SITPWM6Servo3_P6 : '<S33>/SIT PWM6 Servo3'
                                        */
  -1.0,                                /* SITPWM7Servo4_P1 : '<S33>/SIT PWM7 Servo4'
                                        */
  1.0,                                 /* SITPWM7Servo4_P2 : '<S33>/SIT PWM7 Servo4'
                                        */
  4.0,                                 /* SITPWM7Servo4_P3 : '<S33>/SIT PWM7 Servo4'
                                        */
  -1.0,                                /* SITPWM7Servo4_P4 : '<S33>/SIT PWM7 Servo4'
                                        */
  1.0,                                 /* SITPWM7Servo4_P5 : '<S33>/SIT PWM7 Servo4'
                                        */
  0.0,                                 /* SITPWM7Servo4_P6 : '<S33>/SIT PWM7 Servo4'
                                        */
  -1.0,                                /* SITPWM1VSPSPort_P1 : '<S33>/SIT PWM1 VSPS Port'
                                        */
  1.0,                                 /* SITPWM1VSPSPort_P2 : '<S33>/SIT PWM1 VSPS Port'
                                        */
  5.0,                                 /* SITPWM1VSPSPort_P3 : '<S33>/SIT PWM1 VSPS Port'
                                        */
  -1.0,                                /* SITPWM1VSPSPort_P4 : '<S33>/SIT PWM1 VSPS Port'
                                        */
  1.0,                                 /* SITPWM1VSPSPort_P5 : '<S33>/SIT PWM1 VSPS Port'
                                        */
  0.0,                                 /* SITPWM1VSPSPort_P6 : '<S33>/SIT PWM1 VSPS Port'
                                        */
  -1.0,                                /* SITPWM2VSPSStarboard_P1 : '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  1.0,                                 /* SITPWM2VSPSStarboard_P2 : '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  6.0,                                 /* SITPWM2VSPSStarboard_P3 : '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  -1.0,                                /* SITPWM2VSPSStarboard_P4 : '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  1.0,                                 /* SITPWM2VSPSStarboard_P5 : '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  0.0,                                 /* SITPWM2VSPSStarboard_P6 : '<S33>/SIT PWM2 VSPS Starboard'
                                        */
  -1.0,                                /* x_Gain : '<S33>/-x'
                                        */
  -1.0,                                /* y_Gain : '<S33>/-y'
                                        */

  /*  Servo1_RowIdx : '<S33>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo1_ColIdx : '<S33>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo1_Table : '<S33>/Servo1'
   */
  { 0.06, 0.0495363, 0.043301, 0.06, 0.052446, 0.043301, 0.06, 0.0541518,
    0.043301 },

  /*  Servo2_RowIdx : '<S33>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo2_ColIdx : '<S33>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo2_Table : '<S33>/Servo2'
   */
  { 0.0386088, 0.0386088, 0.0386088, 0.0459941, 0.0477243, 0.0500953, 0.057,
    0.057, 0.057 },

  /*  Servo3_RowIdx : '<S33>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo3_ColIdx : '<S33>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo3_Table : '<S33>/Servo3'
   */
  { 0.0640809, 0.0640809, 0.0640809, 0.0539629, 0.0541315, 0.0556492, 0.0442664,
    0.0442664, 0.0442664 },

  /*  Servo4_RowIdx : '<S33>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo4_ColIdx : '<S33>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo4_Table : '<S33>/Servo4'
   */
  { 0.0602867, 0.0470489, 0.0403879, 0.0602867, 0.049747, 0.0403879, 0.0602867,
    0.0526138, 0.0403879 },
  -0.02,                               /* VPS_Speed_Gain_Gain : '<S33>/VPS_Speed_Gain'
                                        */
  0.05,                                /* VPS_Power_Offset_Value : '<S33>/VPS_Power_Offset'
                                        */
  1.0,                                 /* VSPSPort_Gain : '<S33>/VSPS Port'
                                        */
  1.0,                                 /* VSPSStarboard_Gain : '<S33>/VSPS Starboard'
                                        */
  128U,                                /* Gain_Gain : '<S10>/Gain'
                                        */
  192U,                                /* Gain1_Gain : '<S10>/Gain1'
                                        */
  128U,                                /* Gain_Gain_h : '<S11>/Gain'
                                        */
  192U,                                /* Gain1_Gain_p : '<S11>/Gain1'
                                        */
  128U,                                /* Gain_Gain_f : '<S12>/Gain'
                                        */
  192U,                                /* Gain1_Gain_o : '<S12>/Gain1'
                                        */
  128U,                                /* Gain_Gain_b : '<S13>/Gain'
                                        */
  192U,                                /* Gain1_Gain_l : '<S13>/Gain1'
                                        */
  128U,                                /* Gain_Gain_g : '<S14>/Gain'
                                        */
  192U                                 /* Gain1_Gain_k : '<S14>/Gain1'
                                        */
};
