/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define sixaxis2u_alpha_P             sixaxis2u_alpha_P DataSection(".NIVS.defaultparams")
#endif

/*
 * sixaxis2u_alpha_data.c
 *
 * Code generation for model "sixaxis2u_alpha".
 *
 * Model version              : 1.21
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Feb 03 14:13:28 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "sixaxis2u_alpha.h"
#include "sixaxis2u_alpha_private.h"

/* Block parameters (auto storage) */
P_sixaxis2u_alpha_T sixaxis2u_alpha_P = {
  0.0,                                 /* Mask Parameter: DetectIncrease_vinit
                                        * Referenced by: '<S4>/Delay Input1'
                                        */
  0.0,                                 /* Mask Parameter: DetectIncrease1_vinit
                                        * Referenced by: '<S5>/Delay Input1'
                                        */
  0.0,                                 /* Mask Parameter: DetectIncrease2_vinit
                                        * Referenced by: '<S6>/Delay Input1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/L1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/L1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/L1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/L1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/L1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/L1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/PosXLeft'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/PosXLeft'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/PosXLeft'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/PosXLeft'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/PosXLeft'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/PosXLeft'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/PosYLeft'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/PosYLeft'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/PosYLeft'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/PosYLeft'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/PosYLeft'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/PosYLeft'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Gain'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Saturation'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S1>/Saturation'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/u_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/u_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/u_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/u_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/PosYRight'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/PosYRight'
                                        */
  20.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/PosYRight'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/PosYRight'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/PosYRight'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/PosYRight'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S2>/Gain'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/PosXRight'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/PosXRight'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/PosXRight'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/PosXRight'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/PosXRight'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/PosXRight'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Saturation'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S2>/Saturation'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/u_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/u_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/u_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/u_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/u_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/L2_discrete'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/L2_discrete'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/L2_discrete'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/L2_discrete'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/L2_discrete'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/L2_discrete'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/L2_cont'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/L2_cont'
                                        */
  21.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/L2_cont'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/L2_cont'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/L2_cont'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/L2_cont'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/R2_cont'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/R2_cont'
                                        */
  22.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/R2_cont'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/R2_cont'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/R2_cont'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/R2_cont'
                                        */
  -0.5,                                /* Expression: -.5
                                        * Referenced by: '<Root>/Gain'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_BT'
                                        */
  5.0,                                 /* Expression: portnum
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
                                        * Referenced by: '<Root>/R2_discrete'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/R2_discrete'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/R2_discrete'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/R2_discrete'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/R2_discrete'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/R2_discrete'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/ArrowUp'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/ArrowUp'
                                        */
  14.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/ArrowUp'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/ArrowUp'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/ArrowUp'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/ArrowUp'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/ArrowDown'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/ArrowDown'
                                        */
  17.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/ArrowDown'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/ArrowDown'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/ArrowDown'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/ArrowDown'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Start'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Start'
                                        */
  12.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Start'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Start'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Start'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Start'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Memory'
                                        */
  0.8,                                 /* Expression: 0.8
                                        * Referenced by: '<S3>/Saturation'
                                        */
  -0.8,                                /* Expression: -0.8
                                        * Referenced by: '<S3>/Saturation'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/omega_VSP'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/omega_VSP'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/omega_VSP'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/omega_VSP'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/omega_VSP'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/omega_VSP'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/R1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/R1'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/R1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/R1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/R1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/R1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Triangle'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Triangle'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Triangle'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Triangle'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Triangle'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Triangle'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Circle'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Circle'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Circle'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Circle'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Circle'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Circle'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Square'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Square'
                                        */
  10.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Square'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Square'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Square'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Square'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Cross'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Cross'
                                        */
  11.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Cross'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Cross'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Cross'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Cross'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Select'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Select'
                                        */
  13.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/Select'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Select'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Select'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Select'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/ArrowLeft'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/ArrowLeft'
                                        */
  15.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/ArrowLeft'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/ArrowLeft'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/ArrowLeft'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/ArrowLeft'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/ArrowRight'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/ArrowRight'
                                        */
  16.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/ArrowRight'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/ArrowRight'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/ArrowRight'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/ArrowRight'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/L3'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/L3'
                                        */
  18.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/L3'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/L3'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/L3'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/L3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/R3'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/R3'
                                        */
  19.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/R3'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/R3'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/R3'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/R3'
                                        */
  1.0                                  /* Expression: 1
                                        * Referenced by: '<Root>/NIVeriStandSignalProbe'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_sixaxis2u_alpha_T_sizes[] DataSection(
  ".NIVS.defaultparamsizes") = {
  { sizeof(P_sixaxis2u_alpha_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
