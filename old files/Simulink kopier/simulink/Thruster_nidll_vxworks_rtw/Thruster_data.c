/*
 * Thruster_data.c
 *
 * Real-Time Workshop code generation for Simulink model "Thruster.mdl".
 *
 * Model Version              : 1.8
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 15:31:19 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Thruster.h"
#include "Thruster_private.h"

/* Block parameters (auto storage) */
Parameters_Thruster Thruster_P = {
  0.0,                                 /* ControlMode_Value : '<S1>/Control Mode'
                                        */
  0.0,                                 /* AS_LY_Value : '<S4>/AS_LY'
                                        */
  3.0518509475997192E-005,             /* ScalingLY_Gain : '<S4>/ScalingLY'
                                        */
  1.0,                                 /* PS3u_1_Gain : '<S5>/PS3 u_1'
                                        */
  0.0,                                 /* AS_LX_Value : '<S4>/AS_LX'
                                        */
  3.0518509475997192E-005,             /* ScalingLX_Gain : '<S4>/ScalingLX'
                                        */
  1.0,                                 /* PS3u_2_Gain : '<S5>/PS3 u_2'
                                        */
  0.0,                                 /* AS_RY_Value : '<S4>/AS_RY'
                                        */
  3.0518509475997192E-005,             /* ScalingRY_Gain : '<S4>/ScalingRY'
                                        */
  1.0,                                 /* PS3u_3_Gain : '<S5>/PS3 u_3'
                                        */
  0.0,                                 /* AS_RX_Value : '<S4>/AS_RX'
                                        */
  3.0518509475997192E-005,             /* Scaling_RX_Gain : '<S4>/Scaling_RX'
                                        */
  1.0,                                 /* PS3u_4_Gain : '<S5>/PS3 u_4'
                                        */
  0.0,                                 /* L2_Value : '<S4>/L2'
                                        */
  0.0,                                 /* R2_Value : '<S4>/R2'
                                        */
  1.0,                                 /* PS3u_5_Gain : '<S5>/PS3 u_5'
                                        */
  0.0,                                 /* PS3_BT_Power_Value : '<S4>/PS3_BT_Power'
                                        */
  0.0,                                 /* PS3_VSP_Speed_Value : '<S4>/PS3_VSP_Speed'
                                        */
  0.0,                                 /* u1_Value : '<S6>/u1'
                                        */
  1.0,                                 /* LabVIEWu_1_Gain : '<S6>/LabVIEW u_1'
                                        */
  0.0,                                 /* u2_Value : '<S6>/u2'
                                        */
  1.0,                                 /* LabVIEWu_2_Gain : '<S6>/LabVIEW u_2'
                                        */
  0.0,                                 /* u3_Value : '<S6>/u3'
                                        */
  1.0,                                 /* LabVIEWu_3_Gain : '<S6>/LabVIEW u_3'
                                        */
  0.0,                                 /* u4_Value : '<S6>/u4'
                                        */
  1.0,                                 /* LabVIEWu_4_Gain : '<S6>/LabVIEW u_4'
                                        */
  0.0,                                 /* u5_Value : '<S6>/u5'
                                        */
  1.0,                                 /* LabVIEWu_5_Gain : '<S6>/LabVIEW u_5'
                                        */
  0.0,                                 /* BTpower_Value : '<S6>/BT power'
                                        */
  0.0,                                 /* VSPspeed_Value : '<S6>/VSP speed'
                                        */
  1.0,                                 /* Saturation_UpperSat : '<S1>/Saturation'
                                        */
  -1.0,                                /* Saturation_LowerSat : '<S1>/Saturation'
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
  -1.0,                                /* SITPWM0BT_P1 : '<S8>/SIT PWM0 BT'
                                        */
  1.0,                                 /* SITPWM0BT_P2 : '<S8>/SIT PWM0 BT'
                                        */
  1.0,                                 /* SITPWM0BT_P3 : '<S8>/SIT PWM0 BT'
                                        */
  -1.0,                                /* SITPWM0BT_P4 : '<S8>/SIT PWM0 BT'
                                        */
  1.0,                                 /* SITPWM0BT_P5 : '<S8>/SIT PWM0 BT'
                                        */
  0.0,                                 /* SITPWM0BT_P6 : '<S8>/SIT PWM0 BT'
                                        */
  0.02,                                /* BT_D_Gain1_Gain : '<S8>/BT_D_Gain1'
                                        */
  0.05,                                /* BT_Power_Offset1_Value : '<S8>/BT_Power_Offset1'
                                        */
  0.02,                                /* BT_D_Gain2_Gain : '<S8>/BT_D_Gain2'
                                        */
  0.02,                                /* BT_L_Gain1_Gain : '<S8>/BT_L_Gain1'
                                        */
  -0.02,                               /* BT_L_Gain2_Gain : '<S8>/BT_L_Gain2'
                                        */
  0.05,                                /* BT_Power_Offset2_Value : '<S8>/BT_Power_Offset2'
                                        */
  0.05,                                /* BT_Power_Offset3_Value : '<S8>/BT_Power_Offset3'
                                        */
  0.0,                                 /* Constant_Value : '<S8>/Constant'
                                        */
  0.0,                                 /* Constant1_Value : '<S8>/Constant1'
                                        */
  -1.0,                                /* Neg_Gain : '<S8>/Neg'
                                        */
  -1.0,                                /* SITPWM4Servo1_P1 : '<S9>/SIT PWM4 Servo1'
                                        */
  1.0,                                 /* SITPWM4Servo1_P2 : '<S9>/SIT PWM4 Servo1'
                                        */
  1.0,                                 /* SITPWM4Servo1_P3 : '<S9>/SIT PWM4 Servo1'
                                        */
  -1.0,                                /* SITPWM4Servo1_P4 : '<S9>/SIT PWM4 Servo1'
                                        */
  1.0,                                 /* SITPWM4Servo1_P5 : '<S9>/SIT PWM4 Servo1'
                                        */
  0.0,                                 /* SITPWM4Servo1_P6 : '<S9>/SIT PWM4 Servo1'
                                        */
  -1.0,                                /* SITPWM5Servo2_P1 : '<S9>/SIT PWM5 Servo2'
                                        */
  1.0,                                 /* SITPWM5Servo2_P2 : '<S9>/SIT PWM5 Servo2'
                                        */
  2.0,                                 /* SITPWM5Servo2_P3 : '<S9>/SIT PWM5 Servo2'
                                        */
  -1.0,                                /* SITPWM5Servo2_P4 : '<S9>/SIT PWM5 Servo2'
                                        */
  1.0,                                 /* SITPWM5Servo2_P5 : '<S9>/SIT PWM5 Servo2'
                                        */
  0.0,                                 /* SITPWM5Servo2_P6 : '<S9>/SIT PWM5 Servo2'
                                        */
  -1.0,                                /* SITPWM6Servo3_P1 : '<S9>/SIT PWM6 Servo3'
                                        */
  1.0,                                 /* SITPWM6Servo3_P2 : '<S9>/SIT PWM6 Servo3'
                                        */
  3.0,                                 /* SITPWM6Servo3_P3 : '<S9>/SIT PWM6 Servo3'
                                        */
  -1.0,                                /* SITPWM6Servo3_P4 : '<S9>/SIT PWM6 Servo3'
                                        */
  1.0,                                 /* SITPWM6Servo3_P5 : '<S9>/SIT PWM6 Servo3'
                                        */
  0.0,                                 /* SITPWM6Servo3_P6 : '<S9>/SIT PWM6 Servo3'
                                        */
  -1.0,                                /* SITPWM7Servo4_P1 : '<S9>/SIT PWM7 Servo4'
                                        */
  1.0,                                 /* SITPWM7Servo4_P2 : '<S9>/SIT PWM7 Servo4'
                                        */
  4.0,                                 /* SITPWM7Servo4_P3 : '<S9>/SIT PWM7 Servo4'
                                        */
  -1.0,                                /* SITPWM7Servo4_P4 : '<S9>/SIT PWM7 Servo4'
                                        */
  1.0,                                 /* SITPWM7Servo4_P5 : '<S9>/SIT PWM7 Servo4'
                                        */
  0.0,                                 /* SITPWM7Servo4_P6 : '<S9>/SIT PWM7 Servo4'
                                        */
  -1.0,                                /* SITPWM1VSPSPort_P1 : '<S9>/SIT PWM1 VSPS Port'
                                        */
  1.0,                                 /* SITPWM1VSPSPort_P2 : '<S9>/SIT PWM1 VSPS Port'
                                        */
  5.0,                                 /* SITPWM1VSPSPort_P3 : '<S9>/SIT PWM1 VSPS Port'
                                        */
  -1.0,                                /* SITPWM1VSPSPort_P4 : '<S9>/SIT PWM1 VSPS Port'
                                        */
  1.0,                                 /* SITPWM1VSPSPort_P5 : '<S9>/SIT PWM1 VSPS Port'
                                        */
  0.0,                                 /* SITPWM1VSPSPort_P6 : '<S9>/SIT PWM1 VSPS Port'
                                        */
  -1.0,                                /* SITPWM2VSPSStarboard_P1 : '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  1.0,                                 /* SITPWM2VSPSStarboard_P2 : '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  6.0,                                 /* SITPWM2VSPSStarboard_P3 : '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  -1.0,                                /* SITPWM2VSPSStarboard_P4 : '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  1.0,                                 /* SITPWM2VSPSStarboard_P5 : '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  0.0,                                 /* SITPWM2VSPSStarboard_P6 : '<S9>/SIT PWM2 VSPS Starboard'
                                        */
  -1.0,                                /* x_Gain : '<S9>/-x'
                                        */
  -1.0,                                /* y_Gain : '<S9>/-y'
                                        */

  /*  Servo1_RowIdx : '<S9>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo1_ColIdx : '<S9>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo1_Table : '<S9>/Servo1'
   */
  { 0.06, 0.0495363, 0.043301, 0.06, 0.052446, 0.043301, 0.06, 0.0541518,
    0.043301 },

  /*  Servo2_RowIdx : '<S9>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo2_ColIdx : '<S9>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo2_Table : '<S9>/Servo2'
   */
  { 0.0386088, 0.0386088, 0.0386088, 0.0459941, 0.0477243, 0.0500953, 0.057,
    0.057, 0.057 },

  /*  Servo3_RowIdx : '<S9>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo3_ColIdx : '<S9>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo3_Table : '<S9>/Servo3'
   */
  { 0.0640809, 0.0640809, 0.0640809, 0.0539629, 0.0541315, 0.0556492, 0.0442664,
    0.0442664, 0.0442664 },

  /*  Servo4_RowIdx : '<S9>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo4_ColIdx : '<S9>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Servo4_Table : '<S9>/Servo4'
   */
  { 0.0602867, 0.0470489, 0.0403879, 0.0602867, 0.049747, 0.0403879, 0.0602867,
    0.0526138, 0.0403879 },
  -0.02,                               /* VPS_Speed_Gain_Gain : '<S9>/VPS_Speed_Gain'
                                        */
  0.05,                                /* VPS_Power_Offset_Value : '<S9>/VPS_Power_Offset'
                                        */
  1.0,                                 /* VSPSPort_Gain : '<S9>/VSPS Port'
                                        */
  1.0                                  /* VSPSStarboard_Gain : '<S9>/VSPS Starboard'
                                        */
};
