/*
 * BP_MC1_data.c
 *
 * Real-Time Workshop code generation for Simulink model "BP_MC1.mdl".
 *
 * Model Version              : 1.49
 * Real-Time Workshop version : 7.4  (R2009b)  29-Jun-2009
 * C source code generated on : Wed Sep 19 12:19:00 2012
 *
 * Target selection: nidll.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "BP_MC1.h"
#include "BP_MC1_private.h"

/* Block parameters (auto storage) */
Parameters_BP_MC1 BP_MC1_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/SIT Out1 Servo1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/SIT Out1 Servo1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/SIT Out1 Servo1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/SIT Out1 Servo1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/SIT Out1 Servo1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/SIT Out1 Servo1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/SIT Out2 Servo2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/SIT Out2 Servo2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/SIT Out2 Servo2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/SIT Out2 Servo2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/SIT Out2 Servo2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/SIT Out2 Servo2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/SIT Out3 Servo3'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/SIT Out3 Servo3'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/SIT Out3 Servo3'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/SIT Out3 Servo3'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/SIT Out3 Servo3'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/SIT Out3 Servo3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/SIT Out4 Servo4'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/SIT Out4 Servo4'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/SIT Out4 Servo4'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/SIT Out4 Servo4'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/SIT Out4 Servo4'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/SIT Out4 Servo4'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/SIT Out5 VSPS Port '
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/SIT Out5 VSPS Port '
                                        */
  40.0,                                /* Expression: portnum
                                        * Referenced by: '<S4>/SIT Out5 VSPS Port '
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/SIT Out5 VSPS Port '
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/SIT Out5 VSPS Port '
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/SIT Out5 VSPS Port '
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/SIT Out6 VSPS Starboard'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/SIT Out6 VSPS Starboard'
                                        */
  41.0,                                /* Expression: portnum
                                        * Referenced by: '<S4>/SIT Out6 VSPS Starboard'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/SIT Out6 VSPS Starboard'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/SIT Out6 VSPS Starboard'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/SIT Out6 VSPS Starboard'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/JS_L_X'
                                        */
  3.0518509475997192E-005,             /* Expression: 1/32767
                                        * Referenced by: '<S3>/Scaling_JS_L_X'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/LabVIEW_VSPS'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S4>/Neg1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/JS_L_Y'
                                        */
  3.0518509475997192E-005,             /* Expression: 1/32767
                                        * Referenced by: '<S3>/Scaling_JS_L_Y'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S4>/Neg2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/JS_R_X'
                                        */
  3.0518509475997192E-005,             /* Expression: 1/32767
                                        * Referenced by: '<S3>/Scaling_JS_R_X'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/JS_R_Y'
                                        */
  3.0518509475997192E-005,             /* Expression: 1/32767
                                        * Referenced by: '<S3>/Scaling_JS_R_Y'
                                        */

  /*  Expression: [-1,0,1]
   * Referenced by: '<S4>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Expression: [-1,0,1]
   * Referenced by: '<S4>/Servo1'
   */
  { -1.0, 0.0, 1.0 },

  /*  Expression: reshape([0.06,0.0495363,0.043301,0.06,0.052446,0.043301,0.06,0.0541518,0.043301],3,3)
   * Referenced by: '<S4>/Servo1'
   */
  { 0.06, 0.0495363, 0.043301, 0.06, 0.052446, 0.043301, 0.06, 0.0541518,
    0.043301 },

  /*  Expression: [-1,0,1]
   * Referenced by: '<S4>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Expression: [-1,0,1]
   * Referenced by: '<S4>/Servo2'
   */
  { -1.0, 0.0, 1.0 },

  /*  Expression: reshape([0.03860880,0.0386088,0.03860880,0.0459941,0.0477243,0.0500953,0.057,0.057,0.057],3,3)
   * Referenced by: '<S4>/Servo2'
   */
  { 0.0386088, 0.0386088, 0.0386088, 0.0459941, 0.0477243, 0.0500953, 0.057,
    0.057, 0.057 },

  /*  Expression: [-1,0,1]
   * Referenced by: '<S4>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Expression: [-1,0,1]
   * Referenced by: '<S4>/Servo3'
   */
  { -1.0, 0.0, 1.0 },

  /*  Expression: reshape([0.0640809,0.0640809,0.0640809,0.0539629,0.0541315,0.0556492,0.0442664,0.0442664,0.0442664],3,3)
   * Referenced by: '<S4>/Servo3'
   */
  { 0.0640809, 0.0640809, 0.0640809, 0.0539629, 0.0541315, 0.0556492, 0.0442664,
    0.0442664, 0.0442664 },

  /*  Expression: [-1,0,1]
   * Referenced by: '<S4>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Expression: [-1,0,1]
   * Referenced by: '<S4>/Servo4'
   */
  { -1.0, 0.0, 1.0 },

  /*  Expression: reshape([0.0602867,0.0470489,0.0403879,0.0602867,0.049747,0.0403879,0.0602867,0.0526138,0.0403879],3,3)
   * Referenced by: '<S4>/Servo4'
   */
  { 0.0602867, 0.0470489, 0.0403879, 0.0602867, 0.049747, 0.0403879, 0.0602867,
    0.0526138, 0.0403879 },
  -0.02,                               /* Expression: -0.02
                                        * Referenced by: '<S4>/VPS_Speed_Gain'
                                        */
  0.05,                                /* Expression: 0.05
                                        * Referenced by: '<S4>/VPS_Power_Offset'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/SIT Out7 BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/SIT Out7 BT'
                                        */
  42.0,                                /* Expression: portnum
                                        * Referenced by: '<S4>/SIT Out7 BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/SIT Out7 BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/SIT Out7 BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/SIT Out7 BT'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/L2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/R2'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S4>/BT_D_Gain1'
                                        */
  0.05,                                /* Expression: 0.05
                                        * Referenced by: '<S4>/BT_Power_Offset1'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S4>/BT_D_Gain2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/LabVIEW_BT_Limit'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S4>/BT_L_Gain1'
                                        */
  -0.02,                               /* Expression: -0.02
                                        * Referenced by: '<S4>/BT_L_Gain2'
                                        */
  0.05,                                /* Expression: 0.05
                                        * Referenced by: '<S4>/BT_Power_Offset2'
                                        */
  0.05,                                /* Expression: 0.05
                                        * Referenced by: '<S4>/BT_Power_Offset3'
                                        */
  1.0                                  /* Expression: 1
                                        * Referenced by: '<Root>/SignalProbe'
                                        */
};
