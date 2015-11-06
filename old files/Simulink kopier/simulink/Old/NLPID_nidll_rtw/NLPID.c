/*
 * NLPID.c
 *
 * Real-Time Workshop code generation for Simulink model "NLPID.mdl".
 *
 * Model Version              : 1.31
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Mon Mar 17 14:05:33 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "NLPID.h"
#include "NLPID_private.h"

/* Block signals (auto storage) */
BlockIO_NLPID NLPID_B;

/* Continuous states */
ContinuousStates_NLPID NLPID_X;

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
D_Work_NLPID NLPID_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_NLPID NLPID_PrevZCSigState;

/* Real-time model */
RT_MODEL_NLPID NLPID_M_;
RT_MODEL_NLPID *NLPID_M = &NLPID_M_;

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
  NLPID_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  NLPID_output(0);
  NLPID_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE5_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  NLPID_output(0);
  NLPID_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++)
    hB[i] = h * rt_ODE5_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  NLPID_output(0);
  NLPID_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++)
    hB[i] = h * rt_ODE5_B[3][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  NLPID_output(0);
  NLPID_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++)
    hB[i] = h * rt_ODE5_B[4][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  NLPID_output(0);
  NLPID_derivatives();

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
void NLPID_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(NLPID_M)) {
    NLPID_M->Timing.t[0] = rtsiGetT(&NLPID_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(NLPID_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&NLPID_M->solverInfo,
                          ((NLPID_M->Timing.clockTick0+1)*
      NLPID_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T tmp;
    real_T tmp_0[5];
    int32_T i;
    real_T tmp_1[18];
    real_T tmp_2[9];
    real_T tmp_3[4];
    real_T tmp_4[9];
    real_T tmp_5[6];
    int32_T tmp_6;

    /* Gain: '<S196>/QTM In2 Error' */
    NLPID_B.QTMIn2Error = NLPID_P.QTMIn2Error_Gain * NLPID_B.QTMIn[1];

    /* Gain: '<S196>/QTM In9 Residual' */
    NLPID_B.QTMIn9Residual = NLPID_P.QTMIn9Residual_Gain * NLPID_B.QTMIn[8];

    /* Gain: '<S196>/QTM In3' */
    NLPID_B.QTMIn3 = NLPID_P.QTMIn3_Gain * NLPID_B.QTMIn[2];

    /* Gain: '<S196>/mm2m x' */
    NLPID_B.mm2mx = NLPID_P.mm2mx_Gain * NLPID_B.QTMIn3;

    /* Gain: '<S196>/QTM In4' */
    NLPID_B.QTMIn4 = NLPID_P.QTMIn4_Gain * NLPID_B.QTMIn[3];

    /* Gain: '<S196>/mm2m y' */
    NLPID_B.mm2my = NLPID_P.mm2my_Gain * NLPID_B.QTMIn4;

    /* Gain: '<S196>/QTM In6' */
    NLPID_B.QTMIn6 = NLPID_P.QTMIn6_Gain * NLPID_B.QTMIn[5];

    /* Gain: '<S196>/d2r yaw' */
    NLPID_B.d2ryaw = NLPID_P.d2ryaw_Gain * NLPID_B.QTMIn6;

    /* Derivative Block: '<S196>/Derivative1' */
    {
      real_T t = NLPID_M->Timing.t[0];
      real_T timeStampA = NLPID_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = NLPID_DWork.Derivative1_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        NLPID_B.Derivative1[0] = 0.0;
        NLPID_B.Derivative1[1] = 0.0;
        NLPID_B.Derivative1[2] = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &NLPID_DWork.Derivative1_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 4;
          }
        } else if (timeStampA >= t) {
          lastBank += 4;
        }

        deltaT = t - *lastBank++;
        NLPID_B.Derivative1[0] = (NLPID_B.mm2mx - *lastBank++) / deltaT;
        NLPID_B.Derivative1[1] = (NLPID_B.mm2my - *lastBank++) / deltaT;
        NLPID_B.Derivative1[2] = (NLPID_B.d2ryaw - *lastBank++) / deltaT;
      }
    }

    /* Outputs for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Constant: '<S5>/Enable Linear Simulator'
     *  EnablePort: '<S199>/Enable'
     */
    if (rtmIsMajorTimeStep(NLPID_M) && rtmIsMajorTimeStep(NLPID_M)) {
      if (NLPID_P.EnableLinearSimulator_Value > 0.0) {
        if (NLPID_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S206>/Integrator' */
          if (rtmIsFirstInitCond(NLPID_M)) {
            NLPID_X.Integrator_CSTATE_l[0] = 0.0;
            NLPID_X.Integrator_CSTATE_l[1] = 0.0;
            NLPID_X.Integrator_CSTATE_l[2] = 0.0;
          }

          NLPID_DWork.Integrator_IWORK_k.IcNeedsLoading = 1;

          /* Integrator Block: '<S206>/Integrator1' */
          if (rtmIsFirstInitCond(NLPID_M)) {
            NLPID_X.Integrator1_CSTATE_i[0] = 0.0;
            NLPID_X.Integrator1_CSTATE_i[1] = 0.0;
            NLPID_X.Integrator1_CSTATE_i[2] = 0.0;
          }

          NLPID_DWork.Integrator1_IWORK_o.IcNeedsLoading = 1;
          NLPID_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (NLPID_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
          NLPID_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (NLPID_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      if (rtmIsMajorTimeStep(NLPID_M)) {
        /* Gain: '<S207>/-N_r' incorporates:
         *  Constant: '<S207>/N_r'
         */
        NLPID_B.N_r_l = NLPID_P.N_r_Gain_p * NLPID_P.N_r_Value_j;

        /* Gain: '<S207>/-N_v' incorporates:
         *  Constant: '<S207>/N_v'
         */
        NLPID_B.N_v_g = NLPID_P.N_v_Gain_d * NLPID_P.N_v_Value_d;

        /* Gain: '<S207>/-X_u' incorporates:
         *  Constant: '<S207>/X_u'
         */
        NLPID_B.X_u_k = NLPID_P.X_u_Gain_m * NLPID_P.X_u_Value_m;

        /* Gain: '<S207>/-Y_v' incorporates:
         *  Constant: '<S207>/Y_v'
         */
        NLPID_B.Y_v_h = NLPID_P.Y_v_Gain_p * NLPID_P.Y_v_Value_p;

        /* Gain: '<S207>/-Y_vr' incorporates:
         *  Constant: '<S207>/Y_r'
         */
        NLPID_B.Y_vr_i = NLPID_P.Y_vr_Gain_c * NLPID_P.Y_r_Value_f;

        /* Reshape: '<S207>/Linear Dampning matrix' incorporates:
         *  Constant: '<S207>/D_L_12'
         *  Constant: '<S207>/D_L_13'
         *  Constant: '<S207>/D_L_21'
         *  Constant: '<S207>/D_L_31'
         */
        NLPID_B.LinearDampningmatrix_f[0] = NLPID_B.X_u_k;
        NLPID_B.LinearDampningmatrix_f[1] = NLPID_P.D_L_21_Value_d;
        NLPID_B.LinearDampningmatrix_f[2] = NLPID_P.D_L_31_Value_l;
        NLPID_B.LinearDampningmatrix_f[3] = NLPID_P.D_L_12_Value_g;
        NLPID_B.LinearDampningmatrix_f[4] = NLPID_B.Y_v_h;
        NLPID_B.LinearDampningmatrix_f[5] = NLPID_B.N_v_g;
        NLPID_B.LinearDampningmatrix_f[6] = NLPID_P.D_L_13_Value_o;
        NLPID_B.LinearDampningmatrix_f[7] = NLPID_B.Y_vr_i;
        NLPID_B.LinearDampningmatrix_f[8] = NLPID_B.N_r_l;

        /* Constant: '<S208>/psi_0' */
        NLPID_B.psi_0 = NLPID_P.psi_0_Value;

        /* Constant: '<S208>/x_0' */
        NLPID_B.x_0 = NLPID_P.x_0_Value;

        /* Constant: '<S208>/y_0' */
        NLPID_B.y_0 = NLPID_P.y_0_Value;

        /* Constant: '<S209>/r_0' */
        NLPID_B.r_0 = NLPID_P.r_0_Value;

        /* Constant: '<S209>/u_0' */
        NLPID_B.u_0 = NLPID_P.u_0_Value;

        /* Constant: '<S209>/v_0' */
        NLPID_B.v_0 = NLPID_P.v_0_Value;
      }

      /* Integrator Block: '<S206>/Integrator'
       */
      if (rtmIsMajorTimeStep(NLPID_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &NLPID_PrevZCSigState.Integrator_Reset_ZCE_c,
                           NLPID_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || NLPID_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            NLPID_DWork.Integrator_IWORK_k.IcNeedsLoading) {
          NLPID_X.Integrator_CSTATE_l[0] = NLPID_B.u_0;
          NLPID_X.Integrator_CSTATE_l[1] = NLPID_B.v_0;
          NLPID_X.Integrator_CSTATE_l[2] = NLPID_B.r_0;
        }

        NLPID_DWork.Integrator_IWORK_k.IcNeedsLoading = 0;
      }

      NLPID_B.Integrator_m[0] = NLPID_X.Integrator_CSTATE_l[0];
      NLPID_B.Integrator_m[1] = NLPID_X.Integrator_CSTATE_l[1];
      NLPID_B.Integrator_m[2] = NLPID_X.Integrator_CSTATE_l[2];

      /* Integrator Block: '<S206>/Integrator1'
       */
      if (rtmIsMajorTimeStep(NLPID_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &NLPID_PrevZCSigState.Integrator1_Reset_ZCE_o,
                           NLPID_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || NLPID_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            NLPID_DWork.Integrator1_IWORK_o.IcNeedsLoading) {
          NLPID_X.Integrator1_CSTATE_i[0] = NLPID_B.x_0;
          NLPID_X.Integrator1_CSTATE_i[1] = NLPID_B.y_0;
          NLPID_X.Integrator1_CSTATE_i[2] = NLPID_B.psi_0;
        }

        NLPID_DWork.Integrator1_IWORK_o.IcNeedsLoading = 0;
      }

      NLPID_B.Integrator1_m[0] = NLPID_X.Integrator1_CSTATE_i[0];
      NLPID_B.Integrator1_m[1] = NLPID_X.Integrator1_CSTATE_i[1];
      NLPID_B.Integrator1_m[2] = NLPID_X.Integrator1_CSTATE_i[2];
      if (rtmIsMajorTimeStep(NLPID_M)) {
        /* Sum: '<S210>/M_11' incorporates:
         *  Constant: '<S210>/X_udot'
         *  Constant: '<S210>/m'
         */
        NLPID_B.M_11_c = NLPID_P.m_Value_k - NLPID_P.X_udot_Value_k;

        /* Sum: '<S210>/M_22' incorporates:
         *  Constant: '<S210>/Y_vdot'
         *  Constant: '<S210>/m'
         */
        NLPID_B.M_22_k = NLPID_P.m_Value_k - NLPID_P.Y_vdot_Value_b;

        /* Product: '<S210>/m x_g' incorporates:
         *  Constant: '<S210>/m'
         *  Constant: '<S210>/x_g'
         */
        NLPID_B.mx_g_c = NLPID_P.m_Value_k * NLPID_P.x_g_Value_i;

        /* Sum: '<S210>/M_32' incorporates:
         *  Constant: '<S210>/N_vdot'
         */
        NLPID_B.M_32_b = NLPID_B.mx_g_c - NLPID_P.N_vdot_Value_n;

        /* Sum: '<S210>/M_23' incorporates:
         *  Constant: '<S210>/Y_rdot'
         */
        NLPID_B.M_23_f = NLPID_B.mx_g_c - NLPID_P.Y_rdot_Value_f;

        /* Sum: '<S210>/M_33' incorporates:
         *  Constant: '<S210>/I_z'
         *  Constant: '<S210>/N_rdot'
         */
        NLPID_B.M_33_e = NLPID_P.I_z_Value_k - NLPID_P.N_rdot_Value_f;

        /* Reshape: '<S210>/M' incorporates:
         *  Constant: '<S210>/M_12'
         *  Constant: '<S210>/M_13'
         *  Constant: '<S210>/M_21'
         *  Constant: '<S210>/M_31'
         */
        NLPID_B.M[0] = NLPID_B.M_11_c;
        NLPID_B.M[1] = NLPID_P.M_21_Value_h;
        NLPID_B.M[2] = NLPID_P.M_31_Value_d;
        NLPID_B.M[3] = NLPID_P.M_12_Value_j;
        NLPID_B.M[4] = NLPID_B.M_22_k;
        NLPID_B.M[5] = NLPID_B.M_32_b;
        NLPID_B.M[6] = NLPID_P.M_13_Value_d;
        NLPID_B.M[7] = NLPID_B.M_23_f;
        NLPID_B.M[8] = NLPID_B.M_33_e;

        /* Product Block: '<S210>/Inverse' */
        {
          static const int_T dims[3] = { 3, 3, 3 };

          rt_MatDivRR_Dbl(NLPID_B.Inverse, NLPID_B.M,
                          &NLPID_DWork.Inverse_DWORK4[0], (real_T*)
                          &NLPID_DWork.Pseudoinverse_X[0],
                          &NLPID_DWork.Inverse_DWORK2[0], (real_T*)
                          &NLPID_DWork.Inverse_DWORK3[0],
                          &dims[0]);
        }
      }

      /* Fcn: '<S211>/R11' */
      NLPID_B.R11_m = cos(NLPID_B.Integrator1_m[2]);

      /* Fcn: '<S211>/R21' */
      NLPID_B.R21_h = sin(NLPID_B.Integrator1_m[2]);

      /* Fcn: '<S211>/R12' */
      NLPID_B.R12_d = -1.0 * sin(NLPID_B.Integrator1_m[2]);

      /* Fcn: '<S211>/R22' */
      NLPID_B.R22_le = cos(NLPID_B.Integrator1_m[2]);

      /* Reshape: '<S211>/R(psi)' incorporates:
       *  Constant: '<S211>/R13'
       *  Constant: '<S211>/R23'
       *  Constant: '<S211>/R31'
       *  Constant: '<S211>/R32'
       *  Constant: '<S211>/R33'
       */
      NLPID_B.Rpsi_c[0] = NLPID_B.R11_m;
      NLPID_B.Rpsi_c[1] = NLPID_B.R21_h;
      NLPID_B.Rpsi_c[2] = NLPID_P.R31_Value_n;
      NLPID_B.Rpsi_c[3] = NLPID_B.R12_d;
      NLPID_B.Rpsi_c[4] = NLPID_B.R22_le;
      NLPID_B.Rpsi_c[5] = NLPID_P.R32_Value_g;
      NLPID_B.Rpsi_c[6] = NLPID_P.R13_Value_i;
      NLPID_B.Rpsi_c[7] = NLPID_P.R23_Value_i;
      NLPID_B.Rpsi_c[8] = NLPID_P.R33_Value_k;
      for (i = 0; i < 3; i++) {
        /* Product: '<S206>/Product1' */
        NLPID_B.Product1_o4[i] = 0.0;
        NLPID_B.Product1_o4[i] = NLPID_B.LinearDampningmatrix_f[i] *
          NLPID_B.Integrator_m[0] + NLPID_B.Product1_o4[i];
        NLPID_B.Product1_o4[i] = NLPID_B.LinearDampningmatrix_f[i + 3] *
          NLPID_B.Integrator_m[1] + NLPID_B.Product1_o4[i];
        NLPID_B.Product1_o4[i] = NLPID_B.LinearDampningmatrix_f[i + 6] *
          NLPID_B.Integrator_m[2] + NLPID_B.Product1_o4[i];

        /* Product: '<S206>/Product3' */
        NLPID_B.Product3_fn[i] = 0.0;
        NLPID_B.Product3_fn[i] = NLPID_B.Rpsi_c[i] * NLPID_B.Integrator_m[0] +
          NLPID_B.Product3_fn[i];
        NLPID_B.Product3_fn[i] = NLPID_B.Rpsi_c[i + 3] * NLPID_B.Integrator_m[1]
          + NLPID_B.Product3_fn[i];
        NLPID_B.Product3_fn[i] = NLPID_B.Rpsi_c[i + 6] * NLPID_B.Integrator_m[2]
          + NLPID_B.Product3_fn[i];
      }

      /* Gain: '<S199>/eta_surge_hil' */
      NLPID_B.eta_surge_hil = NLPID_P.eta_surge_hil_Gain *
        NLPID_B.Integrator1_m[0];

      /* Gain: '<S199>/eta_sway_hil' */
      NLPID_B.eta_sway_hil = NLPID_P.eta_sway_hil_Gain * NLPID_B.Integrator1_m[1];

      /* Gain: '<S199>/eta_yaw_hil' */
      NLPID_B.eta_yaw_hil = NLPID_P.eta_yaw_hil_Gain * NLPID_B.Integrator1_m[2];

      /* Gain: '<S199>/etadot_surge_hil' */
      NLPID_B.etadot_surge_hil = NLPID_P.etadot_surge_hil_Gain *
        NLPID_B.Product3_fn[0];

      /* Gain: '<S199>/etadot_sway_hil' */
      NLPID_B.etadot_sway_hil = NLPID_P.etadot_sway_hil_Gain *
        NLPID_B.Product3_fn[1];

      /* Gain: '<S199>/etadot_yaw_hil' */
      NLPID_B.etadot_yaw_hil = NLPID_P.etadot_yaw_hil_Gain *
        NLPID_B.Product3_fn[2];

      /* Gain: '<S199>/nu_surge_hil' */
      NLPID_B.nu_surge_hil = NLPID_P.nu_surge_hil_Gain * NLPID_B.Integrator_m[0];

      /* Gain: '<S199>/nu_sway_hil' */
      NLPID_B.nu_sway_hil = NLPID_P.nu_sway_hil_Gain * NLPID_B.Integrator_m[1];

      /* Gain: '<S199>/nu_yaw_hil' */
      NLPID_B.nu_yaw_hil = NLPID_P.nu_yaw_hil_Gain * NLPID_B.Integrator_m[2];
    }

    /* end of Outputs for SubSystem: '<S5>/Linear Simulator' */

    /* MultiPortSwitch: '<S4>/Etadot Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)NLPID_P.ControllerInputSelector_Value == 0) {
      NLPID_B.EtadotSwitch[0] = NLPID_B.Derivative1[0];
      NLPID_B.EtadotSwitch[1] = NLPID_B.Derivative1[1];
      NLPID_B.EtadotSwitch[2] = NLPID_B.Derivative1[2];
    } else {
      NLPID_B.EtadotSwitch[0] = NLPID_B.etadot_surge_hil;
      NLPID_B.EtadotSwitch[1] = NLPID_B.etadot_sway_hil;
      NLPID_B.EtadotSwitch[2] = NLPID_B.etadot_yaw_hil;
    }

    /* Gain: '<S4>/etadot_surge' */
    NLPID_B.etadot_surge = NLPID_P.etadot_surge_Gain * NLPID_B.EtadotSwitch[0];

    /* Gain: '<S4>/etadot_sway' */
    NLPID_B.etadot_sway = NLPID_P.etadot_sway_Gain * NLPID_B.EtadotSwitch[1];

    /* Gain: '<S4>/etadot_yaw' */
    NLPID_B.etadot_yaw = NLPID_P.etadot_yaw_Gain * NLPID_B.EtadotSwitch[2];

    /* MultiPortSwitch: '<S4>/Eta Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)NLPID_P.ControllerInputSelector_Value == 0) {
      NLPID_B.EtaSwitch[0] = NLPID_B.mm2mx;
      NLPID_B.EtaSwitch[1] = NLPID_B.mm2my;
      NLPID_B.EtaSwitch[2] = NLPID_B.d2ryaw;
    } else {
      NLPID_B.EtaSwitch[0] = NLPID_B.eta_surge_hil;
      NLPID_B.EtaSwitch[1] = NLPID_B.eta_sway_hil;
      NLPID_B.EtaSwitch[2] = NLPID_B.eta_yaw_hil;
    }

    /* Gain: '<S4>/eta_surge' */
    NLPID_B.eta_surge = NLPID_P.eta_surge_Gain * NLPID_B.EtaSwitch[0];

    /* Gain: '<S4>/eta_sway' */
    NLPID_B.eta_sway = NLPID_P.eta_sway_Gain * NLPID_B.EtaSwitch[1];

    /* Gain: '<S4>/eta_yaw' */
    NLPID_B.eta_yaw = NLPID_P.eta_yaw_Gain * NLPID_B.EtaSwitch[2];

    /* Gain: '<S196>/QTM In8' */
    NLPID_B.QTMIn8 = NLPID_P.QTMIn8_Gain * NLPID_B.QTMIn[7];

    /* Gain: '<S196>/d2r roll' */
    NLPID_B.d2rroll = NLPID_P.d2rroll_Gain * NLPID_B.QTMIn8;

    /* Gain: '<S196>/QTM In7' */
    NLPID_B.QTMIn7 = NLPID_P.QTMIn7_Gain * NLPID_B.QTMIn[6];

    /* Gain: '<S196>/d2r pitch' */
    NLPID_B.d2rpitch = NLPID_P.d2rpitch_Gain * NLPID_B.QTMIn7;

    /* Trigonometry: '<S197>/sin(theta)' */
    NLPID_B.sintheta[0] = sin(NLPID_B.d2rroll);
    NLPID_B.sintheta[1] = sin(NLPID_B.d2rpitch);
    NLPID_B.sintheta[2] = sin(NLPID_B.d2ryaw);

    /* Trigonometry: '<S197>/cos(theta)' */
    NLPID_B.costheta[0] = cos(NLPID_B.d2rroll);
    NLPID_B.costheta[1] = cos(NLPID_B.d2rpitch);
    NLPID_B.costheta[2] = cos(NLPID_B.d2ryaw);

    /* Fcn: '<S197>/R11' */
    NLPID_B.R11 = NLPID_B.costheta[1] * NLPID_B.costheta[2];

    /* Fcn: '<S197>/R21 ' */
    NLPID_B.R21 = NLPID_B.sintheta[0] * NLPID_B.sintheta[1] * NLPID_B.costheta[2]
      + (-NLPID_B.costheta[0]) * NLPID_B.sintheta[2];

    /* Fcn: '<S197>/R31 ' */
    NLPID_B.R31 = NLPID_B.costheta[0] * NLPID_B.sintheta[1] * NLPID_B.costheta[2]
      + NLPID_B.sintheta[0] * NLPID_B.sintheta[2];

    /* Fcn: '<S197>/R12' */
    NLPID_B.R12 = NLPID_B.costheta[1] * NLPID_B.sintheta[2];

    /* Fcn: '<S197>/R22' */
    NLPID_B.R22 = NLPID_B.sintheta[0] * NLPID_B.sintheta[1] * NLPID_B.sintheta[2]
      + NLPID_B.costheta[0] * NLPID_B.costheta[2];

    /* Fcn: '<S197>/R32' */
    NLPID_B.R32 = NLPID_B.costheta[0] * NLPID_B.sintheta[1] * NLPID_B.sintheta[2]
      + (-NLPID_B.sintheta[0]) * NLPID_B.costheta[2];

    /* Fcn: '<S197>/R13' */
    NLPID_B.R13 = -NLPID_B.sintheta[1];

    /* Fcn: '<S197>/R23' */
    NLPID_B.R23 = NLPID_B.sintheta[0] * NLPID_B.costheta[1];

    /* Fcn: '<S197>/R33' */
    NLPID_B.R33 = NLPID_B.costheta[0] * NLPID_B.costheta[1];

    /* Reshape: '<S197>/Reshape 9x1->3x3' */
    NLPID_B.Reshape9x13x3[0] = NLPID_B.R11;
    NLPID_B.Reshape9x13x3[1] = NLPID_B.R21;
    NLPID_B.Reshape9x13x3[2] = NLPID_B.R31;
    NLPID_B.Reshape9x13x3[3] = NLPID_B.R12;
    NLPID_B.Reshape9x13x3[4] = NLPID_B.R22;
    NLPID_B.Reshape9x13x3[5] = NLPID_B.R32;
    NLPID_B.Reshape9x13x3[6] = NLPID_B.R13;
    NLPID_B.Reshape9x13x3[7] = NLPID_B.R23;
    NLPID_B.Reshape9x13x3[8] = NLPID_B.R33;

    /* Concatenate: '<S196>/Matrix Concatenate' incorporates:
     *  Constant: '<S196>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = NLPID_B.Reshape9x13x3[3 * i];
      tmp_1[1 + 6 * i] = NLPID_B.Reshape9x13x3[3 * i + 1];
      tmp_1[2 + 6 * i] = NLPID_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = NLPID_P.Constant1_Value[3 * i];
      tmp_1[4 + 6 * i] = NLPID_P.Constant1_Value[3 * i + 1];
      tmp_1[5 + 6 * i] = NLPID_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&NLPID_B.MatrixConcatenate2[0]), (void *)&tmp_1[0], 18U *
           sizeof(real_T));

    /* Concatenate: '<S196>/Matrix Concatenate1' incorporates:
     *  Constant: '<S196>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = NLPID_P.Constant1_Value[3 * i];
      tmp_1[1 + 6 * i] = NLPID_P.Constant1_Value[3 * i + 1];
      tmp_1[2 + 6 * i] = NLPID_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = NLPID_B.Reshape9x13x3[3 * i];
      tmp_1[4 + 6 * i] = NLPID_B.Reshape9x13x3[3 * i + 1];
      tmp_1[5 + 6 * i] = NLPID_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&NLPID_B.MatrixConcatenate2[18]), (void *)&tmp_1[0], 18U *
           sizeof(real_T));

    /* Gain: '<S196>/QTM In5' */
    NLPID_B.QTMIn5 = NLPID_P.QTMIn5_Gain * NLPID_B.QTMIn[4];

    /* Gain: '<S196>/mm2m z' */
    NLPID_B.mm2mz = NLPID_P.mm2mz_Gain * NLPID_B.QTMIn5;

    /* Derivative Block: '<S196>/Derivative' */
    {
      real_T t = NLPID_M->Timing.t[0];
      real_T timeStampA = NLPID_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = NLPID_DWork.Derivative_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = NLPID_B.Derivative;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank = &NLPID_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        NLPID_B.Derivative[0] = (NLPID_B.mm2mx - *lastBank++) / deltaT;
        NLPID_B.Derivative[1] = (NLPID_B.mm2my - *lastBank++) / deltaT;
        NLPID_B.Derivative[2] = (NLPID_B.mm2mz - *lastBank++) / deltaT;
        NLPID_B.Derivative[3] = (NLPID_B.d2rroll - *lastBank++) / deltaT;
        NLPID_B.Derivative[4] = (NLPID_B.d2rpitch - *lastBank++) / deltaT;
        NLPID_B.Derivative[5] = (NLPID_B.d2ryaw - *lastBank++) / deltaT;
      }
    }

    /* Product: '<S196>/Product' */
    for (i = 0; i < 6; i++) {
      NLPID_B.Product[i] = 0.0;
      for (tmp_6 = 0; tmp_6 < 6; tmp_6++) {
        NLPID_B.Product[i] = NLPID_B.MatrixConcatenate2[6 * tmp_6 + i] *
          NLPID_B.Derivative[tmp_6] + NLPID_B.Product[i];
      }
    }

    /* MultiPortSwitch: '<S4>/Nu Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)NLPID_P.ControllerInputSelector_Value == 0) {
      NLPID_B.NuSwitch[0] = NLPID_B.Product[0];
      NLPID_B.NuSwitch[1] = NLPID_B.Product[1];
      NLPID_B.NuSwitch[2] = NLPID_B.Product[5];
    } else {
      NLPID_B.NuSwitch[0] = NLPID_B.nu_surge_hil;
      NLPID_B.NuSwitch[1] = NLPID_B.nu_sway_hil;
      NLPID_B.NuSwitch[2] = NLPID_B.nu_yaw_hil;
    }

    /* Gain: '<S4>/nu_surge' */
    NLPID_B.nu_surge = NLPID_P.nu_surge_Gain * NLPID_B.NuSwitch[0];

    /* Gain: '<S4>/nu_sway' */
    NLPID_B.nu_sway = NLPID_P.nu_sway_Gain * NLPID_B.NuSwitch[1];

    /* Gain: '<S4>/nu_yaw' */
    NLPID_B.nu_yaw = NLPID_P.nu_yaw_Gain * NLPID_B.NuSwitch[2];
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Gain: '<S110>/eta_d DP N' incorporates:
       *  Constant: '<S193>/x_d'
       */
      NLPID_B.eta_dDPN = NLPID_P.eta_dDPN_Gain * NLPID_P.x_d_Value;

      /* Gain: '<S110>/eta_d DP E' incorporates:
       *  Constant: '<S193>/y_d'
       */
      NLPID_B.eta_dDPE = NLPID_P.eta_dDPE_Gain * NLPID_P.y_d_Value;

      /* Gain: '<S195>/Gain1' incorporates:
       *  Constant: '<S193>/psi_d'
       */
      NLPID_B.Gain1 = NLPID_P.Gain1_Gain * NLPID_P.psi_d_Value;

      /* Gain: '<S110>/eta_d DP Psi' */
      NLPID_B.eta_dDPPsi = NLPID_P.eta_dDPPsi_Gain * NLPID_B.Gain1;

      /* Constant: '<S102>/q_x_0' */
      NLPID_B.q_x_0 = NLPID_P.q_x_0_Value;

      /* Constant: '<S102>/q_y_0' */
      NLPID_B.q_y_0 = NLPID_P.q_y_0_Value;
    }

    /* Integrator Block: '<S50>/Integrator'
     */
    if (rtmIsMajorTimeStep(NLPID_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &NLPID_PrevZCSigState.Integrator_Reset_ZCE,
                         NLPID_P.Resetq_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || NLPID_P.Resetq_Value != 0.0 ||
          NLPID_DWork.Integrator_IWORK.IcNeedsLoading) {
        NLPID_X.Integrator_CSTATE[0] = NLPID_B.q_x_0;
        NLPID_X.Integrator_CSTATE[1] = NLPID_B.q_y_0;
      }

      NLPID_DWork.Integrator_IWORK.IcNeedsLoading = 0;
    }

    NLPID_B.Integrator[0] = NLPID_X.Integrator_CSTATE[0];
    NLPID_B.Integrator[1] = NLPID_X.Integrator_CSTATE[1];

    /* SignalConversion: '<S122>/ConcatBufferAtVector ConcatenateIn1' */
    NLPID_B.VectorConcatenate[0] = NLPID_B.Integrator[0];
    NLPID_B.VectorConcatenate[1] = NLPID_B.Integrator[1];
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Sum: '<S184>/x_2 - x_1' incorporates:
       *  Constant: '<S194>/x_1'
       *  Constant: '<S194>/x_2'
       */
      NLPID_B.x_2x_1 = NLPID_P.x_2_Value - NLPID_P.x_1_Value;

      /* Sum: '<S184>/y_2 - y_1' incorporates:
       *  Constant: '<S194>/y_1'
       *  Constant: '<S194>/y_2'
       */
      NLPID_B.y_2y_1 = NLPID_P.y_2_Value - NLPID_P.y_1_Value;

      /* SignalConversion: '<S185>/TmpHiddenBufferAtProductInport2' */
      NLPID_B.TmpHiddenBufferAtProductInport2[0] = NLPID_B.x_2x_1;
      NLPID_B.TmpHiddenBufferAtProductInport2[1] = NLPID_B.y_2y_1;

      /* Product: '<S179>/Product' incorporates:
       *  Constant: '<S114>/Path Selector'
       */
      NLPID_B.Product_l[0] = NLPID_B.TmpHiddenBufferAtProductInport2[0] *
        NLPID_P.PathSelector_Value;
      NLPID_B.Product_l[1] = NLPID_B.TmpHiddenBufferAtProductInport2[1] *
        NLPID_P.PathSelector_Value;

      /* Constant: '<S50>/s_0' */
      NLPID_B.s_0 = NLPID_P.s_0_Value;
    }

    /* Integrator Block: '<S50>/Integrator1'
     */
    if (rtmIsMajorTimeStep(NLPID_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &NLPID_PrevZCSigState.Integrator1_Reset_ZCE,
                         NLPID_P.Resets_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || NLPID_P.Resets_Value != 0.0 ||
          NLPID_DWork.Integrator1_IWORK.IcNeedsLoading) {
        NLPID_X.Integrator1_CSTATE = NLPID_B.s_0;
      }

      NLPID_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
    }

    NLPID_B.Integrator1 = NLPID_X.Integrator1_CSTATE;

    /* Product: '<S173>/Product2' incorporates:
     *  Constant: '<S194>/k'
     */
    NLPID_B.Product2 = NLPID_B.Integrator1 * NLPID_P.k_Value;

    /* Trigonometry: '<S173>/sin(s)' */
    NLPID_B.sins = sin(NLPID_B.Product2);

    /* Product: '<S173>/Product' incorporates:
     *  Constant: '<S194>/k'
     *  Constant: '<S194>/r_x'
     */
    NLPID_B.Product_b = NLPID_P.r_x_Value * NLPID_B.sins * NLPID_P.k_Value;

    /* Gain: '<S173>/Gain' */
    NLPID_B.Gain = NLPID_P.Gain_Gain * NLPID_B.Product_b;

    /* Trigonometry: '<S173>/cos(s)' */
    NLPID_B.coss = cos(NLPID_B.Product2);

    /* Product: '<S173>/Product1' incorporates:
     *  Constant: '<S194>/k'
     *  Constant: '<S194>/r_y'
     */
    NLPID_B.Product1 = NLPID_P.r_y_Value * NLPID_B.coss * NLPID_P.k_Value;

    /* SignalConversion: '<S176>/TmpHiddenBufferAtProductInport2' */
    NLPID_B.TmpHiddenBufferAtProductInpor_k[0] = NLPID_B.Gain;
    NLPID_B.TmpHiddenBufferAtProductInpor_k[1] = NLPID_B.Product1;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Sum: '<S179>/Subtract' incorporates:
       *  Constant: '<S114>/Path Selector'
       *  Constant: '<S179>/Constant'
       */
      NLPID_B.Subtract = NLPID_P.Constant_Value - NLPID_P.PathSelector_Value;
    }

    /* Product: '<S179>/Product1' */
    NLPID_B.Product1_k[0] = NLPID_B.TmpHiddenBufferAtProductInpor_k[0] *
      NLPID_B.Subtract;

    /* Sum: '<S179>/Add' */
    NLPID_B.Add[0] = NLPID_B.Product_l[0] + NLPID_B.Product1_k[0];

    /* Product: '<S179>/Product1' */
    NLPID_B.Product1_k[1] = NLPID_B.TmpHiddenBufferAtProductInpor_k[1] *
      NLPID_B.Subtract;

    /* Sum: '<S179>/Add' */
    NLPID_B.Add[1] = NLPID_B.Product_l[1] + NLPID_B.Product1_k[1];

    /* Trigonometry: '<S116>/Trigonometric Function' */
    NLPID_B.TrigonometricFunction = rt_atan2_snf(NLPID_B.Add[1], NLPID_B.Add[0]);

    /* Gain: '<S121>/Gain' */
    NLPID_B.Gain_l = NLPID_P.Gain_Gain_k * NLPID_B.TrigonometricFunction;

    /* Saturate: '<S119>/Saturation' */
    tmp = NLPID_B.Gain_l;
    NLPID_B.Saturation = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat,
      NLPID_P.Saturation_UpperSat);

    /* Signum: '<S119>/Sign' */
    NLPID_B.Sign = rt_SIGNd_snf(NLPID_B.Saturation);

    /* Gain: '<S119>/Gain' */
    NLPID_B.Gain_g = NLPID_P.Gain_Gain_d * NLPID_B.Sign;

    /* Sum: '<S119>/Sum1' */
    NLPID_B.Sum1 = NLPID_B.Saturation + NLPID_B.Gain_g;

    /* Math: '<S119>/Math Function' incorporates:
     *  Constant: '<S119>/Constant'
     */
    NLPID_B.MathFunction = rt_rem_snf(NLPID_B.Sum1, NLPID_P.Constant_Value_e);

    /* Sum: '<S119>/Sum' */
    NLPID_B.Sum = NLPID_B.MathFunction - NLPID_B.Gain_g;

    /* Gain: '<S120>/Gain1' */
    NLPID_B.Gain1_o = NLPID_P.Gain1_Gain_g * NLPID_B.Sum;

    /* Gain: '<S154>/Gain' */
    NLPID_B.Gain_i = NLPID_P.Gain_Gain_h * NLPID_B.Gain1_o;

    /* Saturate: '<S150>/Saturation' */
    tmp = NLPID_B.Gain_i;
    NLPID_B.Saturation_k = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat_d,
      NLPID_P.Saturation_UpperSat_o);

    /* Signum: '<S150>/Sign' */
    NLPID_B.Sign_o = rt_SIGNd_snf(NLPID_B.Saturation_k);

    /* Gain: '<S150>/Gain' */
    NLPID_B.Gain_h = NLPID_P.Gain_Gain_j * NLPID_B.Sign_o;

    /* Sum: '<S150>/Sum1' */
    NLPID_B.Sum1_o = NLPID_B.Saturation_k + NLPID_B.Gain_h;

    /* Math: '<S150>/Math Function' incorporates:
     *  Constant: '<S150>/Constant'
     */
    NLPID_B.MathFunction_g = rt_rem_snf(NLPID_B.Sum1_o, NLPID_P.Constant_Value_c);

    /* Sum: '<S150>/Sum' */
    NLPID_B.Sum_h = NLPID_B.MathFunction_g - NLPID_B.Gain_h;

    /* Gain: '<S153>/Gain1' */
    NLPID_B.Gain1_f = NLPID_P.Gain1_Gain_j * NLPID_B.Sum_h;

    /* Outputs for atomic SubSystem: '<S127>/R_2' */

    /* Trigonometry: '<S159>/R11' */
    NLPID_B.R11_k = cos(NLPID_B.Gain1_o);

    /* Trigonometry: '<S159>/R21' */
    NLPID_B.R21_o = sin(NLPID_B.Gain1_o);

    /* Gain: '<S159>/R12' */
    NLPID_B.R12_h = NLPID_P.R12_Gain * NLPID_B.R21_o;

    /* Gain: '<S159>/R22' */
    NLPID_B.R22_c = NLPID_P.R22_Gain * NLPID_B.R11_k;

    /* Reshape: '<S159>/R_2(psi_d)' */
    NLPID_B.R_2psi_d[0] = NLPID_B.R11_k;
    NLPID_B.R_2psi_d[1] = NLPID_B.R21_o;
    NLPID_B.R_2psi_d[2] = NLPID_B.R12_h;
    NLPID_B.R_2psi_d[3] = NLPID_B.R22_c;

    /* end of Outputs for SubSystem: '<S127>/R_2' */

    /* Math: '<S160>/Math Function' */
    NLPID_B.MathFunction_d[0] = NLPID_B.R_2psi_d[0];
    NLPID_B.MathFunction_d[1] = NLPID_B.R_2psi_d[2];
    NLPID_B.MathFunction_d[2] = NLPID_B.R_2psi_d[1];
    NLPID_B.MathFunction_d[3] = NLPID_B.R_2psi_d[3];
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Sum: '<S183>/x_2 - x_1' incorporates:
       *  Constant: '<S194>/x_1'
       *  Constant: '<S194>/x_2'
       */
      NLPID_B.x_2x_1_p = NLPID_P.x_2_Value - NLPID_P.x_1_Value;
    }

    /* Product: '<S183>/(x_2 - x_1) * s' */
    NLPID_B.x_2x_1s = NLPID_B.x_2x_1_p * NLPID_B.Integrator1;

    /* Sum: '<S183>/(x_2 - x_1) * s + x_1' incorporates:
     *  Constant: '<S194>/x_1'
     */
    NLPID_B.x_2x_1sx_1 = NLPID_B.x_2x_1s + NLPID_P.x_1_Value;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Sum: '<S183>/y_2 - y_1' incorporates:
       *  Constant: '<S194>/y_1'
       *  Constant: '<S194>/y_2'
       */
      NLPID_B.y_2y_1_g = NLPID_P.y_2_Value - NLPID_P.y_1_Value;
    }

    /* Product: '<S183>/(y_2 - y_1) * s' */
    NLPID_B.y_2y_1s = NLPID_B.y_2y_1_g * NLPID_B.Integrator1;

    /* Sum: '<S183>/(y_2 - y_1) * s + y_1' incorporates:
     *  Constant: '<S194>/y_1'
     */
    NLPID_B.y_2y_1sy_1 = NLPID_B.y_2y_1s + NLPID_P.y_1_Value;

    /* Product: '<S178>/p_d1 *a' incorporates:
     *  Constant: '<S114>/Path Selector'
     */
    NLPID_B.p_d1a[0] = NLPID_B.x_2x_1sx_1 * NLPID_P.PathSelector_Value;
    NLPID_B.p_d1a[1] = NLPID_B.y_2y_1sy_1 * NLPID_P.PathSelector_Value;

    /* Product: '<S172>/Product2' incorporates:
     *  Constant: '<S194>/k'
     */
    NLPID_B.Product2_j = NLPID_B.Integrator1 * NLPID_P.k_Value;

    /* Trigonometry: '<S172>/cos(s)' */
    NLPID_B.coss_p = cos(NLPID_B.Product2_j);

    /* Product: '<S172>/Product' incorporates:
     *  Constant: '<S194>/r_x'
     */
    NLPID_B.Product_la = NLPID_P.r_x_Value * NLPID_B.coss_p;

    /* Sum: '<S172>/Add' incorporates:
     *  Constant: '<S194>/origin_x'
     */
    NLPID_B.Add_i = NLPID_B.Product_la + NLPID_P.origin_x_Value;

    /* Trigonometry: '<S172>/sin(s)' */
    NLPID_B.sins_f = sin(NLPID_B.Product2_j);

    /* Product: '<S172>/Product1' incorporates:
     *  Constant: '<S194>/r_y'
     */
    NLPID_B.Product1_f = NLPID_P.r_y_Value * NLPID_B.sins_f;

    /* Sum: '<S172>/Add1' incorporates:
     *  Constant: '<S194>/origo_y'
     */
    NLPID_B.Add1 = NLPID_B.Product1_f + NLPID_P.origo_y_Value;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Sum: '<S178>/1 - a' incorporates:
       *  Constant: '<S114>/Path Selector'
       *  Constant: '<S178>/Constant'
       */
      NLPID_B.a = NLPID_P.Constant_Value_k - NLPID_P.PathSelector_Value;
    }

    /* Product: '<S178>/p_d2 * (1- a )' */
    NLPID_B.p_d21a[0] = NLPID_B.Add_i * NLPID_B.a;
    NLPID_B.p_d21a[1] = NLPID_B.Add1 * NLPID_B.a;

    /* Sum: '<S178>/Add' */
    NLPID_B.Add_m[0] = NLPID_B.p_d1a[0] + NLPID_B.p_d21a[0];
    NLPID_B.Add_m[1] = NLPID_B.p_d1a[1] + NLPID_B.p_d21a[1];

    /* RelationalOperator: '<S187>/LowerRelop1' incorporates:
     *  Constant: '<S171>/x_dmax'
     */
    NLPID_B.LowerRelop1 = (NLPID_B.Add_m[0] > NLPID_P.x_dmax_Value);

    /* RelationalOperator: '<S187>/UpperRelop' incorporates:
     *  Constant: '<S171>/x_dmin'
     */
    NLPID_B.UpperRelop = (NLPID_B.Add_m[0] < NLPID_P.x_dmin_Value);

    /* Switch: '<S187>/Switch' incorporates:
     *  Constant: '<S171>/x_dmin'
     */
    if (NLPID_B.UpperRelop) {
      NLPID_B.Switch = NLPID_P.x_dmin_Value;
    } else {
      NLPID_B.Switch = NLPID_B.Add_m[0];
    }

    /* Switch: '<S187>/Switch2' incorporates:
     *  Constant: '<S171>/x_dmax'
     */
    if (NLPID_B.LowerRelop1) {
      NLPID_B.Switch2 = NLPID_P.x_dmax_Value;
    } else {
      NLPID_B.Switch2 = NLPID_B.Switch;
    }

    /* RelationalOperator: '<S188>/LowerRelop1' incorporates:
     *  Constant: '<S171>/y_dmax'
     */
    NLPID_B.LowerRelop1_l = (NLPID_B.Add_m[1] > NLPID_P.y_dmax_Value);

    /* RelationalOperator: '<S188>/UpperRelop' incorporates:
     *  Constant: '<S171>/y_dmin'
     */
    NLPID_B.UpperRelop_e = (NLPID_B.Add_m[1] < NLPID_P.y_dmin_Value);

    /* Switch: '<S188>/Switch' incorporates:
     *  Constant: '<S171>/y_dmin'
     */
    if (NLPID_B.UpperRelop_e) {
      NLPID_B.Switch_b = NLPID_P.y_dmin_Value;
    } else {
      NLPID_B.Switch_b = NLPID_B.Add_m[1];
    }

    /* Switch: '<S188>/Switch2' incorporates:
     *  Constant: '<S171>/y_dmax'
     */
    if (NLPID_B.LowerRelop1_l) {
      NLPID_B.Switch2_b = NLPID_P.y_dmax_Value;
    } else {
      NLPID_B.Switch2_b = NLPID_B.Switch_b;
    }

    /* Sum: '<S127>/q - p_d' */
    NLPID_B.qp_d[0] = NLPID_B.Integrator[0] - NLPID_B.Switch2;
    NLPID_B.qp_d[1] = NLPID_B.Integrator[1] - NLPID_B.Switch2_b;

    /* Product: '<S127>/epsilon' */
    NLPID_B.epsilon[0] = 0.0;
    NLPID_B.epsilon[0] = NLPID_B.MathFunction_d[0] * NLPID_B.qp_d[0] +
      NLPID_B.epsilon[0];
    NLPID_B.epsilon[0] = NLPID_B.MathFunction_d[2] * NLPID_B.qp_d[1] +
      NLPID_B.epsilon[0];
    NLPID_B.epsilon[1] = 0.0;
    NLPID_B.epsilon[1] = NLPID_B.MathFunction_d[1] * NLPID_B.qp_d[0] +
      NLPID_B.epsilon[1];
    NLPID_B.epsilon[1] = NLPID_B.MathFunction_d[3] * NLPID_B.qp_d[1] +
      NLPID_B.epsilon[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector' */
    {
      const byte_T *u = (byte_T *)NLPID_B.epsilon;/* input port */
      const int32_T *index = (const int32_T *)&NLPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&NLPID_B.MultiportSelector;
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
    }                                  /* end <S127>/Multiport Selector */

    /* Trigonometry: '<S144>/Trigonometric Function' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.TrigonometricFunction_e = rt_atan2_snf(NLPID_B.MultiportSelector,
      NLPID_P.Delta_Value);

    /* Gain: '<S156>/Gain' */
    NLPID_B.Gain_j = NLPID_P.Gain_Gain_p * NLPID_B.TrigonometricFunction_e;

    /* Saturate: '<S151>/Saturation' */
    tmp = NLPID_B.Gain_j;
    NLPID_B.Saturation_n = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat_c,
      NLPID_P.Saturation_UpperSat_c);

    /* Signum: '<S151>/Sign' */
    NLPID_B.Sign_p = rt_SIGNd_snf(NLPID_B.Saturation_n);

    /* Gain: '<S151>/Gain' */
    NLPID_B.Gain_f = NLPID_P.Gain_Gain_m * NLPID_B.Sign_p;

    /* Sum: '<S151>/Sum1' */
    NLPID_B.Sum1_n = NLPID_B.Saturation_n + NLPID_B.Gain_f;

    /* Math: '<S151>/Math Function' incorporates:
     *  Constant: '<S151>/Constant'
     */
    NLPID_B.MathFunction_b = rt_rem_snf(NLPID_B.Sum1_n, NLPID_P.Constant_Value_n);

    /* Sum: '<S151>/Sum' */
    NLPID_B.Sum_g = NLPID_B.MathFunction_b - NLPID_B.Gain_f;

    /* Gain: '<S155>/Gain1' */
    NLPID_B.Gain1_o3 = NLPID_P.Gain1_Gain_h * NLPID_B.Sum_g;

    /* Sum: '<S144>/Subtract' */
    NLPID_B.Subtract_j = NLPID_B.Gain1_f - NLPID_B.Gain1_o3;

    /* Gain: '<S158>/Gain' */
    NLPID_B.Gain_c = NLPID_P.Gain_Gain_jf * NLPID_B.Subtract_j;

    /* Saturate: '<S152>/Saturation' */
    tmp = NLPID_B.Gain_c;
    NLPID_B.Saturation_kb = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat_o,
      NLPID_P.Saturation_UpperSat_og);

    /* Signum: '<S152>/Sign' */
    NLPID_B.Sign_k = rt_SIGNd_snf(NLPID_B.Saturation_kb);

    /* Gain: '<S152>/Gain' */
    NLPID_B.Gain_fb = NLPID_P.Gain_Gain_f * NLPID_B.Sign_k;

    /* Sum: '<S152>/Sum1' */
    NLPID_B.Sum1_i = NLPID_B.Saturation_kb + NLPID_B.Gain_fb;

    /* Math: '<S152>/Math Function' incorporates:
     *  Constant: '<S152>/Constant'
     */
    NLPID_B.MathFunction_a = rt_rem_snf(NLPID_B.Sum1_i, NLPID_P.Constant_Value_h);

    /* Sum: '<S152>/Sum' */
    NLPID_B.Sum_p = NLPID_B.MathFunction_a - NLPID_B.Gain_fb;

    /* Gain: '<S157>/Gain1' */
    NLPID_B.Gain1_d = NLPID_P.Gain1_Gain_i * NLPID_B.Sum_p;

    /* SignalConversion: '<S122>/ConcatBufferAtVector ConcatenateIn2' */
    NLPID_B.VectorConcatenate[2] = NLPID_B.Gain1_d;

    /* Gain: '<S2>/q_x' */
    NLPID_B.q_x = NLPID_P.q_x_Gain * NLPID_B.VectorConcatenate[0];

    /* Gain: '<S2>/q_y' */
    NLPID_B.q_y = NLPID_P.q_y_Gain * NLPID_B.VectorConcatenate[1];

    /* Gain: '<S2>/psi_los' */
    NLPID_B.psi_los = NLPID_P.psi_los_Gain * NLPID_B.VectorConcatenate[2];

    /* Gain: '<S2>/path x_d' */
    NLPID_B.pathx_d = NLPID_P.pathx_d_Gain * NLPID_B.Switch2;

    /* Gain: '<S2>/path y_d' */
    NLPID_B.pathy_d = NLPID_P.pathy_d_Gain * NLPID_B.Switch2_b;

    /* Gain: '<S2>/path psi_d' */
    NLPID_B.pathpsi_d = NLPID_P.pathpsi_d_Gain * NLPID_B.Gain1_o;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S186>/Math Function' */
      NLPID_B.MathFunction_i[0] = NLPID_B.TmpHiddenBufferAtProductInport2[0];
      NLPID_B.MathFunction_i[1] = NLPID_B.TmpHiddenBufferAtProductInport2[1];

      /* Product: '<S185>/Product' */
      tmp = NLPID_B.MathFunction_i[0] * NLPID_B.TmpHiddenBufferAtProductInport2
        [0];
      tmp += NLPID_B.MathFunction_i[1] *
        NLPID_B.TmpHiddenBufferAtProductInport2[1];
      NLPID_B.Product_j = tmp;

      /* Math: '<S185>/sqrt' */
      tmp = NLPID_B.Product_j;
      if (tmp < 0.0) {
        NLPID_B.sqrt_j = -sqrt(-tmp);
      } else {
        NLPID_B.sqrt_j = sqrt(tmp);
      }

      /* Product: '<S182>/Product' incorporates:
       *  Constant: '<S114>/Path Selector'
       */
      NLPID_B.Product_jd = NLPID_B.sqrt_j * NLPID_P.PathSelector_Value;
    }

    /* Math: '<S177>/Math Function' */
    NLPID_B.MathFunction_at[0] = NLPID_B.TmpHiddenBufferAtProductInpor_k[0];
    NLPID_B.MathFunction_at[1] = NLPID_B.TmpHiddenBufferAtProductInpor_k[1];

    /* Product: '<S176>/Product' */
    tmp = NLPID_B.MathFunction_at[0] * NLPID_B.TmpHiddenBufferAtProductInpor_k[0];
    tmp += NLPID_B.MathFunction_at[1] * NLPID_B.TmpHiddenBufferAtProductInpor_k
      [1];
    NLPID_B.Product_o = tmp;

    /* Math: '<S176>/sqrt' */
    tmp = NLPID_B.Product_o;
    if (tmp < 0.0) {
      NLPID_B.sqrt_f = -sqrt(-tmp);
    } else {
      NLPID_B.sqrt_f = sqrt(tmp);
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Sum: '<S182>/Subtract' incorporates:
       *  Constant: '<S114>/Path Selector'
       *  Constant: '<S182>/Constant'
       */
      NLPID_B.Subtract_h = NLPID_P.Constant_Value_p - NLPID_P.PathSelector_Value;
    }

    /* Product: '<S182>/Product1' */
    NLPID_B.Product1_j = NLPID_B.sqrt_f * NLPID_B.Subtract_h;

    /* Sum: '<S182>/Add' */
    NLPID_B.Add_p = NLPID_B.Product_jd + NLPID_B.Product1_j;

    /* Product: '<S189>/Divide' incorporates:
     *  Constant: '<S194>/u_d'
     */
    NLPID_B.Divide = NLPID_P.u_d_Value / NLPID_B.Add_p;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Gain: '<S8>/ScalingLY' incorporates:
       *  Constant: '<S8>/AS_LY'
       */
      NLPID_B.ypositionofleftanalogstick11 = NLPID_P.ScalingLY_Gain *
        NLPID_P.AS_LY_Value;

      /* Gain: '<S9>/PS3 u_1' */
      NLPID_B.u_1 = NLPID_P.PS3u_1_Gain * NLPID_B.ypositionofleftanalogstick11;

      /* Gain: '<S8>/ScalingLX' incorporates:
       *  Constant: '<S8>/AS_LX'
       */
      NLPID_B.xpositionofleftanalogstick11 = NLPID_P.ScalingLX_Gain *
        NLPID_P.AS_LX_Value;

      /* Gain: '<S9>/PS3 u_2' */
      NLPID_B.u_2 = NLPID_P.PS3u_2_Gain * NLPID_B.xpositionofleftanalogstick11;

      /* Gain: '<S8>/ScalingRY' incorporates:
       *  Constant: '<S8>/AS_RY'
       */
      NLPID_B.ypositionofrightanalogstick11 = NLPID_P.ScalingRY_Gain *
        NLPID_P.AS_RY_Value;

      /* Gain: '<S9>/PS3 u_3' */
      NLPID_B.u_3 = NLPID_P.PS3u_3_Gain * NLPID_B.ypositionofrightanalogstick11;

      /* Gain: '<S8>/Scaling_RX' incorporates:
       *  Constant: '<S8>/AS_RX'
       */
      NLPID_B.xpositionofrightanalogstick11 = NLPID_P.Scaling_RX_Gain *
        NLPID_P.AS_RX_Value;

      /* Gain: '<S9>/PS3 u_4' */
      NLPID_B.u_4 = NLPID_P.PS3u_4_Gain * NLPID_B.xpositionofrightanalogstick11;

      /* Sum: '<S9>/Add' incorporates:
       *  Constant: '<S8>/L2'
       *  Constant: '<S8>/R2'
       */
      NLPID_B.BowThrusterdirection = NLPID_P.L2_Value + NLPID_P.R2_Value;

      /* Gain: '<S9>/PS3 u_5' */
      NLPID_B.u_5 = NLPID_P.PS3u_5_Gain * NLPID_B.BowThrusterdirection;

      /* Gain: '<S37>/-l_x1' incorporates:
       *  Constant: '<S37>/l_x1'
       */
      NLPID_B.l_x1 = NLPID_P.l_x1_Gain * NLPID_P.l_x1_Value;

      /* Gain: '<S37>/-l_y2' incorporates:
       *  Constant: '<S37>/l_y2'
       */
      NLPID_B.l_y2 = NLPID_P.l_y2_Gain * NLPID_P.l_y2_Value;

      /* Gain: '<S37>/-l_x2' incorporates:
       *  Constant: '<S37>/l_x2'
       */
      NLPID_B.l_x2 = NLPID_P.l_x2_Gain * NLPID_P.l_x2_Value;

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
      NLPID_B.x5[0] = NLPID_P.T_e11_Value;
      NLPID_B.x5[1] = NLPID_P.T_e21_Value;
      NLPID_B.x5[2] = NLPID_P.l_y1_Value;
      NLPID_B.x5[3] = NLPID_P.T_e12_Value;
      NLPID_B.x5[4] = NLPID_P.T_e22_Value;
      NLPID_B.x5[5] = NLPID_B.l_x1;
      NLPID_B.x5[6] = NLPID_P.T_e13_Value;
      NLPID_B.x5[7] = NLPID_P.T_e23_Value;
      NLPID_B.x5[8] = NLPID_B.l_y2;
      NLPID_B.x5[9] = NLPID_P.T_e14_Value;
      NLPID_B.x5[10] = NLPID_P.T_e24_Value;
      NLPID_B.x5[11] = NLPID_B.l_x2;
      NLPID_B.x5[12] = NLPID_P.T_e15_Value;
      NLPID_B.x5[13] = NLPID_P.T_e25_Value;
      NLPID_B.x5[14] = NLPID_P.l_x3_Value;

      /* S-Function (sdsppinv): '<S16>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&NLPID_DWork.Pseudoinverse_X[0]), (void *)(&NLPID_B.x5[0]),
             15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&NLPID_DWork.Pseudoinverse_X[0], 3, 5,
                      &NLPID_DWork.Pseudoinverse_S[0],
                      &NLPID_DWork.Inverse_DWORK3[0],
                      &NLPID_DWork.Pseudoinverse_WORK[0],
                      &NLPID_DWork.Pseudoinverse_U[0],
                      &NLPID_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&NLPID_DWork.Pseudoinverse_S[0],
          &NLPID_DWork.Pseudoinverse_U[0], &NLPID_DWork.Pseudoinverse_V[0],
          &NLPID_B.Pseudoinverse[0], (const int32_T)3, (const int32_T)5);
      }
    }

    /* Fcn: '<S10>/yaw angle' */
    NLPID_B.psi = NLPID_B.eta_yaw;

    /* Saturate: '<S14>/Saturation' */
    tmp = NLPID_B.psi;
    NLPID_B.Saturation_b = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat_n,
      NLPID_P.Saturation_UpperSat_d);

    /* Signum: '<S14>/Sign' */
    NLPID_B.Sign_g = rt_SIGNd_snf(NLPID_B.Saturation_b);

    /* Gain: '<S14>/Gain' */
    NLPID_B.Gain_gl = NLPID_P.Gain_Gain_i * NLPID_B.Sign_g;

    /* Sum: '<S14>/Sum1' */
    NLPID_B.Sum1_m = NLPID_B.Saturation_b + NLPID_B.Gain_gl;

    /* Math: '<S14>/Math Function' incorporates:
     *  Constant: '<S14>/Constant'
     */
    NLPID_B.MathFunction_al = rt_rem_snf(NLPID_B.Sum1_m,
      NLPID_P.Constant_Value_b);

    /* Sum: '<S14>/Sum' */
    NLPID_B.Sum_a = NLPID_B.MathFunction_al - NLPID_B.Gain_gl;

    /* Sum: '<S10>/Sum2' */
    NLPID_B.regulationerror[0] = NLPID_B.eta_dDPN - NLPID_B.eta_surge;
    NLPID_B.regulationerror[1] = NLPID_B.eta_dDPE - NLPID_B.eta_sway;
    NLPID_B.regulationerror[2] = NLPID_B.eta_dDPPsi - NLPID_B.eta_yaw;

    /* Saturate: '<S13>/Saturation' */
    tmp = NLPID_B.regulationerror[2];
    NLPID_B.Saturation_a = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat_cp,
      NLPID_P.Saturation_UpperSat_j);

    /* Signum: '<S13>/Sign' */
    NLPID_B.Sign_i = rt_SIGNd_snf(NLPID_B.Saturation_a);

    /* Gain: '<S13>/Gain' */
    NLPID_B.Gain_m = NLPID_P.Gain_Gain_g * NLPID_B.Sign_i;

    /* Sum: '<S13>/Sum1' */
    NLPID_B.Sum1_k = NLPID_B.Saturation_a + NLPID_B.Gain_m;

    /* Math: '<S13>/Math Function' incorporates:
     *  Constant: '<S13>/Constant'
     */
    NLPID_B.MathFunction_gf = rt_rem_snf(NLPID_B.Sum1_k,
      NLPID_P.Constant_Value_i);

    /* Sum: '<S13>/Sum' */
    NLPID_B.Sum_m = NLPID_B.MathFunction_gf - NLPID_B.Gain_m;

    /* Fcn: '<S12>/Row1' */
    NLPID_B.Row1 = cos(NLPID_B.Sum_a) * NLPID_B.regulationerror[0] + sin
      (NLPID_B.Sum_a) * NLPID_B.regulationerror[1];

    /* Fcn: '<S12>/Row2' */
    NLPID_B.Row2 = (-sin(NLPID_B.Sum_a)) * NLPID_B.regulationerror[0] + cos
      (NLPID_B.Sum_a) * NLPID_B.regulationerror[1];

    /* Fcn: '<S12>/Row3' */
    NLPID_B.Row3 = NLPID_B.Sum_m;

    /* SignalConversion: '<S10>/TmpHiddenBufferAtKpInport1' */
    NLPID_B.TmpHiddenBufferAtKpInport1[0] = NLPID_B.Row1;
    NLPID_B.TmpHiddenBufferAtKpInport1[1] = NLPID_B.Row2;
    NLPID_B.TmpHiddenBufferAtKpInport1[2] = NLPID_B.Row3;

    /* Gain: '<S10>/Kp' */
    for (i = 0; i < 3; i++) {
      NLPID_B.Kp[i] = 0.0;
      NLPID_B.Kp[i] = NLPID_P.Kp_Gain[i] * NLPID_B.TmpHiddenBufferAtKpInport1[0]
        + NLPID_B.Kp[i];
      NLPID_B.Kp[i] = NLPID_P.Kp_Gain[i + 3] *
        NLPID_B.TmpHiddenBufferAtKpInport1[1] + NLPID_B.Kp[i];
      NLPID_B.Kp[i] = NLPID_P.Kp_Gain[i + 6] *
        NLPID_B.TmpHiddenBufferAtKpInport1[2] + NLPID_B.Kp[i];
    }

    /* Gain: '<S10>/K_p_surge_scale' */
    NLPID_B.K_p_surge_scale = NLPID_P.K_p_surge_scale_Gain * NLPID_B.Kp[0];

    /* Gain: '<S10>/K_p_sway_scale' */
    NLPID_B.K_p_sway_scale = NLPID_P.K_p_sway_scale_Gain * NLPID_B.Kp[1];

    /* Gain: '<S10>/K_p_yaw_scale' */
    NLPID_B.K_p_yaw_scale = NLPID_P.K_p_yaw_scale_Gain * NLPID_B.Kp[2];

    /* Integrator Block: '<S10>/Integrator'
     */
    if (rtmIsMajorTimeStep(NLPID_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &NLPID_PrevZCSigState.Integrator_Reset_ZCE_d,
                         NLPID_P.Reset_DP_integrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || NLPID_P.Reset_DP_integrator_Value != 0.0) {
        NLPID_X.Integrator_CSTATE_m[0] = NLPID_P.Integrator_IC;
        NLPID_X.Integrator_CSTATE_m[1] = NLPID_P.Integrator_IC;
        NLPID_X.Integrator_CSTATE_m[2] = NLPID_P.Integrator_IC;
      }
    }

    NLPID_B.Integrator_f[0] = NLPID_X.Integrator_CSTATE_m[0];
    NLPID_B.Integrator_f[1] = NLPID_X.Integrator_CSTATE_m[1];
    NLPID_B.Integrator_f[2] = NLPID_X.Integrator_CSTATE_m[2];

    /* Gain: '<S10>/Ki' */
    for (i = 0; i < 3; i++) {
      NLPID_B.Ki[i] = 0.0;
      NLPID_B.Ki[i] = NLPID_P.Ki_Gain[i] * NLPID_B.Integrator_f[0] +
        NLPID_B.Ki[i];
      NLPID_B.Ki[i] = NLPID_P.Ki_Gain[i + 3] * NLPID_B.Integrator_f[1] +
        NLPID_B.Ki[i];
      NLPID_B.Ki[i] = NLPID_P.Ki_Gain[i + 6] * NLPID_B.Integrator_f[2] +
        NLPID_B.Ki[i];
    }

    /* Gain: '<S10>/K_i_surge_scale' */
    NLPID_B.K_i_surge_scale = NLPID_P.K_i_surge_scale_Gain * NLPID_B.Ki[0];

    /* Gain: '<S10>/K_i_sway_scale' */
    NLPID_B.K_i_sway_scale = NLPID_P.K_i_sway_scale_Gain * NLPID_B.Ki[1];

    /* Gain: '<S10>/K_i_yaw_scale' */
    NLPID_B.K_i_yaw_scale = NLPID_P.K_i_yaw_scale_Gain * NLPID_B.Ki[2];

    /* Sum: '<S10>/Sum3' */
    NLPID_B.Sum3[0] = NLPID_B.K_p_surge_scale + NLPID_B.K_i_surge_scale;
    NLPID_B.Sum3[1] = NLPID_B.K_p_sway_scale + NLPID_B.K_i_sway_scale;
    NLPID_B.Sum3[2] = NLPID_B.K_p_yaw_scale + NLPID_B.K_i_yaw_scale;

    /* SignalConversion: '<S10>/TmpHiddenBufferAtKdInport1' */
    NLPID_B.TmpHiddenBufferAtKdInport1[0] = NLPID_B.nu_surge;
    NLPID_B.TmpHiddenBufferAtKdInport1[1] = NLPID_B.nu_sway;
    NLPID_B.TmpHiddenBufferAtKdInport1[2] = NLPID_B.nu_yaw;

    /* Gain: '<S10>/Kd' */
    for (i = 0; i < 3; i++) {
      NLPID_B.Kd[i] = 0.0;
      NLPID_B.Kd[i] = NLPID_P.Kd_Gain[i] * NLPID_B.TmpHiddenBufferAtKdInport1[0]
        + NLPID_B.Kd[i];
      NLPID_B.Kd[i] = NLPID_P.Kd_Gain[i + 3] *
        NLPID_B.TmpHiddenBufferAtKdInport1[1] + NLPID_B.Kd[i];
      NLPID_B.Kd[i] = NLPID_P.Kd_Gain[i + 6] *
        NLPID_B.TmpHiddenBufferAtKdInport1[2] + NLPID_B.Kd[i];
    }

    /* Gain: '<S10>/K_d_surge_scale' */
    NLPID_B.K_d_surge_scale = NLPID_P.K_d_surge_scale_Gain * NLPID_B.Kd[0];

    /* Gain: '<S10>/K_d_sway_scale' */
    NLPID_B.K_d_sway_scale = NLPID_P.K_d_sway_scale_Gain * NLPID_B.Kd[1];

    /* Gain: '<S10>/K_d_yaw_scale' */
    NLPID_B.K_d_yaw_scale = NLPID_P.K_d_yaw_scale_Gain * NLPID_B.Kd[2];

    /* Sum: '<S10>/Sum1' */
    NLPID_B.Sum1_p[0] = NLPID_B.Sum3[0] - NLPID_B.K_d_surge_scale;
    NLPID_B.Sum1_p[1] = NLPID_B.Sum3[1] - NLPID_B.K_d_sway_scale;
    NLPID_B.Sum1_p[2] = NLPID_B.Sum3[2] - NLPID_B.K_d_yaw_scale;

    /* Product: '<S16>/Product' */
    for (i = 0; i < 5; i++) {
      NLPID_B.Product_n[i] = 0.0;
      NLPID_B.Product_n[i] = NLPID_B.Pseudoinverse[i] * NLPID_B.Sum1_p[0] +
        NLPID_B.Product_n[i];
      NLPID_B.Product_n[i] = NLPID_B.Pseudoinverse[i + 5] * NLPID_B.Sum1_p[1] +
        NLPID_B.Product_n[i];
      NLPID_B.Product_n[i] = NLPID_B.Pseudoinverse[i + 10] * NLPID_B.Sum1_p[2] +
        NLPID_B.Product_n[i];
    }

    /* DeadZone Block: '<S17>/Dead Zone'
     */
    if (NLPID_B.Product_n[0] >= NLPID_P.DeadZone_End) {
      NLPID_B.DeadZone = NLPID_B.Product_n[0] - NLPID_P.DeadZone_End;
    } else if (NLPID_B.Product_n[0] > NLPID_P.DeadZone_Start) {
      NLPID_B.DeadZone = 0.0;
    } else {
      NLPID_B.DeadZone = NLPID_B.Product_n[0] - NLPID_P.DeadZone_Start;
    }

    /* RelationalOperator: '<S22>/Compare' incorporates:
     *  Constant: '<S22>/Constant'
     */
    NLPID_B.Compare = (NLPID_B.DeadZone < NLPID_P.Constant_Value_kk);

    /* RelationalOperator: '<S24>/Compare' */
    NLPID_B.Compare_m = (NLPID_B.DeadZone == 0.0);

    /* Gain: '<S17>/Gain' */
    NLPID_B.Gain_fm = (uint16_T)(NLPID_P.Gain_Gain_k1 * NLPID_B.Compare_m);

    /* RelationalOperator: '<S23>/Compare' incorporates:
     *  Constant: '<S23>/Constant'
     */
    NLPID_B.Compare_i = (NLPID_B.DeadZone > NLPID_P.Constant_Value_j);

    /* Gain: '<S17>/Gain1' */
    NLPID_B.Gain1_ce = (uint16_T)(NLPID_P.Gain1_Gain_b * NLPID_B.Compare_i);

    /* Sum: '<S17>/Sum' */
    NLPID_B.Sum_i = (uint16_T)(uint32_T)(((NLPID_B.Compare << 6) +
      NLPID_B.Gain_fm) + NLPID_B.Gain1_ce);

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
    LookUp_real_T_real_T( &(NLPID_B.f_10), NLPID_P.f_10_YData,
                         NLPID_B.Product_n[0], NLPID_P.f_10_XData, 8U);

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
    LookUp_real_T_real_T( &(NLPID_B.f_10_l), NLPID_P.f_10_YData_j,
                         NLPID_B.Product_n[0], NLPID_P.f_10_XData_f, 9U);

    /* MultiPortSwitch: '<S17>/Multiport Switch' incorporates:
     *  Constant: '<S17>/f_1 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_i >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch = NLPID_B.f_10;
      break;

     case 2:
      NLPID_B.MultiportSwitch = NLPID_P.f_10_Value;
      break;

     default:
      NLPID_B.MultiportSwitch = NLPID_B.f_10_l;
      break;
    }

    /* DeadZone Block: '<S18>/Dead Zone'
     */
    if (NLPID_B.Product_n[1] >= NLPID_P.DeadZone_End_o) {
      NLPID_B.DeadZone_l = NLPID_B.Product_n[1] - NLPID_P.DeadZone_End_o;
    } else if (NLPID_B.Product_n[1] > NLPID_P.DeadZone_Start_f) {
      NLPID_B.DeadZone_l = 0.0;
    } else {
      NLPID_B.DeadZone_l = NLPID_B.Product_n[1] - NLPID_P.DeadZone_Start_f;
    }

    /* RelationalOperator: '<S25>/Compare' incorporates:
     *  Constant: '<S25>/Constant'
     */
    NLPID_B.Compare_b = (NLPID_B.DeadZone_l < NLPID_P.Constant_Value_l);

    /* RelationalOperator: '<S26>/Compare' incorporates:
     *  Constant: '<S26>/Constant'
     */
    NLPID_B.Compare_g = (NLPID_B.DeadZone_l == NLPID_P.Constant_Value_l4);

    /* Gain: '<S18>/Gain' */
    NLPID_B.Gain_o = (uint16_T)(NLPID_P.Gain_Gain_g0p * NLPID_B.Compare_g);

    /* RelationalOperator: '<S27>/Compare' incorporates:
     *  Constant: '<S27>/Constant'
     */
    NLPID_B.Compare_mz = (NLPID_B.DeadZone_l > NLPID_P.Constant_Value_f);

    /* Gain: '<S18>/Gain1' */
    NLPID_B.Gain1_e = (uint16_T)(NLPID_P.Gain1_Gain_cz * NLPID_B.Compare_mz);

    /* Sum: '<S18>/Sum' */
    NLPID_B.Sum_k = (uint16_T)(uint32_T)(((NLPID_B.Compare_b << 6) +
      NLPID_B.Gain_o) + NLPID_B.Gain1_e);

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
    LookUp_real_T_real_T( &(NLPID_B.f_20), NLPID_P.f_20_YData,
                         NLPID_B.Product_n[1], NLPID_P.f_20_XData, 10U);

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
    LookUp_real_T_real_T( &(NLPID_B.f_20_h), NLPID_P.f_20_YData_n,
                         NLPID_B.Product_n[1], NLPID_P.f_20_XData_o, 9U);

    /* MultiPortSwitch: '<S18>/Multiport Switch' incorporates:
     *  Constant: '<S18>/f_2 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_k >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch_o = NLPID_B.f_20;
      break;

     case 2:
      NLPID_B.MultiportSwitch_o = NLPID_P.f_20_Value;
      break;

     default:
      NLPID_B.MultiportSwitch_o = NLPID_B.f_20_h;
      break;
    }

    /* DeadZone Block: '<S19>/Dead Zone'
     */
    if (NLPID_B.Product_n[2] >= NLPID_P.DeadZone_End_c) {
      NLPID_B.DeadZone_i = NLPID_B.Product_n[2] - NLPID_P.DeadZone_End_c;
    } else if (NLPID_B.Product_n[2] > NLPID_P.DeadZone_Start_fx) {
      NLPID_B.DeadZone_i = 0.0;
    } else {
      NLPID_B.DeadZone_i = NLPID_B.Product_n[2] - NLPID_P.DeadZone_Start_fx;
    }

    /* RelationalOperator: '<S28>/Compare' incorporates:
     *  Constant: '<S28>/Constant'
     */
    NLPID_B.Compare_gm = (NLPID_B.DeadZone_i < NLPID_P.Constant_Value_cr);

    /* RelationalOperator: '<S30>/Compare' */
    NLPID_B.Compare_l = (NLPID_B.DeadZone_i == 0.0);

    /* Gain: '<S19>/Gain' */
    NLPID_B.Gain_d = (uint16_T)(NLPID_P.Gain_Gain_bp * NLPID_B.Compare_l);

    /* RelationalOperator: '<S29>/Compare' incorporates:
     *  Constant: '<S29>/Constant'
     */
    NLPID_B.Compare_bs = (NLPID_B.DeadZone_i > NLPID_P.Constant_Value_n2);

    /* Gain: '<S19>/Gain1' */
    NLPID_B.Gain1_fx = (uint16_T)(NLPID_P.Gain1_Gain_k * NLPID_B.Compare_bs);

    /* Sum: '<S19>/Sum' */
    NLPID_B.Sum_mf = (uint16_T)(uint32_T)(((NLPID_B.Compare_gm << 6) +
      NLPID_B.Gain_d) + NLPID_B.Gain1_fx);

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
    LookUp_real_T_real_T( &(NLPID_B.f_30), NLPID_P.f_30_YData,
                         NLPID_B.Product_n[2], NLPID_P.f_30_XData, 7U);

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
    LookUp_real_T_real_T( &(NLPID_B.f_30_i), NLPID_P.f_30_YData_k,
                         NLPID_B.Product_n[2], NLPID_P.f_30_XData_d, 10U);

    /* MultiPortSwitch: '<S19>/Multiport Switch' incorporates:
     *  Constant: '<S19>/f_3 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_mf >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch_n = NLPID_B.f_30;
      break;

     case 2:
      NLPID_B.MultiportSwitch_n = NLPID_P.f_30_Value;
      break;

     default:
      NLPID_B.MultiportSwitch_n = NLPID_B.f_30_i;
      break;
    }

    /* DeadZone Block: '<S20>/Dead Zone'
     */
    if (NLPID_B.Product_n[3] >= NLPID_P.DeadZone_End_e) {
      NLPID_B.DeadZone_ly = NLPID_B.Product_n[3] - NLPID_P.DeadZone_End_e;
    } else if (NLPID_B.Product_n[3] > NLPID_P.DeadZone_Start_i) {
      NLPID_B.DeadZone_ly = 0.0;
    } else {
      NLPID_B.DeadZone_ly = NLPID_B.Product_n[3] - NLPID_P.DeadZone_Start_i;
    }

    /* RelationalOperator: '<S31>/Compare' incorporates:
     *  Constant: '<S31>/Constant'
     */
    NLPID_B.Compare_j = (NLPID_B.DeadZone_ly < NLPID_P.Constant_Value_fy);

    /* RelationalOperator: '<S33>/Compare' */
    NLPID_B.Compare_je = (NLPID_B.DeadZone_ly == 0.0);

    /* Gain: '<S20>/Gain' */
    NLPID_B.Gain_n = (uint16_T)(NLPID_P.Gain_Gain_ef * NLPID_B.Compare_je);

    /* RelationalOperator: '<S32>/Compare' incorporates:
     *  Constant: '<S32>/Constant'
     */
    NLPID_B.Compare_h = (NLPID_B.DeadZone_ly > NLPID_P.Constant_Value_m);

    /* Gain: '<S20>/Gain1' */
    NLPID_B.Gain1_i = (uint16_T)(NLPID_P.Gain1_Gain_o * NLPID_B.Compare_h);

    /* Sum: '<S20>/Sum' */
    NLPID_B.Sum_it = (uint16_T)(uint32_T)(((NLPID_B.Compare_j << 6) +
      NLPID_B.Gain_n) + NLPID_B.Gain1_i);

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
    LookUp_real_T_real_T( &(NLPID_B.f_40), NLPID_P.f_40_YData,
                         NLPID_B.Product_n[3], NLPID_P.f_40_XData, 9U);

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
    LookUp_real_T_real_T( &(NLPID_B.f_40_f), NLPID_P.f_40_YData_i,
                         NLPID_B.Product_n[3], NLPID_P.f_40_XData_l, 6U);

    /* MultiPortSwitch: '<S20>/Multiport Switch' incorporates:
     *  Constant: '<S20>/f_4 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_it >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch_o0 = NLPID_B.f_40;
      break;

     case 2:
      NLPID_B.MultiportSwitch_o0 = NLPID_P.f_40_Value;
      break;

     default:
      NLPID_B.MultiportSwitch_o0 = NLPID_B.f_40_f;
      break;
    }

    /* DeadZone Block: '<S21>/Dead Zone'
     */
    if (NLPID_B.Product_n[4] >= NLPID_P.DeadZone_End_m) {
      NLPID_B.DeadZone_g = NLPID_B.Product_n[4] - NLPID_P.DeadZone_End_m;
    } else if (NLPID_B.Product_n[4] > NLPID_P.DeadZone_Start_l) {
      NLPID_B.DeadZone_g = 0.0;
    } else {
      NLPID_B.DeadZone_g = NLPID_B.Product_n[4] - NLPID_P.DeadZone_Start_l;
    }

    /* RelationalOperator: '<S34>/Compare' incorporates:
     *  Constant: '<S34>/Constant'
     */
    NLPID_B.Compare_l3 = (NLPID_B.DeadZone_g < NLPID_P.Constant_Value_g);

    /* RelationalOperator: '<S36>/Compare' */
    NLPID_B.Compare_m1 = (NLPID_B.DeadZone_g == 0.0);

    /* Gain: '<S21>/Gain' */
    NLPID_B.Gain_fd = (uint16_T)(NLPID_P.Gain_Gain_g3 * NLPID_B.Compare_m1);

    /* RelationalOperator: '<S35>/Compare' incorporates:
     *  Constant: '<S35>/Constant'
     */
    NLPID_B.Compare_d = (NLPID_B.DeadZone_g > NLPID_P.Constant_Value_d);

    /* Gain: '<S21>/Gain1' */
    NLPID_B.Gain1_n = (uint16_T)(NLPID_P.Gain1_Gain_l * NLPID_B.Compare_d);

    /* Sum: '<S21>/Sum' */
    NLPID_B.Sum_e1 = (uint16_T)(uint32_T)(((NLPID_B.Compare_l3 << 6) +
      NLPID_B.Gain_fd) + NLPID_B.Gain1_n);

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
    LookUp_real_T_real_T( &(NLPID_B.f_50), NLPID_P.f_50_YData,
                         NLPID_B.Product_n[4], NLPID_P.f_50_XData, 2U);

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
    LookUp_real_T_real_T( &(NLPID_B.f_50_o), NLPID_P.f_50_YData_a,
                         NLPID_B.Product_n[4], NLPID_P.f_50_XData_d, 2U);

    /* MultiPortSwitch: '<S21>/Multiport Switch' incorporates:
     *  Constant: '<S21>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_e1 >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch_ng = NLPID_B.f_50;
      break;

     case 2:
      NLPID_B.MultiportSwitch_ng = NLPID_P.f_50_Value;
      break;

     default:
      NLPID_B.MultiportSwitch_ng = NLPID_B.f_50_o;
      break;
    }

    /* Saturate: '<S6>/Saturation' */
    tmp_0[0] = NLPID_B.MultiportSwitch;
    tmp_0[1] = NLPID_B.MultiportSwitch_o;
    tmp_0[2] = NLPID_B.MultiportSwitch_n;
    tmp_0[3] = NLPID_B.MultiportSwitch_o0;
    tmp_0[4] = NLPID_B.MultiportSwitch_ng;
    for (i = 0; i < 5; i++) {
      NLPID_B.Saturation_kt[i] = rt_SATURATE(tmp_0[i],
        NLPID_P.Saturation_LowerSat_b, NLPID_P.Saturation_UpperSat_l);
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Gain: '<S100>/-l_x1' incorporates:
       *  Constant: '<S100>/l_x1'
       */
      NLPID_B.l_x1_l = NLPID_P.l_x1_Gain_j * NLPID_P.l_x1_Value_n;

      /* Gain: '<S100>/-l_y2' incorporates:
       *  Constant: '<S100>/l_y2'
       */
      NLPID_B.l_y2_m = NLPID_P.l_y2_Gain_e * NLPID_P.l_y2_Value_n;

      /* Gain: '<S100>/-l_x2' incorporates:
       *  Constant: '<S100>/l_x2'
       */
      NLPID_B.l_x2_p = NLPID_P.l_x2_Gain_p * NLPID_P.l_x2_Value_c;

      /* Reshape: '<S100>/3x5' incorporates:
       *  Constant: '<S100>/T_e11'
       *  Constant: '<S100>/T_e12'
       *  Constant: '<S100>/T_e13'
       *  Constant: '<S100>/T_e14'
       *  Constant: '<S100>/T_e15'
       *  Constant: '<S100>/T_e21'
       *  Constant: '<S100>/T_e22'
       *  Constant: '<S100>/T_e23'
       *  Constant: '<S100>/T_e24'
       *  Constant: '<S100>/T_e25'
       *  Constant: '<S100>/l_x3'
       *  Constant: '<S100>/l_y1'
       */
      NLPID_B.x5_n[0] = NLPID_P.T_e11_Value_o;
      NLPID_B.x5_n[1] = NLPID_P.T_e21_Value_a;
      NLPID_B.x5_n[2] = NLPID_P.l_y1_Value_b;
      NLPID_B.x5_n[3] = NLPID_P.T_e12_Value_h;
      NLPID_B.x5_n[4] = NLPID_P.T_e22_Value_m;
      NLPID_B.x5_n[5] = NLPID_B.l_x1_l;
      NLPID_B.x5_n[6] = NLPID_P.T_e13_Value_a;
      NLPID_B.x5_n[7] = NLPID_P.T_e23_Value_o;
      NLPID_B.x5_n[8] = NLPID_B.l_y2_m;
      NLPID_B.x5_n[9] = NLPID_P.T_e14_Value_m;
      NLPID_B.x5_n[10] = NLPID_P.T_e24_Value_b;
      NLPID_B.x5_n[11] = NLPID_B.l_x2_p;
      NLPID_B.x5_n[12] = NLPID_P.T_e15_Value_o;
      NLPID_B.x5_n[13] = NLPID_P.T_e25_Value_b;
      NLPID_B.x5_n[14] = NLPID_P.l_x3_Value_i;

      /* S-Function (sdsppinv): '<S79>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&NLPID_DWork.Pseudoinverse_X[0]), (void *)(&NLPID_B.x5_n[0]),
             15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&NLPID_DWork.Pseudoinverse_X[0], 3, 5,
                      &NLPID_DWork.Pseudoinverse_S[0],
                      &NLPID_DWork.Inverse_DWORK3[0],
                      &NLPID_DWork.Pseudoinverse_WORK[0],
                      &NLPID_DWork.Pseudoinverse_U[0],
                      &NLPID_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&NLPID_DWork.Pseudoinverse_S[0],
          &NLPID_DWork.Pseudoinverse_U[0], &NLPID_DWork.Pseudoinverse_V[0],
          &NLPID_B.Pseudoinverse_c[0], (const int32_T)3, (const int32_T)5);
      }
    }

    /* Fcn: '<S47>/R11' */
    NLPID_B.R11_a = cos(NLPID_B.eta_yaw);

    /* Fcn: '<S47>/R21' */
    NLPID_B.R21_n = sin(NLPID_B.eta_yaw);

    /* Fcn: '<S47>/R12' */
    NLPID_B.R12_c = -1.0 * sin(NLPID_B.eta_yaw);

    /* Fcn: '<S47>/R22' */
    NLPID_B.R22_l = cos(NLPID_B.eta_yaw);

    /* Reshape: '<S47>/R(psi)' incorporates:
     *  Constant: '<S47>/R13'
     *  Constant: '<S47>/R23'
     *  Constant: '<S47>/R31'
     *  Constant: '<S47>/R32'
     *  Constant: '<S47>/R33'
     */
    NLPID_B.Rpsi[0] = NLPID_B.R11_a;
    NLPID_B.Rpsi[1] = NLPID_B.R21_n;
    NLPID_B.Rpsi[2] = NLPID_P.R31_Value;
    NLPID_B.Rpsi[3] = NLPID_B.R12_c;
    NLPID_B.Rpsi[4] = NLPID_B.R22_l;
    NLPID_B.Rpsi[5] = NLPID_P.R32_Value;
    NLPID_B.Rpsi[6] = NLPID_P.R13_Value;
    NLPID_B.Rpsi[7] = NLPID_P.R23_Value;
    NLPID_B.Rpsi[8] = NLPID_P.R33_Value;

    /* Math: '<S48>/Math Function' */
    for (i = 0; i < 3; i++) {
      NLPID_B.MathFunction_l[3 * i] = NLPID_B.Rpsi[i];
      NLPID_B.MathFunction_l[1 + 3 * i] = NLPID_B.Rpsi[i + 3];
      NLPID_B.MathFunction_l[2 + 3 * i] = NLPID_B.Rpsi[i + 6];
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Reshape: '<S46>/R(psi)' incorporates:
       *  Constant: '<S46>/12'
       *  Constant: '<S46>/13'
       *  Constant: '<S46>/21'
       *  Constant: '<S46>/23'
       *  Constant: '<S46>/31'
       *  Constant: '<S46>/32'
       *  Constant: '<S7>/K_p_Surge'
       *  Constant: '<S7>/K_p_Sway'
       *  Constant: '<S7>/K_p_Yaw'
       */
      NLPID_B.Rpsi_b[0] = NLPID_P.K_p_Surge_Value;
      NLPID_B.Rpsi_b[1] = NLPID_P.u_Value;
      NLPID_B.Rpsi_b[2] = NLPID_P.u_Value_k;
      NLPID_B.Rpsi_b[3] = NLPID_P.u_Value_e;
      NLPID_B.Rpsi_b[4] = NLPID_P.K_p_Sway_Value;
      NLPID_B.Rpsi_b[5] = NLPID_P.u_Value_a;
      NLPID_B.Rpsi_b[6] = NLPID_P.u_Value_c;
      NLPID_B.Rpsi_b[7] = NLPID_P.u_Value_eh;
      NLPID_B.Rpsi_b[8] = NLPID_P.K_p_Yaw_Value;
    }

    /* Gain: '<S74>/Gain' */
    NLPID_B.Gain_p = NLPID_P.Gain_Gain_c * NLPID_B.eta_yaw;

    /* Saturate: '<S72>/Saturation' */
    tmp = NLPID_B.Gain_p;
    NLPID_B.Saturation_bi = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat_l,
      NLPID_P.Saturation_UpperSat_dr);

    /* Signum: '<S72>/Sign' */
    NLPID_B.Sign_h = rt_SIGNd_snf(NLPID_B.Saturation_bi);

    /* Gain: '<S72>/Gain' */
    NLPID_B.Gain_hl = NLPID_P.Gain_Gain_fq * NLPID_B.Sign_h;

    /* Sum: '<S72>/Sum1' */
    NLPID_B.Sum1_iw = NLPID_B.Saturation_bi + NLPID_B.Gain_hl;

    /* Math: '<S72>/Math Function' incorporates:
     *  Constant: '<S72>/Constant'
     */
    NLPID_B.MathFunction_be = rt_rem_snf(NLPID_B.Sum1_iw,
      NLPID_P.Constant_Value_fc);

    /* Sum: '<S72>/Sum' */
    NLPID_B.Sum_l = NLPID_B.MathFunction_be - NLPID_B.Gain_hl;

    /* Gain: '<S73>/Gain1' */
    NLPID_B.Gain1_oh = NLPID_P.Gain1_Gain_i5 * NLPID_B.Sum_l;

    /* Sum: '<S41>/Subtract' */
    NLPID_B.Subtract_k[0] = NLPID_B.eta_surge - NLPID_B.q_x;
    NLPID_B.Subtract_k[1] = NLPID_B.eta_sway - NLPID_B.q_y;
    NLPID_B.Subtract_k[2] = NLPID_B.Gain1_oh - NLPID_B.psi_los;

    /* Gain: '<S77>/Gain' */
    NLPID_B.Gain_gi = NLPID_P.Gain_Gain_f0 * NLPID_B.Subtract_k[2];

    /* Saturate: '<S75>/Saturation' */
    tmp = NLPID_B.Gain_gi;
    NLPID_B.Saturation_kg = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat_nw,
      NLPID_P.Saturation_UpperSat_d1);

    /* Signum: '<S75>/Sign' */
    NLPID_B.Sign_ge = rt_SIGNd_snf(NLPID_B.Saturation_kg);

    /* Gain: '<S75>/Gain' */
    NLPID_B.Gain_e = NLPID_P.Gain_Gain_l * NLPID_B.Sign_ge;

    /* Sum: '<S75>/Sum1' */
    NLPID_B.Sum1_a = NLPID_B.Saturation_kg + NLPID_B.Gain_e;

    /* Math: '<S75>/Math Function' incorporates:
     *  Constant: '<S75>/Constant'
     */
    NLPID_B.MathFunction_e = rt_rem_snf(NLPID_B.Sum1_a,
      NLPID_P.Constant_Value_dk);

    /* Sum: '<S75>/Sum' */
    NLPID_B.Sum_f = NLPID_B.MathFunction_e - NLPID_B.Gain_e;

    /* Gain: '<S76>/Gain1' */
    NLPID_B.Gain1_b = NLPID_P.Gain1_Gain_a * NLPID_B.Sum_f;

    /* SignalConversion: '<S67>/TmpHiddenBufferAtProductInport3' */
    NLPID_B.TmpHiddenBufferAtProductInport3[0] = NLPID_B.Subtract_k[0];
    NLPID_B.TmpHiddenBufferAtProductInport3[1] = NLPID_B.Subtract_k[1];
    NLPID_B.TmpHiddenBufferAtProductInport3[2] = NLPID_B.Gain1_b;

    /* Product: '<S67>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + NLPID_B.Rpsi_b[3 * tmp_6] *
          NLPID_B.MathFunction_l[i];
        tmp_2[i + 3 * tmp_6] = NLPID_B.Rpsi_b[3 * tmp_6 + 1] *
          NLPID_B.MathFunction_l[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = NLPID_B.Rpsi_b[3 * tmp_6 + 2] *
          NLPID_B.MathFunction_l[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      NLPID_B.Product_bj[i] = 0.0;
      NLPID_B.Product_bj[i] = tmp_2[i] *
        NLPID_B.TmpHiddenBufferAtProductInport3[0] + NLPID_B.Product_bj[i];
      NLPID_B.Product_bj[i] = tmp_2[i + 3] *
        NLPID_B.TmpHiddenBufferAtProductInport3[1] + NLPID_B.Product_bj[i];
      NLPID_B.Product_bj[i] = tmp_2[i + 6] *
        NLPID_B.TmpHiddenBufferAtProductInport3[2] + NLPID_B.Product_bj[i];
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Reshape: '<S45>/R(psi)' incorporates:
       *  Constant: '<S45>/12'
       *  Constant: '<S45>/13'
       *  Constant: '<S45>/21'
       *  Constant: '<S45>/23'
       *  Constant: '<S45>/31'
       *  Constant: '<S45>/32'
       *  Constant: '<S7>/K_i_Surge'
       *  Constant: '<S7>/K_i_Sway'
       *  Constant: '<S7>/K_i_Yaw'
       */
      NLPID_B.Rpsi_m[0] = NLPID_P.K_i_Surge_Value;
      NLPID_B.Rpsi_m[1] = NLPID_P.u_Value_n;
      NLPID_B.Rpsi_m[2] = NLPID_P.u_Value_l;
      NLPID_B.Rpsi_m[3] = NLPID_P.u_Value_i;
      NLPID_B.Rpsi_m[4] = NLPID_P.K_i_Sway_Value;
      NLPID_B.Rpsi_m[5] = NLPID_P.u_Value_d;
      NLPID_B.Rpsi_m[6] = NLPID_P.u_Value_kc;
      NLPID_B.Rpsi_m[7] = NLPID_P.u_Value_f;
      NLPID_B.Rpsi_m[8] = NLPID_P.K_i_Yaw_Value;
    }

    /* Integrator: '<S7>/zeta' */
    NLPID_B.zeta[0] = NLPID_X.zeta_CSTATE[0];
    NLPID_B.zeta[1] = NLPID_X.zeta_CSTATE[1];
    NLPID_B.zeta[2] = NLPID_X.zeta_CSTATE[2];

    /* Product: '<S67>/Product1' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + NLPID_B.Rpsi_m[3 * tmp_6] *
          NLPID_B.MathFunction_l[i];
        tmp_2[i + 3 * tmp_6] = NLPID_B.Rpsi_m[3 * tmp_6 + 1] *
          NLPID_B.MathFunction_l[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = NLPID_B.Rpsi_m[3 * tmp_6 + 2] *
          NLPID_B.MathFunction_l[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      NLPID_B.Product1_o[i] = 0.0;
      NLPID_B.Product1_o[i] = tmp_2[i] * NLPID_B.zeta[0] + NLPID_B.Product1_o[i];
      NLPID_B.Product1_o[i] = tmp_2[i + 3] * NLPID_B.zeta[1] +
        NLPID_B.Product1_o[i];
      NLPID_B.Product1_o[i] = tmp_2[i + 6] * NLPID_B.zeta[2] +
        NLPID_B.Product1_o[i];
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Reshape: '<S44>/R(psi)' incorporates:
       *  Constant: '<S44>/12'
       *  Constant: '<S44>/13'
       *  Constant: '<S44>/21'
       *  Constant: '<S44>/23'
       *  Constant: '<S44>/31'
       *  Constant: '<S44>/32'
       *  Constant: '<S7>/K_d_Surge'
       *  Constant: '<S7>/K_d_Sway'
       *  Constant: '<S7>/K_d_Yaw'
       */
      NLPID_B.Rpsi_k[0] = NLPID_P.K_d_Surge_Value;
      NLPID_B.Rpsi_k[1] = NLPID_P.u_Value_j;
      NLPID_B.Rpsi_k[2] = NLPID_P.u_Value_aw;
      NLPID_B.Rpsi_k[3] = NLPID_P.u_Value_l1;
      NLPID_B.Rpsi_k[4] = NLPID_P.K_d_Sway_Value;
      NLPID_B.Rpsi_k[5] = NLPID_P.u_Value_b;
      NLPID_B.Rpsi_k[6] = NLPID_P.u_Value_ju;
      NLPID_B.Rpsi_k[7] = NLPID_P.u_Value_eq;
      NLPID_B.Rpsi_k[8] = NLPID_P.K_d_Yaw_Value;
    }

    /* Trigonometry: '<S129>/f_qx' */
    NLPID_B.f_qx = cos(NLPID_B.Gain1_d);

    /* Trigonometry: '<S129>/f_qy' */
    NLPID_B.f_qy = sin(NLPID_B.Gain1_d);

    /* SignalConversion: '<S129>/TmpHiddenBufferAtProductInport1' */
    NLPID_B.TmpHiddenBufferAtProductInport1[0] = NLPID_B.f_qx;
    NLPID_B.TmpHiddenBufferAtProductInport1[1] = NLPID_B.f_qy;

    /* Product: '<S129>/Product' incorporates:
     *  Constant: '<S194>/u_d'
     */
    NLPID_B.Product_p[0] = NLPID_B.TmpHiddenBufferAtProductInport1[0] *
      NLPID_P.u_d_Value;
    NLPID_B.Product_p[1] = NLPID_B.TmpHiddenBufferAtProductInport1[1] *
      NLPID_P.u_d_Value;

    /* SignalConversion: '<S54>/ConcatBufferAtVector ConcatenateIn1' */
    NLPID_B.VectorConcatenate_a[0] = NLPID_B.Product_p[0];
    NLPID_B.VectorConcatenate_a[1] = NLPID_B.Product_p[1];
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S145>/Delta^2' incorporates:
       *  Constant: '<S111>/Delta'
       */
      tmp = NLPID_P.Delta_Value;
      NLPID_B.Delta2 = tmp * tmp;
    }

    /* Math: '<S145>/epsilon_n^2' */
    tmp = NLPID_B.MultiportSelector;
    NLPID_B.epsilon_n2 = tmp * tmp;

    /* Sum: '<S145>/Add' */
    NLPID_B.Add_f = NLPID_B.Delta2 + NLPID_B.epsilon_n2;

    /* Product: '<S145>/Divide' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Divide_b = NLPID_P.Delta_Value / NLPID_B.Add_f;

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector1' */
    {
      const byte_T *u = (byte_T *)NLPID_B.MathFunction_d;/* input port */
      const int32_T *index = (const int32_T *)&NLPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)NLPID_B.MultiportSelector1;
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
    }                                  /* end <S127>/Multiport Selector1 */

    /* Product: '<S145>/Product' */
    NLPID_B.Product_f[0] = NLPID_B.Divide_b * NLPID_B.MultiportSelector1[0];

    /* Gain: '<S145>/-1' */
    NLPID_B.u[0] = NLPID_P.u_Gain * NLPID_B.Product_f[0];

    /* Product: '<S145>/Product' */
    NLPID_B.Product_f[1] = NLPID_B.Divide_b * NLPID_B.MultiportSelector1[1];

    /* Gain: '<S145>/-1' */
    NLPID_B.u[1] = NLPID_P.u_Gain * NLPID_B.Product_f[1];

    /* Product: '<S54>/Product' */
    tmp = NLPID_B.u[0] * NLPID_B.Product_p[0];
    tmp += NLPID_B.u[1] * NLPID_B.Product_p[1];
    NLPID_B.VectorConcatenate_a[2] = tmp;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Constant: '<S60>/0_2x1' */
      NLPID_B.VectorConcatenate_m[0] = NLPID_P._2x1_Value[0];
      NLPID_B.VectorConcatenate_m[1] = NLPID_P._2x1_Value[1];

      /* Product: '<S181>/Product' incorporates:
       *  Constant: '<S114>/Path Selector'
       *  Constant: '<S170>/0_2x1'
       */
      NLPID_B.Product_m[0] = NLPID_P._2x1_Value_c * NLPID_P.PathSelector_Value;
      NLPID_B.Product_m[1] = NLPID_P._2x1_Value_c * NLPID_P.PathSelector_Value;
    }

    /* Product: '<S175>/Product2' incorporates:
     *  Constant: '<S194>/k'
     */
    NLPID_B.Product2_o = NLPID_B.Integrator1 * NLPID_P.k_Value;

    /* Trigonometry: '<S175>/sin(s)3' */
    NLPID_B.sins3 = sin(NLPID_B.Product2_o);
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S175>/Math Function' incorporates:
       *  Constant: '<S175>/Constant'
       *  Constant: '<S194>/k'
       */
      if ((NLPID_P.k_Value < 0.0) && (NLPID_P.Constant_Value_fyr > floor
           (NLPID_P.Constant_Value_fyr))) {
        NLPID_B.MathFunction_p = -rt_pow_snf(-NLPID_P.k_Value,
          NLPID_P.Constant_Value_fyr);
      } else {
        NLPID_B.MathFunction_p = rt_pow_snf(NLPID_P.k_Value,
          NLPID_P.Constant_Value_fyr);
      }
    }

    /* Product: '<S175>/Product' incorporates:
     *  Constant: '<S194>/r_x'
     */
    NLPID_B.Product_d = NLPID_P.r_x_Value * NLPID_B.sins3 *
      NLPID_B.MathFunction_p;

    /* Trigonometry: '<S175>/cos(s)3' */
    NLPID_B.coss3 = cos(NLPID_B.Product2_o);

    /* Product: '<S175>/Product1' incorporates:
     *  Constant: '<S194>/r_y'
     */
    NLPID_B.Product1_fw = NLPID_P.r_y_Value * NLPID_B.coss3 *
      NLPID_B.MathFunction_p;

    /* Gain: '<S175>/Gain' */
    NLPID_B.Gain_mw = NLPID_P.Gain_Gain_jk * NLPID_B.Product1_fw;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Sum: '<S181>/Subtract' incorporates:
       *  Constant: '<S114>/Path Selector'
       *  Constant: '<S181>/Constant'
       */
      NLPID_B.Subtract_o = NLPID_P.Constant_Value_jt -
        NLPID_P.PathSelector_Value;
    }

    /* Product: '<S181>/Product1' */
    NLPID_B.Product1_i[0] = NLPID_B.Product_d * NLPID_B.Subtract_o;
    NLPID_B.Product1_i[1] = NLPID_B.Gain_mw * NLPID_B.Subtract_o;

    /* Sum: '<S181>/Add' */
    NLPID_B.Add_e[0] = NLPID_B.Product_m[0] + NLPID_B.Product1_i[0];
    NLPID_B.Add_e[1] = NLPID_B.Product_m[1] + NLPID_B.Product1_i[1];

    /* Product: '<S117>/x_d^s * y_d^s^2' */
    NLPID_B.x_dsy_ds2 = NLPID_B.Add[0] * NLPID_B.Add_e[1];

    /* Product: '<S117>/x_d^s^2 * y_d^s' */
    NLPID_B.x_ds2y_ds = NLPID_B.Add_e[0] * NLPID_B.Add[1];

    /* Sum: '<S117>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
    NLPID_B.x_dsy_ds2x_ds2y_ds = NLPID_B.x_dsy_ds2 - NLPID_B.x_ds2y_ds;

    /* Math: '<S117>/( x_d^s )^2' */
    tmp = NLPID_B.Add[0];
    NLPID_B.x_ds2 = tmp * tmp;

    /* Math: '<S117>/( y_d^s )^2' */
    tmp = NLPID_B.Add[1];
    NLPID_B.y_ds2 = tmp * tmp;

    /* Sum: '<S117>/( x_d^s )^2 + ( y_d^s )^2' */
    NLPID_B.x_ds2y_ds2 = NLPID_B.x_ds2 + NLPID_B.y_ds2;

    /* Product: '<S117>/Divide' */
    NLPID_B.Divide_h = NLPID_B.x_dsy_ds2x_ds2y_ds / NLPID_B.x_ds2y_ds2;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S148>/Delta^2' incorporates:
       *  Constant: '<S111>/Delta'
       */
      tmp = NLPID_P.Delta_Value;
      NLPID_B.Delta2_b = tmp * tmp;
    }

    /* Math: '<S148>/epsilon_n^2' */
    tmp = NLPID_B.MultiportSelector;
    NLPID_B.epsilon_n2_j = tmp * tmp;

    /* Sum: '<S148>/Add' */
    NLPID_B.Add_a = NLPID_B.Delta2_b + NLPID_B.epsilon_n2_j;

    /* Product: '<S148>/Divide' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Divide_p = NLPID_P.Delta_Value / NLPID_B.Add_a;

    /* Outputs for atomic SubSystem: '<S127>/S_2' */

    /* Gain: '<S161>/S12' */
    NLPID_B.S12_c = NLPID_P.S12_Gain_p * NLPID_B.Divide_h;

    /* Reshape: '<S161>/S_2(psi_d^s)' incorporates:
     *  Constant: '<S161>/0'
     */
    NLPID_B.S_2psi_ds[0] = NLPID_P._Value;
    NLPID_B.S_2psi_ds[1] = NLPID_B.Divide_h;
    NLPID_B.S_2psi_ds[2] = NLPID_B.S12_c;
    NLPID_B.S_2psi_ds[3] = NLPID_P._Value;

    /* end of Outputs for SubSystem: '<S127>/S_2' */

    /* Math: '<S164>/Math Function' */
    NLPID_B.MathFunction_k[0] = NLPID_B.S_2psi_ds[0];
    NLPID_B.MathFunction_k[1] = NLPID_B.S_2psi_ds[2];
    NLPID_B.MathFunction_k[2] = NLPID_B.S_2psi_ds[1];
    NLPID_B.MathFunction_k[3] = NLPID_B.S_2psi_ds[3];

    /* Product: '<S166>/Product' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += NLPID_B.MathFunction_k[i] * NLPID_B.MathFunction_d[0];
      tmp_3[i] += NLPID_B.MathFunction_k[i + 2] * NLPID_B.MathFunction_d[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += NLPID_B.MathFunction_k[i] * NLPID_B.MathFunction_d[2];
      tmp_3[i + 2] += NLPID_B.MathFunction_k[i + 2] * NLPID_B.MathFunction_d[3];
    }

    NLPID_B.Product_lx[0] = 0.0;
    NLPID_B.Product_lx[0] = tmp_3[0] * NLPID_B.qp_d[0] + NLPID_B.Product_lx[0];
    NLPID_B.Product_lx[0] = tmp_3[2] * NLPID_B.qp_d[1] + NLPID_B.Product_lx[0];

    /* Product: '<S166>/Product1' */
    NLPID_B.Product1_h[0] = 0.0;
    NLPID_B.Product1_h[0] = NLPID_B.MathFunction_d[0] * NLPID_B.Add[0] +
      NLPID_B.Product1_h[0];
    NLPID_B.Product1_h[0] = NLPID_B.MathFunction_d[2] * NLPID_B.Add[1] +
      NLPID_B.Product1_h[0];

    /* Sum: '<S166>/Subtract1' */
    NLPID_B.Subtract1[0] = NLPID_B.Product_lx[0] - NLPID_B.Product1_h[0];
    NLPID_B.Product_lx[1] = 0.0;
    NLPID_B.Product_lx[1] = tmp_3[1] * NLPID_B.qp_d[0] + NLPID_B.Product_lx[1];
    NLPID_B.Product_lx[1] = tmp_3[3] * NLPID_B.qp_d[1] + NLPID_B.Product_lx[1];

    /* Product: '<S166>/Product1' */
    NLPID_B.Product1_h[1] = 0.0;
    NLPID_B.Product1_h[1] = NLPID_B.MathFunction_d[1] * NLPID_B.Add[0] +
      NLPID_B.Product1_h[1];
    NLPID_B.Product1_h[1] = NLPID_B.MathFunction_d[3] * NLPID_B.Add[1] +
      NLPID_B.Product1_h[1];

    /* Sum: '<S166>/Subtract1' */
    NLPID_B.Subtract1[1] = NLPID_B.Product_lx[1] - NLPID_B.Product1_h[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector2' */
    {
      const byte_T *u = (byte_T *)NLPID_B.Subtract1;/* input port */
      const int32_T *index = (const int32_T *)&NLPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&NLPID_B.MultiportSelector2;
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
    }                                  /* end <S127>/Multiport Selector2 */

    /* Product: '<S148>/Product' */
    NLPID_B.Product_bn = NLPID_B.Divide_p * NLPID_B.MultiportSelector2;

    /* Sum: '<S148>/Subtract' */
    NLPID_B.Subtract_g = NLPID_B.Divide_h - NLPID_B.Product_bn;

    /* Math: '<S133>/epsilon_n^2' */
    tmp = NLPID_B.MultiportSelector;
    NLPID_B.epsilon_n2_f = tmp * tmp;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S133>/Delta^2' incorporates:
       *  Constant: '<S111>/Delta'
       */
      tmp = NLPID_P.Delta_Value;
      NLPID_B.Delta2_d = tmp * tmp;
    }

    /* Sum: '<S133>/Add' */
    NLPID_B.Add_h = NLPID_B.epsilon_n2_f + NLPID_B.Delta2_d;

    /* Math: '<S133>/sqrt' */
    tmp = NLPID_B.Add_h;
    if (tmp < 0.0) {
      NLPID_B.sqrt_i = -sqrt(-tmp);
    } else {
      NLPID_B.sqrt_i = sqrt(tmp);
    }

    /* Product: '<S133>/Divide' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Divide_c = NLPID_P.Delta_Value / NLPID_B.sqrt_i;

    /* Product: '<S133>/Product' */
    NLPID_B.Product_e = NLPID_B.Divide_c * NLPID_B.Divide;

    /* Math: '<S140>/Math Function' */
    NLPID_B.MathFunction_pj[0] = NLPID_B.Add[0];

    /* Product: '<S137>/Divide' */
    NLPID_B.Divide_i[0] = NLPID_B.MathFunction_pj[0] / NLPID_B.Add_p;

    /* Math: '<S140>/Math Function' */
    NLPID_B.MathFunction_pj[1] = NLPID_B.Add[1];

    /* Product: '<S137>/Divide' */
    NLPID_B.Divide_i[1] = NLPID_B.MathFunction_pj[1] / NLPID_B.Add_p;

    /* Sum: '<S125>/Subtract' */
    NLPID_B.Subtract_m[0] = NLPID_B.Integrator[0] - NLPID_B.Switch2;
    NLPID_B.Subtract_m[1] = NLPID_B.Integrator[1] - NLPID_B.Switch2_b;

    /* Product: '<S137>/Product' incorporates:
     *  Constant: '<S111>/my'
     */
    tmp = NLPID_P.my_Value * NLPID_B.Divide_i[0] * NLPID_B.Subtract_m[0];
    tmp += NLPID_P.my_Value * NLPID_B.Divide_i[1] * NLPID_B.Subtract_m[1];
    NLPID_B.Product_f1 = tmp;

    /* Gain: '<S137>/Gain' */
    NLPID_B.Gain_cx = NLPID_P.Gain_Gain_o * NLPID_B.Product_f1;

    /* Sum: '<S133>/Subtract' */
    NLPID_B.Subtract_f = NLPID_B.Product_e - NLPID_B.Gain_cx;

    /* Product: '<S60>/Product' */
    NLPID_B.VectorConcatenate_m[2] = NLPID_B.Subtract_g * NLPID_B.Subtract_f;

    /* Sum: '<S53>/Add' */
    NLPID_B.Add_fj[0] = NLPID_B.VectorConcatenate_a[0] +
      NLPID_B.VectorConcatenate_m[0];
    NLPID_B.Add_fj[1] = NLPID_B.VectorConcatenate_a[1] +
      NLPID_B.VectorConcatenate_m[1];
    NLPID_B.Add_fj[2] = NLPID_B.VectorConcatenate_a[2] +
      NLPID_B.VectorConcatenate_m[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S52>/Product' */
      NLPID_B.Product_a[i] = 0.0;
      NLPID_B.Product_a[i] = NLPID_B.MathFunction_l[i] * NLPID_B.Add_fj[0] +
        NLPID_B.Product_a[i];
      NLPID_B.Product_a[i] = NLPID_B.MathFunction_l[i + 3] * NLPID_B.Add_fj[1] +
        NLPID_B.Product_a[i];
      NLPID_B.Product_a[i] = NLPID_B.MathFunction_l[i + 6] * NLPID_B.Add_fj[2] +
        NLPID_B.Product_a[i];

      /* Sum: '<S52>/Subtract' */
      NLPID_B.Subtract_c[i] = NLPID_B.TmpHiddenBufferAtKdInport1[i] -
        NLPID_B.Product_a[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S67>/Product2' */
      NLPID_B.Product2_j4[i] = 0.0;
      NLPID_B.Product2_j4[i] = NLPID_B.Rpsi_k[i] * NLPID_B.Subtract_c[0] +
        NLPID_B.Product2_j4[i];
      NLPID_B.Product2_j4[i] = NLPID_B.Rpsi_k[i + 3] * NLPID_B.Subtract_c[1] +
        NLPID_B.Product2_j4[i];
      NLPID_B.Product2_j4[i] = NLPID_B.Rpsi_k[i + 6] * NLPID_B.Subtract_c[2] +
        NLPID_B.Product2_j4[i];

      /* Sum: '<S67>/Sum' */
      NLPID_B.Sum_a0[i] = ((0.0 - NLPID_B.Product_bj[i]) - NLPID_B.Product1_o[i])
        - NLPID_B.Product2_j4[i];
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Gain: '<S69>/-X_u' incorporates:
       *  Constant: '<S69>/X_u'
       */
      NLPID_B.X_u = NLPID_P.X_u_Gain * NLPID_P.X_u_Value;

      /* Gain: '<S69>/-Y_v' incorporates:
       *  Constant: '<S69>/Y_v'
       */
      NLPID_B.Y_v = NLPID_P.Y_v_Gain * NLPID_P.Y_v_Value;

      /* Gain: '<S69>/-N_v' incorporates:
       *  Constant: '<S69>/N_v'
       */
      NLPID_B.N_v = NLPID_P.N_v_Gain * NLPID_P.N_v_Value;

      /* Gain: '<S69>/-Y_vr' incorporates:
       *  Constant: '<S69>/Y_r'
       */
      NLPID_B.Y_vr = NLPID_P.Y_vr_Gain * NLPID_P.Y_r_Value;

      /* Gain: '<S69>/-N_r' incorporates:
       *  Constant: '<S69>/N_r'
       */
      NLPID_B.N_r = NLPID_P.N_r_Gain * NLPID_P.N_r_Value;

      /* Reshape: '<S69>/Linear Dampning matrix' incorporates:
       *  Constant: '<S69>/D_L_12'
       *  Constant: '<S69>/D_L_13'
       *  Constant: '<S69>/D_L_21'
       *  Constant: '<S69>/D_L_31'
       */
      NLPID_B.LinearDampningmatrix[0] = NLPID_B.X_u;
      NLPID_B.LinearDampningmatrix[1] = NLPID_P.D_L_21_Value;
      NLPID_B.LinearDampningmatrix[2] = NLPID_P.D_L_31_Value;
      NLPID_B.LinearDampningmatrix[3] = NLPID_P.D_L_12_Value;
      NLPID_B.LinearDampningmatrix[4] = NLPID_B.Y_v;
      NLPID_B.LinearDampningmatrix[5] = NLPID_B.N_v;
      NLPID_B.LinearDampningmatrix[6] = NLPID_P.D_L_13_Value;
      NLPID_B.LinearDampningmatrix[7] = NLPID_B.Y_vr;
      NLPID_B.LinearDampningmatrix[8] = NLPID_B.N_r;
    }

    /* Product: '<S66>/Product1' */
    for (i = 0; i < 3; i++) {
      NLPID_B.Product1_kq[i] = 0.0;
      NLPID_B.Product1_kq[i] = NLPID_B.LinearDampningmatrix[i] *
        NLPID_B.TmpHiddenBufferAtKdInport1[0] + NLPID_B.Product1_kq[i];
      NLPID_B.Product1_kq[i] = NLPID_B.LinearDampningmatrix[i + 3] *
        NLPID_B.TmpHiddenBufferAtKdInport1[1] + NLPID_B.Product1_kq[i];
      NLPID_B.Product1_kq[i] = NLPID_B.LinearDampningmatrix[i + 6] *
        NLPID_B.TmpHiddenBufferAtKdInport1[2] + NLPID_B.Product1_kq[i];
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Sum: '<S68>/M_11' incorporates:
       *  Constant: '<S68>/X_udot'
       *  Constant: '<S68>/m'
       */
      NLPID_B.M_11 = NLPID_P.m_Value - NLPID_P.X_udot_Value;

      /* Sum: '<S68>/M_22' incorporates:
       *  Constant: '<S68>/Y_vdot'
       *  Constant: '<S68>/m'
       */
      NLPID_B.M_22 = NLPID_P.m_Value - NLPID_P.Y_vdot_Value;

      /* Product: '<S68>/m x_g' incorporates:
       *  Constant: '<S68>/m'
       *  Constant: '<S68>/x_g'
       */
      NLPID_B.mx_g = NLPID_P.m_Value * NLPID_P.x_g_Value;

      /* Sum: '<S68>/M_32' incorporates:
       *  Constant: '<S68>/N_vdot'
       */
      NLPID_B.M_32 = NLPID_B.mx_g - NLPID_P.N_vdot_Value;

      /* Sum: '<S68>/M_23' incorporates:
       *  Constant: '<S68>/Y_rdot'
       */
      NLPID_B.M_23 = NLPID_B.mx_g - NLPID_P.Y_rdot_Value;

      /* Sum: '<S68>/M_33' incorporates:
       *  Constant: '<S68>/I_z'
       *  Constant: '<S68>/N_rdot'
       */
      NLPID_B.M_33 = NLPID_P.I_z_Value - NLPID_P.N_rdot_Value;

      /* Reshape: '<S68>/3x3' incorporates:
       *  Constant: '<S68>/M_12'
       *  Constant: '<S68>/M_13'
       *  Constant: '<S68>/M_21'
       *  Constant: '<S68>/M_31'
       */
      NLPID_B.x3[0] = NLPID_B.M_11;
      NLPID_B.x3[1] = NLPID_P.M_21_Value;
      NLPID_B.x3[2] = NLPID_P.M_31_Value;
      NLPID_B.x3[3] = NLPID_P.M_12_Value;
      NLPID_B.x3[4] = NLPID_B.M_22;
      NLPID_B.x3[5] = NLPID_B.M_32;
      NLPID_B.x3[6] = NLPID_P.M_13_Value;
      NLPID_B.x3[7] = NLPID_B.M_23;
      NLPID_B.x3[8] = NLPID_B.M_33;
    }

    /* Trigonometry: '<S130>/Trigonometric Function1' */
    NLPID_B.TrigonometricFunction1 = sin(NLPID_B.Gain1_d);

    /* Gain: '<S130>/Gain' */
    NLPID_B.Gain_ga = NLPID_P.Gain_Gain_e * NLPID_B.TrigonometricFunction1;

    /* Trigonometry: '<S130>/Trigonometric Function' */
    NLPID_B.TrigonometricFunction_n = cos(NLPID_B.Gain1_d);

    /* Product: '<S130>/Product1' */
    NLPID_B.Product1_n[0] = NLPID_B.Gain_ga * NLPID_B.u[0];

    /* Product: '<S130>/Product2' */
    NLPID_B.Product2_c[0] = NLPID_B.TrigonometricFunction_n * NLPID_B.u[0];

    /* Product: '<S130>/Product1' */
    NLPID_B.Product1_n[1] = NLPID_B.Gain_ga * NLPID_B.u[1];

    /* Product: '<S130>/Product2' */
    NLPID_B.Product2_c[1] = NLPID_B.TrigonometricFunction_n * NLPID_B.u[1];

    /* Concatenate: '<S130>/Matrix Concatenate' */
    NLPID_B.MatrixConcatenate[0] = NLPID_B.Product1_n[0];
    NLPID_B.MatrixConcatenate[2] = NLPID_B.Product1_n[1];
    NLPID_B.MatrixConcatenate[1] = NLPID_B.Product2_c[0];
    NLPID_B.MatrixConcatenate[3] = NLPID_B.Product2_c[1];

    /* Product: '<S130>/Product' incorporates:
     *  Constant: '<S194>/u_d'
     */
    NLPID_B.Product_i[0] = NLPID_B.MatrixConcatenate[0] * NLPID_P.u_d_Value;
    NLPID_B.Product_i[1] = NLPID_B.MatrixConcatenate[1] * NLPID_P.u_d_Value;
    NLPID_B.Product_i[2] = NLPID_B.MatrixConcatenate[2] * NLPID_P.u_d_Value;
    NLPID_B.Product_i[3] = NLPID_B.MatrixConcatenate[3] * NLPID_P.u_d_Value;

    /* Product: '<S146>/Product2' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product2_p = NLPID_P.Delta_Value * NLPID_B.MultiportSelector;

    /* Math: '<S58>/Math Function' */
    NLPID_B.MathFunction_iq[0] = NLPID_B.Product_p[0];

    /* Math: '<S146>/Math Function' */
    NLPID_B.MathFunction_n[0] = NLPID_B.MultiportSelector1[0];

    /* Math: '<S58>/Math Function' */
    NLPID_B.MathFunction_iq[1] = NLPID_B.Product_p[1];

    /* Math: '<S146>/Math Function' */
    NLPID_B.MathFunction_n[1] = NLPID_B.MultiportSelector1[1];

    /* Product: '<S146>/Product3' */
    NLPID_B.Product3[0] = 0.0;
    NLPID_B.Product3[0] = NLPID_B.MathFunction_n[0] *
      NLPID_B.MultiportSelector1[0] + NLPID_B.Product3[0];
    NLPID_B.Product3[2] = 0.0;
    NLPID_B.Product3[2] = NLPID_B.MathFunction_n[0] *
      NLPID_B.MultiportSelector1[1] + NLPID_B.Product3[2];
    NLPID_B.Product3[1] = 0.0;
    NLPID_B.Product3[1] = NLPID_B.MathFunction_n[1] *
      NLPID_B.MultiportSelector1[0] + NLPID_B.Product3[1];
    NLPID_B.Product3[3] = 0.0;
    NLPID_B.Product3[3] = NLPID_B.MathFunction_n[1] *
      NLPID_B.MultiportSelector1[1] + NLPID_B.Product3[3];

    /* Product: '<S146>/Product4' */
    NLPID_B.Product4[0] = NLPID_B.Product2_p * NLPID_B.Product3[0];

    /* Gain: '<S146>/2' */
    NLPID_B.u_g[0] = NLPID_P._Gain * NLPID_B.Product4[0];

    /* Product: '<S146>/Product4' */
    NLPID_B.Product4[1] = NLPID_B.Product2_p * NLPID_B.Product3[1];

    /* Gain: '<S146>/2' */
    NLPID_B.u_g[1] = NLPID_P._Gain * NLPID_B.Product4[1];

    /* Product: '<S146>/Product4' */
    NLPID_B.Product4[2] = NLPID_B.Product2_p * NLPID_B.Product3[2];

    /* Gain: '<S146>/2' */
    NLPID_B.u_g[2] = NLPID_P._Gain * NLPID_B.Product4[2];

    /* Product: '<S146>/Product4' */
    NLPID_B.Product4[3] = NLPID_B.Product2_p * NLPID_B.Product3[3];

    /* Gain: '<S146>/2' */
    NLPID_B.u_g[3] = NLPID_P._Gain * NLPID_B.Product4[3];
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S146>/Delta^2' incorporates:
       *  Constant: '<S111>/Delta'
       */
      tmp = NLPID_P.Delta_Value;
      NLPID_B.Delta2_d4 = tmp * tmp;
    }

    /* Math: '<S146>/epsilon_n^2' */
    tmp = NLPID_B.MultiportSelector;
    NLPID_B.epsilon_n2_o = tmp * tmp;

    /* Sum: '<S146>/Add' */
    NLPID_B.Add_d = NLPID_B.Delta2_d4 + NLPID_B.epsilon_n2_o;

    /* Math: '<S146>/( )^2' */
    tmp = NLPID_B.Add_d;
    NLPID_B.u_n = tmp * tmp;

    /* Product: '<S146>/Divide' */
    NLPID_B.Divide_hf[0] = NLPID_B.u_g[0] / NLPID_B.u_n;
    NLPID_B.Divide_hf[1] = NLPID_B.u_g[1] / NLPID_B.u_n;
    NLPID_B.Divide_hf[2] = NLPID_B.u_g[2] / NLPID_B.u_n;
    NLPID_B.Divide_hf[3] = NLPID_B.u_g[3] / NLPID_B.u_n;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Product: '<S146>/Product1' incorporates:
       *  Constant: '<S111>/Delta'
       *  Constant: '<S127>/0_2x2'
       */
      NLPID_B.Product1_c[0] = NLPID_P.Delta_Value * NLPID_P._2x2_Value[0];
      NLPID_B.Product1_c[1] = NLPID_P.Delta_Value * NLPID_P._2x2_Value[1];
      NLPID_B.Product1_c[2] = NLPID_P.Delta_Value * NLPID_P._2x2_Value[2];
      NLPID_B.Product1_c[3] = NLPID_P.Delta_Value * NLPID_P._2x2_Value[3];
    }

    /* Product: '<S146>/Divide1' */
    NLPID_B.Divide1[0] = NLPID_B.Product1_c[0] / NLPID_B.Add_d;

    /* Sum: '<S146>/Subtract' */
    NLPID_B.Subtract_ju[0] = NLPID_B.Divide_hf[0] - NLPID_B.Divide1[0];

    /* Product: '<S146>/Divide1' */
    NLPID_B.Divide1[1] = NLPID_B.Product1_c[1] / NLPID_B.Add_d;

    /* Sum: '<S146>/Subtract' */
    NLPID_B.Subtract_ju[1] = NLPID_B.Divide_hf[1] - NLPID_B.Divide1[1];

    /* Product: '<S146>/Divide1' */
    NLPID_B.Divide1[2] = NLPID_B.Product1_c[2] / NLPID_B.Add_d;

    /* Sum: '<S146>/Subtract' */
    NLPID_B.Subtract_ju[2] = NLPID_B.Divide_hf[2] - NLPID_B.Divide1[2];

    /* Product: '<S146>/Divide1' */
    NLPID_B.Divide1[3] = NLPID_B.Product1_c[3] / NLPID_B.Add_d;

    /* Sum: '<S146>/Subtract' */
    NLPID_B.Subtract_ju[3] = NLPID_B.Divide_hf[3] - NLPID_B.Divide1[3];

    /* Math: '<S59>/Math Function' */
    NLPID_B.MathFunction_o[0] = NLPID_B.Subtract_ju[0];
    NLPID_B.MathFunction_o[1] = NLPID_B.Subtract_ju[2];
    NLPID_B.MathFunction_o[2] = NLPID_B.Subtract_ju[1];
    NLPID_B.MathFunction_o[3] = NLPID_B.Subtract_ju[3];

    /* Product: '<S55>/Product' */
    NLPID_B.Product_g[0] = 0.0;
    NLPID_B.Product_g[0] = NLPID_B.MathFunction_iq[0] * NLPID_B.MathFunction_o[0]
      + NLPID_B.Product_g[0];
    NLPID_B.Product_g[0] = NLPID_B.MathFunction_iq[1] * NLPID_B.MathFunction_o[1]
      + NLPID_B.Product_g[0];

    /* Product: '<S55>/Product1' */
    NLPID_B.Product1_d[0] = 0.0;
    NLPID_B.Product1_d[0] = NLPID_B.u[0] * NLPID_B.Product_i[0] +
      NLPID_B.Product1_d[0];
    NLPID_B.Product1_d[0] = NLPID_B.u[1] * NLPID_B.Product_i[1] +
      NLPID_B.Product1_d[0];

    /* Sum: '<S55>/Add' */
    NLPID_B.Add_ax[0] = NLPID_B.Product_g[0] + NLPID_B.Product1_d[0];

    /* Product: '<S55>/Product' */
    NLPID_B.Product_g[1] = 0.0;
    NLPID_B.Product_g[1] = NLPID_B.MathFunction_iq[0] * NLPID_B.MathFunction_o[2]
      + NLPID_B.Product_g[1];
    NLPID_B.Product_g[1] = NLPID_B.MathFunction_iq[1] * NLPID_B.MathFunction_o[3]
      + NLPID_B.Product_g[1];

    /* Product: '<S55>/Product1' */
    NLPID_B.Product1_d[1] = 0.0;
    NLPID_B.Product1_d[1] = NLPID_B.u[0] * NLPID_B.Product_i[2] +
      NLPID_B.Product1_d[1];
    NLPID_B.Product1_d[1] = NLPID_B.u[1] * NLPID_B.Product_i[3] +
      NLPID_B.Product1_d[1];

    /* Sum: '<S55>/Add' */
    NLPID_B.Add_ax[1] = NLPID_B.Product_g[1] + NLPID_B.Product1_d[1];

    /* Concatenate: '<S55>/Matrix Concatenate' */
    NLPID_B.MatrixConcatenate_j[0] = NLPID_B.Product_i[0];
    NLPID_B.MatrixConcatenate_j[1] = NLPID_B.Product_i[1];
    NLPID_B.MatrixConcatenate_j[3] = NLPID_B.Product_i[2];
    NLPID_B.MatrixConcatenate_j[4] = NLPID_B.Product_i[3];
    NLPID_B.MatrixConcatenate_j[2] = NLPID_B.Add_ax[0];
    NLPID_B.MatrixConcatenate_j[5] = NLPID_B.Add_ax[1];

    /* Product: '<S147>/Product' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product_a5[0] = NLPID_P.Delta_Value * NLPID_B.MultiportSelector *
      NLPID_B.MultiportSelector2 * NLPID_B.MultiportSelector1[0];

    /* Gain: '<S147>/2' */
    NLPID_B.u_k[0] = NLPID_P._Gain_b * NLPID_B.Product_a5[0];

    /* Product: '<S147>/Product' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product_a5[1] = NLPID_P.Delta_Value * NLPID_B.MultiportSelector *
      NLPID_B.MultiportSelector2 * NLPID_B.MultiportSelector1[1];

    /* Gain: '<S147>/2' */
    NLPID_B.u_k[1] = NLPID_P._Gain_b * NLPID_B.Product_a5[1];
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S147>/Delta^2' incorporates:
       *  Constant: '<S111>/Delta'
       */
      tmp = NLPID_P.Delta_Value;
      NLPID_B.Delta2_m = tmp * tmp;
    }

    /* Math: '<S147>/epsilon_n^2' */
    tmp = NLPID_B.MultiportSelector;
    NLPID_B.epsilon_n2_b = tmp * tmp;

    /* Sum: '<S147>/Add' */
    NLPID_B.Add_dw = NLPID_B.Delta2_m + NLPID_B.epsilon_n2_b;

    /* Math: '<S147>/( )^2' */
    tmp = NLPID_B.Add_dw;
    NLPID_B.u_b = tmp * tmp;

    /* Product: '<S147>/Divide' */
    NLPID_B.Divide_f[0] = NLPID_B.u_k[0] / NLPID_B.u_b;
    NLPID_B.Divide_f[1] = NLPID_B.u_k[1] / NLPID_B.u_b;

    /* Product: '<S165>/Product1' */
    for (i = 0; i < 2; i++) {
      NLPID_B.Product1_fo[i] = 0.0;
      NLPID_B.Product1_fo[i] = NLPID_B.MathFunction_k[i] *
        NLPID_B.MathFunction_d[0] + NLPID_B.Product1_fo[i];
      NLPID_B.Product1_fo[i] = NLPID_B.MathFunction_k[i + 2] *
        NLPID_B.MathFunction_d[1] + NLPID_B.Product1_fo[i];
      NLPID_B.Product1_fo[i + 2] = 0.0;
      NLPID_B.Product1_fo[i + 2] = NLPID_B.Product1_fo[i + 2] +
        NLPID_B.MathFunction_k[i] * NLPID_B.MathFunction_d[2];
      NLPID_B.Product1_fo[i + 2] = NLPID_B.MathFunction_k[i + 2] *
        NLPID_B.MathFunction_d[3] + NLPID_B.Product1_fo[i + 2];
    }

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector3' */
    {
      const byte_T *u = (byte_T *)NLPID_B.Product1_fo;/* input port */
      const int32_T *index = (const int32_T *)&NLPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)NLPID_B.MultiportSelector3;
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
    }                                  /* end <S127>/Multiport Selector3 */

    /* Product: '<S147>/Product1' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product1_g[0] = NLPID_P.Delta_Value * NLPID_B.MultiportSelector3[0];

    /* Product: '<S147>/Divide1' */
    NLPID_B.Divide1_l[0] = NLPID_B.Product1_g[0] / NLPID_B.Add_dw;

    /* Sum: '<S147>/Subtract' */
    NLPID_B.Subtract_fn[0] = NLPID_B.Divide_f[0] - NLPID_B.Divide1_l[0];

    /* Product: '<S61>/Product' */
    NLPID_B.Product_ae[0] = NLPID_B.Subtract_fn[0] * NLPID_B.Subtract_f;

    /* Product: '<S134>/Product1' */
    NLPID_B.Product1_d4[0] = NLPID_B.MultiportSelector *
      NLPID_B.MultiportSelector1[0];

    /* Product: '<S147>/Product1' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product1_g[1] = NLPID_P.Delta_Value * NLPID_B.MultiportSelector3[1];

    /* Product: '<S147>/Divide1' */
    NLPID_B.Divide1_l[1] = NLPID_B.Product1_g[1] / NLPID_B.Add_dw;

    /* Sum: '<S147>/Subtract' */
    NLPID_B.Subtract_fn[1] = NLPID_B.Divide_f[1] - NLPID_B.Divide1_l[1];

    /* Product: '<S61>/Product' */
    NLPID_B.Product_ae[1] = NLPID_B.Subtract_fn[1] * NLPID_B.Subtract_f;

    /* Product: '<S134>/Product1' */
    NLPID_B.Product1_d4[1] = NLPID_B.MultiportSelector *
      NLPID_B.MultiportSelector1[1];

    /* Math: '<S134>/epsilon_n^2' */
    tmp = NLPID_B.MultiportSelector;
    NLPID_B.epsilon_n2_n = tmp * tmp;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S134>/Delta^2' incorporates:
       *  Constant: '<S111>/Delta'
       */
      tmp = NLPID_P.Delta_Value;
      NLPID_B.Delta2_a = tmp * tmp;
    }

    /* Sum: '<S134>/Add' */
    NLPID_B.Add_c = NLPID_B.epsilon_n2_n + NLPID_B.Delta2_a;

    /* Math: '<S134>/^3//2' incorporates:
     *  Constant: '<S134>/3//2'
     */
    if ((NLPID_B.Add_c < 0.0) && (NLPID_P.u_Value_ip > floor(NLPID_P.u_Value_ip)))
    {
      NLPID_B.u2 = -rt_pow_snf(-NLPID_B.Add_c, NLPID_P.u_Value_ip);
    } else {
      NLPID_B.u2 = rt_pow_snf(NLPID_B.Add_c, NLPID_P.u_Value_ip);
    }

    /* Product: '<S134>/Divide' */
    NLPID_B.Divide_j[0] = NLPID_B.Product1_d4[0] / NLPID_B.u2;

    /* Product: '<S134>/Product' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product_lao[0] = NLPID_P.Delta_Value * NLPID_B.Divide_j[0] *
      NLPID_B.Divide;

    /* Math: '<S141>/Math Function' */
    NLPID_B.MathFunction_m[0] = NLPID_B.Add[0];

    /* Product: '<S138>/Divide' */
    NLPID_B.Divide_e[0] = NLPID_B.MathFunction_m[0] / NLPID_B.Add_p;

    /* Product: '<S138>/Product' incorporates:
     *  Constant: '<S111>/my'
     */
    NLPID_B.Product_gv[0] = NLPID_P.my_Value * NLPID_B.Divide_e[0];

    /* Gain: '<S138>/Gain' */
    NLPID_B.Gain_mb[0] = NLPID_P.Gain_Gain_b * NLPID_B.Product_gv[0];

    /* Sum: '<S134>/Sum' */
    NLPID_B.Sum_mp[0] = (0.0 - NLPID_B.Product_lao[0]) - NLPID_B.Gain_mb[0];

    /* Product: '<S61>/Product1' */
    NLPID_B.Product1_a[0] = NLPID_B.Subtract_g * NLPID_B.Sum_mp[0];

    /* Sum: '<S61>/Add' */
    NLPID_B.Add_b[0] = NLPID_B.Product_ae[0] + NLPID_B.Product1_a[0];

    /* Product: '<S134>/Divide' */
    NLPID_B.Divide_j[1] = NLPID_B.Product1_d4[1] / NLPID_B.u2;

    /* Product: '<S134>/Product' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product_lao[1] = NLPID_P.Delta_Value * NLPID_B.Divide_j[1] *
      NLPID_B.Divide;

    /* Math: '<S141>/Math Function' */
    NLPID_B.MathFunction_m[1] = NLPID_B.Add[1];

    /* Product: '<S138>/Divide' */
    NLPID_B.Divide_e[1] = NLPID_B.MathFunction_m[1] / NLPID_B.Add_p;

    /* Product: '<S138>/Product' incorporates:
     *  Constant: '<S111>/my'
     */
    NLPID_B.Product_gv[1] = NLPID_P.my_Value * NLPID_B.Divide_e[1];

    /* Gain: '<S138>/Gain' */
    NLPID_B.Gain_mb[1] = NLPID_P.Gain_Gain_b * NLPID_B.Product_gv[1];

    /* Sum: '<S134>/Sum' */
    NLPID_B.Sum_mp[1] = (0.0 - NLPID_B.Product_lao[1]) - NLPID_B.Gain_mb[1];

    /* Product: '<S61>/Product1' */
    NLPID_B.Product1_a[1] = NLPID_B.Subtract_g * NLPID_B.Sum_mp[1];

    /* Sum: '<S61>/Add' */
    NLPID_B.Add_b[1] = NLPID_B.Product_ae[1] + NLPID_B.Product1_a[1];

    /* Concatenate: '<S61>/Matrix Concatenate' incorporates:
     *  Constant: '<S61>/0_2x2'
     */
    NLPID_B.MatrixConcatenate_n[0] = NLPID_P._2x2_Value_f[0];
    NLPID_B.MatrixConcatenate_n[1] = NLPID_P._2x2_Value_f[1];
    NLPID_B.MatrixConcatenate_n[3] = NLPID_P._2x2_Value_f[2];
    NLPID_B.MatrixConcatenate_n[4] = NLPID_P._2x2_Value_f[3];
    NLPID_B.MatrixConcatenate_n[2] = NLPID_B.Add_b[0];
    NLPID_B.MatrixConcatenate_n[5] = NLPID_B.Add_b[1];

    /* Sum: '<S103>/Add' */
    for (i = 0; i < 6; i++) {
      NLPID_B.Add_ac[i] = NLPID_B.MatrixConcatenate_j[i] +
        NLPID_B.MatrixConcatenate_n[i];
    }

    /* Integrator: '<S50>/omega_q' */
    NLPID_B.omega_q[0] = NLPID_X.omega_q_CSTATE[0];

    /* Sum: '<S50>/Add' */
    NLPID_B.Add_ic[0] = NLPID_B.omega_q[0] + NLPID_B.Product_p[0];

    /* Integrator: '<S50>/omega_q' */
    NLPID_B.omega_q[1] = NLPID_X.omega_q_CSTATE[1];

    /* Sum: '<S50>/Add' */
    NLPID_B.Add_ic[1] = NLPID_B.omega_q[1] + NLPID_B.Product_p[1];

    /* Product: '<S51>/Product' */
    for (i = 0; i < 3; i++) {
      NLPID_B.Product_gq[i] = 0.0;
      NLPID_B.Product_gq[i] = NLPID_B.Add_ac[i] * NLPID_B.Add_ic[0] +
        NLPID_B.Product_gq[i];
      NLPID_B.Product_gq[i] = NLPID_B.Add_ac[i + 3] * NLPID_B.Add_ic[1] +
        NLPID_B.Product_gq[i];
    }

    /* Trigonometry: '<S131>/Trigonometric Function1' */
    NLPID_B.TrigonometricFunction1_k = sin(NLPID_B.Gain1_d);

    /* Gain: '<S131>/Gain' */
    NLPID_B.Gain_l1 = NLPID_P.Gain_Gain_lf * NLPID_B.TrigonometricFunction1_k;

    /* Product: '<S131>/Product1' */
    NLPID_B.Product1_i1 = NLPID_B.Gain_l1 * NLPID_B.Subtract_g;

    /* Trigonometry: '<S131>/Trigonometric Function' */
    NLPID_B.TrigonometricFunction_p = cos(NLPID_B.Gain1_d);

    /* Product: '<S131>/Product2' */
    NLPID_B.Product2_ok = NLPID_B.TrigonometricFunction_p * NLPID_B.Subtract_g;

    /* SignalConversion: '<S131>/TmpHiddenBufferAtProductInport1' */
    NLPID_B.TmpHiddenBufferAtProductInpor_n[0] = NLPID_B.Product1_i1;
    NLPID_B.TmpHiddenBufferAtProductInpor_n[1] = NLPID_B.Product2_ok;

    /* Product: '<S131>/Product' incorporates:
     *  Constant: '<S194>/u_d'
     */
    NLPID_B.Product_fr[0] = NLPID_B.TmpHiddenBufferAtProductInpor_n[0] *
      NLPID_P.u_d_Value;
    NLPID_B.Product_fr[1] = NLPID_B.TmpHiddenBufferAtProductInpor_n[1] *
      NLPID_P.u_d_Value;

    /* SignalConversion: '<S56>/ConcatBufferAtVector ConcatenateIn1' */
    NLPID_B.VectorConcatenate_l[0] = NLPID_B.Product_fr[0];
    NLPID_B.VectorConcatenate_l[1] = NLPID_B.Product_fr[1];

    /* Product: '<S56>/Product' */
    tmp = NLPID_B.Subtract_fn[0] * NLPID_B.Product_p[0];
    tmp += NLPID_B.Subtract_fn[1] * NLPID_B.Product_p[1];
    NLPID_B.Product_h = tmp;

    /* Product: '<S56>/Product1' */
    tmp = NLPID_B.u[0] * NLPID_B.Product_fr[0];
    tmp += NLPID_B.u[1] * NLPID_B.Product_fr[1];
    NLPID_B.Product1_os = tmp;

    /* Sum: '<S56>/Add' */
    NLPID_B.VectorConcatenate_l[2] = NLPID_B.Product_h + NLPID_B.Product1_os;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Constant: '<S62>/0_2x1' */
      NLPID_B.VectorConcatenate_d[0] = NLPID_P._2x1_Value_d[0];
      NLPID_B.VectorConcatenate_d[1] = NLPID_P._2x1_Value_d[1];

      /* Product: '<S180>/Product' incorporates:
       *  Constant: '<S114>/Path Selector'
       *  Constant: '<S170>/0_2x1'
       */
      NLPID_B.Product_jv[0] = NLPID_P._2x1_Value_c * NLPID_P.PathSelector_Value;
      NLPID_B.Product_jv[1] = NLPID_P._2x1_Value_c * NLPID_P.PathSelector_Value;
    }

    /* Product: '<S174>/Product2' incorporates:
     *  Constant: '<S194>/k'
     */
    NLPID_B.Product2_a = NLPID_B.Integrator1 * NLPID_P.k_Value;

    /* Trigonometry: '<S174>/cos(s)' */
    NLPID_B.coss_pz = cos(NLPID_B.Product2_a);
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S174>/Math Function' incorporates:
       *  Constant: '<S194>/k'
       */
      tmp = NLPID_P.k_Value;
      NLPID_B.MathFunction_gs = tmp * tmp;
    }

    /* Product: '<S174>/Product' incorporates:
     *  Constant: '<S194>/r_x'
     */
    NLPID_B.Product_pa = NLPID_P.r_x_Value * NLPID_B.coss_pz *
      NLPID_B.MathFunction_gs;

    /* Gain: '<S174>/Gain' */
    NLPID_B.Gain_a = NLPID_P.Gain_Gain_a * NLPID_B.Product_pa;

    /* Trigonometry: '<S174>/sin(s)' */
    NLPID_B.sins_p = sin(NLPID_B.Product2_a);

    /* Product: '<S174>/Product1' incorporates:
     *  Constant: '<S194>/r_y'
     */
    NLPID_B.Product1_jk = NLPID_P.r_y_Value * NLPID_B.sins_p *
      NLPID_B.MathFunction_gs;

    /* Gain: '<S174>/Gain1' */
    NLPID_B.Gain1_c = NLPID_P.Gain1_Gain_c * NLPID_B.Product1_jk;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Sum: '<S180>/Subtract' incorporates:
       *  Constant: '<S114>/Path Selector'
       *  Constant: '<S180>/Constant'
       */
      NLPID_B.Subtract_fr = NLPID_P.Constant_Value_pr -
        NLPID_P.PathSelector_Value;
    }

    /* Product: '<S180>/Product1' */
    NLPID_B.Product1_if[0] = NLPID_B.Gain_a * NLPID_B.Subtract_fr;
    NLPID_B.Product1_if[1] = NLPID_B.Gain1_c * NLPID_B.Subtract_fr;

    /* Sum: '<S180>/Add' */
    NLPID_B.Add_ef[0] = NLPID_B.Product_jv[0] + NLPID_B.Product1_if[0];
    NLPID_B.Add_ef[1] = NLPID_B.Product_jv[1] + NLPID_B.Product1_if[1];

    /* Product: '<S118>/x_d^s * y_d^s^3 ' */
    NLPID_B.x_dsy_ds3 = NLPID_B.Add[0] * NLPID_B.Add_ef[1];

    /* Product: '<S118>/x_d^s^3 * y_d^s' */
    NLPID_B.x_ds3y_ds = NLPID_B.Add_ef[0] * NLPID_B.Add[1];

    /* Sum: '<S118>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
    NLPID_B.x_dsy_ds3x_ds3y_ds = NLPID_B.x_dsy_ds3 - NLPID_B.x_ds3y_ds;

    /* Product: '<S118>/Product1' */
    NLPID_B.Product1_hm = NLPID_B.x_dsy_ds3x_ds3y_ds * NLPID_B.x_ds2y_ds2;

    /* Product: '<S118>/x_d^s * x_d^s^2' */
    NLPID_B.x_dsx_ds2 = NLPID_B.Add[0] * NLPID_B.Add_e[0];

    /* Product: '<S118>/y_d^s * y_d^s^2' */
    NLPID_B.y_dsy_ds2 = NLPID_B.Add[1] * NLPID_B.Add_e[1];

    /* Sum: '<S118>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
    NLPID_B.x_dsx_ds2x_ds3y_ds = NLPID_B.x_dsx_ds2 + NLPID_B.y_dsy_ds2;

    /* Gain: '<S118>/+ 2' */
    NLPID_B.u_d = NLPID_P.u_Gain_j * NLPID_B.x_dsx_ds2x_ds3y_ds;

    /* Product: '<S118>/Product2' */
    NLPID_B.Product2_g = NLPID_B.x_dsy_ds2x_ds2y_ds * NLPID_B.u_d;

    /* Sum: '<S118>/Subtract' */
    NLPID_B.Subtract_jg = NLPID_B.Product1_hm - NLPID_B.Product2_g;

    /* Math: '<S118>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
    tmp = NLPID_B.x_ds2y_ds2;
    NLPID_B.x_ds2y_ds22 = tmp * tmp;

    /* Product: '<S118>/Divide' */
    NLPID_B.Divide_ph = NLPID_B.Subtract_jg / NLPID_B.x_ds2y_ds22;

    /* Math: '<S149>/(epsilon_n^s)^2' */
    tmp = NLPID_B.MultiportSelector2;
    NLPID_B.epsilon_ns2 = tmp * tmp;

    /* Product: '<S149>/Product' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product_nc = NLPID_P.Delta_Value * NLPID_B.MultiportSelector *
      NLPID_B.epsilon_ns2;

    /* Gain: '<S149>/2' */
    NLPID_B.u_f = NLPID_P._Gain_h * NLPID_B.Product_nc;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S149>/Delta^2' incorporates:
       *  Constant: '<S111>/Delta'
       */
      tmp = NLPID_P.Delta_Value;
      NLPID_B.Delta2_p = tmp * tmp;
    }

    /* Math: '<S149>/epsilon_n^2' */
    tmp = NLPID_B.MultiportSelector;
    NLPID_B.epsilon_n2_ji = tmp * tmp;

    /* Sum: '<S149>/Add' */
    NLPID_B.Add_di = NLPID_B.Delta2_p + NLPID_B.epsilon_n2_ji;

    /* Math: '<S149>/( )^2' */
    tmp = NLPID_B.Add_di;
    NLPID_B.u_bl = tmp * tmp;

    /* Product: '<S149>/Divide' */
    NLPID_B.Divide_cz = NLPID_B.u_f / NLPID_B.u_bl;

    /* Outputs for atomic SubSystem: '<S127>/S_2(psi_d^s^2)' */

    /* Gain: '<S162>/S12' */
    NLPID_B.S12_j = NLPID_P.S12_Gain_k * NLPID_B.Divide_ph;

    /* Reshape: '<S162>/S_2(psi_d^s^2)' incorporates:
     *  Constant: '<S162>/0'
     */
    NLPID_B.S_2psi_ds2[0] = NLPID_P._Value_c;
    NLPID_B.S_2psi_ds2[1] = NLPID_B.Divide_ph;
    NLPID_B.S_2psi_ds2[2] = NLPID_B.S12_j;
    NLPID_B.S_2psi_ds2[3] = NLPID_P._Value_c;

    /* end of Outputs for SubSystem: '<S127>/S_2(psi_d^s^2)' */

    /* Math: '<S163>/Math Function' */
    NLPID_B.MathFunction_ox[0] = NLPID_B.S_2psi_ds2[0];
    NLPID_B.MathFunction_ox[1] = NLPID_B.S_2psi_ds2[2];
    NLPID_B.MathFunction_ox[2] = NLPID_B.S_2psi_ds2[1];
    NLPID_B.MathFunction_ox[3] = NLPID_B.S_2psi_ds2[3];

    /* Product: '<S167>/Product' */
    for (i = 0; i < 2; i++) {
      NLPID_B.Product_fb[i] = 0.0;
      NLPID_B.Product_fb[i] = NLPID_B.MathFunction_k[i] *
        NLPID_B.MathFunction_k[0] + NLPID_B.Product_fb[i];
      NLPID_B.Product_fb[i] = NLPID_B.MathFunction_k[i + 2] *
        NLPID_B.MathFunction_k[1] + NLPID_B.Product_fb[i];
      NLPID_B.Product_fb[i + 2] = 0.0;
      NLPID_B.Product_fb[i + 2] = NLPID_B.Product_fb[i + 2] +
        NLPID_B.MathFunction_k[i] * NLPID_B.MathFunction_k[2];
      NLPID_B.Product_fb[i + 2] = NLPID_B.MathFunction_k[i + 2] *
        NLPID_B.MathFunction_k[3] + NLPID_B.Product_fb[i + 2];
    }

    /* Sum: '<S167>/Add' */
    NLPID_B.Add_au[0] = NLPID_B.MathFunction_ox[0] + NLPID_B.Product_fb[0];
    NLPID_B.Add_au[1] = NLPID_B.MathFunction_ox[1] + NLPID_B.Product_fb[1];
    NLPID_B.Add_au[2] = NLPID_B.MathFunction_ox[2] + NLPID_B.Product_fb[2];
    NLPID_B.Add_au[3] = NLPID_B.MathFunction_ox[3] + NLPID_B.Product_fb[3];

    /* Product: '<S167>/Product1' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += NLPID_B.Add_au[i] * NLPID_B.MathFunction_d[0];
      tmp_3[i] += NLPID_B.Add_au[i + 2] * NLPID_B.MathFunction_d[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += NLPID_B.Add_au[i] * NLPID_B.MathFunction_d[2];
      tmp_3[i + 2] += NLPID_B.Add_au[i + 2] * NLPID_B.MathFunction_d[3];
    }

    NLPID_B.Product1_l[0] = 0.0;
    NLPID_B.Product1_l[0] = tmp_3[0] * NLPID_B.qp_d[0] + NLPID_B.Product1_l[0];
    NLPID_B.Product1_l[0] = tmp_3[2] * NLPID_B.qp_d[1] + NLPID_B.Product1_l[0];
    NLPID_B.Product1_l[1] = 0.0;
    NLPID_B.Product1_l[1] = tmp_3[1] * NLPID_B.qp_d[0] + NLPID_B.Product1_l[1];
    NLPID_B.Product1_l[1] = tmp_3[3] * NLPID_B.qp_d[1] + NLPID_B.Product1_l[1];

    /* Product: '<S167>/Product2' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += NLPID_B.MathFunction_k[i] * NLPID_B.MathFunction_d[0];
      tmp_3[i] += NLPID_B.MathFunction_k[i + 2] * NLPID_B.MathFunction_d[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += NLPID_B.MathFunction_k[i] * NLPID_B.MathFunction_d[2];
      tmp_3[i + 2] += NLPID_B.MathFunction_k[i + 2] * NLPID_B.MathFunction_d[3];
    }

    NLPID_B.Product2_h[0] = 0.0;
    NLPID_B.Product2_h[0] = tmp_3[0] * NLPID_B.Add[0] + NLPID_B.Product2_h[0];
    NLPID_B.Product2_h[0] = tmp_3[2] * NLPID_B.Add[1] + NLPID_B.Product2_h[0];

    /* Gain: '<S167>/2' */
    NLPID_B.u_j[0] = NLPID_P._Gain_k * NLPID_B.Product2_h[0];

    /* Product: '<S167>/Product3' */
    NLPID_B.Product3_f[0] = 0.0;
    NLPID_B.Product3_f[0] = NLPID_B.MathFunction_d[0] * NLPID_B.Add_e[0] +
      NLPID_B.Product3_f[0];
    NLPID_B.Product3_f[0] = NLPID_B.MathFunction_d[2] * NLPID_B.Add_e[1] +
      NLPID_B.Product3_f[0];

    /* Sum: '<S167>/Sum' */
    NLPID_B.Sum_o[0] = (NLPID_B.Product1_l[0] - NLPID_B.u_j[0]) -
      NLPID_B.Product3_f[0];

    /* Gain: '<S167>/Gain' */
    NLPID_B.Gain_lk[0] = NLPID_P.Gain_Gain_l0 * NLPID_B.Sum_o[0];
    NLPID_B.Product2_h[1] = 0.0;
    NLPID_B.Product2_h[1] = tmp_3[1] * NLPID_B.Add[0] + NLPID_B.Product2_h[1];
    NLPID_B.Product2_h[1] = tmp_3[3] * NLPID_B.Add[1] + NLPID_B.Product2_h[1];

    /* Gain: '<S167>/2' */
    NLPID_B.u_j[1] = NLPID_P._Gain_k * NLPID_B.Product2_h[1];

    /* Product: '<S167>/Product3' */
    NLPID_B.Product3_f[1] = 0.0;
    NLPID_B.Product3_f[1] = NLPID_B.MathFunction_d[1] * NLPID_B.Add_e[0] +
      NLPID_B.Product3_f[1];
    NLPID_B.Product3_f[1] = NLPID_B.MathFunction_d[3] * NLPID_B.Add_e[1] +
      NLPID_B.Product3_f[1];

    /* Sum: '<S167>/Sum' */
    NLPID_B.Sum_o[1] = (NLPID_B.Product1_l[1] - NLPID_B.u_j[1]) -
      NLPID_B.Product3_f[1];

    /* Gain: '<S167>/Gain' */
    NLPID_B.Gain_lk[1] = NLPID_P.Gain_Gain_l0 * NLPID_B.Sum_o[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S127>/Multiport Selector4' */
    {
      const byte_T *u = (byte_T *)NLPID_B.Gain_lk;/* input port */
      const int32_T *index = (const int32_T *)&NLPID_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPID_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&NLPID_B.MultiportSelector4;
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
    }                                  /* end <S127>/Multiport Selector4 */

    /* Product: '<S149>/Product1' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product1_jb = NLPID_P.Delta_Value * NLPID_B.MultiportSelector4;

    /* Product: '<S149>/Divide1' */
    NLPID_B.Divide1_e = NLPID_B.Product1_jb / NLPID_B.Add_di;

    /* Sum: '<S149>/Sum' */
    NLPID_B.Sum_hf = (NLPID_B.Divide_ph + NLPID_B.Divide_cz) - NLPID_B.Divide1_e;

    /* Product: '<S62>/Product' */
    NLPID_B.Product_av = NLPID_B.Sum_hf * NLPID_B.Subtract_f;

    /* Math: '<S192>/Math Function' */
    NLPID_B.MathFunction_f[0] = NLPID_B.Add[0];
    NLPID_B.MathFunction_f[1] = NLPID_B.Add[1];

    /* Product: '<S190>/Product1' */
    tmp = NLPID_B.MathFunction_f[0] * NLPID_B.Add_e[0];
    tmp += NLPID_B.MathFunction_f[1] * NLPID_B.Add_e[1];
    NLPID_B.Product1_cs = tmp;

    /* Math: '<S190>/|p_d^s|^3' incorporates:
     *  Constant: '<S190>/Constant'
     */
    if ((NLPID_B.Add_p < 0.0) && (NLPID_P.Constant_Value_fg > floor
         (NLPID_P.Constant_Value_fg))) {
      NLPID_B.p_ds3 = -rt_pow_snf(-NLPID_B.Add_p, NLPID_P.Constant_Value_fg);
    } else {
      NLPID_B.p_ds3 = rt_pow_snf(NLPID_B.Add_p, NLPID_P.Constant_Value_fg);
    }

    /* Product: '<S190>/Divide' */
    NLPID_B.Divide_m = NLPID_B.Product1_cs / NLPID_B.p_ds3;

    /* Product: '<S190>/Product' incorporates:
     *  Constant: '<S194>/u_d'
     */
    NLPID_B.Product_nw = NLPID_B.Divide_m * NLPID_P.u_d_Value;

    /* Gain: '<S190>/Gain' */
    NLPID_B.Gain_jk = NLPID_P.Gain_Gain_mo * NLPID_B.Product_nw;

    /* Math: '<S135>/epsilon_n^2' */
    tmp = NLPID_B.MultiportSelector;
    NLPID_B.epsilon_n2_bc = tmp * tmp;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S135>/Delta^2' incorporates:
       *  Constant: '<S111>/Delta'
       */
      tmp = NLPID_P.Delta_Value;
      NLPID_B.Delta2_c = tmp * tmp;
    }

    /* Sum: '<S135>/Add' */
    NLPID_B.Add_n = NLPID_B.epsilon_n2_bc + NLPID_B.Delta2_c;

    /* Math: '<S135>/Math Function' */
    tmp = NLPID_B.Add_n;
    if (tmp < 0.0) {
      NLPID_B.MathFunction_atw = -sqrt(-tmp);
    } else {
      NLPID_B.MathFunction_atw = sqrt(tmp);
    }

    /* Product: '<S135>/Divide' */
    NLPID_B.Divide_ey = NLPID_B.Gain_jk / NLPID_B.MathFunction_atw;

    /* Product: '<S135>/Product1' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product1_hq = NLPID_P.Delta_Value * NLPID_B.Divide_ey;

    /* Product: '<S135>/Product2' */
    NLPID_B.Product2_ha = NLPID_B.MultiportSelector * NLPID_B.MultiportSelector2;

    /* Math: '<S135>/^3//2' incorporates:
     *  Constant: '<S135>/3//2'
     */
    if ((NLPID_B.Add_n < 0.0) && (NLPID_P.u_Value_ns > floor(NLPID_P.u_Value_ns)))
    {
      NLPID_B.u2_f = -rt_pow_snf(-NLPID_B.Add_n, NLPID_P.u_Value_ns);
    } else {
      NLPID_B.u2_f = rt_pow_snf(NLPID_B.Add_n, NLPID_P.u_Value_ns);
    }

    /* Product: '<S135>/Divide1' */
    NLPID_B.Divide1_k = NLPID_B.Product2_ha / NLPID_B.u2_f;

    /* Product: '<S135>/Product3' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Product3_n = NLPID_P.Delta_Value * NLPID_B.Divide1_k *
      NLPID_B.Divide;

    /* Product: '<S139>/Product1' incorporates:
     *  Constant: '<S111>/my'
     */
    NLPID_B.Product1_p = NLPID_P.my_Value * NLPID_B.Add_p;

    /* Math: '<S143>/Math Function' */
    NLPID_B.MathFunction_g4[0] = NLPID_B.Add_e[0];

    /* Product: '<S139>/Divide2' */
    NLPID_B.Divide2[0] = NLPID_B.MathFunction_g4[0] / NLPID_B.Add_p;

    /* Math: '<S142>/Math Function' */
    NLPID_B.MathFunction_j[0] = NLPID_B.Add[0];

    /* Math: '<S143>/Math Function' */
    NLPID_B.MathFunction_g4[1] = NLPID_B.Add_e[1];

    /* Product: '<S139>/Divide2' */
    NLPID_B.Divide2[1] = NLPID_B.MathFunction_g4[1] / NLPID_B.Add_p;

    /* Math: '<S142>/Math Function' */
    NLPID_B.MathFunction_j[1] = NLPID_B.Add[1];

    /* Product: '<S139>/Product2' */
    tmp = NLPID_B.MathFunction_g4[0] * NLPID_B.Add[0];
    tmp += NLPID_B.MathFunction_g4[1] * NLPID_B.Add[1];
    NLPID_B.Product2_aa[0] = tmp * NLPID_B.MathFunction_j[0];
    NLPID_B.Product2_aa[1] = tmp * NLPID_B.MathFunction_j[1];

    /* Math: '<S139>/Math Function' incorporates:
     *  Constant: '<S139>/Constant'
     */
    if ((NLPID_B.Add_p < 0.0) && (NLPID_P.Constant_Value_ml > floor
         (NLPID_P.Constant_Value_ml))) {
      NLPID_B.MathFunction_gc = -rt_pow_snf(-NLPID_B.Add_p,
        NLPID_P.Constant_Value_ml);
    } else {
      NLPID_B.MathFunction_gc = rt_pow_snf(NLPID_B.Add_p,
        NLPID_P.Constant_Value_ml);
    }

    /* Product: '<S139>/Divide1' */
    NLPID_B.Divide1_m[0] = NLPID_B.Product2_aa[0] / NLPID_B.MathFunction_gc;

    /* Sum: '<S139>/Subtract1' */
    NLPID_B.Subtract1_f[0] = NLPID_B.Divide2[0] - NLPID_B.Divide1_m[0];

    /* Product: '<S139>/Divide1' */
    NLPID_B.Divide1_m[1] = NLPID_B.Product2_aa[1] / NLPID_B.MathFunction_gc;

    /* Sum: '<S139>/Subtract1' */
    NLPID_B.Subtract1_f[1] = NLPID_B.Divide2[1] - NLPID_B.Divide1_m[1];

    /* Product: '<S139>/Product' incorporates:
     *  Constant: '<S111>/my'
     */
    tmp = NLPID_P.my_Value * NLPID_B.Subtract1_f[0] * NLPID_B.Subtract_m[0];
    tmp += NLPID_P.my_Value * NLPID_B.Subtract1_f[1] * NLPID_B.Subtract_m[1];
    NLPID_B.Product_c = tmp;

    /* Sum: '<S139>/Subtract' */
    NLPID_B.Subtract_gr = NLPID_B.Product1_p - NLPID_B.Product_c;

    /* Sum: '<S135>/Sum' */
    NLPID_B.Sum_ou = (NLPID_B.Product1_hq - NLPID_B.Product3_n) -
      NLPID_B.Subtract_gr;

    /* Product: '<S62>/Product1' */
    NLPID_B.Product1_gt = NLPID_B.Subtract_g * NLPID_B.Sum_ou;

    /* Sum: '<S62>/Add' */
    NLPID_B.VectorConcatenate_d[2] = NLPID_B.Product_av + NLPID_B.Product1_gt;

    /* Sum: '<S104>/Add1' */
    NLPID_B.Add1_b[0] = NLPID_B.VectorConcatenate_l[0] +
      NLPID_B.VectorConcatenate_d[0];

    /* Product: '<S51>/Product1' */
    NLPID_B.Product1_km[0] = NLPID_B.Add1_b[0] * NLPID_B.Subtract_f;

    /* Sum: '<S104>/Add1' */
    NLPID_B.Add1_b[1] = NLPID_B.VectorConcatenate_l[1] +
      NLPID_B.VectorConcatenate_d[1];

    /* Product: '<S51>/Product1' */
    NLPID_B.Product1_km[1] = NLPID_B.Add1_b[1] * NLPID_B.Subtract_f;

    /* Sum: '<S104>/Add1' */
    NLPID_B.Add1_b[2] = NLPID_B.VectorConcatenate_l[2] +
      NLPID_B.VectorConcatenate_d[2];

    /* Product: '<S51>/Product1' */
    NLPID_B.Product1_km[2] = NLPID_B.Add1_b[2] * NLPID_B.Subtract_f;

    /* Trigonometry: '<S132>/Trigonometric Function' */
    NLPID_B.TrigonometricFunction_m = cos(NLPID_B.Gain1_d);

    /* Trigonometry: '<S132>/Trigonometric Function1' */
    NLPID_B.TrigonometricFunction1_j = sin(NLPID_B.Gain1_d);

    /* Derivative Block: '<S115>/Derivative' */
    {
      real_T t = NLPID_M->Timing.t[0];
      real_T timeStampA = NLPID_DWork.Derivative_RWORK_d.TimeStampA;
      real_T timeStampB = NLPID_DWork.Derivative_RWORK_d.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        NLPID_B.Derivative_d = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &NLPID_DWork.Derivative_RWORK_d.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 2;
          }
        } else if (timeStampA >= t) {
          lastBank += 2;
        }

        deltaT = t - *lastBank++;
        NLPID_B.Derivative_d = (NLPID_P.u_d_Value - *lastBank++) / deltaT;
      }
    }

    /* Product: '<S132>/Product' */
    NLPID_B.Product_ji[0] = NLPID_B.TrigonometricFunction_m *
      NLPID_B.Derivative_d;
    NLPID_B.Product_ji[1] = NLPID_B.TrigonometricFunction1_j *
      NLPID_B.Derivative_d;

    /* SignalConversion: '<S57>/ConcatBufferAtVector ConcatenateIn1' */
    NLPID_B.VectorConcatenate_p[0] = NLPID_B.Product_ji[0];
    NLPID_B.VectorConcatenate_p[1] = NLPID_B.Product_ji[1];

    /* Product: '<S57>/Product1' */
    tmp = NLPID_B.u[0] * NLPID_B.Product_ji[0];
    tmp += NLPID_B.u[1] * NLPID_B.Product_ji[1];
    NLPID_B.VectorConcatenate_p[2] = tmp;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Constant: '<S63>/0_2x1' */
      NLPID_B.VectorConcatenate_dx[0] = NLPID_P._2x1_Value_o[0];
      NLPID_B.VectorConcatenate_dx[1] = NLPID_P._2x1_Value_o[1];
    }

    /* Math: '<S136>/epsilon_n^2' */
    tmp = NLPID_B.MultiportSelector;
    NLPID_B.epsilon_n2_nl = tmp * tmp;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Math: '<S136>/Delta^2' incorporates:
       *  Constant: '<S111>/Delta'
       */
      tmp = NLPID_P.Delta_Value;
      NLPID_B.Delta2_f = tmp * tmp;
    }

    /* Sum: '<S136>/Add' */
    NLPID_B.Add_fq = NLPID_B.epsilon_n2_nl + NLPID_B.Delta2_f;

    /* Math: '<S136>/sqrt' */
    tmp = NLPID_B.Add_fq;
    if (tmp < 0.0) {
      NLPID_B.sqrt_a = -sqrt(-tmp);
    } else {
      NLPID_B.sqrt_a = sqrt(tmp);
    }

    /* Product: '<S136>/Divide' incorporates:
     *  Constant: '<S111>/Delta'
     */
    NLPID_B.Divide_d = NLPID_P.Delta_Value / NLPID_B.sqrt_a;

    /* Product: '<S191>/Divide' */
    NLPID_B.Divide_g = NLPID_B.Derivative_d / NLPID_B.Add_p;

    /* Product: '<S136>/Product' */
    NLPID_B.Product_h4 = NLPID_B.Divide_d * NLPID_B.Divide_g;

    /* Product: '<S63>/Product1' */
    NLPID_B.VectorConcatenate_dx[2] = NLPID_B.Subtract_g * NLPID_B.Product_h4;

    /* Sum: '<S105>/Add' */
    NLPID_B.Add_em[0] = NLPID_B.VectorConcatenate_p[0] +
      NLPID_B.VectorConcatenate_dx[0];

    /* Sum: '<S51>/Sum' */
    NLPID_B.Sum_b[0] = (NLPID_B.Product_gq[0] + NLPID_B.Product1_km[0]) +
      NLPID_B.Add_em[0];

    /* Sum: '<S105>/Add' */
    NLPID_B.Add_em[1] = NLPID_B.VectorConcatenate_p[1] +
      NLPID_B.VectorConcatenate_dx[1];

    /* Sum: '<S51>/Sum' */
    NLPID_B.Sum_b[1] = (NLPID_B.Product_gq[1] + NLPID_B.Product1_km[1]) +
      NLPID_B.Add_em[1];

    /* Sum: '<S105>/Add' */
    NLPID_B.Add_em[2] = NLPID_B.VectorConcatenate_p[2] +
      NLPID_B.VectorConcatenate_dx[2];

    /* Sum: '<S51>/Sum' */
    NLPID_B.Sum_b[2] = (NLPID_B.Product_gq[2] + NLPID_B.Product1_km[2]) +
      NLPID_B.Add_em[2];

    /* Product: '<S65>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + NLPID_B.MathFunction_l[3 *
          tmp_6] * NLPID_B.x3[i];
        tmp_2[i + 3 * tmp_6] = NLPID_B.MathFunction_l[3 * tmp_6 + 1] *
          NLPID_B.x3[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = NLPID_B.MathFunction_l[3 * tmp_6 + 2] *
          NLPID_B.x3[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      NLPID_B.Product_l0[i] = 0.0;
      NLPID_B.Product_l0[i] = tmp_2[i] * NLPID_B.Sum_b[0] + NLPID_B.Product_l0[i];
      NLPID_B.Product_l0[i] = tmp_2[i + 3] * NLPID_B.Sum_b[1] +
        NLPID_B.Product_l0[i];
      NLPID_B.Product_l0[i] = tmp_2[i + 6] * NLPID_B.Sum_b[2] +
        NLPID_B.Product_l0[i];
    }

    /* Gain: '<S64>/S12' */
    NLPID_B.S12 = NLPID_P.S12_Gain * NLPID_B.nu_yaw;

    /* Reshape: '<S64>/S(r)' incorporates:
     *  Constant: '<S64>/R31'
     *  Constant: '<S64>/S11'
     *  Constant: '<S64>/S13'
     *  Constant: '<S64>/S22'
     *  Constant: '<S64>/S23'
     *  Constant: '<S64>/S32'
     *  Constant: '<S64>/S33'
     */
    NLPID_B.Sr[0] = NLPID_P.S11_Value;
    NLPID_B.Sr[1] = NLPID_B.nu_yaw;
    NLPID_B.Sr[2] = NLPID_P.R31_Value_j;
    NLPID_B.Sr[3] = NLPID_B.S12;
    NLPID_B.Sr[4] = NLPID_P.S22_Value;
    NLPID_B.Sr[5] = NLPID_P.S32_Value;
    NLPID_B.Sr[6] = NLPID_P.S13_Value;
    NLPID_B.Sr[7] = NLPID_P.S23_Value;
    NLPID_B.Sr[8] = NLPID_P.S33_Value;

    /* Product: '<S65>/Product1' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + NLPID_B.Sr[3 * tmp_6] *
          NLPID_B.x3[i];
        tmp_2[i + 3 * tmp_6] = NLPID_B.Sr[3 * tmp_6 + 1] * NLPID_B.x3[i + 3] +
          tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = NLPID_B.Sr[3 * tmp_6 + 2] * NLPID_B.x3[i + 6] +
          tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_4[i + 3 * tmp_6] = 0.0;
        tmp_4[i + 3 * tmp_6] = tmp_4[3 * tmp_6 + i] + NLPID_B.MathFunction_l[3 *
          tmp_6] * tmp_2[i];
        tmp_4[i + 3 * tmp_6] = NLPID_B.MathFunction_l[3 * tmp_6 + 1] * tmp_2[i +
          3] + tmp_4[3 * tmp_6 + i];
        tmp_4[i + 3 * tmp_6] = NLPID_B.MathFunction_l[3 * tmp_6 + 2] * tmp_2[i +
          6] + tmp_4[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      NLPID_B.Product1_m[i] = 0.0;
      NLPID_B.Product1_m[i] = tmp_4[i] * NLPID_B.Add_fj[0] +
        NLPID_B.Product1_m[i];
      NLPID_B.Product1_m[i] = tmp_4[i + 3] * NLPID_B.Add_fj[1] +
        NLPID_B.Product1_m[i];
      NLPID_B.Product1_m[i] = tmp_4[i + 6] * NLPID_B.Add_fj[2] +
        NLPID_B.Product1_m[i];

      /* Sum: '<S65>/Subtract' */
      NLPID_B.Subtract_p[i] = NLPID_B.Product_l0[i] - NLPID_B.Product1_m[i];

      /* Gain: '<S65>/Gain' */
      NLPID_B.Gain_mx[i] = NLPID_P.Gain_Gain_g0 * NLPID_B.Subtract_p[i];

      /* Sum: '<S40>/Sum' */
      NLPID_B.Sum_hl[i] = (NLPID_B.Sum_a0[i] + NLPID_B.Product1_kq[i]) +
        NLPID_B.Gain_mx[i];
    }

    /* Product: '<S79>/Product' */
    for (i = 0; i < 5; i++) {
      NLPID_B.Product_bs[i] = 0.0;
      NLPID_B.Product_bs[i] = NLPID_B.Pseudoinverse_c[i] * NLPID_B.Sum_hl[0] +
        NLPID_B.Product_bs[i];
      NLPID_B.Product_bs[i] = NLPID_B.Pseudoinverse_c[i + 5] * NLPID_B.Sum_hl[1]
        + NLPID_B.Product_bs[i];
      NLPID_B.Product_bs[i] = NLPID_B.Pseudoinverse_c[i + 10] * NLPID_B.Sum_hl[2]
        + NLPID_B.Product_bs[i];
    }

    /* DeadZone Block: '<S80>/Dead Zone'
     */
    if (NLPID_B.Product_bs[0] >= NLPID_P.DeadZone_End_d) {
      NLPID_B.DeadZone_p = NLPID_B.Product_bs[0] - NLPID_P.DeadZone_End_d;
    } else if (NLPID_B.Product_bs[0] > NLPID_P.DeadZone_Start_g) {
      NLPID_B.DeadZone_p = 0.0;
    } else {
      NLPID_B.DeadZone_p = NLPID_B.Product_bs[0] - NLPID_P.DeadZone_Start_g;
    }

    /* RelationalOperator: '<S85>/Compare' incorporates:
     *  Constant: '<S85>/Constant'
     */
    NLPID_B.Compare_p = (NLPID_B.DeadZone_p < NLPID_P.Constant_Value_ip);

    /* RelationalOperator: '<S87>/Compare' */
    NLPID_B.Compare_ma = (NLPID_B.DeadZone_p == 0.0);

    /* Gain: '<S80>/Gain' */
    NLPID_B.Gain_gb = (uint16_T)(NLPID_P.Gain_Gain_p2 * NLPID_B.Compare_ma);

    /* RelationalOperator: '<S86>/Compare' incorporates:
     *  Constant: '<S86>/Constant'
     */
    NLPID_B.Compare_go = (NLPID_B.DeadZone_p > NLPID_P.Constant_Value_hk);

    /* Gain: '<S80>/Gain1' */
    NLPID_B.Gain1_cn = (uint16_T)(NLPID_P.Gain1_Gain_d * NLPID_B.Compare_go);

    /* Sum: '<S80>/Sum' */
    NLPID_B.Sum_c = (uint16_T)(uint32_T)(((NLPID_B.Compare_p << 6) +
      NLPID_B.Gain_gb) + NLPID_B.Gain1_cn);

    /* Lookup Block: '<S80>/f_1 < 0'
     * About '<S80>/f_1 < 0 :'
     * Lookup Block: '<S80>/f_1 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_10_j), NLPID_P.f_10_YData_g,
                         NLPID_B.Product_bs[0], NLPID_P.f_10_XData_n, 8U);

    /* Lookup Block: '<S80>/f_1 > 0'
     * About '<S80>/f_1 > 0 :'
     * Lookup Block: '<S80>/f_1 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_10_e), NLPID_P.f_10_YData_l,
                         NLPID_B.Product_bs[0], NLPID_P.f_10_XData_k, 9U);

    /* MultiPortSwitch: '<S80>/Multiport Switch' incorporates:
     *  Constant: '<S80>/f_1 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_c >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch_f = NLPID_B.f_10_j;
      break;

     case 2:
      NLPID_B.MultiportSwitch_f = NLPID_P.f_10_Value_g;
      break;

     default:
      NLPID_B.MultiportSwitch_f = NLPID_B.f_10_e;
      break;
    }

    /* DeadZone Block: '<S81>/Dead Zone'
     */
    if (NLPID_B.Product_bs[1] >= NLPID_P.DeadZone_End_b) {
      NLPID_B.DeadZone_c = NLPID_B.Product_bs[1] - NLPID_P.DeadZone_End_b;
    } else if (NLPID_B.Product_bs[1] > NLPID_P.DeadZone_Start_m) {
      NLPID_B.DeadZone_c = 0.0;
    } else {
      NLPID_B.DeadZone_c = NLPID_B.Product_bs[1] - NLPID_P.DeadZone_Start_m;
    }

    /* RelationalOperator: '<S88>/Compare' incorporates:
     *  Constant: '<S88>/Constant'
     */
    NLPID_B.Compare_g1 = (NLPID_B.DeadZone_c < NLPID_P.Constant_Value_hl);

    /* RelationalOperator: '<S89>/Compare' incorporates:
     *  Constant: '<S89>/Constant'
     */
    NLPID_B.Compare_jl = (NLPID_B.DeadZone_c == NLPID_P.Constant_Value_pg);

    /* Gain: '<S81>/Gain' */
    NLPID_B.Gain_b = (uint16_T)(NLPID_P.Gain_Gain_jh * NLPID_B.Compare_jl);

    /* RelationalOperator: '<S90>/Compare' incorporates:
     *  Constant: '<S90>/Constant'
     */
    NLPID_B.Compare_l1 = (NLPID_B.DeadZone_c > NLPID_P.Constant_Value_my);

    /* Gain: '<S81>/Gain1' */
    NLPID_B.Gain1_cm = (uint16_T)(NLPID_P.Gain1_Gain_cy * NLPID_B.Compare_l1);

    /* Sum: '<S81>/Sum' */
    NLPID_B.Sum_m3 = (uint16_T)(uint32_T)(((NLPID_B.Compare_g1 << 6) +
      NLPID_B.Gain_b) + NLPID_B.Gain1_cm);

    /* Lookup Block: '<S81>/f_2 < 0'
     * About '<S81>/f_2 < 0 :'
     * Lookup Block: '<S81>/f_2 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_20_p), NLPID_P.f_20_YData_nw,
                         NLPID_B.Product_bs[1], NLPID_P.f_20_XData_g, 10U);

    /* Lookup Block: '<S81>/f_2 > 0'
     * About '<S81>/f_2 > 0 :'
     * Lookup Block: '<S81>/f_2 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_20_l), NLPID_P.f_20_YData_f,
                         NLPID_B.Product_bs[1], NLPID_P.f_20_XData_a, 9U);

    /* MultiPortSwitch: '<S81>/Multiport Switch' incorporates:
     *  Constant: '<S81>/f_2 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_m3 >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch_fh = NLPID_B.f_20_p;
      break;

     case 2:
      NLPID_B.MultiportSwitch_fh = NLPID_P.f_20_Value_k;
      break;

     default:
      NLPID_B.MultiportSwitch_fh = NLPID_B.f_20_l;
      break;
    }

    /* DeadZone Block: '<S82>/Dead Zone'
     */
    if (NLPID_B.Product_bs[2] >= NLPID_P.DeadZone_End_n) {
      NLPID_B.DeadZone_h = NLPID_B.Product_bs[2] - NLPID_P.DeadZone_End_n;
    } else if (NLPID_B.Product_bs[2] > NLPID_P.DeadZone_Start_d) {
      NLPID_B.DeadZone_h = 0.0;
    } else {
      NLPID_B.DeadZone_h = NLPID_B.Product_bs[2] - NLPID_P.DeadZone_Start_d;
    }

    /* RelationalOperator: '<S91>/Compare' incorporates:
     *  Constant: '<S91>/Constant'
     */
    NLPID_B.Compare_jlz = (NLPID_B.DeadZone_h < NLPID_P.Constant_Value_la);

    /* RelationalOperator: '<S93>/Compare' */
    NLPID_B.Compare_g0 = (NLPID_B.DeadZone_h == 0.0);

    /* Gain: '<S82>/Gain' */
    NLPID_B.Gain_ef = (uint16_T)(NLPID_P.Gain_Gain_ej * NLPID_B.Compare_g0);

    /* RelationalOperator: '<S92>/Compare' incorporates:
     *  Constant: '<S92>/Constant'
     */
    NLPID_B.Compare_hr = (NLPID_B.DeadZone_h > NLPID_P.Constant_Value_d2);

    /* Gain: '<S82>/Gain1' */
    NLPID_B.Gain1_k = (uint16_T)(NLPID_P.Gain1_Gain_e * NLPID_B.Compare_hr);

    /* Sum: '<S82>/Sum' */
    NLPID_B.Sum_d = (uint16_T)(uint32_T)(((NLPID_B.Compare_jlz << 6) +
      NLPID_B.Gain_ef) + NLPID_B.Gain1_k);

    /* Lookup Block: '<S82>/f_3 < 0'
     * About '<S82>/f_3 < 0 :'
     * Lookup Block: '<S82>/f_3 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_30_d), NLPID_P.f_30_YData_i,
                         NLPID_B.Product_bs[2], NLPID_P.f_30_XData_g, 7U);

    /* Lookup Block: '<S82>/f_3 > 0'
     * About '<S82>/f_3 > 0 :'
     * Lookup Block: '<S82>/f_3 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_30_h), NLPID_P.f_30_YData_f,
                         NLPID_B.Product_bs[2], NLPID_P.f_30_XData_e, 10U);

    /* MultiPortSwitch: '<S82>/Multiport Switch' incorporates:
     *  Constant: '<S82>/f_3 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_d >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch_l = NLPID_B.f_30_d;
      break;

     case 2:
      NLPID_B.MultiportSwitch_l = NLPID_P.f_30_Value_b;
      break;

     default:
      NLPID_B.MultiportSwitch_l = NLPID_B.f_30_h;
      break;
    }

    /* DeadZone Block: '<S83>/Dead Zone'
     */
    if (NLPID_B.Product_bs[3] >= NLPID_P.DeadZone_End_h) {
      NLPID_B.DeadZone_pp = NLPID_B.Product_bs[3] - NLPID_P.DeadZone_End_h;
    } else if (NLPID_B.Product_bs[3] > NLPID_P.DeadZone_Start_my) {
      NLPID_B.DeadZone_pp = 0.0;
    } else {
      NLPID_B.DeadZone_pp = NLPID_B.Product_bs[3] - NLPID_P.DeadZone_Start_my;
    }

    /* RelationalOperator: '<S94>/Compare' incorporates:
     *  Constant: '<S94>/Constant'
     */
    NLPID_B.Compare_a = (NLPID_B.DeadZone_pp < NLPID_P.Constant_Value_o);

    /* RelationalOperator: '<S96>/Compare' */
    NLPID_B.Compare_gq = (NLPID_B.DeadZone_pp == 0.0);

    /* Gain: '<S83>/Gain' */
    NLPID_B.Gain_nf = (uint16_T)(NLPID_P.Gain_Gain_an * NLPID_B.Compare_gq);

    /* RelationalOperator: '<S95>/Compare' incorporates:
     *  Constant: '<S95>/Constant'
     */
    NLPID_B.Compare_j1 = (NLPID_B.DeadZone_pp > NLPID_P.Constant_Value_dl);

    /* Gain: '<S83>/Gain1' */
    NLPID_B.Gain1_h = (uint16_T)(NLPID_P.Gain1_Gain_j3 * NLPID_B.Compare_j1);

    /* Sum: '<S83>/Sum' */
    NLPID_B.Sum_kv = (uint16_T)(uint32_T)(((NLPID_B.Compare_a << 6) +
      NLPID_B.Gain_nf) + NLPID_B.Gain1_h);

    /* Lookup Block: '<S83>/f_4 < 0'
     * About '<S83>/f_4 < 0 :'
     * Lookup Block: '<S83>/f_4 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_40_fz), NLPID_P.f_40_YData_e,
                         NLPID_B.Product_bs[3], NLPID_P.f_40_XData_n, 9U);

    /* Lookup Block: '<S83>/f_4 > 0'
     * About '<S83>/f_4 > 0 :'
     * Lookup Block: '<S83>/f_4 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_40_n), NLPID_P.f_40_YData_a,
                         NLPID_B.Product_bs[3], NLPID_P.f_40_XData_j, 6U);

    /* MultiPortSwitch: '<S83>/Multiport Switch' incorporates:
     *  Constant: '<S83>/f_4 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_kv >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch_e = NLPID_B.f_40_fz;
      break;

     case 2:
      NLPID_B.MultiportSwitch_e = NLPID_P.f_40_Value_a;
      break;

     default:
      NLPID_B.MultiportSwitch_e = NLPID_B.f_40_n;
      break;
    }

    /* DeadZone Block: '<S84>/Dead Zone'
     */
    if (NLPID_B.Product_bs[4] >= NLPID_P.DeadZone_End_m5) {
      NLPID_B.DeadZone_pa = NLPID_B.Product_bs[4] - NLPID_P.DeadZone_End_m5;
    } else if (NLPID_B.Product_bs[4] > NLPID_P.DeadZone_Start_lo) {
      NLPID_B.DeadZone_pa = 0.0;
    } else {
      NLPID_B.DeadZone_pa = NLPID_B.Product_bs[4] - NLPID_P.DeadZone_Start_lo;
    }

    /* RelationalOperator: '<S97>/Compare' incorporates:
     *  Constant: '<S97>/Constant'
     */
    NLPID_B.Compare_c = (NLPID_B.DeadZone_pa < NLPID_P.Constant_Value_c5);

    /* RelationalOperator: '<S99>/Compare' */
    NLPID_B.Compare_f = (NLPID_B.DeadZone_pa == 0.0);

    /* Gain: '<S84>/Gain' */
    NLPID_B.Gain_nx = (uint16_T)(NLPID_P.Gain_Gain_fw * NLPID_B.Compare_f);

    /* RelationalOperator: '<S98>/Compare' incorporates:
     *  Constant: '<S98>/Constant'
     */
    NLPID_B.Compare_js = (NLPID_B.DeadZone_pa > NLPID_P.Constant_Value_gc);

    /* Gain: '<S84>/Gain1' */
    NLPID_B.Gain1_cx = (uint16_T)(NLPID_P.Gain1_Gain_lh * NLPID_B.Compare_js);

    /* Sum: '<S84>/Sum' */
    NLPID_B.Sum_hs = (uint16_T)(uint32_T)(((NLPID_B.Compare_c << 6) +
      NLPID_B.Gain_nx) + NLPID_B.Gain1_cx);

    /* Lookup Block: '<S84>/f_5 < 0'
     * About '<S84>/f_5 < 0 :'
     * Lookup Block: '<S84>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_50_n), NLPID_P.f_50_YData_p,
                         NLPID_B.Product_bs[4], NLPID_P.f_50_XData_e, 2U);

    /* Lookup Block: '<S84>/f_5 > 0'
     * About '<S84>/f_5 > 0 :'
     * Lookup Block: '<S84>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPID_B.f_50_g), NLPID_P.f_50_YData_pp,
                         NLPID_B.Product_bs[4], NLPID_P.f_50_XData_p, 2U);

    /* MultiPortSwitch: '<S84>/Multiport Switch' incorporates:
     *  Constant: '<S84>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPID_B.Sum_hs >> 6)) {
     case 1:
      NLPID_B.MultiportSwitch_lr = NLPID_B.f_50_n;
      break;

     case 2:
      NLPID_B.MultiportSwitch_lr = NLPID_P.f_50_Value_b;
      break;

     default:
      NLPID_B.MultiportSwitch_lr = NLPID_B.f_50_g;
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
    switch ((int32_T)NLPID_P.ControlMode_Value) {
     case 0:
      NLPID_B.ThrustersettingSwitch[0] = NLPID_B.u_1;
      NLPID_B.ThrustersettingSwitch[1] = NLPID_B.u_2;
      NLPID_B.ThrustersettingSwitch[2] = NLPID_B.u_3;
      NLPID_B.ThrustersettingSwitch[3] = NLPID_B.u_4;
      NLPID_B.ThrustersettingSwitch[4] = NLPID_B.u_5;
      NLPID_B.ThrustersettingSwitch[5] = NLPID_P.PS3_BT_Power_Value;
      NLPID_B.ThrustersettingSwitch[6] = NLPID_P.PS3_VSP_Speed_Value;
      break;

     case 1:
      for (i = 0; i < 5; i++) {
        NLPID_B.ThrustersettingSwitch[i] = NLPID_B.Saturation_kt[i];
      }

      NLPID_B.ThrustersettingSwitch[5] = NLPID_P.BT_power_limit_Value;
      NLPID_B.ThrustersettingSwitch[6] = NLPID_P.VSP_speeds_Value;
      break;

     default:
      NLPID_B.ThrustersettingSwitch[0] = NLPID_B.MultiportSwitch_f;
      NLPID_B.ThrustersettingSwitch[1] = NLPID_B.MultiportSwitch_fh;
      NLPID_B.ThrustersettingSwitch[2] = NLPID_B.MultiportSwitch_l;
      NLPID_B.ThrustersettingSwitch[3] = NLPID_B.MultiportSwitch_e;
      NLPID_B.ThrustersettingSwitch[4] = NLPID_B.MultiportSwitch_lr;
      NLPID_B.ThrustersettingSwitch[5] = NLPID_P.BT_power_limit_Value_n;
      NLPID_B.ThrustersettingSwitch[6] = NLPID_P.VSP_speeds_Value_l;
      break;
    }

    /* Saturate: '<S1>/Saturation' */
    for (i = 0; i < 7; i++) {
      tmp = NLPID_B.ThrustersettingSwitch[i];
      NLPID_B.Saturation_f[i] = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat_ll,
        NLPID_P.Saturation_UpperSat_j2);
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Gain: '<S109>/-l_x1' incorporates:
       *  Constant: '<S109>/l_x1'
       */
      NLPID_B.l_x1_e = NLPID_P.l_x1_Gain_n * NLPID_P.l_x1_Value_j;

      /* Gain: '<S109>/-l_y2' incorporates:
       *  Constant: '<S109>/l_y2'
       */
      NLPID_B.l_y2_g = NLPID_P.l_y2_Gain_h * NLPID_P.l_y2_Value_ne;

      /* Gain: '<S109>/-l_x2' incorporates:
       *  Constant: '<S109>/l_x2'
       */
      NLPID_B.l_x2_a = NLPID_P.l_x2_Gain_po * NLPID_P.l_x2_Value_p;

      /* Reshape: '<S109>/3x5' incorporates:
       *  Constant: '<S109>/T_e11'
       *  Constant: '<S109>/T_e12'
       *  Constant: '<S109>/T_e13'
       *  Constant: '<S109>/T_e14'
       *  Constant: '<S109>/T_e15'
       *  Constant: '<S109>/T_e21'
       *  Constant: '<S109>/T_e22'
       *  Constant: '<S109>/T_e23'
       *  Constant: '<S109>/T_e24'
       *  Constant: '<S109>/T_e25'
       *  Constant: '<S109>/l_x3'
       *  Constant: '<S109>/l_y1'
       */
      NLPID_B.x5_a[0] = NLPID_P.T_e11_Value_od;
      NLPID_B.x5_a[1] = NLPID_P.T_e21_Value_k;
      NLPID_B.x5_a[2] = NLPID_P.l_y1_Value_k;
      NLPID_B.x5_a[3] = NLPID_P.T_e12_Value_j;
      NLPID_B.x5_a[4] = NLPID_P.T_e22_Value_n;
      NLPID_B.x5_a[5] = NLPID_B.l_x1_e;
      NLPID_B.x5_a[6] = NLPID_P.T_e13_Value_ai;
      NLPID_B.x5_a[7] = NLPID_P.T_e23_Value_b;
      NLPID_B.x5_a[8] = NLPID_B.l_y2_g;
      NLPID_B.x5_a[9] = NLPID_P.T_e14_Value_mp;
      NLPID_B.x5_a[10] = NLPID_P.T_e24_Value_c;
      NLPID_B.x5_a[11] = NLPID_B.l_x2_a;
      NLPID_B.x5_a[12] = NLPID_P.T_e15_Value_l;
      NLPID_B.x5_a[13] = NLPID_P.T_e25_Value_n;
      NLPID_B.x5_a[14] = NLPID_P.l_x3_Value_e;

      /* Lookup Block: '<S108>/u_1 to f_1'
       * About '<S108>/u_1 to f_1 :'
       * Lookup Block: '<S108>/u_1 to f_1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPID_B.u_1tof_1), NLPID_P.u_1tof_1_YData,
                           NLPID_B.u_1, NLPID_P.u_1tof_1_XData, 18U);

      /* Lookup Block: '<S108>/u_2 to f_2'
       * About '<S108>/u_2 to f_2 :'
       * Lookup Block: '<S108>/u_2 to f_2'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPID_B.u_2tof_2), NLPID_P.u_2tof_2_YData,
                           NLPID_B.u_2, NLPID_P.u_2tof_2_XData, 20U);

      /* Lookup Block: '<S108>/u_3 to f_3'
       * About '<S108>/u_3 to f_3 :'
       * Lookup Block: '<S108>/u_3 to f_3'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPID_B.u_3tof_3), NLPID_P.u_3tof_3_YData,
                           NLPID_B.u_3, NLPID_P.u_3tof_3_XData, 18U);

      /* Lookup Block: '<S108>/u_4 to f_4'
       * About '<S108>/u_4 to f_4 :'
       * Lookup Block: '<S108>/u_4 to f_4'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPID_B.u_4tof_4), NLPID_P.u_4tof_4_YData,
                           NLPID_B.u_4, NLPID_P.u_4tof_4_XData, 16U);

      /* Lookup Block: '<S108>/u_5 to f_5'
       * About '<S108>/u_5 to f_5 :'
       * Lookup Block: '<S108>/u_5 to f_5'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPID_B.u_5tof_5), NLPID_P.u_5tof_5_YData,
                           NLPID_B.u_5, NLPID_P.u_5tof_5_XData, 6U);

      /* SignalConversion: '<S107>/TmpHiddenBufferAtProductInport2' */
      NLPID_B.TmpHiddenBufferAtProductInpor_f[0] = NLPID_B.u_1tof_1;
      NLPID_B.TmpHiddenBufferAtProductInpor_f[1] = NLPID_B.u_2tof_2;
      NLPID_B.TmpHiddenBufferAtProductInpor_f[2] = NLPID_B.u_3tof_3;
      NLPID_B.TmpHiddenBufferAtProductInpor_f[3] = NLPID_B.u_4tof_4;
      NLPID_B.TmpHiddenBufferAtProductInpor_f[4] = NLPID_B.u_5tof_5;

      /* Product: '<S107>/Product' */
      for (i = 0; i < 3; i++) {
        NLPID_B.Product_fy[i] = 0.0;
        for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
          NLPID_B.Product_fy[i] = NLPID_B.x5_a[3 * tmp_6 + i] *
            NLPID_B.TmpHiddenBufferAtProductInpor_f[tmp_6] +
            NLPID_B.Product_fy[i];
        }
      }
    }

    /* MultiPortSwitch: '<S1>/tau Switch' incorporates:
     *  Constant: '<S1>/Control Mode'
     */
    switch ((int32_T)NLPID_P.ControlMode_Value) {
     case 0:
      NLPID_B.tauSwitch[0] = NLPID_B.Product_fy[0];
      NLPID_B.tauSwitch[1] = NLPID_B.Product_fy[1];
      NLPID_B.tauSwitch[2] = NLPID_B.Product_fy[2];
      break;

     case 1:
      NLPID_B.tauSwitch[0] = NLPID_B.Sum1_p[0];
      NLPID_B.tauSwitch[1] = NLPID_B.Sum1_p[1];
      NLPID_B.tauSwitch[2] = NLPID_B.Sum1_p[2];
      break;

     default:
      NLPID_B.tauSwitch[0] = NLPID_B.Sum_hl[0];
      NLPID_B.tauSwitch[1] = NLPID_B.Sum_hl[1];
      NLPID_B.tauSwitch[2] = NLPID_B.Sum_hl[2];
      break;
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* SignalConversion: '<Root>/TmpHiddenBufferAtTo FileInport1' incorporates:
       *  Constant: '<S114>/Path Selector'
       *  Constant: '<S194>/u_d'
       *  Constant: '<S1>/Control Mode'
       *  Constant: '<S4>/Controller Input Selector'
       */
      NLPID_B.TmpHiddenBufferAtToFileInport1[0] =
        NLPID_P.ControllerInputSelector_Value;
      NLPID_B.TmpHiddenBufferAtToFileInport1[1] = NLPID_B.QTMIn2Error;
      NLPID_B.TmpHiddenBufferAtToFileInport1[2] = NLPID_B.QTMIn9Residual;
      NLPID_B.TmpHiddenBufferAtToFileInport1[3] = NLPID_B.etadot_surge;
      NLPID_B.TmpHiddenBufferAtToFileInport1[4] = NLPID_B.etadot_sway;
      NLPID_B.TmpHiddenBufferAtToFileInport1[5] = NLPID_B.etadot_yaw;
      NLPID_B.TmpHiddenBufferAtToFileInport1[6] = NLPID_B.eta_surge;
      NLPID_B.TmpHiddenBufferAtToFileInport1[7] = NLPID_B.eta_sway;
      NLPID_B.TmpHiddenBufferAtToFileInport1[8] = NLPID_B.eta_yaw;
      NLPID_B.TmpHiddenBufferAtToFileInport1[9] = NLPID_B.nu_surge;
      NLPID_B.TmpHiddenBufferAtToFileInport1[10] = NLPID_B.nu_sway;
      NLPID_B.TmpHiddenBufferAtToFileInport1[11] = NLPID_B.nu_yaw;
      NLPID_B.TmpHiddenBufferAtToFileInport1[12] = NLPID_B.eta_dDPN;
      NLPID_B.TmpHiddenBufferAtToFileInport1[13] = NLPID_B.eta_dDPE;
      NLPID_B.TmpHiddenBufferAtToFileInport1[14] = NLPID_B.eta_dDPPsi;
      NLPID_B.TmpHiddenBufferAtToFileInport1[15] = NLPID_B.q_x;
      NLPID_B.TmpHiddenBufferAtToFileInport1[16] = NLPID_B.q_y;
      NLPID_B.TmpHiddenBufferAtToFileInport1[17] = NLPID_B.psi_los;
      NLPID_B.TmpHiddenBufferAtToFileInport1[18] = NLPID_P.PathSelector_Value;
      NLPID_B.TmpHiddenBufferAtToFileInport1[19] = NLPID_B.pathx_d;
      NLPID_B.TmpHiddenBufferAtToFileInport1[20] = NLPID_B.pathy_d;
      NLPID_B.TmpHiddenBufferAtToFileInport1[21] = NLPID_B.pathpsi_d;
      NLPID_B.TmpHiddenBufferAtToFileInport1[22] = NLPID_P.u_d_Value;
      NLPID_B.TmpHiddenBufferAtToFileInport1[23] = NLPID_B.Divide;
      NLPID_B.TmpHiddenBufferAtToFileInport1[24] = NLPID_B.Integrator1;
      NLPID_B.TmpHiddenBufferAtToFileInport1[25] = NLPID_P.ControlMode_Value;
      for (i = 0; i < 7; i++) {
        NLPID_B.TmpHiddenBufferAtToFileInport1[i + 26] = NLPID_B.Saturation_f[i];
      }

      NLPID_B.TmpHiddenBufferAtToFileInport1[33] = NLPID_B.tauSwitch[0];
      NLPID_B.TmpHiddenBufferAtToFileInport1[34] = NLPID_B.tauSwitch[1];
      NLPID_B.TmpHiddenBufferAtToFileInport1[35] = NLPID_B.tauSwitch[2];

      /* ToFile Block: '<Root>/To File'
       */
      if (rtmIsMajorTimeStep(NLPID_M)) {
        if (!(++NLPID_DWork.ToFile_IWORK.Decimation % 1) &&
            (NLPID_DWork.ToFile_IWORK.Count*37)+1 < 100000000 ) {
          real_T u[37];
          FILE *fp = (FILE *) NLPID_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            NLPID_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = NLPID_M->Timing.t[1];
            u[1] = NLPID_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = NLPID_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = NLPID_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = NLPID_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = NLPID_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = NLPID_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = NLPID_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = NLPID_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = NLPID_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = NLPID_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = NLPID_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = NLPID_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = NLPID_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = NLPID_B.TmpHiddenBufferAtToFileInport1[13];
            u[15] = NLPID_B.TmpHiddenBufferAtToFileInport1[14];
            u[16] = NLPID_B.TmpHiddenBufferAtToFileInport1[15];
            u[17] = NLPID_B.TmpHiddenBufferAtToFileInport1[16];
            u[18] = NLPID_B.TmpHiddenBufferAtToFileInport1[17];
            u[19] = NLPID_B.TmpHiddenBufferAtToFileInport1[18];
            u[20] = NLPID_B.TmpHiddenBufferAtToFileInport1[19];
            u[21] = NLPID_B.TmpHiddenBufferAtToFileInport1[20];
            u[22] = NLPID_B.TmpHiddenBufferAtToFileInport1[21];
            u[23] = NLPID_B.TmpHiddenBufferAtToFileInport1[22];
            u[24] = NLPID_B.TmpHiddenBufferAtToFileInport1[23];
            u[25] = NLPID_B.TmpHiddenBufferAtToFileInport1[24];
            u[26] = NLPID_B.TmpHiddenBufferAtToFileInport1[25];
            u[27] = NLPID_B.TmpHiddenBufferAtToFileInport1[26];
            u[28] = NLPID_B.TmpHiddenBufferAtToFileInport1[27];
            u[29] = NLPID_B.TmpHiddenBufferAtToFileInport1[28];
            u[30] = NLPID_B.TmpHiddenBufferAtToFileInport1[29];
            u[31] = NLPID_B.TmpHiddenBufferAtToFileInport1[30];
            u[32] = NLPID_B.TmpHiddenBufferAtToFileInport1[31];
            u[33] = NLPID_B.TmpHiddenBufferAtToFileInport1[32];
            u[34] = NLPID_B.TmpHiddenBufferAtToFileInport1[33];
            u[35] = NLPID_B.TmpHiddenBufferAtToFileInport1[34];
            u[36] = NLPID_B.TmpHiddenBufferAtToFileInport1[35];
            if (fwrite(u, sizeof(real_T), 37, fp) != 37) {
              rtmSetErrorStatus(NLPID_M,
                                "Error writing to MAT-file CSE1_NLPID_data.mat");
              return;
            }

            if (((++NLPID_DWork.ToFile_IWORK.Count)*37)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file CSE1_NLPID_data.mat.\n");
            }
          }
        }
      }

      /* Reshape: '<S42>/2x2' incorporates:
       *  Constant: '<S42>/12'
       *  Constant: '<S42>/21'
       *  Constant: '<S7>/Gamma_q_Surge'
       *  Constant: '<S7>/Gamma_q_Sway'
       */
      NLPID_B.x2[0] = NLPID_P.Gamma_q_Surge_Value;
      NLPID_B.x2[1] = NLPID_P.u_Value_h;
      NLPID_B.x2[2] = NLPID_P.u_Value_fv;
      NLPID_B.x2[3] = NLPID_P.Gamma_q_Sway_Value;
    }

    /* Product: '<S43>/Product' */
    for (i = 0; i < 3; i++) {
      NLPID_B.Product_cb[i] = 0.0;
      NLPID_B.Product_cb[i] = NLPID_B.Rpsi[i] * NLPID_B.Subtract_c[0] +
        NLPID_B.Product_cb[i];
      NLPID_B.Product_cb[i] = NLPID_B.Rpsi[i + 3] * NLPID_B.Subtract_c[1] +
        NLPID_B.Product_cb[i];
      NLPID_B.Product_cb[i] = NLPID_B.Rpsi[i + 6] * NLPID_B.Subtract_c[2] +
        NLPID_B.Product_cb[i];
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
    }

    /* Concatenate: '<S122>/Matrix Concatenate' incorporates:
     *  Constant: '<S128>/Constant'
     */
    NLPID_B.MatrixConcatenate_k[0] = NLPID_P.Constant_Value_od[0];
    NLPID_B.MatrixConcatenate_k[1] = NLPID_P.Constant_Value_od[1];
    NLPID_B.MatrixConcatenate_k[3] = NLPID_P.Constant_Value_od[2];
    NLPID_B.MatrixConcatenate_k[4] = NLPID_P.Constant_Value_od[3];
    NLPID_B.MatrixConcatenate_k[2] = NLPID_B.u[0];
    NLPID_B.MatrixConcatenate_k[5] = NLPID_B.u[1];

    /* Math: '<S101>/Math Function' */
    for (i = 0; i < 3; i++) {
      NLPID_B.MathFunction_an[i << 1] = NLPID_B.MatrixConcatenate_k[i];
      NLPID_B.MathFunction_an[1 + (i << 1)] = NLPID_B.MatrixConcatenate_k[i + 3];
    }

    /* Product: '<S50>/Product2' */
    for (i = 0; i < 2; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_5[i + (tmp_6 << 1)] = 0.0;
        tmp_5[i + (tmp_6 << 1)] = tmp_5[(tmp_6 << 1) + i] + NLPID_B.Rpsi_b[3 *
          tmp_6] * NLPID_B.MathFunction_an[i];
        tmp_5[i + (tmp_6 << 1)] = NLPID_B.Rpsi_b[3 * tmp_6 + 1] *
          NLPID_B.MathFunction_an[i + 2] + tmp_5[(tmp_6 << 1) + i];
        tmp_5[i + (tmp_6 << 1)] = NLPID_B.Rpsi_b[3 * tmp_6 + 2] *
          NLPID_B.MathFunction_an[i + 4] + tmp_5[(tmp_6 << 1) + i];
      }
    }

    for (i = 0; i < 2; i++) {
      NLPID_B.Product2_k[i] = 0.0;
      NLPID_B.Product2_k[i] = tmp_5[i] *
        NLPID_B.TmpHiddenBufferAtProductInport3[0] + NLPID_B.Product2_k[i];
      NLPID_B.Product2_k[i] = tmp_5[i + 2] *
        NLPID_B.TmpHiddenBufferAtProductInport3[1] + NLPID_B.Product2_k[i];
      NLPID_B.Product2_k[i] = tmp_5[i + 4] *
        NLPID_B.TmpHiddenBufferAtProductInport3[2] + NLPID_B.Product2_k[i];
    }

    /* Product: '<S50>/Product3' */
    NLPID_B.Product3_g[0] = 0.0;
    NLPID_B.Product3_g[0] = NLPID_B.x2[0] * NLPID_B.Product2_k[0] +
      NLPID_B.Product3_g[0];
    NLPID_B.Product3_g[0] = NLPID_B.x2[2] * NLPID_B.Product2_k[1] +
      NLPID_B.Product3_g[0];

    /* Sum: '<S50>/Subtract' */
    NLPID_B.Subtract_o2[0] = NLPID_B.omega_q[0] - NLPID_B.Product3_g[0];

    /* Product: '<S50>/Product1' incorporates:
     *  Constant: '<S7>/lambda'
     */
    NLPID_B.Product1_as[0] = NLPID_P.lambda_Value * NLPID_B.Subtract_o2[0];

    /* Gain: '<S50>/dot omega_q' */
    NLPID_B.dotomega_q[0] = NLPID_P.dotomega_q_Gain * NLPID_B.Product1_as[0];

    /* Product: '<S50>/Product3' */
    NLPID_B.Product3_g[1] = 0.0;
    NLPID_B.Product3_g[1] = NLPID_B.x2[1] * NLPID_B.Product2_k[0] +
      NLPID_B.Product3_g[1];
    NLPID_B.Product3_g[1] = NLPID_B.x2[3] * NLPID_B.Product2_k[1] +
      NLPID_B.Product3_g[1];

    /* Sum: '<S50>/Subtract' */
    NLPID_B.Subtract_o2[1] = NLPID_B.omega_q[1] - NLPID_B.Product3_g[1];

    /* Product: '<S50>/Product1' incorporates:
     *  Constant: '<S7>/lambda'
     */
    NLPID_B.Product1_as[1] = NLPID_P.lambda_Value * NLPID_B.Subtract_o2[1];

    /* Gain: '<S50>/dot omega_q' */
    NLPID_B.dotomega_q[1] = NLPID_P.dotomega_q_Gain * NLPID_B.Product1_as[1];
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Constant: '<S122>/0_2x1' */
      NLPID_B.VectorConcatenate1[0] = NLPID_P._2x1_Value_m[0];
      NLPID_B.VectorConcatenate1[1] = NLPID_P._2x1_Value_m[1];
    }

    /* SignalConversion: '<S122>/ConcatBufferAtVector Concatenate1In2' */
    NLPID_B.VectorConcatenate1[2] = NLPID_B.Subtract_g;
    if (rtmIsMajorTimeStep(NLPID_M)) {
      /* Gain: '<S3>/Battery Bow Thruster' */
      NLPID_B.BatteryBowThruster = NLPID_P.BatteryBowThruster_Gain *
        NLPID_B.SITzAI0;

      /* Gain: '<S3>/Battery Servo' */
      NLPID_B.BatteryServo = NLPID_P.BatteryServo_Gain * NLPID_B.SITzAI1;

      /* Gain: '<S3>/Battery Main' */
      NLPID_B.BatteryMain = NLPID_P.BatteryMain_Gain * NLPID_B.SITzAI2;
    }

    /* Gain: '<S196>/QTM In1 FPS' */
    NLPID_B.QTMIn1FPS = NLPID_P.QTMIn1FPS_Gain * NLPID_B.QTMIn[0];

    /* Saturate: '<S200>/Saturation' */
    tmp = NLPID_B.tauSwitch[0];
    NLPID_B.Saturation_f5 = rt_SATURATE(tmp, NLPID_P.Saturation_LowerSat_op,
      NLPID_P.Saturation_UpperSat_js);

    /* Saturate: '<S200>/Saturation1' */
    tmp = NLPID_B.tauSwitch[1];
    NLPID_B.Saturation1 = rt_SATURATE(tmp, NLPID_P.Saturation1_LowerSat,
      NLPID_P.Saturation1_UpperSat);

    /* Saturate: '<S200>/Saturation2' */
    tmp = NLPID_B.tauSwitch[2];
    NLPID_B.Saturation2 = rt_SATURATE(tmp, NLPID_P.Saturation2_LowerSat,
      NLPID_P.Saturation2_UpperSat);

    /* Gain: '<S200>/plant tau_surge' */
    NLPID_B.planttau_surge = NLPID_P.planttau_surge_Gain * NLPID_B.Saturation_f5;

    /* Gain: '<S200>/plant tau_sway' */
    NLPID_B.planttau_sway = NLPID_P.planttau_sway_Gain * NLPID_B.Saturation1;

    /* Gain: '<S200>/plant tau_yaw' */
    NLPID_B.planttau_yaw = NLPID_P.planttau_yaw_Gain * NLPID_B.Saturation2;

    /* Gain: '<S5>/plant u_1' */
    NLPID_B.plantu_1 = NLPID_P.plantu_1_Gain * NLPID_B.Saturation_f[0];

    /* Gain: '<S5>/plant u_2' */
    NLPID_B.plantu_2 = NLPID_P.plantu_2_Gain * NLPID_B.Saturation_f[1];

    /* Gain: '<S5>/plant u_3' */
    NLPID_B.plantu_3 = NLPID_P.plantu_3_Gain * NLPID_B.Saturation_f[2];

    /* Gain: '<S5>/plant u_4' */
    NLPID_B.plantu_4 = NLPID_P.plantu_4_Gain * NLPID_B.Saturation_f[3];

    /* Gain: '<S5>/plant u_5' */
    NLPID_B.plantu_5 = NLPID_P.plantu_5_Gain * NLPID_B.Saturation_f[4];

    /* Gain: '<S5>/plant BT power' */
    NLPID_B.plantBTpower = NLPID_P.plantBTpower_Gain * NLPID_B.Saturation_f[5];

    /* Gain: '<S5>/plant VSP speed' */
    NLPID_B.plantVSPspeed = NLPID_P.plantVSPspeed_Gain * NLPID_B.Saturation_f[6];

    /* Outputs for enable SubSystem: '<S5>/CSE1' incorporates:
     *  Constant: '<S5>/Enable CSE1'
     *  EnablePort: '<S198>/Enable'
     */
    if (rtmIsMajorTimeStep(NLPID_M) && rtmIsMajorTimeStep(NLPID_M)) {
      if (NLPID_P.EnableCSE1_Value > 0.0) {
        if (NLPID_DWork.CSE1_MODE == SUBSYS_DISABLED) {
          NLPID_DWork.CSE1_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (NLPID_DWork.CSE1_MODE == SUBSYS_ENABLED) {
          NLPID_DWork.CSE1_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (NLPID_DWork.CSE1_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S201>/BT_D_Gain1' */
      NLPID_B.BT_D_Gain1 = NLPID_P.BT_D_Gain1_Gain * NLPID_B.plantu_5;

      /* Gain: '<S201>/BT_D_Gain2' */
      NLPID_B.BT_D_Gain2 = NLPID_P.BT_D_Gain2_Gain * NLPID_B.plantu_5;

      /* Sum: '<S201>/Add' incorporates:
       *  Constant: '<S201>/BT_Power_Offset1'
       */
      NLPID_B.Add_af = (NLPID_B.BT_D_Gain1 + NLPID_P.BT_Power_Offset1_Value) +
        NLPID_B.BT_D_Gain2;

      /* Gain: '<S201>/BT_L_Gain1' */
      NLPID_B.BT_L_Gain1 = NLPID_P.BT_L_Gain1_Gain * NLPID_B.plantBTpower;

      /* Gain: '<S201>/BT_L_Gain2' */
      NLPID_B.BT_L_Gain2 = NLPID_P.BT_L_Gain2_Gain * NLPID_B.plantBTpower;

      /* Gain: '<S201>/Neg' */
      NLPID_B.Neg = NLPID_P.Neg_Gain * NLPID_B.plantBTpower;
      if (rtmIsMajorTimeStep(NLPID_M)) {
      }

      /* Sum: '<S201>/Sum1' incorporates:
       *  Constant: '<S201>/BT_Power_Offset2'
       */
      NLPID_B.Sum1_nf = NLPID_B.BT_L_Gain1 + NLPID_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S203>/LowerRelop1' */
      NLPID_B.LowerRelop1_e = (NLPID_B.Add_af > NLPID_B.Sum1_nf);

      /* Sum: '<S201>/Sum2' incorporates:
       *  Constant: '<S201>/BT_Power_Offset3'
       */
      NLPID_B.Sum2 = NLPID_B.BT_L_Gain2 + NLPID_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S203>/UpperRelop' */
      NLPID_B.UpperRelop_p = (NLPID_B.Add_af < NLPID_B.Sum2);

      /* Switch: '<S203>/Switch' */
      if (NLPID_B.UpperRelop_p) {
        NLPID_B.Switch_j = NLPID_B.Sum2;
      } else {
        NLPID_B.Switch_j = NLPID_B.Add_af;
      }

      /* Switch: '<S203>/Switch2' */
      if (NLPID_B.LowerRelop1_e) {
        NLPID_B.Switch2_e = NLPID_B.Sum1_nf;
      } else {
        NLPID_B.Switch2_e = NLPID_B.Switch_j;
      }

      if (rtmIsMajorTimeStep(NLPID_M)) {
      }

      /* RelationalOperator: '<S204>/LowerRelop1' incorporates:
       *  Constant: '<S201>/Constant'
       */
      NLPID_B.LowerRelop1_h = (NLPID_B.plantu_5 > NLPID_P.Constant_Value_a);

      /* RelationalOperator: '<S204>/UpperRelop' */
      NLPID_B.UpperRelop_o = (NLPID_B.plantu_5 < NLPID_B.Neg);

      /* Switch: '<S204>/Switch' */
      if (NLPID_B.UpperRelop_o) {
        NLPID_B.Switch_i = NLPID_B.Neg;
      } else {
        NLPID_B.Switch_i = NLPID_B.plantu_5;
      }

      /* Switch: '<S204>/Switch2' incorporates:
       *  Constant: '<S201>/Constant'
       */
      if (NLPID_B.LowerRelop1_h) {
        NLPID_B.Switch2_i = NLPID_P.Constant_Value_a;
      } else {
        NLPID_B.Switch2_i = NLPID_B.Switch_i;
      }

      if (rtmIsMajorTimeStep(NLPID_M)) {
      }

      /* RelationalOperator: '<S205>/LowerRelop1' */
      NLPID_B.LowerRelop1_i = (NLPID_B.plantu_5 > NLPID_B.plantBTpower);

      /* RelationalOperator: '<S205>/UpperRelop' incorporates:
       *  Constant: '<S201>/Constant1'
       */
      NLPID_B.UpperRelop_l = (NLPID_B.plantu_5 < NLPID_P.Constant1_Value_c);

      /* Switch: '<S205>/Switch' incorporates:
       *  Constant: '<S201>/Constant1'
       */
      if (NLPID_B.UpperRelop_l) {
        NLPID_B.Switch_e = NLPID_P.Constant1_Value_c;
      } else {
        NLPID_B.Switch_e = NLPID_B.plantu_5;
      }

      /* Switch: '<S205>/Switch2' */
      if (NLPID_B.LowerRelop1_i) {
        NLPID_B.Switch2_o = NLPID_B.plantBTpower;
      } else {
        NLPID_B.Switch2_o = NLPID_B.Switch_e;
      }

      /* Signum: '<S202>/Sign' */
      NLPID_B.Sign_c = rt_SIGNd_snf(NLPID_B.plantVSPspeed);

      /* Product: '<S202>/Product1' */
      NLPID_B.PortVPS_X = NLPID_B.plantu_2 * NLPID_B.Sign_c;

      /* Gain: '<S202>/-x' */
      NLPID_B.PortVPS_X_l = NLPID_P.x_Gain * NLPID_B.PortVPS_X;

      /* Product: '<S202>/Product2' */
      NLPID_B.PortVSP_Y = NLPID_B.plantu_1 * NLPID_B.Sign_c;

      /* Gain: '<S202>/-y' */
      NLPID_B.PortVSP_Y_c = NLPID_P.y_Gain * NLPID_B.PortVSP_Y;

      /* Product: '<S202>/Product3' */
      NLPID_B.StarboardVSP_X = NLPID_B.plantu_4 * NLPID_B.Sign_c;

      /* Product: '<S202>/Product4' */
      NLPID_B.StarboardVSP_Y = NLPID_B.plantu_3 * NLPID_B.Sign_c;

      /* Lookup2D: '<S202>/Servo1' */
      NLPID_B.Servo1 = rt_Lookup2D_Normal((const real_T *)
        (&NLPID_P.Servo1_RowIdx[0]), 3, (const real_T *)(&NLPID_P.Servo1_ColIdx
        [0]), 3, (const real_T *)(&NLPID_P.Servo1_Table[0]), (const real_T)
        NLPID_B.PortVPS_X_l, (const real_T)NLPID_B.PortVSP_Y_c);

      /* Lookup2D: '<S202>/Servo2' */
      NLPID_B.Servo2 = rt_Lookup2D_Normal((const real_T *)
        (&NLPID_P.Servo2_RowIdx[0]), 3, (const real_T *)(&NLPID_P.Servo2_ColIdx
        [0]), 3, (const real_T *)(&NLPID_P.Servo2_Table[0]), (const real_T)
        NLPID_B.PortVPS_X_l, (const real_T)NLPID_B.PortVSP_Y_c);

      /* Lookup2D: '<S202>/Servo3' */
      NLPID_B.Servo3 = rt_Lookup2D_Normal((const real_T *)
        (&NLPID_P.Servo3_RowIdx[0]), 3, (const real_T *)(&NLPID_P.Servo3_ColIdx
        [0]), 3, (const real_T *)(&NLPID_P.Servo3_Table[0]), (const real_T)
        NLPID_B.StarboardVSP_X, (const real_T)NLPID_B.StarboardVSP_Y);

      /* Lookup2D: '<S202>/Servo4' */
      NLPID_B.Servo4 = rt_Lookup2D_Normal((const real_T *)
        (&NLPID_P.Servo4_RowIdx[0]), 3, (const real_T *)(&NLPID_P.Servo4_ColIdx
        [0]), 3, (const real_T *)(&NLPID_P.Servo4_Table[0]), (const real_T)
        NLPID_B.StarboardVSP_X, (const real_T)NLPID_B.StarboardVSP_Y);

      /* Gain: '<S202>/VPS_Speed_Gain' */
      NLPID_B.VPS_Speed_Gain = NLPID_P.VPS_Speed_Gain_Gain *
        NLPID_B.plantVSPspeed;

      /* Sum: '<S202>/Sum' incorporates:
       *  Constant: '<S202>/VPS_Power_Offset'
       */
      NLPID_B.Sum_bl = NLPID_B.VPS_Speed_Gain + NLPID_P.VPS_Power_Offset_Value;

      /* Gain: '<S202>/VSPS Port' */
      NLPID_B.VSPSPort = NLPID_P.VSPSPort_Gain * NLPID_B.Sum_bl;

      /* Gain: '<S202>/VSPS Starboard' */
      NLPID_B.VSPSStarboard = NLPID_P.VSPSStarboard_Gain * NLPID_B.Sum_bl;
    }

    /* end of Outputs for SubSystem: '<S5>/CSE1' */

    /* Gain: '<Root>/eta_psi' */
    NLPID_B.eta_psi = NLPID_P.eta_psi_Gain * NLPID_B.eta_yaw;

    /* Gain: '<Root>/eta_psid' */
    NLPID_B.eta_psid = NLPID_P.eta_psid_Gain * NLPID_B.pathpsi_d;

    /* Gain: '<Root>/eta_x' */
    NLPID_B.eta_x = NLPID_P.eta_x_Gain * NLPID_B.eta_surge;

    /* Gain: '<Root>/eta_xd' */
    NLPID_B.eta_xd = NLPID_P.eta_xd_Gain * NLPID_B.pathx_d;

    /* Gain: '<Root>/eta_y' */
    NLPID_B.eta_y = NLPID_P.eta_y_Gain * NLPID_B.eta_sway;

    /* Gain: '<Root>/eta_yd' */
    NLPID_B.eta_yd = NLPID_P.eta_yd_Gain * NLPID_B.pathy_d;

    /* Gain: '<Root>/psi_los' */
    NLPID_B.psi_los_l = NLPID_P.psi_los_Gain_h * NLPID_B.psi_los;

    /* Gain: '<Root>/psi_plot' */
    NLPID_B.psi_plot[0] = NLPID_P.psi_plot_Gain * NLPID_B.eta_psi;
    NLPID_B.psi_plot[1] = NLPID_P.psi_plot_Gain * NLPID_B.psi_los_l;
    NLPID_B.psi_plot[2] = NLPID_P.psi_plot_Gain * NLPID_B.eta_psid;

    /* Gain: '<Root>/q_x' */
    NLPID_B.q_x_f = NLPID_P.q_x_Gain_f * NLPID_B.q_x;

    /* Gain: '<Root>/q_y' */
    NLPID_B.q_y_j = NLPID_P.q_y_Gain_j * NLPID_B.q_y;

    /* Gain: '<Root>/x_plot' */
    NLPID_B.x_plot[0] = NLPID_P.x_plot_Gain * NLPID_B.eta_x;
    NLPID_B.x_plot[1] = NLPID_P.x_plot_Gain * NLPID_B.q_x_f;
    NLPID_B.x_plot[2] = NLPID_P.x_plot_Gain * NLPID_B.eta_xd;

    /* Gain: '<Root>/y_plot' */
    NLPID_B.y_plot[0] = NLPID_P.y_plot_Gain * NLPID_B.eta_y;
    NLPID_B.y_plot[1] = NLPID_P.y_plot_Gain * NLPID_B.q_y_j;
    NLPID_B.y_plot[2] = NLPID_P.y_plot_Gain * NLPID_B.eta_yd;
    if (rtmIsMajorTimeStep(NLPID_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void NLPID_update(int_T tid)
{
  {
    int32_T tmp;

    /* Derivative Block: '<S196>/Derivative1' */
    {
      real_T timeStampA = NLPID_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = NLPID_DWork.Derivative1_RWORK.TimeStampB;
      real_T *lastBank = &NLPID_DWork.Derivative1_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 4;
        } else if (timeStampA >= timeStampB) {
          lastBank += 4;
        }
      }

      *lastBank++ = NLPID_M->Timing.t[0];
      *lastBank++ = NLPID_B.mm2mx;
      *lastBank++ = NLPID_B.mm2my;
      *lastBank++ = NLPID_B.d2ryaw;
    }

    /* Update for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S199>/Enable'
     */
    if (NLPID_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Sum: '<S206>/Sum' */
      NLPID_B.Sum_e[0] = NLPID_B.planttau_surge - NLPID_B.Product1_o4[0];
      NLPID_B.Sum_e[1] = NLPID_B.planttau_sway - NLPID_B.Product1_o4[1];
      NLPID_B.Sum_e[2] = NLPID_B.planttau_yaw - NLPID_B.Product1_o4[2];

      /* Product: '<S206>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        NLPID_B.Product2_kw[tmp] = 0.0;
        NLPID_B.Product2_kw[tmp] = NLPID_B.Inverse[tmp] * NLPID_B.Sum_e[0] +
          NLPID_B.Product2_kw[tmp];
        NLPID_B.Product2_kw[tmp] = NLPID_B.Inverse[tmp + 3] * NLPID_B.Sum_e[1] +
          NLPID_B.Product2_kw[tmp];
        NLPID_B.Product2_kw[tmp] = NLPID_B.Inverse[tmp + 6] * NLPID_B.Sum_e[2] +
          NLPID_B.Product2_kw[tmp];
      }
    }

    /* end of Update for SubSystem: '<S5>/Linear Simulator' */

    /* Derivative Block: '<S196>/Derivative' */
    {
      real_T timeStampA = NLPID_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = NLPID_DWork.Derivative_RWORK.TimeStampB;
      real_T *lastBank = &NLPID_DWork.Derivative_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = NLPID_M->Timing.t[0];
      *lastBank++ = NLPID_B.mm2mx;
      *lastBank++ = NLPID_B.mm2my;
      *lastBank++ = NLPID_B.mm2mz;
      *lastBank++ = NLPID_B.d2rroll;
      *lastBank++ = NLPID_B.d2rpitch;
      *lastBank++ = NLPID_B.d2ryaw;
    }

    /* Derivative Block: '<S115>/Derivative' */
    {
      real_T timeStampA = NLPID_DWork.Derivative_RWORK_d.TimeStampA;
      real_T timeStampB = NLPID_DWork.Derivative_RWORK_d.TimeStampB;
      real_T *lastBank = &NLPID_DWork.Derivative_RWORK_d.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 2;
        } else if (timeStampA >= timeStampB) {
          lastBank += 2;
        }
      }

      *lastBank++ = NLPID_M->Timing.t[0];
      *lastBank++ = NLPID_P.u_d_Value;
    }

    if (rtmIsMajorTimeStep(NLPID_M)) {
    }
  }

  if (rtmIsMajorTimeStep(NLPID_M)) {
    rt_ertODEUpdateContinuousStates(&NLPID_M->solverInfo);
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
  if (!(++NLPID_M->Timing.clockTick0))
    ++NLPID_M->Timing.clockTickH0;
  NLPID_M->Timing.t[0] = NLPID_M->Timing.clockTick0 * NLPID_M->Timing.stepSize0
    + NLPID_M->Timing.clockTickH0 * NLPID_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(NLPID_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++NLPID_M->Timing.clockTick1))
      ++NLPID_M->Timing.clockTickH1;
    NLPID_M->Timing.t[1] = NLPID_M->Timing.clockTick1 *
      NLPID_M->Timing.stepSize1 + NLPID_M->Timing.clockTickH1 *
      NLPID_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void NLPID_derivatives(void)
{
  {
    int32_T tmp;

    /* Derivatives for enable SubSystem: '<S5>/Linear Simulator' */
    if (NLPID_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Sum: '<S206>/Sum' */
      NLPID_B.Sum_e[0] = NLPID_B.planttau_surge - NLPID_B.Product1_o4[0];
      NLPID_B.Sum_e[1] = NLPID_B.planttau_sway - NLPID_B.Product1_o4[1];
      NLPID_B.Sum_e[2] = NLPID_B.planttau_yaw - NLPID_B.Product1_o4[2];

      /* Product: '<S206>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        NLPID_B.Product2_kw[tmp] = 0.0;
        NLPID_B.Product2_kw[tmp] = NLPID_B.Inverse[tmp] * NLPID_B.Sum_e[0] +
          NLPID_B.Product2_kw[tmp];
        NLPID_B.Product2_kw[tmp] = NLPID_B.Inverse[tmp + 3] * NLPID_B.Sum_e[1] +
          NLPID_B.Product2_kw[tmp];
        NLPID_B.Product2_kw[tmp] = NLPID_B.Inverse[tmp + 6] * NLPID_B.Sum_e[2] +
          NLPID_B.Product2_kw[tmp];
      }

      /* Integrator Block: '<S206>/Integrator' */
      {
        if (NLPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator_CSTATE_l[0] = NLPID_B.Product2_kw[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator_CSTATE_l[0] = 0.0;
        }

        if (NLPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator_CSTATE_l[1] = NLPID_B.Product2_kw[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator_CSTATE_l[1] = 0.0;
        }

        if (NLPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator_CSTATE_l[2] = NLPID_B.Product2_kw[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator_CSTATE_l[2] = 0.0;
        }
      }

      /* Integrator Block: '<S206>/Integrator1' */
      {
        if (NLPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator1_CSTATE_i[0] = NLPID_B.Product3_fn[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator1_CSTATE_i[0] = 0.0;
        }

        if (NLPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator1_CSTATE_i[1] = NLPID_B.Product3_fn[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator1_CSTATE_i[1] = 0.0;
        }

        if (NLPID_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator1_CSTATE_i[2] = NLPID_B.Product3_fn[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
            ->Integrator1_CSTATE_i[2] = 0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
               ->Integrator_CSTATE_l[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S5>/Linear Simulator' */

    /* Integrator Block: '<S50>/Integrator' */
    {
      if (NLPID_P.Resetq_Value== 0.0) {
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = NLPID_B.Add_ic[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = 0.0;
      }

      if (NLPID_P.Resetq_Value== 0.0) {
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = NLPID_B.Add_ic[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = 0.0;
      }
    }

    /* Integrator Block: '<S50>/Integrator1' */
    {
      if (NLPID_P.Resets_Value== 0.0) {
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator1_CSTATE = NLPID_B.Subtract_f;
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator1_CSTATE = 0.0;
      }
    }

    /* Integrator Block: '<S10>/Integrator' */
    {
      if (NLPID_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE_m[0] = NLPID_B.TmpHiddenBufferAtKpInport1[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE_m[0] = 0.0;
      }

      if (NLPID_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE_m[1] = NLPID_B.TmpHiddenBufferAtKpInport1[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE_m[1] = 0.0;
      }

      if (NLPID_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE_m[2] = NLPID_B.TmpHiddenBufferAtKpInport1[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)
          ->Integrator_CSTATE_m[2] = 0.0;
      }
    }

    /* Derivatives for Integrator: '<S7>/zeta' */
    ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)->zeta_CSTATE[0] =
      NLPID_B.Product_cb[0];
    ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)->zeta_CSTATE[1] =
      NLPID_B.Product_cb[1];
    ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)->zeta_CSTATE[2] =
      NLPID_B.Product_cb[2];

    /* Derivatives for Integrator: '<S50>/omega_q' */
    ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)->omega_q_CSTATE[0] =
      NLPID_B.dotomega_q[0];
    ((StateDerivatives_NLPID *) NLPID_M->ModelData.derivs)->omega_q_CSTATE[1] =
      NLPID_B.dotomega_q[1];
  }
}

/* Model initialize function */
void NLPID_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)NLPID_M,0,
                sizeof(RT_MODEL_NLPID));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&NLPID_M->solverInfo, &NLPID_M->Timing.simTimeStep);
    rtsiSetTPtr(&NLPID_M->solverInfo, &rtmGetTPtr(NLPID_M));
    rtsiSetStepSizePtr(&NLPID_M->solverInfo, &NLPID_M->Timing.stepSize0);
    rtsiSetdXPtr(&NLPID_M->solverInfo, &NLPID_M->ModelData.derivs);
    rtsiSetContStatesPtr(&NLPID_M->solverInfo, &NLPID_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&NLPID_M->solverInfo, &NLPID_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&NLPID_M->solverInfo, (&rtmGetErrorStatus(NLPID_M)));
    rtsiSetRTModelPtr(&NLPID_M->solverInfo, NLPID_M);
  }

  rtsiSetSimTimeStep(&NLPID_M->solverInfo, MAJOR_TIME_STEP);
  NLPID_M->ModelData.intgData.y = NLPID_M->ModelData.odeY;
  NLPID_M->ModelData.intgData.f[0] = NLPID_M->ModelData.odeF[0];
  NLPID_M->ModelData.intgData.f[1] = NLPID_M->ModelData.odeF[1];
  NLPID_M->ModelData.intgData.f[2] = NLPID_M->ModelData.odeF[2];
  NLPID_M->ModelData.intgData.f[3] = NLPID_M->ModelData.odeF[3];
  NLPID_M->ModelData.intgData.f[4] = NLPID_M->ModelData.odeF[4];
  NLPID_M->ModelData.intgData.f[5] = NLPID_M->ModelData.odeF[5];
  NLPID_M->ModelData.contStates = ((real_T *) &NLPID_X);
  rtsiSetSolverData(&NLPID_M->solverInfo, (void *)&NLPID_M->ModelData.intgData);
  rtsiSetSolverName(&NLPID_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = NLPID_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    NLPID_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    NLPID_M->Timing.sampleTimes = (&NLPID_M->Timing.sampleTimesArray[0]);
    NLPID_M->Timing.offsetTimes = (&NLPID_M->Timing.offsetTimesArray[0]);

    /* task periods */
    NLPID_M->Timing.sampleTimes[0] = (0.0);
    NLPID_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    NLPID_M->Timing.offsetTimes[0] = (0.0);
    NLPID_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(NLPID_M, &NLPID_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = NLPID_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    NLPID_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(NLPID_M, -1);
  NLPID_M->Timing.stepSize0 = 0.1;
  NLPID_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(NLPID_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    NLPID_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(NLPID_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(NLPID_M->rtwLogInfo, (NULL));
    rtliSetLogT(NLPID_M->rtwLogInfo, "");
    rtliSetLogX(NLPID_M->rtwLogInfo, "");
    rtliSetLogXFinal(NLPID_M->rtwLogInfo, "");
    rtliSetSigLog(NLPID_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(NLPID_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(NLPID_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(NLPID_M->rtwLogInfo, 0);
    rtliSetLogDecimation(NLPID_M->rtwLogInfo, 1);
    rtliSetLogY(NLPID_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(NLPID_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(NLPID_M->rtwLogInfo, (NULL));
  }

  NLPID_M->solverInfoPtr = (&NLPID_M->solverInfo);
  NLPID_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&NLPID_M->solverInfo, 0.1);
  rtsiSetSolverMode(&NLPID_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  NLPID_M->ModelData.blockIO = ((void *) &NLPID_B);
  (void) memset(((void *) &NLPID_B),0,
                sizeof(BlockIO_NLPID));

  /* parameters */
  NLPID_M->ModelData.defaultParam = ((real_T *) &NLPID_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &NLPID_X;
    NLPID_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_NLPID));
  }

  /* states (dwork) */
  NLPID_M->Work.dwork = ((void *) &NLPID_DWork);
  (void) memset((void *)&NLPID_DWork, 0,
                sizeof(D_Work_NLPID));
  NLPID_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  NLPID_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  NLPID_PrevZCSigState.Integrator_Reset_ZCE_d = UNINITIALIZED_ZCSIG;
  NLPID_PrevZCSigState.Integrator_Reset_ZCE_c = UNINITIALIZED_ZCSIG;
  NLPID_PrevZCSigState.Integrator1_Reset_ZCE_o = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void NLPID_terminate(void)
{
  /* ToFile Block: '<Root>/To File' */
  {
    FILE *fp = (FILE *) NLPID_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_NLPID_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(NLPID_M, "Error closing MAT-file CSE1_NLPID_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(NLPID_M,
                          "Error reopening MAT-file CSE1_NLPID_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 37, NLPID_DWork.ToFile_IWORK.Count,
           "cse1_NLPID_data")) {
        rtmSetErrorStatus(NLPID_M,
                          "Error writing header for cse1_NLPID_data to MAT-file CSE1_NLPID_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(NLPID_M, "Error closing MAT-file CSE1_NLPID_data.mat");
        return;
      }

      NLPID_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  NLPID_output(tid);
}

void MdlUpdate(int_T tid)
{
  NLPID_update(tid);
}

void MdlInitializeSizes(void)
{
  NLPID_M->Sizes.numContStates = (17); /* Number of continuous states */
  NLPID_M->Sizes.numY = (0);           /* Number of model outputs */
  NLPID_M->Sizes.numU = (0);           /* Number of model inputs */
  NLPID_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  NLPID_M->Sizes.numSampTimes = (2);   /* Number of sample times */
  NLPID_M->Sizes.numBlocks = (1004);   /* Number of blocks */
  NLPID_M->Sizes.numBlockIO = (716);   /* Number of block outputs */
  NLPID_M->Sizes.numBlockPrms = (1148);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* Derivative Block: '<S196>/Derivative1' */
  NLPID_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  NLPID_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* Derivative Block: '<S196>/Derivative' */
  NLPID_DWork.Derivative_RWORK.TimeStampA = rtInf;
  NLPID_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* Integrator Block: '<S50>/Integrator' */
  if (rtmIsFirstInitCond(NLPID_M)) {
    NLPID_X.Integrator_CSTATE[0] = 0.0;
    NLPID_X.Integrator_CSTATE[1] = 0.0;
  }

  NLPID_DWork.Integrator_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S50>/Integrator1' */
  if (rtmIsFirstInitCond(NLPID_M)) {
    NLPID_X.Integrator1_CSTATE = 0.0;
  }

  NLPID_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S10>/Integrator' */
  NLPID_X.Integrator_CSTATE_m[0] = NLPID_P.Integrator_IC;
  NLPID_X.Integrator_CSTATE_m[1] = NLPID_P.Integrator_IC;
  NLPID_X.Integrator_CSTATE_m[2] = NLPID_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<S7>/zeta' */
  NLPID_X.zeta_CSTATE[0] = NLPID_P.zeta_IC;
  NLPID_X.zeta_CSTATE[1] = NLPID_P.zeta_IC;
  NLPID_X.zeta_CSTATE[2] = NLPID_P.zeta_IC;

  /* InitializeConditions for Integrator: '<S50>/omega_q' */
  NLPID_X.omega_q_CSTATE[0] = NLPID_P.omega_q_IC;
  NLPID_X.omega_q_CSTATE[1] = NLPID_P.omega_q_IC;

  /* Derivative Block: '<S115>/Derivative' */
  NLPID_DWork.Derivative_RWORK_d.TimeStampA = rtInf;
  NLPID_DWork.Derivative_RWORK_d.TimeStampB = rtInf;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(NLPID_M)) {
    rtmSetFirstInitCond(NLPID_M, 0);
  }
}

void MdlStart(void)
{
  /* Start for enable SubSystem: '<S5>/Linear Simulator' */
  NLPID_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

  /* Start for Constant: '<S208>/psi_0' */
  NLPID_B.psi_0 = NLPID_P.psi_0_Value;

  /* Start for Constant: '<S208>/x_0' */
  NLPID_B.x_0 = NLPID_P.x_0_Value;

  /* Start for Constant: '<S208>/y_0' */
  NLPID_B.y_0 = NLPID_P.y_0_Value;

  /* Start for Constant: '<S209>/r_0' */
  NLPID_B.r_0 = NLPID_P.r_0_Value;

  /* Start for Constant: '<S209>/u_0' */
  NLPID_B.u_0 = NLPID_P.u_0_Value;

  /* Start for Constant: '<S209>/v_0' */
  NLPID_B.v_0 = NLPID_P.v_0_Value;

  /* Create Identity Matrix for Block: '<S210>/Inverse' */
  {
    int_T i;
    real_T *dWork = &NLPID_DWork.Inverse_DWORK4[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &NLPID_DWork.Inverse_DWORK4[0];
    while (dWork < &NLPID_DWork.Inverse_DWORK4[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  /* Integrator Block: '<S206>/Integrator' */
  if (rtmIsFirstInitCond(NLPID_M)) {
    NLPID_X.Integrator_CSTATE_l[0] = 0.0;
    NLPID_X.Integrator_CSTATE_l[1] = 0.0;
    NLPID_X.Integrator_CSTATE_l[2] = 0.0;
  }

  NLPID_DWork.Integrator_IWORK_k.IcNeedsLoading = 1;

  /* Integrator Block: '<S206>/Integrator1' */
  if (rtmIsFirstInitCond(NLPID_M)) {
    NLPID_X.Integrator1_CSTATE_i[0] = 0.0;
    NLPID_X.Integrator1_CSTATE_i[1] = 0.0;
    NLPID_X.Integrator1_CSTATE_i[2] = 0.0;
  }

  NLPID_DWork.Integrator1_IWORK_o.IcNeedsLoading = 1;

  /* end of Start for SubSystem: '<S5>/Linear Simulator' */

  /* Start for Constant: '<S102>/q_x_0' */
  NLPID_B.q_x_0 = NLPID_P.q_x_0_Value;

  /* Start for Constant: '<S102>/q_y_0' */
  NLPID_B.q_y_0 = NLPID_P.q_y_0_Value;

  /* Start for Constant: '<S50>/s_0' */
  NLPID_B.s_0 = NLPID_P.s_0_Value;

  /* ToFile Block: '<Root>/To File' */
  {
    const char *fileName = "CSE1_NLPID_data.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(NLPID_M, "Error creating .mat file CSE1_NLPID_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,37,0,"cse1_NLPID_data")) {
      rtmSetErrorStatus(NLPID_M,
                        "Error writing mat file header to file CSE1_NLPID_data.mat");
      return;
    }

    NLPID_DWork.ToFile_IWORK.Count = 0;
    NLPID_DWork.ToFile_IWORK.Decimation = -1;
    NLPID_DWork.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for enable SubSystem: '<S5>/CSE1' */
  NLPID_DWork.CSE1_MODE = SUBSYS_DISABLED;

  /* end of Start for SubSystem: '<S5>/CSE1' */
  MdlInitialize();
}

RT_MODEL_NLPID *NLPID(void)
{
  NLPID_initialize(1);
  return NLPID_M;
}

void MdlTerminate(void)
{
  NLPID_terminate();
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
#ifdef NI_ROOTMODEL_NLPID
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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 77:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 77:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern NLPID_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Naviagation Systems/Qualisys 6 DOF/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(NLPID_B.QTMIn, count, data[index++], 44, 0);
    }
  } else {
    index += 9;
  }

  // HMI/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&NLPID_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&NLPID_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&NLPID_B.SITzAI2, 0, data[index++], 0, 0);
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
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Switch2_e,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.VSPSStarboard,0,0,0);
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
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Switch2_e,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Servo1,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Servo2,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Servo3,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.Servo4,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.VSPSPort,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPID_B.VSPSStarboard,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "nlpid/Naviagation Systems/Controller Input Selector/Value", offsetof
    (Parameters_NLPID, ControllerInputSelector_Value), 21, 1, 2, 0, "", 0 },

  { 1, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain", offsetof
    (Parameters_NLPID, QTMIn2Error_Gain), 21, 1, 2, 2, "", 0 },

  { 2, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain",
    offsetof(Parameters_NLPID, QTMIn9Residual_Gain), 21, 1, 2, 4, "", 0 },

  { 3, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain", offsetof
    (Parameters_NLPID, QTMIn3_Gain), 21, 1, 2, 6, "", 0 },

  { 4, "nlpid/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain", offsetof
    (Parameters_NLPID, mm2mx_Gain), 21, 1, 2, 8, "", 0 },

  { 5, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain", offsetof
    (Parameters_NLPID, QTMIn4_Gain), 21, 1, 2, 10, "", 0 },

  { 6, "nlpid/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain", offsetof
    (Parameters_NLPID, mm2my_Gain), 21, 1, 2, 12, "", 0 },

  { 7, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain", offsetof
    (Parameters_NLPID, QTMIn6_Gain), 21, 1, 2, 14, "", 0 },

  { 8, "nlpid/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain", offsetof
    (Parameters_NLPID, d2ryaw_Gain), 21, 1, 2, 16, "", 0 },

  { 9, "nlpid/Plants/Enable Linear Simulator/Value", offsetof(Parameters_NLPID,
    EnableLinearSimulator_Value), 21, 1, 2, 18, "", 0 },

  { 10, "nlpid/Naviagation Systems/etadot_surge/Gain", offsetof(Parameters_NLPID,
    etadot_surge_Gain), 21, 1, 2, 20, "", 0 },

  { 11, "nlpid/Naviagation Systems/etadot_sway/Gain", offsetof(Parameters_NLPID,
    etadot_sway_Gain), 21, 1, 2, 22, "", 0 },

  { 12, "nlpid/Naviagation Systems/etadot_yaw/Gain", offsetof(Parameters_NLPID,
    etadot_yaw_Gain), 21, 1, 2, 24, "", 0 },

  { 13, "nlpid/Naviagation Systems/eta_surge/Gain", offsetof(Parameters_NLPID,
    eta_surge_Gain), 21, 1, 2, 26, "", 0 },

  { 14, "nlpid/Naviagation Systems/eta_sway/Gain", offsetof(Parameters_NLPID,
    eta_sway_Gain), 21, 1, 2, 28, "", 0 },

  { 15, "nlpid/Naviagation Systems/eta_yaw/Gain", offsetof(Parameters_NLPID,
    eta_yaw_Gain), 21, 1, 2, 30, "", 0 },

  { 16, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain", offsetof
    (Parameters_NLPID, QTMIn8_Gain), 21, 1, 2, 32, "", 0 },

  { 17, "nlpid/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain", offsetof
    (Parameters_NLPID, d2rroll_Gain), 21, 1, 2, 34, "", 0 },

  { 18, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain", offsetof
    (Parameters_NLPID, QTMIn7_Gain), 21, 1, 2, 36, "", 0 },

  { 19, "nlpid/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain", offsetof
    (Parameters_NLPID, d2rpitch_Gain), 21, 1, 2, 38, "", 0 },

  { 20, "nlpid/Naviagation Systems/Qualisys 6 DOF/Constant1/Value", offsetof
    (Parameters_NLPID, Constant1_Value), 36, 9, 2, 40, "", 0 },

  { 21, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain", offsetof
    (Parameters_NLPID, QTMIn5_Gain), 21, 1, 2, 42, "", 0 },

  { 22, "nlpid/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain", offsetof
    (Parameters_NLPID, mm2mz_Gain), 21, 1, 2, 44, "", 0 },

  { 23, "nlpid/Naviagation Systems/nu_surge/Gain", offsetof(Parameters_NLPID,
    nu_surge_Gain), 21, 1, 2, 46, "", 0 },

  { 24, "nlpid/Naviagation Systems/nu_sway/Gain", offsetof(Parameters_NLPID,
    nu_sway_Gain), 21, 1, 2, 48, "", 0 },

  { 25, "nlpid/Naviagation Systems/nu_yaw/Gain", offsetof(Parameters_NLPID,
    nu_yaw_Gain), 21, 1, 2, 50, "", 0 },

  { 26, "nlpid/HMI/DP Input/x_d/Value", offsetof(Parameters_NLPID, x_d_Value),
    21, 1, 2, 52, "", 0 },

  { 27, "nlpid/Guidance Systems/DP/eta_d DP N/Gain", offsetof(Parameters_NLPID,
    eta_dDPN_Gain), 21, 1, 2, 54, "", 0 },

  { 28, "nlpid/HMI/DP Input/y_d/Value", offsetof(Parameters_NLPID, y_d_Value),
    21, 1, 2, 56, "", 0 },

  { 29, "nlpid/Guidance Systems/DP/eta_d DP E/Gain", offsetof(Parameters_NLPID,
    eta_dDPE_Gain), 21, 1, 2, 58, "", 0 },

  { 30, "nlpid/HMI/DP Input/psi_d/Value", offsetof(Parameters_NLPID, psi_d_Value),
    21, 1, 2, 60, "", 0 },

  { 31, "nlpid/HMI/DP Input/Degrees to Radians/Gain1/Gain", offsetof
    (Parameters_NLPID, Gain1_Gain), 21, 1, 2, 62, "", 0 },

  { 32, "nlpid/Guidance Systems/DP/eta_d DP Psi/Gain", offsetof(Parameters_NLPID,
    eta_dDPPsi_Gain), 21, 1, 2, 64, "", 0 },

  { 33, "nlpid/Control Systems/Nonlinear PID/Update laws/Reset q/Value",
    offsetof(Parameters_NLPID, Resetq_Value), 21, 1, 2, 66, "", 0 },

  { 34, "nlpid/Control Systems/Nonlinear PID/Update laws/q_0/q_x_0/Value",
    offsetof(Parameters_NLPID, q_x_0_Value), 21, 1, 2, 68, "", 0 },

  { 35, "nlpid/Control Systems/Nonlinear PID/Update laws/q_0/q_y_0/Value",
    offsetof(Parameters_NLPID, q_y_0_Value), 21, 1, 2, 70, "", 0 },

  { 36, "nlpid/HMI/Path-following input/x_2/Value", offsetof(Parameters_NLPID,
    x_2_Value), 21, 1, 2, 72, "", 0 },

  { 37, "nlpid/HMI/Path-following input/x_1/Value", offsetof(Parameters_NLPID,
    x_1_Value), 21, 1, 2, 74, "", 0 },

  { 38, "nlpid/HMI/Path-following input/y_2/Value", offsetof(Parameters_NLPID,
    y_2_Value), 21, 1, 2, 76, "", 0 },

  { 39, "nlpid/HMI/Path-following input/y_1/Value", offsetof(Parameters_NLPID,
    y_1_Value), 21, 1, 2, 78, "", 0 },

  { 40, "nlpid/Guidance Systems/Path-following/Path/Path Selector/Value",
    offsetof(Parameters_NLPID, PathSelector_Value), 21, 1, 2, 80, "", 0 },

  { 41, "nlpid/HMI/Path-following input/r_x/Value", offsetof(Parameters_NLPID,
    r_x_Value), 21, 1, 2, 82, "", 0 },

  { 42, "nlpid/Control Systems/Nonlinear PID/Update laws/Reset s/Value",
    offsetof(Parameters_NLPID, Resets_Value), 21, 1, 2, 84, "", 0 },

  { 43, "nlpid/Control Systems/Nonlinear PID/Update laws/s_0/Value", offsetof
    (Parameters_NLPID, s_0_Value), 21, 1, 2, 86, "", 0 },

  { 44, "nlpid/HMI/Path-following input/k/Value", offsetof(Parameters_NLPID,
    k_Value), 21, 1, 2, 88, "", 0 },

  { 45,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain), 21, 1, 2, 90, "", 0 },

  { 46, "nlpid/HMI/Path-following input/r_y/Value", offsetof(Parameters_NLPID,
    r_y_Value), 21, 1, 2, 92, "", 0 },

  { 47,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value), 21, 1, 2, 94, "", 0 },

  { 48,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_k), 21, 1, 2, 96, "", 0 },

  { 49,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_NLPID, Saturation_UpperSat), 21, 1, 2, 98, "", 0 },

  { 50,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_NLPID, Saturation_LowerSat), 21, 1, 2, 100, "", 0 },

  { 51,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_d), 21, 1, 2, 102, "", 0 },

  { 52,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_e), 21, 1, 2, 104, "", 0 },

  { 53,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_g), 21, 1, 2, 106, "", 0 },

  { 54,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_h), 21, 1, 2, 108, "", 0 },

  { 55,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/UpperLimit",
    offsetof(Parameters_NLPID, Saturation_UpperSat_o), 21, 1, 2, 110, "", 0 },

  { 56,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/LowerLimit",
    offsetof(Parameters_NLPID, Saturation_LowerSat_d), 21, 1, 2, 112, "", 0 },

  { 57,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_j), 21, 1, 2, 114, "", 0 },

  { 58,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_c), 21, 1, 2, 116, "", 0 },

  { 59,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_j), 21, 1, 2, 118, "", 0 },

  { 60, "nlpid/Guidance Systems/Path-following/Path/saturation/x_dmax/Value",
    offsetof(Parameters_NLPID, x_dmax_Value), 21, 1, 2, 120, "", 0 },

  { 61, "nlpid/HMI/Path-following input/origin_x/Value", offsetof
    (Parameters_NLPID, origin_x_Value), 21, 1, 2, 122, "", 0 },

  { 62, "nlpid/HMI/Path-following input/origo_y/Value", offsetof
    (Parameters_NLPID, origo_y_Value), 21, 1, 2, 124, "", 0 },

  { 63,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_k), 21, 1, 2, 126, "", 0 },

  { 64, "nlpid/Guidance Systems/Path-following/Path/saturation/x_dmin/Value",
    offsetof(Parameters_NLPID, x_dmin_Value), 21, 1, 2, 128, "", 0 },

  { 65, "nlpid/Guidance Systems/Path-following/Path/saturation/y_dmax/Value",
    offsetof(Parameters_NLPID, y_dmax_Value), 21, 1, 2, 130, "", 0 },

  { 66, "nlpid/Guidance Systems/Path-following/Path/saturation/y_dmin/Value",
    offsetof(Parameters_NLPID, y_dmin_Value), 21, 1, 2, 132, "", 0 },

  { 67, "nlpid/Guidance Systems/Path-following/Delta/Value", offsetof
    (Parameters_NLPID, Delta_Value), 21, 1, 2, 134, "", 0 },

  { 68,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_p), 21, 1, 2, 136, "", 0 },

  { 69,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/UpperLimit",
    offsetof(Parameters_NLPID, Saturation_UpperSat_c), 21, 1, 2, 138, "", 0 },

  { 70,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/LowerLimit",
    offsetof(Parameters_NLPID, Saturation_LowerSat_c), 21, 1, 2, 140, "", 0 },

  { 71,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_m), 21, 1, 2, 142, "", 0 },

  { 72,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_n), 21, 1, 2, 144, "", 0 },

  { 73,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_h), 21, 1, 2, 146, "", 0 },

  { 74,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_jf), 21, 1, 2, 148, "", 0 },

  { 75,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/UpperLimit",
    offsetof(Parameters_NLPID, Saturation_UpperSat_og), 21, 1, 2, 150, "", 0 },

  { 76,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/LowerLimit",
    offsetof(Parameters_NLPID, Saturation_LowerSat_o), 21, 1, 2, 152, "", 0 },

  { 77,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_f), 21, 1, 2, 154, "", 0 },

  { 78,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_h), 21, 1, 2, 156, "", 0 },

  { 79,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_i), 21, 1, 2, 158, "", 0 },

  { 80, "nlpid/Guidance Systems/q_x/Gain", offsetof(Parameters_NLPID, q_x_Gain),
    21, 1, 2, 160, "", 0 },

  { 81, "nlpid/Guidance Systems/q_y/Gain", offsetof(Parameters_NLPID, q_y_Gain),
    21, 1, 2, 162, "", 0 },

  { 82, "nlpid/Guidance Systems/psi_los/Gain", offsetof(Parameters_NLPID,
    psi_los_Gain), 21, 1, 2, 164, "", 0 },

  { 83, "nlpid/Guidance Systems/path x_d/Gain", offsetof(Parameters_NLPID,
    pathx_d_Gain), 21, 1, 2, 166, "", 0 },

  { 84, "nlpid/Guidance Systems/path y_d/Gain", offsetof(Parameters_NLPID,
    pathy_d_Gain), 21, 1, 2, 168, "", 0 },

  { 85, "nlpid/Guidance Systems/path psi_d/Gain", offsetof(Parameters_NLPID,
    pathpsi_d_Gain), 21, 1, 2, 170, "", 0 },

  { 86, "nlpid/HMI/Path-following input/u_d/Value", offsetof(Parameters_NLPID,
    u_d_Value), 21, 1, 2, 172, "", 0 },

  { 87,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_p), 21, 1, 2, 174, "", 0 },

  { 88, "nlpid/Control Systems/Control Mode/Value", offsetof(Parameters_NLPID,
    ControlMode_Value), 21, 1, 2, 176, "", 0 },

  { 89, "nlpid/Control Systems/PS3 input/AS_LY/Value", offsetof(Parameters_NLPID,
    AS_LY_Value), 21, 1, 2, 178, "", 0 },

  { 90, "nlpid/Control Systems/PS3 input/ScalingLY/Gain", offsetof
    (Parameters_NLPID, ScalingLY_Gain), 21, 1, 2, 180, "", 0 },

  { 91, "nlpid/Control Systems/PS3 u input control/PS3 u_1/Gain", offsetof
    (Parameters_NLPID, PS3u_1_Gain), 21, 1, 2, 182, "", 0 },

  { 92, "nlpid/Control Systems/PS3 input/AS_LX/Value", offsetof(Parameters_NLPID,
    AS_LX_Value), 21, 1, 2, 184, "", 0 },

  { 93, "nlpid/Control Systems/PS3 input/ScalingLX/Gain", offsetof
    (Parameters_NLPID, ScalingLX_Gain), 21, 1, 2, 186, "", 0 },

  { 94, "nlpid/Control Systems/PS3 u input control/PS3 u_2/Gain", offsetof
    (Parameters_NLPID, PS3u_2_Gain), 21, 1, 2, 188, "", 0 },

  { 95, "nlpid/Control Systems/PS3 input/AS_RY/Value", offsetof(Parameters_NLPID,
    AS_RY_Value), 21, 1, 2, 190, "", 0 },

  { 96, "nlpid/Control Systems/PS3 input/ScalingRY/Gain", offsetof
    (Parameters_NLPID, ScalingRY_Gain), 21, 1, 2, 192, "", 0 },

  { 97, "nlpid/Control Systems/PS3 u input control/PS3 u_3/Gain", offsetof
    (Parameters_NLPID, PS3u_3_Gain), 21, 1, 2, 194, "", 0 },

  { 98, "nlpid/Control Systems/PS3 input/AS_RX/Value", offsetof(Parameters_NLPID,
    AS_RX_Value), 21, 1, 2, 196, "", 0 },

  { 99, "nlpid/Control Systems/PS3 input/Scaling_RX/Gain", offsetof
    (Parameters_NLPID, Scaling_RX_Gain), 21, 1, 2, 198, "", 0 },

  { 100, "nlpid/Control Systems/PS3 u input control/PS3 u_4/Gain", offsetof
    (Parameters_NLPID, PS3u_4_Gain), 21, 1, 2, 200, "", 0 },

  { 101, "nlpid/Control Systems/PS3 input/L2/Value", offsetof(Parameters_NLPID,
    L2_Value), 21, 1, 2, 202, "", 0 },

  { 102, "nlpid/Control Systems/PS3 input/R2/Value", offsetof(Parameters_NLPID,
    R2_Value), 21, 1, 2, 204, "", 0 },

  { 103, "nlpid/Control Systems/PS3 u input control/PS3 u_5/Gain", offsetof
    (Parameters_NLPID, PS3u_5_Gain), 21, 1, 2, 206, "", 0 },

  { 104, "nlpid/Control Systems/PS3 input/PS3_BT_Power/Value", offsetof
    (Parameters_NLPID, PS3_BT_Power_Value), 21, 1, 2, 208, "", 0 },

  { 105, "nlpid/Control Systems/PS3 input/PS3_VSP_Speed/Value", offsetof
    (Parameters_NLPID, PS3_VSP_Speed_Value), 21, 1, 2, 210, "", 0 },

  { 106,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_NLPID, T_e11_Value), 21, 1, 2, 212, "", 0 },

  { 107,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_NLPID, T_e21_Value), 21, 1, 2, 214, "", 0 },

  { 108,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_NLPID, l_y1_Value), 21, 1, 2, 216, "", 0 },

  { 109,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_NLPID, T_e12_Value), 21, 1, 2, 218, "", 0 },

  { 110,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_NLPID, T_e22_Value), 21, 1, 2, 220, "", 0 },

  { 111,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_NLPID, l_x1_Value), 21, 1, 2, 222, "", 0 },

  { 112,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_NLPID, l_x1_Gain), 21, 1, 2, 224, "", 0 },

  { 113,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_NLPID, T_e13_Value), 21, 1, 2, 226, "", 0 },

  { 114,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_NLPID, T_e23_Value), 21, 1, 2, 228, "", 0 },

  { 115,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_NLPID, l_y2_Value), 21, 1, 2, 230, "", 0 },

  { 116,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_NLPID, l_y2_Gain), 21, 1, 2, 232, "", 0 },

  { 117,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_NLPID, T_e14_Value), 21, 1, 2, 234, "", 0 },

  { 118,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_NLPID, T_e24_Value), 21, 1, 2, 236, "", 0 },

  { 119,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_NLPID, l_x2_Value), 21, 1, 2, 238, "", 0 },

  { 120,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_NLPID, l_x2_Gain), 21, 1, 2, 240, "", 0 },

  { 121,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_NLPID, T_e15_Value), 21, 1, 2, 242, "", 0 },

  { 122,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_NLPID, T_e25_Value), 21, 1, 2, 244, "", 0 },

  { 123,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_NLPID, l_x3_Value), 21, 1, 2, 246, "", 0 },

  { 124,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_NLPID, Saturation_UpperSat_d), 21, 1, 2, 248, "", 0 },

  { 125,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_NLPID, Saturation_LowerSat_n), 21, 1, 2, 250, "", 0 },

  { 126,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_i), 21, 1, 2, 252, "", 0 },

  { 127,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_b), 21, 1, 2, 254, "", 0 },

  { 128,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_NLPID, Saturation_UpperSat_j), 21, 1, 2, 256, "", 0 },

  { 129,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_NLPID, Saturation_LowerSat_cp), 21, 1, 2, 258, "", 0 },

  { 130,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_g), 21, 1, 2, 260, "", 0 },

  { 131,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_i), 21, 1, 2, 262, "", 0 },

  { 132, "nlpid/Control Systems/DP control/DP controller/Kp/Gain", offsetof
    (Parameters_NLPID, Kp_Gain), 36, 9, 2, 264, "", 0 },

  { 133, "nlpid/Control Systems/DP control/DP controller/K_p_surge_scale/Gain",
    offsetof(Parameters_NLPID, K_p_surge_scale_Gain), 21, 1, 2, 266, "", 0 },

  { 134, "nlpid/Control Systems/DP control/DP controller/K_p_sway_scale/Gain",
    offsetof(Parameters_NLPID, K_p_sway_scale_Gain), 21, 1, 2, 268, "", 0 },

  { 135, "nlpid/Control Systems/DP control/DP controller/K_p_yaw_scale/Gain",
    offsetof(Parameters_NLPID, K_p_yaw_scale_Gain), 21, 1, 2, 270, "", 0 },

  { 136,
    "nlpid/Control Systems/DP control/DP controller/Reset_DP_integrator/Value",
    offsetof(Parameters_NLPID, Reset_DP_integrator_Value), 21, 1, 2, 272, "", 0
  },

  { 137,
    "nlpid/Control Systems/DP control/DP controller/Integrator/InitialCondition",
    offsetof(Parameters_NLPID, Integrator_IC), 21, 1, 2, 274, "", 0 },

  { 138, "nlpid/Control Systems/DP control/DP controller/Ki/Gain", offsetof
    (Parameters_NLPID, Ki_Gain), 36, 9, 2, 276, "", 0 },

  { 139, "nlpid/Control Systems/DP control/DP controller/K_i_surge_scale/Gain",
    offsetof(Parameters_NLPID, K_i_surge_scale_Gain), 21, 1, 2, 278, "", 0 },

  { 140, "nlpid/Control Systems/DP control/DP controller/K_i_sway_scale/Gain",
    offsetof(Parameters_NLPID, K_i_sway_scale_Gain), 21, 1, 2, 280, "", 0 },

  { 141, "nlpid/Control Systems/DP control/DP controller/K_i_yaw_scale/Gain",
    offsetof(Parameters_NLPID, K_i_yaw_scale_Gain), 21, 1, 2, 282, "", 0 },

  { 142, "nlpid/Control Systems/DP control/DP controller/Kd/Gain", offsetof
    (Parameters_NLPID, Kd_Gain), 36, 9, 2, 284, "", 0 },

  { 143, "nlpid/Control Systems/DP control/DP controller/K_d_surge_scale/Gain",
    offsetof(Parameters_NLPID, K_d_surge_scale_Gain), 21, 1, 2, 286, "", 0 },

  { 144, "nlpid/Control Systems/DP control/DP controller/K_d_sway_scale/Gain",
    offsetof(Parameters_NLPID, K_d_sway_scale_Gain), 21, 1, 2, 288, "", 0 },

  { 145, "nlpid/Control Systems/DP control/DP controller/K_d_yaw_scale/Gain",
    offsetof(Parameters_NLPID, K_d_yaw_scale_Gain), 21, 1, 2, 290, "", 0 },

  { 146,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start), 21, 1, 2, 292, "", 0 },

  { 147,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End), 21, 1, 2, 294, "", 0 },

  { 148,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_kk), 21, 1, 2, 296, "", 0 },

  { 149,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_j), 21, 1, 2, 298, "", 0 },

  { 150,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_NLPID, f_10_XData), 44, 9, 2, 300, "", 0 },

  { 151,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_NLPID, f_10_YData), 44, 9, 2, 302, "", 0 },

  { 152,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_NLPID, f_10_Value), 21, 1, 2, 304, "", 0 },

  { 153,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_NLPID, f_10_XData_f), 68, 10, 2, 306, "", 0 },

  { 154,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_NLPID, f_10_YData_j), 68, 10, 2, 308, "", 0 },

  { 155,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start_f), 21, 1, 2, 310, "", 0 },

  { 156,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End_o), 21, 1, 2, 312, "", 0 },

  { 157,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_l), 21, 1, 2, 314, "", 0 },

  { 158,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_l4), 21, 1, 2, 316, "", 0 },

  { 159,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_f), 21, 1, 2, 318, "", 0 },

  { 160,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_NLPID, f_20_XData), 69, 11, 2, 320, "", 0 },

  { 161,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_NLPID, f_20_YData), 69, 11, 2, 322, "", 0 },

  { 162,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_NLPID, f_20_Value), 21, 1, 2, 324, "", 0 },

  { 163,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_NLPID, f_20_XData_o), 68, 10, 2, 326, "", 0 },

  { 164,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_NLPID, f_20_YData_n), 68, 10, 2, 328, "", 0 },

  { 165,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start_fx), 21, 1, 2, 330, "", 0 },

  { 166,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End_c), 21, 1, 2, 332, "", 0 },

  { 167,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_cr), 21, 1, 2, 334, "", 0 },

  { 168,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_n2), 21, 1, 2, 336, "", 0 },

  { 169,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_NLPID, f_30_XData), 70, 8, 2, 338, "", 0 },

  { 170,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_NLPID, f_30_YData), 70, 8, 2, 340, "", 0 },

  { 171,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_NLPID, f_30_Value), 21, 1, 2, 342, "", 0 },

  { 172,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_NLPID, f_30_XData_d), 69, 11, 2, 344, "", 0 },

  { 173,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_NLPID, f_30_YData_k), 69, 11, 2, 346, "", 0 },

  { 174,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start_i), 21, 1, 2, 348, "", 0 },

  { 175,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End_e), 21, 1, 2, 350, "", 0 },

  { 176,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_fy), 21, 1, 2, 352, "", 0 },

  { 177,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_m), 21, 1, 2, 354, "", 0 },

  { 178,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_NLPID, f_40_XData), 68, 10, 2, 356, "", 0 },

  { 179,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_NLPID, f_40_YData), 68, 10, 2, 358, "", 0 },

  { 180,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_NLPID, f_40_Value), 21, 1, 2, 360, "", 0 },

  { 181,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_NLPID, f_40_XData_l), 71, 7, 2, 362, "", 0 },

  { 182,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_NLPID, f_40_YData_i), 71, 7, 2, 364, "", 0 },

  { 183,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start_l), 21, 1, 2, 366, "", 0 },

  { 184,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End_m), 21, 1, 2, 368, "", 0 },

  { 185,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_g), 21, 1, 2, 370, "", 0 },

  { 186,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_d), 21, 1, 2, 372, "", 0 },

  { 187,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_NLPID, f_50_XData), 26, 3, 2, 374, "", 0 },

  { 188,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_NLPID, f_50_YData), 26, 3, 2, 376, "", 0 },

  { 189,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_NLPID, f_50_Value), 21, 1, 2, 378, "", 0 },

  { 190,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_NLPID, f_50_XData_d), 26, 3, 2, 380, "", 0 },

  { 191,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_NLPID, f_50_YData_a), 26, 3, 2, 382, "", 0 },

  { 192, "nlpid/Control Systems/DP control/Saturation/UpperLimit", offsetof
    (Parameters_NLPID, Saturation_UpperSat_l), 21, 1, 2, 384, "", 0 },

  { 193, "nlpid/Control Systems/DP control/Saturation/LowerLimit", offsetof
    (Parameters_NLPID, Saturation_LowerSat_b), 21, 1, 2, 386, "", 0 },

  { 194, "nlpid/Control Systems/DP control/BT_power_limit/Value", offsetof
    (Parameters_NLPID, BT_power_limit_Value), 21, 1, 2, 388, "", 0 },

  { 195, "nlpid/Control Systems/DP control/VSP_speeds/Value", offsetof
    (Parameters_NLPID, VSP_speeds_Value), 21, 1, 2, 390, "", 0 },

  { 196,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_NLPID, T_e11_Value_o), 21, 1, 2, 392, "", 0 },

  { 197,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_NLPID, T_e21_Value_a), 21, 1, 2, 394, "", 0 },

  { 198,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_NLPID, l_y1_Value_b), 21, 1, 2, 396, "", 0 },

  { 199,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_NLPID, T_e12_Value_h), 21, 1, 2, 398, "", 0 },

  { 200,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_NLPID, T_e22_Value_m), 21, 1, 2, 400, "", 0 },

  { 201,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_NLPID, l_x1_Value_n), 21, 1, 2, 402, "", 0 },

  { 202,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_NLPID, l_x1_Gain_j), 21, 1, 2, 404, "", 0 },

  { 203,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_NLPID, T_e13_Value_a), 21, 1, 2, 406, "", 0 },

  { 204,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_NLPID, T_e23_Value_o), 21, 1, 2, 408, "", 0 },

  { 205,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_NLPID, l_y2_Value_n), 21, 1, 2, 410, "", 0 },

  { 206,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_NLPID, l_y2_Gain_e), 21, 1, 2, 412, "", 0 },

  { 207,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_NLPID, T_e14_Value_m), 21, 1, 2, 414, "", 0 },

  { 208,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_NLPID, T_e24_Value_b), 21, 1, 2, 416, "", 0 },

  { 209,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_NLPID, l_x2_Value_c), 21, 1, 2, 418, "", 0 },

  { 210,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_NLPID, l_x2_Gain_p), 21, 1, 2, 420, "", 0 },

  { 211,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_NLPID, T_e15_Value_o), 21, 1, 2, 422, "", 0 },

  { 212,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_NLPID, T_e25_Value_b), 21, 1, 2, 424, "", 0 },

  { 213,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_NLPID, l_x3_Value_i), 21, 1, 2, 426, "", 0 },

  { 214, "nlpid/Control Systems/Nonlinear PID/R(psi)/R31/Value", offsetof
    (Parameters_NLPID, R31_Value), 21, 1, 2, 428, "", 0 },

  { 215, "nlpid/Control Systems/Nonlinear PID/R(psi)/R32/Value", offsetof
    (Parameters_NLPID, R32_Value), 21, 1, 2, 430, "", 0 },

  { 216, "nlpid/Control Systems/Nonlinear PID/R(psi)/R13/Value", offsetof
    (Parameters_NLPID, R13_Value), 21, 1, 2, 432, "", 0 },

  { 217, "nlpid/Control Systems/Nonlinear PID/R(psi)/R23/Value", offsetof
    (Parameters_NLPID, R23_Value), 21, 1, 2, 434, "", 0 },

  { 218, "nlpid/Control Systems/Nonlinear PID/R(psi)/R33/Value", offsetof
    (Parameters_NLPID, R33_Value), 21, 1, 2, 436, "", 0 },

  { 219, "nlpid/Control Systems/Nonlinear PID/K_p_Surge/Value", offsetof
    (Parameters_NLPID, K_p_Surge_Value), 21, 1, 2, 438, "", 0 },

  { 220, "nlpid/Control Systems/Nonlinear PID/K_p/21/Value", offsetof
    (Parameters_NLPID, u_Value), 21, 1, 2, 440, "", 0 },

  { 221, "nlpid/Control Systems/Nonlinear PID/K_p/31/Value", offsetof
    (Parameters_NLPID, u_Value_k), 21, 1, 2, 442, "", 0 },

  { 222, "nlpid/Control Systems/Nonlinear PID/K_p/12/Value", offsetof
    (Parameters_NLPID, u_Value_e), 21, 1, 2, 444, "", 0 },

  { 223, "nlpid/Control Systems/Nonlinear PID/K_p_Sway/Value", offsetof
    (Parameters_NLPID, K_p_Sway_Value), 21, 1, 2, 446, "", 0 },

  { 224, "nlpid/Control Systems/Nonlinear PID/K_p/32/Value", offsetof
    (Parameters_NLPID, u_Value_a), 21, 1, 2, 448, "", 0 },

  { 225, "nlpid/Control Systems/Nonlinear PID/K_p/13/Value", offsetof
    (Parameters_NLPID, u_Value_c), 21, 1, 2, 450, "", 0 },

  { 226, "nlpid/Control Systems/Nonlinear PID/K_p/23/Value", offsetof
    (Parameters_NLPID, u_Value_eh), 21, 1, 2, 452, "", 0 },

  { 227, "nlpid/Control Systems/Nonlinear PID/K_p_Yaw/Value", offsetof
    (Parameters_NLPID, K_p_Yaw_Value), 21, 1, 2, 454, "", 0 },

  { 228,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_c), 21, 1, 2, 456, "", 0 },

  { 229,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_NLPID, Saturation_UpperSat_dr), 21, 1, 2, 458, "", 0 },

  { 230,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_NLPID, Saturation_LowerSat_l), 21, 1, 2, 460, "", 0 },

  { 231,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_fq), 21, 1, 2, 462, "", 0 },

  { 232,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_fc), 21, 1, 2, 464, "", 0 },

  { 233,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_i5), 21, 1, 2, 466, "", 0 },

  { 234,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_f0), 21, 1, 2, 468, "", 0 },

  { 235,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_NLPID, Saturation_UpperSat_d1), 21, 1, 2, 470, "", 0 },

  { 236,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_NLPID, Saturation_LowerSat_nw), 21, 1, 2, 472, "", 0 },

  { 237,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_l), 21, 1, 2, 474, "", 0 },

  { 238,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_dk), 21, 1, 2, 476, "", 0 },

  { 239,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_a), 21, 1, 2, 478, "", 0 },

  { 240, "nlpid/Control Systems/Nonlinear PID/K_i_Surge/Value", offsetof
    (Parameters_NLPID, K_i_Surge_Value), 21, 1, 2, 480, "", 0 },

  { 241, "nlpid/Control Systems/Nonlinear PID/K_i/21/Value", offsetof
    (Parameters_NLPID, u_Value_n), 21, 1, 2, 482, "", 0 },

  { 242, "nlpid/Control Systems/Nonlinear PID/K_i/31/Value", offsetof
    (Parameters_NLPID, u_Value_l), 21, 1, 2, 484, "", 0 },

  { 243, "nlpid/Control Systems/Nonlinear PID/K_i/12/Value", offsetof
    (Parameters_NLPID, u_Value_i), 21, 1, 2, 486, "", 0 },

  { 244, "nlpid/Control Systems/Nonlinear PID/K_i_Sway/Value", offsetof
    (Parameters_NLPID, K_i_Sway_Value), 21, 1, 2, 488, "", 0 },

  { 245, "nlpid/Control Systems/Nonlinear PID/K_i/32/Value", offsetof
    (Parameters_NLPID, u_Value_d), 21, 1, 2, 490, "", 0 },

  { 246, "nlpid/Control Systems/Nonlinear PID/K_i/13/Value", offsetof
    (Parameters_NLPID, u_Value_kc), 21, 1, 2, 492, "", 0 },

  { 247, "nlpid/Control Systems/Nonlinear PID/K_i/23/Value", offsetof
    (Parameters_NLPID, u_Value_f), 21, 1, 2, 494, "", 0 },

  { 248, "nlpid/Control Systems/Nonlinear PID/K_i_Yaw/Value", offsetof
    (Parameters_NLPID, K_i_Yaw_Value), 21, 1, 2, 496, "", 0 },

  { 249, "nlpid/Control Systems/Nonlinear PID/zeta/InitialCondition", offsetof
    (Parameters_NLPID, zeta_IC), 21, 1, 2, 498, "", 0 },

  { 250, "nlpid/Control Systems/Nonlinear PID/K_d_Surge/Value", offsetof
    (Parameters_NLPID, K_d_Surge_Value), 21, 1, 2, 500, "", 0 },

  { 251, "nlpid/Control Systems/Nonlinear PID/K_d/21/Value", offsetof
    (Parameters_NLPID, u_Value_j), 21, 1, 2, 502, "", 0 },

  { 252, "nlpid/Control Systems/Nonlinear PID/K_d/31/Value", offsetof
    (Parameters_NLPID, u_Value_aw), 21, 1, 2, 504, "", 0 },

  { 253, "nlpid/Control Systems/Nonlinear PID/K_d/12/Value", offsetof
    (Parameters_NLPID, u_Value_l1), 21, 1, 2, 506, "", 0 },

  { 254, "nlpid/Control Systems/Nonlinear PID/K_d_Sway/Value", offsetof
    (Parameters_NLPID, K_d_Sway_Value), 21, 1, 2, 508, "", 0 },

  { 255, "nlpid/Control Systems/Nonlinear PID/K_d/32/Value", offsetof
    (Parameters_NLPID, u_Value_b), 21, 1, 2, 510, "", 0 },

  { 256, "nlpid/Control Systems/Nonlinear PID/K_d/13/Value", offsetof
    (Parameters_NLPID, u_Value_ju), 21, 1, 2, 512, "", 0 },

  { 257, "nlpid/Control Systems/Nonlinear PID/K_d/23/Value", offsetof
    (Parameters_NLPID, u_Value_eq), 21, 1, 2, 514, "", 0 },

  { 258, "nlpid/Control Systems/Nonlinear PID/K_d_Yaw/Value", offsetof
    (Parameters_NLPID, K_d_Yaw_Value), 21, 1, 2, 516, "", 0 },

  { 259,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain",
    offsetof(Parameters_NLPID, u_Gain), 21, 1, 2, 518, "", 0 },

  { 260,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s eq/0_2x1/Value",
    offsetof(Parameters_NLPID, _2x1_Value), 35, 2, 2, 520, "", 0 },

  { 261, "nlpid/Guidance Systems/Path-following/Path/Straight path/0_2x1/Value",
    offsetof(Parameters_NLPID, _2x1_Value_c), 21, 1, 2, 522, "", 0 },

  { 262,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_fyr), 21, 1, 2, 524, "", 0 },

  { 263,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_jk), 21, 1, 2, 526, "", 0 },

  { 264,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_jt), 21, 1, 2, 528, "", 0 },

  { 265, "nlpid/Guidance Systems/Path-following/my/Value", offsetof
    (Parameters_NLPID, my_Value), 21, 1, 2, 530, "", 0 },

  { 266,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_o), 21, 1, 2, 532, "", 0 },

  { 267, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/X_u/Value",
    offsetof(Parameters_NLPID, X_u_Value), 21, 1, 2, 534, "", 0 },

  { 268, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-X_u/Gain",
    offsetof(Parameters_NLPID, X_u_Gain), 21, 1, 2, 536, "", 0 },

  { 269,
    "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_21/Value",
    offsetof(Parameters_NLPID, D_L_21_Value), 21, 1, 2, 538, "", 0 },

  { 270,
    "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_31/Value",
    offsetof(Parameters_NLPID, D_L_31_Value), 21, 1, 2, 540, "", 0 },

  { 271,
    "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_12/Value",
    offsetof(Parameters_NLPID, D_L_12_Value), 21, 1, 2, 542, "", 0 },

  { 272, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Y_v/Value",
    offsetof(Parameters_NLPID, Y_v_Value), 21, 1, 2, 544, "", 0 },

  { 273, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_v/Gain",
    offsetof(Parameters_NLPID, Y_v_Gain), 21, 1, 2, 546, "", 0 },

  { 274, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/N_v/Value",
    offsetof(Parameters_NLPID, N_v_Value), 21, 1, 2, 548, "", 0 },

  { 275, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_v/Gain",
    offsetof(Parameters_NLPID, N_v_Gain), 21, 1, 2, 550, "", 0 },

  { 276,
    "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_13/Value",
    offsetof(Parameters_NLPID, D_L_13_Value), 21, 1, 2, 552, "", 0 },

  { 277, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Y_r/Value",
    offsetof(Parameters_NLPID, Y_r_Value), 21, 1, 2, 554, "", 0 },

  { 278, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_vr/Gain",
    offsetof(Parameters_NLPID, Y_vr_Gain), 21, 1, 2, 556, "", 0 },

  { 279, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/N_r/Value",
    offsetof(Parameters_NLPID, N_r_Value), 21, 1, 2, 558, "", 0 },

  { 280, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_r/Gain",
    offsetof(Parameters_NLPID, N_r_Gain), 21, 1, 2, 560, "", 0 },

  { 281, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/m/Value",
    offsetof(Parameters_NLPID, m_Value), 21, 1, 2, 562, "", 0 },

  { 282, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/X_udot/Value",
    offsetof(Parameters_NLPID, X_udot_Value), 21, 1, 2, 564, "", 0 },

  { 283, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_21/Value",
    offsetof(Parameters_NLPID, M_21_Value), 21, 1, 2, 566, "", 0 },

  { 284, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_31/Value",
    offsetof(Parameters_NLPID, M_31_Value), 21, 1, 2, 568, "", 0 },

  { 285, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_12/Value",
    offsetof(Parameters_NLPID, M_12_Value), 21, 1, 2, 570, "", 0 },

  { 286, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/Y_vdot/Value",
    offsetof(Parameters_NLPID, Y_vdot_Value), 21, 1, 2, 572, "", 0 },

  { 287, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/x_g/Value",
    offsetof(Parameters_NLPID, x_g_Value), 21, 1, 2, 574, "", 0 },

  { 288, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/N_vdot/Value",
    offsetof(Parameters_NLPID, N_vdot_Value), 21, 1, 2, 576, "", 0 },

  { 289, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_13/Value",
    offsetof(Parameters_NLPID, M_13_Value), 21, 1, 2, 578, "", 0 },

  { 290, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/Y_rdot/Value",
    offsetof(Parameters_NLPID, Y_rdot_Value), 21, 1, 2, 580, "", 0 },

  { 291, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/I_z/Value",
    offsetof(Parameters_NLPID, I_z_Value), 21, 1, 2, 582, "", 0 },

  { 292, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/N_rdot/Value",
    offsetof(Parameters_NLPID, N_rdot_Value), 21, 1, 2, 584, "", 0 },

  { 293,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_e), 21, 1, 2, 586, "", 0 },

  { 294,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain",
    offsetof(Parameters_NLPID, _Gain), 21, 1, 2, 588, "", 0 },

  { 295,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/0_2x2/Value",
    offsetof(Parameters_NLPID, _2x2_Value), 22, 4, 2, 590, "", 0 },

  { 296,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/0_2x2/Value",
    offsetof(Parameters_NLPID, _2x2_Value_f), 22, 4, 2, 592, "", 0 },

  { 297,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain",
    offsetof(Parameters_NLPID, _Gain_b), 21, 1, 2, 594, "", 0 },

  { 298,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value",
    offsetof(Parameters_NLPID, u_Value_ip), 21, 1, 2, 596, "", 0 },

  { 299,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_b), 21, 1, 2, 598, "", 0 },

  { 300,
    "nlpid/Control Systems/Nonlinear PID/Update laws/omega_q/InitialCondition",
    offsetof(Parameters_NLPID, omega_q_IC), 21, 1, 2, 600, "", 0 },

  { 301,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_lf), 21, 1, 2, 602, "", 0 },

  { 302,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/0_2x1/Value",
    offsetof(Parameters_NLPID, _2x1_Value_d), 35, 2, 2, 604, "", 0 },

  { 303,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_a), 21, 1, 2, 606, "", 0 },

  { 304,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_c), 21, 1, 2, 608, "", 0 },

  { 305,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_pr), 21, 1, 2, 610, "", 0 },

  { 306, "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/+ 2/Gain",
    offsetof(Parameters_NLPID, u_Gain_j), 21, 1, 2, 612, "", 0 },

  { 307,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain",
    offsetof(Parameters_NLPID, _Gain_h), 21, 1, 2, 614, "", 0 },

  { 308,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain",
    offsetof(Parameters_NLPID, _Gain_k), 21, 1, 2, 616, "", 0 },

  { 309,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_l0), 21, 1, 2, 618, "", 0 },

  { 310,
    "nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_fg), 21, 1, 2, 620, "", 0 },

  { 311,
    "nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_mo), 21, 1, 2, 622, "", 0 },

  { 312,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value",
    offsetof(Parameters_NLPID, u_Value_ns), 21, 1, 2, 624, "", 0 },

  { 313,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_ml), 21, 1, 2, 626, "", 0 },

  { 314,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^t eq/0_2x1/Value",
    offsetof(Parameters_NLPID, _2x1_Value_o), 35, 2, 2, 628, "", 0 },

  { 315, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S11/Value",
    offsetof(Parameters_NLPID, S11_Value), 21, 1, 2, 630, "", 0 },

  { 316, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/R31/Value",
    offsetof(Parameters_NLPID, R31_Value_j), 21, 1, 2, 632, "", 0 },

  { 317, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S12/Gain",
    offsetof(Parameters_NLPID, S12_Gain), 21, 1, 2, 634, "", 0 },

  { 318, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S22/Value",
    offsetof(Parameters_NLPID, S22_Value), 21, 1, 2, 636, "", 0 },

  { 319, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S32/Value",
    offsetof(Parameters_NLPID, S32_Value), 21, 1, 2, 638, "", 0 },

  { 320, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S13/Value",
    offsetof(Parameters_NLPID, S13_Value), 21, 1, 2, 640, "", 0 },

  { 321, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S23/Value",
    offsetof(Parameters_NLPID, S23_Value), 21, 1, 2, 642, "", 0 },

  { 322, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S33/Value",
    offsetof(Parameters_NLPID, S33_Value), 21, 1, 2, 644, "", 0 },

  { 323, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_g0), 21, 1, 2, 646, "", 0 },

  { 324,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start_g), 21, 1, 2, 648, "", 0 },

  { 325,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End_d), 21, 1, 2, 650, "", 0 },

  { 326,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_ip), 21, 1, 2, 652, "", 0 },

  { 327,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_hk), 21, 1, 2, 654, "", 0 },

  { 328,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_NLPID, f_10_XData_n), 44, 9, 2, 656, "", 0 },

  { 329,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_NLPID, f_10_YData_g), 44, 9, 2, 658, "", 0 },

  { 330,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_NLPID, f_10_Value_g), 21, 1, 2, 660, "", 0 },

  { 331,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_NLPID, f_10_XData_k), 68, 10, 2, 662, "", 0 },

  { 332,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_NLPID, f_10_YData_l), 68, 10, 2, 664, "", 0 },

  { 333,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start_m), 21, 1, 2, 666, "", 0 },

  { 334,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End_b), 21, 1, 2, 668, "", 0 },

  { 335,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_hl), 21, 1, 2, 670, "", 0 },

  { 336,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_pg), 21, 1, 2, 672, "", 0 },

  { 337,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_my), 21, 1, 2, 674, "", 0 },

  { 338,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_NLPID, f_20_XData_g), 69, 11, 2, 676, "", 0 },

  { 339,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_NLPID, f_20_YData_nw), 69, 11, 2, 678, "", 0 },

  { 340,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_NLPID, f_20_Value_k), 21, 1, 2, 680, "", 0 },

  { 341,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_NLPID, f_20_XData_a), 68, 10, 2, 682, "", 0 },

  { 342,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_NLPID, f_20_YData_f), 68, 10, 2, 684, "", 0 },

  { 343,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start_d), 21, 1, 2, 686, "", 0 },

  { 344,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End_n), 21, 1, 2, 688, "", 0 },

  { 345,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_la), 21, 1, 2, 690, "", 0 },

  { 346,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_d2), 21, 1, 2, 692, "", 0 },

  { 347,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_NLPID, f_30_XData_g), 70, 8, 2, 694, "", 0 },

  { 348,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_NLPID, f_30_YData_i), 70, 8, 2, 696, "", 0 },

  { 349,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_NLPID, f_30_Value_b), 21, 1, 2, 698, "", 0 },

  { 350,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_NLPID, f_30_XData_e), 69, 11, 2, 700, "", 0 },

  { 351,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_NLPID, f_30_YData_f), 69, 11, 2, 702, "", 0 },

  { 352,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start_my), 21, 1, 2, 704, "", 0 },

  { 353,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End_h), 21, 1, 2, 706, "", 0 },

  { 354,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_o), 21, 1, 2, 708, "", 0 },

  { 355,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_dl), 21, 1, 2, 710, "", 0 },

  { 356,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_NLPID, f_40_XData_n), 68, 10, 2, 712, "", 0 },

  { 357,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_NLPID, f_40_YData_e), 68, 10, 2, 714, "", 0 },

  { 358,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_NLPID, f_40_Value_a), 21, 1, 2, 716, "", 0 },

  { 359,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_NLPID, f_40_XData_j), 71, 7, 2, 718, "", 0 },

  { 360,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_NLPID, f_40_YData_a), 71, 7, 2, 720, "", 0 },

  { 361,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue",
    offsetof(Parameters_NLPID, DeadZone_Start_lo), 21, 1, 2, 722, "", 0 },

  { 362,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue",
    offsetof(Parameters_NLPID, DeadZone_End_m5), 21, 1, 2, 724, "", 0 },

  { 363,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_c5), 21, 1, 2, 726, "", 0 },

  { 364,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_gc), 21, 1, 2, 728, "", 0 },

  { 365,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_NLPID, f_50_XData_e), 26, 3, 2, 730, "", 0 },

  { 366,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_NLPID, f_50_YData_p), 26, 3, 2, 732, "", 0 },

  { 367,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_NLPID, f_50_Value_b), 21, 1, 2, 734, "", 0 },

  { 368,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_NLPID, f_50_XData_p), 26, 3, 2, 736, "", 0 },

  { 369,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_NLPID, f_50_YData_pp), 26, 3, 2, 738, "", 0 },

  { 370, "nlpid/Control Systems/Nonlinear PID/BT_power_limit/Value", offsetof
    (Parameters_NLPID, BT_power_limit_Value_n), 21, 1, 2, 740, "", 0 },

  { 371, "nlpid/Control Systems/Nonlinear PID/VSP_speeds/Value", offsetof
    (Parameters_NLPID, VSP_speeds_Value_l), 21, 1, 2, 742, "", 0 },

  { 372, "nlpid/Control Systems/Saturation/UpperLimit", offsetof
    (Parameters_NLPID, Saturation_UpperSat_j2), 21, 1, 2, 744, "", 0 },

  { 373, "nlpid/Control Systems/Saturation/LowerLimit", offsetof
    (Parameters_NLPID, Saturation_LowerSat_ll), 21, 1, 2, 746, "", 0 },

  { 374,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value",
    offsetof(Parameters_NLPID, T_e11_Value_od), 21, 1, 2, 748, "", 0 },

  { 375,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value",
    offsetof(Parameters_NLPID, T_e21_Value_k), 21, 1, 2, 750, "", 0 },

  { 376,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value",
    offsetof(Parameters_NLPID, l_y1_Value_k), 21, 1, 2, 752, "", 0 },

  { 377,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value",
    offsetof(Parameters_NLPID, T_e12_Value_j), 21, 1, 2, 754, "", 0 },

  { 378,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value",
    offsetof(Parameters_NLPID, T_e22_Value_n), 21, 1, 2, 756, "", 0 },

  { 379,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value",
    offsetof(Parameters_NLPID, l_x1_Value_j), 21, 1, 2, 758, "", 0 },

  { 380,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain",
    offsetof(Parameters_NLPID, l_x1_Gain_n), 21, 1, 2, 760, "", 0 },

  { 381,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value",
    offsetof(Parameters_NLPID, T_e13_Value_ai), 21, 1, 2, 762, "", 0 },

  { 382,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value",
    offsetof(Parameters_NLPID, T_e23_Value_b), 21, 1, 2, 764, "", 0 },

  { 383,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value",
    offsetof(Parameters_NLPID, l_y2_Value_ne), 21, 1, 2, 766, "", 0 },

  { 384,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain",
    offsetof(Parameters_NLPID, l_y2_Gain_h), 21, 1, 2, 768, "", 0 },

  { 385,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value",
    offsetof(Parameters_NLPID, T_e14_Value_mp), 21, 1, 2, 770, "", 0 },

  { 386,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value",
    offsetof(Parameters_NLPID, T_e24_Value_c), 21, 1, 2, 772, "", 0 },

  { 387,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value",
    offsetof(Parameters_NLPID, l_x2_Value_p), 21, 1, 2, 774, "", 0 },

  { 388,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain",
    offsetof(Parameters_NLPID, l_x2_Gain_po), 21, 1, 2, 776, "", 0 },

  { 389,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value",
    offsetof(Parameters_NLPID, T_e15_Value_l), 21, 1, 2, 778, "", 0 },

  { 390,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value",
    offsetof(Parameters_NLPID, T_e25_Value_n), 21, 1, 2, 780, "", 0 },

  { 391,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value",
    offsetof(Parameters_NLPID, l_x3_Value_e), 21, 1, 2, 782, "", 0 },

  { 392,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues",
    offsetof(Parameters_NLPID, u_1tof_1_XData), 72, 19, 2, 784, "", 0 },

  { 393,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table",
    offsetof(Parameters_NLPID, u_1tof_1_YData), 72, 19, 2, 786, "", 0 },

  { 394,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues",
    offsetof(Parameters_NLPID, u_2tof_2_XData), 73, 21, 2, 788, "", 0 },

  { 395,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table",
    offsetof(Parameters_NLPID, u_2tof_2_YData), 73, 21, 2, 790, "", 0 },

  { 396,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues",
    offsetof(Parameters_NLPID, u_3tof_3_XData), 72, 19, 2, 792, "", 0 },

  { 397,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table",
    offsetof(Parameters_NLPID, u_3tof_3_YData), 72, 19, 2, 794, "", 0 },

  { 398,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues",
    offsetof(Parameters_NLPID, u_4tof_4_XData), 74, 17, 2, 796, "", 0 },

  { 399,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table",
    offsetof(Parameters_NLPID, u_4tof_4_YData), 74, 17, 2, 798, "", 0 },

  { 400,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues",
    offsetof(Parameters_NLPID, u_5tof_5_XData), 75, 7, 2, 800, "", 0 },

  { 401,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table",
    offsetof(Parameters_NLPID, u_5tof_5_YData), 75, 7, 2, 802, "", 0 },

  { 402, "nlpid/Control Systems/Nonlinear PID/Gamma_q/12/Value", offsetof
    (Parameters_NLPID, u_Value_fv), 21, 1, 2, 804, "", 0 },

  { 403, "nlpid/Control Systems/Nonlinear PID/Gamma_q/21/Value", offsetof
    (Parameters_NLPID, u_Value_h), 21, 1, 2, 806, "", 0 },

  { 404, "nlpid/Control Systems/Nonlinear PID/Gamma_q_Surge/Value", offsetof
    (Parameters_NLPID, Gamma_q_Surge_Value), 21, 1, 2, 808, "", 0 },

  { 405, "nlpid/Control Systems/Nonlinear PID/Gamma_q_Sway/Value", offsetof
    (Parameters_NLPID, Gamma_q_Sway_Value), 21, 1, 2, 810, "", 0 },

  { 406, "nlpid/Control Systems/Nonlinear PID/lambda/Value", offsetof
    (Parameters_NLPID, lambda_Value), 21, 1, 2, 812, "", 0 },

  { 407,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/I/Constant/Value",
    offsetof(Parameters_NLPID, Constant_Value_od), 22, 4, 2, 814, "", 0 },

  { 408, "nlpid/Control Systems/Nonlinear PID/Update laws/dot omega_q/Gain",
    offsetof(Parameters_NLPID, dotomega_q_Gain), 21, 1, 2, 816, "", 0 },

  { 409,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/0_2x1/Value",
    offsetof(Parameters_NLPID, _2x1_Value_m), 35, 2, 2, 818, "", 0 },

  { 410, "nlpid/HMI/Battery Bow Thruster/Gain", offsetof(Parameters_NLPID,
    BatteryBowThruster_Gain), 21, 1, 2, 820, "", 0 },

  { 411, "nlpid/HMI/Battery Servo/Gain", offsetof(Parameters_NLPID,
    BatteryServo_Gain), 21, 1, 2, 822, "", 0 },

  { 412, "nlpid/HMI/Battery Main/Gain", offsetof(Parameters_NLPID,
    BatteryMain_Gain), 21, 1, 2, 824, "", 0 },

  { 413, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain", offsetof
    (Parameters_NLPID, QTMIn1FPS_Gain), 21, 1, 2, 826, "", 0 },

  { 414, "nlpid/Plants/saturation/Saturation/UpperLimit", offsetof
    (Parameters_NLPID, Saturation_UpperSat_js), 21, 1, 2, 828, "", 0 },

  { 415, "nlpid/Plants/saturation/Saturation/LowerLimit", offsetof
    (Parameters_NLPID, Saturation_LowerSat_op), 21, 1, 2, 830, "", 0 },

  { 416, "nlpid/Plants/saturation/Saturation1/UpperLimit", offsetof
    (Parameters_NLPID, Saturation1_UpperSat), 21, 1, 2, 832, "", 0 },

  { 417, "nlpid/Plants/saturation/Saturation1/LowerLimit", offsetof
    (Parameters_NLPID, Saturation1_LowerSat), 21, 1, 2, 834, "", 0 },

  { 418, "nlpid/Plants/saturation/Saturation2/UpperLimit", offsetof
    (Parameters_NLPID, Saturation2_UpperSat), 21, 1, 2, 836, "", 0 },

  { 419, "nlpid/Plants/saturation/Saturation2/LowerLimit", offsetof
    (Parameters_NLPID, Saturation2_LowerSat), 21, 1, 2, 838, "", 0 },

  { 420, "nlpid/Plants/saturation/plant tau_surge/Gain", offsetof
    (Parameters_NLPID, planttau_surge_Gain), 21, 1, 2, 840, "", 0 },

  { 421, "nlpid/Plants/saturation/plant tau_sway/Gain", offsetof
    (Parameters_NLPID, planttau_sway_Gain), 21, 1, 2, 842, "", 0 },

  { 422, "nlpid/Plants/saturation/plant tau_yaw/Gain", offsetof(Parameters_NLPID,
    planttau_yaw_Gain), 21, 1, 2, 844, "", 0 },

  { 423, "nlpid/Plants/plant u_1/Gain", offsetof(Parameters_NLPID, plantu_1_Gain),
    21, 1, 2, 846, "", 0 },

  { 424, "nlpid/Plants/plant u_2/Gain", offsetof(Parameters_NLPID, plantu_2_Gain),
    21, 1, 2, 848, "", 0 },

  { 425, "nlpid/Plants/plant u_3/Gain", offsetof(Parameters_NLPID, plantu_3_Gain),
    21, 1, 2, 850, "", 0 },

  { 426, "nlpid/Plants/plant u_4/Gain", offsetof(Parameters_NLPID, plantu_4_Gain),
    21, 1, 2, 852, "", 0 },

  { 427, "nlpid/Plants/plant u_5/Gain", offsetof(Parameters_NLPID, plantu_5_Gain),
    21, 1, 2, 854, "", 0 },

  { 428, "nlpid/Plants/plant BT power/Gain", offsetof(Parameters_NLPID,
    plantBTpower_Gain), 21, 1, 2, 856, "", 0 },

  { 429, "nlpid/Plants/plant VSP speed/Gain", offsetof(Parameters_NLPID,
    plantVSPspeed_Gain), 21, 1, 2, 858, "", 0 },

  { 430, "nlpid/Plants/Enable CSE1/Value", offsetof(Parameters_NLPID,
    EnableCSE1_Value), 21, 1, 2, 860, "", 0 },

  { 431, "nlpid/eta_psi/Gain", offsetof(Parameters_NLPID, eta_psi_Gain), 21, 1,
    2, 862, "", 0 },

  { 432, "nlpid/eta_psid/Gain", offsetof(Parameters_NLPID, eta_psid_Gain), 21, 1,
    2, 864, "", 0 },

  { 433, "nlpid/eta_x/Gain", offsetof(Parameters_NLPID, eta_x_Gain), 21, 1, 2,
    866, "", 0 },

  { 434, "nlpid/eta_xd/Gain", offsetof(Parameters_NLPID, eta_xd_Gain), 21, 1, 2,
    868, "", 0 },

  { 435, "nlpid/eta_y/Gain", offsetof(Parameters_NLPID, eta_y_Gain), 21, 1, 2,
    870, "", 0 },

  { 436, "nlpid/eta_yd/Gain", offsetof(Parameters_NLPID, eta_yd_Gain), 21, 1, 2,
    872, "", 0 },

  { 437, "nlpid/psi_los/Gain", offsetof(Parameters_NLPID, psi_los_Gain_h), 21, 1,
    2, 874, "", 0 },

  { 438, "nlpid/psi_plot/Gain", offsetof(Parameters_NLPID, psi_plot_Gain), 21, 1,
    2, 876, "", 0 },

  { 439, "nlpid/q_x/Gain", offsetof(Parameters_NLPID, q_x_Gain_f), 21, 1, 2, 878,
    "", 0 },

  { 440, "nlpid/q_y/Gain", offsetof(Parameters_NLPID, q_y_Gain_j), 21, 1, 2, 880,
    "", 0 },

  { 441, "nlpid/x_plot/Gain", offsetof(Parameters_NLPID, x_plot_Gain), 21, 1, 2,
    882, "", 0 },

  { 442, "nlpid/y_plot/Gain", offsetof(Parameters_NLPID, y_plot_Gain), 21, 1, 2,
    884, "", 0 },

  { 443,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R12/Gain",
    offsetof(Parameters_NLPID, R12_Gain), 21, 1, 2, 886, "", 0 },

  { 444,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R22/Gain",
    offsetof(Parameters_NLPID, R22_Gain), 21, 1, 2, 888, "", 0 },

  { 445,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/0/Value",
    offsetof(Parameters_NLPID, _Value), 21, 1, 2, 890, "", 0 },

  { 446,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S12/Gain",
    offsetof(Parameters_NLPID, S12_Gain_p), 21, 1, 2, 892, "", 0 },

  { 447,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value",
    offsetof(Parameters_NLPID, _Value_c), 21, 1, 2, 894, "", 0 },

  { 448,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain",
    offsetof(Parameters_NLPID, S12_Gain_k), 21, 1, 2, 896, "", 0 },

  { 449, "nlpid/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain", offsetof
    (Parameters_NLPID, BT_D_Gain1_Gain), 21, 1, 2, 898, "", 0 },

  { 450, "nlpid/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value", offsetof
    (Parameters_NLPID, BT_Power_Offset1_Value), 21, 1, 2, 900, "", 0 },

  { 451, "nlpid/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain", offsetof
    (Parameters_NLPID, BT_D_Gain2_Gain), 21, 1, 2, 902, "", 0 },

  { 452, "nlpid/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain", offsetof
    (Parameters_NLPID, BT_L_Gain1_Gain), 21, 1, 2, 904, "", 0 },

  { 453, "nlpid/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain", offsetof
    (Parameters_NLPID, BT_L_Gain2_Gain), 21, 1, 2, 906, "", 0 },

  { 454, "nlpid/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value", offsetof
    (Parameters_NLPID, BT_Power_Offset2_Value), 21, 1, 2, 908, "", 0 },

  { 455, "nlpid/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value", offsetof
    (Parameters_NLPID, BT_Power_Offset3_Value), 21, 1, 2, 910, "", 0 },

  { 456, "nlpid/Plants/CSE1/Bow Thruster/Constant/Value", offsetof
    (Parameters_NLPID, Constant_Value_a), 21, 1, 2, 912, "", 0 },

  { 457, "nlpid/Plants/CSE1/Bow Thruster/Constant1/Value", offsetof
    (Parameters_NLPID, Constant1_Value_c), 21, 1, 2, 914, "", 0 },

  { 458, "nlpid/Plants/CSE1/Bow Thruster/Neg/Gain", offsetof(Parameters_NLPID,
    Neg_Gain), 21, 1, 2, 916, "", 0 },

  { 459, "nlpid/Plants/CSE1/Voith Schneider Propeller /-x/Gain", offsetof
    (Parameters_NLPID, x_Gain), 21, 1, 2, 918, "", 0 },

  { 460, "nlpid/Plants/CSE1/Voith Schneider Propeller /-y/Gain", offsetof
    (Parameters_NLPID, y_Gain), 21, 1, 2, 920, "", 0 },

  { 461, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex",
    offsetof(Parameters_NLPID, Servo1_RowIdx), 76, 3, 2, 922, "", 0 },

  { 462, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_NLPID, Servo1_ColIdx), 76, 3, 2, 924, "", 0 },

  { 463, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo1/Table", offsetof
    (Parameters_NLPID, Servo1_Table), 36, 9, 2, 926, "", 0 },

  { 464, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex",
    offsetof(Parameters_NLPID, Servo2_RowIdx), 76, 3, 2, 928, "", 0 },

  { 465, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_NLPID, Servo2_ColIdx), 76, 3, 2, 930, "", 0 },

  { 466, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo2/Table", offsetof
    (Parameters_NLPID, Servo2_Table), 36, 9, 2, 932, "", 0 },

  { 467, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex",
    offsetof(Parameters_NLPID, Servo3_RowIdx), 76, 3, 2, 934, "", 0 },

  { 468, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_NLPID, Servo3_ColIdx), 76, 3, 2, 936, "", 0 },

  { 469, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo3/Table", offsetof
    (Parameters_NLPID, Servo3_Table), 36, 9, 2, 938, "", 0 },

  { 470, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex",
    offsetof(Parameters_NLPID, Servo4_RowIdx), 76, 3, 2, 940, "", 0 },

  { 471, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_NLPID, Servo4_ColIdx), 76, 3, 2, 942, "", 0 },

  { 472, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo4/Table", offsetof
    (Parameters_NLPID, Servo4_Table), 36, 9, 2, 944, "", 0 },

  { 473, "nlpid/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_NLPID, VPS_Speed_Gain_Gain), 21, 1, 2, 946, "", 0 },

  { 474, "nlpid/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_NLPID, VPS_Power_Offset_Value), 21, 1, 2, 948, "", 0 },

  { 475, "nlpid/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain", offsetof
    (Parameters_NLPID, VSPSPort_Gain), 21, 1, 2, 950, "", 0 },

  { 476, "nlpid/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_NLPID, VSPSStarboard_Gain), 21, 1, 2, 952, "", 0 },

  { 477, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_r/Value",
    offsetof(Parameters_NLPID, N_r_Value_j), 21, 1, 2, 954, "", 0 },

  { 478, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r/Gain",
    offsetof(Parameters_NLPID, N_r_Gain_p), 21, 1, 2, 956, "", 0 },

  { 479, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_v/Value",
    offsetof(Parameters_NLPID, N_v_Value_d), 21, 1, 2, 958, "", 0 },

  { 480, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v/Gain",
    offsetof(Parameters_NLPID, N_v_Gain_d), 21, 1, 2, 960, "", 0 },

  { 481, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/X_u/Value",
    offsetof(Parameters_NLPID, X_u_Value_m), 21, 1, 2, 962, "", 0 },

  { 482, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u/Gain",
    offsetof(Parameters_NLPID, X_u_Gain_m), 21, 1, 2, 964, "", 0 },

  { 483, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_v/Value",
    offsetof(Parameters_NLPID, Y_v_Value_p), 21, 1, 2, 966, "", 0 },

  { 484, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v/Gain",
    offsetof(Parameters_NLPID, Y_v_Gain_p), 21, 1, 2, 968, "", 0 },

  { 485, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_r/Value",
    offsetof(Parameters_NLPID, Y_r_Value_f), 21, 1, 2, 970, "", 0 },

  { 486, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr/Gain",
    offsetof(Parameters_NLPID, Y_vr_Gain_c), 21, 1, 2, 972, "", 0 },

  { 487, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_12/Value",
    offsetof(Parameters_NLPID, D_L_12_Value_g), 21, 1, 2, 974, "", 0 },

  { 488, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_13/Value",
    offsetof(Parameters_NLPID, D_L_13_Value_o), 21, 1, 2, 976, "", 0 },

  { 489, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_21/Value",
    offsetof(Parameters_NLPID, D_L_21_Value_d), 21, 1, 2, 978, "", 0 },

  { 490, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_31/Value",
    offsetof(Parameters_NLPID, D_L_31_Value_l), 21, 1, 2, 980, "", 0 },

  { 491,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0/Value",
    offsetof(Parameters_NLPID, psi_0_Value), 21, 1, 2, 982, "", 0 },

  { 492,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0/Value",
    offsetof(Parameters_NLPID, x_0_Value), 21, 1, 2, 984, "", 0 },

  { 493,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0/Value",
    offsetof(Parameters_NLPID, y_0_Value), 21, 1, 2, 986, "", 0 },

  { 494,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0/Value",
    offsetof(Parameters_NLPID, r_0_Value), 21, 1, 2, 988, "", 0 },

  { 495,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0/Value",
    offsetof(Parameters_NLPID, u_0_Value), 21, 1, 2, 990, "", 0 },

  { 496,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0/Value",
    offsetof(Parameters_NLPID, v_0_Value), 21, 1, 2, 992, "", 0 },

  { 497,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_NLPID, ResetLinearSimulatorintegrator_), 21, 1, 2, 994,
    "", 0 },

  { 498, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/I_z/Value",
    offsetof(Parameters_NLPID, I_z_Value_k), 21, 1, 2, 996, "", 0 },

  { 499, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m/Value",
    offsetof(Parameters_NLPID, m_Value_k), 21, 1, 2, 998, "", 0 },

  { 500,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/X_udot/Value",
    offsetof(Parameters_NLPID, X_udot_Value_k), 21, 1, 2, 1000, "", 0 },

  { 501, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_21/Value",
    offsetof(Parameters_NLPID, M_21_Value_h), 21, 1, 2, 1002, "", 0 },

  { 502, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_31/Value",
    offsetof(Parameters_NLPID, M_31_Value_d), 21, 1, 2, 1004, "", 0 },

  { 503, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_12/Value",
    offsetof(Parameters_NLPID, M_12_Value_j), 21, 1, 2, 1006, "", 0 },

  { 504,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_vdot/Value",
    offsetof(Parameters_NLPID, Y_vdot_Value_b), 21, 1, 2, 1008, "", 0 },

  { 505, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/x_g/Value",
    offsetof(Parameters_NLPID, x_g_Value_i), 21, 1, 2, 1010, "", 0 },

  { 506,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_vdot/Value",
    offsetof(Parameters_NLPID, N_vdot_Value_n), 21, 1, 2, 1012, "", 0 },

  { 507, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_13/Value",
    offsetof(Parameters_NLPID, M_13_Value_d), 21, 1, 2, 1014, "", 0 },

  { 508,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_rdot/Value",
    offsetof(Parameters_NLPID, Y_rdot_Value_f), 21, 1, 2, 1016, "", 0 },

  { 509,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_rdot/Value",
    offsetof(Parameters_NLPID, N_rdot_Value_f), 21, 1, 2, 1018, "", 0 },

  { 510, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_NLPID, R31_Value_n), 21, 1, 2, 1020, "", 0 },

  { 511, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_NLPID, R32_Value_g), 21, 1, 2, 1022, "", 0 },

  { 512, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_NLPID, R13_Value_i), 21, 1, 2, 1024, "", 0 },

  { 513, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_NLPID, R23_Value_i), 21, 1, 2, 1026, "", 0 },

  { 514, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_NLPID, R33_Value_k), 21, 1, 2, 1028, "", 0 },

  { 515, "nlpid/Plants/Linear Simulator/eta_surge_hil/Gain", offsetof
    (Parameters_NLPID, eta_surge_hil_Gain), 21, 1, 2, 1030, "", 0 },

  { 516, "nlpid/Plants/Linear Simulator/eta_sway_hil/Gain", offsetof
    (Parameters_NLPID, eta_sway_hil_Gain), 21, 1, 2, 1032, "", 0 },

  { 517, "nlpid/Plants/Linear Simulator/eta_yaw_hil/Gain", offsetof
    (Parameters_NLPID, eta_yaw_hil_Gain), 21, 1, 2, 1034, "", 0 },

  { 518, "nlpid/Plants/Linear Simulator/etadot_surge_hil/Gain", offsetof
    (Parameters_NLPID, etadot_surge_hil_Gain), 21, 1, 2, 1036, "", 0 },

  { 519, "nlpid/Plants/Linear Simulator/etadot_sway_hil/Gain", offsetof
    (Parameters_NLPID, etadot_sway_hil_Gain), 21, 1, 2, 1038, "", 0 },

  { 520, "nlpid/Plants/Linear Simulator/etadot_yaw_hil/Gain", offsetof
    (Parameters_NLPID, etadot_yaw_hil_Gain), 21, 1, 2, 1040, "", 0 },

  { 521, "nlpid/Plants/Linear Simulator/nu_surge_hil/Gain", offsetof
    (Parameters_NLPID, nu_surge_hil_Gain), 21, 1, 2, 1042, "", 0 },

  { 522, "nlpid/Plants/Linear Simulator/nu_sway_hil/Gain", offsetof
    (Parameters_NLPID, nu_sway_hil_Gain), 21, 1, 2, 1044, "", 0 },

  { 523, "nlpid/Plants/Linear Simulator/nu_yaw_hil/Gain", offsetof
    (Parameters_NLPID, nu_yaw_hil_Gain), 21, 1, 2, 1046, "", 0 },

  { 524,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_k1), 38, 1, 2, 1048, "", 0 },

  { 525,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_b), 38, 1, 2, 1050, "", 0 },

  { 526,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_g0p), 38, 1, 2, 1052, "", 0 },

  { 527,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_cz), 38, 1, 2, 1054, "", 0 },

  { 528,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_bp), 38, 1, 2, 1056, "", 0 },

  { 529,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_k), 38, 1, 2, 1058, "", 0 },

  { 530,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_ef), 38, 1, 2, 1060, "", 0 },

  { 531,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_o), 38, 1, 2, 1062, "", 0 },

  { 532,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_g3), 38, 1, 2, 1064, "", 0 },

  { 533,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_l), 38, 1, 2, 1066, "", 0 },

  { 534,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_p2), 38, 1, 2, 1068, "", 0 },

  { 535,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_d), 38, 1, 2, 1070, "", 0 },

  { 536,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_jh), 38, 1, 2, 1072, "", 0 },

  { 537,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_cy), 38, 1, 2, 1074, "", 0 },

  { 538,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_ej), 38, 1, 2, 1076, "", 0 },

  { 539,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_e), 38, 1, 2, 1078, "", 0 },

  { 540,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_an), 38, 1, 2, 1080, "", 0 },

  { 541,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_j3), 38, 1, 2, 1082, "", 0 },

  { 542,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_NLPID, Gain_Gain_fw), 38, 1, 2, 1084, "", 0 },

  { 543,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_NLPID, Gain1_Gain_lh), 38, 1, 2, 1086, "", 0 },
};

static int NI_ParamListSize = 544;
static int NI_ParamDimList[] = {
  1, 1,                                /* nlpid/Naviagation Systems/Controller Input Selector/Value */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain */
  1, 1,                                /* nlpid/Plants/Enable Linear Simulator/Value */
  1, 1,                                /* nlpid/Naviagation Systems/etadot_surge/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/etadot_sway/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/etadot_yaw/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/eta_surge/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/eta_sway/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/eta_yaw/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain */
  3, 3,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/Constant1/Value */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/nu_surge/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/nu_sway/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/nu_yaw/Gain */
  1, 1,                                /* nlpid/HMI/DP Input/x_d/Value */
  1, 1,                                /* nlpid/Guidance Systems/DP/eta_d DP N/Gain */
  1, 1,                                /* nlpid/HMI/DP Input/y_d/Value */
  1, 1,                                /* nlpid/Guidance Systems/DP/eta_d DP E/Gain */
  1, 1,                                /* nlpid/HMI/DP Input/psi_d/Value */
  1, 1,                                /* nlpid/HMI/DP Input/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* nlpid/Guidance Systems/DP/eta_d DP Psi/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Update laws/Reset q/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Update laws/q_0/q_x_0/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Update laws/q_0/q_y_0/Value */
  1, 1,                                /* nlpid/HMI/Path-following input/x_2/Value */
  1, 1,                                /* nlpid/HMI/Path-following input/x_1/Value */
  1, 1,                                /* nlpid/HMI/Path-following input/y_2/Value */
  1, 1,                                /* nlpid/HMI/Path-following input/y_1/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Path Selector/Value */
  1, 1,                                /* nlpid/HMI/Path-following input/r_x/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Update laws/Reset s/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Update laws/s_0/Value */
  1, 1,                                /* nlpid/HMI/Path-following input/k/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Gain/Gain */
  1, 1,                                /* nlpid/HMI/Path-following input/r_y/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/saturation/x_dmax/Value */
  1, 1,                                /* nlpid/HMI/Path-following input/origin_x/Value */
  1, 1,                                /* nlpid/HMI/Path-following input/origo_y/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/saturation/x_dmin/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/saturation/y_dmax/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/saturation/y_dmin/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Delta/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* nlpid/Guidance Systems/q_x/Gain */
  1, 1,                                /* nlpid/Guidance Systems/q_y/Gain */
  1, 1,                                /* nlpid/Guidance Systems/psi_los/Gain */
  1, 1,                                /* nlpid/Guidance Systems/path x_d/Gain */
  1, 1,                                /* nlpid/Guidance Systems/path y_d/Gain */
  1, 1,                                /* nlpid/Guidance Systems/path psi_d/Gain */
  1, 1,                                /* nlpid/HMI/Path-following input/u_d/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Control Mode/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 input/AS_LY/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 input/ScalingLY/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/PS3 u_1/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 input/AS_LX/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 input/ScalingLX/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/PS3 u_2/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 input/AS_RY/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 input/ScalingRY/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/PS3 u_3/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 input/AS_RX/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 input/Scaling_RX/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/PS3 u_4/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 input/L2/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 input/R2/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/PS3 u_5/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 input/PS3_BT_Power/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 input/PS3_VSP_Speed/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value */
  3, 3,                                /* nlpid/Control Systems/DP control/DP controller/Kp/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/K_p_surge_scale/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/K_p_sway_scale/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/K_p_yaw_scale/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/Reset_DP_integrator/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/Integrator/InitialCondition */
  3, 3,                                /* nlpid/Control Systems/DP control/DP controller/Ki/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/K_i_surge_scale/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/K_i_sway_scale/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/K_i_yaw_scale/Gain */
  3, 3,                                /* nlpid/Control Systems/DP control/DP controller/Kd/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/K_d_surge_scale/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/K_d_sway_scale/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/DP controller/K_d_yaw_scale/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/DP control/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Control Systems/DP control/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Control Systems/DP control/BT_power_limit/Value */
  1, 1,                                /* nlpid/Control Systems/DP control/VSP_speeds/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/R(psi)/R31/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/R(psi)/R32/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/R(psi)/R13/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/R(psi)/R23/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/R(psi)/R33/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_p_Surge/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_p/21/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_p/31/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_p/12/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_p_Sway/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_p/32/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_p/13/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_p/23/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_p_Yaw/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_i_Surge/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_i/21/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_i/31/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_i/12/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_i_Sway/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_i/32/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_i/13/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_i/23/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_i_Yaw/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/zeta/InitialCondition */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_d_Surge/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_d/21/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_d/31/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_d/12/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_d_Sway/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_d/32/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_d/13/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_d/23/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/K_d_Yaw/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain */
  2, 1,                                /* nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s eq/0_2x1/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Straight path/0_2x1/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/my/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/X_u/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-X_u/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_21/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_31/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_12/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Y_v/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_v/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/N_v/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_v/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_13/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Y_r/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_vr/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/N_r/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_r/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/m/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/X_udot/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_21/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_31/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_12/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/Y_vdot/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/x_g/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/N_vdot/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_13/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/Y_rdot/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/I_z/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/N_rdot/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain */
  2, 2,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/0_2x2/Value */
  2, 2,                                /* nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/0_2x2/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Update laws/omega_q/InitialCondition */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain */
  2, 1,                                /* nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/0_2x1/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/+ 2/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Constant/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Gain/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value */
  2, 1,                                /* nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^t eq/0_2x1/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S11/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/S(r)/R31/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S12/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S22/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S32/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S13/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S23/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S33/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/BT_power_limit/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/VSP_speeds/Value */
  1, 1,                                /* nlpid/Control Systems/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Control Systems/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value */
  1, 1,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value */
  19, 1,                               /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues */
  19, 1,                               /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table */
  21, 1,                               /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues */
  21, 1,                               /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table */
  19, 1,                               /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues */
  19, 1,                               /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table */
  17, 1,                               /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues */
  17, 1,                               /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table */
  1, 7,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues */
  1, 7,                                /* nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Gamma_q/12/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Gamma_q/21/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Gamma_q_Surge/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Gamma_q_Sway/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/lambda/Value */
  2, 2,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/I/Constant/Value */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Update laws/dot omega_q/Gain */
  2, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/0_2x1/Value */
  1, 1,                                /* nlpid/HMI/Battery Bow Thruster/Gain */
  1, 1,                                /* nlpid/HMI/Battery Servo/Gain */
  1, 1,                                /* nlpid/HMI/Battery Main/Gain */
  1, 1,                                /* nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain */
  1, 1,                                /* nlpid/Plants/saturation/Saturation/UpperLimit */
  1, 1,                                /* nlpid/Plants/saturation/Saturation/LowerLimit */
  1, 1,                                /* nlpid/Plants/saturation/Saturation1/UpperLimit */
  1, 1,                                /* nlpid/Plants/saturation/Saturation1/LowerLimit */
  1, 1,                                /* nlpid/Plants/saturation/Saturation2/UpperLimit */
  1, 1,                                /* nlpid/Plants/saturation/Saturation2/LowerLimit */
  1, 1,                                /* nlpid/Plants/saturation/plant tau_surge/Gain */
  1, 1,                                /* nlpid/Plants/saturation/plant tau_sway/Gain */
  1, 1,                                /* nlpid/Plants/saturation/plant tau_yaw/Gain */
  1, 1,                                /* nlpid/Plants/plant u_1/Gain */
  1, 1,                                /* nlpid/Plants/plant u_2/Gain */
  1, 1,                                /* nlpid/Plants/plant u_3/Gain */
  1, 1,                                /* nlpid/Plants/plant u_4/Gain */
  1, 1,                                /* nlpid/Plants/plant u_5/Gain */
  1, 1,                                /* nlpid/Plants/plant BT power/Gain */
  1, 1,                                /* nlpid/Plants/plant VSP speed/Gain */
  1, 1,                                /* nlpid/Plants/Enable CSE1/Value */
  1, 1,                                /* nlpid/eta_psi/Gain */
  1, 1,                                /* nlpid/eta_psid/Gain */
  1, 1,                                /* nlpid/eta_x/Gain */
  1, 1,                                /* nlpid/eta_xd/Gain */
  1, 1,                                /* nlpid/eta_y/Gain */
  1, 1,                                /* nlpid/eta_yd/Gain */
  1, 1,                                /* nlpid/psi_los/Gain */
  1, 1,                                /* nlpid/psi_plot/Gain */
  1, 1,                                /* nlpid/q_x/Gain */
  1, 1,                                /* nlpid/q_y/Gain */
  1, 1,                                /* nlpid/x_plot/Gain */
  1, 1,                                /* nlpid/y_plot/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R12/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R22/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/0/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S12/Gain */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value */
  1, 1,                                /* nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/Constant/Value */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/Constant1/Value */
  1, 1,                                /* nlpid/Plants/CSE1/Bow Thruster/Neg/Gain */
  1, 1,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* nlpid/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_r/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_v/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/X_u/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_v/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_r/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_12/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_13/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_21/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_31/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Reset Linear Simulator integrator/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/I_z/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/X_udot/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_21/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_31/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_12/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_vdot/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/x_g/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_vdot/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_13/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_rdot/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_rdot/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* nlpid/Plants/Linear Simulator/eta_surge_hil/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/eta_sway_hil/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/eta_yaw_hil/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/etadot_surge_hil/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/etadot_sway_hil/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/etadot_yaw_hil/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/nu_surge_hil/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/nu_sway_hil/Gain */
  1, 1,                                /* nlpid/Plants/Linear Simulator/nu_yaw_hil/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 707;
static NI_Signal NI_SigList[] = {
  { 0, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In", 0, "", offsetof
    (BlockIO_NLPID, QTMIn), BLOCKIO_SIG, 44, 9, 2, 0, 0 },

  { 1, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error", 0, "", offsetof
    (BlockIO_NLPID, QTMIn2Error), BLOCKIO_SIG, 21, 1, 2, 2, 0 },

  { 2, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual", 0, "",
    offsetof(BlockIO_NLPID, QTMIn9Residual), BLOCKIO_SIG, 21, 1, 2, 4, 0 },

  { 3, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In3", 0, "", offsetof
    (BlockIO_NLPID, QTMIn3), BLOCKIO_SIG, 21, 1, 2, 6, 0 },

  { 4, "nlpid/Naviagation Systems/Qualisys 6 DOF/mm2m x", 0, "", offsetof
    (BlockIO_NLPID, mm2mx), BLOCKIO_SIG, 21, 1, 2, 8, 0 },

  { 5, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In4", 0, "", offsetof
    (BlockIO_NLPID, QTMIn4), BLOCKIO_SIG, 21, 1, 2, 10, 0 },

  { 6, "nlpid/Naviagation Systems/Qualisys 6 DOF/mm2m y", 0, "", offsetof
    (BlockIO_NLPID, mm2my), BLOCKIO_SIG, 21, 1, 2, 12, 0 },

  { 7, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In6", 0, "", offsetof
    (BlockIO_NLPID, QTMIn6), BLOCKIO_SIG, 21, 1, 2, 14, 0 },

  { 8, "nlpid/Naviagation Systems/Qualisys 6 DOF/d2r yaw", 0, "", offsetof
    (BlockIO_NLPID, d2ryaw), BLOCKIO_SIG, 21, 1, 2, 16, 0 },

  { 9, "nlpid/Naviagation Systems/Qualisys 6 DOF/Derivative1", 0, "", offsetof
    (BlockIO_NLPID, Derivative1), BLOCKIO_SIG, 24, 3, 2, 18, 0 },

  { 10, "nlpid/Naviagation Systems/Etadot Switch", 0, "", offsetof(BlockIO_NLPID,
    EtadotSwitch), BLOCKIO_SIG, 24, 3, 2, 20, 0 },

  { 11, "nlpid/Naviagation Systems/etadot_surge", 0, "", offsetof(BlockIO_NLPID,
    etadot_surge), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "nlpid/Naviagation Systems/etadot_sway", 0, "", offsetof(BlockIO_NLPID,
    etadot_sway), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "nlpid/Naviagation Systems/etadot_yaw", 0, "", offsetof(BlockIO_NLPID,
    etadot_yaw), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "nlpid/Naviagation Systems/Eta Switch", 0, "", offsetof(BlockIO_NLPID,
    EtaSwitch), BLOCKIO_SIG, 24, 3, 2, 28, 0 },

  { 15, "nlpid/Naviagation Systems/eta_surge", 0, "", offsetof(BlockIO_NLPID,
    eta_surge), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "nlpid/Naviagation Systems/eta_sway", 0, "", offsetof(BlockIO_NLPID,
    eta_sway), BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17, "nlpid/Naviagation Systems/eta_yaw", 0, "", offsetof(BlockIO_NLPID,
    eta_yaw), BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In8", 0, "", offsetof
    (BlockIO_NLPID, QTMIn8), BLOCKIO_SIG, 21, 1, 2, 36, 0 },

  { 19, "nlpid/Naviagation Systems/Qualisys 6 DOF/d2r roll", 0, "", offsetof
    (BlockIO_NLPID, d2rroll), BLOCKIO_SIG, 21, 1, 2, 38, 0 },

  { 20, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In7", 0, "", offsetof
    (BlockIO_NLPID, QTMIn7), BLOCKIO_SIG, 21, 1, 2, 40, 0 },

  { 21, "nlpid/Naviagation Systems/Qualisys 6 DOF/d2r pitch", 0, "", offsetof
    (BlockIO_NLPID, d2rpitch), BLOCKIO_SIG, 21, 1, 2, 42, 0 },

  { 22,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_NLPID, sintheta), BLOCKIO_SIG, 24, 3, 2, 44, 0 },

  { 23,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_NLPID, costheta), BLOCKIO_SIG, 24, 3, 2, 46, 0 },

  { 24,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_NLPID, R11), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_NLPID, R21), BLOCKIO_SIG, 0, 1, 2, 50, 0 },

  { 26,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_NLPID, R31), BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_NLPID, R12), BLOCKIO_SIG, 0, 1, 2, 54, 0 },

  { 28,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_NLPID, R22), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_NLPID, R32), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_NLPID, R13), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_NLPID, R23), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_NLPID, R33), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33,
    "nlpid/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_NLPID, Reshape9x13x3), BLOCKIO_SIG, 36, 9, 2, 66, 0
  },

  { 34, "nlpid/Naviagation Systems/Qualisys 6 DOF/Matrix Concatenate2", 0, "",
    offsetof(BlockIO_NLPID, MatrixConcatenate2), BLOCKIO_SIG, 48, 36, 2, 68, 0 },

  { 35, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In5", 0, "", offsetof
    (BlockIO_NLPID, QTMIn5), BLOCKIO_SIG, 21, 1, 2, 70, 0 },

  { 36, "nlpid/Naviagation Systems/Qualisys 6 DOF/mm2m z", 0, "", offsetof
    (BlockIO_NLPID, mm2mz), BLOCKIO_SIG, 21, 1, 2, 72, 0 },

  { 37, "nlpid/Naviagation Systems/Qualisys 6 DOF/Derivative", 0, "", offsetof
    (BlockIO_NLPID, Derivative), BLOCKIO_SIG, 41, 6, 2, 74, 0 },

  { 38, "nlpid/Naviagation Systems/Qualisys 6 DOF/Product", 0, "", offsetof
    (BlockIO_NLPID, Product), BLOCKIO_SIG, 41, 6, 2, 76, 0 },

  { 39, "nlpid/Naviagation Systems/Nu Switch", 0, "", offsetof(BlockIO_NLPID,
    NuSwitch), BLOCKIO_SIG, 24, 3, 2, 78, 0 },

  { 40, "nlpid/Naviagation Systems/nu_surge", 0, "", offsetof(BlockIO_NLPID,
    nu_surge), BLOCKIO_SIG, 0, 1, 2, 80, 0 },

  { 41, "nlpid/Naviagation Systems/nu_sway", 0, "", offsetof(BlockIO_NLPID,
    nu_sway), BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42, "nlpid/Naviagation Systems/nu_yaw", 0, "", offsetof(BlockIO_NLPID,
    nu_yaw), BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43, "nlpid/Guidance Systems/DP/eta_d DP N", 0, "", offsetof(BlockIO_NLPID,
    eta_dDPN), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44, "nlpid/Guidance Systems/DP/eta_d DP E", 0, "", offsetof(BlockIO_NLPID,
    eta_dDPE), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "nlpid/HMI/DP Input/Degrees to Radians/Gain1", 0, "", offsetof
    (BlockIO_NLPID, Gain1), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46, "nlpid/Guidance Systems/DP/eta_d DP Psi", 0, "", offsetof(BlockIO_NLPID,
    eta_dDPPsi), BLOCKIO_SIG, 0, 1, 2, 92, 0 },

  { 47, "nlpid/Control Systems/Nonlinear PID/Update laws/q_0/q_x_0", 0, "",
    offsetof(BlockIO_NLPID, q_x_0), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48, "nlpid/Control Systems/Nonlinear PID/Update laws/q_0/q_y_0", 0, "",
    offsetof(BlockIO_NLPID, q_y_0), BLOCKIO_SIG, 0, 1, 2, 96, 0 },

  { 49, "nlpid/Control Systems/Nonlinear PID/Update laws/Integrator", 0, "",
    offsetof(BlockIO_NLPID, Integrator), BLOCKIO_SIG, 23, 2, 2, 98, 0 },

  { 50,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/p_d^s eq/x_2 - x_1",
    0, "", offsetof(BlockIO_NLPID, x_2x_1), BLOCKIO_SIG, 0, 1, 2, 100, 0 },

  { 51,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/p_d^s eq/y_2 - y_1",
    0, "", offsetof(BlockIO_NLPID, y_2y_1), BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Product",
    0, "", offsetof(BlockIO_NLPID, Product_l), BLOCKIO_SIG, 23, 2, 2, 104, 0 },

  { 53, "nlpid/Control Systems/Nonlinear PID/Update laws/s_0", 0, "", offsetof
    (BlockIO_NLPID, s_0), BLOCKIO_SIG, 0, 1, 2, 106, 0 },

  { 54, "nlpid/Control Systems/Nonlinear PID/Update laws/Integrator1", 0, "",
    offsetof(BlockIO_NLPID, Integrator1), BLOCKIO_SIG, 21, 1, 2, 108, 0 },

  { 55,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2), BLOCKIO_SIG, 0, 1, 2, 110, 0 },

  { 56,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/sin(s)", 0,
    "", offsetof(BlockIO_NLPID, sins), BLOCKIO_SIG, 0, 1, 2, 112, 0 },

  { 57,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_b), BLOCKIO_SIG, 0, 1, 2, 114, 0 },

  { 58, "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain), BLOCKIO_SIG, 0, 1, 2, 116, 0 },

  { 59,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/cos(s)", 0,
    "", offsetof(BlockIO_NLPID, coss), BLOCKIO_SIG, 0, 1, 2, 118, 0 },

  { 60,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1), BLOCKIO_SIG, 0, 1, 2, 120, 0 },

  { 61,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract), BLOCKIO_SIG, 0, 1, 2, 122, 0 },

  { 62,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_k), BLOCKIO_SIG, 23, 2, 2, 124, 0 },

  { 63,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s selcetor/Add",
    0, "", offsetof(BlockIO_NLPID, Add), BLOCKIO_SIG, 23, 2, 2, 126, 0 },

  { 64,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPID, TrigonometricFunction), BLOCKIO_SIG, 0, 1, 2,
    128, 0 },

  { 65,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_l), BLOCKIO_SIG, 0, 1, 2, 130, 0 },

  { 66,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_NLPID, Saturation), BLOCKIO_SIG, 0, 1, 2, 132, 0 },

  { 67,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_NLPID, Sign), BLOCKIO_SIG, 0, 1, 2, 134, 0 },

  { 68,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_g), BLOCKIO_SIG, 0, 1, 2, 136, 0 },

  { 69,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_NLPID, Sum1), BLOCKIO_SIG, 0, 1, 2, 138, 0 },

  { 70,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction), BLOCKIO_SIG, 0, 1, 2, 140, 0 },

  { 71,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Sum", 0,
    "", offsetof(BlockIO_NLPID, Sum), BLOCKIO_SIG, 0, 1, 2, 142, 0 },

  { 72,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_o), BLOCKIO_SIG, 0, 1, 2, 144, 0 },

  { 73,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_i), BLOCKIO_SIG, 0, 1, 2, 146, 0 },

  { 74,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation",
    0, "", offsetof(BlockIO_NLPID, Saturation_k), BLOCKIO_SIG, 0, 1, 2, 148, 0 },

  { 75,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Sign",
    0, "", offsetof(BlockIO_NLPID, Sign_o), BLOCKIO_SIG, 0, 1, 2, 150, 0 },

  { 76,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_h), BLOCKIO_SIG, 0, 1, 2, 152, 0 },

  { 77,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Sum1",
    0, "", offsetof(BlockIO_NLPID, Sum1_o), BLOCKIO_SIG, 0, 1, 2, 154, 0 },

  { 78,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_g), BLOCKIO_SIG, 0, 1, 2, 156, 0
  },

  { 79,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_h), BLOCKIO_SIG, 0, 1, 2, 158, 0 },

  { 80,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_f), BLOCKIO_SIG, 0, 1, 2, 160, 0 },

  { 81,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2^T/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_d), BLOCKIO_SIG, 22, 4, 2, 162,
    0 },

  { 82,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/p_d eq/x_2 - x_1",
    0, "", offsetof(BlockIO_NLPID, x_2x_1_p), BLOCKIO_SIG, 0, 1, 2, 164, 0 },

  { 83,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/p_d eq/(x_2 - x_1) + s",
    0, "", offsetof(BlockIO_NLPID, x_2x_1s), BLOCKIO_SIG, 0, 1, 2, 166, 0 },

  { 84,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/p_d eq/(x_2 - x_1) + s + x_1",
    0, "", offsetof(BlockIO_NLPID, x_2x_1sx_1), BLOCKIO_SIG, 0, 1, 2, 168, 0 },

  { 85,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/p_d eq/y_2 - y_1",
    0, "", offsetof(BlockIO_NLPID, y_2y_1_g), BLOCKIO_SIG, 0, 1, 2, 170, 0 },

  { 86,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/p_d eq/(y_2 - y_1) + s",
    0, "", offsetof(BlockIO_NLPID, y_2y_1s), BLOCKIO_SIG, 0, 1, 2, 172, 0 },

  { 87,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/p_d eq/(y_2 - y_1) + s + y_1",
    0, "", offsetof(BlockIO_NLPID, y_2y_1sy_1), BLOCKIO_SIG, 0, 1, 2, 174, 0 },

  { 88,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/p_d1 +a",
    0, "", offsetof(BlockIO_NLPID, p_d1a), BLOCKIO_SIG, 23, 2, 2, 176, 0 },

  { 89,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Product2", 0,
    "", offsetof(BlockIO_NLPID, Product2_j), BLOCKIO_SIG, 0, 1, 2, 178, 0 },

  { 90, "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/cos(s)",
    0, "", offsetof(BlockIO_NLPID, coss_p), BLOCKIO_SIG, 0, 1, 2, 180, 0 },

  { 91, "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_la), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92, "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Add", 0,
    "", offsetof(BlockIO_NLPID, Add_i), BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93, "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/sin(s)",
    0, "", offsetof(BlockIO_NLPID, sins_f), BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Product1", 0,
    "", offsetof(BlockIO_NLPID, Product1_f), BLOCKIO_SIG, 0, 1, 2, 188, 0 },

  { 95, "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d eq/Add1", 0,
    "", offsetof(BlockIO_NLPID, Add1), BLOCKIO_SIG, 0, 1, 2, 190, 0 },

  { 96,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/1 - a",
    0, "", offsetof(BlockIO_NLPID, a), BLOCKIO_SIG, 0, 1, 2, 192, 0 },

  { 97,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/p_d2 + (1- a )",
    0, "", offsetof(BlockIO_NLPID, p_d21a), BLOCKIO_SIG, 23, 2, 2, 194, 0 },

  { 98,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d selcetor/Add",
    0, "", offsetof(BlockIO_NLPID, Add_m), BLOCKIO_SIG, 23, 2, 2, 196, 0 },

  { 99,
    "nlpid/Guidance Systems/Path-following/Path/saturation/Saturation x/Switch",
    0, "", offsetof(BlockIO_NLPID, Switch), BLOCKIO_SIG, 0, 1, 2, 198, 0 },

  { 100,
    "nlpid/Guidance Systems/Path-following/Path/saturation/Saturation x/Switch2",
    0, "", offsetof(BlockIO_NLPID, Switch2), BLOCKIO_SIG, 0, 1, 2, 200, 0 },

  { 101,
    "nlpid/Guidance Systems/Path-following/Path/saturation/Saturation y/Switch",
    0, "", offsetof(BlockIO_NLPID, Switch_b), BLOCKIO_SIG, 0, 1, 2, 202, 0 },

  { 102,
    "nlpid/Guidance Systems/Path-following/Path/saturation/Saturation y/Switch2",
    0, "", offsetof(BlockIO_NLPID, Switch2_b), BLOCKIO_SIG, 0, 1, 2, 204, 0 },

  { 103,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/q - p_d",
    0, "", offsetof(BlockIO_NLPID, qp_d), BLOCKIO_SIG, 23, 2, 2, 206, 0 },

  { 104,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon",
    0, "", offsetof(BlockIO_NLPID, epsilon), BLOCKIO_SIG, 23, 2, 2, 208, 0 },

  { 105,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector",
    0, "", offsetof(BlockIO_NLPID, MultiportSelector), BLOCKIO_SIG, 21, 1, 2,
    210, 0 },

  { 106,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPID, TrigonometricFunction_e), BLOCKIO_SIG, 21, 1,
    2, 212, 0 },

  { 107,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_j), BLOCKIO_SIG, 21, 1, 2, 214, 0 },

  { 108,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation",
    0, "", offsetof(BlockIO_NLPID, Saturation_n), BLOCKIO_SIG, 21, 1, 2, 216, 0
  },

  { 109,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Sign",
    0, "", offsetof(BlockIO_NLPID, Sign_p), BLOCKIO_SIG, 21, 1, 2, 218, 0 },

  { 110,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_f), BLOCKIO_SIG, 21, 1, 2, 220, 0 },

  { 111,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Sum1",
    0, "", offsetof(BlockIO_NLPID, Sum1_n), BLOCKIO_SIG, 21, 1, 2, 222, 0 },

  { 112,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_b), BLOCKIO_SIG, 21, 1, 2, 224,
    0 },

  { 113,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_g), BLOCKIO_SIG, 21, 1, 2, 226, 0 },

  { 114,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_o3), BLOCKIO_SIG, 21, 1, 2, 228, 0 },

  { 115,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_j), BLOCKIO_SIG, 21, 1, 2, 230, 0 },

  { 116,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_c), BLOCKIO_SIG, 21, 1, 2, 232, 0 },

  { 117,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation",
    0, "", offsetof(BlockIO_NLPID, Saturation_kb), BLOCKIO_SIG, 21, 1, 2, 234, 0
  },

  { 118,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Sign",
    0, "", offsetof(BlockIO_NLPID, Sign_k), BLOCKIO_SIG, 21, 1, 2, 236, 0 },

  { 119,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_fb), BLOCKIO_SIG, 21, 1, 2, 238, 0 },

  { 120,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Sum1",
    0, "", offsetof(BlockIO_NLPID, Sum1_i), BLOCKIO_SIG, 21, 1, 2, 240, 0 },

  { 121,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_a), BLOCKIO_SIG, 21, 1, 2, 242,
    0 },

  { 122,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_p), BLOCKIO_SIG, 21, 1, 2, 244, 0 },

  { 123,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_d), BLOCKIO_SIG, 21, 1, 2, 246, 0 },

  { 124,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPID, VectorConcatenate), BLOCKIO_SIG, 24, 3, 2,
    248, 0 },

  { 125, "nlpid/Guidance Systems/q_x", 0, "", offsetof(BlockIO_NLPID, q_x),
    BLOCKIO_SIG, 0, 1, 2, 250, 0 },

  { 126, "nlpid/Guidance Systems/q_y", 0, "", offsetof(BlockIO_NLPID, q_y),
    BLOCKIO_SIG, 0, 1, 2, 252, 0 },

  { 127, "nlpid/Guidance Systems/psi_los", 0, "", offsetof(BlockIO_NLPID,
    psi_los), BLOCKIO_SIG, 0, 1, 2, 254, 0 },

  { 128, "nlpid/Guidance Systems/path x_d", 0, "", offsetof(BlockIO_NLPID,
    pathx_d), BLOCKIO_SIG, 0, 1, 2, 256, 0 },

  { 129, "nlpid/Guidance Systems/path y_d", 0, "", offsetof(BlockIO_NLPID,
    pathy_d), BLOCKIO_SIG, 0, 1, 2, 258, 0 },

  { 130, "nlpid/Guidance Systems/path psi_d", 0, "", offsetof(BlockIO_NLPID,
    pathpsi_d), BLOCKIO_SIG, 0, 1, 2, 260, 0 },

  { 131,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_i), BLOCKIO_SIG, 20, 2, 2, 262,
    0 },

  { 132,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_j), BLOCKIO_SIG, 0, 1, 2, 264, 0 },

  { 133,
    "nlpid/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_NLPID, sqrt_j), BLOCKIO_SIG, 0, 1, 2, 266, 0 },

  { 134,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Product",
    0, "", offsetof(BlockIO_NLPID, Product_jd), BLOCKIO_SIG, 0, 1, 2, 268, 0 },

  { 135,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_at), BLOCKIO_SIG, 20, 2, 2, 270,
    0 },

  { 136,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_o), BLOCKIO_SIG, 0, 1, 2, 272, 0 },

  { 137,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/|p_d^s| eq/sqrt", 0,
    "", offsetof(BlockIO_NLPID, sqrt_f), BLOCKIO_SIG, 0, 1, 2, 274, 0 },

  { 138,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_h), BLOCKIO_SIG, 0, 1, 2, 276, 0 },

  { 139,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_j), BLOCKIO_SIG, 0, 1, 2, 278, 0 },

  { 140,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/|p_d^s| selcetor/Add",
    0, "", offsetof(BlockIO_NLPID, Add_p), BLOCKIO_SIG, 0, 1, 2, 280, 0 },

  { 141, "nlpid/Guidance Systems/Path-following/Speed assigment/v_s eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide), BLOCKIO_SIG, 0, 1, 2, 282, 0 },

  { 142, "nlpid/Control Systems/PS3 input/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_NLPID,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 284, 0 },

  { 143, "nlpid/Control Systems/PS3 u input control/PS3 u_1", 0, "u_1", offsetof
    (BlockIO_NLPID, u_1), BLOCKIO_SIG, 0, 1, 2, 286, 0 },

  { 144, "nlpid/Control Systems/PS3 input/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_NLPID,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 288, 0 },

  { 145, "nlpid/Control Systems/PS3 u input control/PS3 u_2", 0, "u_2", offsetof
    (BlockIO_NLPID, u_2), BLOCKIO_SIG, 0, 1, 2, 290, 0 },

  { 146, "nlpid/Control Systems/PS3 input/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_NLPID,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 292, 0 },

  { 147, "nlpid/Control Systems/PS3 u input control/PS3 u_3", 0, "u_3", offsetof
    (BlockIO_NLPID, u_3), BLOCKIO_SIG, 0, 1, 2, 294, 0 },

  { 148, "nlpid/Control Systems/PS3 input/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_NLPID,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 296, 0 },

  { 149, "nlpid/Control Systems/PS3 u input control/PS3 u_4", 0, "u_4", offsetof
    (BlockIO_NLPID, u_4), BLOCKIO_SIG, 0, 1, 2, 298, 0 },

  { 150, "nlpid/Control Systems/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_NLPID, BowThrusterdirection),
    BLOCKIO_SIG, 0, 1, 2, 300, 0 },

  { 151, "nlpid/Control Systems/PS3 u input control/PS3 u_5", 0, "u_5", offsetof
    (BlockIO_NLPID, u_5), BLOCKIO_SIG, 0, 1, 2, 302, 0 },

  { 152,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_NLPID, l_x1), BLOCKIO_SIG, 0, 1, 2, 304, 0 },

  { 153,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_NLPID, l_y2), BLOCKIO_SIG, 0, 1, 2, 306, 0 },

  { 154,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_NLPID, l_x2), BLOCKIO_SIG, 0, 1, 2, 308, 0 },

  { 155,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_NLPID, x5), BLOCKIO_SIG, 31, 15, 2, 310, 0 },

  { 156,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_NLPID, Pseudoinverse), BLOCKIO_SIG, 30, 15, 2, 312,
    0 },

  { 157, "nlpid/Control Systems/DP control/DP controller/yaw angle", 0, "psi",
    offsetof(BlockIO_NLPID, psi), BLOCKIO_SIG, 0, 1, 2, 314, 0 },

  { 158,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_NLPID, Saturation_b), BLOCKIO_SIG, 0, 1, 2, 316, 0 },

  { 159,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_NLPID, Sign_g), BLOCKIO_SIG, 0, 1, 2, 318, 0 },

  { 160,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_gl), BLOCKIO_SIG, 0, 1, 2, 320, 0 },

  { 161,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_NLPID, Sum1_m), BLOCKIO_SIG, 0, 1, 2, 322, 0 },

  { 162,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_al), BLOCKIO_SIG, 0, 1, 2, 324,
    0 },

  { 163,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_a), BLOCKIO_SIG, 0, 1, 2, 326, 0 },

  { 164, "nlpid/Control Systems/DP control/DP controller/Sum2", 0,
    "regulation error", offsetof(BlockIO_NLPID, regulationerror), BLOCKIO_SIG,
    24, 3, 2, 328, 0 },

  { 165,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_NLPID, Saturation_a), BLOCKIO_SIG, 0, 1, 2, 330, 0 },

  { 166,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_NLPID, Sign_i), BLOCKIO_SIG, 0, 1, 2, 332, 0 },

  { 167,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_m), BLOCKIO_SIG, 0, 1, 2, 334, 0 },

  { 168,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_NLPID, Sum1_k), BLOCKIO_SIG, 0, 1, 2, 336, 0 },

  { 169,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_gf), BLOCKIO_SIG, 0, 1, 2, 338,
    0 },

  { 170,
    "nlpid/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_m), BLOCKIO_SIG, 0, 1, 2, 340, 0 },

  { 171,
    "nlpid/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_NLPID, Row1), BLOCKIO_SIG, 0, 1, 2, 342, 0 },

  { 172,
    "nlpid/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_NLPID, Row2), BLOCKIO_SIG, 0, 1, 2, 344, 0 },

  { 173,
    "nlpid/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_NLPID, Row3), BLOCKIO_SIG, 0, 1, 2, 346, 0 },

  { 174, "nlpid/Control Systems/DP control/DP controller/Kp", 0, "", offsetof
    (BlockIO_NLPID, Kp), BLOCKIO_SIG, 24, 3, 2, 348, 0 },

  { 175, "nlpid/Control Systems/DP control/DP controller/K_p_surge_scale", 0, "",
    offsetof(BlockIO_NLPID, K_p_surge_scale), BLOCKIO_SIG, 0, 1, 2, 350, 0 },

  { 176, "nlpid/Control Systems/DP control/DP controller/K_p_sway_scale", 0, "",
    offsetof(BlockIO_NLPID, K_p_sway_scale), BLOCKIO_SIG, 0, 1, 2, 352, 0 },

  { 177, "nlpid/Control Systems/DP control/DP controller/K_p_yaw_scale", 0, "",
    offsetof(BlockIO_NLPID, K_p_yaw_scale), BLOCKIO_SIG, 0, 1, 2, 354, 0 },

  { 178, "nlpid/Control Systems/DP control/DP controller/Integrator", 0, "",
    offsetof(BlockIO_NLPID, Integrator_f), BLOCKIO_SIG, 24, 3, 2, 356, 0 },

  { 179, "nlpid/Control Systems/DP control/DP controller/Ki", 0, "", offsetof
    (BlockIO_NLPID, Ki), BLOCKIO_SIG, 24, 3, 2, 358, 0 },

  { 180, "nlpid/Control Systems/DP control/DP controller/K_i_surge_scale", 0, "",
    offsetof(BlockIO_NLPID, K_i_surge_scale), BLOCKIO_SIG, 0, 1, 2, 360, 0 },

  { 181, "nlpid/Control Systems/DP control/DP controller/K_i_sway_scale", 0, "",
    offsetof(BlockIO_NLPID, K_i_sway_scale), BLOCKIO_SIG, 0, 1, 2, 362, 0 },

  { 182, "nlpid/Control Systems/DP control/DP controller/K_i_yaw_scale", 0, "",
    offsetof(BlockIO_NLPID, K_i_yaw_scale), BLOCKIO_SIG, 0, 1, 2, 364, 0 },

  { 183, "nlpid/Control Systems/DP control/DP controller/Sum3", 0, "", offsetof
    (BlockIO_NLPID, Sum3), BLOCKIO_SIG, 24, 3, 2, 366, 0 },

  { 184, "nlpid/Control Systems/DP control/DP controller/Kd", 0, "", offsetof
    (BlockIO_NLPID, Kd), BLOCKIO_SIG, 24, 3, 2, 368, 0 },

  { 185, "nlpid/Control Systems/DP control/DP controller/K_d_surge_scale", 0, "",
    offsetof(BlockIO_NLPID, K_d_surge_scale), BLOCKIO_SIG, 0, 1, 2, 370, 0 },

  { 186, "nlpid/Control Systems/DP control/DP controller/K_d_sway_scale", 0, "",
    offsetof(BlockIO_NLPID, K_d_sway_scale), BLOCKIO_SIG, 0, 1, 2, 372, 0 },

  { 187, "nlpid/Control Systems/DP control/DP controller/K_d_yaw_scale", 0, "",
    offsetof(BlockIO_NLPID, K_d_yaw_scale), BLOCKIO_SIG, 0, 1, 2, 374, 0 },

  { 188, "nlpid/Control Systems/DP control/DP controller/Sum1", 0, "", offsetof
    (BlockIO_NLPID, Sum1_p), BLOCKIO_SIG, 24, 3, 2, 376, 0 },

  { 189,
    "nlpid/Control Systems/DP control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_NLPID, Product_n), BLOCKIO_SIG, 29, 5, 2, 378, 0 },

  { 190,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone), BLOCKIO_SIG, 0, 1, 2, 380, 0 },

  { 191,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_NLPID, f_10), BLOCKIO_SIG, 0, 1, 2, 382, 0 },

  { 192,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_NLPID, f_10_l), BLOCKIO_SIG, 0, 1, 2, 384, 0 },

  { 193,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch), BLOCKIO_SIG, 0, 1, 2, 386,
    0 },

  { 194,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone_l), BLOCKIO_SIG, 0, 1, 2, 388, 0 },

  { 195,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_NLPID, f_20), BLOCKIO_SIG, 0, 1, 2, 390, 0 },

  { 196,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_NLPID, f_20_h), BLOCKIO_SIG, 0, 1, 2, 392, 0 },

  { 197,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch_o), BLOCKIO_SIG, 0, 1, 2, 394,
    0 },

  { 198,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone_i), BLOCKIO_SIG, 0, 1, 2, 396, 0 },

  { 199,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_NLPID, f_30), BLOCKIO_SIG, 0, 1, 2, 398, 0 },

  { 200,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_NLPID, f_30_i), BLOCKIO_SIG, 0, 1, 2, 400, 0 },

  { 201,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch_n), BLOCKIO_SIG, 0, 1, 2, 402,
    0 },

  { 202,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone_ly), BLOCKIO_SIG, 0, 1, 2, 404, 0 },

  { 203,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_NLPID, f_40), BLOCKIO_SIG, 0, 1, 2, 406, 0 },

  { 204,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_NLPID, f_40_f), BLOCKIO_SIG, 0, 1, 2, 408, 0 },

  { 205,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch_o0), BLOCKIO_SIG, 0, 1, 2,
    410, 0 },

  { 206,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone_g), BLOCKIO_SIG, 0, 1, 2, 412, 0 },

  { 207,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_NLPID, f_50), BLOCKIO_SIG, 0, 1, 2, 414, 0 },

  { 208,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_NLPID, f_50_o), BLOCKIO_SIG, 0, 1, 2, 416, 0 },

  { 209,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch_ng), BLOCKIO_SIG, 0, 1, 2,
    418, 0 },

  { 210, "nlpid/Control Systems/DP control/Saturation", 0, "", offsetof
    (BlockIO_NLPID, Saturation_kt), BLOCKIO_SIG, 29, 5, 2, 420, 0 },

  { 211,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_NLPID, l_x1_l), BLOCKIO_SIG, 0, 1, 2, 422, 0 },

  { 212,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_NLPID, l_y2_m), BLOCKIO_SIG, 0, 1, 2, 424, 0 },

  { 213,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_NLPID, l_x2_p), BLOCKIO_SIG, 0, 1, 2, 426, 0 },

  { 214,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_NLPID, x5_n), BLOCKIO_SIG, 31, 15, 2, 428, 0 },

  { 215,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_NLPID, Pseudoinverse_c), BLOCKIO_SIG, 30, 15, 2, 430,
    0 },

  { 216, "nlpid/Control Systems/Nonlinear PID/R(psi)/R11", 0, "", offsetof
    (BlockIO_NLPID, R11_a), BLOCKIO_SIG, 0, 1, 2, 432, 0 },

  { 217, "nlpid/Control Systems/Nonlinear PID/R(psi)/R21", 0, "", offsetof
    (BlockIO_NLPID, R21_n), BLOCKIO_SIG, 0, 1, 2, 434, 0 },

  { 218, "nlpid/Control Systems/Nonlinear PID/R(psi)/R12", 0, "", offsetof
    (BlockIO_NLPID, R12_c), BLOCKIO_SIG, 0, 1, 2, 436, 0 },

  { 219, "nlpid/Control Systems/Nonlinear PID/R(psi)/R22", 0, "", offsetof
    (BlockIO_NLPID, R22_l), BLOCKIO_SIG, 0, 1, 2, 438, 0 },

  { 220, "nlpid/Control Systems/Nonlinear PID/R(psi)/R(psi)", 0, "", offsetof
    (BlockIO_NLPID, Rpsi), BLOCKIO_SIG, 36, 9, 2, 440, 0 },

  { 221, "nlpid/Control Systems/Nonlinear PID/R^T/Math Function", 0, "",
    offsetof(BlockIO_NLPID, MathFunction_l), BLOCKIO_SIG, 36, 9, 2, 442, 0 },

  { 222, "nlpid/Control Systems/Nonlinear PID/K_p/R(psi)", 0, "", offsetof
    (BlockIO_NLPID, Rpsi_b), BLOCKIO_SIG, 36, 9, 2, 444, 0 },

  { 223,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_p), BLOCKIO_SIG, 0, 1, 2, 446, 0 },

  { 224,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_NLPID, Saturation_bi), BLOCKIO_SIG, 0, 1, 2, 448, 0
  },

  { 225,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_NLPID, Sign_h), BLOCKIO_SIG, 0, 1, 2, 450, 0 },

  { 226,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_hl), BLOCKIO_SIG, 0, 1, 2, 452, 0 },

  { 227,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_NLPID, Sum1_iw), BLOCKIO_SIG, 0, 1, 2, 454, 0 },

  { 228,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_be), BLOCKIO_SIG, 0, 1, 2, 456,
    0 },

  { 229,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_l), BLOCKIO_SIG, 0, 1, 2, 458, 0 },

  { 230,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_oh), BLOCKIO_SIG, 0, 1, 2, 460, 0 },

  { 231, "nlpid/Control Systems/Nonlinear PID/Error/Subtract", 0, "", offsetof
    (BlockIO_NLPID, Subtract_k), BLOCKIO_SIG, 24, 3, 2, 462, 0 },

  { 232,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_gi), BLOCKIO_SIG, 0, 1, 2, 464, 0 },

  { 233,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_NLPID, Saturation_kg), BLOCKIO_SIG, 0, 1, 2, 466, 0
  },

  { 234,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_NLPID, Sign_ge), BLOCKIO_SIG, 0, 1, 2, 468, 0 },

  { 235,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_e), BLOCKIO_SIG, 0, 1, 2, 470, 0 },

  { 236,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_NLPID, Sum1_a), BLOCKIO_SIG, 0, 1, 2, 472, 0 },

  { 237,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_e), BLOCKIO_SIG, 0, 1, 2, 474, 0
  },

  { 238,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_f), BLOCKIO_SIG, 0, 1, 2, 476, 0 },

  { 239,
    "nlpid/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_b), BLOCKIO_SIG, 0, 1, 2, 478, 0 },

  { 240, "nlpid/Control Systems/Nonlinear PID/Control law/tau_PID/Product", 0,
    "", offsetof(BlockIO_NLPID, Product_bj), BLOCKIO_SIG, 24, 3, 2, 480, 0 },

  { 241, "nlpid/Control Systems/Nonlinear PID/K_i/R(psi)", 0, "", offsetof
    (BlockIO_NLPID, Rpsi_m), BLOCKIO_SIG, 36, 9, 2, 482, 0 },

  { 242, "nlpid/Control Systems/Nonlinear PID/zeta", 0, "", offsetof
    (BlockIO_NLPID, zeta), BLOCKIO_SIG, 26, 3, 2, 484, 0 },

  { 243, "nlpid/Control Systems/Nonlinear PID/Control law/tau_PID/Product1", 0,
    "", offsetof(BlockIO_NLPID, Product1_o), BLOCKIO_SIG, 26, 3, 2, 486, 0 },

  { 244, "nlpid/Control Systems/Nonlinear PID/K_d/R(psi)", 0, "", offsetof
    (BlockIO_NLPID, Rpsi_k), BLOCKIO_SIG, 36, 9, 2, 488, 0 },

  { 245,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qx",
    0, "", offsetof(BlockIO_NLPID, f_qx), BLOCKIO_SIG, 21, 1, 2, 490, 0 },

  { 246,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qy",
    0, "", offsetof(BlockIO_NLPID, f_qy), BLOCKIO_SIG, 21, 1, 2, 492, 0 },

  { 247,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_p), BLOCKIO_SIG, 23, 2, 2, 494, 0 },

  { 248,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Delta^2",
    0, "", offsetof(BlockIO_NLPID, Delta2), BLOCKIO_SIG, 0, 1, 2, 496, 0 },

  { 249,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_n2), BLOCKIO_SIG, 21, 1, 2, 498, 0 },

  { 250,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_f), BLOCKIO_SIG, 21, 1, 2, 500, 0 },

  { 251,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_b), BLOCKIO_SIG, 21, 1, 2, 502, 0 },

  { 252,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector1",
    0, "", offsetof(BlockIO_NLPID, MultiportSelector1), BLOCKIO_SIG, 20, 2, 2,
    504, 0 },

  { 253,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_f), BLOCKIO_SIG, 20, 2, 2, 506, 0 },

  { 254,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/-1",
    0, "", offsetof(BlockIO_NLPID, u), BLOCKIO_SIG, 20, 2, 2, 508, 0 },

  { 255,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPID, VectorConcatenate_a), BLOCKIO_SIG, 24, 3, 2,
    510, 0 },

  { 256,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Product",
    0, "", offsetof(BlockIO_NLPID, Product_m), BLOCKIO_SIG, 23, 2, 2, 512, 0 },

  { 257,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2_o), BLOCKIO_SIG, 0, 1, 2, 514, 0 },

  { 258,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/sin(s)3",
    0, "", offsetof(BlockIO_NLPID, sins3), BLOCKIO_SIG, 0, 1, 2, 516, 0 },

  { 259,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_p), BLOCKIO_SIG, 0, 1, 2, 518, 0
  },

  { 260,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_d), BLOCKIO_SIG, 0, 1, 2, 520, 0 },

  { 261,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/cos(s)3",
    0, "", offsetof(BlockIO_NLPID, coss3), BLOCKIO_SIG, 0, 1, 2, 522, 0 },

  { 262,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_fw), BLOCKIO_SIG, 0, 1, 2, 524, 0 },

  { 263,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^3 eq/Gain", 0,
    "", offsetof(BlockIO_NLPID, Gain_mw), BLOCKIO_SIG, 0, 1, 2, 526, 0 },

  { 264,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_o), BLOCKIO_SIG, 0, 1, 2, 528, 0 },

  { 265,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_i), BLOCKIO_SIG, 23, 2, 2, 530, 0 },

  { 266,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_ds^2 selcetor/Add",
    0, "", offsetof(BlockIO_NLPID, Add_e), BLOCKIO_SIG, 23, 2, 2, 532, 0 },

  { 267,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s eq/x_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_NLPID, x_dsy_ds2), BLOCKIO_SIG, 0, 1, 2, 534, 0 },

  { 268,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s eq/x_d^s^2 + y_d^s",
    0, "", offsetof(BlockIO_NLPID, x_ds2y_ds), BLOCKIO_SIG, 0, 1, 2, 536, 0 },

  { 269,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s eq/( x_d^s + y_d^s^2 ) - ( x_d^s^2 + y_d^s )",
    0, "", offsetof(BlockIO_NLPID, x_dsy_ds2x_ds2y_ds), BLOCKIO_SIG, 0, 1, 2,
    538, 0 },

  { 270, "nlpid/Guidance Systems/Path-following/Heading/psi_d^s eq/( x_d^s )^2",
    0, "", offsetof(BlockIO_NLPID, x_ds2), BLOCKIO_SIG, 0, 1, 2, 540, 0 },

  { 271, "nlpid/Guidance Systems/Path-following/Heading/psi_d^s eq/( y_d^s )^2",
    0, "", offsetof(BlockIO_NLPID, y_ds2), BLOCKIO_SIG, 0, 1, 2, 542, 0 },

  { 272,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s eq/( x_d^s )^2 + ( y_d^s )^2",
    0, "", offsetof(BlockIO_NLPID, x_ds2y_ds2), BLOCKIO_SIG, 0, 1, 2, 544, 0 },

  { 273, "nlpid/Guidance Systems/Path-following/Heading/psi_d^s eq/Divide", 0,
    "", offsetof(BlockIO_NLPID, Divide_h), BLOCKIO_SIG, 0, 1, 2, 546, 0 },

  { 274,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Delta^2",
    0, "", offsetof(BlockIO_NLPID, Delta2_b), BLOCKIO_SIG, 0, 1, 2, 548, 0 },

  { 275,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_n2_j), BLOCKIO_SIG, 21, 1, 2, 550, 0
  },

  { 276,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_a), BLOCKIO_SIG, 21, 1, 2, 552, 0 },

  { 277,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_p), BLOCKIO_SIG, 21, 1, 2, 554, 0 },

  { 278,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2^T/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_k), BLOCKIO_SIG, 22, 4, 2, 556,
    0 },

  { 279,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_lx), BLOCKIO_SIG, 23, 2, 2, 558, 0 },

  { 280,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_h), BLOCKIO_SIG, 23, 2, 2, 560, 0 },

  { 281,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq/Subtract1",
    0, "", offsetof(BlockIO_NLPID, Subtract1), BLOCKIO_SIG, 23, 2, 2, 562, 0 },

  { 282,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector2",
    0, "", offsetof(BlockIO_NLPID, MultiportSelector2), BLOCKIO_SIG, 21, 1, 2,
    564, 0 },

  { 283,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_bn), BLOCKIO_SIG, 21, 1, 2, 566, 0 },

  { 284,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_g), BLOCKIO_SIG, 21, 1, 2, 568, 0 },

  { 285,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_n2_f), BLOCKIO_SIG, 21, 1, 2, 570, 0
  },

  { 286,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Delta^2",
    0, "", offsetof(BlockIO_NLPID, Delta2_d), BLOCKIO_SIG, 0, 1, 2, 572, 0 },

  { 287,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_h), BLOCKIO_SIG, 21, 1, 2, 574, 0 },

  { 288,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/sqrt",
    0, "", offsetof(BlockIO_NLPID, sqrt_i), BLOCKIO_SIG, 21, 1, 2, 576, 0 },

  { 289,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_c), BLOCKIO_SIG, 21, 1, 2, 578, 0 },

  { 290,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_e), BLOCKIO_SIG, 21, 1, 2, 580, 0 },

  { 291,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_pj), BLOCKIO_SIG, 20, 2, 2, 582,
    0 },

  { 292,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_i), BLOCKIO_SIG, 20, 2, 2, 584, 0 },

  { 293,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_m), BLOCKIO_SIG, 23, 2, 2, 586, 0 },

  { 294,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_f1), BLOCKIO_SIG, 0, 1, 2, 588, 0 },

  { 295,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_cx), BLOCKIO_SIG, 0, 1, 2, 590, 0 },

  { 296,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_f), BLOCKIO_SIG, 21, 1, 2, 592, 0 },

  { 297,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPID, VectorConcatenate_m), BLOCKIO_SIG, 26, 3, 2,
    594, 0 },

  { 298, "nlpid/Control Systems/Nonlinear PID/v_d/Add", 0, "", offsetof
    (BlockIO_NLPID, Add_fj), BLOCKIO_SIG, 26, 3, 2, 596, 0 },

  { 299, "nlpid/Control Systems/Nonlinear PID/nu tilde/Product", 0, "", offsetof
    (BlockIO_NLPID, Product_a), BLOCKIO_SIG, 26, 3, 2, 598, 0 },

  { 300, "nlpid/Control Systems/Nonlinear PID/nu tilde/Subtract", 0, "",
    offsetof(BlockIO_NLPID, Subtract_c), BLOCKIO_SIG, 26, 3, 2, 600, 0 },

  { 301, "nlpid/Control Systems/Nonlinear PID/Control law/tau_PID/Product2", 0,
    "", offsetof(BlockIO_NLPID, Product2_j4), BLOCKIO_SIG, 26, 3, 2, 602, 0 },

  { 302, "nlpid/Control Systems/Nonlinear PID/Control law/tau_PID/Sum", 0, "",
    offsetof(BlockIO_NLPID, Sum_a0), BLOCKIO_SIG, 26, 3, 2, 604, 0 },

  { 303, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-X_u", 0,
    "", offsetof(BlockIO_NLPID, X_u), BLOCKIO_SIG, 0, 1, 2, 606, 0 },

  { 304, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_v", 0,
    "", offsetof(BlockIO_NLPID, Y_v), BLOCKIO_SIG, 0, 1, 2, 608, 0 },

  { 305, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_v", 0,
    "", offsetof(BlockIO_NLPID, N_v), BLOCKIO_SIG, 0, 1, 2, 610, 0 },

  { 306, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_vr", 0,
    "", offsetof(BlockIO_NLPID, Y_vr), BLOCKIO_SIG, 0, 1, 2, 612, 0 },

  { 307, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_r", 0,
    "", offsetof(BlockIO_NLPID, N_r), BLOCKIO_SIG, 0, 1, 2, 614, 0 },

  { 308,
    "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Linear Dampning matrix",
    0, "", offsetof(BlockIO_NLPID, LinearDampningmatrix), BLOCKIO_SIG, 36, 9, 2,
    616, 0 },

  { 309, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FL/Product1", 0,
    "", offsetof(BlockIO_NLPID, Product1_kq), BLOCKIO_SIG, 24, 3, 2, 618, 0 },

  { 310, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_11", 0, "",
    offsetof(BlockIO_NLPID, M_11), BLOCKIO_SIG, 0, 1, 2, 620, 0 },

  { 311, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_22", 0, "",
    offsetof(BlockIO_NLPID, M_22), BLOCKIO_SIG, 0, 1, 2, 622, 0 },

  { 312, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/m x_g", 0, "",
    offsetof(BlockIO_NLPID, mx_g), BLOCKIO_SIG, 0, 1, 2, 624, 0 },

  { 313, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_32", 0, "",
    offsetof(BlockIO_NLPID, M_32), BLOCKIO_SIG, 0, 1, 2, 626, 0 },

  { 314, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_23", 0, "",
    offsetof(BlockIO_NLPID, M_23), BLOCKIO_SIG, 0, 1, 2, 628, 0 },

  { 315, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_33", 0, "",
    offsetof(BlockIO_NLPID, M_33), BLOCKIO_SIG, 0, 1, 2, 630, 0 },

  { 316, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/M/3x3", 0, "",
    offsetof(BlockIO_NLPID, x3), BLOCKIO_SIG, 36, 9, 2, 632, 0 },

  { 317,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_NLPID, TrigonometricFunction1), BLOCKIO_SIG, 21, 1,
    2, 634, 0 },

  { 318,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_ga), BLOCKIO_SIG, 21, 1, 2, 636, 0 },

  { 319,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_n), BLOCKIO_SIG, 20, 2, 2, 638, 0 },

  { 320,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPID, TrigonometricFunction_n), BLOCKIO_SIG, 21, 1,
    2, 640, 0 },

  { 321,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2_c), BLOCKIO_SIG, 20, 2, 2, 642, 0 },

  { 322,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_NLPID, MatrixConcatenate), BLOCKIO_SIG, 22, 4, 2,
    644, 0 },

  { 323,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_i), BLOCKIO_SIG, 22, 4, 2, 646, 0 },

  { 324,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/f_q^T/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_iq), BLOCKIO_SIG, 20, 2, 2, 648,
    0 },

  { 325,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2_p), BLOCKIO_SIG, 21, 1, 2, 650, 0 },

  { 326,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_n), BLOCKIO_SIG, 35, 2, 2, 652,
    0 },

  { 327,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product3",
    0, "", offsetof(BlockIO_NLPID, Product3), BLOCKIO_SIG, 22, 4, 2, 654, 0 },

  { 328,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product4",
    0, "", offsetof(BlockIO_NLPID, Product4), BLOCKIO_SIG, 22, 4, 2, 656, 0 },

  { 329,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2",
    0, "", offsetof(BlockIO_NLPID, u_g), BLOCKIO_SIG, 22, 4, 2, 658, 0 },

  { 330,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Delta^2",
    0, "", offsetof(BlockIO_NLPID, Delta2_d4), BLOCKIO_SIG, 0, 1, 2, 660, 0 },

  { 331,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_n2_o), BLOCKIO_SIG, 21, 1, 2, 662, 0
  },

  { 332,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_d), BLOCKIO_SIG, 21, 1, 2, 664, 0 },

  { 333,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/( )^2",
    0, "", offsetof(BlockIO_NLPID, u_n), BLOCKIO_SIG, 21, 1, 2, 666, 0 },

  { 334,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_hf), BLOCKIO_SIG, 22, 4, 2, 668, 0 },

  { 335,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_c), BLOCKIO_SIG, 22, 4, 2, 670, 0 },

  { 336,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide1",
    0, "", offsetof(BlockIO_NLPID, Divide1), BLOCKIO_SIG, 22, 4, 2, 672, 0 },

  { 337,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_ju), BLOCKIO_SIG, 22, 4, 2, 674, 0 },

  { 338,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/psi_los^q^2^T/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_o), BLOCKIO_SIG, 22, 4, 2, 676,
    0 },

  { 339,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_g), BLOCKIO_SIG, 20, 2, 2, 678, 0 },

  { 340,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_d), BLOCKIO_SIG, 20, 2, 2, 680, 0 },

  { 341,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Add", 0,
    "", offsetof(BlockIO_NLPID, Add_ax), BLOCKIO_SIG, 20, 2, 2, 682, 0 },

  { 342,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_NLPID, MatrixConcatenate_j), BLOCKIO_SIG, 25, 6, 2,
    684, 0 },

  { 343,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_a5), BLOCKIO_SIG, 20, 2, 2, 686, 0 },

  { 344,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2",
    0, "", offsetof(BlockIO_NLPID, u_k), BLOCKIO_SIG, 20, 2, 2, 688, 0 },

  { 345,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Delta^2",
    0, "", offsetof(BlockIO_NLPID, Delta2_m), BLOCKIO_SIG, 0, 1, 2, 690, 0 },

  { 346,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_n2_b), BLOCKIO_SIG, 21, 1, 2, 692, 0
  },

  { 347,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_dw), BLOCKIO_SIG, 21, 1, 2, 694, 0 },

  { 348,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/( )^2",
    0, "", offsetof(BlockIO_NLPID, u_b), BLOCKIO_SIG, 21, 1, 2, 696, 0 },

  { 349,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_f), BLOCKIO_SIG, 20, 2, 2, 698, 0 },

  { 350,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_fo), BLOCKIO_SIG, 22, 4, 2, 700, 0 },

  { 351,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector3",
    0, "", offsetof(BlockIO_NLPID, MultiportSelector3), BLOCKIO_SIG, 20, 2, 2,
    702, 0 },

  { 352,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_g), BLOCKIO_SIG, 20, 2, 2, 704, 0 },

  { 353,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide1",
    0, "", offsetof(BlockIO_NLPID, Divide1_l), BLOCKIO_SIG, 20, 2, 2, 706, 0 },

  { 354,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_fn), BLOCKIO_SIG, 20, 2, 2, 708, 0 },

  { 355,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_ae), BLOCKIO_SIG, 20, 2, 2, 710, 0 },

  { 356,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_d4), BLOCKIO_SIG, 20, 2, 2, 712, 0 },

  { 357,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_n2_n), BLOCKIO_SIG, 21, 1, 2, 714, 0
  },

  { 358,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Delta^2",
    0, "", offsetof(BlockIO_NLPID, Delta2_a), BLOCKIO_SIG, 0, 1, 2, 716, 0 },

  { 359,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_c), BLOCKIO_SIG, 21, 1, 2, 718, 0 },

  { 360,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/^3//2",
    0, "", offsetof(BlockIO_NLPID, u2), BLOCKIO_SIG, 21, 1, 2, 720, 0 },

  { 361,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_j), BLOCKIO_SIG, 20, 2, 2, 722, 0 },

  { 362,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_lao), BLOCKIO_SIG, 20, 2, 2, 724, 0 },

  { 363,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_m), BLOCKIO_SIG, 20, 2, 2, 726,
    0 },

  { 364,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_e), BLOCKIO_SIG, 20, 2, 2, 728, 0 },

  { 365,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_gv), BLOCKIO_SIG, 20, 2, 2, 730, 0 },

  { 366,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_mb), BLOCKIO_SIG, 20, 2, 2, 732, 0 },

  { 367,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_mp), BLOCKIO_SIG, 20, 2, 2, 734, 0 },

  { 368,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_a), BLOCKIO_SIG, 20, 2, 2, 736, 0 },

  { 369,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Add", 0,
    "", offsetof(BlockIO_NLPID, Add_b), BLOCKIO_SIG, 20, 2, 2, 738, 0 },

  { 370,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_NLPID, MatrixConcatenate_n), BLOCKIO_SIG, 25, 6, 2,
    740, 0 },

  { 371, "nlpid/Control Systems/Nonlinear PID/a_d/v_d^q/Add", 0, "", offsetof
    (BlockIO_NLPID, Add_ac), BLOCKIO_SIG, 25, 6, 2, 742, 0 },

  { 372, "nlpid/Control Systems/Nonlinear PID/Update laws/omega_q", 0, "",
    offsetof(BlockIO_NLPID, omega_q), BLOCKIO_SIG, 23, 2, 2, 744, 0 },

  { 373, "nlpid/Control Systems/Nonlinear PID/Update laws/Add", 0, "", offsetof
    (BlockIO_NLPID, Add_ic), BLOCKIO_SIG, 23, 2, 2, 746, 0 },

  { 374, "nlpid/Control Systems/Nonlinear PID/a_d/Product", 0, "", offsetof
    (BlockIO_NLPID, Product_gq), BLOCKIO_SIG, 24, 3, 2, 748, 0 },

  { 375,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_NLPID, TrigonometricFunction1_k), BLOCKIO_SIG, 21, 1,
    2, 750, 0 },

  { 376,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_l1), BLOCKIO_SIG, 21, 1, 2, 752, 0 },

  { 377,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_i1), BLOCKIO_SIG, 21, 1, 2, 754, 0 },

  { 378,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPID, TrigonometricFunction_p), BLOCKIO_SIG, 21, 1,
    2, 756, 0 },

  { 379,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2_ok), BLOCKIO_SIG, 21, 1, 2, 758, 0 },

  { 380,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_fr), BLOCKIO_SIG, 23, 2, 2, 760, 0 },

  { 381,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_h), BLOCKIO_SIG, 0, 1, 2, 762, 0 },

  { 382,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_os), BLOCKIO_SIG, 0, 1, 2, 764, 0 },

  { 383,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPID, VectorConcatenate_l), BLOCKIO_SIG, 24, 3, 2,
    766, 0 },

  { 384,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Product",
    0, "", offsetof(BlockIO_NLPID, Product_jv), BLOCKIO_SIG, 23, 2, 2, 768, 0 },

  { 385,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2_a), BLOCKIO_SIG, 0, 1, 2, 770, 0 },

  { 386,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/cos(s)",
    0, "", offsetof(BlockIO_NLPID, coss_pz), BLOCKIO_SIG, 0, 1, 2, 772, 0 },

  { 387,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_gs), BLOCKIO_SIG, 0, 1, 2, 774,
    0 },

  { 388,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_pa), BLOCKIO_SIG, 0, 1, 2, 776, 0 },

  { 389,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain", 0,
    "", offsetof(BlockIO_NLPID, Gain_a), BLOCKIO_SIG, 0, 1, 2, 778, 0 },

  { 390,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/sin(s)",
    0, "", offsetof(BlockIO_NLPID, sins_p), BLOCKIO_SIG, 0, 1, 2, 780, 0 },

  { 391,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_jk), BLOCKIO_SIG, 0, 1, 2, 782, 0 },

  { 392,
    "nlpid/Guidance Systems/Path-following/Path/Ellipse path/p_d^s^2 eq/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_c), BLOCKIO_SIG, 0, 1, 2, 784, 0 },

  { 393,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_fr), BLOCKIO_SIG, 0, 1, 2, 786, 0 },

  { 394,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_if), BLOCKIO_SIG, 23, 2, 2, 788, 0 },

  { 395,
    "nlpid/Guidance Systems/Path-following/Path/Path Switch workaround/p_d^s^3 selcetor/Add",
    0, "", offsetof(BlockIO_NLPID, Add_ef), BLOCKIO_SIG, 23, 2, 2, 790, 0 },

  { 396,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/x_d^s + y_d^s^3",
    0, "", offsetof(BlockIO_NLPID, x_dsy_ds3), BLOCKIO_SIG, 0, 1, 2, 792, 0 },

  { 397,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/x_d^s^3 + y_d^s",
    0, "", offsetof(BlockIO_NLPID, x_ds3y_ds), BLOCKIO_SIG, 0, 1, 2, 794, 0 },

  { 398,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/( x_d^s + y_d^s^3  ) - ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_NLPID, x_dsy_ds3x_ds3y_ds), BLOCKIO_SIG, 0, 1, 2,
    796, 0 },

  { 399, "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_hm), BLOCKIO_SIG, 0, 1, 2, 798, 0 },

  { 400,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/x_d^s + x_d^s^2",
    0, "", offsetof(BlockIO_NLPID, x_dsx_ds2), BLOCKIO_SIG, 0, 1, 2, 800, 0 },

  { 401,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/y_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_NLPID, y_dsy_ds2), BLOCKIO_SIG, 0, 1, 2, 802, 0 },

  { 402,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/( x_d^s + x_d^s^2 ) + ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_NLPID, x_dsx_ds2x_ds3y_ds), BLOCKIO_SIG, 0, 1, 2,
    804, 0 },

  { 403, "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/+ 2", 0, "",
    offsetof(BlockIO_NLPID, u_d), BLOCKIO_SIG, 0, 1, 2, 806, 0 },

  { 404, "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2_g), BLOCKIO_SIG, 0, 1, 2, 808, 0 },

  { 405, "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_jg), BLOCKIO_SIG, 0, 1, 2, 810, 0 },

  { 406,
    "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2",
    0, "", offsetof(BlockIO_NLPID, x_ds2y_ds22), BLOCKIO_SIG, 0, 1, 2, 812, 0 },

  { 407, "nlpid/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Divide", 0,
    "", offsetof(BlockIO_NLPID, Divide_ph), BLOCKIO_SIG, 0, 1, 2, 814, 0 },

  { 408,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/(epsilon_n^s)^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_ns2), BLOCKIO_SIG, 21, 1, 2, 816, 0 },

  { 409,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_nc), BLOCKIO_SIG, 21, 1, 2, 818, 0 },

  { 410,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2",
    0, "", offsetof(BlockIO_NLPID, u_f), BLOCKIO_SIG, 21, 1, 2, 820, 0 },

  { 411,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Delta^2",
    0, "", offsetof(BlockIO_NLPID, Delta2_p), BLOCKIO_SIG, 0, 1, 2, 822, 0 },

  { 412,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_n2_ji), BLOCKIO_SIG, 21, 1, 2, 824, 0
  },

  { 413,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_di), BLOCKIO_SIG, 21, 1, 2, 826, 0 },

  { 414,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/( )^2",
    0, "", offsetof(BlockIO_NLPID, u_bl), BLOCKIO_SIG, 21, 1, 2, 828, 0 },

  { 415,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_cz), BLOCKIO_SIG, 21, 1, 2, 830, 0 },

  { 416,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_ox), BLOCKIO_SIG, 22, 4, 2, 832,
    0 },

  { 417,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_fb), BLOCKIO_SIG, 22, 4, 2, 834, 0 },

  { 418,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_au), BLOCKIO_SIG, 22, 4, 2, 836, 0 },

  { 419,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_l), BLOCKIO_SIG, 23, 2, 2, 838, 0 },

  { 420,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2_h), BLOCKIO_SIG, 23, 2, 2, 840, 0 },

  { 421,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2",
    0, "", offsetof(BlockIO_NLPID, u_j), BLOCKIO_SIG, 23, 2, 2, 842, 0 },

  { 422,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product3",
    0, "", offsetof(BlockIO_NLPID, Product3_f), BLOCKIO_SIG, 23, 2, 2, 844, 0 },

  { 423,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_o), BLOCKIO_SIG, 23, 2, 2, 846, 0 },

  { 424,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_lk), BLOCKIO_SIG, 23, 2, 2, 848, 0 },

  { 425,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector4",
    0, "", offsetof(BlockIO_NLPID, MultiportSelector4), BLOCKIO_SIG, 21, 1, 2,
    850, 0 },

  { 426,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_jb), BLOCKIO_SIG, 21, 1, 2, 852, 0 },

  { 427,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide1",
    0, "", offsetof(BlockIO_NLPID, Divide1_e), BLOCKIO_SIG, 21, 1, 2, 854, 0 },

  { 428,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_hf), BLOCKIO_SIG, 21, 1, 2, 856, 0 },

  { 429,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_av), BLOCKIO_SIG, 21, 1, 2, 858, 0 },

  { 430,
    "nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_f), BLOCKIO_SIG, 20, 2, 2, 860,
    0 },

  { 431,
    "nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Product1", 0,
    "", offsetof(BlockIO_NLPID, Product1_cs), BLOCKIO_SIG, 0, 1, 2, 862, 0 },

  { 432,
    "nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/|p_d^s|^3",
    0, "", offsetof(BlockIO_NLPID, p_ds3), BLOCKIO_SIG, 0, 1, 2, 864, 0 },

  { 433, "nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_m), BLOCKIO_SIG, 0, 1, 2, 866, 0 },

  { 434,
    "nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Product", 0,
    "", offsetof(BlockIO_NLPID, Product_nw), BLOCKIO_SIG, 0, 1, 2, 868, 0 },

  { 435, "nlpid/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_jk), BLOCKIO_SIG, 0, 1, 2, 870, 0 },

  { 436,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_n2_bc), BLOCKIO_SIG, 21, 1, 2, 872, 0
  },

  { 437,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Delta^2",
    0, "", offsetof(BlockIO_NLPID, Delta2_c), BLOCKIO_SIG, 0, 1, 2, 874, 0 },

  { 438,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_n), BLOCKIO_SIG, 21, 1, 2, 876, 0 },

  { 439,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_atw), BLOCKIO_SIG, 21, 1, 2, 878,
    0 },

  { 440,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_ey), BLOCKIO_SIG, 21, 1, 2, 880, 0 },

  { 441,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_hq), BLOCKIO_SIG, 21, 1, 2, 882, 0 },

  { 442,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2_ha), BLOCKIO_SIG, 21, 1, 2, 884, 0 },

  { 443,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/^3//2",
    0, "", offsetof(BlockIO_NLPID, u2_f), BLOCKIO_SIG, 21, 1, 2, 886, 0 },

  { 444,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide1",
    0, "", offsetof(BlockIO_NLPID, Divide1_k), BLOCKIO_SIG, 21, 1, 2, 888, 0 },

  { 445,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product3",
    0, "", offsetof(BlockIO_NLPID, Product3_n), BLOCKIO_SIG, 21, 1, 2, 890, 0 },

  { 446,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_p), BLOCKIO_SIG, 0, 1, 2, 892, 0 },

  { 447,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_g4), BLOCKIO_SIG, 20, 2, 2, 894,
    0 },

  { 448,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide2",
    0, "", offsetof(BlockIO_NLPID, Divide2), BLOCKIO_SIG, 20, 2, 2, 896, 0 },

  { 449,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_j), BLOCKIO_SIG, 20, 2, 2, 898,
    0 },

  { 450,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product2",
    0, "", offsetof(BlockIO_NLPID, Product2_aa), BLOCKIO_SIG, 20, 2, 2, 900, 0 },

  { 451,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Math Function",
    0, "", offsetof(BlockIO_NLPID, MathFunction_gc), BLOCKIO_SIG, 0, 1, 2, 902,
    0 },

  { 452,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide1",
    0, "", offsetof(BlockIO_NLPID, Divide1_m), BLOCKIO_SIG, 20, 2, 2, 904, 0 },

  { 453,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract1",
    0, "", offsetof(BlockIO_NLPID, Subtract1_f), BLOCKIO_SIG, 20, 2, 2, 906, 0 },

  { 454,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_c), BLOCKIO_SIG, 0, 1, 2, 908, 0 },

  { 455,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract",
    0, "", offsetof(BlockIO_NLPID, Subtract_gr), BLOCKIO_SIG, 0, 1, 2, 910, 0 },

  { 456,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_ou), BLOCKIO_SIG, 21, 1, 2, 912, 0 },

  { 457,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Product1",
    0, "", offsetof(BlockIO_NLPID, Product1_gt), BLOCKIO_SIG, 21, 1, 2, 914, 0 },

  { 458,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPID, VectorConcatenate_d), BLOCKIO_SIG, 26, 3, 2,
    916, 0 },

  { 459, "nlpid/Control Systems/Nonlinear PID/a_d/v_d^s/Add1", 0, "", offsetof
    (BlockIO_NLPID, Add1_b), BLOCKIO_SIG, 26, 3, 2, 918, 0 },

  { 460, "nlpid/Control Systems/Nonlinear PID/a_d/Product1", 0, "", offsetof
    (BlockIO_NLPID, Product1_km), BLOCKIO_SIG, 24, 3, 2, 920, 0 },

  { 461,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPID, TrigonometricFunction_m), BLOCKIO_SIG, 21, 1,
    2, 922, 0 },

  { 462,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_NLPID, TrigonometricFunction1_j), BLOCKIO_SIG, 21, 1,
    2, 924, 0 },

  { 463, "nlpid/Guidance Systems/Path-following/Speed assigment/Derivative", 0,
    "", offsetof(BlockIO_NLPID, Derivative_d), BLOCKIO_SIG, 0, 1, 2, 926, 0 },

  { 464,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_ji), BLOCKIO_SIG, 23, 2, 2, 928, 0 },

  { 465,
    "nlpid/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPID, VectorConcatenate_p), BLOCKIO_SIG, 24, 3, 2,
    930, 0 },

  { 466,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPID, epsilon_n2_nl), BLOCKIO_SIG, 21, 1, 2, 932, 0
  },

  { 467,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Delta^2",
    0, "", offsetof(BlockIO_NLPID, Delta2_f), BLOCKIO_SIG, 0, 1, 2, 934, 0 },

  { 468,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Add",
    0, "", offsetof(BlockIO_NLPID, Add_fq), BLOCKIO_SIG, 21, 1, 2, 936, 0 },

  { 469,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/sqrt",
    0, "", offsetof(BlockIO_NLPID, sqrt_a), BLOCKIO_SIG, 21, 1, 2, 938, 0 },

  { 470,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_d), BLOCKIO_SIG, 21, 1, 2, 940, 0 },

  { 471, "nlpid/Guidance Systems/Path-following/Speed assigment/v_s^t eq/Divide",
    0, "", offsetof(BlockIO_NLPID, Divide_g), BLOCKIO_SIG, 0, 1, 2, 942, 0 },

  { 472,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Product",
    0, "", offsetof(BlockIO_NLPID, Product_h4), BLOCKIO_SIG, 21, 1, 2, 944, 0 },

  { 473,
    "nlpid/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPID, VectorConcatenate_dx), BLOCKIO_SIG, 26, 3, 2,
    946, 0 },

  { 474, "nlpid/Control Systems/Nonlinear PID/a_d/v_d^t/Add", 0, "", offsetof
    (BlockIO_NLPID, Add_em), BLOCKIO_SIG, 26, 3, 2, 948, 0 },

  { 475, "nlpid/Control Systems/Nonlinear PID/a_d/Sum", 0, "", offsetof
    (BlockIO_NLPID, Sum_b), BLOCKIO_SIG, 26, 3, 2, 950, 0 },

  { 476, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/Product", 0, "",
    offsetof(BlockIO_NLPID, Product_l0), BLOCKIO_SIG, 26, 3, 2, 952, 0 },

  { 477, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S12", 0, "",
    offsetof(BlockIO_NLPID, S12), BLOCKIO_SIG, 0, 1, 2, 954, 0 },

  { 478, "nlpid/Control Systems/Nonlinear PID/Control law/S(r)/S(r)", 0, "",
    offsetof(BlockIO_NLPID, Sr), BLOCKIO_SIG, 36, 9, 2, 956, 0 },

  { 479, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/Product1", 0,
    "", offsetof(BlockIO_NLPID, Product1_m), BLOCKIO_SIG, 26, 3, 2, 958, 0 },

  { 480, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/Subtract", 0,
    "", offsetof(BlockIO_NLPID, Subtract_p), BLOCKIO_SIG, 26, 3, 2, 960, 0 },

  { 481, "nlpid/Control Systems/Nonlinear PID/Control law/tau_FF/Gain", 0, "",
    offsetof(BlockIO_NLPID, Gain_mx), BLOCKIO_SIG, 26, 3, 2, 962, 0 },

  { 482, "nlpid/Control Systems/Nonlinear PID/Control law/Sum", 0, "", offsetof
    (BlockIO_NLPID, Sum_hl), BLOCKIO_SIG, 26, 3, 2, 964, 0 },

  { 483,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_NLPID, Product_bs), BLOCKIO_SIG, 37, 5, 2, 966, 0 },

  { 484,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone_p), BLOCKIO_SIG, 21, 1, 2, 968, 0 },

  { 485,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_NLPID, f_10_j), BLOCKIO_SIG, 21, 1, 2, 970, 0 },

  { 486,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_NLPID, f_10_e), BLOCKIO_SIG, 21, 1, 2, 972, 0 },

  { 487,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch_f), BLOCKIO_SIG, 21, 1, 2,
    974, 0 },

  { 488,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone_c), BLOCKIO_SIG, 21, 1, 2, 976, 0 },

  { 489,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_NLPID, f_20_p), BLOCKIO_SIG, 21, 1, 2, 978, 0 },

  { 490,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_NLPID, f_20_l), BLOCKIO_SIG, 21, 1, 2, 980, 0 },

  { 491,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch_fh), BLOCKIO_SIG, 21, 1, 2,
    982, 0 },

  { 492,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone_h), BLOCKIO_SIG, 21, 1, 2, 984, 0 },

  { 493,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_NLPID, f_30_d), BLOCKIO_SIG, 21, 1, 2, 986, 0 },

  { 494,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_NLPID, f_30_h), BLOCKIO_SIG, 21, 1, 2, 988, 0 },

  { 495,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch_l), BLOCKIO_SIG, 21, 1, 2,
    990, 0 },

  { 496,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone_pp), BLOCKIO_SIG, 21, 1, 2, 992, 0 },

  { 497,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_NLPID, f_40_fz), BLOCKIO_SIG, 21, 1, 2, 994, 0 },

  { 498,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_NLPID, f_40_n), BLOCKIO_SIG, 21, 1, 2, 996, 0 },

  { 499,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch_e), BLOCKIO_SIG, 21, 1, 2,
    998, 0 },

  { 500,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone",
    0, "", offsetof(BlockIO_NLPID, DeadZone_pa), BLOCKIO_SIG, 21, 1, 2, 1000, 0
  },

  { 501,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_NLPID, f_50_n), BLOCKIO_SIG, 21, 1, 2, 1002, 0 },

  { 502,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_NLPID, f_50_g), BLOCKIO_SIG, 21, 1, 2, 1004, 0 },

  { 503,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_NLPID, MultiportSwitch_lr), BLOCKIO_SIG, 21, 1, 2,
    1006, 0 },

  { 504, "nlpid/Control Systems/Thruster setting Switch", 0, "", offsetof
    (BlockIO_NLPID, ThrustersettingSwitch), BLOCKIO_SIG, 27, 7, 2, 1008, 0 },

  { 505, "nlpid/Control Systems/Saturation", 0, "", offsetof(BlockIO_NLPID,
    Saturation_f), BLOCKIO_SIG, 27, 7, 2, 1010, 0 },

  { 506,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1",
    0, "", offsetof(BlockIO_NLPID, l_x1_e), BLOCKIO_SIG, 0, 1, 2, 1012, 0 },

  { 507,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2",
    0, "", offsetof(BlockIO_NLPID, l_y2_g), BLOCKIO_SIG, 0, 1, 2, 1014, 0 },

  { 508,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2",
    0, "", offsetof(BlockIO_NLPID, l_x2_a), BLOCKIO_SIG, 0, 1, 2, 1016, 0 },

  { 509,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/T_e/3x5",
    0, "", offsetof(BlockIO_NLPID, x5_a), BLOCKIO_SIG, 31, 15, 2, 1018, 0 },

  { 510,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1",
    0, "", offsetof(BlockIO_NLPID, u_1tof_1), BLOCKIO_SIG, 0, 1, 2, 1020, 0 },

  { 511,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2",
    0, "", offsetof(BlockIO_NLPID, u_2tof_2), BLOCKIO_SIG, 0, 1, 2, 1022, 0 },

  { 512,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3",
    0, "", offsetof(BlockIO_NLPID, u_3tof_3), BLOCKIO_SIG, 0, 1, 2, 1024, 0 },

  { 513,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4",
    0, "", offsetof(BlockIO_NLPID, u_4tof_4), BLOCKIO_SIG, 0, 1, 2, 1026, 0 },

  { 514,
    "nlpid/Control Systems/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5",
    0, "", offsetof(BlockIO_NLPID, u_5tof_5), BLOCKIO_SIG, 0, 1, 2, 1028, 0 },

  { 515,
    "nlpid/Control Systems/PS3 u input control/Subsystem/f_act to tau/Product",
    0, "", offsetof(BlockIO_NLPID, Product_fy), BLOCKIO_SIG, 24, 3, 2, 1030, 0 },

  { 516, "nlpid/Control Systems/tau Switch", 0, "", offsetof(BlockIO_NLPID,
    tauSwitch), BLOCKIO_SIG, 26, 3, 2, 1032, 0 },

  { 517, "nlpid/Control Systems/Nonlinear PID/Gamma_q/2x2", 0, "", offsetof
    (BlockIO_NLPID, x2), BLOCKIO_SIG, 22, 4, 2, 1034, 0 },

  { 518, "nlpid/Control Systems/Nonlinear PID/Integral action state/Product", 0,
    "", offsetof(BlockIO_NLPID, Product_cb), BLOCKIO_SIG, 26, 3, 2, 1036, 0 },

  { 519,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/Matrix Concatenate",
    0, "", offsetof(BlockIO_NLPID, MatrixConcatenate_k), BLOCKIO_SIG, 25, 6, 2,
    1038, 0 },

  { 520,
    "nlpid/Control Systems/Nonlinear PID/Update laws/Transpose/Math Function", 0,
    "", offsetof(BlockIO_NLPID, MathFunction_an), BLOCKIO_SIG, 40, 6, 2, 1040, 0
  },

  { 521, "nlpid/Control Systems/Nonlinear PID/Update laws/Product2", 0, "",
    offsetof(BlockIO_NLPID, Product2_k), BLOCKIO_SIG, 23, 2, 2, 1042, 0 },

  { 522, "nlpid/Control Systems/Nonlinear PID/Update laws/Product3", 0, "",
    offsetof(BlockIO_NLPID, Product3_g), BLOCKIO_SIG, 23, 2, 2, 1044, 0 },

  { 523, "nlpid/Control Systems/Nonlinear PID/Update laws/Subtract", 0, "",
    offsetof(BlockIO_NLPID, Subtract_o2), BLOCKIO_SIG, 23, 2, 2, 1046, 0 },

  { 524, "nlpid/Control Systems/Nonlinear PID/Update laws/Product1", 0, "",
    offsetof(BlockIO_NLPID, Product1_as), BLOCKIO_SIG, 23, 2, 2, 1048, 0 },

  { 525, "nlpid/Control Systems/Nonlinear PID/Update laws/dot omega_q", 0, "",
    offsetof(BlockIO_NLPID, dotomega_q), BLOCKIO_SIG, 23, 2, 2, 1050, 0 },

  { 526,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/Vector Concatenate1",
    0, "", offsetof(BlockIO_NLPID, VectorConcatenate1), BLOCKIO_SIG, 26, 3, 2,
    1052, 0 },

  { 527, "nlpid/HMI/SIT zAI0", 0, "", offsetof(BlockIO_NLPID, SITzAI0),
    BLOCKIO_SIG, 0, 1, 2, 1054, 0 },

  { 528, "nlpid/HMI/Battery Bow Thruster", 0, "", offsetof(BlockIO_NLPID,
    BatteryBowThruster), BLOCKIO_SIG, 0, 1, 2, 1056, 0 },

  { 529, "nlpid/HMI/SIT zAI1", 0, "", offsetof(BlockIO_NLPID, SITzAI1),
    BLOCKIO_SIG, 0, 1, 2, 1058, 0 },

  { 530, "nlpid/HMI/Battery Servo", 0, "", offsetof(BlockIO_NLPID, BatteryServo),
    BLOCKIO_SIG, 0, 1, 2, 1060, 0 },

  { 531, "nlpid/HMI/SIT zAI2", 0, "", offsetof(BlockIO_NLPID, SITzAI2),
    BLOCKIO_SIG, 0, 1, 2, 1062, 0 },

  { 532, "nlpid/HMI/Battery Main", 0, "", offsetof(BlockIO_NLPID, BatteryMain),
    BLOCKIO_SIG, 0, 1, 2, 1064, 0 },

  { 533, "nlpid/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS", 0, "", offsetof
    (BlockIO_NLPID, QTMIn1FPS), BLOCKIO_SIG, 21, 1, 2, 1066, 0 },

  { 534, "nlpid/Plants/saturation/Saturation", 0, "", offsetof(BlockIO_NLPID,
    Saturation_f5), BLOCKIO_SIG, 21, 1, 2, 1068, 0 },

  { 535, "nlpid/Plants/saturation/Saturation1", 0, "", offsetof(BlockIO_NLPID,
    Saturation1), BLOCKIO_SIG, 21, 1, 2, 1070, 0 },

  { 536, "nlpid/Plants/saturation/Saturation2", 0, "", offsetof(BlockIO_NLPID,
    Saturation2), BLOCKIO_SIG, 21, 1, 2, 1072, 0 },

  { 537, "nlpid/Plants/saturation/plant tau_surge", 0, "", offsetof
    (BlockIO_NLPID, planttau_surge), BLOCKIO_SIG, 21, 1, 2, 1074, 0 },

  { 538, "nlpid/Plants/saturation/plant tau_sway", 0, "", offsetof(BlockIO_NLPID,
    planttau_sway), BLOCKIO_SIG, 21, 1, 2, 1076, 0 },

  { 539, "nlpid/Plants/saturation/plant tau_yaw", 0, "", offsetof(BlockIO_NLPID,
    planttau_yaw), BLOCKIO_SIG, 21, 1, 2, 1078, 0 },

  { 540, "nlpid/Plants/plant u_1", 0, "", offsetof(BlockIO_NLPID, plantu_1),
    BLOCKIO_SIG, 0, 1, 2, 1080, 0 },

  { 541, "nlpid/Plants/plant u_2", 0, "", offsetof(BlockIO_NLPID, plantu_2),
    BLOCKIO_SIG, 0, 1, 2, 1082, 0 },

  { 542, "nlpid/Plants/plant u_3", 0, "", offsetof(BlockIO_NLPID, plantu_3),
    BLOCKIO_SIG, 0, 1, 2, 1084, 0 },

  { 543, "nlpid/Plants/plant u_4", 0, "", offsetof(BlockIO_NLPID, plantu_4),
    BLOCKIO_SIG, 0, 1, 2, 1086, 0 },

  { 544, "nlpid/Plants/plant u_5", 0, "", offsetof(BlockIO_NLPID, plantu_5),
    BLOCKIO_SIG, 0, 1, 2, 1088, 0 },

  { 545, "nlpid/Plants/plant BT power", 0, "", offsetof(BlockIO_NLPID,
    plantBTpower), BLOCKIO_SIG, 0, 1, 2, 1090, 0 },

  { 546, "nlpid/Plants/plant VSP speed", 0, "", offsetof(BlockIO_NLPID,
    plantVSPspeed), BLOCKIO_SIG, 0, 1, 2, 1092, 0 },

  { 547, "nlpid/eta_psi", 0, "", offsetof(BlockIO_NLPID, eta_psi), BLOCKIO_SIG,
    0, 1, 2, 1094, 0 },

  { 548, "nlpid/eta_psid", 0, "", offsetof(BlockIO_NLPID, eta_psid), BLOCKIO_SIG,
    0, 1, 2, 1096, 0 },

  { 549, "nlpid/eta_x", 0, "", offsetof(BlockIO_NLPID, eta_x), BLOCKIO_SIG, 0, 1,
    2, 1098, 0 },

  { 550, "nlpid/eta_xd", 0, "", offsetof(BlockIO_NLPID, eta_xd), BLOCKIO_SIG, 0,
    1, 2, 1100, 0 },

  { 551, "nlpid/eta_y", 0, "", offsetof(BlockIO_NLPID, eta_y), BLOCKIO_SIG, 0, 1,
    2, 1102, 0 },

  { 552, "nlpid/eta_yd", 0, "", offsetof(BlockIO_NLPID, eta_yd), BLOCKIO_SIG, 0,
    1, 2, 1104, 0 },

  { 553, "nlpid/psi_los", 0, "", offsetof(BlockIO_NLPID, psi_los_l), BLOCKIO_SIG,
    0, 1, 2, 1106, 0 },

  { 554, "nlpid/psi_plot", 0, "", offsetof(BlockIO_NLPID, psi_plot), BLOCKIO_SIG,
    24, 3, 2, 1108, 0 },

  { 555, "nlpid/q_x", 0, "", offsetof(BlockIO_NLPID, q_x_f), BLOCKIO_SIG, 0, 1,
    2, 1110, 0 },

  { 556, "nlpid/q_y", 0, "", offsetof(BlockIO_NLPID, q_y_j), BLOCKIO_SIG, 0, 1,
    2, 1112, 0 },

  { 557, "nlpid/x_plot", 0, "", offsetof(BlockIO_NLPID, x_plot), BLOCKIO_SIG, 24,
    3, 2, 1114, 0 },

  { 558, "nlpid/y_plot", 0, "", offsetof(BlockIO_NLPID, y_plot), BLOCKIO_SIG, 24,
    3, 2, 1116, 0 },

  { 559, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r", 0, "",
    offsetof(BlockIO_NLPID, N_r_l), BLOCKIO_SIG, 0, 1, 2, 1118, 0 },

  { 560, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v", 0, "",
    offsetof(BlockIO_NLPID, N_v_g), BLOCKIO_SIG, 0, 1, 2, 1120, 0 },

  { 561, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u", 0, "",
    offsetof(BlockIO_NLPID, X_u_k), BLOCKIO_SIG, 0, 1, 2, 1122, 0 },

  { 562, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v", 0, "",
    offsetof(BlockIO_NLPID, Y_v_h), BLOCKIO_SIG, 0, 1, 2, 1124, 0 },

  { 563, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr", 0, "",
    offsetof(BlockIO_NLPID, Y_vr_i), BLOCKIO_SIG, 0, 1, 2, 1126, 0 },

  { 564,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Linear Dampning matrix",
    0, "", offsetof(BlockIO_NLPID, LinearDampningmatrix_f), BLOCKIO_SIG, 36, 9,
    2, 1128, 0 },

  { 565,
    "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0", 0,
    "", offsetof(BlockIO_NLPID, psi_0), BLOCKIO_SIG, 0, 1, 2, 1130, 0 },

  { 566, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0",
    0, "", offsetof(BlockIO_NLPID, x_0), BLOCKIO_SIG, 0, 1, 2, 1132, 0 },

  { 567, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0",
    0, "", offsetof(BlockIO_NLPID, y_0), BLOCKIO_SIG, 0, 1, 2, 1134, 0 },

  { 568, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0",
    0, "", offsetof(BlockIO_NLPID, r_0), BLOCKIO_SIG, 0, 1, 2, 1136, 0 },

  { 569, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0",
    0, "", offsetof(BlockIO_NLPID, u_0), BLOCKIO_SIG, 0, 1, 2, 1138, 0 },

  { 570, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0",
    0, "", offsetof(BlockIO_NLPID, v_0), BLOCKIO_SIG, 0, 1, 2, 1140, 0 },

  { 571, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Integrator", 0,
    "", offsetof(BlockIO_NLPID, Integrator_m), BLOCKIO_SIG, 24, 3, 2, 1142, 0 },

  { 572, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Integrator1", 0,
    "", offsetof(BlockIO_NLPID, Integrator1_m), BLOCKIO_SIG, 24, 3, 2, 1144, 0 },

  { 573, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_11", 0,
    "", offsetof(BlockIO_NLPID, M_11_c), BLOCKIO_SIG, 0, 1, 2, 1146, 0 },

  { 574, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_22", 0,
    "", offsetof(BlockIO_NLPID, M_22_k), BLOCKIO_SIG, 0, 1, 2, 1148, 0 },

  { 575, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m x_g", 0,
    "", offsetof(BlockIO_NLPID, mx_g_c), BLOCKIO_SIG, 0, 1, 2, 1150, 0 },

  { 576, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_32", 0,
    "", offsetof(BlockIO_NLPID, M_32_b), BLOCKIO_SIG, 0, 1, 2, 1152, 0 },

  { 577, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_23", 0,
    "", offsetof(BlockIO_NLPID, M_23_f), BLOCKIO_SIG, 0, 1, 2, 1154, 0 },

  { 578, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_33", 0,
    "", offsetof(BlockIO_NLPID, M_33_e), BLOCKIO_SIG, 0, 1, 2, 1156, 0 },

  { 579, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M", 0, "",
    offsetof(BlockIO_NLPID, M), BLOCKIO_SIG, 36, 9, 2, 1158, 0 },

  { 580, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Inverse", 0,
    "", offsetof(BlockIO_NLPID, Inverse), BLOCKIO_SIG, 36, 9, 2, 1160, 0 },

  { 581, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Product1", 0, "",
    offsetof(BlockIO_NLPID, Product1_o4), BLOCKIO_SIG, 24, 3, 2, 1162, 0 },

  { 582, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R11", 0,
    "", offsetof(BlockIO_NLPID, R11_m), BLOCKIO_SIG, 0, 1, 2, 1164, 0 },

  { 583, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R21", 0,
    "", offsetof(BlockIO_NLPID, R21_h), BLOCKIO_SIG, 0, 1, 2, 1166, 0 },

  { 584, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R12", 0,
    "", offsetof(BlockIO_NLPID, R12_d), BLOCKIO_SIG, 0, 1, 2, 1168, 0 },

  { 585, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R22", 0,
    "", offsetof(BlockIO_NLPID, R22_le), BLOCKIO_SIG, 0, 1, 2, 1170, 0 },

  { 586, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R(psi)", 0,
    "", offsetof(BlockIO_NLPID, Rpsi_c), BLOCKIO_SIG, 36, 9, 2, 1172, 0 },

  { 587, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Product3", 0, "",
    offsetof(BlockIO_NLPID, Product3_fn), BLOCKIO_SIG, 24, 3, 2, 1174, 0 },

  { 588, "nlpid/Plants/Linear Simulator/eta_surge_hil", 0, "", offsetof
    (BlockIO_NLPID, eta_surge_hil), BLOCKIO_SIG, 0, 1, 2, 1176, 0 },

  { 589, "nlpid/Plants/Linear Simulator/eta_sway_hil", 0, "", offsetof
    (BlockIO_NLPID, eta_sway_hil), BLOCKIO_SIG, 0, 1, 2, 1178, 0 },

  { 590, "nlpid/Plants/Linear Simulator/eta_yaw_hil", 0, "", offsetof
    (BlockIO_NLPID, eta_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 1180, 0 },

  { 591, "nlpid/Plants/Linear Simulator/etadot_surge_hil", 0, "", offsetof
    (BlockIO_NLPID, etadot_surge_hil), BLOCKIO_SIG, 0, 1, 2, 1182, 0 },

  { 592, "nlpid/Plants/Linear Simulator/etadot_sway_hil", 0, "", offsetof
    (BlockIO_NLPID, etadot_sway_hil), BLOCKIO_SIG, 0, 1, 2, 1184, 0 },

  { 593, "nlpid/Plants/Linear Simulator/etadot_yaw_hil", 0, "", offsetof
    (BlockIO_NLPID, etadot_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 1186, 0 },

  { 594, "nlpid/Plants/Linear Simulator/nu_surge_hil", 0, "", offsetof
    (BlockIO_NLPID, nu_surge_hil), BLOCKIO_SIG, 0, 1, 2, 1188, 0 },

  { 595, "nlpid/Plants/Linear Simulator/nu_sway_hil", 0, "", offsetof
    (BlockIO_NLPID, nu_sway_hil), BLOCKIO_SIG, 0, 1, 2, 1190, 0 },

  { 596, "nlpid/Plants/Linear Simulator/nu_yaw_hil", 0, "", offsetof
    (BlockIO_NLPID, nu_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 1192, 0 },

  { 597, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Sum", 0, "",
    offsetof(BlockIO_NLPID, Sum_e), BLOCKIO_SIG, 24, 3, 2, 1194, 0 },

  { 598, "nlpid/Plants/Linear Simulator/Linear Vessel Dynamics/Product2", 0, "",
    offsetof(BlockIO_NLPID, Product2_kw), BLOCKIO_SIG, 24, 3, 2, 1196, 0 },

  { 599, "nlpid/Plants/CSE1/Bow Thruster/BT_D_Gain1", 0, "", offsetof
    (BlockIO_NLPID, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2, 1198, 0 },

  { 600, "nlpid/Plants/CSE1/Bow Thruster/BT_D_Gain2", 0, "", offsetof
    (BlockIO_NLPID, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2, 1200, 0 },

  { 601, "nlpid/Plants/CSE1/Bow Thruster/Add", 0, "", offsetof(BlockIO_NLPID,
    Add_af), BLOCKIO_SIG, 0, 1, 2, 1202, 0 },

  { 602, "nlpid/Plants/CSE1/Bow Thruster/BT_L_Gain1", 0, "", offsetof
    (BlockIO_NLPID, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2, 1204, 0 },

  { 603, "nlpid/Plants/CSE1/Bow Thruster/BT_L_Gain2", 0, "", offsetof
    (BlockIO_NLPID, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2, 1206, 0 },

  { 604, "nlpid/Plants/CSE1/Bow Thruster/Neg", 0, "", offsetof(BlockIO_NLPID,
    Neg), BLOCKIO_SIG, 0, 1, 2, 1208, 0 },

  { 605, "nlpid/Plants/CSE1/Bow Thruster/Sum1", 0, "", offsetof(BlockIO_NLPID,
    Sum1_nf), BLOCKIO_SIG, 0, 1, 2, 1210, 0 },

  { 606, "nlpid/Plants/CSE1/Bow Thruster/Sum2", 0, "", offsetof(BlockIO_NLPID,
    Sum2), BLOCKIO_SIG, 0, 1, 2, 1212, 0 },

  { 607, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch", 0, "",
    offsetof(BlockIO_NLPID, Switch_j), BLOCKIO_SIG, 0, 1, 2, 1214, 0 },

  { 608, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch2", 0, "",
    offsetof(BlockIO_NLPID, Switch2_e), BLOCKIO_SIG, 0, 1, 2, 1216, 0 },

  { 609, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch", 0, "",
    offsetof(BlockIO_NLPID, Switch_i), BLOCKIO_SIG, 0, 1, 2, 1218, 0 },

  { 610, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch2", 0, "",
    offsetof(BlockIO_NLPID, Switch2_i), BLOCKIO_SIG, 0, 1, 2, 1220, 0 },

  { 611, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch", 0, "",
    offsetof(BlockIO_NLPID, Switch_e), BLOCKIO_SIG, 0, 1, 2, 1222, 0 },

  { 612, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch2", 0, "",
    offsetof(BlockIO_NLPID, Switch2_o), BLOCKIO_SIG, 0, 1, 2, 1224, 0 },

  { 613, "nlpid/Plants/CSE1/Voith Schneider Propeller /Sign", 0, "", offsetof
    (BlockIO_NLPID, Sign_c), BLOCKIO_SIG, 0, 1, 2, 1226, 0 },

  { 614, "nlpid/Plants/CSE1/Voith Schneider Propeller /Product1", 0,
    "Port VPS_X", offsetof(BlockIO_NLPID, PortVPS_X), BLOCKIO_SIG, 0, 1, 2, 1228,
    0 },

  { 615, "nlpid/Plants/CSE1/Voith Schneider Propeller /-x", 0, "Port VPS_X",
    offsetof(BlockIO_NLPID, PortVPS_X_l), BLOCKIO_SIG, 0, 1, 2, 1230, 0 },

  { 616, "nlpid/Plants/CSE1/Voith Schneider Propeller /Product2", 0,
    "Port VSP_Y", offsetof(BlockIO_NLPID, PortVSP_Y), BLOCKIO_SIG, 0, 1, 2, 1232,
    0 },

  { 617, "nlpid/Plants/CSE1/Voith Schneider Propeller /-y", 0, "Port VSP_Y",
    offsetof(BlockIO_NLPID, PortVSP_Y_c), BLOCKIO_SIG, 0, 1, 2, 1234, 0 },

  { 618, "nlpid/Plants/CSE1/Voith Schneider Propeller /Product3", 0,
    "Starboard VSP_X", offsetof(BlockIO_NLPID, StarboardVSP_X), BLOCKIO_SIG, 0,
    1, 2, 1236, 0 },

  { 619, "nlpid/Plants/CSE1/Voith Schneider Propeller /Product4", 0,
    "Starboard VSP_Y", offsetof(BlockIO_NLPID, StarboardVSP_Y), BLOCKIO_SIG, 0,
    1, 2, 1238, 0 },

  { 620, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo1", 0, "", offsetof
    (BlockIO_NLPID, Servo1), BLOCKIO_SIG, 0, 1, 2, 1240, 0 },

  { 621, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo2", 0, "", offsetof
    (BlockIO_NLPID, Servo2), BLOCKIO_SIG, 0, 1, 2, 1242, 0 },

  { 622, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo3", 0, "", offsetof
    (BlockIO_NLPID, Servo3), BLOCKIO_SIG, 0, 1, 2, 1244, 0 },

  { 623, "nlpid/Plants/CSE1/Voith Schneider Propeller /Servo4", 0, "", offsetof
    (BlockIO_NLPID, Servo4), BLOCKIO_SIG, 0, 1, 2, 1246, 0 },

  { 624, "nlpid/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain", 0, "",
    offsetof(BlockIO_NLPID, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2, 1248, 0 },

  { 625, "nlpid/Plants/CSE1/Voith Schneider Propeller /Sum", 0, "", offsetof
    (BlockIO_NLPID, Sum_bl), BLOCKIO_SIG, 0, 1, 2, 1250, 0 },

  { 626, "nlpid/Plants/CSE1/Voith Schneider Propeller /VSPS Port", 0, "",
    offsetof(BlockIO_NLPID, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 1252, 0 },

  { 627, "nlpid/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard", 0, "",
    offsetof(BlockIO_NLPID, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2, 1254, 0 },

  { 628,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12",
    0, "", offsetof(BlockIO_NLPID, S12_j), BLOCKIO_SIG, 0, 1, 2, 1256, 0 },

  { 629,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S_2(psi_d^s^2)",
    0, "", offsetof(BlockIO_NLPID, S_2psi_ds2), BLOCKIO_SIG, 22, 4, 2, 1258, 0 },

  { 630,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S12",
    0, "", offsetof(BlockIO_NLPID, S12_c), BLOCKIO_SIG, 0, 1, 2, 1260, 0 },

  { 631,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S_2(psi_d^s)",
    0, "", offsetof(BlockIO_NLPID, S_2psi_ds), BLOCKIO_SIG, 22, 4, 2, 1262, 0 },

  { 632,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R11",
    0, "", offsetof(BlockIO_NLPID, R11_k), BLOCKIO_SIG, 0, 1, 2, 1264, 0 },

  { 633,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R21",
    0, "", offsetof(BlockIO_NLPID, R21_o), BLOCKIO_SIG, 0, 1, 2, 1266, 0 },

  { 634,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R12",
    0, "", offsetof(BlockIO_NLPID, R12_h), BLOCKIO_SIG, 0, 1, 2, 1268, 0 },

  { 635,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R22",
    0, "", offsetof(BlockIO_NLPID, R22_c), BLOCKIO_SIG, 0, 1, 2, 1270, 0 },

  { 636,
    "nlpid/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R_2(psi_d)",
    0, "", offsetof(BlockIO_NLPID, R_2psi_d), BLOCKIO_SIG, 22, 4, 2, 1272, 0 },

  { 637,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_fm), BLOCKIO_SIG, 15, 1, 2, 1274, 0 },

  { 638,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_ce), BLOCKIO_SIG, 15, 1, 2, 1276, 0 },

  { 639,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_i), BLOCKIO_SIG, 15, 1, 2, 1278, 0 },

  { 640,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_o), BLOCKIO_SIG, 15, 1, 2, 1280, 0 },

  { 641,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_e), BLOCKIO_SIG, 15, 1, 2, 1282, 0 },

  { 642,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_k), BLOCKIO_SIG, 15, 1, 2, 1284, 0 },

  { 643,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_d), BLOCKIO_SIG, 15, 1, 2, 1286, 0 },

  { 644,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_fx), BLOCKIO_SIG, 15, 1, 2, 1288, 0 },

  { 645,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_mf), BLOCKIO_SIG, 15, 1, 2, 1290, 0 },

  { 646,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_n), BLOCKIO_SIG, 15, 1, 2, 1292, 0 },

  { 647,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_i), BLOCKIO_SIG, 15, 1, 2, 1294, 0 },

  { 648,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_it), BLOCKIO_SIG, 15, 1, 2, 1296, 0 },

  { 649,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_fd), BLOCKIO_SIG, 15, 1, 2, 1298, 0 },

  { 650,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_n), BLOCKIO_SIG, 15, 1, 2, 1300, 0 },

  { 651,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_e1), BLOCKIO_SIG, 15, 1, 2, 1302, 0 },

  { 652,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_gb), BLOCKIO_SIG, 39, 1, 2, 1304, 0 },

  { 653,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_cn), BLOCKIO_SIG, 39, 1, 2, 1306, 0 },

  { 654,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_c), BLOCKIO_SIG, 39, 1, 2, 1308, 0 },

  { 655,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_b), BLOCKIO_SIG, 39, 1, 2, 1310, 0 },

  { 656,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_cm), BLOCKIO_SIG, 39, 1, 2, 1312, 0 },

  { 657,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_m3), BLOCKIO_SIG, 39, 1, 2, 1314, 0 },

  { 658,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_ef), BLOCKIO_SIG, 39, 1, 2, 1316, 0 },

  { 659,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_k), BLOCKIO_SIG, 39, 1, 2, 1318, 0 },

  { 660,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_d), BLOCKIO_SIG, 39, 1, 2, 1320, 0 },

  { 661,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_nf), BLOCKIO_SIG, 39, 1, 2, 1322, 0 },

  { 662,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_h), BLOCKIO_SIG, 39, 1, 2, 1324, 0 },

  { 663,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_kv), BLOCKIO_SIG, 39, 1, 2, 1326, 0 },

  { 664,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_NLPID, Gain_nx), BLOCKIO_SIG, 39, 1, 2, 1328, 0 },

  { 665,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_NLPID, Gain1_cx), BLOCKIO_SIG, 39, 1, 2, 1330, 0 },

  { 666,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_NLPID, Sum_hs), BLOCKIO_SIG, 39, 1, 2, 1332, 0 },

  { 667,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare), BLOCKIO_SIG, 3, 1, 2, 1334, 0 },

  { 668,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_m), BLOCKIO_SIG, 3, 1, 2, 1336, 0 },

  { 669,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_i), BLOCKIO_SIG, 3, 1, 2, 1338, 0 },

  { 670,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_b), BLOCKIO_SIG, 3, 1, 2, 1340, 0 },

  { 671,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_g), BLOCKIO_SIG, 3, 1, 2, 1342, 0 },

  { 672,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_mz), BLOCKIO_SIG, 3, 1, 2, 1344, 0 },

  { 673,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_gm), BLOCKIO_SIG, 3, 1, 2, 1346, 0 },

  { 674,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_l), BLOCKIO_SIG, 3, 1, 2, 1348, 0 },

  { 675,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_bs), BLOCKIO_SIG, 3, 1, 2, 1350, 0 },

  { 676,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_j), BLOCKIO_SIG, 3, 1, 2, 1352, 0 },

  { 677,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_je), BLOCKIO_SIG, 3, 1, 2, 1354, 0 },

  { 678,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_h), BLOCKIO_SIG, 3, 1, 2, 1356, 0 },

  { 679,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_l3), BLOCKIO_SIG, 3, 1, 2, 1358, 0 },

  { 680,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_m1), BLOCKIO_SIG, 3, 1, 2, 1360, 0 },

  { 681,
    "nlpid/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_d), BLOCKIO_SIG, 3, 1, 2, 1362, 0 },

  { 682,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_p), BLOCKIO_SIG, 38, 1, 2, 1364, 0 },

  { 683,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_ma), BLOCKIO_SIG, 38, 1, 2, 1366, 0 },

  { 684,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_go), BLOCKIO_SIG, 38, 1, 2, 1368, 0 },

  { 685,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_g1), BLOCKIO_SIG, 38, 1, 2, 1370, 0 },

  { 686,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_jl), BLOCKIO_SIG, 38, 1, 2, 1372, 0 },

  { 687,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_l1), BLOCKIO_SIG, 38, 1, 2, 1374, 0 },

  { 688,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_jlz), BLOCKIO_SIG, 38, 1, 2, 1376, 0
  },

  { 689,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_g0), BLOCKIO_SIG, 38, 1, 2, 1378, 0 },

  { 690,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_hr), BLOCKIO_SIG, 38, 1, 2, 1380, 0 },

  { 691,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_a), BLOCKIO_SIG, 38, 1, 2, 1382, 0 },

  { 692,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_gq), BLOCKIO_SIG, 38, 1, 2, 1384, 0 },

  { 693,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_j1), BLOCKIO_SIG, 38, 1, 2, 1386, 0 },

  { 694,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_c), BLOCKIO_SIG, 38, 1, 2, 1388, 0 },

  { 695,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_f), BLOCKIO_SIG, 38, 1, 2, 1390, 0 },

  { 696,
    "nlpid/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPID, Compare_js), BLOCKIO_SIG, 38, 1, 2, 1392, 0 },

  { 697,
    "nlpid/Guidance Systems/Path-following/Path/saturation/Saturation x/LowerRelop1",
    0, "", offsetof(BlockIO_NLPID, LowerRelop1), BLOCKIO_SIG, 8, 1, 2, 1394, 0 },

  { 698,
    "nlpid/Guidance Systems/Path-following/Path/saturation/Saturation x/UpperRelop",
    0, "", offsetof(BlockIO_NLPID, UpperRelop), BLOCKIO_SIG, 8, 1, 2, 1396, 0 },

  { 699,
    "nlpid/Guidance Systems/Path-following/Path/saturation/Saturation y/LowerRelop1",
    0, "", offsetof(BlockIO_NLPID, LowerRelop1_l), BLOCKIO_SIG, 8, 1, 2, 1398, 0
  },

  { 700,
    "nlpid/Guidance Systems/Path-following/Path/saturation/Saturation y/UpperRelop",
    0, "", offsetof(BlockIO_NLPID, UpperRelop_e), BLOCKIO_SIG, 8, 1, 2, 1400, 0
  },

  { 701, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic/LowerRelop1", 0, "",
    offsetof(BlockIO_NLPID, LowerRelop1_e), BLOCKIO_SIG, 8, 1, 2, 1402, 0 },

  { 702, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic/UpperRelop", 0, "",
    offsetof(BlockIO_NLPID, UpperRelop_p), BLOCKIO_SIG, 8, 1, 2, 1404, 0 },

  { 703, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic1/LowerRelop1", 0, "",
    offsetof(BlockIO_NLPID, LowerRelop1_h), BLOCKIO_SIG, 8, 1, 2, 1406, 0 },

  { 704, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic1/UpperRelop", 0, "",
    offsetof(BlockIO_NLPID, UpperRelop_o), BLOCKIO_SIG, 8, 1, 2, 1408, 0 },

  { 705, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic2/LowerRelop1", 0, "",
    offsetof(BlockIO_NLPID, LowerRelop1_i), BLOCKIO_SIG, 8, 1, 2, 1410, 0 },

  { 706, "nlpid/Plants/CSE1/Bow Thruster/Saturation Dynamic2/UpperRelop", 0, "",
    offsetof(BlockIO_NLPID, UpperRelop_l), BLOCKIO_SIG, 8, 1, 2, 1412, 0 },

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
  1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 3, 5, 5, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3,
  3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 3, 1, 3, 3, 1, 1, 1, 1,
  1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1,
  3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2,
  1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2,
  1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2,
  1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 3, 3, 3, 1, 3, 1,
  3, 1, 3, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 7, 1, 1,
  1, 1, 1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 2, 2, 3, 1, 3, 2,
  2, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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

static char* NI_CompiledModelName = "nlpid";
static char* NI_CompiledModelVersion = "1.31";
static char* NI_CompiledModelDateTime = "Mon Mar 17 14:05:32 2014";

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
   The undef allows us to access the real NLPID_P
   In the rest of the code NLPID_P is redefine to be the read-side
   of rtParameter.
 */
#undef NLPID_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &NLPID_P, sizeof(Parameters_NLPID));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka NLPID_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_NLPID));
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
             (Parameters_NLPID));

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
           (Parameters_NLPID));
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

#endif                                 // of NI_ROOTMODEL_NLPID
