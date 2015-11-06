/*
 * LgV2.c
 *
 * Real-Time Workshop code generation for Simulink model "LgV2.mdl".
 *
 * Model Version              : 1.30
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Mon Mar 17 14:04:20 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "LgV2.h"
#include "LgV2_private.h"

/* Block signals (auto storage) */
BlockIO_LgV2 LgV2_B;

/* Continuous states */
ContinuousStates_LgV2 LgV2_X;

/* Solver Matrices */

/* A and B matrices used by ODE5 fixed-step solver */
static const real_T rt_ODE5_A[6] = {
  1.0/5.0, 3.0/10.0, 4.0/5.0, 8.0/9.0, 1.0, 1.0
};

static const real_T rt_ODE5_B[6][6] = {
  { 1.0/5.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  { 3.0/40.0, 9.0/40.0, 0.0, 0.0, 0.0, 0.0 },

  { 44.0/45.0, -56.0/15.0, 32.0/9.0, 0.0, 0.0, 0.0 },

  { 19372.0/6561.0, -25360.0/2187.0, 64448.0/6561.0, -212.0/729.0, 0.0, 0.0 },

  { 9017.0/3168.0, -355.0/33.0, 46732.0/5247.0, 49.0/176.0, -5103.0/18656.0, 0.0
  },

  { 35.0/384.0, 0.0, 500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0 }
};

/* Block states (auto storage) */
D_Work_LgV2 LgV2_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_LgV2 LgV2_PrevZCSigState;

/* Real-time model */
RT_MODEL_LgV2 LgV2_M_;
RT_MODEL_LgV2 *LgV2_M = &LgV2_M_;

/* Function: rt_WriteMat4FileHeader =========================================
 * Abstract:
 *      Writes out MAT-file header.  Returns success or failure.
 *
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*********************************************************************
 * Lookup Binary Search Utility BINARYSEARCH_real_T
 */
void BINARYSEARCH_real_T( uint32_T *piLeft, uint32_T *piRght, real_T u, const
  real_T *pData, uint32_T iHi)
{
  /* Find the location of current input value in the data table. */
  *piLeft = 0;
  *piRght = iHi;
  if (u <= pData[0] ) {
    /* Less than or equal to the smallest point in the table. */
    *piRght = 0;
  } else if (u >= pData[iHi] ) {
    /* Greater than or equal to the largest point in the table. */
    *piLeft = iHi;
  } else {
    uint32_T i;

    /* Do a binary search. */
    while (( *piRght - *piLeft ) > 1 ) {
      /* Get the average of the left and right indices using to Floor rounding. */
      i = (*piLeft + *piRght) >> 1;

      /* Move either the right index or the left index so that */
      /*  LeftDataPoint <= CurrentValue < RightDataPoint */
      if (u < pData[i] ) {
        *piRght = i;
      } else {
        *piLeft = i;
      }
    }
  }
}

/* end macro BINARYSEARCH_real_T
 *********************************************************************/

/*********************************************************************
 * Lookup Utility LookUp_real_T_real_T
 */
void LookUp_real_T_real_T( real_T *pY, const real_T *pYData, real_T u, const
  real_T *pUData, uint32_T iHi)
{
  uint32_T iLeft;
  uint32_T iRght;
  BINARYSEARCH_real_T( &(iLeft), &(iRght), u, pUData, iHi);

  {
    real_T lambda;
    if (pUData[iRght] > pUData[iLeft] ) {
      real_T num;
      real_T den;
      den = pUData[iRght];
      den = den - pUData[iLeft];
      num = u;
      num = num - pUData[iLeft];
      lambda = num / den;
    } else {
      lambda = 0;
    }

    {
      real_T yLeftCast;
      real_T yRghtCast;
      yLeftCast = pYData[iLeft];
      yRghtCast = pYData[iRght];
      if (lambda != 0) {
        yLeftCast += lambda * ( yRghtCast - yLeftCast );
      }

      (*pY) = yLeftCast;
    }
  }
}

/* end function LookUp_real_T_real_T
 *********************************************************************/
void MWDSPCG_Pseudoinverse_D(real_T pS[], real_T pU[], real_T pV[], real_T pX[],
  const int32_T M, const int32_T N)
{
  int32_T ppSIdx;
  real_T tol;
  real_T cabsS;
  int32_T P;
  int32_T rank;
  int32_T ppXIdx;
  int32_T ppUIdx;
  int32_T ppVIdx;
  int32_T j;
  int32_T k;
  rank = 0;
  P = rt_MIN(M, N);
  tol = (real_T)rt_MAX(M, N) * pS[0U] * 2.2204460492503131E-016;
  ppSIdx = P - 1;
  while (P > 0) {
    cabsS = fabs(pS[ppSIdx]);
    ppSIdx = ppSIdx - 1;
    if (cabsS >= tol) {
      rank = P;
      P = 0;
    }

    P = P - 1;
  }

  if (rank != 0) {
    ppXIdx = 0;

    /* Initialize output array */
    for (P = 0; P < N * M; P = P + 1) {
      pX[ppXIdx] = 0.0;
      ppXIdx = ppXIdx + 1;
    }

    ppXIdx = 0;
    for (j = 0; j < M; j = j + 1) {
      for (P = 0; P < N; P = P + 1) {
        ppVIdx = P;
        ppUIdx = j;
        ppSIdx = 0;
        for (k = 0; k < rank; k = k + 1) {
          tol = pV[ppVIdx] * pU[ppUIdx] / pS[ppSIdx];
          pX[ppXIdx] = pX[ppXIdx] + tol;
          ppSIdx = ppSIdx + 1;
          ppVIdx = ppVIdx + N;
          ppUIdx = ppUIdx + M;
        }

        ppXIdx = ppXIdx + 1;
      }
    }
  }
}

/* This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE5_IntgData *id = (ODE5_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T *f4 = id->f[4];
  real_T *f5 = id->f[5];
  real_T hB[6];
  int_T i;
  int_T nXc = 17;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y,x,
                nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  LgV2_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  LgV2_output(0);
  LgV2_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE5_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  LgV2_output(0);
  LgV2_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++)
    hB[i] = h * rt_ODE5_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  LgV2_output(0);
  LgV2_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++)
    hB[i] = h * rt_ODE5_B[3][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  LgV2_output(0);
  LgV2_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++)
    hB[i] = h * rt_ODE5_B[4][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  LgV2_output(0);
  LgV2_derivatives();

  /* tnew = t + hA(6);
     ynew = y + f*hB(:,6); */
  for (i = 0; i <= 5; i++)
    hB[i] = h * rt_ODE5_B[5][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4] + f5[i]*hB[5]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void LgV2_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(LgV2_M)) {
    LgV2_M->Timing.t[0] = rtsiGetT(&LgV2_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(LgV2_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&LgV2_M->solverInfo,
                          ((LgV2_M->Timing.clockTick0+1)*
      LgV2_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T tmp;
    real_T tmp_0[5];
    int32_T i;
    real_T tmp_1[18];
    real_T tmp_2[9];
    real_T tmp_3[4];
    real_T tmp_4[6];
    real_T tmp_5[3];
    int32_T tmp_6;

    /* Gain: '<S199>/QTM In2 Error' */
    LgV2_B.QTMIn2Error = LgV2_P.QTMIn2Error_Gain * LgV2_B.QTMIn[1];

    /* Gain: '<S199>/QTM In9 Residual' */
    LgV2_B.QTMIn9Residual = LgV2_P.QTMIn9Residual_Gain * LgV2_B.QTMIn[8];

    /* Gain: '<S199>/QTM In3' */
    LgV2_B.QTMIn3 = LgV2_P.QTMIn3_Gain * LgV2_B.QTMIn[2];

    /* Gain: '<S199>/mm2m x' */
    LgV2_B.mm2mx = LgV2_P.mm2mx_Gain * LgV2_B.QTMIn3;

    /* Gain: '<S199>/QTM In4' */
    LgV2_B.QTMIn4 = LgV2_P.QTMIn4_Gain * LgV2_B.QTMIn[3];

    /* Gain: '<S199>/mm2m y' */
    LgV2_B.mm2my = LgV2_P.mm2my_Gain * LgV2_B.QTMIn4;

    /* Gain: '<S199>/QTM In6' */
    LgV2_B.QTMIn6 = LgV2_P.QTMIn6_Gain * LgV2_B.QTMIn[5];

    /* Gain: '<S199>/d2r yaw' */
    LgV2_B.d2ryaw = LgV2_P.d2ryaw_Gain * LgV2_B.QTMIn6;

    /* Derivative Block: '<S199>/Derivative1' */
    {
      real_T t = LgV2_M->Timing.t[0];
      real_T timeStampA = LgV2_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = LgV2_DWork.Derivative1_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        LgV2_B.Derivative1[0] = 0.0;
        LgV2_B.Derivative1[1] = 0.0;
        LgV2_B.Derivative1[2] = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &LgV2_DWork.Derivative1_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 4;
          }
        } else if (timeStampA >= t) {
          lastBank += 4;
        }

        deltaT = t - *lastBank++;
        LgV2_B.Derivative1[0] = (LgV2_B.mm2mx - *lastBank++) / deltaT;
        LgV2_B.Derivative1[1] = (LgV2_B.mm2my - *lastBank++) / deltaT;
        LgV2_B.Derivative1[2] = (LgV2_B.d2ryaw - *lastBank++) / deltaT;
      }
    }

    /* Outputs for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Constant: '<S5>/Enable Linear Simulator'
     *  EnablePort: '<S202>/Enable'
     */
    if (rtmIsMajorTimeStep(LgV2_M) && rtmIsMajorTimeStep(LgV2_M)) {
      if (LgV2_P.EnableLinearSimulator_Value > 0.0) {
        if (LgV2_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S209>/Integrator' */
          if (rtmIsFirstInitCond(LgV2_M)) {
            LgV2_X.Integrator_CSTATE_f[0] = 0.0;
            LgV2_X.Integrator_CSTATE_f[1] = 0.0;
            LgV2_X.Integrator_CSTATE_f[2] = 0.0;
          }

          LgV2_DWork.Integrator_IWORK_o.IcNeedsLoading = 1;

          /* Integrator Block: '<S209>/Integrator1' */
          if (rtmIsFirstInitCond(LgV2_M)) {
            LgV2_X.Integrator1_CSTATE_h[0] = 0.0;
            LgV2_X.Integrator1_CSTATE_h[1] = 0.0;
            LgV2_X.Integrator1_CSTATE_h[2] = 0.0;
          }

          LgV2_DWork.Integrator1_IWORK_l.IcNeedsLoading = 1;
          LgV2_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (LgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
          LgV2_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (LgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* Gain: '<S210>/-N_r' incorporates:
         *  Constant: '<S210>/N_r'
         */
        LgV2_B.N_r_o = LgV2_P.N_r_Gain_f * LgV2_P.N_r_Value_e;

        /* Gain: '<S210>/-N_v' incorporates:
         *  Constant: '<S210>/N_v'
         */
        LgV2_B.N_v_h = LgV2_P.N_v_Gain_k * LgV2_P.N_v_Value_k;

        /* Gain: '<S210>/-X_u' incorporates:
         *  Constant: '<S210>/X_u'
         */
        LgV2_B.X_u_o = LgV2_P.X_u_Gain_k * LgV2_P.X_u_Value_l;

        /* Gain: '<S210>/-Y_v' incorporates:
         *  Constant: '<S210>/Y_v'
         */
        LgV2_B.Y_v_g = LgV2_P.Y_v_Gain_p * LgV2_P.Y_v_Value_n;

        /* Gain: '<S210>/-Y_vr' incorporates:
         *  Constant: '<S210>/Y_r'
         */
        LgV2_B.Y_vr_g = LgV2_P.Y_vr_Gain_c * LgV2_P.Y_r_Value_o;

        /* Reshape: '<S210>/Linear Dampning matrix' incorporates:
         *  Constant: '<S210>/D_L_12'
         *  Constant: '<S210>/D_L_13'
         *  Constant: '<S210>/D_L_21'
         *  Constant: '<S210>/D_L_31'
         */
        LgV2_B.LinearDampningmatrix_m[0] = LgV2_B.X_u_o;
        LgV2_B.LinearDampningmatrix_m[1] = LgV2_P.D_L_21_Value_i;
        LgV2_B.LinearDampningmatrix_m[2] = LgV2_P.D_L_31_Value_h;
        LgV2_B.LinearDampningmatrix_m[3] = LgV2_P.D_L_12_Value_k;
        LgV2_B.LinearDampningmatrix_m[4] = LgV2_B.Y_v_g;
        LgV2_B.LinearDampningmatrix_m[5] = LgV2_B.N_v_h;
        LgV2_B.LinearDampningmatrix_m[6] = LgV2_P.D_L_13_Value_c;
        LgV2_B.LinearDampningmatrix_m[7] = LgV2_B.Y_vr_g;
        LgV2_B.LinearDampningmatrix_m[8] = LgV2_B.N_r_o;

        /* Constant: '<S211>/psi_0' */
        LgV2_B.psi_0 = LgV2_P.psi_0_Value;

        /* Constant: '<S211>/x_0' */
        LgV2_B.x_0 = LgV2_P.x_0_Value;

        /* Constant: '<S211>/y_0' */
        LgV2_B.y_0 = LgV2_P.y_0_Value;

        /* Constant: '<S212>/r_0' */
        LgV2_B.r_0 = LgV2_P.r_0_Value;

        /* Constant: '<S212>/u_0' */
        LgV2_B.u_0 = LgV2_P.u_0_Value;

        /* Constant: '<S212>/v_0' */
        LgV2_B.v_0 = LgV2_P.v_0_Value;
      }

      /* Integrator Block: '<S209>/Integrator'
       */
      if (rtmIsMajorTimeStep(LgV2_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &LgV2_PrevZCSigState.Integrator_Reset_ZCE_k,
                           LgV2_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || LgV2_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            LgV2_DWork.Integrator_IWORK_o.IcNeedsLoading) {
          LgV2_X.Integrator_CSTATE_f[0] = LgV2_B.u_0;
          LgV2_X.Integrator_CSTATE_f[1] = LgV2_B.v_0;
          LgV2_X.Integrator_CSTATE_f[2] = LgV2_B.r_0;
        }

        LgV2_DWork.Integrator_IWORK_o.IcNeedsLoading = 0;
      }

      LgV2_B.Integrator_p[0] = LgV2_X.Integrator_CSTATE_f[0];
      LgV2_B.Integrator_p[1] = LgV2_X.Integrator_CSTATE_f[1];
      LgV2_B.Integrator_p[2] = LgV2_X.Integrator_CSTATE_f[2];

      /* Integrator Block: '<S209>/Integrator1'
       */
      if (rtmIsMajorTimeStep(LgV2_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &LgV2_PrevZCSigState.Integrator1_Reset_ZCE_g,
                           LgV2_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || LgV2_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            LgV2_DWork.Integrator1_IWORK_l.IcNeedsLoading) {
          LgV2_X.Integrator1_CSTATE_h[0] = LgV2_B.x_0;
          LgV2_X.Integrator1_CSTATE_h[1] = LgV2_B.y_0;
          LgV2_X.Integrator1_CSTATE_h[2] = LgV2_B.psi_0;
        }

        LgV2_DWork.Integrator1_IWORK_l.IcNeedsLoading = 0;
      }

      LgV2_B.Integrator1_f[0] = LgV2_X.Integrator1_CSTATE_h[0];
      LgV2_B.Integrator1_f[1] = LgV2_X.Integrator1_CSTATE_h[1];
      LgV2_B.Integrator1_f[2] = LgV2_X.Integrator1_CSTATE_h[2];
      if (rtmIsMajorTimeStep(LgV2_M)) {
        /* Sum: '<S213>/M_11' incorporates:
         *  Constant: '<S213>/X_udot'
         *  Constant: '<S213>/m'
         */
        LgV2_B.M_11_f = LgV2_P.m_Value_f - LgV2_P.X_udot_Value_l;

        /* Sum: '<S213>/M_22' incorporates:
         *  Constant: '<S213>/Y_vdot'
         *  Constant: '<S213>/m'
         */
        LgV2_B.M_22_c = LgV2_P.m_Value_f - LgV2_P.Y_vdot_Value_n;

        /* Product: '<S213>/m x_g' incorporates:
         *  Constant: '<S213>/m'
         *  Constant: '<S213>/x_g'
         */
        LgV2_B.mx_g_e = LgV2_P.m_Value_f * LgV2_P.x_g_Value_g;

        /* Sum: '<S213>/M_32' incorporates:
         *  Constant: '<S213>/N_vdot'
         */
        LgV2_B.M_32_n = LgV2_B.mx_g_e - LgV2_P.N_vdot_Value_d;

        /* Sum: '<S213>/M_23' incorporates:
         *  Constant: '<S213>/Y_rdot'
         */
        LgV2_B.M_23_l = LgV2_B.mx_g_e - LgV2_P.Y_rdot_Value_e;

        /* Sum: '<S213>/M_33' incorporates:
         *  Constant: '<S213>/I_z'
         *  Constant: '<S213>/N_rdot'
         */
        LgV2_B.M_33_p = LgV2_P.I_z_Value_e - LgV2_P.N_rdot_Value_p;

        /* Reshape: '<S213>/M' incorporates:
         *  Constant: '<S213>/M_12'
         *  Constant: '<S213>/M_13'
         *  Constant: '<S213>/M_21'
         *  Constant: '<S213>/M_31'
         */
        LgV2_B.M[0] = LgV2_B.M_11_f;
        LgV2_B.M[1] = LgV2_P.M_21_Value_h;
        LgV2_B.M[2] = LgV2_P.M_31_Value_o;
        LgV2_B.M[3] = LgV2_P.M_12_Value_n;
        LgV2_B.M[4] = LgV2_B.M_22_c;
        LgV2_B.M[5] = LgV2_B.M_32_n;
        LgV2_B.M[6] = LgV2_P.M_13_Value_f;
        LgV2_B.M[7] = LgV2_B.M_23_l;
        LgV2_B.M[8] = LgV2_B.M_33_p;

        /* Product Block: '<S213>/Inverse' */
        {
          static const int_T dims[3] = { 3, 3, 3 };

          rt_MatDivRR_Dbl(LgV2_B.Inverse, LgV2_B.M,
                          &LgV2_DWork.Inverse_DWORK4[0], (real_T*)
                          &LgV2_DWork.Pseudoinverse_X[0],
                          &LgV2_DWork.Inverse_DWORK2[0], (real_T*)
                          &LgV2_DWork.Inverse_DWORK3[0],
                          &dims[0]);
        }
      }

      /* Fcn: '<S214>/R11' */
      LgV2_B.R11_n = cos(LgV2_B.Integrator1_f[2]);

      /* Fcn: '<S214>/R21' */
      LgV2_B.R21_m4 = sin(LgV2_B.Integrator1_f[2]);

      /* Fcn: '<S214>/R12' */
      LgV2_B.R12_l = -1.0 * sin(LgV2_B.Integrator1_f[2]);

      /* Fcn: '<S214>/R22' */
      LgV2_B.R22_pu = cos(LgV2_B.Integrator1_f[2]);

      /* Reshape: '<S214>/R(psi)' incorporates:
       *  Constant: '<S214>/R13'
       *  Constant: '<S214>/R23'
       *  Constant: '<S214>/R31'
       *  Constant: '<S214>/R32'
       *  Constant: '<S214>/R33'
       */
      LgV2_B.Rpsi_o[0] = LgV2_B.R11_n;
      LgV2_B.Rpsi_o[1] = LgV2_B.R21_m4;
      LgV2_B.Rpsi_o[2] = LgV2_P.R31_Value_m;
      LgV2_B.Rpsi_o[3] = LgV2_B.R12_l;
      LgV2_B.Rpsi_o[4] = LgV2_B.R22_pu;
      LgV2_B.Rpsi_o[5] = LgV2_P.R32_Value_h;
      LgV2_B.Rpsi_o[6] = LgV2_P.R13_Value_b;
      LgV2_B.Rpsi_o[7] = LgV2_P.R23_Value_e;
      LgV2_B.Rpsi_o[8] = LgV2_P.R33_Value_c;
      for (i = 0; i < 3; i++) {
        /* Product: '<S209>/Product1' */
        LgV2_B.Product1_ob[i] = 0.0;
        LgV2_B.Product1_ob[i] = LgV2_B.LinearDampningmatrix_m[i] *
          LgV2_B.Integrator_p[0] + LgV2_B.Product1_ob[i];
        LgV2_B.Product1_ob[i] = LgV2_B.LinearDampningmatrix_m[i + 3] *
          LgV2_B.Integrator_p[1] + LgV2_B.Product1_ob[i];
        LgV2_B.Product1_ob[i] = LgV2_B.LinearDampningmatrix_m[i + 6] *
          LgV2_B.Integrator_p[2] + LgV2_B.Product1_ob[i];

        /* Product: '<S209>/Product3' */
        LgV2_B.Product3_f[i] = 0.0;
        LgV2_B.Product3_f[i] = LgV2_B.Rpsi_o[i] * LgV2_B.Integrator_p[0] +
          LgV2_B.Product3_f[i];
        LgV2_B.Product3_f[i] = LgV2_B.Rpsi_o[i + 3] * LgV2_B.Integrator_p[1] +
          LgV2_B.Product3_f[i];
        LgV2_B.Product3_f[i] = LgV2_B.Rpsi_o[i + 6] * LgV2_B.Integrator_p[2] +
          LgV2_B.Product3_f[i];
      }

      /* Gain: '<S202>/eta_surge_hil' */
      LgV2_B.eta_surge_hil = LgV2_P.eta_surge_hil_Gain * LgV2_B.Integrator1_f[0];

      /* Gain: '<S202>/eta_sway_hil' */
      LgV2_B.eta_sway_hil = LgV2_P.eta_sway_hil_Gain * LgV2_B.Integrator1_f[1];

      /* Gain: '<S202>/eta_yaw_hil' */
      LgV2_B.eta_yaw_hil = LgV2_P.eta_yaw_hil_Gain * LgV2_B.Integrator1_f[2];

      /* Gain: '<S202>/etadot_surge_hil' */
      LgV2_B.etadot_surge_hil = LgV2_P.etadot_surge_hil_Gain *
        LgV2_B.Product3_f[0];

      /* Gain: '<S202>/etadot_sway_hil' */
      LgV2_B.etadot_sway_hil = LgV2_P.etadot_sway_hil_Gain * LgV2_B.Product3_f[1];

      /* Gain: '<S202>/etadot_yaw_hil' */
      LgV2_B.etadot_yaw_hil = LgV2_P.etadot_yaw_hil_Gain * LgV2_B.Product3_f[2];

      /* Gain: '<S202>/nu_surge_hil' */
      LgV2_B.nu_surge_hil = LgV2_P.nu_surge_hil_Gain * LgV2_B.Integrator_p[0];

      /* Gain: '<S202>/nu_sway_hil' */
      LgV2_B.nu_sway_hil = LgV2_P.nu_sway_hil_Gain * LgV2_B.Integrator_p[1];

      /* Gain: '<S202>/nu_yaw_hil' */
      LgV2_B.nu_yaw_hil = LgV2_P.nu_yaw_hil_Gain * LgV2_B.Integrator_p[2];
    }

    /* end of Outputs for SubSystem: '<S5>/Linear Simulator' */

    /* MultiPortSwitch: '<S4>/Etadot Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)LgV2_P.ControllerInputSelector_Value == 0) {
      LgV2_B.EtadotSwitch[0] = LgV2_B.Derivative1[0];
      LgV2_B.EtadotSwitch[1] = LgV2_B.Derivative1[1];
      LgV2_B.EtadotSwitch[2] = LgV2_B.Derivative1[2];
    } else {
      LgV2_B.EtadotSwitch[0] = LgV2_B.etadot_surge_hil;
      LgV2_B.EtadotSwitch[1] = LgV2_B.etadot_sway_hil;
      LgV2_B.EtadotSwitch[2] = LgV2_B.etadot_yaw_hil;
    }

    /* Gain: '<S4>/etadot_surge' */
    LgV2_B.etadot_surge = LgV2_P.etadot_surge_Gain * LgV2_B.EtadotSwitch[0];

    /* Gain: '<S4>/etadot_sway' */
    LgV2_B.etadot_sway = LgV2_P.etadot_sway_Gain * LgV2_B.EtadotSwitch[1];

    /* Gain: '<S4>/etadot_yaw' */
    LgV2_B.etadot_yaw = LgV2_P.etadot_yaw_Gain * LgV2_B.EtadotSwitch[2];

    /* MultiPortSwitch: '<S4>/Eta Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)LgV2_P.ControllerInputSelector_Value == 0) {
      LgV2_B.EtaSwitch[0] = LgV2_B.mm2mx;
      LgV2_B.EtaSwitch[1] = LgV2_B.mm2my;
      LgV2_B.EtaSwitch[2] = LgV2_B.d2ryaw;
    } else {
      LgV2_B.EtaSwitch[0] = LgV2_B.eta_surge_hil;
      LgV2_B.EtaSwitch[1] = LgV2_B.eta_sway_hil;
      LgV2_B.EtaSwitch[2] = LgV2_B.eta_yaw_hil;
    }

    /* Gain: '<S4>/eta_surge' */
    LgV2_B.eta_surge = LgV2_P.eta_surge_Gain * LgV2_B.EtaSwitch[0];

    /* Gain: '<S4>/eta_sway' */
    LgV2_B.eta_sway = LgV2_P.eta_sway_Gain * LgV2_B.EtaSwitch[1];

    /* Gain: '<S4>/eta_yaw' */
    LgV2_B.eta_yaw = LgV2_P.eta_yaw_Gain * LgV2_B.EtaSwitch[2];

    /* Gain: '<S199>/QTM In8' */
    LgV2_B.QTMIn8 = LgV2_P.QTMIn8_Gain * LgV2_B.QTMIn[7];

    /* Gain: '<S199>/d2r roll' */
    LgV2_B.d2rroll = LgV2_P.d2rroll_Gain * LgV2_B.QTMIn8;

    /* Gain: '<S199>/QTM In7' */
    LgV2_B.QTMIn7 = LgV2_P.QTMIn7_Gain * LgV2_B.QTMIn[6];

    /* Gain: '<S199>/d2r pitch' */
    LgV2_B.d2rpitch = LgV2_P.d2rpitch_Gain * LgV2_B.QTMIn7;

    /* Trigonometry: '<S200>/sin(theta)' */
    LgV2_B.sintheta[0] = sin(LgV2_B.d2rroll);
    LgV2_B.sintheta[1] = sin(LgV2_B.d2rpitch);
    LgV2_B.sintheta[2] = sin(LgV2_B.d2ryaw);

    /* Trigonometry: '<S200>/cos(theta)' */
    LgV2_B.costheta[0] = cos(LgV2_B.d2rroll);
    LgV2_B.costheta[1] = cos(LgV2_B.d2rpitch);
    LgV2_B.costheta[2] = cos(LgV2_B.d2ryaw);

    /* Fcn: '<S200>/R11' */
    LgV2_B.R11 = LgV2_B.costheta[1] * LgV2_B.costheta[2];

    /* Fcn: '<S200>/R21 ' */
    LgV2_B.R21 = LgV2_B.sintheta[0] * LgV2_B.sintheta[1] * LgV2_B.costheta[2] +
      (-LgV2_B.costheta[0]) * LgV2_B.sintheta[2];

    /* Fcn: '<S200>/R31 ' */
    LgV2_B.R31 = LgV2_B.costheta[0] * LgV2_B.sintheta[1] * LgV2_B.costheta[2] +
      LgV2_B.sintheta[0] * LgV2_B.sintheta[2];

    /* Fcn: '<S200>/R12' */
    LgV2_B.R12 = LgV2_B.costheta[1] * LgV2_B.sintheta[2];

    /* Fcn: '<S200>/R22' */
    LgV2_B.R22 = LgV2_B.sintheta[0] * LgV2_B.sintheta[1] * LgV2_B.sintheta[2] +
      LgV2_B.costheta[0] * LgV2_B.costheta[2];

    /* Fcn: '<S200>/R32' */
    LgV2_B.R32 = LgV2_B.costheta[0] * LgV2_B.sintheta[1] * LgV2_B.sintheta[2] +
      (-LgV2_B.sintheta[0]) * LgV2_B.costheta[2];

    /* Fcn: '<S200>/R13' */
    LgV2_B.R13 = -LgV2_B.sintheta[1];

    /* Fcn: '<S200>/R23' */
    LgV2_B.R23 = LgV2_B.sintheta[0] * LgV2_B.costheta[1];

    /* Fcn: '<S200>/R33' */
    LgV2_B.R33 = LgV2_B.costheta[0] * LgV2_B.costheta[1];

    /* Reshape: '<S200>/Reshape 9x1->3x3' */
    LgV2_B.Reshape9x13x3[0] = LgV2_B.R11;
    LgV2_B.Reshape9x13x3[1] = LgV2_B.R21;
    LgV2_B.Reshape9x13x3[2] = LgV2_B.R31;
    LgV2_B.Reshape9x13x3[3] = LgV2_B.R12;
    LgV2_B.Reshape9x13x3[4] = LgV2_B.R22;
    LgV2_B.Reshape9x13x3[5] = LgV2_B.R32;
    LgV2_B.Reshape9x13x3[6] = LgV2_B.R13;
    LgV2_B.Reshape9x13x3[7] = LgV2_B.R23;
    LgV2_B.Reshape9x13x3[8] = LgV2_B.R33;

    /* Concatenate: '<S199>/Matrix Concatenate' incorporates:
     *  Constant: '<S199>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = LgV2_B.Reshape9x13x3[3 * i];
      tmp_1[1 + 6 * i] = LgV2_B.Reshape9x13x3[3 * i + 1];
      tmp_1[2 + 6 * i] = LgV2_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = LgV2_P.Constant1_Value[3 * i];
      tmp_1[4 + 6 * i] = LgV2_P.Constant1_Value[3 * i + 1];
      tmp_1[5 + 6 * i] = LgV2_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&LgV2_B.MatrixConcatenate2[0]), (void *)&tmp_1[0], 18U *
           sizeof(real_T));

    /* Concatenate: '<S199>/Matrix Concatenate1' incorporates:
     *  Constant: '<S199>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = LgV2_P.Constant1_Value[3 * i];
      tmp_1[1 + 6 * i] = LgV2_P.Constant1_Value[3 * i + 1];
      tmp_1[2 + 6 * i] = LgV2_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = LgV2_B.Reshape9x13x3[3 * i];
      tmp_1[4 + 6 * i] = LgV2_B.Reshape9x13x3[3 * i + 1];
      tmp_1[5 + 6 * i] = LgV2_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&LgV2_B.MatrixConcatenate2[18]), (void *)&tmp_1[0], 18U *
           sizeof(real_T));

    /* Gain: '<S199>/QTM In5' */
    LgV2_B.QTMIn5 = LgV2_P.QTMIn5_Gain * LgV2_B.QTMIn[4];

    /* Gain: '<S199>/mm2m z' */
    LgV2_B.mm2mz = LgV2_P.mm2mz_Gain * LgV2_B.QTMIn5;

    /* Derivative Block: '<S199>/Derivative' */
    {
      real_T t = LgV2_M->Timing.t[0];
      real_T timeStampA = LgV2_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = LgV2_DWork.Derivative_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = LgV2_B.Derivative;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank = &LgV2_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        LgV2_B.Derivative[0] = (LgV2_B.mm2mx - *lastBank++) / deltaT;
        LgV2_B.Derivative[1] = (LgV2_B.mm2my - *lastBank++) / deltaT;
        LgV2_B.Derivative[2] = (LgV2_B.mm2mz - *lastBank++) / deltaT;
        LgV2_B.Derivative[3] = (LgV2_B.d2rroll - *lastBank++) / deltaT;
        LgV2_B.Derivative[4] = (LgV2_B.d2rpitch - *lastBank++) / deltaT;
        LgV2_B.Derivative[5] = (LgV2_B.d2ryaw - *lastBank++) / deltaT;
      }
    }

    /* Product: '<S199>/Product' */
    for (i = 0; i < 6; i++) {
      LgV2_B.Product[i] = 0.0;
      for (tmp_6 = 0; tmp_6 < 6; tmp_6++) {
        LgV2_B.Product[i] = LgV2_B.MatrixConcatenate2[6 * tmp_6 + i] *
          LgV2_B.Derivative[tmp_6] + LgV2_B.Product[i];
      }
    }

    /* MultiPortSwitch: '<S4>/Nu Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)LgV2_P.ControllerInputSelector_Value == 0) {
      LgV2_B.NuSwitch[0] = LgV2_B.Product[0];
      LgV2_B.NuSwitch[1] = LgV2_B.Product[1];
      LgV2_B.NuSwitch[2] = LgV2_B.Product[5];
    } else {
      LgV2_B.NuSwitch[0] = LgV2_B.nu_surge_hil;
      LgV2_B.NuSwitch[1] = LgV2_B.nu_sway_hil;
      LgV2_B.NuSwitch[2] = LgV2_B.nu_yaw_hil;
    }

    /* Gain: '<S4>/nu_surge' */
    LgV2_B.nu_surge = LgV2_P.nu_surge_Gain * LgV2_B.NuSwitch[0];

    /* Gain: '<S4>/nu_sway' */
    LgV2_B.nu_sway = LgV2_P.nu_sway_Gain * LgV2_B.NuSwitch[1];

    /* Gain: '<S4>/nu_yaw' */
    LgV2_B.nu_yaw = LgV2_P.nu_yaw_Gain * LgV2_B.NuSwitch[2];
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Gain: '<S113>/eta_d DP N' incorporates:
       *  Constant: '<S196>/x_d'
       */
      LgV2_B.eta_dDPN = LgV2_P.eta_dDPN_Gain * LgV2_P.x_d_Value;

      /* Gain: '<S113>/eta_d DP E' incorporates:
       *  Constant: '<S196>/y_d'
       */
      LgV2_B.eta_dDPE = LgV2_P.eta_dDPE_Gain * LgV2_P.y_d_Value;

      /* Gain: '<S198>/Gain1' incorporates:
       *  Constant: '<S196>/psi_d'
       */
      LgV2_B.Gain1 = LgV2_P.Gain1_Gain * LgV2_P.psi_d_Value;

      /* Gain: '<S113>/eta_d DP Psi' */
      LgV2_B.eta_dDPPsi = LgV2_P.eta_dDPPsi_Gain * LgV2_B.Gain1;

      /* Constant: '<S95>/q_x_0' */
      LgV2_B.q_x_0 = LgV2_P.q_x_0_Value;

      /* Constant: '<S95>/q_y_0' */
      LgV2_B.q_y_0 = LgV2_P.q_y_0_Value;
    }

    /* Integrator Block: '<S52>/Integrator'
     */
    if (rtmIsMajorTimeStep(LgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &LgV2_PrevZCSigState.Integrator_Reset_ZCE,
                         LgV2_P.Resetq_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || LgV2_P.Resetq_Value != 0.0 ||
          LgV2_DWork.Integrator_IWORK.IcNeedsLoading) {
        LgV2_X.Integrator_CSTATE[0] = LgV2_B.q_x_0;
        LgV2_X.Integrator_CSTATE[1] = LgV2_B.q_y_0;
      }

      LgV2_DWork.Integrator_IWORK.IcNeedsLoading = 0;
    }

    LgV2_B.Integrator[0] = LgV2_X.Integrator_CSTATE[0];
    LgV2_B.Integrator[1] = LgV2_X.Integrator_CSTATE[1];

    /* SignalConversion: '<S125>/ConcatBufferAtVector ConcatenateIn1' */
    LgV2_B.VectorConcatenate[0] = LgV2_B.Integrator[0];
    LgV2_B.VectorConcatenate[1] = LgV2_B.Integrator[1];
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Sum: '<S187>/x_2 - x_1' incorporates:
       *  Constant: '<S197>/x_1'
       *  Constant: '<S197>/x_2'
       */
      LgV2_B.x_2x_1 = LgV2_P.x_2_Value - LgV2_P.x_1_Value;

      /* Sum: '<S187>/y_2 - y_1' incorporates:
       *  Constant: '<S197>/y_1'
       *  Constant: '<S197>/y_2'
       */
      LgV2_B.y_2y_1 = LgV2_P.y_2_Value - LgV2_P.y_1_Value;

      /* SignalConversion: '<S188>/TmpHiddenBufferAtProductInport2' */
      LgV2_B.TmpHiddenBufferAtProductInport2[0] = LgV2_B.x_2x_1;
      LgV2_B.TmpHiddenBufferAtProductInport2[1] = LgV2_B.y_2y_1;

      /* Product: '<S182>/Product' incorporates:
       *  Constant: '<S117>/Path Selector'
       */
      LgV2_B.Product_g[0] = LgV2_B.TmpHiddenBufferAtProductInport2[0] *
        LgV2_P.PathSelector_Value;
      LgV2_B.Product_g[1] = LgV2_B.TmpHiddenBufferAtProductInport2[1] *
        LgV2_P.PathSelector_Value;

      /* Constant: '<S52>/s_0' */
      LgV2_B.s_0 = LgV2_P.s_0_Value;
    }

    /* Integrator Block: '<S52>/Integrator1'
     */
    if (rtmIsMajorTimeStep(LgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &LgV2_PrevZCSigState.Integrator1_Reset_ZCE,
                         LgV2_P.Resets_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || LgV2_P.Resets_Value != 0.0 ||
          LgV2_DWork.Integrator1_IWORK.IcNeedsLoading) {
        LgV2_X.Integrator1_CSTATE = LgV2_B.s_0;
      }

      LgV2_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
    }

    LgV2_B.Integrator1 = LgV2_X.Integrator1_CSTATE;

    /* Product: '<S176>/Product2' incorporates:
     *  Constant: '<S197>/k'
     */
    LgV2_B.Product2 = LgV2_B.Integrator1 * LgV2_P.k_Value;

    /* Trigonometry: '<S176>/sin(s)' */
    LgV2_B.sins = sin(LgV2_B.Product2);

    /* Product: '<S176>/Product' incorporates:
     *  Constant: '<S197>/k'
     *  Constant: '<S197>/r_x'
     */
    LgV2_B.Product_m = LgV2_P.r_x_Value * LgV2_B.sins * LgV2_P.k_Value;

    /* Gain: '<S176>/Gain' */
    LgV2_B.Gain = LgV2_P.Gain_Gain * LgV2_B.Product_m;

    /* Trigonometry: '<S176>/cos(s)' */
    LgV2_B.coss = cos(LgV2_B.Product2);

    /* Product: '<S176>/Product1' incorporates:
     *  Constant: '<S197>/k'
     *  Constant: '<S197>/r_y'
     */
    LgV2_B.Product1 = LgV2_P.r_y_Value * LgV2_B.coss * LgV2_P.k_Value;

    /* SignalConversion: '<S179>/TmpHiddenBufferAtProductInport2' */
    LgV2_B.TmpHiddenBufferAtProductInpor_d[0] = LgV2_B.Gain;
    LgV2_B.TmpHiddenBufferAtProductInpor_d[1] = LgV2_B.Product1;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Sum: '<S182>/Subtract' incorporates:
       *  Constant: '<S117>/Path Selector'
       *  Constant: '<S182>/Constant'
       */
      LgV2_B.Subtract = LgV2_P.Constant_Value - LgV2_P.PathSelector_Value;
    }

    /* Product: '<S182>/Product1' */
    LgV2_B.Product1_c[0] = LgV2_B.TmpHiddenBufferAtProductInpor_d[0] *
      LgV2_B.Subtract;

    /* Sum: '<S182>/Add' */
    LgV2_B.Add[0] = LgV2_B.Product_g[0] + LgV2_B.Product1_c[0];

    /* Product: '<S182>/Product1' */
    LgV2_B.Product1_c[1] = LgV2_B.TmpHiddenBufferAtProductInpor_d[1] *
      LgV2_B.Subtract;

    /* Sum: '<S182>/Add' */
    LgV2_B.Add[1] = LgV2_B.Product_g[1] + LgV2_B.Product1_c[1];

    /* Trigonometry: '<S119>/Trigonometric Function' */
    LgV2_B.TrigonometricFunction = rt_atan2_snf(LgV2_B.Add[1], LgV2_B.Add[0]);

    /* Gain: '<S124>/Gain' */
    LgV2_B.Gain_b = LgV2_P.Gain_Gain_p * LgV2_B.TrigonometricFunction;

    /* Saturate: '<S122>/Saturation' */
    tmp = LgV2_B.Gain_b;
    LgV2_B.Saturation = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat,
      LgV2_P.Saturation_UpperSat);

    /* Signum: '<S122>/Sign' */
    LgV2_B.Sign = rt_SIGNd_snf(LgV2_B.Saturation);

    /* Gain: '<S122>/Gain' */
    LgV2_B.Gain_bx = LgV2_P.Gain_Gain_m * LgV2_B.Sign;

    /* Sum: '<S122>/Sum1' */
    LgV2_B.Sum1 = LgV2_B.Saturation + LgV2_B.Gain_bx;

    /* Math: '<S122>/Math Function' incorporates:
     *  Constant: '<S122>/Constant'
     */
    LgV2_B.MathFunction = rt_rem_snf(LgV2_B.Sum1, LgV2_P.Constant_Value_h);

    /* Sum: '<S122>/Sum' */
    LgV2_B.Sum = LgV2_B.MathFunction - LgV2_B.Gain_bx;

    /* Gain: '<S123>/Gain1' */
    LgV2_B.Gain1_f = LgV2_P.Gain1_Gain_g * LgV2_B.Sum;

    /* Gain: '<S157>/Gain' */
    LgV2_B.Gain_n = LgV2_P.Gain_Gain_n * LgV2_B.Gain1_f;

    /* Saturate: '<S153>/Saturation' */
    tmp = LgV2_B.Gain_n;
    LgV2_B.Saturation_h = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_i,
      LgV2_P.Saturation_UpperSat_b);

    /* Signum: '<S153>/Sign' */
    LgV2_B.Sign_c = rt_SIGNd_snf(LgV2_B.Saturation_h);

    /* Gain: '<S153>/Gain' */
    LgV2_B.Gain_m = LgV2_P.Gain_Gain_g * LgV2_B.Sign_c;

    /* Sum: '<S153>/Sum1' */
    LgV2_B.Sum1_c = LgV2_B.Saturation_h + LgV2_B.Gain_m;

    /* Math: '<S153>/Math Function' incorporates:
     *  Constant: '<S153>/Constant'
     */
    LgV2_B.MathFunction_o = rt_rem_snf(LgV2_B.Sum1_c, LgV2_P.Constant_Value_p);

    /* Sum: '<S153>/Sum' */
    LgV2_B.Sum_g = LgV2_B.MathFunction_o - LgV2_B.Gain_m;

    /* Gain: '<S156>/Gain1' */
    LgV2_B.Gain1_c = LgV2_P.Gain1_Gain_o * LgV2_B.Sum_g;

    /* Outputs for atomic SubSystem: '<S130>/R_2' */

    /* Trigonometry: '<S162>/R11' */
    LgV2_B.R11_cj = cos(LgV2_B.Gain1_f);

    /* Trigonometry: '<S162>/R21' */
    LgV2_B.R21_o = sin(LgV2_B.Gain1_f);

    /* Gain: '<S162>/R12' */
    LgV2_B.R12_k = LgV2_P.R12_Gain * LgV2_B.R21_o;

    /* Gain: '<S162>/R22' */
    LgV2_B.R22_l = LgV2_P.R22_Gain * LgV2_B.R11_cj;

    /* Reshape: '<S162>/R_2(psi_d)' */
    LgV2_B.R_2psi_d[0] = LgV2_B.R11_cj;
    LgV2_B.R_2psi_d[1] = LgV2_B.R21_o;
    LgV2_B.R_2psi_d[2] = LgV2_B.R12_k;
    LgV2_B.R_2psi_d[3] = LgV2_B.R22_l;

    /* end of Outputs for SubSystem: '<S130>/R_2' */

    /* Math: '<S163>/Math Function' */
    LgV2_B.MathFunction_b[0] = LgV2_B.R_2psi_d[0];
    LgV2_B.MathFunction_b[1] = LgV2_B.R_2psi_d[2];
    LgV2_B.MathFunction_b[2] = LgV2_B.R_2psi_d[1];
    LgV2_B.MathFunction_b[3] = LgV2_B.R_2psi_d[3];
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Sum: '<S186>/x_2 - x_1' incorporates:
       *  Constant: '<S197>/x_1'
       *  Constant: '<S197>/x_2'
       */
      LgV2_B.x_2x_1_m = LgV2_P.x_2_Value - LgV2_P.x_1_Value;
    }

    /* Product: '<S186>/(x_2 - x_1) * s' */
    LgV2_B.x_2x_1s = LgV2_B.x_2x_1_m * LgV2_B.Integrator1;

    /* Sum: '<S186>/(x_2 - x_1) * s + x_1' incorporates:
     *  Constant: '<S197>/x_1'
     */
    LgV2_B.x_2x_1sx_1 = LgV2_B.x_2x_1s + LgV2_P.x_1_Value;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Sum: '<S186>/y_2 - y_1' incorporates:
       *  Constant: '<S197>/y_1'
       *  Constant: '<S197>/y_2'
       */
      LgV2_B.y_2y_1_l = LgV2_P.y_2_Value - LgV2_P.y_1_Value;
    }

    /* Product: '<S186>/(y_2 - y_1) * s' */
    LgV2_B.y_2y_1s = LgV2_B.y_2y_1_l * LgV2_B.Integrator1;

    /* Sum: '<S186>/(y_2 - y_1) * s + y_1' incorporates:
     *  Constant: '<S197>/y_1'
     */
    LgV2_B.y_2y_1sy_1 = LgV2_B.y_2y_1s + LgV2_P.y_1_Value;

    /* Product: '<S181>/p_d1 *a' incorporates:
     *  Constant: '<S117>/Path Selector'
     */
    LgV2_B.p_d1a[0] = LgV2_B.x_2x_1sx_1 * LgV2_P.PathSelector_Value;
    LgV2_B.p_d1a[1] = LgV2_B.y_2y_1sy_1 * LgV2_P.PathSelector_Value;

    /* Product: '<S175>/Product2' incorporates:
     *  Constant: '<S197>/k'
     */
    LgV2_B.Product2_c = LgV2_B.Integrator1 * LgV2_P.k_Value;

    /* Trigonometry: '<S175>/cos(s)' */
    LgV2_B.coss_d = cos(LgV2_B.Product2_c);

    /* Product: '<S175>/Product' incorporates:
     *  Constant: '<S197>/r_x'
     */
    LgV2_B.Product_k = LgV2_P.r_x_Value * LgV2_B.coss_d;

    /* Sum: '<S175>/Add' incorporates:
     *  Constant: '<S197>/origin_x'
     */
    LgV2_B.Add_m = LgV2_B.Product_k + LgV2_P.origin_x_Value;

    /* Trigonometry: '<S175>/sin(s)' */
    LgV2_B.sins_i = sin(LgV2_B.Product2_c);

    /* Product: '<S175>/Product1' incorporates:
     *  Constant: '<S197>/r_y'
     */
    LgV2_B.Product1_n = LgV2_P.r_y_Value * LgV2_B.sins_i;

    /* Sum: '<S175>/Add1' incorporates:
     *  Constant: '<S197>/origo_y'
     */
    LgV2_B.Add1 = LgV2_B.Product1_n + LgV2_P.origo_y_Value;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Sum: '<S181>/1 - a' incorporates:
       *  Constant: '<S117>/Path Selector'
       *  Constant: '<S181>/Constant'
       */
      LgV2_B.a = LgV2_P.Constant_Value_o - LgV2_P.PathSelector_Value;
    }

    /* Product: '<S181>/p_d2 * (1- a )' */
    LgV2_B.p_d21a[0] = LgV2_B.Add_m * LgV2_B.a;
    LgV2_B.p_d21a[1] = LgV2_B.Add1 * LgV2_B.a;

    /* Sum: '<S181>/Add' */
    LgV2_B.Add_e[0] = LgV2_B.p_d1a[0] + LgV2_B.p_d21a[0];
    LgV2_B.Add_e[1] = LgV2_B.p_d1a[1] + LgV2_B.p_d21a[1];

    /* RelationalOperator: '<S190>/LowerRelop1' incorporates:
     *  Constant: '<S174>/x_dmax'
     */
    LgV2_B.LowerRelop1 = (LgV2_B.Add_e[0] > LgV2_P.x_dmax_Value);

    /* RelationalOperator: '<S190>/UpperRelop' incorporates:
     *  Constant: '<S174>/x_dmin'
     */
    LgV2_B.UpperRelop = (LgV2_B.Add_e[0] < LgV2_P.x_dmin_Value);

    /* Switch: '<S190>/Switch' incorporates:
     *  Constant: '<S174>/x_dmin'
     */
    if (LgV2_B.UpperRelop) {
      LgV2_B.Switch = LgV2_P.x_dmin_Value;
    } else {
      LgV2_B.Switch = LgV2_B.Add_e[0];
    }

    /* Switch: '<S190>/Switch2' incorporates:
     *  Constant: '<S174>/x_dmax'
     */
    if (LgV2_B.LowerRelop1) {
      LgV2_B.Switch2 = LgV2_P.x_dmax_Value;
    } else {
      LgV2_B.Switch2 = LgV2_B.Switch;
    }

    /* RelationalOperator: '<S191>/LowerRelop1' incorporates:
     *  Constant: '<S174>/y_dmax'
     */
    LgV2_B.LowerRelop1_k = (LgV2_B.Add_e[1] > LgV2_P.y_dmax_Value);

    /* RelationalOperator: '<S191>/UpperRelop' incorporates:
     *  Constant: '<S174>/y_dmin'
     */
    LgV2_B.UpperRelop_e = (LgV2_B.Add_e[1] < LgV2_P.y_dmin_Value);

    /* Switch: '<S191>/Switch' incorporates:
     *  Constant: '<S174>/y_dmin'
     */
    if (LgV2_B.UpperRelop_e) {
      LgV2_B.Switch_m = LgV2_P.y_dmin_Value;
    } else {
      LgV2_B.Switch_m = LgV2_B.Add_e[1];
    }

    /* Switch: '<S191>/Switch2' incorporates:
     *  Constant: '<S174>/y_dmax'
     */
    if (LgV2_B.LowerRelop1_k) {
      LgV2_B.Switch2_h = LgV2_P.y_dmax_Value;
    } else {
      LgV2_B.Switch2_h = LgV2_B.Switch_m;
    }

    /* Sum: '<S130>/q - p_d' */
    LgV2_B.qp_d[0] = LgV2_B.Integrator[0] - LgV2_B.Switch2;
    LgV2_B.qp_d[1] = LgV2_B.Integrator[1] - LgV2_B.Switch2_h;

    /* Product: '<S130>/epsilon' */
    LgV2_B.epsilon[0] = 0.0;
    LgV2_B.epsilon[0] = LgV2_B.MathFunction_b[0] * LgV2_B.qp_d[0] +
      LgV2_B.epsilon[0];
    LgV2_B.epsilon[0] = LgV2_B.MathFunction_b[2] * LgV2_B.qp_d[1] +
      LgV2_B.epsilon[0];
    LgV2_B.epsilon[1] = 0.0;
    LgV2_B.epsilon[1] = LgV2_B.MathFunction_b[1] * LgV2_B.qp_d[0] +
      LgV2_B.epsilon[1];
    LgV2_B.epsilon[1] = LgV2_B.MathFunction_b[3] * LgV2_B.qp_d[1] +
      LgV2_B.epsilon[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S130>/Multiport Selector' */
    {
      const byte_T *u = (byte_T *)LgV2_B.epsilon;/* input port */
      const int32_T *index = (const int32_T *)&LgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&LgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&LgV2_B.MultiportSelector;
      int_T ctr;

      /* Loop over each row of current output port index */
      for (ctr = 0; ctr < numRowsThisOutput; ctr++) {
        int_T inputRowIdx = *index++;
        int_T inputRowOffsetBytes;
        int_T outputRowOffsetBytes;
        int_T sampleIdx;
        inputRowOffsetBytes = inputRowIdx * sizeof(real_T);
        outputRowOffsetBytes = ctr * sizeof(real_T);

        /* Copy one sample at a time from each input column */
        for (sampleIdx = 0; sampleIdx < 1; sampleIdx++) {
          memcpy((y + (sampleIdx * bytesPerOutCol) + outputRowOffsetBytes),
                 (u + (sampleIdx * (2 * sizeof(real_T))) + inputRowOffsetBytes),
                 sizeof(real_T) );
        }
      }                                /* output row loop */
    }                                  /* end <S130>/Multiport Selector */

    /* Trigonometry: '<S147>/Trigonometric Function' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.TrigonometricFunction_f = rt_atan2_snf(LgV2_B.MultiportSelector,
      LgV2_P.Delta_Value);

    /* Gain: '<S159>/Gain' */
    LgV2_B.Gain_h = LgV2_P.Gain_Gain_pe * LgV2_B.TrigonometricFunction_f;

    /* Saturate: '<S154>/Saturation' */
    tmp = LgV2_B.Gain_h;
    LgV2_B.Saturation_i = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_p,
      LgV2_P.Saturation_UpperSat_k);

    /* Signum: '<S154>/Sign' */
    LgV2_B.Sign_i = rt_SIGNd_snf(LgV2_B.Saturation_i);

    /* Gain: '<S154>/Gain' */
    LgV2_B.Gain_g = LgV2_P.Gain_Gain_pg * LgV2_B.Sign_i;

    /* Sum: '<S154>/Sum1' */
    LgV2_B.Sum1_f = LgV2_B.Saturation_i + LgV2_B.Gain_g;

    /* Math: '<S154>/Math Function' incorporates:
     *  Constant: '<S154>/Constant'
     */
    LgV2_B.MathFunction_p = rt_rem_snf(LgV2_B.Sum1_f, LgV2_P.Constant_Value_od);

    /* Sum: '<S154>/Sum' */
    LgV2_B.Sum_p = LgV2_B.MathFunction_p - LgV2_B.Gain_g;

    /* Gain: '<S158>/Gain1' */
    LgV2_B.Gain1_h = LgV2_P.Gain1_Gain_m * LgV2_B.Sum_p;

    /* Sum: '<S147>/Subtract' */
    LgV2_B.Subtract_a = LgV2_B.Gain1_c - LgV2_B.Gain1_h;

    /* Gain: '<S161>/Gain' */
    LgV2_B.Gain_k = LgV2_P.Gain_Gain_l * LgV2_B.Subtract_a;

    /* Saturate: '<S155>/Saturation' */
    tmp = LgV2_B.Gain_k;
    LgV2_B.Saturation_c = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_iq,
      LgV2_P.Saturation_UpperSat_i);

    /* Signum: '<S155>/Sign' */
    LgV2_B.Sign_d = rt_SIGNd_snf(LgV2_B.Saturation_c);

    /* Gain: '<S155>/Gain' */
    LgV2_B.Gain_ki = LgV2_P.Gain_Gain_f * LgV2_B.Sign_d;

    /* Sum: '<S155>/Sum1' */
    LgV2_B.Sum1_a = LgV2_B.Saturation_c + LgV2_B.Gain_ki;

    /* Math: '<S155>/Math Function' incorporates:
     *  Constant: '<S155>/Constant'
     */
    LgV2_B.MathFunction_bn = rt_rem_snf(LgV2_B.Sum1_a, LgV2_P.Constant_Value_e);

    /* Sum: '<S155>/Sum' */
    LgV2_B.Sum_o = LgV2_B.MathFunction_bn - LgV2_B.Gain_ki;

    /* Gain: '<S160>/Gain1' */
    LgV2_B.Gain1_o = LgV2_P.Gain1_Gain_k * LgV2_B.Sum_o;

    /* SignalConversion: '<S125>/ConcatBufferAtVector ConcatenateIn2' */
    LgV2_B.VectorConcatenate[2] = LgV2_B.Gain1_o;

    /* Gain: '<S2>/q_x' */
    LgV2_B.q_x = LgV2_P.q_x_Gain * LgV2_B.VectorConcatenate[0];

    /* Gain: '<S2>/q_y' */
    LgV2_B.q_y = LgV2_P.q_y_Gain * LgV2_B.VectorConcatenate[1];

    /* Gain: '<S2>/psi_los' */
    LgV2_B.psi_los = LgV2_P.psi_los_Gain * LgV2_B.VectorConcatenate[2];

    /* Gain: '<S2>/path x_d' */
    LgV2_B.pathx_d = LgV2_P.pathx_d_Gain * LgV2_B.Switch2;

    /* Gain: '<S2>/path y_d' */
    LgV2_B.pathy_d = LgV2_P.pathy_d_Gain * LgV2_B.Switch2_h;

    /* Gain: '<S2>/path psi_d' */
    LgV2_B.pathpsi_d = LgV2_P.pathpsi_d_Gain * LgV2_B.Gain1_f;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S189>/Math Function' */
      LgV2_B.MathFunction_i[0] = LgV2_B.TmpHiddenBufferAtProductInport2[0];
      LgV2_B.MathFunction_i[1] = LgV2_B.TmpHiddenBufferAtProductInport2[1];

      /* Product: '<S188>/Product' */
      tmp = LgV2_B.MathFunction_i[0] * LgV2_B.TmpHiddenBufferAtProductInport2[0];
      tmp += LgV2_B.MathFunction_i[1] * LgV2_B.TmpHiddenBufferAtProductInport2[1];
      LgV2_B.Product_p = tmp;

      /* Math: '<S188>/sqrt' */
      tmp = LgV2_B.Product_p;
      if (tmp < 0.0) {
        LgV2_B.sqrt_p = -sqrt(-tmp);
      } else {
        LgV2_B.sqrt_p = sqrt(tmp);
      }

      /* Product: '<S185>/Product' incorporates:
       *  Constant: '<S117>/Path Selector'
       */
      LgV2_B.Product_ka = LgV2_B.sqrt_p * LgV2_P.PathSelector_Value;
    }

    /* Math: '<S180>/Math Function' */
    LgV2_B.MathFunction_h[0] = LgV2_B.TmpHiddenBufferAtProductInpor_d[0];
    LgV2_B.MathFunction_h[1] = LgV2_B.TmpHiddenBufferAtProductInpor_d[1];

    /* Product: '<S179>/Product' */
    tmp = LgV2_B.MathFunction_h[0] * LgV2_B.TmpHiddenBufferAtProductInpor_d[0];
    tmp += LgV2_B.MathFunction_h[1] * LgV2_B.TmpHiddenBufferAtProductInpor_d[1];
    LgV2_B.Product_b = tmp;

    /* Math: '<S179>/sqrt' */
    tmp = LgV2_B.Product_b;
    if (tmp < 0.0) {
      LgV2_B.sqrt_h = -sqrt(-tmp);
    } else {
      LgV2_B.sqrt_h = sqrt(tmp);
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Sum: '<S185>/Subtract' incorporates:
       *  Constant: '<S117>/Path Selector'
       *  Constant: '<S185>/Constant'
       */
      LgV2_B.Subtract_d = LgV2_P.Constant_Value_oc - LgV2_P.PathSelector_Value;
    }

    /* Product: '<S185>/Product1' */
    LgV2_B.Product1_j = LgV2_B.sqrt_h * LgV2_B.Subtract_d;

    /* Sum: '<S185>/Add' */
    LgV2_B.Add_n = LgV2_B.Product_ka + LgV2_B.Product1_j;

    /* Product: '<S192>/Divide' incorporates:
     *  Constant: '<S197>/u_d'
     */
    LgV2_B.Divide = LgV2_P.u_d_Value / LgV2_B.Add_n;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Gain: '<S8>/ScalingLY' incorporates:
       *  Constant: '<S8>/AS_LY'
       */
      LgV2_B.ypositionofleftanalogstick11 = LgV2_P.ScalingLY_Gain *
        LgV2_P.AS_LY_Value;

      /* Gain: '<S9>/PS3 u_1' */
      LgV2_B.u_1 = LgV2_P.PS3u_1_Gain * LgV2_B.ypositionofleftanalogstick11;

      /* Gain: '<S8>/ScalingLX' incorporates:
       *  Constant: '<S8>/AS_LX'
       */
      LgV2_B.xpositionofleftanalogstick11 = LgV2_P.ScalingLX_Gain *
        LgV2_P.AS_LX_Value;

      /* Gain: '<S9>/PS3 u_2' */
      LgV2_B.u_2 = LgV2_P.PS3u_2_Gain * LgV2_B.xpositionofleftanalogstick11;

      /* Gain: '<S8>/ScalingRY' incorporates:
       *  Constant: '<S8>/AS_RY'
       */
      LgV2_B.ypositionofrightanalogstick11 = LgV2_P.ScalingRY_Gain *
        LgV2_P.AS_RY_Value;

      /* Gain: '<S9>/PS3 u_3' */
      LgV2_B.u_3 = LgV2_P.PS3u_3_Gain * LgV2_B.ypositionofrightanalogstick11;

      /* Gain: '<S8>/Scaling_RX' incorporates:
       *  Constant: '<S8>/AS_RX'
       */
      LgV2_B.xpositionofrightanalogstick11 = LgV2_P.Scaling_RX_Gain *
        LgV2_P.AS_RX_Value;

      /* Gain: '<S9>/PS3 u_4' */
      LgV2_B.u_4 = LgV2_P.PS3u_4_Gain * LgV2_B.xpositionofrightanalogstick11;

      /* Sum: '<S9>/Add' incorporates:
       *  Constant: '<S8>/L2'
       *  Constant: '<S8>/R2'
       */
      LgV2_B.BowThrusterdirection = LgV2_P.L2_Value + LgV2_P.R2_Value;

      /* Gain: '<S9>/PS3 u_5' */
      LgV2_B.u_5 = LgV2_P.PS3u_5_Gain * LgV2_B.BowThrusterdirection;

      /* Gain: '<S37>/-l_x1' incorporates:
       *  Constant: '<S37>/l_x1'
       */
      LgV2_B.l_x1 = LgV2_P.l_x1_Gain * LgV2_P.l_x1_Value;

      /* Gain: '<S37>/-l_y2' incorporates:
       *  Constant: '<S37>/l_y2'
       */
      LgV2_B.l_y2 = LgV2_P.l_y2_Gain * LgV2_P.l_y2_Value;

      /* Gain: '<S37>/-l_x2' incorporates:
       *  Constant: '<S37>/l_x2'
       */
      LgV2_B.l_x2 = LgV2_P.l_x2_Gain * LgV2_P.l_x2_Value;

      /* Reshape: '<S37>/3x5' incorporates:
       *  Constant: '<S37>/T_e11'
       *  Constant: '<S37>/T_e12'
       *  Constant: '<S37>/T_e13'
       *  Constant: '<S37>/T_e14'
       *  Constant: '<S37>/T_e15'
       *  Constant: '<S37>/T_e21'
       *  Constant: '<S37>/T_e22'
       *  Constant: '<S37>/T_e23'
       *  Constant: '<S37>/T_e24'
       *  Constant: '<S37>/T_e25'
       *  Constant: '<S37>/l_x3'
       *  Constant: '<S37>/l_y1'
       */
      LgV2_B.x5[0] = LgV2_P.T_e11_Value;
      LgV2_B.x5[1] = LgV2_P.T_e21_Value;
      LgV2_B.x5[2] = LgV2_P.l_y1_Value;
      LgV2_B.x5[3] = LgV2_P.T_e12_Value;
      LgV2_B.x5[4] = LgV2_P.T_e22_Value;
      LgV2_B.x5[5] = LgV2_B.l_x1;
      LgV2_B.x5[6] = LgV2_P.T_e13_Value;
      LgV2_B.x5[7] = LgV2_P.T_e23_Value;
      LgV2_B.x5[8] = LgV2_B.l_y2;
      LgV2_B.x5[9] = LgV2_P.T_e14_Value;
      LgV2_B.x5[10] = LgV2_P.T_e24_Value;
      LgV2_B.x5[11] = LgV2_B.l_x2;
      LgV2_B.x5[12] = LgV2_P.T_e15_Value;
      LgV2_B.x5[13] = LgV2_P.T_e25_Value;
      LgV2_B.x5[14] = LgV2_P.l_x3_Value;

      /* S-Function (sdsppinv): '<S16>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&LgV2_DWork.Pseudoinverse_X[0]), (void *)(&LgV2_B.x5[0]),
             15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&LgV2_DWork.Pseudoinverse_X[0], 3, 5,
                      &LgV2_DWork.Pseudoinverse_S[0],
                      &LgV2_DWork.Inverse_DWORK3[0],
                      &LgV2_DWork.Pseudoinverse_WORK[0],
                      &LgV2_DWork.Pseudoinverse_U[0],
                      &LgV2_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&LgV2_DWork.Pseudoinverse_S[0],
          &LgV2_DWork.Pseudoinverse_U[0], &LgV2_DWork.Pseudoinverse_V[0],
          &LgV2_B.Pseudoinverse[0], (const int32_T)3, (const int32_T)5);
      }
    }

    /* Fcn: '<S10>/yaw angle' */
    LgV2_B.psi = LgV2_B.eta_yaw;

    /* Saturate: '<S14>/Saturation' */
    tmp = LgV2_B.psi;
    LgV2_B.Saturation_ha = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_j,
      LgV2_P.Saturation_UpperSat_j);

    /* Signum: '<S14>/Sign' */
    LgV2_B.Sign_a = rt_SIGNd_snf(LgV2_B.Saturation_ha);

    /* Gain: '<S14>/Gain' */
    LgV2_B.Gain_j = LgV2_P.Gain_Gain_h * LgV2_B.Sign_a;

    /* Sum: '<S14>/Sum1' */
    LgV2_B.Sum1_i = LgV2_B.Saturation_ha + LgV2_B.Gain_j;

    /* Math: '<S14>/Math Function' incorporates:
     *  Constant: '<S14>/Constant'
     */
    LgV2_B.MathFunction_ij = rt_rem_snf(LgV2_B.Sum1_i, LgV2_P.Constant_Value_g);

    /* Sum: '<S14>/Sum' */
    LgV2_B.Sum_b = LgV2_B.MathFunction_ij - LgV2_B.Gain_j;

    /* Sum: '<S10>/Sum2' */
    LgV2_B.regulationerror[0] = LgV2_B.eta_dDPN - LgV2_B.eta_surge;
    LgV2_B.regulationerror[1] = LgV2_B.eta_dDPE - LgV2_B.eta_sway;
    LgV2_B.regulationerror[2] = LgV2_B.eta_dDPPsi - LgV2_B.eta_yaw;

    /* Saturate: '<S13>/Saturation' */
    tmp = LgV2_B.regulationerror[2];
    LgV2_B.Saturation_m = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_m,
      LgV2_P.Saturation_UpperSat_g);

    /* Signum: '<S13>/Sign' */
    LgV2_B.Sign_j = rt_SIGNd_snf(LgV2_B.Saturation_m);

    /* Gain: '<S13>/Gain' */
    LgV2_B.Gain_a = LgV2_P.Gain_Gain_fh * LgV2_B.Sign_j;

    /* Sum: '<S13>/Sum1' */
    LgV2_B.Sum1_p = LgV2_B.Saturation_m + LgV2_B.Gain_a;

    /* Math: '<S13>/Math Function' incorporates:
     *  Constant: '<S13>/Constant'
     */
    LgV2_B.MathFunction_d = rt_rem_snf(LgV2_B.Sum1_p, LgV2_P.Constant_Value_gt);

    /* Sum: '<S13>/Sum' */
    LgV2_B.Sum_j = LgV2_B.MathFunction_d - LgV2_B.Gain_a;

    /* Fcn: '<S12>/Row1' */
    LgV2_B.Row1 = cos(LgV2_B.Sum_b) * LgV2_B.regulationerror[0] + sin
      (LgV2_B.Sum_b) * LgV2_B.regulationerror[1];

    /* Fcn: '<S12>/Row2' */
    LgV2_B.Row2 = (-sin(LgV2_B.Sum_b)) * LgV2_B.regulationerror[0] + cos
      (LgV2_B.Sum_b) * LgV2_B.regulationerror[1];

    /* Fcn: '<S12>/Row3' */
    LgV2_B.Row3 = LgV2_B.Sum_j;

    /* SignalConversion: '<S10>/TmpHiddenBufferAtKpInport1' */
    LgV2_B.TmpHiddenBufferAtKpInport1[0] = LgV2_B.Row1;
    LgV2_B.TmpHiddenBufferAtKpInport1[1] = LgV2_B.Row2;
    LgV2_B.TmpHiddenBufferAtKpInport1[2] = LgV2_B.Row3;

    /* Gain: '<S10>/Kp' */
    for (i = 0; i < 3; i++) {
      LgV2_B.Kp[i] = 0.0;
      LgV2_B.Kp[i] = LgV2_P.Kp_Gain[i] * LgV2_B.TmpHiddenBufferAtKpInport1[0] +
        LgV2_B.Kp[i];
      LgV2_B.Kp[i] = LgV2_P.Kp_Gain[i + 3] * LgV2_B.TmpHiddenBufferAtKpInport1[1]
        + LgV2_B.Kp[i];
      LgV2_B.Kp[i] = LgV2_P.Kp_Gain[i + 6] * LgV2_B.TmpHiddenBufferAtKpInport1[2]
        + LgV2_B.Kp[i];
    }

    /* Gain: '<S10>/K_p_surge_scale' */
    LgV2_B.K_p_surge_scale = LgV2_P.K_p_surge_scale_Gain * LgV2_B.Kp[0];

    /* Gain: '<S10>/K_p_sway_scale' */
    LgV2_B.K_p_sway_scale = LgV2_P.K_p_sway_scale_Gain * LgV2_B.Kp[1];

    /* Gain: '<S10>/K_p_yaw_scale' */
    LgV2_B.K_p_yaw_scale = LgV2_P.K_p_yaw_scale_Gain * LgV2_B.Kp[2];

    /* Integrator Block: '<S10>/Integrator'
     */
    if (rtmIsMajorTimeStep(LgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &LgV2_PrevZCSigState.Integrator_Reset_ZCE_f,
                         LgV2_P.Reset_DP_integrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || LgV2_P.Reset_DP_integrator_Value != 0.0) {
        LgV2_X.Integrator_CSTATE_k[0] = LgV2_P.Integrator_IC;
        LgV2_X.Integrator_CSTATE_k[1] = LgV2_P.Integrator_IC;
        LgV2_X.Integrator_CSTATE_k[2] = LgV2_P.Integrator_IC;
      }
    }

    LgV2_B.Integrator_g[0] = LgV2_X.Integrator_CSTATE_k[0];
    LgV2_B.Integrator_g[1] = LgV2_X.Integrator_CSTATE_k[1];
    LgV2_B.Integrator_g[2] = LgV2_X.Integrator_CSTATE_k[2];

    /* Gain: '<S10>/Ki' */
    for (i = 0; i < 3; i++) {
      LgV2_B.Ki[i] = 0.0;
      LgV2_B.Ki[i] = LgV2_P.Ki_Gain[i] * LgV2_B.Integrator_g[0] + LgV2_B.Ki[i];
      LgV2_B.Ki[i] = LgV2_P.Ki_Gain[i + 3] * LgV2_B.Integrator_g[1] +
        LgV2_B.Ki[i];
      LgV2_B.Ki[i] = LgV2_P.Ki_Gain[i + 6] * LgV2_B.Integrator_g[2] +
        LgV2_B.Ki[i];
    }

    /* Gain: '<S10>/K_i_surge_scale' */
    LgV2_B.K_i_surge_scale = LgV2_P.K_i_surge_scale_Gain * LgV2_B.Ki[0];

    /* Gain: '<S10>/K_i_sway_scale' */
    LgV2_B.K_i_sway_scale = LgV2_P.K_i_sway_scale_Gain * LgV2_B.Ki[1];

    /* Gain: '<S10>/K_i_yaw_scale' */
    LgV2_B.K_i_yaw_scale = LgV2_P.K_i_yaw_scale_Gain * LgV2_B.Ki[2];

    /* Sum: '<S10>/Sum3' */
    LgV2_B.Sum3[0] = LgV2_B.K_p_surge_scale + LgV2_B.K_i_surge_scale;
    LgV2_B.Sum3[1] = LgV2_B.K_p_sway_scale + LgV2_B.K_i_sway_scale;
    LgV2_B.Sum3[2] = LgV2_B.K_p_yaw_scale + LgV2_B.K_i_yaw_scale;

    /* SignalConversion: '<S10>/TmpHiddenBufferAtKdInport1' */
    LgV2_B.TmpHiddenBufferAtKdInport1[0] = LgV2_B.nu_surge;
    LgV2_B.TmpHiddenBufferAtKdInport1[1] = LgV2_B.nu_sway;
    LgV2_B.TmpHiddenBufferAtKdInport1[2] = LgV2_B.nu_yaw;

    /* Gain: '<S10>/Kd' */
    for (i = 0; i < 3; i++) {
      LgV2_B.Kd[i] = 0.0;
      LgV2_B.Kd[i] = LgV2_P.Kd_Gain[i] * LgV2_B.TmpHiddenBufferAtKdInport1[0] +
        LgV2_B.Kd[i];
      LgV2_B.Kd[i] = LgV2_P.Kd_Gain[i + 3] * LgV2_B.TmpHiddenBufferAtKdInport1[1]
        + LgV2_B.Kd[i];
      LgV2_B.Kd[i] = LgV2_P.Kd_Gain[i + 6] * LgV2_B.TmpHiddenBufferAtKdInport1[2]
        + LgV2_B.Kd[i];
    }

    /* Gain: '<S10>/K_d_surge_scale' */
    LgV2_B.K_d_surge_scale = LgV2_P.K_d_surge_scale_Gain * LgV2_B.Kd[0];

    /* Gain: '<S10>/K_d_sway_scale' */
    LgV2_B.K_d_sway_scale = LgV2_P.K_d_sway_scale_Gain * LgV2_B.Kd[1];

    /* Gain: '<S10>/K_d_yaw_scale' */
    LgV2_B.K_d_yaw_scale = LgV2_P.K_d_yaw_scale_Gain * LgV2_B.Kd[2];

    /* Sum: '<S10>/Sum1' */
    LgV2_B.Sum1_j[0] = LgV2_B.Sum3[0] - LgV2_B.K_d_surge_scale;
    LgV2_B.Sum1_j[1] = LgV2_B.Sum3[1] - LgV2_B.K_d_sway_scale;
    LgV2_B.Sum1_j[2] = LgV2_B.Sum3[2] - LgV2_B.K_d_yaw_scale;

    /* Product: '<S16>/Product' */
    for (i = 0; i < 5; i++) {
      LgV2_B.Product_o[i] = 0.0;
      LgV2_B.Product_o[i] = LgV2_B.Pseudoinverse[i] * LgV2_B.Sum1_j[0] +
        LgV2_B.Product_o[i];
      LgV2_B.Product_o[i] = LgV2_B.Pseudoinverse[i + 5] * LgV2_B.Sum1_j[1] +
        LgV2_B.Product_o[i];
      LgV2_B.Product_o[i] = LgV2_B.Pseudoinverse[i + 10] * LgV2_B.Sum1_j[2] +
        LgV2_B.Product_o[i];
    }

    /* DeadZone Block: '<S17>/Dead Zone'
     */
    if (LgV2_B.Product_o[0] >= LgV2_P.DeadZone_End) {
      LgV2_B.DeadZone = LgV2_B.Product_o[0] - LgV2_P.DeadZone_End;
    } else if (LgV2_B.Product_o[0] > LgV2_P.DeadZone_Start) {
      LgV2_B.DeadZone = 0.0;
    } else {
      LgV2_B.DeadZone = LgV2_B.Product_o[0] - LgV2_P.DeadZone_Start;
    }

    /* RelationalOperator: '<S22>/Compare' incorporates:
     *  Constant: '<S22>/Constant'
     */
    LgV2_B.Compare = (LgV2_B.DeadZone < LgV2_P.Constant_Value_c);

    /* RelationalOperator: '<S24>/Compare' */
    LgV2_B.Compare_e = (LgV2_B.DeadZone == 0.0);

    /* Gain: '<S17>/Gain' */
    LgV2_B.Gain_p = (uint16_T)(LgV2_P.Gain_Gain_gz * LgV2_B.Compare_e);

    /* RelationalOperator: '<S23>/Compare' incorporates:
     *  Constant: '<S23>/Constant'
     */
    LgV2_B.Compare_j = (LgV2_B.DeadZone > LgV2_P.Constant_Value_ek);

    /* Gain: '<S17>/Gain1' */
    LgV2_B.Gain1_a = (uint16_T)(LgV2_P.Gain1_Gain_a * LgV2_B.Compare_j);

    /* Sum: '<S17>/Sum' */
    LgV2_B.Sum_i = (uint16_T)(uint32_T)(((LgV2_B.Compare << 6) + LgV2_B.Gain_p)
      + LgV2_B.Gain1_a);

    /* Lookup Block: '<S17>/f_1 < 0'
     * About '<S17>/f_1 < 0 :'
     * Lookup Block: '<S17>/f_1 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_10), LgV2_P.f_10_YData, LgV2_B.Product_o[0],
                         LgV2_P.f_10_XData, 8U);

    /* Lookup Block: '<S17>/f_1 > 0'
     * About '<S17>/f_1 > 0 :'
     * Lookup Block: '<S17>/f_1 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_10_l), LgV2_P.f_10_YData_h,
                         LgV2_B.Product_o[0], LgV2_P.f_10_XData_j, 9U);

    /* MultiPortSwitch: '<S17>/Multiport Switch' incorporates:
     *  Constant: '<S17>/f_1 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_i >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch = LgV2_B.f_10;
      break;

     case 2:
      LgV2_B.MultiportSwitch = LgV2_P.f_10_Value;
      break;

     default:
      LgV2_B.MultiportSwitch = LgV2_B.f_10_l;
      break;
    }

    /* DeadZone Block: '<S18>/Dead Zone'
     */
    if (LgV2_B.Product_o[1] >= LgV2_P.DeadZone_End_e) {
      LgV2_B.DeadZone_j = LgV2_B.Product_o[1] - LgV2_P.DeadZone_End_e;
    } else if (LgV2_B.Product_o[1] > LgV2_P.DeadZone_Start_c) {
      LgV2_B.DeadZone_j = 0.0;
    } else {
      LgV2_B.DeadZone_j = LgV2_B.Product_o[1] - LgV2_P.DeadZone_Start_c;
    }

    /* RelationalOperator: '<S25>/Compare' incorporates:
     *  Constant: '<S25>/Constant'
     */
    LgV2_B.Compare_a = (LgV2_B.DeadZone_j < LgV2_P.Constant_Value_d);

    /* RelationalOperator: '<S26>/Compare' incorporates:
     *  Constant: '<S26>/Constant'
     */
    LgV2_B.Compare_n = (LgV2_B.DeadZone_j == LgV2_P.Constant_Value_m);

    /* Gain: '<S18>/Gain' */
    LgV2_B.Gain_nw = (uint16_T)(LgV2_P.Gain_Gain_o * LgV2_B.Compare_n);

    /* RelationalOperator: '<S27>/Compare' incorporates:
     *  Constant: '<S27>/Constant'
     */
    LgV2_B.Compare_m = (LgV2_B.DeadZone_j > LgV2_P.Constant_Value_go);

    /* Gain: '<S18>/Gain1' */
    LgV2_B.Gain1_hg = (uint16_T)(LgV2_P.Gain1_Gain_b * LgV2_B.Compare_m);

    /* Sum: '<S18>/Sum' */
    LgV2_B.Sum_a = (uint16_T)(uint32_T)(((LgV2_B.Compare_a << 6) +
      LgV2_B.Gain_nw) + LgV2_B.Gain1_hg);

    /* Lookup Block: '<S18>/f_2 < 0'
     * About '<S18>/f_2 < 0 :'
     * Lookup Block: '<S18>/f_2 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_20), LgV2_P.f_20_YData, LgV2_B.Product_o[1],
                         LgV2_P.f_20_XData, 10U);

    /* Lookup Block: '<S18>/f_2 > 0'
     * About '<S18>/f_2 > 0 :'
     * Lookup Block: '<S18>/f_2 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_20_l), LgV2_P.f_20_YData_g,
                         LgV2_B.Product_o[1], LgV2_P.f_20_XData_b, 9U);

    /* MultiPortSwitch: '<S18>/Multiport Switch' incorporates:
     *  Constant: '<S18>/f_2 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_a >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch_h = LgV2_B.f_20;
      break;

     case 2:
      LgV2_B.MultiportSwitch_h = LgV2_P.f_20_Value;
      break;

     default:
      LgV2_B.MultiportSwitch_h = LgV2_B.f_20_l;
      break;
    }

    /* DeadZone Block: '<S19>/Dead Zone'
     */
    if (LgV2_B.Product_o[2] >= LgV2_P.DeadZone_End_n) {
      LgV2_B.DeadZone_m = LgV2_B.Product_o[2] - LgV2_P.DeadZone_End_n;
    } else if (LgV2_B.Product_o[2] > LgV2_P.DeadZone_Start_n) {
      LgV2_B.DeadZone_m = 0.0;
    } else {
      LgV2_B.DeadZone_m = LgV2_B.Product_o[2] - LgV2_P.DeadZone_Start_n;
    }

    /* RelationalOperator: '<S28>/Compare' incorporates:
     *  Constant: '<S28>/Constant'
     */
    LgV2_B.Compare_p = (LgV2_B.DeadZone_m < LgV2_P.Constant_Value_oz);

    /* RelationalOperator: '<S30>/Compare' */
    LgV2_B.Compare_c = (LgV2_B.DeadZone_m == 0.0);

    /* Gain: '<S19>/Gain' */
    LgV2_B.Gain_br = (uint16_T)(LgV2_P.Gain_Gain_o1 * LgV2_B.Compare_c);

    /* RelationalOperator: '<S29>/Compare' incorporates:
     *  Constant: '<S29>/Constant'
     */
    LgV2_B.Compare_i = (LgV2_B.DeadZone_m > LgV2_P.Constant_Value_j);

    /* Gain: '<S19>/Gain1' */
    LgV2_B.Gain1_hu = (uint16_T)(LgV2_P.Gain1_Gain_h * LgV2_B.Compare_i);

    /* Sum: '<S19>/Sum' */
    LgV2_B.Sum_n5 = (uint16_T)(uint32_T)(((LgV2_B.Compare_p << 6) +
      LgV2_B.Gain_br) + LgV2_B.Gain1_hu);

    /* Lookup Block: '<S19>/f_3 < 0'
     * About '<S19>/f_3 < 0 :'
     * Lookup Block: '<S19>/f_3 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_30), LgV2_P.f_30_YData, LgV2_B.Product_o[2],
                         LgV2_P.f_30_XData, 7U);

    /* Lookup Block: '<S19>/f_3 > 0'
     * About '<S19>/f_3 > 0 :'
     * Lookup Block: '<S19>/f_3 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_30_o), LgV2_P.f_30_YData_b,
                         LgV2_B.Product_o[2], LgV2_P.f_30_XData_k, 10U);

    /* MultiPortSwitch: '<S19>/Multiport Switch' incorporates:
     *  Constant: '<S19>/f_3 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_n5 >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch_c = LgV2_B.f_30;
      break;

     case 2:
      LgV2_B.MultiportSwitch_c = LgV2_P.f_30_Value;
      break;

     default:
      LgV2_B.MultiportSwitch_c = LgV2_B.f_30_o;
      break;
    }

    /* DeadZone Block: '<S20>/Dead Zone'
     */
    if (LgV2_B.Product_o[3] >= LgV2_P.DeadZone_End_j) {
      LgV2_B.DeadZone_g = LgV2_B.Product_o[3] - LgV2_P.DeadZone_End_j;
    } else if (LgV2_B.Product_o[3] > LgV2_P.DeadZone_Start_h) {
      LgV2_B.DeadZone_g = 0.0;
    } else {
      LgV2_B.DeadZone_g = LgV2_B.Product_o[3] - LgV2_P.DeadZone_Start_h;
    }

    /* RelationalOperator: '<S31>/Compare' incorporates:
     *  Constant: '<S31>/Constant'
     */
    LgV2_B.Compare_o = (LgV2_B.DeadZone_g < LgV2_P.Constant_Value_a);

    /* RelationalOperator: '<S33>/Compare' */
    LgV2_B.Compare_ng = (LgV2_B.DeadZone_g == 0.0);

    /* Gain: '<S20>/Gain' */
    LgV2_B.Gain_c5 = (uint16_T)(LgV2_P.Gain_Gain_fc * LgV2_B.Compare_ng);

    /* RelationalOperator: '<S32>/Compare' incorporates:
     *  Constant: '<S32>/Constant'
     */
    LgV2_B.Compare_cx = (LgV2_B.DeadZone_g > LgV2_P.Constant_Value_b);

    /* Gain: '<S20>/Gain1' */
    LgV2_B.Gain1_mp = (uint16_T)(LgV2_P.Gain1_Gain_bf * LgV2_B.Compare_cx);

    /* Sum: '<S20>/Sum' */
    LgV2_B.Sum_k = (uint16_T)(uint32_T)(((LgV2_B.Compare_o << 6) +
      LgV2_B.Gain_c5) + LgV2_B.Gain1_mp);

    /* Lookup Block: '<S20>/f_4 < 0'
     * About '<S20>/f_4 < 0 :'
     * Lookup Block: '<S20>/f_4 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_40), LgV2_P.f_40_YData, LgV2_B.Product_o[3],
                         LgV2_P.f_40_XData, 9U);

    /* Lookup Block: '<S20>/f_4 > 0'
     * About '<S20>/f_4 > 0 :'
     * Lookup Block: '<S20>/f_4 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_40_f), LgV2_P.f_40_YData_f,
                         LgV2_B.Product_o[3], LgV2_P.f_40_XData_j, 6U);

    /* MultiPortSwitch: '<S20>/Multiport Switch' incorporates:
     *  Constant: '<S20>/f_4 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_k >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch_cc = LgV2_B.f_40;
      break;

     case 2:
      LgV2_B.MultiportSwitch_cc = LgV2_P.f_40_Value;
      break;

     default:
      LgV2_B.MultiportSwitch_cc = LgV2_B.f_40_f;
      break;
    }

    /* DeadZone Block: '<S21>/Dead Zone'
     */
    if (LgV2_B.Product_o[4] >= LgV2_P.DeadZone_End_a) {
      LgV2_B.DeadZone_f = LgV2_B.Product_o[4] - LgV2_P.DeadZone_End_a;
    } else if (LgV2_B.Product_o[4] > LgV2_P.DeadZone_Start_l) {
      LgV2_B.DeadZone_f = 0.0;
    } else {
      LgV2_B.DeadZone_f = LgV2_B.Product_o[4] - LgV2_P.DeadZone_Start_l;
    }

    /* RelationalOperator: '<S34>/Compare' incorporates:
     *  Constant: '<S34>/Constant'
     */
    LgV2_B.Compare_l = (LgV2_B.DeadZone_f < LgV2_P.Constant_Value_om);

    /* RelationalOperator: '<S36>/Compare' */
    LgV2_B.Compare_b = (LgV2_B.DeadZone_f == 0.0);

    /* Gain: '<S21>/Gain' */
    LgV2_B.Gain_j1 = (uint16_T)(LgV2_P.Gain_Gain_k * LgV2_B.Compare_b);

    /* RelationalOperator: '<S35>/Compare' incorporates:
     *  Constant: '<S35>/Constant'
     */
    LgV2_B.Compare_d = (LgV2_B.DeadZone_f > LgV2_P.Constant_Value_cn);

    /* Gain: '<S21>/Gain1' */
    LgV2_B.Gain1_cf = (uint16_T)(LgV2_P.Gain1_Gain_n * LgV2_B.Compare_d);

    /* Sum: '<S21>/Sum' */
    LgV2_B.Sum_fw = (uint16_T)(uint32_T)(((LgV2_B.Compare_l << 6) +
      LgV2_B.Gain_j1) + LgV2_B.Gain1_cf);

    /* Lookup Block: '<S21>/f_5 < 0'
     * About '<S21>/f_5 < 0 :'
     * Lookup Block: '<S21>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_50), LgV2_P.f_50_YData, LgV2_B.Product_o[4],
                         LgV2_P.f_50_XData, 2U);

    /* Lookup Block: '<S21>/f_5 > 0'
     * About '<S21>/f_5 > 0 :'
     * Lookup Block: '<S21>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_50_g), LgV2_P.f_50_YData_m,
                         LgV2_B.Product_o[4], LgV2_P.f_50_XData_c, 2U);

    /* MultiPortSwitch: '<S21>/Multiport Switch' incorporates:
     *  Constant: '<S21>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_fw >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch_hs = LgV2_B.f_50;
      break;

     case 2:
      LgV2_B.MultiportSwitch_hs = LgV2_P.f_50_Value;
      break;

     default:
      LgV2_B.MultiportSwitch_hs = LgV2_B.f_50_g;
      break;
    }

    /* Saturate: '<S6>/Saturation' */
    tmp_0[0] = LgV2_B.MultiportSwitch;
    tmp_0[1] = LgV2_B.MultiportSwitch_h;
    tmp_0[2] = LgV2_B.MultiportSwitch_c;
    tmp_0[3] = LgV2_B.MultiportSwitch_cc;
    tmp_0[4] = LgV2_B.MultiportSwitch_hs;
    for (i = 0; i < 5; i++) {
      LgV2_B.Saturation_p[i] = rt_SATURATE(tmp_0[i],
        LgV2_P.Saturation_LowerSat_d, LgV2_P.Saturation_UpperSat_d);
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Gain: '<S93>/-l_x1' incorporates:
       *  Constant: '<S93>/l_x1'
       */
      LgV2_B.l_x1_d = LgV2_P.l_x1_Gain_h * LgV2_P.l_x1_Value_p;

      /* Gain: '<S93>/-l_y2' incorporates:
       *  Constant: '<S93>/l_y2'
       */
      LgV2_B.l_y2_h = LgV2_P.l_y2_Gain_o * LgV2_P.l_y2_Value_c;

      /* Gain: '<S93>/-l_x2' incorporates:
       *  Constant: '<S93>/l_x2'
       */
      LgV2_B.l_x2_m = LgV2_P.l_x2_Gain_e * LgV2_P.l_x2_Value_k;

      /* Reshape: '<S93>/3x5' incorporates:
       *  Constant: '<S93>/T_e11'
       *  Constant: '<S93>/T_e12'
       *  Constant: '<S93>/T_e13'
       *  Constant: '<S93>/T_e14'
       *  Constant: '<S93>/T_e15'
       *  Constant: '<S93>/T_e21'
       *  Constant: '<S93>/T_e22'
       *  Constant: '<S93>/T_e23'
       *  Constant: '<S93>/T_e24'
       *  Constant: '<S93>/T_e25'
       *  Constant: '<S93>/l_x3'
       *  Constant: '<S93>/l_y1'
       */
      LgV2_B.x5_a[0] = LgV2_P.T_e11_Value_i;
      LgV2_B.x5_a[1] = LgV2_P.T_e21_Value_m;
      LgV2_B.x5_a[2] = LgV2_P.l_y1_Value_a;
      LgV2_B.x5_a[3] = LgV2_P.T_e12_Value_c;
      LgV2_B.x5_a[4] = LgV2_P.T_e22_Value_c;
      LgV2_B.x5_a[5] = LgV2_B.l_x1_d;
      LgV2_B.x5_a[6] = LgV2_P.T_e13_Value_g;
      LgV2_B.x5_a[7] = LgV2_P.T_e23_Value_h;
      LgV2_B.x5_a[8] = LgV2_B.l_y2_h;
      LgV2_B.x5_a[9] = LgV2_P.T_e14_Value_b;
      LgV2_B.x5_a[10] = LgV2_P.T_e24_Value_c;
      LgV2_B.x5_a[11] = LgV2_B.l_x2_m;
      LgV2_B.x5_a[12] = LgV2_P.T_e15_Value_l;
      LgV2_B.x5_a[13] = LgV2_P.T_e25_Value_o;
      LgV2_B.x5_a[14] = LgV2_P.l_x3_Value_m;

      /* S-Function (sdsppinv): '<S72>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&LgV2_DWork.Pseudoinverse_X[0]), (void *)(&LgV2_B.x5_a[0]),
             15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&LgV2_DWork.Pseudoinverse_X[0], 3, 5,
                      &LgV2_DWork.Pseudoinverse_S[0],
                      &LgV2_DWork.Inverse_DWORK3[0],
                      &LgV2_DWork.Pseudoinverse_WORK[0],
                      &LgV2_DWork.Pseudoinverse_U[0],
                      &LgV2_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&LgV2_DWork.Pseudoinverse_S[0],
          &LgV2_DWork.Pseudoinverse_U[0], &LgV2_DWork.Pseudoinverse_V[0],
          &LgV2_B.Pseudoinverse_j[0], (const int32_T)3, (const int32_T)5);
      }
    }

    /* Trigonometry: '<S47>/R11' */
    LgV2_B.R11_c = cos(LgV2_B.eta_yaw);

    /* Trigonometry: '<S47>/R21' */
    LgV2_B.R21_m = sin(LgV2_B.eta_yaw);

    /* Trigonometry: '<S47>/R12' */
    LgV2_B.R12_f = sin(LgV2_B.eta_yaw);

    /* Gain: '<S47>/-1' */
    LgV2_B.u = LgV2_P.u_Gain * LgV2_B.R12_f;

    /* Trigonometry: '<S47>/R22' */
    LgV2_B.R22_p = cos(LgV2_B.eta_yaw);

    /* Reshape: '<S47>/R(psi)' incorporates:
     *  Constant: '<S47>/R13'
     *  Constant: '<S47>/R23'
     *  Constant: '<S47>/R31'
     *  Constant: '<S47>/R32'
     *  Constant: '<S47>/R33'
     */
    LgV2_B.Rpsi[0] = LgV2_B.R11_c;
    LgV2_B.Rpsi[1] = LgV2_B.R21_m;
    LgV2_B.Rpsi[2] = LgV2_P.R31_Value;
    LgV2_B.Rpsi[3] = LgV2_B.u;
    LgV2_B.Rpsi[4] = LgV2_B.R22_p;
    LgV2_B.Rpsi[5] = LgV2_P.R32_Value;
    LgV2_B.Rpsi[6] = LgV2_P.R13_Value;
    LgV2_B.Rpsi[7] = LgV2_P.R23_Value;
    LgV2_B.Rpsi[8] = LgV2_P.R33_Value;

    /* Math: '<S48>/Math Function' */
    for (i = 0; i < 3; i++) {
      LgV2_B.MathFunction_dr[3 * i] = LgV2_B.Rpsi[i];
      LgV2_B.MathFunction_dr[1 + 3 * i] = LgV2_B.Rpsi[i + 3];
      LgV2_B.MathFunction_dr[2 + 3 * i] = LgV2_B.Rpsi[i + 6];
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Reshape: '<S44>/3x3' incorporates:
       *  Constant: '<S44>/12'
       *  Constant: '<S44>/13'
       *  Constant: '<S44>/21'
       *  Constant: '<S44>/23'
       *  Constant: '<S44>/31'
       *  Constant: '<S44>/32'
       *  Constant: '<S7>/K_i_Surge'
       *  Constant: '<S7>/K_i_Sway'
       *  Constant: '<S7>/K_i_Yaw'
       */
      LgV2_B.x3[0] = LgV2_P.K_i_Surge_Value;
      LgV2_B.x3[1] = LgV2_P.u_Value;
      LgV2_B.x3[2] = LgV2_P.u_Value_e;
      LgV2_B.x3[3] = LgV2_P.u_Value_h;
      LgV2_B.x3[4] = LgV2_P.K_i_Sway_Value;
      LgV2_B.x3[5] = LgV2_P.u_Value_h2;
      LgV2_B.x3[6] = LgV2_P.u_Value_n;
      LgV2_B.x3[7] = LgV2_P.u_Value_h3;
      LgV2_B.x3[8] = LgV2_P.K_i_Yaw_Value;
    }

    /* Integrator: '<S42>/Integrator' */
    LgV2_B.Integrator_k[0] = LgV2_X.Integrator_CSTATE_j[0];
    LgV2_B.Integrator_k[1] = LgV2_X.Integrator_CSTATE_j[1];
    LgV2_B.Integrator_k[2] = LgV2_X.Integrator_CSTATE_j[2];

    /* Product: '<S40>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + LgV2_B.x3[3 * tmp_6] *
          LgV2_B.MathFunction_dr[i];
        tmp_2[i + 3 * tmp_6] = LgV2_B.x3[3 * tmp_6 + 1] *
          LgV2_B.MathFunction_dr[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = LgV2_B.x3[3 * tmp_6 + 2] *
          LgV2_B.MathFunction_dr[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      LgV2_B.Product_c[i] = 0.0;
      LgV2_B.Product_c[i] = tmp_2[i] * LgV2_B.Integrator_k[0] +
        LgV2_B.Product_c[i];
      LgV2_B.Product_c[i] = tmp_2[i + 3] * LgV2_B.Integrator_k[1] +
        LgV2_B.Product_c[i];
      LgV2_B.Product_c[i] = tmp_2[i + 6] * LgV2_B.Integrator_k[2] +
        LgV2_B.Product_c[i];
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Reshape: '<S43>/3x3' incorporates:
       *  Constant: '<S43>/12'
       *  Constant: '<S43>/13'
       *  Constant: '<S43>/21'
       *  Constant: '<S43>/23'
       *  Constant: '<S43>/31'
       *  Constant: '<S43>/32'
       *  Constant: '<S7>/K_d_Surge'
       *  Constant: '<S7>/K_d_Sway'
       *  Constant: '<S7>/K_d_Yaw'
       */
      LgV2_B.x3_d[0] = LgV2_P.K_d_Surge_Value;
      LgV2_B.x3_d[1] = LgV2_P.u_Value_m;
      LgV2_B.x3_d[2] = LgV2_P.u_Value_hb;
      LgV2_B.x3_d[3] = LgV2_P.u_Value_f;
      LgV2_B.x3_d[4] = LgV2_P.K_d_Sway_Value;
      LgV2_B.x3_d[5] = LgV2_P.u_Value_j;
      LgV2_B.x3_d[6] = LgV2_P.u_Value_i;
      LgV2_B.x3_d[7] = LgV2_P.u_Value_d;
      LgV2_B.x3_d[8] = LgV2_P.K_d_Yaw_Value;

      /* Gain: '<S40>/4' incorporates:
       *  Constant: '<S7>/kappa_1'
       */
      LgV2_B.u_n = LgV2_P._Gain * LgV2_P.kappa_1_Value;

      /* Product: '<S40>/Divide' incorporates:
       *  Constant: '<S40>/1'
       */
      LgV2_B.Divide_g = LgV2_P._Value / LgV2_B.u_n;

      /* Reshape: '<S45>/R(psi)' incorporates:
       *  Constant: '<S45>/12'
       *  Constant: '<S45>/13'
       *  Constant: '<S45>/21'
       *  Constant: '<S45>/23'
       *  Constant: '<S45>/31'
       *  Constant: '<S45>/32'
       *  Constant: '<S7>/K_p_Surge'
       *  Constant: '<S7>/K_p_Sway'
       *  Constant: '<S7>/K_p_Yaw'
       */
      LgV2_B.Rpsi_n[0] = LgV2_P.K_p_Surge_Value;
      LgV2_B.Rpsi_n[1] = LgV2_P.u_Value_ho;
      LgV2_B.Rpsi_n[2] = LgV2_P.u_Value_k;
      LgV2_B.Rpsi_n[3] = LgV2_P.u_Value_fw;
      LgV2_B.Rpsi_n[4] = LgV2_P.K_p_Sway_Value;
      LgV2_B.Rpsi_n[5] = LgV2_P.u_Value_hc;
      LgV2_B.Rpsi_n[6] = LgV2_P.u_Value_fu;
      LgV2_B.Rpsi_n[7] = LgV2_P.u_Value_mz;
      LgV2_B.Rpsi_n[8] = LgV2_P.K_p_Yaw_Value;
      for (i = 0; i < 9; i++) {
        /* Sum: '<S40>/Add1' */
        LgV2_B.Add1_j[i] = LgV2_B.x3_d[i] + LgV2_B.Divide_g;

        /* Product: '<S54>/Product' incorporates:
         *  Constant: '<S7>/kappa_1'
         *  Constant: '<S97>/Constant'
         */
        LgV2_B.Product_bs[i] = LgV2_P.kappa_1_Value * LgV2_P.Constant_Value_bc[i];

        /* Sum: '<S54>/Subtract' */
        LgV2_B.Subtract_dr[i] = LgV2_B.Rpsi_n[i] - LgV2_B.Product_bs[i];
      }
    }

    /* Gain: '<S105>/Gain' */
    LgV2_B.Gain_c = LgV2_P.Gain_Gain_a * LgV2_B.eta_yaw;

    /* Saturate: '<S103>/Saturation' */
    tmp = LgV2_B.Gain_c;
    LgV2_B.Saturation_cg = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_id,
      LgV2_P.Saturation_UpperSat_gd);

    /* Signum: '<S103>/Sign' */
    LgV2_B.Sign_g = rt_SIGNd_snf(LgV2_B.Saturation_cg);

    /* Gain: '<S103>/Gain' */
    LgV2_B.Gain_je = LgV2_P.Gain_Gain_j * LgV2_B.Sign_g;

    /* Sum: '<S103>/Sum1' */
    LgV2_B.Sum1_e = LgV2_B.Saturation_cg + LgV2_B.Gain_je;

    /* Math: '<S103>/Math Function' incorporates:
     *  Constant: '<S103>/Constant'
     */
    LgV2_B.MathFunction_f = rt_rem_snf(LgV2_B.Sum1_e, LgV2_P.Constant_Value_cj);

    /* Sum: '<S103>/Sum' */
    LgV2_B.Sum_d = LgV2_B.MathFunction_f - LgV2_B.Gain_je;

    /* Gain: '<S104>/Gain1' */
    LgV2_B.Gain1_l = LgV2_P.Gain1_Gain_oh * LgV2_B.Sum_d;

    /* Sum: '<S58>/Subtract' */
    LgV2_B.Subtract_f[0] = LgV2_B.eta_surge - LgV2_B.q_x;
    LgV2_B.Subtract_f[1] = LgV2_B.eta_sway - LgV2_B.q_y;
    LgV2_B.Subtract_f[2] = LgV2_B.Gain1_l - LgV2_B.psi_los;

    /* Gain: '<S108>/Gain' */
    LgV2_B.Gain_bu = LgV2_P.Gain_Gain_c * LgV2_B.Subtract_f[2];

    /* Saturate: '<S106>/Saturation' */
    tmp = LgV2_B.Gain_bu;
    LgV2_B.Saturation_d = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_g,
      LgV2_P.Saturation_UpperSat_bg);

    /* Signum: '<S106>/Sign' */
    LgV2_B.Sign_g2 = rt_SIGNd_snf(LgV2_B.Saturation_d);

    /* Gain: '<S106>/Gain' */
    LgV2_B.Gain_ag = LgV2_P.Gain_Gain_c0 * LgV2_B.Sign_g2;

    /* Sum: '<S106>/Sum1' */
    LgV2_B.Sum1_h = LgV2_B.Saturation_d + LgV2_B.Gain_ag;

    /* Math: '<S106>/Math Function' incorporates:
     *  Constant: '<S106>/Constant'
     */
    LgV2_B.MathFunction_od = rt_rem_snf(LgV2_B.Sum1_h, LgV2_P.Constant_Value_l);

    /* Sum: '<S106>/Sum' */
    LgV2_B.Sum_e = LgV2_B.MathFunction_od - LgV2_B.Gain_ag;

    /* Gain: '<S107>/Gain1' */
    LgV2_B.Gain1_m = LgV2_P.Gain1_Gain_d * LgV2_B.Sum_e;

    /* SignalConversion: '<S58>/TmpHiddenBufferAtProductInport2' */
    LgV2_B.TmpHiddenBufferAtProductInpor_a[0] = LgV2_B.Subtract_f[0];
    LgV2_B.TmpHiddenBufferAtProductInpor_a[1] = LgV2_B.Subtract_f[1];
    LgV2_B.TmpHiddenBufferAtProductInpor_a[2] = LgV2_B.Gain1_m;

    /* Product: '<S58>/Product' */
    for (i = 0; i < 3; i++) {
      LgV2_B.Product_i[i] = 0.0;
      LgV2_B.Product_i[i] = LgV2_B.MathFunction_dr[i] *
        LgV2_B.TmpHiddenBufferAtProductInpor_a[0] + LgV2_B.Product_i[i];
      LgV2_B.Product_i[i] = LgV2_B.MathFunction_dr[i + 3] *
        LgV2_B.TmpHiddenBufferAtProductInpor_a[1] + LgV2_B.Product_i[i];
      LgV2_B.Product_i[i] = LgV2_B.MathFunction_dr[i + 6] *
        LgV2_B.TmpHiddenBufferAtProductInpor_a[2] + LgV2_B.Product_i[i];
    }

    /* Product: '<S54>/Product1' */
    for (i = 0; i < 3; i++) {
      LgV2_B.Product1_ce[i] = 0.0;
      LgV2_B.Product1_ce[i] = LgV2_B.Subtract_dr[i] * LgV2_B.Product_i[0] +
        LgV2_B.Product1_ce[i];
      LgV2_B.Product1_ce[i] = LgV2_B.Subtract_dr[i + 3] * LgV2_B.Product_i[1] +
        LgV2_B.Product1_ce[i];
      LgV2_B.Product1_ce[i] = LgV2_B.Subtract_dr[i + 6] * LgV2_B.Product_i[2] +
        LgV2_B.Product1_ce[i];
    }

    /* Trigonometry: '<S132>/f_qx' */
    LgV2_B.f_qx = cos(LgV2_B.Gain1_o);

    /* Trigonometry: '<S132>/f_qy' */
    LgV2_B.f_qy = sin(LgV2_B.Gain1_o);

    /* SignalConversion: '<S132>/TmpHiddenBufferAtProductInport1' */
    LgV2_B.TmpHiddenBufferAtProductInport1[0] = LgV2_B.f_qx;
    LgV2_B.TmpHiddenBufferAtProductInport1[1] = LgV2_B.f_qy;

    /* Product: '<S132>/Product' incorporates:
     *  Constant: '<S197>/u_d'
     */
    LgV2_B.Product_g5[0] = LgV2_B.TmpHiddenBufferAtProductInport1[0] *
      LgV2_P.u_d_Value;
    LgV2_B.Product_g5[1] = LgV2_B.TmpHiddenBufferAtProductInport1[1] *
      LgV2_P.u_d_Value;

    /* SignalConversion: '<S60>/ConcatBufferAtVector ConcatenateIn1' */
    LgV2_B.VectorConcatenate_e[0] = LgV2_B.Product_g5[0];
    LgV2_B.VectorConcatenate_e[1] = LgV2_B.Product_g5[1];
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S148>/Delta^2' incorporates:
       *  Constant: '<S114>/Delta'
       */
      tmp = LgV2_P.Delta_Value;
      LgV2_B.Delta2 = tmp * tmp;
    }

    /* Math: '<S148>/epsilon_n^2' */
    tmp = LgV2_B.MultiportSelector;
    LgV2_B.epsilon_n2 = tmp * tmp;

    /* Sum: '<S148>/Add' */
    LgV2_B.Add_o = LgV2_B.Delta2 + LgV2_B.epsilon_n2;

    /* Product: '<S148>/Divide' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Divide_gx = LgV2_P.Delta_Value / LgV2_B.Add_o;

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S130>/Multiport Selector1' */
    {
      const byte_T *u = (byte_T *)LgV2_B.MathFunction_b;/* input port */
      const int32_T *index = (const int32_T *)&LgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&LgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)LgV2_B.MultiportSelector1;
      int_T ctr;

      /* Loop over each row of current output port index */
      for (ctr = 0; ctr < numRowsThisOutput; ctr++) {
        int_T inputRowIdx = *index++;
        int_T inputRowOffsetBytes;
        int_T outputRowOffsetBytes;
        int_T sampleIdx;
        inputRowOffsetBytes = inputRowIdx * sizeof(real_T);
        outputRowOffsetBytes = ctr * sizeof(real_T);

        /* Copy one sample at a time from each input column */
        for (sampleIdx = 0; sampleIdx < 2; sampleIdx++) {
          memcpy((y + (sampleIdx * bytesPerOutCol) + outputRowOffsetBytes),
                 (u + (sampleIdx * (2 * sizeof(real_T))) + inputRowOffsetBytes),
                 sizeof(real_T) );
        }
      }                                /* output row loop */
    }                                  /* end <S130>/Multiport Selector1 */

    /* Product: '<S148>/Product' */
    LgV2_B.Product_n[0] = LgV2_B.Divide_gx * LgV2_B.MultiportSelector1[0];

    /* Gain: '<S148>/-1' */
    LgV2_B.u_o[0] = LgV2_P.u_Gain_e * LgV2_B.Product_n[0];

    /* Product: '<S148>/Product' */
    LgV2_B.Product_n[1] = LgV2_B.Divide_gx * LgV2_B.MultiportSelector1[1];

    /* Gain: '<S148>/-1' */
    LgV2_B.u_o[1] = LgV2_P.u_Gain_e * LgV2_B.Product_n[1];

    /* Product: '<S60>/Product' */
    tmp = LgV2_B.u_o[0] * LgV2_B.Product_g5[0];
    tmp += LgV2_B.u_o[1] * LgV2_B.Product_g5[1];
    LgV2_B.VectorConcatenate_e[2] = tmp;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Constant: '<S66>/0_2x1' */
      LgV2_B.VectorConcatenate_eb[0] = LgV2_P._2x1_Value[0];
      LgV2_B.VectorConcatenate_eb[1] = LgV2_P._2x1_Value[1];

      /* Product: '<S184>/Product' incorporates:
       *  Constant: '<S117>/Path Selector'
       *  Constant: '<S173>/0_2x1'
       */
      LgV2_B.Product_a[0] = LgV2_P._2x1_Value_n * LgV2_P.PathSelector_Value;
      LgV2_B.Product_a[1] = LgV2_P._2x1_Value_n * LgV2_P.PathSelector_Value;
    }

    /* Product: '<S178>/Product2' incorporates:
     *  Constant: '<S197>/k'
     */
    LgV2_B.Product2_b = LgV2_B.Integrator1 * LgV2_P.k_Value;

    /* Trigonometry: '<S178>/sin(s)3' */
    LgV2_B.sins3 = sin(LgV2_B.Product2_b);
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S178>/Math Function' incorporates:
       *  Constant: '<S178>/Constant'
       *  Constant: '<S197>/k'
       */
      if ((LgV2_P.k_Value < 0.0) && (LgV2_P.Constant_Value_a4 > floor
           (LgV2_P.Constant_Value_a4))) {
        LgV2_B.MathFunction_l = -rt_pow_snf(-LgV2_P.k_Value,
          LgV2_P.Constant_Value_a4);
      } else {
        LgV2_B.MathFunction_l = rt_pow_snf(LgV2_P.k_Value,
          LgV2_P.Constant_Value_a4);
      }
    }

    /* Product: '<S178>/Product' incorporates:
     *  Constant: '<S197>/r_x'
     */
    LgV2_B.Product_nx = LgV2_P.r_x_Value * LgV2_B.sins3 * LgV2_B.MathFunction_l;

    /* Trigonometry: '<S178>/cos(s)3' */
    LgV2_B.coss3 = cos(LgV2_B.Product2_b);

    /* Product: '<S178>/Product1' incorporates:
     *  Constant: '<S197>/r_y'
     */
    LgV2_B.Product1_o = LgV2_P.r_y_Value * LgV2_B.coss3 * LgV2_B.MathFunction_l;

    /* Gain: '<S178>/Gain' */
    LgV2_B.Gain_d = LgV2_P.Gain_Gain_gg * LgV2_B.Product1_o;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Sum: '<S184>/Subtract' incorporates:
       *  Constant: '<S117>/Path Selector'
       *  Constant: '<S184>/Constant'
       */
      LgV2_B.Subtract_j = LgV2_P.Constant_Value_d3 - LgV2_P.PathSelector_Value;
    }

    /* Product: '<S184>/Product1' */
    LgV2_B.Product1_m[0] = LgV2_B.Product_nx * LgV2_B.Subtract_j;
    LgV2_B.Product1_m[1] = LgV2_B.Gain_d * LgV2_B.Subtract_j;

    /* Sum: '<S184>/Add' */
    LgV2_B.Add_mw[0] = LgV2_B.Product_a[0] + LgV2_B.Product1_m[0];
    LgV2_B.Add_mw[1] = LgV2_B.Product_a[1] + LgV2_B.Product1_m[1];

    /* Product: '<S120>/x_d^s * y_d^s^2' */
    LgV2_B.x_dsy_ds2 = LgV2_B.Add[0] * LgV2_B.Add_mw[1];

    /* Product: '<S120>/x_d^s^2 * y_d^s' */
    LgV2_B.x_ds2y_ds = LgV2_B.Add_mw[0] * LgV2_B.Add[1];

    /* Sum: '<S120>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
    LgV2_B.x_dsy_ds2x_ds2y_ds = LgV2_B.x_dsy_ds2 - LgV2_B.x_ds2y_ds;

    /* Math: '<S120>/( x_d^s )^2' */
    tmp = LgV2_B.Add[0];
    LgV2_B.x_ds2 = tmp * tmp;

    /* Math: '<S120>/( y_d^s )^2' */
    tmp = LgV2_B.Add[1];
    LgV2_B.y_ds2 = tmp * tmp;

    /* Sum: '<S120>/( x_d^s )^2 + ( y_d^s )^2' */
    LgV2_B.x_ds2y_ds2 = LgV2_B.x_ds2 + LgV2_B.y_ds2;

    /* Product: '<S120>/Divide' */
    LgV2_B.Divide_h = LgV2_B.x_dsy_ds2x_ds2y_ds / LgV2_B.x_ds2y_ds2;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S151>/Delta^2' incorporates:
       *  Constant: '<S114>/Delta'
       */
      tmp = LgV2_P.Delta_Value;
      LgV2_B.Delta2_h = tmp * tmp;
    }

    /* Math: '<S151>/epsilon_n^2' */
    tmp = LgV2_B.MultiportSelector;
    LgV2_B.epsilon_n2_c = tmp * tmp;

    /* Sum: '<S151>/Add' */
    LgV2_B.Add_no = LgV2_B.Delta2_h + LgV2_B.epsilon_n2_c;

    /* Product: '<S151>/Divide' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Divide_a = LgV2_P.Delta_Value / LgV2_B.Add_no;

    /* Outputs for atomic SubSystem: '<S130>/S_2' */

    /* Gain: '<S164>/S12' */
    LgV2_B.S12_c = LgV2_P.S12_Gain_o * LgV2_B.Divide_h;

    /* Reshape: '<S164>/S_2(psi_d^s)' incorporates:
     *  Constant: '<S164>/0'
     */
    LgV2_B.S_2psi_ds[0] = LgV2_P._Value_i;
    LgV2_B.S_2psi_ds[1] = LgV2_B.Divide_h;
    LgV2_B.S_2psi_ds[2] = LgV2_B.S12_c;
    LgV2_B.S_2psi_ds[3] = LgV2_P._Value_i;

    /* end of Outputs for SubSystem: '<S130>/S_2' */

    /* Math: '<S167>/Math Function' */
    LgV2_B.MathFunction_ii[0] = LgV2_B.S_2psi_ds[0];
    LgV2_B.MathFunction_ii[1] = LgV2_B.S_2psi_ds[2];
    LgV2_B.MathFunction_ii[2] = LgV2_B.S_2psi_ds[1];
    LgV2_B.MathFunction_ii[3] = LgV2_B.S_2psi_ds[3];

    /* Product: '<S169>/Product' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += LgV2_B.MathFunction_ii[i] * LgV2_B.MathFunction_b[0];
      tmp_3[i] += LgV2_B.MathFunction_ii[i + 2] * LgV2_B.MathFunction_b[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += LgV2_B.MathFunction_ii[i] * LgV2_B.MathFunction_b[2];
      tmp_3[i + 2] += LgV2_B.MathFunction_ii[i + 2] * LgV2_B.MathFunction_b[3];
    }

    LgV2_B.Product_gx[0] = 0.0;
    LgV2_B.Product_gx[0] = tmp_3[0] * LgV2_B.qp_d[0] + LgV2_B.Product_gx[0];
    LgV2_B.Product_gx[0] = tmp_3[2] * LgV2_B.qp_d[1] + LgV2_B.Product_gx[0];

    /* Product: '<S169>/Product1' */
    LgV2_B.Product1_p[0] = 0.0;
    LgV2_B.Product1_p[0] = LgV2_B.MathFunction_b[0] * LgV2_B.Add[0] +
      LgV2_B.Product1_p[0];
    LgV2_B.Product1_p[0] = LgV2_B.MathFunction_b[2] * LgV2_B.Add[1] +
      LgV2_B.Product1_p[0];

    /* Sum: '<S169>/Subtract1' */
    LgV2_B.Subtract1[0] = LgV2_B.Product_gx[0] - LgV2_B.Product1_p[0];
    LgV2_B.Product_gx[1] = 0.0;
    LgV2_B.Product_gx[1] = tmp_3[1] * LgV2_B.qp_d[0] + LgV2_B.Product_gx[1];
    LgV2_B.Product_gx[1] = tmp_3[3] * LgV2_B.qp_d[1] + LgV2_B.Product_gx[1];

    /* Product: '<S169>/Product1' */
    LgV2_B.Product1_p[1] = 0.0;
    LgV2_B.Product1_p[1] = LgV2_B.MathFunction_b[1] * LgV2_B.Add[0] +
      LgV2_B.Product1_p[1];
    LgV2_B.Product1_p[1] = LgV2_B.MathFunction_b[3] * LgV2_B.Add[1] +
      LgV2_B.Product1_p[1];

    /* Sum: '<S169>/Subtract1' */
    LgV2_B.Subtract1[1] = LgV2_B.Product_gx[1] - LgV2_B.Product1_p[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S130>/Multiport Selector2' */
    {
      const byte_T *u = (byte_T *)LgV2_B.Subtract1;/* input port */
      const int32_T *index = (const int32_T *)&LgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&LgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&LgV2_B.MultiportSelector2;
      int_T ctr;

      /* Loop over each row of current output port index */
      for (ctr = 0; ctr < numRowsThisOutput; ctr++) {
        int_T inputRowIdx = *index++;
        int_T inputRowOffsetBytes;
        int_T outputRowOffsetBytes;
        int_T sampleIdx;
        inputRowOffsetBytes = inputRowIdx * sizeof(real_T);
        outputRowOffsetBytes = ctr * sizeof(real_T);

        /* Copy one sample at a time from each input column */
        for (sampleIdx = 0; sampleIdx < 1; sampleIdx++) {
          memcpy((y + (sampleIdx * bytesPerOutCol) + outputRowOffsetBytes),
                 (u + (sampleIdx * (2 * sizeof(real_T))) + inputRowOffsetBytes),
                 sizeof(real_T) );
        }
      }                                /* output row loop */
    }                                  /* end <S130>/Multiport Selector2 */

    /* Product: '<S151>/Product' */
    LgV2_B.Product_ay = LgV2_B.Divide_a * LgV2_B.MultiportSelector2;

    /* Sum: '<S151>/Subtract' */
    LgV2_B.Subtract_h = LgV2_B.Divide_h - LgV2_B.Product_ay;

    /* Math: '<S136>/epsilon_n^2' */
    tmp = LgV2_B.MultiportSelector;
    LgV2_B.epsilon_n2_i = tmp * tmp;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S136>/Delta^2' incorporates:
       *  Constant: '<S114>/Delta'
       */
      tmp = LgV2_P.Delta_Value;
      LgV2_B.Delta2_b = tmp * tmp;
    }

    /* Sum: '<S136>/Add' */
    LgV2_B.Add_mh = LgV2_B.epsilon_n2_i + LgV2_B.Delta2_b;

    /* Math: '<S136>/sqrt' */
    tmp = LgV2_B.Add_mh;
    if (tmp < 0.0) {
      LgV2_B.sqrt_c = -sqrt(-tmp);
    } else {
      LgV2_B.sqrt_c = sqrt(tmp);
    }

    /* Product: '<S136>/Divide' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Divide_f = LgV2_P.Delta_Value / LgV2_B.sqrt_c;

    /* Product: '<S136>/Product' */
    LgV2_B.Product_bv = LgV2_B.Divide_f * LgV2_B.Divide;

    /* Math: '<S143>/Math Function' */
    LgV2_B.MathFunction_p1[0] = LgV2_B.Add[0];

    /* Product: '<S140>/Divide' */
    LgV2_B.Divide_k[0] = LgV2_B.MathFunction_p1[0] / LgV2_B.Add_n;

    /* Math: '<S143>/Math Function' */
    LgV2_B.MathFunction_p1[1] = LgV2_B.Add[1];

    /* Product: '<S140>/Divide' */
    LgV2_B.Divide_k[1] = LgV2_B.MathFunction_p1[1] / LgV2_B.Add_n;

    /* Sum: '<S128>/Subtract' */
    LgV2_B.Subtract_e[0] = LgV2_B.Integrator[0] - LgV2_B.Switch2;
    LgV2_B.Subtract_e[1] = LgV2_B.Integrator[1] - LgV2_B.Switch2_h;

    /* Product: '<S140>/Product' incorporates:
     *  Constant: '<S114>/my'
     */
    tmp = LgV2_P.my_Value * LgV2_B.Divide_k[0] * LgV2_B.Subtract_e[0];
    tmp += LgV2_P.my_Value * LgV2_B.Divide_k[1] * LgV2_B.Subtract_e[1];
    LgV2_B.Product_kj = tmp;

    /* Gain: '<S140>/Gain' */
    LgV2_B.Gain_c0 = LgV2_P.Gain_Gain_b * LgV2_B.Product_kj;

    /* Sum: '<S136>/Subtract' */
    LgV2_B.Subtract_l = LgV2_B.Product_bv - LgV2_B.Gain_c0;

    /* Product: '<S66>/Product' */
    LgV2_B.VectorConcatenate_eb[2] = LgV2_B.Subtract_h * LgV2_B.Subtract_l;

    /* Sum: '<S54>/Add' */
    LgV2_B.Add_c[0] = LgV2_B.VectorConcatenate_e[0] +
      LgV2_B.VectorConcatenate_eb[0];
    LgV2_B.Add_c[1] = LgV2_B.VectorConcatenate_e[1] +
      LgV2_B.VectorConcatenate_eb[1];
    LgV2_B.Add_c[2] = LgV2_B.VectorConcatenate_e[2] +
      LgV2_B.VectorConcatenate_eb[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S54>/Product2' */
      LgV2_B.Product2_p[i] = 0.0;
      LgV2_B.Product2_p[i] = LgV2_B.MathFunction_dr[i] * LgV2_B.Add_c[0] +
        LgV2_B.Product2_p[i];
      LgV2_B.Product2_p[i] = LgV2_B.MathFunction_dr[i + 3] * LgV2_B.Add_c[1] +
        LgV2_B.Product2_p[i];
      LgV2_B.Product2_p[i] = LgV2_B.MathFunction_dr[i + 6] * LgV2_B.Add_c[2] +
        LgV2_B.Product2_p[i];

      /* Sum: '<S54>/Sum' */
      LgV2_B.Sum_p5[i] = LgV2_B.Product2_p[i] - LgV2_B.Product1_ce[i];

      /* Sum: '<S59>/Subtract' */
      LgV2_B.Subtract_di[i] = LgV2_B.TmpHiddenBufferAtKdInport1[i] -
        LgV2_B.Sum_p5[i];
    }

    /* Product: '<S40>/Product1' */
    for (i = 0; i < 3; i++) {
      LgV2_B.Product1_a[i] = 0.0;
      LgV2_B.Product1_a[i] = LgV2_B.Add1_j[i] * LgV2_B.Subtract_di[0] +
        LgV2_B.Product1_a[i];
      LgV2_B.Product1_a[i] = LgV2_B.Add1_j[i + 3] * LgV2_B.Subtract_di[1] +
        LgV2_B.Product1_a[i];
      LgV2_B.Product1_a[i] = LgV2_B.Add1_j[i + 6] * LgV2_B.Subtract_di[2] +
        LgV2_B.Product1_a[i];
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Gain: '<S70>/-X_u' incorporates:
       *  Constant: '<S70>/X_u'
       */
      LgV2_B.X_u = LgV2_P.X_u_Gain * LgV2_P.X_u_Value;

      /* Gain: '<S70>/-Y_v' incorporates:
       *  Constant: '<S70>/Y_v'
       */
      LgV2_B.Y_v = LgV2_P.Y_v_Gain * LgV2_P.Y_v_Value;

      /* Gain: '<S70>/-N_v' incorporates:
       *  Constant: '<S70>/N_v'
       */
      LgV2_B.N_v = LgV2_P.N_v_Gain * LgV2_P.N_v_Value;

      /* Gain: '<S70>/-Y_vr' incorporates:
       *  Constant: '<S70>/Y_r'
       */
      LgV2_B.Y_vr = LgV2_P.Y_vr_Gain * LgV2_P.Y_r_Value;

      /* Gain: '<S70>/-N_r' incorporates:
       *  Constant: '<S70>/N_r'
       */
      LgV2_B.N_r = LgV2_P.N_r_Gain * LgV2_P.N_r_Value;

      /* Reshape: '<S70>/Linear Dampning matrix' incorporates:
       *  Constant: '<S70>/D_L_12'
       *  Constant: '<S70>/D_L_13'
       *  Constant: '<S70>/D_L_21'
       *  Constant: '<S70>/D_L_31'
       */
      LgV2_B.LinearDampningmatrix[0] = LgV2_B.X_u;
      LgV2_B.LinearDampningmatrix[1] = LgV2_P.D_L_21_Value;
      LgV2_B.LinearDampningmatrix[2] = LgV2_P.D_L_31_Value;
      LgV2_B.LinearDampningmatrix[3] = LgV2_P.D_L_12_Value;
      LgV2_B.LinearDampningmatrix[4] = LgV2_B.Y_v;
      LgV2_B.LinearDampningmatrix[5] = LgV2_B.N_v;
      LgV2_B.LinearDampningmatrix[6] = LgV2_P.D_L_13_Value;
      LgV2_B.LinearDampningmatrix[7] = LgV2_B.Y_vr;
      LgV2_B.LinearDampningmatrix[8] = LgV2_B.N_r;
    }

    /* Product: '<S40>/Product2' */
    for (i = 0; i < 3; i++) {
      LgV2_B.Product2_o[i] = 0.0;
      LgV2_B.Product2_o[i] = LgV2_B.LinearDampningmatrix[i] *
        LgV2_B.TmpHiddenBufferAtKdInport1[0] + LgV2_B.Product2_o[i];
      LgV2_B.Product2_o[i] = LgV2_B.LinearDampningmatrix[i + 3] *
        LgV2_B.TmpHiddenBufferAtKdInport1[1] + LgV2_B.Product2_o[i];
      LgV2_B.Product2_o[i] = LgV2_B.LinearDampningmatrix[i + 6] *
        LgV2_B.TmpHiddenBufferAtKdInport1[2] + LgV2_B.Product2_o[i];
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Sum: '<S46>/M_11' incorporates:
       *  Constant: '<S46>/X_udot'
       *  Constant: '<S46>/m'
       */
      LgV2_B.M_11 = LgV2_P.m_Value - LgV2_P.X_udot_Value;

      /* Sum: '<S46>/M_22' incorporates:
       *  Constant: '<S46>/Y_vdot'
       *  Constant: '<S46>/m'
       */
      LgV2_B.M_22 = LgV2_P.m_Value - LgV2_P.Y_vdot_Value;

      /* Product: '<S46>/m x_g' incorporates:
       *  Constant: '<S46>/m'
       *  Constant: '<S46>/x_g'
       */
      LgV2_B.mx_g = LgV2_P.m_Value * LgV2_P.x_g_Value;

      /* Sum: '<S46>/M_32' incorporates:
       *  Constant: '<S46>/N_vdot'
       */
      LgV2_B.M_32 = LgV2_B.mx_g - LgV2_P.N_vdot_Value;

      /* Sum: '<S46>/M_23' incorporates:
       *  Constant: '<S46>/Y_rdot'
       */
      LgV2_B.M_23 = LgV2_B.mx_g - LgV2_P.Y_rdot_Value;

      /* Sum: '<S46>/M_33' incorporates:
       *  Constant: '<S46>/I_z'
       *  Constant: '<S46>/N_rdot'
       */
      LgV2_B.M_33 = LgV2_P.I_z_Value - LgV2_P.N_rdot_Value;

      /* Reshape: '<S46>/3x3' incorporates:
       *  Constant: '<S46>/M_12'
       *  Constant: '<S46>/M_13'
       *  Constant: '<S46>/M_21'
       *  Constant: '<S46>/M_31'
       */
      LgV2_B.x3_n[0] = LgV2_B.M_11;
      LgV2_B.x3_n[1] = LgV2_P.M_21_Value;
      LgV2_B.x3_n[2] = LgV2_P.M_31_Value;
      LgV2_B.x3_n[3] = LgV2_P.M_12_Value;
      LgV2_B.x3_n[4] = LgV2_B.M_22;
      LgV2_B.x3_n[5] = LgV2_B.M_32;
      LgV2_B.x3_n[6] = LgV2_P.M_13_Value;
      LgV2_B.x3_n[7] = LgV2_B.M_23;
      LgV2_B.x3_n[8] = LgV2_B.M_33;
      for (i = 0; i < 9; i++) {
        /* Product: '<S57>/Product1' incorporates:
         *  Constant: '<S100>/Constant'
         *  Constant: '<S7>/kappa_1'
         */
        LgV2_B.Product1_e[i] = LgV2_P.kappa_1_Value * LgV2_P.Constant_Value_dh[i];

        /* Sum: '<S57>/Add3' */
        LgV2_B.Add3[i] = LgV2_B.Rpsi_n[i] + LgV2_B.Product1_e[i];
      }
    }

    /* Gain: '<S49>/S12' */
    LgV2_B.S12 = LgV2_P.S12_Gain * LgV2_B.nu_yaw;

    /* Reshape: '<S49>/S(r)' incorporates:
     *  Constant: '<S49>/R31'
     *  Constant: '<S49>/S11'
     *  Constant: '<S49>/S13'
     *  Constant: '<S49>/S22'
     *  Constant: '<S49>/S23'
     *  Constant: '<S49>/S32'
     *  Constant: '<S49>/S33'
     */
    LgV2_B.Sr[0] = LgV2_P.S11_Value;
    LgV2_B.Sr[1] = LgV2_B.nu_yaw;
    LgV2_B.Sr[2] = LgV2_P.R31_Value_a;
    LgV2_B.Sr[3] = LgV2_B.S12;
    LgV2_B.Sr[4] = LgV2_P.S22_Value;
    LgV2_B.Sr[5] = LgV2_P.S32_Value;
    LgV2_B.Sr[6] = LgV2_P.S13_Value;
    LgV2_B.Sr[7] = LgV2_P.S23_Value;
    LgV2_B.Sr[8] = LgV2_P.S33_Value;

    /* Math: '<S50>/Math Function' */
    for (i = 0; i < 3; i++) {
      LgV2_B.MathFunction_oi[3 * i] = LgV2_B.Sr[i];
      LgV2_B.MathFunction_oi[1 + 3 * i] = LgV2_B.Sr[i + 3];
      LgV2_B.MathFunction_oi[2 + 3 * i] = LgV2_B.Sr[i + 6];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S57>/Product' */
      LgV2_B.Product_gv[i] = 0.0;
      LgV2_B.Product_gv[i] = LgV2_B.MathFunction_oi[i] * LgV2_B.Product_i[0] +
        LgV2_B.Product_gv[i];
      LgV2_B.Product_gv[i] = LgV2_B.MathFunction_oi[i + 3] * LgV2_B.Product_i[1]
        + LgV2_B.Product_gv[i];
      LgV2_B.Product_gv[i] = LgV2_B.MathFunction_oi[i + 6] * LgV2_B.Product_i[2]
        + LgV2_B.Product_gv[i];

      /* Sum: '<S57>/Add' */
      LgV2_B.Add_ot[i] = LgV2_B.Product_gv[i] +
        LgV2_B.TmpHiddenBufferAtKdInport1[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S57>/Product2' */
      LgV2_B.Product2_i[i] = 0.0;
      LgV2_B.Product2_i[i] = LgV2_B.Add3[i] * LgV2_B.Add_ot[0] +
        LgV2_B.Product2_i[i];
      LgV2_B.Product2_i[i] = LgV2_B.Add3[i + 3] * LgV2_B.Add_ot[1] +
        LgV2_B.Product2_i[i];
      LgV2_B.Product2_i[i] = LgV2_B.Add3[i + 6] * LgV2_B.Add_ot[2] +
        LgV2_B.Product2_i[i];

      /* Sum: '<S57>/Add1' */
      LgV2_B.Add1_o[i] = LgV2_B.VectorConcatenate_e[i] +
        LgV2_B.VectorConcatenate_eb[i];
    }

    /* Product: '<S57>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + LgV2_B.MathFunction_dr[3 *
          tmp_6] * LgV2_B.MathFunction_oi[i];
        tmp_2[i + 3 * tmp_6] = LgV2_B.MathFunction_dr[3 * tmp_6 + 1] *
          LgV2_B.MathFunction_oi[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = LgV2_B.MathFunction_dr[3 * tmp_6 + 2] *
          LgV2_B.MathFunction_oi[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      LgV2_B.Product3[i] = 0.0;
      LgV2_B.Product3[i] = tmp_2[i] * LgV2_B.Add1_o[0] + LgV2_B.Product3[i];
      LgV2_B.Product3[i] = tmp_2[i + 3] * LgV2_B.Add1_o[1] + LgV2_B.Product3[i];
      LgV2_B.Product3[i] = tmp_2[i + 6] * LgV2_B.Add1_o[2] + LgV2_B.Product3[i];
    }

    /* Trigonometry: '<S135>/Trigonometric Function' */
    LgV2_B.TrigonometricFunction_b = cos(LgV2_B.Gain1_o);

    /* Trigonometry: '<S135>/Trigonometric Function1' */
    LgV2_B.TrigonometricFunction1 = sin(LgV2_B.Gain1_o);

    /* Derivative Block: '<S118>/Derivative' */
    {
      real_T t = LgV2_M->Timing.t[0];
      real_T timeStampA = LgV2_DWork.Derivative_RWORK_m.TimeStampA;
      real_T timeStampB = LgV2_DWork.Derivative_RWORK_m.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        LgV2_B.Derivative_j = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &LgV2_DWork.Derivative_RWORK_m.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 2;
          }
        } else if (timeStampA >= t) {
          lastBank += 2;
        }

        deltaT = t - *lastBank++;
        LgV2_B.Derivative_j = (LgV2_P.u_d_Value - *lastBank++) / deltaT;
      }
    }

    /* Product: '<S135>/Product' */
    LgV2_B.Product_kt[0] = LgV2_B.TrigonometricFunction_b * LgV2_B.Derivative_j;
    LgV2_B.Product_kt[1] = LgV2_B.TrigonometricFunction1 * LgV2_B.Derivative_j;

    /* SignalConversion: '<S63>/ConcatBufferAtVector ConcatenateIn1' */
    LgV2_B.VectorConcatenate_m[0] = LgV2_B.Product_kt[0];
    LgV2_B.VectorConcatenate_m[1] = LgV2_B.Product_kt[1];

    /* Product: '<S63>/Product1' */
    tmp = LgV2_B.u_o[0] * LgV2_B.Product_kt[0];
    tmp += LgV2_B.u_o[1] * LgV2_B.Product_kt[1];
    LgV2_B.VectorConcatenate_m[2] = tmp;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Constant: '<S69>/0_2x1' */
      LgV2_B.VectorConcatenate_c[0] = LgV2_P._2x1_Value_p[0];
      LgV2_B.VectorConcatenate_c[1] = LgV2_P._2x1_Value_p[1];
    }

    /* Math: '<S139>/epsilon_n^2' */
    tmp = LgV2_B.MultiportSelector;
    LgV2_B.epsilon_n2_cp = tmp * tmp;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S139>/Delta^2' incorporates:
       *  Constant: '<S114>/Delta'
       */
      tmp = LgV2_P.Delta_Value;
      LgV2_B.Delta2_n = tmp * tmp;
    }

    /* Sum: '<S139>/Add' */
    LgV2_B.Add_g = LgV2_B.epsilon_n2_cp + LgV2_B.Delta2_n;

    /* Math: '<S139>/sqrt' */
    tmp = LgV2_B.Add_g;
    if (tmp < 0.0) {
      LgV2_B.sqrt_n = -sqrt(-tmp);
    } else {
      LgV2_B.sqrt_n = sqrt(tmp);
    }

    /* Product: '<S139>/Divide' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Divide_f1 = LgV2_P.Delta_Value / LgV2_B.sqrt_n;

    /* Product: '<S194>/Divide' */
    LgV2_B.Divide_fp = LgV2_B.Derivative_j / LgV2_B.Add_n;

    /* Product: '<S139>/Product' */
    LgV2_B.Product_l = LgV2_B.Divide_f1 * LgV2_B.Divide_fp;

    /* Product: '<S69>/Product1' */
    LgV2_B.VectorConcatenate_c[2] = LgV2_B.Subtract_h * LgV2_B.Product_l;

    /* Sum: '<S57>/Add2' */
    LgV2_B.Add2[0] = LgV2_B.VectorConcatenate_m[0] + LgV2_B.VectorConcatenate_c
      [0];
    LgV2_B.Add2[1] = LgV2_B.VectorConcatenate_m[1] + LgV2_B.VectorConcatenate_c
      [1];
    LgV2_B.Add2[2] = LgV2_B.VectorConcatenate_m[2] + LgV2_B.VectorConcatenate_c
      [2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S57>/Product4' */
      LgV2_B.Product4[i] = 0.0;
      LgV2_B.Product4[i] = LgV2_B.MathFunction_dr[i] * LgV2_B.Add2[0] +
        LgV2_B.Product4[i];
      LgV2_B.Product4[i] = LgV2_B.MathFunction_dr[i + 3] * LgV2_B.Add2[1] +
        LgV2_B.Product4[i];
      LgV2_B.Product4[i] = LgV2_B.MathFunction_dr[i + 6] * LgV2_B.Add2[2] +
        LgV2_B.Product4[i];

      /* Sum: '<S57>/Sum' */
      LgV2_B.Sum_m[i] = (LgV2_B.Product3[i] - LgV2_B.Product2_i[i]) +
        LgV2_B.Product4[i];
    }

    /* Product: '<S40>/Product4' */
    for (i = 0; i < 3; i++) {
      LgV2_B.Product4_h[i] = 0.0;
      LgV2_B.Product4_h[i] = LgV2_B.x3_n[i] * LgV2_B.Sum_m[0] +
        LgV2_B.Product4_h[i];
      LgV2_B.Product4_h[i] = LgV2_B.x3_n[i + 3] * LgV2_B.Sum_m[1] +
        LgV2_B.Product4_h[i];
      LgV2_B.Product4_h[i] = LgV2_B.x3_n[i + 6] * LgV2_B.Sum_m[2] +
        LgV2_B.Product4_h[i];
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      for (i = 0; i < 9; i++) {
        /* Product: '<S55>/Product1' incorporates:
         *  Constant: '<S7>/kappa_1'
         *  Constant: '<S98>/Constant'
         */
        LgV2_B.Product1_h[i] = LgV2_P.kappa_1_Value * LgV2_P.Constant_Value_cf[i];

        /* Sum: '<S55>/Add' */
        LgV2_B.Add_e3[i] = LgV2_B.Rpsi_n[i] + LgV2_B.Product1_h[i];
      }
    }

    /* Concatenate: '<S125>/Matrix Concatenate' incorporates:
     *  Constant: '<S131>/Constant'
     */
    LgV2_B.MatrixConcatenate[0] = LgV2_P.Constant_Value_k[0];
    LgV2_B.MatrixConcatenate[1] = LgV2_P.Constant_Value_k[1];
    LgV2_B.MatrixConcatenate[3] = LgV2_P.Constant_Value_k[2];
    LgV2_B.MatrixConcatenate[4] = LgV2_P.Constant_Value_k[3];
    LgV2_B.MatrixConcatenate[2] = LgV2_B.u_o[0];
    LgV2_B.MatrixConcatenate[5] = LgV2_B.u_o[1];

    /* Product: '<S55>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + LgV2_B.MathFunction_dr[3 *
          tmp_6] * LgV2_B.Add_e3[i];
        tmp_2[i + 3 * tmp_6] = LgV2_B.MathFunction_dr[3 * tmp_6 + 1] *
          LgV2_B.Add_e3[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = LgV2_B.MathFunction_dr[3 * tmp_6 + 2] *
          LgV2_B.Add_e3[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 2; tmp_6++) {
        LgV2_B.Product3_j[i + 3 * tmp_6] = 0.0;
        LgV2_B.Product3_j[i + 3 * tmp_6] = LgV2_B.Product3_j[3 * tmp_6 + i] +
          LgV2_B.MatrixConcatenate[3 * tmp_6] * tmp_2[i];
        LgV2_B.Product3_j[i + 3 * tmp_6] = LgV2_B.MatrixConcatenate[3 * tmp_6 +
          1] * tmp_2[i + 3] + LgV2_B.Product3_j[3 * tmp_6 + i];
        LgV2_B.Product3_j[i + 3 * tmp_6] = LgV2_B.MatrixConcatenate[3 * tmp_6 +
          2] * tmp_2[i + 6] + LgV2_B.Product3_j[3 * tmp_6 + i];
      }
    }

    /* Trigonometry: '<S133>/Trigonometric Function1' */
    LgV2_B.TrigonometricFunction1_h = sin(LgV2_B.Gain1_o);

    /* Gain: '<S133>/Gain' */
    LgV2_B.Gain_ah = LgV2_P.Gain_Gain_e * LgV2_B.TrigonometricFunction1_h;

    /* Trigonometry: '<S133>/Trigonometric Function' */
    LgV2_B.TrigonometricFunction_n = cos(LgV2_B.Gain1_o);

    /* Product: '<S133>/Product1' */
    LgV2_B.Product1_aq[0] = LgV2_B.Gain_ah * LgV2_B.u_o[0];

    /* Product: '<S133>/Product2' */
    LgV2_B.Product2_c1[0] = LgV2_B.TrigonometricFunction_n * LgV2_B.u_o[0];

    /* Product: '<S133>/Product1' */
    LgV2_B.Product1_aq[1] = LgV2_B.Gain_ah * LgV2_B.u_o[1];

    /* Product: '<S133>/Product2' */
    LgV2_B.Product2_c1[1] = LgV2_B.TrigonometricFunction_n * LgV2_B.u_o[1];

    /* Concatenate: '<S133>/Matrix Concatenate' */
    LgV2_B.MatrixConcatenate_b[0] = LgV2_B.Product1_aq[0];
    LgV2_B.MatrixConcatenate_b[2] = LgV2_B.Product1_aq[1];
    LgV2_B.MatrixConcatenate_b[1] = LgV2_B.Product2_c1[0];
    LgV2_B.MatrixConcatenate_b[3] = LgV2_B.Product2_c1[1];

    /* Product: '<S133>/Product' incorporates:
     *  Constant: '<S197>/u_d'
     */
    LgV2_B.Product_pg[0] = LgV2_B.MatrixConcatenate_b[0] * LgV2_P.u_d_Value;
    LgV2_B.Product_pg[1] = LgV2_B.MatrixConcatenate_b[1] * LgV2_P.u_d_Value;
    LgV2_B.Product_pg[2] = LgV2_B.MatrixConcatenate_b[2] * LgV2_P.u_d_Value;
    LgV2_B.Product_pg[3] = LgV2_B.MatrixConcatenate_b[3] * LgV2_P.u_d_Value;

    /* Product: '<S149>/Product2' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product2_om = LgV2_P.Delta_Value * LgV2_B.MultiportSelector;

    /* Math: '<S64>/Math Function' */
    LgV2_B.MathFunction_j[0] = LgV2_B.Product_g5[0];

    /* Math: '<S149>/Math Function' */
    LgV2_B.MathFunction_jw[0] = LgV2_B.MultiportSelector1[0];

    /* Math: '<S64>/Math Function' */
    LgV2_B.MathFunction_j[1] = LgV2_B.Product_g5[1];

    /* Math: '<S149>/Math Function' */
    LgV2_B.MathFunction_jw[1] = LgV2_B.MultiportSelector1[1];

    /* Product: '<S149>/Product3' */
    LgV2_B.Product3_k[0] = 0.0;
    LgV2_B.Product3_k[0] = LgV2_B.MathFunction_jw[0] *
      LgV2_B.MultiportSelector1[0] + LgV2_B.Product3_k[0];
    LgV2_B.Product3_k[2] = 0.0;
    LgV2_B.Product3_k[2] = LgV2_B.MathFunction_jw[0] *
      LgV2_B.MultiportSelector1[1] + LgV2_B.Product3_k[2];
    LgV2_B.Product3_k[1] = 0.0;
    LgV2_B.Product3_k[1] = LgV2_B.MathFunction_jw[1] *
      LgV2_B.MultiportSelector1[0] + LgV2_B.Product3_k[1];
    LgV2_B.Product3_k[3] = 0.0;
    LgV2_B.Product3_k[3] = LgV2_B.MathFunction_jw[1] *
      LgV2_B.MultiportSelector1[1] + LgV2_B.Product3_k[3];

    /* Product: '<S149>/Product4' */
    LgV2_B.Product4_b[0] = LgV2_B.Product2_om * LgV2_B.Product3_k[0];

    /* Gain: '<S149>/2' */
    LgV2_B.u_c[0] = LgV2_P._Gain_l * LgV2_B.Product4_b[0];

    /* Product: '<S149>/Product4' */
    LgV2_B.Product4_b[1] = LgV2_B.Product2_om * LgV2_B.Product3_k[1];

    /* Gain: '<S149>/2' */
    LgV2_B.u_c[1] = LgV2_P._Gain_l * LgV2_B.Product4_b[1];

    /* Product: '<S149>/Product4' */
    LgV2_B.Product4_b[2] = LgV2_B.Product2_om * LgV2_B.Product3_k[2];

    /* Gain: '<S149>/2' */
    LgV2_B.u_c[2] = LgV2_P._Gain_l * LgV2_B.Product4_b[2];

    /* Product: '<S149>/Product4' */
    LgV2_B.Product4_b[3] = LgV2_B.Product2_om * LgV2_B.Product3_k[3];

    /* Gain: '<S149>/2' */
    LgV2_B.u_c[3] = LgV2_P._Gain_l * LgV2_B.Product4_b[3];
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S149>/Delta^2' incorporates:
       *  Constant: '<S114>/Delta'
       */
      tmp = LgV2_P.Delta_Value;
      LgV2_B.Delta2_p = tmp * tmp;
    }

    /* Math: '<S149>/epsilon_n^2' */
    tmp = LgV2_B.MultiportSelector;
    LgV2_B.epsilon_n2_f = tmp * tmp;

    /* Sum: '<S149>/Add' */
    LgV2_B.Add_gr = LgV2_B.Delta2_p + LgV2_B.epsilon_n2_f;

    /* Math: '<S149>/( )^2' */
    tmp = LgV2_B.Add_gr;
    LgV2_B.u_e = tmp * tmp;

    /* Product: '<S149>/Divide' */
    LgV2_B.Divide_o[0] = LgV2_B.u_c[0] / LgV2_B.u_e;
    LgV2_B.Divide_o[1] = LgV2_B.u_c[1] / LgV2_B.u_e;
    LgV2_B.Divide_o[2] = LgV2_B.u_c[2] / LgV2_B.u_e;
    LgV2_B.Divide_o[3] = LgV2_B.u_c[3] / LgV2_B.u_e;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Product: '<S149>/Product1' incorporates:
       *  Constant: '<S114>/Delta'
       *  Constant: '<S130>/0_2x2'
       */
      LgV2_B.Product1_ej[0] = LgV2_P.Delta_Value * LgV2_P._2x2_Value[0];
      LgV2_B.Product1_ej[1] = LgV2_P.Delta_Value * LgV2_P._2x2_Value[1];
      LgV2_B.Product1_ej[2] = LgV2_P.Delta_Value * LgV2_P._2x2_Value[2];
      LgV2_B.Product1_ej[3] = LgV2_P.Delta_Value * LgV2_P._2x2_Value[3];
    }

    /* Product: '<S149>/Divide1' */
    LgV2_B.Divide1[0] = LgV2_B.Product1_ej[0] / LgV2_B.Add_gr;

    /* Sum: '<S149>/Subtract' */
    LgV2_B.Subtract_di2[0] = LgV2_B.Divide_o[0] - LgV2_B.Divide1[0];

    /* Product: '<S149>/Divide1' */
    LgV2_B.Divide1[1] = LgV2_B.Product1_ej[1] / LgV2_B.Add_gr;

    /* Sum: '<S149>/Subtract' */
    LgV2_B.Subtract_di2[1] = LgV2_B.Divide_o[1] - LgV2_B.Divide1[1];

    /* Product: '<S149>/Divide1' */
    LgV2_B.Divide1[2] = LgV2_B.Product1_ej[2] / LgV2_B.Add_gr;

    /* Sum: '<S149>/Subtract' */
    LgV2_B.Subtract_di2[2] = LgV2_B.Divide_o[2] - LgV2_B.Divide1[2];

    /* Product: '<S149>/Divide1' */
    LgV2_B.Divide1[3] = LgV2_B.Product1_ej[3] / LgV2_B.Add_gr;

    /* Sum: '<S149>/Subtract' */
    LgV2_B.Subtract_di2[3] = LgV2_B.Divide_o[3] - LgV2_B.Divide1[3];

    /* Math: '<S65>/Math Function' */
    LgV2_B.MathFunction_g[0] = LgV2_B.Subtract_di2[0];
    LgV2_B.MathFunction_g[1] = LgV2_B.Subtract_di2[2];
    LgV2_B.MathFunction_g[2] = LgV2_B.Subtract_di2[1];
    LgV2_B.MathFunction_g[3] = LgV2_B.Subtract_di2[3];

    /* Product: '<S61>/Product' */
    LgV2_B.Product_nz[0] = 0.0;
    LgV2_B.Product_nz[0] = LgV2_B.MathFunction_j[0] * LgV2_B.MathFunction_g[0] +
      LgV2_B.Product_nz[0];
    LgV2_B.Product_nz[0] = LgV2_B.MathFunction_j[1] * LgV2_B.MathFunction_g[1] +
      LgV2_B.Product_nz[0];

    /* Product: '<S61>/Product1' */
    LgV2_B.Product1_my[0] = 0.0;
    LgV2_B.Product1_my[0] = LgV2_B.u_o[0] * LgV2_B.Product_pg[0] +
      LgV2_B.Product1_my[0];
    LgV2_B.Product1_my[0] = LgV2_B.u_o[1] * LgV2_B.Product_pg[1] +
      LgV2_B.Product1_my[0];

    /* Sum: '<S61>/Add' */
    LgV2_B.Add_mg[0] = LgV2_B.Product_nz[0] + LgV2_B.Product1_my[0];

    /* Product: '<S61>/Product' */
    LgV2_B.Product_nz[1] = 0.0;
    LgV2_B.Product_nz[1] = LgV2_B.MathFunction_j[0] * LgV2_B.MathFunction_g[2] +
      LgV2_B.Product_nz[1];
    LgV2_B.Product_nz[1] = LgV2_B.MathFunction_j[1] * LgV2_B.MathFunction_g[3] +
      LgV2_B.Product_nz[1];

    /* Product: '<S61>/Product1' */
    LgV2_B.Product1_my[1] = 0.0;
    LgV2_B.Product1_my[1] = LgV2_B.u_o[0] * LgV2_B.Product_pg[2] +
      LgV2_B.Product1_my[1];
    LgV2_B.Product1_my[1] = LgV2_B.u_o[1] * LgV2_B.Product_pg[3] +
      LgV2_B.Product1_my[1];

    /* Sum: '<S61>/Add' */
    LgV2_B.Add_mg[1] = LgV2_B.Product_nz[1] + LgV2_B.Product1_my[1];

    /* Concatenate: '<S61>/Matrix Concatenate' */
    LgV2_B.MatrixConcatenate_f[0] = LgV2_B.Product_pg[0];
    LgV2_B.MatrixConcatenate_f[1] = LgV2_B.Product_pg[1];
    LgV2_B.MatrixConcatenate_f[3] = LgV2_B.Product_pg[2];
    LgV2_B.MatrixConcatenate_f[4] = LgV2_B.Product_pg[3];
    LgV2_B.MatrixConcatenate_f[2] = LgV2_B.Add_mg[0];
    LgV2_B.MatrixConcatenate_f[5] = LgV2_B.Add_mg[1];

    /* Product: '<S150>/Product' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product_k3[0] = LgV2_P.Delta_Value * LgV2_B.MultiportSelector *
      LgV2_B.MultiportSelector2 * LgV2_B.MultiportSelector1[0];

    /* Gain: '<S150>/2' */
    LgV2_B.u_i[0] = LgV2_P._Gain_b * LgV2_B.Product_k3[0];

    /* Product: '<S150>/Product' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product_k3[1] = LgV2_P.Delta_Value * LgV2_B.MultiportSelector *
      LgV2_B.MultiportSelector2 * LgV2_B.MultiportSelector1[1];

    /* Gain: '<S150>/2' */
    LgV2_B.u_i[1] = LgV2_P._Gain_b * LgV2_B.Product_k3[1];
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S150>/Delta^2' incorporates:
       *  Constant: '<S114>/Delta'
       */
      tmp = LgV2_P.Delta_Value;
      LgV2_B.Delta2_o = tmp * tmp;
    }

    /* Math: '<S150>/epsilon_n^2' */
    tmp = LgV2_B.MultiportSelector;
    LgV2_B.epsilon_n2_a = tmp * tmp;

    /* Sum: '<S150>/Add' */
    LgV2_B.Add_e2 = LgV2_B.Delta2_o + LgV2_B.epsilon_n2_a;

    /* Math: '<S150>/( )^2' */
    tmp = LgV2_B.Add_e2;
    LgV2_B.u_l = tmp * tmp;

    /* Product: '<S150>/Divide' */
    LgV2_B.Divide_d[0] = LgV2_B.u_i[0] / LgV2_B.u_l;
    LgV2_B.Divide_d[1] = LgV2_B.u_i[1] / LgV2_B.u_l;

    /* Product: '<S168>/Product1' */
    for (i = 0; i < 2; i++) {
      LgV2_B.Product1_d[i] = 0.0;
      LgV2_B.Product1_d[i] = LgV2_B.MathFunction_ii[i] * LgV2_B.MathFunction_b[0]
        + LgV2_B.Product1_d[i];
      LgV2_B.Product1_d[i] = LgV2_B.MathFunction_ii[i + 2] *
        LgV2_B.MathFunction_b[1] + LgV2_B.Product1_d[i];
      LgV2_B.Product1_d[i + 2] = 0.0;
      LgV2_B.Product1_d[i + 2] = LgV2_B.Product1_d[i + 2] +
        LgV2_B.MathFunction_ii[i] * LgV2_B.MathFunction_b[2];
      LgV2_B.Product1_d[i + 2] = LgV2_B.MathFunction_ii[i + 2] *
        LgV2_B.MathFunction_b[3] + LgV2_B.Product1_d[i + 2];
    }

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S130>/Multiport Selector3' */
    {
      const byte_T *u = (byte_T *)LgV2_B.Product1_d;/* input port */
      const int32_T *index = (const int32_T *)&LgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&LgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)LgV2_B.MultiportSelector3;
      int_T ctr;

      /* Loop over each row of current output port index */
      for (ctr = 0; ctr < numRowsThisOutput; ctr++) {
        int_T inputRowIdx = *index++;
        int_T inputRowOffsetBytes;
        int_T outputRowOffsetBytes;
        int_T sampleIdx;
        inputRowOffsetBytes = inputRowIdx * sizeof(real_T);
        outputRowOffsetBytes = ctr * sizeof(real_T);

        /* Copy one sample at a time from each input column */
        for (sampleIdx = 0; sampleIdx < 2; sampleIdx++) {
          memcpy((y + (sampleIdx * bytesPerOutCol) + outputRowOffsetBytes),
                 (u + (sampleIdx * (2 * sizeof(real_T))) + inputRowOffsetBytes),
                 sizeof(real_T) );
        }
      }                                /* output row loop */
    }                                  /* end <S130>/Multiport Selector3 */

    /* Product: '<S150>/Product1' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product1_di[0] = LgV2_P.Delta_Value * LgV2_B.MultiportSelector3[0];

    /* Product: '<S150>/Divide1' */
    LgV2_B.Divide1_b[0] = LgV2_B.Product1_di[0] / LgV2_B.Add_e2;

    /* Sum: '<S150>/Subtract' */
    LgV2_B.Subtract_m[0] = LgV2_B.Divide_d[0] - LgV2_B.Divide1_b[0];

    /* Product: '<S67>/Product' */
    LgV2_B.Product_i3[0] = LgV2_B.Subtract_m[0] * LgV2_B.Subtract_l;

    /* Product: '<S137>/Product1' */
    LgV2_B.Product1_f[0] = LgV2_B.MultiportSelector * LgV2_B.MultiportSelector1
      [0];

    /* Product: '<S150>/Product1' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product1_di[1] = LgV2_P.Delta_Value * LgV2_B.MultiportSelector3[1];

    /* Product: '<S150>/Divide1' */
    LgV2_B.Divide1_b[1] = LgV2_B.Product1_di[1] / LgV2_B.Add_e2;

    /* Sum: '<S150>/Subtract' */
    LgV2_B.Subtract_m[1] = LgV2_B.Divide_d[1] - LgV2_B.Divide1_b[1];

    /* Product: '<S67>/Product' */
    LgV2_B.Product_i3[1] = LgV2_B.Subtract_m[1] * LgV2_B.Subtract_l;

    /* Product: '<S137>/Product1' */
    LgV2_B.Product1_f[1] = LgV2_B.MultiportSelector * LgV2_B.MultiportSelector1
      [1];

    /* Math: '<S137>/epsilon_n^2' */
    tmp = LgV2_B.MultiportSelector;
    LgV2_B.epsilon_n2_l = tmp * tmp;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S137>/Delta^2' incorporates:
       *  Constant: '<S114>/Delta'
       */
      tmp = LgV2_P.Delta_Value;
      LgV2_B.Delta2_g = tmp * tmp;
    }

    /* Sum: '<S137>/Add' */
    LgV2_B.Add_g3 = LgV2_B.epsilon_n2_l + LgV2_B.Delta2_g;

    /* Math: '<S137>/^3//2' incorporates:
     *  Constant: '<S137>/3//2'
     */
    if ((LgV2_B.Add_g3 < 0.0) && (LgV2_P.u_Value_id > floor(LgV2_P.u_Value_id)))
    {
      LgV2_B.u2 = -rt_pow_snf(-LgV2_B.Add_g3, LgV2_P.u_Value_id);
    } else {
      LgV2_B.u2 = rt_pow_snf(LgV2_B.Add_g3, LgV2_P.u_Value_id);
    }

    /* Product: '<S137>/Divide' */
    LgV2_B.Divide_l[0] = LgV2_B.Product1_f[0] / LgV2_B.u2;

    /* Product: '<S137>/Product' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product_ly[0] = LgV2_P.Delta_Value * LgV2_B.Divide_l[0] *
      LgV2_B.Divide;

    /* Math: '<S144>/Math Function' */
    LgV2_B.MathFunction_a[0] = LgV2_B.Add[0];

    /* Product: '<S141>/Divide' */
    LgV2_B.Divide_i[0] = LgV2_B.MathFunction_a[0] / LgV2_B.Add_n;

    /* Product: '<S141>/Product' incorporates:
     *  Constant: '<S114>/my'
     */
    LgV2_B.Product_az[0] = LgV2_P.my_Value * LgV2_B.Divide_i[0];

    /* Gain: '<S141>/Gain' */
    LgV2_B.Gain_o[0] = LgV2_P.Gain_Gain_d * LgV2_B.Product_az[0];

    /* Sum: '<S137>/Sum' */
    LgV2_B.Sum_n[0] = (0.0 - LgV2_B.Product_ly[0]) - LgV2_B.Gain_o[0];

    /* Product: '<S67>/Product1' */
    LgV2_B.Product1_oc[0] = LgV2_B.Subtract_h * LgV2_B.Sum_n[0];

    /* Sum: '<S67>/Add' */
    LgV2_B.Add_j[0] = LgV2_B.Product_i3[0] + LgV2_B.Product1_oc[0];

    /* Product: '<S137>/Divide' */
    LgV2_B.Divide_l[1] = LgV2_B.Product1_f[1] / LgV2_B.u2;

    /* Product: '<S137>/Product' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product_ly[1] = LgV2_P.Delta_Value * LgV2_B.Divide_l[1] *
      LgV2_B.Divide;

    /* Math: '<S144>/Math Function' */
    LgV2_B.MathFunction_a[1] = LgV2_B.Add[1];

    /* Product: '<S141>/Divide' */
    LgV2_B.Divide_i[1] = LgV2_B.MathFunction_a[1] / LgV2_B.Add_n;

    /* Product: '<S141>/Product' incorporates:
     *  Constant: '<S114>/my'
     */
    LgV2_B.Product_az[1] = LgV2_P.my_Value * LgV2_B.Divide_i[1];

    /* Gain: '<S141>/Gain' */
    LgV2_B.Gain_o[1] = LgV2_P.Gain_Gain_d * LgV2_B.Product_az[1];

    /* Sum: '<S137>/Sum' */
    LgV2_B.Sum_n[1] = (0.0 - LgV2_B.Product_ly[1]) - LgV2_B.Gain_o[1];

    /* Product: '<S67>/Product1' */
    LgV2_B.Product1_oc[1] = LgV2_B.Subtract_h * LgV2_B.Sum_n[1];

    /* Sum: '<S67>/Add' */
    LgV2_B.Add_j[1] = LgV2_B.Product_i3[1] + LgV2_B.Product1_oc[1];

    /* Concatenate: '<S67>/Matrix Concatenate' incorporates:
     *  Constant: '<S67>/0_2x2'
     */
    LgV2_B.MatrixConcatenate_k[0] = LgV2_P._2x2_Value_n[0];
    LgV2_B.MatrixConcatenate_k[1] = LgV2_P._2x2_Value_n[1];
    LgV2_B.MatrixConcatenate_k[3] = LgV2_P._2x2_Value_n[2];
    LgV2_B.MatrixConcatenate_k[4] = LgV2_P._2x2_Value_n[3];
    LgV2_B.MatrixConcatenate_k[2] = LgV2_B.Add_j[0];
    LgV2_B.MatrixConcatenate_k[5] = LgV2_B.Add_j[1];

    /* Sum: '<S55>/Add2' */
    for (i = 0; i < 6; i++) {
      LgV2_B.Add2_d[i] = LgV2_B.MatrixConcatenate_f[i] +
        LgV2_B.MatrixConcatenate_k[i];
    }

    /* Product: '<S55>/Product4' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 2; tmp_6++) {
        LgV2_B.Product4_g[i + 3 * tmp_6] = 0.0;
        LgV2_B.Product4_g[i + 3 * tmp_6] = LgV2_B.Product4_g[3 * tmp_6 + i] +
          LgV2_B.Add2_d[3 * tmp_6] * LgV2_B.MathFunction_dr[i];
        LgV2_B.Product4_g[i + 3 * tmp_6] = LgV2_B.Add2_d[3 * tmp_6 + 1] *
          LgV2_B.MathFunction_dr[i + 3] + LgV2_B.Product4_g[3 * tmp_6 + i];
        LgV2_B.Product4_g[i + 3 * tmp_6] = LgV2_B.Add2_d[3 * tmp_6 + 2] *
          LgV2_B.MathFunction_dr[i + 6] + LgV2_B.Product4_g[3 * tmp_6 + i];
      }
    }

    /* Sum: '<S55>/Add3' */
    for (i = 0; i < 6; i++) {
      LgV2_B.Add3_m[i] = LgV2_B.Product3_j[i] + LgV2_B.Product4_g[i];
    }

    /* Integrator: '<S52>/Integrator2' */
    LgV2_B.Integrator2[0] = LgV2_X.Integrator2_CSTATE[0];

    /* Sum: '<S40>/Add2' */
    LgV2_B.Add2_m[0] = LgV2_B.Integrator2[0] + LgV2_B.Product_g5[0];

    /* Integrator: '<S52>/Integrator2' */
    LgV2_B.Integrator2[1] = LgV2_X.Integrator2_CSTATE[1];

    /* Sum: '<S40>/Add2' */
    LgV2_B.Add2_m[1] = LgV2_B.Integrator2[1] + LgV2_B.Product_g5[1];

    /* Product: '<S40>/Product5' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 2; tmp_6++) {
        tmp_4[i + 3 * tmp_6] = 0.0;
        tmp_4[i + 3 * tmp_6] = tmp_4[3 * tmp_6 + i] + LgV2_B.Add3_m[3 * tmp_6] *
          LgV2_B.x3_n[i];
        tmp_4[i + 3 * tmp_6] = LgV2_B.Add3_m[3 * tmp_6 + 1] * LgV2_B.x3_n[i + 3]
          + tmp_4[3 * tmp_6 + i];
        tmp_4[i + 3 * tmp_6] = LgV2_B.Add3_m[3 * tmp_6 + 2] * LgV2_B.x3_n[i + 6]
          + tmp_4[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      LgV2_B.Product5[i] = 0.0;
      LgV2_B.Product5[i] = tmp_4[i] * LgV2_B.Add2_m[0] + LgV2_B.Product5[i];
      LgV2_B.Product5[i] = tmp_4[i + 3] * LgV2_B.Add2_m[1] + LgV2_B.Product5[i];
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      for (i = 0; i < 9; i++) {
        /* Product: '<S56>/Product1' incorporates:
         *  Constant: '<S7>/kappa_1'
         *  Constant: '<S99>/Constant'
         */
        LgV2_B.Product1_b[i] = LgV2_P.kappa_1_Value * LgV2_P.Constant_Value_bk[i];

        /* Sum: '<S56>/Add1' */
        LgV2_B.Add1_o3[i] = LgV2_B.Rpsi_n[i] + LgV2_B.Product1_b[i];
      }

      /* Constant: '<S125>/0_2x1' */
      LgV2_B.VectorConcatenate1[0] = LgV2_P._2x1_Value_j[0];
      LgV2_B.VectorConcatenate1[1] = LgV2_P._2x1_Value_j[1];
    }

    /* SignalConversion: '<S125>/ConcatBufferAtVector Concatenate1In2' */
    LgV2_B.VectorConcatenate1[2] = LgV2_B.Subtract_h;

    /* Product: '<S56>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + LgV2_B.MathFunction_dr[3 *
          tmp_6] * LgV2_B.Add1_o3[i];
        tmp_2[i + 3 * tmp_6] = LgV2_B.MathFunction_dr[3 * tmp_6 + 1] *
          LgV2_B.Add1_o3[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = LgV2_B.MathFunction_dr[3 * tmp_6 + 2] *
          LgV2_B.Add1_o3[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      LgV2_B.Product3_d[i] = 0.0;
      LgV2_B.Product3_d[i] = tmp_2[i] * LgV2_B.VectorConcatenate1[0] +
        LgV2_B.Product3_d[i];
      LgV2_B.Product3_d[i] = tmp_2[i + 3] * LgV2_B.VectorConcatenate1[1] +
        LgV2_B.Product3_d[i];
      LgV2_B.Product3_d[i] = tmp_2[i + 6] * LgV2_B.VectorConcatenate1[2] +
        LgV2_B.Product3_d[i];
    }

    /* Trigonometry: '<S134>/Trigonometric Function1' */
    LgV2_B.TrigonometricFunction1_i = sin(LgV2_B.Gain1_o);

    /* Gain: '<S134>/Gain' */
    LgV2_B.Gain_f = LgV2_P.Gain_Gain_dz * LgV2_B.TrigonometricFunction1_i;

    /* Product: '<S134>/Product1' */
    LgV2_B.Product1_jn = LgV2_B.Gain_f * LgV2_B.Subtract_h;

    /* Trigonometry: '<S134>/Trigonometric Function' */
    LgV2_B.TrigonometricFunction_i = cos(LgV2_B.Gain1_o);

    /* Product: '<S134>/Product2' */
    LgV2_B.Product2_n = LgV2_B.TrigonometricFunction_i * LgV2_B.Subtract_h;

    /* SignalConversion: '<S134>/TmpHiddenBufferAtProductInport1' */
    LgV2_B.TmpHiddenBufferAtProductInpor_i[0] = LgV2_B.Product1_jn;
    LgV2_B.TmpHiddenBufferAtProductInpor_i[1] = LgV2_B.Product2_n;

    /* Product: '<S134>/Product' incorporates:
     *  Constant: '<S197>/u_d'
     */
    LgV2_B.Product_nxy[0] = LgV2_B.TmpHiddenBufferAtProductInpor_i[0] *
      LgV2_P.u_d_Value;
    LgV2_B.Product_nxy[1] = LgV2_B.TmpHiddenBufferAtProductInpor_i[1] *
      LgV2_P.u_d_Value;

    /* SignalConversion: '<S62>/ConcatBufferAtVector ConcatenateIn1' */
    LgV2_B.VectorConcatenate_f[0] = LgV2_B.Product_nxy[0];
    LgV2_B.VectorConcatenate_f[1] = LgV2_B.Product_nxy[1];

    /* Product: '<S62>/Product' */
    tmp = LgV2_B.Subtract_m[0] * LgV2_B.Product_g5[0];
    tmp += LgV2_B.Subtract_m[1] * LgV2_B.Product_g5[1];
    LgV2_B.Product_in = tmp;

    /* Product: '<S62>/Product1' */
    tmp = LgV2_B.u_o[0] * LgV2_B.Product_nxy[0];
    tmp += LgV2_B.u_o[1] * LgV2_B.Product_nxy[1];
    LgV2_B.Product1_nf = tmp;

    /* Sum: '<S62>/Add' */
    LgV2_B.VectorConcatenate_f[2] = LgV2_B.Product_in + LgV2_B.Product1_nf;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Constant: '<S68>/0_2x1' */
      LgV2_B.VectorConcatenate_p[0] = LgV2_P._2x1_Value_jo[0];
      LgV2_B.VectorConcatenate_p[1] = LgV2_P._2x1_Value_jo[1];

      /* Product: '<S183>/Product' incorporates:
       *  Constant: '<S117>/Path Selector'
       *  Constant: '<S173>/0_2x1'
       */
      LgV2_B.Product_h[0] = LgV2_P._2x1_Value_n * LgV2_P.PathSelector_Value;
      LgV2_B.Product_h[1] = LgV2_P._2x1_Value_n * LgV2_P.PathSelector_Value;
    }

    /* Product: '<S177>/Product2' incorporates:
     *  Constant: '<S197>/k'
     */
    LgV2_B.Product2_f = LgV2_B.Integrator1 * LgV2_P.k_Value;

    /* Trigonometry: '<S177>/cos(s)' */
    LgV2_B.coss_g = cos(LgV2_B.Product2_f);
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S177>/Math Function' incorporates:
       *  Constant: '<S197>/k'
       */
      tmp = LgV2_P.k_Value;
      LgV2_B.MathFunction_b4 = tmp * tmp;
    }

    /* Product: '<S177>/Product' incorporates:
     *  Constant: '<S197>/r_x'
     */
    LgV2_B.Product_mj = LgV2_P.r_x_Value * LgV2_B.coss_g *
      LgV2_B.MathFunction_b4;

    /* Gain: '<S177>/Gain' */
    LgV2_B.Gain_hu = LgV2_P.Gain_Gain_nx * LgV2_B.Product_mj;

    /* Trigonometry: '<S177>/sin(s)' */
    LgV2_B.sins_f = sin(LgV2_B.Product2_f);

    /* Product: '<S177>/Product1' incorporates:
     *  Constant: '<S197>/r_y'
     */
    LgV2_B.Product1_ok = LgV2_P.r_y_Value * LgV2_B.sins_f *
      LgV2_B.MathFunction_b4;

    /* Gain: '<S177>/Gain1' */
    LgV2_B.Gain1_o2 = LgV2_P.Gain1_Gain_p * LgV2_B.Product1_ok;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Sum: '<S183>/Subtract' incorporates:
       *  Constant: '<S117>/Path Selector'
       *  Constant: '<S183>/Constant'
       */
      LgV2_B.Subtract_en = LgV2_P.Constant_Value_pj - LgV2_P.PathSelector_Value;
    }

    /* Product: '<S183>/Product1' */
    LgV2_B.Product1_l[0] = LgV2_B.Gain_hu * LgV2_B.Subtract_en;
    LgV2_B.Product1_l[1] = LgV2_B.Gain1_o2 * LgV2_B.Subtract_en;

    /* Sum: '<S183>/Add' */
    LgV2_B.Add_b[0] = LgV2_B.Product_h[0] + LgV2_B.Product1_l[0];
    LgV2_B.Add_b[1] = LgV2_B.Product_h[1] + LgV2_B.Product1_l[1];

    /* Product: '<S121>/x_d^s * y_d^s^3 ' */
    LgV2_B.x_dsy_ds3 = LgV2_B.Add[0] * LgV2_B.Add_b[1];

    /* Product: '<S121>/x_d^s^3 * y_d^s' */
    LgV2_B.x_ds3y_ds = LgV2_B.Add_b[0] * LgV2_B.Add[1];

    /* Sum: '<S121>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
    LgV2_B.x_dsy_ds3x_ds3y_ds = LgV2_B.x_dsy_ds3 - LgV2_B.x_ds3y_ds;

    /* Product: '<S121>/Product1' */
    LgV2_B.Product1_a3 = LgV2_B.x_dsy_ds3x_ds3y_ds * LgV2_B.x_ds2y_ds2;

    /* Product: '<S121>/x_d^s * x_d^s^2' */
    LgV2_B.x_dsx_ds2 = LgV2_B.Add[0] * LgV2_B.Add_mw[0];

    /* Product: '<S121>/y_d^s * y_d^s^2' */
    LgV2_B.y_dsy_ds2 = LgV2_B.Add[1] * LgV2_B.Add_mw[1];

    /* Sum: '<S121>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
    LgV2_B.x_dsx_ds2x_ds3y_ds = LgV2_B.x_dsx_ds2 + LgV2_B.y_dsy_ds2;

    /* Gain: '<S121>/+ 2' */
    LgV2_B.u_m = LgV2_P.u_Gain_m * LgV2_B.x_dsx_ds2x_ds3y_ds;

    /* Product: '<S121>/Product2' */
    LgV2_B.Product2_i5 = LgV2_B.x_dsy_ds2x_ds2y_ds * LgV2_B.u_m;

    /* Sum: '<S121>/Subtract' */
    LgV2_B.Subtract_n = LgV2_B.Product1_a3 - LgV2_B.Product2_i5;

    /* Math: '<S121>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
    tmp = LgV2_B.x_ds2y_ds2;
    LgV2_B.x_ds2y_ds22 = tmp * tmp;

    /* Product: '<S121>/Divide' */
    LgV2_B.Divide_kj = LgV2_B.Subtract_n / LgV2_B.x_ds2y_ds22;

    /* Math: '<S152>/(epsilon_n^s)^2' */
    tmp = LgV2_B.MultiportSelector2;
    LgV2_B.epsilon_ns2 = tmp * tmp;

    /* Product: '<S152>/Product' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product_j = LgV2_P.Delta_Value * LgV2_B.MultiportSelector *
      LgV2_B.epsilon_ns2;

    /* Gain: '<S152>/2' */
    LgV2_B.u_d = LgV2_P._Gain_p * LgV2_B.Product_j;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S152>/Delta^2' incorporates:
       *  Constant: '<S114>/Delta'
       */
      tmp = LgV2_P.Delta_Value;
      LgV2_B.Delta2_oj = tmp * tmp;
    }

    /* Math: '<S152>/epsilon_n^2' */
    tmp = LgV2_B.MultiportSelector;
    LgV2_B.epsilon_n2_b = tmp * tmp;

    /* Sum: '<S152>/Add' */
    LgV2_B.Add_k = LgV2_B.Delta2_oj + LgV2_B.epsilon_n2_b;

    /* Math: '<S152>/( )^2' */
    tmp = LgV2_B.Add_k;
    LgV2_B.u_p = tmp * tmp;

    /* Product: '<S152>/Divide' */
    LgV2_B.Divide_p = LgV2_B.u_d / LgV2_B.u_p;

    /* Outputs for atomic SubSystem: '<S130>/S_2(psi_d^s^2)' */

    /* Gain: '<S165>/S12' */
    LgV2_B.S12_o = LgV2_P.S12_Gain_f * LgV2_B.Divide_kj;

    /* Reshape: '<S165>/S_2(psi_d^s^2)' incorporates:
     *  Constant: '<S165>/0'
     */
    LgV2_B.S_2psi_ds2[0] = LgV2_P._Value_h;
    LgV2_B.S_2psi_ds2[1] = LgV2_B.Divide_kj;
    LgV2_B.S_2psi_ds2[2] = LgV2_B.S12_o;
    LgV2_B.S_2psi_ds2[3] = LgV2_P._Value_h;

    /* end of Outputs for SubSystem: '<S130>/S_2(psi_d^s^2)' */

    /* Math: '<S166>/Math Function' */
    LgV2_B.MathFunction_m[0] = LgV2_B.S_2psi_ds2[0];
    LgV2_B.MathFunction_m[1] = LgV2_B.S_2psi_ds2[2];
    LgV2_B.MathFunction_m[2] = LgV2_B.S_2psi_ds2[1];
    LgV2_B.MathFunction_m[3] = LgV2_B.S_2psi_ds2[3];

    /* Product: '<S170>/Product' */
    for (i = 0; i < 2; i++) {
      LgV2_B.Product_f[i] = 0.0;
      LgV2_B.Product_f[i] = LgV2_B.MathFunction_ii[i] * LgV2_B.MathFunction_ii[0]
        + LgV2_B.Product_f[i];
      LgV2_B.Product_f[i] = LgV2_B.MathFunction_ii[i + 2] *
        LgV2_B.MathFunction_ii[1] + LgV2_B.Product_f[i];
      LgV2_B.Product_f[i + 2] = 0.0;
      LgV2_B.Product_f[i + 2] = LgV2_B.Product_f[i + 2] +
        LgV2_B.MathFunction_ii[i] * LgV2_B.MathFunction_ii[2];
      LgV2_B.Product_f[i + 2] = LgV2_B.MathFunction_ii[i + 2] *
        LgV2_B.MathFunction_ii[3] + LgV2_B.Product_f[i + 2];
    }

    /* Sum: '<S170>/Add' */
    LgV2_B.Add_i[0] = LgV2_B.MathFunction_m[0] + LgV2_B.Product_f[0];
    LgV2_B.Add_i[1] = LgV2_B.MathFunction_m[1] + LgV2_B.Product_f[1];
    LgV2_B.Add_i[2] = LgV2_B.MathFunction_m[2] + LgV2_B.Product_f[2];
    LgV2_B.Add_i[3] = LgV2_B.MathFunction_m[3] + LgV2_B.Product_f[3];

    /* Product: '<S170>/Product1' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += LgV2_B.Add_i[i] * LgV2_B.MathFunction_b[0];
      tmp_3[i] += LgV2_B.Add_i[i + 2] * LgV2_B.MathFunction_b[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += LgV2_B.Add_i[i] * LgV2_B.MathFunction_b[2];
      tmp_3[i + 2] += LgV2_B.Add_i[i + 2] * LgV2_B.MathFunction_b[3];
    }

    LgV2_B.Product1_co[0] = 0.0;
    LgV2_B.Product1_co[0] = tmp_3[0] * LgV2_B.qp_d[0] + LgV2_B.Product1_co[0];
    LgV2_B.Product1_co[0] = tmp_3[2] * LgV2_B.qp_d[1] + LgV2_B.Product1_co[0];
    LgV2_B.Product1_co[1] = 0.0;
    LgV2_B.Product1_co[1] = tmp_3[1] * LgV2_B.qp_d[0] + LgV2_B.Product1_co[1];
    LgV2_B.Product1_co[1] = tmp_3[3] * LgV2_B.qp_d[1] + LgV2_B.Product1_co[1];

    /* Product: '<S170>/Product2' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += LgV2_B.MathFunction_ii[i] * LgV2_B.MathFunction_b[0];
      tmp_3[i] += LgV2_B.MathFunction_ii[i + 2] * LgV2_B.MathFunction_b[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += LgV2_B.MathFunction_ii[i] * LgV2_B.MathFunction_b[2];
      tmp_3[i + 2] += LgV2_B.MathFunction_ii[i + 2] * LgV2_B.MathFunction_b[3];
    }

    LgV2_B.Product2_px[0] = 0.0;
    LgV2_B.Product2_px[0] = tmp_3[0] * LgV2_B.Add[0] + LgV2_B.Product2_px[0];
    LgV2_B.Product2_px[0] = tmp_3[2] * LgV2_B.Add[1] + LgV2_B.Product2_px[0];

    /* Gain: '<S170>/2' */
    LgV2_B.u_mr[0] = LgV2_P._Gain_a * LgV2_B.Product2_px[0];

    /* Product: '<S170>/Product3' */
    LgV2_B.Product3_c[0] = 0.0;
    LgV2_B.Product3_c[0] = LgV2_B.MathFunction_b[0] * LgV2_B.Add_mw[0] +
      LgV2_B.Product3_c[0];
    LgV2_B.Product3_c[0] = LgV2_B.MathFunction_b[2] * LgV2_B.Add_mw[1] +
      LgV2_B.Product3_c[0];

    /* Sum: '<S170>/Sum' */
    LgV2_B.Sum_pn[0] = (LgV2_B.Product1_co[0] - LgV2_B.u_mr[0]) -
      LgV2_B.Product3_c[0];

    /* Gain: '<S170>/Gain' */
    LgV2_B.Gain_dg[0] = LgV2_P.Gain_Gain_eq * LgV2_B.Sum_pn[0];
    LgV2_B.Product2_px[1] = 0.0;
    LgV2_B.Product2_px[1] = tmp_3[1] * LgV2_B.Add[0] + LgV2_B.Product2_px[1];
    LgV2_B.Product2_px[1] = tmp_3[3] * LgV2_B.Add[1] + LgV2_B.Product2_px[1];

    /* Gain: '<S170>/2' */
    LgV2_B.u_mr[1] = LgV2_P._Gain_a * LgV2_B.Product2_px[1];

    /* Product: '<S170>/Product3' */
    LgV2_B.Product3_c[1] = 0.0;
    LgV2_B.Product3_c[1] = LgV2_B.MathFunction_b[1] * LgV2_B.Add_mw[0] +
      LgV2_B.Product3_c[1];
    LgV2_B.Product3_c[1] = LgV2_B.MathFunction_b[3] * LgV2_B.Add_mw[1] +
      LgV2_B.Product3_c[1];

    /* Sum: '<S170>/Sum' */
    LgV2_B.Sum_pn[1] = (LgV2_B.Product1_co[1] - LgV2_B.u_mr[1]) -
      LgV2_B.Product3_c[1];

    /* Gain: '<S170>/Gain' */
    LgV2_B.Gain_dg[1] = LgV2_P.Gain_Gain_eq * LgV2_B.Sum_pn[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S130>/Multiport Selector4' */
    {
      const byte_T *u = (byte_T *)LgV2_B.Gain_dg;/* input port */
      const int32_T *index = (const int32_T *)&LgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&LgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&LgV2_B.MultiportSelector4;
      int_T ctr;

      /* Loop over each row of current output port index */
      for (ctr = 0; ctr < numRowsThisOutput; ctr++) {
        int_T inputRowIdx = *index++;
        int_T inputRowOffsetBytes;
        int_T outputRowOffsetBytes;
        int_T sampleIdx;
        inputRowOffsetBytes = inputRowIdx * sizeof(real_T);
        outputRowOffsetBytes = ctr * sizeof(real_T);

        /* Copy one sample at a time from each input column */
        for (sampleIdx = 0; sampleIdx < 1; sampleIdx++) {
          memcpy((y + (sampleIdx * bytesPerOutCol) + outputRowOffsetBytes),
                 (u + (sampleIdx * (2 * sizeof(real_T))) + inputRowOffsetBytes),
                 sizeof(real_T) );
        }
      }                                /* output row loop */
    }                                  /* end <S130>/Multiport Selector4 */

    /* Product: '<S152>/Product1' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product1_ns = LgV2_P.Delta_Value * LgV2_B.MultiportSelector4;

    /* Product: '<S152>/Divide1' */
    LgV2_B.Divide1_p = LgV2_B.Product1_ns / LgV2_B.Add_k;

    /* Sum: '<S152>/Sum' */
    LgV2_B.Sum_f = (LgV2_B.Divide_kj + LgV2_B.Divide_p) - LgV2_B.Divide1_p;

    /* Product: '<S68>/Product' */
    LgV2_B.Product_cc = LgV2_B.Sum_f * LgV2_B.Subtract_l;

    /* Math: '<S195>/Math Function' */
    LgV2_B.MathFunction_lq[0] = LgV2_B.Add[0];
    LgV2_B.MathFunction_lq[1] = LgV2_B.Add[1];

    /* Product: '<S193>/Product1' */
    tmp = LgV2_B.MathFunction_lq[0] * LgV2_B.Add_mw[0];
    tmp += LgV2_B.MathFunction_lq[1] * LgV2_B.Add_mw[1];
    LgV2_B.Product1_jd = tmp;

    /* Math: '<S193>/|p_d^s|^3' incorporates:
     *  Constant: '<S193>/Constant'
     */
    if ((LgV2_B.Add_n < 0.0) && (LgV2_P.Constant_Value_c5 > floor
         (LgV2_P.Constant_Value_c5))) {
      LgV2_B.p_ds3 = -rt_pow_snf(-LgV2_B.Add_n, LgV2_P.Constant_Value_c5);
    } else {
      LgV2_B.p_ds3 = rt_pow_snf(LgV2_B.Add_n, LgV2_P.Constant_Value_c5);
    }

    /* Product: '<S193>/Divide' */
    LgV2_B.Divide_iy = LgV2_B.Product1_jd / LgV2_B.p_ds3;

    /* Product: '<S193>/Product' incorporates:
     *  Constant: '<S197>/u_d'
     */
    LgV2_B.Product_bn = LgV2_B.Divide_iy * LgV2_P.u_d_Value;

    /* Gain: '<S193>/Gain' */
    LgV2_B.Gain_e = LgV2_P.Gain_Gain_af * LgV2_B.Product_bn;

    /* Math: '<S138>/epsilon_n^2' */
    tmp = LgV2_B.MultiportSelector;
    LgV2_B.epsilon_n2_cs = tmp * tmp;
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Math: '<S138>/Delta^2' incorporates:
       *  Constant: '<S114>/Delta'
       */
      tmp = LgV2_P.Delta_Value;
      LgV2_B.Delta2_i = tmp * tmp;
    }

    /* Sum: '<S138>/Add' */
    LgV2_B.Add_es = LgV2_B.epsilon_n2_cs + LgV2_B.Delta2_i;

    /* Math: '<S138>/Math Function' */
    tmp = LgV2_B.Add_es;
    if (tmp < 0.0) {
      LgV2_B.MathFunction_jo = -sqrt(-tmp);
    } else {
      LgV2_B.MathFunction_jo = sqrt(tmp);
    }

    /* Product: '<S138>/Divide' */
    LgV2_B.Divide_j = LgV2_B.Gain_e / LgV2_B.MathFunction_jo;

    /* Product: '<S138>/Product1' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product1_es = LgV2_P.Delta_Value * LgV2_B.Divide_j;

    /* Product: '<S138>/Product2' */
    LgV2_B.Product2_h = LgV2_B.MultiportSelector * LgV2_B.MultiportSelector2;

    /* Math: '<S138>/^3//2' incorporates:
     *  Constant: '<S138>/3//2'
     */
    if ((LgV2_B.Add_es < 0.0) && (LgV2_P.u_Value_jc > floor(LgV2_P.u_Value_jc)))
    {
      LgV2_B.u2_b = -rt_pow_snf(-LgV2_B.Add_es, LgV2_P.u_Value_jc);
    } else {
      LgV2_B.u2_b = rt_pow_snf(LgV2_B.Add_es, LgV2_P.u_Value_jc);
    }

    /* Product: '<S138>/Divide1' */
    LgV2_B.Divide1_d = LgV2_B.Product2_h / LgV2_B.u2_b;

    /* Product: '<S138>/Product3' incorporates:
     *  Constant: '<S114>/Delta'
     */
    LgV2_B.Product3_a = LgV2_P.Delta_Value * LgV2_B.Divide1_d * LgV2_B.Divide;

    /* Product: '<S142>/Product1' incorporates:
     *  Constant: '<S114>/my'
     */
    LgV2_B.Product1_en = LgV2_P.my_Value * LgV2_B.Add_n;

    /* Math: '<S146>/Math Function' */
    LgV2_B.MathFunction_c[0] = LgV2_B.Add_mw[0];

    /* Product: '<S142>/Divide2' */
    LgV2_B.Divide2[0] = LgV2_B.MathFunction_c[0] / LgV2_B.Add_n;

    /* Math: '<S145>/Math Function' */
    LgV2_B.MathFunction_cc[0] = LgV2_B.Add[0];

    /* Math: '<S146>/Math Function' */
    LgV2_B.MathFunction_c[1] = LgV2_B.Add_mw[1];

    /* Product: '<S142>/Divide2' */
    LgV2_B.Divide2[1] = LgV2_B.MathFunction_c[1] / LgV2_B.Add_n;

    /* Math: '<S145>/Math Function' */
    LgV2_B.MathFunction_cc[1] = LgV2_B.Add[1];

    /* Product: '<S142>/Product2' */
    tmp = LgV2_B.MathFunction_c[0] * LgV2_B.Add[0];
    tmp += LgV2_B.MathFunction_c[1] * LgV2_B.Add[1];
    LgV2_B.Product2_im[0] = tmp * LgV2_B.MathFunction_cc[0];
    LgV2_B.Product2_im[1] = tmp * LgV2_B.MathFunction_cc[1];

    /* Math: '<S142>/Math Function' incorporates:
     *  Constant: '<S142>/Constant'
     */
    if ((LgV2_B.Add_n < 0.0) && (LgV2_P.Constant_Value_dc > floor
         (LgV2_P.Constant_Value_dc))) {
      LgV2_B.MathFunction_ak = -rt_pow_snf(-LgV2_B.Add_n,
        LgV2_P.Constant_Value_dc);
    } else {
      LgV2_B.MathFunction_ak = rt_pow_snf(LgV2_B.Add_n, LgV2_P.Constant_Value_dc);
    }

    /* Product: '<S142>/Divide1' */
    LgV2_B.Divide1_be[0] = LgV2_B.Product2_im[0] / LgV2_B.MathFunction_ak;

    /* Sum: '<S142>/Subtract1' */
    LgV2_B.Subtract1_c[0] = LgV2_B.Divide2[0] - LgV2_B.Divide1_be[0];

    /* Product: '<S142>/Divide1' */
    LgV2_B.Divide1_be[1] = LgV2_B.Product2_im[1] / LgV2_B.MathFunction_ak;

    /* Sum: '<S142>/Subtract1' */
    LgV2_B.Subtract1_c[1] = LgV2_B.Divide2[1] - LgV2_B.Divide1_be[1];

    /* Product: '<S142>/Product' incorporates:
     *  Constant: '<S114>/my'
     */
    tmp = LgV2_P.my_Value * LgV2_B.Subtract1_c[0] * LgV2_B.Subtract_e[0];
    tmp += LgV2_P.my_Value * LgV2_B.Subtract1_c[1] * LgV2_B.Subtract_e[1];
    LgV2_B.Product_of = tmp;

    /* Sum: '<S142>/Subtract' */
    LgV2_B.Subtract_nq = LgV2_B.Product1_en - LgV2_B.Product_of;

    /* Sum: '<S138>/Sum' */
    LgV2_B.Sum_oq = (LgV2_B.Product1_es - LgV2_B.Product3_a) -
      LgV2_B.Subtract_nq;

    /* Product: '<S68>/Product1' */
    LgV2_B.Product1_o2 = LgV2_B.Subtract_h * LgV2_B.Sum_oq;

    /* Sum: '<S68>/Add' */
    LgV2_B.VectorConcatenate_p[2] = LgV2_B.Product_cc + LgV2_B.Product1_o2;

    /* Sum: '<S56>/Add2' */
    LgV2_B.Add2_e[0] = LgV2_B.VectorConcatenate_f[0] +
      LgV2_B.VectorConcatenate_p[0];
    LgV2_B.Add2_e[1] = LgV2_B.VectorConcatenate_f[1] +
      LgV2_B.VectorConcatenate_p[1];
    LgV2_B.Add2_e[2] = LgV2_B.VectorConcatenate_f[2] +
      LgV2_B.VectorConcatenate_p[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S56>/Product4' */
      LgV2_B.Product4_a[i] = 0.0;
      LgV2_B.Product4_a[i] = LgV2_B.MathFunction_dr[i] * LgV2_B.Add2_e[0] +
        LgV2_B.Product4_a[i];
      LgV2_B.Product4_a[i] = LgV2_B.MathFunction_dr[i + 3] * LgV2_B.Add2_e[1] +
        LgV2_B.Product4_a[i];
      LgV2_B.Product4_a[i] = LgV2_B.MathFunction_dr[i + 6] * LgV2_B.Add2_e[2] +
        LgV2_B.Product4_a[i];

      /* Sum: '<S56>/Add3' */
      LgV2_B.Add3_l[i] = LgV2_B.Product3_d[i] + LgV2_B.Product4_a[i];
    }

    for (i = 0; i < 3; i++) {
      tmp_5[i] = 0.0;
      tmp = tmp_5[i];
      tmp += LgV2_B.x3_n[i] * LgV2_B.Add3_l[0];
      tmp_5[i] = tmp;
      tmp = tmp_5[i];
      tmp += LgV2_B.x3_n[i + 3] * LgV2_B.Add3_l[1];
      tmp_5[i] = tmp;
      tmp = tmp_5[i];
      tmp += LgV2_B.x3_n[i + 6] * LgV2_B.Add3_l[2];
      tmp_5[i] = tmp;
      LgV2_B.Product6[i] = tmp_5[i] * LgV2_B.Subtract_l;

      /* Sum: '<S40>/Sum' */
      LgV2_B.Sum_gc[i] = ((((LgV2_B.Product2_o[i] - LgV2_B.Product_c[i]) -
                            LgV2_B.Product1_a[i]) + LgV2_B.Product4_h[i]) +
                          LgV2_B.Product5[i]) + LgV2_B.Product6[i];
    }

    /* Product: '<S72>/Product' */
    for (i = 0; i < 5; i++) {
      LgV2_B.Product_cl[i] = 0.0;
      LgV2_B.Product_cl[i] = LgV2_B.Pseudoinverse_j[i] * LgV2_B.Sum_gc[0] +
        LgV2_B.Product_cl[i];
      LgV2_B.Product_cl[i] = LgV2_B.Pseudoinverse_j[i + 5] * LgV2_B.Sum_gc[1] +
        LgV2_B.Product_cl[i];
      LgV2_B.Product_cl[i] = LgV2_B.Pseudoinverse_j[i + 10] * LgV2_B.Sum_gc[2] +
        LgV2_B.Product_cl[i];
    }

    /* DeadZone Block: '<S73>/Dead Zone'
     */
    if (LgV2_B.Product_cl[0] >= LgV2_P.DeadZone_End_jo) {
      LgV2_B.DeadZone_h = LgV2_B.Product_cl[0] - LgV2_P.DeadZone_End_jo;
    } else if (LgV2_B.Product_cl[0] > LgV2_P.DeadZone_Start_b) {
      LgV2_B.DeadZone_h = 0.0;
    } else {
      LgV2_B.DeadZone_h = LgV2_B.Product_cl[0] - LgV2_P.DeadZone_Start_b;
    }

    /* RelationalOperator: '<S78>/Compare' incorporates:
     *  Constant: '<S78>/Constant'
     */
    LgV2_B.Compare_en = (LgV2_B.DeadZone_h < LgV2_P.Constant_Value_jz);

    /* RelationalOperator: '<S80>/Compare' */
    LgV2_B.Compare_p1 = (LgV2_B.DeadZone_h == 0.0);

    /* Gain: '<S73>/Gain' */
    LgV2_B.Gain_ji = (uint16_T)(LgV2_P.Gain_Gain_i * LgV2_B.Compare_p1);

    /* RelationalOperator: '<S79>/Compare' incorporates:
     *  Constant: '<S79>/Constant'
     */
    LgV2_B.Compare_f = (LgV2_B.DeadZone_h > LgV2_P.Constant_Value_gp);

    /* Gain: '<S73>/Gain1' */
    LgV2_B.Gain1_ld = (uint16_T)(LgV2_P.Gain1_Gain_j * LgV2_B.Compare_f);

    /* Sum: '<S73>/Sum' */
    LgV2_B.Sum_gp = (uint16_T)(uint32_T)(((LgV2_B.Compare_en << 6) +
      LgV2_B.Gain_ji) + LgV2_B.Gain1_ld);

    /* Lookup Block: '<S73>/f_1 < 0'
     * About '<S73>/f_1 < 0 :'
     * Lookup Block: '<S73>/f_1 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_10_c), LgV2_P.f_10_YData_b,
                         LgV2_B.Product_cl[0], LgV2_P.f_10_XData_n, 8U);

    /* Lookup Block: '<S73>/f_1 > 0'
     * About '<S73>/f_1 > 0 :'
     * Lookup Block: '<S73>/f_1 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_10_i), LgV2_P.f_10_YData_d,
                         LgV2_B.Product_cl[0], LgV2_P.f_10_XData_k, 9U);

    /* MultiPortSwitch: '<S73>/Multiport Switch' incorporates:
     *  Constant: '<S73>/f_1 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_gp >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch_j = LgV2_B.f_10_c;
      break;

     case 2:
      LgV2_B.MultiportSwitch_j = LgV2_P.f_10_Value_i;
      break;

     default:
      LgV2_B.MultiportSwitch_j = LgV2_B.f_10_i;
      break;
    }

    /* DeadZone Block: '<S74>/Dead Zone'
     */
    if (LgV2_B.Product_cl[1] >= LgV2_P.DeadZone_End_p) {
      LgV2_B.DeadZone_g1 = LgV2_B.Product_cl[1] - LgV2_P.DeadZone_End_p;
    } else if (LgV2_B.Product_cl[1] > LgV2_P.DeadZone_Start_g) {
      LgV2_B.DeadZone_g1 = 0.0;
    } else {
      LgV2_B.DeadZone_g1 = LgV2_B.Product_cl[1] - LgV2_P.DeadZone_Start_g;
    }

    /* RelationalOperator: '<S81>/Compare' incorporates:
     *  Constant: '<S81>/Constant'
     */
    LgV2_B.Compare_em = (LgV2_B.DeadZone_g1 < LgV2_P.Constant_Value_cv);

    /* RelationalOperator: '<S82>/Compare' incorporates:
     *  Constant: '<S82>/Constant'
     */
    LgV2_B.Compare_ib = (LgV2_B.DeadZone_g1 == LgV2_P.Constant_Value_ow);

    /* Gain: '<S74>/Gain' */
    LgV2_B.Gain_n4 = (uint16_T)(LgV2_P.Gain_Gain_l1 * LgV2_B.Compare_ib);

    /* RelationalOperator: '<S83>/Compare' incorporates:
     *  Constant: '<S83>/Constant'
     */
    LgV2_B.Compare_lq = (LgV2_B.DeadZone_g1 > LgV2_P.Constant_Value_oq);

    /* Gain: '<S74>/Gain1' */
    LgV2_B.Gain1_aa = (uint16_T)(LgV2_P.Gain1_Gain_l * LgV2_B.Compare_lq);

    /* Sum: '<S74>/Sum' */
    LgV2_B.Sum_af = (uint16_T)(uint32_T)(((LgV2_B.Compare_em << 6) +
      LgV2_B.Gain_n4) + LgV2_B.Gain1_aa);

    /* Lookup Block: '<S74>/f_2 < 0'
     * About '<S74>/f_2 < 0 :'
     * Lookup Block: '<S74>/f_2 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_20_o), LgV2_P.f_20_YData_f,
                         LgV2_B.Product_cl[1], LgV2_P.f_20_XData_g, 10U);

    /* Lookup Block: '<S74>/f_2 > 0'
     * About '<S74>/f_2 > 0 :'
     * Lookup Block: '<S74>/f_2 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_20_c), LgV2_P.f_20_YData_b,
                         LgV2_B.Product_cl[1], LgV2_P.f_20_XData_g0, 9U);

    /* MultiPortSwitch: '<S74>/Multiport Switch' incorporates:
     *  Constant: '<S74>/f_2 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_af >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch_m = LgV2_B.f_20_o;
      break;

     case 2:
      LgV2_B.MultiportSwitch_m = LgV2_P.f_20_Value_c;
      break;

     default:
      LgV2_B.MultiportSwitch_m = LgV2_B.f_20_c;
      break;
    }

    /* DeadZone Block: '<S75>/Dead Zone'
     */
    if (LgV2_B.Product_cl[2] >= LgV2_P.DeadZone_End_o) {
      LgV2_B.DeadZone_f2 = LgV2_B.Product_cl[2] - LgV2_P.DeadZone_End_o;
    } else if (LgV2_B.Product_cl[2] > LgV2_P.DeadZone_Start_cu) {
      LgV2_B.DeadZone_f2 = 0.0;
    } else {
      LgV2_B.DeadZone_f2 = LgV2_B.Product_cl[2] - LgV2_P.DeadZone_Start_cu;
    }

    /* RelationalOperator: '<S84>/Compare' incorporates:
     *  Constant: '<S84>/Constant'
     */
    LgV2_B.Compare_lu = (LgV2_B.DeadZone_f2 < LgV2_P.Constant_Value_f);

    /* RelationalOperator: '<S86>/Compare' */
    LgV2_B.Compare_p0 = (LgV2_B.DeadZone_f2 == 0.0);

    /* Gain: '<S75>/Gain' */
    LgV2_B.Gain_dm = (uint16_T)(LgV2_P.Gain_Gain_bo * LgV2_B.Compare_p0);

    /* RelationalOperator: '<S85>/Compare' incorporates:
     *  Constant: '<S85>/Constant'
     */
    LgV2_B.Compare_ot = (LgV2_B.DeadZone_f2 > LgV2_P.Constant_Value_gc);

    /* Gain: '<S75>/Gain1' */
    LgV2_B.Gain1_hl = (uint16_T)(LgV2_P.Gain1_Gain_mu * LgV2_B.Compare_ot);

    /* Sum: '<S75>/Sum' */
    LgV2_B.Sum_fi = (uint16_T)(uint32_T)(((LgV2_B.Compare_lu << 6) +
      LgV2_B.Gain_dm) + LgV2_B.Gain1_hl);

    /* Lookup Block: '<S75>/f_3 < 0'
     * About '<S75>/f_3 < 0 :'
     * Lookup Block: '<S75>/f_3 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_30_f), LgV2_P.f_30_YData_e,
                         LgV2_B.Product_cl[2], LgV2_P.f_30_XData_p, 7U);

    /* Lookup Block: '<S75>/f_3 > 0'
     * About '<S75>/f_3 > 0 :'
     * Lookup Block: '<S75>/f_3 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_30_e), LgV2_P.f_30_YData_p,
                         LgV2_B.Product_cl[2], LgV2_P.f_30_XData_g, 10U);

    /* MultiPortSwitch: '<S75>/Multiport Switch' incorporates:
     *  Constant: '<S75>/f_3 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_fi >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch_g = LgV2_B.f_30_f;
      break;

     case 2:
      LgV2_B.MultiportSwitch_g = LgV2_P.f_30_Value_m;
      break;

     default:
      LgV2_B.MultiportSwitch_g = LgV2_B.f_30_e;
      break;
    }

    /* DeadZone Block: '<S76>/Dead Zone'
     */
    if (LgV2_B.Product_cl[3] >= LgV2_P.DeadZone_End_g) {
      LgV2_B.DeadZone_fm = LgV2_B.Product_cl[3] - LgV2_P.DeadZone_End_g;
    } else if (LgV2_B.Product_cl[3] > LgV2_P.DeadZone_Start_bq) {
      LgV2_B.DeadZone_fm = 0.0;
    } else {
      LgV2_B.DeadZone_fm = LgV2_B.Product_cl[3] - LgV2_P.DeadZone_Start_bq;
    }

    /* RelationalOperator: '<S87>/Compare' incorporates:
     *  Constant: '<S87>/Constant'
     */
    LgV2_B.Compare_g = (LgV2_B.DeadZone_fm < LgV2_P.Constant_Value_kh);

    /* RelationalOperator: '<S89>/Compare' */
    LgV2_B.Compare_on = (LgV2_B.DeadZone_fm == 0.0);

    /* Gain: '<S76>/Gain' */
    LgV2_B.Gain_gr = (uint16_T)(LgV2_P.Gain_Gain_mw * LgV2_B.Compare_on);

    /* RelationalOperator: '<S88>/Compare' incorporates:
     *  Constant: '<S88>/Constant'
     */
    LgV2_B.Compare_ir = (LgV2_B.DeadZone_fm > LgV2_P.Constant_Value_n);

    /* Gain: '<S76>/Gain1' */
    LgV2_B.Gain1_mc = (uint16_T)(LgV2_P.Gain1_Gain_bp * LgV2_B.Compare_ir);

    /* Sum: '<S76>/Sum' */
    LgV2_B.Sum_mq = (uint16_T)(uint32_T)(((LgV2_B.Compare_g << 6) +
      LgV2_B.Gain_gr) + LgV2_B.Gain1_mc);

    /* Lookup Block: '<S76>/f_4 < 0'
     * About '<S76>/f_4 < 0 :'
     * Lookup Block: '<S76>/f_4 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_40_l), LgV2_P.f_40_YData_m,
                         LgV2_B.Product_cl[3], LgV2_P.f_40_XData_h, 9U);

    /* Lookup Block: '<S76>/f_4 > 0'
     * About '<S76>/f_4 > 0 :'
     * Lookup Block: '<S76>/f_4 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_40_o), LgV2_P.f_40_YData_l,
                         LgV2_B.Product_cl[3], LgV2_P.f_40_XData_j2, 6U);

    /* MultiPortSwitch: '<S76>/Multiport Switch' incorporates:
     *  Constant: '<S76>/f_4 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_mq >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch_i = LgV2_B.f_40_l;
      break;

     case 2:
      LgV2_B.MultiportSwitch_i = LgV2_P.f_40_Value_j;
      break;

     default:
      LgV2_B.MultiportSwitch_i = LgV2_B.f_40_o;
      break;
    }

    /* DeadZone Block: '<S77>/Dead Zone'
     */
    if (LgV2_B.Product_cl[4] >= LgV2_P.DeadZone_End_k) {
      LgV2_B.DeadZone_jb = LgV2_B.Product_cl[4] - LgV2_P.DeadZone_End_k;
    } else if (LgV2_B.Product_cl[4] > LgV2_P.DeadZone_Start_f) {
      LgV2_B.DeadZone_jb = 0.0;
    } else {
      LgV2_B.DeadZone_jb = LgV2_B.Product_cl[4] - LgV2_P.DeadZone_Start_f;
    }

    /* RelationalOperator: '<S90>/Compare' incorporates:
     *  Constant: '<S90>/Constant'
     */
    LgV2_B.Compare_bz = (LgV2_B.DeadZone_jb < LgV2_P.Constant_Value_a4x);

    /* RelationalOperator: '<S92>/Compare' */
    LgV2_B.Compare_cv = (LgV2_B.DeadZone_jb == 0.0);

    /* Gain: '<S77>/Gain' */
    LgV2_B.Gain_cv = (uint16_T)(LgV2_P.Gain_Gain_op * LgV2_B.Compare_cv);

    /* RelationalOperator: '<S91>/Compare' incorporates:
     *  Constant: '<S91>/Constant'
     */
    LgV2_B.Compare_mx = (LgV2_B.DeadZone_jb > LgV2_P.Constant_Value_hx);

    /* Gain: '<S77>/Gain1' */
    LgV2_B.Gain1_e = (uint16_T)(LgV2_P.Gain1_Gain_ma * LgV2_B.Compare_mx);

    /* Sum: '<S77>/Sum' */
    LgV2_B.Sum_ih = (uint16_T)(uint32_T)(((LgV2_B.Compare_bz << 6) +
      LgV2_B.Gain_cv) + LgV2_B.Gain1_e);

    /* Lookup Block: '<S77>/f_5 < 0'
     * About '<S77>/f_5 < 0 :'
     * Lookup Block: '<S77>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_50_b), LgV2_P.f_50_YData_f,
                         LgV2_B.Product_cl[4], LgV2_P.f_50_XData_o, 2U);

    /* Lookup Block: '<S77>/f_5 > 0'
     * About '<S77>/f_5 > 0 :'
     * Lookup Block: '<S77>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(LgV2_B.f_50_k), LgV2_P.f_50_YData_h,
                         LgV2_B.Product_cl[4], LgV2_P.f_50_XData_a, 2U);

    /* MultiPortSwitch: '<S77>/Multiport Switch' incorporates:
     *  Constant: '<S77>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)LgV2_B.Sum_ih >> 6)) {
     case 1:
      LgV2_B.MultiportSwitch_o = LgV2_B.f_50_b;
      break;

     case 2:
      LgV2_B.MultiportSwitch_o = LgV2_P.f_50_Value_j;
      break;

     default:
      LgV2_B.MultiportSwitch_o = LgV2_B.f_50_k;
      break;
    }

    /* MultiPortSwitch: '<S1>/Thruster setting Switch' incorporates:
     *  Constant: '<S1>/Control Mode'
     *  Constant: '<S6>/BT_power_limit'
     *  Constant: '<S6>/VSP_speeds'
     *  Constant: '<S7>/BT_power_limit'
     *  Constant: '<S7>/VSP_speeds'
     *  Constant: '<S8>/PS3_BT_Power'
     *  Constant: '<S8>/PS3_VSP_Speed'
     */
    switch ((int32_T)LgV2_P.ControlMode_Value) {
     case 0:
      LgV2_B.ThrustersettingSwitch[0] = LgV2_B.u_1;
      LgV2_B.ThrustersettingSwitch[1] = LgV2_B.u_2;
      LgV2_B.ThrustersettingSwitch[2] = LgV2_B.u_3;
      LgV2_B.ThrustersettingSwitch[3] = LgV2_B.u_4;
      LgV2_B.ThrustersettingSwitch[4] = LgV2_B.u_5;
      LgV2_B.ThrustersettingSwitch[5] = LgV2_P.PS3_BT_Power_Value;
      LgV2_B.ThrustersettingSwitch[6] = LgV2_P.PS3_VSP_Speed_Value;
      break;

     case 1:
      for (i = 0; i < 5; i++) {
        LgV2_B.ThrustersettingSwitch[i] = LgV2_B.Saturation_p[i];
      }

      LgV2_B.ThrustersettingSwitch[5] = LgV2_P.BT_power_limit_Value;
      LgV2_B.ThrustersettingSwitch[6] = LgV2_P.VSP_speeds_Value;
      break;

     default:
      LgV2_B.ThrustersettingSwitch[0] = LgV2_B.MultiportSwitch_j;
      LgV2_B.ThrustersettingSwitch[1] = LgV2_B.MultiportSwitch_m;
      LgV2_B.ThrustersettingSwitch[2] = LgV2_B.MultiportSwitch_g;
      LgV2_B.ThrustersettingSwitch[3] = LgV2_B.MultiportSwitch_i;
      LgV2_B.ThrustersettingSwitch[4] = LgV2_B.MultiportSwitch_o;
      LgV2_B.ThrustersettingSwitch[5] = LgV2_P.BT_power_limit_Value_b;
      LgV2_B.ThrustersettingSwitch[6] = LgV2_P.VSP_speeds_Value_c;
      break;
    }

    /* Saturate: '<S1>/Saturation' */
    for (i = 0; i < 7; i++) {
      tmp = LgV2_B.ThrustersettingSwitch[i];
      LgV2_B.Saturation_e[i] = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_g5,
        LgV2_P.Saturation_UpperSat_p);
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Gain: '<S112>/-l_x1' incorporates:
       *  Constant: '<S112>/l_x1'
       */
      LgV2_B.l_x1_e = LgV2_P.l_x1_Gain_i * LgV2_P.l_x1_Value_ph;

      /* Gain: '<S112>/-l_y2' incorporates:
       *  Constant: '<S112>/l_y2'
       */
      LgV2_B.l_y2_g = LgV2_P.l_y2_Gain_h * LgV2_P.l_y2_Value_a;

      /* Gain: '<S112>/-l_x2' incorporates:
       *  Constant: '<S112>/l_x2'
       */
      LgV2_B.l_x2_h = LgV2_P.l_x2_Gain_i * LgV2_P.l_x2_Value_l;

      /* Reshape: '<S112>/3x5' incorporates:
       *  Constant: '<S112>/T_e11'
       *  Constant: '<S112>/T_e12'
       *  Constant: '<S112>/T_e13'
       *  Constant: '<S112>/T_e14'
       *  Constant: '<S112>/T_e15'
       *  Constant: '<S112>/T_e21'
       *  Constant: '<S112>/T_e22'
       *  Constant: '<S112>/T_e23'
       *  Constant: '<S112>/T_e24'
       *  Constant: '<S112>/T_e25'
       *  Constant: '<S112>/l_x3'
       *  Constant: '<S112>/l_y1'
       */
      LgV2_B.x5_f[0] = LgV2_P.T_e11_Value_j;
      LgV2_B.x5_f[1] = LgV2_P.T_e21_Value_p;
      LgV2_B.x5_f[2] = LgV2_P.l_y1_Value_p;
      LgV2_B.x5_f[3] = LgV2_P.T_e12_Value_b;
      LgV2_B.x5_f[4] = LgV2_P.T_e22_Value_p;
      LgV2_B.x5_f[5] = LgV2_B.l_x1_e;
      LgV2_B.x5_f[6] = LgV2_P.T_e13_Value_d;
      LgV2_B.x5_f[7] = LgV2_P.T_e23_Value_g;
      LgV2_B.x5_f[8] = LgV2_B.l_y2_g;
      LgV2_B.x5_f[9] = LgV2_P.T_e14_Value_i;
      LgV2_B.x5_f[10] = LgV2_P.T_e24_Value_j;
      LgV2_B.x5_f[11] = LgV2_B.l_x2_h;
      LgV2_B.x5_f[12] = LgV2_P.T_e15_Value_f;
      LgV2_B.x5_f[13] = LgV2_P.T_e25_Value_l;
      LgV2_B.x5_f[14] = LgV2_P.l_x3_Value_o;

      /* Lookup Block: '<S111>/u_1 to f_1'
       * About '<S111>/u_1 to f_1 :'
       * Lookup Block: '<S111>/u_1 to f_1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(LgV2_B.u_1tof_1), LgV2_P.u_1tof_1_YData,
                           LgV2_B.u_1, LgV2_P.u_1tof_1_XData, 18U);

      /* Lookup Block: '<S111>/u_2 to f_2'
       * About '<S111>/u_2 to f_2 :'
       * Lookup Block: '<S111>/u_2 to f_2'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(LgV2_B.u_2tof_2), LgV2_P.u_2tof_2_YData,
                           LgV2_B.u_2, LgV2_P.u_2tof_2_XData, 20U);

      /* Lookup Block: '<S111>/u_3 to f_3'
       * About '<S111>/u_3 to f_3 :'
       * Lookup Block: '<S111>/u_3 to f_3'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(LgV2_B.u_3tof_3), LgV2_P.u_3tof_3_YData,
                           LgV2_B.u_3, LgV2_P.u_3tof_3_XData, 18U);

      /* Lookup Block: '<S111>/u_4 to f_4'
       * About '<S111>/u_4 to f_4 :'
       * Lookup Block: '<S111>/u_4 to f_4'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(LgV2_B.u_4tof_4), LgV2_P.u_4tof_4_YData,
                           LgV2_B.u_4, LgV2_P.u_4tof_4_XData, 16U);

      /* Lookup Block: '<S111>/u_5 to f_5'
       * About '<S111>/u_5 to f_5 :'
       * Lookup Block: '<S111>/u_5 to f_5'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(LgV2_B.u_5tof_5), LgV2_P.u_5tof_5_YData,
                           LgV2_B.u_5, LgV2_P.u_5tof_5_XData, 6U);

      /* SignalConversion: '<S110>/TmpHiddenBufferAtProductInport2' */
      LgV2_B.TmpHiddenBufferAtProductInpor_c[0] = LgV2_B.u_1tof_1;
      LgV2_B.TmpHiddenBufferAtProductInpor_c[1] = LgV2_B.u_2tof_2;
      LgV2_B.TmpHiddenBufferAtProductInpor_c[2] = LgV2_B.u_3tof_3;
      LgV2_B.TmpHiddenBufferAtProductInpor_c[3] = LgV2_B.u_4tof_4;
      LgV2_B.TmpHiddenBufferAtProductInpor_c[4] = LgV2_B.u_5tof_5;

      /* Product: '<S110>/Product' */
      for (i = 0; i < 3; i++) {
        LgV2_B.Product_cb[i] = 0.0;
        for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
          LgV2_B.Product_cb[i] = LgV2_B.x5_f[3 * tmp_6 + i] *
            LgV2_B.TmpHiddenBufferAtProductInpor_c[tmp_6] + LgV2_B.Product_cb[i];
        }
      }
    }

    /* MultiPortSwitch: '<S1>/tau Switch' incorporates:
     *  Constant: '<S1>/Control Mode'
     */
    switch ((int32_T)LgV2_P.ControlMode_Value) {
     case 0:
      LgV2_B.tauSwitch[0] = LgV2_B.Product_cb[0];
      LgV2_B.tauSwitch[1] = LgV2_B.Product_cb[1];
      LgV2_B.tauSwitch[2] = LgV2_B.Product_cb[2];
      break;

     case 1:
      LgV2_B.tauSwitch[0] = LgV2_B.Sum1_j[0];
      LgV2_B.tauSwitch[1] = LgV2_B.Sum1_j[1];
      LgV2_B.tauSwitch[2] = LgV2_B.Sum1_j[2];
      break;

     default:
      LgV2_B.tauSwitch[0] = LgV2_B.Sum_gc[0];
      LgV2_B.tauSwitch[1] = LgV2_B.Sum_gc[1];
      LgV2_B.tauSwitch[2] = LgV2_B.Sum_gc[2];
      break;
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* SignalConversion: '<Root>/TmpHiddenBufferAtTo FileInport1' incorporates:
       *  Constant: '<S117>/Path Selector'
       *  Constant: '<S197>/u_d'
       *  Constant: '<S1>/Control Mode'
       *  Constant: '<S4>/Controller Input Selector'
       */
      LgV2_B.TmpHiddenBufferAtToFileInport1[0] =
        LgV2_P.ControllerInputSelector_Value;
      LgV2_B.TmpHiddenBufferAtToFileInport1[1] = LgV2_B.QTMIn2Error;
      LgV2_B.TmpHiddenBufferAtToFileInport1[2] = LgV2_B.QTMIn9Residual;
      LgV2_B.TmpHiddenBufferAtToFileInport1[3] = LgV2_B.etadot_surge;
      LgV2_B.TmpHiddenBufferAtToFileInport1[4] = LgV2_B.etadot_sway;
      LgV2_B.TmpHiddenBufferAtToFileInport1[5] = LgV2_B.etadot_yaw;
      LgV2_B.TmpHiddenBufferAtToFileInport1[6] = LgV2_B.eta_surge;
      LgV2_B.TmpHiddenBufferAtToFileInport1[7] = LgV2_B.eta_sway;
      LgV2_B.TmpHiddenBufferAtToFileInport1[8] = LgV2_B.eta_yaw;
      LgV2_B.TmpHiddenBufferAtToFileInport1[9] = LgV2_B.nu_surge;
      LgV2_B.TmpHiddenBufferAtToFileInport1[10] = LgV2_B.nu_sway;
      LgV2_B.TmpHiddenBufferAtToFileInport1[11] = LgV2_B.nu_yaw;
      LgV2_B.TmpHiddenBufferAtToFileInport1[12] = LgV2_B.eta_dDPN;
      LgV2_B.TmpHiddenBufferAtToFileInport1[13] = LgV2_B.eta_dDPE;
      LgV2_B.TmpHiddenBufferAtToFileInport1[14] = LgV2_B.eta_dDPPsi;
      LgV2_B.TmpHiddenBufferAtToFileInport1[15] = LgV2_B.q_x;
      LgV2_B.TmpHiddenBufferAtToFileInport1[16] = LgV2_B.q_y;
      LgV2_B.TmpHiddenBufferAtToFileInport1[17] = LgV2_B.psi_los;
      LgV2_B.TmpHiddenBufferAtToFileInport1[18] = LgV2_P.PathSelector_Value;
      LgV2_B.TmpHiddenBufferAtToFileInport1[19] = LgV2_B.pathx_d;
      LgV2_B.TmpHiddenBufferAtToFileInport1[20] = LgV2_B.pathy_d;
      LgV2_B.TmpHiddenBufferAtToFileInport1[21] = LgV2_B.pathpsi_d;
      LgV2_B.TmpHiddenBufferAtToFileInport1[22] = LgV2_P.u_d_Value;
      LgV2_B.TmpHiddenBufferAtToFileInport1[23] = LgV2_B.Divide;
      LgV2_B.TmpHiddenBufferAtToFileInport1[24] = LgV2_B.Integrator1;
      LgV2_B.TmpHiddenBufferAtToFileInport1[25] = LgV2_P.ControlMode_Value;
      for (i = 0; i < 7; i++) {
        LgV2_B.TmpHiddenBufferAtToFileInport1[i + 26] = LgV2_B.Saturation_e[i];
      }

      LgV2_B.TmpHiddenBufferAtToFileInport1[33] = LgV2_B.tauSwitch[0];
      LgV2_B.TmpHiddenBufferAtToFileInport1[34] = LgV2_B.tauSwitch[1];
      LgV2_B.TmpHiddenBufferAtToFileInport1[35] = LgV2_B.tauSwitch[2];

      /* ToFile Block: '<Root>/To File'
       */
      if (rtmIsMajorTimeStep(LgV2_M)) {
        if (!(++LgV2_DWork.ToFile_IWORK.Decimation % 1) &&
            (LgV2_DWork.ToFile_IWORK.Count*37)+1 < 100000000 ) {
          real_T u[37];
          FILE *fp = (FILE *) LgV2_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            LgV2_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = LgV2_M->Timing.t[1];
            u[1] = LgV2_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = LgV2_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = LgV2_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = LgV2_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = LgV2_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = LgV2_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = LgV2_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = LgV2_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = LgV2_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = LgV2_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = LgV2_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = LgV2_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = LgV2_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = LgV2_B.TmpHiddenBufferAtToFileInport1[13];
            u[15] = LgV2_B.TmpHiddenBufferAtToFileInport1[14];
            u[16] = LgV2_B.TmpHiddenBufferAtToFileInport1[15];
            u[17] = LgV2_B.TmpHiddenBufferAtToFileInport1[16];
            u[18] = LgV2_B.TmpHiddenBufferAtToFileInport1[17];
            u[19] = LgV2_B.TmpHiddenBufferAtToFileInport1[18];
            u[20] = LgV2_B.TmpHiddenBufferAtToFileInport1[19];
            u[21] = LgV2_B.TmpHiddenBufferAtToFileInport1[20];
            u[22] = LgV2_B.TmpHiddenBufferAtToFileInport1[21];
            u[23] = LgV2_B.TmpHiddenBufferAtToFileInport1[22];
            u[24] = LgV2_B.TmpHiddenBufferAtToFileInport1[23];
            u[25] = LgV2_B.TmpHiddenBufferAtToFileInport1[24];
            u[26] = LgV2_B.TmpHiddenBufferAtToFileInport1[25];
            u[27] = LgV2_B.TmpHiddenBufferAtToFileInport1[26];
            u[28] = LgV2_B.TmpHiddenBufferAtToFileInport1[27];
            u[29] = LgV2_B.TmpHiddenBufferAtToFileInport1[28];
            u[30] = LgV2_B.TmpHiddenBufferAtToFileInport1[29];
            u[31] = LgV2_B.TmpHiddenBufferAtToFileInport1[30];
            u[32] = LgV2_B.TmpHiddenBufferAtToFileInport1[31];
            u[33] = LgV2_B.TmpHiddenBufferAtToFileInport1[32];
            u[34] = LgV2_B.TmpHiddenBufferAtToFileInport1[33];
            u[35] = LgV2_B.TmpHiddenBufferAtToFileInport1[34];
            u[36] = LgV2_B.TmpHiddenBufferAtToFileInport1[35];
            if (fwrite(u, sizeof(real_T), 37, fp) != 37) {
              rtmSetErrorStatus(LgV2_M,
                                "Error writing to MAT-file CSE1_LgV2_data.mat");
              return;
            }

            if (((++LgV2_DWork.ToFile_IWORK.Count)*37)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file CSE1_LgV2_data.mat.\n");
            }
          }
        }
      }

      /* Reshape: '<S41>/2x2' incorporates:
       *  Constant: '<S41>/12'
       *  Constant: '<S41>/21'
       *  Constant: '<S7>/Gamma_q_Surge'
       *  Constant: '<S7>/Gamma_q_Sway'
       */
      LgV2_B.x2[0] = LgV2_P.Gamma_q_Surge_Value;
      LgV2_B.x2[1] = LgV2_P.u_Value_io;
      LgV2_B.x2[2] = LgV2_P.u_Value_nw;
      LgV2_B.x2[3] = LgV2_P.Gamma_q_Sway_Value;
    }

    /* Product: '<S42>/Product' */
    for (i = 0; i < 3; i++) {
      LgV2_B.Product_ff[i] = 0.0;
      LgV2_B.Product_ff[i] = LgV2_B.Rpsi[i] * LgV2_B.Subtract_di[0] +
        LgV2_B.Product_ff[i];
      LgV2_B.Product_ff[i] = LgV2_B.Rpsi[i + 3] * LgV2_B.Subtract_di[1] +
        LgV2_B.Product_ff[i];
      LgV2_B.Product_ff[i] = LgV2_B.Rpsi[i + 6] * LgV2_B.Subtract_di[2] +
        LgV2_B.Product_ff[i];
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
    }

    /* Sum: '<S52>/Add' */
    LgV2_B.Add_h[0] = LgV2_B.Integrator2[0] + LgV2_B.Product_g5[0];
    LgV2_B.Add_h[1] = LgV2_B.Integrator2[1] + LgV2_B.Product_g5[1];

    /* Math: '<S96>/Math Function' */
    LgV2_B.MathFunction_gg[0] = LgV2_B.Product_i[0];
    LgV2_B.MathFunction_gg[1] = LgV2_B.Product_i[1];
    LgV2_B.MathFunction_gg[2] = LgV2_B.Product_i[2];

    /* Product: '<S53>/Product' */
    for (i = 0; i < 3; i++) {
      tmp_5[i] = 0.0;
      tmp = tmp_5[i];
      tmp += LgV2_B.MathFunction_dr[3 * i] * LgV2_B.MathFunction_gg[0];
      tmp_5[i] = tmp;
      tmp = tmp_5[i];
      tmp += LgV2_B.MathFunction_dr[3 * i + 1] * LgV2_B.MathFunction_gg[1];
      tmp_5[i] = tmp;
      tmp = tmp_5[i];
      tmp += LgV2_B.MathFunction_dr[3 * i + 2] * LgV2_B.MathFunction_gg[2];
      tmp_5[i] = tmp;
    }

    for (i = 0; i < 2; i++) {
      LgV2_B.Product_cu[i] = 0.0;
      LgV2_B.Product_cu[i] = LgV2_B.MatrixConcatenate[3 * i] * tmp_5[0] +
        LgV2_B.Product_cu[i];
      LgV2_B.Product_cu[i] = LgV2_B.MatrixConcatenate[3 * i + 1] * tmp_5[1] +
        LgV2_B.Product_cu[i];
      LgV2_B.Product_cu[i] = LgV2_B.MatrixConcatenate[3 * i + 2] * tmp_5[2] +
        LgV2_B.Product_cu[i];

      /* Gain: '<S53>/Gain' */
      LgV2_B.Gain_f3[i] = LgV2_P.Gain_Gain_cq * LgV2_B.Product_cu[i];

      /* Math: '<S94>/Math Function' */
      LgV2_B.MathFunction_g1[i] = LgV2_B.Gain_f3[i];
    }

    /* Product: '<S52>/Product' */
    LgV2_B.Product_if[0] = 0.0;
    LgV2_B.Product_if[0] = LgV2_B.x2[0] * LgV2_B.MathFunction_g1[0] +
      LgV2_B.Product_if[0];
    LgV2_B.Product_if[0] = LgV2_B.x2[2] * LgV2_B.MathFunction_g1[1] +
      LgV2_B.Product_if[0];

    /* Sum: '<S52>/Add1' */
    LgV2_B.Add1_c[0] = LgV2_B.Integrator2[0] + LgV2_B.Product_if[0];

    /* Product: '<S52>/Product1' incorporates:
     *  Constant: '<S7>/lambda'
     */
    LgV2_B.Product1_f5[0] = LgV2_P.lambda_Value * LgV2_B.Add1_c[0];

    /* Gain: '<S52>/Gain' */
    LgV2_B.Gain_kii[0] = LgV2_P.Gain_Gain_gw * LgV2_B.Product1_f5[0];

    /* Product: '<S52>/Product' */
    LgV2_B.Product_if[1] = 0.0;
    LgV2_B.Product_if[1] = LgV2_B.x2[1] * LgV2_B.MathFunction_g1[0] +
      LgV2_B.Product_if[1];
    LgV2_B.Product_if[1] = LgV2_B.x2[3] * LgV2_B.MathFunction_g1[1] +
      LgV2_B.Product_if[1];

    /* Sum: '<S52>/Add1' */
    LgV2_B.Add1_c[1] = LgV2_B.Integrator2[1] + LgV2_B.Product_if[1];

    /* Product: '<S52>/Product1' incorporates:
     *  Constant: '<S7>/lambda'
     */
    LgV2_B.Product1_f5[1] = LgV2_P.lambda_Value * LgV2_B.Add1_c[1];

    /* Gain: '<S52>/Gain' */
    LgV2_B.Gain_kii[1] = LgV2_P.Gain_Gain_gw * LgV2_B.Product1_f5[1];
    if (rtmIsMajorTimeStep(LgV2_M)) {
      /* Gain: '<S3>/Battery Bow Thruster' */
      LgV2_B.BatteryBowThruster = LgV2_P.BatteryBowThruster_Gain *
        LgV2_B.SITzAI0;

      /* Gain: '<S3>/Battery Servo' */
      LgV2_B.BatteryServo = LgV2_P.BatteryServo_Gain * LgV2_B.SITzAI1;

      /* Gain: '<S3>/Battery Main' */
      LgV2_B.BatteryMain = LgV2_P.BatteryMain_Gain * LgV2_B.SITzAI2;
    }

    /* Gain: '<S199>/QTM In1 FPS' */
    LgV2_B.QTMIn1FPS = LgV2_P.QTMIn1FPS_Gain * LgV2_B.QTMIn[0];

    /* Saturate: '<S203>/Saturation' */
    tmp = LgV2_B.tauSwitch[0];
    LgV2_B.Saturation_dq = rt_SATURATE(tmp, LgV2_P.Saturation_LowerSat_k,
      LgV2_P.Saturation_UpperSat_a);

    /* Saturate: '<S203>/Saturation1' */
    tmp = LgV2_B.tauSwitch[1];
    LgV2_B.Saturation1 = rt_SATURATE(tmp, LgV2_P.Saturation1_LowerSat,
      LgV2_P.Saturation1_UpperSat);

    /* Saturate: '<S203>/Saturation2' */
    tmp = LgV2_B.tauSwitch[2];
    LgV2_B.Saturation2 = rt_SATURATE(tmp, LgV2_P.Saturation2_LowerSat,
      LgV2_P.Saturation2_UpperSat);

    /* Gain: '<S203>/plant tau_surge' */
    LgV2_B.planttau_surge = LgV2_P.planttau_surge_Gain * LgV2_B.Saturation_dq;

    /* Gain: '<S203>/plant tau_sway' */
    LgV2_B.planttau_sway = LgV2_P.planttau_sway_Gain * LgV2_B.Saturation1;

    /* Gain: '<S203>/plant tau_yaw' */
    LgV2_B.planttau_yaw = LgV2_P.planttau_yaw_Gain * LgV2_B.Saturation2;

    /* Gain: '<S5>/plant u_1' */
    LgV2_B.plantu_1 = LgV2_P.plantu_1_Gain * LgV2_B.Saturation_e[0];

    /* Gain: '<S5>/plant u_2' */
    LgV2_B.plantu_2 = LgV2_P.plantu_2_Gain * LgV2_B.Saturation_e[1];

    /* Gain: '<S5>/plant u_3' */
    LgV2_B.plantu_3 = LgV2_P.plantu_3_Gain * LgV2_B.Saturation_e[2];

    /* Gain: '<S5>/plant u_4' */
    LgV2_B.plantu_4 = LgV2_P.plantu_4_Gain * LgV2_B.Saturation_e[3];

    /* Gain: '<S5>/plant u_5' */
    LgV2_B.plantu_5 = LgV2_P.plantu_5_Gain * LgV2_B.Saturation_e[4];

    /* Gain: '<S5>/plant BT power' */
    LgV2_B.plantBTpower = LgV2_P.plantBTpower_Gain * LgV2_B.Saturation_e[5];

    /* Gain: '<S5>/plant VSP speed' */
    LgV2_B.plantVSPspeed = LgV2_P.plantVSPspeed_Gain * LgV2_B.Saturation_e[6];

    /* Outputs for enable SubSystem: '<S5>/CSE1' incorporates:
     *  Constant: '<S5>/Enable CSE1'
     *  EnablePort: '<S201>/Enable'
     */
    if (rtmIsMajorTimeStep(LgV2_M) && rtmIsMajorTimeStep(LgV2_M)) {
      if (LgV2_P.EnableCSE1_Value > 0.0) {
        if (LgV2_DWork.CSE1_MODE == SUBSYS_DISABLED) {
          LgV2_DWork.CSE1_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (LgV2_DWork.CSE1_MODE == SUBSYS_ENABLED) {
          LgV2_DWork.CSE1_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (LgV2_DWork.CSE1_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S204>/BT_D_Gain1' */
      LgV2_B.BT_D_Gain1 = LgV2_P.BT_D_Gain1_Gain * LgV2_B.plantu_5;

      /* Gain: '<S204>/BT_D_Gain2' */
      LgV2_B.BT_D_Gain2 = LgV2_P.BT_D_Gain2_Gain * LgV2_B.plantu_5;

      /* Sum: '<S204>/Add' incorporates:
       *  Constant: '<S204>/BT_Power_Offset1'
       */
      LgV2_B.Add_ct = (LgV2_B.BT_D_Gain1 + LgV2_P.BT_Power_Offset1_Value) +
        LgV2_B.BT_D_Gain2;

      /* Gain: '<S204>/BT_L_Gain1' */
      LgV2_B.BT_L_Gain1 = LgV2_P.BT_L_Gain1_Gain * LgV2_B.plantBTpower;

      /* Gain: '<S204>/BT_L_Gain2' */
      LgV2_B.BT_L_Gain2 = LgV2_P.BT_L_Gain2_Gain * LgV2_B.plantBTpower;

      /* Gain: '<S204>/Neg' */
      LgV2_B.Neg = LgV2_P.Neg_Gain * LgV2_B.plantBTpower;
      if (rtmIsMajorTimeStep(LgV2_M)) {
      }

      /* Sum: '<S204>/Sum1' incorporates:
       *  Constant: '<S204>/BT_Power_Offset2'
       */
      LgV2_B.Sum1_k = LgV2_B.BT_L_Gain1 + LgV2_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S206>/LowerRelop1' */
      LgV2_B.LowerRelop1_n = (LgV2_B.Add_ct > LgV2_B.Sum1_k);

      /* Sum: '<S204>/Sum2' incorporates:
       *  Constant: '<S204>/BT_Power_Offset3'
       */
      LgV2_B.Sum2 = LgV2_B.BT_L_Gain2 + LgV2_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S206>/UpperRelop' */
      LgV2_B.UpperRelop_m = (LgV2_B.Add_ct < LgV2_B.Sum2);

      /* Switch: '<S206>/Switch' */
      if (LgV2_B.UpperRelop_m) {
        LgV2_B.Switch_i = LgV2_B.Sum2;
      } else {
        LgV2_B.Switch_i = LgV2_B.Add_ct;
      }

      /* Switch: '<S206>/Switch2' */
      if (LgV2_B.LowerRelop1_n) {
        LgV2_B.Switch2_d = LgV2_B.Sum1_k;
      } else {
        LgV2_B.Switch2_d = LgV2_B.Switch_i;
      }

      if (rtmIsMajorTimeStep(LgV2_M)) {
      }

      /* RelationalOperator: '<S207>/LowerRelop1' incorporates:
       *  Constant: '<S204>/Constant'
       */
      LgV2_B.LowerRelop1_j = (LgV2_B.plantu_5 > LgV2_P.Constant_Value_i);

      /* RelationalOperator: '<S207>/UpperRelop' */
      LgV2_B.UpperRelop_b = (LgV2_B.plantu_5 < LgV2_B.Neg);

      /* Switch: '<S207>/Switch' */
      if (LgV2_B.UpperRelop_b) {
        LgV2_B.Switch_d = LgV2_B.Neg;
      } else {
        LgV2_B.Switch_d = LgV2_B.plantu_5;
      }

      /* Switch: '<S207>/Switch2' incorporates:
       *  Constant: '<S204>/Constant'
       */
      if (LgV2_B.LowerRelop1_j) {
        LgV2_B.Switch2_p = LgV2_P.Constant_Value_i;
      } else {
        LgV2_B.Switch2_p = LgV2_B.Switch_d;
      }

      if (rtmIsMajorTimeStep(LgV2_M)) {
      }

      /* RelationalOperator: '<S208>/LowerRelop1' */
      LgV2_B.LowerRelop1_b = (LgV2_B.plantu_5 > LgV2_B.plantBTpower);

      /* RelationalOperator: '<S208>/UpperRelop' incorporates:
       *  Constant: '<S204>/Constant1'
       */
      LgV2_B.UpperRelop_h = (LgV2_B.plantu_5 < LgV2_P.Constant1_Value_j);

      /* Switch: '<S208>/Switch' incorporates:
       *  Constant: '<S204>/Constant1'
       */
      if (LgV2_B.UpperRelop_h) {
        LgV2_B.Switch_d3 = LgV2_P.Constant1_Value_j;
      } else {
        LgV2_B.Switch_d3 = LgV2_B.plantu_5;
      }

      /* Switch: '<S208>/Switch2' */
      if (LgV2_B.LowerRelop1_b) {
        LgV2_B.Switch2_o = LgV2_B.plantBTpower;
      } else {
        LgV2_B.Switch2_o = LgV2_B.Switch_d3;
      }

      /* Signum: '<S205>/Sign' */
      LgV2_B.Sign_o = rt_SIGNd_snf(LgV2_B.plantVSPspeed);

      /* Product: '<S205>/Product1' */
      LgV2_B.PortVPS_X = LgV2_B.plantu_2 * LgV2_B.Sign_o;

      /* Gain: '<S205>/-x' */
      LgV2_B.PortVPS_X_n = LgV2_P.x_Gain * LgV2_B.PortVPS_X;

      /* Product: '<S205>/Product2' */
      LgV2_B.PortVSP_Y = LgV2_B.plantu_1 * LgV2_B.Sign_o;

      /* Gain: '<S205>/-y' */
      LgV2_B.PortVSP_Y_b = LgV2_P.y_Gain * LgV2_B.PortVSP_Y;

      /* Product: '<S205>/Product3' */
      LgV2_B.StarboardVSP_X = LgV2_B.plantu_4 * LgV2_B.Sign_o;

      /* Product: '<S205>/Product4' */
      LgV2_B.StarboardVSP_Y = LgV2_B.plantu_3 * LgV2_B.Sign_o;

      /* Lookup2D: '<S205>/Servo1' */
      LgV2_B.Servo1 = rt_Lookup2D_Normal((const real_T *)(&LgV2_P.Servo1_RowIdx
        [0]), 3, (const real_T *)(&LgV2_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&LgV2_P.Servo1_Table[0]), (const real_T)LgV2_B.PortVPS_X_n, (const
        real_T)LgV2_B.PortVSP_Y_b);

      /* Lookup2D: '<S205>/Servo2' */
      LgV2_B.Servo2 = rt_Lookup2D_Normal((const real_T *)(&LgV2_P.Servo2_RowIdx
        [0]), 3, (const real_T *)(&LgV2_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&LgV2_P.Servo2_Table[0]), (const real_T)LgV2_B.PortVPS_X_n, (const
        real_T)LgV2_B.PortVSP_Y_b);

      /* Lookup2D: '<S205>/Servo3' */
      LgV2_B.Servo3 = rt_Lookup2D_Normal((const real_T *)(&LgV2_P.Servo3_RowIdx
        [0]), 3, (const real_T *)(&LgV2_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&LgV2_P.Servo3_Table[0]), (const real_T)LgV2_B.StarboardVSP_X, (const
        real_T)LgV2_B.StarboardVSP_Y);

      /* Lookup2D: '<S205>/Servo4' */
      LgV2_B.Servo4 = rt_Lookup2D_Normal((const real_T *)(&LgV2_P.Servo4_RowIdx
        [0]), 3, (const real_T *)(&LgV2_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&LgV2_P.Servo4_Table[0]), (const real_T)LgV2_B.StarboardVSP_X, (const
        real_T)LgV2_B.StarboardVSP_Y);

      /* Gain: '<S205>/VPS_Speed_Gain' */
      LgV2_B.VPS_Speed_Gain = LgV2_P.VPS_Speed_Gain_Gain * LgV2_B.plantVSPspeed;

      /* Sum: '<S205>/Sum' incorporates:
       *  Constant: '<S205>/VPS_Power_Offset'
       */
      LgV2_B.Sum_d3 = LgV2_B.VPS_Speed_Gain + LgV2_P.VPS_Power_Offset_Value;

      /* Gain: '<S205>/VSPS Port' */
      LgV2_B.VSPSPort = LgV2_P.VSPSPort_Gain * LgV2_B.Sum_d3;

      /* Gain: '<S205>/VSPS Starboard' */
      LgV2_B.VSPSStarboard = LgV2_P.VSPSStarboard_Gain * LgV2_B.Sum_d3;
    }

    /* end of Outputs for SubSystem: '<S5>/CSE1' */

    /* Gain: '<Root>/eta_psi' */
    LgV2_B.eta_psi = LgV2_P.eta_psi_Gain * LgV2_B.eta_yaw;

    /* Gain: '<Root>/eta_psid' */
    LgV2_B.eta_psid = LgV2_P.eta_psid_Gain * LgV2_B.pathpsi_d;

    /* Gain: '<Root>/eta_x' */
    LgV2_B.eta_x = LgV2_P.eta_x_Gain * LgV2_B.eta_surge;

    /* Gain: '<Root>/eta_xd' */
    LgV2_B.eta_xd = LgV2_P.eta_xd_Gain * LgV2_B.pathx_d;

    /* Gain: '<Root>/eta_y' */
    LgV2_B.eta_y = LgV2_P.eta_y_Gain * LgV2_B.eta_sway;

    /* Gain: '<Root>/eta_yd' */
    LgV2_B.eta_yd = LgV2_P.eta_yd_Gain * LgV2_B.pathy_d;

    /* Gain: '<Root>/psi_los' */
    LgV2_B.psi_los_k = LgV2_P.psi_los_Gain_o * LgV2_B.psi_los;

    /* Gain: '<Root>/psi_plot' */
    LgV2_B.psi_plot[0] = LgV2_P.psi_plot_Gain * LgV2_B.eta_psi;
    LgV2_B.psi_plot[1] = LgV2_P.psi_plot_Gain * LgV2_B.psi_los_k;
    LgV2_B.psi_plot[2] = LgV2_P.psi_plot_Gain * LgV2_B.eta_psid;

    /* Gain: '<Root>/q_x' */
    LgV2_B.q_x_e = LgV2_P.q_x_Gain_o * LgV2_B.q_x;

    /* Gain: '<Root>/q_y' */
    LgV2_B.q_y_c = LgV2_P.q_y_Gain_p * LgV2_B.q_y;

    /* Gain: '<Root>/x_plot' */
    LgV2_B.x_plot[0] = LgV2_P.x_plot_Gain * LgV2_B.eta_x;
    LgV2_B.x_plot[1] = LgV2_P.x_plot_Gain * LgV2_B.q_x_e;
    LgV2_B.x_plot[2] = LgV2_P.x_plot_Gain * LgV2_B.eta_xd;

    /* Gain: '<Root>/y_plot' */
    LgV2_B.y_plot[0] = LgV2_P.y_plot_Gain * LgV2_B.eta_y;
    LgV2_B.y_plot[1] = LgV2_P.y_plot_Gain * LgV2_B.q_y_c;
    LgV2_B.y_plot[2] = LgV2_P.y_plot_Gain * LgV2_B.eta_yd;
    if (rtmIsMajorTimeStep(LgV2_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void LgV2_update(int_T tid)
{
  {
    int32_T tmp;

    /* Derivative Block: '<S199>/Derivative1' */
    {
      real_T timeStampA = LgV2_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = LgV2_DWork.Derivative1_RWORK.TimeStampB;
      real_T *lastBank = &LgV2_DWork.Derivative1_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 4;
        } else if (timeStampA >= timeStampB) {
          lastBank += 4;
        }
      }

      *lastBank++ = LgV2_M->Timing.t[0];
      *lastBank++ = LgV2_B.mm2mx;
      *lastBank++ = LgV2_B.mm2my;
      *lastBank++ = LgV2_B.d2ryaw;
    }

    /* Update for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S202>/Enable'
     */
    if (LgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Sum: '<S209>/Sum' */
      LgV2_B.Sum_j3[0] = LgV2_B.planttau_surge - LgV2_B.Product1_ob[0];
      LgV2_B.Sum_j3[1] = LgV2_B.planttau_sway - LgV2_B.Product1_ob[1];
      LgV2_B.Sum_j3[2] = LgV2_B.planttau_yaw - LgV2_B.Product1_ob[2];

      /* Product: '<S209>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        LgV2_B.Product2_d[tmp] = 0.0;
        LgV2_B.Product2_d[tmp] = LgV2_B.Inverse[tmp] * LgV2_B.Sum_j3[0] +
          LgV2_B.Product2_d[tmp];
        LgV2_B.Product2_d[tmp] = LgV2_B.Inverse[tmp + 3] * LgV2_B.Sum_j3[1] +
          LgV2_B.Product2_d[tmp];
        LgV2_B.Product2_d[tmp] = LgV2_B.Inverse[tmp + 6] * LgV2_B.Sum_j3[2] +
          LgV2_B.Product2_d[tmp];
      }
    }

    /* end of Update for SubSystem: '<S5>/Linear Simulator' */

    /* Derivative Block: '<S199>/Derivative' */
    {
      real_T timeStampA = LgV2_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = LgV2_DWork.Derivative_RWORK.TimeStampB;
      real_T *lastBank = &LgV2_DWork.Derivative_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = LgV2_M->Timing.t[0];
      *lastBank++ = LgV2_B.mm2mx;
      *lastBank++ = LgV2_B.mm2my;
      *lastBank++ = LgV2_B.mm2mz;
      *lastBank++ = LgV2_B.d2rroll;
      *lastBank++ = LgV2_B.d2rpitch;
      *lastBank++ = LgV2_B.d2ryaw;
    }

    /* Derivative Block: '<S118>/Derivative' */
    {
      real_T timeStampA = LgV2_DWork.Derivative_RWORK_m.TimeStampA;
      real_T timeStampB = LgV2_DWork.Derivative_RWORK_m.TimeStampB;
      real_T *lastBank = &LgV2_DWork.Derivative_RWORK_m.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 2;
        } else if (timeStampA >= timeStampB) {
          lastBank += 2;
        }
      }

      *lastBank++ = LgV2_M->Timing.t[0];
      *lastBank++ = LgV2_P.u_d_Value;
    }

    if (rtmIsMajorTimeStep(LgV2_M)) {
    }
  }

  if (rtmIsMajorTimeStep(LgV2_M)) {
    rt_ertODEUpdateContinuousStates(&LgV2_M->solverInfo);
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
  if (!(++LgV2_M->Timing.clockTick0))
    ++LgV2_M->Timing.clockTickH0;
  LgV2_M->Timing.t[0] = LgV2_M->Timing.clockTick0 * LgV2_M->Timing.stepSize0 +
    LgV2_M->Timing.clockTickH0 * LgV2_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(LgV2_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++LgV2_M->Timing.clockTick1))
      ++LgV2_M->Timing.clockTickH1;
    LgV2_M->Timing.t[1] = LgV2_M->Timing.clockTick1 * LgV2_M->Timing.stepSize1 +
      LgV2_M->Timing.clockTickH1 * LgV2_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void LgV2_derivatives(void)
{
  {
    int32_T tmp;

    /* Derivatives for enable SubSystem: '<S5>/Linear Simulator' */
    if (LgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Sum: '<S209>/Sum' */
      LgV2_B.Sum_j3[0] = LgV2_B.planttau_surge - LgV2_B.Product1_ob[0];
      LgV2_B.Sum_j3[1] = LgV2_B.planttau_sway - LgV2_B.Product1_ob[1];
      LgV2_B.Sum_j3[2] = LgV2_B.planttau_yaw - LgV2_B.Product1_ob[2];

      /* Product: '<S209>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        LgV2_B.Product2_d[tmp] = 0.0;
        LgV2_B.Product2_d[tmp] = LgV2_B.Inverse[tmp] * LgV2_B.Sum_j3[0] +
          LgV2_B.Product2_d[tmp];
        LgV2_B.Product2_d[tmp] = LgV2_B.Inverse[tmp + 3] * LgV2_B.Sum_j3[1] +
          LgV2_B.Product2_d[tmp];
        LgV2_B.Product2_d[tmp] = LgV2_B.Inverse[tmp + 6] * LgV2_B.Sum_j3[2] +
          LgV2_B.Product2_d[tmp];
      }

      /* Integrator Block: '<S209>/Integrator' */
      {
        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_f[0] = LgV2_B.Product2_d[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_f[0] = 0.0;
        }

        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_f[1] = LgV2_B.Product2_d[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_f[1] = 0.0;
        }

        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_f[2] = LgV2_B.Product2_d[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_f[2] = 0.0;
        }
      }

      /* Integrator Block: '<S209>/Integrator1' */
      {
        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_h[0] = LgV2_B.Product3_f[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_h[0] = 0.0;
        }

        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_h[1] = LgV2_B.Product3_f[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_h[1] = 0.0;
        }

        if (LgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_h[2] = LgV2_B.Product3_f[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_h[2] = 0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
               ->Integrator_CSTATE_f[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S5>/Linear Simulator' */

    /* Integrator Block: '<S52>/Integrator' */
    {
      if (LgV2_P.Resetq_Value== 0.0) {
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE
          [0] = LgV2_B.Add_h[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE
          [0] = 0.0;
      }

      if (LgV2_P.Resetq_Value== 0.0) {
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE
          [1] = LgV2_B.Add_h[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE
          [1] = 0.0;
      }
    }

    /* Integrator Block: '<S52>/Integrator1' */
    {
      if (LgV2_P.Resets_Value== 0.0) {
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator1_CSTATE
          = LgV2_B.Subtract_l;
      } else {
        /* level reset is active*/
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator1_CSTATE
          = 0.0;
      }
    }

    /* Integrator Block: '<S10>/Integrator' */
    {
      if (LgV2_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_k[0] = LgV2_B.TmpHiddenBufferAtKpInport1[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_k[0] = 0.0;
      }

      if (LgV2_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_k[1] = LgV2_B.TmpHiddenBufferAtKpInport1[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_k[1] = 0.0;
      }

      if (LgV2_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_k[2] = LgV2_B.TmpHiddenBufferAtKpInport1[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_k[2] = 0.0;
      }
    }

    /* Derivatives for Integrator: '<S42>/Integrator' */
    ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE_j[0]
      = LgV2_B.Product_ff[0];
    ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE_j[1]
      = LgV2_B.Product_ff[1];
    ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator_CSTATE_j[2]
      = LgV2_B.Product_ff[2];

    /* Derivatives for Integrator: '<S52>/Integrator2' */
    ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator2_CSTATE[0] =
      LgV2_B.Gain_kii[0];
    ((StateDerivatives_LgV2 *) LgV2_M->ModelData.derivs)->Integrator2_CSTATE[1] =
      LgV2_B.Gain_kii[1];
  }
}

/* Model initialize function */
void LgV2_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)LgV2_M,0,
                sizeof(RT_MODEL_LgV2));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&LgV2_M->solverInfo, &LgV2_M->Timing.simTimeStep);
    rtsiSetTPtr(&LgV2_M->solverInfo, &rtmGetTPtr(LgV2_M));
    rtsiSetStepSizePtr(&LgV2_M->solverInfo, &LgV2_M->Timing.stepSize0);
    rtsiSetdXPtr(&LgV2_M->solverInfo, &LgV2_M->ModelData.derivs);
    rtsiSetContStatesPtr(&LgV2_M->solverInfo, &LgV2_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&LgV2_M->solverInfo, &LgV2_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&LgV2_M->solverInfo, (&rtmGetErrorStatus(LgV2_M)));
    rtsiSetRTModelPtr(&LgV2_M->solverInfo, LgV2_M);
  }

  rtsiSetSimTimeStep(&LgV2_M->solverInfo, MAJOR_TIME_STEP);
  LgV2_M->ModelData.intgData.y = LgV2_M->ModelData.odeY;
  LgV2_M->ModelData.intgData.f[0] = LgV2_M->ModelData.odeF[0];
  LgV2_M->ModelData.intgData.f[1] = LgV2_M->ModelData.odeF[1];
  LgV2_M->ModelData.intgData.f[2] = LgV2_M->ModelData.odeF[2];
  LgV2_M->ModelData.intgData.f[3] = LgV2_M->ModelData.odeF[3];
  LgV2_M->ModelData.intgData.f[4] = LgV2_M->ModelData.odeF[4];
  LgV2_M->ModelData.intgData.f[5] = LgV2_M->ModelData.odeF[5];
  LgV2_M->ModelData.contStates = ((real_T *) &LgV2_X);
  rtsiSetSolverData(&LgV2_M->solverInfo, (void *)&LgV2_M->ModelData.intgData);
  rtsiSetSolverName(&LgV2_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = LgV2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    LgV2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    LgV2_M->Timing.sampleTimes = (&LgV2_M->Timing.sampleTimesArray[0]);
    LgV2_M->Timing.offsetTimes = (&LgV2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    LgV2_M->Timing.sampleTimes[0] = (0.0);
    LgV2_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    LgV2_M->Timing.offsetTimes[0] = (0.0);
    LgV2_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(LgV2_M, &LgV2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = LgV2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    LgV2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(LgV2_M, -1);
  LgV2_M->Timing.stepSize0 = 0.1;
  LgV2_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(LgV2_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    LgV2_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(LgV2_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(LgV2_M->rtwLogInfo, (NULL));
    rtliSetLogT(LgV2_M->rtwLogInfo, "");
    rtliSetLogX(LgV2_M->rtwLogInfo, "");
    rtliSetLogXFinal(LgV2_M->rtwLogInfo, "");
    rtliSetSigLog(LgV2_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(LgV2_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(LgV2_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(LgV2_M->rtwLogInfo, 0);
    rtliSetLogDecimation(LgV2_M->rtwLogInfo, 1);
    rtliSetLogY(LgV2_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(LgV2_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(LgV2_M->rtwLogInfo, (NULL));
  }

  LgV2_M->solverInfoPtr = (&LgV2_M->solverInfo);
  LgV2_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&LgV2_M->solverInfo, 0.1);
  rtsiSetSolverMode(&LgV2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  LgV2_M->ModelData.blockIO = ((void *) &LgV2_B);
  (void) memset(((void *) &LgV2_B),0,
                sizeof(BlockIO_LgV2));

  /* parameters */
  LgV2_M->ModelData.defaultParam = ((real_T *) &LgV2_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &LgV2_X;
    LgV2_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_LgV2));
  }

  /* states (dwork) */
  LgV2_M->Work.dwork = ((void *) &LgV2_DWork);
  (void) memset((void *)&LgV2_DWork, 0,
                sizeof(D_Work_LgV2));
  LgV2_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  LgV2_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  LgV2_PrevZCSigState.Integrator_Reset_ZCE_f = UNINITIALIZED_ZCSIG;
  LgV2_PrevZCSigState.Integrator_Reset_ZCE_k = UNINITIALIZED_ZCSIG;
  LgV2_PrevZCSigState.Integrator1_Reset_ZCE_g = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void LgV2_terminate(void)
{
  /* ToFile Block: '<Root>/To File' */
  {
    FILE *fp = (FILE *) LgV2_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_LgV2_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(LgV2_M, "Error closing MAT-file CSE1_LgV2_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(LgV2_M, "Error reopening MAT-file CSE1_LgV2_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 37, LgV2_DWork.ToFile_IWORK.Count,
           "cse1_LgV2_data")) {
        rtmSetErrorStatus(LgV2_M,
                          "Error writing header for cse1_LgV2_data to MAT-file CSE1_LgV2_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(LgV2_M, "Error closing MAT-file CSE1_LgV2_data.mat");
        return;
      }

      LgV2_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  LgV2_output(tid);
}

void MdlUpdate(int_T tid)
{
  LgV2_update(tid);
}

void MdlInitializeSizes(void)
{
  LgV2_M->Sizes.numContStates = (17);  /* Number of continuous states */
  LgV2_M->Sizes.numY = (0);            /* Number of model outputs */
  LgV2_M->Sizes.numU = (0);            /* Number of model inputs */
  LgV2_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  LgV2_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  LgV2_M->Sizes.numBlocks = (1037);    /* Number of blocks */
  LgV2_M->Sizes.numBlockIO = (742);    /* Number of block outputs */
  LgV2_M->Sizes.numBlockPrms = (1190); /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* Derivative Block: '<S199>/Derivative1' */
  LgV2_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  LgV2_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* Derivative Block: '<S199>/Derivative' */
  LgV2_DWork.Derivative_RWORK.TimeStampA = rtInf;
  LgV2_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* Integrator Block: '<S52>/Integrator' */
  if (rtmIsFirstInitCond(LgV2_M)) {
    LgV2_X.Integrator_CSTATE[0] = 0.0;
    LgV2_X.Integrator_CSTATE[1] = 0.0;
  }

  LgV2_DWork.Integrator_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S52>/Integrator1' */
  if (rtmIsFirstInitCond(LgV2_M)) {
    LgV2_X.Integrator1_CSTATE = 0.0;
  }

  LgV2_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S10>/Integrator' */
  LgV2_X.Integrator_CSTATE_k[0] = LgV2_P.Integrator_IC;
  LgV2_X.Integrator_CSTATE_k[1] = LgV2_P.Integrator_IC;
  LgV2_X.Integrator_CSTATE_k[2] = LgV2_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<S42>/Integrator' */
  LgV2_X.Integrator_CSTATE_j[0] = LgV2_P.Integrator_IC_n[0];
  LgV2_X.Integrator_CSTATE_j[1] = LgV2_P.Integrator_IC_n[1];
  LgV2_X.Integrator_CSTATE_j[2] = LgV2_P.Integrator_IC_n[2];

  /* Derivative Block: '<S118>/Derivative' */
  LgV2_DWork.Derivative_RWORK_m.TimeStampA = rtInf;
  LgV2_DWork.Derivative_RWORK_m.TimeStampB = rtInf;

  /* InitializeConditions for Integrator: '<S52>/Integrator2' */
  LgV2_X.Integrator2_CSTATE[0] = LgV2_P.Integrator2_IC;
  LgV2_X.Integrator2_CSTATE[1] = LgV2_P.Integrator2_IC;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(LgV2_M)) {
    rtmSetFirstInitCond(LgV2_M, 0);
  }
}

void MdlStart(void)
{
  /* Start for enable SubSystem: '<S5>/Linear Simulator' */
  LgV2_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

  /* Start for Constant: '<S211>/psi_0' */
  LgV2_B.psi_0 = LgV2_P.psi_0_Value;

  /* Start for Constant: '<S211>/x_0' */
  LgV2_B.x_0 = LgV2_P.x_0_Value;

  /* Start for Constant: '<S211>/y_0' */
  LgV2_B.y_0 = LgV2_P.y_0_Value;

  /* Start for Constant: '<S212>/r_0' */
  LgV2_B.r_0 = LgV2_P.r_0_Value;

  /* Start for Constant: '<S212>/u_0' */
  LgV2_B.u_0 = LgV2_P.u_0_Value;

  /* Start for Constant: '<S212>/v_0' */
  LgV2_B.v_0 = LgV2_P.v_0_Value;

  /* Create Identity Matrix for Block: '<S213>/Inverse' */
  {
    int_T i;
    real_T *dWork = &LgV2_DWork.Inverse_DWORK4[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &LgV2_DWork.Inverse_DWORK4[0];
    while (dWork < &LgV2_DWork.Inverse_DWORK4[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  /* Integrator Block: '<S209>/Integrator' */
  if (rtmIsFirstInitCond(LgV2_M)) {
    LgV2_X.Integrator_CSTATE_f[0] = 0.0;
    LgV2_X.Integrator_CSTATE_f[1] = 0.0;
    LgV2_X.Integrator_CSTATE_f[2] = 0.0;
  }

  LgV2_DWork.Integrator_IWORK_o.IcNeedsLoading = 1;

  /* Integrator Block: '<S209>/Integrator1' */
  if (rtmIsFirstInitCond(LgV2_M)) {
    LgV2_X.Integrator1_CSTATE_h[0] = 0.0;
    LgV2_X.Integrator1_CSTATE_h[1] = 0.0;
    LgV2_X.Integrator1_CSTATE_h[2] = 0.0;
  }

  LgV2_DWork.Integrator1_IWORK_l.IcNeedsLoading = 1;

  /* end of Start for SubSystem: '<S5>/Linear Simulator' */

  /* Start for Constant: '<S95>/q_x_0' */
  LgV2_B.q_x_0 = LgV2_P.q_x_0_Value;

  /* Start for Constant: '<S95>/q_y_0' */
  LgV2_B.q_y_0 = LgV2_P.q_y_0_Value;

  /* Start for Constant: '<S52>/s_0' */
  LgV2_B.s_0 = LgV2_P.s_0_Value;

  /* ToFile Block: '<Root>/To File' */
  {
    const char *fileName = "CSE1_LgV2_data.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(LgV2_M, "Error creating .mat file CSE1_LgV2_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,37,0,"cse1_LgV2_data")) {
      rtmSetErrorStatus(LgV2_M,
                        "Error writing mat file header to file CSE1_LgV2_data.mat");
      return;
    }

    LgV2_DWork.ToFile_IWORK.Count = 0;
    LgV2_DWork.ToFile_IWORK.Decimation = -1;
    LgV2_DWork.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for enable SubSystem: '<S5>/CSE1' */
  LgV2_DWork.CSE1_MODE = SUBSYS_DISABLED;

  /* end of Start for SubSystem: '<S5>/CSE1' */
  MdlInitialize();
}

RT_MODEL_LgV2 *LgV2(void)
{
  LgV2_initialize(1);
  return LgV2_M;
}

void MdlTerminate(void)
{
  LgV2_terminate();
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
#ifdef NI_ROOTMODEL_LgV2
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

   case 14:
    //Type is fixed-point and NiUseScaledFixedPoint is on. Call GetValueByDataType for its real type and then scale.
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex) * 1.0 * pow(2,-6) +
      0.0;

   case 15:
    //Type is fixed-point and NiUseScaledFixedPoint is on. Call GetValueByDataType for its real type and then scale.
    return NIRT_GetValueByDataType(ptr,subindex,5,Complex) * 1.0 * pow(2,-6) +
      0.0;

   case 18:
    //Type is renamed. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 19:
    //Type is fixed-point and NiUseScaledFixedPoint is on. Call GetValueByDataType for its real type and then scale.
    return NIRT_GetValueByDataType(ptr,subindex,7,Complex) * 1.0 * pow(2,-6) +
      0.0;

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 35:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 36:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 37:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 38:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 39:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,15,Complex);

   case 40:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 41:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 42:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 43:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 44:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 50:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 51:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 52:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,10,Complex);

   case 53:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,11,Complex);

   case 54:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 55:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 56:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 57:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 58:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 59:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 68:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 69:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 70:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 71:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 72:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 73:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 74:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 75:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 76:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);
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

   case 14:
    //Type is fixed-point and NiUseScaledFixedPoint is on. Call SetValueByDataType for its real type on the unscaled value.
    return NIRT_SetValueByDataType(ptr,subindex,(value - 0.0)/(1.0 * pow(2,-6)),
      3,Complex);

   case 15:
    //Type is fixed-point and NiUseScaledFixedPoint is on. Call SetValueByDataType for its real type on the unscaled value.
    return NIRT_SetValueByDataType(ptr,subindex,(value - 0.0)/(1.0 * pow(2,-6)),
      5,Complex);

   case 18:
    //Type is renamed. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 19:
    //Type is fixed-point and NiUseScaledFixedPoint is on. Call SetValueByDataType for its real type on the unscaled value.
    return NIRT_SetValueByDataType(ptr,subindex,(value - 0.0)/(1.0 * pow(2,-6)),
      7,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 35:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 36:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 37:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 38:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 39:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,15,Complex);

   case 40:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 41:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 42:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 43:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 44:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 50:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 51:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 52:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,10,Complex);

   case 53:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,11,Complex);

   case 54:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 55:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 56:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 57:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 58:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 59:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 68:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 69:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 70:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 71:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 72:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 73:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 74:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 75:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 76:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern LgV2_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Naviagation Systems/Qualisys 6 DOF/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(LgV2_B.QTMIn, count, data[index++], 44, 0);
    }
  } else {
    index += 9;
  }

  // HMI/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&LgV2_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&LgV2_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&LgV2_B.SITzAI2, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 12;
}

double ni_extout[7];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Plants/CSE1/Bow Thruster/SIT PWM0 BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Switch2_d,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.VSPSStarboard,0,0,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 7;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

  // Plants/CSE1/Bow Thruster/SIT PWM0 BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Switch2_d,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo1,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo2,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo3,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.Servo4,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.VSPSPort,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&LgV2_B.VSPSStarboard,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "lgv2/Naviagation Systems/Controller Input Selector/Value", offsetof
    (Parameters_LgV2, ControllerInputSelector_Value), 21, 1, 2, 0, "", 0 },

  { 1, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain", offsetof
    (Parameters_LgV2, QTMIn2Error_Gain), 21, 1, 2, 2, "", 0 },

  { 2, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain", offsetof
    (Parameters_LgV2, QTMIn9Residual_Gain), 21, 1, 2, 4, "", 0 },

  { 3, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain", offsetof
    (Parameters_LgV2, QTMIn3_Gain), 21, 1, 2, 6, "", 0 },

  { 4, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain", offsetof
    (Parameters_LgV2, mm2mx_Gain), 21, 1, 2, 8, "", 0 },

  { 5, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain", offsetof
    (Parameters_LgV2, QTMIn4_Gain), 21, 1, 2, 10, "", 0 },

  { 6, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain", offsetof
    (Parameters_LgV2, mm2my_Gain), 21, 1, 2, 12, "", 0 },

  { 7, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain", offsetof
    (Parameters_LgV2, QTMIn6_Gain), 21, 1, 2, 14, "", 0 },

  { 8, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain", offsetof
    (Parameters_LgV2, d2ryaw_Gain), 21, 1, 2, 16, "", 0 },

  { 9, "lgv2/Plants/Enable Linear Simulator/Value", offsetof(Parameters_LgV2,
    EnableLinearSimulator_Value), 21, 1, 2, 18, "", 0 },

  { 10, "lgv2/Naviagation Systems/etadot_surge/Gain", offsetof(Parameters_LgV2,
    etadot_surge_Gain), 21, 1, 2, 20, "", 0 },

  { 11, "lgv2/Naviagation Systems/etadot_sway/Gain", offsetof(Parameters_LgV2,
    etadot_sway_Gain), 21, 1, 2, 22, "", 0 },

  { 12, "lgv2/Naviagation Systems/etadot_yaw/Gain", offsetof(Parameters_LgV2,
    etadot_yaw_Gain), 21, 1, 2, 24, "", 0 },

  { 13, "lgv2/Naviagation Systems/eta_surge/Gain", offsetof(Parameters_LgV2,
    eta_surge_Gain), 21, 1, 2, 26, "", 0 },

  { 14, "lgv2/Naviagation Systems/eta_sway/Gain", offsetof(Parameters_LgV2,
    eta_sway_Gain), 21, 1, 2, 28, "", 0 },

  { 15, "lgv2/Naviagation Systems/eta_yaw/Gain", offsetof(Parameters_LgV2,
    eta_yaw_Gain), 21, 1, 2, 30, "", 0 },

  { 16, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain", offsetof
    (Parameters_LgV2, QTMIn8_Gain), 21, 1, 2, 32, "", 0 },

  { 17, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain", offsetof
    (Parameters_LgV2, d2rroll_Gain), 21, 1, 2, 34, "", 0 },

  { 18, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain", offsetof
    (Parameters_LgV2, QTMIn7_Gain), 21, 1, 2, 36, "", 0 },

  { 19, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain", offsetof
    (Parameters_LgV2, d2rpitch_Gain), 21, 1, 2, 38, "", 0 },

  { 20, "lgv2/Naviagation Systems/Qualisys 6 DOF/Constant1/Value", offsetof
    (Parameters_LgV2, Constant1_Value), 36, 9, 2, 40, "", 0 },

  { 21, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain", offsetof
    (Parameters_LgV2, QTMIn5_Gain), 21, 1, 2, 42, "", 0 },

  { 22, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain", offsetof
    (Parameters_LgV2, mm2mz_Gain), 21, 1, 2, 44, "", 0 },

  { 23, "lgv2/Naviagation Systems/nu_surge/Gain", offsetof(Parameters_LgV2,
    nu_surge_Gain), 21, 1, 2, 46, "", 0 },

  { 24, "lgv2/Naviagation Systems/nu_sway/Gain", offsetof(Parameters_LgV2,
    nu_sway_Gain), 21, 1, 2, 48, "", 0 },

  { 25, "lgv2/Naviagation Systems/nu_yaw/Gain", offsetof(Parameters_LgV2,
    nu_yaw_Gain), 21, 1, 2, 50, "", 0 },

  { 26, "lgv2/HMI/DP Input/x_d/Value", offsetof(Parameters_LgV2, x_d_Value), 21,
    1, 2, 52, "", 0 },

  { 27, "lgv2/Guidance Systems/DP/eta_d DP N/Gain", offsetof(Parameters_LgV2,
    eta_dDPN_Gain), 21, 1, 2, 54, "", 0 },

  { 28, "lgv2/HMI/DP Input/y_d/Value", offsetof(Parameters_LgV2, y_d_Value), 21,
    1, 2, 56, "", 0 },

  { 29, "lgv2/Guidance Systems/DP/eta_d DP E/Gain", offsetof(Parameters_LgV2,
    eta_dDPE_Gain), 21, 1, 2, 58, "", 0 },

  { 30, "lgv2/HMI/DP Input/psi_d/Value", offsetof(Parameters_LgV2, psi_d_Value),
    21, 1, 2, 60, "", 0 },

  { 31, "lgv2/HMI/DP Input/Degrees to Radians/Gain1/Gain", offsetof
    (Parameters_LgV2, Gain1_Gain), 21, 1, 2, 62, "", 0 },

  { 32, "lgv2/Guidance Systems/DP/eta_d DP Psi/Gain", offsetof(Parameters_LgV2,
    eta_dDPPsi_Gain), 21, 1, 2, 64, "", 0 },

  { 33, "lgv2/Control Systems/LgV design 2/Update laws/Reset q/Value", offsetof
    (Parameters_LgV2, Resetq_Value), 21, 1, 2, 66, "", 0 },

  { 34, "lgv2/Control Systems/LgV design 2/Update laws/q_0/q_x_0/Value",
    offsetof(Parameters_LgV2, q_x_0_Value), 21, 1, 2, 68, "", 0 },

  { 35, "lgv2/Control Systems/LgV design 2/Update laws/q_0/q_y_0/Value",
    offsetof(Parameters_LgV2, q_y_0_Value), 21, 1, 2, 70, "", 0 },

  { 36, "lgv2/HMI/Path-following input/x_2/Value", offsetof(Parameters_LgV2,
    x_2_Value), 21, 1, 2, 72, "", 0 },

  { 37, "lgv2/HMI/Path-following input/x_1/Value", offsetof(Parameters_LgV2,
    x_1_Value), 21, 1, 2, 74, "", 0 },

  { 38, "lgv2/HMI/Path-following input/y_2/Value", offsetof(Parameters_LgV2,
    y_2_Value), 21, 1, 2, 76, "", 0 },

  { 39, "lgv2/HMI/Path-following input/y_1/Value", offsetof(Parameters_LgV2,
    y_1_Value), 21, 1, 2, 78, "", 0 },

  { 40, "lgv2/Guidance Systems/Path-following/Path/Path Selector/Value",
    offsetof(Parameters_LgV2, PathSelector_Value), 21, 1, 2, 80, "", 0 },

  { 41, "lgv2/HMI/Path-following input/r_x/Value", offsetof(Parameters_LgV2,
    r_x_Value), 21, 1, 2, 82, "", 0 },

  { 42, "lgv2/Control Systems/LgV design 2/Update laws/Reset s/Value", offsetof
    (Parameters_LgV2, Resets_Value), 21, 1, 2, 84, "", 0 },

  { 43, "lgv2/Control Systems/LgV design 2/Update laws/s_0/Value", offsetof
    (Parameters_LgV2, s_0_Value), 21, 1, 2, 86, "", 0 },

  { 44, "lgv2/HMI/Path-following input/k/Value", offsetof(Parameters_LgV2,
    k_Value), 21, 1, 2, 88, "", 0 },

  { 45,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain), 21, 1, 2, 90, "", 0 },

  { 46, "lgv2/HMI/Path-following input/r_y/Value", offsetof(Parameters_LgV2,
    r_y_Value), 21, 1, 2, 92, "", 0 },

  { 47,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value), 21, 1, 2, 94, "", 0 },

  { 48,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_p), 21, 1, 2, 96, "", 0 },

  { 49,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat), 21, 1, 2, 98, "", 0 },

  { 50,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat), 21, 1, 2, 100, "", 0 },

  { 51,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_m), 21, 1, 2, 102, "", 0 },

  { 52,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_h), 21, 1, 2, 104, "", 0 },

  { 53,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_g), 21, 1, 2, 106, "", 0 },

  { 54,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_n), 21, 1, 2, 108, "", 0 },

  { 55,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_b), 21, 1, 2, 110, "", 0 },

  { 56,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_i), 21, 1, 2, 112, "", 0 },

  { 57,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_g), 21, 1, 2, 114, "", 0 },

  { 58,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_p), 21, 1, 2, 116, "", 0 },

  { 59,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_o), 21, 1, 2, 118, "", 0 },

  { 60, "lgv2/Guidance Systems/Path-following/Path/saturation/x_dmax/Value",
    offsetof(Parameters_LgV2, x_dmax_Value), 21, 1, 2, 120, "", 0 },

  { 61, "lgv2/HMI/Path-following input/origin_x/Value", offsetof(Parameters_LgV2,
    origin_x_Value), 21, 1, 2, 122, "", 0 },

  { 62, "lgv2/HMI/Path-following input/origo_y/Value", offsetof(Parameters_LgV2,
    origo_y_Value), 21, 1, 2, 124, "", 0 },

  { 63,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_o), 21, 1, 2, 126, "", 0 },

  { 64, "lgv2/Guidance Systems/Path-following/Path/saturation/x_dmin/Value",
    offsetof(Parameters_LgV2, x_dmin_Value), 21, 1, 2, 128, "", 0 },

  { 65, "lgv2/Guidance Systems/Path-following/Path/saturation/y_dmax/Value",
    offsetof(Parameters_LgV2, y_dmax_Value), 21, 1, 2, 130, "", 0 },

  { 66, "lgv2/Guidance Systems/Path-following/Path/saturation/y_dmin/Value",
    offsetof(Parameters_LgV2, y_dmin_Value), 21, 1, 2, 132, "", 0 },

  { 67, "lgv2/Guidance Systems/Path-following/Delta/Value", offsetof
    (Parameters_LgV2, Delta_Value), 21, 1, 2, 134, "", 0 },

  { 68,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_pe), 21, 1, 2, 136, "", 0 },

  { 69,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_k), 21, 1, 2, 138, "", 0 },

  { 70,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_p), 21, 1, 2, 140, "", 0 },

  { 71,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_pg), 21, 1, 2, 142, "", 0 },

  { 72,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_od), 21, 1, 2, 144, "", 0 },

  { 73,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_m), 21, 1, 2, 146, "", 0 },

  { 74,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_l), 21, 1, 2, 148, "", 0 },

  { 75,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_i), 21, 1, 2, 150, "", 0 },

  { 76,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_iq), 21, 1, 2, 152, "", 0 },

  { 77,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_f), 21, 1, 2, 154, "", 0 },

  { 78,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_e), 21, 1, 2, 156, "", 0 },

  { 79,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_k), 21, 1, 2, 158, "", 0 },

  { 80, "lgv2/Guidance Systems/q_x/Gain", offsetof(Parameters_LgV2, q_x_Gain),
    21, 1, 2, 160, "", 0 },

  { 81, "lgv2/Guidance Systems/q_y/Gain", offsetof(Parameters_LgV2, q_y_Gain),
    21, 1, 2, 162, "", 0 },

  { 82, "lgv2/Guidance Systems/psi_los/Gain", offsetof(Parameters_LgV2,
    psi_los_Gain), 21, 1, 2, 164, "", 0 },

  { 83, "lgv2/Guidance Systems/path x_d/Gain", offsetof(Parameters_LgV2,
    pathx_d_Gain), 21, 1, 2, 166, "", 0 },

  { 84, "lgv2/Guidance Systems/path y_d/Gain", offsetof(Parameters_LgV2,
    pathy_d_Gain), 21, 1, 2, 168, "", 0 },

  { 85, "lgv2/Guidance Systems/path psi_d/Gain", offsetof(Parameters_LgV2,
    pathpsi_d_Gain), 21, 1, 2, 170, "", 0 },

  { 86, "lgv2/HMI/Path-following input/u_d/Value", offsetof(Parameters_LgV2,
    u_d_Value), 21, 1, 2, 172, "", 0 },

  { 87,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_oc), 21, 1, 2, 174, "", 0 },

  { 88, "lgv2/Control Systems/Control Mode/Value", offsetof(Parameters_LgV2,
    ControlMode_Value), 21, 1, 2, 176, "", 0 },

  { 89, "lgv2/Control Systems/PS3 input/AS_LY/Value", offsetof(Parameters_LgV2,
    AS_LY_Value), 21, 1, 2, 178, "", 0 },

  { 90, "lgv2/Control Systems/PS3 input/ScalingLY/Gain", offsetof
    (Parameters_LgV2, ScalingLY_Gain), 21, 1, 2, 180, "", 0 },

  { 91, "lgv2/Control Systems/PS3 u input control/PS3 u_1/Gain", offsetof
    (Parameters_LgV2, PS3u_1_Gain), 21, 1, 2, 182, "", 0 },

  { 92, "lgv2/Control Systems/PS3 input/AS_LX/Value", offsetof(Parameters_LgV2,
    AS_LX_Value), 21, 1, 2, 184, "", 0 },

  { 93, "lgv2/Control Systems/PS3 input/ScalingLX/Gain", offsetof
    (Parameters_LgV2, ScalingLX_Gain), 21, 1, 2, 186, "", 0 },

  { 94, "lgv2/Control Systems/PS3 u input control/PS3 u_2/Gain", offsetof
    (Parameters_LgV2, PS3u_2_Gain), 21, 1, 2, 188, "", 0 },

  { 95, "lgv2/Control Systems/PS3 input/AS_RY/Value", offsetof(Parameters_LgV2,
    AS_RY_Value), 21, 1, 2, 190, "", 0 },

  { 96, "lgv2/Control Systems/PS3 input/ScalingRY/Gain", offsetof
    (Parameters_LgV2, ScalingRY_Gain), 21, 1, 2, 192, "", 0 },

  { 97, "lgv2/Control Systems/PS3 u input control/PS3 u_3/Gain", offsetof
    (Parameters_LgV2, PS3u_3_Gain), 21, 1, 2, 194, "", 0 },

  { 98, "lgv2/Control Systems/PS3 input/AS_RX/Value", offsetof(Parameters_LgV2,
    AS_RX_Value), 21, 1, 2, 196, "", 0 },

  { 99, "lgv2/Control Systems/PS3 input/Scaling_RX/Gain", offsetof
    (Parameters_LgV2, Scaling_RX_Gain), 21, 1, 2, 198, "", 0 },

  { 100, "lgv2/Control Systems/PS3 u input control/PS3 u_4/Gain", offsetof
    (Parameters_LgV2, PS3u_4_Gain), 21, 1, 2, 200, "", 0 },

  { 101, "lgv2/Control Systems/PS3 input/L2/Value", offsetof(Parameters_LgV2,
    L2_Value), 21, 1, 2, 202, "", 0 },

  { 102, "lgv2/Control Systems/PS3 input/R2/Value", offsetof(Parameters_LgV2,
    R2_Value), 21, 1, 2, 204, "", 0 },

  { 103, "lgv2/Control Systems/PS3 u input control/PS3 u_5/Gain", offsetof
    (Parameters_LgV2, PS3u_5_Gain), 21, 1, 2, 206, "", 0 },

  { 104, "lgv2/Control Systems/PS3 input/PS3_BT_Power/Value", offsetof
    (Parameters_LgV2, PS3_BT_Power_Value), 21, 1, 2, 208, "", 0 },

  { 105, "lgv2/Control Systems/PS3 input/PS3_VSP_Speed/Value", offsetof
    (Parameters_LgV2, PS3_VSP_Speed_Value), 21, 1, 2, 210, "", 0 },

  { 106,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_LgV2, T_e11_Value), 21, 1, 2, 212, "", 0 },

  { 107,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_LgV2, T_e21_Value), 21, 1, 2, 214, "", 0 },

  { 108,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_LgV2, l_y1_Value), 21, 1, 2, 216, "", 0 },

  { 109,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_LgV2, T_e12_Value), 21, 1, 2, 218, "", 0 },

  { 110,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_LgV2, T_e22_Value), 21, 1, 2, 220, "", 0 },

  { 111,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_LgV2, l_x1_Value), 21, 1, 2, 222, "", 0 },

  { 112,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_LgV2, l_x1_Gain), 21, 1, 2, 224, "", 0 },

  { 113,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_LgV2, T_e13_Value), 21, 1, 2, 226, "", 0 },

  { 114,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_LgV2, T_e23_Value), 21, 1, 2, 228, "", 0 },

  { 115,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_LgV2, l_y2_Value), 21, 1, 2, 230, "", 0 },

  { 116,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_LgV2, l_y2_Gain), 21, 1, 2, 232, "", 0 },

  { 117,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_LgV2, T_e14_Value), 21, 1, 2, 234, "", 0 },

  { 118,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_LgV2, T_e24_Value), 21, 1, 2, 236, "", 0 },

  { 119,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_LgV2, l_x2_Value), 21, 1, 2, 238, "", 0 },

  { 120,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_LgV2, l_x2_Gain), 21, 1, 2, 240, "", 0 },

  { 121,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_LgV2, T_e15_Value), 21, 1, 2, 242, "", 0 },

  { 122,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_LgV2, T_e25_Value), 21, 1, 2, 244, "", 0 },

  { 123,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_LgV2, l_x3_Value), 21, 1, 2, 246, "", 0 },

  { 124,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_j), 21, 1, 2, 248, "", 0 },

  { 125,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_j), 21, 1, 2, 250, "", 0 },

  { 126,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_h), 21, 1, 2, 252, "", 0 },

  { 127,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_g), 21, 1, 2, 254, "", 0 },

  { 128,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_g), 21, 1, 2, 256, "", 0 },

  { 129,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_m), 21, 1, 2, 258, "", 0 },

  { 130,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_fh), 21, 1, 2, 260, "", 0 },

  { 131,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_gt), 21, 1, 2, 262, "", 0 },

  { 132, "lgv2/Control Systems/DP control/DP controller/Kp/Gain", offsetof
    (Parameters_LgV2, Kp_Gain), 36, 9, 2, 264, "", 0 },

  { 133, "lgv2/Control Systems/DP control/DP controller/K_p_surge_scale/Gain",
    offsetof(Parameters_LgV2, K_p_surge_scale_Gain), 21, 1, 2, 266, "", 0 },

  { 134, "lgv2/Control Systems/DP control/DP controller/K_p_sway_scale/Gain",
    offsetof(Parameters_LgV2, K_p_sway_scale_Gain), 21, 1, 2, 268, "", 0 },

  { 135, "lgv2/Control Systems/DP control/DP controller/K_p_yaw_scale/Gain",
    offsetof(Parameters_LgV2, K_p_yaw_scale_Gain), 21, 1, 2, 270, "", 0 },

  { 136,
    "lgv2/Control Systems/DP control/DP controller/Reset_DP_integrator/Value",
    offsetof(Parameters_LgV2, Reset_DP_integrator_Value), 21, 1, 2, 272, "", 0 },

  { 137,
    "lgv2/Control Systems/DP control/DP controller/Integrator/InitialCondition",
    offsetof(Parameters_LgV2, Integrator_IC), 21, 1, 2, 274, "", 0 },

  { 138, "lgv2/Control Systems/DP control/DP controller/Ki/Gain", offsetof
    (Parameters_LgV2, Ki_Gain), 36, 9, 2, 276, "", 0 },

  { 139, "lgv2/Control Systems/DP control/DP controller/K_i_surge_scale/Gain",
    offsetof(Parameters_LgV2, K_i_surge_scale_Gain), 21, 1, 2, 278, "", 0 },

  { 140, "lgv2/Control Systems/DP control/DP controller/K_i_sway_scale/Gain",
    offsetof(Parameters_LgV2, K_i_sway_scale_Gain), 21, 1, 2, 280, "", 0 },

  { 141, "lgv2/Control Systems/DP control/DP controller/K_i_yaw_scale/Gain",
    offsetof(Parameters_LgV2, K_i_yaw_scale_Gain), 21, 1, 2, 282, "", 0 },

  { 142, "lgv2/Control Systems/DP control/DP controller/Kd/Gain", offsetof
    (Parameters_LgV2, Kd_Gain), 36, 9, 2, 284, "", 0 },

  { 143, "lgv2/Control Systems/DP control/DP controller/K_d_surge_scale/Gain",
    offsetof(Parameters_LgV2, K_d_surge_scale_Gain), 21, 1, 2, 286, "", 0 },

  { 144, "lgv2/Control Systems/DP control/DP controller/K_d_sway_scale/Gain",
    offsetof(Parameters_LgV2, K_d_sway_scale_Gain), 21, 1, 2, 288, "", 0 },

  { 145, "lgv2/Control Systems/DP control/DP controller/K_d_yaw_scale/Gain",
    offsetof(Parameters_LgV2, K_d_yaw_scale_Gain), 21, 1, 2, 290, "", 0 },

  { 146,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start), 21, 1, 2, 292, "", 0 },

  { 147,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End), 21, 1, 2, 294, "", 0 },

  { 148,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_c), 21, 1, 2, 296, "", 0 },

  { 149,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_ek), 21, 1, 2, 298, "", 0 },

  { 150,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_LgV2, f_10_XData), 44, 9, 2, 300, "", 0 },

  { 151,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_LgV2, f_10_YData), 44, 9, 2, 302, "", 0 },

  { 152,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_LgV2, f_10_Value), 21, 1, 2, 304, "", 0 },

  { 153,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_LgV2, f_10_XData_j), 68, 10, 2, 306, "", 0 },

  { 154,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_LgV2, f_10_YData_h), 68, 10, 2, 308, "", 0 },

  { 155,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start_c), 21, 1, 2, 310, "", 0 },

  { 156,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End_e), 21, 1, 2, 312, "", 0 },

  { 157,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_d), 21, 1, 2, 314, "", 0 },

  { 158,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_m), 21, 1, 2, 316, "", 0 },

  { 159,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_go), 21, 1, 2, 318, "", 0 },

  { 160,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_LgV2, f_20_XData), 69, 11, 2, 320, "", 0 },

  { 161,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_LgV2, f_20_YData), 69, 11, 2, 322, "", 0 },

  { 162,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_LgV2, f_20_Value), 21, 1, 2, 324, "", 0 },

  { 163,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_LgV2, f_20_XData_b), 68, 10, 2, 326, "", 0 },

  { 164,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_LgV2, f_20_YData_g), 68, 10, 2, 328, "", 0 },

  { 165,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start_n), 21, 1, 2, 330, "", 0 },

  { 166,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End_n), 21, 1, 2, 332, "", 0 },

  { 167,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_oz), 21, 1, 2, 334, "", 0 },

  { 168,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_j), 21, 1, 2, 336, "", 0 },

  { 169,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_LgV2, f_30_XData), 70, 8, 2, 338, "", 0 },

  { 170,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_LgV2, f_30_YData), 70, 8, 2, 340, "", 0 },

  { 171,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_LgV2, f_30_Value), 21, 1, 2, 342, "", 0 },

  { 172,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_LgV2, f_30_XData_k), 69, 11, 2, 344, "", 0 },

  { 173,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_LgV2, f_30_YData_b), 69, 11, 2, 346, "", 0 },

  { 174,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start_h), 21, 1, 2, 348, "", 0 },

  { 175,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End_j), 21, 1, 2, 350, "", 0 },

  { 176,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_a), 21, 1, 2, 352, "", 0 },

  { 177,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_b), 21, 1, 2, 354, "", 0 },

  { 178,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_LgV2, f_40_XData), 68, 10, 2, 356, "", 0 },

  { 179,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_LgV2, f_40_YData), 68, 10, 2, 358, "", 0 },

  { 180,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_LgV2, f_40_Value), 21, 1, 2, 360, "", 0 },

  { 181,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_LgV2, f_40_XData_j), 71, 7, 2, 362, "", 0 },

  { 182,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_LgV2, f_40_YData_f), 71, 7, 2, 364, "", 0 },

  { 183,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start_l), 21, 1, 2, 366, "", 0 },

  { 184,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End_a), 21, 1, 2, 368, "", 0 },

  { 185,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_om), 21, 1, 2, 370, "", 0 },

  { 186,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_cn), 21, 1, 2, 372, "", 0 },

  { 187,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_LgV2, f_50_XData), 26, 3, 2, 374, "", 0 },

  { 188,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_LgV2, f_50_YData), 26, 3, 2, 376, "", 0 },

  { 189,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_LgV2, f_50_Value), 21, 1, 2, 378, "", 0 },

  { 190,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_LgV2, f_50_XData_c), 26, 3, 2, 380, "", 0 },

  { 191,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_LgV2, f_50_YData_m), 26, 3, 2, 382, "", 0 },

  { 192, "lgv2/Control Systems/DP control/Saturation/UpperLimit", offsetof
    (Parameters_LgV2, Saturation_UpperSat_d), 21, 1, 2, 384, "", 0 },

  { 193, "lgv2/Control Systems/DP control/Saturation/LowerLimit", offsetof
    (Parameters_LgV2, Saturation_LowerSat_d), 21, 1, 2, 386, "", 0 },

  { 194, "lgv2/Control Systems/DP control/BT_power_limit/Value", offsetof
    (Parameters_LgV2, BT_power_limit_Value), 21, 1, 2, 388, "", 0 },

  { 195, "lgv2/Control Systems/DP control/VSP_speeds/Value", offsetof
    (Parameters_LgV2, VSP_speeds_Value), 21, 1, 2, 390, "", 0 },

  { 196,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_LgV2, T_e11_Value_i), 21, 1, 2, 392, "", 0 },

  { 197,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_LgV2, T_e21_Value_m), 21, 1, 2, 394, "", 0 },

  { 198,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_LgV2, l_y1_Value_a), 21, 1, 2, 396, "", 0 },

  { 199,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_LgV2, T_e12_Value_c), 21, 1, 2, 398, "", 0 },

  { 200,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_LgV2, T_e22_Value_c), 21, 1, 2, 400, "", 0 },

  { 201,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_LgV2, l_x1_Value_p), 21, 1, 2, 402, "", 0 },

  { 202,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_LgV2, l_x1_Gain_h), 21, 1, 2, 404, "", 0 },

  { 203,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_LgV2, T_e13_Value_g), 21, 1, 2, 406, "", 0 },

  { 204,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_LgV2, T_e23_Value_h), 21, 1, 2, 408, "", 0 },

  { 205,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_LgV2, l_y2_Value_c), 21, 1, 2, 410, "", 0 },

  { 206,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_LgV2, l_y2_Gain_o), 21, 1, 2, 412, "", 0 },

  { 207,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_LgV2, T_e14_Value_b), 21, 1, 2, 414, "", 0 },

  { 208,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_LgV2, T_e24_Value_c), 21, 1, 2, 416, "", 0 },

  { 209,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_LgV2, l_x2_Value_k), 21, 1, 2, 418, "", 0 },

  { 210,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_LgV2, l_x2_Gain_e), 21, 1, 2, 420, "", 0 },

  { 211,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_LgV2, T_e15_Value_l), 21, 1, 2, 422, "", 0 },

  { 212,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_LgV2, T_e25_Value_o), 21, 1, 2, 424, "", 0 },

  { 213,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_LgV2, l_x3_Value_m), 21, 1, 2, 426, "", 0 },

  { 214, "lgv2/Control Systems/LgV design 2/R(psi)/R31/Value", offsetof
    (Parameters_LgV2, R31_Value), 21, 1, 2, 428, "", 0 },

  { 215, "lgv2/Control Systems/LgV design 2/R(psi)/-1/Gain", offsetof
    (Parameters_LgV2, u_Gain), 21, 1, 2, 430, "", 0 },

  { 216, "lgv2/Control Systems/LgV design 2/R(psi)/R32/Value", offsetof
    (Parameters_LgV2, R32_Value), 21, 1, 2, 432, "", 0 },

  { 217, "lgv2/Control Systems/LgV design 2/R(psi)/R13/Value", offsetof
    (Parameters_LgV2, R13_Value), 21, 1, 2, 434, "", 0 },

  { 218, "lgv2/Control Systems/LgV design 2/R(psi)/R23/Value", offsetof
    (Parameters_LgV2, R23_Value), 21, 1, 2, 436, "", 0 },

  { 219, "lgv2/Control Systems/LgV design 2/R(psi)/R33/Value", offsetof
    (Parameters_LgV2, R33_Value), 21, 1, 2, 438, "", 0 },

  { 220, "lgv2/Control Systems/LgV design 2/K_i_Surge/Value", offsetof
    (Parameters_LgV2, K_i_Surge_Value), 21, 1, 2, 440, "", 0 },

  { 221, "lgv2/Control Systems/LgV design 2/K_i/21/Value", offsetof
    (Parameters_LgV2, u_Value), 21, 1, 2, 442, "", 0 },

  { 222, "lgv2/Control Systems/LgV design 2/K_i/31/Value", offsetof
    (Parameters_LgV2, u_Value_e), 21, 1, 2, 444, "", 0 },

  { 223, "lgv2/Control Systems/LgV design 2/K_i/12/Value", offsetof
    (Parameters_LgV2, u_Value_h), 21, 1, 2, 446, "", 0 },

  { 224, "lgv2/Control Systems/LgV design 2/K_i_Sway/Value", offsetof
    (Parameters_LgV2, K_i_Sway_Value), 21, 1, 2, 448, "", 0 },

  { 225, "lgv2/Control Systems/LgV design 2/K_i/32/Value", offsetof
    (Parameters_LgV2, u_Value_h2), 21, 1, 2, 450, "", 0 },

  { 226, "lgv2/Control Systems/LgV design 2/K_i/13/Value", offsetof
    (Parameters_LgV2, u_Value_n), 21, 1, 2, 452, "", 0 },

  { 227, "lgv2/Control Systems/LgV design 2/K_i/23/Value", offsetof
    (Parameters_LgV2, u_Value_h3), 21, 1, 2, 454, "", 0 },

  { 228, "lgv2/Control Systems/LgV design 2/K_i_Yaw/Value", offsetof
    (Parameters_LgV2, K_i_Yaw_Value), 21, 1, 2, 456, "", 0 },

  { 229,
    "lgv2/Control Systems/LgV design 2/Integral action state/Integrator/InitialCondition",
    offsetof(Parameters_LgV2, Integrator_IC_n), 26, 3, 2, 458, "", 0 },

  { 230, "lgv2/Control Systems/LgV design 2/K_d_Surge/Value", offsetof
    (Parameters_LgV2, K_d_Surge_Value), 21, 1, 2, 460, "", 0 },

  { 231, "lgv2/Control Systems/LgV design 2/K_d/21/Value", offsetof
    (Parameters_LgV2, u_Value_m), 21, 1, 2, 462, "", 0 },

  { 232, "lgv2/Control Systems/LgV design 2/K_d/31/Value", offsetof
    (Parameters_LgV2, u_Value_hb), 21, 1, 2, 464, "", 0 },

  { 233, "lgv2/Control Systems/LgV design 2/K_d/12/Value", offsetof
    (Parameters_LgV2, u_Value_f), 21, 1, 2, 466, "", 0 },

  { 234, "lgv2/Control Systems/LgV design 2/K_d_Sway/Value", offsetof
    (Parameters_LgV2, K_d_Sway_Value), 21, 1, 2, 468, "", 0 },

  { 235, "lgv2/Control Systems/LgV design 2/K_d/32/Value", offsetof
    (Parameters_LgV2, u_Value_j), 21, 1, 2, 470, "", 0 },

  { 236, "lgv2/Control Systems/LgV design 2/K_d/13/Value", offsetof
    (Parameters_LgV2, u_Value_i), 21, 1, 2, 472, "", 0 },

  { 237, "lgv2/Control Systems/LgV design 2/K_d/23/Value", offsetof
    (Parameters_LgV2, u_Value_d), 21, 1, 2, 474, "", 0 },

  { 238, "lgv2/Control Systems/LgV design 2/K_d_Yaw/Value", offsetof
    (Parameters_LgV2, K_d_Yaw_Value), 21, 1, 2, 476, "", 0 },

  { 239, "lgv2/Control Systems/LgV design 2/Control law/1/Value", offsetof
    (Parameters_LgV2, _Value), 21, 1, 2, 478, "", 0 },

  { 240, "lgv2/Control Systems/LgV design 2/kappa_1/Value", offsetof
    (Parameters_LgV2, kappa_1_Value), 21, 1, 2, 480, "", 0 },

  { 241, "lgv2/Control Systems/LgV design 2/Control law/4/Gain", offsetof
    (Parameters_LgV2, _Gain), 21, 1, 2, 482, "", 0 },

  { 242, "lgv2/Control Systems/LgV design 2/K_p_Surge/Value", offsetof
    (Parameters_LgV2, K_p_Surge_Value), 21, 1, 2, 484, "", 0 },

  { 243, "lgv2/Control Systems/LgV design 2/K_p/21/Value", offsetof
    (Parameters_LgV2, u_Value_ho), 21, 1, 2, 486, "", 0 },

  { 244, "lgv2/Control Systems/LgV design 2/K_p/31/Value", offsetof
    (Parameters_LgV2, u_Value_k), 21, 1, 2, 488, "", 0 },

  { 245, "lgv2/Control Systems/LgV design 2/K_p/12/Value", offsetof
    (Parameters_LgV2, u_Value_fw), 21, 1, 2, 490, "", 0 },

  { 246, "lgv2/Control Systems/LgV design 2/K_p_Sway/Value", offsetof
    (Parameters_LgV2, K_p_Sway_Value), 21, 1, 2, 492, "", 0 },

  { 247, "lgv2/Control Systems/LgV design 2/K_p/32/Value", offsetof
    (Parameters_LgV2, u_Value_hc), 21, 1, 2, 494, "", 0 },

  { 248, "lgv2/Control Systems/LgV design 2/K_p/13/Value", offsetof
    (Parameters_LgV2, u_Value_fu), 21, 1, 2, 496, "", 0 },

  { 249, "lgv2/Control Systems/LgV design 2/K_p/23/Value", offsetof
    (Parameters_LgV2, u_Value_mz), 21, 1, 2, 498, "", 0 },

  { 250, "lgv2/Control Systems/LgV design 2/K_p_Yaw/Value", offsetof
    (Parameters_LgV2, K_p_Yaw_Value), 21, 1, 2, 500, "", 0 },

  { 251, "lgv2/Control Systems/LgV design 2/Virtual control/I/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_bc), 36, 9, 2, 502, "", 0 },

  { 252,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_a), 21, 1, 2, 504, "", 0 },

  { 253,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_gd), 21, 1, 2, 506, "", 0 },

  { 254,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_id), 21, 1, 2, 508, "", 0 },

  { 255,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_j), 21, 1, 2, 510, "", 0 },

  { 256,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_cj), 21, 1, 2, 512, "", 0 },

  { 257,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_oh), 21, 1, 2, 514, "", 0 },

  { 258,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_c), 21, 1, 2, 516, "", 0 },

  { 259,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_LgV2, Saturation_UpperSat_bg), 21, 1, 2, 518, "", 0 },

  { 260,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_LgV2, Saturation_LowerSat_g), 21, 1, 2, 520, "", 0 },

  { 261,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_c0), 21, 1, 2, 522, "", 0 },

  { 262,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_l), 21, 1, 2, 524, "", 0 },

  { 263,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_d), 21, 1, 2, 526, "", 0 },

  { 264,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain",
    offsetof(Parameters_LgV2, u_Gain_e), 21, 1, 2, 528, "", 0 },

  { 265,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s eq/0_2x1/Value",
    offsetof(Parameters_LgV2, _2x1_Value), 35, 2, 2, 530, "", 0 },

  { 266, "lgv2/Guidance Systems/Path-following/Path/Straight path/0_2x1/Value",
    offsetof(Parameters_LgV2, _2x1_Value_n), 21, 1, 2, 532, "", 0 },

  { 267,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_a4), 21, 1, 2, 534, "", 0 },

  { 268,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_gg), 21, 1, 2, 536, "", 0 },

  { 269,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_d3), 21, 1, 2, 538, "", 0 },

  { 270, "lgv2/Guidance Systems/Path-following/my/Value", offsetof
    (Parameters_LgV2, my_Value), 21, 1, 2, 540, "", 0 },

  { 271,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_b), 21, 1, 2, 542, "", 0 },

  { 272, "lgv2/Control Systems/LgV design 2/Control law/D_L/X_u/Value", offsetof
    (Parameters_LgV2, X_u_Value), 21, 1, 2, 544, "", 0 },

  { 273, "lgv2/Control Systems/LgV design 2/Control law/D_L/-X_u/Gain", offsetof
    (Parameters_LgV2, X_u_Gain), 21, 1, 2, 546, "", 0 },

  { 274, "lgv2/Control Systems/LgV design 2/Control law/D_L/D_L_21/Value",
    offsetof(Parameters_LgV2, D_L_21_Value), 21, 1, 2, 548, "", 0 },

  { 275, "lgv2/Control Systems/LgV design 2/Control law/D_L/D_L_31/Value",
    offsetof(Parameters_LgV2, D_L_31_Value), 21, 1, 2, 550, "", 0 },

  { 276, "lgv2/Control Systems/LgV design 2/Control law/D_L/D_L_12/Value",
    offsetof(Parameters_LgV2, D_L_12_Value), 21, 1, 2, 552, "", 0 },

  { 277, "lgv2/Control Systems/LgV design 2/Control law/D_L/Y_v/Value", offsetof
    (Parameters_LgV2, Y_v_Value), 21, 1, 2, 554, "", 0 },

  { 278, "lgv2/Control Systems/LgV design 2/Control law/D_L/-Y_v/Gain", offsetof
    (Parameters_LgV2, Y_v_Gain), 21, 1, 2, 556, "", 0 },

  { 279, "lgv2/Control Systems/LgV design 2/Control law/D_L/N_v/Value", offsetof
    (Parameters_LgV2, N_v_Value), 21, 1, 2, 558, "", 0 },

  { 280, "lgv2/Control Systems/LgV design 2/Control law/D_L/-N_v/Gain", offsetof
    (Parameters_LgV2, N_v_Gain), 21, 1, 2, 560, "", 0 },

  { 281, "lgv2/Control Systems/LgV design 2/Control law/D_L/D_L_13/Value",
    offsetof(Parameters_LgV2, D_L_13_Value), 21, 1, 2, 562, "", 0 },

  { 282, "lgv2/Control Systems/LgV design 2/Control law/D_L/Y_r/Value", offsetof
    (Parameters_LgV2, Y_r_Value), 21, 1, 2, 564, "", 0 },

  { 283, "lgv2/Control Systems/LgV design 2/Control law/D_L/-Y_vr/Gain",
    offsetof(Parameters_LgV2, Y_vr_Gain), 21, 1, 2, 566, "", 0 },

  { 284, "lgv2/Control Systems/LgV design 2/Control law/D_L/N_r/Value", offsetof
    (Parameters_LgV2, N_r_Value), 21, 1, 2, 568, "", 0 },

  { 285, "lgv2/Control Systems/LgV design 2/Control law/D_L/-N_r/Gain", offsetof
    (Parameters_LgV2, N_r_Gain), 21, 1, 2, 570, "", 0 },

  { 286, "lgv2/Control Systems/LgV design 2/M/m/Value", offsetof(Parameters_LgV2,
    m_Value), 21, 1, 2, 572, "", 0 },

  { 287, "lgv2/Control Systems/LgV design 2/M/X_udot/Value", offsetof
    (Parameters_LgV2, X_udot_Value), 21, 1, 2, 574, "", 0 },

  { 288, "lgv2/Control Systems/LgV design 2/M/M_21/Value", offsetof
    (Parameters_LgV2, M_21_Value), 21, 1, 2, 576, "", 0 },

  { 289, "lgv2/Control Systems/LgV design 2/M/M_31/Value", offsetof
    (Parameters_LgV2, M_31_Value), 21, 1, 2, 578, "", 0 },

  { 290, "lgv2/Control Systems/LgV design 2/M/M_12/Value", offsetof
    (Parameters_LgV2, M_12_Value), 21, 1, 2, 580, "", 0 },

  { 291, "lgv2/Control Systems/LgV design 2/M/Y_vdot/Value", offsetof
    (Parameters_LgV2, Y_vdot_Value), 21, 1, 2, 582, "", 0 },

  { 292, "lgv2/Control Systems/LgV design 2/M/x_g/Value", offsetof
    (Parameters_LgV2, x_g_Value), 21, 1, 2, 584, "", 0 },

  { 293, "lgv2/Control Systems/LgV design 2/M/N_vdot/Value", offsetof
    (Parameters_LgV2, N_vdot_Value), 21, 1, 2, 586, "", 0 },

  { 294, "lgv2/Control Systems/LgV design 2/M/M_13/Value", offsetof
    (Parameters_LgV2, M_13_Value), 21, 1, 2, 588, "", 0 },

  { 295, "lgv2/Control Systems/LgV design 2/M/Y_rdot/Value", offsetof
    (Parameters_LgV2, Y_rdot_Value), 21, 1, 2, 590, "", 0 },

  { 296, "lgv2/Control Systems/LgV design 2/M/I_z/Value", offsetof
    (Parameters_LgV2, I_z_Value), 21, 1, 2, 592, "", 0 },

  { 297, "lgv2/Control Systems/LgV design 2/M/N_rdot/Value", offsetof
    (Parameters_LgV2, N_rdot_Value), 21, 1, 2, 594, "", 0 },

  { 298, "lgv2/Control Systems/LgV design 2/sigma eq/I/Constant/Value", offsetof
    (Parameters_LgV2, Constant_Value_dh), 36, 9, 2, 596, "", 0 },

  { 299, "lgv2/Control Systems/LgV design 2/S(r)/S11/Value", offsetof
    (Parameters_LgV2, S11_Value), 21, 1, 2, 598, "", 0 },

  { 300, "lgv2/Control Systems/LgV design 2/S(r)/R31/Value", offsetof
    (Parameters_LgV2, R31_Value_a), 21, 1, 2, 600, "", 0 },

  { 301, "lgv2/Control Systems/LgV design 2/S(r)/S12/Gain", offsetof
    (Parameters_LgV2, S12_Gain), 21, 1, 2, 602, "", 0 },

  { 302, "lgv2/Control Systems/LgV design 2/S(r)/S22/Value", offsetof
    (Parameters_LgV2, S22_Value), 21, 1, 2, 604, "", 0 },

  { 303, "lgv2/Control Systems/LgV design 2/S(r)/S32/Value", offsetof
    (Parameters_LgV2, S32_Value), 21, 1, 2, 606, "", 0 },

  { 304, "lgv2/Control Systems/LgV design 2/S(r)/S13/Value", offsetof
    (Parameters_LgV2, S13_Value), 21, 1, 2, 608, "", 0 },

  { 305, "lgv2/Control Systems/LgV design 2/S(r)/S23/Value", offsetof
    (Parameters_LgV2, S23_Value), 21, 1, 2, 610, "", 0 },

  { 306, "lgv2/Control Systems/LgV design 2/S(r)/S33/Value", offsetof
    (Parameters_LgV2, S33_Value), 21, 1, 2, 612, "", 0 },

  { 307,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^t eq/0_2x1/Value",
    offsetof(Parameters_LgV2, _2x1_Value_p), 35, 2, 2, 614, "", 0 },

  { 308, "lgv2/Control Systems/LgV design 2/alpha^q/I/Constant/Value", offsetof
    (Parameters_LgV2, Constant_Value_cf), 36, 9, 2, 616, "", 0 },

  { 309,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/I/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_k), 22, 4, 2, 618, "", 0 },

  { 310,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_e), 21, 1, 2, 620, "", 0 },

  { 311,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain",
    offsetof(Parameters_LgV2, _Gain_l), 21, 1, 2, 622, "", 0 },

  { 312,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/0_2x2/Value",
    offsetof(Parameters_LgV2, _2x2_Value), 22, 4, 2, 624, "", 0 },

  { 313,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/0_2x2/Value",
    offsetof(Parameters_LgV2, _2x2_Value_n), 22, 4, 2, 626, "", 0 },

  { 314,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain",
    offsetof(Parameters_LgV2, _Gain_b), 21, 1, 2, 628, "", 0 },

  { 315,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value",
    offsetof(Parameters_LgV2, u_Value_id), 21, 1, 2, 630, "", 0 },

  { 316,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_d), 21, 1, 2, 632, "", 0 },

  { 317,
    "lgv2/Control Systems/LgV design 2/Update laws/Integrator2/InitialCondition",
    offsetof(Parameters_LgV2, Integrator2_IC), 21, 1, 2, 634, "", 0 },

  { 318, "lgv2/Control Systems/LgV design 2/alpha^s/I/Constant/Value", offsetof
    (Parameters_LgV2, Constant_Value_bk), 36, 9, 2, 636, "", 0 },

  { 319,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/0_2x1/Value",
    offsetof(Parameters_LgV2, _2x1_Value_j), 35, 2, 2, 638, "", 0 },

  { 320,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_dz), 21, 1, 2, 640, "", 0 },

  { 321,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/0_2x1/Value",
    offsetof(Parameters_LgV2, _2x1_Value_jo), 35, 2, 2, 642, "", 0 },

  { 322,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_nx), 21, 1, 2, 644, "", 0 },

  { 323,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_p), 21, 1, 2, 646, "", 0 },

  { 324,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_pj), 21, 1, 2, 648, "", 0 },

  { 325, "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/+ 2/Gain",
    offsetof(Parameters_LgV2, u_Gain_m), 21, 1, 2, 650, "", 0 },

  { 326,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain",
    offsetof(Parameters_LgV2, _Gain_p), 21, 1, 2, 652, "", 0 },

  { 327,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain",
    offsetof(Parameters_LgV2, _Gain_a), 21, 1, 2, 654, "", 0 },

  { 328,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_eq), 21, 1, 2, 656, "", 0 },

  { 329,
    "lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_c5), 21, 1, 2, 658, "", 0 },

  { 330,
    "lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_af), 21, 1, 2, 660, "", 0 },

  { 331,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value",
    offsetof(Parameters_LgV2, u_Value_jc), 21, 1, 2, 662, "", 0 },

  { 332,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_dc), 21, 1, 2, 664, "", 0 },

  { 333,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start_b), 21, 1, 2, 666, "", 0 },

  { 334,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End_jo), 21, 1, 2, 668, "", 0 },

  { 335,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_jz), 21, 1, 2, 670, "", 0 },

  { 336,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_gp), 21, 1, 2, 672, "", 0 },

  { 337,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_LgV2, f_10_XData_n), 44, 9, 2, 674, "", 0 },

  { 338,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_LgV2, f_10_YData_b), 44, 9, 2, 676, "", 0 },

  { 339,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_LgV2, f_10_Value_i), 21, 1, 2, 678, "", 0 },

  { 340,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_LgV2, f_10_XData_k), 68, 10, 2, 680, "", 0 },

  { 341,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_LgV2, f_10_YData_d), 68, 10, 2, 682, "", 0 },

  { 342,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start_g), 21, 1, 2, 684, "", 0 },

  { 343,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End_p), 21, 1, 2, 686, "", 0 },

  { 344,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_cv), 21, 1, 2, 688, "", 0 },

  { 345,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_ow), 21, 1, 2, 690, "", 0 },

  { 346,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_oq), 21, 1, 2, 692, "", 0 },

  { 347,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_LgV2, f_20_XData_g), 69, 11, 2, 694, "", 0 },

  { 348,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_LgV2, f_20_YData_f), 69, 11, 2, 696, "", 0 },

  { 349,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_LgV2, f_20_Value_c), 21, 1, 2, 698, "", 0 },

  { 350,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_LgV2, f_20_XData_g0), 68, 10, 2, 700, "", 0 },

  { 351,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_LgV2, f_20_YData_b), 68, 10, 2, 702, "", 0 },

  { 352,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start_cu), 21, 1, 2, 704, "", 0 },

  { 353,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End_o), 21, 1, 2, 706, "", 0 },

  { 354,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_f), 21, 1, 2, 708, "", 0 },

  { 355,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_gc), 21, 1, 2, 710, "", 0 },

  { 356,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_LgV2, f_30_XData_p), 70, 8, 2, 712, "", 0 },

  { 357,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_LgV2, f_30_YData_e), 70, 8, 2, 714, "", 0 },

  { 358,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_LgV2, f_30_Value_m), 21, 1, 2, 716, "", 0 },

  { 359,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_LgV2, f_30_XData_g), 69, 11, 2, 718, "", 0 },

  { 360,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_LgV2, f_30_YData_p), 69, 11, 2, 720, "", 0 },

  { 361,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start_bq), 21, 1, 2, 722, "", 0 },

  { 362,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End_g), 21, 1, 2, 724, "", 0 },

  { 363,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_kh), 21, 1, 2, 726, "", 0 },

  { 364,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_n), 21, 1, 2, 728, "", 0 },

  { 365,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_LgV2, f_40_XData_h), 68, 10, 2, 730, "", 0 },

  { 366,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_LgV2, f_40_YData_m), 68, 10, 2, 732, "", 0 },

  { 367,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_LgV2, f_40_Value_j), 21, 1, 2, 734, "", 0 },

  { 368,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_LgV2, f_40_XData_j2), 71, 7, 2, 736, "", 0 },

  { 369,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_LgV2, f_40_YData_l), 71, 7, 2, 738, "", 0 },

  { 370,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue",
    offsetof(Parameters_LgV2, DeadZone_Start_f), 21, 1, 2, 740, "", 0 },

  { 371,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue",
    offsetof(Parameters_LgV2, DeadZone_End_k), 21, 1, 2, 742, "", 0 },

  { 372,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_a4x), 21, 1, 2, 744, "", 0 },

  { 373,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_LgV2, Constant_Value_hx), 21, 1, 2, 746, "", 0 },

  { 374,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_LgV2, f_50_XData_o), 26, 3, 2, 748, "", 0 },

  { 375,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_LgV2, f_50_YData_f), 26, 3, 2, 750, "", 0 },

  { 376,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_LgV2, f_50_Value_j), 21, 1, 2, 752, "", 0 },

  { 377,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_LgV2, f_50_XData_a), 26, 3, 2, 754, "", 0 },

  { 378,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_LgV2, f_50_YData_h), 26, 3, 2, 756, "", 0 },

  { 379, "lgv2/Control Systems/LgV design 2/BT_power_limit/Value", offsetof
    (Parameters_LgV2, BT_power_limit_Value_b), 21, 1, 2, 758, "", 0 },

  { 380, "lgv2/Control Systems/LgV design 2/VSP_speeds/Value", offsetof
    (Parameters_LgV2, VSP_speeds_Value_c), 21, 1, 2, 760, "", 0 },

  { 381, "lgv2/Control Systems/Saturation/UpperLimit", offsetof(Parameters_LgV2,
    Saturation_UpperSat_p), 21, 1, 2, 762, "", 0 },

  { 382, "lgv2/Control Systems/Saturation/LowerLimit", offsetof(Parameters_LgV2,
    Saturation_LowerSat_g5), 21, 1, 2, 764, "", 0 },

  { 383,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value",
    offsetof(Parameters_LgV2, T_e11_Value_j), 21, 1, 2, 766, "", 0 },

  { 384,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value",
    offsetof(Parameters_LgV2, T_e21_Value_p), 21, 1, 2, 768, "", 0 },

  { 385,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value",
    offsetof(Parameters_LgV2, l_y1_Value_p), 21, 1, 2, 770, "", 0 },

  { 386,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value",
    offsetof(Parameters_LgV2, T_e12_Value_b), 21, 1, 2, 772, "", 0 },

  { 387,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value",
    offsetof(Parameters_LgV2, T_e22_Value_p), 21, 1, 2, 774, "", 0 },

  { 388,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value",
    offsetof(Parameters_LgV2, l_x1_Value_ph), 21, 1, 2, 776, "", 0 },

  { 389,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain",
    offsetof(Parameters_LgV2, l_x1_Gain_i), 21, 1, 2, 778, "", 0 },

  { 390,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value",
    offsetof(Parameters_LgV2, T_e13_Value_d), 21, 1, 2, 780, "", 0 },

  { 391,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value",
    offsetof(Parameters_LgV2, T_e23_Value_g), 21, 1, 2, 782, "", 0 },

  { 392,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value",
    offsetof(Parameters_LgV2, l_y2_Value_a), 21, 1, 2, 784, "", 0 },

  { 393,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain",
    offsetof(Parameters_LgV2, l_y2_Gain_h), 21, 1, 2, 786, "", 0 },

  { 394,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value",
    offsetof(Parameters_LgV2, T_e14_Value_i), 21, 1, 2, 788, "", 0 },

  { 395,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value",
    offsetof(Parameters_LgV2, T_e24_Value_j), 21, 1, 2, 790, "", 0 },

  { 396,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value",
    offsetof(Parameters_LgV2, l_x2_Value_l), 21, 1, 2, 792, "", 0 },

  { 397,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain",
    offsetof(Parameters_LgV2, l_x2_Gain_i), 21, 1, 2, 794, "", 0 },

  { 398,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value",
    offsetof(Parameters_LgV2, T_e15_Value_f), 21, 1, 2, 796, "", 0 },

  { 399,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value",
    offsetof(Parameters_LgV2, T_e25_Value_l), 21, 1, 2, 798, "", 0 },

  { 400,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value",
    offsetof(Parameters_LgV2, l_x3_Value_o), 21, 1, 2, 800, "", 0 },

  { 401,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues",
    offsetof(Parameters_LgV2, u_1tof_1_XData), 72, 19, 2, 802, "", 0 },

  { 402,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table",
    offsetof(Parameters_LgV2, u_1tof_1_YData), 72, 19, 2, 804, "", 0 },

  { 403,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues",
    offsetof(Parameters_LgV2, u_2tof_2_XData), 73, 21, 2, 806, "", 0 },

  { 404,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table",
    offsetof(Parameters_LgV2, u_2tof_2_YData), 73, 21, 2, 808, "", 0 },

  { 405,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues",
    offsetof(Parameters_LgV2, u_3tof_3_XData), 72, 19, 2, 810, "", 0 },

  { 406,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table",
    offsetof(Parameters_LgV2, u_3tof_3_YData), 72, 19, 2, 812, "", 0 },

  { 407,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues",
    offsetof(Parameters_LgV2, u_4tof_4_XData), 74, 17, 2, 814, "", 0 },

  { 408,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table",
    offsetof(Parameters_LgV2, u_4tof_4_YData), 74, 17, 2, 816, "", 0 },

  { 409,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues",
    offsetof(Parameters_LgV2, u_5tof_5_XData), 75, 7, 2, 818, "", 0 },

  { 410,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table",
    offsetof(Parameters_LgV2, u_5tof_5_YData), 75, 7, 2, 820, "", 0 },

  { 411, "lgv2/Control Systems/LgV design 2/Gamma_q/12/Value", offsetof
    (Parameters_LgV2, u_Value_nw), 21, 1, 2, 822, "", 0 },

  { 412, "lgv2/Control Systems/LgV design 2/Gamma_q/21/Value", offsetof
    (Parameters_LgV2, u_Value_io), 21, 1, 2, 824, "", 0 },

  { 413, "lgv2/Control Systems/LgV design 2/Gamma_q_Surge/Value", offsetof
    (Parameters_LgV2, Gamma_q_Surge_Value), 21, 1, 2, 826, "", 0 },

  { 414, "lgv2/Control Systems/LgV design 2/Gamma_q_Sway/Value", offsetof
    (Parameters_LgV2, Gamma_q_Sway_Value), 21, 1, 2, 828, "", 0 },

  { 415, "lgv2/Control Systems/LgV design 2/V_1^q/Gain/Gain", offsetof
    (Parameters_LgV2, Gain_Gain_cq), 21, 1, 2, 830, "", 0 },

  { 416, "lgv2/Control Systems/LgV design 2/lambda/Value", offsetof
    (Parameters_LgV2, lambda_Value), 21, 1, 2, 832, "", 0 },

  { 417, "lgv2/Control Systems/LgV design 2/Update laws/Gain/Gain", offsetof
    (Parameters_LgV2, Gain_Gain_gw), 21, 1, 2, 834, "", 0 },

  { 418, "lgv2/HMI/Battery Bow Thruster/Gain", offsetof(Parameters_LgV2,
    BatteryBowThruster_Gain), 21, 1, 2, 836, "", 0 },

  { 419, "lgv2/HMI/Battery Servo/Gain", offsetof(Parameters_LgV2,
    BatteryServo_Gain), 21, 1, 2, 838, "", 0 },

  { 420, "lgv2/HMI/Battery Main/Gain", offsetof(Parameters_LgV2,
    BatteryMain_Gain), 21, 1, 2, 840, "", 0 },

  { 421, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain", offsetof
    (Parameters_LgV2, QTMIn1FPS_Gain), 21, 1, 2, 842, "", 0 },

  { 422, "lgv2/Plants/saturation/Saturation/UpperLimit", offsetof
    (Parameters_LgV2, Saturation_UpperSat_a), 21, 1, 2, 844, "", 0 },

  { 423, "lgv2/Plants/saturation/Saturation/LowerLimit", offsetof
    (Parameters_LgV2, Saturation_LowerSat_k), 21, 1, 2, 846, "", 0 },

  { 424, "lgv2/Plants/saturation/Saturation1/UpperLimit", offsetof
    (Parameters_LgV2, Saturation1_UpperSat), 21, 1, 2, 848, "", 0 },

  { 425, "lgv2/Plants/saturation/Saturation1/LowerLimit", offsetof
    (Parameters_LgV2, Saturation1_LowerSat), 21, 1, 2, 850, "", 0 },

  { 426, "lgv2/Plants/saturation/Saturation2/UpperLimit", offsetof
    (Parameters_LgV2, Saturation2_UpperSat), 21, 1, 2, 852, "", 0 },

  { 427, "lgv2/Plants/saturation/Saturation2/LowerLimit", offsetof
    (Parameters_LgV2, Saturation2_LowerSat), 21, 1, 2, 854, "", 0 },

  { 428, "lgv2/Plants/saturation/plant tau_surge/Gain", offsetof(Parameters_LgV2,
    planttau_surge_Gain), 21, 1, 2, 856, "", 0 },

  { 429, "lgv2/Plants/saturation/plant tau_sway/Gain", offsetof(Parameters_LgV2,
    planttau_sway_Gain), 21, 1, 2, 858, "", 0 },

  { 430, "lgv2/Plants/saturation/plant tau_yaw/Gain", offsetof(Parameters_LgV2,
    planttau_yaw_Gain), 21, 1, 2, 860, "", 0 },

  { 431, "lgv2/Plants/plant u_1/Gain", offsetof(Parameters_LgV2, plantu_1_Gain),
    21, 1, 2, 862, "", 0 },

  { 432, "lgv2/Plants/plant u_2/Gain", offsetof(Parameters_LgV2, plantu_2_Gain),
    21, 1, 2, 864, "", 0 },

  { 433, "lgv2/Plants/plant u_3/Gain", offsetof(Parameters_LgV2, plantu_3_Gain),
    21, 1, 2, 866, "", 0 },

  { 434, "lgv2/Plants/plant u_4/Gain", offsetof(Parameters_LgV2, plantu_4_Gain),
    21, 1, 2, 868, "", 0 },

  { 435, "lgv2/Plants/plant u_5/Gain", offsetof(Parameters_LgV2, plantu_5_Gain),
    21, 1, 2, 870, "", 0 },

  { 436, "lgv2/Plants/plant BT power/Gain", offsetof(Parameters_LgV2,
    plantBTpower_Gain), 21, 1, 2, 872, "", 0 },

  { 437, "lgv2/Plants/plant VSP speed/Gain", offsetof(Parameters_LgV2,
    plantVSPspeed_Gain), 21, 1, 2, 874, "", 0 },

  { 438, "lgv2/Plants/Enable CSE1/Value", offsetof(Parameters_LgV2,
    EnableCSE1_Value), 21, 1, 2, 876, "", 0 },

  { 439, "lgv2/eta_psi/Gain", offsetof(Parameters_LgV2, eta_psi_Gain), 21, 1, 2,
    878, "", 0 },

  { 440, "lgv2/eta_psid/Gain", offsetof(Parameters_LgV2, eta_psid_Gain), 21, 1,
    2, 880, "", 0 },

  { 441, "lgv2/eta_x/Gain", offsetof(Parameters_LgV2, eta_x_Gain), 21, 1, 2, 882,
    "", 0 },

  { 442, "lgv2/eta_xd/Gain", offsetof(Parameters_LgV2, eta_xd_Gain), 21, 1, 2,
    884, "", 0 },

  { 443, "lgv2/eta_y/Gain", offsetof(Parameters_LgV2, eta_y_Gain), 21, 1, 2, 886,
    "", 0 },

  { 444, "lgv2/eta_yd/Gain", offsetof(Parameters_LgV2, eta_yd_Gain), 21, 1, 2,
    888, "", 0 },

  { 445, "lgv2/psi_los/Gain", offsetof(Parameters_LgV2, psi_los_Gain_o), 21, 1,
    2, 890, "", 0 },

  { 446, "lgv2/psi_plot/Gain", offsetof(Parameters_LgV2, psi_plot_Gain), 21, 1,
    2, 892, "", 0 },

  { 447, "lgv2/q_x/Gain", offsetof(Parameters_LgV2, q_x_Gain_o), 21, 1, 2, 894,
    "", 0 },

  { 448, "lgv2/q_y/Gain", offsetof(Parameters_LgV2, q_y_Gain_p), 21, 1, 2, 896,
    "", 0 },

  { 449, "lgv2/x_plot/Gain", offsetof(Parameters_LgV2, x_plot_Gain), 21, 1, 2,
    898, "", 0 },

  { 450, "lgv2/y_plot/Gain", offsetof(Parameters_LgV2, y_plot_Gain), 21, 1, 2,
    900, "", 0 },

  { 451,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R12/Gain",
    offsetof(Parameters_LgV2, R12_Gain), 21, 1, 2, 902, "", 0 },

  { 452,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R22/Gain",
    offsetof(Parameters_LgV2, R22_Gain), 21, 1, 2, 904, "", 0 },

  { 453,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/0/Value",
    offsetof(Parameters_LgV2, _Value_i), 21, 1, 2, 906, "", 0 },

  { 454,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S12/Gain",
    offsetof(Parameters_LgV2, S12_Gain_o), 21, 1, 2, 908, "", 0 },

  { 455,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value",
    offsetof(Parameters_LgV2, _Value_h), 21, 1, 2, 910, "", 0 },

  { 456,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain",
    offsetof(Parameters_LgV2, S12_Gain_f), 21, 1, 2, 912, "", 0 },

  { 457, "lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain", offsetof
    (Parameters_LgV2, BT_D_Gain1_Gain), 21, 1, 2, 914, "", 0 },

  { 458, "lgv2/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value", offsetof
    (Parameters_LgV2, BT_Power_Offset1_Value), 21, 1, 2, 916, "", 0 },

  { 459, "lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain", offsetof
    (Parameters_LgV2, BT_D_Gain2_Gain), 21, 1, 2, 918, "", 0 },

  { 460, "lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain", offsetof
    (Parameters_LgV2, BT_L_Gain1_Gain), 21, 1, 2, 920, "", 0 },

  { 461, "lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain", offsetof
    (Parameters_LgV2, BT_L_Gain2_Gain), 21, 1, 2, 922, "", 0 },

  { 462, "lgv2/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value", offsetof
    (Parameters_LgV2, BT_Power_Offset2_Value), 21, 1, 2, 924, "", 0 },

  { 463, "lgv2/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value", offsetof
    (Parameters_LgV2, BT_Power_Offset3_Value), 21, 1, 2, 926, "", 0 },

  { 464, "lgv2/Plants/CSE1/Bow Thruster/Constant/Value", offsetof
    (Parameters_LgV2, Constant_Value_i), 21, 1, 2, 928, "", 0 },

  { 465, "lgv2/Plants/CSE1/Bow Thruster/Constant1/Value", offsetof
    (Parameters_LgV2, Constant1_Value_j), 21, 1, 2, 930, "", 0 },

  { 466, "lgv2/Plants/CSE1/Bow Thruster/Neg/Gain", offsetof(Parameters_LgV2,
    Neg_Gain), 21, 1, 2, 932, "", 0 },

  { 467, "lgv2/Plants/CSE1/Voith Schneider Propeller /-x/Gain", offsetof
    (Parameters_LgV2, x_Gain), 21, 1, 2, 934, "", 0 },

  { 468, "lgv2/Plants/CSE1/Voith Schneider Propeller /-y/Gain", offsetof
    (Parameters_LgV2, y_Gain), 21, 1, 2, 936, "", 0 },

  { 469, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex", offsetof
    (Parameters_LgV2, Servo1_RowIdx), 40, 3, 2, 938, "", 0 },

  { 470, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_LgV2, Servo1_ColIdx), 40, 3, 2, 940, "", 0 },

  { 471, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1/Table", offsetof
    (Parameters_LgV2, Servo1_Table), 36, 9, 2, 942, "", 0 },

  { 472, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex", offsetof
    (Parameters_LgV2, Servo2_RowIdx), 40, 3, 2, 944, "", 0 },

  { 473, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_LgV2, Servo2_ColIdx), 40, 3, 2, 946, "", 0 },

  { 474, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2/Table", offsetof
    (Parameters_LgV2, Servo2_Table), 36, 9, 2, 948, "", 0 },

  { 475, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex", offsetof
    (Parameters_LgV2, Servo3_RowIdx), 40, 3, 2, 950, "", 0 },

  { 476, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_LgV2, Servo3_ColIdx), 40, 3, 2, 952, "", 0 },

  { 477, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3/Table", offsetof
    (Parameters_LgV2, Servo3_Table), 36, 9, 2, 954, "", 0 },

  { 478, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex", offsetof
    (Parameters_LgV2, Servo4_RowIdx), 40, 3, 2, 956, "", 0 },

  { 479, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_LgV2, Servo4_ColIdx), 40, 3, 2, 958, "", 0 },

  { 480, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4/Table", offsetof
    (Parameters_LgV2, Servo4_Table), 36, 9, 2, 960, "", 0 },

  { 481, "lgv2/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_LgV2, VPS_Speed_Gain_Gain), 21, 1, 2, 962, "", 0 },

  { 482, "lgv2/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_LgV2, VPS_Power_Offset_Value), 21, 1, 2, 964, "", 0 },

  { 483, "lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain", offsetof
    (Parameters_LgV2, VSPSPort_Gain), 21, 1, 2, 966, "", 0 },

  { 484, "lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_LgV2, VSPSStarboard_Gain), 21, 1, 2, 968, "", 0 },

  { 485, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_r/Value",
    offsetof(Parameters_LgV2, N_r_Value_e), 21, 1, 2, 970, "", 0 },

  { 486, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r/Gain",
    offsetof(Parameters_LgV2, N_r_Gain_f), 21, 1, 2, 972, "", 0 },

  { 487, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_v/Value",
    offsetof(Parameters_LgV2, N_v_Value_k), 21, 1, 2, 974, "", 0 },

  { 488, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v/Gain",
    offsetof(Parameters_LgV2, N_v_Gain_k), 21, 1, 2, 976, "", 0 },

  { 489, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/X_u/Value",
    offsetof(Parameters_LgV2, X_u_Value_l), 21, 1, 2, 978, "", 0 },

  { 490, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u/Gain",
    offsetof(Parameters_LgV2, X_u_Gain_k), 21, 1, 2, 980, "", 0 },

  { 491, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_v/Value",
    offsetof(Parameters_LgV2, Y_v_Value_n), 21, 1, 2, 982, "", 0 },

  { 492, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v/Gain",
    offsetof(Parameters_LgV2, Y_v_Gain_p), 21, 1, 2, 984, "", 0 },

  { 493, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_r/Value",
    offsetof(Parameters_LgV2, Y_r_Value_o), 21, 1, 2, 986, "", 0 },

  { 494, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr/Gain",
    offsetof(Parameters_LgV2, Y_vr_Gain_c), 21, 1, 2, 988, "", 0 },

  { 495, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_12/Value",
    offsetof(Parameters_LgV2, D_L_12_Value_k), 21, 1, 2, 990, "", 0 },

  { 496, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_13/Value",
    offsetof(Parameters_LgV2, D_L_13_Value_c), 21, 1, 2, 992, "", 0 },

  { 497, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_21/Value",
    offsetof(Parameters_LgV2, D_L_21_Value_i), 21, 1, 2, 994, "", 0 },

  { 498, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_31/Value",
    offsetof(Parameters_LgV2, D_L_31_Value_h), 21, 1, 2, 996, "", 0 },

  { 499,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0/Value",
    offsetof(Parameters_LgV2, psi_0_Value), 21, 1, 2, 998, "", 0 },

  { 500,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0/Value",
    offsetof(Parameters_LgV2, x_0_Value), 21, 1, 2, 1000, "", 0 },

  { 501,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0/Value",
    offsetof(Parameters_LgV2, y_0_Value), 21, 1, 2, 1002, "", 0 },

  { 502,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0/Value",
    offsetof(Parameters_LgV2, r_0_Value), 21, 1, 2, 1004, "", 0 },

  { 503,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0/Value",
    offsetof(Parameters_LgV2, u_0_Value), 21, 1, 2, 1006, "", 0 },

  { 504,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0/Value",
    offsetof(Parameters_LgV2, v_0_Value), 21, 1, 2, 1008, "", 0 },

  { 505,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_LgV2, ResetLinearSimulatorintegrator_), 21, 1, 2, 1010,
    "", 0 },

  { 506, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/I_z/Value",
    offsetof(Parameters_LgV2, I_z_Value_e), 21, 1, 2, 1012, "", 0 },

  { 507, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m/Value",
    offsetof(Parameters_LgV2, m_Value_f), 21, 1, 2, 1014, "", 0 },

  { 508,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/X_udot/Value",
    offsetof(Parameters_LgV2, X_udot_Value_l), 21, 1, 2, 1016, "", 0 },

  { 509, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_21/Value",
    offsetof(Parameters_LgV2, M_21_Value_h), 21, 1, 2, 1018, "", 0 },

  { 510, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_31/Value",
    offsetof(Parameters_LgV2, M_31_Value_o), 21, 1, 2, 1020, "", 0 },

  { 511, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_12/Value",
    offsetof(Parameters_LgV2, M_12_Value_n), 21, 1, 2, 1022, "", 0 },

  { 512,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_vdot/Value",
    offsetof(Parameters_LgV2, Y_vdot_Value_n), 21, 1, 2, 1024, "", 0 },

  { 513, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/x_g/Value",
    offsetof(Parameters_LgV2, x_g_Value_g), 21, 1, 2, 1026, "", 0 },

  { 514,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_vdot/Value",
    offsetof(Parameters_LgV2, N_vdot_Value_d), 21, 1, 2, 1028, "", 0 },

  { 515, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_13/Value",
    offsetof(Parameters_LgV2, M_13_Value_f), 21, 1, 2, 1030, "", 0 },

  { 516,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_rdot/Value",
    offsetof(Parameters_LgV2, Y_rdot_Value_e), 21, 1, 2, 1032, "", 0 },

  { 517,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_rdot/Value",
    offsetof(Parameters_LgV2, N_rdot_Value_p), 21, 1, 2, 1034, "", 0 },

  { 518, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_LgV2, R31_Value_m), 21, 1, 2, 1036, "", 0 },

  { 519, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_LgV2, R32_Value_h), 21, 1, 2, 1038, "", 0 },

  { 520, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_LgV2, R13_Value_b), 21, 1, 2, 1040, "", 0 },

  { 521, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_LgV2, R23_Value_e), 21, 1, 2, 1042, "", 0 },

  { 522, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_LgV2, R33_Value_c), 21, 1, 2, 1044, "", 0 },

  { 523, "lgv2/Plants/Linear Simulator/eta_surge_hil/Gain", offsetof
    (Parameters_LgV2, eta_surge_hil_Gain), 21, 1, 2, 1046, "", 0 },

  { 524, "lgv2/Plants/Linear Simulator/eta_sway_hil/Gain", offsetof
    (Parameters_LgV2, eta_sway_hil_Gain), 21, 1, 2, 1048, "", 0 },

  { 525, "lgv2/Plants/Linear Simulator/eta_yaw_hil/Gain", offsetof
    (Parameters_LgV2, eta_yaw_hil_Gain), 21, 1, 2, 1050, "", 0 },

  { 526, "lgv2/Plants/Linear Simulator/etadot_surge_hil/Gain", offsetof
    (Parameters_LgV2, etadot_surge_hil_Gain), 21, 1, 2, 1052, "", 0 },

  { 527, "lgv2/Plants/Linear Simulator/etadot_sway_hil/Gain", offsetof
    (Parameters_LgV2, etadot_sway_hil_Gain), 21, 1, 2, 1054, "", 0 },

  { 528, "lgv2/Plants/Linear Simulator/etadot_yaw_hil/Gain", offsetof
    (Parameters_LgV2, etadot_yaw_hil_Gain), 21, 1, 2, 1056, "", 0 },

  { 529, "lgv2/Plants/Linear Simulator/nu_surge_hil/Gain", offsetof
    (Parameters_LgV2, nu_surge_hil_Gain), 21, 1, 2, 1058, "", 0 },

  { 530, "lgv2/Plants/Linear Simulator/nu_sway_hil/Gain", offsetof
    (Parameters_LgV2, nu_sway_hil_Gain), 21, 1, 2, 1060, "", 0 },

  { 531, "lgv2/Plants/Linear Simulator/nu_yaw_hil/Gain", offsetof
    (Parameters_LgV2, nu_yaw_hil_Gain), 21, 1, 2, 1062, "", 0 },

  { 532,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_gz), 38, 1, 2, 1064, "", 0 },

  { 533,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_a), 38, 1, 2, 1066, "", 0 },

  { 534,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_o), 38, 1, 2, 1068, "", 0 },

  { 535,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_b), 38, 1, 2, 1070, "", 0 },

  { 536,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_o1), 38, 1, 2, 1072, "", 0 },

  { 537,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_h), 38, 1, 2, 1074, "", 0 },

  { 538,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_fc), 38, 1, 2, 1076, "", 0 },

  { 539,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_bf), 38, 1, 2, 1078, "", 0 },

  { 540,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_k), 38, 1, 2, 1080, "", 0 },

  { 541,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_n), 38, 1, 2, 1082, "", 0 },

  { 542,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_i), 38, 1, 2, 1084, "", 0 },

  { 543,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_j), 38, 1, 2, 1086, "", 0 },

  { 544,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_l1), 38, 1, 2, 1088, "", 0 },

  { 545,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_l), 38, 1, 2, 1090, "", 0 },

  { 546,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_bo), 38, 1, 2, 1092, "", 0 },

  { 547,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_mu), 38, 1, 2, 1094, "", 0 },

  { 548,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_mw), 38, 1, 2, 1096, "", 0 },

  { 549,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_bp), 38, 1, 2, 1098, "", 0 },

  { 550,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_LgV2, Gain_Gain_op), 38, 1, 2, 1100, "", 0 },

  { 551,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_LgV2, Gain1_Gain_ma), 38, 1, 2, 1102, "", 0 },
};

static int NI_ParamListSize = 552;
static int NI_ParamDimList[] = {
  1, 1,                                /* lgv2/Naviagation Systems/Controller Input Selector/Value */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain */
  1, 1,                                /* lgv2/Plants/Enable Linear Simulator/Value */
  1, 1,                                /* lgv2/Naviagation Systems/etadot_surge/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/etadot_sway/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/etadot_yaw/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/eta_surge/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/eta_sway/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/eta_yaw/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain */
  3, 3,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/Constant1/Value */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/nu_surge/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/nu_sway/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/nu_yaw/Gain */
  1, 1,                                /* lgv2/HMI/DP Input/x_d/Value */
  1, 1,                                /* lgv2/Guidance Systems/DP/eta_d DP N/Gain */
  1, 1,                                /* lgv2/HMI/DP Input/y_d/Value */
  1, 1,                                /* lgv2/Guidance Systems/DP/eta_d DP E/Gain */
  1, 1,                                /* lgv2/HMI/DP Input/psi_d/Value */
  1, 1,                                /* lgv2/HMI/DP Input/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* lgv2/Guidance Systems/DP/eta_d DP Psi/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Update laws/Reset q/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Update laws/q_0/q_x_0/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Update laws/q_0/q_y_0/Value */
  1, 1,                                /* lgv2/HMI/Path-following input/x_2/Value */
  1, 1,                                /* lgv2/HMI/Path-following input/x_1/Value */
  1, 1,                                /* lgv2/HMI/Path-following input/y_2/Value */
  1, 1,                                /* lgv2/HMI/Path-following input/y_1/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Path Selector/Value */
  1, 1,                                /* lgv2/HMI/Path-following input/r_x/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Update laws/Reset s/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Update laws/s_0/Value */
  1, 1,                                /* lgv2/HMI/Path-following input/k/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Gain/Gain */
  1, 1,                                /* lgv2/HMI/Path-following input/r_y/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/saturation/x_dmax/Value */
  1, 1,                                /* lgv2/HMI/Path-following input/origin_x/Value */
  1, 1,                                /* lgv2/HMI/Path-following input/origo_y/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/saturation/x_dmin/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/saturation/y_dmax/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/saturation/y_dmin/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Delta/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* lgv2/Guidance Systems/q_x/Gain */
  1, 1,                                /* lgv2/Guidance Systems/q_y/Gain */
  1, 1,                                /* lgv2/Guidance Systems/psi_los/Gain */
  1, 1,                                /* lgv2/Guidance Systems/path x_d/Gain */
  1, 1,                                /* lgv2/Guidance Systems/path y_d/Gain */
  1, 1,                                /* lgv2/Guidance Systems/path psi_d/Gain */
  1, 1,                                /* lgv2/HMI/Path-following input/u_d/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/Control Mode/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 input/AS_LY/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 input/ScalingLY/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/PS3 u_1/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 input/AS_LX/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 input/ScalingLX/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/PS3 u_2/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 input/AS_RY/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 input/ScalingRY/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/PS3 u_3/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 input/AS_RX/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 input/Scaling_RX/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/PS3 u_4/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 input/L2/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 input/R2/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/PS3 u_5/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 input/PS3_BT_Power/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 input/PS3_VSP_Speed/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value */
  3, 3,                                /* lgv2/Control Systems/DP control/DP controller/Kp/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_p_surge_scale/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_p_sway_scale/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_p_yaw_scale/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Reset_DP_integrator/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/Integrator/InitialCondition */
  3, 3,                                /* lgv2/Control Systems/DP control/DP controller/Ki/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_i_surge_scale/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_i_sway_scale/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_i_yaw_scale/Gain */
  3, 3,                                /* lgv2/Control Systems/DP control/DP controller/Kd/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_d_surge_scale/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_d_sway_scale/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/DP controller/K_d_yaw_scale/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/DP control/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/DP control/BT_power_limit/Value */
  1, 1,                                /* lgv2/Control Systems/DP control/VSP_speeds/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/R(psi)/R31/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/R(psi)/-1/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/R(psi)/R32/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/R(psi)/R13/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/R(psi)/R23/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/R(psi)/R33/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_i_Surge/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_i/21/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_i/31/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_i/12/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_i_Sway/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_i/32/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_i/13/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_i/23/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_i_Yaw/Value */
  3, 1,                                /* lgv2/Control Systems/LgV design 2/Integral action state/Integrator/InitialCondition */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_d_Surge/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_d/21/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_d/31/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_d/12/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_d_Sway/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_d/32/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_d/13/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_d/23/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_d_Yaw/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/1/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/kappa_1/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/4/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_p_Surge/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_p/21/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_p/31/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_p/12/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_p_Sway/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_p/32/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_p/13/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_p/23/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/K_p_Yaw/Value */
  3, 3,                                /* lgv2/Control Systems/LgV design 2/Virtual control/I/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain */
  2, 1,                                /* lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s eq/0_2x1/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Straight path/0_2x1/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/my/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/X_u/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/-X_u/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/D_L_21/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/D_L_31/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/D_L_12/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/Y_v/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/-Y_v/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/N_v/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/-N_v/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/D_L_13/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/Y_r/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/-Y_vr/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/N_r/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Control law/D_L/-N_r/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/m/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/X_udot/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/M_21/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/M_31/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/M_12/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/Y_vdot/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/x_g/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/N_vdot/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/M_13/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/Y_rdot/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/I_z/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/M/N_rdot/Value */
  3, 3,                                /* lgv2/Control Systems/LgV design 2/sigma eq/I/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/S(r)/S11/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/S(r)/R31/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/S(r)/S12/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/S(r)/S22/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/S(r)/S32/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/S(r)/S13/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/S(r)/S23/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/S(r)/S33/Value */
  2, 1,                                /* lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^t eq/0_2x1/Value */
  3, 3,                                /* lgv2/Control Systems/LgV design 2/alpha^q/I/Constant/Value */
  2, 2,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/I/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain */
  2, 2,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/0_2x2/Value */
  2, 2,                                /* lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/0_2x2/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Update laws/Integrator2/InitialCondition */
  3, 3,                                /* lgv2/Control Systems/LgV design 2/alpha^s/I/Constant/Value */
  2, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/0_2x1/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain */
  2, 1,                                /* lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/0_2x1/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/+ 2/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Constant/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Gain/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/BT_power_limit/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/VSP_speeds/Value */
  1, 1,                                /* lgv2/Control Systems/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Control Systems/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value */
  1, 1,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value */
  19, 1,                               /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues */
  19, 1,                               /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table */
  21, 1,                               /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues */
  21, 1,                               /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table */
  19, 1,                               /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues */
  19, 1,                               /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table */
  17, 1,                               /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues */
  17, 1,                               /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table */
  1, 7,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues */
  1, 7,                                /* lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Gamma_q/12/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Gamma_q/21/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Gamma_q_Surge/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Gamma_q_Sway/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/V_1^q/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/lambda/Value */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Update laws/Gain/Gain */
  1, 1,                                /* lgv2/HMI/Battery Bow Thruster/Gain */
  1, 1,                                /* lgv2/HMI/Battery Servo/Gain */
  1, 1,                                /* lgv2/HMI/Battery Main/Gain */
  1, 1,                                /* lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain */
  1, 1,                                /* lgv2/Plants/saturation/Saturation/UpperLimit */
  1, 1,                                /* lgv2/Plants/saturation/Saturation/LowerLimit */
  1, 1,                                /* lgv2/Plants/saturation/Saturation1/UpperLimit */
  1, 1,                                /* lgv2/Plants/saturation/Saturation1/LowerLimit */
  1, 1,                                /* lgv2/Plants/saturation/Saturation2/UpperLimit */
  1, 1,                                /* lgv2/Plants/saturation/Saturation2/LowerLimit */
  1, 1,                                /* lgv2/Plants/saturation/plant tau_surge/Gain */
  1, 1,                                /* lgv2/Plants/saturation/plant tau_sway/Gain */
  1, 1,                                /* lgv2/Plants/saturation/plant tau_yaw/Gain */
  1, 1,                                /* lgv2/Plants/plant u_1/Gain */
  1, 1,                                /* lgv2/Plants/plant u_2/Gain */
  1, 1,                                /* lgv2/Plants/plant u_3/Gain */
  1, 1,                                /* lgv2/Plants/plant u_4/Gain */
  1, 1,                                /* lgv2/Plants/plant u_5/Gain */
  1, 1,                                /* lgv2/Plants/plant BT power/Gain */
  1, 1,                                /* lgv2/Plants/plant VSP speed/Gain */
  1, 1,                                /* lgv2/Plants/Enable CSE1/Value */
  1, 1,                                /* lgv2/eta_psi/Gain */
  1, 1,                                /* lgv2/eta_psid/Gain */
  1, 1,                                /* lgv2/eta_x/Gain */
  1, 1,                                /* lgv2/eta_xd/Gain */
  1, 1,                                /* lgv2/eta_y/Gain */
  1, 1,                                /* lgv2/eta_yd/Gain */
  1, 1,                                /* lgv2/psi_los/Gain */
  1, 1,                                /* lgv2/psi_plot/Gain */
  1, 1,                                /* lgv2/q_x/Gain */
  1, 1,                                /* lgv2/q_y/Gain */
  1, 1,                                /* lgv2/x_plot/Gain */
  1, 1,                                /* lgv2/y_plot/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R12/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R22/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/0/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S12/Gain */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value */
  1, 1,                                /* lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/Constant/Value */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/Constant1/Value */
  1, 1,                                /* lgv2/Plants/CSE1/Bow Thruster/Neg/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_r/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_v/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/X_u/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_v/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_r/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_12/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_13/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_21/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_31/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Reset Linear Simulator integrator/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/I_z/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/X_udot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_21/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_31/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_12/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_vdot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/x_g/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_vdot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_13/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_rdot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_rdot/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* lgv2/Plants/Linear Simulator/eta_surge_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/eta_sway_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/eta_yaw_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/etadot_surge_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/etadot_sway_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/etadot_yaw_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/nu_surge_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/nu_sway_hil/Gain */
  1, 1,                                /* lgv2/Plants/Linear Simulator/nu_yaw_hil/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 733;
static NI_Signal NI_SigList[] = {
  { 0, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In", 0, "", offsetof
    (BlockIO_LgV2, QTMIn), BLOCKIO_SIG, 44, 9, 2, 0, 0 },

  { 1, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error", 0, "", offsetof
    (BlockIO_LgV2, QTMIn2Error), BLOCKIO_SIG, 21, 1, 2, 2, 0 },

  { 2, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual", 0, "",
    offsetof(BlockIO_LgV2, QTMIn9Residual), BLOCKIO_SIG, 21, 1, 2, 4, 0 },

  { 3, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In3", 0, "", offsetof
    (BlockIO_LgV2, QTMIn3), BLOCKIO_SIG, 21, 1, 2, 6, 0 },

  { 4, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m x", 0, "", offsetof
    (BlockIO_LgV2, mm2mx), BLOCKIO_SIG, 21, 1, 2, 8, 0 },

  { 5, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In4", 0, "", offsetof
    (BlockIO_LgV2, QTMIn4), BLOCKIO_SIG, 21, 1, 2, 10, 0 },

  { 6, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m y", 0, "", offsetof
    (BlockIO_LgV2, mm2my), BLOCKIO_SIG, 21, 1, 2, 12, 0 },

  { 7, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In6", 0, "", offsetof
    (BlockIO_LgV2, QTMIn6), BLOCKIO_SIG, 21, 1, 2, 14, 0 },

  { 8, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r yaw", 0, "", offsetof
    (BlockIO_LgV2, d2ryaw), BLOCKIO_SIG, 21, 1, 2, 16, 0 },

  { 9, "lgv2/Naviagation Systems/Qualisys 6 DOF/Derivative1", 0, "", offsetof
    (BlockIO_LgV2, Derivative1), BLOCKIO_SIG, 24, 3, 2, 18, 0 },

  { 10, "lgv2/Naviagation Systems/Etadot Switch", 0, "", offsetof(BlockIO_LgV2,
    EtadotSwitch), BLOCKIO_SIG, 24, 3, 2, 20, 0 },

  { 11, "lgv2/Naviagation Systems/etadot_surge", 0, "", offsetof(BlockIO_LgV2,
    etadot_surge), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "lgv2/Naviagation Systems/etadot_sway", 0, "", offsetof(BlockIO_LgV2,
    etadot_sway), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "lgv2/Naviagation Systems/etadot_yaw", 0, "", offsetof(BlockIO_LgV2,
    etadot_yaw), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "lgv2/Naviagation Systems/Eta Switch", 0, "", offsetof(BlockIO_LgV2,
    EtaSwitch), BLOCKIO_SIG, 24, 3, 2, 28, 0 },

  { 15, "lgv2/Naviagation Systems/eta_surge", 0, "", offsetof(BlockIO_LgV2,
    eta_surge), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "lgv2/Naviagation Systems/eta_sway", 0, "", offsetof(BlockIO_LgV2,
    eta_sway), BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17, "lgv2/Naviagation Systems/eta_yaw", 0, "", offsetof(BlockIO_LgV2,
    eta_yaw), BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In8", 0, "", offsetof
    (BlockIO_LgV2, QTMIn8), BLOCKIO_SIG, 21, 1, 2, 36, 0 },

  { 19, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r roll", 0, "", offsetof
    (BlockIO_LgV2, d2rroll), BLOCKIO_SIG, 21, 1, 2, 38, 0 },

  { 20, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In7", 0, "", offsetof
    (BlockIO_LgV2, QTMIn7), BLOCKIO_SIG, 21, 1, 2, 40, 0 },

  { 21, "lgv2/Naviagation Systems/Qualisys 6 DOF/d2r pitch", 0, "", offsetof
    (BlockIO_LgV2, d2rpitch), BLOCKIO_SIG, 21, 1, 2, 42, 0 },

  { 22,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_LgV2, sintheta), BLOCKIO_SIG, 24, 3, 2, 44, 0 },

  { 23,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_LgV2, costheta), BLOCKIO_SIG, 24, 3, 2, 46, 0 },

  { 24,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_LgV2, R11), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_LgV2, R21), BLOCKIO_SIG, 0, 1, 2, 50, 0 },

  { 26,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_LgV2, R31), BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_LgV2, R12), BLOCKIO_SIG, 0, 1, 2, 54, 0 },

  { 28,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_LgV2, R22), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_LgV2, R32), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_LgV2, R13), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_LgV2, R23), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_LgV2, R33), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33,
    "lgv2/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_LgV2, Reshape9x13x3), BLOCKIO_SIG, 36, 9, 2, 66, 0 },

  { 34, "lgv2/Naviagation Systems/Qualisys 6 DOF/Matrix Concatenate2", 0, "",
    offsetof(BlockIO_LgV2, MatrixConcatenate2), BLOCKIO_SIG, 48, 36, 2, 68, 0 },

  { 35, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In5", 0, "", offsetof
    (BlockIO_LgV2, QTMIn5), BLOCKIO_SIG, 21, 1, 2, 70, 0 },

  { 36, "lgv2/Naviagation Systems/Qualisys 6 DOF/mm2m z", 0, "", offsetof
    (BlockIO_LgV2, mm2mz), BLOCKIO_SIG, 21, 1, 2, 72, 0 },

  { 37, "lgv2/Naviagation Systems/Qualisys 6 DOF/Derivative", 0, "", offsetof
    (BlockIO_LgV2, Derivative), BLOCKIO_SIG, 41, 6, 2, 74, 0 },

  { 38, "lgv2/Naviagation Systems/Qualisys 6 DOF/Product", 0, "", offsetof
    (BlockIO_LgV2, Product), BLOCKIO_SIG, 41, 6, 2, 76, 0 },

  { 39, "lgv2/Naviagation Systems/Nu Switch", 0, "", offsetof(BlockIO_LgV2,
    NuSwitch), BLOCKIO_SIG, 24, 3, 2, 78, 0 },

  { 40, "lgv2/Naviagation Systems/nu_surge", 0, "", offsetof(BlockIO_LgV2,
    nu_surge), BLOCKIO_SIG, 0, 1, 2, 80, 0 },

  { 41, "lgv2/Naviagation Systems/nu_sway", 0, "", offsetof(BlockIO_LgV2,
    nu_sway), BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42, "lgv2/Naviagation Systems/nu_yaw", 0, "", offsetof(BlockIO_LgV2, nu_yaw),
    BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43, "lgv2/Guidance Systems/DP/eta_d DP N", 0, "", offsetof(BlockIO_LgV2,
    eta_dDPN), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44, "lgv2/Guidance Systems/DP/eta_d DP E", 0, "", offsetof(BlockIO_LgV2,
    eta_dDPE), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "lgv2/HMI/DP Input/Degrees to Radians/Gain1", 0, "", offsetof
    (BlockIO_LgV2, Gain1), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46, "lgv2/Guidance Systems/DP/eta_d DP Psi", 0, "", offsetof(BlockIO_LgV2,
    eta_dDPPsi), BLOCKIO_SIG, 0, 1, 2, 92, 0 },

  { 47, "lgv2/Control Systems/LgV design 2/Update laws/q_0/q_x_0", 0, "",
    offsetof(BlockIO_LgV2, q_x_0), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48, "lgv2/Control Systems/LgV design 2/Update laws/q_0/q_y_0", 0, "",
    offsetof(BlockIO_LgV2, q_y_0), BLOCKIO_SIG, 0, 1, 2, 96, 0 },

  { 49, "lgv2/Control Systems/LgV design 2/Update laws/Integrator", 0, "",
    offsetof(BlockIO_LgV2, Integrator), BLOCKIO_SIG, 23, 2, 2, 98, 0 },

  { 50,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/p_d^s eq/x_2 - x_1",
    0, "", offsetof(BlockIO_LgV2, x_2x_1), BLOCKIO_SIG, 0, 1, 2, 100, 0 },

  { 51,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/p_d^s eq/y_2 - y_1",
    0, "", offsetof(BlockIO_LgV2, y_2y_1), BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Product",
    0, "", offsetof(BlockIO_LgV2, Product_g), BLOCKIO_SIG, 23, 2, 2, 104, 0 },

  { 53, "lgv2/Control Systems/LgV design 2/Update laws/s_0", 0, "", offsetof
    (BlockIO_LgV2, s_0), BLOCKIO_SIG, 0, 1, 2, 106, 0 },

  { 54, "lgv2/Control Systems/LgV design 2/Update laws/Integrator1", 0, "",
    offsetof(BlockIO_LgV2, Integrator1), BLOCKIO_SIG, 21, 1, 2, 108, 0 },

  { 55,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2), BLOCKIO_SIG, 0, 1, 2, 110, 0 },

  { 56, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/sin(s)",
    0, "", offsetof(BlockIO_LgV2, sins), BLOCKIO_SIG, 0, 1, 2, 112, 0 },

  { 57,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Product", 0,
    "", offsetof(BlockIO_LgV2, Product_m), BLOCKIO_SIG, 0, 1, 2, 114, 0 },

  { 58, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain), BLOCKIO_SIG, 0, 1, 2, 116, 0 },

  { 59, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/cos(s)",
    0, "", offsetof(BlockIO_LgV2, coss), BLOCKIO_SIG, 0, 1, 2, 118, 0 },

  { 60,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1), BLOCKIO_SIG, 0, 1, 2, 120, 0 },

  { 61,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract), BLOCKIO_SIG, 0, 1, 2, 122, 0 },

  { 62,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_c), BLOCKIO_SIG, 23, 2, 2, 124, 0 },

  { 63,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Add",
    0, "", offsetof(BlockIO_LgV2, Add), BLOCKIO_SIG, 23, 2, 2, 126, 0 },

  { 64,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/Trigonometric Function",
    0, "", offsetof(BlockIO_LgV2, TrigonometricFunction), BLOCKIO_SIG, 0, 1, 2,
    128, 0 },

  { 65,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_b), BLOCKIO_SIG, 0, 1, 2, 130, 0 },

  { 66,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation), BLOCKIO_SIG, 0, 1, 2, 132, 0 },

  { 67,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Sign", 0,
    "", offsetof(BlockIO_LgV2, Sign), BLOCKIO_SIG, 0, 1, 2, 134, 0 },

  { 68,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Gain", 0,
    "", offsetof(BlockIO_LgV2, Gain_bx), BLOCKIO_SIG, 0, 1, 2, 136, 0 },

  { 69,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Sum1", 0,
    "", offsetof(BlockIO_LgV2, Sum1), BLOCKIO_SIG, 0, 1, 2, 138, 0 },

  { 70,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction), BLOCKIO_SIG, 0, 1, 2, 140, 0 },

  { 71, "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum), BLOCKIO_SIG, 0, 1, 2, 142, 0 },

  { 72,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_f), BLOCKIO_SIG, 0, 1, 2, 144, 0 },

  { 73,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_n), BLOCKIO_SIG, 0, 1, 2, 146, 0 },

  { 74,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_h), BLOCKIO_SIG, 0, 1, 2, 148, 0 },

  { 75,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_c), BLOCKIO_SIG, 0, 1, 2, 150, 0 },

  { 76,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_m), BLOCKIO_SIG, 0, 1, 2, 152, 0 },

  { 77,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_c), BLOCKIO_SIG, 0, 1, 2, 154, 0 },

  { 78,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_o), BLOCKIO_SIG, 0, 1, 2, 156, 0
  },

  { 79,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_g), BLOCKIO_SIG, 0, 1, 2, 158, 0 },

  { 80,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_c), BLOCKIO_SIG, 0, 1, 2, 160, 0 },

  { 81,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2^T/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_b), BLOCKIO_SIG, 22, 4, 2, 162, 0
  },

  { 82,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/p_d eq/x_2 - x_1",
    0, "", offsetof(BlockIO_LgV2, x_2x_1_m), BLOCKIO_SIG, 0, 1, 2, 164, 0 },

  { 83,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/p_d eq/(x_2 - x_1) + s",
    0, "", offsetof(BlockIO_LgV2, x_2x_1s), BLOCKIO_SIG, 0, 1, 2, 166, 0 },

  { 84,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/p_d eq/(x_2 - x_1) + s + x_1",
    0, "", offsetof(BlockIO_LgV2, x_2x_1sx_1), BLOCKIO_SIG, 0, 1, 2, 168, 0 },

  { 85,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/p_d eq/y_2 - y_1",
    0, "", offsetof(BlockIO_LgV2, y_2y_1_l), BLOCKIO_SIG, 0, 1, 2, 170, 0 },

  { 86,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/p_d eq/(y_2 - y_1) + s",
    0, "", offsetof(BlockIO_LgV2, y_2y_1s), BLOCKIO_SIG, 0, 1, 2, 172, 0 },

  { 87,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/p_d eq/(y_2 - y_1) + s + y_1",
    0, "", offsetof(BlockIO_LgV2, y_2y_1sy_1), BLOCKIO_SIG, 0, 1, 2, 174, 0 },

  { 88,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/p_d1 +a",
    0, "", offsetof(BlockIO_LgV2, p_d1a), BLOCKIO_SIG, 23, 2, 2, 176, 0 },

  { 89, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2_c), BLOCKIO_SIG, 0, 1, 2, 178, 0 },

  { 90, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/cos(s)",
    0, "", offsetof(BlockIO_LgV2, coss_d), BLOCKIO_SIG, 0, 1, 2, 180, 0 },

  { 91, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_k), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Add", 0,
    "", offsetof(BlockIO_LgV2, Add_m), BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/sin(s)",
    0, "", offsetof(BlockIO_LgV2, sins_i), BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_n), BLOCKIO_SIG, 0, 1, 2, 188, 0 },

  { 95, "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Add1", 0,
    "", offsetof(BlockIO_LgV2, Add1), BLOCKIO_SIG, 0, 1, 2, 190, 0 },

  { 96,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/1 - a",
    0, "", offsetof(BlockIO_LgV2, a), BLOCKIO_SIG, 0, 1, 2, 192, 0 },

  { 97,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/p_d2 + (1- a )",
    0, "", offsetof(BlockIO_LgV2, p_d21a), BLOCKIO_SIG, 23, 2, 2, 194, 0 },

  { 98,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/Add",
    0, "", offsetof(BlockIO_LgV2, Add_e), BLOCKIO_SIG, 23, 2, 2, 196, 0 },

  { 99,
    "lgv2/Guidance Systems/Path-following/Path/saturation/Saturation x/Switch",
    0, "", offsetof(BlockIO_LgV2, Switch), BLOCKIO_SIG, 0, 1, 2, 198, 0 },

  { 100,
    "lgv2/Guidance Systems/Path-following/Path/saturation/Saturation x/Switch2",
    0, "", offsetof(BlockIO_LgV2, Switch2), BLOCKIO_SIG, 0, 1, 2, 200, 0 },

  { 101,
    "lgv2/Guidance Systems/Path-following/Path/saturation/Saturation y/Switch",
    0, "", offsetof(BlockIO_LgV2, Switch_m), BLOCKIO_SIG, 0, 1, 2, 202, 0 },

  { 102,
    "lgv2/Guidance Systems/Path-following/Path/saturation/Saturation y/Switch2",
    0, "", offsetof(BlockIO_LgV2, Switch2_h), BLOCKIO_SIG, 0, 1, 2, 204, 0 },

  { 103,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/q - p_d",
    0, "", offsetof(BlockIO_LgV2, qp_d), BLOCKIO_SIG, 23, 2, 2, 206, 0 },

  { 104,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon",
    0, "", offsetof(BlockIO_LgV2, epsilon), BLOCKIO_SIG, 23, 2, 2, 208, 0 },

  { 105,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector",
    0, "", offsetof(BlockIO_LgV2, MultiportSelector), BLOCKIO_SIG, 21, 1, 2, 210,
    0 },

  { 106,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/Trigonometric Function",
    0, "", offsetof(BlockIO_LgV2, TrigonometricFunction_f), BLOCKIO_SIG, 21, 1,
    2, 212, 0 },

  { 107,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_h), BLOCKIO_SIG, 21, 1, 2, 214, 0 },

  { 108,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_i), BLOCKIO_SIG, 21, 1, 2, 216, 0 },

  { 109,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_i), BLOCKIO_SIG, 21, 1, 2, 218, 0 },

  { 110,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_g), BLOCKIO_SIG, 21, 1, 2, 220, 0 },

  { 111,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_f), BLOCKIO_SIG, 21, 1, 2, 222, 0 },

  { 112,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_p), BLOCKIO_SIG, 21, 1, 2, 224, 0
  },

  { 113,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_p), BLOCKIO_SIG, 21, 1, 2, 226, 0 },

  { 114,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_h), BLOCKIO_SIG, 21, 1, 2, 228, 0 },

  { 115,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_a), BLOCKIO_SIG, 21, 1, 2, 230, 0 },

  { 116,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_k), BLOCKIO_SIG, 21, 1, 2, 232, 0 },

  { 117,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_c), BLOCKIO_SIG, 21, 1, 2, 234, 0 },

  { 118,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_d), BLOCKIO_SIG, 21, 1, 2, 236, 0 },

  { 119,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_ki), BLOCKIO_SIG, 21, 1, 2, 238, 0 },

  { 120,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_a), BLOCKIO_SIG, 21, 1, 2, 240, 0 },

  { 121,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_bn), BLOCKIO_SIG, 21, 1, 2, 242,
    0 },

  { 122,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_o), BLOCKIO_SIG, 21, 1, 2, 244, 0 },

  { 123,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_o), BLOCKIO_SIG, 21, 1, 2, 246, 0 },

  { 124,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/Vector Concatenate",
    0, "", offsetof(BlockIO_LgV2, VectorConcatenate), BLOCKIO_SIG, 24, 3, 2, 248,
    0 },

  { 125, "lgv2/Guidance Systems/q_x", 0, "", offsetof(BlockIO_LgV2, q_x),
    BLOCKIO_SIG, 0, 1, 2, 250, 0 },

  { 126, "lgv2/Guidance Systems/q_y", 0, "", offsetof(BlockIO_LgV2, q_y),
    BLOCKIO_SIG, 0, 1, 2, 252, 0 },

  { 127, "lgv2/Guidance Systems/psi_los", 0, "", offsetof(BlockIO_LgV2, psi_los),
    BLOCKIO_SIG, 0, 1, 2, 254, 0 },

  { 128, "lgv2/Guidance Systems/path x_d", 0, "", offsetof(BlockIO_LgV2, pathx_d),
    BLOCKIO_SIG, 0, 1, 2, 256, 0 },

  { 129, "lgv2/Guidance Systems/path y_d", 0, "", offsetof(BlockIO_LgV2, pathy_d),
    BLOCKIO_SIG, 0, 1, 2, 258, 0 },

  { 130, "lgv2/Guidance Systems/path psi_d", 0, "", offsetof(BlockIO_LgV2,
    pathpsi_d), BLOCKIO_SIG, 0, 1, 2, 260, 0 },

  { 131,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_i), BLOCKIO_SIG, 20, 2, 2, 262, 0
  },

  { 132,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_p), BLOCKIO_SIG, 0, 1, 2, 264, 0 },

  { 133,
    "lgv2/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/sqrt", 0,
    "", offsetof(BlockIO_LgV2, sqrt_p), BLOCKIO_SIG, 0, 1, 2, 266, 0 },

  { 134,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Product",
    0, "", offsetof(BlockIO_LgV2, Product_ka), BLOCKIO_SIG, 0, 1, 2, 268, 0 },

  { 135,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_h), BLOCKIO_SIG, 20, 2, 2, 270, 0
  },

  { 136,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_b), BLOCKIO_SIG, 0, 1, 2, 272, 0 },

  { 137,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq/sqrt", 0,
    "", offsetof(BlockIO_LgV2, sqrt_h), BLOCKIO_SIG, 0, 1, 2, 274, 0 },

  { 138,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_d), BLOCKIO_SIG, 0, 1, 2, 276, 0 },

  { 139,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_j), BLOCKIO_SIG, 0, 1, 2, 278, 0 },

  { 140,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Add",
    0, "", offsetof(BlockIO_LgV2, Add_n), BLOCKIO_SIG, 0, 1, 2, 280, 0 },

  { 141, "lgv2/Guidance Systems/Path-following/Speed assigment/v_s eq/Divide", 0,
    "", offsetof(BlockIO_LgV2, Divide), BLOCKIO_SIG, 0, 1, 2, 282, 0 },

  { 142, "lgv2/Control Systems/PS3 input/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_LgV2,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 284, 0 },

  { 143, "lgv2/Control Systems/PS3 u input control/PS3 u_1", 0, "u_1", offsetof
    (BlockIO_LgV2, u_1), BLOCKIO_SIG, 0, 1, 2, 286, 0 },

  { 144, "lgv2/Control Systems/PS3 input/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_LgV2,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 288, 0 },

  { 145, "lgv2/Control Systems/PS3 u input control/PS3 u_2", 0, "u_2", offsetof
    (BlockIO_LgV2, u_2), BLOCKIO_SIG, 0, 1, 2, 290, 0 },

  { 146, "lgv2/Control Systems/PS3 input/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_LgV2,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 292, 0 },

  { 147, "lgv2/Control Systems/PS3 u input control/PS3 u_3", 0, "u_3", offsetof
    (BlockIO_LgV2, u_3), BLOCKIO_SIG, 0, 1, 2, 294, 0 },

  { 148, "lgv2/Control Systems/PS3 input/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_LgV2,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 296, 0 },

  { 149, "lgv2/Control Systems/PS3 u input control/PS3 u_4", 0, "u_4", offsetof
    (BlockIO_LgV2, u_4), BLOCKIO_SIG, 0, 1, 2, 298, 0 },

  { 150, "lgv2/Control Systems/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_LgV2, BowThrusterdirection),
    BLOCKIO_SIG, 0, 1, 2, 300, 0 },

  { 151, "lgv2/Control Systems/PS3 u input control/PS3 u_5", 0, "u_5", offsetof
    (BlockIO_LgV2, u_5), BLOCKIO_SIG, 0, 1, 2, 302, 0 },

  { 152,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_LgV2, l_x1), BLOCKIO_SIG, 0, 1, 2, 304, 0 },

  { 153,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_LgV2, l_y2), BLOCKIO_SIG, 0, 1, 2, 306, 0 },

  { 154,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_LgV2, l_x2), BLOCKIO_SIG, 0, 1, 2, 308, 0 },

  { 155,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_LgV2, x5), BLOCKIO_SIG, 31, 15, 2, 310, 0 },

  { 156,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_LgV2, Pseudoinverse), BLOCKIO_SIG, 30, 15, 2, 312, 0
  },

  { 157, "lgv2/Control Systems/DP control/DP controller/yaw angle", 0, "psi",
    offsetof(BlockIO_LgV2, psi), BLOCKIO_SIG, 0, 1, 2, 314, 0 },

  { 158,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_ha), BLOCKIO_SIG, 0, 1, 2, 316, 0 },

  { 159,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_a), BLOCKIO_SIG, 0, 1, 2, 318, 0 },

  { 160,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_j), BLOCKIO_SIG, 0, 1, 2, 320, 0 },

  { 161,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_i), BLOCKIO_SIG, 0, 1, 2, 322, 0 },

  { 162,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_ij), BLOCKIO_SIG, 0, 1, 2, 324, 0
  },

  { 163,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_b), BLOCKIO_SIG, 0, 1, 2, 326, 0 },

  { 164, "lgv2/Control Systems/DP control/DP controller/Sum2", 0,
    "regulation error", offsetof(BlockIO_LgV2, regulationerror), BLOCKIO_SIG, 24,
    3, 2, 328, 0 },

  { 165,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_m), BLOCKIO_SIG, 0, 1, 2, 330, 0 },

  { 166,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_j), BLOCKIO_SIG, 0, 1, 2, 332, 0 },

  { 167,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_a), BLOCKIO_SIG, 0, 1, 2, 334, 0 },

  { 168,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_p), BLOCKIO_SIG, 0, 1, 2, 336, 0 },

  { 169,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_d), BLOCKIO_SIG, 0, 1, 2, 338, 0
  },

  { 170,
    "lgv2/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_j), BLOCKIO_SIG, 0, 1, 2, 340, 0 },

  { 171,
    "lgv2/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_LgV2, Row1), BLOCKIO_SIG, 0, 1, 2, 342, 0 },

  { 172,
    "lgv2/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_LgV2, Row2), BLOCKIO_SIG, 0, 1, 2, 344, 0 },

  { 173,
    "lgv2/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_LgV2, Row3), BLOCKIO_SIG, 0, 1, 2, 346, 0 },

  { 174, "lgv2/Control Systems/DP control/DP controller/Kp", 0, "", offsetof
    (BlockIO_LgV2, Kp), BLOCKIO_SIG, 24, 3, 2, 348, 0 },

  { 175, "lgv2/Control Systems/DP control/DP controller/K_p_surge_scale", 0, "",
    offsetof(BlockIO_LgV2, K_p_surge_scale), BLOCKIO_SIG, 0, 1, 2, 350, 0 },

  { 176, "lgv2/Control Systems/DP control/DP controller/K_p_sway_scale", 0, "",
    offsetof(BlockIO_LgV2, K_p_sway_scale), BLOCKIO_SIG, 0, 1, 2, 352, 0 },

  { 177, "lgv2/Control Systems/DP control/DP controller/K_p_yaw_scale", 0, "",
    offsetof(BlockIO_LgV2, K_p_yaw_scale), BLOCKIO_SIG, 0, 1, 2, 354, 0 },

  { 178, "lgv2/Control Systems/DP control/DP controller/Integrator", 0, "",
    offsetof(BlockIO_LgV2, Integrator_g), BLOCKIO_SIG, 24, 3, 2, 356, 0 },

  { 179, "lgv2/Control Systems/DP control/DP controller/Ki", 0, "", offsetof
    (BlockIO_LgV2, Ki), BLOCKIO_SIG, 24, 3, 2, 358, 0 },

  { 180, "lgv2/Control Systems/DP control/DP controller/K_i_surge_scale", 0, "",
    offsetof(BlockIO_LgV2, K_i_surge_scale), BLOCKIO_SIG, 0, 1, 2, 360, 0 },

  { 181, "lgv2/Control Systems/DP control/DP controller/K_i_sway_scale", 0, "",
    offsetof(BlockIO_LgV2, K_i_sway_scale), BLOCKIO_SIG, 0, 1, 2, 362, 0 },

  { 182, "lgv2/Control Systems/DP control/DP controller/K_i_yaw_scale", 0, "",
    offsetof(BlockIO_LgV2, K_i_yaw_scale), BLOCKIO_SIG, 0, 1, 2, 364, 0 },

  { 183, "lgv2/Control Systems/DP control/DP controller/Sum3", 0, "", offsetof
    (BlockIO_LgV2, Sum3), BLOCKIO_SIG, 24, 3, 2, 366, 0 },

  { 184, "lgv2/Control Systems/DP control/DP controller/Kd", 0, "", offsetof
    (BlockIO_LgV2, Kd), BLOCKIO_SIG, 24, 3, 2, 368, 0 },

  { 185, "lgv2/Control Systems/DP control/DP controller/K_d_surge_scale", 0, "",
    offsetof(BlockIO_LgV2, K_d_surge_scale), BLOCKIO_SIG, 0, 1, 2, 370, 0 },

  { 186, "lgv2/Control Systems/DP control/DP controller/K_d_sway_scale", 0, "",
    offsetof(BlockIO_LgV2, K_d_sway_scale), BLOCKIO_SIG, 0, 1, 2, 372, 0 },

  { 187, "lgv2/Control Systems/DP control/DP controller/K_d_yaw_scale", 0, "",
    offsetof(BlockIO_LgV2, K_d_yaw_scale), BLOCKIO_SIG, 0, 1, 2, 374, 0 },

  { 188, "lgv2/Control Systems/DP control/DP controller/Sum1", 0, "", offsetof
    (BlockIO_LgV2, Sum1_j), BLOCKIO_SIG, 24, 3, 2, 376, 0 },

  { 189,
    "lgv2/Control Systems/DP control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_LgV2, Product_o), BLOCKIO_SIG, 29, 5, 2, 378, 0 },

  { 190,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone), BLOCKIO_SIG, 0, 1, 2, 380, 0 },

  { 191,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_LgV2, f_10), BLOCKIO_SIG, 0, 1, 2, 382, 0 },

  { 192,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_LgV2, f_10_l), BLOCKIO_SIG, 0, 1, 2, 384, 0 },

  { 193,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch), BLOCKIO_SIG, 0, 1, 2, 386, 0
  },

  { 194,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone_j), BLOCKIO_SIG, 0, 1, 2, 388, 0 },

  { 195,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_LgV2, f_20), BLOCKIO_SIG, 0, 1, 2, 390, 0 },

  { 196,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_LgV2, f_20_l), BLOCKIO_SIG, 0, 1, 2, 392, 0 },

  { 197,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch_h), BLOCKIO_SIG, 0, 1, 2, 394,
    0 },

  { 198,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone_m), BLOCKIO_SIG, 0, 1, 2, 396, 0 },

  { 199,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_LgV2, f_30), BLOCKIO_SIG, 0, 1, 2, 398, 0 },

  { 200,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_LgV2, f_30_o), BLOCKIO_SIG, 0, 1, 2, 400, 0 },

  { 201,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch_c), BLOCKIO_SIG, 0, 1, 2, 402,
    0 },

  { 202,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone_g), BLOCKIO_SIG, 0, 1, 2, 404, 0 },

  { 203,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_LgV2, f_40), BLOCKIO_SIG, 0, 1, 2, 406, 0 },

  { 204,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_LgV2, f_40_f), BLOCKIO_SIG, 0, 1, 2, 408, 0 },

  { 205,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch_cc), BLOCKIO_SIG, 0, 1, 2, 410,
    0 },

  { 206,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone_f), BLOCKIO_SIG, 0, 1, 2, 412, 0 },

  { 207,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_LgV2, f_50), BLOCKIO_SIG, 0, 1, 2, 414, 0 },

  { 208,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_LgV2, f_50_g), BLOCKIO_SIG, 0, 1, 2, 416, 0 },

  { 209,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch_hs), BLOCKIO_SIG, 0, 1, 2, 418,
    0 },

  { 210, "lgv2/Control Systems/DP control/Saturation", 0, "", offsetof
    (BlockIO_LgV2, Saturation_p), BLOCKIO_SIG, 29, 5, 2, 420, 0 },

  { 211,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_LgV2, l_x1_d), BLOCKIO_SIG, 0, 1, 2, 422, 0 },

  { 212,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_LgV2, l_y2_h), BLOCKIO_SIG, 0, 1, 2, 424, 0 },

  { 213,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_LgV2, l_x2_m), BLOCKIO_SIG, 0, 1, 2, 426, 0 },

  { 214,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_LgV2, x5_a), BLOCKIO_SIG, 31, 15, 2, 428, 0 },

  { 215,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_LgV2, Pseudoinverse_j), BLOCKIO_SIG, 30, 15, 2, 430,
    0 },

  { 216, "lgv2/Control Systems/LgV design 2/R(psi)/R11", 0, "", offsetof
    (BlockIO_LgV2, R11_c), BLOCKIO_SIG, 0, 1, 2, 432, 0 },

  { 217, "lgv2/Control Systems/LgV design 2/R(psi)/R21", 0, "", offsetof
    (BlockIO_LgV2, R21_m), BLOCKIO_SIG, 0, 1, 2, 434, 0 },

  { 218, "lgv2/Control Systems/LgV design 2/R(psi)/R12", 0, "", offsetof
    (BlockIO_LgV2, R12_f), BLOCKIO_SIG, 0, 1, 2, 436, 0 },

  { 219, "lgv2/Control Systems/LgV design 2/R(psi)/-1", 0, "", offsetof
    (BlockIO_LgV2, u), BLOCKIO_SIG, 0, 1, 2, 438, 0 },

  { 220, "lgv2/Control Systems/LgV design 2/R(psi)/R22", 0, "", offsetof
    (BlockIO_LgV2, R22_p), BLOCKIO_SIG, 0, 1, 2, 440, 0 },

  { 221, "lgv2/Control Systems/LgV design 2/R(psi)/R(psi)", 0, "", offsetof
    (BlockIO_LgV2, Rpsi), BLOCKIO_SIG, 36, 9, 2, 442, 0 },

  { 222, "lgv2/Control Systems/LgV design 2/R^T/Math Function", 0, "", offsetof
    (BlockIO_LgV2, MathFunction_dr), BLOCKIO_SIG, 36, 9, 2, 444, 0 },

  { 223, "lgv2/Control Systems/LgV design 2/K_i/3x3", 0, "", offsetof
    (BlockIO_LgV2, x3), BLOCKIO_SIG, 36, 9, 2, 446, 0 },

  { 224, "lgv2/Control Systems/LgV design 2/Integral action state/Integrator", 0,
    "", offsetof(BlockIO_LgV2, Integrator_k), BLOCKIO_SIG, 26, 3, 2, 448, 0 },

  { 225, "lgv2/Control Systems/LgV design 2/Control law/Product", 0, "",
    offsetof(BlockIO_LgV2, Product_c), BLOCKIO_SIG, 26, 3, 2, 450, 0 },

  { 226, "lgv2/Control Systems/LgV design 2/K_d/3x3", 0, "", offsetof
    (BlockIO_LgV2, x3_d), BLOCKIO_SIG, 36, 9, 2, 452, 0 },

  { 227, "lgv2/Control Systems/LgV design 2/Control law/4", 0, "", offsetof
    (BlockIO_LgV2, u_n), BLOCKIO_SIG, 0, 1, 2, 454, 0 },

  { 228, "lgv2/Control Systems/LgV design 2/Control law/Divide", 0, "", offsetof
    (BlockIO_LgV2, Divide_g), BLOCKIO_SIG, 0, 1, 2, 456, 0 },

  { 229, "lgv2/Control Systems/LgV design 2/Control law/Add1", 0, "", offsetof
    (BlockIO_LgV2, Add1_j), BLOCKIO_SIG, 36, 9, 2, 458, 0 },

  { 230, "lgv2/Control Systems/LgV design 2/K_p/R(psi)", 0, "", offsetof
    (BlockIO_LgV2, Rpsi_n), BLOCKIO_SIG, 36, 9, 2, 460, 0 },

  { 231, "lgv2/Control Systems/LgV design 2/Virtual control/Product", 0, "",
    offsetof(BlockIO_LgV2, Product_bs), BLOCKIO_SIG, 36, 9, 2, 462, 0 },

  { 232, "lgv2/Control Systems/LgV design 2/Virtual control/Subtract", 0, "",
    offsetof(BlockIO_LgV2, Subtract_dr), BLOCKIO_SIG, 36, 9, 2, 464, 0 },

  { 233,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_c), BLOCKIO_SIG, 0, 1, 2, 466, 0 },

  { 234,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_cg), BLOCKIO_SIG, 0, 1, 2, 468, 0 },

  { 235,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_g), BLOCKIO_SIG, 0, 1, 2, 470, 0 },

  { 236,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_je), BLOCKIO_SIG, 0, 1, 2, 472, 0 },

  { 237,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_e), BLOCKIO_SIG, 0, 1, 2, 474, 0 },

  { 238,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_f), BLOCKIO_SIG, 0, 1, 2, 476, 0
  },

  { 239,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_d), BLOCKIO_SIG, 0, 1, 2, 478, 0 },

  { 240,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_l), BLOCKIO_SIG, 0, 1, 2, 480, 0 },

  { 241, "lgv2/Control Systems/LgV design 2/z_1 eq/Subtract", 0, "", offsetof
    (BlockIO_LgV2, Subtract_f), BLOCKIO_SIG, 24, 3, 2, 482, 0 },

  { 242,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_bu), BLOCKIO_SIG, 0, 1, 2, 484, 0 },

  { 243,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_LgV2, Saturation_d), BLOCKIO_SIG, 0, 1, 2, 486, 0 },

  { 244,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_LgV2, Sign_g2), BLOCKIO_SIG, 0, 1, 2, 488, 0 },

  { 245,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_ag), BLOCKIO_SIG, 0, 1, 2, 490, 0 },

  { 246,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_LgV2, Sum1_h), BLOCKIO_SIG, 0, 1, 2, 492, 0 },

  { 247,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_od), BLOCKIO_SIG, 0, 1, 2, 494, 0
  },

  { 248,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_e), BLOCKIO_SIG, 0, 1, 2, 496, 0 },

  { 249,
    "lgv2/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_m), BLOCKIO_SIG, 0, 1, 2, 498, 0 },

  { 250, "lgv2/Control Systems/LgV design 2/z_1 eq/Product", 0, "", offsetof
    (BlockIO_LgV2, Product_i), BLOCKIO_SIG, 24, 3, 2, 500, 0 },

  { 251, "lgv2/Control Systems/LgV design 2/Virtual control/Product1", 0, "",
    offsetof(BlockIO_LgV2, Product1_ce), BLOCKIO_SIG, 24, 3, 2, 502, 0 },

  { 252,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qx",
    0, "", offsetof(BlockIO_LgV2, f_qx), BLOCKIO_SIG, 21, 1, 2, 504, 0 },

  { 253,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qy",
    0, "", offsetof(BlockIO_LgV2, f_qy), BLOCKIO_SIG, 21, 1, 2, 506, 0 },

  { 254,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_g5), BLOCKIO_SIG, 23, 2, 2, 508, 0 },

  { 255,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Delta^2",
    0, "", offsetof(BlockIO_LgV2, Delta2), BLOCKIO_SIG, 0, 1, 2, 510, 0 },

  { 256,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_n2), BLOCKIO_SIG, 21, 1, 2, 512, 0 },

  { 257,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_o), BLOCKIO_SIG, 21, 1, 2, 514, 0 },

  { 258,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_gx), BLOCKIO_SIG, 21, 1, 2, 516, 0 },

  { 259,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector1",
    0, "", offsetof(BlockIO_LgV2, MultiportSelector1), BLOCKIO_SIG, 20, 2, 2,
    518, 0 },

  { 260,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_n), BLOCKIO_SIG, 20, 2, 2, 520, 0 },

  { 261,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/-1",
    0, "", offsetof(BlockIO_LgV2, u_o), BLOCKIO_SIG, 20, 2, 2, 522, 0 },

  { 262,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q eq/Vector Concatenate",
    0, "", offsetof(BlockIO_LgV2, VectorConcatenate_e), BLOCKIO_SIG, 24, 3, 2,
    524, 0 },

  { 263,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Product",
    0, "", offsetof(BlockIO_LgV2, Product_a), BLOCKIO_SIG, 23, 2, 2, 526, 0 },

  { 264,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2_b), BLOCKIO_SIG, 0, 1, 2, 528, 0 },

  { 265,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/sin(s)3",
    0, "", offsetof(BlockIO_LgV2, sins3), BLOCKIO_SIG, 0, 1, 2, 530, 0 },

  { 266,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_l), BLOCKIO_SIG, 0, 1, 2, 532, 0
  },

  { 267,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_nx), BLOCKIO_SIG, 0, 1, 2, 534, 0 },

  { 268,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/cos(s)3",
    0, "", offsetof(BlockIO_LgV2, coss3), BLOCKIO_SIG, 0, 1, 2, 536, 0 },

  { 269,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_o), BLOCKIO_SIG, 0, 1, 2, 538, 0 },

  { 270,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Gain", 0,
    "", offsetof(BlockIO_LgV2, Gain_d), BLOCKIO_SIG, 0, 1, 2, 540, 0 },

  { 271,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_j), BLOCKIO_SIG, 0, 1, 2, 542, 0 },

  { 272,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_m), BLOCKIO_SIG, 23, 2, 2, 544, 0 },

  { 273,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Add",
    0, "", offsetof(BlockIO_LgV2, Add_mw), BLOCKIO_SIG, 23, 2, 2, 546, 0 },

  { 274,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s eq/x_d^s + y_d^s^2", 0,
    "", offsetof(BlockIO_LgV2, x_dsy_ds2), BLOCKIO_SIG, 0, 1, 2, 548, 0 },

  { 275,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s eq/x_d^s^2 + y_d^s", 0,
    "", offsetof(BlockIO_LgV2, x_ds2y_ds), BLOCKIO_SIG, 0, 1, 2, 550, 0 },

  { 276,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s eq/( x_d^s + y_d^s^2 ) - ( x_d^s^2 + y_d^s )",
    0, "", offsetof(BlockIO_LgV2, x_dsy_ds2x_ds2y_ds), BLOCKIO_SIG, 0, 1, 2, 552,
    0 },

  { 277, "lgv2/Guidance Systems/Path-following/Heading/psi_d^s eq/( x_d^s )^2",
    0, "", offsetof(BlockIO_LgV2, x_ds2), BLOCKIO_SIG, 0, 1, 2, 554, 0 },

  { 278, "lgv2/Guidance Systems/Path-following/Heading/psi_d^s eq/( y_d^s )^2",
    0, "", offsetof(BlockIO_LgV2, y_ds2), BLOCKIO_SIG, 0, 1, 2, 556, 0 },

  { 279,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s eq/( x_d^s )^2 + ( y_d^s )^2",
    0, "", offsetof(BlockIO_LgV2, x_ds2y_ds2), BLOCKIO_SIG, 0, 1, 2, 558, 0 },

  { 280, "lgv2/Guidance Systems/Path-following/Heading/psi_d^s eq/Divide", 0, "",
    offsetof(BlockIO_LgV2, Divide_h), BLOCKIO_SIG, 0, 1, 2, 560, 0 },

  { 281,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Delta^2",
    0, "", offsetof(BlockIO_LgV2, Delta2_h), BLOCKIO_SIG, 0, 1, 2, 562, 0 },

  { 282,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_n2_c), BLOCKIO_SIG, 21, 1, 2, 564, 0 },

  { 283,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_no), BLOCKIO_SIG, 21, 1, 2, 566, 0 },

  { 284,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_a), BLOCKIO_SIG, 21, 1, 2, 568, 0 },

  { 285,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2^T/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_ii), BLOCKIO_SIG, 22, 4, 2, 570,
    0 },

  { 286,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_gx), BLOCKIO_SIG, 23, 2, 2, 572, 0 },

  { 287,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_p), BLOCKIO_SIG, 23, 2, 2, 574, 0 },

  { 288,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq/Subtract1",
    0, "", offsetof(BlockIO_LgV2, Subtract1), BLOCKIO_SIG, 23, 2, 2, 576, 0 },

  { 289,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector2",
    0, "", offsetof(BlockIO_LgV2, MultiportSelector2), BLOCKIO_SIG, 21, 1, 2,
    578, 0 },

  { 290,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_ay), BLOCKIO_SIG, 21, 1, 2, 580, 0 },

  { 291,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_h), BLOCKIO_SIG, 21, 1, 2, 582, 0 },

  { 292,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_n2_i), BLOCKIO_SIG, 21, 1, 2, 584, 0 },

  { 293,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Delta^2",
    0, "", offsetof(BlockIO_LgV2, Delta2_b), BLOCKIO_SIG, 0, 1, 2, 586, 0 },

  { 294,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_mh), BLOCKIO_SIG, 21, 1, 2, 588, 0 },

  { 295,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/sqrt",
    0, "", offsetof(BlockIO_LgV2, sqrt_c), BLOCKIO_SIG, 21, 1, 2, 590, 0 },

  { 296,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_f), BLOCKIO_SIG, 21, 1, 2, 592, 0 },

  { 297,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_bv), BLOCKIO_SIG, 21, 1, 2, 594, 0 },

  { 298,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_p1), BLOCKIO_SIG, 20, 2, 2, 596,
    0 },

  { 299,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_k), BLOCKIO_SIG, 20, 2, 2, 598, 0 },

  { 300,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_e), BLOCKIO_SIG, 23, 2, 2, 600, 0 },

  { 301,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_kj), BLOCKIO_SIG, 0, 1, 2, 602, 0 },

  { 302,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_c0), BLOCKIO_SIG, 0, 1, 2, 604, 0 },

  { 303,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_l), BLOCKIO_SIG, 21, 1, 2, 606, 0 },

  { 304,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_LgV2, VectorConcatenate_eb), BLOCKIO_SIG, 26, 3, 2,
    608, 0 },

  { 305, "lgv2/Control Systems/LgV design 2/Virtual control/Add", 0, "",
    offsetof(BlockIO_LgV2, Add_c), BLOCKIO_SIG, 26, 3, 2, 610, 0 },

  { 306, "lgv2/Control Systems/LgV design 2/Virtual control/Product2", 0, "",
    offsetof(BlockIO_LgV2, Product2_p), BLOCKIO_SIG, 26, 3, 2, 612, 0 },

  { 307, "lgv2/Control Systems/LgV design 2/Virtual control/Sum", 0, "",
    offsetof(BlockIO_LgV2, Sum_p5), BLOCKIO_SIG, 26, 3, 2, 614, 0 },

  { 308, "lgv2/Control Systems/LgV design 2/z_2 eq/Subtract", 0, "", offsetof
    (BlockIO_LgV2, Subtract_di), BLOCKIO_SIG, 26, 3, 2, 616, 0 },

  { 309, "lgv2/Control Systems/LgV design 2/Control law/Product1", 0, "",
    offsetof(BlockIO_LgV2, Product1_a), BLOCKIO_SIG, 26, 3, 2, 618, 0 },

  { 310, "lgv2/Control Systems/LgV design 2/Control law/D_L/-X_u", 0, "",
    offsetof(BlockIO_LgV2, X_u), BLOCKIO_SIG, 0, 1, 2, 620, 0 },

  { 311, "lgv2/Control Systems/LgV design 2/Control law/D_L/-Y_v", 0, "",
    offsetof(BlockIO_LgV2, Y_v), BLOCKIO_SIG, 0, 1, 2, 622, 0 },

  { 312, "lgv2/Control Systems/LgV design 2/Control law/D_L/-N_v", 0, "",
    offsetof(BlockIO_LgV2, N_v), BLOCKIO_SIG, 0, 1, 2, 624, 0 },

  { 313, "lgv2/Control Systems/LgV design 2/Control law/D_L/-Y_vr", 0, "",
    offsetof(BlockIO_LgV2, Y_vr), BLOCKIO_SIG, 0, 1, 2, 626, 0 },

  { 314, "lgv2/Control Systems/LgV design 2/Control law/D_L/-N_r", 0, "",
    offsetof(BlockIO_LgV2, N_r), BLOCKIO_SIG, 0, 1, 2, 628, 0 },

  { 315,
    "lgv2/Control Systems/LgV design 2/Control law/D_L/Linear Dampning matrix",
    0, "", offsetof(BlockIO_LgV2, LinearDampningmatrix), BLOCKIO_SIG, 36, 9, 2,
    630, 0 },

  { 316, "lgv2/Control Systems/LgV design 2/Control law/Product2", 0, "",
    offsetof(BlockIO_LgV2, Product2_o), BLOCKIO_SIG, 24, 3, 2, 632, 0 },

  { 317, "lgv2/Control Systems/LgV design 2/M/M_11", 0, "", offsetof
    (BlockIO_LgV2, M_11), BLOCKIO_SIG, 0, 1, 2, 634, 0 },

  { 318, "lgv2/Control Systems/LgV design 2/M/M_22", 0, "", offsetof
    (BlockIO_LgV2, M_22), BLOCKIO_SIG, 0, 1, 2, 636, 0 },

  { 319, "lgv2/Control Systems/LgV design 2/M/m x_g", 0, "", offsetof
    (BlockIO_LgV2, mx_g), BLOCKIO_SIG, 0, 1, 2, 638, 0 },

  { 320, "lgv2/Control Systems/LgV design 2/M/M_32", 0, "", offsetof
    (BlockIO_LgV2, M_32), BLOCKIO_SIG, 0, 1, 2, 640, 0 },

  { 321, "lgv2/Control Systems/LgV design 2/M/M_23", 0, "", offsetof
    (BlockIO_LgV2, M_23), BLOCKIO_SIG, 0, 1, 2, 642, 0 },

  { 322, "lgv2/Control Systems/LgV design 2/M/M_33", 0, "", offsetof
    (BlockIO_LgV2, M_33), BLOCKIO_SIG, 0, 1, 2, 644, 0 },

  { 323, "lgv2/Control Systems/LgV design 2/M/3x3", 0, "", offsetof(BlockIO_LgV2,
    x3_n), BLOCKIO_SIG, 36, 9, 2, 646, 0 },

  { 324, "lgv2/Control Systems/LgV design 2/sigma eq/Product1", 0, "", offsetof
    (BlockIO_LgV2, Product1_e), BLOCKIO_SIG, 36, 9, 2, 648, 0 },

  { 325, "lgv2/Control Systems/LgV design 2/sigma eq/Add3", 0, "", offsetof
    (BlockIO_LgV2, Add3), BLOCKIO_SIG, 36, 9, 2, 650, 0 },

  { 326, "lgv2/Control Systems/LgV design 2/S(r)/S12", 0, "", offsetof
    (BlockIO_LgV2, S12), BLOCKIO_SIG, 0, 1, 2, 652, 0 },

  { 327, "lgv2/Control Systems/LgV design 2/S(r)/S(r)", 0, "", offsetof
    (BlockIO_LgV2, Sr), BLOCKIO_SIG, 36, 9, 2, 654, 0 },

  { 328, "lgv2/Control Systems/LgV design 2/S^T/Math Function", 0, "", offsetof
    (BlockIO_LgV2, MathFunction_oi), BLOCKIO_SIG, 36, 9, 2, 656, 0 },

  { 329, "lgv2/Control Systems/LgV design 2/sigma eq/Product", 0, "", offsetof
    (BlockIO_LgV2, Product_gv), BLOCKIO_SIG, 24, 3, 2, 658, 0 },

  { 330, "lgv2/Control Systems/LgV design 2/sigma eq/Add", 0, "", offsetof
    (BlockIO_LgV2, Add_ot), BLOCKIO_SIG, 24, 3, 2, 660, 0 },

  { 331, "lgv2/Control Systems/LgV design 2/sigma eq/Product2", 0, "", offsetof
    (BlockIO_LgV2, Product2_i), BLOCKIO_SIG, 24, 3, 2, 662, 0 },

  { 332, "lgv2/Control Systems/LgV design 2/sigma eq/Add1", 0, "", offsetof
    (BlockIO_LgV2, Add1_o), BLOCKIO_SIG, 26, 3, 2, 664, 0 },

  { 333, "lgv2/Control Systems/LgV design 2/sigma eq/Product3", 0, "", offsetof
    (BlockIO_LgV2, Product3), BLOCKIO_SIG, 26, 3, 2, 666, 0 },

  { 334,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function",
    0, "", offsetof(BlockIO_LgV2, TrigonometricFunction_b), BLOCKIO_SIG, 21, 1,
    2, 668, 0 },

  { 335,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_LgV2, TrigonometricFunction1), BLOCKIO_SIG, 21, 1, 2,
    670, 0 },

  { 336, "lgv2/Guidance Systems/Path-following/Speed assigment/Derivative", 0,
    "", offsetof(BlockIO_LgV2, Derivative_j), BLOCKIO_SIG, 0, 1, 2, 672, 0 },

  { 337,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_kt), BLOCKIO_SIG, 23, 2, 2, 674, 0 },

  { 338,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_LgV2, VectorConcatenate_m), BLOCKIO_SIG, 24, 3, 2,
    676, 0 },

  { 339,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/epsilon_n^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_n2_cp), BLOCKIO_SIG, 21, 1, 2, 678, 0
  },

  { 340,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Delta^2",
    0, "", offsetof(BlockIO_LgV2, Delta2_n), BLOCKIO_SIG, 0, 1, 2, 680, 0 },

  { 341,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_g), BLOCKIO_SIG, 21, 1, 2, 682, 0 },

  { 342,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/sqrt",
    0, "", offsetof(BlockIO_LgV2, sqrt_n), BLOCKIO_SIG, 21, 1, 2, 684, 0 },

  { 343,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_f1), BLOCKIO_SIG, 21, 1, 2, 686, 0 },

  { 344, "lgv2/Guidance Systems/Path-following/Speed assigment/v_s^t eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_fp), BLOCKIO_SIG, 0, 1, 2, 688, 0 },

  { 345,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_l), BLOCKIO_SIG, 21, 1, 2, 690, 0 },

  { 346,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_LgV2, VectorConcatenate_c), BLOCKIO_SIG, 26, 3, 2,
    692, 0 },

  { 347, "lgv2/Control Systems/LgV design 2/sigma eq/Add2", 0, "", offsetof
    (BlockIO_LgV2, Add2), BLOCKIO_SIG, 26, 3, 2, 694, 0 },

  { 348, "lgv2/Control Systems/LgV design 2/sigma eq/Product4", 0, "", offsetof
    (BlockIO_LgV2, Product4), BLOCKIO_SIG, 26, 3, 2, 696, 0 },

  { 349, "lgv2/Control Systems/LgV design 2/sigma eq/Sum", 0, "", offsetof
    (BlockIO_LgV2, Sum_m), BLOCKIO_SIG, 26, 3, 2, 698, 0 },

  { 350, "lgv2/Control Systems/LgV design 2/Control law/Product4", 0, "",
    offsetof(BlockIO_LgV2, Product4_h), BLOCKIO_SIG, 26, 3, 2, 700, 0 },

  { 351, "lgv2/Control Systems/LgV design 2/alpha^q/Product1", 0, "", offsetof
    (BlockIO_LgV2, Product1_h), BLOCKIO_SIG, 36, 9, 2, 702, 0 },

  { 352, "lgv2/Control Systems/LgV design 2/alpha^q/Add", 0, "", offsetof
    (BlockIO_LgV2, Add_e3), BLOCKIO_SIG, 36, 9, 2, 704, 0 },

  { 353,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/Matrix Concatenate",
    0, "", offsetof(BlockIO_LgV2, MatrixConcatenate), BLOCKIO_SIG, 25, 6, 2, 706,
    0 },

  { 354, "lgv2/Control Systems/LgV design 2/alpha^q/Product3", 0, "", offsetof
    (BlockIO_LgV2, Product3_j), BLOCKIO_SIG, 25, 6, 2, 708, 0 },

  { 355,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_LgV2, TrigonometricFunction1_h), BLOCKIO_SIG, 21, 1,
    2, 710, 0 },

  { 356,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_ah), BLOCKIO_SIG, 21, 1, 2, 712, 0 },

  { 357,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_aq), BLOCKIO_SIG, 20, 2, 2, 714, 0 },

  { 358,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function",
    0, "", offsetof(BlockIO_LgV2, TrigonometricFunction_n), BLOCKIO_SIG, 21, 1,
    2, 716, 0 },

  { 359,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2_c1), BLOCKIO_SIG, 20, 2, 2, 718, 0 },

  { 360,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_LgV2, MatrixConcatenate_b), BLOCKIO_SIG, 22, 4, 2,
    720, 0 },

  { 361,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_pg), BLOCKIO_SIG, 22, 4, 2, 722, 0 },

  { 362,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/f_q^T/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_j), BLOCKIO_SIG, 20, 2, 2, 724, 0
  },

  { 363,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2_om), BLOCKIO_SIG, 21, 1, 2, 726, 0 },

  { 364,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_jw), BLOCKIO_SIG, 35, 2, 2, 728,
    0 },

  { 365,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product3",
    0, "", offsetof(BlockIO_LgV2, Product3_k), BLOCKIO_SIG, 22, 4, 2, 730, 0 },

  { 366,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product4",
    0, "", offsetof(BlockIO_LgV2, Product4_b), BLOCKIO_SIG, 22, 4, 2, 732, 0 },

  { 367,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2",
    0, "", offsetof(BlockIO_LgV2, u_c), BLOCKIO_SIG, 22, 4, 2, 734, 0 },

  { 368,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Delta^2",
    0, "", offsetof(BlockIO_LgV2, Delta2_p), BLOCKIO_SIG, 0, 1, 2, 736, 0 },

  { 369,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_n2_f), BLOCKIO_SIG, 21, 1, 2, 738, 0 },

  { 370,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_gr), BLOCKIO_SIG, 21, 1, 2, 740, 0 },

  { 371,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/( )^2",
    0, "", offsetof(BlockIO_LgV2, u_e), BLOCKIO_SIG, 21, 1, 2, 742, 0 },

  { 372,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_o), BLOCKIO_SIG, 22, 4, 2, 744, 0 },

  { 373,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_ej), BLOCKIO_SIG, 22, 4, 2, 746, 0 },

  { 374,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide1",
    0, "", offsetof(BlockIO_LgV2, Divide1), BLOCKIO_SIG, 22, 4, 2, 748, 0 },

  { 375,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_di2), BLOCKIO_SIG, 22, 4, 2, 750, 0 },

  { 376,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/psi_los^q^2T/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_g), BLOCKIO_SIG, 22, 4, 2, 752, 0
  },

  { 377,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_nz), BLOCKIO_SIG, 20, 2, 2, 754, 0 },

  { 378,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_my), BLOCKIO_SIG, 20, 2, 2, 756, 0 },

  { 379, "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_mg), BLOCKIO_SIG, 20, 2, 2, 758, 0 },

  { 380,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_LgV2, MatrixConcatenate_f), BLOCKIO_SIG, 25, 6, 2,
    760, 0 },

  { 381,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_k3), BLOCKIO_SIG, 20, 2, 2, 762, 0 },

  { 382,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2",
    0, "", offsetof(BlockIO_LgV2, u_i), BLOCKIO_SIG, 20, 2, 2, 764, 0 },

  { 383,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Delta^2",
    0, "", offsetof(BlockIO_LgV2, Delta2_o), BLOCKIO_SIG, 0, 1, 2, 766, 0 },

  { 384,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/epsilon_n^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_n2_a), BLOCKIO_SIG, 21, 1, 2, 768, 0 },

  { 385,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_e2), BLOCKIO_SIG, 21, 1, 2, 770, 0 },

  { 386,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/( )^2",
    0, "", offsetof(BlockIO_LgV2, u_l), BLOCKIO_SIG, 21, 1, 2, 772, 0 },

  { 387,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_d), BLOCKIO_SIG, 20, 2, 2, 774, 0 },

  { 388,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_d), BLOCKIO_SIG, 22, 4, 2, 776, 0 },

  { 389,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector3",
    0, "", offsetof(BlockIO_LgV2, MultiportSelector3), BLOCKIO_SIG, 20, 2, 2,
    778, 0 },

  { 390,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_di), BLOCKIO_SIG, 20, 2, 2, 780, 0 },

  { 391,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide1",
    0, "", offsetof(BlockIO_LgV2, Divide1_b), BLOCKIO_SIG, 20, 2, 2, 782, 0 },

  { 392,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_m), BLOCKIO_SIG, 20, 2, 2, 784, 0 },

  { 393,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_i3), BLOCKIO_SIG, 20, 2, 2, 786, 0 },

  { 394,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_f), BLOCKIO_SIG, 20, 2, 2, 788, 0 },

  { 395,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_n2_l), BLOCKIO_SIG, 21, 1, 2, 790, 0 },

  { 396,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Delta^2",
    0, "", offsetof(BlockIO_LgV2, Delta2_g), BLOCKIO_SIG, 0, 1, 2, 792, 0 },

  { 397,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_g3), BLOCKIO_SIG, 21, 1, 2, 794, 0 },

  { 398,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/^3//2",
    0, "", offsetof(BlockIO_LgV2, u2), BLOCKIO_SIG, 21, 1, 2, 796, 0 },

  { 399,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_l), BLOCKIO_SIG, 20, 2, 2, 798, 0 },

  { 400,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_ly), BLOCKIO_SIG, 20, 2, 2, 800, 0 },

  { 401,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_a), BLOCKIO_SIG, 20, 2, 2, 802, 0
  },

  { 402,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_i), BLOCKIO_SIG, 20, 2, 2, 804, 0 },

  { 403,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_az), BLOCKIO_SIG, 20, 2, 2, 806, 0 },

  { 404,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_o), BLOCKIO_SIG, 20, 2, 2, 808, 0 },

  { 405,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_n), BLOCKIO_SIG, 20, 2, 2, 810, 0 },

  { 406,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_oc), BLOCKIO_SIG, 20, 2, 2, 812, 0 },

  { 407, "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_j), BLOCKIO_SIG, 20, 2, 2, 814, 0 },

  { 408,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_LgV2, MatrixConcatenate_k), BLOCKIO_SIG, 25, 6, 2,
    816, 0 },

  { 409, "lgv2/Control Systems/LgV design 2/alpha^q/Add2", 0, "", offsetof
    (BlockIO_LgV2, Add2_d), BLOCKIO_SIG, 25, 6, 2, 818, 0 },

  { 410, "lgv2/Control Systems/LgV design 2/alpha^q/Product4", 0, "", offsetof
    (BlockIO_LgV2, Product4_g), BLOCKIO_SIG, 25, 6, 2, 820, 0 },

  { 411, "lgv2/Control Systems/LgV design 2/alpha^q/Add3", 0, "", offsetof
    (BlockIO_LgV2, Add3_m), BLOCKIO_SIG, 25, 6, 2, 822, 0 },

  { 412, "lgv2/Control Systems/LgV design 2/Update laws/Integrator2", 0, "",
    offsetof(BlockIO_LgV2, Integrator2), BLOCKIO_SIG, 35, 2, 2, 824, 0 },

  { 413, "lgv2/Control Systems/LgV design 2/Control law/Add2", 0, "", offsetof
    (BlockIO_LgV2, Add2_m), BLOCKIO_SIG, 35, 2, 2, 826, 0 },

  { 414, "lgv2/Control Systems/LgV design 2/Control law/Product5", 0, "",
    offsetof(BlockIO_LgV2, Product5), BLOCKIO_SIG, 26, 3, 2, 828, 0 },

  { 415, "lgv2/Control Systems/LgV design 2/alpha^s/Product1", 0, "", offsetof
    (BlockIO_LgV2, Product1_b), BLOCKIO_SIG, 36, 9, 2, 830, 0 },

  { 416, "lgv2/Control Systems/LgV design 2/alpha^s/Add1", 0, "", offsetof
    (BlockIO_LgV2, Add1_o3), BLOCKIO_SIG, 36, 9, 2, 832, 0 },

  { 417,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/Vector Concatenate1",
    0, "", offsetof(BlockIO_LgV2, VectorConcatenate1), BLOCKIO_SIG, 26, 3, 2,
    834, 0 },

  { 418, "lgv2/Control Systems/LgV design 2/alpha^s/Product3", 0, "", offsetof
    (BlockIO_LgV2, Product3_d), BLOCKIO_SIG, 26, 3, 2, 836, 0 },

  { 419,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_LgV2, TrigonometricFunction1_i), BLOCKIO_SIG, 21, 1,
    2, 838, 0 },

  { 420,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_f), BLOCKIO_SIG, 21, 1, 2, 840, 0 },

  { 421,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_jn), BLOCKIO_SIG, 21, 1, 2, 842, 0 },

  { 422,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function",
    0, "", offsetof(BlockIO_LgV2, TrigonometricFunction_i), BLOCKIO_SIG, 21, 1,
    2, 844, 0 },

  { 423,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2_n), BLOCKIO_SIG, 21, 1, 2, 846, 0 },

  { 424,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_nxy), BLOCKIO_SIG, 23, 2, 2, 848, 0 },

  { 425,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^s eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_in), BLOCKIO_SIG, 0, 1, 2, 850, 0 },

  { 426,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^s eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_nf), BLOCKIO_SIG, 0, 1, 2, 852, 0 },

  { 427,
    "lgv2/Control Systems/LgV design 2/Auxilary functions g_q/g_q^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_LgV2, VectorConcatenate_f), BLOCKIO_SIG, 24, 3, 2,
    854, 0 },

  { 428,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Product",
    0, "", offsetof(BlockIO_LgV2, Product_h), BLOCKIO_SIG, 23, 2, 2, 856, 0 },

  { 429,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2_f), BLOCKIO_SIG, 0, 1, 2, 858, 0 },

  { 430,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/cos(s)",
    0, "", offsetof(BlockIO_LgV2, coss_g), BLOCKIO_SIG, 0, 1, 2, 860, 0 },

  { 431,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_b4), BLOCKIO_SIG, 0, 1, 2, 862, 0
  },

  { 432,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_mj), BLOCKIO_SIG, 0, 1, 2, 864, 0 },

  { 433,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain", 0,
    "", offsetof(BlockIO_LgV2, Gain_hu), BLOCKIO_SIG, 0, 1, 2, 866, 0 },

  { 434,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/sin(s)",
    0, "", offsetof(BlockIO_LgV2, sins_f), BLOCKIO_SIG, 0, 1, 2, 868, 0 },

  { 435,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_ok), BLOCKIO_SIG, 0, 1, 2, 870, 0 },

  { 436,
    "lgv2/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain1", 0,
    "", offsetof(BlockIO_LgV2, Gain1_o2), BLOCKIO_SIG, 0, 1, 2, 872, 0 },

  { 437,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_en), BLOCKIO_SIG, 0, 1, 2, 874, 0 },

  { 438,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_l), BLOCKIO_SIG, 23, 2, 2, 876, 0 },

  { 439,
    "lgv2/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Add",
    0, "", offsetof(BlockIO_LgV2, Add_b), BLOCKIO_SIG, 23, 2, 2, 878, 0 },

  { 440,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/x_d^s + y_d^s^3",
    0, "", offsetof(BlockIO_LgV2, x_dsy_ds3), BLOCKIO_SIG, 0, 1, 2, 880, 0 },

  { 441,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/x_d^s^3 + y_d^s",
    0, "", offsetof(BlockIO_LgV2, x_ds3y_ds), BLOCKIO_SIG, 0, 1, 2, 882, 0 },

  { 442,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/( x_d^s + y_d^s^3  ) - ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_LgV2, x_dsy_ds3x_ds3y_ds), BLOCKIO_SIG, 0, 1, 2, 884,
    0 },

  { 443, "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Product1", 0,
    "", offsetof(BlockIO_LgV2, Product1_a3), BLOCKIO_SIG, 0, 1, 2, 886, 0 },

  { 444,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/x_d^s + x_d^s^2",
    0, "", offsetof(BlockIO_LgV2, x_dsx_ds2), BLOCKIO_SIG, 0, 1, 2, 888, 0 },

  { 445,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/y_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_LgV2, y_dsy_ds2), BLOCKIO_SIG, 0, 1, 2, 890, 0 },

  { 446,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/( x_d^s + x_d^s^2 ) + ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_LgV2, x_dsx_ds2x_ds3y_ds), BLOCKIO_SIG, 0, 1, 2, 892,
    0 },

  { 447, "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/+ 2", 0, "",
    offsetof(BlockIO_LgV2, u_m), BLOCKIO_SIG, 0, 1, 2, 894, 0 },

  { 448, "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Product2", 0,
    "", offsetof(BlockIO_LgV2, Product2_i5), BLOCKIO_SIG, 0, 1, 2, 896, 0 },

  { 449, "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Subtract", 0,
    "", offsetof(BlockIO_LgV2, Subtract_n), BLOCKIO_SIG, 0, 1, 2, 898, 0 },

  { 450,
    "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2",
    0, "", offsetof(BlockIO_LgV2, x_ds2y_ds22), BLOCKIO_SIG, 0, 1, 2, 900, 0 },

  { 451, "lgv2/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Divide", 0,
    "", offsetof(BlockIO_LgV2, Divide_kj), BLOCKIO_SIG, 0, 1, 2, 902, 0 },

  { 452,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/(epsilon_n^s)^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_ns2), BLOCKIO_SIG, 21, 1, 2, 904, 0 },

  { 453,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_j), BLOCKIO_SIG, 21, 1, 2, 906, 0 },

  { 454,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2",
    0, "", offsetof(BlockIO_LgV2, u_d), BLOCKIO_SIG, 21, 1, 2, 908, 0 },

  { 455,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Delta^2",
    0, "", offsetof(BlockIO_LgV2, Delta2_oj), BLOCKIO_SIG, 0, 1, 2, 910, 0 },

  { 456,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_n2_b), BLOCKIO_SIG, 21, 1, 2, 912, 0 },

  { 457,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_k), BLOCKIO_SIG, 21, 1, 2, 914, 0 },

  { 458,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/( )^2",
    0, "", offsetof(BlockIO_LgV2, u_p), BLOCKIO_SIG, 21, 1, 2, 916, 0 },

  { 459,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_p), BLOCKIO_SIG, 21, 1, 2, 918, 0 },

  { 460,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_m), BLOCKIO_SIG, 22, 4, 2, 920, 0
  },

  { 461,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_f), BLOCKIO_SIG, 22, 4, 2, 922, 0 },

  { 462,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_i), BLOCKIO_SIG, 22, 4, 2, 924, 0 },

  { 463,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_co), BLOCKIO_SIG, 23, 2, 2, 926, 0 },

  { 464,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2_px), BLOCKIO_SIG, 23, 2, 2, 928, 0 },

  { 465,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2",
    0, "", offsetof(BlockIO_LgV2, u_mr), BLOCKIO_SIG, 23, 2, 2, 930, 0 },

  { 466,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product3",
    0, "", offsetof(BlockIO_LgV2, Product3_c), BLOCKIO_SIG, 23, 2, 2, 932, 0 },

  { 467,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_pn), BLOCKIO_SIG, 23, 2, 2, 934, 0 },

  { 468,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_dg), BLOCKIO_SIG, 23, 2, 2, 936, 0 },

  { 469,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector4",
    0, "", offsetof(BlockIO_LgV2, MultiportSelector4), BLOCKIO_SIG, 21, 1, 2,
    938, 0 },

  { 470,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_ns), BLOCKIO_SIG, 21, 1, 2, 940, 0 },

  { 471,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide1",
    0, "", offsetof(BlockIO_LgV2, Divide1_p), BLOCKIO_SIG, 21, 1, 2, 942, 0 },

  { 472,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_f), BLOCKIO_SIG, 21, 1, 2, 944, 0 },

  { 473,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_cc), BLOCKIO_SIG, 21, 1, 2, 946, 0 },

  { 474,
    "lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_lq), BLOCKIO_SIG, 20, 2, 2, 948,
    0 },

  { 475,
    "lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Product1", 0,
    "", offsetof(BlockIO_LgV2, Product1_jd), BLOCKIO_SIG, 0, 1, 2, 950, 0 },

  { 476,
    "lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/|p_d^s|^3", 0,
    "", offsetof(BlockIO_LgV2, p_ds3), BLOCKIO_SIG, 0, 1, 2, 952, 0 },

  { 477, "lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_iy), BLOCKIO_SIG, 0, 1, 2, 954, 0 },

  { 478, "lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_bn), BLOCKIO_SIG, 0, 1, 2, 956, 0 },

  { 479, "lgv2/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Gain", 0,
    "", offsetof(BlockIO_LgV2, Gain_e), BLOCKIO_SIG, 0, 1, 2, 958, 0 },

  { 480,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_LgV2, epsilon_n2_cs), BLOCKIO_SIG, 21, 1, 2, 960, 0
  },

  { 481,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Delta^2",
    0, "", offsetof(BlockIO_LgV2, Delta2_i), BLOCKIO_SIG, 0, 1, 2, 962, 0 },

  { 482,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Add",
    0, "", offsetof(BlockIO_LgV2, Add_es), BLOCKIO_SIG, 21, 1, 2, 964, 0 },

  { 483,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_jo), BLOCKIO_SIG, 21, 1, 2, 966,
    0 },

  { 484,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide",
    0, "", offsetof(BlockIO_LgV2, Divide_j), BLOCKIO_SIG, 21, 1, 2, 968, 0 },

  { 485,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_es), BLOCKIO_SIG, 21, 1, 2, 970, 0 },

  { 486,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2_h), BLOCKIO_SIG, 21, 1, 2, 972, 0 },

  { 487,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/^3//2",
    0, "", offsetof(BlockIO_LgV2, u2_b), BLOCKIO_SIG, 21, 1, 2, 974, 0 },

  { 488,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide1",
    0, "", offsetof(BlockIO_LgV2, Divide1_d), BLOCKIO_SIG, 21, 1, 2, 976, 0 },

  { 489,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product3",
    0, "", offsetof(BlockIO_LgV2, Product3_a), BLOCKIO_SIG, 21, 1, 2, 978, 0 },

  { 490,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_en), BLOCKIO_SIG, 0, 1, 2, 980, 0 },

  { 491,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_c), BLOCKIO_SIG, 20, 2, 2, 982, 0
  },

  { 492,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide2",
    0, "", offsetof(BlockIO_LgV2, Divide2), BLOCKIO_SIG, 20, 2, 2, 984, 0 },

  { 493,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_cc), BLOCKIO_SIG, 20, 2, 2, 986,
    0 },

  { 494,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product2",
    0, "", offsetof(BlockIO_LgV2, Product2_im), BLOCKIO_SIG, 20, 2, 2, 988, 0 },

  { 495,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_ak), BLOCKIO_SIG, 0, 1, 2, 990, 0
  },

  { 496,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide1",
    0, "", offsetof(BlockIO_LgV2, Divide1_be), BLOCKIO_SIG, 20, 2, 2, 992, 0 },

  { 497,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract1",
    0, "", offsetof(BlockIO_LgV2, Subtract1_c), BLOCKIO_SIG, 20, 2, 2, 994, 0 },

  { 498,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product",
    0, "", offsetof(BlockIO_LgV2, Product_of), BLOCKIO_SIG, 0, 1, 2, 996, 0 },

  { 499,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract",
    0, "", offsetof(BlockIO_LgV2, Subtract_nq), BLOCKIO_SIG, 0, 1, 2, 998, 0 },

  { 500,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_oq), BLOCKIO_SIG, 21, 1, 2, 1000, 0 },

  { 501,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/Product1",
    0, "", offsetof(BlockIO_LgV2, Product1_o2), BLOCKIO_SIG, 21, 1, 2, 1002, 0 },

  { 502,
    "lgv2/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_LgV2, VectorConcatenate_p), BLOCKIO_SIG, 26, 3, 2,
    1004, 0 },

  { 503, "lgv2/Control Systems/LgV design 2/alpha^s/Add2", 0, "", offsetof
    (BlockIO_LgV2, Add2_e), BLOCKIO_SIG, 26, 3, 2, 1006, 0 },

  { 504, "lgv2/Control Systems/LgV design 2/alpha^s/Product4", 0, "", offsetof
    (BlockIO_LgV2, Product4_a), BLOCKIO_SIG, 26, 3, 2, 1008, 0 },

  { 505, "lgv2/Control Systems/LgV design 2/alpha^s/Add3", 0, "", offsetof
    (BlockIO_LgV2, Add3_l), BLOCKIO_SIG, 26, 3, 2, 1010, 0 },

  { 506, "lgv2/Control Systems/LgV design 2/Control law/Product6", 0, "",
    offsetof(BlockIO_LgV2, Product6), BLOCKIO_SIG, 26, 3, 2, 1012, 0 },

  { 507, "lgv2/Control Systems/LgV design 2/Control law/Sum", 0, "", offsetof
    (BlockIO_LgV2, Sum_gc), BLOCKIO_SIG, 26, 3, 2, 1014, 0 },

  { 508,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_LgV2, Product_cl), BLOCKIO_SIG, 37, 5, 2, 1016, 0 },

  { 509,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone_h), BLOCKIO_SIG, 21, 1, 2, 1018, 0 },

  { 510,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_LgV2, f_10_c), BLOCKIO_SIG, 21, 1, 2, 1020, 0 },

  { 511,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_LgV2, f_10_i), BLOCKIO_SIG, 21, 1, 2, 1022, 0 },

  { 512,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch_j), BLOCKIO_SIG, 21, 1, 2,
    1024, 0 },

  { 513,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone_g1), BLOCKIO_SIG, 21, 1, 2, 1026, 0 },

  { 514,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_LgV2, f_20_o), BLOCKIO_SIG, 21, 1, 2, 1028, 0 },

  { 515,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_LgV2, f_20_c), BLOCKIO_SIG, 21, 1, 2, 1030, 0 },

  { 516,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch_m), BLOCKIO_SIG, 21, 1, 2,
    1032, 0 },

  { 517,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone_f2), BLOCKIO_SIG, 21, 1, 2, 1034, 0 },

  { 518,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_LgV2, f_30_f), BLOCKIO_SIG, 21, 1, 2, 1036, 0 },

  { 519,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_LgV2, f_30_e), BLOCKIO_SIG, 21, 1, 2, 1038, 0 },

  { 520,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch_g), BLOCKIO_SIG, 21, 1, 2,
    1040, 0 },

  { 521,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone_fm), BLOCKIO_SIG, 21, 1, 2, 1042, 0 },

  { 522,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_LgV2, f_40_l), BLOCKIO_SIG, 21, 1, 2, 1044, 0 },

  { 523,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_LgV2, f_40_o), BLOCKIO_SIG, 21, 1, 2, 1046, 0 },

  { 524,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch_i), BLOCKIO_SIG, 21, 1, 2,
    1048, 0 },

  { 525,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone",
    0, "", offsetof(BlockIO_LgV2, DeadZone_jb), BLOCKIO_SIG, 21, 1, 2, 1050, 0 },

  { 526,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_LgV2, f_50_b), BLOCKIO_SIG, 21, 1, 2, 1052, 0 },

  { 527,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_LgV2, f_50_k), BLOCKIO_SIG, 21, 1, 2, 1054, 0 },

  { 528,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_LgV2, MultiportSwitch_o), BLOCKIO_SIG, 21, 1, 2,
    1056, 0 },

  { 529, "lgv2/Control Systems/Thruster setting Switch", 0, "", offsetof
    (BlockIO_LgV2, ThrustersettingSwitch), BLOCKIO_SIG, 27, 7, 2, 1058, 0 },

  { 530, "lgv2/Control Systems/Saturation", 0, "", offsetof(BlockIO_LgV2,
    Saturation_e), BLOCKIO_SIG, 27, 7, 2, 1060, 0 },

  { 531,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1",
    0, "", offsetof(BlockIO_LgV2, l_x1_e), BLOCKIO_SIG, 0, 1, 2, 1062, 0 },

  { 532,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2",
    0, "", offsetof(BlockIO_LgV2, l_y2_g), BLOCKIO_SIG, 0, 1, 2, 1064, 0 },

  { 533,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2",
    0, "", offsetof(BlockIO_LgV2, l_x2_h), BLOCKIO_SIG, 0, 1, 2, 1066, 0 },

  { 534,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/3x5", 0,
    "", offsetof(BlockIO_LgV2, x5_f), BLOCKIO_SIG, 31, 15, 2, 1068, 0 },

  { 535,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1",
    0, "", offsetof(BlockIO_LgV2, u_1tof_1), BLOCKIO_SIG, 0, 1, 2, 1070, 0 },

  { 536,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2",
    0, "", offsetof(BlockIO_LgV2, u_2tof_2), BLOCKIO_SIG, 0, 1, 2, 1072, 0 },

  { 537,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3",
    0, "", offsetof(BlockIO_LgV2, u_3tof_3), BLOCKIO_SIG, 0, 1, 2, 1074, 0 },

  { 538,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4",
    0, "", offsetof(BlockIO_LgV2, u_4tof_4), BLOCKIO_SIG, 0, 1, 2, 1076, 0 },

  { 539,
    "lgv2/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5",
    0, "", offsetof(BlockIO_LgV2, u_5tof_5), BLOCKIO_SIG, 0, 1, 2, 1078, 0 },

  { 540,
    "lgv2/Control Systems/PS3 u input control/Subsystem/f_act to tau/Product", 0,
    "", offsetof(BlockIO_LgV2, Product_cb), BLOCKIO_SIG, 24, 3, 2, 1080, 0 },

  { 541, "lgv2/Control Systems/tau Switch", 0, "", offsetof(BlockIO_LgV2,
    tauSwitch), BLOCKIO_SIG, 26, 3, 2, 1082, 0 },

  { 542, "lgv2/Control Systems/LgV design 2/Gamma_q/2x2", 0, "", offsetof
    (BlockIO_LgV2, x2), BLOCKIO_SIG, 22, 4, 2, 1084, 0 },

  { 543, "lgv2/Control Systems/LgV design 2/Integral action state/Product", 0,
    "", offsetof(BlockIO_LgV2, Product_ff), BLOCKIO_SIG, 26, 3, 2, 1086, 0 },

  { 544, "lgv2/Control Systems/LgV design 2/Update laws/Add", 0, "", offsetof
    (BlockIO_LgV2, Add_h), BLOCKIO_SIG, 35, 2, 2, 1088, 0 },

  { 545, "lgv2/Control Systems/LgV design 2/V_1^q/Transpose/Math Function", 0,
    "", offsetof(BlockIO_LgV2, MathFunction_gg), BLOCKIO_SIG, 40, 3, 2, 1090, 0
  },

  { 546, "lgv2/Control Systems/LgV design 2/V_1^q/Product", 0, "", offsetof
    (BlockIO_LgV2, Product_cu), BLOCKIO_SIG, 20, 2, 2, 1092, 0 },

  { 547, "lgv2/Control Systems/LgV design 2/V_1^q/Gain", 0, "", offsetof
    (BlockIO_LgV2, Gain_f3), BLOCKIO_SIG, 20, 2, 2, 1094, 0 },

  { 548, "lgv2/Control Systems/LgV design 2/Update laws/Transpose/Math Function",
    0, "", offsetof(BlockIO_LgV2, MathFunction_g1), BLOCKIO_SIG, 35, 2, 2, 1096,
    0 },

  { 549, "lgv2/Control Systems/LgV design 2/Update laws/Product", 0, "",
    offsetof(BlockIO_LgV2, Product_if), BLOCKIO_SIG, 35, 2, 2, 1098, 0 },

  { 550, "lgv2/Control Systems/LgV design 2/Update laws/Add1", 0, "", offsetof
    (BlockIO_LgV2, Add1_c), BLOCKIO_SIG, 35, 2, 2, 1100, 0 },

  { 551, "lgv2/Control Systems/LgV design 2/Update laws/Product1", 0, "",
    offsetof(BlockIO_LgV2, Product1_f5), BLOCKIO_SIG, 35, 2, 2, 1102, 0 },

  { 552, "lgv2/Control Systems/LgV design 2/Update laws/Gain", 0, "", offsetof
    (BlockIO_LgV2, Gain_kii), BLOCKIO_SIG, 35, 2, 2, 1104, 0 },

  { 553, "lgv2/HMI/SIT zAI0", 0, "", offsetof(BlockIO_LgV2, SITzAI0),
    BLOCKIO_SIG, 0, 1, 2, 1106, 0 },

  { 554, "lgv2/HMI/Battery Bow Thruster", 0, "", offsetof(BlockIO_LgV2,
    BatteryBowThruster), BLOCKIO_SIG, 0, 1, 2, 1108, 0 },

  { 555, "lgv2/HMI/SIT zAI1", 0, "", offsetof(BlockIO_LgV2, SITzAI1),
    BLOCKIO_SIG, 0, 1, 2, 1110, 0 },

  { 556, "lgv2/HMI/Battery Servo", 0, "", offsetof(BlockIO_LgV2, BatteryServo),
    BLOCKIO_SIG, 0, 1, 2, 1112, 0 },

  { 557, "lgv2/HMI/SIT zAI2", 0, "", offsetof(BlockIO_LgV2, SITzAI2),
    BLOCKIO_SIG, 0, 1, 2, 1114, 0 },

  { 558, "lgv2/HMI/Battery Main", 0, "", offsetof(BlockIO_LgV2, BatteryMain),
    BLOCKIO_SIG, 0, 1, 2, 1116, 0 },

  { 559, "lgv2/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS", 0, "", offsetof
    (BlockIO_LgV2, QTMIn1FPS), BLOCKIO_SIG, 21, 1, 2, 1118, 0 },

  { 560, "lgv2/Plants/saturation/Saturation", 0, "", offsetof(BlockIO_LgV2,
    Saturation_dq), BLOCKIO_SIG, 21, 1, 2, 1120, 0 },

  { 561, "lgv2/Plants/saturation/Saturation1", 0, "", offsetof(BlockIO_LgV2,
    Saturation1), BLOCKIO_SIG, 21, 1, 2, 1122, 0 },

  { 562, "lgv2/Plants/saturation/Saturation2", 0, "", offsetof(BlockIO_LgV2,
    Saturation2), BLOCKIO_SIG, 21, 1, 2, 1124, 0 },

  { 563, "lgv2/Plants/saturation/plant tau_surge", 0, "", offsetof(BlockIO_LgV2,
    planttau_surge), BLOCKIO_SIG, 21, 1, 2, 1126, 0 },

  { 564, "lgv2/Plants/saturation/plant tau_sway", 0, "", offsetof(BlockIO_LgV2,
    planttau_sway), BLOCKIO_SIG, 21, 1, 2, 1128, 0 },

  { 565, "lgv2/Plants/saturation/plant tau_yaw", 0, "", offsetof(BlockIO_LgV2,
    planttau_yaw), BLOCKIO_SIG, 21, 1, 2, 1130, 0 },

  { 566, "lgv2/Plants/plant u_1", 0, "", offsetof(BlockIO_LgV2, plantu_1),
    BLOCKIO_SIG, 0, 1, 2, 1132, 0 },

  { 567, "lgv2/Plants/plant u_2", 0, "", offsetof(BlockIO_LgV2, plantu_2),
    BLOCKIO_SIG, 0, 1, 2, 1134, 0 },

  { 568, "lgv2/Plants/plant u_3", 0, "", offsetof(BlockIO_LgV2, plantu_3),
    BLOCKIO_SIG, 0, 1, 2, 1136, 0 },

  { 569, "lgv2/Plants/plant u_4", 0, "", offsetof(BlockIO_LgV2, plantu_4),
    BLOCKIO_SIG, 0, 1, 2, 1138, 0 },

  { 570, "lgv2/Plants/plant u_5", 0, "", offsetof(BlockIO_LgV2, plantu_5),
    BLOCKIO_SIG, 0, 1, 2, 1140, 0 },

  { 571, "lgv2/Plants/plant BT power", 0, "", offsetof(BlockIO_LgV2,
    plantBTpower), BLOCKIO_SIG, 0, 1, 2, 1142, 0 },

  { 572, "lgv2/Plants/plant VSP speed", 0, "", offsetof(BlockIO_LgV2,
    plantVSPspeed), BLOCKIO_SIG, 0, 1, 2, 1144, 0 },

  { 573, "lgv2/eta_psi", 0, "", offsetof(BlockIO_LgV2, eta_psi), BLOCKIO_SIG, 0,
    1, 2, 1146, 0 },

  { 574, "lgv2/eta_psid", 0, "", offsetof(BlockIO_LgV2, eta_psid), BLOCKIO_SIG,
    0, 1, 2, 1148, 0 },

  { 575, "lgv2/eta_x", 0, "", offsetof(BlockIO_LgV2, eta_x), BLOCKIO_SIG, 0, 1,
    2, 1150, 0 },

  { 576, "lgv2/eta_xd", 0, "", offsetof(BlockIO_LgV2, eta_xd), BLOCKIO_SIG, 0, 1,
    2, 1152, 0 },

  { 577, "lgv2/eta_y", 0, "", offsetof(BlockIO_LgV2, eta_y), BLOCKIO_SIG, 0, 1,
    2, 1154, 0 },

  { 578, "lgv2/eta_yd", 0, "", offsetof(BlockIO_LgV2, eta_yd), BLOCKIO_SIG, 0, 1,
    2, 1156, 0 },

  { 579, "lgv2/psi_los", 0, "", offsetof(BlockIO_LgV2, psi_los_k), BLOCKIO_SIG,
    0, 1, 2, 1158, 0 },

  { 580, "lgv2/psi_plot", 0, "", offsetof(BlockIO_LgV2, psi_plot), BLOCKIO_SIG,
    24, 3, 2, 1160, 0 },

  { 581, "lgv2/q_x", 0, "", offsetof(BlockIO_LgV2, q_x_e), BLOCKIO_SIG, 0, 1, 2,
    1162, 0 },

  { 582, "lgv2/q_y", 0, "", offsetof(BlockIO_LgV2, q_y_c), BLOCKIO_SIG, 0, 1, 2,
    1164, 0 },

  { 583, "lgv2/x_plot", 0, "", offsetof(BlockIO_LgV2, x_plot), BLOCKIO_SIG, 24,
    3, 2, 1166, 0 },

  { 584, "lgv2/y_plot", 0, "", offsetof(BlockIO_LgV2, y_plot), BLOCKIO_SIG, 24,
    3, 2, 1168, 0 },

  { 585, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r", 0, "",
    offsetof(BlockIO_LgV2, N_r_o), BLOCKIO_SIG, 0, 1, 2, 1170, 0 },

  { 586, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v", 0, "",
    offsetof(BlockIO_LgV2, N_v_h), BLOCKIO_SIG, 0, 1, 2, 1172, 0 },

  { 587, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u", 0, "",
    offsetof(BlockIO_LgV2, X_u_o), BLOCKIO_SIG, 0, 1, 2, 1174, 0 },

  { 588, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v", 0, "",
    offsetof(BlockIO_LgV2, Y_v_g), BLOCKIO_SIG, 0, 1, 2, 1176, 0 },

  { 589, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr", 0, "",
    offsetof(BlockIO_LgV2, Y_vr_g), BLOCKIO_SIG, 0, 1, 2, 1178, 0 },

  { 590,
    "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Linear Dampning matrix",
    0, "", offsetof(BlockIO_LgV2, LinearDampningmatrix_m), BLOCKIO_SIG, 36, 9, 2,
    1180, 0 },

  { 591, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0",
    0, "", offsetof(BlockIO_LgV2, psi_0), BLOCKIO_SIG, 0, 1, 2, 1182, 0 },

  { 592, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0",
    0, "", offsetof(BlockIO_LgV2, x_0), BLOCKIO_SIG, 0, 1, 2, 1184, 0 },

  { 593, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0",
    0, "", offsetof(BlockIO_LgV2, y_0), BLOCKIO_SIG, 0, 1, 2, 1186, 0 },

  { 594, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0", 0,
    "", offsetof(BlockIO_LgV2, r_0), BLOCKIO_SIG, 0, 1, 2, 1188, 0 },

  { 595, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0", 0,
    "", offsetof(BlockIO_LgV2, u_0), BLOCKIO_SIG, 0, 1, 2, 1190, 0 },

  { 596, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0", 0,
    "", offsetof(BlockIO_LgV2, v_0), BLOCKIO_SIG, 0, 1, 2, 1192, 0 },

  { 597, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Integrator", 0, "",
    offsetof(BlockIO_LgV2, Integrator_p), BLOCKIO_SIG, 24, 3, 2, 1194, 0 },

  { 598, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Integrator1", 0,
    "", offsetof(BlockIO_LgV2, Integrator1_f), BLOCKIO_SIG, 24, 3, 2, 1196, 0 },

  { 599, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_11", 0, "",
    offsetof(BlockIO_LgV2, M_11_f), BLOCKIO_SIG, 0, 1, 2, 1198, 0 },

  { 600, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_22", 0, "",
    offsetof(BlockIO_LgV2, M_22_c), BLOCKIO_SIG, 0, 1, 2, 1200, 0 },

  { 601, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m x_g", 0,
    "", offsetof(BlockIO_LgV2, mx_g_e), BLOCKIO_SIG, 0, 1, 2, 1202, 0 },

  { 602, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_32", 0, "",
    offsetof(BlockIO_LgV2, M_32_n), BLOCKIO_SIG, 0, 1, 2, 1204, 0 },

  { 603, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_23", 0, "",
    offsetof(BlockIO_LgV2, M_23_l), BLOCKIO_SIG, 0, 1, 2, 1206, 0 },

  { 604, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_33", 0, "",
    offsetof(BlockIO_LgV2, M_33_p), BLOCKIO_SIG, 0, 1, 2, 1208, 0 },

  { 605, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M", 0, "",
    offsetof(BlockIO_LgV2, M), BLOCKIO_SIG, 36, 9, 2, 1210, 0 },

  { 606, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Inverse", 0,
    "", offsetof(BlockIO_LgV2, Inverse), BLOCKIO_SIG, 36, 9, 2, 1212, 0 },

  { 607, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Product1", 0, "",
    offsetof(BlockIO_LgV2, Product1_ob), BLOCKIO_SIG, 24, 3, 2, 1214, 0 },

  { 608, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R11", 0, "",
    offsetof(BlockIO_LgV2, R11_n), BLOCKIO_SIG, 0, 1, 2, 1216, 0 },

  { 609, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R21", 0, "",
    offsetof(BlockIO_LgV2, R21_m4), BLOCKIO_SIG, 0, 1, 2, 1218, 0 },

  { 610, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R12", 0, "",
    offsetof(BlockIO_LgV2, R12_l), BLOCKIO_SIG, 0, 1, 2, 1220, 0 },

  { 611, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R22", 0, "",
    offsetof(BlockIO_LgV2, R22_pu), BLOCKIO_SIG, 0, 1, 2, 1222, 0 },

  { 612, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R(psi)", 0,
    "", offsetof(BlockIO_LgV2, Rpsi_o), BLOCKIO_SIG, 36, 9, 2, 1224, 0 },

  { 613, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Product3", 0, "",
    offsetof(BlockIO_LgV2, Product3_f), BLOCKIO_SIG, 24, 3, 2, 1226, 0 },

  { 614, "lgv2/Plants/Linear Simulator/eta_surge_hil", 0, "", offsetof
    (BlockIO_LgV2, eta_surge_hil), BLOCKIO_SIG, 0, 1, 2, 1228, 0 },

  { 615, "lgv2/Plants/Linear Simulator/eta_sway_hil", 0, "", offsetof
    (BlockIO_LgV2, eta_sway_hil), BLOCKIO_SIG, 0, 1, 2, 1230, 0 },

  { 616, "lgv2/Plants/Linear Simulator/eta_yaw_hil", 0, "", offsetof
    (BlockIO_LgV2, eta_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 1232, 0 },

  { 617, "lgv2/Plants/Linear Simulator/etadot_surge_hil", 0, "", offsetof
    (BlockIO_LgV2, etadot_surge_hil), BLOCKIO_SIG, 0, 1, 2, 1234, 0 },

  { 618, "lgv2/Plants/Linear Simulator/etadot_sway_hil", 0, "", offsetof
    (BlockIO_LgV2, etadot_sway_hil), BLOCKIO_SIG, 0, 1, 2, 1236, 0 },

  { 619, "lgv2/Plants/Linear Simulator/etadot_yaw_hil", 0, "", offsetof
    (BlockIO_LgV2, etadot_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 1238, 0 },

  { 620, "lgv2/Plants/Linear Simulator/nu_surge_hil", 0, "", offsetof
    (BlockIO_LgV2, nu_surge_hil), BLOCKIO_SIG, 0, 1, 2, 1240, 0 },

  { 621, "lgv2/Plants/Linear Simulator/nu_sway_hil", 0, "", offsetof
    (BlockIO_LgV2, nu_sway_hil), BLOCKIO_SIG, 0, 1, 2, 1242, 0 },

  { 622, "lgv2/Plants/Linear Simulator/nu_yaw_hil", 0, "", offsetof(BlockIO_LgV2,
    nu_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 1244, 0 },

  { 623, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Sum", 0, "",
    offsetof(BlockIO_LgV2, Sum_j3), BLOCKIO_SIG, 24, 3, 2, 1246, 0 },

  { 624, "lgv2/Plants/Linear Simulator/Linear Vessel Dynamics/Product2", 0, "",
    offsetof(BlockIO_LgV2, Product2_d), BLOCKIO_SIG, 24, 3, 2, 1248, 0 },

  { 625, "lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain1", 0, "", offsetof
    (BlockIO_LgV2, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2, 1250, 0 },

  { 626, "lgv2/Plants/CSE1/Bow Thruster/BT_D_Gain2", 0, "", offsetof
    (BlockIO_LgV2, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2, 1252, 0 },

  { 627, "lgv2/Plants/CSE1/Bow Thruster/Add", 0, "", offsetof(BlockIO_LgV2,
    Add_ct), BLOCKIO_SIG, 0, 1, 2, 1254, 0 },

  { 628, "lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain1", 0, "", offsetof
    (BlockIO_LgV2, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2, 1256, 0 },

  { 629, "lgv2/Plants/CSE1/Bow Thruster/BT_L_Gain2", 0, "", offsetof
    (BlockIO_LgV2, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2, 1258, 0 },

  { 630, "lgv2/Plants/CSE1/Bow Thruster/Neg", 0, "", offsetof(BlockIO_LgV2, Neg),
    BLOCKIO_SIG, 0, 1, 2, 1260, 0 },

  { 631, "lgv2/Plants/CSE1/Bow Thruster/Sum1", 0, "", offsetof(BlockIO_LgV2,
    Sum1_k), BLOCKIO_SIG, 0, 1, 2, 1262, 0 },

  { 632, "lgv2/Plants/CSE1/Bow Thruster/Sum2", 0, "", offsetof(BlockIO_LgV2,
    Sum2), BLOCKIO_SIG, 0, 1, 2, 1264, 0 },

  { 633, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch", 0, "",
    offsetof(BlockIO_LgV2, Switch_i), BLOCKIO_SIG, 0, 1, 2, 1266, 0 },

  { 634, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch2", 0, "",
    offsetof(BlockIO_LgV2, Switch2_d), BLOCKIO_SIG, 0, 1, 2, 1268, 0 },

  { 635, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch", 0, "",
    offsetof(BlockIO_LgV2, Switch_d), BLOCKIO_SIG, 0, 1, 2, 1270, 0 },

  { 636, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch2", 0, "",
    offsetof(BlockIO_LgV2, Switch2_p), BLOCKIO_SIG, 0, 1, 2, 1272, 0 },

  { 637, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch", 0, "",
    offsetof(BlockIO_LgV2, Switch_d3), BLOCKIO_SIG, 0, 1, 2, 1274, 0 },

  { 638, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch2", 0, "",
    offsetof(BlockIO_LgV2, Switch2_o), BLOCKIO_SIG, 0, 1, 2, 1276, 0 },

  { 639, "lgv2/Plants/CSE1/Voith Schneider Propeller /Sign", 0, "", offsetof
    (BlockIO_LgV2, Sign_o), BLOCKIO_SIG, 0, 1, 2, 1278, 0 },

  { 640, "lgv2/Plants/CSE1/Voith Schneider Propeller /Product1", 0, "Port VPS_X",
    offsetof(BlockIO_LgV2, PortVPS_X), BLOCKIO_SIG, 0, 1, 2, 1280, 0 },

  { 641, "lgv2/Plants/CSE1/Voith Schneider Propeller /-x", 0, "Port VPS_X",
    offsetof(BlockIO_LgV2, PortVPS_X_n), BLOCKIO_SIG, 0, 1, 2, 1282, 0 },

  { 642, "lgv2/Plants/CSE1/Voith Schneider Propeller /Product2", 0, "Port VSP_Y",
    offsetof(BlockIO_LgV2, PortVSP_Y), BLOCKIO_SIG, 0, 1, 2, 1284, 0 },

  { 643, "lgv2/Plants/CSE1/Voith Schneider Propeller /-y", 0, "Port VSP_Y",
    offsetof(BlockIO_LgV2, PortVSP_Y_b), BLOCKIO_SIG, 0, 1, 2, 1286, 0 },

  { 644, "lgv2/Plants/CSE1/Voith Schneider Propeller /Product3", 0,
    "Starboard VSP_X", offsetof(BlockIO_LgV2, StarboardVSP_X), BLOCKIO_SIG, 0, 1,
    2, 1288, 0 },

  { 645, "lgv2/Plants/CSE1/Voith Schneider Propeller /Product4", 0,
    "Starboard VSP_Y", offsetof(BlockIO_LgV2, StarboardVSP_Y), BLOCKIO_SIG, 0, 1,
    2, 1290, 0 },

  { 646, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo1", 0, "", offsetof
    (BlockIO_LgV2, Servo1), BLOCKIO_SIG, 0, 1, 2, 1292, 0 },

  { 647, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo2", 0, "", offsetof
    (BlockIO_LgV2, Servo2), BLOCKIO_SIG, 0, 1, 2, 1294, 0 },

  { 648, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo3", 0, "", offsetof
    (BlockIO_LgV2, Servo3), BLOCKIO_SIG, 0, 1, 2, 1296, 0 },

  { 649, "lgv2/Plants/CSE1/Voith Schneider Propeller /Servo4", 0, "", offsetof
    (BlockIO_LgV2, Servo4), BLOCKIO_SIG, 0, 1, 2, 1298, 0 },

  { 650, "lgv2/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain", 0, "",
    offsetof(BlockIO_LgV2, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2, 1300, 0 },

  { 651, "lgv2/Plants/CSE1/Voith Schneider Propeller /Sum", 0, "", offsetof
    (BlockIO_LgV2, Sum_d3), BLOCKIO_SIG, 0, 1, 2, 1302, 0 },

  { 652, "lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Port", 0, "",
    offsetof(BlockIO_LgV2, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 1304, 0 },

  { 653, "lgv2/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard", 0, "",
    offsetof(BlockIO_LgV2, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2, 1306, 0 },

  { 654,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12",
    0, "", offsetof(BlockIO_LgV2, S12_o), BLOCKIO_SIG, 0, 1, 2, 1308, 0 },

  { 655,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S_2(psi_d^s^2)",
    0, "", offsetof(BlockIO_LgV2, S_2psi_ds2), BLOCKIO_SIG, 22, 4, 2, 1310, 0 },

  { 656,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S12",
    0, "", offsetof(BlockIO_LgV2, S12_c), BLOCKIO_SIG, 0, 1, 2, 1312, 0 },

  { 657,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S_2(psi_d^s)",
    0, "", offsetof(BlockIO_LgV2, S_2psi_ds), BLOCKIO_SIG, 22, 4, 2, 1314, 0 },

  { 658,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R11",
    0, "", offsetof(BlockIO_LgV2, R11_cj), BLOCKIO_SIG, 0, 1, 2, 1316, 0 },

  { 659,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R21",
    0, "", offsetof(BlockIO_LgV2, R21_o), BLOCKIO_SIG, 0, 1, 2, 1318, 0 },

  { 660,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R12",
    0, "", offsetof(BlockIO_LgV2, R12_k), BLOCKIO_SIG, 0, 1, 2, 1320, 0 },

  { 661,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R22",
    0, "", offsetof(BlockIO_LgV2, R22_l), BLOCKIO_SIG, 0, 1, 2, 1322, 0 },

  { 662,
    "lgv2/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R_2(psi_d)",
    0, "", offsetof(BlockIO_LgV2, R_2psi_d), BLOCKIO_SIG, 22, 4, 2, 1324, 0 },

  { 663,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_p), BLOCKIO_SIG, 15, 1, 2, 1326, 0 },

  { 664,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_a), BLOCKIO_SIG, 15, 1, 2, 1328, 0 },

  { 665,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_i), BLOCKIO_SIG, 15, 1, 2, 1330, 0 },

  { 666,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_nw), BLOCKIO_SIG, 15, 1, 2, 1332, 0 },

  { 667,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_hg), BLOCKIO_SIG, 15, 1, 2, 1334, 0 },

  { 668,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_a), BLOCKIO_SIG, 15, 1, 2, 1336, 0 },

  { 669,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_br), BLOCKIO_SIG, 15, 1, 2, 1338, 0 },

  { 670,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_hu), BLOCKIO_SIG, 15, 1, 2, 1340, 0 },

  { 671,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_n5), BLOCKIO_SIG, 15, 1, 2, 1342, 0 },

  { 672,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_c5), BLOCKIO_SIG, 15, 1, 2, 1344, 0 },

  { 673,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_mp), BLOCKIO_SIG, 15, 1, 2, 1346, 0 },

  { 674,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_k), BLOCKIO_SIG, 15, 1, 2, 1348, 0 },

  { 675,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_j1), BLOCKIO_SIG, 15, 1, 2, 1350, 0 },

  { 676,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_cf), BLOCKIO_SIG, 15, 1, 2, 1352, 0 },

  { 677,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_fw), BLOCKIO_SIG, 15, 1, 2, 1354, 0 },

  { 678,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_ji), BLOCKIO_SIG, 39, 1, 2, 1356, 0 },

  { 679,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_ld), BLOCKIO_SIG, 39, 1, 2, 1358, 0 },

  { 680,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_gp), BLOCKIO_SIG, 39, 1, 2, 1360, 0 },

  { 681,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_n4), BLOCKIO_SIG, 39, 1, 2, 1362, 0 },

  { 682,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_aa), BLOCKIO_SIG, 39, 1, 2, 1364, 0 },

  { 683,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_af), BLOCKIO_SIG, 39, 1, 2, 1366, 0 },

  { 684,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_dm), BLOCKIO_SIG, 39, 1, 2, 1368, 0 },

  { 685,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_hl), BLOCKIO_SIG, 39, 1, 2, 1370, 0 },

  { 686,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_fi), BLOCKIO_SIG, 39, 1, 2, 1372, 0 },

  { 687,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_gr), BLOCKIO_SIG, 39, 1, 2, 1374, 0 },

  { 688,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_mc), BLOCKIO_SIG, 39, 1, 2, 1376, 0 },

  { 689,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_mq), BLOCKIO_SIG, 39, 1, 2, 1378, 0 },

  { 690,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_LgV2, Gain_cv), BLOCKIO_SIG, 39, 1, 2, 1380, 0 },

  { 691,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_LgV2, Gain1_e), BLOCKIO_SIG, 39, 1, 2, 1382, 0 },

  { 692,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_LgV2, Sum_ih), BLOCKIO_SIG, 39, 1, 2, 1384, 0 },

  { 693,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare), BLOCKIO_SIG, 3, 1, 2, 1386, 0 },

  { 694,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_e), BLOCKIO_SIG, 3, 1, 2, 1388, 0 },

  { 695,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_j), BLOCKIO_SIG, 3, 1, 2, 1390, 0 },

  { 696,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_a), BLOCKIO_SIG, 3, 1, 2, 1392, 0 },

  { 697,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_n), BLOCKIO_SIG, 3, 1, 2, 1394, 0 },

  { 698,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_m), BLOCKIO_SIG, 3, 1, 2, 1396, 0 },

  { 699,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_p), BLOCKIO_SIG, 3, 1, 2, 1398, 0 },

  { 700,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_c), BLOCKIO_SIG, 3, 1, 2, 1400, 0 },

  { 701,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_i), BLOCKIO_SIG, 3, 1, 2, 1402, 0 },

  { 702,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_o), BLOCKIO_SIG, 3, 1, 2, 1404, 0 },

  { 703,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_ng), BLOCKIO_SIG, 3, 1, 2, 1406, 0 },

  { 704,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_cx), BLOCKIO_SIG, 3, 1, 2, 1408, 0 },

  { 705,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_l), BLOCKIO_SIG, 3, 1, 2, 1410, 0 },

  { 706,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_b), BLOCKIO_SIG, 3, 1, 2, 1412, 0 },

  { 707,
    "lgv2/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_d), BLOCKIO_SIG, 3, 1, 2, 1414, 0 },

  { 708,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_en), BLOCKIO_SIG, 38, 1, 2, 1416, 0 },

  { 709,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_p1), BLOCKIO_SIG, 38, 1, 2, 1418, 0 },

  { 710,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_f), BLOCKIO_SIG, 38, 1, 2, 1420, 0 },

  { 711,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_em), BLOCKIO_SIG, 38, 1, 2, 1422, 0 },

  { 712,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_ib), BLOCKIO_SIG, 38, 1, 2, 1424, 0 },

  { 713,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_lq), BLOCKIO_SIG, 38, 1, 2, 1426, 0 },

  { 714,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_lu), BLOCKIO_SIG, 38, 1, 2, 1428, 0 },

  { 715,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_p0), BLOCKIO_SIG, 38, 1, 2, 1430, 0 },

  { 716,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_ot), BLOCKIO_SIG, 38, 1, 2, 1432, 0 },

  { 717,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_g), BLOCKIO_SIG, 38, 1, 2, 1434, 0 },

  { 718,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_on), BLOCKIO_SIG, 38, 1, 2, 1436, 0 },

  { 719,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_ir), BLOCKIO_SIG, 38, 1, 2, 1438, 0 },

  { 720,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_bz), BLOCKIO_SIG, 38, 1, 2, 1440, 0 },

  { 721,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_cv), BLOCKIO_SIG, 38, 1, 2, 1442, 0 },

  { 722,
    "lgv2/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_LgV2, Compare_mx), BLOCKIO_SIG, 38, 1, 2, 1444, 0 },

  { 723,
    "lgv2/Guidance Systems/Path-following/Path/saturation/Saturation x/LowerRelop1",
    0, "", offsetof(BlockIO_LgV2, LowerRelop1), BLOCKIO_SIG, 8, 1, 2, 1446, 0 },

  { 724,
    "lgv2/Guidance Systems/Path-following/Path/saturation/Saturation x/UpperRelop",
    0, "", offsetof(BlockIO_LgV2, UpperRelop), BLOCKIO_SIG, 8, 1, 2, 1448, 0 },

  { 725,
    "lgv2/Guidance Systems/Path-following/Path/saturation/Saturation y/LowerRelop1",
    0, "", offsetof(BlockIO_LgV2, LowerRelop1_k), BLOCKIO_SIG, 8, 1, 2, 1450, 0
  },

  { 726,
    "lgv2/Guidance Systems/Path-following/Path/saturation/Saturation y/UpperRelop",
    0, "", offsetof(BlockIO_LgV2, UpperRelop_e), BLOCKIO_SIG, 8, 1, 2, 1452, 0 },

  { 727, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic/LowerRelop1", 0, "",
    offsetof(BlockIO_LgV2, LowerRelop1_n), BLOCKIO_SIG, 8, 1, 2, 1454, 0 },

  { 728, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic/UpperRelop", 0, "",
    offsetof(BlockIO_LgV2, UpperRelop_m), BLOCKIO_SIG, 8, 1, 2, 1456, 0 },

  { 729, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic1/LowerRelop1", 0, "",
    offsetof(BlockIO_LgV2, LowerRelop1_j), BLOCKIO_SIG, 8, 1, 2, 1458, 0 },

  { 730, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic1/UpperRelop", 0, "",
    offsetof(BlockIO_LgV2, UpperRelop_b), BLOCKIO_SIG, 8, 1, 2, 1460, 0 },

  { 731, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic2/LowerRelop1", 0, "",
    offsetof(BlockIO_LgV2, LowerRelop1_b), BLOCKIO_SIG, 8, 1, 2, 1462, 0 },

  { 732, "lgv2/Plants/CSE1/Bow Thruster/Saturation Dynamic2/UpperRelop", 0, "",
    offsetof(BlockIO_LgV2, UpperRelop_h), BLOCKIO_SIG, 8, 1, 2, 1464, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 6, 6, 1, 1, 1, 1, 1, 6, 1, 6,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1,
  1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 5,
  5, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 3, 5, 5, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  3, 3, 3, 3, 3, 3, 3, 1, 3, 1, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 2, 1, 2, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
  1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
  3, 3, 1, 1, 3, 3, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
  3, 3, 3, 3, 3, 2, 3, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 1, 1,
  2, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2,
  1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2,
  1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2, 1, 2, 1, 3, 1, 3, 3,
  3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 1, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
  1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2,
  1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
  3, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 7, 1, 1, 1, 1,
  1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 2, 2, 3, 1, 2, 1, 1, 3,
  1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize = 11;
static NI_ExternalIO NI_ExtList[] = {
  { 0, "Naviagation Systems/Qualisys 6 DOF/QTM In", 0, EXT_IN, 9, 9, 1 },

  { 1, "HMI/SIT zAI0", 1, EXT_IN, 1, 1, 1 },

  { 2, "HMI/SIT zAI1", 1, EXT_IN, 1, 1, 1 },

  { 3, "HMI/SIT zAI2", 1, EXT_IN, 1, 1, 1 },

  { 0, "Plants/CSE1/Bow Thruster/SIT PWM0 BT", 0, EXT_OUT, 1, 1, 1 },

  { 1, "Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1", 0, EXT_OUT, 1,
    1, 1 },

  { 2, "Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2", 0, EXT_OUT, 1,
    1, 1 },

  { 3, "Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3", 0, EXT_OUT, 1,
    1, 1 },

  { 4, "Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4", 0, EXT_OUT, 1,
    1, 1 },

  { 5, "Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port", 0, EXT_OUT,
    1, 1, 1 },

  { 6, "Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard", 0,
    EXT_OUT, 1, 1, 1 },

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

static char* NI_CompiledModelName = "lgv2";
static char* NI_CompiledModelVersion = "1.30";
static char* NI_CompiledModelDateTime = "Mon Mar 17 14:04:19 2014";

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
   The undef allows us to access the real LgV2_P
   In the rest of the code LgV2_P is redefine to be the read-side
   of rtParameter.
 */
#undef LgV2_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &LgV2_P, sizeof(Parameters_LgV2));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka LgV2_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_LgV2));
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
             (Parameters_LgV2));

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
           (Parameters_LgV2));
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

#endif                                 // of NI_ROOTMODEL_LgV2
