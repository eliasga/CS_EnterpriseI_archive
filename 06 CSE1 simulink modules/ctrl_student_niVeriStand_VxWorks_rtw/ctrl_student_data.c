/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define ctrl_student_P                ctrl_student_P DataSection(".NIVS.defaultparams")
#endif

/*
 * ctrl_student_data.c
 *
 * Code generation for model "ctrl_student".
 *
 * Model version              : 1.44
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Thu Mar 19 13:51:16 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "ctrl_student.h"
#include "ctrl_student_private.h"

/* Block parameters (auto storage) */
P_ctrl_student_T ctrl_student_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/psi'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/psi'
                                        */

  /*  Expression: [0 0 0]
   * Referenced by: '<S1>/Memory'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: [0 0 0]
   * Referenced by: '<S1>/Memory1'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: [0 0 0]
   * Referenced by: '<S1>/Memory2'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: [0 0 0]
   * Referenced by: '<S1>/Memory3'
   */
  { 0.0, 0.0, 0.0 },
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/alpha_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/omega_VSP1'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/omega_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/omega_VSP2'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/omega_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/alpha_VSP1'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/alpha_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/u_BT'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/u_BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/u_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/u_VSP1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/u_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/u_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/u_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/u_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/u_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/u_VSP2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/u_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/u_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/u_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/u_VSP2'
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

NI_ParamSizeWidth P_ctrl_student_T_sizes[] DataSection(".NIVS.defaultparamsizes")
  = {
  { sizeof(P_ctrl_student_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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

  { sizeof(real_T), 3, 0 },

  { sizeof(real_T), 3, 0 },

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
};

#endif
