/*
 * HILmodel.c
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

/* Block signals (auto storage) */
B_HILmodel_T HILmodel_B;

/* Continuous states */
X_HILmodel_T HILmodel_X;

/* Block states (auto storage) */
DW_HILmodel_T HILmodel_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_HILmodel_T HILmodel_PrevZCX;

/* Real-time model */
RT_MODEL_HILmodel_T HILmodel_M_;
RT_MODEL_HILmodel_T *const HILmodel_M = &HILmodel_M_;

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
  int_T nXc = 12;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  HILmodel_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  HILmodel_output();
  HILmodel_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  HILmodel_output();
  HILmodel_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  HILmodel_output();
  HILmodel_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

void rt_mldivide_U1d6x6_U2d_4sw8yi9v(const real_T u0[36], const real_T u1[6],
  real_T y[6])
{
  real_T y_0[6];
  real_T temp;
  real_T A[36];
  int8_T ipiv[6];
  int32_T jm1;
  int32_T jj;
  int32_T j;
  int32_T c;
  int32_T ix;
  real_T s;
  int32_T k;
  int32_T kAcol;
  int32_T i;
  memcpy(&A[0], &u0[0], 36U * sizeof(real_T));
  for (i = 0; i < 6; i++) {
    ipiv[i] = (int8_T)(1 + i);
  }

  for (j = 0; j < 5; j++) {
    c = j * 7;
    jj = j * 7;
    kAcol = 1;
    ix = c;
    temp = fabs(A[jj]);
    for (k = 2; k <= 6 - j; k++) {
      ix++;
      s = fabs(A[ix]);
      if (s > temp) {
        kAcol = k;
        temp = s;
      }
    }

    kAcol--;
    if (A[c + kAcol] != 0.0) {
      if (kAcol != 0) {
        ipiv[j] = (int8_T)((j + kAcol) + 1);
        ix = j;
        kAcol += j;
        for (k = 0; k < 6; k++) {
          temp = A[ix];
          A[ix] = A[kAcol];
          A[kAcol] = temp;
          ix += 6;
          kAcol += 6;
        }
      }

      i = c - j;
      for (jm1 = c + 1; jm1 + 1 <= i + 6; jm1++) {
        A[jm1] /= A[c];
      }
    }

    kAcol = jj + 6;
    for (jm1 = 1; jm1 <= 5 - j; jm1++) {
      if (A[kAcol] != 0.0) {
        temp = -A[kAcol];
        ix = c;
        i = jj - j;
        for (k = jj + 7; k + 1 <= i + 12; k++) {
          A[k] += A[ix + 1] * temp;
          ix++;
        }
      }

      kAcol += 6;
      jj += 6;
    }
  }

  for (i = 0; i < 6; i++) {
    y_0[i] = u1[i];
  }

  for (kAcol = 0; kAcol < 5; kAcol++) {
    if (kAcol + 1 != ipiv[kAcol]) {
      temp = y_0[kAcol];
      y_0[kAcol] = y_0[ipiv[kAcol] - 1];
      y_0[ipiv[kAcol] - 1] = temp;
    }
  }

  for (k = 0; k < 6; k++) {
    kAcol = 6 * k;
    if (y_0[k] != 0.0) {
      for (jm1 = k + 1; jm1 + 1 < 7; jm1++) {
        y_0[jm1] -= A[jm1 + kAcol] * y_0[k];
      }
    }
  }

  for (k = 5; k >= 0; k += -1) {
    kAcol = 6 * k;
    if (y_0[k] != 0.0) {
      y_0[k] /= A[k + kAcol];
      for (jm1 = 0; jm1 + 1 <= k; jm1++) {
        y_0[jm1] -= A[jm1 + kAcol] * y_0[k];
      }
    }
  }

  for (i = 0; i < 6; i++) {
    y[i] = y_0[i];
  }
}

