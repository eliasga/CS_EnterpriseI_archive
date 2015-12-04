/*
 * NonlinearPassiveObserver.c
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

/* Block signals (auto storage) */
B_NonlinearPassiveObserver_T NonlinearPassiveObserver_B;

/* Continuous states */
X_NonlinearPassiveObserver_T NonlinearPassiveObserver_X;

/* Block states (auto storage) */
DW_NonlinearPassiveObserver_T NonlinearPassiveObserver_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_NonlinearPassiveObser_T NonlinearPassiveObserve_PrevZCX;

/* Real-time model */
RT_MODEL_NonlinearPassiveObse_T NonlinearPassiveObserver_M_;
RT_MODEL_NonlinearPassiveObse_T *const NonlinearPassiveObserver_M =
  &NonlinearPassiveObserver_M_;

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
  NonlinearPassiveObserver_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  NonlinearPassiveObserver_output();
  NonlinearPassiveObserver_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  NonlinearPassiveObserver_output();
  NonlinearPassiveObserver_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  NonlinearPassiveObserver_output();
  NonlinearPassiveObserver_derivatives();

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

/* Model output function */
void NonlinearPassiveObserver_output(void)
{
  real_T b_y0;
  real_T tau[3];
  static const real_T a[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, -0.4575, 0.0, 1.0,
    0.3875 };

  real_T D_NL[9];
  real_T x[9];
  real_T rtb_psi_dot;
  real_T rtb_Row1_j;
  real_T rtb_Row1;
  real_T rtb_Row2;
  real_T rtb_Row3;
  real_T rtb_TmpSignalConversionAtSFunct[3];
  real_T rtb_K_d[9];
  int32_T i;
  real_T tmp[3];
  real_T tau_0[3];
  real_T rtb_Row1_0[3];
  real_T rtb_Sum_idx_2;
  real_T rtb_Sum_idx_0;
  real_T rtb_Sum_idx_1;
  real_T unnamed_idx_0;
  if (rtmIsMajorTimeStep(NonlinearPassiveObserver_M)) {
    /* set solver stop time */
    if (!(NonlinearPassiveObserver_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&NonlinearPassiveObserver_M->solverInfo,
                            ((NonlinearPassiveObserver_M->Timing.clockTickH0 + 1)
        * NonlinearPassiveObserver_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&NonlinearPassiveObserver_M->solverInfo,
                            ((NonlinearPassiveObserver_M->Timing.clockTick0 + 1)
        * NonlinearPassiveObserver_M->Timing.stepSize0 +
        NonlinearPassiveObserver_M->Timing.clockTickH0 *
        NonlinearPassiveObserver_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(NonlinearPassiveObserver_M)) {
    NonlinearPassiveObserver_M->Timing.t[0] = rtsiGetT
      (&NonlinearPassiveObserver_M->solverInfo);
  }

  /* Integrator: '<S1>/Integrator2' */
  if (rtmIsMajorTimeStep(NonlinearPassiveObserver_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                       &NonlinearPassiveObserve_PrevZCX.Integrator2_Reset_ZCE,
                       NonlinearPassiveObserver_B.reset);

    /* evaluate zero-crossings */
    if (zcEvent) {
      NonlinearPassiveObserver_X.Integrator2_CSTATE[0] =
        (NonlinearPassiveObserver_P.Integrator2_IC[0]);
      NonlinearPassiveObserver_X.Integrator2_CSTATE[1] =
        (NonlinearPassiveObserver_P.Integrator2_IC[1]);
      NonlinearPassiveObserver_X.Integrator2_CSTATE[2] =
        (NonlinearPassiveObserver_P.Integrator2_IC[2]);
    }
  }

  NonlinearPassiveObserver_B.Integrator2[0] =
    NonlinearPassiveObserver_X.Integrator2_CSTATE[0];
  NonlinearPassiveObserver_B.Integrator2[1] =
    NonlinearPassiveObserver_X.Integrator2_CSTATE[1];
  NonlinearPassiveObserver_B.Integrator2[2] =
    NonlinearPassiveObserver_X.Integrator2_CSTATE[2];

  /* Integrator: '<S1>/Integrator' */
  if (rtmIsMajorTimeStep(NonlinearPassiveObserver_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                       &NonlinearPassiveObserve_PrevZCX.Integrator_Reset_ZCE,
                       NonlinearPassiveObserver_B.reset);

    /* evaluate zero-crossings */
    if (zcEvent || NonlinearPassiveObserver_DW.Integrator_IWORK.IcNeedsLoading)
    {
      NonlinearPassiveObserver_X.Integrator_CSTATE[0] =
        NonlinearPassiveObserver_B.x;
      NonlinearPassiveObserver_X.Integrator_CSTATE[1] =
        NonlinearPassiveObserver_B.y;
      NonlinearPassiveObserver_X.Integrator_CSTATE[2] =
        NonlinearPassiveObserver_B.psi;
    }
  }

  NonlinearPassiveObserver_B.Integrator[0] =
    NonlinearPassiveObserver_X.Integrator_CSTATE[0];
  NonlinearPassiveObserver_B.Integrator[1] =
    NonlinearPassiveObserver_X.Integrator_CSTATE[1];
  NonlinearPassiveObserver_B.Integrator[2] =
    NonlinearPassiveObserver_X.Integrator_CSTATE[2];

  /* Saturate: '<S15>/Saturation' */
  if (NonlinearPassiveObserver_B.Integrator[2] >
      NonlinearPassiveObserver_P.Saturation_UpperSat) {
    rtb_psi_dot = NonlinearPassiveObserver_P.Saturation_UpperSat;
  } else if (NonlinearPassiveObserver_B.Integrator[2] <
             NonlinearPassiveObserver_P.Saturation_LowerSat) {
    rtb_psi_dot = NonlinearPassiveObserver_P.Saturation_LowerSat;
  } else {
    rtb_psi_dot = NonlinearPassiveObserver_B.Integrator[2];
  }

  /* End of Saturate: '<S15>/Saturation' */

  /* Signum: '<S15>/Sign' */
  if (rtb_psi_dot < 0.0) {
    b_y0 = -1.0;
  } else if (rtb_psi_dot > 0.0) {
    b_y0 = 1.0;
  } else if (rtb_psi_dot == 0.0) {
    b_y0 = 0.0;
  } else {
    b_y0 = rtb_psi_dot;
  }

  /* Gain: '<S15>/Gain' incorporates:
   *  Signum: '<S15>/Sign'
   */
  rtb_Row1_j = NonlinearPassiveObserver_P.Gain_Gain * b_y0;

  /* Sum: '<S15>/Sum1' */
  rtb_psi_dot += rtb_Row1_j;

  /* Math: '<S15>/Math Function' incorporates:
   *  Constant: '<S15>/Constant'
   */
  rtb_psi_dot = rt_remd_snf(rtb_psi_dot,
    NonlinearPassiveObserver_P.Constant_Value);

  /* Sum: '<S15>/Sum' */
  NonlinearPassiveObserver_B.Sum = rtb_psi_dot - rtb_Row1_j;

  /* Saturate: '<S16>/Saturation' */
  if (NonlinearPassiveObserver_B.psi >
      NonlinearPassiveObserver_P.Saturation_UpperSat_f) {
    rtb_Row1_j = NonlinearPassiveObserver_P.Saturation_UpperSat_f;
  } else if (NonlinearPassiveObserver_B.psi <
             NonlinearPassiveObserver_P.Saturation_LowerSat_d) {
    rtb_Row1_j = NonlinearPassiveObserver_P.Saturation_LowerSat_d;
  } else {
    rtb_Row1_j = NonlinearPassiveObserver_B.psi;
  }

  /* End of Saturate: '<S16>/Saturation' */

  /* Signum: '<S16>/Sign' */
  if (rtb_Row1_j < 0.0) {
    b_y0 = -1.0;
  } else if (rtb_Row1_j > 0.0) {
    b_y0 = 1.0;
  } else if (rtb_Row1_j == 0.0) {
    b_y0 = 0.0;
  } else {
    b_y0 = rtb_Row1_j;
  }

  /* Gain: '<S16>/Gain' incorporates:
   *  Signum: '<S16>/Sign'
   */
  rtb_psi_dot = NonlinearPassiveObserver_P.Gain_Gain_h * b_y0;

  /* Sum: '<S16>/Sum1' */
  rtb_Row1_j += rtb_psi_dot;

  /* Math: '<S16>/Math Function' incorporates:
   *  Constant: '<S16>/Constant'
   */
  rtb_Row1_j = rt_remd_snf(rtb_Row1_j,
    NonlinearPassiveObserver_P.Constant_Value_p);

  /* Sum: '<S16>/Sum' */
  rtb_Row1_j -= rtb_psi_dot;

  /* Fcn: '<S1>/Fcn' */
  rtb_psi_dot = rtb_Row1_j;

  /* Fcn: '<S14>/Row1' incorporates:
   *  Fcn: '<S1>/Fcn'
   */
  rtb_Row1 = cos(rtb_Row1_j) * NonlinearPassiveObserver_B.Integrator2[0] + sin
    (rtb_Row1_j) * NonlinearPassiveObserver_B.Integrator2[1];

  /* Fcn: '<S14>/Row2' incorporates:
   *  Fcn: '<S1>/Fcn'
   */
  rtb_Row2 = -sin(rtb_Row1_j) * NonlinearPassiveObserver_B.Integrator2[0] + cos
    (rtb_Row1_j) * NonlinearPassiveObserver_B.Integrator2[1];

  /* Fcn: '<S14>/Row3' */
  rtb_Row3 = NonlinearPassiveObserver_B.Integrator2[2];

  /* MATLAB Function: '<S2>/MATLAB Function2' incorporates:
   *  SignalConversion: '<S19>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'Observer Gains/MATLAB Function2': '<S19>:1' */
  /* '<S19>:1:4' */
  memset(&rtb_K_d[0], 0, 9U * sizeof(real_T));
  rtb_K_d[0] = NonlinearPassiveObserver_B.K_4_x;
  rtb_K_d[4] = NonlinearPassiveObserver_B.K_4_y;
  rtb_K_d[8] = NonlinearPassiveObserver_B.K_4_psi;

  /* Sum: '<S1>/Sum' */
  rtb_Sum_idx_0 = NonlinearPassiveObserver_B.x -
    NonlinearPassiveObserver_B.Integrator[0];
  rtb_Sum_idx_1 = NonlinearPassiveObserver_B.y -
    NonlinearPassiveObserver_B.Integrator[1];
  rtb_Sum_idx_2 = rtb_Row1_j - NonlinearPassiveObserver_B.Sum;

  /* Product: '<S1>/Matrix Multiply2' */
  for (i = 0; i < 3; i++) {
    rtb_TmpSignalConversionAtSFunct[i] = rtb_K_d[i + 6] * rtb_Sum_idx_2 +
      (rtb_K_d[i + 3] * rtb_Sum_idx_1 + rtb_K_d[i] * rtb_Sum_idx_0);
  }

  /* End of Product: '<S1>/Matrix Multiply2' */

  /* Integrator: '<S1>/Integrator1' */
  if (rtmIsMajorTimeStep(NonlinearPassiveObserver_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                       &NonlinearPassiveObserve_PrevZCX.Integrator1_Reset_ZCE,
                       NonlinearPassiveObserver_B.reset);

    /* evaluate zero-crossings */
    if (zcEvent) {
      NonlinearPassiveObserver_X.Integrator1_CSTATE[0] =
        (NonlinearPassiveObserver_P.Integrator1_IC[0]);
      NonlinearPassiveObserver_X.Integrator1_CSTATE[1] =
        (NonlinearPassiveObserver_P.Integrator1_IC[1]);
      NonlinearPassiveObserver_X.Integrator1_CSTATE[2] =
        (NonlinearPassiveObserver_P.Integrator1_IC[2]);
    }
  }

  NonlinearPassiveObserver_B.Integrator1[0] =
    NonlinearPassiveObserver_X.Integrator1_CSTATE[0];
  NonlinearPassiveObserver_B.Integrator1[1] =
    NonlinearPassiveObserver_X.Integrator1_CSTATE[1];
  NonlinearPassiveObserver_B.Integrator1[2] =
    NonlinearPassiveObserver_X.Integrator1_CSTATE[2];

  /* MATLAB Function: '<S21>/Bow thruster' */
  /* MATLAB Function 'tau_2_tau_actual/Thruster mapping/Bow thruster': '<S22>:1' */
  /* '<S22>:1:3' */
  /*  Thruster characteristics */
  if (NonlinearPassiveObserver_B.u_BT > 0.0879) {
    /* '<S22>:1:5' */
    /* '<S22>:1:10' */
    b_y0 = exp(0.1174 * NonlinearPassiveObserver_B.u_BT) * 2.515 + exp(-1.131 *
      NonlinearPassiveObserver_B.u_BT) * -2.807;
  } else if (NonlinearPassiveObserver_B.u_BT < -0.059) {
    /* '<S22>:1:11' */
    /* '<S22>:1:16' */
    b_y0 = exp(0.193 * NonlinearPassiveObserver_B.u_BT) * -548.0 + exp(0.1992 *
      NonlinearPassiveObserver_B.u_BT) * 548.2;
  } else {
    /* '<S22>:1:18' */
    b_y0 = 0.0;
  }

  /* MATLAB Function: '<S8>/Thruster configuration matrix' incorporates:
   *  MATLAB Function: '<S21>/Bow thruster'
   *  MATLAB Function: '<S21>/VSP'
   */
  /*  Thruster losses due to forward speed */
  /* '<S22>:1:21' */
  /* '<S22>:1:24' */
  /* '<S22>:1:25' */
  /* MATLAB Function 'tau_2_tau_actual/Thruster mapping/VSP': '<S23>:1' */
  /*  Calculating the force in x-direction */
  /* '<S23>:1:6' */
  /* '<S23>:1:9' */
  /* '<S23>:1:12' */
  /* '<S23>:1:15' */
  /* '<S23>:1:18' */
  /* '<S23>:1:21' */
  /* '<S23>:1:22' */
  /*  Calculating the force in y-direction */
  /* '<S23>:1:31' */
  /* '<S23>:1:34' */
  /* '<S23>:1:37' */
  /* '<S23>:1:40' */
  /* '<S23>:1:43' */
  /* '<S23>:1:46' */
  /* '<S23>:1:47' */
  /* MATLAB Function 'tau_2_tau_actual/Thruster configuration matrix': '<S20>:1' */
  /* '<S20>:1:7' */
  /* '<S20>:1:13' */
  unnamed_idx_0 = (((((sin(1.001 * NonlinearPassiveObserver_B.u_alpha + 1.564) *
                       1.107 + sin(0.1397 * NonlinearPassiveObserver_B.u_alpha +
    -1.599) * 0.3471) + sin(1.993 * NonlinearPassiveObserver_B.u_alpha + 1.886) *
                      0.1558) + sin(0.218 * NonlinearPassiveObserver_B.u_alpha +
    1.513) * 0.1599) + sin(2.986 * NonlinearPassiveObserver_B.u_alpha + -1.601) *
                    0.08237) + sin(3.964 * NonlinearPassiveObserver_B.u_alpha +
    1.738) * 0.04641) * NonlinearPassiveObserver_B.u_VSP;
  rtb_Row1_j = (((((sin(1.001 * NonlinearPassiveObserver_B.u_alpha + 0.01605) *
                    0.7936 + sin(1.997 * NonlinearPassiveObserver_B.u_alpha +
    0.03229) * 0.2112) + sin(2.991 * NonlinearPassiveObserver_B.u_alpha + 2.986)
                   * 0.07608) + sin(3.999 * NonlinearPassiveObserver_B.u_alpha +
    -0.8668) * 0.04817) + sin(4.904 * NonlinearPassiveObserver_B.u_alpha +
    -2.622) * 0.01757) + sin(5.068 * NonlinearPassiveObserver_B.u_alpha + 0.2548)
                * -0.02089) * NonlinearPassiveObserver_B.u_VSP;
  b_y0 = (atan(-10.22 * NonlinearPassiveObserver_B.Integrator1[0] + 2.947) *
          0.3075 + 0.7561) * b_y0 / 1.1385;
  for (i = 0; i < 3; i++) {
    tau[i] = a[i + 6] * b_y0 + (a[i + 3] * rtb_Row1_j + a[i] * unnamed_idx_0);
  }

  /* MATLAB Function: '<S1>/D(nu)*nu' */
  /* '<S20>:1:15' */
  /* '<S20>:1:16' */
  /* '<S20>:1:17' */
  /* MATLAB Function 'Nonlinear Passisve Observer/D(nu)*nu': '<S11>:1' */
  /* '<S11>:1:3' */
  /* '<S11>:1:4' */
  /* '<S11>:1:5' */
  /* '<S11>:1:7' */
  /* D */
  /*     D = D(U,V,R) */
  /*     This function was generated by the Symbolic Math Toolbox version 6.0. */
  /*     15-Mar-2015 18:54:30 */
  rtb_Row1_j = fabs(NonlinearPassiveObserver_B.Integrator1[2]);
  b_y0 = fabs(NonlinearPassiveObserver_B.Integrator1[1]);
  x[0] = (NonlinearPassiveObserver_B.Integrator1[0] *
          NonlinearPassiveObserver_B.Integrator1[0] * 3.787 +
          NonlinearPassiveObserver_B.Integrator1[0] * -0.3545) + 0.6555;
  x[1] = 0.0;
  x[2] = 0.0;
  x[3] = NonlinearPassiveObserver_B.Integrator1[1] * 2.443;
  x[4] = ((rtb_Row1_j * 0.805 + NonlinearPassiveObserver_B.Integrator1[1] *
           2.776) + NonlinearPassiveObserver_B.Integrator1[1] *
          NonlinearPassiveObserver_B.Integrator1[1] * 64.91) + 1.33;
  x[5] = rtb_Row1_j * -0.13 + NonlinearPassiveObserver_B.Integrator1[1] * 0.2088;
  x[6] = 0.0;
  x[7] = (rtb_Row1_j * 3.45 + b_y0 * 0.845) + 7.25;
  x[8] = (rtb_Row1_j * 0.75 - b_y0 * 0.08) + 1.9;
  memcpy(&D_NL[0], &x[0], 9U * sizeof(real_T));

  /* MATLAB Function: '<S1>/C(nu)*nu' */
  /* '<S11>:1:9' */
  /* MATLAB Function 'Nonlinear Passisve Observer/C(nu)*nu': '<S10>:1' */
  /* '<S10>:1:3' */
  /* '<S10>:1:4' */
  /* '<S10>:1:5' */
  /* '<S10>:1:7' */
  /* C */
  /*     C = C(U,V,R) */
  /*     This function was generated by the Symbolic Math Toolbox version 6.0. */
  /*     15-Mar-2015 18:54:30 */
  rtb_Row1_j = NonlinearPassiveObserver_B.Integrator1[0] * 16.79;
  x[0] = 0.0;
  x[1] = 0.0;
  x[2] = NonlinearPassiveObserver_B.Integrator1[2] * 0.554625 +
    NonlinearPassiveObserver_B.Integrator1[1] * 24.79;
  x[3] = 0.0;
  x[4] = 0.0;
  x[5] = -rtb_Row1_j;
  x[6] = NonlinearPassiveObserver_B.Integrator1[2] * -0.554625 -
    NonlinearPassiveObserver_B.Integrator1[1] * 24.79;
  x[7] = rtb_Row1_j;
  x[8] = 0.0;
  memcpy(&rtb_K_d[0], &x[0], 9U * sizeof(real_T));

  /* Sum: '<S1>/Sum2' incorporates:
   *  Fcn: '<S13>/Row1'
   *  Fcn: '<S13>/Row2'
   *  Fcn: '<S13>/Row3'
   *  MATLAB Function: '<S8>/Thruster configuration matrix'
   */
  /* '<S10>:1:9' */
  tmp[0] = cos(rtb_psi_dot) * rtb_TmpSignalConversionAtSFunct[0] + sin
    (rtb_psi_dot) * rtb_TmpSignalConversionAtSFunct[1];
  tmp[1] = -sin(rtb_psi_dot) * rtb_TmpSignalConversionAtSFunct[0] + cos
    (rtb_psi_dot) * rtb_TmpSignalConversionAtSFunct[1];
  tmp[2] = rtb_TmpSignalConversionAtSFunct[2];
  tau_0[0] = tau[0];
  tau_0[1] = tau[1];
  tau_0[2] = tau[2];

  /* Sum: '<S1>/Sum3' incorporates:
   *  MATLAB Function: '<S1>/D(nu)*nu'
   *  Sum: '<S1>/Sum2'
   */
  rtb_Row1_0[0] = rtb_Row1;
  rtb_Row1_0[1] = rtb_Row2;
  rtb_Row1_0[2] = rtb_Row3;
  for (i = 0; i < 3; i++) {
    tau[i] = ((tmp[i] + tau_0[i]) + rtb_Row1_0[i]) - ((D_NL[i + 3] *
      NonlinearPassiveObserver_B.Integrator1[1] + D_NL[i] *
      NonlinearPassiveObserver_B.Integrator1[0]) + D_NL[i + 6] *
      NonlinearPassiveObserver_B.Integrator1[2]);
  }

  /* MATLAB Function: '<S1>/C(nu)*nu' incorporates:
   *  Sum: '<S1>/Sum3'
   */
  for (i = 0; i < 3; i++) {
    rtb_TmpSignalConversionAtSFunct[i] = rtb_K_d[i + 6] *
      NonlinearPassiveObserver_B.Integrator1[2] + (rtb_K_d[i + 3] *
      NonlinearPassiveObserver_B.Integrator1[1] + rtb_K_d[i] *
      NonlinearPassiveObserver_B.Integrator1[0]);
  }

  /* Sum: '<S1>/Sum3' incorporates:
   *  Gain: '<S1>/M^-1'
   */
  b_y0 = tau[0] - rtb_TmpSignalConversionAtSFunct[0];
  rtb_Row1_j = tau[1] - rtb_TmpSignalConversionAtSFunct[1];
  unnamed_idx_0 = tau[2] - rtb_TmpSignalConversionAtSFunct[2];

  /* Gain: '<S1>/M^-1' */
  for (i = 0; i < 3; i++) {
    NonlinearPassiveObserver_B.M1[i] = 0.0;
    NonlinearPassiveObserver_B.M1[i] += NonlinearPassiveObserver_P.M1_Gain[i] *
      b_y0;
    NonlinearPassiveObserver_B.M1[i] += NonlinearPassiveObserver_P.M1_Gain[i + 3]
      * rtb_Row1_j;
    NonlinearPassiveObserver_B.M1[i] += NonlinearPassiveObserver_P.M1_Gain[i + 6]
      * unnamed_idx_0;
  }

  /* MATLAB Function 'Observer Gains/MATLAB Function': '<S17>:1' */
  /* '<S17>:1:4' */
  for (i = 0; i < 9; i++) {
    /* MATLAB Function: '<S2>/MATLAB Function' */
    rtb_K_d[i] = 0.0;

    /* MATLAB Function: '<S2>/MATLAB Function1' */
    D_NL[i] = 0.0;
  }

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  SignalConversion: '<S17>/TmpSignal ConversionAt SFunction Inport1'
   */
  rtb_K_d[0] = NonlinearPassiveObserver_B.K_2_x;
  rtb_K_d[4] = NonlinearPassiveObserver_B.K_2_y;
  rtb_K_d[8] = NonlinearPassiveObserver_B.K_2_psi;

  /* MATLAB Function: '<S2>/MATLAB Function1' incorporates:
   *  SignalConversion: '<S18>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'Observer Gains/MATLAB Function1': '<S18>:1' */
  /* '<S18>:1:4' */
  D_NL[0] = NonlinearPassiveObserver_B.K_3_x;
  D_NL[4] = NonlinearPassiveObserver_B.K_3_y;
  D_NL[8] = NonlinearPassiveObserver_B.K_3_psi;

  /* Product: '<S1>/Matrix Multiply1' */
  for (i = 0; i < 3; i++) {
    NonlinearPassiveObserver_B.MatrixMultiply1[i] = 0.0;
    NonlinearPassiveObserver_B.MatrixMultiply1[i] += D_NL[i] * rtb_Sum_idx_0;
    NonlinearPassiveObserver_B.MatrixMultiply1[i] += D_NL[i + 3] * rtb_Sum_idx_1;
    NonlinearPassiveObserver_B.MatrixMultiply1[i] += D_NL[i + 6] * rtb_Sum_idx_2;
  }

  /* End of Product: '<S1>/Matrix Multiply1' */

  /* Product: '<S1>/Matrix Multiply' incorporates:
   *  Sum: '<S1>/Sum1'
   */
  for (i = 0; i < 3; i++) {
    rtb_TmpSignalConversionAtSFunct[i] = rtb_K_d[i + 6] * rtb_Sum_idx_2 +
      (rtb_K_d[i + 3] * rtb_Sum_idx_1 + rtb_K_d[i] * rtb_Sum_idx_0);
  }

  /* End of Product: '<S1>/Matrix Multiply' */

  /* Sum: '<S1>/Sum1' incorporates:
   *  Fcn: '<S12>/Fcn'
   *  Fcn: '<S12>/Fcn1'
   *  Fcn: '<S12>/Fcn2'
   */
  NonlinearPassiveObserver_B.Sum1[0] = (cos(rtb_psi_dot) *
    NonlinearPassiveObserver_B.Integrator1[0] - sin(rtb_psi_dot) *
    NonlinearPassiveObserver_B.Integrator1[1]) +
    rtb_TmpSignalConversionAtSFunct[0];
  NonlinearPassiveObserver_B.Sum1[1] = (sin(rtb_psi_dot) *
    NonlinearPassiveObserver_B.Integrator1[0] + cos(rtb_psi_dot) *
    NonlinearPassiveObserver_B.Integrator1[1]) +
    rtb_TmpSignalConversionAtSFunct[1];
  NonlinearPassiveObserver_B.Sum1[2] = rtb_TmpSignalConversionAtSFunct[2] +
    NonlinearPassiveObserver_B.Integrator1[2];
}

/* Model update function */
void NonlinearPassiveObserver_update(void)
{
  /* Update for Integrator: '<S1>/Integrator' */
  NonlinearPassiveObserver_DW.Integrator_IWORK.IcNeedsLoading = 0;
  if (rtmIsMajorTimeStep(NonlinearPassiveObserver_M)) {
    rt_ertODEUpdateContinuousStates(&NonlinearPassiveObserver_M->solverInfo);
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
  if (!(++NonlinearPassiveObserver_M->Timing.clockTick0)) {
    ++NonlinearPassiveObserver_M->Timing.clockTickH0;
  }

  NonlinearPassiveObserver_M->Timing.t[0] = rtsiGetSolverStopTime
    (&NonlinearPassiveObserver_M->solverInfo);

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
    if (!(++NonlinearPassiveObserver_M->Timing.clockTick1)) {
      ++NonlinearPassiveObserver_M->Timing.clockTickH1;
    }

    NonlinearPassiveObserver_M->Timing.t[1] =
      NonlinearPassiveObserver_M->Timing.clockTick1 *
      NonlinearPassiveObserver_M->Timing.stepSize1 +
      NonlinearPassiveObserver_M->Timing.clockTickH1 *
      NonlinearPassiveObserver_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void NonlinearPassiveObserver_derivatives(void)
{
  /* Derivatives for Integrator: '<S1>/Integrator2' */
  {
    ((XDot_NonlinearPassiveObserver_T *)
      NonlinearPassiveObserver_M->ModelData.derivs)->Integrator2_CSTATE[0] =
      NonlinearPassiveObserver_B.MatrixMultiply1[0];
    ((XDot_NonlinearPassiveObserver_T *)
      NonlinearPassiveObserver_M->ModelData.derivs)->Integrator2_CSTATE[1] =
      NonlinearPassiveObserver_B.MatrixMultiply1[1];
    ((XDot_NonlinearPassiveObserver_T *)
      NonlinearPassiveObserver_M->ModelData.derivs)->Integrator2_CSTATE[2] =
      NonlinearPassiveObserver_B.MatrixMultiply1[2];
  }

  /* Derivatives for Integrator: '<S1>/Integrator' */
  {
    ((XDot_NonlinearPassiveObserver_T *)
      NonlinearPassiveObserver_M->ModelData.derivs)->Integrator_CSTATE[0] =
      NonlinearPassiveObserver_B.Sum1[0];
    ((XDot_NonlinearPassiveObserver_T *)
      NonlinearPassiveObserver_M->ModelData.derivs)->Integrator_CSTATE[1] =
      NonlinearPassiveObserver_B.Sum1[1];
    ((XDot_NonlinearPassiveObserver_T *)
      NonlinearPassiveObserver_M->ModelData.derivs)->Integrator_CSTATE[2] =
      NonlinearPassiveObserver_B.Sum1[2];
  }

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  {
    ((XDot_NonlinearPassiveObserver_T *)
      NonlinearPassiveObserver_M->ModelData.derivs)->Integrator1_CSTATE[0] =
      NonlinearPassiveObserver_B.M1[0];
    ((XDot_NonlinearPassiveObserver_T *)
      NonlinearPassiveObserver_M->ModelData.derivs)->Integrator1_CSTATE[1] =
      NonlinearPassiveObserver_B.M1[1];
    ((XDot_NonlinearPassiveObserver_T *)
      NonlinearPassiveObserver_M->ModelData.derivs)->Integrator1_CSTATE[2] =
      NonlinearPassiveObserver_B.M1[2];
  }
}

/* Model initialize function */
void NonlinearPassiveObserver_initialize(void)
{
  NonlinearPassiveObserve_PrevZCX.Integrator2_Reset_ZCE = UNINITIALIZED_ZCSIG;
  NonlinearPassiveObserve_PrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  NonlinearPassiveObserve_PrevZCX.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Integrator: '<S1>/Integrator2' */
  NonlinearPassiveObserver_X.Integrator2_CSTATE[0] =
    (NonlinearPassiveObserver_P.Integrator2_IC[0]);
  NonlinearPassiveObserver_X.Integrator2_CSTATE[1] =
    (NonlinearPassiveObserver_P.Integrator2_IC[1]);
  NonlinearPassiveObserver_X.Integrator2_CSTATE[2] =
    (NonlinearPassiveObserver_P.Integrator2_IC[2]);

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  if (rtmIsFirstInitCond(NonlinearPassiveObserver_M)) {
    NonlinearPassiveObserver_X.Integrator_CSTATE[0] = 0.0;
    NonlinearPassiveObserver_X.Integrator_CSTATE[1] = 0.0;
    NonlinearPassiveObserver_X.Integrator_CSTATE[2] = 0.0;
  }

  NonlinearPassiveObserver_DW.Integrator_IWORK.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  NonlinearPassiveObserver_X.Integrator1_CSTATE[0] =
    (NonlinearPassiveObserver_P.Integrator1_IC[0]);
  NonlinearPassiveObserver_X.Integrator1_CSTATE[1] =
    (NonlinearPassiveObserver_P.Integrator1_IC[1]);
  NonlinearPassiveObserver_X.Integrator1_CSTATE[2] =
    (NonlinearPassiveObserver_P.Integrator1_IC[2]);

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(NonlinearPassiveObserver_M)) {
    rtmSetFirstInitCond(NonlinearPassiveObserver_M, 0);
  }
}

/* Model terminate function */
void NonlinearPassiveObserver_terminate(void)
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
  NonlinearPassiveObserver_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  NonlinearPassiveObserver_update();
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
  NonlinearPassiveObserver_initialize();
}

void MdlTerminate(void)
{
  NonlinearPassiveObserver_terminate();
}

/* Registration function */
RT_MODEL_NonlinearPassiveObse_T *NonlinearPassiveObserver(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)NonlinearPassiveObserver_M, 0,
                sizeof(RT_MODEL_NonlinearPassiveObse_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&NonlinearPassiveObserver_M->solverInfo,
                          &NonlinearPassiveObserver_M->Timing.simTimeStep);
    rtsiSetTPtr(&NonlinearPassiveObserver_M->solverInfo, &rtmGetTPtr
                (NonlinearPassiveObserver_M));
    rtsiSetStepSizePtr(&NonlinearPassiveObserver_M->solverInfo,
                       &NonlinearPassiveObserver_M->Timing.stepSize0);
    rtsiSetdXPtr(&NonlinearPassiveObserver_M->solverInfo,
                 &NonlinearPassiveObserver_M->ModelData.derivs);
    rtsiSetContStatesPtr(&NonlinearPassiveObserver_M->solverInfo, (real_T **)
                         &NonlinearPassiveObserver_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&NonlinearPassiveObserver_M->solverInfo,
      &NonlinearPassiveObserver_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&NonlinearPassiveObserver_M->solverInfo,
                          (&rtmGetErrorStatus(NonlinearPassiveObserver_M)));
    rtsiSetRTModelPtr(&NonlinearPassiveObserver_M->solverInfo,
                      NonlinearPassiveObserver_M);
  }

  rtsiSetSimTimeStep(&NonlinearPassiveObserver_M->solverInfo, MAJOR_TIME_STEP);
  NonlinearPassiveObserver_M->ModelData.intgData.y =
    NonlinearPassiveObserver_M->ModelData.odeY;
  NonlinearPassiveObserver_M->ModelData.intgData.f[0] =
    NonlinearPassiveObserver_M->ModelData.odeF[0];
  NonlinearPassiveObserver_M->ModelData.intgData.f[1] =
    NonlinearPassiveObserver_M->ModelData.odeF[1];
  NonlinearPassiveObserver_M->ModelData.intgData.f[2] =
    NonlinearPassiveObserver_M->ModelData.odeF[2];
  NonlinearPassiveObserver_M->ModelData.intgData.f[3] =
    NonlinearPassiveObserver_M->ModelData.odeF[3];
  NonlinearPassiveObserver_M->ModelData.contStates = ((real_T *)
    &NonlinearPassiveObserver_X);
  rtsiSetSolverData(&NonlinearPassiveObserver_M->solverInfo, (void *)
                    &NonlinearPassiveObserver_M->ModelData.intgData);
  rtsiSetSolverName(&NonlinearPassiveObserver_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = NonlinearPassiveObserver_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    NonlinearPassiveObserver_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    NonlinearPassiveObserver_M->Timing.sampleTimes =
      (&NonlinearPassiveObserver_M->Timing.sampleTimesArray[0]);
    NonlinearPassiveObserver_M->Timing.offsetTimes =
      (&NonlinearPassiveObserver_M->Timing.offsetTimesArray[0]);

    /* task periods */
    NonlinearPassiveObserver_M->Timing.sampleTimes[0] = (0.0);
    NonlinearPassiveObserver_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    NonlinearPassiveObserver_M->Timing.offsetTimes[0] = (0.0);
    NonlinearPassiveObserver_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(NonlinearPassiveObserver_M,
             &NonlinearPassiveObserver_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = NonlinearPassiveObserver_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    NonlinearPassiveObserver_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(NonlinearPassiveObserver_M, -1);
  NonlinearPassiveObserver_M->Timing.stepSize0 = 0.01;
  NonlinearPassiveObserver_M->Timing.stepSize1 = 0.01;
  rtmSetFirstInitCond(NonlinearPassiveObserver_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    NonlinearPassiveObserver_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(NonlinearPassiveObserver_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(NonlinearPassiveObserver_M->rtwLogInfo, (NULL));
    rtliSetLogT(NonlinearPassiveObserver_M->rtwLogInfo, "tout");
    rtliSetLogX(NonlinearPassiveObserver_M->rtwLogInfo, "");
    rtliSetLogXFinal(NonlinearPassiveObserver_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(NonlinearPassiveObserver_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(NonlinearPassiveObserver_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(NonlinearPassiveObserver_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(NonlinearPassiveObserver_M->rtwLogInfo, 1);
    rtliSetLogY(NonlinearPassiveObserver_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(NonlinearPassiveObserver_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(NonlinearPassiveObserver_M->rtwLogInfo, (NULL));
  }

  NonlinearPassiveObserver_M->solverInfoPtr =
    (&NonlinearPassiveObserver_M->solverInfo);
  NonlinearPassiveObserver_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&NonlinearPassiveObserver_M->solverInfo, 0.01);
  rtsiSetSolverMode(&NonlinearPassiveObserver_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  NonlinearPassiveObserver_M->ModelData.blockIO = ((void *)
    &NonlinearPassiveObserver_B);
  (void) memset(((void *) &NonlinearPassiveObserver_B), 0,
                sizeof(B_NonlinearPassiveObserver_T));

  /* parameters */
  NonlinearPassiveObserver_M->ModelData.defaultParam = ((real_T *)
    &NonlinearPassiveObserver_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &NonlinearPassiveObserver_X;
    NonlinearPassiveObserver_M->ModelData.contStates = (x);
    (void) memset((void *)&NonlinearPassiveObserver_X, 0,
                  sizeof(X_NonlinearPassiveObserver_T));
  }

  /* states (dwork) */
  NonlinearPassiveObserver_M->ModelData.dwork = ((void *)
    &NonlinearPassiveObserver_DW);
  (void) memset((void *)&NonlinearPassiveObserver_DW, 0,
                sizeof(DW_NonlinearPassiveObserver_T));

  /* Initialize Sizes */
  NonlinearPassiveObserver_M->Sizes.numContStates = (9);/* Number of continuous states */
  NonlinearPassiveObserver_M->Sizes.numY = (0);/* Number of model outputs */
  NonlinearPassiveObserver_M->Sizes.numU = (0);/* Number of model inputs */
  NonlinearPassiveObserver_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  NonlinearPassiveObserver_M->Sizes.numSampTimes = (2);/* Number of sample times */
  NonlinearPassiveObserver_M->Sizes.numBlocks = (82);/* Number of blocks */
  NonlinearPassiveObserver_M->Sizes.numBlockIO = (23);/* Number of block outputs */
  NonlinearPassiveObserver_M->Sizes.numBlockPrms = (191);/* Sum of parameter "widths" */
  return NonlinearPassiveObserver_M;
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
#ifdef NI_ROOTMODEL_NonlinearPassiveObserver
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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 20:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 21:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 22:
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 30:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 18:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 19:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 20:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 21:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 22:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 30:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

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

extern NonlinearPassiveObserver_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // reset
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.reset, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // eta input/x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.x, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // eta input/y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.y, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // eta input/psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.psi, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Observer Gains/K_2_x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.K_2_x, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Observer Gains/K_2_y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.K_2_y, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Observer Gains/K_2_psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.K_2_psi, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Observer Gains/K_3_psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.K_3_psi, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Observer Gains/K_3_x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.K_3_x, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Observer Gains/K_3_y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.K_3_y, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Observer Gains/K_4_psi
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.K_4_psi, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Observer Gains/K_4_x
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.K_4_x, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Observer Gains/K_4_y
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.K_4_y, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // u input/u_BT
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.u_BT, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // u input/u_VSP
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.u_VSP, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // u input/u_alpha
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_B.u_alpha, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 16;
}

double ni_extout[12];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // b_hat output/b_x_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_B.Integrator2,0,17,0);
  } else {
    index += 1;
  }

  // b_hat output/b_y_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_B.Integrator2,1,17,0);
  } else {
    index += 1;
  }

  // b_hat output/b_psi_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_B.Integrator2,2,17,0);
  } else {
    index += 1;
  }

  // eta_hat output/x_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_B.Integrator,0,17,0);
  } else {
    index += 1;
  }

  // eta_hat output/y_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_B.Integrator,1,17,0);
  } else {
    index += 1;
  }

  // eta_hat output/psi_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NonlinearPassiveObserver_B.Sum,
      0,0,0);
  } else {
    index += 1;
  }

  // nu_dot_hat output/u_dot_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NonlinearPassiveObserver_B.M1,
      0,17,0);
  } else {
    index += 1;
  }

  // nu_dot_hat output/v_dot_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NonlinearPassiveObserver_B.M1,
      1,17,0);
  } else {
    index += 1;
  }

  // nu_dot_hat output/r_dot_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NonlinearPassiveObserver_B.M1,
      2,17,0);
  } else {
    index += 1;
  }

  // nu_hat output/u_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_B.Integrator1,0,17,0);
  } else {
    index += 1;
  }

  // nu_hat output/v_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_B.Integrator1,1,17,0);
  } else {
    index += 1;
  }

  // nu_hat output/r_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_B.Integrator1,2,17,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 12;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

  // b_hat output/b_x_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&NonlinearPassiveObserver_B.Integrator2,0,17,0);

  // b_hat output/b_y_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&NonlinearPassiveObserver_B.Integrator2,1,17,0);

  // b_hat output/b_psi_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&NonlinearPassiveObserver_B.Integrator2,2,17,0);

  // eta_hat output/x_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&NonlinearPassiveObserver_B.Integrator,0,17,0);

  // eta_hat output/y_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&NonlinearPassiveObserver_B.Integrator,1,17,0);

  // eta_hat output/psi_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NonlinearPassiveObserver_B.Sum,0,
    0,0);

  // nu_dot_hat output/u_dot_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NonlinearPassiveObserver_B.M1,0,
    17,0);

  // nu_dot_hat output/v_dot_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NonlinearPassiveObserver_B.M1,1,
    17,0);

  // nu_dot_hat output/r_dot_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NonlinearPassiveObserver_B.M1,2,
    17,0);

  // nu_hat output/u_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&NonlinearPassiveObserver_B.Integrator1,0,17,0);

  // nu_hat output/v_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&NonlinearPassiveObserver_B.Integrator1,1,17,0);

  // nu_hat output/r_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&NonlinearPassiveObserver_B.Integrator1,2,17,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator2/InitialCondition",
    offsetof(P_NonlinearPassiveObserver_T, Integrator2_IC), 31, 3, 2, 0, 0 },

  { 1,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(P_NonlinearPassiveObserver_T, Saturation_UpperSat), 30, 1, 2, 2, 0
  },

  { 2,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(P_NonlinearPassiveObserver_T, Saturation_LowerSat), 30, 1, 2, 4, 0
  },

  { 3,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(P_NonlinearPassiveObserver_T, Gain_Gain), 30, 1, 2, 6, 0 },

  { 4,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(P_NonlinearPassiveObserver_T, Constant_Value), 30, 1, 2, 8, 0 },

  { 5,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(P_NonlinearPassiveObserver_T, Saturation_UpperSat_f), 30, 1, 2, 10,
    0 },

  { 6,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(P_NonlinearPassiveObserver_T, Saturation_LowerSat_d), 30, 1, 2, 12,
    0 },

  { 7,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(P_NonlinearPassiveObserver_T, Gain_Gain_h), 30, 1, 2, 14, 0 },

  { 8,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(P_NonlinearPassiveObserver_T, Constant_Value_p), 30, 1, 2, 16, 0 },

  { 9,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator1/InitialCondition",
    offsetof(P_NonlinearPassiveObserver_T, Integrator1_IC), 31, 3, 2, 18, 0 },

  { 10, "nonlinearpassiveobserver/Nonlinear Passisve Observer/M^-1/Gain",
    offsetof(P_NonlinearPassiveObserver_T, M1_Gain), 18, 9, 2, 20, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 11;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  3, 1,                                /* Parameter at index 0 */
  1, 1,                                /* Parameter at index 1 */
  1, 1,                                /* Parameter at index 2 */
  1, 1,                                /* Parameter at index 3 */
  1, 1,                                /* Parameter at index 4 */
  1, 1,                                /* Parameter at index 5 */
  1, 1,                                /* Parameter at index 6 */
  1, 1,                                /* Parameter at index 7 */
  1, 1,                                /* Parameter at index 8 */
  3, 1,                                /* Parameter at index 9 */
  3, 3,                                /* Parameter at index 10 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "nonlinearpassiveobserver/reset", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, reset)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    0, 0 },

  { 1, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator2", 0,
    "(1,1)", offsetof(B_NonlinearPassiveObserver_T, Integrator2)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 2, 0 },

  { 2, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator2", 0,
    "(1,2)", offsetof(B_NonlinearPassiveObserver_T, Integrator2)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 4, 0 },

  { 3, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator2", 0,
    "(1,3)", offsetof(B_NonlinearPassiveObserver_T, Integrator2)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 6, 0 },

  { 4, "nonlinearpassiveobserver/eta input/x", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 8,
    0 },

  { 5, "nonlinearpassiveobserver/eta input/y", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 10,
    0 },

  { 6, "nonlinearpassiveobserver/eta input/psi", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, psi)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    12, 0 },

  { 7, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator", 0,
    "(1,1)", offsetof(B_NonlinearPassiveObserver_T, Integrator)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 14, 0 },

  { 8, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator", 0,
    "(1,2)", offsetof(B_NonlinearPassiveObserver_T, Integrator)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 16, 0 },

  { 9, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator", 0,
    "(1,3)", offsetof(B_NonlinearPassiveObserver_T, Integrator)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 18, 0 },

  { 10,
    "nonlinearpassiveobserver/Nonlinear Passisve Observer/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(B_NonlinearPassiveObserver_T, Sum)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "nonlinearpassiveobserver/Observer Gains/K_2_x", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, K_2_x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    22, 0 },

  { 12, "nonlinearpassiveobserver/Observer Gains/K_2_y", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, K_2_y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    24, 0 },

  { 13, "nonlinearpassiveobserver/Observer Gains/K_2_psi", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, K_2_psi)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 26, 0 },

  { 14, "nonlinearpassiveobserver/Observer Gains/K_3_psi", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, K_3_psi)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 28, 0 },

  { 15, "nonlinearpassiveobserver/Observer Gains/K_3_x", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, K_3_x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    30, 0 },

  { 16, "nonlinearpassiveobserver/Observer Gains/K_3_y", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, K_3_y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    32, 0 },

  { 17, "nonlinearpassiveobserver/Observer Gains/K_4_psi", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, K_4_psi)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 34, 0 },

  { 18, "nonlinearpassiveobserver/Observer Gains/K_4_x", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, K_4_x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    36, 0 },

  { 19, "nonlinearpassiveobserver/Observer Gains/K_4_y", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, K_4_y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    38, 0 },

  { 20, "nonlinearpassiveobserver/u input/u_BT", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, u_BT)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    40, 0 },

  { 21, "nonlinearpassiveobserver/u input/u_VSP", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, u_VSP)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    42, 0 },

  { 22, "nonlinearpassiveobserver/u input/u_alpha", 0, "", offsetof
    (B_NonlinearPassiveObserver_T, u_alpha)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 44, 0 },

  { 23, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator1", 0,
    "(1,1)", offsetof(B_NonlinearPassiveObserver_T, Integrator1)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 46, 0 },

  { 24, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator1", 0,
    "(1,2)", offsetof(B_NonlinearPassiveObserver_T, Integrator1)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 48, 0 },

  { 25, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Integrator1", 0,
    "(1,3)", offsetof(B_NonlinearPassiveObserver_T, Integrator1)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 50, 0 },

  { 26, "nonlinearpassiveobserver/Nonlinear Passisve Observer/M^-1", 0, "(1,1)",
    offsetof(B_NonlinearPassiveObserver_T, M1)+0*sizeof(real_T), BLOCKIO_SIG, 17,
    1, 2, 52, 0 },

  { 27, "nonlinearpassiveobserver/Nonlinear Passisve Observer/M^-1", 0, "(1,2)",
    offsetof(B_NonlinearPassiveObserver_T, M1)+1*sizeof(real_T), BLOCKIO_SIG, 17,
    1, 2, 54, 0 },

  { 28, "nonlinearpassiveobserver/Nonlinear Passisve Observer/M^-1", 0, "(1,3)",
    offsetof(B_NonlinearPassiveObserver_T, M1)+2*sizeof(real_T), BLOCKIO_SIG, 17,
    1, 2, 56, 0 },

  { 29, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Matrix Multiply1",
    0, "(1,1)", offsetof(B_NonlinearPassiveObserver_T, MatrixMultiply1)+0*sizeof
    (real_T), BLOCKIO_SIG, 17, 1, 2, 58, 0 },

  { 30, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Matrix Multiply1",
    0, "(1,2)", offsetof(B_NonlinearPassiveObserver_T, MatrixMultiply1)+1*sizeof
    (real_T), BLOCKIO_SIG, 17, 1, 2, 60, 0 },

  { 31, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Matrix Multiply1",
    0, "(1,3)", offsetof(B_NonlinearPassiveObserver_T, MatrixMultiply1)+2*sizeof
    (real_T), BLOCKIO_SIG, 17, 1, 2, 62, 0 },

  { 32, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Sum1", 0, "(1,1)",
    offsetof(B_NonlinearPassiveObserver_T, Sum1)+0*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 64, 0 },

  { 33, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Sum1", 0, "(1,2)",
    offsetof(B_NonlinearPassiveObserver_T, Sum1)+1*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 66, 0 },

  { 34, "nonlinearpassiveobserver/Nonlinear Passisve Observer/Sum1", 0, "(1,3)",
    offsetof(B_NonlinearPassiveObserver_T, Sum1)+2*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 68, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 35;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 28;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "reset", 0, EXT_IN, 1, 1, 1 },

  { 1, "eta input/x", 0, EXT_IN, 1, 1, 1 },

  { 2, "eta input/y", 0, EXT_IN, 1, 1, 1 },

  { 3, "eta input/psi", 0, EXT_IN, 1, 1, 1 },

  { 4, "Observer Gains/K_2_x", 0, EXT_IN, 1, 1, 1 },

  { 5, "Observer Gains/K_2_y", 0, EXT_IN, 1, 1, 1 },

  { 6, "Observer Gains/K_2_psi", 0, EXT_IN, 1, 1, 1 },

  { 7, "Observer Gains/K_3_psi", 0, EXT_IN, 1, 1, 1 },

  { 8, "Observer Gains/K_3_x", 0, EXT_IN, 1, 1, 1 },

  { 9, "Observer Gains/K_3_y", 0, EXT_IN, 1, 1, 1 },

  { 10, "Observer Gains/K_4_psi", 0, EXT_IN, 1, 1, 1 },

  { 11, "Observer Gains/K_4_x", 0, EXT_IN, 1, 1, 1 },

  { 12, "Observer Gains/K_4_y", 0, EXT_IN, 1, 1, 1 },

  { 13, "u input/u_BT", 0, EXT_IN, 1, 1, 1 },

  { 14, "u input/u_VSP", 0, EXT_IN, 1, 1, 1 },

  { 15, "u input/u_alpha", 0, EXT_IN, 1, 1, 1 },

  { 0, "b_hat output/b_x_hat", 0, EXT_OUT, 1, 1, 1 },

  { 1, "b_hat output/b_y_hat", 0, EXT_OUT, 1, 1, 1 },

  { 2, "b_hat output/b_psi_hat", 0, EXT_OUT, 1, 1, 1 },

  { 3, "eta_hat output/x_hat", 0, EXT_OUT, 1, 1, 1 },

  { 4, "eta_hat output/y_hat", 0, EXT_OUT, 1, 1, 1 },

  { 5, "eta_hat output/psi_hat", 0, EXT_OUT, 1, 1, 1 },

  { 6, "nu_dot_hat output/u_dot_hat", 0, EXT_OUT, 1, 1, 1 },

  { 7, "nu_dot_hat output/v_dot_hat", 0, EXT_OUT, 1, 1, 1 },

  { 8, "nu_dot_hat output/r_dot_hat", 0, EXT_OUT, 1, 1, 1 },

  { 9, "nu_hat output/u_hat", 0, EXT_OUT, 1, 1, 1 },

  { 10, "nu_hat output/v_hat", 0, EXT_OUT, 1, 1, 1 },

  { 11, "nu_hat output/r_hat", 0, EXT_OUT, 1, 1, 1 },

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
  "nonlinearpassiveobserver";
static char* NI_CompiledModelVersion = "1.6";
static char* NI_CompiledModelDateTime = "Sun Mar 15 19:19:21 2015";
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
   The undef allows us to access the real NonlinearPassiveObserver_P
   In the rest of the code NonlinearPassiveObserver_P is redefine to be the read-side
   of rtParameter.
 */
#undef NonlinearPassiveObserver_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &NonlinearPassiveObserver_P, sizeof
         (P_NonlinearPassiveObserver_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka NonlinearPassiveObserver_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof
           (P_NonlinearPassiveObserver_T));
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
             (P_NonlinearPassiveObserver_T));
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
               (P_NonlinearPassiveObserver_T));

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
           (P_NonlinearPassiveObserver_T));
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
           (P_NonlinearPassiveObserver_T));
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
           (P_NonlinearPassiveObserver_T));
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
      *numDiscStates = 729;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (contStates && contStatesNames) {
    idx = 0;
    contStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_X.Integrator2_CSTATE[0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_X.Integrator2_CSTATE[0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_X.Integrator2_CSTATE[0], 2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_X.Integrator_CSTATE[0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_X.Integrator_CSTATE[0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_X.Integrator_CSTATE[0], 2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_X.Integrator1_CSTATE[0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator1_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_X.Integrator1_CSTATE[0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator1_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_X.Integrator1_CSTATE[0], 2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator1_CSTATE");
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.reset_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.reset_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.b_x_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.b_x_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.b_y_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.b_y_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.b_psi_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.b_psi_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.x_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.y_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.psi_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.x_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.x_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.y_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.y_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.psi_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.psi_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.K_2_x_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.K_2_x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.K_2_y_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.K_2_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.K_2_psi_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.K_2_psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.K_3_psi_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.K_3_psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.K_3_x_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.K_3_x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.K_3_y_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.K_3_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.K_4_psi_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.K_4_psi_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.K_4_x_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.K_4_x_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.K_4_y_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.K_4_y_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.u_BT_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.u_BT_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.u_VSP_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.u_VSP_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.u_alpha_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.u_alpha_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.u_dot_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.u_dot_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.v_dot_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.v_dot_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.r_dot_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.r_dot_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.u_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.u_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.v_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.v_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.r_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.r_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&NonlinearPassiveObserver_DW.Integrator_IWORK.IcNeedsLoading, 0, 10, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&NonlinearPassiveObserver_DW.Integrator_IWORK.IcNeedsLoading");
    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.reset_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.reset_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.b_x_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.b_x_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.b_y_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.b_y_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.b_psi_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.b_psi_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.x_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.x_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.y_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.y_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.psi_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.psi_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.x_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.x_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.y_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.y_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.psi_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.psi_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.K_2_x_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.K_2_x_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.K_2_y_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.K_2_y_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.K_2_psi_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.K_2_psi_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.K_3_psi_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.K_3_psi_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.K_3_x_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.K_3_x_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.K_3_y_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.K_3_y_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.K_4_psi_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.K_4_psi_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.K_4_x_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.K_4_x_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.K_4_y_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.K_4_y_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.u_BT_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.u_BT_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.u_VSP_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.u_VSP_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.u_alpha_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.u_alpha_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.u_dot_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.u_dot_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.v_dot_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.v_dot_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.r_dot_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.r_dot_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.u_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.u_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.v_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.v_hat_DWORK2");
    }

    for (count = 0; count < 25; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&NonlinearPassiveObserver_DW.r_hat_DWORK2, count, 20, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&NonlinearPassiveObserver_DW.r_hat_DWORK2");
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
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_X.Integrator2_CSTATE[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_X.Integrator2_CSTATE[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_X.Integrator2_CSTATE[0], 2,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_X.Integrator_CSTATE[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_X.Integrator_CSTATE[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_X.Integrator_CSTATE[0], 2,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_X.Integrator1_CSTATE[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_X.Integrator1_CSTATE[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_X.Integrator1_CSTATE[0], 2,
      contStates[idx++], 0, 0);
  }

  if (discStates) {
    idx = 0;
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.reset_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.b_x_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.b_y_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.b_psi_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.x_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.y_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.psi_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.x_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.y_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.psi_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_2_x_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_2_y_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_2_psi_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_3_psi_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_3_x_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_3_y_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_4_psi_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_4_x_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_4_y_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_BT_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_VSP_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_alpha_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_dot_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.v_dot_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.r_dot_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.v_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.r_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType
      (&NonlinearPassiveObserver_DW.Integrator_IWORK.IcNeedsLoading, 0,
       discStates[idx++], 10, 0);
    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.reset_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.b_x_hat_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.b_y_hat_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.b_psi_hat_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.x_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.y_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.psi_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.x_hat_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.y_hat_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.psi_hat_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_2_x_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_2_y_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_2_psi_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_3_psi_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_3_x_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_3_y_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_4_psi_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_4_x_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.K_4_y_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_BT_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_VSP_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_alpha_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_dot_hat_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.v_dot_hat_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.r_dot_hat_DWORK2,
        count, discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.u_hat_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.v_hat_DWORK2, count,
        discStates[idx++], 20, 0);
    }

    for (count = 0; count < 25; count++) {
      NIRT_SetValueByDataType(&NonlinearPassiveObserver_DW.r_hat_DWORK2, count,
        discStates[idx++], 20, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
    S->Timing.clockTick1 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_NonlinearPassiveObserver
