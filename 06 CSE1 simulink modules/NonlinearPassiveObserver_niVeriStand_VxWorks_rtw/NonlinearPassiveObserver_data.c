/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define NonlinearPassiveObserver_P    NonlinearPassiveObserver_P DataSection(".NIVS.defaultparams")
#endif

/*
 * NonlinearPassiveObserver_data.c
 *
 * Code generation for model "NonlinearPassiveObserver".
 *
 * Model version              : 1.6
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sun Mar 15 19:19:21 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "NonlinearPassiveObserver.h"
#include "NonlinearPassiveObserver_private.h"

/* Block parameters (auto storage) */
P_NonlinearPassiveObserver_T NonlinearPassiveObserver_P = {
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/reset'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/reset'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/reset'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/reset'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/reset'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/reset'
                                        */

  /*  Expression: [0 0 0]'
   * Referenced by: '<S1>/Integrator2'
   */
  { 0.0, 0.0, 0.0 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/b_x_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/b_y_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/b_psi_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/psi'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/x_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/x_hat'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/x_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/x_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/x_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/x_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/y_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/y_hat'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/y_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/y_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/y_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/y_hat'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S15>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S15>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S15>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S15>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/psi_hat'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S16>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S16>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S16>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S16>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/K_2_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/K_2_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/K_2_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/K_3_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/K_3_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/K_3_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/K_4_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/K_4_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/K_4_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S9>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S9>/u_BT'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S9>/u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S9>/u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S9>/u_BT'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S9>/u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S9>/u_VSP'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S9>/u_alpha'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S9>/u_alpha'
                                        */

  /*  Expression: [0 0 0]'
   * Referenced by: '<S1>/Integrator1'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: M^-1
   * Referenced by: '<S1>/M^-1'
   */
  { 0.059559261465157838, 0.0, 0.0, 0.0, 0.040521023365024243,
    -0.0081427436897922364, 0.0, -0.0081427436897922364, 0.36395513377498229 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/u_dot_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/v_dot_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/r_dot_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/u_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/u_hat'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/u_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/u_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/u_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/u_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/v_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/v_hat'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/v_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/v_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/v_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/v_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/r_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/r_hat'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/r_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/r_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/r_hat'
                                        */
  0.0                                  /* Expression: btype
                                        * Referenced by: '<S7>/r_hat'
                                        */
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_NonlinearPassiveObserver_T_sizes[] DataSection(
  ".NIVS.defaultparamsizes") = {
  { sizeof(P_NonlinearPassiveObserver_T), 1 },

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

  { sizeof(real_T), 3, 0 },

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
};

#endif