/* Model output function */
void HILmodel_output(void)
{
  real_T rtb_Sum1[6];
  real_T rtb_Sum5[6];
  real_T rtb_Sum_fd[36];
  real_T rtb_uMM[36];
  int32_T i;
  real_T tmp[3];
  real_T tmp_0[3];
  real_T rtb_Sum_ge[36];
  real_T rtb_Sum_i_0[6];
  real_T tmp_1[6];
  real_T rtb_Sum_h_0[6];
  real_T tmp_2[6];
  int32_T i_0;
  real_T rtb_sintheta_0[9];
  real_T tmp_3[9];
  real_T rtb_Sum5_i;
  real_T rtb_Sum_i_idx_0;
  real_T rtb_Sum_h_idx_1;
  real_T rtb_Sum_h_idx_2;
  real_T rtb_Sum_i_idx_1;
  real_T rtb_Sum_h_idx_0;
  real_T rtb_Sum_i_idx_2;
  real_T rtb_Sum3_a_idx_0;
  real_T rtb_Sum3_a_idx_2;
  real_T rtb_costheta_idx_1;
  real_T rtb_costheta_idx_2;
  real_T rtb_costheta_idx_0;
  real_T rtb_Sum_c_idx_0;
  real_T rtb_Sum_c_idx_1;
  real_T rtb_Sum_c_idx_2;
  real_T rtb_Sum3_ax_idx_0;
  real_T rtb_Sum3_ax_idx_2;
  real_T rtb_Sum3_a_idx_1;
  real_T rtb_Sum3_ax_idx_1;
  real_T rtb_sintheta_idx_0;
  real_T rtb_sintheta_idx_1;
  real_T rtb_sintheta_idx_2;
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    /* set solver stop time */
    if (!(HILmodel_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&HILmodel_M->solverInfo,
                            ((HILmodel_M->Timing.clockTickH0 + 1) *
        HILmodel_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&HILmodel_M->solverInfo,
                            ((HILmodel_M->Timing.clockTick0 + 1) *
        HILmodel_M->Timing.stepSize0 + HILmodel_M->Timing.clockTickH0 *
        HILmodel_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(HILmodel_M)) {
    HILmodel_M->Timing.t[0] = rtsiGetT(&HILmodel_M->solverInfo);
  }

  /* Integrator: '<S1>/Integrator4' */
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,&HILmodel_PrevZCX.Integrator4_Reset_ZCE,
                       HILmodel_B.reset);

    /* evaluate zero-crossings and the level of the reset signal */
    if (zcEvent || HILmodel_B.reset != 0.0 ||
        HILmodel_DW.Integrator4_IWORK.IcNeedsLoading) {
      HILmodel_X.Integrator4_CSTATE[0] = HILmodel_B.eta_01;
      HILmodel_X.Integrator4_CSTATE[1] = HILmodel_B.eta_02;
      HILmodel_X.Integrator4_CSTATE[2] = HILmodel_B.eta_03;
    }
  }

  HILmodel_B.p[0] = HILmodel_X.Integrator4_CSTATE[0];
  HILmodel_B.p[1] = HILmodel_X.Integrator4_CSTATE[1];
  HILmodel_B.p[2] = HILmodel_X.Integrator4_CSTATE[2];

  /* Integrator: '<S1>/Integrator2' */
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,&HILmodel_PrevZCX.Integrator2_Reset_ZCE,
                       HILmodel_B.reset);

    /* evaluate zero-crossings and the level of the reset signal */
    if (zcEvent || HILmodel_B.reset != 0.0 ||
        HILmodel_DW.Integrator2_IWORK.IcNeedsLoading) {
      HILmodel_X.Integrator2_CSTATE[0] = HILmodel_B.eta_04;
      HILmodel_X.Integrator2_CSTATE[1] = HILmodel_B.eta_05;
      HILmodel_X.Integrator2_CSTATE[2] = HILmodel_B.eta_06;
    }
  }

  HILmodel_B.theta[0] = HILmodel_X.Integrator2_CSTATE[0];
  HILmodel_B.theta[1] = HILmodel_X.Integrator2_CSTATE[1];
  HILmodel_B.theta[2] = HILmodel_X.Integrator2_CSTATE[2];

  /* Integrator: '<S1>/Integrator3' */
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,&HILmodel_PrevZCX.Integrator3_Reset_ZCE,
                       HILmodel_B.reset);

    /* evaluate zero-crossings and the level of the reset signal */
    if (zcEvent || HILmodel_B.reset != 0.0 ||
        HILmodel_DW.Integrator3_IWORK.IcNeedsLoading) {
      HILmodel_X.Integrator3_CSTATE[0] = HILmodel_B.eta1;
      HILmodel_X.Integrator3_CSTATE[1] = HILmodel_B.eta2;
      HILmodel_X.Integrator3_CSTATE[2] = HILmodel_B.eta3;
      HILmodel_X.Integrator3_CSTATE[3] = HILmodel_B.eta4;
      HILmodel_X.Integrator3_CSTATE[4] = HILmodel_B.eta5;
      HILmodel_X.Integrator3_CSTATE[5] = HILmodel_B.eta6;
    }
  }

  {
    int_T i1;
    real_T *y0 = &HILmodel_B.nu[0];
    real_T *xc = &HILmodel_X.Integrator3_CSTATE[0];
    for (i1=0; i1 < 6; i1++) {
      y0[i1] = xc[i1];
    }
  }

  if (rtmIsMajorTimeStep(HILmodel_M)) {
    /* Gain: '<S8>/Gain' incorporates:
     *  Constant: '<Root>/M_RB'
     *  Math: '<S8>/transpose'
     *  Sum: '<S8>/Sum'
     */
    for (i = 0; i < 6; i++) {
      for (i_0 = 0; i_0 < 6; i_0++) {
        rtb_uMM[i_0 + 6 * i] = (HILmodel_P.M_RB[6 * i + i_0] + HILmodel_P.M_RB[6
          * i_0 + i]) * HILmodel_P.Gain_Gain;
      }
    }

    /* End of Gain: '<S8>/Gain' */

    /* Selector: '<S8>/M11' */
    for (i = 0; i < 3; i++) {
      HILmodel_B.M11[3 * i] = rtb_uMM[6 * i];
      HILmodel_B.M11[1 + 3 * i] = rtb_uMM[6 * i + 1];
      HILmodel_B.M11[2 + 3 * i] = rtb_uMM[6 * i + 2];
    }

    /* End of Selector: '<S8>/M11' */

    /* Selector: '<S8>/M12' */
    for (i = 0; i < 3; i++) {
      HILmodel_B.M12[3 * i] = rtb_uMM[(3 + i) * 6];
      HILmodel_B.M12[1 + 3 * i] = rtb_uMM[(3 + i) * 6 + 1];
      HILmodel_B.M12[2 + 3 * i] = rtb_uMM[(3 + i) * 6 + 2];
    }

    /* End of Selector: '<S8>/M12' */
  }

  /* Product: '<S8>/Product' incorporates:
   *  Sum: '<S8>/Sum1'
   */
  for (i = 0; i < 3; i++) {
    tmp[i] = HILmodel_B.M11[i + 6] * HILmodel_B.nu[2] + (HILmodel_B.M11[i + 3] *
      HILmodel_B.nu[1] + HILmodel_B.M11[i] * HILmodel_B.nu[0]);
  }

  /* End of Product: '<S8>/Product' */

  /* Product: '<S8>/Product1' incorporates:
   *  Sum: '<S8>/Sum1'
   */
  for (i = 0; i < 3; i++) {
    tmp_0[i] = HILmodel_B.M12[i + 6] * HILmodel_B.nu[5] + (HILmodel_B.M12[i + 3]
      * HILmodel_B.nu[4] + HILmodel_B.M12[i] * HILmodel_B.nu[3]);
  }

  /* End of Product: '<S8>/Product1' */

  /* Gain: '<S8>/Gain1' incorporates:
   *  Sum: '<S8>/Sum1'
   */
  rtb_Sum_h_idx_0 = (tmp[0] + tmp_0[0]) * HILmodel_P.Gain1_Gain;
  rtb_Sum_h_idx_1 = (tmp[1] + tmp_0[1]) * HILmodel_P.Gain1_Gain;
  rtb_Sum_h_idx_2 = (tmp[2] + tmp_0[2]) * HILmodel_P.Gain1_Gain;

  /* Sum: '<S16>/Sum' incorporates:
   *  Product: '<S16>/Product'
   *  Product: '<S16>/Product1'
   */
  rtb_Sum_i_idx_0 = rtb_Sum_h_idx_1 * HILmodel_B.nu[5] - rtb_Sum_h_idx_2 *
    HILmodel_B.nu[4];
  rtb_Sum_i_idx_1 = rtb_Sum_h_idx_2 * HILmodel_B.nu[3] - rtb_Sum_h_idx_0 *
    HILmodel_B.nu[5];
  rtb_Sum_i_idx_2 = rtb_Sum_h_idx_0 * HILmodel_B.nu[4] - rtb_Sum_h_idx_1 *
    HILmodel_B.nu[3];
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    /* Math: '<S8>/transpose1' */
    for (i = 0; i < 3; i++) {
      HILmodel_B.M21M12[3 * i] = HILmodel_B.M12[i];
      HILmodel_B.M21M12[1 + 3 * i] = HILmodel_B.M12[i + 3];
      HILmodel_B.M21M12[2 + 3 * i] = HILmodel_B.M12[i + 6];
    }

    /* End of Math: '<S8>/transpose1' */

    /* Selector: '<S8>/M22' */
    for (i = 0; i < 3; i++) {
      HILmodel_B.M22[3 * i] = rtb_uMM[(3 + i) * 6 + 3];
      HILmodel_B.M22[1 + 3 * i] = rtb_uMM[(3 + i) * 6 + 4];
      HILmodel_B.M22[2 + 3 * i] = rtb_uMM[(3 + i) * 6 + 5];
    }

    /* End of Selector: '<S8>/M22' */
  }

  /* Product: '<S8>/Product2' incorporates:
   *  Sum: '<S8>/Sum2'
   */
  for (i = 0; i < 3; i++) {
    tmp[i] = HILmodel_B.M21M12[i + 6] * HILmodel_B.nu[2] + (HILmodel_B.M21M12[i
      + 3] * HILmodel_B.nu[1] + HILmodel_B.M21M12[i] * HILmodel_B.nu[0]);
  }

  /* End of Product: '<S8>/Product2' */

  /* Product: '<S8>/Product3' incorporates:
   *  Sum: '<S8>/Sum2'
   */
  for (i = 0; i < 3; i++) {
    tmp_0[i] = HILmodel_B.M22[i + 6] * HILmodel_B.nu[5] + (HILmodel_B.M22[i + 3]
      * HILmodel_B.nu[4] + HILmodel_B.M22[i] * HILmodel_B.nu[3]);
  }

  /* End of Product: '<S8>/Product3' */

  /* Gain: '<S8>/Gain2' incorporates:
   *  Sum: '<S8>/Sum2'
   */
  rtb_Sum3_a_idx_0 = (tmp[0] + tmp_0[0]) * HILmodel_P.Gain2_Gain;
  rtb_Sum3_a_idx_1 = (tmp[1] + tmp_0[1]) * HILmodel_P.Gain2_Gain;
  rtb_Sum3_a_idx_2 = (tmp[2] + tmp_0[2]) * HILmodel_P.Gain2_Gain;

  /* Product: '<S18>/Product' */
  rtb_Sum_c_idx_0 = rtb_Sum3_a_idx_0;

  /* Product: '<S18>/Product1' */
  rtb_Sum_c_idx_1 = rtb_Sum3_a_idx_1;

  /* Sum: '<S8>/Sum3' incorporates:
   *  Product: '<S17>/Product'
   *  Product: '<S17>/Product1'
   *  Product: '<S18>/Product'
   *  Product: '<S18>/Product1'
   *  Sum: '<S17>/Sum'
   *  Sum: '<S18>/Sum'
   */
  rtb_Sum3_a_idx_0 = (rtb_Sum_h_idx_1 * HILmodel_B.nu[2] - rtb_Sum_h_idx_2 *
                      HILmodel_B.nu[1]) + (rtb_Sum3_a_idx_1 * HILmodel_B.nu[5] -
    rtb_Sum3_a_idx_2 * HILmodel_B.nu[4]);
  rtb_Sum3_a_idx_1 = (rtb_Sum_h_idx_2 * HILmodel_B.nu[0] - rtb_Sum_h_idx_0 *
                      HILmodel_B.nu[2]) + (rtb_Sum3_a_idx_2 * HILmodel_B.nu[3] -
    rtb_Sum_c_idx_0 * HILmodel_B.nu[5]);
  rtb_Sum3_a_idx_2 = (rtb_Sum_h_idx_0 * HILmodel_B.nu[1] - rtb_Sum_h_idx_1 *
                      HILmodel_B.nu[0]) + (rtb_Sum_c_idx_0 * HILmodel_B.nu[4] -
    rtb_Sum_c_idx_1 * HILmodel_B.nu[3]);
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    /* Gain: '<S9>/Gain' incorporates:
     *  Constant: '<Root>/M_A'
     *  Math: '<S9>/transpose'
     *  Sum: '<S9>/Sum'
     */
    for (i = 0; i < 6; i++) {
      for (i_0 = 0; i_0 < 6; i_0++) {
        rtb_uMM[i_0 + 6 * i] = (HILmodel_P.M_A[6 * i + i_0] + HILmodel_P.M_A[6 *
          i_0 + i]) * HILmodel_P.Gain_Gain_f;
      }
    }

    /* End of Gain: '<S9>/Gain' */

    /* Selector: '<S9>/M11' */
    for (i = 0; i < 3; i++) {
      HILmodel_B.M11_j[3 * i] = rtb_uMM[6 * i];
      HILmodel_B.M11_j[1 + 3 * i] = rtb_uMM[6 * i + 1];
      HILmodel_B.M11_j[2 + 3 * i] = rtb_uMM[6 * i + 2];
    }

    /* End of Selector: '<S9>/M11' */
  }

  /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
   *  Constant: '<S6>/Constant'
   *  Constant: '<S6>/Constant1'
   *  Constant: '<S6>/Constant2'
   *  Constant: '<S6>/Constant3'
   *  Constant: '<S6>/Constant4'
   */
  if ((int32_T)HILmodel_B.nu_c_onoff == 0) {
    for (i = 0; i < 6; i++) {
      rtb_Sum1[i] = HILmodel_P.Constant3_Value[i];
    }
  } else {
    rtb_Sum1[0] = HILmodel_B.nu_c1;
    rtb_Sum1[1] = HILmodel_B.nu_c2;
    rtb_Sum1[2] = HILmodel_P.Constant_Value;
    rtb_Sum1[3] = HILmodel_P.Constant1_Value;
    rtb_Sum1[4] = HILmodel_P.Constant2_Value;
    rtb_Sum1[5] = HILmodel_P.Constant4_Value;
  }

  /* End of MultiPortSwitch: '<S6>/Multiport Switch' */

  /* Sum: '<S1>/Sum1' */
  for (i = 0; i < 6; i++) {
    rtb_Sum1[i] = HILmodel_B.nu[i] - rtb_Sum1[i];
  }

  /* End of Sum: '<S1>/Sum1' */
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    /* Selector: '<S9>/M12' */
    for (i = 0; i < 3; i++) {
      HILmodel_B.M12_i[3 * i] = rtb_uMM[(3 + i) * 6];
      HILmodel_B.M12_i[1 + 3 * i] = rtb_uMM[(3 + i) * 6 + 1];
      HILmodel_B.M12_i[2 + 3 * i] = rtb_uMM[(3 + i) * 6 + 2];
    }

    /* End of Selector: '<S9>/M12' */
  }

  /* Product: '<S9>/Product' incorporates:
   *  Sum: '<S9>/Sum1'
   */
  for (i = 0; i < 3; i++) {
    tmp[i] = HILmodel_B.M11_j[i + 6] * rtb_Sum1[2] + (HILmodel_B.M11_j[i + 3] *
      rtb_Sum1[1] + HILmodel_B.M11_j[i] * rtb_Sum1[0]);
  }

  /* End of Product: '<S9>/Product' */

  /* Product: '<S9>/Product1' incorporates:
   *  Sum: '<S9>/Sum1'
   */
  for (i = 0; i < 3; i++) {
    tmp_0[i] = HILmodel_B.M12_i[i + 6] * rtb_Sum1[5] + (HILmodel_B.M12_i[i + 3] *
      rtb_Sum1[4] + HILmodel_B.M12_i[i] * rtb_Sum1[3]);
  }

  /* End of Product: '<S9>/Product1' */

  /* Gain: '<S9>/Gain1' incorporates:
   *  Sum: '<S9>/Sum1'
   */
  rtb_costheta_idx_0 = (tmp[0] + tmp_0[0]) * HILmodel_P.Gain1_Gain_h;
  rtb_costheta_idx_1 = (tmp[1] + tmp_0[1]) * HILmodel_P.Gain1_Gain_h;
  rtb_costheta_idx_2 = (tmp[2] + tmp_0[2]) * HILmodel_P.Gain1_Gain_h;

  /* Sum: '<S19>/Sum' incorporates:
   *  Product: '<S19>/Product'
   *  Product: '<S19>/Product1'
   */
  rtb_Sum_h_idx_0 = rtb_costheta_idx_1 * rtb_Sum1[5] - rtb_costheta_idx_2 *
    rtb_Sum1[4];
  rtb_Sum_h_idx_1 = rtb_costheta_idx_2 * rtb_Sum1[3] - rtb_costheta_idx_0 *
    rtb_Sum1[5];
  rtb_Sum_h_idx_2 = rtb_costheta_idx_0 * rtb_Sum1[4] - rtb_costheta_idx_1 *
    rtb_Sum1[3];

  /* Sum: '<S20>/Sum' incorporates:
   *  Product: '<S20>/Product'
   *  Product: '<S20>/Product1'
   */
  rtb_Sum_c_idx_0 = rtb_costheta_idx_1 * rtb_Sum1[2] - rtb_costheta_idx_2 *
    rtb_Sum1[1];
  rtb_Sum_c_idx_1 = rtb_costheta_idx_2 * rtb_Sum1[0] - rtb_costheta_idx_0 *
    rtb_Sum1[2];
  rtb_Sum_c_idx_2 = rtb_costheta_idx_0 * rtb_Sum1[1] - rtb_costheta_idx_1 *
    rtb_Sum1[0];
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    /* Math: '<S9>/transpose1' */
    for (i = 0; i < 3; i++) {
      HILmodel_B.M21M12_b[3 * i] = HILmodel_B.M12_i[i];
      HILmodel_B.M21M12_b[1 + 3 * i] = HILmodel_B.M12_i[i + 3];
      HILmodel_B.M21M12_b[2 + 3 * i] = HILmodel_B.M12_i[i + 6];
    }

    /* End of Math: '<S9>/transpose1' */

    /* Selector: '<S9>/M22' */
    for (i = 0; i < 3; i++) {
      HILmodel_B.M22_l[3 * i] = rtb_uMM[(3 + i) * 6 + 3];
      HILmodel_B.M22_l[1 + 3 * i] = rtb_uMM[(3 + i) * 6 + 4];
      HILmodel_B.M22_l[2 + 3 * i] = rtb_uMM[(3 + i) * 6 + 5];
    }

    /* End of Selector: '<S9>/M22' */
  }

  /* Product: '<S9>/Product2' incorporates:
   *  Sum: '<S9>/Sum2'
   */
  for (i = 0; i < 3; i++) {
    tmp[i] = HILmodel_B.M21M12_b[i + 6] * rtb_Sum1[2] + (HILmodel_B.M21M12_b[i +
      3] * rtb_Sum1[1] + HILmodel_B.M21M12_b[i] * rtb_Sum1[0]);
  }

  /* End of Product: '<S9>/Product2' */

  /* Product: '<S9>/Product3' incorporates:
   *  Sum: '<S9>/Sum2'
   */
  for (i = 0; i < 3; i++) {
    tmp_0[i] = HILmodel_B.M22_l[i + 6] * rtb_Sum1[5] + (HILmodel_B.M22_l[i + 3] *
      rtb_Sum1[4] + HILmodel_B.M22_l[i] * rtb_Sum1[3]);
  }

  /* End of Product: '<S9>/Product3' */

  /* Gain: '<S9>/Gain2' incorporates:
   *  Sum: '<S9>/Sum2'
   */
  rtb_Sum3_ax_idx_0 = (tmp[0] + tmp_0[0]) * HILmodel_P.Gain2_Gain_o;
  rtb_Sum3_ax_idx_1 = (tmp[1] + tmp_0[1]) * HILmodel_P.Gain2_Gain_o;
  rtb_Sum3_ax_idx_2 = (tmp[2] + tmp_0[2]) * HILmodel_P.Gain2_Gain_o;

  /* Trigonometry: '<S10>/sin(theta)' */
  rtb_sintheta_idx_0 = sin(HILmodel_B.theta[0]);
  rtb_sintheta_idx_1 = sin(HILmodel_B.theta[1]);
  rtb_sintheta_idx_2 = sin(HILmodel_B.theta[2]);

  /* Trigonometry: '<S10>/cos(theta)' */
  rtb_costheta_idx_0 = cos(HILmodel_B.theta[0]);
  rtb_costheta_idx_1 = cos(HILmodel_B.theta[1]);
  rtb_costheta_idx_2 = cos(HILmodel_B.theta[2]);
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    /* Sum: '<S1>/Sum2' incorporates:
     *  Constant: '<Root>/M_A'
     *  Constant: '<Root>/M_RB'
     */
    for (i = 0; i < 36; i++) {
      HILmodel_B.M[i] = HILmodel_P.M_RB[i] + HILmodel_P.M_A[i];
    }

    /* End of Sum: '<S1>/Sum2' */
  }

  /* MultiPortSwitch: '<S2>/Multiport Switch' incorporates:
   *  Constant: '<S2>/D_NL=0'
   *  Constant: '<S2>/D_NLxx '
   */
  if ((int32_T)HILmodel_B.D_NL_onoff == 0) {
    memcpy(&rtb_uMM[0], &HILmodel_P.D_NL0_Value[0], 36U * sizeof(real_T));
  } else {
    memcpy(&rtb_uMM[0], &HILmodel_P.D_NLxx[0], 36U * sizeof(real_T));
  }

  for (i = 0; i < 6; i++) {
    /* Abs: '<S12>/Abs' */
    rtb_Sum5_i = fabs(rtb_Sum1[i]);

    /* SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn1' */
    rtb_Sum_fd[i] = rtb_Sum5_i;

    /* Abs: '<S12>/Abs' */
    rtb_Sum5[i] = rtb_Sum5_i;
  }

  /* End of MultiPortSwitch: '<S2>/Multiport Switch' */

  /* SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn2' */
  for (i = 0; i < 6; i++) {
    rtb_Sum_fd[i + 6] = rtb_Sum5[i];
  }

  /* End of SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn2' */

  /* SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn3' */
  for (i = 0; i < 6; i++) {
    rtb_Sum_fd[i + 12] = rtb_Sum5[i];
  }

  /* End of SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn3' */

  /* SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn4' */
  for (i = 0; i < 6; i++) {
    rtb_Sum_fd[i + 18] = rtb_Sum5[i];
  }

  /* End of SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn4' */

  /* SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn5' */
  for (i = 0; i < 6; i++) {
    rtb_Sum_fd[i + 24] = rtb_Sum5[i];
  }

  /* End of SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn5' */

  /* SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn6' */
  for (i = 0; i < 6; i++) {
    rtb_Sum_fd[i + 30] = rtb_Sum5[i];
  }

  /* End of SignalConversion: '<S12>/ConcatBufferAtMatrix ConcatenateIn6' */

  /* Math: '<S12>/transpose' */
  for (i = 0; i < 6; i++) {
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Sum_ge[i_0 + 6 * i] = rtb_Sum_fd[6 * i_0 + i];
    }
  }

  for (i = 0; i < 6; i++) {
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Sum_fd[i_0 + 6 * i] = rtb_Sum_ge[6 * i + i_0];
    }
  }

  /* End of Math: '<S12>/transpose' */

  /* Product: '<S12>/Product' */
  for (i = 0; i < 36; i++) {
    rtb_uMM[i] *= rtb_Sum_fd[i];
  }

  /* End of Product: '<S12>/Product' */

  /* MultiPortSwitch: '<S3>/Multiport Switch' incorporates:
   *  Constant: '<S3>/D_NL=0'
   *  Constant: '<S3>/D_NLxy '
   */
  if ((int32_T)HILmodel_B.D_NL_onoff_g == 0) {
    memcpy(&rtb_Sum_fd[0], &HILmodel_P.D_NL0_Value_n[0], 36U * sizeof(real_T));
  } else {
    memcpy(&rtb_Sum_fd[0], &HILmodel_P.D_NLxy[0], 36U * sizeof(real_T));
  }

  /* End of MultiPortSwitch: '<S3>/Multiport Switch' */
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    /* Constant: '<S12>/Constant' */
    for (i = 0; i < 6; i++) {
      HILmodel_B.MatrixConcatenate1[i] = HILmodel_P.Constant_Value_h[i];
    }

    /* End of Constant: '<S12>/Constant' */
  }

  /* Product: '<S12>/Product1' incorporates:
   *  Constant: '<S12>/Constant1'
   *  Fcn: '<S12>/v'
   */
  for (i = 0; i < 6; i++) {
    HILmodel_B.MatrixConcatenate1[i + 6] = rtb_Sum1[1] *
      HILmodel_P.Constant1_Value_l[i];
  }

  /* End of Product: '<S12>/Product1' */
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    /* Constant: '<S12>/Constant2' */
    memcpy(&HILmodel_B.MatrixConcatenate1[12], &HILmodel_P.Constant2_Value_f[0],
           18U * sizeof(real_T));
  }

  /* Product: '<S12>/Product2' incorporates:
   *  Constant: '<S12>/Constant1'
   *  Fcn: '<S12>/r'
   */
  for (i = 0; i < 6; i++) {
    HILmodel_B.MatrixConcatenate1[i + 30] = rtb_Sum1[5] *
      HILmodel_P.Constant1_Value_l[i];
  }

  /* End of Product: '<S12>/Product2' */

  /* Sum: '<S12>/Sum' incorporates:
   *  Product: '<S12>/Product3'
   */
  for (i = 0; i < 36; i++) {
    rtb_Sum_fd[i] = rtb_Sum_fd[i] * HILmodel_B.MatrixConcatenate1[i] + rtb_uMM[i];
  }

  /* End of Sum: '<S12>/Sum' */

  /* Sum: '<S1>/Sum' */
  rtb_Sum_i_0[0] = rtb_Sum_i_idx_0;
  rtb_Sum_i_0[1] = rtb_Sum_i_idx_1;
  rtb_Sum_i_0[2] = rtb_Sum_i_idx_2;
  rtb_Sum_i_0[3] = rtb_Sum3_a_idx_0;
  rtb_Sum_i_0[4] = rtb_Sum3_a_idx_1;
  rtb_Sum_i_0[5] = rtb_Sum3_a_idx_2;
  tmp_1[0] = HILmodel_B.tau1;
  tmp_1[1] = HILmodel_B.tau2;
  tmp_1[2] = HILmodel_B.tau3;
  tmp_1[3] = HILmodel_B.tau4;
  tmp_1[4] = HILmodel_B.tau5;
  tmp_1[5] = HILmodel_B.tau6;

  /* Sum: '<S1>/Sum3' incorporates:
   *  Product: '<S21>/Product'
   *  Product: '<S21>/Product1'
   *  Sum: '<S21>/Sum'
   *  Sum: '<S9>/Sum3'
   */
  rtb_Sum_h_0[0] = rtb_Sum_h_idx_0;
  rtb_Sum_h_0[1] = rtb_Sum_h_idx_1;
  rtb_Sum_h_0[2] = rtb_Sum_h_idx_2;
  rtb_Sum_h_0[3] = (rtb_Sum3_ax_idx_1 * rtb_Sum1[5] - rtb_Sum3_ax_idx_2 *
                    rtb_Sum1[4]) + rtb_Sum_c_idx_0;
  rtb_Sum_h_0[4] = (rtb_Sum3_ax_idx_2 * rtb_Sum1[3] - rtb_Sum3_ax_idx_0 *
                    rtb_Sum1[5]) + rtb_Sum_c_idx_1;
  rtb_Sum_h_0[5] = (rtb_Sum3_ax_idx_0 * rtb_Sum1[4] - rtb_Sum3_ax_idx_1 *
                    rtb_Sum1[3]) + rtb_Sum_c_idx_2;

  /* Sum: '<S1>/Sum4' incorporates:
   *  Constant: '<Root>/D_L '
   *  Product: '<S1>/Product3'
   *  Sum: '<S1>/Sum'
   *  Sum: '<S1>/Sum3'
   *  Sum: '<S1>/Sum5'
   */
  for (i = 0; i < 6; i++) {
    rtb_Sum_c_idx_0 = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Sum_c_idx_0 += HILmodel_P.D_L[6 * i_0 + i] * rtb_Sum1[i_0];
    }

    tmp_2[i] = ((tmp_1[i] - rtb_Sum_i_0[i]) - rtb_Sum_h_0[i]) - rtb_Sum_c_idx_0;
  }

  for (i = 0; i < 6; i++) {
    /* Product: '<S12>/Product4' incorporates:
     *  Sum: '<S1>/Sum5'
     */
    rtb_Sum5[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Sum5[i] += rtb_Sum_fd[6 * i_0 + i] * rtb_Sum1[i_0];
    }

    /* End of Product: '<S12>/Product4' */

    /* Sum: '<S1>/Sum5' */
    tmp_1[i] = tmp_2[i] - rtb_Sum5[i];
  }

  /* End of Sum: '<S1>/Sum4' */

  /* Product: '<S1>/Product' */
  rt_mldivide_U1d6x6_U2d_4sw8yi9v(HILmodel_B.M, tmp_1, HILmodel_B.nu_dot);

  /* SignalConversion: '<S1>/TmpSignal ConversionAtProduct1Inport1' incorporates:
   *  Fcn: '<S10>/R11'
   *  Fcn: '<S10>/R12'
   *  Fcn: '<S10>/R13'
   *  Fcn: '<S10>/R21 '
   *  Fcn: '<S10>/R22'
   *  Fcn: '<S10>/R23'
   *  Fcn: '<S10>/R31 '
   *  Fcn: '<S10>/R32'
   *  Fcn: '<S10>/R33'
   */
  rtb_sintheta_0[0] = rtb_costheta_idx_2 * rtb_costheta_idx_1;
  rtb_sintheta_0[1] = rtb_sintheta_idx_2 * rtb_costheta_idx_1;
  rtb_sintheta_0[2] = -rtb_sintheta_idx_1;
  rtb_sintheta_0[3] = rtb_costheta_idx_2 * rtb_sintheta_idx_1 *
    rtb_sintheta_idx_0 - rtb_sintheta_idx_2 * rtb_costheta_idx_0;
  rtb_sintheta_0[4] = rtb_sintheta_idx_2 * rtb_sintheta_idx_1 *
    rtb_sintheta_idx_0 + rtb_costheta_idx_2 * rtb_costheta_idx_0;
  rtb_sintheta_0[5] = rtb_costheta_idx_1 * rtb_sintheta_idx_0;
  rtb_sintheta_0[6] = rtb_costheta_idx_0 * rtb_sintheta_idx_1 *
    rtb_costheta_idx_2 + rtb_sintheta_idx_2 * rtb_sintheta_idx_0;
  rtb_sintheta_0[7] = rtb_sintheta_idx_2 * rtb_sintheta_idx_1 *
    rtb_costheta_idx_0 - rtb_costheta_idx_2 * rtb_sintheta_idx_0;
  rtb_sintheta_0[8] = rtb_costheta_idx_1 * rtb_costheta_idx_0;

  /* Product: '<S1>/Product1' */
  for (i = 0; i < 3; i++) {
    HILmodel_B.p_dot[i] = 0.0;
    HILmodel_B.p_dot[i] += rtb_sintheta_0[i] * HILmodel_B.nu[0];
    HILmodel_B.p_dot[i] += rtb_sintheta_0[i + 3] * HILmodel_B.nu[1];
    HILmodel_B.p_dot[i] += rtb_sintheta_0[i + 6] * HILmodel_B.nu[2];
  }

  /* End of Product: '<S1>/Product1' */

  /* Reshape: '<S11>/Reshape 9x1->3x3' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S11>/Constant '
   *  Fcn: '<S11>/T21 '
   *  Fcn: '<S11>/T22'
   *  Fcn: '<S11>/T23'
   *  Fcn: '<S11>/T31 '
   *  Fcn: '<S11>/T32'
   *  Fcn: '<S11>/T33'
   */
  tmp_3[0] = HILmodel_P.Constant_Value_c;
  tmp_3[1] = HILmodel_P.Constant_Value_e;
  tmp_3[2] = HILmodel_P.Constant_Value_e;
  tmp_3[3] = sin(HILmodel_B.theta[0]) * tan(HILmodel_B.theta[1]);
  tmp_3[4] = cos(HILmodel_B.theta[0]);
  tmp_3[5] = sin(HILmodel_B.theta[0]) / cos(HILmodel_B.theta[1]);
  tmp_3[6] = cos(HILmodel_B.theta[0]) * tan(HILmodel_B.theta[1]);
  tmp_3[7] = -sin(HILmodel_B.theta[0]);
  tmp_3[8] = cos(HILmodel_B.theta[0]) / cos(HILmodel_B.theta[1]);

  /* Product: '<S1>/Product2' */
  for (i = 0; i < 3; i++) {
    HILmodel_B.theta_dot[i] = 0.0;
    HILmodel_B.theta_dot[i] += tmp_3[i] * HILmodel_B.nu[3];
    HILmodel_B.theta_dot[i] += tmp_3[i + 3] * HILmodel_B.nu[4];
    HILmodel_B.theta_dot[i] += tmp_3[i + 6] * HILmodel_B.nu[5];
  }

  /* End of Product: '<S1>/Product2' */
}

