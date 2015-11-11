/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define button_switch_P               button_switch_P DataSection(".NIVS.defaultparams")
#endif

/*
 * button_switch_data.c
 *
 * Code generation for model "button_switch".
 *
 * Model version              : 1.11
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Feb 03 14:35:05 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "button_switch.h"
#include "button_switch_private.h"

/* Block parameters (auto storage) */
P_button_switch_T button_switch_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Switch_Cross'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Switch_Cross'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Switch_Cross'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Switch_Cross'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Switch_Cross'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Switch_Cross'
                                        */
  4.0,                                 /* Expression: 4
                                        * Referenced by: '<S4>/Memory'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Switch_Square'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Switch_Square'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Switch_Square'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Switch_Square'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Switch_Square'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Switch_Square'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Switch_Circle'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Switch_Circle'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Switch_Circle'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Switch_Circle'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Switch_Circle'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Switch_Circle'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Switch_Triangle'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Switch_Triangle'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Switch_Triangle'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Switch_Triangle'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Switch_Triangle'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Switch_Triangle'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Student_Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Student_Ctrl_omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Student_Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Student_Ctrl_u_1'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Student_Ctrl_u_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Student_Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Student_Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Student_Ctrl_u_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Student_Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Student_Ctrl_u_2'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Student_Ctrl_u_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Student_Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Student_Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Student_Ctrl_u_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Student_Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Student_Ctrl_u_BT2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Student_Ctrl_u_BT2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Student_Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Student_Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Student_Ctrl_u_BT2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_1'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_2'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_BT2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_BT2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/Sixaxis_force_Ctrl_u_BT2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_alpha_2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_omega_VSP1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_omega_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_omega_VSP2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_omega_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_u_1'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_u_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_u_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_u_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_u_2'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_u_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_u_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_u_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/Ctrl_u_BT2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/Ctrl_u_BT2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/Ctrl_u_BT2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/Ctrl_u_BT2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/Sixaxis_alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/Sixaxis_alpha_1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/Sixaxis_alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/Sixaxis_alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/Sixaxis_alpha_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/Sixaxis_alpha_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/Sixaxis_alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/Sixaxis_alpha_2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/Sixaxis_alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/Sixaxis_alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/Sixaxis_alpha_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/Sixaxis_alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/Sixaxis_omega_VSP'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/Sixaxis_omega_VSP'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/Sixaxis_omega_VSP'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/Sixaxis_omega_VSP'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/Sixaxis_omega_VSP'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/Sixaxis_omega_VSP'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/Sixaxis_u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/Sixaxis_u_1'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/Sixaxis_u_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/Sixaxis_u_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/Sixaxis_u_1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/Sixaxis_u_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/Sixaxis_u_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/Sixaxis_u_2'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/Sixaxis_u_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/Sixaxis_u_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/Sixaxis_u_2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/Sixaxis_u_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/Sixaxis_u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/Sixaxis_u_BT'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/Sixaxis_u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/Sixaxis_u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/Sixaxis_u_BT'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/Sixaxis_u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/U_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/U_BT'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/U_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/U_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/U_BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/U_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/alpha_1'
                                        */
  2.0,                                 /* Expression: portnum
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
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/u_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_1'
                                        */
  3.0,                                 /* Expression: portnum
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
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/alpha_2'
                                        */
  4.0,                                 /* Expression: portnum
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
                                        * Referenced by: '<Root>/u_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/u_2'
                                        */
  5.0,                                 /* Expression: portnum
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
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/omega_VSP_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/omega_VSP_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Switch_indicator'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Switch_indicator'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Switch_indicator'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Switch_indicator'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Switch_indicator'
                                        */
  0.0                                  /* Expression: btype
                                        * Referenced by: '<Root>/Switch_indicator'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_button_switch_T_sizes[] DataSection(
  ".NIVS.defaultparamsizes") = {
  { sizeof(P_button_switch_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
