/*
 * ctrl_student.c
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

/* Block signals (auto storage) */
B_ctrl_student_T ctrl_student_B;

/* Continuous states */
X_ctrl_student_T ctrl_student_X;

/* Block states (auto storage) */
DW_ctrl_student_T ctrl_student_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_ctrl_student_T ctrl_student_PrevZCX;

/* Real-time model */
RT_MODEL_ctrl_student_T ctrl_student_M_;
RT_MODEL_ctrl_student_T *const ctrl_student_M = &ctrl_student_M_;

/* Forward declaration for local functions */
static void ctrl_student_mldivide(const real_T A[9], const real_T B[3], real_T
  Y[3]);

/*
 * This function updates continuous states using the ODE4 fixed-step
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
  int_T nXc = 9;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  ctrl_student_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  ctrl_student_output();
  ctrl_student_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  ctrl_student_output();
  ctrl_student_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  ctrl_student_output();
  ctrl_student_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Function for MATLAB Function: '<Root>/Thrust allocation' */
static void ctrl_student_mldivide(const real_T A[9], const real_T B[3], real_T
  Y[3])
{
  real_T b_A[9];
  int32_T r1;
  int32_T r2;
  int32_T r3;
  real_T maxval;
  real_T a21;
  int32_T rtemp;
  memcpy(&b_A[0], &A[0], 9U * sizeof(real_T));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(A[0]);
  a21 = fabs(A[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(A[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] = A[r2] / A[r1];
  b_A[r3] /= b_A[r1];
  b_A[3 + r2] -= b_A[3 + r1] * b_A[r2];
  b_A[3 + r3] -= b_A[3 + r1] * b_A[r3];
  b_A[6 + r2] -= b_A[6 + r1] * b_A[r2];
  b_A[6 + r3] -= b_A[6 + r1] * b_A[r3];
  if (fabs(b_A[3 + r3]) > fabs(b_A[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b_A[3 + r3] /= b_A[3 + r2];
  b_A[6 + r3] -= b_A[3 + r3] * b_A[6 + r2];
  Y[1] = B[r2] - B[r1] * b_A[r2];
  Y[2] = (B[r3] - B[r1] * b_A[r3]) - b_A[3 + r3] * Y[1];
  Y[2] /= b_A[6 + r3];
  Y[0] = B[r1] - b_A[6 + r1] * Y[2];
  Y[1] -= b_A[6 + r2] * Y[2];
  Y[1] /= b_A[3 + r2];
  Y[0] -= b_A[3 + r1] * Y[1];
  Y[0] /= b_A[r1];
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T u1_0;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    y = (rtNaN);
  } else {
    if (u1 < 0.0) {
      u1_0 = ceil(u1);
    } else {
      u1_0 = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != u1_0)) {
      u1_0 = u0 / u1;
      if (fabs(u1_0 - rt_roundd_snf(u1_0)) <= DBL_EPSILON * fabs(u1_0)) {
        y = 0.0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

/* Model output function */
void ctrl_student_output(void)
{
  real_T u[3];
  static const real_T b[9] = { 1.165, 0.0, 0.0, 0.0, 1.165, 0.0, 0.0, 0.0, 2.629
  };

  static const real_T c[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, -0.4575, 0.0, 1.0,
    0.3875 };

  real_T tau[3];
  static const real_T a[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, -0.4575, 0.0, 1.0,
    0.3875 };

  real_T D_NL[9];
  real_T t3;
  real_T x[9];
  real_T C_NL[9];
  real_T rtb_Fcn;
  real_T rtb_Row1_h;
  real_T rtb_psi_dot;
  real_T rtb_Row2;
  real_T rtb_Row3;
  int32_T i;
  real_T tmp[3];
  real_T tau_0[3];
  real_T rtb_Row1_l[3];
  real_T rtb_Row1_l_0[3];
  real_T rtb_Product_idx_0;
  real_T rtb_Product_idx_1;
  real_T rtb_Product_idx_2;
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    /* set solver stop time */
    if (!(ctrl_student_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&ctrl_student_M->solverInfo,
                            ((ctrl_student_M->Timing.clockTickH0 + 1) *
        ctrl_student_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&ctrl_student_M->solverInfo,
                            ((ctrl_student_M->Timing.clockTick0 + 1) *
        ctrl_student_M->Timing.stepSize0 + ctrl_student_M->Timing.clockTickH0 *
        ctrl_student_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(ctrl_student_M)) {
    ctrl_student_M->Timing.t[0] = rtsiGetT(&ctrl_student_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    /* MATLAB Function: '<Root>/Thrust allocation' incorporates:
     *  Constant: '<Root>/Constant'
     */
    /* MATLAB Function 'Thrust allocation': '<S3>:1' */
    /*  Forces and moments vector */
    /* '<S3>:1:4' */
    /*  Extended thrust configuration matrix */
    /*  Extended thrust coefficient matrix */
    /*  tau = T*K*u inverse */
    /* '<S3>:1:23' */
    tau[0] = 0.0;
    tau[1] = 0.0;
    tau[2] = 0.0;
    ctrl_student_mldivide(c, tau, rtb_Row1_l_0);
    ctrl_student_mldivide(b, rtb_Row1_l_0, u);

    /* '<S3>:1:25' */
    /* '<S3>:1:27' */
    /* '<S3>:1:28' */
    /* '<S3>:1:29' */
    /* '<S3>:1:30' */
    if (ctrl_student_P.Constant_Value != 0.0) {
      /* '<S3>:1:33' */
      ctrl_student_B.omega_VSP = 0.3;
    } else {
      /* '<S3>:1:35' */
      ctrl_student_B.omega_VSP = 0.0;
    }

    ctrl_student_B.u_BT = u[2];
    ctrl_student_B.u_VSP = sqrt(u[0] * u[0] + u[1] * u[1]);
    ctrl_student_B.alpha_VSP = rt_atan2d_snf(u[1], u[0]);

    /* End of MATLAB Function: '<Root>/Thrust allocation' */

    /* MATLAB Function: '<Root>/control limit checking' incorporates:
     *  SignalConversion: '<S4>/TmpSignal ConversionAt SFunction Inport1'
     */
    /* MATLAB Function 'control limit checking': '<S4>:1' */
    /* '<S4>:1:2' */
    /* '<S4>:1:3' */
    /* '<S4>:1:5' */
    /* '<S4>:1:6' */
    /* '<S4>:1:7' */
    /* '<S4>:1:8' */
    /* '<S4>:1:10' */
    /* '<S4>:1:18' */
    ctrl_student_B.fault = !((-1.0 <= ctrl_student_B.u_BT) &&
      (ctrl_student_B.u_BT <= 1.0) && (0.0 <= ctrl_student_B.u_VSP) &&
      (ctrl_student_B.u_VSP <= 1.0) && (0.0 <= ctrl_student_B.u_VSP) &&
      (ctrl_student_B.u_VSP <= 2.0) && (-3.1415926535897931 <=
      ctrl_student_B.alpha_VSP) && (ctrl_student_B.alpha_VSP <=
      3.1415926535897931) && (-3.1415926535897931 <= ctrl_student_B.alpha_VSP) &&
                             (ctrl_student_B.alpha_VSP <= 3.1415926535897931) &&
                             (-1.0 <= ctrl_student_B.omega_VSP) &&
      (ctrl_student_B.omega_VSP <= 1.0) && (-1.0 <= ctrl_student_B.omega_VSP) &&
                             (ctrl_student_B.omega_VSP <= 1.0));
  }

  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    /* Delay: '<S1>/Delay' incorporates:
     *  SignalConversion: '<S1>/TmpSignal ConversionAtDelayInport2'
     */
    if (ctrl_student_DW.icLoad != 0) {
      ctrl_student_DW.Delay_DSTATE[0] = ctrl_student_B.x_m;
      ctrl_student_DW.Delay_DSTATE[1] = ctrl_student_B.y_m;
      ctrl_student_DW.Delay_DSTATE[2] = ctrl_student_B.psi_m;
    }

    ctrl_student_B.Delay[0] = ctrl_student_DW.Delay_DSTATE[0];
    ctrl_student_B.Delay[1] = ctrl_student_DW.Delay_DSTATE[1];
    ctrl_student_B.Delay[2] = ctrl_student_DW.Delay_DSTATE[2];

    /* End of Delay: '<S1>/Delay' */
  }

  /* MATLAB Function: '<S1>/Low pass filter' incorporates:
   *  Constant: '<S1>/Low pass Gain 1'
   *  SignalConversion: '<S9>/TmpSignal ConversionAt SFunction Inport2'
   */
  /* MATLAB Function 'Derivative filter/Low pass filter': '<S9>:1' */
  /* '<S9>:1:3' */
  ctrl_student_B.eta_filtered[0] = (1.0 - ctrl_student_P.LowpassGain1_Value) *
    ctrl_student_B.Delay[0] + ctrl_student_P.LowpassGain1_Value *
    ctrl_student_B.x_m;
  ctrl_student_B.eta_filtered[1] = (1.0 - ctrl_student_P.LowpassGain1_Value) *
    ctrl_student_B.Delay[1] + ctrl_student_P.LowpassGain1_Value *
    ctrl_student_B.y_m;
  ctrl_student_B.eta_filtered[2] = (1.0 - ctrl_student_P.LowpassGain1_Value) *
    ctrl_student_B.Delay[2] + ctrl_student_P.LowpassGain1_Value *
    ctrl_student_B.psi_m;

  /* MATLAB Function 'Derivative filter/Discrete derivative': '<S8>:1' */
  /* '<S8>:1:3' */
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    /* Memory: '<S1>/Memory3' */
    ctrl_student_B.Memory3[0] = ctrl_student_DW.Memory3_PreviousInput[0];
    ctrl_student_B.Memory3[1] = ctrl_student_DW.Memory3_PreviousInput[1];
    ctrl_student_B.Memory3[2] = ctrl_student_DW.Memory3_PreviousInput[2];
  }

  /* MATLAB Function: '<S1>/Low pass filter 2' incorporates:
   *  Constant: '<S1>/Low pass Gain 2'
   *  Constant: '<S1>/sample time'
   *  MATLAB Function: '<S1>/Discrete derivative'
   */
  /* MATLAB Function 'Derivative filter/Low pass filter 2': '<S10>:1' */
  /* '<S10>:1:3' */
  ctrl_student_B.eta_dot_filtered[0] = (ctrl_student_B.eta_filtered[0] -
    ctrl_student_B.Delay[0]) / ctrl_student_P.sampletime_Value *
    ctrl_student_P.LowpassGain2_Value + (1.0 - ctrl_student_P.LowpassGain2_Value)
    * ctrl_student_B.Memory3[0];
  ctrl_student_B.eta_dot_filtered[1] = (ctrl_student_B.eta_filtered[1] -
    ctrl_student_B.Delay[1]) / ctrl_student_P.sampletime_Value *
    ctrl_student_P.LowpassGain2_Value + (1.0 - ctrl_student_P.LowpassGain2_Value)
    * ctrl_student_B.Memory3[1];
  ctrl_student_B.eta_dot_filtered[2] = (ctrl_student_B.eta_filtered[2] -
    ctrl_student_B.Delay[2]) / ctrl_student_P.sampletime_Value *
    ctrl_student_P.LowpassGain2_Value + (1.0 - ctrl_student_P.LowpassGain2_Value)
    * ctrl_student_B.Memory3[2];

  /* MATLAB Function: '<S1>/Rotation matrix' incorporates:
   *  Fcn: '<S1>/Fcn'
   */
  /* MATLAB Function 'Derivative filter/Rotation matrix': '<S11>:1' */
  /* '<S11>:1:3' */
  /* '<S11>:1:6' */
  D_NL[0] = cos(ctrl_student_B.psi_m);
  D_NL[3] = sin(ctrl_student_B.psi_m);
  D_NL[6] = 0.0;
  D_NL[1] = -sin(ctrl_student_B.psi_m);
  D_NL[4] = cos(ctrl_student_B.psi_m);
  D_NL[7] = 0.0;
  D_NL[2] = 0.0;
  D_NL[5] = 0.0;
  D_NL[8] = 1.0;
  for (i = 0; i < 3; i++) {
    ctrl_student_B.nu[i] = 0.0;
    ctrl_student_B.nu[i] += D_NL[i] * ctrl_student_B.eta_dot_filtered[0];
    ctrl_student_B.nu[i] += D_NL[i + 3] * ctrl_student_B.eta_dot_filtered[1];
    ctrl_student_B.nu[i] += D_NL[i + 6] * ctrl_student_B.eta_dot_filtered[2];
  }

  /* End of MATLAB Function: '<S1>/Rotation matrix' */
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    /* Memory: '<S1>/Memory2' */
    ctrl_student_B.Memory2[0] = ctrl_student_DW.Memory2_PreviousInput[0];
    ctrl_student_B.Memory2[1] = ctrl_student_DW.Memory2_PreviousInput[1];
    ctrl_student_B.Memory2[2] = ctrl_student_DW.Memory2_PreviousInput[2];

    /* Memory: '<S1>/Memory1' */
    ctrl_student_B.Memory1[0] = ctrl_student_DW.Memory1_PreviousInput[0];
    ctrl_student_B.Memory1[1] = ctrl_student_DW.Memory1_PreviousInput[1];
    ctrl_student_B.Memory1[2] = ctrl_student_DW.Memory1_PreviousInput[2];
  }

  /* MATLAB Function: '<S1>/Differentiate and filter1' */
  /* MATLAB Function 'Derivative filter/Differentiate and filter1': '<S7>:1' */
  /*  derivative */
  /* '<S7>:1:5' */
  ctrl_student_B.nu_dot[0] = (ctrl_student_B.nu[0] - ctrl_student_B.Memory2[0]) /
    0.01;
  ctrl_student_B.nu_dot[1] = (ctrl_student_B.nu[1] - ctrl_student_B.Memory2[1]) /
    0.01;
  ctrl_student_B.nu_dot[2] = (ctrl_student_B.nu[2] - ctrl_student_B.Memory2[2]) /
    0.01;

  /*  filter */
  /* '<S7>:1:9' */
  ctrl_student_B.nu_dot[0] = 0.01 * ctrl_student_B.nu_dot[0] + 0.99 *
    ctrl_student_B.Memory1[0];
  ctrl_student_B.nu_dot[1] = 0.01 * ctrl_student_B.nu_dot[1] + 0.99 *
    ctrl_student_B.Memory1[1];
  ctrl_student_B.nu_dot[2] = 0.01 * ctrl_student_B.nu_dot[2] + 0.99 *
    ctrl_student_B.Memory1[2];

  /* Integrator: '<S2>/Integrator2' */
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                       &ctrl_student_PrevZCX.Integrator2_Reset_ZCE,
                       ctrl_student_B.reset);

    /* evaluate zero-crossings */
    if (zcEvent) {
      ctrl_student_X.Integrator2_CSTATE[0] = (ctrl_student_P.Integrator2_IC[0]);
      ctrl_student_X.Integrator2_CSTATE[1] = (ctrl_student_P.Integrator2_IC[1]);
      ctrl_student_X.Integrator2_CSTATE[2] = (ctrl_student_P.Integrator2_IC[2]);
    }
  }

  ctrl_student_B.Integrator2[0] = ctrl_student_X.Integrator2_CSTATE[0];
  ctrl_student_B.Integrator2[1] = ctrl_student_X.Integrator2_CSTATE[1];
  ctrl_student_B.Integrator2[2] = ctrl_student_X.Integrator2_CSTATE[2];

  /* Integrator: '<S2>/Integrator' */
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                       &ctrl_student_PrevZCX.Integrator_Reset_ZCE,
                       ctrl_student_B.reset);

    /* evaluate zero-crossings */
    if (zcEvent || ctrl_student_DW.Integrator_IWORK.IcNeedsLoading) {
      ctrl_student_X.Integrator_CSTATE[0] = ctrl_student_B.x_m;
      ctrl_student_X.Integrator_CSTATE[1] = ctrl_student_B.y_m;
      ctrl_student_X.Integrator_CSTATE[2] = ctrl_student_B.psi_m;
    }
  }

  ctrl_student_B.Integrator[0] = ctrl_student_X.Integrator_CSTATE[0];
  ctrl_student_B.Integrator[1] = ctrl_student_X.Integrator_CSTATE[1];
  ctrl_student_B.Integrator[2] = ctrl_student_X.Integrator_CSTATE[2];

  /* Saturate: '<S23>/Saturation' */
  if (ctrl_student_B.Integrator[2] > ctrl_student_P.Saturation_UpperSat) {
    rtb_Row1_h = ctrl_student_P.Saturation_UpperSat;
  } else if (ctrl_student_B.Integrator[2] < ctrl_student_P.Saturation_LowerSat)
  {
    rtb_Row1_h = ctrl_student_P.Saturation_LowerSat;
  } else {
    rtb_Row1_h = ctrl_student_B.Integrator[2];
  }

  /* End of Saturate: '<S23>/Saturation' */

  /* Signum: '<S23>/Sign' */
  if (rtb_Row1_h < 0.0) {
    rtb_Fcn = -1.0;
  } else if (rtb_Row1_h > 0.0) {
    rtb_Fcn = 1.0;
  } else if (rtb_Row1_h == 0.0) {
    rtb_Fcn = 0.0;
  } else {
    rtb_Fcn = rtb_Row1_h;
  }

  /* Gain: '<S23>/Gain' incorporates:
   *  Signum: '<S23>/Sign'
   */
  rtb_psi_dot = ctrl_student_P.Gain_Gain * rtb_Fcn;

  /* Sum: '<S23>/Sum1' */
  rtb_Row1_h += rtb_psi_dot;

  /* Math: '<S23>/Math Function' incorporates:
   *  Constant: '<S23>/Constant'
   */
  rtb_Row1_h = rt_remd_snf(rtb_Row1_h, ctrl_student_P.Constant_Value_c);

  /* Sum: '<S23>/Sum' */
  ctrl_student_B.Sum = rtb_Row1_h - rtb_psi_dot;

  /* Fcn: '<S2>/Fcn' */
  rtb_psi_dot = ctrl_student_B.psi_m;

  /* Fcn: '<S22>/Row1' incorporates:
   *  Fcn: '<S2>/Fcn'
   */
  rtb_Row1_h = cos(ctrl_student_B.psi_m) * ctrl_student_B.Integrator2[0] + sin
    (ctrl_student_B.psi_m) * ctrl_student_B.Integrator2[1];

  /* Fcn: '<S22>/Row2' incorporates:
   *  Fcn: '<S2>/Fcn'
   */
  rtb_Row2 = -sin(ctrl_student_B.psi_m) * ctrl_student_B.Integrator2[0] + cos
    (ctrl_student_B.psi_m) * ctrl_student_B.Integrator2[1];

  /* Fcn: '<S22>/Row3' */
  rtb_Row3 = ctrl_student_B.Integrator2[2];

  /* Sum: '<S2>/Sum' */
  u[0] = ctrl_student_B.x_m - ctrl_student_B.Integrator[0];
  u[1] = ctrl_student_B.y_m - ctrl_student_B.Integrator[1];
  u[2] = ctrl_student_B.psi_m - ctrl_student_B.Sum;

  /* Product: '<S2>/Product2' */
  rtb_Product_idx_0 = ctrl_student_B.K_4x * u[0];
  rtb_Product_idx_1 = ctrl_student_B.K_4y * u[1];
  rtb_Product_idx_2 = ctrl_student_B.K_4psi * u[2];

  /* Integrator: '<S2>/Integrator1' */
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                       &ctrl_student_PrevZCX.Integrator1_Reset_ZCE,
                       ctrl_student_B.reset);

    /* evaluate zero-crossings */
    if (zcEvent) {
      ctrl_student_X.Integrator1_CSTATE[0] = (ctrl_student_P.Integrator1_IC[0]);
      ctrl_student_X.Integrator1_CSTATE[1] = (ctrl_student_P.Integrator1_IC[1]);
      ctrl_student_X.Integrator1_CSTATE[2] = (ctrl_student_P.Integrator1_IC[2]);
    }
  }

  ctrl_student_B.Integrator1[0] = ctrl_student_X.Integrator1_CSTATE[0];
  ctrl_student_B.Integrator1[1] = ctrl_student_X.Integrator1_CSTATE[1];
  ctrl_student_B.Integrator1[2] = ctrl_student_X.Integrator1_CSTATE[2];

  /* MATLAB Function: '<S30>/Bow thruster' */
  /* MATLAB Function 'Observer/u_2_tau/Thruster mapping/Bow thruster': '<S31>:1' */
  /* '<S31>:1:3' */
  /*  Thruster characteristics */
  if (ctrl_student_B.u_BT > 0.0879) {
    /* '<S31>:1:5' */
    /* '<S31>:1:10' */
    rtb_Fcn = exp(0.1174 * ctrl_student_B.u_BT) * 2.515 + exp(-1.131 *
      ctrl_student_B.u_BT) * -2.807;
  } else if (ctrl_student_B.u_BT < -0.059) {
    /* '<S31>:1:11' */
    /* '<S31>:1:16' */
    rtb_Fcn = exp(0.193 * ctrl_student_B.u_BT) * -548.0 + exp(0.1992 *
      ctrl_student_B.u_BT) * 548.2;
  } else {
    /* '<S31>:1:18' */
    rtb_Fcn = 0.0;
  }

  /*  Thruster losses due to forward speed */
  /* '<S31>:1:21' */
  /* '<S31>:1:24' */
  /* '<S31>:1:25' */
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    /* MATLAB Function: '<S30>/VSP' */
    /* MATLAB Function 'Observer/u_2_tau/Thruster mapping/VSP': '<S32>:1' */
    /*  Calculating the force in x-direction */
    /* '<S32>:1:6' */
    /* '<S32>:1:9' */
    /* '<S32>:1:12' */
    /* '<S32>:1:15' */
    /* '<S32>:1:18' */
    /* '<S32>:1:21' */
    /* '<S32>:1:22' */
    ctrl_student_B.F_x = (((((sin(1.001 * ctrl_student_B.alpha_VSP + 1.564) *
      1.107 + sin(0.1397 * ctrl_student_B.alpha_VSP + -1.599) * 0.3471) + sin
      (1.993 * ctrl_student_B.alpha_VSP + 1.886) * 0.1558) + sin(0.218 *
      ctrl_student_B.alpha_VSP + 1.513) * 0.1599) + sin(2.986 *
      ctrl_student_B.alpha_VSP + -1.601) * 0.08237) + sin(3.964 *
      ctrl_student_B.alpha_VSP + 1.738) * 0.04641) * ctrl_student_B.u_VSP;

    /*  Calculating the force in y-direction */
    /* '<S32>:1:31' */
    /* '<S32>:1:34' */
    /* '<S32>:1:37' */
    /* '<S32>:1:40' */
    /* '<S32>:1:43' */
    /* '<S32>:1:46' */
    /* '<S32>:1:47' */
    ctrl_student_B.F_y = (((((sin(1.001 * ctrl_student_B.alpha_VSP + 0.01605) *
      0.7936 + sin(1.997 * ctrl_student_B.alpha_VSP + 0.03229) * 0.2112) + sin
      (2.991 * ctrl_student_B.alpha_VSP + 2.986) * 0.07608) + sin(3.999 *
      ctrl_student_B.alpha_VSP + -0.8668) * 0.04817) + sin(4.904 *
      ctrl_student_B.alpha_VSP + -2.622) * 0.01757) + sin(5.068 *
      ctrl_student_B.alpha_VSP + 0.2548) * -0.02089) * ctrl_student_B.u_VSP;
  }

  /* MATLAB Function: '<S28>/Thruster configuration matrix' incorporates:
   *  MATLAB Function: '<S30>/Bow thruster'
   */
  /* MATLAB Function 'Observer/u_2_tau/Thruster configuration matrix': '<S29>:1' */
  /* '<S29>:1:7' */
  /* '<S29>:1:13' */
  rtb_Fcn = (atan(-10.22 * ctrl_student_B.Integrator1[0] + 2.947) * 0.3075 +
             0.7561) * rtb_Fcn / 1.1385;
  for (i = 0; i < 3; i++) {
    tau[i] = a[i + 6] * rtb_Fcn + (a[i + 3] * ctrl_student_B.F_y + a[i] *
      ctrl_student_B.F_x);
  }

  /* MATLAB Function: '<S2>/D(nu)*nu' */
  /* '<S29>:1:15' */
  /* '<S29>:1:16' */
  /* '<S29>:1:17' */
  /* MATLAB Function 'Observer/D(nu)*nu': '<S13>:1' */
  /* '<S13>:1:3' */
  /* '<S13>:1:4' */
  /* '<S13>:1:5' */
  /* '<S13>:1:7' */
  /* CTRL_STUDENT_OBSERVER_D */
  /*     D = CTRL_STUDENT_OBSERVER_D(U,V,R) */
  /*     This function was generated by the Symbolic Math Toolbox version 6.0. */
  /*     16-Dec-2015 15:38:25 */
  rtb_Fcn = fabs(ctrl_student_B.Integrator1[2]);
  t3 = fabs(ctrl_student_B.Integrator1[1]);
  x[0] = (ctrl_student_B.Integrator1[0] * ctrl_student_B.Integrator1[0] * 3.787
          + ctrl_student_B.Integrator1[0] * -0.3545) + 0.6555;
  x[1] = 0.0;
  x[2] = 0.0;
  x[3] = ctrl_student_B.Integrator1[1] * 2.443;
  x[4] = ((rtb_Fcn * 0.805 + ctrl_student_B.Integrator1[1] * 2.776) +
          ctrl_student_B.Integrator1[1] * ctrl_student_B.Integrator1[1] * 64.91)
    + 1.33;
  x[5] = rtb_Fcn * -0.13 + ctrl_student_B.Integrator1[1] * 0.2088;
  x[6] = 0.0;
  x[7] = (rtb_Fcn * 3.45 + t3 * 0.845) + 7.25;
  x[8] = (rtb_Fcn * 0.75 - t3 * 0.08) + 1.9;
  memcpy(&D_NL[0], &x[0], 9U * sizeof(real_T));

  /* MATLAB Function: '<S2>/C(nu)*nu' */
  /* '<S13>:1:9' */
  /* MATLAB Function 'Observer/C(nu)*nu': '<S12>:1' */
  /* '<S12>:1:3' */
  /* '<S12>:1:4' */
  /* '<S12>:1:5' */
  /* '<S12>:1:7' */
  /* CTRL_STUDENT_OBSERVER_C */
  /*     C = CTRL_STUDENT_OBSERVER_C(U,V,R) */
  /*     This function was generated by the Symbolic Math Toolbox version 6.0. */
  /*     16-Dec-2015 15:38:26 */
  rtb_Fcn = ctrl_student_B.Integrator1[0] * 16.79;
  x[0] = 0.0;
  x[1] = 0.0;
  x[2] = ctrl_student_B.Integrator1[2] * 0.554625 + ctrl_student_B.Integrator1[1]
    * 24.79;
  x[3] = 0.0;
  x[4] = 0.0;
  x[5] = -rtb_Fcn;
  x[6] = ctrl_student_B.Integrator1[2] * -0.554625 - ctrl_student_B.Integrator1
    [1] * 24.79;
  x[7] = rtb_Fcn;
  x[8] = 0.0;
  memcpy(&C_NL[0], &x[0], 9U * sizeof(real_T));

  /* Sum: '<S2>/Sum2' incorporates:
   *  Fcn: '<S21>/Row1'
   *  Fcn: '<S21>/Row2'
   *  Fcn: '<S21>/Row3'
   *  MATLAB Function: '<S28>/Thruster configuration matrix'
   */
  /* '<S12>:1:9' */
  tmp[0] = cos(rtb_psi_dot) * rtb_Product_idx_0 + sin(rtb_psi_dot) *
    rtb_Product_idx_1;
  tmp[1] = -sin(rtb_psi_dot) * rtb_Product_idx_0 + cos(rtb_psi_dot) *
    rtb_Product_idx_1;
  tmp[2] = rtb_Product_idx_2;
  tau_0[0] = tau[0];
  tau_0[1] = tau[1];
  tau_0[2] = tau[2];

  /* Sum: '<S2>/Sum3' incorporates:
   *  MATLAB Function: '<S2>/D(nu)*nu'
   *  Sum: '<S2>/Sum2'
   */
  rtb_Row1_l[0] = rtb_Row1_h;
  rtb_Row1_l[1] = rtb_Row2;
  rtb_Row1_l[2] = rtb_Row3;
  for (i = 0; i < 3; i++) {
    rtb_Row1_l_0[i] = ((tmp[i] + tau_0[i]) + rtb_Row1_l[i]) - ((D_NL[i + 3] *
      ctrl_student_B.Integrator1[1] + D_NL[i] * ctrl_student_B.Integrator1[0]) +
      D_NL[i + 6] * ctrl_student_B.Integrator1[2]);
  }

  /* MATLAB Function: '<S2>/C(nu)*nu' incorporates:
   *  Sum: '<S2>/Sum3'
   */
  for (i = 0; i < 3; i++) {
    tau[i] = C_NL[i + 6] * ctrl_student_B.Integrator1[2] + (C_NL[i + 3] *
      ctrl_student_B.Integrator1[1] + C_NL[i] * ctrl_student_B.Integrator1[0]);
  }

  /* Sum: '<S2>/Sum3' incorporates:
   *  Gain: '<S2>/M^-1'
   */
  rtb_Fcn = rtb_Row1_l_0[0] - tau[0];
  t3 = rtb_Row1_l_0[1] - tau[1];
  rtb_Row2 = rtb_Row1_l_0[2] - tau[2];

  /* Gain: '<S2>/M^-1' */
  for (i = 0; i < 3; i++) {
    ctrl_student_B.M1[i] = 0.0;
    ctrl_student_B.M1[i] += ctrl_student_P.M1_Gain[i] * rtb_Fcn;
    ctrl_student_B.M1[i] += ctrl_student_P.M1_Gain[i + 3] * t3;
    ctrl_student_B.M1[i] += ctrl_student_P.M1_Gain[i + 6] * rtb_Row2;
  }

  /* Product: '<S2>/Product1' */
  ctrl_student_B.Product1[0] = ctrl_student_B.K_3x * u[0];
  ctrl_student_B.Product1[1] = ctrl_student_B.K_3y * u[1];
  ctrl_student_B.Product1[2] = ctrl_student_B.K_3psi * u[2];

  /* Sum: '<S2>/Sum1' incorporates:
   *  Fcn: '<S20>/Fcn'
   *  Fcn: '<S20>/Fcn1'
   *  Fcn: '<S20>/Fcn2'
   *  Product: '<S2>/Product'
   */
  ctrl_student_B.Sum1[0] = (cos(rtb_psi_dot) * ctrl_student_B.Integrator1[0] -
    sin(rtb_psi_dot) * ctrl_student_B.Integrator1[1]) + ctrl_student_B.K_2x * u
    [0];
  ctrl_student_B.Sum1[1] = (sin(rtb_psi_dot) * ctrl_student_B.Integrator1[0] +
    cos(rtb_psi_dot) * ctrl_student_B.Integrator1[1]) + ctrl_student_B.K_2y * u
    [1];
  ctrl_student_B.Sum1[2] = ctrl_student_B.K_2psi * u[2] +
    ctrl_student_B.Integrator1[2];
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    /* MATLAB Function 'Observer/MATLAB Function': '<S17>:1' */
    /* '<S17>:1:4' */
    /* MATLAB Function 'Observer/MATLAB Function1': '<S18>:1' */
    /* '<S18>:1:4' */
    /* MATLAB Function 'Observer/MATLAB Function2': '<S19>:1' */
    /* '<S19>:1:4' */
  }
}

/* Model update function */
void ctrl_student_update(void)
{
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    /* Update for Delay: '<S1>/Delay' */
    ctrl_student_DW.icLoad = 0U;
    ctrl_student_DW.Delay_DSTATE[0] = ctrl_student_B.eta_filtered[0];
    ctrl_student_DW.Delay_DSTATE[1] = ctrl_student_B.eta_filtered[1];
    ctrl_student_DW.Delay_DSTATE[2] = ctrl_student_B.eta_filtered[2];

    /* Update for Memory: '<S1>/Memory3' */
    ctrl_student_DW.Memory3_PreviousInput[0] = ctrl_student_B.eta_dot_filtered[0];
    ctrl_student_DW.Memory3_PreviousInput[1] = ctrl_student_B.eta_dot_filtered[1];
    ctrl_student_DW.Memory3_PreviousInput[2] = ctrl_student_B.eta_dot_filtered[2];

    /* Update for Memory: '<S1>/Memory2' */
    ctrl_student_DW.Memory2_PreviousInput[0] = ctrl_student_B.nu[0];
    ctrl_student_DW.Memory2_PreviousInput[1] = ctrl_student_B.nu[1];
    ctrl_student_DW.Memory2_PreviousInput[2] = ctrl_student_B.nu[2];

    /* Update for Memory: '<S1>/Memory1' */
    ctrl_student_DW.Memory1_PreviousInput[0] = ctrl_student_B.nu_dot[0];
    ctrl_student_DW.Memory1_PreviousInput[1] = ctrl_student_B.nu_dot[1];
    ctrl_student_DW.Memory1_PreviousInput[2] = ctrl_student_B.nu_dot[2];
  }

  /* Update for Integrator: '<S2>/Integrator' */
  ctrl_student_DW.Integrator_IWORK.IcNeedsLoading = 0;
  if (rtmIsMajorTimeStep(ctrl_student_M)) {
    rt_ertODEUpdateContinuousStates(&ctrl_student_M->solverInfo);
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
  if (!(++ctrl_student_M->Timing.clockTick0)) {
    ++ctrl_student_M->Timing.clockTickH0;
  }

  ctrl_student_M->Timing.t[0] = rtsiGetSolverStopTime
    (&ctrl_student_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++ctrl_student_M->Timing.clockTick1)) {
      ++ctrl_student_M->Timing.clockTickH1;
    }

    ctrl_student_M->Timing.t[1] = ctrl_student_M->Timing.clockTick1 *
      ctrl_student_M->Timing.stepSize1 + ctrl_student_M->Timing.clockTickH1 *
      ctrl_student_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void ctrl_student_derivatives(void)
{
  /* Derivatives for Integrator: '<S2>/Integrator2' */
  {
    ((XDot_ctrl_student_T *) ctrl_student_M->ModelData.derivs)
      ->Integrator2_CSTATE[0] = ctrl_student_B.Product1[0];
    ((XDot_ctrl_student_T *) ctrl_student_M->ModelData.derivs)
      ->Integrator2_CSTATE[1] = ctrl_student_B.Product1[1];
    ((XDot_ctrl_student_T *) ctrl_student_M->ModelData.derivs)
      ->Integrator2_CSTATE[2] = ctrl_student_B.Product1[2];
  }

  /* Derivatives for Integrator: '<S2>/Integrator' */
  {
    ((XDot_ctrl_student_T *) ctrl_student_M->ModelData.derivs)
      ->Integrator_CSTATE[0] = ctrl_student_B.Sum1[0];
    ((XDot_ctrl_student_T *) ctrl_student_M->ModelData.derivs)
      ->Integrator_CSTATE[1] = ctrl_student_B.Sum1[1];
    ((XDot_ctrl_student_T *) ctrl_student_M->ModelData.derivs)
      ->Integrator_CSTATE[2] = ctrl_student_B.Sum1[2];
  }

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  {
    ((XDot_ctrl_student_T *) ctrl_student_M->ModelData.derivs)
      ->Integrator1_CSTATE[0] = ctrl_student_B.M1[0];
    ((XDot_ctrl_student_T *) ctrl_student_M->ModelData.derivs)
      ->Integrator1_CSTATE[1] = ctrl_student_B.M1[1];
    ((XDot_ctrl_student_T *) ctrl_student_M->ModelData.derivs)
      ->Integrator1_CSTATE[2] = ctrl_student_B.M1[2];
  }
}

/* Model initialize function */
void ctrl_student_initialize(void)
{
  ctrl_student_PrevZCX.Integrator2_Reset_ZCE = UNINITIALIZED_ZCSIG;
  ctrl_student_PrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  ctrl_student_PrevZCX.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Delay: '<S1>/Delay' */
  ctrl_student_DW.icLoad = 1U;

  /* InitializeConditions for Memory: '<S1>/Memory3' */
  ctrl_student_DW.Memory3_PreviousInput[0] = ctrl_student_P.Memory3_X0[0];
  ctrl_student_DW.Memory3_PreviousInput[1] = ctrl_student_P.Memory3_X0[1];
  ctrl_student_DW.Memory3_PreviousInput[2] = ctrl_student_P.Memory3_X0[2];

  /* InitializeConditions for Memory: '<S1>/Memory2' */
  ctrl_student_DW.Memory2_PreviousInput[0] = ctrl_student_P.Memory2_X0[0];
  ctrl_student_DW.Memory2_PreviousInput[1] = ctrl_student_P.Memory2_X0[1];
  ctrl_student_DW.Memory2_PreviousInput[2] = ctrl_student_P.Memory2_X0[2];

  /* InitializeConditions for Memory: '<S1>/Memory1' */
  ctrl_student_DW.Memory1_PreviousInput[0] = ctrl_student_P.Memory1_X0[0];
  ctrl_student_DW.Memory1_PreviousInput[1] = ctrl_student_P.Memory1_X0[1];
  ctrl_student_DW.Memory1_PreviousInput[2] = ctrl_student_P.Memory1_X0[2];

  /* InitializeConditions for Integrator: '<S2>/Integrator2' */
  ctrl_student_X.Integrator2_CSTATE[0] = (ctrl_student_P.Integrator2_IC[0]);
  ctrl_student_X.Integrator2_CSTATE[1] = (ctrl_student_P.Integrator2_IC[1]);
  ctrl_student_X.Integrator2_CSTATE[2] = (ctrl_student_P.Integrator2_IC[2]);

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  if (rtmIsFirstInitCond(ctrl_student_M)) {
    ctrl_student_X.Integrator_CSTATE[0] = 0.0;
    ctrl_student_X.Integrator_CSTATE[1] = 0.0;
    ctrl_student_X.Integrator_CSTATE[2] = 0.0;
  }

  ctrl_student_DW.Integrator_IWORK.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  ctrl_student_X.Integrator1_CSTATE[0] = (ctrl_student_P.Integrator1_IC[0]);
  ctrl_student_X.Integrator1_CSTATE[1] = (ctrl_student_P.Integrator1_IC[1]);
  ctrl_student_X.Integrator1_CSTATE[2] = (ctrl_student_P.Integrator1_IC[2]);

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(ctrl_student_M)) {
    rtmSetFirstInitCond(ctrl_student_M, 0);
  }
}

