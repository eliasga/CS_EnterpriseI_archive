/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define HILmodel_P                    HILmodel_P DataSection(".NIVS.defaultparams")
#endif

/*
 * HILmodel_data.c
 *
 * Code generation for model "HILmodel".
 *
 * Model version              : 1.12
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sat Jan 10 18:08:25 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "HILmodel.h"
#include "HILmodel_private.h"

/* Block parameters (auto storage) */
P_HILmodel_T HILmodel_P = {
  /*  Variable: D_L
   * Referenced by: '<Root>/D_L '
   */
  { 0.59739, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 3.50625, -0.0, -0.0, -0.0, 7.25,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.1814, -0.0, -0.0, -0.0, 1.9 },

  /*  Variable: D_NLxx
   * Referenced by: '<S2>/D_NLxx '
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 1.0 },

  /*  Variable: D_NLxy
   * Referenced by: '<S3>/D_NLxy '
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 1.0 },

  /*  Variable: M_A
   * Referenced by: '<Root>/M_A'
   */
  { 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },

  /*  Variable: M_RB
   * Referenced by: '<Root>/M_RB'
   */
  { 17.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 17.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 17.6,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.76 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S1>/reset'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S1>/reset'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S1>/reset'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S1>/reset'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S1>/reset'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S1>/reset'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S13>/eta_01'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S13>/eta_01'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S13>/eta_01'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S13>/eta_01'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S13>/eta_01'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S13>/eta_01'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S13>/eta_02'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S13>/eta_02'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S13>/eta_02'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S13>/eta_02'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S13>/eta_02'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S13>/eta_02'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S13>/eta_03'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S13>/eta_03'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S13>/eta_03'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S13>/eta_03'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S13>/eta_03'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S13>/eta_03'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/eta1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/eta1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/eta1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/eta1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/eta1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/eta1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/eta2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/eta2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/eta2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/eta2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/eta2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/eta2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/eta3'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/eta3'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/eta3'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/eta3'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/eta3'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/eta3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S14>/eta_04'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S14>/eta_04'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S14>/eta_04'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S14>/eta_04'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S14>/eta_04'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S14>/eta_04'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S14>/eta_05'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S14>/eta_05'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S14>/eta_05'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S14>/eta_05'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S14>/eta_05'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S14>/eta_05'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S14>/eta_06'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S14>/eta_06'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S14>/eta_06'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S14>/eta_06'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S14>/eta_06'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S14>/eta_06'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/eta4'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/eta4'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/eta4'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/eta4'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/eta4'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/eta4'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/eta5'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/eta5'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/eta5'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/eta5'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/eta5'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/eta5'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S4>/eta6'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S4>/eta6'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S4>/eta6'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S4>/eta6'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S4>/eta6'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S4>/eta6'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S15>/eta1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S15>/eta1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S15>/eta1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S15>/eta1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S15>/eta1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S15>/eta1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S15>/eta2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S15>/eta2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S15>/eta2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S15>/eta2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S15>/eta2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S15>/eta2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S15>/eta3'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S15>/eta3'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S15>/eta3'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S15>/eta3'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S15>/eta3'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S15>/eta3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S15>/eta4'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S15>/eta4'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S15>/eta4'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S15>/eta4'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S15>/eta4'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S15>/eta4'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S15>/eta5'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S15>/eta5'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S15>/eta5'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S15>/eta5'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S15>/eta5'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S15>/eta5'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S15>/eta6'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S15>/eta6'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S15>/eta6'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S15>/eta6'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S15>/eta6'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S15>/eta6'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/nu1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/nu1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/nu1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/nu1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/nu1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/nu1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/nu2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/nu2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/nu2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/nu2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/nu2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/nu2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/nu3'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/nu3'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/nu3'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/nu3'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/nu3'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/nu3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/nu4'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/nu4'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/nu4'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/nu4'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/nu4'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/nu4'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/nu5'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/nu5'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/nu5'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/nu5'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/nu5'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/nu5'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S5>/nu6'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S5>/nu6'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S5>/nu6'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S5>/nu6'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S5>/nu6'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<S5>/nu6'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S8>/Gain'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S8>/Gain1'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S8>/Gain2'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S9>/Gain'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/nu_c1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/nu_c2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S6>/nu_c_onoff'
                                        */

  /*  Expression: zeros(6,1)
   * Referenced by: '<S6>/Constant3'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Constant2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Constant4'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S9>/Gain1'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S9>/Gain2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S11>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S11>/Constant '
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/tau1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/tau1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/tau1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/tau1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/tau1'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/tau1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/tau2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/tau2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/tau2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/tau2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/tau2'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/tau2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/tau3'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/tau3'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/tau3'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/tau3'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/tau3'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/tau3'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/tau4'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/tau4'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/tau4'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/tau4'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/tau4'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/tau4'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/tau5'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/tau5'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/tau5'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/tau5'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/tau5'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/tau5'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S7>/tau6'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S7>/tau6'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<S7>/tau6'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S7>/tau6'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S7>/tau6'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S7>/tau6'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S2>/D_NL_onoff'
                                        */

  /*  Expression: zeros(6,6)
   * Referenced by: '<S2>/D_NL=0'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/D_NL_onoff'
                                        */

  /*  Expression: zeros(6,6)
   * Referenced by: '<S3>/D_NL=0'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  Expression: zeros(6,1)
   * Referenced by: '<S12>/Constant'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  Expression: [0 1 0 0 0 1]
   * Referenced by: '<S12>/Constant1'
   */
  { 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 },

  /*  Expression: zeros(6,3)
   * Referenced by: '<S12>/Constant2'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0 }
};

#if defined VXWORKS || defined kNIOSLinux

typedef struct {
  long size;
  long width;
  long basetype;
} NI_ParamSizeWidth;

NI_ParamSizeWidth P_HILmodel_T_sizes[] DataSection(".NIVS.defaultparamsizes") =
  {
  { sizeof(P_HILmodel_T), 1 },

  { sizeof(real_T), 36, 0 },

  { sizeof(real_T), 36, 0 },

  { sizeof(real_T), 36, 0 },

  { sizeof(real_T), 36, 0 },

  { sizeof(real_T), 36, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 6, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 36, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 36, 0 },

  { sizeof(real_T), 6, 0 },

  { sizeof(real_T), 6, 0 },

  { sizeof(real_T), 18, 0 },
};

#endif