/* Model update function */
void HILmodel_update(void)
{
  /* Update for Integrator: '<S1>/Integrator4' */
  HILmodel_DW.Integrator4_IWORK.IcNeedsLoading = 0;

  /* Update for Integrator: '<S1>/Integrator2' */
  HILmodel_DW.Integrator2_IWORK.IcNeedsLoading = 0;

  /* Update for Integrator: '<S1>/Integrator3' */
  HILmodel_DW.Integrator3_IWORK.IcNeedsLoading = 0;
  if (rtmIsMajorTimeStep(HILmodel_M)) {
    rt_ertODEUpdateContinuousStates(&HILmodel_M->solverInfo);
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
  if (!(++HILmodel_M->Timing.clockTick0)) {
    ++HILmodel_M->Timing.clockTickH0;
  }

  HILmodel_M->Timing.t[0] = rtsiGetSolverStopTime(&HILmodel_M->solverInfo);

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
    if (!(++HILmodel_M->Timing.clockTick1)) {
      ++HILmodel_M->Timing.clockTickH1;
    }

    HILmodel_M->Timing.t[1] = HILmodel_M->Timing.clockTick1 *
      HILmodel_M->Timing.stepSize1 + HILmodel_M->Timing.clockTickH1 *
      HILmodel_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void HILmodel_derivatives(void)
{
  /* Derivatives for Integrator: '<S1>/Integrator4' */
  {
    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator4_CSTATE[0] =
        HILmodel_B.p_dot[0];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator4_CSTATE[0] =
        0.0;
    }

    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator4_CSTATE[1] =
        HILmodel_B.p_dot[1];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator4_CSTATE[1] =
        0.0;
    }

    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator4_CSTATE[2] =
        HILmodel_B.p_dot[2];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator4_CSTATE[2] =
        0.0;
    }
  }

  /* Derivatives for Integrator: '<S1>/Integrator2' */
  {
    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator2_CSTATE[0] =
        HILmodel_B.theta_dot[0];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator2_CSTATE[0] =
        0.0;
    }

    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator2_CSTATE[1] =
        HILmodel_B.theta_dot[1];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator2_CSTATE[1] =
        0.0;
    }

    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator2_CSTATE[2] =
        HILmodel_B.theta_dot[2];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator2_CSTATE[2] =
        0.0;
    }
  }

  /* Derivatives for Integrator: '<S1>/Integrator3' */
  {
    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[0] =
        HILmodel_B.nu_dot[0];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[0] =
        0.0;
    }

    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[1] =
        HILmodel_B.nu_dot[1];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[1] =
        0.0;
    }

    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[2] =
        HILmodel_B.nu_dot[2];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[2] =
        0.0;
    }

    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[3] =
        HILmodel_B.nu_dot[3];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[3] =
        0.0;
    }

    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[4] =
        HILmodel_B.nu_dot[4];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[4] =
        0.0;
    }

    if (HILmodel_B.reset== 0.0) {
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[5] =
        HILmodel_B.nu_dot[5];
    } else {
      /* level reset is active*/
      ((XDot_HILmodel_T *) HILmodel_M->ModelData.derivs)->Integrator3_CSTATE[5] =
        0.0;
    }
  }
}