/* Model terminate function */
void ctrl_student_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  ctrl_student_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  ctrl_student_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  ctrl_student_initialize();
}

void MdlTerminate(void)
{
  ctrl_student_terminate();
}

/* Registration function */
RT_MODEL_ctrl_student_T *ctrl_student(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ctrl_student_M, 0,
                sizeof(RT_MODEL_ctrl_student_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&ctrl_student_M->solverInfo,
                          &ctrl_student_M->Timing.simTimeStep);
    rtsiSetTPtr(&ctrl_student_M->solverInfo, &rtmGetTPtr(ctrl_student_M));
    rtsiSetStepSizePtr(&ctrl_student_M->solverInfo,
                       &ctrl_student_M->Timing.stepSize0);
    rtsiSetdXPtr(&ctrl_student_M->solverInfo, &ctrl_student_M->ModelData.derivs);
    rtsiSetContStatesPtr(&ctrl_student_M->solverInfo, (real_T **)
                         &ctrl_student_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&ctrl_student_M->solverInfo,
      &ctrl_student_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&ctrl_student_M->solverInfo, (&rtmGetErrorStatus
      (ctrl_student_M)));
    rtsiSetRTModelPtr(&ctrl_student_M->solverInfo, ctrl_student_M);
  }

  rtsiSetSimTimeStep(&ctrl_student_M->solverInfo, MAJOR_TIME_STEP);
  ctrl_student_M->ModelData.intgData.y = ctrl_student_M->ModelData.odeY;
  ctrl_student_M->ModelData.intgData.f[0] = ctrl_student_M->ModelData.odeF[0];
  ctrl_student_M->ModelData.intgData.f[1] = ctrl_student_M->ModelData.odeF[1];
  ctrl_student_M->ModelData.intgData.f[2] = ctrl_student_M->ModelData.odeF[2];
  ctrl_student_M->ModelData.intgData.f[3] = ctrl_student_M->ModelData.odeF[3];
  ctrl_student_M->ModelData.contStates = ((real_T *) &ctrl_student_X);
  rtsiSetSolverData(&ctrl_student_M->solverInfo, (void *)
                    &ctrl_student_M->ModelData.intgData);
  rtsiSetSolverName(&ctrl_student_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ctrl_student_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    ctrl_student_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ctrl_student_M->Timing.sampleTimes =
      (&ctrl_student_M->Timing.sampleTimesArray[0]);
    ctrl_student_M->Timing.offsetTimes =
      (&ctrl_student_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ctrl_student_M->Timing.sampleTimes[0] = (0.0);
    ctrl_student_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    ctrl_student_M->Timing.offsetTimes[0] = (0.0);
    ctrl_student_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(ctrl_student_M, &ctrl_student_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ctrl_student_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    ctrl_student_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ctrl_student_M, -1);
  ctrl_student_M->Timing.stepSize0 = 0.01;
  ctrl_student_M->Timing.stepSize1 = 0.01;
  rtmSetFirstInitCond(ctrl_student_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    ctrl_student_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ctrl_student_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(ctrl_student_M->rtwLogInfo, (NULL));
    rtliSetLogT(ctrl_student_M->rtwLogInfo, "tout");
    rtliSetLogX(ctrl_student_M->rtwLogInfo, "");
    rtliSetLogXFinal(ctrl_student_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(ctrl_student_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(ctrl_student_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(ctrl_student_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(ctrl_student_M->rtwLogInfo, 1);
    rtliSetLogY(ctrl_student_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(ctrl_student_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(ctrl_student_M->rtwLogInfo, (NULL));
  }

  ctrl_student_M->solverInfoPtr = (&ctrl_student_M->solverInfo);
  ctrl_student_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&ctrl_student_M->solverInfo, 0.01);
  rtsiSetSolverMode(&ctrl_student_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  ctrl_student_M->ModelData.blockIO = ((void *) &ctrl_student_B);
  (void) memset(((void *) &ctrl_student_B), 0,
                sizeof(B_ctrl_student_T));

  /* parameters */
  ctrl_student_M->ModelData.defaultParam = ((real_T *)&ctrl_student_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &ctrl_student_X;
    ctrl_student_M->ModelData.contStates = (x);
    (void) memset((void *)&ctrl_student_X, 0,
                  sizeof(X_ctrl_student_T));
  }

  /* states (dwork) */
  ctrl_student_M->ModelData.dwork = ((void *) &ctrl_student_DW);
  (void) memset((void *)&ctrl_student_DW, 0,
                sizeof(DW_ctrl_student_T));

  /* Initialize Sizes */
  ctrl_student_M->Sizes.numContStates = (9);/* Number of continuous states */
  ctrl_student_M->Sizes.numY = (0);    /* Number of model outputs */
  ctrl_student_M->Sizes.numU = (0);    /* Number of model inputs */
  ctrl_student_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  ctrl_student_M->Sizes.numSampTimes = (2);/* Number of sample times */
  ctrl_student_M->Sizes.numBlocks = (116);/* Number of blocks */
  ctrl_student_M->Sizes.numBlockIO = (36);/* Number of block outputs */
  ctrl_student_M->Sizes.numBlockPrms = (241);/* Sum of parameter "widths" */
  return ctrl_student_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================*
 * This file contains automatically generated code for functions
 * to update the inports and outports of a Simulink/Realtime Workshop
 * model. Calls to these functions should be made before each step is taken
 * (inports, call SetExternalInputs) and after each step is taken
 * (outports, call SetExternalOutputs.)
 */
#ifdef NI_ROOTMODEL_ctrl_student
#include "model_info.h"
#include <stddef.h>
#include <stdlib.h>
#include <float.h>

unsigned char ReadSideDirtyFlag = 0, WriteSideDirtyFlag = 0;
double NIRT_GetValueByDataType(void* ptr,int subindex, int type, int Complex)
{
  switch (type)
  {
   case 0:
    return (double)(((real_T*)ptr)[subindex]);

   case 1:
    return (double)(((real32_T*)ptr)[subindex]);

   case 2:
    return (double)(((int8_T*)ptr)[subindex]);

   case 3:
    return (double)(((uint8_T*)ptr)[subindex]);

   case 4:
    return (double)(((int16_T*)ptr)[subindex]);

   case 5:
    return (double)(((uint16_T*)ptr)[subindex]);

   case 6:
    return (double)(((int32_T*)ptr)[subindex]);

   case 7:
    return (double)(((uint32_T*)ptr)[subindex]);

   case 8:
    return (double)(((boolean_T*)ptr)[subindex]);

   case 10:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 13:
    return NIRT_GetValueByDataType(ptr,subindex,7,Complex);

   case 15:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 16:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 17:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 18:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 19:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 20:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 21:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 22:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 23:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 24:
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 32:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 33:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 34:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 35:
    return NIRT_GetValueByDataType(ptr,subindex,7,Complex);

   case 36:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 37:
    return NIRT_GetValueByDataType(ptr,subindex,7,Complex);
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

   case 15:
    //Type is enum. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 16:
    //Type is enum. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 17:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 18:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 19:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 20:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 32:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 33:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 34:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 35:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,7,Complex);

   case 36:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 37:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,7,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern ctrl_student_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // pose measured/x_m
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.x_m, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // pose measured/y_m
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.y_m, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // pose measured/psi_m
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.psi_m, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/reset
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.reset, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/K_4/K_4,psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.K_4psi, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/K_4/K_4,x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.K_4x, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/K_4/K_4,y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.K_4y, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/K_2/K_2,x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.K_2x, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/K_2/K_2,y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.K_2y, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/K_2/K_2,psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.K_2psi, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/K_3/K_3,psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.K_3psi, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/K_3/K_3,x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.K_3x, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Observer/K_3/K_3,y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_B.K_3y, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 13;
}

double ni_extout[20];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // control input u exceeds bounds: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.fault,0,8,0);
  } else {
    index += 1;
  }

  // u/alpha_VSP2: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.alpha_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/omega_VSP1: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.omega_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/omega_VSP2: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.omega_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/alpha_VSP1: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.alpha_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/u_BT: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_BT,0,0,0);
  } else {
    index += 1;
  }

  // u/u_VSP1: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_VSP,0,0,0);
  } else {
    index += 1;
  }

  // u/u_VSP2: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_VSP,0,0,0);
  } else {
    index += 1;
  }

  // Observer/b_hat/b_x_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator2,0,
      17,0);
  } else {
    index += 1;
  }

  // Observer/b_hat/b_y_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator2,1,
      17,0);
  } else {
    index += 1;
  }

  // Observer/b_hat/b_psi_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator2,2,
      17,0);
  } else {
    index += 1;
  }

  // Observer/eta_hat/x_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator,0,17,
      0);
  } else {
    index += 1;
  }

  // Observer/eta_hat/y_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator,1,17,
      0);
  } else {
    index += 1;
  }

  // Observer/eta_hat/psi_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Sum,0,0,0);
  } else {
    index += 1;
  }

  // Observer/nu_dot_hat/u_dot_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.M1,0,17,0);
  } else {
    index += 1;
  }

  // Observer/nu_dot_hat/v_dot_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.M1,1,17,0);
  } else {
    index += 1;
  }

  // Observer/nu_dot_hat/r_dot_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.M1,2,17,0);
  } else {
    index += 1;
  }

  // Observer/nu_hat/u_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator1,0,
      17,0);
  } else {
    index += 1;
  }

  // Observer/nu_hat/v_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator1,1,
      17,0);
  } else {
    index += 1;
  }

  // Observer/nu_hat/r_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator1,2,
      17,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 20;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

  // control input u exceeds bounds: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.fault,0,8,0);

  // u/alpha_VSP2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.alpha_VSP,0,0,0);

  // u/omega_VSP1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.omega_VSP,0,0,0);

  // u/omega_VSP2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.omega_VSP,0,0,0);

  // u/alpha_VSP1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.alpha_VSP,0,0,0);

  // u/u_BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_BT,0,0,0);

  // u/u_VSP1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_VSP,0,0,0);

  // u/u_VSP2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.u_VSP,0,0,0);

  // Observer/b_hat/b_x_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator2,0,17,
    0);

  // Observer/b_hat/b_y_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator2,1,17,
    0);

  // Observer/b_hat/b_psi_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator2,2,17,
    0);

  // Observer/eta_hat/x_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator,0,17,0);

  // Observer/eta_hat/y_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator,1,17,0);

  // Observer/eta_hat/psi_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Sum,0,0,0);

  // Observer/nu_dot_hat/u_dot_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.M1,0,17,0);

  // Observer/nu_dot_hat/v_dot_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.M1,1,17,0);

  // Observer/nu_dot_hat/r_dot_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.M1,2,17,0);

  // Observer/nu_hat/u_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator1,0,17,
    0);

  // Observer/nu_hat/v_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator1,1,17,
    0);

  // Observer/nu_hat/r_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_B.Integrator1,2,17,
    0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "ctrl_student/Constant/Value", offsetof(P_ctrl_student_T, Constant_Value),
    32, 1, 2, 0, 0 },

  { 1, "ctrl_student/Derivative filter/Low pass Gain 2/Value", offsetof
    (P_ctrl_student_T, LowpassGain2_Value), 32, 1, 2, 2, 0 },

  { 2, "ctrl_student/Derivative filter/sample time/Value", offsetof
    (P_ctrl_student_T, sampletime_Value), 32, 1, 2, 4, 0 },

  { 3, "ctrl_student/Derivative filter/Low pass Gain 1/Value", offsetof
    (P_ctrl_student_T, LowpassGain1_Value), 32, 1, 2, 6, 0 },

  { 4, "ctrl_student/Derivative filter/Memory3/X0", offsetof(P_ctrl_student_T,
    Memory3_X0), 33, 3, 2, 8, 0 },

  { 5, "ctrl_student/Derivative filter/Memory2/X0", offsetof(P_ctrl_student_T,
    Memory2_X0), 33, 3, 2, 10, 0 },

  { 6, "ctrl_student/Derivative filter/Memory1/X0", offsetof(P_ctrl_student_T,
    Memory1_X0), 33, 3, 2, 12, 0 },

  { 7, "ctrl_student/Observer/Integrator2/InitialCondition", offsetof
    (P_ctrl_student_T, Integrator2_IC), 34, 3, 2, 14, 0 },

  { 8, "ctrl_student/Observer/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(P_ctrl_student_T, Saturation_UpperSat), 32, 1, 2, 16, 0 },

  { 9, "ctrl_student/Observer/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(P_ctrl_student_T, Saturation_LowerSat), 32, 1, 2, 18, 0 },

  { 10, "ctrl_student/Observer/[-inf inf] to [-pi pi]/Gain/Gain", offsetof
    (P_ctrl_student_T, Gain_Gain), 32, 1, 2, 20, 0 },

  { 11, "ctrl_student/Observer/[-inf inf] to [-pi pi]/Constant/Value", offsetof
    (P_ctrl_student_T, Constant_Value_c), 32, 1, 2, 22, 0 },

  { 12, "ctrl_student/Observer/Integrator1/InitialCondition", offsetof
    (P_ctrl_student_T, Integrator1_IC), 34, 3, 2, 24, 0 },

  { 13, "ctrl_student/Observer/M^-1/Gain", offsetof(P_ctrl_student_T, M1_Gain),
    21, 9, 2, 26, 0 },

  { 14, "ctrl_student/Observer/Constant/Value", offsetof(P_ctrl_student_T,
    Constant_Value_g), 32, 1, 2, 28, 0 },

  { 15, "ctrl_student/Observer/Constant1/Value", offsetof(P_ctrl_student_T,
    Constant1_Value), 32, 1, 2, 30, 0 },

  { 16, "ctrl_student/Observer/Constant2/Value", offsetof(P_ctrl_student_T,
    Constant2_Value), 32, 1, 2, 32, 0 },

  { 17, "ctrl_student/Observer/Constant3/Value", offsetof(P_ctrl_student_T,
    Constant3_Value), 32, 1, 2, 34, 0 },

  { 18, "ctrl_student/Observer/Constant4/Value", offsetof(P_ctrl_student_T,
    Constant4_Value), 32, 1, 2, 36, 0 },

  { 19, "ctrl_student/Observer/Constant5/Value", offsetof(P_ctrl_student_T,
    Constant5_Value), 32, 1, 2, 38, 0 },

  { 20, "ctrl_student/Observer/Constant6/Value", offsetof(P_ctrl_student_T,
    Constant6_Value), 32, 1, 2, 40, 0 },

  { 21, "ctrl_student/Observer/Constant7/Value", offsetof(P_ctrl_student_T,
    Constant7_Value), 32, 1, 2, 42, 0 },

  { 22, "ctrl_student/Observer/Constant8/Value", offsetof(P_ctrl_student_T,
    Constant8_Value), 32, 1, 2, 44, 0 },

  { 23, "ctrl_student/Derivative filter/Delay/DelayLength", offsetof
    (P_ctrl_student_T, Delay_DelayLength), 35, 1, 2, 46, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 24;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  1, 1,                                /* Parameter at index 0 */
  1, 1,                                /* Parameter at index 1 */
  1, 1,                                /* Parameter at index 2 */
  1, 1,                                /* Parameter at index 3 */
  1, 3,                                /* Parameter at index 4 */
  1, 3,                                /* Parameter at index 5 */
  1, 3,                                /* Parameter at index 6 */
  3, 1,                                /* Parameter at index 7 */
  1, 1,                                /* Parameter at index 8 */
  1, 1,                                /* Parameter at index 9 */
  1, 1,                                /* Parameter at index 10 */
  1, 1,                                /* Parameter at index 11 */
  3, 1,                                /* Parameter at index 12 */
  3, 3,                                /* Parameter at index 13 */
  1, 1,                                /* Parameter at index 14 */
  1, 1,                                /* Parameter at index 15 */
  1, 1,                                /* Parameter at index 16 */
  1, 1,                                /* Parameter at index 17 */
  1, 1,                                /* Parameter at index 18 */
  1, 1,                                /* Parameter at index 19 */
  1, 1,                                /* Parameter at index 20 */
  1, 1,                                /* Parameter at index 21 */
  1, 1,                                /* Parameter at index 22 */
  1, 1,                                /* Parameter at index 23 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "ctrl_student/pose measured/x_m", 0, "", offsetof(B_ctrl_student_T, x_m)+
    0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "ctrl_student/pose measured/y_m", 0, "", offsetof(B_ctrl_student_T, y_m)+
    0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "ctrl_student/pose measured/psi_m", 0, "", offsetof(B_ctrl_student_T,
    psi_m)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "ctrl_student/Derivative filter/Delay", 0, "(1,1)", offsetof
    (B_ctrl_student_T, Delay)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 6, 0 },

  { 4, "ctrl_student/Derivative filter/Delay", 0, "(1,2)", offsetof
    (B_ctrl_student_T, Delay)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 8, 0 },

  { 5, "ctrl_student/Derivative filter/Delay", 0, "(1,3)", offsetof
    (B_ctrl_student_T, Delay)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 10, 0 },

  { 6, "ctrl_student/Derivative filter/Memory3", 0, "(1,1)", offsetof
    (B_ctrl_student_T, Memory3)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 12, 0 },

  { 7, "ctrl_student/Derivative filter/Memory3", 0, "(1,2)", offsetof
    (B_ctrl_student_T, Memory3)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 14, 0 },

  { 8, "ctrl_student/Derivative filter/Memory3", 0, "(1,3)", offsetof
    (B_ctrl_student_T, Memory3)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 16, 0 },

  { 9, "ctrl_student/Derivative filter/Memory2", 0, "(1,1)", offsetof
    (B_ctrl_student_T, Memory2)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 18, 0 },

  { 10, "ctrl_student/Derivative filter/Memory2", 0, "(1,2)", offsetof
    (B_ctrl_student_T, Memory2)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 20, 0 },

  { 11, "ctrl_student/Derivative filter/Memory2", 0, "(1,3)", offsetof
    (B_ctrl_student_T, Memory2)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 22, 0 },

  { 12, "ctrl_student/Derivative filter/Memory1", 0, "(1,1)", offsetof
    (B_ctrl_student_T, Memory1)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 24, 0 },

  { 13, "ctrl_student/Derivative filter/Memory1", 0, "(1,2)", offsetof
    (B_ctrl_student_T, Memory1)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 26, 0 },

  { 14, "ctrl_student/Derivative filter/Memory1", 0, "(1,3)", offsetof
    (B_ctrl_student_T, Memory1)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 28, 0 },

  { 15, "ctrl_student/Observer/reset", 0, "", offsetof(B_ctrl_student_T, reset)+
    0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "ctrl_student/Observer/Integrator2", 0, "(1,1)", offsetof
    (B_ctrl_student_T, Integrator2)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 32,
    0 },

  { 17, "ctrl_student/Observer/Integrator2", 0, "(1,2)", offsetof
    (B_ctrl_student_T, Integrator2)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 34,
    0 },

  { 18, "ctrl_student/Observer/Integrator2", 0, "(1,3)", offsetof
    (B_ctrl_student_T, Integrator2)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 36,
    0 },

  { 19, "ctrl_student/Observer/Integrator", 0, "(1,1)", offsetof
    (B_ctrl_student_T, Integrator)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 38,
    0 },

  { 20, "ctrl_student/Observer/Integrator", 0, "(1,2)", offsetof
    (B_ctrl_student_T, Integrator)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 40,
    0 },

  { 21, "ctrl_student/Observer/Integrator", 0, "(1,3)", offsetof
    (B_ctrl_student_T, Integrator)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 42,
    0 },

  { 22, "ctrl_student/Observer/[-inf inf] to [-pi pi]/Sum", 0, "", offsetof
    (B_ctrl_student_T, Sum)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 44, 0 },

  { 23, "ctrl_student/Observer/K_4/K_4,psi", 0, "", offsetof(B_ctrl_student_T,
    K_4psi)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 46, 0 },

  { 24, "ctrl_student/Observer/K_4/K_4,x", 0, "", offsetof(B_ctrl_student_T,
    K_4x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25, "ctrl_student/Observer/K_4/K_4,y", 0, "", offsetof(B_ctrl_student_T,
    K_4y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 50, 0 },

  { 26, "ctrl_student/Observer/Integrator1", 0, "(1,1)", offsetof
    (B_ctrl_student_T, Integrator1)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 52,
    0 },

  { 27, "ctrl_student/Observer/Integrator1", 0, "(1,2)", offsetof
    (B_ctrl_student_T, Integrator1)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 54,
    0 },

  { 28, "ctrl_student/Observer/Integrator1", 0, "(1,3)", offsetof
    (B_ctrl_student_T, Integrator1)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 56,
    0 },

  { 29, "ctrl_student/Observer/M^-1", 0, "(1,1)", offsetof(B_ctrl_student_T, M1)
    +0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 58, 0 },

  { 30, "ctrl_student/Observer/M^-1", 0, "(1,2)", offsetof(B_ctrl_student_T, M1)
    +1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 60, 0 },

  { 31, "ctrl_student/Observer/M^-1", 0, "(1,3)", offsetof(B_ctrl_student_T, M1)
    +2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 62, 0 },

  { 32, "ctrl_student/Observer/K_2/K_2,x", 0, "", offsetof(B_ctrl_student_T,
    K_2x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33, "ctrl_student/Observer/K_2/K_2,y", 0, "", offsetof(B_ctrl_student_T,
    K_2y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 66, 0 },

  { 34, "ctrl_student/Observer/K_2/K_2,psi", 0, "", offsetof(B_ctrl_student_T,
    K_2psi)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35, "ctrl_student/Observer/K_3/K_3,psi", 0, "", offsetof(B_ctrl_student_T,
    K_3psi)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36, "ctrl_student/Observer/K_3/K_3,x", 0, "", offsetof(B_ctrl_student_T,
    K_3x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37, "ctrl_student/Observer/K_3/K_3,y", 0, "", offsetof(B_ctrl_student_T,
    K_3y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 74, 0 },

  { 38, "ctrl_student/Observer/Product1", 0, "(1,1)", offsetof(B_ctrl_student_T,
    Product1)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 76, 0 },

  { 39, "ctrl_student/Observer/Product1", 0, "(1,2)", offsetof(B_ctrl_student_T,
    Product1)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 78, 0 },

  { 40, "ctrl_student/Observer/Product1", 0, "(1,3)", offsetof(B_ctrl_student_T,
    Product1)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 80, 0 },

  { 41, "ctrl_student/Observer/Sum1", 0, "(1,1)", offsetof(B_ctrl_student_T,
    Sum1)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 82, 0 },

  { 42, "ctrl_student/Observer/Sum1", 0, "(1,2)", offsetof(B_ctrl_student_T,
    Sum1)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 84, 0 },

  { 43, "ctrl_student/Observer/Sum1", 0, "(1,3)", offsetof(B_ctrl_student_T,
    Sum1)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 86, 0 },

  { 44, "ctrl_student/Thrust allocation", 0, "u_BT", offsetof(B_ctrl_student_T,
    u_BT)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "ctrl_student/Thrust allocation", 1, "u_VSP", offsetof(B_ctrl_student_T,
    u_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46, "ctrl_student/Thrust allocation", 2, "alpha_VSP", offsetof
    (B_ctrl_student_T, alpha_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 92, 0
  },

  { 47, "ctrl_student/Thrust allocation", 3, "omega_VSP", offsetof
    (B_ctrl_student_T, omega_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 94, 0
  },

  { 48, "ctrl_student/Observer/u_2_tau/Thruster mapping/VSP", 0, "F_x", offsetof
    (B_ctrl_student_T, F_x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 96, 0 },

  { 49, "ctrl_student/Observer/u_2_tau/Thruster mapping/VSP", 1, "F_y", offsetof
    (B_ctrl_student_T, F_y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 98, 0 },

  { 50, "ctrl_student/Derivative filter/Rotation matrix", 0, "nu(1,1)", offsetof
    (B_ctrl_student_T, nu)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 100, 0 },

  { 51, "ctrl_student/Derivative filter/Rotation matrix", 0, "nu(1,2)", offsetof
    (B_ctrl_student_T, nu)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 102, 0 },

  { 52, "ctrl_student/Derivative filter/Rotation matrix", 0, "nu(1,3)", offsetof
    (B_ctrl_student_T, nu)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 104, 0 },

  { 53, "ctrl_student/Derivative filter/Low pass filter 2", 0,
    "eta_dot_filtered(1,1)", offsetof(B_ctrl_student_T, eta_dot_filtered)+0*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 106, 0 },

  { 54, "ctrl_student/Derivative filter/Low pass filter 2", 0,
    "eta_dot_filtered(1,2)", offsetof(B_ctrl_student_T, eta_dot_filtered)+1*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 108, 0 },

  { 55, "ctrl_student/Derivative filter/Low pass filter 2", 0,
    "eta_dot_filtered(1,3)", offsetof(B_ctrl_student_T, eta_dot_filtered)+2*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 110, 0 },

  { 56, "ctrl_student/Derivative filter/Low pass filter", 0, "eta_filtered(1,1)",
    offsetof(B_ctrl_student_T, eta_filtered)+0*sizeof(real_T), BLOCKIO_SIG, 17,
    1, 2, 112, 0 },

  { 57, "ctrl_student/Derivative filter/Low pass filter", 0, "eta_filtered(1,2)",
    offsetof(B_ctrl_student_T, eta_filtered)+1*sizeof(real_T), BLOCKIO_SIG, 17,
    1, 2, 114, 0 },

  { 58, "ctrl_student/Derivative filter/Low pass filter", 0, "eta_filtered(1,3)",
    offsetof(B_ctrl_student_T, eta_filtered)+2*sizeof(real_T), BLOCKIO_SIG, 17,
    1, 2, 116, 0 },

  { 59, "ctrl_student/Derivative filter/Differentiate and filter1", 0,
    "nu_dot(1,1)", offsetof(B_ctrl_student_T, nu_dot)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 118, 0 },

  { 60, "ctrl_student/Derivative filter/Differentiate and filter1", 0,
    "nu_dot(1,2)", offsetof(B_ctrl_student_T, nu_dot)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 120, 0 },

  { 61, "ctrl_student/Derivative filter/Differentiate and filter1", 0,
    "nu_dot(1,3)", offsetof(B_ctrl_student_T, nu_dot)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 122, 0 },

  { 62, "ctrl_student/control limit checking", 0, "fault", offsetof
    (B_ctrl_student_T, fault)+0*sizeof(boolean_T), BLOCKIO_SIG, 8, 1, 2, 124, 0
  },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 63;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 33;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "pose measured/x_m", 0, EXT_IN, 1, 1, 1 },

  { 1, "pose measured/y_m", 0, EXT_IN, 1, 1, 1 },

  { 2, "pose measured/psi_m", 0, EXT_IN, 1, 1, 1 },

  { 3, "Observer/reset", 0, EXT_IN, 1, 1, 1 },

  { 4, "Observer/K_4/K_4,psi", 0, EXT_IN, 1, 1, 1 },

  { 5, "Observer/K_4/K_4,x", 0, EXT_IN, 1, 1, 1 },

  { 6, "Observer/K_4/K_4,y", 0, EXT_IN, 1, 1, 1 },

  { 7, "Observer/K_2/K_2,x", 0, EXT_IN, 1, 1, 1 },

  { 8, "Observer/K_2/K_2,y", 0, EXT_IN, 1, 1, 1 },

  { 9, "Observer/K_2/K_2,psi", 0, EXT_IN, 1, 1, 1 },

  { 10, "Observer/K_3/K_3,psi", 0, EXT_IN, 1, 1, 1 },

  { 11, "Observer/K_3/K_3,x", 0, EXT_IN, 1, 1, 1 },

  { 12, "Observer/K_3/K_3,y", 0, EXT_IN, 1, 1, 1 },

  { 0, "control input u exceeds bounds", 1, EXT_OUT, 1, 1, 1 },

  { 1, "u/alpha_VSP2", 1, EXT_OUT, 1, 1, 1 },

  { 2, "u/omega_VSP1", 1, EXT_OUT, 1, 1, 1 },

  { 3, "u/omega_VSP2", 1, EXT_OUT, 1, 1, 1 },

  { 4, "u/alpha_VSP1", 1, EXT_OUT, 1, 1, 1 },

  { 5, "u/u_BT", 1, EXT_OUT, 1, 1, 1 },

  { 6, "u/u_VSP1", 1, EXT_OUT, 1, 1, 1 },

  { 7, "u/u_VSP2", 1, EXT_OUT, 1, 1, 1 },

  { 8, "Observer/b_hat/b_x_hat", 0, EXT_OUT, 1, 1, 1 },

  { 9, "Observer/b_hat/b_y_hat", 0, EXT_OUT, 1, 1, 1 },

  { 10, "Observer/b_hat/b_psi_hat", 0, EXT_OUT, 1, 1, 1 },

  { 11, "Observer/eta_hat/x_hat", 0, EXT_OUT, 1, 1, 1 },

  { 12, "Observer/eta_hat/y_hat", 0, EXT_OUT, 1, 1, 1 },

  { 13, "Observer/eta_hat/psi_hat", 0, EXT_OUT, 1, 1, 1 },

  { 14, "Observer/nu_dot_hat/u_dot_hat", 0, EXT_OUT, 1, 1, 1 },

  { 15, "Observer/nu_dot_hat/v_dot_hat", 0, EXT_OUT, 1, 1, 1 },

  { 16, "Observer/nu_dot_hat/r_dot_hat", 0, EXT_OUT, 1, 1, 1 },

  { 17, "Observer/nu_hat/u_hat", 0, EXT_OUT, 1, 1, 1 },

  { 18, "Observer/nu_hat/v_hat", 0, EXT_OUT, 1, 1, 1 },

  { 19, "Observer/nu_hat/r_hat", 0, EXT_OUT, 1, 1, 1 },

  { -1, "", 0, 0, 0, 0, 0 }
};

/* This Task List is generated to allow access to the task specs without
 * initializing the model.
 * 0th entry is for scheduler (base rate)
 * rest for multirate model's tasks.
 */
NI_Task NI_TaskList[] DataSection(".NIVS.tasklist") =
{
  { 0, 0.01, 0 }
};

int NI_NumTasks DataSection(".NIVS.numtasks") = 1;
static char* NI_CompiledModelName DataSection(".NIVS.compiledmodelname") =
  "ctrl_student";
static char* NI_CompiledModelVersion = "1.57";
static char* NI_CompiledModelDateTime = "Wed Dec 16 15:39:04 2015";
static char* NI_builder DataSection(".NIVS.builder") =
  "NI VeriStand 2014.0.0.82 (2014) RTW Build";
static char* NI_BuilderVersion DataSection(".NIVS.builderversion") =
  "2014.0.0.82";

/* Model Information Query fucntions for MATLAB
 */
/* dll information
 * Returns 1 for RTW DLL
 *		   2 for AutoCode DLL
 */
DLL_EXPORT long NIRT_GetBuildInfo(char* detail, long* len)
{
  // There are no console properties to set for VxWorks, because the console is simply serial output data.
  // Just do printf for VxWorks and ignore all console properties.
#if ! defined (VXWORKS) && ! defined (kNIOSLinux)

  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_BLUE |
    FOREGROUND_GREEN | FOREGROUND_RED);

#endif

  printf("\n*******************************************************************************\n");
  printf("%s\nModel Name: %s\nModel Version: %s\nCompiled On: %s",
         NI_builder, NI_CompiledModelName, NI_CompiledModelVersion,
         NI_CompiledModelDateTime);
  printf("\n*******************************************************************************\n");

#if ! defined (VXWORKS) && ! defined (kNIOSLinux)

  SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN |
    FOREGROUND_RED);

#endif

  if (*len>=(long)strlen(NI_builder))
    *len = strlen(NI_builder)+1;
  strncpy(detail,NI_builder,*len);
  return 1;
}

/*
 * Distinction between Index and ID:
 * Index is a long datatype (used to set parameter/probe signals).
 * ID on the other hand is a string (tag "2-3-2-12" for MatrixX/ Full path "f14/Gain/Gain" for Matlab).
 * If Bus support is added then signal path from the block name is added to the end of the port number (Model/subsystem1:1/X/A)
 * where X/A is the path from the block
 * NOTE: ID may not be the same as Paramname or signal name.
 */

/* signal information
   NOTE: signal ID == the blockname and port that feeds it extended with /sinalname.

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

      //ID[i] = 0;
      IDblk = ID;
      IDport = atoi(ID+i+1);

      // lookup the table for matching ID
      // Bus support
      for (i=0;i<NI_SigListSize;i++) {
        char *tempID = (char *)calloc(strlen(NI_SigList[i].blockname)+strlen
          (NI_SigList[i].signalname)+ 11, sizeof(char));

        //sprintf(tempID,"%s%s%s",NI_SigList[i].blockname,"/",NI_SigList[i].signalname);
        if (strlen(NI_SigList[i].signalname)>0)
          sprintf(tempID,"%s:%d%s%s",NI_SigList[i].blockname,NI_SigList[i].
                  portno+1,"/",NI_SigList[i].signalname);
        else
          sprintf(tempID,"%s:%d",NI_SigList[i].blockname,NI_SigList[i].portno+1);
        if (!strcmp(IDblk,tempID) && IDport==(NI_SigList[i].portno+1))
          break;
        free(tempID);
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
      // 11 to accomodate ':','/', port number and null character
      char *tempID = (char *)calloc(strlen(NI_SigList[sigidx].blockname)+strlen
        (NI_SigList[sigidx].signalname)+ 11, sizeof(char));
      if (strlen(NI_SigList[sigidx].signalname)>0)
        sprintf(tempID,"%s:%d%s%s",NI_SigList[sigidx].blockname,
                NI_SigList[sigidx].portno+1,"/",NI_SigList[sigidx].signalname);
      else
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
 * DEPRECATED.
 */
DLL_EXPORT long NIRT_GetParameterExpression(long paramidx, char* expression,
  long *exp_len)
{
  return 0;
}

/*
 * DEPRECATED.
 */
DLL_EXPORT long NIRT_GetVariableName(long varidx, char* variable_name, long
  *var_len)
{
  return 0;
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
                      S->ModelData.blockIO : S->ModelData.inputs) + (int)
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
  int i, j, idx;
  long count = 0;
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
        for (j = 0; j < 2; j++) {
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
   The undef allows us to access the real ctrl_student_P
   In the rest of the code ctrl_student_P is redefine to be the read-side
   of rtParameter.
 */
#undef ctrl_student_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &ctrl_student_P, sizeof(P_ctrl_student_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka ctrl_student_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_ctrl_student_T));
  return NI_OK;
}

static int NI_SetParamTxStatus = NI_OK;

// This function is called by the BGL to set parameters.  When a commit is requested (index < 0),
// the code enters a critical section shared with the TCL. This ensures that the flip occurs only
// when safe, and acts as a messaging scheme for us to copy back the parameters.
DLL_EXPORT long NIRT_SetParameter(long index, long subindex, double value)
{
  char* ptr = NULL;
  if (index>=NI_ParamListSize) {
    SetSITErrorMessage("Parameter index is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (index < 0) {
    if (ReadSideDirtyFlag == 1) {
      memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
             (P_ctrl_student_T));
      ReadSideDirtyFlag = 0;
      if (WriteSideDirtyFlag == 0)
        return NI_OK;
      SetSITErrorMessage("Parameters have been set inline and from the background loop at the same time. Parameters written from the background loop since the last commit have been lost.",
                         1);
      WriteSideDirtyFlag = 0;
      return NI_ERROR;
    }

    if (NI_SetParamTxStatus==NI_ERROR) {
      // fail the transaction.
      // copy old	list of parameters to the failed TX buffer
      if (WriteSideDirtyFlag == 1)
        memcpy(&rtParameter[READSIDE], &rtParameter[1-READSIDE], sizeof
               (P_ctrl_student_T));

      // reset the status.
      NI_SetParamTxStatus = NI_OK;
      WriteSideDirtyFlag = 0;
      return NI_ERROR;
    }

    /*Do nothing if no new parameters were written after last commit*/
    if (WriteSideDirtyFlag == 0)
      return NI_OK;

    // commit changes
    S->ModelData.defaultParam = (double *)&rtParameter[1-READSIDE];
    WaitForSingleObject(SITexportglobals.flipCriticalSection, INFINITE);
    READSIDE = 1 - READSIDE;
    SITexportglobals.copyTaskBitfield = 0xFFFFFFFF;
    ReleaseSemaphore(SITexportglobals.flipCriticalSection, 1, NULL);

    // Copy back the newly set parameters to the writeside.
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (P_ctrl_student_T));
    WriteSideDirtyFlag = 0;
    return NI_OK;
  }

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter subindex is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (ReadSideDirtyFlag == 1) {
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (P_ctrl_student_T));
    ReadSideDirtyFlag = 0;
  }

  ptr = (char *)(&rtParameter[1-READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  WriteSideDirtyFlag = 1;
  return NIRT_SetValueByDataType(ptr,subindex,value,NI_ParamList[index].datatype,
    NI_ParamList[index].IsComplex);
}

DLL_EXPORT long NIRT_SetVectorParameter( unsigned long index, const double
  * paramvalues, unsigned long paramlength)
{
  unsigned int i = 0;
  long retval= NI_OK, temp_retval;
  char* ptr = NULL;
  if (index>=NI_ParamListSize) {
    SetSITErrorMessage("Parameter index is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  // verify that subindex is within bounds.
  if (paramlength!=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter length is incorrect.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (ReadSideDirtyFlag == 1) {
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (P_ctrl_student_T));
    ReadSideDirtyFlag = 0;
  }

  ptr = (char *)(&rtParameter[1-READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  while (i<paramlength) {
    if (temp_retval = NIRT_SetValueByDataType(ptr, i, paramvalues[i],
         NI_ParamList[index].datatype, NI_ParamList[index].IsComplex))//assignment intended in if condition
      retval= temp_retval;
    i++;
  }

  WriteSideDirtyFlag = 1;
  return retval;
}

DLL_EXPORT long NIRT_SetScalarParameterInline( unsigned long index, unsigned
  long subindex, double paramvalue)
{
  char* ptr = NULL;
  if (index>=NI_ParamListSize) {
    SetSITErrorMessage("Parameter index is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter subindex is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  ptr = (char *)(&rtParameter[READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  ReadSideDirtyFlag = 1;
  return NIRT_SetValueByDataType(ptr,subindex,paramvalue,NI_ParamList[index].
    datatype,NI_ParamList[index].IsComplex);
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

DLL_EXPORT long NIRT_GetVectorParameter(unsigned long index, double* paramvalues,
  unsigned long paramlength)
{
  char* ptr = NULL;
  unsigned int i = 0;
  if (index>=NI_ParamListSize || index < 0)
    return NI_ERROR;

  // verify that subindex is within bounds.
  if (paramlength!=NI_ParamList[index].width)
    return NI_ERROR;
  ptr = (char *)(&rtParameter[READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  while (i<paramlength) {
    paramvalues[i] = NIRT_GetValueByDataType(ptr, i, NI_ParamList[index].
      datatype, NI_ParamList[index].IsComplex);
    i++;
  }

  return NI_OK;
}

DLL_EXPORT long NIRT_GetSimState(long* numContStates, char* contStatesNames,
  double* contStates, long* numDiscStates, char* discStatesNames, double
  * discStates, long* numClockTicks, char* clockTicksNames, long* clockTicks)
{
  long count, idx;
  if (numContStates && numDiscStates && numClockTicks) {
    if (*numContStates < 0 || *numDiscStates < 0 || *numClockTicks < 0) {
      *numContStates = 9;
      *numDiscStates = 546;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (contStates && contStatesNames) {
    idx = 0;
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_X.Integrator2_CSTATE[0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_X.Integrator2_CSTATE[0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_X.Integrator2_CSTATE[0], 2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&ctrl_student_X.Integrator_CSTATE
      [0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&ctrl_student_X.Integrator_CSTATE
      [0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&ctrl_student_X.Integrator_CSTATE
      [0], 2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_X.Integrator1_CSTATE[0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator1_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_X.Integrator1_CSTATE[0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator1_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_X.Integrator1_CSTATE[0], 2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator1_CSTATE");
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.Delay_DSTATE, 0,
      17, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.Delay_DSTATE");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.Delay_DSTATE, 1,
      17, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.Delay_DSTATE");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.Delay_DSTATE, 2,
      17, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.Delay_DSTATE");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.controlinputuexceedsbounds_DWOR, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.controlinputuexceedsbounds_DWOR");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.alpha_VSP2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.alpha_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.omega_VSP1_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.omega_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.omega_VSP2_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.omega_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.alpha_VSP1_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.alpha_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_BT_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_VSP1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_VSP1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_VSP2_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_VSP2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.x_m_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.x_m_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.y_m_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.y_m_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.psi_m_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.psi_m_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory3_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory3_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory3_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory2_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory2_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory2_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory1_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory1_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory1_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory1_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Memory1_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Memory1_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.reset_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.reset_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.b_x_hat_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.b_x_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.b_y_hat_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.b_y_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.b_psi_hat_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.b_psi_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.x_hat_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.x_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.y_hat_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.y_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.psi_hat_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.psi_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_4psi_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_4psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_4x_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_4x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_4y_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_4y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_dot_hat_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_dot_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.v_dot_hat_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.v_dot_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.r_dot_hat_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.r_dot_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_hat_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.v_hat_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.v_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.r_hat_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.r_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_2x_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_2x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_2y_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_2y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_2psi_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_2psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_3psi_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_3psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_3x_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_3x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_3y_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_3y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.NIVeriStandSignalProbe_DWORK2, 0, 6, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.NIVeriStandSignalProbe_DWORK2");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_DW.Integrator_IWORK.IcNeedsLoading, 0, 10, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_DW.Integrator_IWORK.IcNeedsLoading");
    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.controlinputuexceedsbounds_DW_j, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.controlinputuexceedsbounds_DW_j");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.alpha_VSP2_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.alpha_VSP2_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.omega_VSP1_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.omega_VSP1_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.omega_VSP2_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.omega_VSP2_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.alpha_VSP1_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.alpha_VSP1_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_BT_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_BT_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_VSP1_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_VSP1_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_VSP2_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_VSP2_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.x_m_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.x_m_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.y_m_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.y_m_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.psi_m_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.psi_m_DWORK2");
    }

    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.icLoad, 0, 3, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.icLoad");
    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.reset_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.reset_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.b_x_hat_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.b_x_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.b_y_hat_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.b_y_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.b_psi_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.b_psi_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.x_hat_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.x_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.y_hat_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.y_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.psi_hat_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.psi_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_4psi_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_4psi_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_4x_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_4x_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_4y_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_4y_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.u_dot_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.u_dot_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.v_dot_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.v_dot_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.r_dot_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.r_dot_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.u_hat_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.u_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.v_hat_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.v_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.r_hat_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.r_hat_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_2x_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_2x_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_2y_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_2y_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_2psi_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_2psi_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_3psi_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_3psi_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_3x_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_3x_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_DW.K_3y_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_DW.K_3y_DWORK2");
    }

    for (count = 0; count < 13; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.NIVeriStandSignalProbe_DWORK1, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.NIVeriStandSignalProbe_DWORK1");
    }

    for (count = 0; count < 56; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_DW.NIVeriStandSignalProbe_DWORK3, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_DW.NIVeriStandSignalProbe_DWORK3");
    }
  }

  if (clockTicks && clockTicksNames) {
    clockTicks[0] = S->Timing.clockTick0;
    strcpy(clockTicksNames, "clockTick0");
  }

  return NI_OK;
}

DLL_EXPORT long NIRT_SetSimState(double* contStates, double* discStates, long
  * clockTicks)
{
  long count, idx;
  if (contStates) {
    idx = 0;
    NIRT_SetValueByDataType(&ctrl_student_X.Integrator2_CSTATE[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_X.Integrator2_CSTATE[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_X.Integrator2_CSTATE[0], 2,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_X.Integrator_CSTATE[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_X.Integrator_CSTATE[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_X.Integrator_CSTATE[0], 2,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_X.Integrator1_CSTATE[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_X.Integrator1_CSTATE[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_X.Integrator1_CSTATE[0], 2,
      contStates[idx++], 0, 0);
  }

  if (discStates) {
    idx = 0;
    NIRT_SetValueByDataType(&ctrl_student_DW.Delay_DSTATE, 0, discStates[idx++],
      17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Delay_DSTATE, 1, discStates[idx++],
      17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Delay_DSTATE, 2, discStates[idx++],
      17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.controlinputuexceedsbounds_DWOR, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.alpha_VSP2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.omega_VSP1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.omega_VSP2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.alpha_VSP1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.u_BT_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.u_VSP1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.u_VSP2_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.x_m_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&ctrl_student_DW.y_m_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&ctrl_student_DW.psi_m_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory3_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory3_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory3_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory2_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory2_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory2_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory1_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory1_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Memory1_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.reset_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.b_x_hat_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.b_y_hat_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.b_psi_hat_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.x_hat_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.y_hat_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.psi_hat_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.K_4psi_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.K_4x_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.K_4y_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.u_dot_hat_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.v_dot_hat_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.r_dot_hat_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.u_hat_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.v_hat_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.r_hat_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.K_2x_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.K_2y_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.K_2psi_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.K_3psi_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.K_3x_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.K_3y_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.NIVeriStandSignalProbe_DWORK2, 0,
      discStates[idx++], 6, 0);
    NIRT_SetValueByDataType(&ctrl_student_DW.Integrator_IWORK.IcNeedsLoading, 0,
      discStates[idx++], 10, 0);
    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.controlinputuexceedsbounds_DW_j,
        count, discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.alpha_VSP2_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.omega_VSP1_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.omega_VSP2_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.alpha_VSP1_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.u_BT_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.u_VSP1_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.u_VSP2_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.x_m_DWORK2, count, discStates[idx
        ++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.y_m_DWORK2, count, discStates[idx
        ++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.psi_m_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    NIRT_SetValueByDataType(&ctrl_student_DW.icLoad, 0, discStates[idx++], 3, 0);
    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.reset_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.b_x_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.b_y_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.b_psi_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.x_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.y_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.psi_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.K_4psi_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.K_4x_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.K_4y_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.u_dot_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.v_dot_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.r_dot_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.u_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.v_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.r_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.K_2x_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.K_2y_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.K_2psi_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.K_3psi_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.K_3x_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.K_3y_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 13; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.NIVeriStandSignalProbe_DWORK1,
        count, discStates[idx++], 19, 0);
    }

    for (count = 0; count < 56; count++) {
      NIRT_SetValueByDataType(&ctrl_student_DW.NIVeriStandSignalProbe_DWORK3,
        count, discStates[idx++], 20, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
    S->Timing.clockTick1 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_ctrl_student
