/*
 * modell.c
 *
 * Real-Time Workshop code generation for Simulink model "modell.mdl".
 *
 * Model Version              : 1.149
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Tue Mar 12 15:06:47 2013
 *
 * Target selection: nidll_vxworks.tlc
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
    real_T tmp;
    int8_T rtAction;
    real_T tmp_0[5];
    int32_T i;
    real_T tmp_1[15];
    int32_T tmp_2;
    int32_T tmp_3;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Constant: '<Root>/Constant' */
      modell_B.Constant = modell_P.Constant_Value;
    }

    /* Integrator Block: '<S2>/Integrator1'
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
      /* ToWorkspace Block: '<S10>/To Workspace'
       */
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

    /* Integrator Block: '<S2>/Integrator'
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

    modell_B.Integrator[0] = modell_X.Integrator_CSTATE[0];
    modell_B.Integrator[1] = modell_X.Integrator_CSTATE[1];
    modell_B.Integrator[2] = modell_X.Integrator_CSTATE[2];

    /* Gain: '<S2>/nu_surge_hil' */
    modell_B.nu_surge_hil = modell_P.nu_surge_hil_Gain * modell_B.Integrator[0];

    /* Gain: '<S2>/nu_sway_hil' */
    modell_B.nu_sway_hil = modell_P.nu_sway_hil_Gain * modell_B.Integrator[1];

    /* Gain: '<S2>/nu_yaw_hil' */
    modell_B.nu_yaw_hil = modell_P.nu_yaw_hil_Gain * modell_B.Integrator[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace Block: '<S10>/To Workspace1'
       */
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
      /* ToWorkspace Block: '<S10>/To Workspace4'
       */
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

    /* Integrator Block: '<S3>/Integrator1'
     */
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
      /* ToWorkspace Block: '<S10>/To Workspace2'
       */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace2_PWORK.LoggedData, (NULL),
                            modell_B.Integrator1_e);
    }

    /* Integrator: '<S3>/Integrator2' */
    modell_B.Integrator2[0] = modell_X.Integrator2_CSTATE[0];
    modell_B.Integrator2[1] = modell_X.Integrator2_CSTATE[1];
    modell_B.Integrator2[2] = modell_X.Integrator2_CSTATE[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace Block: '<S10>/To Workspace3'
       */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace3_PWORK.LoggedData, (NULL),
                            modell_B.Integrator2);

      /* Constant: '<S12>/pos_diff' */
      modell_B.pos_diff[0] = modell_P.pos_diff_Value[0];
      modell_B.pos_diff[1] = modell_P.pos_diff_Value[1];
      modell_B.pos_diff[2] = modell_P.pos_diff_Value[2];
    }

    /* Integrator Block: '<S12>/Integrator'
     */
    if (modell_DWork.Integrator_IWORK_o.IcNeedsLoading) {
      modell_X.Integrator_CSTATE_e[0] = modell_B.pos_diff[0];
      modell_X.Integrator_CSTATE_e[1] = modell_B.pos_diff[1];
      modell_X.Integrator_CSTATE_e[2] = modell_B.pos_diff[2];
      modell_DWork.Integrator_IWORK_o.IcNeedsLoading = 0;
    }

    modell_B.Integrator_l[0] = modell_X.Integrator_CSTATE_e[0];
    modell_B.Integrator_l[1] = modell_X.Integrator_CSTATE_e[1];
    modell_B.Integrator_l[2] = modell_X.Integrator_CSTATE_e[2];

    /* Math: '<S46>/mf1' */
    tmp = modell_B.Integrator_l[0];
    modell_B.mf1 = tmp * tmp;

    /* Math: '<S46>/mf2' */
    tmp = modell_B.Integrator_l[1];
    modell_B.mf2 = tmp * tmp;

    /* Sum: '<S46>/Sum' */
    modell_B.Sum = modell_B.mf1 + modell_B.mf2;

    /* Math: '<S46>/mf3' */
    tmp = modell_B.Sum;
    if (tmp < 0.0) {
      modell_B.mf3 = -sqrt(-tmp);
    } else {
      modell_B.mf3 = sqrt(tmp);
    }

    /* Product: '<S44>/T_temp' incorporates:
     *  Constant: '<S44>/K_tow'
     */
    for (i = 0; i < 3; i++) {
      modell_B.T_temp[i] = 0.0;
      modell_B.T_temp[i] = modell_P.K_tow_Value[i] * modell_B.Integrator_l[0] +
        modell_B.T_temp[i];
      modell_B.T_temp[i] = modell_P.K_tow_Value[i + 3] * modell_B.Integrator_l[1]
        + modell_B.T_temp[i];
      modell_B.T_temp[i] = modell_P.K_tow_Value[i + 6] * modell_B.Integrator_l[2]
        + modell_B.T_temp[i];
    }

    /* Math: '<S47>/mf1' */
    tmp = modell_B.T_temp[0];
    modell_B.mf1_j = tmp * tmp;

    /* Math: '<S47>/mf2' */
    tmp = modell_B.T_temp[1];
    modell_B.mf2_m = tmp * tmp;

    /* Sum: '<S47>/Sum' */
    modell_B.Sum_p = modell_B.mf1_j + modell_B.mf2_m;

    /* Math: '<S47>/mf3' */
    tmp = modell_B.Sum_p;
    if (tmp < 0.0) {
      modell_B.mf3_f = -sqrt(-tmp);
    } else {
      modell_B.mf3_f = sqrt(tmp);
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
      } else if (modell_B.mf3_f > modell_P.T_cr_Value) {
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
      modell_slack(modell_B.T_temp, &modell_B.towing);
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
      /* ToWorkspace Block: '<S10>/To Workspace5'
       */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace5_PWORK.LoggedData, (NULL),
                            modell_B.IC);

      /* ToWorkspace Block: '<S10>/To Workspace6'
       */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace6_PWORK.LoggedData, (NULL),
                            &modell_B.mf3);
    }

    /* Integrator: '<S13>/Integrator' */
    modell_B.Integrator_n[0] = modell_X.Integrator_CSTATE_m[0];
    modell_B.Integrator_n[1] = modell_X.Integrator_CSTATE_m[1];
    modell_B.Integrator_n[2] = modell_X.Integrator_CSTATE_m[2];

    /* Switch: '<S52>/SwitchControl' incorporates:
     *  Constant: '<S13>/zero'
     *  Constant: '<S52>/Constant'
     */
    if (modell_P.Constant_Value_ow > modell_P.SwitchControl_Threshold) {
      /* Fcn: '<S54>/Row1' */
      modell_B.Row1_av = cos(modell_B.Integrator1[2]) * modell_B.Integrator_n[0]
        + sin(modell_B.Integrator1[2]) * modell_B.Integrator_n[1];

      /* Fcn: '<S54>/Row2' */
      modell_B.Row2_e = (-sin(modell_B.Integrator1[2])) * modell_B.Integrator_n
        [0] + cos(modell_B.Integrator1[2]) * modell_B.Integrator_n[1];

      /* Fcn: '<S54>/Row3' */
      modell_B.Row3_it = modell_B.Integrator_n[2];
      modell_B.SwitchControl[0] = modell_B.Row1_av;
      modell_B.SwitchControl[1] = modell_B.Row2_e;
      modell_B.SwitchControl[2] = modell_B.Row3_it;
    } else {
      modell_B.SwitchControl[0] = modell_P.zero_Value;
      modell_B.SwitchControl[1] = modell_P.zero_Value;
      modell_B.SwitchControl[2] = modell_P.zero_Value;
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace Block: '<S10>/To Workspace7'
       */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace7_PWORK.LoggedData, (NULL),
                            modell_B.SwitchControl);
    }

    /* Integrator: '<S8>/wave hat' */
    for (i = 0; i < 6; i++) {
      modell_B.wavehat[i] = modell_X.wavehat_CSTATE[i];
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S8>/C_w' */
      modell_B.C_w[i] = 0.0;
      for (tmp_3 = 0; tmp_3 < 6; tmp_3++) {
        modell_B.C_w[i] = modell_P.C_w_Gain[3 * tmp_3 + i] *
          modell_B.wavehat[tmp_3] + modell_B.C_w[i];
      }

      /* Integrator: '<S8>/eta_hat' */
      modell_B.eta_hat[i] = modell_X.eta_hat_CSTATE[i];

      /* Sum: '<S8>/Sum6' */
      modell_B.Sum6[i] = modell_B.C_w[i] + modell_B.eta_hat[i];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace Block: '<S10>/To Workspace8'
       */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace8_PWORK.LoggedData, (NULL),
                            modell_B.Sum6);
    }

    /* Integrator: '<S8>/nu_hat' */
    modell_B.nu_hat[0] = modell_X.nu_hat_CSTATE[0];
    modell_B.nu_hat[1] = modell_X.nu_hat_CSTATE[1];
    modell_B.nu_hat[2] = modell_X.nu_hat_CSTATE[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace Block: '<S10>/To Workspace9'
       */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace9_PWORK.LoggedData, (NULL),
                            modell_B.nu_hat);
    }

    /* Integrator: '<S7>/wave hat' */
    for (i = 0; i < 6; i++) {
      modell_B.wavehat_n[i] = modell_X.wavehat_CSTATE_g[i];
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S7>/C_w' */
      modell_B.C_w_d[i] = 0.0;
      for (tmp_3 = 0; tmp_3 < 6; tmp_3++) {
        modell_B.C_w_d[i] = modell_P.C_w_Gain_d[3 * tmp_3 + i] *
          modell_B.wavehat_n[tmp_3] + modell_B.C_w_d[i];
      }

      /* Integrator: '<S7>/eta_hat' */
      modell_B.eta_hat_m[i] = modell_X.eta_hat_CSTATE_b[i];

      /* Sum: '<S7>/Sum6' */
      modell_B.Sum6_a[i] = modell_B.C_w_d[i] + modell_B.eta_hat_m[i];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace Block: '<S10>/To Workspace10'
       */
      rt_UpdateStructLogVar((StructLogVar *)
                            modell_DWork.ToWorkspace10_PWORK.LoggedData, (NULL),
                            modell_B.Sum6_a);
    }

    /* Integrator: '<S7>/nu_hat' */
    modell_B.nu_hat_n[0] = modell_X.nu_hat_CSTATE_g[0];
    modell_B.nu_hat_n[1] = modell_X.nu_hat_CSTATE_g[1];
    modell_B.nu_hat_n[2] = modell_X.nu_hat_CSTATE_g[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* ToWorkspace Block: '<S10>/To Workspace11'
       */
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
      /* SignalConversion: '<S15>/TmpHiddenBufferAtKdInport1' */
      modell_B.TmpHiddenBufferAtKdInport1[0] = modell_B.nu_surge_hil;
      modell_B.TmpHiddenBufferAtKdInport1[1] = modell_B.nu_sway_hil;
      modell_B.TmpHiddenBufferAtKdInport1[2] = modell_B.nu_yaw_hil;
      for (i = 0; i < 3; i++) {
        /* Integrator: '<S15>/Integrator' */
        modell_B.Integrator_ln[i] = modell_X.Integrator_CSTATE_p[i];

        /* Gain: '<S15>/Kd' */
        modell_B.Kd[i] = 0.0;
        modell_B.Kd[i] = modell_P.Kd_Gain[i] *
          modell_B.TmpHiddenBufferAtKdInport1[0] + modell_B.Kd[i];
        modell_B.Kd[i] = modell_P.Kd_Gain[i + 3] *
          modell_B.TmpHiddenBufferAtKdInport1[1] + modell_B.Kd[i];
        modell_B.Kd[i] = modell_P.Kd_Gain[i + 6] *
          modell_B.TmpHiddenBufferAtKdInport1[2] + modell_B.Kd[i];
      }

      /* Fcn: '<S15>/yaw angle' */
      modell_B.psi = modell_B.Integrator1[2];

      /* Saturate: '<S18>/Saturation' */
      tmp = modell_B.psi;
      modell_B.Saturation_o = rt_SATURATE(tmp, modell_P.Saturation_LowerSat_b,
        modell_P.Saturation_UpperSat_i);

      /* Signum: '<S18>/Sign' */
      modell_B.Sign = rt_SIGNd_snf(modell_B.Saturation_o);

      /* Gain: '<S18>/Gain' */
      modell_B.Gain_a = modell_P.Gain_Gain_i * modell_B.Sign;

      /* Sum: '<S18>/Sum1' */
      modell_B.Sum1_f = modell_B.Saturation_o + modell_B.Gain_a;

      /* Math: '<S18>/Math Function' incorporates:
       *  Constant: '<S18>/Constant'
       */
      modell_B.MathFunction = rt_rem_snf(modell_B.Sum1_f,
        modell_P.Constant_Value_jb);

      /* Sum: '<S18>/Sum' */
      modell_B.Sum_l = modell_B.MathFunction - modell_B.Gain_a;

      /* Sum: '<S15>/Sum2' */
      modell_B.regulationerror[0] = modell_B.TransferFcn - modell_B.Integrator1
        [0];
      modell_B.regulationerror[1] = modell_B.TransferFcn1 -
        modell_B.Integrator1[1];
      modell_B.regulationerror[2] = modell_B.TransferFcn2 -
        modell_B.Integrator1[2];

      /* Gain: '<S15>/Reg_e_N_hil' */
      modell_B.Reg_e_N_hil = modell_P.Reg_e_N_hil_Gain *
        modell_B.regulationerror[0];

      /* Gain: '<S15>/Reg_e_E_hil' */
      modell_B.Reg_e_E_hil = modell_P.Reg_e_E_hil_Gain *
        modell_B.regulationerror[1];

      /* Gain: '<S15>/Reg_e_Psi_hil' */
      modell_B.Reg_e_Psi_hil = modell_P.Reg_e_Psi_hil_Gain *
        modell_B.regulationerror[2];

      /* Saturate: '<S17>/Saturation' */
      tmp = modell_B.Reg_e_Psi_hil;
      modell_B.Saturation_f = rt_SATURATE(tmp, modell_P.Saturation_LowerSat_n,
        modell_P.Saturation_UpperSat_e);

      /* Signum: '<S17>/Sign' */
      modell_B.Sign_l = rt_SIGNd_snf(modell_B.Saturation_f);

      /* Gain: '<S17>/Gain' */
      modell_B.Gain_h = modell_P.Gain_Gain_k * modell_B.Sign_l;

      /* Sum: '<S17>/Sum1' */
      modell_B.Sum1_h = modell_B.Saturation_f + modell_B.Gain_h;

      /* Math: '<S17>/Math Function' incorporates:
       *  Constant: '<S17>/Constant'
       */
      modell_B.MathFunction_i = rt_rem_snf(modell_B.Sum1_h,
        modell_P.Constant_Value_f);

      /* Sum: '<S17>/Sum' */
      modell_B.Sum_nl = modell_B.MathFunction_i - modell_B.Gain_h;

      /* Fcn: '<S16>/Row1' */
      modell_B.Row1_e = cos(modell_B.Sum_l) * modell_B.Reg_e_N_hil + sin
        (modell_B.Sum_l) * modell_B.Reg_e_E_hil;

      /* Fcn: '<S16>/Row2' */
      modell_B.Row2_o = (-sin(modell_B.Sum_l)) * modell_B.Reg_e_N_hil + cos
        (modell_B.Sum_l) * modell_B.Reg_e_E_hil;

      /* Fcn: '<S16>/Row3' */
      modell_B.Row3_g = modell_B.Sum_nl;

      /* SignalConversion: '<S15>/TmpHiddenBufferAtKpInport1' */
      modell_B.TmpHiddenBufferAtKpInport1[0] = modell_B.Row1_e;
      modell_B.TmpHiddenBufferAtKpInport1[1] = modell_B.Row2_o;
      modell_B.TmpHiddenBufferAtKpInport1[2] = modell_B.Row3_g;
      for (i = 0; i < 3; i++) {
        /* Gain: '<S15>/Ki' */
        modell_B.Ki[i] = 0.0;
        modell_B.Ki[i] = modell_P.Ki_Gain[i] * modell_B.Integrator_ln[0] +
          modell_B.Ki[i];
        modell_B.Ki[i] = modell_P.Ki_Gain[i + 3] * modell_B.Integrator_ln[1] +
          modell_B.Ki[i];
        modell_B.Ki[i] = modell_P.Ki_Gain[i + 6] * modell_B.Integrator_ln[2] +
          modell_B.Ki[i];

        /* Gain: '<S15>/Kp' */
        modell_B.Kp[i] = 0.0;
        modell_B.Kp[i] = modell_P.Kp_Gain[i] *
          modell_B.TmpHiddenBufferAtKpInport1[0] + modell_B.Kp[i];
        modell_B.Kp[i] = modell_P.Kp_Gain[i + 3] *
          modell_B.TmpHiddenBufferAtKpInport1[1] + modell_B.Kp[i];
        modell_B.Kp[i] = modell_P.Kp_Gain[i + 6] *
          modell_B.TmpHiddenBufferAtKpInport1[2] + modell_B.Kp[i];

        /* Product: '<S15>/Product' incorporates:
         *  Constant: '<S15>/Kp_scale'
         */
        modell_B.Product_l[i] = modell_P.Kp_scale_Value * modell_B.Kp[i];

        /* Product: '<S15>/Product1' incorporates:
         *  Constant: '<S15>/Ki_scale'
         */
        modell_B.Product1_j[i] = modell_B.Ki[i] * modell_P.Ki_scale_Value;

        /* Product: '<S15>/Product2' incorporates:
         *  Constant: '<S15>/Kd_scale'
         */
        modell_B.Product2[i] = modell_B.Kd[i] * modell_P.Kd_scale_Value;

        /* Sum: '<S15>/Sum3' */
        modell_B.Sum3_d[i] = modell_B.Product_l[i] + modell_B.Product1_j[i];

        /* Sum: '<S15>/Sum1' */
        modell_B.Sum1_hw[i] = modell_B.Sum3_d[i] - modell_B.Product2[i];
      }
    }

    /* end of Outputs for SubSystem: '<Root>/DP controller' */
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
    modell_B.Sum_b = modell_B.if_f.In1 + modell_B.else_a.In1;
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
      /* Sum: '<S9>/Sum3' incorporates:
       *  Constant: '<S9>/Constant'
       *  Constant: '<S9>/PS3_L2'
       */
      modell_B.Sum3 = modell_P.PS3_L2_Value + modell_P.Constant_Value_o;

      /* Gain: '<S9>/g1' */
      modell_B.g1 = modell_P.g1_Gain * modell_B.Sum3;

      /* Sum: '<S9>/Sum4' incorporates:
       *  Constant: '<S9>/Constant1'
       *  Constant: '<S9>/PS3_R2'
       */
      modell_B.Sum4 = modell_P.PS3_R2_Value + modell_P.Constant1_Value;

      /* Gain: '<S9>/g2' */
      modell_B.g2 = modell_P.g2_Gain * modell_B.Sum4;

      /* Product: '<S4>/Product' incorporates:
       *  Constant: '<S4>/Ke^-1'
       *  Constant: '<S4>/Te^+'
       */
      for (i = 0; i < 5; i++) {
        for (tmp_3 = 0; tmp_3 < 3; tmp_3++) {
          modell_B.Product[i + 5 * tmp_3] = 0.0;
          for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
            modell_B.Product[i + 5 * tmp_3] = modell_P.Ke1_Value[5 * tmp_2 + i] *
              modell_P.Te_Value[5 * tmp_3 + tmp_2] + modell_B.Product[5 * tmp_3
              + i];
          }
        }
      }
    }

    /* Gain: '<S4>/joystick_gain_surge' */
    modell_B.joystick_gain_surge = modell_P.joystick_gain_surge_Gain *
      modell_B.Sum_b;

    /* Gain: '<S4>/joystick_gain_sway' */
    modell_B.joystick_gain_sway = modell_P.joystick_gain_sway_Gain *
      modell_B.Sum_i;

    /* Sum: '<S4>/Sum' */
    modell_B.Sum_c = modell_B.g1 + modell_B.g2;

    /* Gain: '<S4>/joystick_gain_yaw' */
    modell_B.joystick_gain_yaw = modell_P.joystick_gain_yaw_Gain *
      modell_B.Sum_c;

    /* SignalConversion: '<S4>/TmpHiddenBufferAtProduct1Inport2' */
    modell_B.TmpHiddenBufferAtProduct1Inport[0] = modell_B.joystick_gain_surge;
    modell_B.TmpHiddenBufferAtProduct1Inport[1] = modell_B.joystick_gain_sway;
    modell_B.TmpHiddenBufferAtProduct1Inport[2] = modell_B.joystick_gain_yaw;

    /* Saturate: '<S4>/Saturation' */
    for (i = 0; i < 5; i++) {
      /* Product: '<S4>/Product1' */
      modell_B.Product1[i] = 0.0;
      modell_B.Product1[i] = modell_B.Product[i] *
        modell_B.TmpHiddenBufferAtProduct1Inport[0] + modell_B.Product1[i];
      modell_B.Product1[i] = modell_B.Product[i + 5] *
        modell_B.TmpHiddenBufferAtProduct1Inport[1] + modell_B.Product1[i];
      modell_B.Product1[i] = modell_B.Product[i + 10] *
        modell_B.TmpHiddenBufferAtProduct1Inport[2] + modell_B.Product1[i];
      tmp_0[i] = modell_B.Product1[i];
      modell_B.Saturation[i] = rt_SATURATE(tmp_0[i],
        modell_P.Saturation_LowerSat, modell_P.Saturation_UpperSat);
    }

    if (rtmIsMajorTimeStep(modell_M)) {
      /* Product: '<S11>/Product' incorporates:
       *  Constant: '<S11>/Ke^-1'
       *  Constant: '<S11>/Te^+'
       */
      for (i = 0; i < 5; i++) {
        for (tmp_3 = 0; tmp_3 < 3; tmp_3++) {
          modell_B.Product_c[i + 5 * tmp_3] = 0.0;
          for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
            modell_B.Product_c[i + 5 * tmp_3] = modell_P.Ke1_Value_c[5 * tmp_2 +
              i] * modell_P.Te_Value_h[5 * tmp_3 + tmp_2] + modell_B.Product_c[5
              * tmp_3 + i];
          }
        }
      }
    }

    /* Sum: '<S11>/Sum' */
    modell_B.Sum_pv[0] = modell_B.Sum1_hw[0] - modell_B.IC[0];
    modell_B.Sum_pv[1] = modell_B.Sum1_hw[1] - modell_B.IC[1];
    modell_B.Sum_pv[2] = modell_B.Sum1_hw[2] - modell_B.IC[2];

    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Constant: '<Root>/MODE'
     *  Constant: '<S11>/BT_power_limit'
     *  Constant: '<S11>/VSP_speeds'
     *  Constant: '<S4>/BT_power_limit'
     *  Constant: '<S4>/VSP_speeds'
     *  Constant: '<S5>/BT_saturation'
     *  Constant: '<S5>/VSP_speeds'
     *  Saturate: '<S11>/Saturation'
     */
    switch ((int32_T)modell_P.MODE_Value) {
     case 0:
      /* Gain: '<S6>/U1' */
      modell_B.U1 = modell_P.U1_Gain * modell_B.Sum_b;

      /* Gain: '<S6>/U2' */
      modell_B.U2 = modell_P.U2_Gain * modell_B.Sum_i;

      /* Gain: '<S6>/U3' */
      modell_B.U3 = modell_P.U3_Gain * modell_B.Sum_e;

      /* Gain: '<S6>/U4' */
      modell_B.U4 = modell_P.U4_Gain * modell_B.Sum_d;

      /* Sum: '<S6>/Sum' */
      modell_B.Sum_ej = modell_B.g1 + modell_B.g2;

      /* Gain: '<S6>/U5' */
      modell_B.U5 = modell_P.U5_Gain * modell_B.Sum_ej;
      modell_B.MultiportSwitch[0] = modell_B.U1;
      modell_B.MultiportSwitch[1] = modell_B.U2;
      modell_B.MultiportSwitch[2] = modell_B.U3;
      modell_B.MultiportSwitch[3] = modell_B.U4;
      modell_B.MultiportSwitch[4] = modell_B.U5;
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
        modell_B.Product1_o[i] = 0.0;
        modell_B.Product1_o[i] = modell_B.Product_c[i] * modell_B.Sum_pv[0] +
          modell_B.Product1_o[i];
        modell_B.Product1_o[i] = modell_B.Product_c[i + 5] * modell_B.Sum_pv[1]
          + modell_B.Product1_o[i];
        modell_B.Product1_o[i] = modell_B.Product_c[i + 10] * modell_B.Sum_pv[2]
          + modell_B.Product1_o[i];
        tmp_0[i] = modell_B.Product1_o[i];
        modell_B.Saturation_a[i] = rt_SATURATE(tmp_0[i],
          modell_P.Saturation_LowerSat_e, modell_P.Saturation_UpperSat_c);
        modell_B.MultiportSwitch[i] = modell_B.Saturation_a[i];
      }

      modell_B.MultiportSwitch[5] = modell_P.VSP_speeds_Value_k;
      modell_B.MultiportSwitch[6] = modell_P.BT_power_limit_Value_f;
      break;
    }

    /* Gain: '<S2>/BT_power' */
    modell_B.BT_power = modell_P.BT_power_Gain * modell_B.MultiportSwitch[4];

    /* Fcn: '<S19>/x->r' */
    modell_B.xr = rt_hypot_snf(modell_B.MultiportSwitch[1],
      modell_B.MultiportSwitch[0]);

    /* Fcn: '<S19>/x->theta' */
    modell_B.xtheta = rt_atan2_snf(modell_B.MultiportSwitch[0],
      modell_B.MultiportSwitch[1]);

    /* Fcn: '<S20>/x->r' */
    modell_B.xr_i = rt_hypot_snf(modell_B.MultiportSwitch[3],
      modell_B.MultiportSwitch[2]);

    /* Fcn: '<S20>/x->theta' */
    modell_B.xtheta_d = rt_atan2_snf(modell_B.MultiportSwitch[2],
      modell_B.MultiportSwitch[3]);

    /* Gain: '<S2>/D' */
    for (i = 0; i < 3; i++) {
      modell_B.D[i] = 0.0;
      modell_B.D[i] = modell_P.D_Gain[i] * modell_B.Integrator[0] + modell_B.D[i];
      modell_B.D[i] = modell_P.D_Gain[i + 3] * modell_B.Integrator[1] +
        modell_B.D[i];
      modell_B.D[i] = modell_P.D_Gain[i + 6] * modell_B.Integrator[2] +
        modell_B.D[i];
    }

    /* Gain: '<S2>/u1_hil' */
    modell_B.u1_hil = modell_P.u1_hil_Gain * modell_B.MultiportSwitch[0];

    /* Gain: '<S2>/u2_hil' */
    modell_B.u2_hil = modell_P.u2_hil_Gain * modell_B.MultiportSwitch[1];

    /* Gain: '<S2>/u3_hil' */
    modell_B.u3_hil = modell_P.u3_hil_Gain * modell_B.MultiportSwitch[2];

    /* Gain: '<S2>/u4_hil' */
    modell_B.u4_hil = modell_P.u4_hil_Gain * modell_B.MultiportSwitch[3];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* S-Function (sfix_tsampmath) Block: '<S21>/sample time'
       */
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
    modell_B.deltariselimit = modell_B.MultiportSwitch[5] * modell_B.sampletime;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* UnitDelay: '<S21>/Delay Input2' */
      modell_B.Yk1 = modell_DWork.DelayInput2_DSTATE;
    }

    /* Sum: '<S21>/Difference Inputs1' */
    modell_B.UkYk1 = modell_B.MultiportSwitch[4] - modell_B.Yk1;

    /* RelationalOperator: '<S23>/LowerRelop1' */
    modell_B.LowerRelop1 = (modell_B.UkYk1 > modell_B.deltariselimit);

    /* Gain: '<S2>/neg' */
    modell_B.neg = modell_P.neg_Gain * modell_B.MultiportSwitch[5];

    /* Product: '<S21>/delta fall limit' */
    modell_B.deltafalllimit = modell_B.neg * modell_B.sampletime;

    /* RelationalOperator: '<S23>/UpperRelop' */
    modell_B.UpperRelop = (modell_B.UkYk1 < modell_B.deltafalllimit);

    /* Switch: '<S23>/Switch' */
    if (modell_B.UpperRelop) {
      modell_B.Switch = modell_B.deltafalllimit;
    } else {
      modell_B.Switch = modell_B.UkYk1;
    }

    /* Switch: '<S23>/Switch2' */
    if (modell_B.LowerRelop1) {
      modell_B.Switch2 = modell_B.deltariselimit;
    } else {
      modell_B.Switch2 = modell_B.Switch;
    }

    /* Sum: '<S21>/Difference Inputs2' */
    modell_B.DifferenceInputs2 = modell_B.Switch2 + modell_B.Yk1;

    /* Gain: '<S2>/u5_hil' */
    modell_B.u5_hil = modell_P.u5_hil_Gain * modell_B.DifferenceInputs2;

    /* SignalConversion: '<S2>/TmpHiddenBufferAtProductInport3' */
    modell_B.TmpHiddenBufferAtProductInport3[0] = modell_B.u1_hil;
    modell_B.TmpHiddenBufferAtProductInport3[1] = modell_B.u2_hil;
    modell_B.TmpHiddenBufferAtProductInport3[2] = modell_B.u3_hil;
    modell_B.TmpHiddenBufferAtProductInport3[3] = modell_B.u4_hil;
    modell_B.TmpHiddenBufferAtProductInport3[4] = modell_B.u5_hil;

    /* Product: '<S2>/Product' incorporates:
     *  Constant: '<S2>/Constant'
     *  Constant: '<S2>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
        tmp_1[i + 3 * tmp_3] = 0.0;
        for (tmp_2 = 0; tmp_2 < 5; tmp_2++) {
          tmp_1[i + 3 * tmp_3] = modell_P.Constant_Value_e[3 * tmp_2 + i] *
            modell_P.Constant1_Value_o[5 * tmp_3 + tmp_2] + tmp_1[3 * tmp_3 + i];
        }
      }
    }

    for (i = 0; i < 3; i++) {
      modell_B.Product_o[i] = 0.0;
      for (tmp_3 = 0; tmp_3 < 5; tmp_3++) {
        modell_B.Product_o[i] = tmp_1[3 * tmp_3 + i] *
          modell_B.TmpHiddenBufferAtProductInport3[tmp_3] + modell_B.Product_o[i];
      }
    }

    if (rtmIsMajorTimeStep(modell_M)) {
    }

    /* Fcn: '<S22>/Fcn' */
    modell_B.x_dot = cos(modell_B.Integrator1[2]) * modell_B.Integrator[0] - sin
      (modell_B.Integrator1[2]) * modell_B.Integrator[1];

    /* Fcn: '<S22>/Fcn1' */
    modell_B.y_dot = sin(modell_B.Integrator1[2]) * modell_B.Integrator[0] + cos
      (modell_B.Integrator1[2]) * modell_B.Integrator[1];

    /* Fcn: '<S22>/Fcn2' */
    modell_B.psi_dot = modell_B.Integrator[2];

    /* Gain: '<S2>/tau_surge_hil' */
    modell_B.tau_surge_hil = modell_P.tau_surge_hil_Gain * modell_B.Product_o[0];

    /* Gain: '<S2>/tau_sway_hil' */
    modell_B.tau_sway_hil = modell_P.tau_sway_hil_Gain * modell_B.Product_o[1];

    /* Gain: '<S2>/tau_yaw_hil' */
    modell_B.tau_yaw_hil = modell_P.tau_yaw_hil_Gain * modell_B.Product_o[2];

    /* Sum: '<S2>/Sum3' */
    modell_B.Sum3_o[0] = modell_B.tau_surge_hil - modell_B.D[0];
    modell_B.Sum3_o[1] = modell_B.tau_sway_hil - modell_B.D[1];
    modell_B.Sum3_o[2] = modell_B.tau_yaw_hil - modell_B.D[2];

    /* Gain: '<S2>/VIS_HIL_E' */
    modell_B.VIS_HIL_E = modell_P.VIS_HIL_E_Gain * modell_B.Integrator1[1];

    /* Gain: '<S2>/VIS_HIL_N' */
    modell_B.VIS_HIL_N = modell_P.VIS_HIL_N_Gain * modell_B.Integrator1[0];

    /* Gain: '<S2>/VIS_HIL_PIS' */
    modell_B.VIS_HIL_PIS = modell_P.VIS_HIL_PIS_Gain * modell_B.Integrator1[2];

    /* Gain: '<S2>/VSP_angle_deg_port' */
    modell_B.VSP_angle_deg_port = modell_P.VSP_angle_deg_port_Gain *
      modell_B.xtheta;

    /* Gain: '<S2>/VSP_angle_deg_stbd' */
    modell_B.VSP_angle_deg_stbd = modell_P.VSP_angle_deg_stbd_Gain *
      modell_B.xtheta_d;

    /* Fcn: '<S24>/Fcn' */
    modell_B.x_dot_a = cos(modell_B.Integrator1_e[2]) * modell_B.Integrator2[0]
      - sin(modell_B.Integrator1_e[2]) * modell_B.Integrator2[1];

    /* Fcn: '<S24>/Fcn1' */
    modell_B.y_dot_g = sin(modell_B.Integrator1_e[2]) * modell_B.Integrator2[0]
      + cos(modell_B.Integrator1_e[2]) * modell_B.Integrator2[1];

    /* Fcn: '<S24>/Fcn2' */
    modell_B.psi_dot_p = modell_B.Integrator2[2];

    /* Saturate: '<S25>/Saturation' */
    tmp = modell_B.IC[0];
    modell_B.Saturation_l = rt_SATURATE(tmp, modell_P.Saturation_LowerSat_j,
      modell_P.Saturation_UpperSat_n);

    /* Saturate: '<S25>/Saturation1' */
    tmp = modell_B.IC[1];
    modell_B.Saturation1 = rt_SATURATE(tmp, modell_P.Saturation1_LowerSat,
      modell_P.Saturation1_UpperSat);

    /* Saturate: '<S25>/Saturation2' */
    tmp = modell_B.IC[2];
    modell_B.Saturation2 = rt_SATURATE(tmp, modell_P.Saturation2_LowerSat,
      modell_P.Saturation2_UpperSat);
    for (i = 0; i < 3; i++) {
      /* Gain: '<S2>/inv(M)' */
      modell_B.invM[i] = 0.0;
      modell_B.invM[i] = modell_P.invM_Gain[i] * modell_B.Sum3_o[0] +
        modell_B.invM[i];
      modell_B.invM[i] = modell_P.invM_Gain[i + 3] * modell_B.Sum3_o[1] +
        modell_B.invM[i];
      modell_B.invM[i] = modell_P.invM_Gain[i + 6] * modell_B.Sum3_o[2] +
        modell_B.invM[i];

      /* Gain: '<S3>/D' */
      modell_B.D_f[i] = 0.0;
      modell_B.D_f[i] = modell_P.D_Gain_d[i] * modell_B.Integrator2[0] +
        modell_B.D_f[i];
      modell_B.D_f[i] = modell_P.D_Gain_d[i + 3] * modell_B.Integrator2[1] +
        modell_B.D_f[i];
      modell_B.D_f[i] = modell_P.D_Gain_d[i + 6] * modell_B.Integrator2[2] +
        modell_B.D_f[i];

      /* Integrator: '<S13>/Integrator1' */
      modell_B.Integrator1_n[i] = modell_X.Integrator1_CSTATE_p[i];
    }

    /* Switch: '<S53>/SwitchControl' incorporates:
     *  Constant: '<S13>/zero'
     *  Constant: '<S53>/Constant'
     */
    if (modell_P.Constant_Value_b > modell_P.SwitchControl_Threshold_a) {
      modell_B.SwitchControl_o[0] = modell_P.zero_Value;
      modell_B.SwitchControl_o[1] = modell_P.zero_Value;
      modell_B.SwitchControl_o[2] = modell_P.zero_Value;
    } else {
      /* Fcn: '<S55>/Row1' */
      modell_B.Row1_k = cos(modell_B.Integrator1[2]) * modell_B.Integrator1_n[0]
        + sin(modell_B.Integrator1[2]) * modell_B.Integrator1_n[1];

      /* Fcn: '<S55>/Row2' */
      modell_B.Row2_g1 = (-sin(modell_B.Integrator1[2])) *
        modell_B.Integrator1_n[0] + cos(modell_B.Integrator1[2]) *
        modell_B.Integrator1_n[1];

      /* Fcn: '<S55>/Row3' */
      modell_B.Row3_d = modell_B.Integrator1_n[2];
      modell_B.SwitchControl_o[0] = modell_B.Row1_k;
      modell_B.SwitchControl_o[1] = modell_B.Row2_g1;
      modell_B.SwitchControl_o[2] = modell_B.Row3_d;
    }

    /* Sum: '<S3>/Sum3' */
    modell_B.Sum3_f[0] = (modell_B.Saturation_l - modell_B.D_f[0]) +
      modell_B.SwitchControl_o[0];
    modell_B.Sum3_f[1] = (modell_B.Saturation1 - modell_B.D_f[1]) +
      modell_B.SwitchControl_o[1];
    modell_B.Sum3_f[2] = (modell_B.Saturation2 - modell_B.D_f[2]) +
      modell_B.SwitchControl_o[2];

    /* Gain: '<S3>/inv(M)' */
    for (i = 0; i < 3; i++) {
      modell_B.invM_g[i] = 0.0;
      modell_B.invM_g[i] = modell_P.invM_Gain_d[i] * modell_B.Sum3_f[0] +
        modell_B.invM_g[i];
      modell_B.invM_g[i] = modell_P.invM_Gain_d[i + 3] * modell_B.Sum3_f[1] +
        modell_B.invM_g[i];
      modell_B.invM_g[i] = modell_P.invM_Gain_d[i + 6] * modell_B.Sum3_f[2] +
        modell_B.invM_g[i];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
    }

    /* Gain: '<S7>/A_w' */
    for (i = 0; i < 6; i++) {
      modell_B.A_w[i] = 0.0;
      for (tmp_3 = 0; tmp_3 < 6; tmp_3++) {
        modell_B.A_w[i] = modell_P.A_w_Gain[6 * tmp_3 + i] *
          modell_B.wavehat_n[tmp_3] + modell_B.A_w[i];
      }
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S7>/D' */
      modell_B.D_fe[i] = 0.0;
      modell_B.D_fe[i] = modell_P.D_Gain_h[i] * modell_B.nu_hat_n[0] +
        modell_B.D_fe[i];
      modell_B.D_fe[i] = modell_P.D_Gain_h[i + 3] * modell_B.nu_hat_n[1] +
        modell_B.D_fe[i];
      modell_B.D_fe[i] = modell_P.D_Gain_h[i + 6] * modell_B.nu_hat_n[2] +
        modell_B.D_fe[i];

      /* Sum: '<S7>/Sum' */
      modell_B.Sum_n[i] = modell_B.Integrator1_e[i] + modell_B.Sum6_a[i];
    }

    /* Gain: '<S7>/K_1' */
    for (i = 0; i < 6; i++) {
      modell_B.K_1[i] = 0.0;
      modell_B.K_1[i] = modell_P.K_1_Gain[i] * modell_B.Sum_n[0] +
        modell_B.K_1[i];
      modell_B.K_1[i] = modell_P.K_1_Gain[i + 6] * modell_B.Sum_n[1] +
        modell_B.K_1[i];
      modell_B.K_1[i] = modell_P.K_1_Gain[i + 12] * modell_B.Sum_n[2] +
        modell_B.K_1[i];
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S7>/K_2' */
      modell_B.K_2[i] = 0.0;
      modell_B.K_2[i] = modell_P.K_2_Gain[i] * modell_B.Sum_n[0] +
        modell_B.K_2[i];
      modell_B.K_2[i] = modell_P.K_2_Gain[i + 3] * modell_B.Sum_n[1] +
        modell_B.K_2[i];
      modell_B.K_2[i] = modell_P.K_2_Gain[i + 6] * modell_B.Sum_n[2] +
        modell_B.K_2[i];

      /* Gain: '<S7>/K_3' */
      modell_B.K_3[i] = 0.0;
      modell_B.K_3[i] = modell_P.K_3_Gain[i] * modell_B.Sum_n[0] +
        modell_B.K_3[i];
      modell_B.K_3[i] = modell_P.K_3_Gain[i + 3] * modell_B.Sum_n[1] +
        modell_B.K_3[i];
      modell_B.K_3[i] = modell_P.K_3_Gain[i + 6] * modell_B.Sum_n[2] +
        modell_B.K_3[i];

      /* Gain: '<S7>/K_4' */
      modell_B.K_4[i] = 0.0;
      modell_B.K_4[i] = modell_P.K_4_Gain[i] * modell_B.Sum_n[0] +
        modell_B.K_4[i];
      modell_B.K_4[i] = modell_P.K_4_Gain[i + 3] * modell_B.Sum_n[1] +
        modell_B.K_4[i];
      modell_B.K_4[i] = modell_P.K_4_Gain[i + 6] * modell_B.Sum_n[2] +
        modell_B.K_4[i];

      /* Integrator: '<S7>/bias_hat_integrator' */
      modell_B.bias_hat_integrator[i] = modell_X.bias_hat_integrator_CSTATE[i];
    }

    /* Fcn: '<S27>/Row1' */
    modell_B.Row1 = cos(modell_B.Integrator1_e[2]) *
      modell_B.bias_hat_integrator[0] + sin(modell_B.Integrator1_e[2]) *
      modell_B.bias_hat_integrator[1];

    /* Fcn: '<S27>/Row2' */
    modell_B.Row2 = (-sin(modell_B.Integrator1_e[2])) *
      modell_B.bias_hat_integrator[0] + cos(modell_B.Integrator1_e[2]) *
      modell_B.bias_hat_integrator[1];

    /* Fcn: '<S27>/Row3' */
    modell_B.Row3 = modell_B.bias_hat_integrator[2];

    /* Fcn: '<S26>/Row1' */
    modell_B.Row1_d = cos(modell_B.Integrator1_e[2]) * modell_B.K_4[0] + sin
      (modell_B.Integrator1_e[2]) * modell_B.K_4[1];

    /* Fcn: '<S26>/Row2' */
    modell_B.Row2_p = (-sin(modell_B.Integrator1_e[2])) * modell_B.K_4[0] + cos
      (modell_B.Integrator1_e[2]) * modell_B.K_4[1];

    /* Fcn: '<S26>/Row3' */
    modell_B.Row3_j = modell_B.K_4[2];

    /* Sum: '<S7>/Sum1' */
    modell_B.Sum1[0] = modell_B.Row1_d + modell_B.IC[0];
    modell_B.Sum1[1] = modell_B.Row2_p + modell_B.IC[1];
    modell_B.Sum1[2] = modell_B.Row3_j + modell_B.IC[2];

    /* Sum: '<S7>/Sum4' */
    modell_B.Sum4_o[0] = (modell_B.Row1 + modell_B.Sum1[0]) - modell_B.D_fe[0];
    modell_B.Sum4_o[1] = (modell_B.Row2 + modell_B.Sum1[1]) - modell_B.D_fe[1];
    modell_B.Sum4_o[2] = (modell_B.Row3 + modell_B.Sum1[2]) - modell_B.D_fe[2];

    /* Fcn: '<S28>/Fcn' */
    modell_B.x_dot_f = cos(modell_B.Integrator1_e[2]) * modell_B.nu_hat_n[0] -
      sin(modell_B.Integrator1_e[2]) * modell_B.nu_hat_n[1];

    /* Fcn: '<S28>/Fcn1' */
    modell_B.y_dot_m = sin(modell_B.Integrator1_e[2]) * modell_B.nu_hat_n[0] +
      cos(modell_B.Integrator1_e[2]) * modell_B.nu_hat_n[1];

    /* Fcn: '<S28>/Fcn2' */
    modell_B.psi_dot_g = modell_B.nu_hat_n[2];
    for (i = 0; i < 3; i++) {
      /* Gain: '<S7>/M_inv' */
      modell_B.M_inv[i] = 0.0;
      modell_B.M_inv[i] = modell_P.M_inv_Gain[i] * modell_B.Sum4_o[0] +
        modell_B.M_inv[i];
      modell_B.M_inv[i] = modell_P.M_inv_Gain[i + 3] * modell_B.Sum4_o[1] +
        modell_B.M_inv[i];
      modell_B.M_inv[i] = modell_P.M_inv_Gain[i + 6] * modell_B.Sum4_o[2] +
        modell_B.M_inv[i];

      /* Gain: '<S7>/T_inv' */
      modell_B.T_inv[i] = 0.0;
      modell_B.T_inv[i] = modell_P.T_inv_Gain[i] * modell_B.bias_hat_integrator
        [0] + modell_B.T_inv[i];
      modell_B.T_inv[i] = modell_P.T_inv_Gain[i + 3] *
        modell_B.bias_hat_integrator[1] + modell_B.T_inv[i];
      modell_B.T_inv[i] = modell_P.T_inv_Gain[i + 6] *
        modell_B.bias_hat_integrator[2] + modell_B.T_inv[i];

      /* Sum: '<S7>/Sum2' */
      modell_B.Sum2_b[i] = modell_B.K_3[i] - modell_B.T_inv[i];
    }

    /* Sum: '<S7>/Sum3' */
    modell_B.Sum3_g[0] = modell_B.K_2[0] + modell_B.x_dot_f;
    modell_B.Sum3_g[1] = modell_B.K_2[1] + modell_B.y_dot_m;
    modell_B.Sum3_g[2] = modell_B.K_2[2] + modell_B.psi_dot_g;
    for (i = 0; i < 6; i++) {
      /* Sum: '<S7>/Sum5' */
      modell_B.Sum5[i] = modell_B.K_1[i] + modell_B.A_w[i];

      /* Gain: '<S8>/A_w' */
      modell_B.A_w_l[i] = 0.0;
      for (tmp_3 = 0; tmp_3 < 6; tmp_3++) {
        modell_B.A_w_l[i] = modell_P.A_w_Gain_p[6 * tmp_3 + i] *
          modell_B.wavehat[tmp_3] + modell_B.A_w_l[i];
      }
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S8>/D' */
      modell_B.D_n[i] = 0.0;
      modell_B.D_n[i] = modell_P.D_Gain_e[i] * modell_B.nu_hat[0] +
        modell_B.D_n[i];
      modell_B.D_n[i] = modell_P.D_Gain_e[i + 3] * modell_B.nu_hat[1] +
        modell_B.D_n[i];
      modell_B.D_n[i] = modell_P.D_Gain_e[i + 6] * modell_B.nu_hat[2] +
        modell_B.D_n[i];

      /* Sum: '<S8>/Sum' */
      modell_B.Sum_h[i] = modell_B.Integrator1[i] + modell_B.Sum6[i];
    }

    /* Gain: '<S8>/K_1' */
    for (i = 0; i < 6; i++) {
      modell_B.K_1_d[i] = 0.0;
      modell_B.K_1_d[i] = modell_P.K_1_Gain_k[i] * modell_B.Sum_h[0] +
        modell_B.K_1_d[i];
      modell_B.K_1_d[i] = modell_P.K_1_Gain_k[i + 6] * modell_B.Sum_h[1] +
        modell_B.K_1_d[i];
      modell_B.K_1_d[i] = modell_P.K_1_Gain_k[i + 12] * modell_B.Sum_h[2] +
        modell_B.K_1_d[i];
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S8>/K_2' */
      modell_B.K_2_n[i] = 0.0;
      modell_B.K_2_n[i] = modell_P.K_2_Gain_m[i] * modell_B.Sum_h[0] +
        modell_B.K_2_n[i];
      modell_B.K_2_n[i] = modell_P.K_2_Gain_m[i + 3] * modell_B.Sum_h[1] +
        modell_B.K_2_n[i];
      modell_B.K_2_n[i] = modell_P.K_2_Gain_m[i + 6] * modell_B.Sum_h[2] +
        modell_B.K_2_n[i];

      /* Gain: '<S8>/K_3' */
      modell_B.K_3_j[i] = 0.0;
      modell_B.K_3_j[i] = modell_P.K_3_Gain_f[i] * modell_B.Sum_h[0] +
        modell_B.K_3_j[i];
      modell_B.K_3_j[i] = modell_P.K_3_Gain_f[i + 3] * modell_B.Sum_h[1] +
        modell_B.K_3_j[i];
      modell_B.K_3_j[i] = modell_P.K_3_Gain_f[i + 6] * modell_B.Sum_h[2] +
        modell_B.K_3_j[i];

      /* Gain: '<S8>/K_4' */
      modell_B.K_4_j[i] = 0.0;
      modell_B.K_4_j[i] = modell_P.K_4_Gain_m[i] * modell_B.Sum_h[0] +
        modell_B.K_4_j[i];
      modell_B.K_4_j[i] = modell_P.K_4_Gain_m[i + 3] * modell_B.Sum_h[1] +
        modell_B.K_4_j[i];
      modell_B.K_4_j[i] = modell_P.K_4_Gain_m[i + 6] * modell_B.Sum_h[2] +
        modell_B.K_4_j[i];

      /* Integrator: '<S8>/bias_hat_integrator' */
      modell_B.bias_hat_integrator_a[i] =
        modell_X.bias_hat_integrator_CSTATE_l[i];
    }

    /* Fcn: '<S30>/Row1' */
    modell_B.Row1_m = cos(modell_B.Integrator1[2]) *
      modell_B.bias_hat_integrator_a[0] + sin(modell_B.Integrator1[2]) *
      modell_B.bias_hat_integrator_a[1];

    /* Fcn: '<S30>/Row2' */
    modell_B.Row2_c = (-sin(modell_B.Integrator1[2])) *
      modell_B.bias_hat_integrator_a[0] + cos(modell_B.Integrator1[2]) *
      modell_B.bias_hat_integrator_a[1];

    /* Fcn: '<S30>/Row3' */
    modell_B.Row3_i = modell_B.bias_hat_integrator_a[2];

    /* Fcn: '<S29>/Row1' */
    modell_B.Row1_a = cos(modell_B.Integrator1[2]) * modell_B.K_4_j[0] + sin
      (modell_B.Integrator1[2]) * modell_B.K_4_j[1];

    /* Fcn: '<S29>/Row2' */
    modell_B.Row2_g = (-sin(modell_B.Integrator1[2])) * modell_B.K_4_j[0] + cos
      (modell_B.Integrator1[2]) * modell_B.K_4_j[1];

    /* Fcn: '<S29>/Row3' */
    modell_B.Row3_n = modell_B.K_4_j[2];

    /* Sum: '<S8>/Sum1' */
    modell_B.Sum1_g[0] = modell_B.Row1_a + modell_B.Sum_pv[0];
    modell_B.Sum1_g[1] = modell_B.Row2_g + modell_B.Sum_pv[1];
    modell_B.Sum1_g[2] = modell_B.Row3_n + modell_B.Sum_pv[2];

    /* Sum: '<S8>/Sum4' */
    modell_B.Sum4_l[0] = (modell_B.Row1_m + modell_B.Sum1_g[0]) - modell_B.D_n[0];
    modell_B.Sum4_l[1] = (modell_B.Row2_c + modell_B.Sum1_g[1]) - modell_B.D_n[1];
    modell_B.Sum4_l[2] = (modell_B.Row3_i + modell_B.Sum1_g[2]) - modell_B.D_n[2];

    /* Fcn: '<S31>/Fcn' */
    modell_B.x_dot_l = cos(modell_B.Integrator1[2]) * modell_B.nu_hat[0] - sin
      (modell_B.Integrator1[2]) * modell_B.nu_hat[1];

    /* Fcn: '<S31>/Fcn1' */
    modell_B.y_dot_i = sin(modell_B.Integrator1[2]) * modell_B.nu_hat[0] + cos
      (modell_B.Integrator1[2]) * modell_B.nu_hat[1];

    /* Fcn: '<S31>/Fcn2' */
    modell_B.psi_dot_j = modell_B.nu_hat[2];
    for (i = 0; i < 3; i++) {
      /* Gain: '<S8>/M_inv' */
      modell_B.M_inv_d[i] = 0.0;
      modell_B.M_inv_d[i] = modell_P.M_inv_Gain_h[i] * modell_B.Sum4_l[0] +
        modell_B.M_inv_d[i];
      modell_B.M_inv_d[i] = modell_P.M_inv_Gain_h[i + 3] * modell_B.Sum4_l[1] +
        modell_B.M_inv_d[i];
      modell_B.M_inv_d[i] = modell_P.M_inv_Gain_h[i + 6] * modell_B.Sum4_l[2] +
        modell_B.M_inv_d[i];

      /* Gain: '<S8>/T_inv' */
      modell_B.T_inv_i[i] = 0.0;
      modell_B.T_inv_i[i] = modell_P.T_inv_Gain_d[i] *
        modell_B.bias_hat_integrator_a[0] + modell_B.T_inv_i[i];
      modell_B.T_inv_i[i] = modell_P.T_inv_Gain_d[i + 3] *
        modell_B.bias_hat_integrator_a[1] + modell_B.T_inv_i[i];
      modell_B.T_inv_i[i] = modell_P.T_inv_Gain_d[i + 6] *
        modell_B.bias_hat_integrator_a[2] + modell_B.T_inv_i[i];

      /* Sum: '<S8>/Sum2' */
      modell_B.Sum2_k[i] = modell_B.K_3_j[i] - modell_B.T_inv_i[i];
    }

    /* Sum: '<S8>/Sum3' */
    modell_B.Sum3_i[0] = modell_B.K_2_n[0] + modell_B.x_dot_l;
    modell_B.Sum3_i[1] = modell_B.K_2_n[1] + modell_B.y_dot_i;
    modell_B.Sum3_i[2] = modell_B.K_2_n[2] + modell_B.psi_dot_j;

    /* Sum: '<S8>/Sum5' */
    for (i = 0; i < 6; i++) {
      modell_B.Sum5_a[i] = modell_B.K_1_d[i] + modell_B.A_w_l[i];
    }

    if (rtmIsMajorTimeStep(modell_M)) {
    }

    /* Sum: '<S12>/Sum' */
    modell_B.Sum_d0[0] = modell_B.nu_surge_hil - modell_B.Integrator2[0];
    modell_B.Sum_d0[1] = modell_B.nu_sway_hil - modell_B.Integrator2[1];
    modell_B.Sum_d0[2] = modell_B.nu_yaw_hil - modell_B.Integrator2[2];
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Math: '<S45>/mf1' */
      tmp = modell_B.pos_diff[0];
      modell_B.mf1_js = tmp * tmp;

      /* Math: '<S45>/mf2' */
      tmp = modell_B.pos_diff[1];
      modell_B.mf2_d = tmp * tmp;

      /* Sum: '<S45>/Sum' */
      modell_B.Sum_pn = modell_B.mf1_js + modell_B.mf2_d;

      /* Math: '<S45>/mf3' */
      tmp = modell_B.Sum_pn;
      if (tmp < 0.0) {
        modell_B.mf3_l = -sqrt(-tmp);
      } else {
        modell_B.mf3_l = sqrt(tmp);
      }

      /* RandomNumber: '<S51>/White Noise' */
      modell_B.WhiteNoise = modell_DWork.NextOutput;

      /* Gain: '<S51>/Output' */
      modell_B.Output[0] = modell_P.Output_Gain[0] * modell_B.WhiteNoise;
      modell_B.Output[1] = modell_P.Output_Gain[1] * modell_B.WhiteNoise;
      modell_B.Output[2] = modell_P.Output_Gain[2] * modell_B.WhiteNoise;
      for (i = 0; i < 3; i++) {
        /* Gain: '<S13>/E_b_i' */
        modell_B.E_b_i[i] = 0.0;
        modell_B.E_b_i[i] = modell_P.E_b_i_Gain[i] * modell_B.Output[0] +
          modell_B.E_b_i[i];
        modell_B.E_b_i[i] = modell_P.E_b_i_Gain[i + 3] * modell_B.Output[1] +
          modell_B.E_b_i[i];
        modell_B.E_b_i[i] = modell_P.E_b_i_Gain[i + 6] * modell_B.Output[2] +
          modell_B.E_b_i[i];

        /* Gain: '<S13>/E_b_s' */
        modell_B.E_b_s[i] = 0.0;
        modell_B.E_b_s[i] = modell_P.E_b_s_Gain[i] * modell_B.Output[0] +
          modell_B.E_b_s[i];
        modell_B.E_b_s[i] = modell_P.E_b_s_Gain[i + 3] * modell_B.Output[1] +
          modell_B.E_b_s[i];
        modell_B.E_b_s[i] = modell_P.E_b_s_Gain[i + 6] * modell_B.Output[2] +
          modell_B.E_b_s[i];
      }
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S13>/T_s_inv' */
      modell_B.T_s_inv[i] = 0.0;
      modell_B.T_s_inv[i] = modell_P.T_s_inv_Gain[i] * modell_B.Integrator_n[0]
        + modell_B.T_s_inv[i];
      modell_B.T_s_inv[i] = modell_P.T_s_inv_Gain[i + 3] *
        modell_B.Integrator_n[1] + modell_B.T_s_inv[i];
      modell_B.T_s_inv[i] = modell_P.T_s_inv_Gain[i + 6] *
        modell_B.Integrator_n[2] + modell_B.T_s_inv[i];

      /* Sum: '<S13>/Sum' */
      modell_B.Sum_iz[i] = modell_B.T_s_inv[i] + modell_B.E_b_s[i];

      /* Gain: '<S13>/T_i_inv' */
      modell_B.T_i_inv[i] = 0.0;
      modell_B.T_i_inv[i] = modell_P.T_i_inv_Gain[i] * modell_B.Integrator1_n[0]
        + modell_B.T_i_inv[i];
      modell_B.T_i_inv[i] = modell_P.T_i_inv_Gain[i + 3] *
        modell_B.Integrator1_n[1] + modell_B.T_i_inv[i];
      modell_B.T_i_inv[i] = modell_P.T_i_inv_Gain[i + 6] *
        modell_B.Integrator1_n[2] + modell_B.T_i_inv[i];

      /* Sum: '<S13>/Sum1' */
      modell_B.Sum1_i[i] = modell_B.E_b_i[i] + modell_B.T_i_inv[i];
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
    real_T tmpstdDev;
    real_T tmpmean;
    if (rtmIsMajorTimeStep(modell_M)) {
      /* Update for UnitDelay: '<S21>/Delay Input2' */
      modell_DWork.DelayInput2_DSTATE = modell_B.DifferenceInputs2;

      /* Update for RandomNumber: '<S51>/White Noise' */
      tmpstdDev = modell_P.WhiteNoise_StdDev;
      tmpmean = modell_P.WhiteNoise_Mean;
      tmpstdDev *= rt_NormalRand(&modell_DWork.RandSeed);
      modell_DWork.NextOutput = tmpstdDev + tmpmean;
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
      = modell_B.Sum3_g[0];

    /* Derivatives for Integrator: '<S7>/nu_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->nu_hat_CSTATE_g[0]
      = modell_B.M_inv[0];

    /* Derivatives for Integrator: '<S7>/eta_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->eta_hat_CSTATE_b[1]
      = modell_B.Sum3_g[1];

    /* Derivatives for Integrator: '<S7>/nu_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->nu_hat_CSTATE_g[1]
      = modell_B.M_inv[1];

    /* Derivatives for Integrator: '<S7>/eta_hat' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)->eta_hat_CSTATE_b[2]
      = modell_B.Sum3_g[2];

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
      ->Integrator1_CSTATE_p[0] = modell_B.Sum1_i[0];

    /* Derivatives for Integrator: '<S7>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE[0] = modell_B.Sum2_b[0];

    /* Derivatives for Integrator: '<S8>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE_l[0] = modell_B.Sum2_k[0];

    /* Derivatives for Integrator: '<S13>/Integrator1' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->Integrator1_CSTATE_p[1] = modell_B.Sum1_i[1];

    /* Derivatives for Integrator: '<S7>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE[1] = modell_B.Sum2_b[1];

    /* Derivatives for Integrator: '<S8>/bias_hat_integrator' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->bias_hat_integrator_CSTATE_l[1] = modell_B.Sum2_k[1];

    /* Derivatives for Integrator: '<S13>/Integrator1' */
    ((StateDerivatives_modell *) modell_M->ModelData.derivs)
      ->Integrator1_CSTATE_p[2] = modell_B.Sum1_i[2];

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
  modell_M->Sizes.numBlocks = (324);   /* Number of blocks */
  modell_M->Sizes.numBlockIO = (231);  /* Number of block outputs */
  modell_M->Sizes.numBlockPrms = (614);/* Sum of parameter "widths" */
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
    uint32_T n;
    real_T tmpstdDev;
    real_T tmpmean;

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
    modell_DWork.DPcontroller_MODE = SUBSYS_DISABLED;

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
    tmpstdDev = modell_P.WhiteNoise_Seed;
    if (rtIsNaN(tmpstdDev) || rtIsInf(tmpstdDev)) {
      tmpstdDev = 0.0;
    } else {
      tmpstdDev = fmod(floor(tmpstdDev), 4.294967296E+009);
    }

    tseed = tmpstdDev < 0.0 ? -((uint32_T)(-tmpstdDev)) : (uint32_T)tmpstdDev;
    r = (int32_T)(tseed >> 16U);
    t = tseed & 32768U;
    n = (uint32_T)r << 16;
    n -= t;
    n = tseed - n;
    n <<= 16U;
    n += t;
    n += (uint32_T)r;
    modell_DWork.RandSeed = n;
    if (modell_DWork.RandSeed < 1U) {
      modell_DWork.RandSeed = 1144108930U;
    }

    if (modell_DWork.RandSeed > 2147483646U) {
      modell_DWork.RandSeed = 2147483646U;
    }

    tmpstdDev = modell_P.WhiteNoise_StdDev;
    tmpmean = modell_P.WhiteNoise_Mean;
    tmpstdDev *= rt_NormalRand(&modell_DWork.RandSeed);
    modell_DWork.NextOutput = tmpstdDev + tmpmean;
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

/*
   This file contains automatically generated code for functions
   to update the inports and outports of a Simulink/Realtime Workshop
   model. Calls to these functions should be made before each step is taken
   (inports, call SetExternalInputs) and after each step is taken
   (outports, call SetExternalOutputs.)
 */
#ifdef NI_ROOTMODEL_modell
#include "model_info.h"
#include "SIT_API.h"
#include <stddef.h>
#include <stdlib.h>
#include <float.h>

double NIRT_GetValueByDataType(void* ptr,int subindex, int type, int Complex)
{
  switch (type)
  {
   case 0:
    return (double)(((real_T *)ptr)[subindex]);

   case 1:
    return (double)(((real32_T *)ptr)[subindex]);

   case 2:
    return (double)(((int8_T *)ptr)[subindex]);

   case 3:
    return (double)(((uint8_T *)ptr)[subindex]);

   case 4:
    return (double)(((int16_T *)ptr)[subindex]);

   case 5:
    return (double)(((uint16_T *)ptr)[subindex]);

   case 6:
    return (double)(((int32_T *)ptr)[subindex]);

   case 7:
    return (double)(((uint32_T *)ptr)[subindex]);

   case 8:
    return (double)(((boolean_T *)ptr)[subindex]);

   case 10:
    //Type is renamed. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 13:
    //Type is array. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,7,Complex);

   case 16:
    //Type is renamed. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 17:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 18:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 19:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 20:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 21:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 22:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 23:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 24:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 25:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 26:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 27:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 28:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 29:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 30:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 31:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 32:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 33:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 34:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 35:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 45:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 46:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 47:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 48:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 49:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 50:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 51:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 52:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 53:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);
  }

  // return ((double *)ptr)[subindex];
  return rtNaN;
}

long NIRT_SetValueByDataType(void* ptr,int subindex, double value, int type, int
  Complex)
{
  //Complex is only used for R14.3 and down
  switch (type)
  {
   case 0:
    ((real_T *)ptr)[subindex] = (real_T)value;
    return NI_OK;

   case 1:
    ((real32_T *)ptr)[subindex] = (real32_T)value;
    return NI_OK;

   case 2:
    ((int8_T *)ptr)[subindex] = (int8_T)value;
    return NI_OK;

   case 3:
    ((uint8_T *)ptr)[subindex] = (uint8_T)value;
    return NI_OK;

   case 4:
    ((int16_T *)ptr)[subindex] = (int16_T)value;
    return NI_OK;

   case 5:
    ((uint16_T *)ptr)[subindex] = (uint16_T)value;
    return NI_OK;

   case 6:
    ((int32_T *)ptr)[subindex] = (int32_T)value;
    return NI_OK;

   case 7:
    ((uint32_T *)ptr)[subindex] = (uint32_T)value;
    return NI_OK;

   case 8:
    ((boolean_T *)ptr)[subindex] = (boolean_T)value;
    return NI_OK;

   case 10:
    //Type is renamed. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 13:
    //Type is array. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,7,Complex);

   case 16:
    //Type is renamed. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 17:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 18:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 19:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 20:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 21:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 22:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 23:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 24:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 25:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 26:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 27:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 28:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 29:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 30:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 31:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 32:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 33:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 34:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 35:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 45:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 46:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 47:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 48:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 49:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 50:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 51:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 52:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 53:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern modell_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 0;
}

void SetExternalOutputs(double* data, int* TaskSampleHit)
{
}

long NumOutputPorts(void)
{
  return 0;
}

int NI_InitExternalOutputs()
{
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "modell/HIL model/reset_eta_hil/Value", offsetof(Parameters_modell,
    reset_eta_hil_Value), 45, 1, 2, 0, "", 0 },

  { 1, "modell/Constant/Value", offsetof(Parameters_modell, Constant_Value), 45,
    1, 2, 2, "", 0 },

  { 2, "modell/HIL model/initial_nu_hil/Value", offsetof(Parameters_modell,
    initial_nu_hil_Value), 46, 3, 2, 4, "", 0 },

  { 3, "modell/HIL model/nu_surge_hil/Gain", offsetof(Parameters_modell,
    nu_surge_hil_Gain), 45, 1, 2, 6, "", 0 },

  { 4, "modell/HIL model/nu_sway_hil/Gain", offsetof(Parameters_modell,
    nu_sway_hil_Gain), 45, 1, 2, 8, "", 0 },

  { 5, "modell/HIL model/nu_yaw_hil/Gain", offsetof(Parameters_modell,
    nu_yaw_hil_Gain), 45, 1, 2, 10, "", 0 },

  { 6, "modell/LabView Out/Transfer Fcn/A", offsetof(Parameters_modell,
    TransferFcn_A), 45, 1, 2, 12, "", 0 },

  { 7, "modell/LabView Out/Transfer Fcn/C", offsetof(Parameters_modell,
    TransferFcn_C), 45, 1, 2, 14, "", 0 },

  { 8, "modell/LabView Out/Transfer Fcn1/A", offsetof(Parameters_modell,
    TransferFcn1_A), 45, 1, 2, 16, "", 0 },

  { 9, "modell/LabView Out/Transfer Fcn1/C", offsetof(Parameters_modell,
    TransferFcn1_C), 45, 1, 2, 18, "", 0 },

  { 10, "modell/LabView Out/Transfer Fcn2/A", offsetof(Parameters_modell,
    TransferFcn2_A), 45, 1, 2, 20, "", 0 },

  { 11, "modell/LabView Out/Transfer Fcn2/C", offsetof(Parameters_modell,
    TransferFcn2_C), 45, 1, 2, 22, "", 0 },

  { 12, "modell/Iceberg/initial position/Value", offsetof(Parameters_modell,
    initialposition_Value), 46, 3, 2, 24, "", 0 },

  { 13, "modell/Iceberg/Integrator2/InitialCondition", offsetof
    (Parameters_modell, Integrator2_IC), 45, 1, 2, 26, "", 0 },

  { 14, "modell/Towline/Towline dynamics/T_zero/Value", offsetof
    (Parameters_modell, T_zero_Value), 46, 3, 2, 28, "", 0 },

  { 15, "modell/Towline/Towline dynamics/Towline length/Value", offsetof
    (Parameters_modell, Towlinelength_Value), 45, 1, 2, 30, "", 0 },

  { 16, "modell/Towline/pos_diff/Value", offsetof(Parameters_modell,
    pos_diff_Value), 46, 3, 2, 32, "", 0 },

  { 17, "modell/Towline/Towline dynamics/K_tow/Value", offsetof
    (Parameters_modell, K_tow_Value), 27, 9, 2, 34, "", 0 },

  { 18, "modell/Towline/Towline dynamics/T_cr/Value", offsetof(Parameters_modell,
    T_cr_Value), 45, 1, 2, 36, "", 0 },

  { 19, "modell/Towline/IC/Value", offsetof(Parameters_modell, IC_Value), 46, 3,
    2, 38, "", 0 },

  { 20, "modell/bias/Integrator/InitialCondition", offsetof(Parameters_modell,
    Integrator_IC), 45, 1, 2, 40, "", 0 },

  { 21, "modell/bias/zero/Value", offsetof(Parameters_modell, zero_Value), 45, 1,
    2, 42, "", 0 },

  { 22, "modell/Observer (ship)/wave hat/InitialCondition", offsetof
    (Parameters_modell, wavehat_IC), 45, 1, 2, 44, "", 0 },

  { 23, "modell/Observer (ship)/C_w/Gain", offsetof(Parameters_modell, C_w_Gain),
    49, 18, 2, 46, "", 0 },

  { 24, "modell/Observer (ship)/eta_hat/InitialCondition", offsetof
    (Parameters_modell, eta_hat_IC), 45, 1, 2, 48, "", 0 },

  { 25, "modell/Observer (ship)/nu_hat/InitialCondition", offsetof
    (Parameters_modell, nu_hat_IC), 45, 1, 2, 50, "", 0 },

  { 26, "modell/Observer (iceberg)/wave hat/InitialCondition", offsetof
    (Parameters_modell, wavehat_IC_l), 45, 1, 2, 52, "", 0 },

  { 27, "modell/Observer (iceberg)/C_w/Gain", offsetof(Parameters_modell,
    C_w_Gain_d), 49, 18, 2, 54, "", 0 },

  { 28, "modell/Observer (iceberg)/eta_hat/InitialCondition", offsetof
    (Parameters_modell, eta_hat_IC_g), 45, 1, 2, 56, "", 0 },

  { 29, "modell/Observer (iceberg)/nu_hat/InitialCondition", offsetof
    (Parameters_modell, nu_hat_IC_c), 45, 1, 2, 58, "", 0 },

  { 30, "modell/MODE/Value", offsetof(Parameters_modell, MODE_Value), 45, 1, 2,
    60, "", 0 },

  { 31, "modell/ctc/Constant/Value", offsetof(Parameters_modell,
    Constant_Value_j), 45, 1, 2, 62, "", 0 },

  { 32, "modell/PS3 Sixaxis/threshold block1/Constant2/Value", offsetof
    (Parameters_modell, Constant2_Value), 45, 1, 2, 64, "", 0 },

  { 33, "modell/PS3 Sixaxis/PS3_L_JS_Y/Value", offsetof(Parameters_modell,
    PS3_L_JS_Y_Value), 45, 1, 2, 66, "", 0 },

  { 34, "modell/PS3 Sixaxis/limit_L_JS_Y/Value", offsetof(Parameters_modell,
    limit_L_JS_Y_Value), 45, 1, 2, 68, "", 0 },

  { 35, "modell/PS3 Sixaxis/Gain1/Gain", offsetof(Parameters_modell, Gain1_Gain),
    45, 1, 2, 70, "", 0 },

  { 36, "modell/PS3 Sixaxis/threshold block/Constant2/Value", offsetof
    (Parameters_modell, Constant2_Value_j), 45, 1, 2, 72, "", 0 },

  { 37, "modell/PS3 Sixaxis/PS3_L_JS_X/Value", offsetof(Parameters_modell,
    PS3_L_JS_X_Value), 45, 1, 2, 74, "", 0 },

  { 38, "modell/PS3 Sixaxis/limit_L_JS_X/Value", offsetof(Parameters_modell,
    limit_L_JS_X_Value), 45, 1, 2, 76, "", 0 },

  { 39, "modell/PS3 Sixaxis/Gain/Gain", offsetof(Parameters_modell, Gain_Gain),
    45, 1, 2, 78, "", 0 },

  { 40, "modell/PS3 Sixaxis/threshold block3/Constant2/Value", offsetof
    (Parameters_modell, Constant2_Value_f), 45, 1, 2, 80, "", 0 },

  { 41, "modell/PS3 Sixaxis/PS3_R_JS_Y/Value", offsetof(Parameters_modell,
    PS3_R_JS_Y_Value), 45, 1, 2, 82, "", 0 },

  { 42, "modell/PS3 Sixaxis/limit_R_JS_Y/Value", offsetof(Parameters_modell,
    limit_R_JS_Y_Value), 45, 1, 2, 84, "", 0 },

  { 43, "modell/PS3 Sixaxis/Gain3/Gain", offsetof(Parameters_modell, Gain3_Gain),
    45, 1, 2, 86, "", 0 },

  { 44, "modell/PS3 Sixaxis/threshold block2/Constant2/Value", offsetof
    (Parameters_modell, Constant2_Value_o), 45, 1, 2, 88, "", 0 },

  { 45, "modell/PS3 Sixaxis/PS3_R_JS_X/Value", offsetof(Parameters_modell,
    PS3_R_JS_X_Value), 45, 1, 2, 90, "", 0 },

  { 46, "modell/PS3 Sixaxis/limit_R_JS_X/Value", offsetof(Parameters_modell,
    limit_R_JS_X_Value), 45, 1, 2, 92, "", 0 },

  { 47, "modell/PS3 Sixaxis/Gain2/Gain", offsetof(Parameters_modell, Gain2_Gain),
    45, 1, 2, 94, "", 0 },

  { 48, "modell/PS3 Sixaxis/PS3_L2/Value", offsetof(Parameters_modell,
    PS3_L2_Value), 45, 1, 2, 96, "", 0 },

  { 49, "modell/PS3 Sixaxis/Constant/Value", offsetof(Parameters_modell,
    Constant_Value_o), 45, 1, 2, 98, "", 0 },

  { 50, "modell/PS3 Sixaxis/g1/Gain", offsetof(Parameters_modell, g1_Gain), 45,
    1, 2, 100, "", 0 },

  { 51, "modell/PS3 Sixaxis/PS3_R2/Value", offsetof(Parameters_modell,
    PS3_R2_Value), 45, 1, 2, 102, "", 0 },

  { 52, "modell/PS3 Sixaxis/Constant1/Value", offsetof(Parameters_modell,
    Constant1_Value), 45, 1, 2, 104, "", 0 },

  { 53, "modell/PS3 Sixaxis/g2/Gain", offsetof(Parameters_modell, g2_Gain), 45,
    1, 2, 106, "", 0 },

  { 54, "modell/LabView Out/BT_saturation/Value", offsetof(Parameters_modell,
    BT_saturation_Value), 45, 1, 2, 108, "", 0 },

  { 55, "modell/LabView Out/VSP_speeds/Value", offsetof(Parameters_modell,
    VSP_speeds_Value), 45, 1, 2, 110, "", 0 },

  { 56, "modell/Joystick Control/Ke^-1/Value", offsetof(Parameters_modell,
    Ke1_Value), 22, 25, 2, 112, "", 0 },

  { 57, "modell/Joystick Control/Te^+/Value", offsetof(Parameters_modell,
    Te_Value), 25, 15, 2, 114, "", 0 },

  { 58, "modell/Joystick Control/joystick_gain_surge/Gain", offsetof
    (Parameters_modell, joystick_gain_surge_Gain), 45, 1, 2, 116, "", 0 },

  { 59, "modell/Joystick Control/joystick_gain_sway/Gain", offsetof
    (Parameters_modell, joystick_gain_sway_Gain), 45, 1, 2, 118, "", 0 },

  { 60, "modell/Joystick Control/joystick_gain_yaw/Gain", offsetof
    (Parameters_modell, joystick_gain_yaw_Gain), 45, 1, 2, 120, "", 0 },

  { 61, "modell/Joystick Control/Saturation/UpperLimit", offsetof
    (Parameters_modell, Saturation_UpperSat), 45, 1, 2, 122, "", 0 },

  { 62, "modell/Joystick Control/Saturation/LowerLimit", offsetof
    (Parameters_modell, Saturation_LowerSat), 45, 1, 2, 124, "", 0 },

  { 63, "modell/Joystick Control/VSP_speeds/Value", offsetof(Parameters_modell,
    VSP_speeds_Value_n), 45, 1, 2, 126, "", 0 },

  { 64, "modell/Joystick Control/BT_power_limit/Value", offsetof
    (Parameters_modell, BT_power_limit_Value), 45, 1, 2, 128, "", 0 },

  { 65, "modell/Thruster Control/Ke^-1/Value", offsetof(Parameters_modell,
    Ke1_Value_c), 22, 25, 2, 130, "", 0 },

  { 66, "modell/Thruster Control/Te^+/Value", offsetof(Parameters_modell,
    Te_Value_h), 25, 15, 2, 132, "", 0 },

  { 67, "modell/Thruster Control/VSP_speeds/Value", offsetof(Parameters_modell,
    VSP_speeds_Value_k), 45, 1, 2, 134, "", 0 },

  { 68, "modell/Thruster Control/BT_power_limit/Value", offsetof
    (Parameters_modell, BT_power_limit_Value_f), 45, 1, 2, 136, "", 0 },

  { 69, "modell/HIL model/BT_power/Gain", offsetof(Parameters_modell,
    BT_power_Gain), 45, 1, 2, 138, "", 0 },

  { 70, "modell/HIL model/Constant/Value", offsetof(Parameters_modell,
    Constant_Value_e), 21, 15, 2, 140, "", 0 },

  { 71, "modell/HIL model/Constant1/Value", offsetof(Parameters_modell,
    Constant1_Value_o), 22, 25, 2, 142, "", 0 },

  { 72, "modell/HIL model/D/Gain", offsetof(Parameters_modell, D_Gain), 27, 9, 2,
    144, "", 0 },

  { 73, "modell/HIL model/u1_hil/Gain", offsetof(Parameters_modell, u1_hil_Gain),
    45, 1, 2, 146, "", 0 },

  { 74, "modell/HIL model/u2_hil/Gain", offsetof(Parameters_modell, u2_hil_Gain),
    45, 1, 2, 148, "", 0 },

  { 75, "modell/HIL model/u3_hil/Gain", offsetof(Parameters_modell, u3_hil_Gain),
    45, 1, 2, 150, "", 0 },

  { 76, "modell/HIL model/u4_hil/Gain", offsetof(Parameters_modell, u4_hil_Gain),
    45, 1, 2, 152, "", 0 },

  { 77, "modell/HIL model/Rate Limiter Dynamic/sample time/WtEt", offsetof
    (Parameters_modell, sampletime_WtEt), 0, 1, 2, 154, "", 0 },

  { 78, "modell/HIL model/Rate Limiter Dynamic/Delay Input2/X0", offsetof
    (Parameters_modell, DelayInput2_X0), 45, 1, 2, 156, "", 0 },

  { 79, "modell/HIL model/neg/Gain", offsetof(Parameters_modell, neg_Gain), 45,
    1, 2, 158, "", 0 },

  { 80, "modell/HIL model/u5_hil/Gain", offsetof(Parameters_modell, u5_hil_Gain),
    45, 1, 2, 160, "", 0 },

  { 81, "modell/HIL model/tau_surge_hil/Gain", offsetof(Parameters_modell,
    tau_surge_hil_Gain), 45, 1, 2, 162, "", 0 },

  { 82, "modell/HIL model/tau_sway_hil/Gain", offsetof(Parameters_modell,
    tau_sway_hil_Gain), 45, 1, 2, 164, "", 0 },

  { 83, "modell/HIL model/tau_yaw_hil/Gain", offsetof(Parameters_modell,
    tau_yaw_hil_Gain), 45, 1, 2, 166, "", 0 },

  { 84, "modell/HIL model/VIS_HIL_E/Gain", offsetof(Parameters_modell,
    VIS_HIL_E_Gain), 45, 1, 2, 168, "", 0 },

  { 85, "modell/HIL model/VIS_HIL_N/Gain", offsetof(Parameters_modell,
    VIS_HIL_N_Gain), 45, 1, 2, 170, "", 0 },

  { 86, "modell/HIL model/VIS_HIL_PIS/Gain", offsetof(Parameters_modell,
    VIS_HIL_PIS_Gain), 45, 1, 2, 172, "", 0 },

  { 87, "modell/HIL model/VSP_angle_deg_port/Gain", offsetof(Parameters_modell,
    VSP_angle_deg_port_Gain), 45, 1, 2, 174, "", 0 },

  { 88, "modell/HIL model/VSP_angle_deg_stbd/Gain", offsetof(Parameters_modell,
    VSP_angle_deg_stbd_Gain), 45, 1, 2, 176, "", 0 },

  { 89, "modell/HIL model/inv(M)/Gain", offsetof(Parameters_modell, invM_Gain),
    27, 9, 2, 178, "", 0 },

  { 90, "modell/Iceberg/D/Gain", offsetof(Parameters_modell, D_Gain_d), 27, 9, 2,
    180, "", 0 },

  { 91, "modell/Iceberg/saturation/Saturation/UpperLimit", offsetof
    (Parameters_modell, Saturation_UpperSat_n), 45, 1, 2, 182, "", 0 },

  { 92, "modell/Iceberg/saturation/Saturation/LowerLimit", offsetof
    (Parameters_modell, Saturation_LowerSat_j), 45, 1, 2, 184, "", 0 },

  { 93, "modell/Iceberg/saturation/Saturation1/UpperLimit", offsetof
    (Parameters_modell, Saturation1_UpperSat), 45, 1, 2, 186, "", 0 },

  { 94, "modell/Iceberg/saturation/Saturation1/LowerLimit", offsetof
    (Parameters_modell, Saturation1_LowerSat), 45, 1, 2, 188, "", 0 },

  { 95, "modell/Iceberg/saturation/Saturation2/UpperLimit", offsetof
    (Parameters_modell, Saturation2_UpperSat), 45, 1, 2, 190, "", 0 },

  { 96, "modell/Iceberg/saturation/Saturation2/LowerLimit", offsetof
    (Parameters_modell, Saturation2_LowerSat), 45, 1, 2, 192, "", 0 },

  { 97, "modell/bias/Integrator1/InitialCondition", offsetof(Parameters_modell,
    Integrator1_IC), 45, 1, 2, 194, "", 0 },

  { 98, "modell/Iceberg/inv(M)/Gain", offsetof(Parameters_modell, invM_Gain_d),
    27, 9, 2, 196, "", 0 },

  { 99, "modell/LabView Out/eta_d_E/Value", offsetof(Parameters_modell,
    eta_d_E_Value), 45, 1, 2, 198, "", 0 },

  { 100, "modell/LabView Out/eta_d_N/Value", offsetof(Parameters_modell,
    eta_d_N_Value), 45, 1, 2, 200, "", 0 },

  { 101, "modell/LabView Out/eta_d_Psi/Value", offsetof(Parameters_modell,
    eta_d_Psi_Value), 45, 1, 2, 202, "", 0 },

  { 102, "modell/Observer (iceberg)/A_w/Gain", offsetof(Parameters_modell,
    A_w_Gain), 50, 36, 2, 204, "", 0 },

  { 103, "modell/Observer (iceberg)/D/Gain", offsetof(Parameters_modell,
    D_Gain_h), 27, 9, 2, 206, "", 0 },

  { 104, "modell/Observer (iceberg)/K_1/Gain", offsetof(Parameters_modell,
    K_1_Gain), 51, 18, 2, 208, "", 0 },

  { 105, "modell/Observer (iceberg)/K_2/Gain", offsetof(Parameters_modell,
    K_2_Gain), 27, 9, 2, 210, "", 0 },

  { 106, "modell/Observer (iceberg)/K_3/Gain", offsetof(Parameters_modell,
    K_3_Gain), 27, 9, 2, 212, "", 0 },

  { 107, "modell/Observer (iceberg)/K_4/Gain", offsetof(Parameters_modell,
    K_4_Gain), 27, 9, 2, 214, "", 0 },

  { 108, "modell/Observer (iceberg)/bias_hat_integrator/InitialCondition",
    offsetof(Parameters_modell, bias_hat_integrator_IC), 45, 1, 2, 216, "", 0 },

  { 109, "modell/Observer (iceberg)/M_inv/Gain", offsetof(Parameters_modell,
    M_inv_Gain), 27, 9, 2, 218, "", 0 },

  { 110, "modell/Observer (iceberg)/T_inv/Gain", offsetof(Parameters_modell,
    T_inv_Gain), 27, 9, 2, 220, "", 0 },

  { 111, "modell/Observer (ship)/A_w/Gain", offsetof(Parameters_modell,
    A_w_Gain_p), 50, 36, 2, 222, "", 0 },

  { 112, "modell/Observer (ship)/D/Gain", offsetof(Parameters_modell, D_Gain_e),
    27, 9, 2, 224, "", 0 },

  { 113, "modell/Observer (ship)/K_1/Gain", offsetof(Parameters_modell,
    K_1_Gain_k), 51, 18, 2, 226, "", 0 },

  { 114, "modell/Observer (ship)/K_2/Gain", offsetof(Parameters_modell,
    K_2_Gain_m), 27, 9, 2, 228, "", 0 },

  { 115, "modell/Observer (ship)/K_3/Gain", offsetof(Parameters_modell,
    K_3_Gain_f), 27, 9, 2, 230, "", 0 },

  { 116, "modell/Observer (ship)/K_4/Gain", offsetof(Parameters_modell,
    K_4_Gain_m), 27, 9, 2, 232, "", 0 },

  { 117, "modell/Observer (ship)/bias_hat_integrator/InitialCondition", offsetof
    (Parameters_modell, bias_hat_integrator_IC_f), 45, 1, 2, 234, "", 0 },

  { 118, "modell/Observer (ship)/M_inv/Gain", offsetof(Parameters_modell,
    M_inv_Gain_h), 27, 9, 2, 236, "", 0 },

  { 119, "modell/Observer (ship)/T_inv/Gain", offsetof(Parameters_modell,
    T_inv_Gain_d), 27, 9, 2, 238, "", 0 },

  { 120, "modell/bias/Band-Limited White Noise/White Noise/Mean", offsetof
    (Parameters_modell, WhiteNoise_Mean), 45, 1, 2, 240, "", 0 },

  { 121, "modell/bias/Band-Limited White Noise/White Noise/StdDev", offsetof
    (Parameters_modell, WhiteNoise_StdDev), 45, 1, 2, 242, "", 0 },

  { 122, "modell/bias/Band-Limited White Noise/White Noise/Seed", offsetof
    (Parameters_modell, WhiteNoise_Seed), 45, 1, 2, 244, "", 0 },

  { 123, "modell/bias/Band-Limited White Noise/Output/Gain", offsetof
    (Parameters_modell, Output_Gain), 52, 3, 2, 246, "", 0 },

  { 124, "modell/bias/E_b_i/Gain", offsetof(Parameters_modell, E_b_i_Gain), 27,
    9, 2, 248, "", 0 },

  { 125, "modell/bias/E_b_s/Gain", offsetof(Parameters_modell, E_b_s_Gain), 27,
    9, 2, 250, "", 0 },

  { 126, "modell/bias/T_s_inv/Gain", offsetof(Parameters_modell, T_s_inv_Gain),
    27, 9, 2, 252, "", 0 },

  { 127, "modell/bias/T_i_inv/Gain", offsetof(Parameters_modell, T_i_inv_Gain),
    27, 9, 2, 254, "", 0 },

  { 128, "modell/Thruster Control/Saturation/UpperLimit", offsetof
    (Parameters_modell, Saturation_UpperSat_c), 45, 1, 2, 256, "", 0 },

  { 129, "modell/Thruster Control/Saturation/LowerLimit", offsetof
    (Parameters_modell, Saturation_LowerSat_e), 45, 1, 2, 258, "", 0 },

  { 130, "modell/Manual Thruster Control/U1/Gain", offsetof(Parameters_modell,
    U1_Gain), 45, 1, 2, 260, "", 0 },

  { 131, "modell/Manual Thruster Control/U2/Gain", offsetof(Parameters_modell,
    U2_Gain), 45, 1, 2, 262, "", 0 },

  { 132, "modell/Manual Thruster Control/U3/Gain", offsetof(Parameters_modell,
    U3_Gain), 45, 1, 2, 264, "", 0 },

  { 133, "modell/Manual Thruster Control/U4/Gain", offsetof(Parameters_modell,
    U4_Gain), 45, 1, 2, 266, "", 0 },

  { 134, "modell/Manual Thruster Control/U5/Gain", offsetof(Parameters_modell,
    U5_Gain), 45, 1, 2, 268, "", 0 },

  { 135, "modell/DP controller/DP controller/Integrator/InitialCondition",
    offsetof(Parameters_modell, Integrator_IC_l), 45, 1, 2, 270, "", 0 },

  { 136, "modell/DP controller/DP controller/Kd/Gain", offsetof
    (Parameters_modell, Kd_Gain), 27, 9, 2, 272, "", 0 },

  { 137, "modell/DP controller/DP controller/Kd_scale/Value", offsetof
    (Parameters_modell, Kd_scale_Value), 45, 1, 2, 274, "", 0 },

  { 138, "modell/DP controller/DP controller/Ki/Gain", offsetof
    (Parameters_modell, Ki_Gain), 27, 9, 2, 276, "", 0 },

  { 139, "modell/DP controller/DP controller/Ki_scale/Value", offsetof
    (Parameters_modell, Ki_scale_Value), 45, 1, 2, 278, "", 0 },

  { 140,
    "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_modell, Saturation_UpperSat_i), 45, 1, 2, 280, "", 0 },

  { 141,
    "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_modell, Saturation_LowerSat_b), 45, 1, 2, 282, "", 0 },

  { 142, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_modell, Gain_Gain_i), 45, 1, 2, 284, "", 0 },

  { 143,
    "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_modell, Constant_Value_jb), 45, 1, 2, 286, "", 0 },

  { 144, "modell/DP controller/DP controller/Reg_e_N_hil/Gain", offsetof
    (Parameters_modell, Reg_e_N_hil_Gain), 45, 1, 2, 288, "", 0 },

  { 145, "modell/DP controller/DP controller/Reg_e_E_hil/Gain", offsetof
    (Parameters_modell, Reg_e_E_hil_Gain), 45, 1, 2, 290, "", 0 },

  { 146, "modell/DP controller/DP controller/Reg_e_Psi_hil/Gain", offsetof
    (Parameters_modell, Reg_e_Psi_hil_Gain), 45, 1, 2, 292, "", 0 },

  { 147,
    "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_modell, Saturation_UpperSat_e), 45, 1, 2, 294, "", 0 },

  { 148,
    "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_modell, Saturation_LowerSat_n), 45, 1, 2, 296, "", 0 },

  { 149, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_modell, Gain_Gain_k), 45, 1, 2, 298, "", 0 },

  { 150,
    "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_modell, Constant_Value_f), 45, 1, 2, 300, "", 0 },

  { 151, "modell/DP controller/DP controller/Kp/Gain", offsetof
    (Parameters_modell, Kp_Gain), 27, 9, 2, 302, "", 0 },

  { 152, "modell/DP controller/DP controller/Kp_scale/Value", offsetof
    (Parameters_modell, Kp_scale_Value), 45, 1, 2, 304, "", 0 },

  { 153, "modell/bias/Manual Switch/Constant/Value", offsetof(Parameters_modell,
    Constant_Value_ow), 53, 1, 2, 306, "", 0 },

  { 154, "modell/bias/Manual Switch/SwitchControl/Threshold", offsetof
    (Parameters_modell, SwitchControl_Threshold), 53, 1, 2, 308, "", 0 },

  { 155, "modell/bias/Manual Switch1/Constant/Value", offsetof(Parameters_modell,
    Constant_Value_b), 53, 1, 2, 310, "", 0 },

  { 156, "modell/bias/Manual Switch1/SwitchControl/Threshold", offsetof
    (Parameters_modell, SwitchControl_Threshold_a), 53, 1, 2, 312, "", 0 },
};

static int NI_ParamListSize = 157;
static int NI_ParamDimList[] = {
  1, 1,                                /* modell/HIL model/reset_eta_hil/Value */
  1, 1,                                /* modell/Constant/Value */
  3, 1,                                /* modell/HIL model/initial_nu_hil/Value */
  1, 1,                                /* modell/HIL model/nu_surge_hil/Gain */
  1, 1,                                /* modell/HIL model/nu_sway_hil/Gain */
  1, 1,                                /* modell/HIL model/nu_yaw_hil/Gain */
  1, 1,                                /* modell/LabView Out/Transfer Fcn/A */
  1, 1,                                /* modell/LabView Out/Transfer Fcn/C */
  1, 1,                                /* modell/LabView Out/Transfer Fcn1/A */
  1, 1,                                /* modell/LabView Out/Transfer Fcn1/C */
  1, 1,                                /* modell/LabView Out/Transfer Fcn2/A */
  1, 1,                                /* modell/LabView Out/Transfer Fcn2/C */
  3, 1,                                /* modell/Iceberg/initial position/Value */
  1, 1,                                /* modell/Iceberg/Integrator2/InitialCondition */
  3, 1,                                /* modell/Towline/Towline dynamics/T_zero/Value */
  1, 1,                                /* modell/Towline/Towline dynamics/Towline length/Value */
  3, 1,                                /* modell/Towline/pos_diff/Value */
  3, 3,                                /* modell/Towline/Towline dynamics/K_tow/Value */
  1, 1,                                /* modell/Towline/Towline dynamics/T_cr/Value */
  3, 1,                                /* modell/Towline/IC/Value */
  1, 1,                                /* modell/bias/Integrator/InitialCondition */
  1, 1,                                /* modell/bias/zero/Value */
  1, 1,                                /* modell/Observer (ship)/wave hat/InitialCondition */
  3, 6,                                /* modell/Observer (ship)/C_w/Gain */
  1, 1,                                /* modell/Observer (ship)/eta_hat/InitialCondition */
  1, 1,                                /* modell/Observer (ship)/nu_hat/InitialCondition */
  1, 1,                                /* modell/Observer (iceberg)/wave hat/InitialCondition */
  3, 6,                                /* modell/Observer (iceberg)/C_w/Gain */
  1, 1,                                /* modell/Observer (iceberg)/eta_hat/InitialCondition */
  1, 1,                                /* modell/Observer (iceberg)/nu_hat/InitialCondition */
  1, 1,                                /* modell/MODE/Value */
  1, 1,                                /* modell/ctc/Constant/Value */
  1, 1,                                /* modell/PS3 Sixaxis/threshold block1/Constant2/Value */
  1, 1,                                /* modell/PS3 Sixaxis/PS3_L_JS_Y/Value */
  1, 1,                                /* modell/PS3 Sixaxis/limit_L_JS_Y/Value */
  1, 1,                                /* modell/PS3 Sixaxis/Gain1/Gain */
  1, 1,                                /* modell/PS3 Sixaxis/threshold block/Constant2/Value */
  1, 1,                                /* modell/PS3 Sixaxis/PS3_L_JS_X/Value */
  1, 1,                                /* modell/PS3 Sixaxis/limit_L_JS_X/Value */
  1, 1,                                /* modell/PS3 Sixaxis/Gain/Gain */
  1, 1,                                /* modell/PS3 Sixaxis/threshold block3/Constant2/Value */
  1, 1,                                /* modell/PS3 Sixaxis/PS3_R_JS_Y/Value */
  1, 1,                                /* modell/PS3 Sixaxis/limit_R_JS_Y/Value */
  1, 1,                                /* modell/PS3 Sixaxis/Gain3/Gain */
  1, 1,                                /* modell/PS3 Sixaxis/threshold block2/Constant2/Value */
  1, 1,                                /* modell/PS3 Sixaxis/PS3_R_JS_X/Value */
  1, 1,                                /* modell/PS3 Sixaxis/limit_R_JS_X/Value */
  1, 1,                                /* modell/PS3 Sixaxis/Gain2/Gain */
  1, 1,                                /* modell/PS3 Sixaxis/PS3_L2/Value */
  1, 1,                                /* modell/PS3 Sixaxis/Constant/Value */
  1, 1,                                /* modell/PS3 Sixaxis/g1/Gain */
  1, 1,                                /* modell/PS3 Sixaxis/PS3_R2/Value */
  1, 1,                                /* modell/PS3 Sixaxis/Constant1/Value */
  1, 1,                                /* modell/PS3 Sixaxis/g2/Gain */
  1, 1,                                /* modell/LabView Out/BT_saturation/Value */
  1, 1,                                /* modell/LabView Out/VSP_speeds/Value */
  5, 5,                                /* modell/Joystick Control/Ke^-1/Value */
  5, 3,                                /* modell/Joystick Control/Te^+/Value */
  1, 1,                                /* modell/Joystick Control/joystick_gain_surge/Gain */
  1, 1,                                /* modell/Joystick Control/joystick_gain_sway/Gain */
  1, 1,                                /* modell/Joystick Control/joystick_gain_yaw/Gain */
  1, 1,                                /* modell/Joystick Control/Saturation/UpperLimit */
  1, 1,                                /* modell/Joystick Control/Saturation/LowerLimit */
  1, 1,                                /* modell/Joystick Control/VSP_speeds/Value */
  1, 1,                                /* modell/Joystick Control/BT_power_limit/Value */
  5, 5,                                /* modell/Thruster Control/Ke^-1/Value */
  5, 3,                                /* modell/Thruster Control/Te^+/Value */
  1, 1,                                /* modell/Thruster Control/VSP_speeds/Value */
  1, 1,                                /* modell/Thruster Control/BT_power_limit/Value */
  1, 1,                                /* modell/HIL model/BT_power/Gain */
  3, 5,                                /* modell/HIL model/Constant/Value */
  5, 5,                                /* modell/HIL model/Constant1/Value */
  3, 3,                                /* modell/HIL model/D/Gain */
  1, 1,                                /* modell/HIL model/u1_hil/Gain */
  1, 1,                                /* modell/HIL model/u2_hil/Gain */
  1, 1,                                /* modell/HIL model/u3_hil/Gain */
  1, 1,                                /* modell/HIL model/u4_hil/Gain */
  1, 1,                                /* modell/HIL model/Rate Limiter Dynamic/sample time/WtEt */
  1, 1,                                /* modell/HIL model/Rate Limiter Dynamic/Delay Input2/X0 */
  1, 1,                                /* modell/HIL model/neg/Gain */
  1, 1,                                /* modell/HIL model/u5_hil/Gain */
  1, 1,                                /* modell/HIL model/tau_surge_hil/Gain */
  1, 1,                                /* modell/HIL model/tau_sway_hil/Gain */
  1, 1,                                /* modell/HIL model/tau_yaw_hil/Gain */
  1, 1,                                /* modell/HIL model/VIS_HIL_E/Gain */
  1, 1,                                /* modell/HIL model/VIS_HIL_N/Gain */
  1, 1,                                /* modell/HIL model/VIS_HIL_PIS/Gain */
  1, 1,                                /* modell/HIL model/VSP_angle_deg_port/Gain */
  1, 1,                                /* modell/HIL model/VSP_angle_deg_stbd/Gain */
  3, 3,                                /* modell/HIL model/inv(M)/Gain */
  3, 3,                                /* modell/Iceberg/D/Gain */
  1, 1,                                /* modell/Iceberg/saturation/Saturation/UpperLimit */
  1, 1,                                /* modell/Iceberg/saturation/Saturation/LowerLimit */
  1, 1,                                /* modell/Iceberg/saturation/Saturation1/UpperLimit */
  1, 1,                                /* modell/Iceberg/saturation/Saturation1/LowerLimit */
  1, 1,                                /* modell/Iceberg/saturation/Saturation2/UpperLimit */
  1, 1,                                /* modell/Iceberg/saturation/Saturation2/LowerLimit */
  1, 1,                                /* modell/bias/Integrator1/InitialCondition */
  3, 3,                                /* modell/Iceberg/inv(M)/Gain */
  1, 1,                                /* modell/LabView Out/eta_d_E/Value */
  1, 1,                                /* modell/LabView Out/eta_d_N/Value */
  1, 1,                                /* modell/LabView Out/eta_d_Psi/Value */
  6, 6,                                /* modell/Observer (iceberg)/A_w/Gain */
  3, 3,                                /* modell/Observer (iceberg)/D/Gain */
  6, 3,                                /* modell/Observer (iceberg)/K_1/Gain */
  3, 3,                                /* modell/Observer (iceberg)/K_2/Gain */
  3, 3,                                /* modell/Observer (iceberg)/K_3/Gain */
  3, 3,                                /* modell/Observer (iceberg)/K_4/Gain */
  1, 1,                                /* modell/Observer (iceberg)/bias_hat_integrator/InitialCondition */
  3, 3,                                /* modell/Observer (iceberg)/M_inv/Gain */
  3, 3,                                /* modell/Observer (iceberg)/T_inv/Gain */
  6, 6,                                /* modell/Observer (ship)/A_w/Gain */
  3, 3,                                /* modell/Observer (ship)/D/Gain */
  6, 3,                                /* modell/Observer (ship)/K_1/Gain */
  3, 3,                                /* modell/Observer (ship)/K_2/Gain */
  3, 3,                                /* modell/Observer (ship)/K_3/Gain */
  3, 3,                                /* modell/Observer (ship)/K_4/Gain */
  1, 1,                                /* modell/Observer (ship)/bias_hat_integrator/InitialCondition */
  3, 3,                                /* modell/Observer (ship)/M_inv/Gain */
  3, 3,                                /* modell/Observer (ship)/T_inv/Gain */
  1, 1,                                /* modell/bias/Band-Limited White Noise/White Noise/Mean */
  1, 1,                                /* modell/bias/Band-Limited White Noise/White Noise/StdDev */
  1, 1,                                /* modell/bias/Band-Limited White Noise/White Noise/Seed */
  1, 3,                                /* modell/bias/Band-Limited White Noise/Output/Gain */
  3, 3,                                /* modell/bias/E_b_i/Gain */
  3, 3,                                /* modell/bias/E_b_s/Gain */
  3, 3,                                /* modell/bias/T_s_inv/Gain */
  3, 3,                                /* modell/bias/T_i_inv/Gain */
  1, 1,                                /* modell/Thruster Control/Saturation/UpperLimit */
  1, 1,                                /* modell/Thruster Control/Saturation/LowerLimit */
  1, 1,                                /* modell/Manual Thruster Control/U1/Gain */
  1, 1,                                /* modell/Manual Thruster Control/U2/Gain */
  1, 1,                                /* modell/Manual Thruster Control/U3/Gain */
  1, 1,                                /* modell/Manual Thruster Control/U4/Gain */
  1, 1,                                /* modell/Manual Thruster Control/U5/Gain */
  1, 1,                                /* modell/DP controller/DP controller/Integrator/InitialCondition */
  3, 3,                                /* modell/DP controller/DP controller/Kd/Gain */
  1, 1,                                /* modell/DP controller/DP controller/Kd_scale/Value */
  3, 3,                                /* modell/DP controller/DP controller/Ki/Gain */
  1, 1,                                /* modell/DP controller/DP controller/Ki_scale/Value */
  1, 1,                                /* modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* modell/DP controller/DP controller/Reg_e_N_hil/Gain */
  1, 1,                                /* modell/DP controller/DP controller/Reg_e_E_hil/Gain */
  1, 1,                                /* modell/DP controller/DP controller/Reg_e_Psi_hil/Gain */
  1, 1,                                /* modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Constant/Value */
  3, 3,                                /* modell/DP controller/DP controller/Kp/Gain */
  1, 1,                                /* modell/DP controller/DP controller/Kp_scale/Value */
  1, 1,                                /* modell/bias/Manual Switch/Constant/Value */
  1, 1,                                /* modell/bias/Manual Switch/SwitchControl/Threshold */
  1, 1,                                /* modell/bias/Manual Switch1/Constant/Value */
  1, 1,                                /* modell/bias/Manual Switch1/SwitchControl/Threshold */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 227;
static NI_Signal NI_SigList[] = {
  { 0, "modell/Constant", 0, "", offsetof(BlockIO_modell, Constant), BLOCKIO_SIG,
    0, 1, 2, 0, 0 },

  { 1, "modell/HIL model/Integrator1", 0, "", offsetof(BlockIO_modell,
    Integrator1), BLOCKIO_SIG, 17, 3, 2, 2, 0 },

  { 2, "modell/HIL model/initial_nu_hil", 0, "", offsetof(BlockIO_modell,
    initial_nu_hil), BLOCKIO_SIG, 17, 3, 2, 4, 0 },

  { 3, "modell/HIL model/Integrator", 0, "", offsetof(BlockIO_modell, Integrator),
    BLOCKIO_SIG, 17, 3, 2, 6, 0 },

  { 4, "modell/HIL model/nu_surge_hil", 0, "", offsetof(BlockIO_modell,
    nu_surge_hil), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "modell/HIL model/nu_sway_hil", 0, "", offsetof(BlockIO_modell,
    nu_sway_hil), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "modell/HIL model/nu_yaw_hil", 0, "", offsetof(BlockIO_modell, nu_yaw_hil),
    BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "modell/LabView Out/Transfer Fcn", 0, "", offsetof(BlockIO_modell,
    TransferFcn), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "modell/LabView Out/Transfer Fcn1", 0, "", offsetof(BlockIO_modell,
    TransferFcn1), BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "modell/LabView Out/Transfer Fcn2", 0, "", offsetof(BlockIO_modell,
    TransferFcn2), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "modell/Iceberg/initial position", 0, "", offsetof(BlockIO_modell,
    initialposition), BLOCKIO_SIG, 17, 3, 2, 20, 0 },

  { 11, "modell/Iceberg/Integrator1", 0, "", offsetof(BlockIO_modell,
    Integrator1_e), BLOCKIO_SIG, 17, 3, 2, 22, 0 },

  { 12, "modell/Iceberg/Integrator2", 0, "", offsetof(BlockIO_modell,
    Integrator2), BLOCKIO_SIG, 17, 3, 2, 24, 0 },

  { 13, "modell/Towline/pos_diff", 0, "", offsetof(BlockIO_modell, pos_diff),
    BLOCKIO_SIG, 17, 3, 2, 26, 0 },

  { 14, "modell/Towline/Integrator", 0, "", offsetof(BlockIO_modell,
    Integrator_l), BLOCKIO_SIG, 17, 3, 2, 28, 0 },

  { 15, "modell/Towline/Towline dynamics/cartesian length/mf1", 0, "", offsetof
    (BlockIO_modell, mf1), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "modell/Towline/Towline dynamics/cartesian length/mf2", 0, "", offsetof
    (BlockIO_modell, mf2), BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17, "modell/Towline/Towline dynamics/cartesian length/Sum", 0, "", offsetof
    (BlockIO_modell, Sum), BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18, "modell/Towline/Towline dynamics/cartesian length/mf3", 0, "", offsetof
    (BlockIO_modell, mf3), BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "modell/Towline/Towline dynamics/T_temp", 0, "", offsetof(BlockIO_modell,
    T_temp), BLOCKIO_SIG, 17, 3, 2, 38, 0 },

  { 20, "modell/Towline/Towline dynamics/cartesian length1/mf1", 0, "", offsetof
    (BlockIO_modell, mf1_j), BLOCKIO_SIG, 0, 1, 2, 40, 0 },

  { 21, "modell/Towline/Towline dynamics/cartesian length1/mf2", 0, "", offsetof
    (BlockIO_modell, mf2_m), BLOCKIO_SIG, 0, 1, 2, 42, 0 },

  { 22, "modell/Towline/Towline dynamics/cartesian length1/Sum", 0, "", offsetof
    (BlockIO_modell, Sum_p), BLOCKIO_SIG, 0, 1, 2, 44, 0 },

  { 23, "modell/Towline/Towline dynamics/cartesian length1/mf3", 0, "", offsetof
    (BlockIO_modell, mf3_f), BLOCKIO_SIG, 0, 1, 2, 46, 0 },

  { 24, "modell/Towline/Towline dynamics/Sum2", 0, "", offsetof(BlockIO_modell,
    Sum2), BLOCKIO_SIG, 17, 3, 2, 48, 0 },

  { 25, "modell/Towline/IC", 0, "", offsetof(BlockIO_modell, IC), BLOCKIO_SIG,
    17, 3, 2, 50, 0 },

  { 26, "modell/bias/Integrator", 0, "", offsetof(BlockIO_modell, Integrator_n),
    BLOCKIO_SIG, 17, 3, 2, 52, 0 },

  { 27, "modell/bias/Manual Switch/SwitchControl", 0, "", offsetof
    (BlockIO_modell, SwitchControl), BLOCKIO_SIG, 17, 3, 2, 54, 0 },

  { 28, "modell/Observer (ship)/wave hat", 0, "", offsetof(BlockIO_modell,
    wavehat), BLOCKIO_SIG, 24, 6, 2, 56, 0 },

  { 29, "modell/Observer (ship)/C_w", 0, "", offsetof(BlockIO_modell, C_w),
    BLOCKIO_SIG, 17, 3, 2, 58, 0 },

  { 30, "modell/Observer (ship)/eta_hat", 0, "", offsetof(BlockIO_modell,
    eta_hat), BLOCKIO_SIG, 17, 3, 2, 60, 0 },

  { 31, "modell/Observer (ship)/Sum6", 0, "", offsetof(BlockIO_modell, Sum6),
    BLOCKIO_SIG, 17, 3, 2, 62, 0 },

  { 32, "modell/Observer (ship)/nu_hat", 0, "", offsetof(BlockIO_modell, nu_hat),
    BLOCKIO_SIG, 17, 3, 2, 64, 0 },

  { 33, "modell/Observer (iceberg)/wave hat", 0, "", offsetof(BlockIO_modell,
    wavehat_n), BLOCKIO_SIG, 24, 6, 2, 66, 0 },

  { 34, "modell/Observer (iceberg)/C_w", 0, "", offsetof(BlockIO_modell, C_w_d),
    BLOCKIO_SIG, 17, 3, 2, 68, 0 },

  { 35, "modell/Observer (iceberg)/eta_hat", 0, "", offsetof(BlockIO_modell,
    eta_hat_m), BLOCKIO_SIG, 17, 3, 2, 70, 0 },

  { 36, "modell/Observer (iceberg)/Sum6", 0, "", offsetof(BlockIO_modell, Sum6_a),
    BLOCKIO_SIG, 17, 3, 2, 72, 0 },

  { 37, "modell/Observer (iceberg)/nu_hat", 0, "", offsetof(BlockIO_modell,
    nu_hat_n), BLOCKIO_SIG, 17, 3, 2, 74, 0 },

  { 38, "modell/PS3 Sixaxis/threshold block1/Abs", 0, "", offsetof
    (BlockIO_modell, Abs), BLOCKIO_SIG, 0, 1, 2, 76, 0 },

  { 39, "modell/PS3 Sixaxis/Gain1", 0, "", offsetof(BlockIO_modell, Gain1),
    BLOCKIO_SIG, 0, 1, 2, 78, 0 },

  { 40, "modell/PS3 Sixaxis/threshold block1/Sum", 0, "", offsetof
    (BlockIO_modell, Sum_b), BLOCKIO_SIG, 0, 1, 2, 80, 0 },

  { 41, "modell/PS3 Sixaxis/threshold block/Abs", 0, "", offsetof(BlockIO_modell,
    Abs_n), BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42, "modell/PS3 Sixaxis/Gain", 0, "", offsetof(BlockIO_modell, Gain),
    BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43, "modell/PS3 Sixaxis/threshold block/Sum", 0, "", offsetof(BlockIO_modell,
    Sum_i), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44, "modell/PS3 Sixaxis/threshold block3/Abs", 0, "", offsetof
    (BlockIO_modell, Abs_o), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "modell/PS3 Sixaxis/Gain3", 0, "", offsetof(BlockIO_modell, Gain3),
    BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46, "modell/PS3 Sixaxis/threshold block3/Sum", 0, "", offsetof
    (BlockIO_modell, Sum_e), BLOCKIO_SIG, 0, 1, 2, 92, 0 },

  { 47, "modell/PS3 Sixaxis/threshold block2/Abs", 0, "", offsetof
    (BlockIO_modell, Abs_d), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48, "modell/PS3 Sixaxis/Gain2", 0, "", offsetof(BlockIO_modell, Gain2),
    BLOCKIO_SIG, 0, 1, 2, 96, 0 },

  { 49, "modell/PS3 Sixaxis/threshold block2/Sum", 0, "", offsetof
    (BlockIO_modell, Sum_d), BLOCKIO_SIG, 0, 1, 2, 98, 0 },

  { 50, "modell/PS3 Sixaxis/Sum3", 0, "", offsetof(BlockIO_modell, Sum3),
    BLOCKIO_SIG, 0, 1, 2, 100, 0 },

  { 51, "modell/PS3 Sixaxis/g1", 0, "", offsetof(BlockIO_modell, g1),
    BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52, "modell/PS3 Sixaxis/Sum4", 0, "", offsetof(BlockIO_modell, Sum4),
    BLOCKIO_SIG, 0, 1, 2, 104, 0 },

  { 53, "modell/PS3 Sixaxis/g2", 0, "", offsetof(BlockIO_modell, g2),
    BLOCKIO_SIG, 0, 1, 2, 106, 0 },

  { 54, "modell/Joystick Control/Product", 0, "", offsetof(BlockIO_modell,
    Product), BLOCKIO_SIG, 25, 15, 2, 108, 0 },

  { 55, "modell/Joystick Control/joystick_gain_surge", 0, "", offsetof
    (BlockIO_modell, joystick_gain_surge), BLOCKIO_SIG, 0, 1, 2, 110, 0 },

  { 56, "modell/Joystick Control/joystick_gain_sway", 0, "", offsetof
    (BlockIO_modell, joystick_gain_sway), BLOCKIO_SIG, 0, 1, 2, 112, 0 },

  { 57, "modell/Joystick Control/Sum", 0, "", offsetof(BlockIO_modell, Sum_c),
    BLOCKIO_SIG, 0, 1, 2, 114, 0 },

  { 58, "modell/Joystick Control/joystick_gain_yaw", 0, "", offsetof
    (BlockIO_modell, joystick_gain_yaw), BLOCKIO_SIG, 0, 1, 2, 116, 0 },

  { 59, "modell/Joystick Control/Product1", 0, "", offsetof(BlockIO_modell,
    Product1), BLOCKIO_SIG, 23, 5, 2, 118, 0 },

  { 60, "modell/Joystick Control/Saturation", 0, "", offsetof(BlockIO_modell,
    Saturation), BLOCKIO_SIG, 23, 5, 2, 120, 0 },

  { 61, "modell/Thruster Control/Product", 0, "", offsetof(BlockIO_modell,
    Product_c), BLOCKIO_SIG, 25, 15, 2, 122, 0 },

  { 62, "modell/Thruster Control/Sum", 0, "", offsetof(BlockIO_modell, Sum_pv),
    BLOCKIO_SIG, 17, 3, 2, 124, 0 },

  { 63, "modell/Multiport Switch", 0, "", offsetof(BlockIO_modell,
    MultiportSwitch), BLOCKIO_SIG, 19, 7, 2, 126, 0 },

  { 64, "modell/HIL model/BT_power", 0, "", offsetof(BlockIO_modell, BT_power),
    BLOCKIO_SIG, 0, 1, 2, 128, 0 },

  { 65, "modell/HIL model/Cartesian to Polar Port/x->r", 0, "", offsetof
    (BlockIO_modell, xr), BLOCKIO_SIG, 0, 1, 2, 130, 0 },

  { 66, "modell/HIL model/Cartesian to Polar Port/x->theta", 0, "", offsetof
    (BlockIO_modell, xtheta), BLOCKIO_SIG, 0, 1, 2, 132, 0 },

  { 67, "modell/HIL model/Cartesian to Polar Stbd/x->r", 0, "", offsetof
    (BlockIO_modell, xr_i), BLOCKIO_SIG, 0, 1, 2, 134, 0 },

  { 68, "modell/HIL model/Cartesian to Polar Stbd/x->theta", 0, "", offsetof
    (BlockIO_modell, xtheta_d), BLOCKIO_SIG, 0, 1, 2, 136, 0 },

  { 69, "modell/HIL model/D", 0, "", offsetof(BlockIO_modell, D), BLOCKIO_SIG,
    17, 3, 2, 138, 0 },

  { 70, "modell/HIL model/u1_hil", 0, "", offsetof(BlockIO_modell, u1_hil),
    BLOCKIO_SIG, 0, 1, 2, 140, 0 },

  { 71, "modell/HIL model/u2_hil", 0, "", offsetof(BlockIO_modell, u2_hil),
    BLOCKIO_SIG, 0, 1, 2, 142, 0 },

  { 72, "modell/HIL model/u3_hil", 0, "", offsetof(BlockIO_modell, u3_hil),
    BLOCKIO_SIG, 0, 1, 2, 144, 0 },

  { 73, "modell/HIL model/u4_hil", 0, "", offsetof(BlockIO_modell, u4_hil),
    BLOCKIO_SIG, 0, 1, 2, 146, 0 },

  { 74, "modell/HIL model/Rate Limiter Dynamic/sample time", 0, "", offsetof
    (BlockIO_modell, sampletime), BLOCKIO_SIG, 0, 1, 2, 148, 0 },

  { 75, "modell/HIL model/Rate Limiter Dynamic/delta rise limit", 0, "",
    offsetof(BlockIO_modell, deltariselimit), BLOCKIO_SIG, 0, 1, 2, 150, 0 },

  { 76, "modell/HIL model/Rate Limiter Dynamic/Delay Input2", 0, "Y(k-1)",
    offsetof(BlockIO_modell, Yk1), BLOCKIO_SIG, 0, 1, 2, 152, 0 },

  { 77, "modell/HIL model/Rate Limiter Dynamic/Difference Inputs1", 0,
    "( U(k) - Y(k-1) )", offsetof(BlockIO_modell, UkYk1), BLOCKIO_SIG, 0, 1, 2,
    154, 0 },

  { 78, "modell/HIL model/neg", 0, "", offsetof(BlockIO_modell, neg),
    BLOCKIO_SIG, 0, 1, 2, 156, 0 },

  { 79, "modell/HIL model/Rate Limiter Dynamic/delta fall limit", 0, "",
    offsetof(BlockIO_modell, deltafalllimit), BLOCKIO_SIG, 0, 1, 2, 158, 0 },

  { 80, "modell/HIL model/Rate Limiter Dynamic/Saturation Dynamic/Switch", 0, "",
    offsetof(BlockIO_modell, Switch), BLOCKIO_SIG, 0, 1, 2, 160, 0 },

  { 81, "modell/HIL model/Rate Limiter Dynamic/Saturation Dynamic/Switch2", 0,
    "", offsetof(BlockIO_modell, Switch2), BLOCKIO_SIG, 0, 1, 2, 162, 0 },

  { 82, "modell/HIL model/Rate Limiter Dynamic/Difference Inputs2", 0, "",
    offsetof(BlockIO_modell, DifferenceInputs2), BLOCKIO_SIG, 0, 1, 2, 164, 0 },

  { 83, "modell/HIL model/u5_hil", 0, "", offsetof(BlockIO_modell, u5_hil),
    BLOCKIO_SIG, 0, 1, 2, 166, 0 },

  { 84, "modell/HIL model/Product", 0, "", offsetof(BlockIO_modell, Product_o),
    BLOCKIO_SIG, 17, 3, 2, 168, 0 },

  { 85, "modell/HIL model/Rotation matrix in yaw 1/Fcn", 0, "x_dot", offsetof
    (BlockIO_modell, x_dot), BLOCKIO_SIG, 0, 1, 2, 170, 0 },

  { 86, "modell/HIL model/Rotation matrix in yaw 1/Fcn1", 0, "y_dot", offsetof
    (BlockIO_modell, y_dot), BLOCKIO_SIG, 0, 1, 2, 172, 0 },

  { 87, "modell/HIL model/Rotation matrix in yaw 1/Fcn2", 0, "psi_dot", offsetof
    (BlockIO_modell, psi_dot), BLOCKIO_SIG, 0, 1, 2, 174, 0 },

  { 88, "modell/HIL model/tau_surge_hil", 0, "", offsetof(BlockIO_modell,
    tau_surge_hil), BLOCKIO_SIG, 0, 1, 2, 176, 0 },

  { 89, "modell/HIL model/tau_sway_hil", 0, "", offsetof(BlockIO_modell,
    tau_sway_hil), BLOCKIO_SIG, 0, 1, 2, 178, 0 },

  { 90, "modell/HIL model/tau_yaw_hil", 0, "", offsetof(BlockIO_modell,
    tau_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 180, 0 },

  { 91, "modell/HIL model/Sum3", 0, "", offsetof(BlockIO_modell, Sum3_o),
    BLOCKIO_SIG, 17, 3, 2, 182, 0 },

  { 92, "modell/HIL model/VIS_HIL_E", 0, "", offsetof(BlockIO_modell, VIS_HIL_E),
    BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93, "modell/HIL model/VIS_HIL_N", 0, "", offsetof(BlockIO_modell, VIS_HIL_N),
    BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94, "modell/HIL model/VIS_HIL_PIS", 0, "", offsetof(BlockIO_modell,
    VIS_HIL_PIS), BLOCKIO_SIG, 0, 1, 2, 188, 0 },

  { 95, "modell/HIL model/VSP_angle_deg_port", 0, "", offsetof(BlockIO_modell,
    VSP_angle_deg_port), BLOCKIO_SIG, 0, 1, 2, 190, 0 },

  { 96, "modell/HIL model/VSP_angle_deg_stbd", 0, "", offsetof(BlockIO_modell,
    VSP_angle_deg_stbd), BLOCKIO_SIG, 0, 1, 2, 192, 0 },

  { 97, "modell/HIL model/inv(M)", 0, "", offsetof(BlockIO_modell, invM),
    BLOCKIO_SIG, 17, 3, 2, 194, 0 },

  { 98, "modell/Iceberg/D", 0, "", offsetof(BlockIO_modell, D_f), BLOCKIO_SIG,
    17, 3, 2, 196, 0 },

  { 99, "modell/Iceberg/Rotation matrix in yaw 1/Fcn", 0, "x_dot", offsetof
    (BlockIO_modell, x_dot_a), BLOCKIO_SIG, 0, 1, 2, 198, 0 },

  { 100, "modell/Iceberg/Rotation matrix in yaw 1/Fcn1", 0, "y_dot", offsetof
    (BlockIO_modell, y_dot_g), BLOCKIO_SIG, 0, 1, 2, 200, 0 },

  { 101, "modell/Iceberg/Rotation matrix in yaw 1/Fcn2", 0, "psi_dot", offsetof
    (BlockIO_modell, psi_dot_p), BLOCKIO_SIG, 0, 1, 2, 202, 0 },

  { 102, "modell/Iceberg/saturation/Saturation", 0, "", offsetof(BlockIO_modell,
    Saturation_l), BLOCKIO_SIG, 0, 1, 2, 204, 0 },

  { 103, "modell/Iceberg/saturation/Saturation1", 0, "", offsetof(BlockIO_modell,
    Saturation1), BLOCKIO_SIG, 0, 1, 2, 206, 0 },

  { 104, "modell/Iceberg/saturation/Saturation2", 0, "", offsetof(BlockIO_modell,
    Saturation2), BLOCKIO_SIG, 0, 1, 2, 208, 0 },

  { 105, "modell/bias/Integrator1", 0, "", offsetof(BlockIO_modell,
    Integrator1_n), BLOCKIO_SIG, 17, 3, 2, 210, 0 },

  { 106, "modell/bias/Manual Switch1/SwitchControl", 0, "", offsetof
    (BlockIO_modell, SwitchControl_o), BLOCKIO_SIG, 17, 3, 2, 212, 0 },

  { 107, "modell/Iceberg/Sum3", 0, "", offsetof(BlockIO_modell, Sum3_f),
    BLOCKIO_SIG, 17, 3, 2, 214, 0 },

  { 108, "modell/Iceberg/inv(M)", 0, "", offsetof(BlockIO_modell, invM_g),
    BLOCKIO_SIG, 17, 3, 2, 216, 0 },

  { 109, "modell/Observer (iceberg)/A_w", 0, "", offsetof(BlockIO_modell, A_w),
    BLOCKIO_SIG, 24, 6, 2, 218, 0 },

  { 110, "modell/Observer (iceberg)/D", 0, "", offsetof(BlockIO_modell, D_fe),
    BLOCKIO_SIG, 17, 3, 2, 220, 0 },

  { 111, "modell/Observer (iceberg)/Sum", 0, "", offsetof(BlockIO_modell, Sum_n),
    BLOCKIO_SIG, 17, 3, 2, 222, 0 },

  { 112, "modell/Observer (iceberg)/K_1", 0, "", offsetof(BlockIO_modell, K_1),
    BLOCKIO_SIG, 24, 6, 2, 224, 0 },

  { 113, "modell/Observer (iceberg)/K_2", 0, "", offsetof(BlockIO_modell, K_2),
    BLOCKIO_SIG, 17, 3, 2, 226, 0 },

  { 114, "modell/Observer (iceberg)/K_3", 0, "", offsetof(BlockIO_modell, K_3),
    BLOCKIO_SIG, 17, 3, 2, 228, 0 },

  { 115, "modell/Observer (iceberg)/K_4", 0, "", offsetof(BlockIO_modell, K_4),
    BLOCKIO_SIG, 17, 3, 2, 230, 0 },

  { 116, "modell/Observer (iceberg)/bias_hat_integrator", 0, "", offsetof
    (BlockIO_modell, bias_hat_integrator), BLOCKIO_SIG, 17, 3, 2, 232, 0 },

  { 117, "modell/Observer (iceberg)/R_T2/Row1", 0, "", offsetof(BlockIO_modell,
    Row1), BLOCKIO_SIG, 0, 1, 2, 234, 0 },

  { 118, "modell/Observer (iceberg)/R_T2/Row2", 0, "", offsetof(BlockIO_modell,
    Row2), BLOCKIO_SIG, 0, 1, 2, 236, 0 },

  { 119, "modell/Observer (iceberg)/R_T2/Row3", 0, "", offsetof(BlockIO_modell,
    Row3), BLOCKIO_SIG, 0, 1, 2, 238, 0 },

  { 120, "modell/Observer (iceberg)/R_T1/Row1", 0, "", offsetof(BlockIO_modell,
    Row1_d), BLOCKIO_SIG, 0, 1, 2, 240, 0 },

  { 121, "modell/Observer (iceberg)/R_T1/Row2", 0, "", offsetof(BlockIO_modell,
    Row2_p), BLOCKIO_SIG, 0, 1, 2, 242, 0 },

  { 122, "modell/Observer (iceberg)/R_T1/Row3", 0, "", offsetof(BlockIO_modell,
    Row3_j), BLOCKIO_SIG, 0, 1, 2, 244, 0 },

  { 123, "modell/Observer (iceberg)/Sum1", 0, "", offsetof(BlockIO_modell, Sum1),
    BLOCKIO_SIG, 17, 3, 2, 246, 0 },

  { 124, "modell/Observer (iceberg)/Sum4", 0, "", offsetof(BlockIO_modell,
    Sum4_o), BLOCKIO_SIG, 17, 3, 2, 248, 0 },

  { 125, "modell/Observer (iceberg)/M_inv", 0, "", offsetof(BlockIO_modell,
    M_inv), BLOCKIO_SIG, 17, 3, 2, 250, 0 },

  { 126, "modell/Observer (iceberg)/Rotation matrix in yaw /Fcn", 0, "x_dot",
    offsetof(BlockIO_modell, x_dot_f), BLOCKIO_SIG, 0, 1, 2, 252, 0 },

  { 127, "modell/Observer (iceberg)/Rotation matrix in yaw /Fcn1", 0, "y_dot",
    offsetof(BlockIO_modell, y_dot_m), BLOCKIO_SIG, 0, 1, 2, 254, 0 },

  { 128, "modell/Observer (iceberg)/Rotation matrix in yaw /Fcn2", 0, "psi_dot",
    offsetof(BlockIO_modell, psi_dot_g), BLOCKIO_SIG, 0, 1, 2, 256, 0 },

  { 129, "modell/Observer (iceberg)/T_inv", 0, "", offsetof(BlockIO_modell,
    T_inv), BLOCKIO_SIG, 17, 3, 2, 258, 0 },

  { 130, "modell/Observer (iceberg)/Sum2", 0, "", offsetof(BlockIO_modell,
    Sum2_b), BLOCKIO_SIG, 17, 3, 2, 260, 0 },

  { 131, "modell/Observer (iceberg)/Sum3", 0, "", offsetof(BlockIO_modell,
    Sum3_g), BLOCKIO_SIG, 17, 3, 2, 262, 0 },

  { 132, "modell/Observer (iceberg)/Sum5", 0, "", offsetof(BlockIO_modell, Sum5),
    BLOCKIO_SIG, 24, 6, 2, 264, 0 },

  { 133, "modell/Observer (ship)/A_w", 0, "", offsetof(BlockIO_modell, A_w_l),
    BLOCKIO_SIG, 24, 6, 2, 266, 0 },

  { 134, "modell/Observer (ship)/D", 0, "", offsetof(BlockIO_modell, D_n),
    BLOCKIO_SIG, 17, 3, 2, 268, 0 },

  { 135, "modell/Observer (ship)/Sum", 0, "", offsetof(BlockIO_modell, Sum_h),
    BLOCKIO_SIG, 17, 3, 2, 270, 0 },

  { 136, "modell/Observer (ship)/K_1", 0, "", offsetof(BlockIO_modell, K_1_d),
    BLOCKIO_SIG, 24, 6, 2, 272, 0 },

  { 137, "modell/Observer (ship)/K_2", 0, "", offsetof(BlockIO_modell, K_2_n),
    BLOCKIO_SIG, 17, 3, 2, 274, 0 },

  { 138, "modell/Observer (ship)/K_3", 0, "", offsetof(BlockIO_modell, K_3_j),
    BLOCKIO_SIG, 17, 3, 2, 276, 0 },

  { 139, "modell/Observer (ship)/K_4", 0, "", offsetof(BlockIO_modell, K_4_j),
    BLOCKIO_SIG, 17, 3, 2, 278, 0 },

  { 140, "modell/Observer (ship)/bias_hat_integrator", 0, "", offsetof
    (BlockIO_modell, bias_hat_integrator_a), BLOCKIO_SIG, 17, 3, 2, 280, 0 },

  { 141, "modell/Observer (ship)/R_T2/Row1", 0, "", offsetof(BlockIO_modell,
    Row1_m), BLOCKIO_SIG, 0, 1, 2, 282, 0 },

  { 142, "modell/Observer (ship)/R_T2/Row2", 0, "", offsetof(BlockIO_modell,
    Row2_c), BLOCKIO_SIG, 0, 1, 2, 284, 0 },

  { 143, "modell/Observer (ship)/R_T2/Row3", 0, "", offsetof(BlockIO_modell,
    Row3_i), BLOCKIO_SIG, 0, 1, 2, 286, 0 },

  { 144, "modell/Observer (ship)/R_T1/Row1", 0, "", offsetof(BlockIO_modell,
    Row1_a), BLOCKIO_SIG, 0, 1, 2, 288, 0 },

  { 145, "modell/Observer (ship)/R_T1/Row2", 0, "", offsetof(BlockIO_modell,
    Row2_g), BLOCKIO_SIG, 0, 1, 2, 290, 0 },

  { 146, "modell/Observer (ship)/R_T1/Row3", 0, "", offsetof(BlockIO_modell,
    Row3_n), BLOCKIO_SIG, 0, 1, 2, 292, 0 },

  { 147, "modell/Observer (ship)/Sum1", 0, "", offsetof(BlockIO_modell, Sum1_g),
    BLOCKIO_SIG, 17, 3, 2, 294, 0 },

  { 148, "modell/Observer (ship)/Sum4", 0, "", offsetof(BlockIO_modell, Sum4_l),
    BLOCKIO_SIG, 17, 3, 2, 296, 0 },

  { 149, "modell/Observer (ship)/M_inv", 0, "", offsetof(BlockIO_modell, M_inv_d),
    BLOCKIO_SIG, 17, 3, 2, 298, 0 },

  { 150, "modell/Observer (ship)/Rotation matrix in yaw /Fcn", 0, "x_dot",
    offsetof(BlockIO_modell, x_dot_l), BLOCKIO_SIG, 0, 1, 2, 300, 0 },

  { 151, "modell/Observer (ship)/Rotation matrix in yaw /Fcn1", 0, "y_dot",
    offsetof(BlockIO_modell, y_dot_i), BLOCKIO_SIG, 0, 1, 2, 302, 0 },

  { 152, "modell/Observer (ship)/Rotation matrix in yaw /Fcn2", 0, "psi_dot",
    offsetof(BlockIO_modell, psi_dot_j), BLOCKIO_SIG, 0, 1, 2, 304, 0 },

  { 153, "modell/Observer (ship)/T_inv", 0, "", offsetof(BlockIO_modell, T_inv_i),
    BLOCKIO_SIG, 17, 3, 2, 306, 0 },

  { 154, "modell/Observer (ship)/Sum2", 0, "", offsetof(BlockIO_modell, Sum2_k),
    BLOCKIO_SIG, 17, 3, 2, 308, 0 },

  { 155, "modell/Observer (ship)/Sum3", 0, "", offsetof(BlockIO_modell, Sum3_i),
    BLOCKIO_SIG, 17, 3, 2, 310, 0 },

  { 156, "modell/Observer (ship)/Sum5", 0, "", offsetof(BlockIO_modell, Sum5_a),
    BLOCKIO_SIG, 24, 6, 2, 312, 0 },

  { 157, "modell/Towline/Sum", 0, "", offsetof(BlockIO_modell, Sum_d0),
    BLOCKIO_SIG, 17, 3, 2, 314, 0 },

  { 158, "modell/Towline/cartesian length/mf1", 0, "", offsetof(BlockIO_modell,
    mf1_js), BLOCKIO_SIG, 0, 1, 2, 316, 0 },

  { 159, "modell/Towline/cartesian length/mf2", 0, "", offsetof(BlockIO_modell,
    mf2_d), BLOCKIO_SIG, 0, 1, 2, 318, 0 },

  { 160, "modell/Towline/cartesian length/Sum", 0, "", offsetof(BlockIO_modell,
    Sum_pn), BLOCKIO_SIG, 0, 1, 2, 320, 0 },

  { 161, "modell/Towline/cartesian length/mf3", 0, "", offsetof(BlockIO_modell,
    mf3_l), BLOCKIO_SIG, 0, 1, 2, 322, 0 },

  { 162, "modell/bias/Band-Limited White Noise/White Noise", 0, "", offsetof
    (BlockIO_modell, WhiteNoise), BLOCKIO_SIG, 0, 1, 2, 324, 0 },

  { 163, "modell/bias/Band-Limited White Noise/Output", 0, "", offsetof
    (BlockIO_modell, Output), BLOCKIO_SIG, 17, 3, 2, 326, 0 },

  { 164, "modell/bias/E_b_i", 0, "", offsetof(BlockIO_modell, E_b_i),
    BLOCKIO_SIG, 17, 3, 2, 328, 0 },

  { 165, "modell/bias/E_b_s", 0, "", offsetof(BlockIO_modell, E_b_s),
    BLOCKIO_SIG, 17, 3, 2, 330, 0 },

  { 166, "modell/bias/T_s_inv", 0, "", offsetof(BlockIO_modell, T_s_inv),
    BLOCKIO_SIG, 17, 3, 2, 332, 0 },

  { 167, "modell/bias/Sum", 0, "", offsetof(BlockIO_modell, Sum_iz), BLOCKIO_SIG,
    17, 3, 2, 334, 0 },

  { 168, "modell/bias/T_i_inv", 0, "", offsetof(BlockIO_modell, T_i_inv),
    BLOCKIO_SIG, 17, 3, 2, 336, 0 },

  { 169, "modell/bias/Sum1", 0, "", offsetof(BlockIO_modell, Sum1_i),
    BLOCKIO_SIG, 17, 3, 2, 338, 0 },

  { 170, "modell/bias/Transposed rotation  matrix in yaw1/Row1", 0, "", offsetof
    (BlockIO_modell, Row1_k), BLOCKIO_SIG, 0, 1, 2, 340, 0 },

  { 171, "modell/bias/Transposed rotation  matrix in yaw1/Row2", 0, "", offsetof
    (BlockIO_modell, Row2_g1), BLOCKIO_SIG, 0, 1, 2, 342, 0 },

  { 172, "modell/bias/Transposed rotation  matrix in yaw1/Row3", 0, "", offsetof
    (BlockIO_modell, Row3_d), BLOCKIO_SIG, 0, 1, 2, 344, 0 },

  { 173, "modell/bias/Transposed rotation  matrix in yaw/Row1", 0, "", offsetof
    (BlockIO_modell, Row1_av), BLOCKIO_SIG, 0, 1, 2, 346, 0 },

  { 174, "modell/bias/Transposed rotation  matrix in yaw/Row2", 0, "", offsetof
    (BlockIO_modell, Row2_e), BLOCKIO_SIG, 0, 1, 2, 348, 0 },

  { 175, "modell/bias/Transposed rotation  matrix in yaw/Row3", 0, "", offsetof
    (BlockIO_modell, Row3_it), BLOCKIO_SIG, 0, 1, 2, 350, 0 },

  { 176, "modell/DP controller/DP controller/Integrator", 0, "", offsetof
    (BlockIO_modell, Integrator_ln), BLOCKIO_SIG, 17, 3, 2, 352, 0 },

  { 177, "modell/DP controller/DP controller/Kd", 0, "", offsetof(BlockIO_modell,
    Kd), BLOCKIO_SIG, 17, 3, 2, 354, 0 },

  { 178, "modell/DP controller/DP controller/Ki", 0, "", offsetof(BlockIO_modell,
    Ki), BLOCKIO_SIG, 17, 3, 2, 356, 0 },

  { 179, "modell/DP controller/DP controller/yaw angle", 0, "psi", offsetof
    (BlockIO_modell, psi), BLOCKIO_SIG, 0, 1, 2, 358, 0 },

  { 180, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_modell, Saturation_o), BLOCKIO_SIG, 0, 1, 2, 360, 0
  },

  { 181, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Sign", 0,
    "", offsetof(BlockIO_modell, Sign), BLOCKIO_SIG, 0, 1, 2, 362, 0 },

  { 182, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Gain", 0,
    "", offsetof(BlockIO_modell, Gain_a), BLOCKIO_SIG, 0, 1, 2, 364, 0 },

  { 183, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Sum1", 0,
    "", offsetof(BlockIO_modell, Sum1_f), BLOCKIO_SIG, 0, 1, 2, 366, 0 },

  { 184,
    "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_modell, MathFunction), BLOCKIO_SIG, 0, 1, 2, 368, 0
  },

  { 185, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]1/Sum", 0, "",
    offsetof(BlockIO_modell, Sum_l), BLOCKIO_SIG, 0, 1, 2, 370, 0 },

  { 186, "modell/DP controller/DP controller/Sum2", 0, "regulation error",
    offsetof(BlockIO_modell, regulationerror), BLOCKIO_SIG, 17, 3, 2, 372, 0 },

  { 187, "modell/DP controller/DP controller/Reg_e_N_hil", 0, "", offsetof
    (BlockIO_modell, Reg_e_N_hil), BLOCKIO_SIG, 0, 1, 2, 374, 0 },

  { 188, "modell/DP controller/DP controller/Reg_e_E_hil", 0, "", offsetof
    (BlockIO_modell, Reg_e_E_hil), BLOCKIO_SIG, 0, 1, 2, 376, 0 },

  { 189, "modell/DP controller/DP controller/Reg_e_Psi_hil", 0, "", offsetof
    (BlockIO_modell, Reg_e_Psi_hil), BLOCKIO_SIG, 0, 1, 2, 378, 0 },

  { 190, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_modell, Saturation_f), BLOCKIO_SIG, 0, 1, 2, 380, 0
  },

  { 191, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Sign", 0, "",
    offsetof(BlockIO_modell, Sign_l), BLOCKIO_SIG, 0, 1, 2, 382, 0 },

  { 192, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Gain", 0, "",
    offsetof(BlockIO_modell, Gain_h), BLOCKIO_SIG, 0, 1, 2, 384, 0 },

  { 193, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Sum1", 0, "",
    offsetof(BlockIO_modell, Sum1_h), BLOCKIO_SIG, 0, 1, 2, 386, 0 },

  { 194,
    "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Math Function", 0,
    "", offsetof(BlockIO_modell, MathFunction_i), BLOCKIO_SIG, 0, 1, 2, 388, 0 },

  { 195, "modell/DP controller/DP controller/[-inf inf] to [-pi pi]/Sum", 0, "",
    offsetof(BlockIO_modell, Sum_nl), BLOCKIO_SIG, 0, 1, 2, 390, 0 },

  { 196,
    "modell/DP controller/DP controller/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_modell, Row1_e), BLOCKIO_SIG, 0, 1, 2, 392, 0 },

  { 197,
    "modell/DP controller/DP controller/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_modell, Row2_o), BLOCKIO_SIG, 0, 1, 2, 394, 0 },

  { 198,
    "modell/DP controller/DP controller/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_modell, Row3_g), BLOCKIO_SIG, 0, 1, 2, 396, 0 },

  { 199, "modell/DP controller/DP controller/Kp", 0, "", offsetof(BlockIO_modell,
    Kp), BLOCKIO_SIG, 17, 3, 2, 398, 0 },

  { 200, "modell/DP controller/DP controller/Product", 0, "", offsetof
    (BlockIO_modell, Product_l), BLOCKIO_SIG, 17, 3, 2, 400, 0 },

  { 201, "modell/DP controller/DP controller/Product1", 0, "", offsetof
    (BlockIO_modell, Product1_j), BLOCKIO_SIG, 17, 3, 2, 402, 0 },

  { 202, "modell/DP controller/DP controller/Product2", 0, "", offsetof
    (BlockIO_modell, Product2), BLOCKIO_SIG, 17, 3, 2, 404, 0 },

  { 203, "modell/DP controller/DP controller/Sum3", 0, "", offsetof
    (BlockIO_modell, Sum3_d), BLOCKIO_SIG, 17, 3, 2, 406, 0 },

  { 204, "modell/DP controller/DP controller/Sum1", 0, "", offsetof
    (BlockIO_modell, Sum1_hw), BLOCKIO_SIG, 17, 3, 2, 408, 0 },

  { 205, "modell/Manual Thruster Control/U1", 0, "", offsetof(BlockIO_modell, U1),
    BLOCKIO_SIG, 0, 1, 2, 410, 0 },

  { 206, "modell/Manual Thruster Control/U2", 0, "", offsetof(BlockIO_modell, U2),
    BLOCKIO_SIG, 0, 1, 2, 412, 0 },

  { 207, "modell/Manual Thruster Control/U3", 0, "", offsetof(BlockIO_modell, U3),
    BLOCKIO_SIG, 0, 1, 2, 414, 0 },

  { 208, "modell/Manual Thruster Control/U4", 0, "", offsetof(BlockIO_modell, U4),
    BLOCKIO_SIG, 0, 1, 2, 416, 0 },

  { 209, "modell/Manual Thruster Control/Sum", 0, "", offsetof(BlockIO_modell,
    Sum_ej), BLOCKIO_SIG, 0, 1, 2, 418, 0 },

  { 210, "modell/Manual Thruster Control/U5", 0, "", offsetof(BlockIO_modell, U5),
    BLOCKIO_SIG, 0, 1, 2, 420, 0 },

  { 211, "modell/Thruster Control/Product1", 0, "", offsetof(BlockIO_modell,
    Product1_o), BLOCKIO_SIG, 23, 5, 2, 422, 0 },

  { 212, "modell/Thruster Control/Saturation", 0, "", offsetof(BlockIO_modell,
    Saturation_a), BLOCKIO_SIG, 23, 5, 2, 424, 0 },

  { 213, "modell/ctc/Compare", 0, "", offsetof(BlockIO_modell, Compare),
    BLOCKIO_SIG, 3, 1, 2, 426, 0 },

  { 214, "modell/HIL model/Rate Limiter Dynamic/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_modell, LowerRelop1), BLOCKIO_SIG, 8, 1, 2, 428, 0 },

  { 215, "modell/HIL model/Rate Limiter Dynamic/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_modell, UpperRelop), BLOCKIO_SIG, 8, 1, 2, 430, 0 },

  { 216, "modell/Towline/Towline dynamics/towing/In1", 0, "", offsetof
    (BlockIO_modell, towing.In1), BLOCKIO_SIG, 17, 3, 2, 432, 0 },

  { 217, "modell/Towline/Towline dynamics/rupture/In1", 0, "", offsetof
    (BlockIO_modell, rupture.In1), BLOCKIO_SIG, 17, 3, 2, 434, 0 },

  { 218, "modell/Towline/Towline dynamics/slack/In1", 0, "", offsetof
    (BlockIO_modell, slack.In1), BLOCKIO_SIG, 17, 3, 2, 436, 0 },

  { 219, "modell/PS3 Sixaxis/threshold block3/else/In1", 0, "", offsetof
    (BlockIO_modell, else_aj.In1), BLOCKIO_SIG, 0, 1, 2, 438, 0 },

  { 220, "modell/PS3 Sixaxis/threshold block3/if/In1", 0, "", offsetof
    (BlockIO_modell, if_k.In1), BLOCKIO_SIG, 0, 1, 2, 440, 0 },

  { 221, "modell/PS3 Sixaxis/threshold block2/else/In1", 0, "", offsetof
    (BlockIO_modell, else_d.In1), BLOCKIO_SIG, 0, 1, 2, 442, 0 },

  { 222, "modell/PS3 Sixaxis/threshold block2/if/In1", 0, "", offsetof
    (BlockIO_modell, if_i.In1), BLOCKIO_SIG, 0, 1, 2, 444, 0 },

  { 223, "modell/PS3 Sixaxis/threshold block1/else/In1", 0, "", offsetof
    (BlockIO_modell, else_a.In1), BLOCKIO_SIG, 0, 1, 2, 446, 0 },

  { 224, "modell/PS3 Sixaxis/threshold block1/if/In1", 0, "", offsetof
    (BlockIO_modell, if_f.In1), BLOCKIO_SIG, 0, 1, 2, 448, 0 },

  { 225, "modell/PS3 Sixaxis/threshold block/else/In1", 0, "", offsetof
    (BlockIO_modell, else_j.In1), BLOCKIO_SIG, 0, 1, 2, 450, 0 },

  { 226, "modell/PS3 Sixaxis/threshold block/if/In1", 0, "", offsetof
    (BlockIO_modell, if_j.In1), BLOCKIO_SIG, 0, 1, 2, 452, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3,
  1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3,
  1, 3, 1, 3, 1, 6, 1, 3, 1, 3, 1, 3, 1, 3, 1, 6, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 5, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 5, 5, 3, 1, 3, 1, 7, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 6, 1, 3, 1, 3, 1, 6, 1, 3, 1, 3, 1, 3, 1, 3,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3,
  1, 3, 1, 3, 1, 6, 1, 6, 1, 3, 1, 3, 1, 6, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3,
  1, 6, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 5, 1, 5, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize = 0;
static NI_ExternalIO NI_ExtList[] = {
  { -1, "", 0, 0, 0, 0, 0 }
};

/* This Task List is generated to allow access to the task specs without
 * initializing the model.
 * 0th entry is for scheduler (base rate)
 * rest for multirate model's tasks.
 */
NI_Task NI_TaskList[] = {
  { 0, 0.1, 0 }
};

int NI_NumTasks = 1;
int NIRT_ComputeNextCycleSampleHits(void)
{
  int retVal = 1+TID01EQ;              /* TID zero is always a sample hit, unless TID01EQ==1 */

#if defined(MULTITASKING)

  int i = 1;
  int tick, schedule_ticks;
  for (; i < NUMST-TID01EQ; ++i) {
    tick = S->Timing.TaskCounters.TID[i+TID01EQ] + 1;
    schedule_ticks = (int) ((NI_TaskList[i].tstep/NI_TaskList[0].tstep)+0.5);//Round to closest tick count
    if (tick == schedule_ticks)
      retVal |= (1 << (i+TID01EQ));
  }

#endif                                 /* defined(MULTITASKING) */

  return retVal;
}

static char* NI_CompiledModelName = "modell";
static char* NI_CompiledModelVersion = "1.149";
static char* NI_CompiledModelDateTime = "Tue Mar 12 15:06:47 2013";

/* Model Information Query fucntions for MATLAB
 */
/* dll information
 * Returns 1 for RTW DLL
 *		   2 for AutoCode DLL
 */
DLL_EXPORT long NIRT_GetBuildInfo(char* detail, long* len)
{
  static char* builder = "10.0.0 SIT RTW Build";

  //There are no console properties to set for VxWorks, because the console is simply serial output data.
  //Just do printf for VxWorks and ignore all console properties.
#ifndef VXWORKS

  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_BLUE |
    FOREGROUND_GREEN | FOREGROUND_RED);

#endif

  printf("\n*******************************************************************************\n");
  printf("%s\nModel Name: %s\nModel Version: %s\nCompiled On: %s",
         builder, NI_CompiledModelName, NI_CompiledModelVersion,
         NI_CompiledModelDateTime);
  printf("\n*******************************************************************************\n");

#ifndef VXWORKS

  SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN |
    FOREGROUND_RED);

#endif

  if (*len>=(long)strlen(builder))
    *len = strlen(builder)+1;
  strncpy(detail,builder,*len);
  return 1;
}

/*
 * Distinction between Index and ID:
 * Index is a long datatype (used to set parameter/probe signals).
 * ID on the other hand is a string (tag "2-3-2-12" for MatrixX/ Full path "f14/Gain/Gain" for Matlab).
 * NOTE: ID may not be the same as Paramname or signal name.
 */

/* signal information
   NOTE: signal ID == the blockname and port that feeds it.

   The port number in Simulation Environment is 1 indexed.. but on RT is 0 indexed.
 */
DLL_EXPORT long NIRT_GetSignalSpec(long* sidx, char* ID, long* ID_len, char
  * blkname, long *bnlen,
  long *portnum, char* signame, long *snlen, long *dattype, long* dims, long
  * numdim)
{
  long sigidx = *sidx;
  int i = 0;
  char *IDblk = 0;
  int IDport = 0;
  if (sigidx<0) {
    // check if ID has been specified.
    if (ID && *ID_len>0) {
      // parse ID into blkname and port
      i = strrchr(ID, ':') - ID;

      // malformed ID
      if (i<=0)
        return NI_SigListSize;
      ID[i] = 0;
      IDblk = ID;
      IDport = atoi(ID+i+1);

      // lookup the table for matching ID
      for (i=0;i<NI_SigListSize;i++) {
        if (!strcmp(IDblk,NI_SigList[i].blockname) && IDport==(NI_SigList[i].
             portno+1))
          break;
      }

      if (i<NI_SigListSize)
        sigidx = *sidx = i;
      else
        return NI_SigListSize;
    } else                             // no index or ID specified.
      return NI_SigListSize;
  }

  if (sigidx>=0 && sigidx<NI_SigListSize) {
    if (ID) {
      // no need for return string to be null terminated!
      // 10 to accomodate ':', port number and null character
      char *tempID = (char *)calloc(strlen(NI_SigList[sigidx].blockname) + 10,
        sizeof(char));
      sprintf(tempID,"%s:%d",NI_SigList[sigidx].blockname,NI_SigList[sigidx].
              portno+1);
      if ((long)strlen(tempID)<*ID_len)
        *ID_len = strlen(tempID);
      strncpy(ID, tempID, *ID_len);
      free(tempID);
    }

    if (blkname) {
      // no need for return string to be null terminated!
      if ((long)strlen(NI_SigList[sigidx].blockname)<*bnlen)
        *bnlen = strlen(NI_SigList[sigidx].blockname);
      strncpy(blkname, NI_SigList[sigidx].blockname, *bnlen);
    }

    if (signame) {
      // no need for return string to be null terminated!
      if ((long)strlen(NI_SigList[sigidx].signalname)<*snlen)
        *snlen = strlen(NI_SigList[sigidx].signalname);
      strncpy(signame, NI_SigList[sigidx].signalname, *snlen);
    }

    if (portnum)
      *portnum = NI_SigList[sigidx].portno;
    if (dattype)
      *dattype = NI_SigList[sigidx].datatype;
    if (dims && *numdim>=NI_SigList[sigidx].numofdims) {
      *numdim = NI_SigList[sigidx].numofdims;
      for (i=0;i < *numdim; i++)
        dims[i] = NI_SigDimList[NI_SigList[sigidx].dimListOffset +i];
    } else
      *numdim = 0;                     // set numdim to 0 to indicate that no enough memory to return the info.
    return 0;
  }

  return NI_SigListSize;
}

/*
 * Get parameter indices
 */
DLL_EXPORT long NIRT_GetParameterIndices(long* indices, long* len)
{
  long i;
  for (i=0;i<NI_ParamListSize && i<*len;i++)
    indices[i] = NI_ParamList[i].idx;
  *len = i;
  return NI_OK;
}

/*
 * parameter information
 *
 * if *pidx < 0, Lookup parameter by ID if ID != NULL.
 * if ID == NULL or no matching ID found, return number of parameters.
 *
 * plen  -> size of path
 * pnlen -> size of paramname
 * numdim -> size of dims array
 */
DLL_EXPORT long NIRT_GetParameterSpec(long* pidx, char* ID, long* ID_len, char
  * paramname, long *pnlen,
  long *dattype, long* dims, long* numdim)
{
  int i= 0;
  int paramidx = *pidx;
  if (paramidx<0) {
    // check if ID has been specified.
    if (ID && *ID_len>0) {
      // lookup the table for matching ID
      for (i=0;i<NI_ParamListSize;i++) {
        if (!strcmp(ID,NI_ParamList[i].paramname))
          break;
      }

      if (i<NI_ParamListSize)
        paramidx = *pidx = i;
      else
        return NI_ParamListSize;
    } else                             // no index or ID specified.
      return NI_ParamListSize;
  }

  if (paramidx>=0 && paramidx<NI_ParamListSize) {
    if (ID) {
      if ((long)strlen(NI_ParamList[paramidx].paramname)<*ID_len)
        *ID_len = strlen(NI_ParamList[paramidx].paramname);
      strncpy(ID, NI_ParamList[paramidx].paramname, *ID_len);
    }

    if (paramname) {
      // no need for return string to be null terminated!
      if ((long)strlen(NI_ParamList[paramidx].paramname)<*pnlen)
        *pnlen = strlen(NI_ParamList[paramidx].paramname);
      strncpy(paramname, NI_ParamList[paramidx].paramname, *pnlen);
    }

    if (dattype)
      *dattype = NI_ParamList[paramidx].datatype;
    if (!numdim)
      return 0;
    if (*numdim>=NI_ParamList[paramidx].numofdims) {
      *numdim = NI_ParamList[paramidx].numofdims;
      for (i=0;i < *numdim; i++)
        dims[i] = NI_ParamDimList[NI_ParamList[paramidx].dimListOffset +i];
    } else
      *numdim = 0;                     // set numdim to 0 to indicate that no enough memory to return the info.
    return 0;
  }

  return NI_ParamListSize;
}

/*
 * parameter expression information
 * If paramidx is outside of limit returns number of parameters, else 0.
 *
 * explen  -> size of expression
 */
DLL_EXPORT long NIRT_GetParameterExpression(long paramidx, char* expression,
  long *exp_len)
{
  if (paramidx>=0 && paramidx<NI_ParamListSize) {//If paramidx is valid then get expression
    if (expression && exp_len) {       //Make sure expression and exp_len are defined (don't point to NULL)
      if ((long)strlen(NI_ParamList[paramidx].expression)<*exp_len)
        *exp_len = strlen(NI_ParamList[paramidx].expression);
      strncpy(expression, NI_ParamList[paramidx].expression, *exp_len);//Copy string up to exp_len or actual expression length
    }

    return 0;
  }

  if (exp_len)
    *exp_len = 0;
  return NI_ParamListSize;
}

/*
 * variables information
 * If paramidx is outside of limit returns number of variables in list, else 0.
 *
 * varlen  -> size of variable name
 */
DLL_EXPORT long NIRT_GetVariableName(long varidx, char* variable_name, long
  *var_len)
{
  if (varidx>=0 && varidx<NI_VariablesListSize) {//If varidx is in valid range then get variable name
    if (variable_name && var_len) {    //Make sure variable name and var_len are defined (don't point to NULL
      if ((long)strlen(NI_VariablesList[varidx])<*var_len)
        *var_len = strlen(NI_VariablesList[varidx]);
      strncpy(variable_name, NI_VariablesList[varidx], *var_len);//Copy string up to var_len or actual variable length (which ever is shorter)
    }

    return 0;
  }

  if (var_len)
    *var_len = 0;
  return NI_VariablesListSize;
}

/*
 * NIRT_GetExtIOSpec
 *
 * Inputs:
 *		index: index of the task
 * Outputs:
 *		idx:  idx of the IO.
 *		name: Name of the IO block
 *		tid: task id
 *		type: EXT_IN or EXT_OUT
 *		dimX: size of 0th dimension
 *		dimY: size of 1th dimension
 * Return value: 0 if no error. (if index == -1, return number of tasks in the model)
 */
DLL_EXPORT long NIRT_GetExtIOSpec(long index, long *idx, char* name, long* tid,
  long *type, long *dims, long* numdims)
{
  if (index==-1)
    return NI_ExtListSize;
  if (idx)
    *idx = NI_ExtList[index].idx;
  if (name) {
    int sz = strlen(name);
    strncpy(name, NI_ExtList[index].name, sz-1);
    name[sz-1]= 0;
  }

  if (tid)
    *tid = NI_ExtList[index].TID;
  if (type)
    *type = NI_ExtList[index].type;
  if (numdims && dims) {
    if (*numdims>=2) {
      *numdims= 2;
      dims[0] = NI_ExtList[index].dimX;
      dims[1] = NI_ExtList[index].dimY;
    } else
      *numdims= 0;
  }

  return 0;
}

/* Helper function to probe one	signal. baseaddr must NOT be VIRTUAL_SIG */
static long NI_ProbeOneSignal(long idx, double *value, long len, long *count,
  long vOffset, long vLength)
{
  char *ptr = (char*)((NI_SigList[idx].baseaddr == BLOCKIO_SIG) ?
                      S->ModelData.blockIO : S->ModelData.inputs ) + (int)
    NI_SigList[idx].addr;
  long subindex = (vLength == -1) ? 0 : vOffset;
  long sublength = (vLength == -1) ? NI_SigList[idx].width : (vLength + vOffset);
  while ((subindex < sublength) && (*count < len))
    value[(*count)++] = NIRT_GetValueByDataType(ptr, subindex++, NI_SigList[idx]
      .datatype, NI_SigList[idx].IsComplex);
  return *count;
}

/*
 * NIRT_ProbeSignals
 *
 * Inputs:
 *		sigindices: indeces of signals
 *		numsigs: number of signals
 *		len: total length of all signals
 * Outputs:
 *		value: probed signal data
 *		len: length of data (may vary from input)
 * Return value: equal to len
 */
DLL_EXPORT long NIRT_ProbeSignals(long* sigindices, long numsigs,
  double* value, long* len)
{
  int i, j, count = 0, idx;
  if (!SITexportglobals.inCriticalSection)
    SetSITErrorMessage("SignalProbe should only be called between ScheduleTasks and PostOutputs",
                       1);
  if ((*len > 1) && (numsigs > 0)) {
    value[count++] = sigindices[0];
    value[count++] = 0;
  }

  for (i = 1; (i < numsigs) && (count < *len); i++) {
    idx = sigindices[i];
    if (idx < 0)
      break;
    if (idx < NI_SigListSize) {
      if (NI_SigList[idx].baseaddr == VIRTUAL_SIG) {
        for (j = 0; j < 0; j++) {
          long vidx = NI_VirtualBlockSources[NI_SigList[idx].addr][j];
          long voff = NI_VirtualBlockOffsets[NI_SigList[idx].addr][j];
          long vlen = NI_VirtualBlockLengths[NI_SigList[idx].addr][j];
          if (vidx == -1)
            break;
          NI_ProbeOneSignal(vidx, value, *len, &count, voff, vlen);
        }
      } else
        NI_ProbeOneSignal(idx, value, *len, &count, 0, -1);
    }
  }

  *len = count;
  return count;
}

/* Copy the	statically initialized params into our copy of the param struct
   The undef allows us to access the real modell_P
   In the rest of the code modell_P is redefine to be the read-side
   of rtParameter.
 */
#undef modell_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &modell_P, sizeof(Parameters_modell));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka modell_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_modell));
  return NI_OK;
}

static int NI_SetParamTxStatus = NI_OK;

// This function is called by the BGL to set parameters.  When a commit is requested (index < 0),
// the code enters a critical section shared with the TCL. This ensures that the flip occurs only
// when safe, and acts as a messaging scheme for us to copy back the parameters.
DLL_EXPORT long NIRT_SetParameter(long index, long subindex, double value)
{
  char* ptr = NULL;
  if (index>=NI_ParamListSize)
    return NI_SetParamTxStatus= NI_ERROR;
  if (index < 0) {
    if (NI_SetParamTxStatus==NI_ERROR) {
      // fail the transaction.
      // copy old	list of parameters to the failed TX buffer
      memcpy(&rtParameter[READSIDE], &rtParameter[1-READSIDE], sizeof
             (Parameters_modell));

      // reset the status.
      NI_SetParamTxStatus = NI_OK;
      return NI_ERROR;
    }

    // commit changes
    S->ModelData.defaultParam = (double *)&rtParameter[1-READSIDE];
    WaitForSingleObject(SITexportglobals.flipCriticalSection, INFINITE);
    READSIDE = 1 - READSIDE;
    SITexportglobals.copyTaskBitfield = 0xFFFFFFFF;
    ReleaseSemaphore(SITexportglobals.flipCriticalSection, 1, NULL);

    // Copy back the newly set parameters to the writeside.
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (Parameters_modell));
    return NI_OK;
  }

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width)
    return NI_SetParamTxStatus= NI_ERROR;
  ptr = (char *)(&rtParameter[1-READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  return NIRT_SetValueByDataType(ptr,subindex,value,NI_ParamList[index].datatype,
    NI_ParamList[index].IsComplex);
}

DLL_EXPORT long NIRT_GetParameter(long index, long subindex, double *value)
{
  char* ptr = NULL;
  if (index>=NI_ParamListSize || index < 0)
    return NI_ERROR;

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width)
    return NI_ERROR;
  ptr = (char *)(&rtParameter[READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  *value = NIRT_GetValueByDataType(ptr,subindex,NI_ParamList[index].datatype,
    NI_ParamList[index].IsComplex);
  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_modell
