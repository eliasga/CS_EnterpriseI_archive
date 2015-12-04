/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define Oqus2SI_P                     Oqus2SI_P DataSection(".NIVS.defaultparams")
#endif

/*
 * Oqus2SI_data.c
 *
 * Code generation for model "Oqus2SI".
 *
 * Model version              : 1.5
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Mon Feb 02 16:59:11 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Oqus2SI.h"
#include "Oqus2SI_private.h"

/* Block parameters (auto storage) */
P_Oqus2SI_T Oqus2SI_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Oqus_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Oqus_X'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Oqus_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Oqus_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Oqus_X'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Oqus_X'
                                        */
  0.001,                               /* Expression: 1/1000
                                        * Referenced by: '<Root>/Gain'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_X'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_X'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_X'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Oqus_Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Oqus_Y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Oqus_Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Oqus_Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Oqus_Y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Oqus_Y'
                                        */
  0.001,                               /* Expression: 1/1000
                                        * Referenced by: '<Root>/Gain1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_Y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Oqus_Pitch'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Oqus_Pitch'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Oqus_Pitch'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Oqus_Pitch'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Oqus_Pitch'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Oqus_Pitch'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Oqus_Z'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Oqus_Z'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Oqus_Z'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Oqus_Z'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Oqus_Z'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Oqus_Z'
                                        */
  0.001,                               /* Expression: 1/1000
                                        * Referenced by: '<Root>/Gain2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_Z'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Oqus_Roll'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Oqus_Roll'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Oqus_Roll'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Oqus_Roll'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Oqus_Roll'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Oqus_Roll'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<Root>/Gain3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_phi'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<Root>/Gain4'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/SI_theta'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Oqus_Yaw'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Oqus_Yaw'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Oqus_Yaw'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Oqus_Yaw'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Oqus_Yaw'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Oqus_Yaw'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<Root>/Gain5'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<Root>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<Root>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<Root>/Gain6'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<Root>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/SI_psi'
                                        */
  0.0                                  /* Expression: btype
                                        * Referenced by: '<Root>/SI_psi'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_Oqus2SI_T_sizes[] DataSection(".NIVS.defaultparamsizes") = {
  { sizeof(P_Oqus2SI_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
