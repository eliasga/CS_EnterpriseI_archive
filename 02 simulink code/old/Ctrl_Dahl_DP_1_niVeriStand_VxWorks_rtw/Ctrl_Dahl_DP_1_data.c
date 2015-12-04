/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================**/
#include "NIVERISTAND_API.h"
#if defined VXWORKS || defined kNIOSLinux
# define Ctrl_Dahl_DP_1_P              Ctrl_Dahl_DP_1_P DataSection(".NIVS.defaultparams")
#endif

/*
 * Ctrl_Dahl_DP_1_data.c
 *
 * Code generation for model "Ctrl_Dahl_DP_1".
 *
 * Model version              : 1.27
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Feb 04 17:19:35 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Ctrl_Dahl_DP_1.h"
#include "Ctrl_Dahl_DP_1_private.h"

/* Block parameters (auto storage) */
P_Ctrl_Dahl_DP_1_T Ctrl_Dahl_DP_1_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Constant'
                                        */
  0.3,                                 /* Expression: 0.3
                                        * Referenced by: '<S3>/Constant1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_X'
                                        */
  0.42,                                /* Expression: 0.42
                                        * Referenced by: '<S2>/Constant'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_X_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_Y_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_PSI_d'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_Y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_PSI'
                                        */
  0.017453292519943295,                /* Expression: pi/180
                                        * Referenced by: '<Root>/Gain'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/P_x'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/P_x'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/P_x'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/P_x'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/P_x'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/P_x'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/P_y'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/P_y'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/P_y'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/P_y'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/P_y'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/P_y'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/P_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/P_psi'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/P_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/P_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/P_psi'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/P_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_U_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  2.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_U_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  3.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_alpha_1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  4.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_alpha_2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  5.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_U_BT'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<S3>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<S3>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: portnum
                                        * Referenced by: '<S3>/Bool_VSP_omega_on_off'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<S3>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<S3>/Bool_VSP_omega_on_off'
                                        */
  1.0,                                 /* Expression: btype
                                        * Referenced by: '<S3>/Bool_VSP_omega_on_off'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  6.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp1'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  7.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/Ctrl_omega_vsp2'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/epsilon_s'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/epsilon_s'
                                        */
  8.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/epsilon_s'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/epsilon_s'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/epsilon_s'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/epsilon_s'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/epsilon_e'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/epsilon_e'
                                        */
  9.0,                                 /* Expression: portnum
                                        * Referenced by: '<Root>/epsilon_e'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/epsilon_e'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/epsilon_e'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/epsilon_e'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/epsilon_psi'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/epsilon_psi'
                                        */
  10.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/epsilon_psi'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/epsilon_psi'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/epsilon_psi'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/epsilon_psi'
                                        */
  -1.0,                                /* Expression: width
                                        * Referenced by: '<Root>/NIVeriStand Out1'
                                        */
  1.0,                                 /* Expression: dtype
                                        * Referenced by: '<Root>/NIVeriStand Out1'
                                        */
  11.0,                                /* Expression: portnum
                                        * Referenced by: '<Root>/NIVeriStand Out1'
                                        */
  -1.0,                                /* Expression: stime
                                        * Referenced by: '<Root>/NIVeriStand Out1'
                                        */
  1.0,                                 /* Expression: stype
                                        * Referenced by: '<Root>/NIVeriStand Out1'
                                        */
  0.0,                                 /* Expression: btype
                                        * Referenced by: '<Root>/NIVeriStand Out1'
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

NI_ParamSizeWidth P_Ctrl_Dahl_DP_1_T_sizes[] DataSection(
  ".NIVS.defaultparamsizes") = {
  { sizeof(P_Ctrl_Dahl_DP_1_T), 1 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

  { sizeof(real_T), 1, 0 },

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