/* Model initialize function */
void HILmodel_initialize(void)
{
  HILmodel_PrevZCX.Integrator4_Reset_ZCE = UNINITIALIZED_ZCSIG;
  HILmodel_PrevZCX.Integrator2_Reset_ZCE = UNINITIALIZED_ZCSIG;
  HILmodel_PrevZCX.Integrator3_Reset_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Integrator: '<S1>/Integrator4' */
  if (rtmIsFirstInitCond(HILmodel_M)) {
    HILmodel_X.Integrator4_CSTATE[0] = 0.0;
    HILmodel_X.Integrator4_CSTATE[1] = 0.0;
    HILmodel_X.Integrator4_CSTATE[2] = 0.0;
  }

  HILmodel_DW.Integrator4_IWORK.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<S1>/Integrator2' */
  if (rtmIsFirstInitCond(HILmodel_M)) {
    HILmodel_X.Integrator2_CSTATE[0] = 0.0;
    HILmodel_X.Integrator2_CSTATE[1] = 0.0;
    HILmodel_X.Integrator2_CSTATE[2] = 0.0;
  }

  HILmodel_DW.Integrator2_IWORK.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<S1>/Integrator3' */
  if (rtmIsFirstInitCond(HILmodel_M)) {
    HILmodel_X.Integrator3_CSTATE[0] = 0.0;
    HILmodel_X.Integrator3_CSTATE[1] = 0.0;
    HILmodel_X.Integrator3_CSTATE[2] = 0.0;
    HILmodel_X.Integrator3_CSTATE[3] = 0.0;
    HILmodel_X.Integrator3_CSTATE[4] = 0.0;
    HILmodel_X.Integrator3_CSTATE[5] = 0.0;
  }

  HILmodel_DW.Integrator3_IWORK.IcNeedsLoading = 1;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(HILmodel_M)) {
    rtmSetFirstInitCond(HILmodel_M, 0);
  }
}

/* Model terminate function */
void HILmodel_terminate(void)
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
  HILmodel_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  HILmodel_update();
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
  HILmodel_initialize();
}

void MdlTerminate(void)
{
  HILmodel_terminate();
}

