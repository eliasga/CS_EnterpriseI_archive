/*
 * ctrl_DP_mss.c
 *
 * Code generation for model "ctrl_DP_mss".
 *
 * Model version              : 1.10
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Jan 28 18:35:59 2015
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "ctrl_DP_mss.h"
#include "ctrl_DP_mss_private.h"

/* Block signals (auto storage) */
B_ctrl_DP_mss_T ctrl_DP_mss_B;

/* Continuous states */
X_ctrl_DP_mss_T ctrl_DP_mss_X;

/* Block states (auto storage) */
DW_ctrl_DP_mss_T ctrl_DP_mss_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_ctrl_DP_mss_T ctrl_DP_mss_PrevZCX;

/* Real-time model */
RT_MODEL_ctrl_DP_mss_T ctrl_DP_mss_M_;
RT_MODEL_ctrl_DP_mss_T *const ctrl_DP_mss_M = &ctrl_DP_mss_M_;

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
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  ctrl_DP_mss_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  ctrl_DP_mss_output();
  ctrl_DP_mss_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  ctrl_DP_mss_output();
  ctrl_DP_mss_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  ctrl_DP_mss_output();
  ctrl_DP_mss_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
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

/* Model output function */
void ctrl_DP_mss_output(void)
{
  /* local block i/o variables */
  real_T rtb_MatrixMultiply[3];
  real_T rtb_Row3;
  real_T rtb_Sum;
  real_T rtb_MatrixMultiply1[3];
  real_T rtb_Row1;
  real_T rtb_Sum3[3];
  int32_T i;
  if (rtmIsMajorTimeStep(ctrl_DP_mss_M)) {
    /* set solver stop time */
    if (!(ctrl_DP_mss_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&ctrl_DP_mss_M->solverInfo,
                            ((ctrl_DP_mss_M->Timing.clockTickH0 + 1) *
        ctrl_DP_mss_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&ctrl_DP_mss_M->solverInfo,
                            ((ctrl_DP_mss_M->Timing.clockTick0 + 1) *
        ctrl_DP_mss_M->Timing.stepSize0 + ctrl_DP_mss_M->Timing.clockTickH0 *
        ctrl_DP_mss_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(ctrl_DP_mss_M)) {
    ctrl_DP_mss_M->Timing.t[0] = rtsiGetT(&ctrl_DP_mss_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(ctrl_DP_mss_M)) {
    /* Constant: '<S5>/Constant8' */
    ctrl_DP_mss_B.VectorConcatenate[1] = ctrl_DP_mss_P.Constant8_Value;

    /* Constant: '<S5>/Constant10' */
    ctrl_DP_mss_B.VectorConcatenate[2] = ctrl_DP_mss_P.Constant10_Value;

    /* Constant: '<S5>/Constant6' */
    ctrl_DP_mss_B.VectorConcatenate[3] = ctrl_DP_mss_P.Constant6_Value;

    /* Constant: '<S5>/Constant11' */
    ctrl_DP_mss_B.VectorConcatenate[5] = ctrl_DP_mss_P.Constant11_Value;

    /* Constant: '<S5>/Constant7' */
    ctrl_DP_mss_B.VectorConcatenate[6] = ctrl_DP_mss_P.Constant7_Value;

    /* Constant: '<S5>/Constant9' */
    ctrl_DP_mss_B.VectorConcatenate[7] = ctrl_DP_mss_P.Constant9_Value;
  }

  /* Saturate: '<S8>/Saturation' incorporates:
   *  Fcn: '<S1>/yaw angle'
   */
  if (ctrl_DP_mss_B.Ctrl_PSI > ctrl_DP_mss_P.Saturation_UpperSat) {
    rtb_Row3 = ctrl_DP_mss_P.Saturation_UpperSat;
  } else if (ctrl_DP_mss_B.Ctrl_PSI < ctrl_DP_mss_P.Saturation_LowerSat) {
    rtb_Row3 = ctrl_DP_mss_P.Saturation_LowerSat;
  } else {
    rtb_Row3 = ctrl_DP_mss_B.Ctrl_PSI;
  }

  /* End of Saturate: '<S8>/Saturation' */

  /* Signum: '<S8>/Sign' */
  if (rtb_Row3 < 0.0) {
    rtb_Row1 = -1.0;
  } else if (rtb_Row3 > 0.0) {
    rtb_Row1 = 1.0;
  } else if (rtb_Row3 == 0.0) {
    rtb_Row1 = 0.0;
  } else {
    rtb_Row1 = rtb_Row3;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  Signum: '<S8>/Sign'
   */
  rtb_Sum = ctrl_DP_mss_P.Gain_Gain * rtb_Row1;

  /* Sum: '<S8>/Sum1' */
  rtb_Row3 += rtb_Sum;

  /* Math: '<S8>/Math Function' incorporates:
   *  Constant: '<S8>/Constant'
   */
  rtb_Row3 = rt_remd_snf(rtb_Row3, ctrl_DP_mss_P.Constant_Value_l);

  /* Sum: '<S8>/Sum' */
  rtb_Row3 -= rtb_Sum;

  /* Sum: '<S1>/Sum2' */
  rtb_MatrixMultiply1[0] = ctrl_DP_mss_B.Ctrl_X - ctrl_DP_mss_B.Ctrl_X_ref;
  rtb_MatrixMultiply1[1] = ctrl_DP_mss_B.Ctrl_Y - ctrl_DP_mss_B.Ctrl_Y_ref;
  rtb_MatrixMultiply1[2] = ctrl_DP_mss_B.Ctrl_PSI - ctrl_DP_mss_B.Ctrl_PSI_ref;

  /* Saturate: '<S7>/Saturation' */
  if (rtb_MatrixMultiply1[2] > ctrl_DP_mss_P.Saturation_UpperSat_p) {
    rtb_Sum = ctrl_DP_mss_P.Saturation_UpperSat_p;
  } else if (rtb_MatrixMultiply1[2] < ctrl_DP_mss_P.Saturation_LowerSat_i) {
    rtb_Sum = ctrl_DP_mss_P.Saturation_LowerSat_i;
  } else {
    rtb_Sum = rtb_MatrixMultiply1[2];
  }

  /* End of Saturate: '<S7>/Saturation' */

  /* Signum: '<S7>/Sign' */
  if (rtb_Sum < 0.0) {
    rtb_Row1 = -1.0;
  } else if (rtb_Sum > 0.0) {
    rtb_Row1 = 1.0;
  } else if (rtb_Sum == 0.0) {
    rtb_Row1 = 0.0;
  } else {
    rtb_Row1 = rtb_Sum;
  }

  /* Gain: '<S7>/Gain' incorporates:
   *  Signum: '<S7>/Sign'
   */
  rtb_Row1 *= ctrl_DP_mss_P.Gain_Gain_l;

  /* Sum: '<S7>/Sum1' */
  rtb_Sum += rtb_Row1;

  /* Math: '<S7>/Math Function' incorporates:
   *  Constant: '<S7>/Constant'
   */
  rtb_Sum = rt_remd_snf(rtb_Sum, ctrl_DP_mss_P.Constant_Value_g);

  /* Sum: '<S7>/Sum' */
  rtb_Sum -= rtb_Row1;

  /* SignalConversion: '<S1>/TmpSignal ConversionAtMatrix Multiply1Inport2' incorporates:
   *  Fcn: '<S6>/Row1'
   *  Fcn: '<S6>/Row2'
   *  Fcn: '<S6>/Row3'
   */
  ctrl_DP_mss_B.TmpSignalConversionAtMatrixMult[0] = cos(rtb_Row3) *
    rtb_MatrixMultiply1[0] + sin(rtb_Row3) * rtb_MatrixMultiply1[1];
  ctrl_DP_mss_B.TmpSignalConversionAtMatrixMult[1] = -sin(rtb_Row3) *
    rtb_MatrixMultiply1[0] + cos(rtb_Row3) * rtb_MatrixMultiply1[1];
  ctrl_DP_mss_B.TmpSignalConversionAtMatrixMult[2] = rtb_Sum;

  /* Product: '<S1>/Matrix Multiply1' */
  for (i = 0; i < 3; i++) {
    rtb_MatrixMultiply1[i] = ctrl_DP_mss_B.VectorConcatenate[i + 6] *
      ctrl_DP_mss_B.TmpSignalConversionAtMatrixMult[2] +
      (ctrl_DP_mss_B.VectorConcatenate[i + 3] *
       ctrl_DP_mss_B.TmpSignalConversionAtMatrixMult[1] +
       ctrl_DP_mss_B.VectorConcatenate[i] *
       ctrl_DP_mss_B.TmpSignalConversionAtMatrixMult[0]);
  }

  /* End of Product: '<S1>/Matrix Multiply1' */
  if (rtmIsMajorTimeStep(ctrl_DP_mss_M)) {
    /* Constant: '<S4>/Constant14' */
    ctrl_DP_mss_B.VectorConcatenate_l[1] = ctrl_DP_mss_P.Constant14_Value;

    /* Constant: '<S4>/Constant16' */
    ctrl_DP_mss_B.VectorConcatenate_l[2] = ctrl_DP_mss_P.Constant16_Value;

    /* Constant: '<S4>/Constant12' */
    ctrl_DP_mss_B.VectorConcatenate_l[3] = ctrl_DP_mss_P.Constant12_Value;

    /* Constant: '<S4>/Constant17' */
    ctrl_DP_mss_B.VectorConcatenate_l[5] = ctrl_DP_mss_P.Constant17_Value;

    /* Constant: '<S4>/Constant13' */
    ctrl_DP_mss_B.VectorConcatenate_l[6] = ctrl_DP_mss_P.Constant13_Value;

    /* Constant: '<S4>/Constant15' */
    ctrl_DP_mss_B.VectorConcatenate_l[7] = ctrl_DP_mss_P.Constant15_Value;
  }

  /* Integrator: '<S1>/Integrator' */
  if (rtmIsMajorTimeStep(ctrl_DP_mss_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                       &ctrl_DP_mss_PrevZCX.Integrator_Reset_ZCE,
                       ctrl_DP_mss_B.Reset_integrator);

    /* evaluate zero-crossings and the level of the reset signal */
    if (zcEvent || ctrl_DP_mss_B.Reset_integrator != 0.0) {
      ctrl_DP_mss_X.Integrator_CSTATE[0] = ctrl_DP_mss_P.Integrator_IC;
      ctrl_DP_mss_X.Integrator_CSTATE[1] = ctrl_DP_mss_P.Integrator_IC;
      ctrl_DP_mss_X.Integrator_CSTATE[2] = ctrl_DP_mss_P.Integrator_IC;
    }
  }

  rtb_MatrixMultiply[0] = ctrl_DP_mss_X.Integrator_CSTATE[0];
  rtb_MatrixMultiply[1] = ctrl_DP_mss_X.Integrator_CSTATE[1];
  rtb_MatrixMultiply[2] = ctrl_DP_mss_X.Integrator_CSTATE[2];

  /* Sum: '<S1>/Sum3' incorporates:
   *  Product: '<S1>/Matrix Multiply2'
   */
  for (i = 0; i < 3; i++) {
    rtb_Sum3[i] = ((ctrl_DP_mss_B.VectorConcatenate_l[i + 3] *
                    rtb_MatrixMultiply[1] + ctrl_DP_mss_B.VectorConcatenate_l[i]
                    * rtb_MatrixMultiply[0]) +
                   ctrl_DP_mss_B.VectorConcatenate_l[i + 6] *
                   rtb_MatrixMultiply[2]) + rtb_MatrixMultiply1[i];
  }

  /* End of Sum: '<S1>/Sum3' */
  if (rtmIsMajorTimeStep(ctrl_DP_mss_M)) {
    /* Constant: '<S3>/Constant2' */
    ctrl_DP_mss_B.VectorConcatenate_d[1] = ctrl_DP_mss_P.Constant2_Value;

    /* Constant: '<S3>/Constant4' */
    ctrl_DP_mss_B.VectorConcatenate_d[2] = ctrl_DP_mss_P.Constant4_Value;

    /* Constant: '<S3>/Constant' */
    ctrl_DP_mss_B.VectorConcatenate_d[3] = ctrl_DP_mss_P.Constant_Value_m;

    /* Constant: '<S3>/Constant5' */
    ctrl_DP_mss_B.VectorConcatenate_d[5] = ctrl_DP_mss_P.Constant5_Value;

    /* Constant: '<S3>/Constant1' */
    ctrl_DP_mss_B.VectorConcatenate_d[6] = ctrl_DP_mss_P.Constant1_Value_b;

    /* Constant: '<S3>/Constant3' */
    ctrl_DP_mss_B.VectorConcatenate_d[7] = ctrl_DP_mss_P.Constant3_Value;
  }

  /* Product: '<S1>/Matrix Multiply' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAtMatrix MultiplyInport2'
   */
  for (i = 0; i < 3; i++) {
    rtb_MatrixMultiply[i] = 0.0;
    rtb_MatrixMultiply[i] += ctrl_DP_mss_B.VectorConcatenate_d[i] *
      ctrl_DP_mss_B.Ctrl_u_surge;
    rtb_MatrixMultiply[i] += ctrl_DP_mss_B.VectorConcatenate_d[i + 3] *
      ctrl_DP_mss_B.Ctrl_v_sway;
    rtb_MatrixMultiply[i] += ctrl_DP_mss_B.VectorConcatenate_d[i + 6] *
      ctrl_DP_mss_B.Ctrl_r_yawrate;
  }

  /* End of Product: '<S1>/Matrix Multiply' */

  /* Sum: '<S1>/Sum1' */
  ctrl_DP_mss_B.Sum1[0] = rtb_Sum3[0] - rtb_MatrixMultiply[0];
  ctrl_DP_mss_B.Sum1[1] = rtb_Sum3[1] - rtb_MatrixMultiply[1];
  ctrl_DP_mss_B.Sum1[2] = rtb_Sum3[2] - rtb_MatrixMultiply[2];

  /* MATLAB Function: '<S2>/Thrust allocation' incorporates:
   *  Constant: '<S2>/Constant'
   */
  /* MATLAB Function 'Thruster allocation/Thrust allocation': '<S13>:1' */
  /* '<S13>:1:3' */
  rtb_Row3 = fabs(ctrl_DP_mss_B.Sum1[0]) + fabs(ctrl_DP_mss_B.Sum1[1]);

  /* '<S13>:1:6' */
  rtb_Sum = rt_atan2d_snf(ctrl_DP_mss_B.Sum1[1], ctrl_DP_mss_B.Sum1[0]);

  /* '<S13>:1:7' */
  /* '<S13>:1:9' */
  /* '<S13>:1:10' */
  /* '<S13>:1:11' */
  /* '<S13>:1:13' */
  ctrl_DP_mss_B.u_VSP = fabs(ctrl_DP_mss_B.Sum1[2]) /
    ctrl_DP_mss_P.Constant_Value_k + rtb_Row3;

  /* '<S13>:1:14' */
  if (-ctrl_DP_mss_B.Sum1[2] < 0.0) {
    rtb_Row1 = -1.0;
  } else if (-ctrl_DP_mss_B.Sum1[2] > 0.0) {
    rtb_Row1 = 1.0;
  } else if (-ctrl_DP_mss_B.Sum1[2] == 0.0) {
    rtb_Row1 = 0.0;
  } else {
    rtb_Row1 = -ctrl_DP_mss_B.Sum1[2];
  }

  ctrl_DP_mss_B.alpha_VSP = rtb_Row1 * 3.1415926535897931 / 2.0 + rtb_Sum;

  /* '<S13>:1:15' */
  ctrl_DP_mss_B.u_BT = rtb_Row3 * sin(rtb_Sum) * ctrl_DP_mss_P.Constant_Value_k /
    ctrl_DP_mss_P.Constant_Value_k + ctrl_DP_mss_B.Sum1[2] /
    ctrl_DP_mss_P.Constant_Value_k;

  /* End of MATLAB Function: '<S2>/Thrust allocation' */
  if (rtmIsMajorTimeStep(ctrl_DP_mss_M)) {
    /* Switch: '<S12>/Switch' incorporates:
     *  Constant: '<S12>/Constant'
     *  Constant: '<S12>/Constant1'
     */
    if (ctrl_DP_mss_B.Bool_VSP_omega_on_off != 0.0) {
      ctrl_DP_mss_B.Switch = ctrl_DP_mss_P.Constant1_Value;
    } else {
      ctrl_DP_mss_B.Switch = ctrl_DP_mss_P.Constant_Value;
    }

    /* End of Switch: '<S12>/Switch' */
  }
}

/* Model update function */
void ctrl_DP_mss_update(void)
{
  if (rtmIsMajorTimeStep(ctrl_DP_mss_M)) {
    rt_ertODEUpdateContinuousStates(&ctrl_DP_mss_M->solverInfo);
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
  if (!(++ctrl_DP_mss_M->Timing.clockTick0)) {
    ++ctrl_DP_mss_M->Timing.clockTickH0;
  }

  ctrl_DP_mss_M->Timing.t[0] = rtsiGetSolverStopTime(&ctrl_DP_mss_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.2s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++ctrl_DP_mss_M->Timing.clockTick1)) {
      ++ctrl_DP_mss_M->Timing.clockTickH1;
    }

    ctrl_DP_mss_M->Timing.t[1] = ctrl_DP_mss_M->Timing.clockTick1 *
      ctrl_DP_mss_M->Timing.stepSize1 + ctrl_DP_mss_M->Timing.clockTickH1 *
      ctrl_DP_mss_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void ctrl_DP_mss_derivatives(void)
{
  /* Derivatives for Integrator: '<S1>/Integrator' */
  {
    if (ctrl_DP_mss_B.Reset_integrator== 0.0) {
      ((XDot_ctrl_DP_mss_T *) ctrl_DP_mss_M->ModelData.derivs)
        ->Integrator_CSTATE[0] = ctrl_DP_mss_B.TmpSignalConversionAtMatrixMult[0];
    } else {
      /* level reset is active*/
      ((XDot_ctrl_DP_mss_T *) ctrl_DP_mss_M->ModelData.derivs)
        ->Integrator_CSTATE[0] = 0.0;
    }

    if (ctrl_DP_mss_B.Reset_integrator== 0.0) {
      ((XDot_ctrl_DP_mss_T *) ctrl_DP_mss_M->ModelData.derivs)
        ->Integrator_CSTATE[1] = ctrl_DP_mss_B.TmpSignalConversionAtMatrixMult[1];
    } else {
      /* level reset is active*/
      ((XDot_ctrl_DP_mss_T *) ctrl_DP_mss_M->ModelData.derivs)
        ->Integrator_CSTATE[1] = 0.0;
    }

    if (ctrl_DP_mss_B.Reset_integrator== 0.0) {
      ((XDot_ctrl_DP_mss_T *) ctrl_DP_mss_M->ModelData.derivs)
        ->Integrator_CSTATE[2] = ctrl_DP_mss_B.TmpSignalConversionAtMatrixMult[2];
    } else {
      /* level reset is active*/
      ((XDot_ctrl_DP_mss_T *) ctrl_DP_mss_M->ModelData.derivs)
        ->Integrator_CSTATE[2] = 0.0;
    }
  }
}

/* Model initialize function */
void ctrl_DP_mss_initialize(void)
{
  ctrl_DP_mss_PrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  ctrl_DP_mss_X.Integrator_CSTATE[0] = ctrl_DP_mss_P.Integrator_IC;
  ctrl_DP_mss_X.Integrator_CSTATE[1] = ctrl_DP_mss_P.Integrator_IC;
  ctrl_DP_mss_X.Integrator_CSTATE[2] = ctrl_DP_mss_P.Integrator_IC;
}

/* Model terminate function */
void ctrl_DP_mss_terminate(void)
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
  ctrl_DP_mss_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  ctrl_DP_mss_update();
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
  ctrl_DP_mss_initialize();
}

void MdlTerminate(void)
{
  ctrl_DP_mss_terminate();
}

/* Registration function */
RT_MODEL_ctrl_DP_mss_T *ctrl_DP_mss(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ctrl_DP_mss_M, 0,
                sizeof(RT_MODEL_ctrl_DP_mss_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&ctrl_DP_mss_M->solverInfo,
                          &ctrl_DP_mss_M->Timing.simTimeStep);
    rtsiSetTPtr(&ctrl_DP_mss_M->solverInfo, &rtmGetTPtr(ctrl_DP_mss_M));
    rtsiSetStepSizePtr(&ctrl_DP_mss_M->solverInfo,
                       &ctrl_DP_mss_M->Timing.stepSize0);
    rtsiSetdXPtr(&ctrl_DP_mss_M->solverInfo, &ctrl_DP_mss_M->ModelData.derivs);
    rtsiSetContStatesPtr(&ctrl_DP_mss_M->solverInfo, (real_T **)
                         &ctrl_DP_mss_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&ctrl_DP_mss_M->solverInfo,
      &ctrl_DP_mss_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&ctrl_DP_mss_M->solverInfo, (&rtmGetErrorStatus
      (ctrl_DP_mss_M)));
    rtsiSetRTModelPtr(&ctrl_DP_mss_M->solverInfo, ctrl_DP_mss_M);
  }

  rtsiSetSimTimeStep(&ctrl_DP_mss_M->solverInfo, MAJOR_TIME_STEP);
  ctrl_DP_mss_M->ModelData.intgData.y = ctrl_DP_mss_M->ModelData.odeY;
  ctrl_DP_mss_M->ModelData.intgData.f[0] = ctrl_DP_mss_M->ModelData.odeF[0];
  ctrl_DP_mss_M->ModelData.intgData.f[1] = ctrl_DP_mss_M->ModelData.odeF[1];
  ctrl_DP_mss_M->ModelData.intgData.f[2] = ctrl_DP_mss_M->ModelData.odeF[2];
  ctrl_DP_mss_M->ModelData.intgData.f[3] = ctrl_DP_mss_M->ModelData.odeF[3];
  ctrl_DP_mss_M->ModelData.contStates = ((real_T *) &ctrl_DP_mss_X);
  rtsiSetSolverData(&ctrl_DP_mss_M->solverInfo, (void *)
                    &ctrl_DP_mss_M->ModelData.intgData);
  rtsiSetSolverName(&ctrl_DP_mss_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ctrl_DP_mss_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    ctrl_DP_mss_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ctrl_DP_mss_M->Timing.sampleTimes = (&ctrl_DP_mss_M->
      Timing.sampleTimesArray[0]);
    ctrl_DP_mss_M->Timing.offsetTimes = (&ctrl_DP_mss_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    ctrl_DP_mss_M->Timing.sampleTimes[0] = (0.0);
    ctrl_DP_mss_M->Timing.sampleTimes[1] = (0.2);

    /* task offsets */
    ctrl_DP_mss_M->Timing.offsetTimes[0] = (0.0);
    ctrl_DP_mss_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(ctrl_DP_mss_M, &ctrl_DP_mss_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ctrl_DP_mss_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    ctrl_DP_mss_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ctrl_DP_mss_M, -1);
  ctrl_DP_mss_M->Timing.stepSize0 = 0.2;
  ctrl_DP_mss_M->Timing.stepSize1 = 0.2;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    ctrl_DP_mss_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ctrl_DP_mss_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(ctrl_DP_mss_M->rtwLogInfo, (NULL));
    rtliSetLogT(ctrl_DP_mss_M->rtwLogInfo, "tout");
    rtliSetLogX(ctrl_DP_mss_M->rtwLogInfo, "");
    rtliSetLogXFinal(ctrl_DP_mss_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(ctrl_DP_mss_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(ctrl_DP_mss_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(ctrl_DP_mss_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(ctrl_DP_mss_M->rtwLogInfo, 1);
    rtliSetLogY(ctrl_DP_mss_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(ctrl_DP_mss_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(ctrl_DP_mss_M->rtwLogInfo, (NULL));
  }

  ctrl_DP_mss_M->solverInfoPtr = (&ctrl_DP_mss_M->solverInfo);
  ctrl_DP_mss_M->Timing.stepSize = (0.2);
  rtsiSetFixedStepSize(&ctrl_DP_mss_M->solverInfo, 0.2);
  rtsiSetSolverMode(&ctrl_DP_mss_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  ctrl_DP_mss_M->ModelData.blockIO = ((void *) &ctrl_DP_mss_B);
  (void) memset(((void *) &ctrl_DP_mss_B), 0,
                sizeof(B_ctrl_DP_mss_T));

  /* parameters */
  ctrl_DP_mss_M->ModelData.defaultParam = ((real_T *)&ctrl_DP_mss_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &ctrl_DP_mss_X;
    ctrl_DP_mss_M->ModelData.contStates = (x);
    (void) memset((void *)&ctrl_DP_mss_X, 0,
                  sizeof(X_ctrl_DP_mss_T));
  }

  /* states (dwork) */
  ctrl_DP_mss_M->ModelData.dwork = ((void *) &ctrl_DP_mss_DW);
  (void) memset((void *)&ctrl_DP_mss_DW, 0,
                sizeof(DW_ctrl_DP_mss_T));

  /* Initialize Sizes */
  ctrl_DP_mss_M->Sizes.numContStates = (3);/* Number of continuous states */
  ctrl_DP_mss_M->Sizes.numY = (0);     /* Number of model outputs */
  ctrl_DP_mss_M->Sizes.numU = (0);     /* Number of model inputs */
  ctrl_DP_mss_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  ctrl_DP_mss_M->Sizes.numSampTimes = (2);/* Number of sample times */
  ctrl_DP_mss_M->Sizes.numBlocks = (86);/* Number of blocks */
  ctrl_DP_mss_M->Sizes.numBlockIO = (20);/* Number of block outputs */
  ctrl_DP_mss_M->Sizes.numBlockPrms = (210);/* Sum of parameter "widths" */
  return ctrl_DP_mss_M;
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
#ifdef NI_ROOTMODEL_ctrl_DP_mss
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
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 18:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 19:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 20:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 21:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 22:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 23:
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 31:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 32:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);
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
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 31:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 32:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern ctrl_DP_mss_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // DP controller/Proportional gain/Ctrl_K_p_psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.VectorConcatenate, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // DP controller/Proportional gain/Ctrl_K_p_x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.VectorConcatenate, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // DP controller/Proportional gain/Ctrl_K_p_y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.VectorConcatenate, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Ctrl_X
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Ctrl_X, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_Y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Ctrl_Y, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_PSI
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Ctrl_PSI, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_X_ref
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Ctrl_X_ref, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_Y_ref
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Ctrl_Y_ref, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_PSI_ref
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Ctrl_PSI_ref, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // DP controller/Integral  gain/Ctrl_K_i_psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.VectorConcatenate_l, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // DP controller/Integral  gain/Ctrl_K_i_x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.VectorConcatenate_l, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // DP controller/Integral  gain/Ctrl_K_i_y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.VectorConcatenate_l, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // DP controller/Reset_integrator
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Reset_integrator, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // DP controller/Derivative gain/Ctrl_K_d_X
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.VectorConcatenate_d, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // DP controller/Derivative gain/Ctrl_K_d_psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.VectorConcatenate_d, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // DP controller/Derivative gain/Ctrl_K_d_y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.VectorConcatenate_d, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Ctrl_u_surge
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Ctrl_u_surge, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_v_sway
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Ctrl_v_sway, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Ctrl_r_yawrate
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Ctrl_r_yawrate, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Thruster allocation/Set_omega_VSP/Bool_VSP_omega_on_off
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_DP_mss_B.Bool_VSP_omega_on_off, 0, data[index
      ++], 0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 20;
}

double ni_extout[10];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Ctrl_tau_x: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Sum1,0,18,0);
  } else {
    index += 1;
  }

  // Ctrl_tau_y: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Sum1,1,18,0);
  } else {
    index += 1;
  }

  // Ctrl_tau_psi: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Sum1,2,18,0);
  } else {
    index += 1;
  }

  // Ctrl_U_BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.u_BT,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_omega_vsp1: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Switch,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_omega_vsp2: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Switch,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_U_1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.u_VSP,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_U_2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.u_VSP,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_alpha_1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.alpha_VSP,0,0,0);
  } else {
    index += 1;
  }

  // Ctrl_alpha_2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.alpha_VSP,0,0,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 10;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

  // Ctrl_tau_x: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Sum1,0,18,0);

  // Ctrl_tau_y: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Sum1,1,18,0);

  // Ctrl_tau_psi: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Sum1,2,18,0);

  // Ctrl_U_BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.u_BT,0,0,0);

  // Ctrl_omega_vsp1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Switch,0,0,0);

  // Ctrl_omega_vsp2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.Switch,0,0,0);

  // Ctrl_U_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.u_VSP,0,0,0);

  // Ctrl_U_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.u_VSP,0,0,0);

  // Ctrl_alpha_1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.alpha_VSP,0,0,0);

  // Ctrl_alpha_2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_DP_mss_B.alpha_VSP,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "ctrl_dp_mss/Thruster allocation/Set_omega_VSP/Constant/Value", offsetof
    (P_ctrl_DP_mss_T, Constant_Value), 31, 1, 2, 0, 0 },

  { 1, "ctrl_dp_mss/Thruster allocation/Set_omega_VSP/Constant1/Value", offsetof
    (P_ctrl_DP_mss_T, Constant1_Value), 31, 1, 2, 2, 0 },

  { 2, "ctrl_dp_mss/DP controller/Proportional gain/Constant8/Value", offsetof
    (P_ctrl_DP_mss_T, Constant8_Value), 31, 1, 2, 4, 0 },

  { 3, "ctrl_dp_mss/DP controller/Proportional gain/Constant10/Value", offsetof
    (P_ctrl_DP_mss_T, Constant10_Value), 31, 1, 2, 6, 0 },

  { 4, "ctrl_dp_mss/DP controller/Proportional gain/Constant6/Value", offsetof
    (P_ctrl_DP_mss_T, Constant6_Value), 31, 1, 2, 8, 0 },

  { 5, "ctrl_dp_mss/DP controller/Proportional gain/Constant11/Value", offsetof
    (P_ctrl_DP_mss_T, Constant11_Value), 31, 1, 2, 10, 0 },

  { 6, "ctrl_dp_mss/DP controller/Proportional gain/Constant7/Value", offsetof
    (P_ctrl_DP_mss_T, Constant7_Value), 31, 1, 2, 12, 0 },

  { 7, "ctrl_dp_mss/DP controller/Proportional gain/Constant9/Value", offsetof
    (P_ctrl_DP_mss_T, Constant9_Value), 31, 1, 2, 14, 0 },

  { 8, "ctrl_dp_mss/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(P_ctrl_DP_mss_T, Saturation_UpperSat), 31, 1, 2, 16, 0 },

  { 9, "ctrl_dp_mss/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(P_ctrl_DP_mss_T, Saturation_LowerSat), 31, 1, 2, 18, 0 },

  { 10, "ctrl_dp_mss/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain", offsetof
    (P_ctrl_DP_mss_T, Gain_Gain), 31, 1, 2, 20, 0 },

  { 11, "ctrl_dp_mss/DP controller/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(P_ctrl_DP_mss_T, Constant_Value_l), 31, 1, 2, 22, 0 },

  { 12, "ctrl_dp_mss/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(P_ctrl_DP_mss_T, Saturation_UpperSat_p), 31, 1, 2, 24, 0 },

  { 13, "ctrl_dp_mss/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(P_ctrl_DP_mss_T, Saturation_LowerSat_i), 31, 1, 2, 26, 0 },

  { 14, "ctrl_dp_mss/DP controller/[-inf inf] to [-pi pi]/Gain/Gain", offsetof
    (P_ctrl_DP_mss_T, Gain_Gain_l), 31, 1, 2, 28, 0 },

  { 15, "ctrl_dp_mss/DP controller/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(P_ctrl_DP_mss_T, Constant_Value_g), 31, 1, 2, 30, 0 },

  { 16, "ctrl_dp_mss/DP controller/Integral  gain/Constant14/Value", offsetof
    (P_ctrl_DP_mss_T, Constant14_Value), 31, 1, 2, 32, 0 },

  { 17, "ctrl_dp_mss/DP controller/Integral  gain/Constant16/Value", offsetof
    (P_ctrl_DP_mss_T, Constant16_Value), 31, 1, 2, 34, 0 },

  { 18, "ctrl_dp_mss/DP controller/Integral  gain/Constant12/Value", offsetof
    (P_ctrl_DP_mss_T, Constant12_Value), 31, 1, 2, 36, 0 },

  { 19, "ctrl_dp_mss/DP controller/Integral  gain/Constant17/Value", offsetof
    (P_ctrl_DP_mss_T, Constant17_Value), 31, 1, 2, 38, 0 },

  { 20, "ctrl_dp_mss/DP controller/Integral  gain/Constant13/Value", offsetof
    (P_ctrl_DP_mss_T, Constant13_Value), 31, 1, 2, 40, 0 },

  { 21, "ctrl_dp_mss/DP controller/Integral  gain/Constant15/Value", offsetof
    (P_ctrl_DP_mss_T, Constant15_Value), 31, 1, 2, 42, 0 },

  { 22, "ctrl_dp_mss/DP controller/Integrator/InitialCondition", offsetof
    (P_ctrl_DP_mss_T, Integrator_IC), 31, 1, 2, 44, 0 },

  { 23, "ctrl_dp_mss/DP controller/Derivative gain/Constant2/Value", offsetof
    (P_ctrl_DP_mss_T, Constant2_Value), 31, 1, 2, 46, 0 },

  { 24, "ctrl_dp_mss/DP controller/Derivative gain/Constant4/Value", offsetof
    (P_ctrl_DP_mss_T, Constant4_Value), 31, 1, 2, 48, 0 },

  { 25, "ctrl_dp_mss/DP controller/Derivative gain/Constant/Value", offsetof
    (P_ctrl_DP_mss_T, Constant_Value_m), 31, 1, 2, 50, 0 },

  { 26, "ctrl_dp_mss/DP controller/Derivative gain/Constant5/Value", offsetof
    (P_ctrl_DP_mss_T, Constant5_Value), 31, 1, 2, 52, 0 },

  { 27, "ctrl_dp_mss/DP controller/Derivative gain/Constant1/Value", offsetof
    (P_ctrl_DP_mss_T, Constant1_Value_b), 31, 1, 2, 54, 0 },

  { 28, "ctrl_dp_mss/DP controller/Derivative gain/Constant3/Value", offsetof
    (P_ctrl_DP_mss_T, Constant3_Value), 31, 1, 2, 56, 0 },

  { 29, "ctrl_dp_mss/Thruster allocation/Constant/Value", offsetof
    (P_ctrl_DP_mss_T, Constant_Value_k), 31, 1, 2, 58, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 30;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  1, 1,                                /* Parameter at index 0 */
  1, 1,                                /* Parameter at index 1 */
  1, 1,                                /* Parameter at index 2 */
  1, 1,                                /* Parameter at index 3 */
  1, 1,                                /* Parameter at index 4 */
  1, 1,                                /* Parameter at index 5 */
  1, 1,                                /* Parameter at index 6 */
  1, 1,                                /* Parameter at index 7 */
  1, 1,                                /* Parameter at index 8 */
  1, 1,                                /* Parameter at index 9 */
  1, 1,                                /* Parameter at index 10 */
  1, 1,                                /* Parameter at index 11 */
  1, 1,                                /* Parameter at index 12 */
  1, 1,                                /* Parameter at index 13 */
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
  1, 1,                                /* Parameter at index 24 */
  1, 1,                                /* Parameter at index 25 */
  1, 1,                                /* Parameter at index 26 */
  1, 1,                                /* Parameter at index 27 */
  1, 1,                                /* Parameter at index 28 */
  1, 1,                                /* Parameter at index 29 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0,
    "ctrl_dp_mss/DP controller/Proportional gain/Create 3x3 Matrix1/Vector Concatenate",
    0, "(1,1)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate)+0*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 0, 0 },

  { 1,
    "ctrl_dp_mss/DP controller/Proportional gain/Create 3x3 Matrix1/Vector Concatenate",
    0, "(1,2)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate)+1*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 2, 0 },

  { 2,
    "ctrl_dp_mss/DP controller/Proportional gain/Create 3x3 Matrix1/Vector Concatenate",
    0, "(1,3)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate)+2*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 4, 0 },

  { 3,
    "ctrl_dp_mss/DP controller/Proportional gain/Create 3x3 Matrix1/Vector Concatenate",
    0, "(1,4)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate)+3*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 6, 0 },

  { 4,
    "ctrl_dp_mss/DP controller/Proportional gain/Create 3x3 Matrix1/Vector Concatenate",
    0, "(1,5)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate)+4*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 8, 0 },

  { 5,
    "ctrl_dp_mss/DP controller/Proportional gain/Create 3x3 Matrix1/Vector Concatenate",
    0, "(1,6)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate)+5*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 10, 0 },

  { 6,
    "ctrl_dp_mss/DP controller/Proportional gain/Create 3x3 Matrix1/Vector Concatenate",
    0, "(1,7)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate)+6*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 12, 0 },

  { 7,
    "ctrl_dp_mss/DP controller/Proportional gain/Create 3x3 Matrix1/Vector Concatenate",
    0, "(1,8)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate)+7*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 14, 0 },

  { 8,
    "ctrl_dp_mss/DP controller/Proportional gain/Create 3x3 Matrix1/Vector Concatenate",
    0, "(1,9)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate)+8*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 16, 0 },

  { 9, "ctrl_dp_mss/Ctrl_X", 0, "", offsetof(B_ctrl_DP_mss_T, Ctrl_X)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "ctrl_dp_mss/Ctrl_Y", 0, "", offsetof(B_ctrl_DP_mss_T, Ctrl_Y)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "ctrl_dp_mss/Ctrl_PSI", 0, "", offsetof(B_ctrl_DP_mss_T, Ctrl_PSI)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "ctrl_dp_mss/Ctrl_X_ref", 0, "", offsetof(B_ctrl_DP_mss_T, Ctrl_X_ref)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "ctrl_dp_mss/Ctrl_Y_ref", 0, "", offsetof(B_ctrl_DP_mss_T, Ctrl_Y_ref)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "ctrl_dp_mss/Ctrl_PSI_ref", 0, "", offsetof(B_ctrl_DP_mss_T,
    Ctrl_PSI_ref)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 28, 0 },

  { 15,
    "ctrl_dp_mss/DP controller/Integral  gain/Create 3x3 Matrix2/Vector Concatenate",
    0, "(1,1)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_l)+0*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 30, 0 },

  { 16,
    "ctrl_dp_mss/DP controller/Integral  gain/Create 3x3 Matrix2/Vector Concatenate",
    0, "(1,2)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_l)+1*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 32, 0 },

  { 17,
    "ctrl_dp_mss/DP controller/Integral  gain/Create 3x3 Matrix2/Vector Concatenate",
    0, "(1,3)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_l)+2*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 34, 0 },

  { 18,
    "ctrl_dp_mss/DP controller/Integral  gain/Create 3x3 Matrix2/Vector Concatenate",
    0, "(1,4)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_l)+3*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 36, 0 },

  { 19,
    "ctrl_dp_mss/DP controller/Integral  gain/Create 3x3 Matrix2/Vector Concatenate",
    0, "(1,5)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_l)+4*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 38, 0 },

  { 20,
    "ctrl_dp_mss/DP controller/Integral  gain/Create 3x3 Matrix2/Vector Concatenate",
    0, "(1,6)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_l)+5*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 40, 0 },

  { 21,
    "ctrl_dp_mss/DP controller/Integral  gain/Create 3x3 Matrix2/Vector Concatenate",
    0, "(1,7)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_l)+6*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 42, 0 },

  { 22,
    "ctrl_dp_mss/DP controller/Integral  gain/Create 3x3 Matrix2/Vector Concatenate",
    0, "(1,8)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_l)+7*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 44, 0 },

  { 23,
    "ctrl_dp_mss/DP controller/Integral  gain/Create 3x3 Matrix2/Vector Concatenate",
    0, "(1,9)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_l)+8*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 46, 0 },

  { 24, "ctrl_dp_mss/DP controller/Reset_integrator", 0, "", offsetof
    (B_ctrl_DP_mss_T, Reset_integrator)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    48, 0 },

  { 25,
    "ctrl_dp_mss/DP controller/Derivative gain/Create 3x3 Matrix/Vector Concatenate",
    0, "(1,1)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_d)+0*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 50, 0 },

  { 26,
    "ctrl_dp_mss/DP controller/Derivative gain/Create 3x3 Matrix/Vector Concatenate",
    0, "(1,2)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_d)+1*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 52, 0 },

  { 27,
    "ctrl_dp_mss/DP controller/Derivative gain/Create 3x3 Matrix/Vector Concatenate",
    0, "(1,3)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_d)+2*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 54, 0 },

  { 28,
    "ctrl_dp_mss/DP controller/Derivative gain/Create 3x3 Matrix/Vector Concatenate",
    0, "(1,4)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_d)+3*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 56, 0 },

  { 29,
    "ctrl_dp_mss/DP controller/Derivative gain/Create 3x3 Matrix/Vector Concatenate",
    0, "(1,5)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_d)+4*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 58, 0 },

  { 30,
    "ctrl_dp_mss/DP controller/Derivative gain/Create 3x3 Matrix/Vector Concatenate",
    0, "(1,6)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_d)+5*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 60, 0 },

  { 31,
    "ctrl_dp_mss/DP controller/Derivative gain/Create 3x3 Matrix/Vector Concatenate",
    0, "(1,7)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_d)+6*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 62, 0 },

  { 32,
    "ctrl_dp_mss/DP controller/Derivative gain/Create 3x3 Matrix/Vector Concatenate",
    0, "(1,8)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_d)+7*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 64, 0 },

  { 33,
    "ctrl_dp_mss/DP controller/Derivative gain/Create 3x3 Matrix/Vector Concatenate",
    0, "(1,9)", offsetof(B_ctrl_DP_mss_T, VectorConcatenate_d)+8*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 66, 0 },

  { 34, "ctrl_dp_mss/Ctrl_u_surge", 0, "", offsetof(B_ctrl_DP_mss_T,
    Ctrl_u_surge)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35, "ctrl_dp_mss/Ctrl_v_sway", 0, "", offsetof(B_ctrl_DP_mss_T, Ctrl_v_sway)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36, "ctrl_dp_mss/Ctrl_r_yawrate", 0, "", offsetof(B_ctrl_DP_mss_T,
    Ctrl_r_yawrate)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37, "ctrl_dp_mss/DP controller/Sum1", 0, "(1,1)", offsetof(B_ctrl_DP_mss_T,
    Sum1)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 74, 0 },

  { 38, "ctrl_dp_mss/DP controller/Sum1", 0, "(1,2)", offsetof(B_ctrl_DP_mss_T,
    Sum1)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 76, 0 },

  { 39, "ctrl_dp_mss/DP controller/Sum1", 0, "(1,3)", offsetof(B_ctrl_DP_mss_T,
    Sum1)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 78, 0 },

  { 40, "ctrl_dp_mss/Thruster allocation/Set_omega_VSP/Bool_VSP_omega_on_off", 0,
    "", offsetof(B_ctrl_DP_mss_T, Bool_VSP_omega_on_off)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 80, 0 },

  { 41, "ctrl_dp_mss/Thruster allocation/Set_omega_VSP/Switch", 0, "", offsetof
    (B_ctrl_DP_mss_T, Switch)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42, "ctrl_dp_mss/Thruster allocation/Thrust allocation", 0, "u_BT", offsetof
    (B_ctrl_DP_mss_T, u_BT)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43, "ctrl_dp_mss/Thruster allocation/Thrust allocation", 1, "u_VSP",
    offsetof(B_ctrl_DP_mss_T, u_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 86,
    0 },

  { 44, "ctrl_dp_mss/Thruster allocation/Thrust allocation", 2, "alpha_VSP",
    offsetof(B_ctrl_DP_mss_T, alpha_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    88, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 45;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 30;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "DP controller/Proportional gain/Ctrl_K_p_psi", 0, EXT_IN, 1, 1, 1 },

  { 1, "DP controller/Proportional gain/Ctrl_K_p_x", 0, EXT_IN, 1, 1, 1 },

  { 2, "DP controller/Proportional gain/Ctrl_K_p_y", 0, EXT_IN, 1, 1, 1 },

  { 3, "Ctrl_X", 0, EXT_IN, 1, 1, 1 },

  { 4, "Ctrl_Y", 0, EXT_IN, 1, 1, 1 },

  { 5, "Ctrl_PSI", 0, EXT_IN, 1, 1, 1 },

  { 6, "Ctrl_X_ref", 0, EXT_IN, 1, 1, 1 },

  { 7, "Ctrl_Y_ref", 0, EXT_IN, 1, 1, 1 },

  { 8, "Ctrl_PSI_ref", 0, EXT_IN, 1, 1, 1 },

  { 9, "DP controller/Integral  gain/Ctrl_K_i_psi", 0, EXT_IN, 1, 1, 1 },

  { 10, "DP controller/Integral  gain/Ctrl_K_i_x", 0, EXT_IN, 1, 1, 1 },

  { 11, "DP controller/Integral  gain/Ctrl_K_i_y", 0, EXT_IN, 1, 1, 1 },

  { 12, "DP controller/Reset_integrator", 0, EXT_IN, 1, 1, 1 },

  { 13, "DP controller/Derivative gain/Ctrl_K_d_X", 0, EXT_IN, 1, 1, 1 },

  { 14, "DP controller/Derivative gain/Ctrl_K_d_psi", 0, EXT_IN, 1, 1, 1 },

  { 15, "DP controller/Derivative gain/Ctrl_K_d_y", 0, EXT_IN, 1, 1, 1 },

  { 16, "Ctrl_u_surge", 0, EXT_IN, 1, 1, 1 },

  { 17, "Ctrl_v_sway", 0, EXT_IN, 1, 1, 1 },

  { 18, "Ctrl_r_yawrate", 0, EXT_IN, 1, 1, 1 },

  { 19, "Thruster allocation/Set_omega_VSP/Bool_VSP_omega_on_off", 1, EXT_IN, 1,
    1, 1 },

  { 0, "Ctrl_tau_x", 0, EXT_OUT, 1, 1, 1 },

  { 1, "Ctrl_tau_y", 0, EXT_OUT, 1, 1, 1 },

  { 2, "Ctrl_tau_psi", 0, EXT_OUT, 1, 1, 1 },

  { 3, "Ctrl_U_BT", 0, EXT_OUT, 1, 1, 1 },

  { 4, "Ctrl_omega_vsp1", 1, EXT_OUT, 1, 1, 1 },

  { 5, "Ctrl_omega_vsp2", 1, EXT_OUT, 1, 1, 1 },

  { 6, "Ctrl_U_1", 0, EXT_OUT, 1, 1, 1 },

  { 7, "Ctrl_U_2", 0, EXT_OUT, 1, 1, 1 },

  { 8, "Ctrl_alpha_1", 0, EXT_OUT, 1, 1, 1 },

  { 9, "Ctrl_alpha_2", 0, EXT_OUT, 1, 1, 1 },

  { -1, "", 0, 0, 0, 0, 0 }
};

/* This Task List is generated to allow access to the task specs without
 * initializing the model.
 * 0th entry is for scheduler (base rate)
 * rest for multirate model's tasks.
 */
NI_Task NI_TaskList[] DataSection(".NIVS.tasklist") =
{
  { 0, 0.2, 0 }
};

int NI_NumTasks DataSection(".NIVS.numtasks") = 1;
static char* NI_CompiledModelName DataSection(".NIVS.compiledmodelname") =
  "ctrl_dp_mss";
static char* NI_CompiledModelVersion = "1.10";
static char* NI_CompiledModelDateTime = "Wed Jan 28 18:35:58 2015";
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
   The undef allows us to access the real ctrl_DP_mss_P
   In the rest of the code ctrl_DP_mss_P is redefine to be the read-side
   of rtParameter.
 */
#undef ctrl_DP_mss_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &ctrl_DP_mss_P, sizeof(P_ctrl_DP_mss_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka ctrl_DP_mss_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_ctrl_DP_mss_T));
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
             (P_ctrl_DP_mss_T));
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
               (P_ctrl_DP_mss_T));

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
           (P_ctrl_DP_mss_T));
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
           (P_ctrl_DP_mss_T));
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
           (P_ctrl_DP_mss_T));
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
      *numContStates = 3;
      *numDiscStates = 390;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (contStates && contStatesNames) {
    idx = 0;
    contStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_X.Integrator_CSTATE[0],
      0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_X.Integrator_CSTATE[0],
      1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_X.Integrator_CSTATE[0],
      2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_K_p_psi_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_K_p_psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_p_x_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_K_p_x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_p_y_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_K_p_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_X_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_X_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_Y_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_Y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_PSI_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_PSI_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_X_ref_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_X_ref_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_Y_ref_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_Y_ref_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_PSI_ref_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_PSI_ref_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_K_i_psi_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_K_i_psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_i_x_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_K_i_x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_i_y_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_K_i_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Reset_integrator_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Reset_integrator_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_d_X_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_K_d_X_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_K_d_psi_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_K_d_psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_d_y_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_K_d_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_u_surge_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_u_surge_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_v_sway_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_v_sway_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_r_yawrate_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_r_yawrate_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_tau_x_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_tau_x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_tau_y_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_tau_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_tau_psi_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_tau_psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_BT_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_U_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Bool_VSP_omega_on_off_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Bool_VSP_omega_on_off_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_omega_vsp1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_omega_vsp1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_omega_vsp2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_omega_vsp2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_U_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_2_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_U_2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_alpha_1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_alpha_1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_DP_mss_DW.Ctrl_alpha_2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_DP_mss_DW.Ctrl_alpha_2_DWORK1");
    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_K_p_psi_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_K_p_psi_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_K_p_x_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_K_p_x_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_K_p_y_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_K_p_y_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_X_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_X_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_Y_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_Y_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_PSI_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_PSI_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_X_ref_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_X_ref_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_Y_ref_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_Y_ref_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_PSI_ref_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_PSI_ref_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_K_i_psi_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_K_i_psi_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_K_i_x_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_K_i_x_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_K_i_y_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_K_i_y_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Reset_integrator_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Reset_integrator_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_K_d_X_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_K_d_X_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_K_d_psi_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_K_d_psi_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_K_d_y_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_K_d_y_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_u_surge_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_u_surge_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_v_sway_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_v_sway_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_r_yawrate_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_r_yawrate_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_tau_x_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_tau_x_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_tau_y_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_tau_y_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_tau_psi_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_tau_psi_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_BT_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_U_BT_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Bool_VSP_omega_on_off_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Bool_VSP_omega_on_off_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_omega_vsp1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_omega_vsp1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_omega_vsp2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_omega_vsp2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_1_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_U_1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_2_DWORK2,
        count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_DP_mss_DW.Ctrl_U_2_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_alpha_1_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_alpha_1_DWORK2");
    }

    for (count = 0; count < 12; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_DP_mss_DW.Ctrl_alpha_2_DWORK2, count, 17, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_DP_mss_DW.Ctrl_alpha_2_DWORK2");
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
    NIRT_SetValueByDataType(&ctrl_DP_mss_X.Integrator_CSTATE[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_X.Integrator_CSTATE[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_X.Integrator_CSTATE[0], 2,
      contStates[idx++], 0, 0);
  }

  if (discStates) {
    idx = 0;
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_p_psi_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_p_x_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_p_y_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_X_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_Y_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_PSI_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_X_ref_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_Y_ref_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_PSI_ref_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_i_psi_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_i_x_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_i_y_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Reset_integrator_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_d_X_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_d_psi_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_d_y_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_u_surge_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_v_sway_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_r_yawrate_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_tau_x_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_tau_y_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_tau_psi_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_BT_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Bool_VSP_omega_on_off_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_omega_vsp1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_omega_vsp2_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_2_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_alpha_1_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_alpha_2_DWORK1, 0,
      discStates[idx++], 0, 0);
    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_p_psi_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_p_x_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_p_y_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_X_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_Y_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_PSI_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_X_ref_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_Y_ref_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_PSI_ref_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_i_psi_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_i_x_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_i_y_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Reset_integrator_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_d_X_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_d_psi_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_K_d_y_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_u_surge_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_v_sway_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_r_yawrate_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_tau_x_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_tau_y_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_tau_psi_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_BT_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Bool_VSP_omega_on_off_DWORK2,
        count, discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_omega_vsp1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_omega_vsp2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_U_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_alpha_1_DWORK2, count,
        discStates[idx++], 17, 0);
    }

    for (count = 0; count < 12; count++) {
      NIRT_SetValueByDataType(&ctrl_DP_mss_DW.Ctrl_alpha_2_DWORK2, count,
        discStates[idx++], 17, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
    S->Timing.clockTick1 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_ctrl_DP_mss
