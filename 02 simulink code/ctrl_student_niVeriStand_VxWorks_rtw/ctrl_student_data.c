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
 * Model version              : 1.57
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Dec 16 15:39:05 2015
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
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/control input u exceeds bounds'
                                        */
  8.0,                                 /* Expression: portnum
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
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/alpha_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/omega_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/omega_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/alpha_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/u_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/u_BT'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/u_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/u_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/u_BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/u_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/u_VSP1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/u_VSP2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/x_m'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/x_m'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/x_m'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/x_m'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/x_m'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/x_m'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/y_m'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/y_m'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/y_m'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/y_m'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/y_m'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/y_m'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/psi_m'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/psi_m'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/psi_m'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/psi_m'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/psi_m'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/psi_m'
                                        */
  0.05,                                /* Expression: 0.05
                                        * Referenced by: '<S1>/Low pass Gain 2'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/sample time'
                                        */
  0.05,                                /* Expression: 0.05
                                        * Referenced by: '<S1>/Low pass Gain 1'
                                        */

  /*  Expression: [0 0 0]
   * Referenced by: '<S1>/Memory3'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: [0 0 0]
   * Referenced by: '<S1>/Memory2'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: [0 0 0]
   * Referenced by: '<S1>/Memory1'
   */
  { 0.0, 0.0, 0.0 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/reset'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/reset'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/reset'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/reset'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/reset'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/reset'
                                        */

  /*  Expression: [0 0 0]'
   * Referenced by: '<S2>/Integrator2'
   */
  { 0.0, 0.0, 0.0 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S24>/b_x_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S24>/b_y_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S24>/b_psi_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S25>/x_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S25>/x_hat'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S25>/x_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S25>/x_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S25>/x_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S25>/x_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S25>/y_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S25>/y_hat'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S25>/y_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S25>/y_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S25>/y_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S25>/y_hat'
                                        */
  1.0E+10,                             /* Expression: 1e10
                                        * Referenced by: '<S23>/Saturation'
                                        */
  -1.0E+10,                            /* Expression: -1e10
                                        * Referenced by: '<S23>/Saturation'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S23>/Gain'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S23>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S25>/psi_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S16>/K_4,psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S16>/K_4,x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S16>/K_4,y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S16>/K_4,y'
                                        */

  /*  Expression: [0 0 0]'
   * Referenced by: '<S2>/Integrator1'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: M^-1
   * Referenced by: '<S2>/M^-1'
   */
  { 0.059559261465157838, 0.0, 0.0, 0.0, 0.040521023365024243,
    -0.0081427436897922364, 0.0, -0.0081427436897922364, 0.36395513377498229 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S26>/u_dot_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S26>/v_dot_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S26>/r_dot_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S27>/u_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S27>/u_hat'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S27>/u_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S27>/u_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S27>/u_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S27>/u_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S27>/v_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S27>/v_hat'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S27>/v_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S27>/v_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S27>/v_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S27>/v_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S27>/r_hat'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S27>/r_hat'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S27>/r_hat'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S27>/r_hat'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S27>/r_hat'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S27>/r_hat'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S14>/K_2,x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S14>/K_2,y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S14>/K_2,psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S15>/K_3,psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S15>/K_3,x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S15>/K_3,y'
                                        */
  50.0,                                /* Expression: 50
                                        * Referenced by: '<S2>/Constant'
                                        */
  50.0,                                /* Expression: 50
                                        * Referenced by: '<S2>/Constant1'
                                        */
  50.0,                                /* Expression: 50
                                        * Referenced by: '<S2>/Constant2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Constant3'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Constant4'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Constant5'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Constant6'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Constant7'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Constant8'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/NIVeriStandSignalProbe'
                                        */
  1U                                   /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<S1>/Delay'
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

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