/* Registration function */
RT_MODEL_HILmodel_T *HILmodel(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  HILmodel_P.M_RB[21] = rtInf;

  /* initialize real-time model */
  (void) memset((void *)HILmodel_M, 0,
                sizeof(RT_MODEL_HILmodel_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&HILmodel_M->solverInfo,
                          &HILmodel_M->Timing.simTimeStep);
    rtsiSetTPtr(&HILmodel_M->solverInfo, &rtmGetTPtr(HILmodel_M));
    rtsiSetStepSizePtr(&HILmodel_M->solverInfo, &HILmodel_M->Timing.stepSize0);
    rtsiSetdXPtr(&HILmodel_M->solverInfo, &HILmodel_M->ModelData.derivs);
    rtsiSetContStatesPtr(&HILmodel_M->solverInfo, (real_T **)
                         &HILmodel_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&HILmodel_M->solverInfo,
      &HILmodel_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&HILmodel_M->solverInfo, (&rtmGetErrorStatus
      (HILmodel_M)));
    rtsiSetRTModelPtr(&HILmodel_M->solverInfo, HILmodel_M);
  }

  rtsiSetSimTimeStep(&HILmodel_M->solverInfo, MAJOR_TIME_STEP);
  HILmodel_M->ModelData.intgData.y = HILmodel_M->ModelData.odeY;
  HILmodel_M->ModelData.intgData.f[0] = HILmodel_M->ModelData.odeF[0];
  HILmodel_M->ModelData.intgData.f[1] = HILmodel_M->ModelData.odeF[1];
  HILmodel_M->ModelData.intgData.f[2] = HILmodel_M->ModelData.odeF[2];
  HILmodel_M->ModelData.intgData.f[3] = HILmodel_M->ModelData.odeF[3];
  HILmodel_M->ModelData.contStates = ((real_T *) &HILmodel_X);
  rtsiSetSolverData(&HILmodel_M->solverInfo, (void *)
                    &HILmodel_M->ModelData.intgData);
  rtsiSetSolverName(&HILmodel_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = HILmodel_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    HILmodel_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    HILmodel_M->Timing.sampleTimes = (&HILmodel_M->Timing.sampleTimesArray[0]);
    HILmodel_M->Timing.offsetTimes = (&HILmodel_M->Timing.offsetTimesArray[0]);

    /* task periods */
    HILmodel_M->Timing.sampleTimes[0] = (0.0);
    HILmodel_M->Timing.sampleTimes[1] = (0.2);

    /* task offsets */
    HILmodel_M->Timing.offsetTimes[0] = (0.0);
    HILmodel_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(HILmodel_M, &HILmodel_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = HILmodel_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    HILmodel_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(HILmodel_M, -1);
  HILmodel_M->Timing.stepSize0 = 0.2;
  HILmodel_M->Timing.stepSize1 = 0.2;
  rtmSetFirstInitCond(HILmodel_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    HILmodel_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(HILmodel_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(HILmodel_M->rtwLogInfo, (NULL));
    rtliSetLogT(HILmodel_M->rtwLogInfo, "tout");
    rtliSetLogX(HILmodel_M->rtwLogInfo, "");
    rtliSetLogXFinal(HILmodel_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(HILmodel_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(HILmodel_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(HILmodel_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(HILmodel_M->rtwLogInfo, 1);
    rtliSetLogY(HILmodel_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(HILmodel_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(HILmodel_M->rtwLogInfo, (NULL));
  }

  HILmodel_M->solverInfoPtr = (&HILmodel_M->solverInfo);
  HILmodel_M->Timing.stepSize = (0.2);
  rtsiSetFixedStepSize(&HILmodel_M->solverInfo, 0.2);
  rtsiSetSolverMode(&HILmodel_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  HILmodel_M->ModelData.blockIO = ((void *) &HILmodel_B);
  (void) memset(((void *) &HILmodel_B), 0,
                sizeof(B_HILmodel_T));

  /* parameters */
  HILmodel_M->ModelData.defaultParam = ((real_T *)&HILmodel_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &HILmodel_X;
    HILmodel_M->ModelData.contStates = (x);
    (void) memset((void *)&HILmodel_X, 0,
                  sizeof(X_HILmodel_T));
  }

  /* states (dwork) */
  HILmodel_M->ModelData.dwork = ((void *) &HILmodel_DW);
  (void) memset((void *)&HILmodel_DW, 0,
                sizeof(DW_HILmodel_T));

  /* Initialize Sizes */
  HILmodel_M->Sizes.numContStates = (12);/* Number of continuous states */
  HILmodel_M->Sizes.numY = (0);        /* Number of model outputs */
  HILmodel_M->Sizes.numU = (0);        /* Number of model inputs */
  HILmodel_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  HILmodel_M->Sizes.numSampTimes = (2);/* Number of sample times */
  HILmodel_M->Sizes.numBlocks = (156); /* Number of blocks */
  HILmodel_M->Sizes.numBlockIO = (40); /* Number of block outputs */
  HILmodel_M->Sizes.numBlockPrms = (516);/* Sum of parameter "widths" */
  return HILmodel_M;
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
#ifdef NI_ROOTMODEL_HILmodel
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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 21:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 22:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 23:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 24:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 25:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 26:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 27:
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 28:
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 29:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 37:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 38:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 39:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 40:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 21:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 22:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 23:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 24:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 25:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 26:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 27:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 28:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 29:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 37:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 38:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 39:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 40:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern HILmodel_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // 6 DOF Eqs. of motion (under construction)/reset
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.reset, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2/eta_01
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta_01, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2/eta_02
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta_02, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2/eta_03
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta_03, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1/eta_04
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta_04, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1/eta_05
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta_05, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1/eta_06
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta_06, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta3
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta3, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta4
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta4, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta5
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta5, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // 6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta6
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.eta6, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // nu_c from LabVIEW/nu_c1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.nu_c1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // nu_c from LabVIEW/nu_c2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.nu_c2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // nu_c from LabVIEW/nu_c_onoff
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.nu_c_onoff, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // tau from LabVIEW/tau1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.tau1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // tau from LabVIEW/tau2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.tau2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // tau from LabVIEW/tau3
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.tau3, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // tau from LabVIEW/tau4
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.tau4, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // tau from LabVIEW/tau5
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.tau5, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // tau from LabVIEW/tau6
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.tau6, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // D_NLxx from LabVIEW/D_NL_onoff
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.D_NL_onoff, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // D_NLxx from LabVIEW1/D_NL_onoff
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&HILmodel_B.D_NL_onoff_g, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 24;
}

double ni_extout[12];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // eta to LabVIEW/eta1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.p,0,19,0);
  } else {
    index += 1;
  }

  // eta to LabVIEW/eta2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.p,1,19,0);
  } else {
    index += 1;
  }

  // eta to LabVIEW/eta3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.p,2,19,0);
  } else {
    index += 1;
  }

  // eta to LabVIEW/eta4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.theta,0,19,0);
  } else {
    index += 1;
  }

  // eta to LabVIEW/eta5: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.theta,1,19,0);
  } else {
    index += 1;
  }

  // eta to LabVIEW/eta6: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.theta,2,19,0);
  } else {
    index += 1;
  }

  // nu to LabVIEW/nu1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,0,18,0);
  } else {
    index += 1;
  }

  // nu to LabVIEW/nu2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,1,18,0);
  } else {
    index += 1;
  }

  // nu to LabVIEW/nu3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,2,18,0);
  } else {
    index += 1;
  }

  // nu to LabVIEW/nu4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,3,18,0);
  } else {
    index += 1;
  }

  // nu to LabVIEW/nu5: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,4,18,0);
  } else {
    index += 1;
  }

  // nu to LabVIEW/nu6: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,5,18,0);
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

  // eta to LabVIEW/eta1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.p,0,19,0);

  // eta to LabVIEW/eta2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.p,1,19,0);

  // eta to LabVIEW/eta3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.p,2,19,0);

  // eta to LabVIEW/eta4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.theta,0,19,0);

  // eta to LabVIEW/eta5: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.theta,1,19,0);

  // eta to LabVIEW/eta6: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.theta,2,19,0);

  // nu to LabVIEW/nu1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,0,18,0);

  // nu to LabVIEW/nu2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,1,18,0);

  // nu to LabVIEW/nu3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,2,18,0);

  // nu to LabVIEW/nu4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,3,18,0);

  // nu to LabVIEW/nu5: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,4,18,0);

  // nu to LabVIEW/nu6: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&HILmodel_B.nu,5,18,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "hilmodel/D_L/Value", offsetof(P_HILmodel_T, D_L), 17, 36, 2, 0, 0 },

  { 1, "hilmodel/D_NLxx from LabVIEW/D_NLxx/Value", offsetof(P_HILmodel_T,
    D_NLxx), 17, 36, 2, 2, 0 },

  { 2, "hilmodel/D_NLxx from LabVIEW1/D_NLxy/Value", offsetof(P_HILmodel_T,
    D_NLxy), 17, 36, 2, 4, 0 },

  { 3, "hilmodel/M_A/Value", offsetof(P_HILmodel_T, M_A), 17, 36, 2, 6, 0 },

  { 4, "hilmodel/M_RB/Value", offsetof(P_HILmodel_T, M_RB), 17, 36, 2, 8, 0 },

  { 5,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/Gain/Gain",
    offsetof(P_HILmodel_T, Gain_Gain), 37, 1, 2, 10, 0 },

  { 6,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/Gain1/Gain",
    offsetof(P_HILmodel_T, Gain1_Gain), 37, 1, 2, 12, 0 },

  { 7,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/Gain2/Gain",
    offsetof(P_HILmodel_T, Gain2_Gain), 37, 1, 2, 14, 0 },

  { 8,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/Gain/Gain",
    offsetof(P_HILmodel_T, Gain_Gain_f), 37, 1, 2, 16, 0 },

  { 9, "hilmodel/nu_c from LabVIEW/Constant3/Value", offsetof(P_HILmodel_T,
    Constant3_Value), 38, 6, 2, 18, 0 },

  { 10, "hilmodel/nu_c from LabVIEW/Constant/Value", offsetof(P_HILmodel_T,
    Constant_Value), 37, 1, 2, 20, 0 },

  { 11, "hilmodel/nu_c from LabVIEW/Constant1/Value", offsetof(P_HILmodel_T,
    Constant1_Value), 37, 1, 2, 22, 0 },

  { 12, "hilmodel/nu_c from LabVIEW/Constant2/Value", offsetof(P_HILmodel_T,
    Constant2_Value), 37, 1, 2, 24, 0 },

  { 13, "hilmodel/nu_c from LabVIEW/Constant4/Value", offsetof(P_HILmodel_T,
    Constant4_Value), 37, 1, 2, 26, 0 },

  { 14,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/Gain1/Gain",
    offsetof(P_HILmodel_T, Gain1_Gain_h), 37, 1, 2, 28, 0 },

  { 15,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/Gain2/Gain",
    offsetof(P_HILmodel_T, Gain2_Gain_o), 37, 1, 2, 30, 0 },

  { 16,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Euler angles to attitude transformation matrix/Constant/Value",
    offsetof(P_HILmodel_T, Constant_Value_c), 37, 1, 2, 32, 0 },

  { 17,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Euler angles to attitude transformation matrix/Constant/Value",
    offsetof(P_HILmodel_T, Constant_Value_e), 37, 1, 2, 34, 0 },

  { 18, "hilmodel/D_NLxx from LabVIEW/D_NL=0/Value", offsetof(P_HILmodel_T,
    D_NL0_Value), 17, 36, 2, 36, 0 },

  { 19, "hilmodel/D_NLxx from LabVIEW1/D_NL=0/Value", offsetof(P_HILmodel_T,
    D_NL0_Value_n), 17, 36, 2, 38, 0 },

  { 20,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Constant/Value",
    offsetof(P_HILmodel_T, Constant_Value_h), 38, 6, 2, 40, 0 },

  { 21,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Constant1/Value",
    offsetof(P_HILmodel_T, Constant1_Value_l), 39, 6, 2, 42, 0 },

  { 22,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Constant2/Value",
    offsetof(P_HILmodel_T, Constant2_Value_f), 24, 18, 2, 44, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 23;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  6, 6,                                /* Parameter at index 0 */
  6, 6,                                /* Parameter at index 1 */
  6, 6,                                /* Parameter at index 2 */
  6, 6,                                /* Parameter at index 3 */
  6, 6,                                /* Parameter at index 4 */
  1, 1,                                /* Parameter at index 5 */
  1, 1,                                /* Parameter at index 6 */
  1, 1,                                /* Parameter at index 7 */
  1, 1,                                /* Parameter at index 8 */
  6, 1,                                /* Parameter at index 9 */
  1, 1,                                /* Parameter at index 10 */
  1, 1,                                /* Parameter at index 11 */
  1, 1,                                /* Parameter at index 12 */
  1, 1,                                /* Parameter at index 13 */
  1, 1,                                /* Parameter at index 14 */
  1, 1,                                /* Parameter at index 15 */
  1, 1,                                /* Parameter at index 16 */
  1, 1,                                /* Parameter at index 17 */
  6, 6,                                /* Parameter at index 18 */
  6, 6,                                /* Parameter at index 19 */
  6, 1,                                /* Parameter at index 20 */
  1, 6,                                /* Parameter at index 21 */
  6, 3,                                /* Parameter at index 22 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "hilmodel/6 DOF Eqs. of motion (under construction)/reset", 0, "",
    offsetof(B_HILmodel_T, reset)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1,
    "hilmodel/6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2/eta_01",
    0, "", offsetof(B_HILmodel_T, eta_01)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    2, 0 },

  { 2,
    "hilmodel/6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2/eta_02",
    0, "", offsetof(B_HILmodel_T, eta_02)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    4, 0 },

  { 3,
    "hilmodel/6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2/eta_03",
    0, "", offsetof(B_HILmodel_T, eta_03)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    6, 0 },

  { 4, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator4", 0,
    "p(1,1)", offsetof(B_HILmodel_T, p)+0*sizeof(real_T), BLOCKIO_SIG, 19, 1, 2,
    8, 0 },

  { 5, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator4", 0,
    "p(1,2)", offsetof(B_HILmodel_T, p)+1*sizeof(real_T), BLOCKIO_SIG, 19, 1, 2,
    10, 0 },

  { 6, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator4", 0,
    "p(1,3)", offsetof(B_HILmodel_T, p)+2*sizeof(real_T), BLOCKIO_SIG, 19, 1, 2,
    12, 0 },

  { 7,
    "hilmodel/6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1/eta_04",
    0, "", offsetof(B_HILmodel_T, eta_04)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    14, 0 },

  { 8,
    "hilmodel/6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1/eta_05",
    0, "", offsetof(B_HILmodel_T, eta_05)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    16, 0 },

  { 9,
    "hilmodel/6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1/eta_06",
    0, "", offsetof(B_HILmodel_T, eta_06)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    18, 0 },

  { 10, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator2", 0,
    "theta(1,1)", offsetof(B_HILmodel_T, theta)+0*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 20, 0 },

  { 11, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator2", 0,
    "theta(1,2)", offsetof(B_HILmodel_T, theta)+1*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 22, 0 },

  { 12, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator2", 0,
    "theta(1,3)", offsetof(B_HILmodel_T, theta)+2*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 24, 0 },

  { 13,
    "hilmodel/6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta1",
    0, "", offsetof(B_HILmodel_T, eta1)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    26, 0 },

  { 14,
    "hilmodel/6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta2",
    0, "", offsetof(B_HILmodel_T, eta2)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    28, 0 },

  { 15,
    "hilmodel/6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta3",
    0, "", offsetof(B_HILmodel_T, eta3)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    30, 0 },

  { 16,
    "hilmodel/6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta4",
    0, "", offsetof(B_HILmodel_T, eta4)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    32, 0 },

  { 17,
    "hilmodel/6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta5",
    0, "", offsetof(B_HILmodel_T, eta5)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    34, 0 },

  { 18,
    "hilmodel/6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta6",
    0, "", offsetof(B_HILmodel_T, eta6)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    36, 0 },

  { 19, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator3", 0,
    "nu(1,1)", offsetof(B_HILmodel_T, nu)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1,
    2, 38, 0 },

  { 20, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator3", 0,
    "nu(1,2)", offsetof(B_HILmodel_T, nu)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1,
    2, 40, 0 },

  { 21, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator3", 0,
    "nu(1,3)", offsetof(B_HILmodel_T, nu)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1,
    2, 42, 0 },

  { 22, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator3", 0,
    "nu(1,4)", offsetof(B_HILmodel_T, nu)+3*sizeof(real_T), BLOCKIO_SIG, 18, 1,
    2, 44, 0 },

  { 23, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator3", 0,
    "nu(1,5)", offsetof(B_HILmodel_T, nu)+4*sizeof(real_T), BLOCKIO_SIG, 18, 1,
    2, 46, 0 },

  { 24, "hilmodel/6 DOF Eqs. of motion (under construction)/Integrator3", 0,
    "nu(1,6)", offsetof(B_HILmodel_T, nu)+5*sizeof(real_T), BLOCKIO_SIG, 18, 1,
    2, 48, 0 },

  { 25,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M11",
    0, "(1,1)", offsetof(B_HILmodel_T, M11)+0*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 50, 0 },

  { 26,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M11",
    0, "(2,1)", offsetof(B_HILmodel_T, M11)+1*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 52, 0 },

  { 27,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M11",
    0, "(3,1)", offsetof(B_HILmodel_T, M11)+2*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 54, 0 },

  { 28,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M11",
    0, "(1,2)", offsetof(B_HILmodel_T, M11)+3*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 56, 0 },

  { 29,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M11",
    0, "(2,2)", offsetof(B_HILmodel_T, M11)+4*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 58, 0 },

  { 30,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M11",
    0, "(3,2)", offsetof(B_HILmodel_T, M11)+5*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 60, 0 },

  { 31,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M11",
    0, "(1,3)", offsetof(B_HILmodel_T, M11)+6*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 62, 0 },

  { 32,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M11",
    0, "(2,3)", offsetof(B_HILmodel_T, M11)+7*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 64, 0 },

  { 33,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M11",
    0, "(3,3)", offsetof(B_HILmodel_T, M11)+8*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 66, 0 },

  { 34,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M12",
    0, "(1,1)", offsetof(B_HILmodel_T, M12)+0*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 68, 0 },

  { 35,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M12",
    0, "(2,1)", offsetof(B_HILmodel_T, M12)+1*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 70, 0 },

  { 36,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M12",
    0, "(3,1)", offsetof(B_HILmodel_T, M12)+2*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 72, 0 },

  { 37,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M12",
    0, "(1,2)", offsetof(B_HILmodel_T, M12)+3*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 74, 0 },

  { 38,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M12",
    0, "(2,2)", offsetof(B_HILmodel_T, M12)+4*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 76, 0 },

  { 39,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M12",
    0, "(3,2)", offsetof(B_HILmodel_T, M12)+5*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 78, 0 },

  { 40,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M12",
    0, "(1,3)", offsetof(B_HILmodel_T, M12)+6*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 80, 0 },

  { 41,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M12",
    0, "(2,3)", offsetof(B_HILmodel_T, M12)+7*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 82, 0 },

  { 42,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M12",
    0, "(3,3)", offsetof(B_HILmodel_T, M12)+8*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 84, 0 },

  { 43,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/transpose1",
    0, "M21=M12'(1,1)", offsetof(B_HILmodel_T, M21M12)+0*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 86, 0 },

  { 44,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/transpose1",
    0, "M21=M12'(2,1)", offsetof(B_HILmodel_T, M21M12)+1*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 88, 0 },

  { 45,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/transpose1",
    0, "M21=M12'(3,1)", offsetof(B_HILmodel_T, M21M12)+2*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 90, 0 },

  { 46,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/transpose1",
    0, "M21=M12'(1,2)", offsetof(B_HILmodel_T, M21M12)+3*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 92, 0 },

  { 47,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/transpose1",
    0, "M21=M12'(2,2)", offsetof(B_HILmodel_T, M21M12)+4*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 94, 0 },

  { 48,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/transpose1",
    0, "M21=M12'(3,2)", offsetof(B_HILmodel_T, M21M12)+5*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 96, 0 },

  { 49,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/transpose1",
    0, "M21=M12'(1,3)", offsetof(B_HILmodel_T, M21M12)+6*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 98, 0 },

  { 50,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/transpose1",
    0, "M21=M12'(2,3)", offsetof(B_HILmodel_T, M21M12)+7*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 100, 0 },

  { 51,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/transpose1",
    0, "M21=M12'(3,3)", offsetof(B_HILmodel_T, M21M12)+8*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 102, 0 },

  { 52,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M22",
    0, "(1,1)", offsetof(B_HILmodel_T, M22)+0*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 104, 0 },

  { 53,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M22",
    0, "(2,1)", offsetof(B_HILmodel_T, M22)+1*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 106, 0 },

  { 54,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M22",
    0, "(3,1)", offsetof(B_HILmodel_T, M22)+2*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 108, 0 },

  { 55,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M22",
    0, "(1,2)", offsetof(B_HILmodel_T, M22)+3*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 110, 0 },

  { 56,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M22",
    0, "(2,2)", offsetof(B_HILmodel_T, M22)+4*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 112, 0 },

  { 57,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M22",
    0, "(3,2)", offsetof(B_HILmodel_T, M22)+5*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 114, 0 },

  { 58,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M22",
    0, "(1,3)", offsetof(B_HILmodel_T, M22)+6*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 116, 0 },

  { 59,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M22",
    0, "(2,3)", offsetof(B_HILmodel_T, M22)+7*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 118, 0 },

  { 60,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces/M22",
    0, "(3,3)", offsetof(B_HILmodel_T, M22)+8*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 120, 0 },

  { 61,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M11",
    0, "(1,1)", offsetof(B_HILmodel_T, M11_j)+0*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 122, 0 },

  { 62,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M11",
    0, "(2,1)", offsetof(B_HILmodel_T, M11_j)+1*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 124, 0 },

  { 63,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M11",
    0, "(3,1)", offsetof(B_HILmodel_T, M11_j)+2*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 126, 0 },

  { 64,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M11",
    0, "(1,2)", offsetof(B_HILmodel_T, M11_j)+3*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 128, 0 },

  { 65,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M11",
    0, "(2,2)", offsetof(B_HILmodel_T, M11_j)+4*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 130, 0 },

  { 66,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M11",
    0, "(3,2)", offsetof(B_HILmodel_T, M11_j)+5*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 132, 0 },

  { 67,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M11",
    0, "(1,3)", offsetof(B_HILmodel_T, M11_j)+6*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 134, 0 },

  { 68,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M11",
    0, "(2,3)", offsetof(B_HILmodel_T, M11_j)+7*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 136, 0 },

  { 69,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M11",
    0, "(3,3)", offsetof(B_HILmodel_T, M11_j)+8*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 138, 0 },

  { 70, "hilmodel/nu_c from LabVIEW/nu_c1", 0, "", offsetof(B_HILmodel_T, nu_c1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 140, 0 },

  { 71, "hilmodel/nu_c from LabVIEW/nu_c2", 0, "", offsetof(B_HILmodel_T, nu_c2)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 142, 0 },

  { 72, "hilmodel/nu_c from LabVIEW/nu_c_onoff", 0, "", offsetof(B_HILmodel_T,
    nu_c_onoff)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 144, 0 },

  { 73,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M12",
    0, "(1,1)", offsetof(B_HILmodel_T, M12_i)+0*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 146, 0 },

  { 74,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M12",
    0, "(2,1)", offsetof(B_HILmodel_T, M12_i)+1*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 148, 0 },

  { 75,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M12",
    0, "(3,1)", offsetof(B_HILmodel_T, M12_i)+2*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 150, 0 },

  { 76,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M12",
    0, "(1,2)", offsetof(B_HILmodel_T, M12_i)+3*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 152, 0 },

  { 77,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M12",
    0, "(2,2)", offsetof(B_HILmodel_T, M12_i)+4*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 154, 0 },

  { 78,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M12",
    0, "(3,2)", offsetof(B_HILmodel_T, M12_i)+5*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 156, 0 },

  { 79,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M12",
    0, "(1,3)", offsetof(B_HILmodel_T, M12_i)+6*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 158, 0 },

  { 80,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M12",
    0, "(2,3)", offsetof(B_HILmodel_T, M12_i)+7*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 160, 0 },

  { 81,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M12",
    0, "(3,3)", offsetof(B_HILmodel_T, M12_i)+8*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 162, 0 },

  { 82,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/transpose1",
    0, "M21=M12'(1,1)", offsetof(B_HILmodel_T, M21M12_b)+0*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 164, 0 },

  { 83,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/transpose1",
    0, "M21=M12'(2,1)", offsetof(B_HILmodel_T, M21M12_b)+1*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 166, 0 },

  { 84,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/transpose1",
    0, "M21=M12'(3,1)", offsetof(B_HILmodel_T, M21M12_b)+2*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 168, 0 },

  { 85,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/transpose1",
    0, "M21=M12'(1,2)", offsetof(B_HILmodel_T, M21M12_b)+3*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 170, 0 },

  { 86,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/transpose1",
    0, "M21=M12'(2,2)", offsetof(B_HILmodel_T, M21M12_b)+4*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 172, 0 },

  { 87,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/transpose1",
    0, "M21=M12'(3,2)", offsetof(B_HILmodel_T, M21M12_b)+5*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 174, 0 },

  { 88,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/transpose1",
    0, "M21=M12'(1,3)", offsetof(B_HILmodel_T, M21M12_b)+6*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 176, 0 },

  { 89,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/transpose1",
    0, "M21=M12'(2,3)", offsetof(B_HILmodel_T, M21M12_b)+7*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 178, 0 },

  { 90,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/transpose1",
    0, "M21=M12'(3,3)", offsetof(B_HILmodel_T, M21M12_b)+8*sizeof(real_T),
    BLOCKIO_SIG, 20, 1, 2, 180, 0 },

  { 91,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M22",
    0, "(1,1)", offsetof(B_HILmodel_T, M22_l)+0*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 182, 0 },

  { 92,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M22",
    0, "(2,1)", offsetof(B_HILmodel_T, M22_l)+1*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 184, 0 },

  { 93,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M22",
    0, "(3,1)", offsetof(B_HILmodel_T, M22_l)+2*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 186, 0 },

  { 94,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M22",
    0, "(1,2)", offsetof(B_HILmodel_T, M22_l)+3*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 188, 0 },

  { 95,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M22",
    0, "(2,2)", offsetof(B_HILmodel_T, M22_l)+4*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 190, 0 },

  { 96,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M22",
    0, "(3,2)", offsetof(B_HILmodel_T, M22_l)+5*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 192, 0 },

  { 97,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M22",
    0, "(1,3)", offsetof(B_HILmodel_T, M22_l)+6*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 194, 0 },

  { 98,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M22",
    0, "(2,3)", offsetof(B_HILmodel_T, M22_l)+7*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 196, 0 },

  { 99,
    "hilmodel/6 DOF Eqs. of motion (under construction)/6 DOF Coriolis forces1/M22",
    0, "(3,3)", offsetof(B_HILmodel_T, M22_l)+8*sizeof(real_T), BLOCKIO_SIG, 20,
    1, 2, 198, 0 },

  { 100, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(1,1)",
    offsetof(B_HILmodel_T, M)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 200, 0 },

  { 101, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(2,1)",
    offsetof(B_HILmodel_T, M)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 202, 0 },

  { 102, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(3,1)",
    offsetof(B_HILmodel_T, M)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 204, 0 },

  { 103, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(4,1)",
    offsetof(B_HILmodel_T, M)+3*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 206, 0 },

  { 104, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(5,1)",
    offsetof(B_HILmodel_T, M)+4*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 208, 0 },

  { 105, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(6,1)",
    offsetof(B_HILmodel_T, M)+5*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 210, 0 },

  { 106, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(1,2)",
    offsetof(B_HILmodel_T, M)+6*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 212, 0 },

  { 107, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(2,2)",
    offsetof(B_HILmodel_T, M)+7*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 214, 0 },

  { 108, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(3,2)",
    offsetof(B_HILmodel_T, M)+8*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 216, 0 },

  { 109, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(4,2)",
    offsetof(B_HILmodel_T, M)+9*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 218, 0 },

  { 110, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(5,2)",
    offsetof(B_HILmodel_T, M)+10*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 220, 0 },

  { 111, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(6,2)",
    offsetof(B_HILmodel_T, M)+11*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 222, 0 },

  { 112, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(1,3)",
    offsetof(B_HILmodel_T, M)+12*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 224, 0 },

  { 113, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(2,3)",
    offsetof(B_HILmodel_T, M)+13*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 226, 0 },

  { 114, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(3,3)",
    offsetof(B_HILmodel_T, M)+14*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 228, 0 },

  { 115, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(4,3)",
    offsetof(B_HILmodel_T, M)+15*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 230, 0 },

  { 116, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(5,3)",
    offsetof(B_HILmodel_T, M)+16*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 232, 0 },

  { 117, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(6,3)",
    offsetof(B_HILmodel_T, M)+17*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 234, 0 },

  { 118, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(1,4)",
    offsetof(B_HILmodel_T, M)+18*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 236, 0 },

  { 119, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(2,4)",
    offsetof(B_HILmodel_T, M)+19*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 238, 0 },

  { 120, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(3,4)",
    offsetof(B_HILmodel_T, M)+20*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 240, 0 },

  { 121, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(4,4)",
    offsetof(B_HILmodel_T, M)+21*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 242, 0 },

  { 122, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(5,4)",
    offsetof(B_HILmodel_T, M)+22*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 244, 0 },

  { 123, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(6,4)",
    offsetof(B_HILmodel_T, M)+23*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 246, 0 },

  { 124, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(1,5)",
    offsetof(B_HILmodel_T, M)+24*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 248, 0 },

  { 125, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(2,5)",
    offsetof(B_HILmodel_T, M)+25*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 250, 0 },

  { 126, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(3,5)",
    offsetof(B_HILmodel_T, M)+26*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 252, 0 },

  { 127, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(4,5)",
    offsetof(B_HILmodel_T, M)+27*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 254, 0 },

  { 128, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(5,5)",
    offsetof(B_HILmodel_T, M)+28*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 256, 0 },

  { 129, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(6,5)",
    offsetof(B_HILmodel_T, M)+29*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 258, 0 },

  { 130, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(1,6)",
    offsetof(B_HILmodel_T, M)+30*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 260, 0 },

  { 131, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(2,6)",
    offsetof(B_HILmodel_T, M)+31*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 262, 0 },

  { 132, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(3,6)",
    offsetof(B_HILmodel_T, M)+32*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 264, 0 },

  { 133, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(4,6)",
    offsetof(B_HILmodel_T, M)+33*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 266, 0 },

  { 134, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(5,6)",
    offsetof(B_HILmodel_T, M)+34*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 268, 0 },

  { 135, "hilmodel/6 DOF Eqs. of motion (under construction)/Sum2", 0, "M(6,6)",
    offsetof(B_HILmodel_T, M)+35*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 270, 0 },

  { 136, "hilmodel/tau from LabVIEW/tau1", 0, "", offsetof(B_HILmodel_T, tau1)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 272, 0 },

  { 137, "hilmodel/tau from LabVIEW/tau2", 0, "", offsetof(B_HILmodel_T, tau2)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 274, 0 },

  { 138, "hilmodel/tau from LabVIEW/tau3", 0, "", offsetof(B_HILmodel_T, tau3)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 276, 0 },

  { 139, "hilmodel/tau from LabVIEW/tau4", 0, "", offsetof(B_HILmodel_T, tau4)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 278, 0 },

  { 140, "hilmodel/tau from LabVIEW/tau5", 0, "", offsetof(B_HILmodel_T, tau5)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 280, 0 },

  { 141, "hilmodel/tau from LabVIEW/tau6", 0, "", offsetof(B_HILmodel_T, tau6)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 282, 0 },

  { 142, "hilmodel/D_NLxx from LabVIEW/D_NL_onoff", 0, "", offsetof(B_HILmodel_T,
    D_NL_onoff)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 284, 0 },

  { 143, "hilmodel/D_NLxx from LabVIEW1/D_NL_onoff", 0, "", offsetof
    (B_HILmodel_T, D_NL_onoff_g)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 286, 0
  },

  { 144,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(1,1)", offsetof(B_HILmodel_T, MatrixConcatenate1)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 288, 0 },

  { 145,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(2,1)", offsetof(B_HILmodel_T, MatrixConcatenate1)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 290, 0 },

  { 146,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(3,1)", offsetof(B_HILmodel_T, MatrixConcatenate1)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 292, 0 },

  { 147,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(4,1)", offsetof(B_HILmodel_T, MatrixConcatenate1)+3*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 294, 0 },

  { 148,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(5,1)", offsetof(B_HILmodel_T, MatrixConcatenate1)+4*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 296, 0 },

  { 149,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(6,1)", offsetof(B_HILmodel_T, MatrixConcatenate1)+5*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 298, 0 },

  { 150,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(1,2)", offsetof(B_HILmodel_T, MatrixConcatenate1)+6*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 300, 0 },

  { 151,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(2,2)", offsetof(B_HILmodel_T, MatrixConcatenate1)+7*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 302, 0 },

  { 152,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(3,2)", offsetof(B_HILmodel_T, MatrixConcatenate1)+8*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 304, 0 },

  { 153,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(4,2)", offsetof(B_HILmodel_T, MatrixConcatenate1)+9*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 306, 0 },

  { 154,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(5,2)", offsetof(B_HILmodel_T, MatrixConcatenate1)+10*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 308, 0 },

  { 155,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(6,2)", offsetof(B_HILmodel_T, MatrixConcatenate1)+11*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 310, 0 },

  { 156,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(1,3)", offsetof(B_HILmodel_T, MatrixConcatenate1)+12*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 312, 0 },

  { 157,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(2,3)", offsetof(B_HILmodel_T, MatrixConcatenate1)+13*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 314, 0 },

  { 158,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(3,3)", offsetof(B_HILmodel_T, MatrixConcatenate1)+14*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 316, 0 },

  { 159,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(4,3)", offsetof(B_HILmodel_T, MatrixConcatenate1)+15*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 318, 0 },

  { 160,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(5,3)", offsetof(B_HILmodel_T, MatrixConcatenate1)+16*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 320, 0 },

  { 161,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(6,3)", offsetof(B_HILmodel_T, MatrixConcatenate1)+17*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 322, 0 },

  { 162,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(1,4)", offsetof(B_HILmodel_T, MatrixConcatenate1)+18*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 324, 0 },

  { 163,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(2,4)", offsetof(B_HILmodel_T, MatrixConcatenate1)+19*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 326, 0 },

  { 164,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(3,4)", offsetof(B_HILmodel_T, MatrixConcatenate1)+20*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 328, 0 },

  { 165,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(4,4)", offsetof(B_HILmodel_T, MatrixConcatenate1)+21*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 330, 0 },

  { 166,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(5,4)", offsetof(B_HILmodel_T, MatrixConcatenate1)+22*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 332, 0 },

  { 167,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(6,4)", offsetof(B_HILmodel_T, MatrixConcatenate1)+23*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 334, 0 },

  { 168,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(1,5)", offsetof(B_HILmodel_T, MatrixConcatenate1)+24*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 336, 0 },

  { 169,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(2,5)", offsetof(B_HILmodel_T, MatrixConcatenate1)+25*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 338, 0 },

  { 170,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(3,5)", offsetof(B_HILmodel_T, MatrixConcatenate1)+26*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 340, 0 },

  { 171,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(4,5)", offsetof(B_HILmodel_T, MatrixConcatenate1)+27*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 342, 0 },

  { 172,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(5,5)", offsetof(B_HILmodel_T, MatrixConcatenate1)+28*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 344, 0 },

  { 173,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(6,5)", offsetof(B_HILmodel_T, MatrixConcatenate1)+29*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 346, 0 },

  { 174,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(1,6)", offsetof(B_HILmodel_T, MatrixConcatenate1)+30*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 348, 0 },

  { 175,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(2,6)", offsetof(B_HILmodel_T, MatrixConcatenate1)+31*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 350, 0 },

  { 176,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(3,6)", offsetof(B_HILmodel_T, MatrixConcatenate1)+32*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 352, 0 },

  { 177,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(4,6)", offsetof(B_HILmodel_T, MatrixConcatenate1)+33*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 354, 0 },

  { 178,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(5,6)", offsetof(B_HILmodel_T, MatrixConcatenate1)+34*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 356, 0 },

  { 179,
    "hilmodel/6 DOF Eqs. of motion (under construction)/Subsystem/Matrix Concatenate1",
    0, "(6,6)", offsetof(B_HILmodel_T, MatrixConcatenate1)+35*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 358, 0 },

  { 180, "hilmodel/6 DOF Eqs. of motion (under construction)/Product", 0,
    "nu_dot(1,1)", offsetof(B_HILmodel_T, nu_dot)+0*sizeof(real_T), BLOCKIO_SIG,
    18, 1, 2, 360, 0 },

  { 181, "hilmodel/6 DOF Eqs. of motion (under construction)/Product", 0,
    "nu_dot(1,2)", offsetof(B_HILmodel_T, nu_dot)+1*sizeof(real_T), BLOCKIO_SIG,
    18, 1, 2, 362, 0 },

  { 182, "hilmodel/6 DOF Eqs. of motion (under construction)/Product", 0,
    "nu_dot(1,3)", offsetof(B_HILmodel_T, nu_dot)+2*sizeof(real_T), BLOCKIO_SIG,
    18, 1, 2, 364, 0 },

  { 183, "hilmodel/6 DOF Eqs. of motion (under construction)/Product", 0,
    "nu_dot(1,4)", offsetof(B_HILmodel_T, nu_dot)+3*sizeof(real_T), BLOCKIO_SIG,
    18, 1, 2, 366, 0 },

  { 184, "hilmodel/6 DOF Eqs. of motion (under construction)/Product", 0,
    "nu_dot(1,5)", offsetof(B_HILmodel_T, nu_dot)+4*sizeof(real_T), BLOCKIO_SIG,
    18, 1, 2, 368, 0 },

  { 185, "hilmodel/6 DOF Eqs. of motion (under construction)/Product", 0,
    "nu_dot(1,6)", offsetof(B_HILmodel_T, nu_dot)+5*sizeof(real_T), BLOCKIO_SIG,
    18, 1, 2, 370, 0 },

  { 186, "hilmodel/6 DOF Eqs. of motion (under construction)/Product1", 0,
    "p_dot(1,1)", offsetof(B_HILmodel_T, p_dot)+0*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 372, 0 },

  { 187, "hilmodel/6 DOF Eqs. of motion (under construction)/Product1", 0,
    "p_dot(1,2)", offsetof(B_HILmodel_T, p_dot)+1*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 374, 0 },

  { 188, "hilmodel/6 DOF Eqs. of motion (under construction)/Product1", 0,
    "p_dot(1,3)", offsetof(B_HILmodel_T, p_dot)+2*sizeof(real_T), BLOCKIO_SIG,
    19, 1, 2, 376, 0 },

  { 189, "hilmodel/6 DOF Eqs. of motion (under construction)/Product2", 0,
    "theta_dot(1,1)", offsetof(B_HILmodel_T, theta_dot)+0*sizeof(real_T),
    BLOCKIO_SIG, 19, 1, 2, 378, 0 },

  { 190, "hilmodel/6 DOF Eqs. of motion (under construction)/Product2", 0,
    "theta_dot(1,2)", offsetof(B_HILmodel_T, theta_dot)+1*sizeof(real_T),
    BLOCKIO_SIG, 19, 1, 2, 380, 0 },

  { 191, "hilmodel/6 DOF Eqs. of motion (under construction)/Product2", 0,
    "theta_dot(1,3)", offsetof(B_HILmodel_T, theta_dot)+2*sizeof(real_T),
    BLOCKIO_SIG, 19, 1, 2, 382, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 192;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 36;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "6 DOF Eqs. of motion (under construction)/reset", 0, EXT_IN, 1, 1, 1 },

  { 1,
    "6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2/eta_01",
    0, EXT_IN, 1, 1, 1 },

  { 2,
    "6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2/eta_02",
    0, EXT_IN, 1, 1, 1 },

  { 3,
    "6 DOF Eqs. of motion (under construction)/eta_0(1:3) from LabVIEW2/eta_03",
    0, EXT_IN, 1, 1, 1 },

  { 4,
    "6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1/eta_04",
    0, EXT_IN, 1, 1, 1 },

  { 5,
    "6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1/eta_05",
    0, EXT_IN, 1, 1, 1 },

  { 6,
    "6 DOF Eqs. of motion (under construction)/eta_0(4:6) from LabVIEW1/eta_06",
    0, EXT_IN, 1, 1, 1 },

  { 7, "6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta1", 0,
    EXT_IN, 1, 1, 1 },

  { 8, "6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta2", 0,
    EXT_IN, 1, 1, 1 },

  { 9, "6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta3", 0,
    EXT_IN, 1, 1, 1 },

  { 10, "6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta4", 0,
    EXT_IN, 1, 1, 1 },

  { 11, "6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta5", 0,
    EXT_IN, 1, 1, 1 },

  { 12, "6 DOF Eqs. of motion (under construction)/nu_0 from LabVIEW/eta6", 0,
    EXT_IN, 1, 1, 1 },

  { 13, "nu_c from LabVIEW/nu_c1", 0, EXT_IN, 1, 1, 1 },

  { 14, "nu_c from LabVIEW/nu_c2", 0, EXT_IN, 1, 1, 1 },

  { 15, "nu_c from LabVIEW/nu_c_onoff", 0, EXT_IN, 1, 1, 1 },

  { 16, "tau from LabVIEW/tau1", 0, EXT_IN, 1, 1, 1 },

  { 17, "tau from LabVIEW/tau2", 0, EXT_IN, 1, 1, 1 },

  { 18, "tau from LabVIEW/tau3", 0, EXT_IN, 1, 1, 1 },

  { 19, "tau from LabVIEW/tau4", 0, EXT_IN, 1, 1, 1 },

  { 20, "tau from LabVIEW/tau5", 0, EXT_IN, 1, 1, 1 },

  { 21, "tau from LabVIEW/tau6", 0, EXT_IN, 1, 1, 1 },

  { 22, "D_NLxx from LabVIEW/D_NL_onoff", 0, EXT_IN, 1, 1, 1 },

  { 23, "D_NLxx from LabVIEW1/D_NL_onoff", 0, EXT_IN, 1, 1, 1 },

  { 0, "eta to LabVIEW/eta1", 0, EXT_OUT, 1, 1, 1 },

  { 1, "eta to LabVIEW/eta2", 0, EXT_OUT, 1, 1, 1 },

  { 2, "eta to LabVIEW/eta3", 0, EXT_OUT, 1, 1, 1 },

  { 3, "eta to LabVIEW/eta4", 0, EXT_OUT, 1, 1, 1 },

  { 4, "eta to LabVIEW/eta5", 0, EXT_OUT, 1, 1, 1 },

  { 5, "eta to LabVIEW/eta6", 0, EXT_OUT, 1, 1, 1 },

  { 6, "nu to LabVIEW/nu1", 0, EXT_OUT, 1, 1, 1 },

  { 7, "nu to LabVIEW/nu2", 0, EXT_OUT, 1, 1, 1 },

  { 8, "nu to LabVIEW/nu3", 0, EXT_OUT, 1, 1, 1 },

  { 9, "nu to LabVIEW/nu4", 0, EXT_OUT, 1, 1, 1 },

  { 10, "nu to LabVIEW/nu5", 0, EXT_OUT, 1, 1, 1 },

  { 11, "nu to LabVIEW/nu6", 0, EXT_OUT, 1, 1, 1 },

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
  "hilmodel";
static char* NI_CompiledModelVersion = "1.12";
static char* NI_CompiledModelDateTime = "Sat Jan 10 18:08:25 2015";
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
   The undef allows us to access the real HILmodel_P
   In the rest of the code HILmodel_P is redefine to be the read-side
   of rtParameter.
 */
#undef HILmodel_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &HILmodel_P, sizeof(P_HILmodel_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka HILmodel_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_HILmodel_T));
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
             (P_HILmodel_T));
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
               (P_HILmodel_T));

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
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof(P_HILmodel_T));
    WriteSideDirtyFlag = 0;
    return NI_OK;
  }

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter subindex is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (ReadSideDirtyFlag == 1) {
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof(P_HILmodel_T));
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
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof(P_HILmodel_T));
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
      *numContStates = 12;
      *numDiscStates = 363;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (contStates && contStatesNames) {
    idx = 0;
    contStates[idx] = NIRT_GetValueByDataType(&HILmodel_X.Integrator4_CSTATE[0],
      0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator4_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&HILmodel_X.Integrator4_CSTATE[0],
      1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator4_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&HILmodel_X.Integrator4_CSTATE[0],
      2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator4_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&HILmodel_X.Integrator2_CSTATE[0],
      0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&HILmodel_X.Integrator2_CSTATE[0],
      1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType(&HILmodel_X.Integrator2_CSTATE[0],
      2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    for (count = 0; count < 6; count++) {
      contStates[idx] = NIRT_GetValueByDataType(&HILmodel_X.Integrator3_CSTATE[0],
        count, 0, 0);
      strcpy(contStatesNames + (idx++ * 100), "Integrator3_CSTATE");
    }
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.reset_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.reset_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_01_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_01_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_02_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_02_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_03_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_03_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta3_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta3_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_04_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_04_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_05_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_05_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_06_DWORK1, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_06_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta4_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta4_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta5_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta5_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta6_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta6_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta1_DWORK1_p, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta1_DWORK1_p");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta2_DWORK1_l, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta2_DWORK1_l");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta3_DWORK1_m, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta3_DWORK1_m");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta4_DWORK1_g, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta4_DWORK1_g");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta5_DWORK1_h, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta5_DWORK1_h");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta6_DWORK1_g, 0, 0,
      0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta6_DWORK1_g");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu3_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu3_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu4_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu4_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu5_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu5_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu6_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu6_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu_c1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu_c1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu_c2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu_c2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu_c_onoff_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu_c_onoff_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau1_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau2_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau2_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau3_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau3_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau4_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau4_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau5_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau5_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau6_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau6_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.D_NL_onoff_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.D_NL_onoff_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.D_NL_onoff_DWORK1_l,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.D_NL_onoff_DWORK1_l");
    discStates[idx] = NIRT_GetValueByDataType
      (&HILmodel_DW.Integrator4_IWORK.IcNeedsLoading, 0, 10, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&HILmodel_DW.Integrator4_IWORK.IcNeedsLoading");
    discStates[idx] = NIRT_GetValueByDataType
      (&HILmodel_DW.Integrator2_IWORK.IcNeedsLoading, 0, 10, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&HILmodel_DW.Integrator2_IWORK.IcNeedsLoading");
    discStates[idx] = NIRT_GetValueByDataType
      (&HILmodel_DW.Integrator3_IWORK.IcNeedsLoading, 0, 10, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&HILmodel_DW.Integrator3_IWORK.IcNeedsLoading");
    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.reset_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.reset_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_01_DWORK2,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_01_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_02_DWORK2,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_02_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_03_DWORK2,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_03_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta1_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta1_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta2_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta2_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta3_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta3_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_04_DWORK2,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_04_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_05_DWORK2,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_05_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta_06_DWORK2,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta_06_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta4_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta4_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta5_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta5_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta6_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta6_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta1_DWORK2_p,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta1_DWORK2_p");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta2_DWORK2_j,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta2_DWORK2_j");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta3_DWORK2_p,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta3_DWORK2_p");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta4_DWORK2_e,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta4_DWORK2_e");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta5_DWORK2_i,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta5_DWORK2_i");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.eta6_DWORK2_g,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.eta6_DWORK2_g");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu1_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu1_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu2_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu2_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu3_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu3_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu4_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu4_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu5_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu5_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu6_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu6_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu_c1_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu_c1_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu_c2_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu_c2_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.nu_c_onoff_DWORK2,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.nu_c_onoff_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau1_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau1_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau2_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau2_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau3_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau3_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau4_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau4_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau5_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau5_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.tau6_DWORK2, count,
        25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.tau6_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.D_NL_onoff_DWORK2,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.D_NL_onoff_DWORK2");
    }

    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&HILmodel_DW.D_NL_onoff_DWORK2_p,
        count, 25, 0);
      strcpy(discStatesNames + (idx++ * 100), "&HILmodel_DW.D_NL_onoff_DWORK2_p");
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
    NIRT_SetValueByDataType(&HILmodel_X.Integrator4_CSTATE[0], 0, contStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_X.Integrator4_CSTATE[0], 1, contStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_X.Integrator4_CSTATE[0], 2, contStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_X.Integrator2_CSTATE[0], 0, contStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_X.Integrator2_CSTATE[0], 1, contStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_X.Integrator2_CSTATE[0], 2, contStates[idx
      ++], 0, 0);
    for (count = 0; count < 6; count++) {
      NIRT_SetValueByDataType(&HILmodel_X.Integrator3_CSTATE[0], count,
        contStates[idx++], 0, 0);
    }
  }

  if (discStates) {
    idx = 0;
    NIRT_SetValueByDataType(&HILmodel_DW.reset_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta_01_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta_02_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta_03_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta1_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta2_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta3_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta_04_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta_05_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta_06_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta4_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta5_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta6_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta1_DWORK1_p, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta2_DWORK1_l, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta3_DWORK1_m, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta4_DWORK1_g, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta5_DWORK1_h, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.eta6_DWORK1_g, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.nu1_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.nu2_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.nu3_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.nu4_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.nu5_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.nu6_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.nu_c1_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.nu_c2_DWORK1, 0, discStates[idx++], 0,
      0);
    NIRT_SetValueByDataType(&HILmodel_DW.nu_c_onoff_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.tau1_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.tau2_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.tau3_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.tau4_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.tau5_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.tau6_DWORK1, 0, discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.D_NL_onoff_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.D_NL_onoff_DWORK1_l, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.Integrator4_IWORK.IcNeedsLoading, 0,
      discStates[idx++], 10, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.Integrator2_IWORK.IcNeedsLoading, 0,
      discStates[idx++], 10, 0);
    NIRT_SetValueByDataType(&HILmodel_DW.Integrator3_IWORK.IcNeedsLoading, 0,
      discStates[idx++], 10, 0);
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.reset_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta_01_DWORK2, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta_02_DWORK2, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta_03_DWORK2, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta1_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta2_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta3_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta_04_DWORK2, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta_05_DWORK2, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta_06_DWORK2, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta4_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta5_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta6_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta1_DWORK2_p, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta2_DWORK2_j, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta3_DWORK2_p, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta4_DWORK2_e, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta5_DWORK2_i, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.eta6_DWORK2_g, count, discStates[idx
        ++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.nu1_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.nu2_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.nu3_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.nu4_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.nu5_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.nu6_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.nu_c1_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.nu_c2_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.nu_c_onoff_DWORK2, count,
        discStates[idx++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.tau1_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.tau2_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.tau3_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.tau4_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.tau5_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.tau6_DWORK2, count, discStates[idx++],
        25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.D_NL_onoff_DWORK2, count,
        discStates[idx++], 25, 0);
    }

    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&HILmodel_DW.D_NL_onoff_DWORK2_p, count,
        discStates[idx++], 25, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
    S->Timing.clockTick1 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_HILmodel
