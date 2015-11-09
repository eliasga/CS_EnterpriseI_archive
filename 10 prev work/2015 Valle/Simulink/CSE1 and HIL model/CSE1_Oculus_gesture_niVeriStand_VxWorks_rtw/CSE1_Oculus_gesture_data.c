/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define CSE1_Oculus_gesture_P         CSE1_Oculus_gesture_P DataSection(".NIVS.defaultparams")
#endif

/*
 * CSE1_Oculus_gesture_data.c
 *
 * Code generation for model "CSE1_Oculus_gesture".
 *
 * Model version              : 1.30
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Thu Apr 23 10:29:55 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "CSE1_Oculus_gesture.h"
#include "CSE1_Oculus_gesture_private.h"

/* Block parameters (auto storage) */
P_CSE1_Oculus_gesture_T CSE1_Oculus_gesture_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S68>/Triangle'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S68>/Triangle'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S68>/Triangle'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S68>/Triangle'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S68>/Triangle'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S68>/Triangle'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S68>/Circle'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S68>/Circle'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S68>/Circle'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S68>/Circle'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S68>/Circle'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S68>/Circle'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S68>/Cross'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S68>/Cross'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S68>/Cross'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S68>/Cross'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S68>/Cross'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S68>/Cross'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S68>/Square'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S68>/Square'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S68>/Square'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S68>/Square'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S68>/Square'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S68>/Square'
                                        */
  4.0,                                 /* Expression: 4
                                        * Referenced by: '<S62>/Memory'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S29>/K_p_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S29>/K_p_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S29>/K_p_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S29>/K_i_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S29>/K_i_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S29>/K_i_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S29>/K_d_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S29>/K_d_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S29>/K_d_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/psi'
                                        */
  10.0,                                /* Expression: portnum
                                        * Referenced by: '<S3>/psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/psi'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S34>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S34>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S34>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S34>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/reset'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/reset'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/reset'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/reset'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/reset'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/reset'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S32>/Filter 1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S32>/Filter 2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S32>/Filter 3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/VSP_on'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S40>/zeta_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S40>/w_d_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S40>/w_d_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S40>/w_d_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S40>/zeta_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S40>/zeta_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Oculus_ref_on_off'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/psi_ref'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Oculus_yaw'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/x_ref'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/x_ref'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/x_ref'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/x_ref'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/x_ref'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/x_ref'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/y_ref'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/y_ref'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/y_ref'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/y_ref'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/y_ref'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/y_ref'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/x'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/y'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  11.0,                                /* Expression: portnum
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Gesture_off'
                                        */
  -3.2767,                             /* Expression: -32767/10000
                                        * Referenced by: '<S33>/Gain3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S41>/zeta_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S41>/w_d_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S41>/w_d_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S41>/w_d_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S41>/zeta_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S41>/zeta_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S30>/K_u'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S30>/K_u'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S30>/K_u'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S30>/K_u'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S30>/K_u'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S30>/K_u'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S30>/K_v'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S30>/K_v'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S30>/K_v'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S30>/K_v'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S30>/K_v'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S30>/K_v'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S30>/K_r'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S30>/K_r'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S30>/K_r'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S30>/K_r'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S30>/K_r'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S30>/K_r'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  13.0,                                /* Expression: portnum
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Oculus_roll'
                                        */
  -3.2767,                             /* Expression: -32767/10000
                                        * Referenced by: '<S33>/Gain1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  12.0,                                /* Expression: portnum
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Oculus_pitch'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S12>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S12>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S12>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S12>/Constant'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S19>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S19>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S19>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S19>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S18>/Integrator1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S14>/Integrator3'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S20>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S20>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S20>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S20>/Constant'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S11>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S11>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S11>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S11>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S8>/Integrator'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S46>/Constant1'
                                        */

  /*  Expression: [0 0 0]
   * Referenced by: '<S46>/Memory3'
   */
  { 0.0, 0.0, 0.0 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S65>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S65>/u_BT'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S65>/u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S65>/u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S65>/u_BT'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S65>/u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S65>/u_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S65>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S65>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S65>/u_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S65>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S65>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S64>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S64>/u_BT'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S64>/u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S64>/u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S64>/u_BT'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S64>/u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S64>/u_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S64>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S64>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S64>/u_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S64>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S64>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S66>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S66>/u_BT'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S66>/u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S66>/u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S66>/u_BT'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S66>/u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S66>/u_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S66>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S66>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S66>/u_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S66>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S66>/alpha_VSP2'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S7>/Saturation4'
                                        */
  -3.1415926535897931,                 /* Expression: -pi
                                        * Referenced by: '<S7>/Saturation4'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S7>/Saturation'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S7>/Saturation'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/u_BT'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/u_BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/u_BT'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S7>/Saturation1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Saturation1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/u_VSP1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S7>/Saturation2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Saturation2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/u_VSP2'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S7>/Saturation3'
                                        */
  -3.1415926535897931,                 /* Expression: -pi
                                        * Referenced by: '<S7>/Saturation3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S7>/Saturation5'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S7>/Saturation5'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S7>/Saturation6'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S7>/Saturation6'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/control input u exceeds bounds'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S67>/ctrl_DP_basic'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S67>/ctrl_sixaxis2force'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S67>/ctrl_sixaxis2thruster'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S67>/ctrl_student'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S14>/Integrator2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S18>/Integrator2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S18>/Integrator3'
                                        */
  -3.2767,                             /* Expression: -32767/10000
                                        * Referenced by: '<S33>/Gain2'
                                        */
  0.63661977236758138,                 /* Expression: 2/pi
                                        * Referenced by: '<S30>/Gain'
                                        */

  /*  Expression: [0 1 0; 1 0 0; 0 0 1];
   * Referenced by: '<S30>/T_b'
   */
  { 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S51>/tau_N'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S51>/tau_N'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S51>/tau_N'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S51>/tau_N'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S51>/tau_N'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S51>/tau_N'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S51>/tau_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S51>/tau_X'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S51>/tau_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S51>/tau_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S51>/tau_X'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S51>/tau_X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S51>/tau_Y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S52>/x_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S52>/x_d'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S52>/x_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S52>/x_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S52>/x_d'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S52>/x_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S52>/y_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S52>/y_d'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S52>/y_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S52>/y_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S52>/y_d'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S52>/y_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S52>/psi_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S52>/psi_d'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S52>/psi_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S52>/psi_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S52>/psi_d'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S52>/psi_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S52>/r_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S52>/r_d'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S52>/r_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S52>/r_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S52>/r_d'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S52>/r_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S52>/u_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S52>/u_d'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S52>/u_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S52>/u_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S52>/u_d'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S52>/u_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S52>/v_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S52>/v_d'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S52>/v_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S52>/v_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S52>/v_d'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S52>/v_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S52>/r_oculus'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S52>/u_oculus'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S52>/v_oculus'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S53>/r_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S53>/r_hat'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S53>/r_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S53>/r_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S53>/r_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S53>/r_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S53>/u_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S53>/u_hat'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S53>/u_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S53>/u_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S53>/u_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S53>/u_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S53>/v_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S53>/v_hat'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S53>/v_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S53>/v_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S53>/v_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S53>/v_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S54>/x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S54>/x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S54>/x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S54>/x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S54>/x'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S54>/x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S54>/y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S54>/y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S54>/y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S54>/y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S54>/y'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S54>/y'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S60>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S60>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S60>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S60>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S54>/psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S54>/psi'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S54>/psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S54>/psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S54>/psi'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S54>/psi'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/NIVeriStandSignalProbe'
                                        */
  1U                                   /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<S46>/Delay'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_CSE1_Oculus_gesture_T_sizes[] DataSection(
  ".NIVS.defaultparamsizes") = {
  { sizeof(P_CSE1_Oculus_gesture_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 3, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 9, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(uint32_T), 1, 7 },
};

#endif
