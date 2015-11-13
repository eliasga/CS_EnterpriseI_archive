/*
 * modell.c
 *
 * Real-Time Workshop code generation for Simulink model "modell.mdl".
 *
 * Model Version              : 1.146
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Tue Mar 12 12:25:25 2013
 *
 * Target selection: grt.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "modell.h"
#include "modell_private.h"

/* Block signals (auto storage) */
BlockIO_modell modell_B;

/* Continuous states */
ContinuousStates_modell modell_X;

/* Block states (auto storage) */
D_Work_modell modell_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_modell modell_PrevZCSigState;

/* Real-time model */
RT_MODEL_modell modell_M_;
RT_MODEL_modell *modell_M = &modell_M_;

/* This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 57;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y,x,
                nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  modell_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++)
    x[i] = y[i] + (temp*f0[i]);
  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  modell_output(0);
  modell_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++)
    x[i] = y[i] + (temp*f1[i]);
  rtsiSetdX(si, f2);
  modell_output(0);
  modell_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++)
    x[i] = y[i] + (h*f2[i]);
  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  modell_output(0);
  modell_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Output and update for action system:
 *   '<S32>/if'
 *   '<S32>/else'
 *   '<S33>/if'
 *   '<S33>/else'
 *   '<S34>/if'
 *   '<S34>/else'
 *   '<S35>/if'
 *   '<S35>/else'
 */
void modell_if(real_T rtu_0, rtB_if_modell *localB)
{
  /* Inport: '<S37>/In1' */
  localB->In1 = rtu_0;
}

/* Output and update for action system:
 *   '<S44>/slack'
 *   '<S44>/rupture'
 *   '<S44>/towing'
 */
void modell_slack(const real_T rtu_0[3], rtB_slack_modell *localB)
{
  /* Inport: '<S49>/In1' */
  localB->In1[0] = rtu_0[0];
  localB->In1[1] = rtu_0[1];
  localB->In1[2] = rtu_0[2];
}

/* Model output function */
void modell_output(int_T tid)
{
  /* local block i/o variables */
  real_T rtb_T_temp[3];
  real_T rtb_Sum4_l[3];

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(modell_M)) {
    modell_M->Timing.t[0] = rtsiGetT(&modell_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(modell_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&modell_M->solverInfo,
                          ((modell_M->Timing.clockTick0+1)*
      modell_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T rtb_Row3_n;
    int8_T rtAction;
    real_T rtb_wavehat[6];
    real_T rtb_K_3[3];
    real_T rtb_K_2[3];
    real_T rtb_K_1[6];
    real_T rtb_TmpHiddenBufferAtProductInp[5];
    real_T rtb_UkYk1;
    real_T rtb_T_i_inv[3];
    real_T rtb_Row3_g;
    real_T rtb_Reg_e_N_hil;
    real_T rtb_Sum_n;
    real_T rtb_Row1_e;
    real_T rtb_Sum_p[3];
    real_T rtb_Product1_o[5];
    int32_T i;
    real_T tmp[3];
    real_T tmp_0[3];
    real_T tmp_1[3];
    real_T tmp_2[15];
    int32_T tmp_3;
    real_T tmp_4[4];
    real_T tmp_5[4];
    real_T tmp_6[4];
    real_T tmp_7[4];
    real_T tmp_8[4];
    real_T tmp_9[4];
    real_T tmp_a[4];
    real_T tmp_b[4];
    real_T tmp_c[4];
    real_T tmp_d[4];
    real_T tmp_e[4];
    real_T tmp_f[4];
    real_T tmp_g[4];
    real_T tmp_h[4];
    real_T tmp_i[4];
    real_T tmp_j[4];
    real_T tmp_k[4];
    real_T tmp_l[4];
    real_T tmp_m[3];
    real_T tmp_n[6];
    real_T tmp_o[6];
    real_T tmp_p[3];
    int32_T tmp_q;
    real_T rtb_Integrator_idx;
    real_T rtb_Integrator_idx_0;
    real_T rtb_Integrator_idx_1;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Constant: '<Root>/Constant' */
      modell_B.Constant = modell_P.Constant_Value;
    }

    /* Integrator: '<S2>/Integrator1' incorporates:
     *  Constant: '<S2>/reset_eta_hil'
     */
    if (rtmIsMajorTimeStep(modell_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &modell_PrevZCSigState.Integrator1_Reset_ZCE,
                         modell_P.reset_eta_hil_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || modell_P.reset_eta_hil_Value != 0.0 ||
          modell_DWork.Integrator1_IWORK.IcNeedsLoading) {
        modell_X.Integrator1_CSTATE[0] = modell_B.Constant;
        modell_X.Integrator1_CSTATE[1] = modell_B.Constant;
        modell_X.Integrator1_CSTATE[2] = modell_B.Constant;
      }

      modell_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
    }

    modell_B.Integrator1[0] = modell_X.Integrator1_CSTATE[0];
    modell_B.Integrator1[1] = modell_X.Integrator1_CSTATE[1];
    modell_B.Integrator1[2] = modell_X.Integrator1_CSTATE[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace' */
      {
        double locTime = modell_M->Timing.t[1];
        rt_UpdateStructLogVar((StructLogVar *)
                              modell_DWork.ToWorkspace_PWORK.LoggedData,
                              &locTime, modell_B.Integrator1);
      }

      /* Constant: '<S2>/initial_nu_hil' */
      modell_B.initial_nu_hil[0] = modell_P.initial_nu_hil_Value[0];
      modell_B.initial_nu_hil[1] = modell_P.initial_nu_hil_Value[1];
      modell_B.initial_nu_hil[2] = modell_P.initial_nu_hil_Value[2];
    }

    /* Integrator: '<S2>/Integrator' incorporates:
     *  Constant: '<S2>/reset_eta_hil'
     */
    if (rtmIsMajorTimeStep(modell_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &modell_PrevZCSigState.Integrator_Reset_ZCE,
                         modell_P.reset_eta_hil_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || modell_P.reset_eta_hil_Value != 0.0 ||
          modell_DWork.Integrator_IWORK.IcNeedsLoading) {
        modell_X.Integrator_CSTATE[0] = modell_B.initial_nu_hil[0];
        modell_X.Integrator_CSTATE[1] = modell_B.initial_nu_hil[1];
        modell_X.Integrator_CSTATE[2] = modell_B.initial_nu_hil[2];
      }

      modell_DWork.Integrator_IWORK.IcNeedsLoading = 0;
    }

    rtb_Sum4_l[0] = modell_X.Integrator_CSTATE[0];
    rtb_Sum4_l[1] = modell_X.Integrator_CSTATE[1];
    rtb_Sum4_l[2] = modell_X.Integrator_CSTATE[2];

    /* Gain: '<S2>/nu_surge_hil' */
    modell_B.nu_surge_hil = modell_P.nu_surge_hil_Gain * rtb_Sum4_l[0];

    /* Gain: '<S2>/nu_sway_hil' */
    modell_B.nu_sway_hil = modell_P.nu_sway_hil_Gain * rtb_Sum4_l[1];

    /* Gain: '<S2>/nu_yaw_hil' */
    modell_B.nu_yaw_hil = modell_P.nu_yaw_hil_Gain * rtb_Sum4_l[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace1' */
      {
        real_T u[3];
        u[0] = modell_B.nu_surge_hil;
        u[1] = modell_B.nu_sway_hil;
        u[2] = modell_B.nu_yaw_hil;
        rt_UpdateStructLogVar((StructLogVar *)
                              modell_DWork.ToWorkspace1_PWORK.LoggedData, (NULL),
                              u);
      }
    }

    /* TransferFcn Block: '<S5>/Transfer Fcn' */
    modell_B.TransferFcn = modell_P.TransferFcn_C*modell_X.TransferFcn_CSTATE;

    /* TransferFcn Block: '<S5>/Transfer Fcn1' */
    modell_B.TransferFcn1 = modell_P.TransferFcn1_C*modell_X.TransferFcn1_CSTATE;

    /* TransferFcn Block: '<S5>/Transfer Fcn2' */
    modell_B.TransferFcn2 = modell_P.TransferFcn2_C*modell_X.TransferFcn2_CSTATE;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace4' */
      {
        real_T u[3];
        u[0] = modell_B.TransferFcn;
        u[1] = modell_B.TransferFcn1;
        u[2] = modell_B.TransferFcn2;
        rt_UpdateStructLogVar((StructLogVar *)
                              modell_DWork.ToWorkspace4_PWORK.LoggedData, (NULL),
                              u);
      }

      /* Constant: '<S3>/initial position' */
      modell_B.initialposition[0] = modell_P.initialposition_Value[0];
      modell_B.initialposition[1] = modell_P.initialposition_Value[1];
      modell_B.initialposition[2] = modell_P.initialposition_Value[2];
    }

    /* Integrator: '<S3>/Integrator1' */
    if (modell_DWork.Integrator1_IWORK_j.IcNeedsLoading) {
      modell_X.Integrator1_CSTATE_e[0] = modell_B.initialposition[0];
      modell_X.Integrator1_CSTATE_e[1] = modell_B.initialposition[1];
      modell_X.Integrator1_CSTATE_e[2] = modell_B.initialposition[2];
      modell_DWork.Integrator1_IWORK_j.IcNeedsLoading = 0;
    }

    modell_B.Integrator1_e[0] = modell_X.Integrator1_CSTATE_e[0];
    modell_B.Integrator1_e[1] = modell_X.Integrator1_CSTATE_e[1];
    modell_B.Integrator1_e[2] = modell_X.Integrator1_CSTATE_e[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace2' */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace2_PWORK.LoggedData, (NULL),
                            modell_B.Integrator1_e);
    }

    /* Integrator: '<S3>/Integrator2' */
    modell_B.Integrator2[0] = modell_X.Integrator2_CSTATE[0];
    modell_B.Integrator2[1] = modell_X.Integrator2_CSTATE[1];
    modell_B.Integrator2[2] = modell_X.Integrator2_CSTATE[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace3' */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace3_PWORK.LoggedData, (NULL),
                            modell_B.Integrator2);

      /* Constant: '<S12>/pos_diff' */
      modell_B.pos_diff[0] = modell_P.pos_diff_Value[0];
      modell_B.pos_diff[1] = modell_P.pos_diff_Value[1];
      modell_B.pos_diff[2] = modell_P.pos_diff_Value[2];
    }

    /* Integrator: '<S12>/Integrator' */
    if (modell_DWork.Integrator_IWORK_o.IcNeedsLoading) {
      modell_X.Integrator_CSTATE_e[0] = modell_B.pos_diff[0];
      modell_X.Integrator_CSTATE_e[1] = modell_B.pos_diff[1];
      modell_X.Integrator_CSTATE_e[2] = modell_B.pos_diff[2];
      modell_DWork.Integrator_IWORK_o.IcNeedsLoading = 0;
    }

    modell_B.Integrator[0] = modell_X.Integrator_CSTATE_e[0];
    modell_B.Integrator[1] = modell_X.Integrator_CSTATE_e[1];
    modell_B.Integrator[2] = modell_X.Integrator_CSTATE_e[2];

    /* Sum: '<S46>/Sum' incorporates:
     *  Math: '<S46>/mf1'
     *  Math: '<S46>/mf2'
     */
    rtb_Row3_n = modell_B.Integrator[0] * modell_B.Integrator[0] +
      modell_B.Integrator[1] * modell_B.Integrator[1];

    /* Math: '<S46>/mf3' */
    if (rtb_Row3_n < 0.0) {
      modell_B.mf3 = -sqrt(-rtb_Row3_n);
    } else {
      modell_B.mf3 = sqrt(rtb_Row3_n);
    }

    /* Product: '<S44>/T_temp' incorporates:
     *  Constant: '<S44>/K_tow'
     */
    for (i = 0; i < 3; i++) {
      rtb_T_temp[i] = 0.0;
      rtb_T_temp[i] += modell_P.K_tow_Value[i] * modell_B.Integrator[0];
      rtb_T_temp[i] += modell_P.K_tow_Value[i + 3] * modell_B.Integrator[1];
      rtb_T_temp[i] += modell_P.K_tow_Value[i + 6] * modell_B.Integrator[2];
    }

    /* Sum: '<S47>/Sum' incorporates:
     *  Math: '<S47>/mf1'
     *  Math: '<S47>/mf2'
     */
    rtb_Row3_n = rtb_T_temp[0] * rtb_T_temp[0] + rtb_T_temp[1] * rtb_T_temp[1];

    /* Math: '<S47>/mf3' */
    if (rtb_Row3_n < 0.0) {
      rtb_Row3_n = -sqrt(-rtb_Row3_n);
    } else {
      rtb_Row3_n = sqrt(rtb_Row3_n);
    }

    /* If: '<S44>/If' incorporates:
     *  ActionPort: '<S48>/Action Port'
     *  ActionPort: '<S49>/Action Port'
     *  ActionPort: '<S50>/Action Port'
     *  Constant: '<S44>/T_cr'
     *  Constant: '<S44>/Towline length'
     *  SubSystem: '<S44>/rupture'
     *  SubSystem: '<S44>/slack'
     *  SubSystem: '<S44>/towing'
     */
    if (rtmIsMajorTimeStep(modell_M) != 0) {
      if (modell_P.Towlinelength_Value > modell_B.mf3) {
        rtAction = 0;
      } else if (rtb_Row3_n > modell_P.T_cr_Value) {
        rtAction = 1;
      } else {
        rtAction = 2;
      }

      modell_DWork.If_ActiveSubsystem = rtAction;
    } else {
      rtAction = modell_DWork.If_ActiveSubsystem;
    }

    switch (rtAction) {
     case 0:
      modell_slack(&modell_P.T_zero_Value[0], &modell_B.slack);
      break;

     case 1:
      modell_slack(&modell_P.T_zero_Value[0], &modell_B.rupture);
      break;

     case 2:
      modell_slack(rtb_T_temp, &modell_B.towing);
      break;
    }

    /* Sum: '<S44>/Sum2' */
    modell_B.Sum2[0] = (modell_B.slack.In1[0] + modell_B.rupture.In1[0]) +
      modell_B.towing.In1[0];
    modell_B.Sum2[1] = (modell_B.slack.In1[1] + modell_B.rupture.In1[1]) +
      modell_B.towing.In1[1];
    modell_B.Sum2[2] = (modell_B.slack.In1[2] + modell_B.rupture.In1[2]) +
      modell_B.towing.In1[2];

    /* InitialCondition: '<S12>/IC' */
    if ((modell_DWork.IC_FirstOutputTime == (rtMinusInf)) ||
        (modell_DWork.IC_FirstOutputTime == modell_M->Timing.t[0])) {
      modell_DWork.IC_FirstOutputTime = modell_M->Timing.t[0];
      modell_B.IC[0] = modell_P.IC_Value[0];
      modell_B.IC[1] = modell_P.IC_Value[1];
      modell_B.IC[2] = modell_P.IC_Value[2];
    } else {
      modell_B.IC[0] = modell_B.Sum2[0];
      modell_B.IC[1] = modell_B.Sum2[1];
      modell_B.IC[2] = modell_B.Sum2[2];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace5' */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace5_PWORK.LoggedData, (NULL),
                            modell_B.IC);

      /* ToWorkspace: '<S10>/To Workspace6' */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace6_PWORK.LoggedData, (NULL),
                            &modell_B.mf3);
    }

    /* Integrator: '<S13>/Integrator' */
    rtb_Integrator_idx = modell_X.Integrator_CSTATE_m[0];
    rtb_Integrator_idx_0 = modell_X.Integrator_CSTATE_m[1];
    rtb_Integrator_idx_1 = modell_X.Integrator_CSTATE_m[2];

    /* Switch: '<S52>/SwitchControl' incorporates:
     *  Constant: '<S13>/zero'
     *  Constant: '<S52>/Constant'
     *  Fcn: '<S54>/Row1'
     *  Fcn: '<S54>/Row2'
     *  Fcn: '<S54>/Row3'
     */
    if (modell_P.Constant_Value_ow > modell_P.SwitchControl_Threshold) {
      modell_B.SwitchControl[0] = cos(modell_B.Integrator1[2]) *
        modell_X.Integrator_CSTATE_m[0] + sin(modell_B.Integrator1[2]) *
        modell_X.Integrator_CSTATE_m[1];
      modell_B.SwitchControl[1] = (-sin(modell_B.Integrator1[2])) *
        modell_X.Integrator_CSTATE_m[0] + cos(modell_B.Integrator1[2]) *
        modell_X.Integrator_CSTATE_m[1];
      modell_B.SwitchControl[2] = modell_X.Integrator_CSTATE_m[2];
    } else {
      modell_B.SwitchControl[0] = modell_P.zero_Value;
      modell_B.SwitchControl[1] = modell_P.zero_Value;
      modell_B.SwitchControl[2] = modell_P.zero_Value;
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace7' */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace7_PWORK.LoggedData, (NULL),
                            modell_B.SwitchControl);
    }

    /* Integrator: '<S8>/wave hat' */
    for (i = 0; i < 6; i++) {
      rtb_wavehat[i] = modell_X.wavehat_CSTATE[i];
    }

    /* Sum: '<S8>/Sum6' incorporates:
     *  Gain: '<S8>/C_w'
     *  Integrator: '<S8>/eta_hat'
     */
    for (i = 0; i < 3; i++) {
      tmp[i] = 0.0;
      for (tmp_q = 0; tmp_q < 6; tmp_q++) {
        tmp[i] += modell_P.C_w_Gain[3 * tmp_q + i] *
          modell_X.wavehat_CSTATE[tmp_q];
      }

      modell_B.Sum6[i] = tmp[i] + modell_X.eta_hat_CSTATE[i];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace8' */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace8_PWORK.LoggedData, (NULL),
                            modell_B.Sum6);
    }

    /* Integrator: '<S8>/nu_hat' */
    modell_B.nu_hat[0] = modell_X.nu_hat_CSTATE[0];
    modell_B.nu_hat[1] = modell_X.nu_hat_CSTATE[1];
    modell_B.nu_hat[2] = modell_X.nu_hat_CSTATE[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace9' */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace9_PWORK.LoggedData, (NULL),
                            modell_B.nu_hat);
    }

    /* Integrator: '<S7>/wave hat' */
    for (i = 0; i < 6; i++) {
      rtb_K_1[i] = modell_X.wavehat_CSTATE_g[i];
    }

    /* Sum: '<S7>/Sum6' incorporates:
     *  Gain: '<S7>/C_w'
     *  Integrator: '<S7>/eta_hat'
     */
    for (i = 0; i < 3; i++) {
      tmp_0[i] = 0.0;
      for (tmp_q = 0; tmp_q < 6; tmp_q++) {
        tmp_0[i] += modell_P.C_w_Gain_d[3 * tmp_q + i] *
          modell_X.wavehat_CSTATE_g[tmp_q];
      }

      modell_B.Sum6_a[i] = tmp_0[i] + modell_X.eta_hat_CSTATE_b[i];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace10' */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace10_PWORK.LoggedData, (NULL),
                            modell_B.Sum6_a);
    }

    /* Integrator: '<S7>/nu_hat' */
    modell_B.nu_hat_n[0] = modell_X.nu_hat_CSTATE_g[0];
    modell_B.nu_hat_n[1] = modell_X.nu_hat_CSTATE_g[1];
    modell_B.nu_hat_n[2] = modell_X.nu_hat_CSTATE_g[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace: '<S10>/To Workspace11' */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace11_PWORK.LoggedData, (NULL),
                            modell_B.nu_hat_n);

      /* RelationalOperator: '<S14>/Compare' incorporates:
       *  Constant: '<Root>/MODE'
       *  Constant: '<S14>/Constant'
       */
      modell_B.Compare = (modell_P.MODE_Value == modell_P.Constant_Value_j);
    }

    /* Outputs for enable SubSystem: '<Root>/DP controller' incorporates:
     *  EnablePort: '<S1>/Enable'
     */
    if (rtmIsMajorTimeStep(modell_M) && rtmIsMajorTimeStep(modell_M)) {
      if (modell_B.Compare > 0) {
        if (modell_DWork.DPcontroller_MODE == SUBSYS_DISABLED) {
          /* InitializeConditions for Integrator: '<S15>/Integrator' */
          modell_X.Integrator_CSTATE_p[0] = modell_P.Integrator_IC_l;
          modell_X.Integrator_CSTATE_p[1] = modell_P.Integrator_IC_l;
          modell_X.Integrator_CSTATE_p[2] = modell_P.Integrator_IC_l;
          modell_DWork.DPcontroller_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (modell_DWork.DPcontroller_MODE == SUBSYS_ENABLED) {
          modell_DWork.DPcontroller_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (modell_DWork.DPcontroller_MODE == SUBSYS_ENABLED) {
      /* Saturate: '<S18>/Saturation' incorporates:
       *  Fcn: '<S15>/yaw angle'
       */
      rtb_Row3_g = rt_SATURATE(modell_B.Integrator1[2],
        modell_P.Saturation_LowerSat_b, modell_P.Saturation_UpperSat_i);

      /* Gain: '<S18>/Gain' incorporates:
       *  Signum: '<S18>/Sign'
       */
      rtb_Reg_e_N_hil = modell_P.Gain_Gain_i * rt_SIGNd_snf(rtb_Row3_g);

      /* Sum: '<S18>/Sum1' */
      rtb_Row3_g += rtb_Reg_e_N_hil;

      /* Math: '<S18>/Math Function' incorporates:
       *  Constant: '<S18>/Constant'
       */
      rtb_Row3_g = rt_rem_snf(rtb_Row3_g, modell_P.Constant_Value_jb);

      /* Sum: '<S18>/Sum' */
      rtb_Row3_g -= rtb_Reg_e_N_hil;

      /* Gain: '<S15>/Reg_e_N_hil' incorporates:
       *  Sum: '<S15>/Sum2'
       */
      rtb_Reg_e_N_hil = (modell_B.TransferFcn - modell_B.Integrator1[0]) *
        modell_P.Reg_e_N_hil_Gain;

      /* Gain: '<S15>/Reg_e_E_hil' incorporates:
       *  Sum: '<S15>/Sum2'
       */
      rtb_Row3_n = (modell_B.TransferFcn1 - modell_B.Integrator1[1]) *
        modell_P.Reg_e_E_hil_Gain;

      /* Gain: '<S15>/Reg_e_Psi_hil' incorporates:
       *  Sum: '<S15>/Sum2'
       */
      rtb_Sum_n = (modell_B.TransferFcn2 - modell_B.Integrator1[2]) *
        modell_P.Reg_e_Psi_hil_Gain;

      /* Saturate: '<S17>/Saturation' */
      rtb_Sum_n = rt_SATURATE(rtb_Sum_n, modell_P.Saturation_LowerSat_n,
        modell_P.Saturation_UpperSat_e);

      /* Gain: '<S17>/Gain' incorporates:
       *  Signum: '<S17>/Sign'
       */
      rtb_Row1_e = modell_P.Gain_Gain_k * rt_SIGNd_snf(rtb_Sum_n);

      /* Sum: '<S17>/Sum1' */
      rtb_Sum_n += rtb_Row1_e;

      /* Math: '<S17>/Math Function' incorporates:
       *  Constant: '<S17>/Constant'
       */
      rtb_Sum_n = rt_rem_snf(rtb_Sum_n, modell_P.Constant_Value_f);

      /* Sum: '<S17>/Sum' */
      rtb_Sum_n -= rtb_Row1_e;

      /* Fcn: '<S16>/Row1' */
      rtb_Row1_e = cos(rtb_Row3_g) * rtb_Reg_e_N_hil + sin(rtb_Row3_g) *
        rtb_Row3_n;

      /* Fcn: '<S16>/Row2' */
      rtb_Reg_e_N_hil = (-sin(rtb_Row3_g)) * rtb_Reg_e_N_hil + cos(rtb_Row3_g) *
        rtb_Row3_n;

      /* SignalConversion: '<S15>/TmpHiddenBufferAtKpInport1' incorporates:
       *  Fcn: '<S16>/Row3'
       */
      modell_B.TmpHiddenBufferAtKpInport1[0] = rtb_Row1_e;
      modell_B.TmpHiddenBufferAtKpInport1[1] = rtb_Reg_e_N_hil;
      modell_B.TmpHiddenBufferAtKpInport1[2] = rtb_Sum_n;

      /* Sum: '<S15>/Sum1' incorporates:
       *  Constant: '<S15>/Kd_scale'
       *  Constant: '<S15>/Ki_scale'
       *  Constant: '<S15>/Kp_scale'
       *  Gain: '<S15>/Kd'
       *  Gain: '<S15>/Ki'
       *  Gain: '<S15>/Kp'
       *  Integrator: '<S15>/Integrator'
       *  Product: '<S15>/Product'
       *  Product: '<S15>/Product1'
       *  Product: '<S15>/Product2'
       *  SignalConversion: '<S15>/TmpHiddenBufferAtKdInport1'
       *  Sum: '<S15>/Sum3'
       */
      for (i = 0; i < 3; i++) {
        tmp_1[i] = 0.0;
        tmp_1[i] += modell_P.Kp_Gain[i] * modell_B.TmpHiddenBufferAtKpInport1[0];
        tmp_1[i] += modell_P.Kp_Gain[i + 3] *
          modell_B.TmpHiddenBufferAtKpInport1[1];
        tmp_1[i] += modell_P.Kp_Gain[i + 6] *
          modell_B.TmpHiddenBufferAtKpInport1[2];
        tmp[i] = 0.0;
        tmp[i] += modell_P.Ki_Gain[i] * modell_X.Integrator_CSTATE_p[0];
        tmp[i] += modell_P.Ki_Gain[i + 3] * modell_X.Integrator_CSTATE_p[1];
        tmp[i] += modell_P.Ki_Gain[i + 6] * modell_X.Integrator_CSTATE_p[2];
        tmp_0[i] = 0.0;
        tmp_0[i] += modell_P.Kd_Gain[i] * modell_B.nu_surge_hil;
        tmp_0[i] += modell_P.Kd_Gain[i + 3] * modell_B.nu_sway_hil;
        tmp_0[i] += modell_P.Kd_Gain[i + 6] * modell_B.nu_yaw_hil;
        modell_B.Sum1_h[i] = (modell_P.Kp_scale_Value * tmp_1[i] + tmp[i] *
                              modell_P.Ki_scale_Value) - tmp_0[i] *
          modell_P.Kd_scale_Value;
      }
    }

    /* end of Outputs for SubSystem: '<Root>/DP controller' */

    /* Gain: '<S2>/D' */
    for (i = 0; i < 3; i++) {
      rtb_K_2[i] = 0.0;
      rtb_K_2[i] += modell_P.D_Gain[i] * rtb_Sum4_l[0];
      rtb_K_2[i] += modell_P.D_Gain[i + 3] * rtb_Sum4_l[1];
      rtb_K_2[i] += modell_P.D_Gain[i + 6] * rtb_Sum4_l[2];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* Abs: '<S33>/Abs' incorporates:
       *  Constant: '<S9>/PS3_L_JS_Y'
       */
      modell_B.Abs = fabs(modell_P.PS3_L_JS_Y_Value);

      /* Gain: '<S9>/Gain1' incorporates:
       *  Constant: '<S9>/PS3_L_JS_Y'
       */
      modell_B.Gain1 = modell_P.Gain1_Gain * modell_P.PS3_L_JS_Y_Value;
    }

    /* If: '<S33>/If' incorporates:
     *  ActionPort: '<S38>/Action Port'
     *  ActionPort: '<S39>/Action Port'
     *  Constant: '<S9>/limit_L_JS_Y'
     *  SubSystem: '<S33>/else'
     *  SubSystem: '<S33>/if'
     */
    if (rtmIsMajorTimeStep(modell_M) != 0) {
      if (modell_B.Abs < modell_P.limit_L_JS_Y_Value) {
        rtAction = 0;
      } else {
        rtAction = 1;
      }

      modell_DWork.If_ActiveSubsystem_p = rtAction;
    } else {
      rtAction = modell_DWork.If_ActiveSubsystem_p;
    }

    switch (rtAction) {
     case 0:
      modell_if(modell_P.Constant2_Value, &modell_B.if_f);
      break;

     case 1:
      modell_if(modell_B.Gain1, &modell_B.else_a);
      break;
    }

    /* Sum: '<S33>/Sum' */
    modell_B.Sum = modell_B.if_f.In1 + modell_B.else_a.In1;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Abs: '<S32>/Abs' incorporates:
       *  Constant: '<S9>/PS3_L_JS_X'
       */
      modell_B.Abs_n = fabs(modell_P.PS3_L_JS_X_Value);

      /* Gain: '<S9>/Gain' incorporates:
       *  Constant: '<S9>/PS3_L_JS_X'
       */
      modell_B.Gain = modell_P.Gain_Gain * modell_P.PS3_L_JS_X_Value;
    }

    /* If: '<S32>/If' incorporates:
     *  ActionPort: '<S36>/Action Port'
     *  ActionPort: '<S37>/Action Port'
     *  Constant: '<S9>/limit_L_JS_X'
     *  SubSystem: '<S32>/else'
     *  SubSystem: '<S32>/if'
     */
    if (rtmIsMajorTimeStep(modell_M) != 0) {
      if (modell_B.Abs_n < modell_P.limit_L_JS_X_Value) {
        rtAction = 0;
      } else {
        rtAction = 1;
      }

      modell_DWork.If_ActiveSubsystem_j = rtAction;
    } else {
      rtAction = modell_DWork.If_ActiveSubsystem_j;
    }

    switch (rtAction) {
     case 0:
      modell_if(modell_P.Constant2_Value_j, &modell_B.if_j);
      break;

     case 1:
      modell_if(modell_B.Gain, &modell_B.else_j);
      break;
    }

    /* Sum: '<S32>/Sum' */
    modell_B.Sum_i = modell_B.if_j.In1 + modell_B.else_j.In1;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Abs: '<S35>/Abs' incorporates:
       *  Constant: '<S9>/PS3_R_JS_Y'
       */
      modell_B.Abs_o = fabs(modell_P.PS3_R_JS_Y_Value);

      /* Gain: '<S9>/Gain3' incorporates:
       *  Constant: '<S9>/PS3_R_JS_Y'
       */
      modell_B.Gain3 = modell_P.Gain3_Gain * modell_P.PS3_R_JS_Y_Value;
    }

    /* If: '<S35>/If' incorporates:
     *  ActionPort: '<S42>/Action Port'
     *  ActionPort: '<S43>/Action Port'
     *  Constant: '<S9>/limit_R_JS_Y'
     *  SubSystem: '<S35>/else'
     *  SubSystem: '<S35>/if'
     */
    if (rtmIsMajorTimeStep(modell_M) != 0) {
      if (modell_B.Abs_o < modell_P.limit_R_JS_Y_Value) {
        rtAction = 0;
      } else {
        rtAction = 1;
      }

      modell_DWork.If_ActiveSubsystem_jx = rtAction;
    } else {
      rtAction = modell_DWork.If_ActiveSubsystem_jx;
    }

    switch (rtAction) {
     case 0:
      modell_if(modell_P.Constant2_Value_f, &modell_B.if_k);
      break;

     case 1:
      modell_if(modell_B.Gain3, &modell_B.else_aj);
      break;
    }

    /* Sum: '<S35>/Sum' */
    modell_B.Sum_e = modell_B.if_k.In1 + modell_B.else_aj.In1;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Abs: '<S34>/Abs' incorporates:
       *  Constant: '<S9>/PS3_R_JS_X'
       */
      modell_B.Abs_d = fabs(modell_P.PS3_R_JS_X_Value);

      /* Gain: '<S9>/Gain2' incorporates:
       *  Constant: '<S9>/PS3_R_JS_X'
       */
      modell_B.Gain2 = modell_P.Gain2_Gain * modell_P.PS3_R_JS_X_Value;
    }

    /* If: '<S34>/If' incorporates:
     *  ActionPort: '<S40>/Action Port'
     *  ActionPort: '<S41>/Action Port'
     *  Constant: '<S9>/limit_R_JS_X'
     *  SubSystem: '<S34>/else'
     *  SubSystem: '<S34>/if'
     */
    if (rtmIsMajorTimeStep(modell_M) != 0) {
      if (modell_B.Abs_d < modell_P.limit_R_JS_X_Value) {
        rtAction = 0;
      } else {
        rtAction = 1;
      }

      modell_DWork.If_ActiveSubsystem_m = rtAction;
    } else {
      rtAction = modell_DWork.If_ActiveSubsystem_m;
    }

    switch (rtAction) {
     case 0:
      modell_if(modell_P.Constant2_Value_o, &modell_B.if_i);
      break;

     case 1:
      modell_if(modell_B.Gain2, &modell_B.else_d);
      break;
    }

    /* Sum: '<S34>/Sum' */
    modell_B.Sum_d = modell_B.if_i.In1 + modell_B.else_d.In1;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Gain: '<S9>/g1' incorporates:
       *  Constant: '<S9>/Constant'
       *  Constant: '<S9>/PS3_L2'
       *  Sum: '<S9>/Sum3'
       */
      modell_B.g1 = (modell_P.PS3_L2_Value + modell_P.Constant_Value_o) *
        modell_P.g1_Gain;

      /* Gain: '<S9>/g2' incorporates:
       *  Constant: '<S9>/Constant1'
       *  Constant: '<S9>/PS3_R2'
       *  Sum: '<S9>/Sum4'
       */
      modell_B.g2 = (modell_P.PS3_R2_Value + modell_P.Constant1_Value_a) *
        modell_P.g2_Gain;

      /* Product: '<S4>/Product' incorporates:
       *  Constant: '<S4>/Ke^-1'
       *  Constant: '<S4>/Te^+'
       */
      for (i = 0; i < 5; i++) {
        for (tmp_q = 0; tmp_q < 3; tmp_q++) {
          modell_B.Product[i + 5 * tmp_q] = 0.0;
          for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
            modell_B.Product[i + 5 * tmp_q] = modell_P.Ke1_Value[5 * tmp_3 + i] *
              modell_P.Te_Value[5 * tmp_q + tmp_3] + modell_B.Product[5 * tmp_q
              + i];
          }
        }
      }
    }

    /* Product: '<S4>/Product1' incorporates:
     *  Gain: '<S4>/joystick_gain_surge'
     *  Gain: '<S4>/joystick_gain_sway'
     *  Gain: '<S4>/joystick_gain_yaw'
     *  SignalConversion: '<S4>/TmpHiddenBufferAtProduct1Inport2'
     *  Sum: '<S4>/Sum'
     */
    rtb_Row3_n = modell_P.joystick_gain_surge_Gain * modell_B.Sum;
    rtb_Row3_g = modell_P.joystick_gain_sway_Gain * modell_B.Sum_i;
    rtb_Reg_e_N_hil = (modell_B.g1 + modell_B.g2) *
      modell_P.joystick_gain_yaw_Gain;
    for (i = 0; i < 5; i++) {
      rtb_TmpHiddenBufferAtProductInp[i] = 0.0;
      rtb_TmpHiddenBufferAtProductInp[i] += modell_B.Product[i] * rtb_Row3_n;
      rtb_TmpHiddenBufferAtProductInp[i] += modell_B.Product[i + 5] * rtb_Row3_g;
      rtb_TmpHiddenBufferAtProductInp[i] += modell_B.Product[i + 10] *
        rtb_Reg_e_N_hil;

      /* Saturate: '<S4>/Saturation' */
      modell_B.Saturation[i] = rt_SATURATE(rtb_TmpHiddenBufferAtProductInp[i],
        modell_P.Saturation_LowerSat, modell_P.Saturation_UpperSat);
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* Product: '<S11>/Product' incorporates:
       *  Constant: '<S11>/Ke^-1'
       *  Constant: '<S11>/Te^+'
       */
      for (i = 0; i < 5; i++) {
        for (tmp_q = 0; tmp_q < 3; tmp_q++) {
          modell_B.Product_c[i + 5 * tmp_q] = 0.0;
          for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
            modell_B.Product_c[i + 5 * tmp_q] = modell_P.Ke1_Value_c[5 * tmp_3 +
              i] * modell_P.Te_Value_h[5 * tmp_q + tmp_3] + modell_B.Product_c[5
              * tmp_q + i];
          }
        }
      }
    }

    /* Sum: '<S11>/Sum' */
    rtb_Sum_p[0] = modell_B.Sum1_h[0] - modell_B.IC[0];
    rtb_Sum_p[1] = modell_B.Sum1_h[1] - modell_B.IC[1];
    rtb_Sum_p[2] = modell_B.Sum1_h[2] - modell_B.IC[2];

    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Constant: '<Root>/MODE'
     *  Constant: '<S11>/BT_power_limit'
     *  Constant: '<S11>/VSP_speeds'
     *  Constant: '<S4>/BT_power_limit'
     *  Constant: '<S4>/VSP_speeds'
     *  Constant: '<S5>/BT_saturation'
     *  Constant: '<S5>/VSP_speeds'
     *  Gain: '<S6>/U1'
     *  Gain: '<S6>/U2'
     *  Gain: '<S6>/U3'
     *  Gain: '<S6>/U4'
     *  Gain: '<S6>/U5'
     *  Saturate: '<S11>/Saturation'
     *  Sum: '<S6>/Sum'
     */
    switch ((int32_T)modell_P.MODE_Value) {
     case 0:
      modell_B.MultiportSwitch[0] = modell_P.U1_Gain * modell_B.Sum;
      modell_B.MultiportSwitch[1] = modell_P.U2_Gain * modell_B.Sum_i;
      modell_B.MultiportSwitch[2] = modell_P.U3_Gain * modell_B.Sum_e;
      modell_B.MultiportSwitch[3] = modell_P.U4_Gain * modell_B.Sum_d;
      modell_B.MultiportSwitch[4] = (modell_B.g1 + modell_B.g2) *
        modell_P.U5_Gain;
      modell_B.MultiportSwitch[5] = modell_P.BT_saturation_Value;
      modell_B.MultiportSwitch[6] = modell_P.VSP_speeds_Value;
      break;

     case 1:
      for (i = 0; i < 5; i++) {
        modell_B.MultiportSwitch[i] = modell_B.Saturation[i];
      }

      modell_B.MultiportSwitch[5] = modell_P.VSP_speeds_Value_n;
      modell_B.MultiportSwitch[6] = modell_P.BT_power_limit_Value;
      break;

     default:
      for (i = 0; i < 5; i++) {
        /* Product: '<S11>/Product1' */
        rtb_Product1_o[i] = 0.0;
        rtb_Product1_o[i] += modell_B.Product_c[i] * rtb_Sum_p[0];
        rtb_Product1_o[i] += modell_B.Product_c[i + 5] * rtb_Sum_p[1];
        rtb_Product1_o[i] += modell_B.Product_c[i + 10] * rtb_Sum_p[2];
        modell_B.MultiportSwitch[i] = rt_SATURATE(rtb_Product1_o[i],
          modell_P.Saturation_LowerSat_e, modell_P.Saturation_UpperSat_c);
      }

      modell_B.MultiportSwitch[5] = modell_P.VSP_speeds_Value_k;
      modell_B.MultiportSwitch[6] = modell_P.BT_power_limit_Value_f;
      break;
    }

    /* Gain: '<S2>/u1_hil' */
    rtb_Row3_g = modell_P.u1_hil_Gain * modell_B.MultiportSwitch[0];

    /* Gain: '<S2>/u2_hil' */
    rtb_Sum_n = modell_P.u2_hil_Gain * modell_B.MultiportSwitch[1];

    /* Gain: '<S2>/u3_hil' */
    rtb_Row3_n = modell_P.u3_hil_Gain * modell_B.MultiportSwitch[2];

    /* Gain: '<S2>/u4_hil' */
    rtb_Row1_e = modell_P.u4_hil_Gain * modell_B.MultiportSwitch[3];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* S-Function (sfix_tsampmath): '<S21>/sample time' */
      /* Sample Time Math Block: '<S21>/sample time'
       *
       * y = K         where     K = ( w * Ts )
       *
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       *
       * Parameter: WtEt == Weighted Elapsed Time
       *   Data Type:  Floating Point real_T
       *
       */
      modell_B.sampletime = modell_P.sampletime_WtEt;
    }

    /* Product: '<S21>/delta rise limit' */
    rtb_Reg_e_N_hil = modell_B.MultiportSwitch[5] * modell_B.sampletime;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* UnitDelay: '<S21>/Delay Input2' */
      modell_B.Yk1 = modell_DWork.DelayInput2_DSTATE;
    }

    /* Sum: '<S21>/Difference Inputs1' */
    rtb_UkYk1 = modell_B.MultiportSwitch[4] - modell_B.Yk1;

    /* Switch: '<S23>/Switch2' incorporates:
     *  RelationalOperator: '<S23>/LowerRelop1'
     */
    if (!(rtb_UkYk1 > rtb_Reg_e_N_hil)) {
      /* Product: '<S21>/delta fall limit' incorporates:
       *  Gain: '<S2>/neg'
       */
      rtb_Reg_e_N_hil = modell_P.neg_Gain * modell_B.MultiportSwitch[5] *
        modell_B.sampletime;

      /* Switch: '<S23>/Switch' incorporates:
       *  RelationalOperator: '<S23>/UpperRelop'
       */
      if (rtb_UkYk1 < rtb_Reg_e_N_hil) {
        rtb_UkYk1 = rtb_Reg_e_N_hil;
      }

      rtb_Reg_e_N_hil = rtb_UkYk1;
    }

    /* Sum: '<S21>/Difference Inputs2' */
    modell_B.DifferenceInputs2 = rtb_Reg_e_N_hil + modell_B.Yk1;

    /* Product: '<S2>/Product' incorporates:
     *  Constant: '<S2>/Constant'
     *  Constant: '<S2>/Constant1'
     *  Gain: '<S2>/u5_hil'
     *  SignalConversion: '<S2>/TmpHiddenBufferAtProductInport3'
     */
    rtb_Product1_o[0] = rtb_Row3_g;
    rtb_Product1_o[1] = rtb_Sum_n;
    rtb_Product1_o[2] = rtb_Row3_n;
    rtb_Product1_o[3] = rtb_Row1_e;
    rtb_Product1_o[4] = modell_P.u5_hil_Gain * modell_B.DifferenceInputs2;
    for (i = 0; i < 3; i++) {
      for (tmp_q = 0; tmp_q < 5; tmp_q++) {
        tmp_2[i + 3 * tmp_q] = 0.0;
        for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
          tmp_2[i + 3 * tmp_q] = modell_P.Constant_Value_e[3 * tmp_3 + i] *
            modell_P.Constant1_Value[5 * tmp_q + tmp_3] + tmp_2[3 * tmp_q + i];
        }
      }
    }

    for (i = 0; i < 3; i++) {
      rtb_K_3[i] = 0.0;
      for (tmp_q = 0; tmp_q < 5; tmp_q++) {
        rtb_K_3[i] += tmp_2[3 * tmp_q + i] * rtb_Product1_o[tmp_q];
      }
    }

    /* Fcn: '<S22>/Fcn' */
    modell_B.x_dot = cos(modell_B.Integrator1[2]) * rtb_Sum4_l[0] - sin
      (modell_B.Integrator1[2]) * rtb_Sum4_l[1];

    /* Fcn: '<S22>/Fcn1' */
    modell_B.y_dot = sin(modell_B.Integrator1[2]) * rtb_Sum4_l[0] + cos
      (modell_B.Integrator1[2]) * rtb_Sum4_l[1];

    /* Fcn: '<S22>/Fcn2' */
    modell_B.psi_dot = rtb_Sum4_l[2];

    /* Sum: '<S2>/Sum3' incorporates:
     *  Gain: '<S2>/tau_surge_hil'
     *  Gain: '<S2>/tau_sway_hil'
     *  Gain: '<S2>/tau_yaw_hil'
     */
    rtb_K_2[0] = modell_P.tau_surge_hil_Gain * rtb_K_3[0] - rtb_K_2[0];
    rtb_K_2[1] = modell_P.tau_sway_hil_Gain * rtb_K_3[1] - rtb_K_2[1];
    rtb_K_2[2] = modell_P.tau_yaw_hil_Gain * rtb_K_3[2] - rtb_K_2[2];

    /* Gain: '<S2>/inv(M)' */
    for (i = 0; i < 3; i++) {
      modell_B.invM[i] = 0.0;
      modell_B.invM[i] = modell_P.invM_Gain[i] * rtb_K_2[0] + modell_B.invM[i];
      modell_B.invM[i] = modell_P.invM_Gain[i + 3] * rtb_K_2[1] +
        modell_B.invM[i];
      modell_B.invM[i] = modell_P.invM_Gain[i + 6] * rtb_K_2[2] +
        modell_B.invM[i];
    }

    /* Fcn: '<S24>/Fcn' */
    modell_B.x_dot_a = cos(modell_B.Integrator1_e[2]) * modell_B.Integrator2[0]
      - sin(modell_B.Integrator1_e[2]) * modell_B.Integrator2[1];

    /* Fcn: '<S24>/Fcn1' */
    modell_B.y_dot_g = sin(modell_B.Integrator1_e[2]) * modell_B.Integrator2[0]
      + cos(modell_B.Integrator1_e[2]) * modell_B.Integrator2[1];

    /* Fcn: '<S24>/Fcn2' */
    modell_B.psi_dot_p = modell_B.Integrator2[2];

    /* Integrator: '<S13>/Integrator1' */
    rtb_K_2[0] = modell_X.Integrator1_CSTATE_p[0];
    rtb_K_2[1] = modell_X.Integrator1_CSTATE_p[1];
    rtb_K_2[2] = modell_X.Integrator1_CSTATE_p[2];

    /* Switch: '<S53>/SwitchControl' incorporates:
     *  Constant: '<S13>/zero'
     *  Constant: '<S53>/Constant'
     *  Fcn: '<S55>/Row1'
     *  Fcn: '<S55>/Row2'
     *  Fcn: '<S55>/Row3'
     */
    if (modell_P.Constant_Value_b > modell_P.SwitchControl_Threshold_a) {
      rtb_K_3[0] = modell_P.zero_Value;
      rtb_K_3[1] = modell_P.zero_Value;
      rtb_K_3[2] = modell_P.zero_Value;
    } else {
      rtb_K_3[0] = cos(modell_B.Integrator1[2]) * modell_X.Integrator1_CSTATE_p
        [0] + sin(modell_B.Integrator1[2]) * modell_X.Integrator1_CSTATE_p[1];
      rtb_K_3[1] = (-sin(modell_B.Integrator1[2])) *
        modell_X.Integrator1_CSTATE_p[0] + cos(modell_B.Integrator1[2]) *
        modell_X.Integrator1_CSTATE_p[1];
      rtb_K_3[2] = modell_X.Integrator1_CSTATE_p[2];
    }

    /* Gain: '<S3>/inv(M)' incorporates:
     *  Gain: '<S3>/D'
     *  Saturate: '<S25>/Saturation'
     *  Saturate: '<S25>/Saturation1'
     *  Saturate: '<S25>/Saturation2'
     *  Sum: '<S3>/Sum3'
     */
    tmp_0[0] = rt_SATURATE(modell_B.IC[0], modell_P.Saturation_LowerSat_j,
      modell_P.Saturation_UpperSat_n);
    tmp_0[1] = rt_SATURATE(modell_B.IC[1], modell_P.Saturation1_LowerSat,
      modell_P.Saturation1_UpperSat);
    tmp_0[2] = rt_SATURATE(modell_B.IC[2], modell_P.Saturation2_LowerSat,
      modell_P.Saturation2_UpperSat);
    for (i = 0; i < 3; i++) {
      tmp[i] = 0.0;
      tmp[i] += modell_P.D_Gain_d[i] * modell_B.Integrator2[0];
      tmp[i] += modell_P.D_Gain_d[i + 3] * modell_B.Integrator2[1];
      tmp[i] += modell_P.D_Gain_d[i + 6] * modell_B.Integrator2[2];
      tmp_1[i] = (tmp_0[i] - tmp[i]) + rtb_K_3[i];
    }

    for (i = 0; i < 3; i++) {
      modell_B.invM_g[i] = 0.0;
      modell_B.invM_g[i] = modell_P.invM_Gain_d[i] * tmp_1[0] +
        modell_B.invM_g[i];
      modell_B.invM_g[i] = modell_P.invM_Gain_d[i + 3] * tmp_1[1] +
        modell_B.invM_g[i];
      modell_B.invM_g[i] = modell_P.invM_Gain_d[i + 6] * tmp_1[2] +
        modell_B.invM_g[i];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
    }

    /* Sum: '<S7>/Sum' */
    rtb_K_3[0] = modell_B.Integrator1_e[0] + modell_B.Sum6_a[0];
    rtb_K_3[1] = modell_B.Integrator1_e[1] + modell_B.Sum6_a[1];
    rtb_K_3[2] = modell_B.Integrator1_e[2] + modell_B.Sum6_a[2];

    /* Gain: '<S7>/M_inv' incorporates:
     *  Fcn: '<S26>/Row1'
     *  Fcn: '<S26>/Row2'
     *  Fcn: '<S26>/Row3'
     *  Fcn: '<S27>/Row1'
     *  Fcn: '<S27>/Row2'
     *  Fcn: '<S27>/Row3'
     *  Gain: '<S7>/D'
     *  Integrator: '<S7>/bias_hat_integrator'
     *  Sum: '<S7>/Sum1'
     *  Sum: '<S7>/Sum4'
     */
    tmp_4[0] = modell_B.Integrator1_e[2];
    tmp_5[0] = modell_B.Integrator1_e[2];
    tmp_6[0] = modell_B.Integrator1_e[2];
    tmp_7[0] = modell_B.Integrator1_e[2];
    tmp_8[0] = modell_B.Integrator1_e[2];
    tmp_9[0] = modell_B.Integrator1_e[2];
    tmp_a[0] = modell_B.Integrator1_e[2];
    tmp_b[0] = modell_B.Integrator1_e[2];
    tmp_c[0] = modell_B.Integrator1_e[2];
    tmp_d[0] = modell_B.Integrator1_e[2];
    tmp_e[0] = modell_B.Integrator1_e[2];
    tmp_f[0] = modell_B.Integrator1_e[2];
    tmp_g[0] = modell_B.Integrator1_e[2];
    tmp_h[0] = modell_B.Integrator1_e[2];
    tmp_i[0] = modell_B.Integrator1_e[2];
    tmp_j[0] = modell_B.Integrator1_e[2];
    tmp_k[0] = modell_B.Integrator1_e[2];
    tmp_l[0] = modell_B.Integrator1_e[2];
    for (i = 0; i < 3; i++) {
      /* Gain: '<S7>/K_2' */
      rtb_Sum4_l[i] = 0.0;
      rtb_Sum4_l[i] += modell_P.K_2_Gain[i] * rtb_K_3[0];
      rtb_Sum4_l[i] += modell_P.K_2_Gain[i + 3] * rtb_K_3[1];
      rtb_Sum4_l[i] += modell_P.K_2_Gain[i + 6] * rtb_K_3[2];

      /* Gain: '<S7>/K_4' */
      rtb_T_i_inv[i] = 0.0;
      rtb_T_i_inv[i] += modell_P.K_4_Gain[i] * rtb_K_3[0];
      rtb_T_i_inv[i] += modell_P.K_4_Gain[i + 3] * rtb_K_3[1];
      rtb_T_i_inv[i] += modell_P.K_4_Gain[i + 6] * rtb_K_3[2];
      tmp_4[i + 1] = modell_X.bias_hat_integrator_CSTATE[i];
      tmp_5[i + 1] = modell_X.bias_hat_integrator_CSTATE[i];
      tmp_6[i + 1] = modell_X.bias_hat_integrator_CSTATE[i];
      tmp_7[i + 1] = modell_X.bias_hat_integrator_CSTATE[i];
      tmp_8[i + 1] = modell_X.bias_hat_integrator_CSTATE[i];
      tmp_9[i + 1] = modell_X.bias_hat_integrator_CSTATE[i];
      tmp_a[i + 1] = modell_X.bias_hat_integrator_CSTATE[i];
      tmp_b[i + 1] = modell_X.bias_hat_integrator_CSTATE[i];
      tmp_c[i + 1] = modell_X.bias_hat_integrator_CSTATE[i];
      tmp_d[i + 1] = rtb_T_i_inv[i];
      tmp_e[i + 1] = rtb_T_i_inv[i];
      tmp_f[i + 1] = rtb_T_i_inv[i];
      tmp_g[i + 1] = rtb_T_i_inv[i];
      tmp_h[i + 1] = rtb_T_i_inv[i];
      tmp_i[i + 1] = rtb_T_i_inv[i];
      tmp_j[i + 1] = rtb_T_i_inv[i];
      tmp_k[i + 1] = rtb_T_i_inv[i];
      tmp_l[i + 1] = rtb_T_i_inv[i];
      tmp_m[i] = 0.0;
      tmp_m[i] += modell_P.D_Gain_h[i] * modell_B.nu_hat_n[0];
      tmp_m[i] += modell_P.D_Gain_h[i + 3] * modell_B.nu_hat_n[1];
      tmp_m[i] += modell_P.D_Gain_h[i + 6] * modell_B.nu_hat_n[2];
    }

    rtb_Row3_n = (((cos(tmp_d[0]) * tmp_e[1] + sin(tmp_f[0]) * tmp_g[2]) +
                   modell_B.IC[0]) + (cos(tmp_4[0]) * tmp_5[1] + sin(tmp_6[0]) *
      tmp_7[2])) - tmp_m[0];
    rtb_Row3_g = ((((-sin(tmp_h[0])) * tmp_i[1] + cos(tmp_j[0]) * tmp_k[2]) +
                   modell_B.IC[1]) + ((-sin(tmp_8[0])) * tmp_9[1] + cos(tmp_a[0])
      * tmp_b[2])) - tmp_m[1];
    rtb_Reg_e_N_hil = ((tmp_l[3] + modell_B.IC[2]) + tmp_c[3]) - tmp_m[2];

    /* Sum: '<S7>/Sum3' incorporates:
     *  Fcn: '<S28>/Fcn'
     *  Fcn: '<S28>/Fcn1'
     *  Fcn: '<S28>/Fcn2'
     */
    tmp_4[0] = modell_B.Integrator1_e[2];
    tmp_5[0] = modell_B.Integrator1_e[2];
    tmp_6[0] = modell_B.Integrator1_e[2];
    tmp_7[0] = modell_B.Integrator1_e[2];
    for (i = 0; i < 3; i++) {
      modell_B.M_inv[i] = 0.0;
      modell_B.M_inv[i] = modell_P.M_inv_Gain[i] * rtb_Row3_n + modell_B.M_inv[i];
      modell_B.M_inv[i] = modell_P.M_inv_Gain[i + 3] * rtb_Row3_g +
        modell_B.M_inv[i];
      modell_B.M_inv[i] = modell_P.M_inv_Gain[i + 6] * rtb_Reg_e_N_hil +
        modell_B.M_inv[i];
      tmp_0[i] = 0.0;
      tmp_0[i] += modell_P.K_3_Gain[i] * rtb_K_3[0];
      tmp_0[i] += modell_P.K_3_Gain[i + 3] * rtb_K_3[1];
      tmp_0[i] += modell_P.K_3_Gain[i + 6] * rtb_K_3[2];
      tmp_1[i] = 0.0;
      tmp_1[i] += modell_P.T_inv_Gain[i] * modell_X.bias_hat_integrator_CSTATE[0];
      tmp_1[i] += modell_P.T_inv_Gain[i + 3] *
        modell_X.bias_hat_integrator_CSTATE[1];
      tmp_1[i] += modell_P.T_inv_Gain[i + 6] *
        modell_X.bias_hat_integrator_CSTATE[2];
      modell_B.Sum2_b[i] = tmp_0[i] - tmp_1[i];
      tmp_4[i + 1] = modell_B.nu_hat_n[i];
      tmp_5[i + 1] = modell_B.nu_hat_n[i];
      tmp_6[i + 1] = modell_B.nu_hat_n[i];
      tmp_7[i + 1] = modell_B.nu_hat_n[i];
    }

    modell_B.Sum3[0] = (cos(tmp_4[0]) * tmp_5[1] - sin(tmp_6[0]) * tmp_7[2]) +
      rtb_Sum4_l[0];
    modell_B.Sum3[1] = (sin(modell_B.Integrator1_e[2]) * modell_B.nu_hat_n[0] +
                        cos(modell_B.Integrator1_e[2]) * modell_B.nu_hat_n[1]) +
      rtb_Sum4_l[1];
    modell_B.Sum3[2] = rtb_Sum4_l[2] + modell_B.nu_hat_n[2];

    /* Sum: '<S7>/Sum5' incorporates:
     *  Gain: '<S7>/A_w'
     *  Gain: '<S7>/K_1'
     */
    for (i = 0; i < 6; i++) {
      tmp_n[i] = 0.0;
      tmp_n[i] += modell_P.K_1_Gain[i] * rtb_K_3[0];
      tmp_n[i] += modell_P.K_1_Gain[i + 6] * rtb_K_3[1];
      tmp_n[i] += modell_P.K_1_Gain[i + 12] * rtb_K_3[2];
      tmp_o[i] = 0.0;
      for (tmp_q = 0; tmp_q < 6; tmp_q++) {
        tmp_o[i] += modell_P.A_w_Gain[6 * tmp_q + i] * rtb_K_1[tmp_q];
      }

      modell_B.Sum5[i] = tmp_n[i] + tmp_o[i];
    }

    /* Sum: '<S8>/Sum' */
    rtb_Row3_n = modell_B.Integrator1[0] + modell_B.Sum6[0];
    rtb_Row3_g = modell_B.Integrator1[1] + modell_B.Sum6[1];
    rtb_Reg_e_N_hil = modell_B.Integrator1[2] + modell_B.Sum6[2];

    /* Sum: '<S8>/Sum1' incorporates:
     *  Fcn: '<S29>/Row1'
     *  Fcn: '<S29>/Row2'
     *  Fcn: '<S29>/Row3'
     */
    tmp_4[0] = modell_B.Integrator1[2];
    tmp_5[0] = modell_B.Integrator1[2];
    tmp_6[0] = modell_B.Integrator1[2];
    tmp_7[0] = modell_B.Integrator1[2];
    tmp_8[0] = modell_B.Integrator1[2];
    tmp_9[0] = modell_B.Integrator1[2];
    tmp_a[0] = modell_B.Integrator1[2];
    tmp_b[0] = modell_B.Integrator1[2];
    tmp_c[0] = modell_B.Integrator1[2];
    for (i = 0; i < 3; i++) {
      /* Gain: '<S8>/K_4' */
      rtb_Sum4_l[i] = 0.0;
      rtb_Sum4_l[i] += modell_P.K_4_Gain_m[i] * rtb_Row3_n;
      rtb_Sum4_l[i] += modell_P.K_4_Gain_m[i + 3] * rtb_Row3_g;
      rtb_Sum4_l[i] += modell_P.K_4_Gain_m[i + 6] * rtb_Reg_e_N_hil;
      tmp_4[i + 1] = rtb_Sum4_l[i];
      tmp_5[i + 1] = rtb_Sum4_l[i];
      tmp_6[i + 1] = rtb_Sum4_l[i];
      tmp_7[i + 1] = rtb_Sum4_l[i];
      tmp_8[i + 1] = rtb_Sum4_l[i];
      tmp_9[i + 1] = rtb_Sum4_l[i];
      tmp_a[i + 1] = rtb_Sum4_l[i];
      tmp_b[i + 1] = rtb_Sum4_l[i];
      tmp_c[i + 1] = rtb_Sum4_l[i];
    }

    tmp_0[0] = cos(tmp_4[0]) * tmp_5[1] + sin(tmp_6[0]) * tmp_7[2];
    tmp_0[1] = (-sin(tmp_8[0])) * tmp_9[1] + cos(tmp_a[0]) * tmp_b[2];
    tmp_0[2] = tmp_c[3];

    /* Sum: '<S8>/Sum4' incorporates:
     *  Fcn: '<S30>/Row1'
     *  Fcn: '<S30>/Row2'
     *  Fcn: '<S30>/Row3'
     *  Gain: '<S8>/D'
     *  Integrator: '<S8>/bias_hat_integrator'
     */
    tmp_4[0] = modell_B.Integrator1[2];
    tmp_5[0] = modell_B.Integrator1[2];
    tmp_6[0] = modell_B.Integrator1[2];
    tmp_7[0] = modell_B.Integrator1[2];
    tmp_8[0] = modell_B.Integrator1[2];
    tmp_9[0] = modell_B.Integrator1[2];
    tmp_a[0] = modell_B.Integrator1[2];
    tmp_b[0] = modell_B.Integrator1[2];
    tmp_c[0] = modell_B.Integrator1[2];
    for (i = 0; i < 3; i++) {
      rtb_Sum4_l[i] = tmp_0[i] + rtb_Sum_p[i];
      tmp_4[i + 1] = modell_X.bias_hat_integrator_CSTATE_l[i];
      tmp_5[i + 1] = modell_X.bias_hat_integrator_CSTATE_l[i];
      tmp_6[i + 1] = modell_X.bias_hat_integrator_CSTATE_l[i];
      tmp_7[i + 1] = modell_X.bias_hat_integrator_CSTATE_l[i];
      tmp_8[i + 1] = modell_X.bias_hat_integrator_CSTATE_l[i];
      tmp_9[i + 1] = modell_X.bias_hat_integrator_CSTATE_l[i];
      tmp_a[i + 1] = modell_X.bias_hat_integrator_CSTATE_l[i];
      tmp_b[i + 1] = modell_X.bias_hat_integrator_CSTATE_l[i];
      tmp_c[i + 1] = modell_X.bias_hat_integrator_CSTATE_l[i];
      tmp_p[i] = 0.0;
      tmp_p[i] += modell_P.D_Gain_e[i] * modell_B.nu_hat[0];
      tmp_p[i] += modell_P.D_Gain_e[i + 3] * modell_B.nu_hat[1];
      tmp_p[i] += modell_P.D_Gain_e[i + 6] * modell_B.nu_hat[2];
    }

    rtb_Sum4_l[0] = ((cos(tmp_4[0]) * tmp_5[1] + sin(tmp_6[0]) * tmp_7[2]) +
                     rtb_Sum4_l[0]) - tmp_p[0];
    rtb_Sum4_l[1] = (((-sin(tmp_8[0])) * tmp_9[1] + cos(tmp_a[0]) * tmp_b[2]) +
                     rtb_Sum4_l[1]) - tmp_p[1];
    rtb_Sum4_l[2] = (tmp_c[3] + rtb_Sum4_l[2]) - tmp_p[2];

    /* Sum: '<S8>/Sum3' incorporates:
     *  Fcn: '<S31>/Fcn'
     *  Fcn: '<S31>/Fcn1'
     *  Fcn: '<S31>/Fcn2'
     *  Gain: '<S8>/K_2'
     */
    tmp_4[0] = modell_B.Integrator1[2];
    tmp_5[0] = modell_B.Integrator1[2];
    tmp_6[0] = modell_B.Integrator1[2];
    tmp_7[0] = modell_B.Integrator1[2];
    tmp_8[0] = modell_B.Integrator1[2];
    tmp_9[0] = modell_B.Integrator1[2];
    tmp_a[0] = modell_B.Integrator1[2];
    tmp_b[0] = modell_B.Integrator1[2];
    tmp_c[0] = modell_B.Integrator1[2];
    for (i = 0; i < 3; i++) {
      /* Gain: '<S8>/M_inv' */
      modell_B.M_inv_d[i] = 0.0;
      modell_B.M_inv_d[i] = modell_P.M_inv_Gain_h[i] * rtb_Sum4_l[0] +
        modell_B.M_inv_d[i];
      modell_B.M_inv_d[i] = modell_P.M_inv_Gain_h[i + 3] * rtb_Sum4_l[1] +
        modell_B.M_inv_d[i];
      modell_B.M_inv_d[i] = modell_P.M_inv_Gain_h[i + 6] * rtb_Sum4_l[2] +
        modell_B.M_inv_d[i];
      tmp_1[i] = 0.0;
      tmp_1[i] += modell_P.K_3_Gain_f[i] * rtb_Row3_n;
      tmp_1[i] += modell_P.K_3_Gain_f[i + 3] * rtb_Row3_g;
      tmp_1[i] += modell_P.K_3_Gain_f[i + 6] * rtb_Reg_e_N_hil;
      tmp_0[i] = 0.0;
      tmp_0[i] += modell_P.T_inv_Gain_d[i] *
        modell_X.bias_hat_integrator_CSTATE_l[0];
      tmp_0[i] += modell_P.T_inv_Gain_d[i + 3] *
        modell_X.bias_hat_integrator_CSTATE_l[1];
      tmp_0[i] += modell_P.T_inv_Gain_d[i + 6] *
        modell_X.bias_hat_integrator_CSTATE_l[2];
      modell_B.Sum2_k[i] = tmp_1[i] - tmp_0[i];
      tmp[i] = 0.0;
      tmp[i] += modell_P.K_2_Gain_m[i] * rtb_Row3_n;
      tmp[i] += modell_P.K_2_Gain_m[i + 3] * rtb_Row3_g;
      tmp[i] += modell_P.K_2_Gain_m[i + 6] * rtb_Reg_e_N_hil;
      tmp_4[i + 1] = modell_B.nu_hat[i];
      tmp_5[i + 1] = modell_B.nu_hat[i];
      tmp_6[i + 1] = modell_B.nu_hat[i];
      tmp_7[i + 1] = modell_B.nu_hat[i];
      tmp_8[i + 1] = modell_B.nu_hat[i];
      tmp_9[i + 1] = modell_B.nu_hat[i];
      tmp_a[i + 1] = modell_B.nu_hat[i];
      tmp_b[i + 1] = modell_B.nu_hat[i];
      tmp_c[i + 1] = modell_B.nu_hat[i];
    }

    modell_B.Sum3_i[0] = (cos(tmp_4[0]) * tmp_5[1] - sin(tmp_6[0]) * tmp_7[2]) +
      tmp[0];
    modell_B.Sum3_i[1] = (sin(tmp_8[0]) * tmp_9[1] + cos(tmp_a[0]) * tmp_b[2]) +
      tmp[1];
    modell_B.Sum3_i[2] = tmp[2] + tmp_c[3];

    /* Sum: '<S8>/Sum5' incorporates:
     *  Gain: '<S8>/A_w'
     *  Gain: '<S8>/K_1'
     */
    for (i = 0; i < 6; i++) {
      rtb_K_1[i] = 0.0;
      rtb_K_1[i] += modell_P.K_1_Gain_k[i] * rtb_Row3_n;
      rtb_K_1[i] += modell_P.K_1_Gain_k[i + 6] * rtb_Row3_g;
      rtb_K_1[i] += modell_P.K_1_Gain_k[i + 12] * rtb_Reg_e_N_hil;
      tmp_n[i] = 0.0;
      for (tmp_q = 0; tmp_q < 6; tmp_q++) {
        tmp_n[i] += modell_P.A_w_Gain_p[6 * tmp_q + i] * rtb_wavehat[tmp_q];
      }

      modell_B.Sum5_a[i] = rtb_K_1[i] + tmp_n[i];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
    }

    /* Sum: '<S12>/Sum' */
    modell_B.Sum_d0[0] = modell_B.nu_surge_hil - modell_B.Integrator2[0];
    modell_B.Sum_d0[1] = modell_B.nu_sway_hil - modell_B.Integrator2[1];
    modell_B.Sum_d0[2] = modell_B.nu_yaw_hil - modell_B.Integrator2[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Gain: '<S51>/Output' incorporates:
       *  RandomNumber: '<S51>/White Noise'
       */
      rtb_Row3_n = modell_P.Output_Gain[0] * modell_DWork.NextOutput;
      rtb_Row3_g = modell_P.Output_Gain[1] * modell_DWork.NextOutput;
      rtb_Reg_e_N_hil = modell_P.Output_Gain[2] * modell_DWork.NextOutput;
      for (i = 0; i < 3; i++) {
        /* Gain: '<S13>/E_b_i' */
        modell_B.E_b_i[i] = 0.0;
        modell_B.E_b_i[i] = modell_P.E_b_i_Gain[i] * rtb_Row3_n +
          modell_B.E_b_i[i];
        modell_B.E_b_i[i] = modell_P.E_b_i_Gain[i + 3] * rtb_Row3_g +
          modell_B.E_b_i[i];
        modell_B.E_b_i[i] = modell_P.E_b_i_Gain[i + 6] * rtb_Reg_e_N_hil +
          modell_B.E_b_i[i];

        /* Gain: '<S13>/E_b_s' */
        modell_B.E_b_s[i] = 0.0;
        modell_B.E_b_s[i] = modell_P.E_b_s_Gain[i] * rtb_Row3_n +
          modell_B.E_b_s[i];
        modell_B.E_b_s[i] = modell_P.E_b_s_Gain[i + 3] * rtb_Row3_g +
          modell_B.E_b_s[i];
        modell_B.E_b_s[i] = modell_P.E_b_s_Gain[i + 6] * rtb_Reg_e_N_hil +
          modell_B.E_b_s[i];
      }
    }

    /* Sum: '<S13>/Sum1' incorporates:
     *  Gain: '<S13>/T_i_inv'
     */
    for (i = 0; i < 3; i++) {
      tmp_0[i] = 0.0;
      tmp_0[i] += modell_P.T_s_inv_Gain[i] * rtb_Integrator_idx;
      tmp_0[i] += modell_P.T_s_inv_Gain[i + 3] * rtb_Integrator_idx_0;
      tmp_0[i] += modell_P.T_s_inv_Gain[i + 6] * rtb_Integrator_idx_1;
      modell_B.Sum_iz[i] = tmp_0[i] + modell_B.E_b_s[i];
      tmp_1[i] = 0.0;
      tmp_1[i] += modell_P.T_i_inv_Gain[i] * rtb_K_2[0];
      tmp_1[i] += modell_P.T_i_inv_Gain[i + 3] * rtb_K_2[1];
      tmp_1[i] += modell_P.T_i_inv_Gain[i + 6] * rtb_K_2[2];
      modell_B.Sum1[i] = modell_B.E_b_i[i] + tmp_1[i];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void modell_update(int_T tid)
{
  {
    real_T tmpmean;
    real_T m;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Update for UnitDelay: '<S21>/Delay Input2' */
      modell_DWork.DelayInput2_DSTATE = modell_B.DifferenceInputs2;

      /* Update for RandomNumber: '<S51>/White Noise' */
      tmpmean = modell_P.WhiteNoise_Mean;
      m = rt_NormalRand(&modell_DWork.RandSeed) * modell_P.WhiteNoise_StdDev;
      modell_DWork.NextOutput = m + tmpmean;
    }
  }

  if (rtmIsMajorTimeStep(modell_M)) {
    rt_ertODEUpdateContinuousStates(&modell_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++modell_M->Timing.clockTick0))
    ++modell_M->Timing.clockTickH0;
  modell_M->Timing.t[0] = modell_M->Timing.clockTick0 *
    modell_M->Timing.stepSize0 + modell_M->Timing.clockTickH0 *
    modell_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(modell_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++modell_M->Timing.clockTick1))
      ++modell_M->Timing.clockTickH1;
    modell_M->Timing.t[1] = modell_M->Timing.clockTick1 *
      modell_M->Timing.stepSize1 + modell_M->Timing.clockTickH1 *
      modell_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void modell_derivatives(void)
{
  {
    int32_T i;

    /* Integrator Block: '<S2>/Integrator1' */
    {
      if (modell_P.reset_eta_hil_Value== 0.0) {
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator1_CSTATE[0] = modell_B.x_dot;
      } else {
        /* level reset is active*/
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator1_CSTATE[0] = 0.0;
      }

      if (modell_P.reset_eta_hil_Value== 0.0) {
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator1_CSTATE[1] = modell_B.y_dot;
      } else {
        /* level reset is active*/
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator1_CSTATE[1] = 0.0;
      }

      if (modell_P.reset_eta_hil_Value== 0.0) {
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator1_CSTATE[2] = modell_B.psi_dot;
      } else {
        /* level reset is active*/
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator1_CSTATE[2] = 0.0;
      }
    }

    /* Integrator Block: '<S2>/Integrator' */
    {
      if (modell_P.reset_eta_hil_Value== 0.0) {
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = modell_B.invM[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = 0.0;
      }

      if (modell_P.reset_eta_hil_Value== 0.0) {
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = modell_B.invM[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = 0.0;
      }

      if (modell_P.reset_eta_hil_Value== 0.0) {
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator_CSTATE[2] = modell_B.invM[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_modell *) modell_M->ModelData.derivs)
          ->Integrator_CSTATE[2] = 0.0;
      }
    }

    /* TransferFcn Block: '<S5>/Transfer Fcn' */
    {
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->TransferFcn_CSTATE = modell_P.eta_d_N_Value;
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->TransferFcn_CSTATE += (modell_P.TransferFcn_A)*
        modell_X.TransferFcn_CSTATE;
    }

    /* TransferFcn Block: '<S5>/Transfer Fcn1' */
    {
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->TransferFcn1_CSTATE = modell_P.eta_d_E_Value;
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->TransferFcn1_CSTATE += (modell_P.TransferFcn1_A)*
        modell_X.TransferFcn1_CSTATE;
    }

    /* TransferFcn Block: '<S5>/Transfer Fcn2' */
    {
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->TransferFcn2_CSTATE = modell_P.eta_d_Psi_Value;
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->TransferFcn2_CSTATE += (modell_P.TransferFcn2_A)*
        modell_X.TransferFcn2_CSTATE;
    }

    /* Integrator Block: '<S3>/Integrator1' */
    {
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->Integrator1_CSTATE_e[0] = modell_B.x_dot_a;
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->Integrator1_CSTATE_e[1] = modell_B.y_dot_g;
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->Integrator1_CSTATE_e[2] = modell_B.psi_dot_p;
    }

    /* Derivatives for Integrator: '<S3>/Integrator2' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->
      Integrator2_CSTATE[0] = modell_B.invM_g[0];
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->
      Integrator2_CSTATE[1] = modell_B.invM_g[1];
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->
      Integrator2_CSTATE[2] = modell_B.invM_g[2];

    /* Integrator Block: '<S12>/Integrator' */
    {
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->Integrator_CSTATE_e[0] = modell_B.Sum_d0[0];
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->Integrator_CSTATE_e[1] = modell_B.Sum_d0[1];
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->Integrator_CSTATE_e[2] = modell_B.Sum_d0[2];
    }

    /* Derivatives for If: '<S44>/If' */

    /* Derivatives for Integrator: '<S13>/Integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->Integrator_CSTATE_m[0] = modell_B.Sum_iz[0];
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->Integrator_CSTATE_m[1] = modell_B.Sum_iz[1];
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->Integrator_CSTATE_m[2] = modell_B.Sum_iz[2];

    /* Derivatives for Integrator: '<S8>/eta_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->eta_hat_CSTATE[0] =
      modell_B.Sum3_i[0];

    /* Derivatives for Integrator: '<S8>/nu_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->nu_hat_CSTATE[0] =
      modell_B.M_inv_d[0];

    /* Derivatives for Integrator: '<S8>/eta_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->eta_hat_CSTATE[1] =
      modell_B.Sum3_i[1];

    /* Derivatives for Integrator: '<S8>/nu_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->nu_hat_CSTATE[1] =
      modell_B.M_inv_d[1];

    /* Derivatives for Integrator: '<S8>/eta_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->eta_hat_CSTATE[2] =
      modell_B.Sum3_i[2];

    /* Derivatives for Integrator: '<S8>/nu_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->nu_hat_CSTATE[2] =
      modell_B.M_inv_d[2];
    for (i = 0; i < 6; i++) {
      /* Derivatives for Integrator: '<S8>/wave hat' */
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)->wavehat_CSTATE[i]
        = modell_B.Sum5_a[i];

      /* Derivatives for Integrator: '<S7>/wave hat' */
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)->
        wavehat_CSTATE_g[i] = modell_B.Sum5[i];
    }

    /* Derivatives for Integrator: '<S7>/eta_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->eta_hat_CSTATE_b[0]
      = modell_B.Sum3[0];

    /* Derivatives for Integrator: '<S7>/nu_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->nu_hat_CSTATE_g[0]
      = modell_B.M_inv[0];

    /* Derivatives for Integrator: '<S7>/eta_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->eta_hat_CSTATE_b[1]
      = modell_B.Sum3[1];

    /* Derivatives for Integrator: '<S7>/nu_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->nu_hat_CSTATE_g[1]
      = modell_B.M_inv[1];

    /* Derivatives for Integrator: '<S7>/eta_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->eta_hat_CSTATE_b[2]
      = modell_B.Sum3[2];

    /* Derivatives for Integrator: '<S7>/nu_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->nu_hat_CSTATE_g[2]
      = modell_B.M_inv[2];

    /* Derivatives for enable SubSystem: '<Root>/DP controller' */
    if (modell_DWork.DPcontroller_MODE == SUBSYS_ENABLED) {
      /* Derivatives for Integrator: '<S15>/Integrator' */
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->Integrator_CSTATE_p[0] = modell_B.TmpHiddenBufferAtKpInport1[0];
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->Integrator_CSTATE_p[1] = modell_B.TmpHiddenBufferAtKpInport1[1];
      ((StateDerivatives_modell *) modell_M->ModelData.derivs)
        ->Integrator_CSTATE_p[2] = modell_B.TmpHiddenBufferAtKpInport1[2];
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_modell *) modell_M->ModelData.derivs)
               ->Integrator_CSTATE_p[0]);
        for (i=0; i < 3; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<Root>/DP controller' */

    /* Derivatives for If: '<S33>/If' */

    /* Derivatives for If: '<S32>/If' */

    /* Derivatives for If: '<S35>/If' */

    /* Derivatives for If: '<S34>/If' */

    /* Derivatives for Integrator: '<S13>/Integrator1' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->Integrator1_CSTATE_p[0] = modell_B.Sum1[0];

    /* Derivatives for Integrator: '<S7>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE[0] = modell_B.Sum2_b[0];

    /* Derivatives for Integrator: '<S8>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE_l[0] = modell_B.Sum2_k[0];

    /* Derivatives for Integrator: '<S13>/Integrator1' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->Integrator1_CSTATE_p[1] = modell_B.Sum1[1];

    /* Derivatives for Integrator: '<S7>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE[1] = modell_B.Sum2_b[1];

    /* Derivatives for Integrator: '<S8>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE_l[1] = modell_B.Sum2_k[1];

    /* Derivatives for Integrator: '<S13>/Integrator1' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->Integrator1_CSTATE_p[2] = modell_B.Sum1[2];

    /* Derivatives for Integrator: '<S7>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE[2] = modell_B.Sum2_b[2];

    /* Derivatives for Integrator: '<S8>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE_l[2] = modell_B.Sum2_k[2];
  }
}

/* Model initialize function */
void modell_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)modell_M,0,
                sizeof(RT_MODEL_modell));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&modell_M->solverInfo, &modell_M->Timing.simTimeStep);
    rtsiSetTPtr(&modell_M->solverInfo, &rtmGetTPtr(modell_M));
    rtsiSetStepSizePtr(&modell_M->solverInfo, &modell_M->Timing.stepSize0);
    rtsiSetdXPtr(&modell_M->solverInfo, &modell_M->ModelData.derivs);
    rtsiSetContStatesPtr(&modell_M->solverInfo, &modell_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&modell_M->solverInfo,
      &modell_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&modell_M->solverInfo, (&rtmGetErrorStatus(modell_M)));
    rtsiSetRTModelPtr(&modell_M->solverInfo, modell_M);
  }

  rtsiSetSimTimeStep(&modell_M->solverInfo, MAJOR_TIME_STEP);
  modell_M->ModelData.intgData.y = modell_M->ModelData.odeY;
  modell_M->ModelData.intgData.f[0] = modell_M->ModelData.odeF[0];
  modell_M->ModelData.intgData.f[1] = modell_M->ModelData.odeF[1];
  modell_M->ModelData.intgData.f[2] = modell_M->ModelData.odeF[2];
  modell_M->ModelData.intgData.f[3] = modell_M->ModelData.odeF[3];
  modell_M->ModelData.contStates = ((real_T *) &modell_X);
  rtsiSetSolverData(&modell_M->solverInfo, (void *)&modell_M->ModelData.intgData);
  rtsiSetSolverName(&modell_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = modell_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    modell_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    modell_M->Timing.sampleTimes = (&modell_M->Timing.sampleTimesArray[0]);
    modell_M->Timing.offsetTimes = (&modell_M->Timing.offsetTimesArray[0]);

    /* task periods */
    modell_M->Timing.sampleTimes[0] = (0.0);
    modell_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    modell_M->Timing.offsetTimes[0] = (0.0);
    modell_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(modell_M, &modell_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = modell_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    modell_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(modell_M, -1);
  modell_M->Timing.stepSize0 = 0.1;
  modell_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(modell_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    modell_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(modell_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(modell_M->rtwLogInfo, (NULL));
    rtliSetLogT(modell_M->rtwLogInfo, "tout");
    rtliSetLogX(modell_M->rtwLogInfo, "");
    rtliSetLogXFinal(modell_M->rtwLogInfo, "");
    rtliSetSigLog(modell_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(modell_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(modell_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(modell_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(modell_M->rtwLogInfo, 1);
    rtliSetLogY(modell_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(modell_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(modell_M->rtwLogInfo, (NULL));
  }

  modell_M->solverInfoPtr = (&modell_M->solverInfo);
  modell_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&modell_M->solverInfo, 0.1);
  rtsiSetSolverMode(&modell_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  modell_M->ModelData.blockIO = ((void *) &modell_B);
  (void) memset(((void *) &modell_B),0,
                sizeof(BlockIO_modell));

  /* parameters */
  modell_M->ModelData.defaultParam = ((real_T *) &modell_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &modell_X;
    modell_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_modell));
  }

  /* states (dwork) */
  modell_M->Work.dwork = ((void *) &modell_DWork);
  (void) memset((void *)&modell_DWork, 0,
                sizeof(D_Work_modell));
  modell_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  modell_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void modell_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  modell_output(tid);
}

void MdlUpdate(int_T tid)
{
  modell_update(tid);
}

void MdlInitializeSizes(void)
{
  modell_M->Sizes.numContStates = (57);/* Number of continuous states */
  modell_M->Sizes.numY = (0);          /* Number of model outputs */
  modell_M->Sizes.numU = (0);          /* Number of model inputs */
  modell_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  modell_M->Sizes.numSampTimes = (2);  /* Number of sample times */
  modell_M->Sizes.numBlocks = (308);   /* Number of blocks */
  modell_M->Sizes.numBlockIO = (78);   /* Number of block outputs */
  modell_M->Sizes.numBlockPrms = (608);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  {
    int32_T i;

    /* Integrator Block: '<S2>/Integrator1' */
    if (rtmIsFirstInitCond(modell_M)) {
      modell_X.Integrator1_CSTATE[0] = 0.0;
      modell_X.Integrator1_CSTATE[1] = 0.0;
      modell_X.Integrator1_CSTATE[2] = 0.0;
    }

    modell_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

    /* Integrator Block: '<S2>/Integrator' */
    if (rtmIsFirstInitCond(modell_M)) {
      modell_X.Integrator_CSTATE[0] = 0.0;
      modell_X.Integrator_CSTATE[1] = 0.0;
      modell_X.Integrator_CSTATE[2] = 0.0;
    }

    modell_DWork.Integrator_IWORK.IcNeedsLoading = 1;

    /* TransferFcn Block: '<S5>/Transfer Fcn' */
    modell_X.TransferFcn_CSTATE = 0.0;

    /* TransferFcn Block: '<S5>/Transfer Fcn1' */
    modell_X.TransferFcn1_CSTATE = 0.0;

    /* TransferFcn Block: '<S5>/Transfer Fcn2' */
    modell_X.TransferFcn2_CSTATE = 0.0;

    /* Integrator Block: '<S3>/Integrator1' */
    if (rtmIsFirstInitCond(modell_M)) {
      modell_X.Integrator1_CSTATE_e[0] = 0.0;
      modell_X.Integrator1_CSTATE_e[1] = 0.0;
      modell_X.Integrator1_CSTATE_e[2] = 0.0;
    }

    modell_DWork.Integrator1_IWORK_j.IcNeedsLoading = 1;

    /* InitializeConditions for Integrator: '<S3>/Integrator2' */
    modell_X.Integrator2_CSTATE[0] = modell_P.Integrator2_IC;
    modell_X.Integrator2_CSTATE[1] = modell_P.Integrator2_IC;
    modell_X.Integrator2_CSTATE[2] = modell_P.Integrator2_IC;

    /* Integrator Block: '<S12>/Integrator' */
    if (rtmIsFirstInitCond(modell_M)) {
      modell_X.Integrator_CSTATE_e[0] = 0.0;
      modell_X.Integrator_CSTATE_e[1] = 0.0;
      modell_X.Integrator_CSTATE_e[2] = 0.0;
    }

    modell_DWork.Integrator_IWORK_o.IcNeedsLoading = 1;

    /* InitializeConditions for Integrator: '<S13>/Integrator' */
    modell_X.Integrator_CSTATE_m[0] = modell_P.Integrator_IC;
    modell_X.Integrator_CSTATE_m[1] = modell_P.Integrator_IC;
    modell_X.Integrator_CSTATE_m[2] = modell_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<S8>/eta_hat' */
    modell_X.eta_hat_CSTATE[0] = modell_P.eta_hat_IC;

    /* InitializeConditions for Integrator: '<S8>/nu_hat' */
    modell_X.nu_hat_CSTATE[0] = modell_P.nu_hat_IC;

    /* InitializeConditions for Integrator: '<S8>/eta_hat' */
    modell_X.eta_hat_CSTATE[1] = modell_P.eta_hat_IC;

    /* InitializeConditions for Integrator: '<S8>/nu_hat' */
    modell_X.nu_hat_CSTATE[1] = modell_P.nu_hat_IC;

    /* InitializeConditions for Integrator: '<S8>/eta_hat' */
    modell_X.eta_hat_CSTATE[2] = modell_P.eta_hat_IC;

    /* InitializeConditions for Integrator: '<S8>/nu_hat' */
    modell_X.nu_hat_CSTATE[2] = modell_P.nu_hat_IC;
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Integrator: '<S8>/wave hat' */
      modell_X.wavehat_CSTATE[i] = modell_P.wavehat_IC;

      /* InitializeConditions for Integrator: '<S7>/wave hat' */
      modell_X.wavehat_CSTATE_g[i] = modell_P.wavehat_IC_l;
    }

    /* InitializeConditions for UnitDelay: '<S21>/Delay Input2' */
    modell_DWork.DelayInput2_DSTATE = modell_P.DelayInput2_X0;

    /* InitializeConditions for Integrator: '<S7>/eta_hat' */
    modell_X.eta_hat_CSTATE_b[0] = modell_P.eta_hat_IC_g;

    /* InitializeConditions for Integrator: '<S7>/nu_hat' */
    modell_X.nu_hat_CSTATE_g[0] = modell_P.nu_hat_IC_c;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    modell_X.Integrator1_CSTATE_p[0] = modell_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<S7>/bias_hat_integrator' */
    modell_X.bias_hat_integrator_CSTATE[0] = modell_P.bias_hat_integrator_IC;

    /* InitializeConditions for Integrator: '<S8>/bias_hat_integrator' */
    modell_X.bias_hat_integrator_CSTATE_l[0] = modell_P.bias_hat_integrator_IC_f;

    /* InitializeConditions for Integrator: '<S7>/eta_hat' */
    modell_X.eta_hat_CSTATE_b[1] = modell_P.eta_hat_IC_g;

    /* InitializeConditions for Integrator: '<S7>/nu_hat' */
    modell_X.nu_hat_CSTATE_g[1] = modell_P.nu_hat_IC_c;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    modell_X.Integrator1_CSTATE_p[1] = modell_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<S7>/bias_hat_integrator' */
    modell_X.bias_hat_integrator_CSTATE[1] = modell_P.bias_hat_integrator_IC;

    /* InitializeConditions for Integrator: '<S8>/bias_hat_integrator' */
    modell_X.bias_hat_integrator_CSTATE_l[1] = modell_P.bias_hat_integrator_IC_f;

    /* InitializeConditions for Integrator: '<S7>/eta_hat' */
    modell_X.eta_hat_CSTATE_b[2] = modell_P.eta_hat_IC_g;

    /* InitializeConditions for Integrator: '<S7>/nu_hat' */
    modell_X.nu_hat_CSTATE_g[2] = modell_P.nu_hat_IC_c;

    /* InitializeConditions for Integrator: '<S13>/Integrator1' */
    modell_X.Integrator1_CSTATE_p[2] = modell_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<S7>/bias_hat_integrator' */
    modell_X.bias_hat_integrator_CSTATE[2] = modell_P.bias_hat_integrator_IC;

    /* InitializeConditions for Integrator: '<S8>/bias_hat_integrator' */
    modell_X.bias_hat_integrator_CSTATE_l[2] = modell_P.bias_hat_integrator_IC_f;
  }

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(modell_M)) {
    rtmSetFirstInitCond(modell_M, 0);
  }
}

void MdlStart(void)
{
  {
    uint32_T tseed;
    int32_T r;
    uint32_T t;
    real_T tmpmean;
    real_T m;

    /* Start for Constant: '<Root>/Constant' */
    modell_B.Constant = modell_P.Constant_Value;

    /* ToWorkspace Block: '<S10>/To Workspace' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace";
      modell_DWork.ToWorkspace_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_eta_s",
        1,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace_PWORK.LoggedData == (NULL))
        return;
    }

    /* Start for Constant: '<S2>/initial_nu_hil' */
    modell_B.initial_nu_hil[0] = modell_P.initial_nu_hil_Value[0];
    modell_B.initial_nu_hil[1] = modell_P.initial_nu_hil_Value[1];
    modell_B.initial_nu_hil[2] = modell_P.initial_nu_hil_Value[2];

    /* ToWorkspace Block: '<S10>/To Workspace1' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace1";
      modell_DWork.ToWorkspace1_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_nu_s",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace1_PWORK.LoggedData == (NULL))
        return;
    }

    /* ToWorkspace Block: '<S10>/To Workspace4' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace4";
      modell_DWork.ToWorkspace4_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_eta_d",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace4_PWORK.LoggedData == (NULL))
        return;
    }

    /* Start for Constant: '<S3>/initial position' */
    modell_B.initialposition[0] = modell_P.initialposition_Value[0];
    modell_B.initialposition[1] = modell_P.initialposition_Value[1];
    modell_B.initialposition[2] = modell_P.initialposition_Value[2];

    /* ToWorkspace Block: '<S10>/To Workspace2' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace2";
      modell_DWork.ToWorkspace2_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_eta_i",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace2_PWORK.LoggedData == (NULL))
        return;
    }

    /* ToWorkspace Block: '<S10>/To Workspace3' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace3";
      modell_DWork.ToWorkspace3_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_nu_i",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace3_PWORK.LoggedData == (NULL))
        return;
    }

    /* Start for Constant: '<S12>/pos_diff' */
    modell_B.pos_diff[0] = modell_P.pos_diff_Value[0];
    modell_B.pos_diff[1] = modell_P.pos_diff_Value[1];
    modell_B.pos_diff[2] = modell_P.pos_diff_Value[2];

    /* Start for If: '<S44>/If' */
    modell_DWork.If_ActiveSubsystem = -1;

    /* Start for InitialCondition: '<S12>/IC' */
    modell_DWork.IC_FirstOutputTime = (rtMinusInf);

    /* ToWorkspace Block: '<S10>/To Workspace5' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace5";
      modell_DWork.ToWorkspace5_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_towforce",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace5_PWORK.LoggedData == (NULL))
        return;
    }

    /* ToWorkspace Block: '<S10>/To Workspace6' */
    {
      static int_T rt_ToWksWidths[] = { 1 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 1 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace6";
      modell_DWork.ToWorkspace6_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_X",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace6_PWORK.LoggedData == (NULL))
        return;
    }

    /* ToWorkspace Block: '<S10>/To Workspace7' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace7";
      modell_DWork.ToWorkspace7_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_bias_s",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace7_PWORK.LoggedData == (NULL))
        return;
    }

    /* ToWorkspace Block: '<S10>/To Workspace8' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace8";
      modell_DWork.ToWorkspace8_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_eta_s_hat",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace8_PWORK.LoggedData == (NULL))
        return;
    }

    /* ToWorkspace Block: '<S10>/To Workspace9' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace9";
      modell_DWork.ToWorkspace9_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_nu_s_hat",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace9_PWORK.LoggedData == (NULL))
        return;
    }

    /* ToWorkspace Block: '<S10>/To Workspace10' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace10";
      modell_DWork.ToWorkspace10_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_eta_i_hat",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace10_PWORK.LoggedData == (NULL))
        return;
    }

    /* ToWorkspace Block: '<S10>/To Workspace11' */
    {
      static int_T rt_ToWksWidths[] = { 3 };

      static int_T rt_ToWksNumDimensions[] = { 1 };

      static int_T rt_ToWksDimensions[] = { 3 };

      static boolean_T rt_ToWksIsVarDims[] = { 0 };

      static int_T *rt_ToWksCurrSigDims[] = { (NULL) };

      static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_DOUBLE };

      static int_T rt_ToWksComplexSignals[] = { 0 };

      static int_T rt_ToWksFrameData[] = { 0 };

      static const char_T *rt_ToWksLabels[] = { "" };

      static RTWLogSignalInfo rt_ToWksSignalInfo = {
        1,
        rt_ToWksWidths,
        rt_ToWksNumDimensions,
        rt_ToWksDimensions,
        rt_ToWksIsVarDims,
        rt_ToWksCurrSigDims,
        rt_ToWksDataTypeIds,
        rt_ToWksComplexSignals,
        rt_ToWksFrameData,

        { rt_ToWksLabels },
        (NULL),
        (NULL),
        (NULL),

        { (NULL) },

        { (NULL) },
        (NULL),
        (NULL)
      };

      static const char_T rt_ToWksBlockName[] = "modell/Plotter/To Workspace11";
      modell_DWork.ToWorkspace11_PWORK.LoggedData = rt_CreateStructLogVar(
        modell_M->rtwLogInfo,
        rtmGetTFinal(modell_M),
        modell_M->Timing.stepSize0,
        (&rtmGetErrorStatus(modell_M)),
        "simout_nu_i_hat",
        0,
        0,
        1,
        0.1,
        &rt_ToWksSignalInfo,
        rt_ToWksBlockName);
      if (modell_DWork.ToWorkspace11_PWORK.LoggedData == (NULL))
        return;
    }

    /* Start for enable SubSystem: '<Root>/DP controller' */

    /* InitializeConditions for Integrator: '<S15>/Integrator' */
    modell_X.Integrator_CSTATE_p[0] = modell_P.Integrator_IC_l;
    modell_X.Integrator_CSTATE_p[1] = modell_P.Integrator_IC_l;
    modell_X.Integrator_CSTATE_p[2] = modell_P.Integrator_IC_l;

    /* end of Start for SubSystem: '<Root>/DP controller' */

    /* Start for If: '<S33>/If' */
    modell_DWork.If_ActiveSubsystem_p = -1;

    /* Start for If: '<S32>/If' */
    modell_DWork.If_ActiveSubsystem_j = -1;

    /* Start for If: '<S35>/If' */
    modell_DWork.If_ActiveSubsystem_jx = -1;

    /* Start for If: '<S34>/If' */
    modell_DWork.If_ActiveSubsystem_m = -1;

    /* Start for UnitDelay: '<S21>/Delay Input2' */
    modell_B.Yk1 = modell_P.DelayInput2_X0;

    /* Start for RandomNumber: '<S51>/White Noise' */
    if (rtIsNaN(modell_P.WhiteNoise_Seed) || rtIsInf(modell_P.WhiteNoise_Seed))
    {
      tmpmean = 0.0;
    } else {
      tmpmean = fmod(floor(modell_P.WhiteNoise_Seed), 4.294967296E+009);
    }

    tseed = tmpmean < 0.0 ? -((uint32_T)(-tmpmean)) : (uint32_T)tmpmean;
    r = (int32_T)(tseed >> 16U);
    t = tseed & 32768U;
    modell_DWork.RandSeed = (((tseed - (((uint32_T)r << 16) - t)) << 16U) + t) +
      (uint32_T)r;
    if (modell_DWork.RandSeed < 1U) {
      modell_DWork.RandSeed = 1144108930U;
    }

    if (modell_DWork.RandSeed > 2147483646U) {
      modell_DWork.RandSeed = 2147483646U;
    }

    tmpmean = modell_P.WhiteNoise_Mean;
    m = rt_NormalRand(&modell_DWork.RandSeed) * modell_P.WhiteNoise_StdDev;
    modell_DWork.NextOutput = m + tmpmean;
  }

  MdlInitialize();
}

RT_MODEL_modell *modell(void)
{
  modell_initialize(1);
  return modell_M;
}

void MdlTerminate(void)
{
  modell_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
