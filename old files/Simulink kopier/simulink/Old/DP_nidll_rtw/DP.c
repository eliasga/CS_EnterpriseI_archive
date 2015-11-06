/*
 * DP.c
 *
 * Real-Time Workshop code generation for Simulink model "DP.mdl".
 *
 * Model Version              : 1.21
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 16 18:55:56 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DP.h"
#include "DP_private.h"

/* Block signals (auto storage) */
BlockIO_DP DP_B;

/* Continuous states */
ContinuousStates_DP DP_X;

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
D_Work_DP DP_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_DP DP_PrevZCSigState;

/* Real-time model */
RT_MODEL_DP DP_M_;
RT_MODEL_DP *DP_M = &DP_M_;

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
  int_T nXc = 9;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y,x,
                nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  DP_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  DP_output(0);
  DP_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE5_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  DP_output(0);
  DP_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++)
    hB[i] = h * rt_ODE5_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  DP_output(0);
  DP_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++)
    hB[i] = h * rt_ODE5_B[3][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  DP_output(0);
  DP_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++)
    hB[i] = h * rt_ODE5_B[4][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  DP_output(0);
  DP_derivatives();

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
void DP_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(DP_M)) {
    DP_M->Timing.t[0] = rtsiGetT(&DP_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(DP_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&DP_M->solverInfo,
                          ((DP_M->Timing.clockTick0+1)*DP_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T tmp;
    real_T tmp_0[5];
    int32_T i;
    real_T tmp_1[18];
    int32_T tmp_2;

    /* Gain: '<S40>/QTM In2 Error' */
    DP_B.QTMIn2Error = DP_P.QTMIn2Error_Gain * DP_B.QTMIn[1];

    /* Gain: '<S40>/QTM In9 Residual' */
    DP_B.QTMIn9Residual = DP_P.QTMIn9Residual_Gain * DP_B.QTMIn[8];

    /* Gain: '<S40>/QTM In3' */
    DP_B.QTMIn3 = DP_P.QTMIn3_Gain * DP_B.QTMIn[2];

    /* Gain: '<S40>/mm2m x' */
    DP_B.mm2mx = DP_P.mm2mx_Gain * DP_B.QTMIn3;

    /* Gain: '<S40>/QTM In4' */
    DP_B.QTMIn4 = DP_P.QTMIn4_Gain * DP_B.QTMIn[3];

    /* Gain: '<S40>/mm2m y' */
    DP_B.mm2my = DP_P.mm2my_Gain * DP_B.QTMIn4;

    /* Gain: '<S40>/QTM In6' */
    DP_B.QTMIn6 = DP_P.QTMIn6_Gain * DP_B.QTMIn[5];

    /* Gain: '<S40>/d2r yaw' */
    DP_B.d2ryaw = DP_P.d2ryaw_Gain * DP_B.QTMIn6;

    /* Derivative Block: '<S40>/Derivative1' */
    {
      real_T t = DP_M->Timing.t[0];
      real_T timeStampA = DP_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = DP_DWork.Derivative1_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        DP_B.Derivative1[0] = 0.0;
        DP_B.Derivative1[1] = 0.0;
        DP_B.Derivative1[2] = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &DP_DWork.Derivative1_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 4;
          }
        } else if (timeStampA >= t) {
          lastBank += 4;
        }

        deltaT = t - *lastBank++;
        DP_B.Derivative1[0] = (DP_B.mm2mx - *lastBank++) / deltaT;
        DP_B.Derivative1[1] = (DP_B.mm2my - *lastBank++) / deltaT;
        DP_B.Derivative1[2] = (DP_B.d2ryaw - *lastBank++) / deltaT;
      }
    }

    /* Outputs for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Constant: '<S5>/Enable Linear Simulator'
     *  EnablePort: '<S43>/Enable'
     */
    if (rtmIsMajorTimeStep(DP_M) && rtmIsMajorTimeStep(DP_M)) {
      if (DP_P.EnableLinearSimulator_Value > 0.0) {
        if (DP_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S50>/Integrator' */
          if (rtmIsFirstInitCond(DP_M)) {
            DP_X.Integrator_CSTATE_n[0] = 0.0;
            DP_X.Integrator_CSTATE_n[1] = 0.0;
            DP_X.Integrator_CSTATE_n[2] = 0.0;
          }

          DP_DWork.Integrator_IWORK.IcNeedsLoading = 1;

          /* Integrator Block: '<S50>/Integrator1' */
          if (rtmIsFirstInitCond(DP_M)) {
            DP_X.Integrator1_CSTATE[0] = 0.0;
            DP_X.Integrator1_CSTATE[1] = 0.0;
            DP_X.Integrator1_CSTATE[2] = 0.0;
          }

          DP_DWork.Integrator1_IWORK.IcNeedsLoading = 1;
          DP_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (DP_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
          DP_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (DP_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      if (rtmIsMajorTimeStep(DP_M)) {
        /* Gain: '<S51>/-N_r' incorporates:
         *  Constant: '<S51>/N_r'
         */
        DP_B.N_r = DP_P.N_r_Gain * DP_P.N_r_Value;

        /* Gain: '<S51>/-N_v' incorporates:
         *  Constant: '<S51>/N_v'
         */
        DP_B.N_v = DP_P.N_v_Gain * DP_P.N_v_Value;

        /* Gain: '<S51>/-X_u' incorporates:
         *  Constant: '<S51>/X_u'
         */
        DP_B.X_u = DP_P.X_u_Gain * DP_P.X_u_Value;

        /* Gain: '<S51>/-Y_v' incorporates:
         *  Constant: '<S51>/Y_v'
         */
        DP_B.Y_v = DP_P.Y_v_Gain * DP_P.Y_v_Value;

        /* Gain: '<S51>/-Y_vr' incorporates:
         *  Constant: '<S51>/Y_r'
         */
        DP_B.Y_vr = DP_P.Y_vr_Gain * DP_P.Y_r_Value;

        /* Reshape: '<S51>/Linear Dampning matrix' incorporates:
         *  Constant: '<S51>/D_L_12'
         *  Constant: '<S51>/D_L_13'
         *  Constant: '<S51>/D_L_21'
         *  Constant: '<S51>/D_L_31'
         */
        DP_B.LinearDampningmatrix[0] = DP_B.X_u;
        DP_B.LinearDampningmatrix[1] = DP_P.D_L_21_Value;
        DP_B.LinearDampningmatrix[2] = DP_P.D_L_31_Value;
        DP_B.LinearDampningmatrix[3] = DP_P.D_L_12_Value;
        DP_B.LinearDampningmatrix[4] = DP_B.Y_v;
        DP_B.LinearDampningmatrix[5] = DP_B.N_v;
        DP_B.LinearDampningmatrix[6] = DP_P.D_L_13_Value;
        DP_B.LinearDampningmatrix[7] = DP_B.Y_vr;
        DP_B.LinearDampningmatrix[8] = DP_B.N_r;

        /* Constant: '<S52>/psi_0' */
        DP_B.psi_0 = DP_P.psi_0_Value;

        /* Constant: '<S52>/x_0' */
        DP_B.x_0 = DP_P.x_0_Value;

        /* Constant: '<S52>/y_0' */
        DP_B.y_0 = DP_P.y_0_Value;

        /* Constant: '<S53>/r_0' */
        DP_B.r_0 = DP_P.r_0_Value;

        /* Constant: '<S53>/u_0' */
        DP_B.u_0 = DP_P.u_0_Value;

        /* Constant: '<S53>/v_0' */
        DP_B.v_0 = DP_P.v_0_Value;
      }

      /* Integrator Block: '<S50>/Integrator'
       */
      if (rtmIsMajorTimeStep(DP_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &DP_PrevZCSigState.Integrator_Reset_ZCE_e,
                           DP_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || DP_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            DP_DWork.Integrator_IWORK.IcNeedsLoading) {
          DP_X.Integrator_CSTATE_n[0] = DP_B.u_0;
          DP_X.Integrator_CSTATE_n[1] = DP_B.v_0;
          DP_X.Integrator_CSTATE_n[2] = DP_B.r_0;
        }

        DP_DWork.Integrator_IWORK.IcNeedsLoading = 0;
      }

      DP_B.Integrator_d[0] = DP_X.Integrator_CSTATE_n[0];
      DP_B.Integrator_d[1] = DP_X.Integrator_CSTATE_n[1];
      DP_B.Integrator_d[2] = DP_X.Integrator_CSTATE_n[2];

      /* Integrator Block: '<S50>/Integrator1'
       */
      if (rtmIsMajorTimeStep(DP_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &DP_PrevZCSigState.Integrator1_Reset_ZCE,
                           DP_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || DP_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            DP_DWork.Integrator1_IWORK.IcNeedsLoading) {
          DP_X.Integrator1_CSTATE[0] = DP_B.x_0;
          DP_X.Integrator1_CSTATE[1] = DP_B.y_0;
          DP_X.Integrator1_CSTATE[2] = DP_B.psi_0;
        }

        DP_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
      }

      DP_B.Integrator1[0] = DP_X.Integrator1_CSTATE[0];
      DP_B.Integrator1[1] = DP_X.Integrator1_CSTATE[1];
      DP_B.Integrator1[2] = DP_X.Integrator1_CSTATE[2];
      if (rtmIsMajorTimeStep(DP_M)) {
        /* Sum: '<S54>/M_11' incorporates:
         *  Constant: '<S54>/X_udot'
         *  Constant: '<S54>/m'
         */
        DP_B.M_11 = DP_P.m_Value - DP_P.X_udot_Value;

        /* Sum: '<S54>/M_22' incorporates:
         *  Constant: '<S54>/Y_vdot'
         *  Constant: '<S54>/m'
         */
        DP_B.M_22 = DP_P.m_Value - DP_P.Y_vdot_Value;

        /* Product: '<S54>/m x_g' incorporates:
         *  Constant: '<S54>/m'
         *  Constant: '<S54>/x_g'
         */
        DP_B.mx_g = DP_P.m_Value * DP_P.x_g_Value;

        /* Sum: '<S54>/M_32' incorporates:
         *  Constant: '<S54>/N_vdot'
         */
        DP_B.M_32 = DP_B.mx_g - DP_P.N_vdot_Value;

        /* Sum: '<S54>/M_23' incorporates:
         *  Constant: '<S54>/Y_rdot'
         */
        DP_B.M_23 = DP_B.mx_g - DP_P.Y_rdot_Value;

        /* Sum: '<S54>/M_33' incorporates:
         *  Constant: '<S54>/I_z'
         *  Constant: '<S54>/N_rdot'
         */
        DP_B.M_33 = DP_P.I_z_Value - DP_P.N_rdot_Value;

        /* Reshape: '<S54>/M' incorporates:
         *  Constant: '<S54>/M_12'
         *  Constant: '<S54>/M_13'
         *  Constant: '<S54>/M_21'
         *  Constant: '<S54>/M_31'
         */
        DP_B.M[0] = DP_B.M_11;
        DP_B.M[1] = DP_P.M_21_Value;
        DP_B.M[2] = DP_P.M_31_Value;
        DP_B.M[3] = DP_P.M_12_Value;
        DP_B.M[4] = DP_B.M_22;
        DP_B.M[5] = DP_B.M_32;
        DP_B.M[6] = DP_P.M_13_Value;
        DP_B.M[7] = DP_B.M_23;
        DP_B.M[8] = DP_B.M_33;

        /* Product Block: '<S54>/Inverse' */
        {
          static const int_T dims[3] = { 3, 3, 3 };

          rt_MatDivRR_Dbl(DP_B.Inverse, DP_B.M,
                          &DP_DWork.Inverse_DWORK4[0], (real_T*)
                          &DP_DWork.Pseudoinverse_X[0],
                          &DP_DWork.Inverse_DWORK2[0], (real_T*)
                          &DP_DWork.Inverse_DWORK3[0],
                          &dims[0]);
        }
      }

      /* Fcn: '<S55>/R11' */
      DP_B.R11_i = cos(DP_B.Integrator1[2]);

      /* Fcn: '<S55>/R21' */
      DP_B.R21_e = sin(DP_B.Integrator1[2]);

      /* Fcn: '<S55>/R12' */
      DP_B.R12_a = -1.0 * sin(DP_B.Integrator1[2]);

      /* Fcn: '<S55>/R22' */
      DP_B.R22_f = cos(DP_B.Integrator1[2]);

      /* Reshape: '<S55>/R(psi)' incorporates:
       *  Constant: '<S55>/R13'
       *  Constant: '<S55>/R23'
       *  Constant: '<S55>/R31'
       *  Constant: '<S55>/R32'
       *  Constant: '<S55>/R33'
       */
      DP_B.Rpsi[0] = DP_B.R11_i;
      DP_B.Rpsi[1] = DP_B.R21_e;
      DP_B.Rpsi[2] = DP_P.R31_Value;
      DP_B.Rpsi[3] = DP_B.R12_a;
      DP_B.Rpsi[4] = DP_B.R22_f;
      DP_B.Rpsi[5] = DP_P.R32_Value;
      DP_B.Rpsi[6] = DP_P.R13_Value;
      DP_B.Rpsi[7] = DP_P.R23_Value;
      DP_B.Rpsi[8] = DP_P.R33_Value;
      for (i = 0; i < 3; i++) {
        /* Product: '<S50>/Product1' */
        DP_B.Product1[i] = 0.0;
        DP_B.Product1[i] = DP_B.LinearDampningmatrix[i] * DP_B.Integrator_d[0] +
          DP_B.Product1[i];
        DP_B.Product1[i] = DP_B.LinearDampningmatrix[i + 3] * DP_B.Integrator_d
          [1] + DP_B.Product1[i];
        DP_B.Product1[i] = DP_B.LinearDampningmatrix[i + 6] * DP_B.Integrator_d
          [2] + DP_B.Product1[i];

        /* Product: '<S50>/Product3' */
        DP_B.Product3[i] = 0.0;
        DP_B.Product3[i] = DP_B.Rpsi[i] * DP_B.Integrator_d[0] + DP_B.Product3[i];
        DP_B.Product3[i] = DP_B.Rpsi[i + 3] * DP_B.Integrator_d[1] +
          DP_B.Product3[i];
        DP_B.Product3[i] = DP_B.Rpsi[i + 6] * DP_B.Integrator_d[2] +
          DP_B.Product3[i];
      }

      /* Gain: '<S43>/eta_surge_hil' */
      DP_B.eta_surge_hil = DP_P.eta_surge_hil_Gain * DP_B.Integrator1[0];

      /* Gain: '<S43>/eta_sway_hil' */
      DP_B.eta_sway_hil = DP_P.eta_sway_hil_Gain * DP_B.Integrator1[1];

      /* Gain: '<S43>/eta_yaw_hil' */
      DP_B.eta_yaw_hil = DP_P.eta_yaw_hil_Gain * DP_B.Integrator1[2];

      /* Gain: '<S43>/etadot_surge_hil' */
      DP_B.etadot_surge_hil = DP_P.etadot_surge_hil_Gain * DP_B.Product3[0];

      /* Gain: '<S43>/etadot_sway_hil' */
      DP_B.etadot_sway_hil = DP_P.etadot_sway_hil_Gain * DP_B.Product3[1];

      /* Gain: '<S43>/etadot_yaw_hil' */
      DP_B.etadot_yaw_hil = DP_P.etadot_yaw_hil_Gain * DP_B.Product3[2];

      /* Gain: '<S43>/nu_surge_hil' */
      DP_B.nu_surge_hil = DP_P.nu_surge_hil_Gain * DP_B.Integrator_d[0];

      /* Gain: '<S43>/nu_sway_hil' */
      DP_B.nu_sway_hil = DP_P.nu_sway_hil_Gain * DP_B.Integrator_d[1];

      /* Gain: '<S43>/nu_yaw_hil' */
      DP_B.nu_yaw_hil = DP_P.nu_yaw_hil_Gain * DP_B.Integrator_d[2];
    }

    /* end of Outputs for SubSystem: '<S5>/Linear Simulator' */

    /* MultiPortSwitch: '<S4>/Etadot Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)DP_P.ControllerInputSelector_Value == 0) {
      DP_B.EtadotSwitch[0] = DP_B.Derivative1[0];
      DP_B.EtadotSwitch[1] = DP_B.Derivative1[1];
      DP_B.EtadotSwitch[2] = DP_B.Derivative1[2];
    } else {
      DP_B.EtadotSwitch[0] = DP_B.etadot_surge_hil;
      DP_B.EtadotSwitch[1] = DP_B.etadot_sway_hil;
      DP_B.EtadotSwitch[2] = DP_B.etadot_yaw_hil;
    }

    /* Gain: '<S4>/etadot_surge' */
    DP_B.etadot_surge = DP_P.etadot_surge_Gain * DP_B.EtadotSwitch[0];

    /* Gain: '<S4>/etadot_sway' */
    DP_B.etadot_sway = DP_P.etadot_sway_Gain * DP_B.EtadotSwitch[1];

    /* Gain: '<S4>/etadot_yaw' */
    DP_B.etadot_yaw = DP_P.etadot_yaw_Gain * DP_B.EtadotSwitch[2];

    /* MultiPortSwitch: '<S4>/Eta Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)DP_P.ControllerInputSelector_Value == 0) {
      DP_B.EtaSwitch[0] = DP_B.mm2mx;
      DP_B.EtaSwitch[1] = DP_B.mm2my;
      DP_B.EtaSwitch[2] = DP_B.d2ryaw;
    } else {
      DP_B.EtaSwitch[0] = DP_B.eta_surge_hil;
      DP_B.EtaSwitch[1] = DP_B.eta_sway_hil;
      DP_B.EtaSwitch[2] = DP_B.eta_yaw_hil;
    }

    /* Gain: '<S4>/eta_surge' */
    DP_B.eta_surge = DP_P.eta_surge_Gain * DP_B.EtaSwitch[0];

    /* Gain: '<S4>/eta_sway' */
    DP_B.eta_sway = DP_P.eta_sway_Gain * DP_B.EtaSwitch[1];

    /* Gain: '<S4>/eta_yaw' */
    DP_B.eta_yaw = DP_P.eta_yaw_Gain * DP_B.EtaSwitch[2];

    /* Gain: '<S40>/QTM In8' */
    DP_B.QTMIn8 = DP_P.QTMIn8_Gain * DP_B.QTMIn[7];

    /* Gain: '<S40>/d2r roll' */
    DP_B.d2rroll = DP_P.d2rroll_Gain * DP_B.QTMIn8;

    /* Gain: '<S40>/QTM In7' */
    DP_B.QTMIn7 = DP_P.QTMIn7_Gain * DP_B.QTMIn[6];

    /* Gain: '<S40>/d2r pitch' */
    DP_B.d2rpitch = DP_P.d2rpitch_Gain * DP_B.QTMIn7;

    /* Trigonometry: '<S41>/sin(theta)' */
    DP_B.sintheta[0] = sin(DP_B.d2rroll);
    DP_B.sintheta[1] = sin(DP_B.d2rpitch);
    DP_B.sintheta[2] = sin(DP_B.d2ryaw);

    /* Trigonometry: '<S41>/cos(theta)' */
    DP_B.costheta[0] = cos(DP_B.d2rroll);
    DP_B.costheta[1] = cos(DP_B.d2rpitch);
    DP_B.costheta[2] = cos(DP_B.d2ryaw);

    /* Fcn: '<S41>/R11' */
    DP_B.R11 = DP_B.costheta[1] * DP_B.costheta[2];

    /* Fcn: '<S41>/R21 ' */
    DP_B.R21 = DP_B.sintheta[0] * DP_B.sintheta[1] * DP_B.costheta[2] +
      (-DP_B.costheta[0]) * DP_B.sintheta[2];

    /* Fcn: '<S41>/R31 ' */
    DP_B.R31 = DP_B.costheta[0] * DP_B.sintheta[1] * DP_B.costheta[2] +
      DP_B.sintheta[0] * DP_B.sintheta[2];

    /* Fcn: '<S41>/R12' */
    DP_B.R12 = DP_B.costheta[1] * DP_B.sintheta[2];

    /* Fcn: '<S41>/R22' */
    DP_B.R22 = DP_B.sintheta[0] * DP_B.sintheta[1] * DP_B.sintheta[2] +
      DP_B.costheta[0] * DP_B.costheta[2];

    /* Fcn: '<S41>/R32' */
    DP_B.R32 = DP_B.costheta[0] * DP_B.sintheta[1] * DP_B.sintheta[2] +
      (-DP_B.sintheta[0]) * DP_B.costheta[2];

    /* Fcn: '<S41>/R13' */
    DP_B.R13 = -DP_B.sintheta[1];

    /* Fcn: '<S41>/R23' */
    DP_B.R23 = DP_B.sintheta[0] * DP_B.costheta[1];

    /* Fcn: '<S41>/R33' */
    DP_B.R33 = DP_B.costheta[0] * DP_B.costheta[1];

    /* Reshape: '<S41>/Reshape 9x1->3x3' */
    DP_B.Reshape9x13x3[0] = DP_B.R11;
    DP_B.Reshape9x13x3[1] = DP_B.R21;
    DP_B.Reshape9x13x3[2] = DP_B.R31;
    DP_B.Reshape9x13x3[3] = DP_B.R12;
    DP_B.Reshape9x13x3[4] = DP_B.R22;
    DP_B.Reshape9x13x3[5] = DP_B.R32;
    DP_B.Reshape9x13x3[6] = DP_B.R13;
    DP_B.Reshape9x13x3[7] = DP_B.R23;
    DP_B.Reshape9x13x3[8] = DP_B.R33;

    /* Concatenate: '<S40>/Matrix Concatenate' incorporates:
     *  Constant: '<S40>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = DP_B.Reshape9x13x3[3 * i];
      tmp_1[1 + 6 * i] = DP_B.Reshape9x13x3[3 * i + 1];
      tmp_1[2 + 6 * i] = DP_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = DP_P.Constant1_Value[3 * i];
      tmp_1[4 + 6 * i] = DP_P.Constant1_Value[3 * i + 1];
      tmp_1[5 + 6 * i] = DP_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&DP_B.MatrixConcatenate2[0]), (void *)&tmp_1[0], 18U *
           sizeof(real_T));

    /* Concatenate: '<S40>/Matrix Concatenate1' incorporates:
     *  Constant: '<S40>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = DP_P.Constant1_Value[3 * i];
      tmp_1[1 + 6 * i] = DP_P.Constant1_Value[3 * i + 1];
      tmp_1[2 + 6 * i] = DP_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = DP_B.Reshape9x13x3[3 * i];
      tmp_1[4 + 6 * i] = DP_B.Reshape9x13x3[3 * i + 1];
      tmp_1[5 + 6 * i] = DP_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&DP_B.MatrixConcatenate2[18]), (void *)&tmp_1[0], 18U *
           sizeof(real_T));

    /* Gain: '<S40>/QTM In5' */
    DP_B.QTMIn5 = DP_P.QTMIn5_Gain * DP_B.QTMIn[4];

    /* Gain: '<S40>/mm2m z' */
    DP_B.mm2mz = DP_P.mm2mz_Gain * DP_B.QTMIn5;

    /* Derivative Block: '<S40>/Derivative' */
    {
      real_T t = DP_M->Timing.t[0];
      real_T timeStampA = DP_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = DP_DWork.Derivative_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = DP_B.Derivative;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank = &DP_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        DP_B.Derivative[0] = (DP_B.mm2mx - *lastBank++) / deltaT;
        DP_B.Derivative[1] = (DP_B.mm2my - *lastBank++) / deltaT;
        DP_B.Derivative[2] = (DP_B.mm2mz - *lastBank++) / deltaT;
        DP_B.Derivative[3] = (DP_B.d2rroll - *lastBank++) / deltaT;
        DP_B.Derivative[4] = (DP_B.d2rpitch - *lastBank++) / deltaT;
        DP_B.Derivative[5] = (DP_B.d2ryaw - *lastBank++) / deltaT;
      }
    }

    /* Product: '<S40>/Product' */
    for (i = 0; i < 6; i++) {
      DP_B.Product[i] = 0.0;
      for (tmp_2 = 0; tmp_2 < 6; tmp_2++) {
        DP_B.Product[i] = DP_B.MatrixConcatenate2[6 * tmp_2 + i] *
          DP_B.Derivative[tmp_2] + DP_B.Product[i];
      }
    }

    /* MultiPortSwitch: '<S4>/Nu Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)DP_P.ControllerInputSelector_Value == 0) {
      DP_B.NuSwitch[0] = DP_B.Product[0];
      DP_B.NuSwitch[1] = DP_B.Product[1];
      DP_B.NuSwitch[2] = DP_B.Product[5];
    } else {
      DP_B.NuSwitch[0] = DP_B.nu_surge_hil;
      DP_B.NuSwitch[1] = DP_B.nu_sway_hil;
      DP_B.NuSwitch[2] = DP_B.nu_yaw_hil;
    }

    /* Gain: '<S4>/nu_surge' */
    DP_B.nu_surge = DP_P.nu_surge_Gain * DP_B.NuSwitch[0];

    /* Gain: '<S4>/nu_sway' */
    DP_B.nu_sway = DP_P.nu_sway_Gain * DP_B.NuSwitch[1];

    /* Gain: '<S4>/nu_yaw' */
    DP_B.nu_yaw = DP_P.nu_yaw_Gain * DP_B.NuSwitch[2];
    if (rtmIsMajorTimeStep(DP_M)) {
      /* Gain: '<S37>/eta_d DP N' incorporates:
       *  Constant: '<S38>/x_d'
       */
      DP_B.eta_dDPN = DP_P.eta_dDPN_Gain * DP_P.x_d_Value;

      /* Gain: '<S37>/eta_d DP E' incorporates:
       *  Constant: '<S38>/y_d'
       */
      DP_B.eta_dDPE = DP_P.eta_dDPE_Gain * DP_P.y_d_Value;

      /* Gain: '<S39>/Gain1' incorporates:
       *  Constant: '<S38>/psi_d'
       */
      DP_B.Gain1 = DP_P.Gain1_Gain * DP_P.psi_d_Value;

      /* Gain: '<S37>/eta_d DP Psi' */
      DP_B.eta_dDPPsi = DP_P.eta_dDPPsi_Gain * DP_B.Gain1;

      /* Gain: '<S7>/ScalingLY' incorporates:
       *  Constant: '<S7>/AS_LY'
       */
      DP_B.ypositionofleftanalogstick11 = DP_P.ScalingLY_Gain * DP_P.AS_LY_Value;

      /* Gain: '<S8>/PS3 u_1' */
      DP_B.u_1 = DP_P.PS3u_1_Gain * DP_B.ypositionofleftanalogstick11;

      /* Gain: '<S7>/ScalingLX' incorporates:
       *  Constant: '<S7>/AS_LX'
       */
      DP_B.xpositionofleftanalogstick11 = DP_P.ScalingLX_Gain * DP_P.AS_LX_Value;

      /* Gain: '<S8>/PS3 u_2' */
      DP_B.u_2 = DP_P.PS3u_2_Gain * DP_B.xpositionofleftanalogstick11;

      /* Gain: '<S7>/ScalingRY' incorporates:
       *  Constant: '<S7>/AS_RY'
       */
      DP_B.ypositionofrightanalogstick11 = DP_P.ScalingRY_Gain *
        DP_P.AS_RY_Value;

      /* Gain: '<S8>/PS3 u_3' */
      DP_B.u_3 = DP_P.PS3u_3_Gain * DP_B.ypositionofrightanalogstick11;

      /* Gain: '<S7>/Scaling_RX' incorporates:
       *  Constant: '<S7>/AS_RX'
       */
      DP_B.xpositionofrightanalogstick11 = DP_P.Scaling_RX_Gain *
        DP_P.AS_RX_Value;

      /* Gain: '<S8>/PS3 u_4' */
      DP_B.u_4 = DP_P.PS3u_4_Gain * DP_B.xpositionofrightanalogstick11;

      /* Sum: '<S8>/Add' incorporates:
       *  Constant: '<S7>/L2'
       *  Constant: '<S7>/R2'
       */
      DP_B.BowThrusterdirection = DP_P.L2_Value + DP_P.R2_Value;

      /* Gain: '<S8>/PS3 u_5' */
      DP_B.u_5 = DP_P.PS3u_5_Gain * DP_B.BowThrusterdirection;

      /* Gain: '<S36>/-l_x1' incorporates:
       *  Constant: '<S36>/l_x1'
       */
      DP_B.l_x1 = DP_P.l_x1_Gain * DP_P.l_x1_Value;

      /* Gain: '<S36>/-l_y2' incorporates:
       *  Constant: '<S36>/l_y2'
       */
      DP_B.l_y2 = DP_P.l_y2_Gain * DP_P.l_y2_Value;

      /* Gain: '<S36>/-l_x2' incorporates:
       *  Constant: '<S36>/l_x2'
       */
      DP_B.l_x2 = DP_P.l_x2_Gain * DP_P.l_x2_Value;

      /* Reshape: '<S36>/3x5' incorporates:
       *  Constant: '<S36>/T_e11'
       *  Constant: '<S36>/T_e12'
       *  Constant: '<S36>/T_e13'
       *  Constant: '<S36>/T_e14'
       *  Constant: '<S36>/T_e15'
       *  Constant: '<S36>/T_e21'
       *  Constant: '<S36>/T_e22'
       *  Constant: '<S36>/T_e23'
       *  Constant: '<S36>/T_e24'
       *  Constant: '<S36>/T_e25'
       *  Constant: '<S36>/l_x3'
       *  Constant: '<S36>/l_y1'
       */
      DP_B.x5[0] = DP_P.T_e11_Value;
      DP_B.x5[1] = DP_P.T_e21_Value;
      DP_B.x5[2] = DP_P.l_y1_Value;
      DP_B.x5[3] = DP_P.T_e12_Value;
      DP_B.x5[4] = DP_P.T_e22_Value;
      DP_B.x5[5] = DP_B.l_x1;
      DP_B.x5[6] = DP_P.T_e13_Value;
      DP_B.x5[7] = DP_P.T_e23_Value;
      DP_B.x5[8] = DP_B.l_y2;
      DP_B.x5[9] = DP_P.T_e14_Value;
      DP_B.x5[10] = DP_P.T_e24_Value;
      DP_B.x5[11] = DP_B.l_x2;
      DP_B.x5[12] = DP_P.T_e15_Value;
      DP_B.x5[13] = DP_P.T_e25_Value;
      DP_B.x5[14] = DP_P.l_x3_Value;

      /* S-Function (sdsppinv): '<S15>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&DP_DWork.Pseudoinverse_X[0]), (void *)(&DP_B.x5[0]), 15U *
             sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&DP_DWork.Pseudoinverse_X[0], 3, 5,
                      &DP_DWork.Pseudoinverse_S[0], &DP_DWork.Inverse_DWORK3[0],
                      &DP_DWork.Pseudoinverse_WORK[0],
                      &DP_DWork.Pseudoinverse_U[0], &DP_DWork.Pseudoinverse_V[0],
                      1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&DP_DWork.Pseudoinverse_S[0],
          &DP_DWork.Pseudoinverse_U[0], &DP_DWork.Pseudoinverse_V[0],
          &DP_B.Pseudoinverse[0], (const int32_T)3, (const int32_T)5);
      }
    }

    /* Fcn: '<S9>/yaw angle' */
    DP_B.psi = DP_B.eta_yaw;

    /* Saturate: '<S13>/Saturation' */
    tmp = DP_B.psi;
    DP_B.Saturation = rt_SATURATE(tmp, DP_P.Saturation_LowerSat,
      DP_P.Saturation_UpperSat);

    /* Signum: '<S13>/Sign' */
    DP_B.Sign = rt_SIGNd_snf(DP_B.Saturation);

    /* Gain: '<S13>/Gain' */
    DP_B.Gain = DP_P.Gain_Gain * DP_B.Sign;

    /* Sum: '<S13>/Sum1' */
    DP_B.Sum1 = DP_B.Saturation + DP_B.Gain;

    /* Math: '<S13>/Math Function' incorporates:
     *  Constant: '<S13>/Constant'
     */
    DP_B.MathFunction = rt_rem_snf(DP_B.Sum1, DP_P.Constant_Value);

    /* Sum: '<S13>/Sum' */
    DP_B.Sum = DP_B.MathFunction - DP_B.Gain;

    /* Sum: '<S9>/Sum2' */
    DP_B.regulationerror[0] = DP_B.eta_dDPN - DP_B.eta_surge;
    DP_B.regulationerror[1] = DP_B.eta_dDPE - DP_B.eta_sway;
    DP_B.regulationerror[2] = DP_B.eta_dDPPsi - DP_B.eta_yaw;

    /* Saturate: '<S12>/Saturation' */
    tmp = DP_B.regulationerror[2];
    DP_B.Saturation_e = rt_SATURATE(tmp, DP_P.Saturation_LowerSat_g,
      DP_P.Saturation_UpperSat_j);

    /* Signum: '<S12>/Sign' */
    DP_B.Sign_p = rt_SIGNd_snf(DP_B.Saturation_e);

    /* Gain: '<S12>/Gain' */
    DP_B.Gain_b = DP_P.Gain_Gain_i * DP_B.Sign_p;

    /* Sum: '<S12>/Sum1' */
    DP_B.Sum1_e = DP_B.Saturation_e + DP_B.Gain_b;

    /* Math: '<S12>/Math Function' incorporates:
     *  Constant: '<S12>/Constant'
     */
    DP_B.MathFunction_k = rt_rem_snf(DP_B.Sum1_e, DP_P.Constant_Value_i);

    /* Sum: '<S12>/Sum' */
    DP_B.Sum_a = DP_B.MathFunction_k - DP_B.Gain_b;

    /* Fcn: '<S11>/Row1' */
    DP_B.Row1 = cos(DP_B.Sum) * DP_B.regulationerror[0] + sin(DP_B.Sum) *
      DP_B.regulationerror[1];

    /* Fcn: '<S11>/Row2' */
    DP_B.Row2 = (-sin(DP_B.Sum)) * DP_B.regulationerror[0] + cos(DP_B.Sum) *
      DP_B.regulationerror[1];

    /* Fcn: '<S11>/Row3' */
    DP_B.Row3 = DP_B.Sum_a;

    /* SignalConversion: '<S9>/TmpHiddenBufferAtKpInport1' */
    DP_B.TmpHiddenBufferAtKpInport1[0] = DP_B.Row1;
    DP_B.TmpHiddenBufferAtKpInport1[1] = DP_B.Row2;
    DP_B.TmpHiddenBufferAtKpInport1[2] = DP_B.Row3;

    /* Gain: '<S9>/Kp' */
    for (i = 0; i < 3; i++) {
      DP_B.Kp[i] = 0.0;
      DP_B.Kp[i] = DP_P.Kp_Gain[i] * DP_B.TmpHiddenBufferAtKpInport1[0] +
        DP_B.Kp[i];
      DP_B.Kp[i] = DP_P.Kp_Gain[i + 3] * DP_B.TmpHiddenBufferAtKpInport1[1] +
        DP_B.Kp[i];
      DP_B.Kp[i] = DP_P.Kp_Gain[i + 6] * DP_B.TmpHiddenBufferAtKpInport1[2] +
        DP_B.Kp[i];
    }

    /* Gain: '<S9>/K_p_surge_scale' */
    DP_B.K_p_surge_scale = DP_P.K_p_surge_scale_Gain * DP_B.Kp[0];

    /* Gain: '<S9>/K_p_sway_scale' */
    DP_B.K_p_sway_scale = DP_P.K_p_sway_scale_Gain * DP_B.Kp[1];

    /* Gain: '<S9>/K_p_yaw_scale' */
    DP_B.K_p_yaw_scale = DP_P.K_p_yaw_scale_Gain * DP_B.Kp[2];

    /* Integrator Block: '<S9>/Integrator'
     */
    if (rtmIsMajorTimeStep(DP_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &DP_PrevZCSigState.Integrator_Reset_ZCE,
                         DP_P.Reset_DP_integrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || DP_P.Reset_DP_integrator_Value != 0.0) {
        DP_X.Integrator_CSTATE[0] = DP_P.Integrator_IC;
        DP_X.Integrator_CSTATE[1] = DP_P.Integrator_IC;
        DP_X.Integrator_CSTATE[2] = DP_P.Integrator_IC;
      }
    }

    DP_B.Integrator[0] = DP_X.Integrator_CSTATE[0];
    DP_B.Integrator[1] = DP_X.Integrator_CSTATE[1];
    DP_B.Integrator[2] = DP_X.Integrator_CSTATE[2];

    /* Gain: '<S9>/Ki' */
    for (i = 0; i < 3; i++) {
      DP_B.Ki[i] = 0.0;
      DP_B.Ki[i] = DP_P.Ki_Gain[i] * DP_B.Integrator[0] + DP_B.Ki[i];
      DP_B.Ki[i] = DP_P.Ki_Gain[i + 3] * DP_B.Integrator[1] + DP_B.Ki[i];
      DP_B.Ki[i] = DP_P.Ki_Gain[i + 6] * DP_B.Integrator[2] + DP_B.Ki[i];
    }

    /* Gain: '<S9>/K_i_surge_scale' */
    DP_B.K_i_surge_scale = DP_P.K_i_surge_scale_Gain * DP_B.Ki[0];

    /* Gain: '<S9>/K_i_sway_scale' */
    DP_B.K_i_sway_scale = DP_P.K_i_sway_scale_Gain * DP_B.Ki[1];

    /* Gain: '<S9>/K_i_yaw_scale' */
    DP_B.K_i_yaw_scale = DP_P.K_i_yaw_scale_Gain * DP_B.Ki[2];

    /* Sum: '<S9>/Sum3' */
    DP_B.Sum3[0] = DP_B.K_p_surge_scale + DP_B.K_i_surge_scale;
    DP_B.Sum3[1] = DP_B.K_p_sway_scale + DP_B.K_i_sway_scale;
    DP_B.Sum3[2] = DP_B.K_p_yaw_scale + DP_B.K_i_yaw_scale;

    /* SignalConversion: '<S9>/TmpHiddenBufferAtKdInport1' */
    DP_B.TmpHiddenBufferAtKdInport1[0] = DP_B.nu_surge;
    DP_B.TmpHiddenBufferAtKdInport1[1] = DP_B.nu_sway;
    DP_B.TmpHiddenBufferAtKdInport1[2] = DP_B.nu_yaw;

    /* Gain: '<S9>/Kd' */
    for (i = 0; i < 3; i++) {
      DP_B.Kd[i] = 0.0;
      DP_B.Kd[i] = DP_P.Kd_Gain[i] * DP_B.TmpHiddenBufferAtKdInport1[0] +
        DP_B.Kd[i];
      DP_B.Kd[i] = DP_P.Kd_Gain[i + 3] * DP_B.TmpHiddenBufferAtKdInport1[1] +
        DP_B.Kd[i];
      DP_B.Kd[i] = DP_P.Kd_Gain[i + 6] * DP_B.TmpHiddenBufferAtKdInport1[2] +
        DP_B.Kd[i];
    }

    /* Gain: '<S9>/K_d_surge_scale' */
    DP_B.K_d_surge_scale = DP_P.K_d_surge_scale_Gain * DP_B.Kd[0];

    /* Gain: '<S9>/K_d_sway_scale' */
    DP_B.K_d_sway_scale = DP_P.K_d_sway_scale_Gain * DP_B.Kd[1];

    /* Gain: '<S9>/K_d_yaw_scale' */
    DP_B.K_d_yaw_scale = DP_P.K_d_yaw_scale_Gain * DP_B.Kd[2];

    /* Sum: '<S9>/Sum1' */
    DP_B.Sum1_d[0] = DP_B.Sum3[0] - DP_B.K_d_surge_scale;
    DP_B.Sum1_d[1] = DP_B.Sum3[1] - DP_B.K_d_sway_scale;
    DP_B.Sum1_d[2] = DP_B.Sum3[2] - DP_B.K_d_yaw_scale;

    /* Product: '<S15>/Product' */
    for (i = 0; i < 5; i++) {
      DP_B.Product_n[i] = 0.0;
      DP_B.Product_n[i] = DP_B.Pseudoinverse[i] * DP_B.Sum1_d[0] +
        DP_B.Product_n[i];
      DP_B.Product_n[i] = DP_B.Pseudoinverse[i + 5] * DP_B.Sum1_d[1] +
        DP_B.Product_n[i];
      DP_B.Product_n[i] = DP_B.Pseudoinverse[i + 10] * DP_B.Sum1_d[2] +
        DP_B.Product_n[i];
    }

    /* DeadZone Block: '<S16>/Dead Zone'
     */
    if (DP_B.Product_n[0] >= DP_P.DeadZone_End) {
      DP_B.DeadZone = DP_B.Product_n[0] - DP_P.DeadZone_End;
    } else if (DP_B.Product_n[0] > DP_P.DeadZone_Start) {
      DP_B.DeadZone = 0.0;
    } else {
      DP_B.DeadZone = DP_B.Product_n[0] - DP_P.DeadZone_Start;
    }

    /* RelationalOperator: '<S21>/Compare' incorporates:
     *  Constant: '<S21>/Constant'
     */
    DP_B.Compare = (DP_B.DeadZone < DP_P.Constant_Value_b);

    /* RelationalOperator: '<S23>/Compare' */
    DP_B.Compare_c = (DP_B.DeadZone == 0.0);

    /* Gain: '<S16>/Gain' */
    DP_B.Gain_bj = (uint16_T)(DP_P.Gain_Gain_e * DP_B.Compare_c);

    /* RelationalOperator: '<S22>/Compare' incorporates:
     *  Constant: '<S22>/Constant'
     */
    DP_B.Compare_o = (DP_B.DeadZone > DP_P.Constant_Value_p);

    /* Gain: '<S16>/Gain1' */
    DP_B.Gain1_p = (uint16_T)(DP_P.Gain1_Gain_i * DP_B.Compare_o);

    /* Sum: '<S16>/Sum' */
    DP_B.Sum_h = (uint16_T)(uint32_T)(((DP_B.Compare << 6) + DP_B.Gain_bj) +
      DP_B.Gain1_p);

    /* Lookup Block: '<S16>/f_1 < 0'
     * About '<S16>/f_1 < 0 :'
     * Lookup Block: '<S16>/f_1 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_10), DP_P.f_10_YData, DP_B.Product_n[0],
                         DP_P.f_10_XData, 8U);

    /* Lookup Block: '<S16>/f_1 > 0'
     * About '<S16>/f_1 > 0 :'
     * Lookup Block: '<S16>/f_1 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_10_e), DP_P.f_10_YData_o, DP_B.Product_n[0],
                         DP_P.f_10_XData_f, 9U);

    /* MultiPortSwitch: '<S16>/Multiport Switch' incorporates:
     *  Constant: '<S16>/f_1 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)DP_B.Sum_h >> 6)) {
     case 1:
      DP_B.MultiportSwitch = DP_B.f_10;
      break;

     case 2:
      DP_B.MultiportSwitch = DP_P.f_10_Value;
      break;

     default:
      DP_B.MultiportSwitch = DP_B.f_10_e;
      break;
    }

    /* DeadZone Block: '<S17>/Dead Zone'
     */
    if (DP_B.Product_n[1] >= DP_P.DeadZone_End_p) {
      DP_B.DeadZone_i = DP_B.Product_n[1] - DP_P.DeadZone_End_p;
    } else if (DP_B.Product_n[1] > DP_P.DeadZone_Start_e) {
      DP_B.DeadZone_i = 0.0;
    } else {
      DP_B.DeadZone_i = DP_B.Product_n[1] - DP_P.DeadZone_Start_e;
    }

    /* RelationalOperator: '<S24>/Compare' incorporates:
     *  Constant: '<S24>/Constant'
     */
    DP_B.Compare_p = (DP_B.DeadZone_i < DP_P.Constant_Value_l);

    /* RelationalOperator: '<S25>/Compare' incorporates:
     *  Constant: '<S25>/Constant'
     */
    DP_B.Compare_cj = (DP_B.DeadZone_i == DP_P.Constant_Value_f);

    /* Gain: '<S17>/Gain' */
    DP_B.Gain_m = (uint16_T)(DP_P.Gain_Gain_h * DP_B.Compare_cj);

    /* RelationalOperator: '<S26>/Compare' incorporates:
     *  Constant: '<S26>/Constant'
     */
    DP_B.Compare_i = (DP_B.DeadZone_i > DP_P.Constant_Value_a);

    /* Gain: '<S17>/Gain1' */
    DP_B.Gain1_e = (uint16_T)(DP_P.Gain1_Gain_a * DP_B.Compare_i);

    /* Sum: '<S17>/Sum' */
    DP_B.Sum_e = (uint16_T)(uint32_T)(((DP_B.Compare_p << 6) + DP_B.Gain_m) +
      DP_B.Gain1_e);

    /* Lookup Block: '<S17>/f_2 < 0'
     * About '<S17>/f_2 < 0 :'
     * Lookup Block: '<S17>/f_2 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_20), DP_P.f_20_YData, DP_B.Product_n[1],
                         DP_P.f_20_XData, 10U);

    /* Lookup Block: '<S17>/f_2 > 0'
     * About '<S17>/f_2 > 0 :'
     * Lookup Block: '<S17>/f_2 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_20_h), DP_P.f_20_YData_l, DP_B.Product_n[1],
                         DP_P.f_20_XData_d, 9U);

    /* MultiPortSwitch: '<S17>/Multiport Switch' incorporates:
     *  Constant: '<S17>/f_2 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)DP_B.Sum_e >> 6)) {
     case 1:
      DP_B.MultiportSwitch_a = DP_B.f_20;
      break;

     case 2:
      DP_B.MultiportSwitch_a = DP_P.f_20_Value;
      break;

     default:
      DP_B.MultiportSwitch_a = DP_B.f_20_h;
      break;
    }

    /* DeadZone Block: '<S18>/Dead Zone'
     */
    if (DP_B.Product_n[2] >= DP_P.DeadZone_End_h) {
      DP_B.DeadZone_o = DP_B.Product_n[2] - DP_P.DeadZone_End_h;
    } else if (DP_B.Product_n[2] > DP_P.DeadZone_Start_o) {
      DP_B.DeadZone_o = 0.0;
    } else {
      DP_B.DeadZone_o = DP_B.Product_n[2] - DP_P.DeadZone_Start_o;
    }

    /* RelationalOperator: '<S27>/Compare' incorporates:
     *  Constant: '<S27>/Constant'
     */
    DP_B.Compare_is = (DP_B.DeadZone_o < DP_P.Constant_Value_n);

    /* RelationalOperator: '<S29>/Compare' */
    DP_B.Compare_p1 = (DP_B.DeadZone_o == 0.0);

    /* Gain: '<S18>/Gain' */
    DP_B.Gain_p = (uint16_T)(DP_P.Gain_Gain_f * DP_B.Compare_p1);

    /* RelationalOperator: '<S28>/Compare' incorporates:
     *  Constant: '<S28>/Constant'
     */
    DP_B.Compare_og = (DP_B.DeadZone_o > DP_P.Constant_Value_j);

    /* Gain: '<S18>/Gain1' */
    DP_B.Gain1_n = (uint16_T)(DP_P.Gain1_Gain_o * DP_B.Compare_og);

    /* Sum: '<S18>/Sum' */
    DP_B.Sum_ao = (uint16_T)(uint32_T)(((DP_B.Compare_is << 6) + DP_B.Gain_p) +
      DP_B.Gain1_n);

    /* Lookup Block: '<S18>/f_3 < 0'
     * About '<S18>/f_3 < 0 :'
     * Lookup Block: '<S18>/f_3 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_30), DP_P.f_30_YData, DP_B.Product_n[2],
                         DP_P.f_30_XData, 7U);

    /* Lookup Block: '<S18>/f_3 > 0'
     * About '<S18>/f_3 > 0 :'
     * Lookup Block: '<S18>/f_3 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_30_m), DP_P.f_30_YData_a, DP_B.Product_n[2],
                         DP_P.f_30_XData_h, 10U);

    /* MultiPortSwitch: '<S18>/Multiport Switch' incorporates:
     *  Constant: '<S18>/f_3 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)DP_B.Sum_ao >> 6)) {
     case 1:
      DP_B.MultiportSwitch_m = DP_B.f_30;
      break;

     case 2:
      DP_B.MultiportSwitch_m = DP_P.f_30_Value;
      break;

     default:
      DP_B.MultiportSwitch_m = DP_B.f_30_m;
      break;
    }

    /* DeadZone Block: '<S19>/Dead Zone'
     */
    if (DP_B.Product_n[3] >= DP_P.DeadZone_End_k) {
      DP_B.DeadZone_n = DP_B.Product_n[3] - DP_P.DeadZone_End_k;
    } else if (DP_B.Product_n[3] > DP_P.DeadZone_Start_a) {
      DP_B.DeadZone_n = 0.0;
    } else {
      DP_B.DeadZone_n = DP_B.Product_n[3] - DP_P.DeadZone_Start_a;
    }

    /* RelationalOperator: '<S30>/Compare' incorporates:
     *  Constant: '<S30>/Constant'
     */
    DP_B.Compare_j = (DP_B.DeadZone_n < DP_P.Constant_Value_h);

    /* RelationalOperator: '<S32>/Compare' */
    DP_B.Compare_jt = (DP_B.DeadZone_n == 0.0);

    /* Gain: '<S19>/Gain' */
    DP_B.Gain_h = (uint16_T)(DP_P.Gain_Gain_o * DP_B.Compare_jt);

    /* RelationalOperator: '<S31>/Compare' incorporates:
     *  Constant: '<S31>/Constant'
     */
    DP_B.Compare_g = (DP_B.DeadZone_n > DP_P.Constant_Value_ff);

    /* Gain: '<S19>/Gain1' */
    DP_B.Gain1_d = (uint16_T)(DP_P.Gain1_Gain_it * DP_B.Compare_g);

    /* Sum: '<S19>/Sum' */
    DP_B.Sum_l = (uint16_T)(uint32_T)(((DP_B.Compare_j << 6) + DP_B.Gain_h) +
      DP_B.Gain1_d);

    /* Lookup Block: '<S19>/f_4 < 0'
     * About '<S19>/f_4 < 0 :'
     * Lookup Block: '<S19>/f_4 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_40), DP_P.f_40_YData, DP_B.Product_n[3],
                         DP_P.f_40_XData, 9U);

    /* Lookup Block: '<S19>/f_4 > 0'
     * About '<S19>/f_4 > 0 :'
     * Lookup Block: '<S19>/f_4 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_40_l), DP_P.f_40_YData_g, DP_B.Product_n[3],
                         DP_P.f_40_XData_h, 6U);

    /* MultiPortSwitch: '<S19>/Multiport Switch' incorporates:
     *  Constant: '<S19>/f_4 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)DP_B.Sum_l >> 6)) {
     case 1:
      DP_B.MultiportSwitch_o = DP_B.f_40;
      break;

     case 2:
      DP_B.MultiportSwitch_o = DP_P.f_40_Value;
      break;

     default:
      DP_B.MultiportSwitch_o = DP_B.f_40_l;
      break;
    }

    /* DeadZone Block: '<S20>/Dead Zone'
     */
    if (DP_B.Product_n[4] >= DP_P.DeadZone_End_pv) {
      DP_B.DeadZone_d = DP_B.Product_n[4] - DP_P.DeadZone_End_pv;
    } else if (DP_B.Product_n[4] > DP_P.DeadZone_Start_i) {
      DP_B.DeadZone_d = 0.0;
    } else {
      DP_B.DeadZone_d = DP_B.Product_n[4] - DP_P.DeadZone_Start_i;
    }

    /* RelationalOperator: '<S33>/Compare' incorporates:
     *  Constant: '<S33>/Constant'
     */
    DP_B.Compare_b = (DP_B.DeadZone_d < DP_P.Constant_Value_ac);

    /* RelationalOperator: '<S35>/Compare' */
    DP_B.Compare_d = (DP_B.DeadZone_d == 0.0);

    /* Gain: '<S20>/Gain' */
    DP_B.Gain_m3 = (uint16_T)(DP_P.Gain_Gain_k * DP_B.Compare_d);

    /* RelationalOperator: '<S34>/Compare' incorporates:
     *  Constant: '<S34>/Constant'
     */
    DP_B.Compare_n = (DP_B.DeadZone_d > DP_P.Constant_Value_k);

    /* Gain: '<S20>/Gain1' */
    DP_B.Gain1_j = (uint16_T)(DP_P.Gain1_Gain_aq * DP_B.Compare_n);

    /* Sum: '<S20>/Sum' */
    DP_B.Sum_p = (uint16_T)(uint32_T)(((DP_B.Compare_b << 6) + DP_B.Gain_m3) +
      DP_B.Gain1_j);

    /* Lookup Block: '<S20>/f_5 < 0'
     * About '<S20>/f_5 < 0 :'
     * Lookup Block: '<S20>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_50), DP_P.f_50_YData, DP_B.Product_n[4],
                         DP_P.f_50_XData, 2U);

    /* Lookup Block: '<S20>/f_5 > 0'
     * About '<S20>/f_5 > 0 :'
     * Lookup Block: '<S20>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(DP_B.f_50_m), DP_P.f_50_YData_h, DP_B.Product_n[4],
                         DP_P.f_50_XData_k, 2U);

    /* MultiPortSwitch: '<S20>/Multiport Switch' incorporates:
     *  Constant: '<S20>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)DP_B.Sum_p >> 6)) {
     case 1:
      DP_B.MultiportSwitch_h = DP_B.f_50;
      break;

     case 2:
      DP_B.MultiportSwitch_h = DP_P.f_50_Value;
      break;

     default:
      DP_B.MultiportSwitch_h = DP_B.f_50_m;
      break;
    }

    /* Saturate: '<S6>/Saturation' */
    tmp_0[0] = DP_B.MultiportSwitch;
    tmp_0[1] = DP_B.MultiportSwitch_a;
    tmp_0[2] = DP_B.MultiportSwitch_m;
    tmp_0[3] = DP_B.MultiportSwitch_o;
    tmp_0[4] = DP_B.MultiportSwitch_h;
    for (i = 0; i < 5; i++) {
      DP_B.Saturation_a[i] = rt_SATURATE(tmp_0[i], DP_P.Saturation_LowerSat_d,
        DP_P.Saturation_UpperSat_c);
    }

    /* MultiPortSwitch: '<S1>/Thruster setting Switch' incorporates:
     *  Constant: '<S1>/Control Mode'
     *  Constant: '<S6>/BT_power_limit'
     *  Constant: '<S6>/VSP_speeds'
     *  Constant: '<S7>/PS3_BT_Power'
     *  Constant: '<S7>/PS3_VSP_Speed'
     */
    if ((int32_T)DP_P.ControlMode_Value == 0) {
      DP_B.ThrustersettingSwitch[0] = DP_B.u_1;
      DP_B.ThrustersettingSwitch[1] = DP_B.u_2;
      DP_B.ThrustersettingSwitch[2] = DP_B.u_3;
      DP_B.ThrustersettingSwitch[3] = DP_B.u_4;
      DP_B.ThrustersettingSwitch[4] = DP_B.u_5;
      DP_B.ThrustersettingSwitch[5] = DP_P.PS3_BT_Power_Value;
      DP_B.ThrustersettingSwitch[6] = DP_P.PS3_VSP_Speed_Value;
    } else {
      for (i = 0; i < 5; i++) {
        DP_B.ThrustersettingSwitch[i] = DP_B.Saturation_a[i];
      }

      DP_B.ThrustersettingSwitch[5] = DP_P.BT_power_limit_Value;
      DP_B.ThrustersettingSwitch[6] = DP_P.VSP_speeds_Value;
    }

    /* Saturate: '<S1>/Saturation' */
    for (i = 0; i < 7; i++) {
      tmp = DP_B.ThrustersettingSwitch[i];
      DP_B.Saturation_j[i] = rt_SATURATE(tmp, DP_P.Saturation_LowerSat_i,
        DP_P.Saturation_UpperSat_f);
    }

    if (rtmIsMajorTimeStep(DP_M)) {
      /* SignalConversion: '<Root>/TmpHiddenBufferAtTo FileInport1' incorporates:
       *  Constant: '<S1>/Control Mode'
       *  Constant: '<S4>/Controller Input Selector'
       */
      DP_B.TmpHiddenBufferAtToFileInport1[0] =
        DP_P.ControllerInputSelector_Value;
      DP_B.TmpHiddenBufferAtToFileInport1[1] = DP_B.QTMIn2Error;
      DP_B.TmpHiddenBufferAtToFileInport1[2] = DP_B.QTMIn9Residual;
      DP_B.TmpHiddenBufferAtToFileInport1[3] = DP_B.etadot_surge;
      DP_B.TmpHiddenBufferAtToFileInport1[4] = DP_B.etadot_sway;
      DP_B.TmpHiddenBufferAtToFileInport1[5] = DP_B.etadot_yaw;
      DP_B.TmpHiddenBufferAtToFileInport1[6] = DP_B.eta_surge;
      DP_B.TmpHiddenBufferAtToFileInport1[7] = DP_B.eta_sway;
      DP_B.TmpHiddenBufferAtToFileInport1[8] = DP_B.eta_yaw;
      DP_B.TmpHiddenBufferAtToFileInport1[9] = DP_B.nu_surge;
      DP_B.TmpHiddenBufferAtToFileInport1[10] = DP_B.nu_sway;
      DP_B.TmpHiddenBufferAtToFileInport1[11] = DP_B.nu_yaw;
      DP_B.TmpHiddenBufferAtToFileInport1[12] = DP_B.eta_dDPN;
      DP_B.TmpHiddenBufferAtToFileInport1[13] = DP_B.eta_dDPE;
      DP_B.TmpHiddenBufferAtToFileInport1[14] = DP_B.eta_dDPPsi;
      DP_B.TmpHiddenBufferAtToFileInport1[15] = DP_P.ControlMode_Value;
      for (i = 0; i < 7; i++) {
        DP_B.TmpHiddenBufferAtToFileInport1[i + 16] = DP_B.Saturation_j[i];
      }

      DP_B.TmpHiddenBufferAtToFileInport1[23] = DP_B.Sum1_d[0];
      DP_B.TmpHiddenBufferAtToFileInport1[24] = DP_B.Sum1_d[1];
      DP_B.TmpHiddenBufferAtToFileInport1[25] = DP_B.Sum1_d[2];

      /* ToFile Block: '<Root>/To File'
       */
      if (rtmIsMajorTimeStep(DP_M)) {
        if (!(++DP_DWork.ToFile_IWORK.Decimation % 1) &&
            (DP_DWork.ToFile_IWORK.Count*27)+1 < 100000000 ) {
          real_T u[27];
          FILE *fp = (FILE *) DP_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            DP_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = DP_M->Timing.t[1];
            u[1] = DP_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = DP_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = DP_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = DP_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = DP_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = DP_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = DP_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = DP_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = DP_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = DP_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = DP_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = DP_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = DP_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = DP_B.TmpHiddenBufferAtToFileInport1[13];
            u[15] = DP_B.TmpHiddenBufferAtToFileInport1[14];
            u[16] = DP_B.TmpHiddenBufferAtToFileInport1[15];
            u[17] = DP_B.TmpHiddenBufferAtToFileInport1[16];
            u[18] = DP_B.TmpHiddenBufferAtToFileInport1[17];
            u[19] = DP_B.TmpHiddenBufferAtToFileInport1[18];
            u[20] = DP_B.TmpHiddenBufferAtToFileInport1[19];
            u[21] = DP_B.TmpHiddenBufferAtToFileInport1[20];
            u[22] = DP_B.TmpHiddenBufferAtToFileInport1[21];
            u[23] = DP_B.TmpHiddenBufferAtToFileInport1[22];
            u[24] = DP_B.TmpHiddenBufferAtToFileInport1[23];
            u[25] = DP_B.TmpHiddenBufferAtToFileInport1[24];
            u[26] = DP_B.TmpHiddenBufferAtToFileInport1[25];
            if (fwrite(u, sizeof(real_T), 27, fp) != 27) {
              rtmSetErrorStatus(DP_M,
                                "Error writing to MAT-file CSE1_DP_data.mat");
              return;
            }

            if (((++DP_DWork.ToFile_IWORK.Count)*27)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file CSE1_DP_data.mat.\n");
            }
          }
        }
      }

      /* Gain: '<S3>/Battery Bow Thruster' */
      DP_B.BatteryBowThruster = DP_P.BatteryBowThruster_Gain * DP_B.SITzAI0;

      /* Gain: '<S3>/Battery Servo' */
      DP_B.BatteryServo = DP_P.BatteryServo_Gain * DP_B.SITzAI1;

      /* Gain: '<S3>/Battery Main' */
      DP_B.BatteryMain = DP_P.BatteryMain_Gain * DP_B.SITzAI2;
    }

    /* Gain: '<S40>/QTM In1 FPS' */
    DP_B.QTMIn1FPS = DP_P.QTMIn1FPS_Gain * DP_B.QTMIn[0];

    /* Saturate: '<S44>/Saturation' */
    tmp = DP_B.Sum1_d[0];
    DP_B.Saturation_l = rt_SATURATE(tmp, DP_P.Saturation_LowerSat_j,
      DP_P.Saturation_UpperSat_e);

    /* Saturate: '<S44>/Saturation1' */
    tmp = DP_B.Sum1_d[1];
    DP_B.Saturation1 = rt_SATURATE(tmp, DP_P.Saturation1_LowerSat,
      DP_P.Saturation1_UpperSat);

    /* Saturate: '<S44>/Saturation2' */
    tmp = DP_B.Sum1_d[2];
    DP_B.Saturation2 = rt_SATURATE(tmp, DP_P.Saturation2_LowerSat,
      DP_P.Saturation2_UpperSat);

    /* Gain: '<S44>/plant tau_surge' */
    DP_B.planttau_surge = DP_P.planttau_surge_Gain * DP_B.Saturation_l;

    /* Gain: '<S44>/plant tau_sway' */
    DP_B.planttau_sway = DP_P.planttau_sway_Gain * DP_B.Saturation1;

    /* Gain: '<S44>/plant tau_yaw' */
    DP_B.planttau_yaw = DP_P.planttau_yaw_Gain * DP_B.Saturation2;

    /* Gain: '<S5>/plant u_1' */
    DP_B.plantu_1 = DP_P.plantu_1_Gain * DP_B.Saturation_j[0];

    /* Gain: '<S5>/plant u_2' */
    DP_B.plantu_2 = DP_P.plantu_2_Gain * DP_B.Saturation_j[1];

    /* Gain: '<S5>/plant u_3' */
    DP_B.plantu_3 = DP_P.plantu_3_Gain * DP_B.Saturation_j[2];

    /* Gain: '<S5>/plant u_4' */
    DP_B.plantu_4 = DP_P.plantu_4_Gain * DP_B.Saturation_j[3];

    /* Gain: '<S5>/plant u_5' */
    DP_B.plantu_5 = DP_P.plantu_5_Gain * DP_B.Saturation_j[4];

    /* Gain: '<S5>/plant BT power' */
    DP_B.plantBTpower = DP_P.plantBTpower_Gain * DP_B.Saturation_j[5];

    /* Gain: '<S5>/plant VSP speed' */
    DP_B.plantVSPspeed = DP_P.plantVSPspeed_Gain * DP_B.Saturation_j[6];

    /* Outputs for enable SubSystem: '<S5>/CSE1' incorporates:
     *  Constant: '<S5>/Enable CSE1'
     *  EnablePort: '<S42>/Enable'
     */
    if (rtmIsMajorTimeStep(DP_M) && rtmIsMajorTimeStep(DP_M)) {
      if (DP_P.EnableCSE1_Value > 0.0) {
        if (DP_DWork.CSE1_MODE == SUBSYS_DISABLED) {
          DP_DWork.CSE1_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (DP_DWork.CSE1_MODE == SUBSYS_ENABLED) {
          DP_DWork.CSE1_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (DP_DWork.CSE1_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S45>/BT_D_Gain1' */
      DP_B.BT_D_Gain1 = DP_P.BT_D_Gain1_Gain * DP_B.plantu_5;

      /* Gain: '<S45>/BT_D_Gain2' */
      DP_B.BT_D_Gain2 = DP_P.BT_D_Gain2_Gain * DP_B.plantu_5;

      /* Sum: '<S45>/Add' incorporates:
       *  Constant: '<S45>/BT_Power_Offset1'
       */
      DP_B.Add = (DP_B.BT_D_Gain1 + DP_P.BT_Power_Offset1_Value) +
        DP_B.BT_D_Gain2;

      /* Gain: '<S45>/BT_L_Gain1' */
      DP_B.BT_L_Gain1 = DP_P.BT_L_Gain1_Gain * DP_B.plantBTpower;

      /* Gain: '<S45>/BT_L_Gain2' */
      DP_B.BT_L_Gain2 = DP_P.BT_L_Gain2_Gain * DP_B.plantBTpower;

      /* Gain: '<S45>/Neg' */
      DP_B.Neg = DP_P.Neg_Gain * DP_B.plantBTpower;
      if (rtmIsMajorTimeStep(DP_M)) {
      }

      /* Sum: '<S45>/Sum1' incorporates:
       *  Constant: '<S45>/BT_Power_Offset2'
       */
      DP_B.Sum1_h = DP_B.BT_L_Gain1 + DP_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S47>/LowerRelop1' */
      DP_B.LowerRelop1 = (DP_B.Add > DP_B.Sum1_h);

      /* Sum: '<S45>/Sum2' incorporates:
       *  Constant: '<S45>/BT_Power_Offset3'
       */
      DP_B.Sum2 = DP_B.BT_L_Gain2 + DP_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S47>/UpperRelop' */
      DP_B.UpperRelop = (DP_B.Add < DP_B.Sum2);

      /* Switch: '<S47>/Switch' */
      if (DP_B.UpperRelop) {
        DP_B.Switch = DP_B.Sum2;
      } else {
        DP_B.Switch = DP_B.Add;
      }

      /* Switch: '<S47>/Switch2' */
      if (DP_B.LowerRelop1) {
        DP_B.Switch2 = DP_B.Sum1_h;
      } else {
        DP_B.Switch2 = DP_B.Switch;
      }

      if (rtmIsMajorTimeStep(DP_M)) {
      }

      /* RelationalOperator: '<S48>/LowerRelop1' incorporates:
       *  Constant: '<S45>/Constant'
       */
      DP_B.LowerRelop1_b = (DP_B.plantu_5 > DP_P.Constant_Value_m);

      /* RelationalOperator: '<S48>/UpperRelop' */
      DP_B.UpperRelop_b = (DP_B.plantu_5 < DP_B.Neg);

      /* Switch: '<S48>/Switch' */
      if (DP_B.UpperRelop_b) {
        DP_B.Switch_j = DP_B.Neg;
      } else {
        DP_B.Switch_j = DP_B.plantu_5;
      }

      /* Switch: '<S48>/Switch2' incorporates:
       *  Constant: '<S45>/Constant'
       */
      if (DP_B.LowerRelop1_b) {
        DP_B.Switch2_m = DP_P.Constant_Value_m;
      } else {
        DP_B.Switch2_m = DP_B.Switch_j;
      }

      if (rtmIsMajorTimeStep(DP_M)) {
      }

      /* RelationalOperator: '<S49>/LowerRelop1' */
      DP_B.LowerRelop1_bd = (DP_B.plantu_5 > DP_B.plantBTpower);

      /* RelationalOperator: '<S49>/UpperRelop' incorporates:
       *  Constant: '<S45>/Constant1'
       */
      DP_B.UpperRelop_h = (DP_B.plantu_5 < DP_P.Constant1_Value_j);

      /* Switch: '<S49>/Switch' incorporates:
       *  Constant: '<S45>/Constant1'
       */
      if (DP_B.UpperRelop_h) {
        DP_B.Switch_h = DP_P.Constant1_Value_j;
      } else {
        DP_B.Switch_h = DP_B.plantu_5;
      }

      /* Switch: '<S49>/Switch2' */
      if (DP_B.LowerRelop1_bd) {
        DP_B.Switch2_a = DP_B.plantBTpower;
      } else {
        DP_B.Switch2_a = DP_B.Switch_h;
      }

      /* Signum: '<S46>/Sign' */
      DP_B.Sign_a = rt_SIGNd_snf(DP_B.plantVSPspeed);

      /* Product: '<S46>/Product1' */
      DP_B.PortVPS_X = DP_B.plantu_2 * DP_B.Sign_a;

      /* Gain: '<S46>/-x' */
      DP_B.PortVPS_X_p = DP_P.x_Gain * DP_B.PortVPS_X;

      /* Product: '<S46>/Product2' */
      DP_B.PortVSP_Y = DP_B.plantu_1 * DP_B.Sign_a;

      /* Gain: '<S46>/-y' */
      DP_B.PortVSP_Y_d = DP_P.y_Gain * DP_B.PortVSP_Y;

      /* Product: '<S46>/Product3' */
      DP_B.StarboardVSP_X = DP_B.plantu_4 * DP_B.Sign_a;

      /* Product: '<S46>/Product4' */
      DP_B.StarboardVSP_Y = DP_B.plantu_3 * DP_B.Sign_a;

      /* Lookup2D: '<S46>/Servo1' */
      DP_B.Servo1 = rt_Lookup2D_Normal((const real_T *)(&DP_P.Servo1_RowIdx[0]),
        3, (const real_T *)(&DP_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&DP_P.Servo1_Table[0]), (const real_T)DP_B.PortVPS_X_p, (const real_T)
        DP_B.PortVSP_Y_d);

      /* Lookup2D: '<S46>/Servo2' */
      DP_B.Servo2 = rt_Lookup2D_Normal((const real_T *)(&DP_P.Servo2_RowIdx[0]),
        3, (const real_T *)(&DP_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&DP_P.Servo2_Table[0]), (const real_T)DP_B.PortVPS_X_p, (const real_T)
        DP_B.PortVSP_Y_d);

      /* Lookup2D: '<S46>/Servo3' */
      DP_B.Servo3 = rt_Lookup2D_Normal((const real_T *)(&DP_P.Servo3_RowIdx[0]),
        3, (const real_T *)(&DP_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&DP_P.Servo3_Table[0]), (const real_T)DP_B.StarboardVSP_X, (const
        real_T)DP_B.StarboardVSP_Y);

      /* Lookup2D: '<S46>/Servo4' */
      DP_B.Servo4 = rt_Lookup2D_Normal((const real_T *)(&DP_P.Servo4_RowIdx[0]),
        3, (const real_T *)(&DP_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&DP_P.Servo4_Table[0]), (const real_T)DP_B.StarboardVSP_X, (const
        real_T)DP_B.StarboardVSP_Y);

      /* Gain: '<S46>/VPS_Speed_Gain' */
      DP_B.VPS_Speed_Gain = DP_P.VPS_Speed_Gain_Gain * DP_B.plantVSPspeed;

      /* Sum: '<S46>/Sum' incorporates:
       *  Constant: '<S46>/VPS_Power_Offset'
       */
      DP_B.Sum_n = DP_B.VPS_Speed_Gain + DP_P.VPS_Power_Offset_Value;

      /* Gain: '<S46>/VSPS Port' */
      DP_B.VSPSPort = DP_P.VSPSPort_Gain * DP_B.Sum_n;

      /* Gain: '<S46>/VSPS Starboard' */
      DP_B.VSPSStarboard = DP_P.VSPSStarboard_Gain * DP_B.Sum_n;
    }

    /* end of Outputs for SubSystem: '<S5>/CSE1' */
    if (rtmIsMajorTimeStep(DP_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void DP_update(int_T tid)
{
  {
    int32_T tmp;

    /* Derivative Block: '<S40>/Derivative1' */
    {
      real_T timeStampA = DP_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = DP_DWork.Derivative1_RWORK.TimeStampB;
      real_T *lastBank = &DP_DWork.Derivative1_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 4;
        } else if (timeStampA >= timeStampB) {
          lastBank += 4;
        }
      }

      *lastBank++ = DP_M->Timing.t[0];
      *lastBank++ = DP_B.mm2mx;
      *lastBank++ = DP_B.mm2my;
      *lastBank++ = DP_B.d2ryaw;
    }

    /* Update for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S43>/Enable'
     */
    if (DP_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Sum: '<S50>/Sum' */
      DP_B.Sum_k[0] = DP_B.planttau_surge - DP_B.Product1[0];
      DP_B.Sum_k[1] = DP_B.planttau_sway - DP_B.Product1[1];
      DP_B.Sum_k[2] = DP_B.planttau_yaw - DP_B.Product1[2];

      /* Product: '<S50>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        DP_B.Product2[tmp] = 0.0;
        DP_B.Product2[tmp] = DP_B.Inverse[tmp] * DP_B.Sum_k[0] +
          DP_B.Product2[tmp];
        DP_B.Product2[tmp] = DP_B.Inverse[tmp + 3] * DP_B.Sum_k[1] +
          DP_B.Product2[tmp];
        DP_B.Product2[tmp] = DP_B.Inverse[tmp + 6] * DP_B.Sum_k[2] +
          DP_B.Product2[tmp];
      }
    }

    /* end of Update for SubSystem: '<S5>/Linear Simulator' */

    /* Derivative Block: '<S40>/Derivative' */
    {
      real_T timeStampA = DP_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = DP_DWork.Derivative_RWORK.TimeStampB;
      real_T *lastBank = &DP_DWork.Derivative_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = DP_M->Timing.t[0];
      *lastBank++ = DP_B.mm2mx;
      *lastBank++ = DP_B.mm2my;
      *lastBank++ = DP_B.mm2mz;
      *lastBank++ = DP_B.d2rroll;
      *lastBank++ = DP_B.d2rpitch;
      *lastBank++ = DP_B.d2ryaw;
    }

    if (rtmIsMajorTimeStep(DP_M)) {
    }
  }

  if (rtmIsMajorTimeStep(DP_M)) {
    rt_ertODEUpdateContinuousStates(&DP_M->solverInfo);
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
  if (!(++DP_M->Timing.clockTick0))
    ++DP_M->Timing.clockTickH0;
  DP_M->Timing.t[0] = DP_M->Timing.clockTick0 * DP_M->Timing.stepSize0 +
    DP_M->Timing.clockTickH0 * DP_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(DP_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++DP_M->Timing.clockTick1))
      ++DP_M->Timing.clockTickH1;
    DP_M->Timing.t[1] = DP_M->Timing.clockTick1 * DP_M->Timing.stepSize1 +
      DP_M->Timing.clockTickH1 * DP_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void DP_derivatives(void)
{
  {
    int32_T tmp;

    /* Derivatives for enable SubSystem: '<S5>/Linear Simulator' */
    if (DP_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Sum: '<S50>/Sum' */
      DP_B.Sum_k[0] = DP_B.planttau_surge - DP_B.Product1[0];
      DP_B.Sum_k[1] = DP_B.planttau_sway - DP_B.Product1[1];
      DP_B.Sum_k[2] = DP_B.planttau_yaw - DP_B.Product1[2];

      /* Product: '<S50>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        DP_B.Product2[tmp] = 0.0;
        DP_B.Product2[tmp] = DP_B.Inverse[tmp] * DP_B.Sum_k[0] +
          DP_B.Product2[tmp];
        DP_B.Product2[tmp] = DP_B.Inverse[tmp + 3] * DP_B.Sum_k[1] +
          DP_B.Product2[tmp];
        DP_B.Product2[tmp] = DP_B.Inverse[tmp + 6] * DP_B.Sum_k[2] +
          DP_B.Product2[tmp];
      }

      /* Integrator Block: '<S50>/Integrator' */
      {
        if (DP_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE_n
            [0] = DP_B.Product2[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE_n
            [0] = 0.0;
        }

        if (DP_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE_n
            [1] = DP_B.Product2[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE_n
            [1] = 0.0;
        }

        if (DP_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE_n
            [2] = DP_B.Product2[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE_n
            [2] = 0.0;
        }
      }

      /* Integrator Block: '<S50>/Integrator1' */
      {
        if (DP_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator1_CSTATE[0]
            = DP_B.Product3[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator1_CSTATE[0]
            = 0.0;
        }

        if (DP_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator1_CSTATE[1]
            = DP_B.Product3[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator1_CSTATE[1]
            = 0.0;
        }

        if (DP_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator1_CSTATE[2]
            = DP_B.Product3[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator1_CSTATE[2]
            = 0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_DP *) DP_M->ModelData.derivs)
               ->Integrator_CSTATE_n[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S5>/Linear Simulator' */

    /* Integrator Block: '<S9>/Integrator' */
    {
      if (DP_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE[0] =
          DP_B.TmpHiddenBufferAtKpInport1[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE[0] =
          0.0;
      }

      if (DP_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE[1] =
          DP_B.TmpHiddenBufferAtKpInport1[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE[1] =
          0.0;
      }

      if (DP_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE[2] =
          DP_B.TmpHiddenBufferAtKpInport1[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_DP *) DP_M->ModelData.derivs)->Integrator_CSTATE[2] =
          0.0;
      }
    }
  }
}

/* Model initialize function */
void DP_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)DP_M,0,
                sizeof(RT_MODEL_DP));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&DP_M->solverInfo, &DP_M->Timing.simTimeStep);
    rtsiSetTPtr(&DP_M->solverInfo, &rtmGetTPtr(DP_M));
    rtsiSetStepSizePtr(&DP_M->solverInfo, &DP_M->Timing.stepSize0);
    rtsiSetdXPtr(&DP_M->solverInfo, &DP_M->ModelData.derivs);
    rtsiSetContStatesPtr(&DP_M->solverInfo, &DP_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&DP_M->solverInfo, &DP_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&DP_M->solverInfo, (&rtmGetErrorStatus(DP_M)));
    rtsiSetRTModelPtr(&DP_M->solverInfo, DP_M);
  }

  rtsiSetSimTimeStep(&DP_M->solverInfo, MAJOR_TIME_STEP);
  DP_M->ModelData.intgData.y = DP_M->ModelData.odeY;
  DP_M->ModelData.intgData.f[0] = DP_M->ModelData.odeF[0];
  DP_M->ModelData.intgData.f[1] = DP_M->ModelData.odeF[1];
  DP_M->ModelData.intgData.f[2] = DP_M->ModelData.odeF[2];
  DP_M->ModelData.intgData.f[3] = DP_M->ModelData.odeF[3];
  DP_M->ModelData.intgData.f[4] = DP_M->ModelData.odeF[4];
  DP_M->ModelData.intgData.f[5] = DP_M->ModelData.odeF[5];
  DP_M->ModelData.contStates = ((real_T *) &DP_X);
  rtsiSetSolverData(&DP_M->solverInfo, (void *)&DP_M->ModelData.intgData);
  rtsiSetSolverName(&DP_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = DP_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    DP_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    DP_M->Timing.sampleTimes = (&DP_M->Timing.sampleTimesArray[0]);
    DP_M->Timing.offsetTimes = (&DP_M->Timing.offsetTimesArray[0]);

    /* task periods */
    DP_M->Timing.sampleTimes[0] = (0.0);
    DP_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    DP_M->Timing.offsetTimes[0] = (0.0);
    DP_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(DP_M, &DP_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = DP_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    DP_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(DP_M, -1);
  DP_M->Timing.stepSize0 = 0.1;
  DP_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(DP_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    DP_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(DP_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(DP_M->rtwLogInfo, (NULL));
    rtliSetLogT(DP_M->rtwLogInfo, "");
    rtliSetLogX(DP_M->rtwLogInfo, "");
    rtliSetLogXFinal(DP_M->rtwLogInfo, "");
    rtliSetSigLog(DP_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(DP_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(DP_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(DP_M->rtwLogInfo, 0);
    rtliSetLogDecimation(DP_M->rtwLogInfo, 1);
    rtliSetLogY(DP_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(DP_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(DP_M->rtwLogInfo, (NULL));
  }

  DP_M->solverInfoPtr = (&DP_M->solverInfo);
  DP_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&DP_M->solverInfo, 0.1);
  rtsiSetSolverMode(&DP_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  DP_M->ModelData.blockIO = ((void *) &DP_B);
  (void) memset(((void *) &DP_B),0,
                sizeof(BlockIO_DP));

  /* parameters */
  DP_M->ModelData.defaultParam = ((real_T *) &DP_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &DP_X;
    DP_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_DP));
  }

  /* states (dwork) */
  DP_M->Work.dwork = ((void *) &DP_DWork);
  (void) memset((void *)&DP_DWork, 0,
                sizeof(D_Work_DP));
  DP_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  DP_PrevZCSigState.Integrator_Reset_ZCE_e = UNINITIALIZED_ZCSIG;
  DP_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void DP_terminate(void)
{
  /* ToFile Block: '<Root>/To File' */
  {
    FILE *fp = (FILE *) DP_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_DP_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(DP_M, "Error closing MAT-file CSE1_DP_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(DP_M, "Error reopening MAT-file CSE1_DP_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 27, DP_DWork.ToFile_IWORK.Count,
           "cse1_DP_data")) {
        rtmSetErrorStatus(DP_M,
                          "Error writing header for cse1_DP_data to MAT-file CSE1_DP_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(DP_M, "Error closing MAT-file CSE1_DP_data.mat");
        return;
      }

      DP_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  DP_output(tid);
}

void MdlUpdate(int_T tid)
{
  DP_update(tid);
}

void MdlInitializeSizes(void)
{
  DP_M->Sizes.numContStates = (9);     /* Number of continuous states */
  DP_M->Sizes.numY = (0);              /* Number of model outputs */
  DP_M->Sizes.numU = (0);              /* Number of model inputs */
  DP_M->Sizes.sysDirFeedThru = (0);    /* The model is not direct feedthrough */
  DP_M->Sizes.numSampTimes = (2);      /* Number of sample times */
  DP_M->Sizes.numBlocks = (352);       /* Number of blocks */
  DP_M->Sizes.numBlockIO = (246);      /* Number of block outputs */
  DP_M->Sizes.numBlockPrms = (540);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* Derivative Block: '<S40>/Derivative1' */
  DP_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  DP_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* Derivative Block: '<S40>/Derivative' */
  DP_DWork.Derivative_RWORK.TimeStampA = rtInf;
  DP_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* Integrator Block: '<S9>/Integrator' */
  DP_X.Integrator_CSTATE[0] = DP_P.Integrator_IC;
  DP_X.Integrator_CSTATE[1] = DP_P.Integrator_IC;
  DP_X.Integrator_CSTATE[2] = DP_P.Integrator_IC;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(DP_M)) {
    rtmSetFirstInitCond(DP_M, 0);
  }
}

void MdlStart(void)
{
  /* Start for enable SubSystem: '<S5>/Linear Simulator' */
  DP_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

  /* Start for Constant: '<S52>/psi_0' */
  DP_B.psi_0 = DP_P.psi_0_Value;

  /* Start for Constant: '<S52>/x_0' */
  DP_B.x_0 = DP_P.x_0_Value;

  /* Start for Constant: '<S52>/y_0' */
  DP_B.y_0 = DP_P.y_0_Value;

  /* Start for Constant: '<S53>/r_0' */
  DP_B.r_0 = DP_P.r_0_Value;

  /* Start for Constant: '<S53>/u_0' */
  DP_B.u_0 = DP_P.u_0_Value;

  /* Start for Constant: '<S53>/v_0' */
  DP_B.v_0 = DP_P.v_0_Value;

  /* Create Identity Matrix for Block: '<S54>/Inverse' */
  {
    int_T i;
    real_T *dWork = &DP_DWork.Inverse_DWORK4[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &DP_DWork.Inverse_DWORK4[0];
    while (dWork < &DP_DWork.Inverse_DWORK4[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  /* Integrator Block: '<S50>/Integrator' */
  if (rtmIsFirstInitCond(DP_M)) {
    DP_X.Integrator_CSTATE_n[0] = 0.0;
    DP_X.Integrator_CSTATE_n[1] = 0.0;
    DP_X.Integrator_CSTATE_n[2] = 0.0;
  }

  DP_DWork.Integrator_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S50>/Integrator1' */
  if (rtmIsFirstInitCond(DP_M)) {
    DP_X.Integrator1_CSTATE[0] = 0.0;
    DP_X.Integrator1_CSTATE[1] = 0.0;
    DP_X.Integrator1_CSTATE[2] = 0.0;
  }

  DP_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

  /* end of Start for SubSystem: '<S5>/Linear Simulator' */

  /* ToFile Block: '<Root>/To File' */
  {
    const char *fileName = "CSE1_DP_data.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(DP_M, "Error creating .mat file CSE1_DP_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,27,0,"cse1_DP_data")) {
      rtmSetErrorStatus(DP_M,
                        "Error writing mat file header to file CSE1_DP_data.mat");
      return;
    }

    DP_DWork.ToFile_IWORK.Count = 0;
    DP_DWork.ToFile_IWORK.Decimation = -1;
    DP_DWork.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for enable SubSystem: '<S5>/CSE1' */
  DP_DWork.CSE1_MODE = SUBSYS_DISABLED;

  /* end of Start for SubSystem: '<S5>/CSE1' */
  MdlInitialize();
}

RT_MODEL_DP *DP(void)
{
  DP_initialize(1);
  return DP_M;
}

void MdlTerminate(void)
{
  DP_terminate();
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
#ifdef NI_ROOTMODEL_DP
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
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 39:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 40:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,10,Complex);

   case 41:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,11,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 53:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 59:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 39:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 40:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,10,Complex);

   case 41:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,11,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 53:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 59:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern DP_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Naviagation Systems/Qualisys 6 DOF/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(DP_B.QTMIn, count, data[index++], 33, 0);
    }
  } else {
    index += 9;
  }

  // HMI/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&DP_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&DP_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // HMI/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&DP_B.SITzAI2, 0, data[index++], 0, 0);
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
    ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Switch2,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.VSPSStarboard,0,0,0);
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
  ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Switch2,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Servo1,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Servo2,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Servo3,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.Servo4,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.VSPSPort,0,0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&DP_B.VSPSStarboard,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "dp/Naviagation Systems/Controller Input Selector/Value", offsetof
    (Parameters_DP, ControllerInputSelector_Value), 30, 1, 2, 0, "", 0 },

  { 1, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain", offsetof
    (Parameters_DP, QTMIn2Error_Gain), 30, 1, 2, 2, "", 0 },

  { 2, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain", offsetof
    (Parameters_DP, QTMIn9Residual_Gain), 30, 1, 2, 4, "", 0 },

  { 3, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain", offsetof
    (Parameters_DP, QTMIn3_Gain), 30, 1, 2, 6, "", 0 },

  { 4, "dp/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain", offsetof
    (Parameters_DP, mm2mx_Gain), 30, 1, 2, 8, "", 0 },

  { 5, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain", offsetof
    (Parameters_DP, QTMIn4_Gain), 30, 1, 2, 10, "", 0 },

  { 6, "dp/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain", offsetof
    (Parameters_DP, mm2my_Gain), 30, 1, 2, 12, "", 0 },

  { 7, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain", offsetof
    (Parameters_DP, QTMIn6_Gain), 30, 1, 2, 14, "", 0 },

  { 8, "dp/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain", offsetof
    (Parameters_DP, d2ryaw_Gain), 30, 1, 2, 16, "", 0 },

  { 9, "dp/Plants/Enable Linear Simulator/Value", offsetof(Parameters_DP,
    EnableLinearSimulator_Value), 30, 1, 2, 18, "", 0 },

  { 10, "dp/Naviagation Systems/etadot_surge/Gain", offsetof(Parameters_DP,
    etadot_surge_Gain), 30, 1, 2, 20, "", 0 },

  { 11, "dp/Naviagation Systems/etadot_sway/Gain", offsetof(Parameters_DP,
    etadot_sway_Gain), 30, 1, 2, 22, "", 0 },

  { 12, "dp/Naviagation Systems/etadot_yaw/Gain", offsetof(Parameters_DP,
    etadot_yaw_Gain), 30, 1, 2, 24, "", 0 },

  { 13, "dp/Naviagation Systems/eta_surge/Gain", offsetof(Parameters_DP,
    eta_surge_Gain), 30, 1, 2, 26, "", 0 },

  { 14, "dp/Naviagation Systems/eta_sway/Gain", offsetof(Parameters_DP,
    eta_sway_Gain), 30, 1, 2, 28, "", 0 },

  { 15, "dp/Naviagation Systems/eta_yaw/Gain", offsetof(Parameters_DP,
    eta_yaw_Gain), 30, 1, 2, 30, "", 0 },

  { 16, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain", offsetof
    (Parameters_DP, QTMIn8_Gain), 30, 1, 2, 32, "", 0 },

  { 17, "dp/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain", offsetof
    (Parameters_DP, d2rroll_Gain), 30, 1, 2, 34, "", 0 },

  { 18, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain", offsetof
    (Parameters_DP, QTMIn7_Gain), 30, 1, 2, 36, "", 0 },

  { 19, "dp/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain", offsetof
    (Parameters_DP, d2rpitch_Gain), 30, 1, 2, 38, "", 0 },

  { 20, "dp/Naviagation Systems/Qualisys 6 DOF/Constant1/Value", offsetof
    (Parameters_DP, Constant1_Value), 32, 9, 2, 40, "", 0 },

  { 21, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain", offsetof
    (Parameters_DP, QTMIn5_Gain), 30, 1, 2, 42, "", 0 },

  { 22, "dp/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain", offsetof
    (Parameters_DP, mm2mz_Gain), 30, 1, 2, 44, "", 0 },

  { 23, "dp/Naviagation Systems/nu_surge/Gain", offsetof(Parameters_DP,
    nu_surge_Gain), 30, 1, 2, 46, "", 0 },

  { 24, "dp/Naviagation Systems/nu_sway/Gain", offsetof(Parameters_DP,
    nu_sway_Gain), 30, 1, 2, 48, "", 0 },

  { 25, "dp/Naviagation Systems/nu_yaw/Gain", offsetof(Parameters_DP,
    nu_yaw_Gain), 30, 1, 2, 50, "", 0 },

  { 26, "dp/HMI/DP Input/x_d/Value", offsetof(Parameters_DP, x_d_Value), 30, 1,
    2, 52, "", 0 },

  { 27, "dp/Guidance Systems/DP/eta_d DP N/Gain", offsetof(Parameters_DP,
    eta_dDPN_Gain), 30, 1, 2, 54, "", 0 },

  { 28, "dp/HMI/DP Input/y_d/Value", offsetof(Parameters_DP, y_d_Value), 30, 1,
    2, 56, "", 0 },

  { 29, "dp/Guidance Systems/DP/eta_d DP E/Gain", offsetof(Parameters_DP,
    eta_dDPE_Gain), 30, 1, 2, 58, "", 0 },

  { 30, "dp/HMI/DP Input/psi_d/Value", offsetof(Parameters_DP, psi_d_Value), 30,
    1, 2, 60, "", 0 },

  { 31, "dp/HMI/DP Input/Degrees to Radians/Gain1/Gain", offsetof(Parameters_DP,
    Gain1_Gain), 30, 1, 2, 62, "", 0 },

  { 32, "dp/Guidance Systems/DP/eta_d DP Psi/Gain", offsetof(Parameters_DP,
    eta_dDPPsi_Gain), 30, 1, 2, 64, "", 0 },

  { 33, "dp/Control Systems/Control Mode/Value", offsetof(Parameters_DP,
    ControlMode_Value), 30, 1, 2, 66, "", 0 },

  { 34, "dp/Control Systems/PS3 input/AS_LY/Value", offsetof(Parameters_DP,
    AS_LY_Value), 30, 1, 2, 68, "", 0 },

  { 35, "dp/Control Systems/PS3 input/ScalingLY/Gain", offsetof(Parameters_DP,
    ScalingLY_Gain), 30, 1, 2, 70, "", 0 },

  { 36, "dp/Control Systems/PS3 u input control/PS3 u_1/Gain", offsetof
    (Parameters_DP, PS3u_1_Gain), 30, 1, 2, 72, "", 0 },

  { 37, "dp/Control Systems/PS3 input/AS_LX/Value", offsetof(Parameters_DP,
    AS_LX_Value), 30, 1, 2, 74, "", 0 },

  { 38, "dp/Control Systems/PS3 input/ScalingLX/Gain", offsetof(Parameters_DP,
    ScalingLX_Gain), 30, 1, 2, 76, "", 0 },

  { 39, "dp/Control Systems/PS3 u input control/PS3 u_2/Gain", offsetof
    (Parameters_DP, PS3u_2_Gain), 30, 1, 2, 78, "", 0 },

  { 40, "dp/Control Systems/PS3 input/AS_RY/Value", offsetof(Parameters_DP,
    AS_RY_Value), 30, 1, 2, 80, "", 0 },

  { 41, "dp/Control Systems/PS3 input/ScalingRY/Gain", offsetof(Parameters_DP,
    ScalingRY_Gain), 30, 1, 2, 82, "", 0 },

  { 42, "dp/Control Systems/PS3 u input control/PS3 u_3/Gain", offsetof
    (Parameters_DP, PS3u_3_Gain), 30, 1, 2, 84, "", 0 },

  { 43, "dp/Control Systems/PS3 input/AS_RX/Value", offsetof(Parameters_DP,
    AS_RX_Value), 30, 1, 2, 86, "", 0 },

  { 44, "dp/Control Systems/PS3 input/Scaling_RX/Gain", offsetof(Parameters_DP,
    Scaling_RX_Gain), 30, 1, 2, 88, "", 0 },

  { 45, "dp/Control Systems/PS3 u input control/PS3 u_4/Gain", offsetof
    (Parameters_DP, PS3u_4_Gain), 30, 1, 2, 90, "", 0 },

  { 46, "dp/Control Systems/PS3 input/L2/Value", offsetof(Parameters_DP,
    L2_Value), 30, 1, 2, 92, "", 0 },

  { 47, "dp/Control Systems/PS3 input/R2/Value", offsetof(Parameters_DP,
    R2_Value), 30, 1, 2, 94, "", 0 },

  { 48, "dp/Control Systems/PS3 u input control/PS3 u_5/Gain", offsetof
    (Parameters_DP, PS3u_5_Gain), 30, 1, 2, 96, "", 0 },

  { 49, "dp/Control Systems/PS3 input/PS3_BT_Power/Value", offsetof
    (Parameters_DP, PS3_BT_Power_Value), 30, 1, 2, 98, "", 0 },

  { 50, "dp/Control Systems/PS3 input/PS3_VSP_Speed/Value", offsetof
    (Parameters_DP, PS3_VSP_Speed_Value), 30, 1, 2, 100, "", 0 },

  { 51,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_DP, T_e11_Value), 30, 1, 2, 102, "", 0 },

  { 52,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_DP, T_e21_Value), 30, 1, 2, 104, "", 0 },

  { 53,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_DP, l_y1_Value), 30, 1, 2, 106, "", 0 },

  { 54,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_DP, T_e12_Value), 30, 1, 2, 108, "", 0 },

  { 55,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_DP, T_e22_Value), 30, 1, 2, 110, "", 0 },

  { 56,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_DP, l_x1_Value), 30, 1, 2, 112, "", 0 },

  { 57,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_DP, l_x1_Gain), 30, 1, 2, 114, "", 0 },

  { 58,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_DP, T_e13_Value), 30, 1, 2, 116, "", 0 },

  { 59,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_DP, T_e23_Value), 30, 1, 2, 118, "", 0 },

  { 60,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_DP, l_y2_Value), 30, 1, 2, 120, "", 0 },

  { 61,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_DP, l_y2_Gain), 30, 1, 2, 122, "", 0 },

  { 62,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_DP, T_e14_Value), 30, 1, 2, 124, "", 0 },

  { 63,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_DP, T_e24_Value), 30, 1, 2, 126, "", 0 },

  { 64,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_DP, l_x2_Value), 30, 1, 2, 128, "", 0 },

  { 65,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_DP, l_x2_Gain), 30, 1, 2, 130, "", 0 },

  { 66,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_DP, T_e15_Value), 30, 1, 2, 132, "", 0 },

  { 67,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_DP, T_e25_Value), 30, 1, 2, 134, "", 0 },

  { 68,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_DP, l_x3_Value), 30, 1, 2, 136, "", 0 },

  { 69,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_DP, Saturation_UpperSat), 30, 1, 2, 138, "", 0 },

  { 70,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_DP, Saturation_LowerSat), 30, 1, 2, 140, "", 0 },

  { 71,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_DP, Gain_Gain), 30, 1, 2, 142, "", 0 },

  { 72,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_DP, Constant_Value), 30, 1, 2, 144, "", 0 },

  { 73,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_DP, Saturation_UpperSat_j), 30, 1, 2, 146, "", 0 },

  { 74,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_DP, Saturation_LowerSat_g), 30, 1, 2, 148, "", 0 },

  { 75,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_DP, Gain_Gain_i), 30, 1, 2, 150, "", 0 },

  { 76,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_i), 30, 1, 2, 152, "", 0 },

  { 77, "dp/Control Systems/DP control/DP controller/Kp/Gain", offsetof
    (Parameters_DP, Kp_Gain), 32, 9, 2, 154, "", 0 },

  { 78, "dp/Control Systems/DP control/DP controller/K_p_surge_scale/Gain",
    offsetof(Parameters_DP, K_p_surge_scale_Gain), 30, 1, 2, 156, "", 0 },

  { 79, "dp/Control Systems/DP control/DP controller/K_p_sway_scale/Gain",
    offsetof(Parameters_DP, K_p_sway_scale_Gain), 30, 1, 2, 158, "", 0 },

  { 80, "dp/Control Systems/DP control/DP controller/K_p_yaw_scale/Gain",
    offsetof(Parameters_DP, K_p_yaw_scale_Gain), 30, 1, 2, 160, "", 0 },

  { 81, "dp/Control Systems/DP control/DP controller/Reset_DP_integrator/Value",
    offsetof(Parameters_DP, Reset_DP_integrator_Value), 30, 1, 2, 162, "", 0 },

  { 82,
    "dp/Control Systems/DP control/DP controller/Integrator/InitialCondition",
    offsetof(Parameters_DP, Integrator_IC), 30, 1, 2, 164, "", 0 },

  { 83, "dp/Control Systems/DP control/DP controller/Ki/Gain", offsetof
    (Parameters_DP, Ki_Gain), 32, 9, 2, 166, "", 0 },

  { 84, "dp/Control Systems/DP control/DP controller/K_i_surge_scale/Gain",
    offsetof(Parameters_DP, K_i_surge_scale_Gain), 30, 1, 2, 168, "", 0 },

  { 85, "dp/Control Systems/DP control/DP controller/K_i_sway_scale/Gain",
    offsetof(Parameters_DP, K_i_sway_scale_Gain), 30, 1, 2, 170, "", 0 },

  { 86, "dp/Control Systems/DP control/DP controller/K_i_yaw_scale/Gain",
    offsetof(Parameters_DP, K_i_yaw_scale_Gain), 30, 1, 2, 172, "", 0 },

  { 87, "dp/Control Systems/DP control/DP controller/Kd/Gain", offsetof
    (Parameters_DP, Kd_Gain), 32, 9, 2, 174, "", 0 },

  { 88, "dp/Control Systems/DP control/DP controller/K_d_surge_scale/Gain",
    offsetof(Parameters_DP, K_d_surge_scale_Gain), 30, 1, 2, 176, "", 0 },

  { 89, "dp/Control Systems/DP control/DP controller/K_d_sway_scale/Gain",
    offsetof(Parameters_DP, K_d_sway_scale_Gain), 30, 1, 2, 178, "", 0 },

  { 90, "dp/Control Systems/DP control/DP controller/K_d_yaw_scale/Gain",
    offsetof(Parameters_DP, K_d_yaw_scale_Gain), 30, 1, 2, 180, "", 0 },

  { 91,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue",
    offsetof(Parameters_DP, DeadZone_Start), 30, 1, 2, 182, "", 0 },

  { 92,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue",
    offsetof(Parameters_DP, DeadZone_End), 30, 1, 2, 184, "", 0 },

  { 93,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_b), 30, 1, 2, 186, "", 0 },

  { 94,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_p), 30, 1, 2, 188, "", 0 },

  { 95,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_DP, f_10_XData), 33, 9, 2, 190, "", 0 },

  { 96,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_DP, f_10_YData), 33, 9, 2, 192, "", 0 },

  { 97,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_DP, f_10_Value), 30, 1, 2, 194, "", 0 },

  { 98,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_DP, f_10_XData_f), 53, 10, 2, 196, "", 0 },

  { 99,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_DP, f_10_YData_o), 53, 10, 2, 198, "", 0 },

  { 100,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue",
    offsetof(Parameters_DP, DeadZone_Start_e), 30, 1, 2, 200, "", 0 },

  { 101,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue",
    offsetof(Parameters_DP, DeadZone_End_p), 30, 1, 2, 202, "", 0 },

  { 102,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_l), 30, 1, 2, 204, "", 0 },

  { 103,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_f), 30, 1, 2, 206, "", 0 },

  { 104,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_a), 30, 1, 2, 208, "", 0 },

  { 105,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_DP, f_20_XData), 54, 11, 2, 210, "", 0 },

  { 106,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_DP, f_20_YData), 54, 11, 2, 212, "", 0 },

  { 107,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_DP, f_20_Value), 30, 1, 2, 214, "", 0 },

  { 108,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_DP, f_20_XData_d), 53, 10, 2, 216, "", 0 },

  { 109,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_DP, f_20_YData_l), 53, 10, 2, 218, "", 0 },

  { 110,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue",
    offsetof(Parameters_DP, DeadZone_Start_o), 30, 1, 2, 220, "", 0 },

  { 111,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue",
    offsetof(Parameters_DP, DeadZone_End_h), 30, 1, 2, 222, "", 0 },

  { 112,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_n), 30, 1, 2, 224, "", 0 },

  { 113,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_j), 30, 1, 2, 226, "", 0 },

  { 114,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_DP, f_30_XData), 55, 8, 2, 228, "", 0 },

  { 115,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_DP, f_30_YData), 55, 8, 2, 230, "", 0 },

  { 116,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_DP, f_30_Value), 30, 1, 2, 232, "", 0 },

  { 117,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_DP, f_30_XData_h), 54, 11, 2, 234, "", 0 },

  { 118,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_DP, f_30_YData_a), 54, 11, 2, 236, "", 0 },

  { 119,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue",
    offsetof(Parameters_DP, DeadZone_Start_a), 30, 1, 2, 238, "", 0 },

  { 120,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue",
    offsetof(Parameters_DP, DeadZone_End_k), 30, 1, 2, 240, "", 0 },

  { 121,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_h), 30, 1, 2, 242, "", 0 },

  { 122,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_ff), 30, 1, 2, 244, "", 0 },

  { 123,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_DP, f_40_XData), 53, 10, 2, 246, "", 0 },

  { 124,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_DP, f_40_YData), 53, 10, 2, 248, "", 0 },

  { 125,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_DP, f_40_Value), 30, 1, 2, 250, "", 0 },

  { 126,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_DP, f_40_XData_h), 56, 7, 2, 252, "", 0 },

  { 127,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_DP, f_40_YData_g), 56, 7, 2, 254, "", 0 },

  { 128,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue",
    offsetof(Parameters_DP, DeadZone_Start_i), 30, 1, 2, 256, "", 0 },

  { 129,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue",
    offsetof(Parameters_DP, DeadZone_End_pv), 30, 1, 2, 258, "", 0 },

  { 130,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_ac), 30, 1, 2, 260, "", 0 },

  { 131,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_DP, Constant_Value_k), 30, 1, 2, 262, "", 0 },

  { 132,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_DP, f_50_XData), 57, 3, 2, 264, "", 0 },

  { 133,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_DP, f_50_YData), 57, 3, 2, 266, "", 0 },

  { 134,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_DP, f_50_Value), 30, 1, 2, 268, "", 0 },

  { 135,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_DP, f_50_XData_k), 57, 3, 2, 270, "", 0 },

  { 136,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_DP, f_50_YData_h), 57, 3, 2, 272, "", 0 },

  { 137, "dp/Control Systems/DP control/Saturation/UpperLimit", offsetof
    (Parameters_DP, Saturation_UpperSat_c), 30, 1, 2, 274, "", 0 },

  { 138, "dp/Control Systems/DP control/Saturation/LowerLimit", offsetof
    (Parameters_DP, Saturation_LowerSat_d), 30, 1, 2, 276, "", 0 },

  { 139, "dp/Control Systems/DP control/BT_power_limit/Value", offsetof
    (Parameters_DP, BT_power_limit_Value), 30, 1, 2, 278, "", 0 },

  { 140, "dp/Control Systems/DP control/VSP_speeds/Value", offsetof
    (Parameters_DP, VSP_speeds_Value), 30, 1, 2, 280, "", 0 },

  { 141, "dp/Control Systems/Saturation/UpperLimit", offsetof(Parameters_DP,
    Saturation_UpperSat_f), 30, 1, 2, 282, "", 0 },

  { 142, "dp/Control Systems/Saturation/LowerLimit", offsetof(Parameters_DP,
    Saturation_LowerSat_i), 30, 1, 2, 284, "", 0 },

  { 143, "dp/HMI/Battery Bow Thruster/Gain", offsetof(Parameters_DP,
    BatteryBowThruster_Gain), 30, 1, 2, 286, "", 0 },

  { 144, "dp/HMI/Battery Servo/Gain", offsetof(Parameters_DP, BatteryServo_Gain),
    30, 1, 2, 288, "", 0 },

  { 145, "dp/HMI/Battery Main/Gain", offsetof(Parameters_DP, BatteryMain_Gain),
    30, 1, 2, 290, "", 0 },

  { 146, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain", offsetof
    (Parameters_DP, QTMIn1FPS_Gain), 30, 1, 2, 292, "", 0 },

  { 147, "dp/Plants/saturation/Saturation/UpperLimit", offsetof(Parameters_DP,
    Saturation_UpperSat_e), 30, 1, 2, 294, "", 0 },

  { 148, "dp/Plants/saturation/Saturation/LowerLimit", offsetof(Parameters_DP,
    Saturation_LowerSat_j), 30, 1, 2, 296, "", 0 },

  { 149, "dp/Plants/saturation/Saturation1/UpperLimit", offsetof(Parameters_DP,
    Saturation1_UpperSat), 30, 1, 2, 298, "", 0 },

  { 150, "dp/Plants/saturation/Saturation1/LowerLimit", offsetof(Parameters_DP,
    Saturation1_LowerSat), 30, 1, 2, 300, "", 0 },

  { 151, "dp/Plants/saturation/Saturation2/UpperLimit", offsetof(Parameters_DP,
    Saturation2_UpperSat), 30, 1, 2, 302, "", 0 },

  { 152, "dp/Plants/saturation/Saturation2/LowerLimit", offsetof(Parameters_DP,
    Saturation2_LowerSat), 30, 1, 2, 304, "", 0 },

  { 153, "dp/Plants/saturation/plant tau_surge/Gain", offsetof(Parameters_DP,
    planttau_surge_Gain), 30, 1, 2, 306, "", 0 },

  { 154, "dp/Plants/saturation/plant tau_sway/Gain", offsetof(Parameters_DP,
    planttau_sway_Gain), 30, 1, 2, 308, "", 0 },

  { 155, "dp/Plants/saturation/plant tau_yaw/Gain", offsetof(Parameters_DP,
    planttau_yaw_Gain), 30, 1, 2, 310, "", 0 },

  { 156, "dp/Plants/plant u_1/Gain", offsetof(Parameters_DP, plantu_1_Gain), 30,
    1, 2, 312, "", 0 },

  { 157, "dp/Plants/plant u_2/Gain", offsetof(Parameters_DP, plantu_2_Gain), 30,
    1, 2, 314, "", 0 },

  { 158, "dp/Plants/plant u_3/Gain", offsetof(Parameters_DP, plantu_3_Gain), 30,
    1, 2, 316, "", 0 },

  { 159, "dp/Plants/plant u_4/Gain", offsetof(Parameters_DP, plantu_4_Gain), 30,
    1, 2, 318, "", 0 },

  { 160, "dp/Plants/plant u_5/Gain", offsetof(Parameters_DP, plantu_5_Gain), 30,
    1, 2, 320, "", 0 },

  { 161, "dp/Plants/plant BT power/Gain", offsetof(Parameters_DP,
    plantBTpower_Gain), 30, 1, 2, 322, "", 0 },

  { 162, "dp/Plants/plant VSP speed/Gain", offsetof(Parameters_DP,
    plantVSPspeed_Gain), 30, 1, 2, 324, "", 0 },

  { 163, "dp/Plants/Enable CSE1/Value", offsetof(Parameters_DP, EnableCSE1_Value),
    30, 1, 2, 326, "", 0 },

  { 164, "dp/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain", offsetof(Parameters_DP,
    BT_D_Gain1_Gain), 30, 1, 2, 328, "", 0 },

  { 165, "dp/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value", offsetof
    (Parameters_DP, BT_Power_Offset1_Value), 30, 1, 2, 330, "", 0 },

  { 166, "dp/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain", offsetof(Parameters_DP,
    BT_D_Gain2_Gain), 30, 1, 2, 332, "", 0 },

  { 167, "dp/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain", offsetof(Parameters_DP,
    BT_L_Gain1_Gain), 30, 1, 2, 334, "", 0 },

  { 168, "dp/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain", offsetof(Parameters_DP,
    BT_L_Gain2_Gain), 30, 1, 2, 336, "", 0 },

  { 169, "dp/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value", offsetof
    (Parameters_DP, BT_Power_Offset2_Value), 30, 1, 2, 338, "", 0 },

  { 170, "dp/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value", offsetof
    (Parameters_DP, BT_Power_Offset3_Value), 30, 1, 2, 340, "", 0 },

  { 171, "dp/Plants/CSE1/Bow Thruster/Constant/Value", offsetof(Parameters_DP,
    Constant_Value_m), 30, 1, 2, 342, "", 0 },

  { 172, "dp/Plants/CSE1/Bow Thruster/Constant1/Value", offsetof(Parameters_DP,
    Constant1_Value_j), 30, 1, 2, 344, "", 0 },

  { 173, "dp/Plants/CSE1/Bow Thruster/Neg/Gain", offsetof(Parameters_DP,
    Neg_Gain), 30, 1, 2, 346, "", 0 },

  { 174, "dp/Plants/CSE1/Voith Schneider Propeller /-x/Gain", offsetof
    (Parameters_DP, x_Gain), 30, 1, 2, 348, "", 0 },

  { 175, "dp/Plants/CSE1/Voith Schneider Propeller /-y/Gain", offsetof
    (Parameters_DP, y_Gain), 30, 1, 2, 350, "", 0 },

  { 176, "dp/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex", offsetof
    (Parameters_DP, Servo1_RowIdx), 58, 3, 2, 352, "", 0 },

  { 177, "dp/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_DP, Servo1_ColIdx), 58, 3, 2, 354, "", 0 },

  { 178, "dp/Plants/CSE1/Voith Schneider Propeller /Servo1/Table", offsetof
    (Parameters_DP, Servo1_Table), 32, 9, 2, 356, "", 0 },

  { 179, "dp/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex", offsetof
    (Parameters_DP, Servo2_RowIdx), 58, 3, 2, 358, "", 0 },

  { 180, "dp/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_DP, Servo2_ColIdx), 58, 3, 2, 360, "", 0 },

  { 181, "dp/Plants/CSE1/Voith Schneider Propeller /Servo2/Table", offsetof
    (Parameters_DP, Servo2_Table), 32, 9, 2, 362, "", 0 },

  { 182, "dp/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex", offsetof
    (Parameters_DP, Servo3_RowIdx), 58, 3, 2, 364, "", 0 },

  { 183, "dp/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_DP, Servo3_ColIdx), 58, 3, 2, 366, "", 0 },

  { 184, "dp/Plants/CSE1/Voith Schneider Propeller /Servo3/Table", offsetof
    (Parameters_DP, Servo3_Table), 32, 9, 2, 368, "", 0 },

  { 185, "dp/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex", offsetof
    (Parameters_DP, Servo4_RowIdx), 58, 3, 2, 370, "", 0 },

  { 186, "dp/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_DP, Servo4_ColIdx), 58, 3, 2, 372, "", 0 },

  { 187, "dp/Plants/CSE1/Voith Schneider Propeller /Servo4/Table", offsetof
    (Parameters_DP, Servo4_Table), 32, 9, 2, 374, "", 0 },

  { 188, "dp/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_DP, VPS_Speed_Gain_Gain), 30, 1, 2, 376, "", 0 },

  { 189, "dp/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_DP, VPS_Power_Offset_Value), 30, 1, 2, 378, "", 0 },

  { 190, "dp/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain", offsetof
    (Parameters_DP, VSPSPort_Gain), 30, 1, 2, 380, "", 0 },

  { 191, "dp/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_DP, VSPSStarboard_Gain), 30, 1, 2, 382, "", 0 },

  { 192, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_r/Value",
    offsetof(Parameters_DP, N_r_Value), 30, 1, 2, 384, "", 0 },

  { 193, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r/Gain",
    offsetof(Parameters_DP, N_r_Gain), 30, 1, 2, 386, "", 0 },

  { 194, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_v/Value",
    offsetof(Parameters_DP, N_v_Value), 30, 1, 2, 388, "", 0 },

  { 195, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v/Gain",
    offsetof(Parameters_DP, N_v_Gain), 30, 1, 2, 390, "", 0 },

  { 196, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/X_u/Value",
    offsetof(Parameters_DP, X_u_Value), 30, 1, 2, 392, "", 0 },

  { 197, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u/Gain",
    offsetof(Parameters_DP, X_u_Gain), 30, 1, 2, 394, "", 0 },

  { 198, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_v/Value",
    offsetof(Parameters_DP, Y_v_Value), 30, 1, 2, 396, "", 0 },

  { 199, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v/Gain",
    offsetof(Parameters_DP, Y_v_Gain), 30, 1, 2, 398, "", 0 },

  { 200, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_r/Value",
    offsetof(Parameters_DP, Y_r_Value), 30, 1, 2, 400, "", 0 },

  { 201, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr/Gain",
    offsetof(Parameters_DP, Y_vr_Gain), 30, 1, 2, 402, "", 0 },

  { 202, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_12/Value",
    offsetof(Parameters_DP, D_L_12_Value), 30, 1, 2, 404, "", 0 },

  { 203, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_13/Value",
    offsetof(Parameters_DP, D_L_13_Value), 30, 1, 2, 406, "", 0 },

  { 204, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_21/Value",
    offsetof(Parameters_DP, D_L_21_Value), 30, 1, 2, 408, "", 0 },

  { 205, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_31/Value",
    offsetof(Parameters_DP, D_L_31_Value), 30, 1, 2, 410, "", 0 },

  { 206,
    "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0/Value",
    offsetof(Parameters_DP, psi_0_Value), 30, 1, 2, 412, "", 0 },

  { 207,
    "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0/Value",
    offsetof(Parameters_DP, x_0_Value), 30, 1, 2, 414, "", 0 },

  { 208,
    "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0/Value",
    offsetof(Parameters_DP, y_0_Value), 30, 1, 2, 416, "", 0 },

  { 209,
    "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0/Value",
    offsetof(Parameters_DP, r_0_Value), 30, 1, 2, 418, "", 0 },

  { 210,
    "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0/Value",
    offsetof(Parameters_DP, u_0_Value), 30, 1, 2, 420, "", 0 },

  { 211,
    "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0/Value",
    offsetof(Parameters_DP, v_0_Value), 30, 1, 2, 422, "", 0 },

  { 212,
    "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_DP, ResetLinearSimulatorintegrator_), 30, 1, 2, 424, "",
    0 },

  { 213, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/I_z/Value",
    offsetof(Parameters_DP, I_z_Value), 30, 1, 2, 426, "", 0 },

  { 214, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m/Value",
    offsetof(Parameters_DP, m_Value), 30, 1, 2, 428, "", 0 },

  { 215, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/X_udot/Value",
    offsetof(Parameters_DP, X_udot_Value), 30, 1, 2, 430, "", 0 },

  { 216, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_21/Value",
    offsetof(Parameters_DP, M_21_Value), 30, 1, 2, 432, "", 0 },

  { 217, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_31/Value",
    offsetof(Parameters_DP, M_31_Value), 30, 1, 2, 434, "", 0 },

  { 218, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_12/Value",
    offsetof(Parameters_DP, M_12_Value), 30, 1, 2, 436, "", 0 },

  { 219, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_vdot/Value",
    offsetof(Parameters_DP, Y_vdot_Value), 30, 1, 2, 438, "", 0 },

  { 220, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/x_g/Value",
    offsetof(Parameters_DP, x_g_Value), 30, 1, 2, 440, "", 0 },

  { 221, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_vdot/Value",
    offsetof(Parameters_DP, N_vdot_Value), 30, 1, 2, 442, "", 0 },

  { 222, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_13/Value",
    offsetof(Parameters_DP, M_13_Value), 30, 1, 2, 444, "", 0 },

  { 223, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_rdot/Value",
    offsetof(Parameters_DP, Y_rdot_Value), 30, 1, 2, 446, "", 0 },

  { 224, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_rdot/Value",
    offsetof(Parameters_DP, N_rdot_Value), 30, 1, 2, 448, "", 0 },

  { 225, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_DP, R31_Value), 30, 1, 2, 450, "", 0 },

  { 226, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_DP, R32_Value), 30, 1, 2, 452, "", 0 },

  { 227, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_DP, R13_Value), 30, 1, 2, 454, "", 0 },

  { 228, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_DP, R23_Value), 30, 1, 2, 456, "", 0 },

  { 229, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_DP, R33_Value), 30, 1, 2, 458, "", 0 },

  { 230, "dp/Plants/Linear Simulator/eta_surge_hil/Gain", offsetof(Parameters_DP,
    eta_surge_hil_Gain), 30, 1, 2, 460, "", 0 },

  { 231, "dp/Plants/Linear Simulator/eta_sway_hil/Gain", offsetof(Parameters_DP,
    eta_sway_hil_Gain), 30, 1, 2, 462, "", 0 },

  { 232, "dp/Plants/Linear Simulator/eta_yaw_hil/Gain", offsetof(Parameters_DP,
    eta_yaw_hil_Gain), 30, 1, 2, 464, "", 0 },

  { 233, "dp/Plants/Linear Simulator/etadot_surge_hil/Gain", offsetof
    (Parameters_DP, etadot_surge_hil_Gain), 30, 1, 2, 466, "", 0 },

  { 234, "dp/Plants/Linear Simulator/etadot_sway_hil/Gain", offsetof
    (Parameters_DP, etadot_sway_hil_Gain), 30, 1, 2, 468, "", 0 },

  { 235, "dp/Plants/Linear Simulator/etadot_yaw_hil/Gain", offsetof
    (Parameters_DP, etadot_yaw_hil_Gain), 30, 1, 2, 470, "", 0 },

  { 236, "dp/Plants/Linear Simulator/nu_surge_hil/Gain", offsetof(Parameters_DP,
    nu_surge_hil_Gain), 30, 1, 2, 472, "", 0 },

  { 237, "dp/Plants/Linear Simulator/nu_sway_hil/Gain", offsetof(Parameters_DP,
    nu_sway_hil_Gain), 30, 1, 2, 474, "", 0 },

  { 238, "dp/Plants/Linear Simulator/nu_yaw_hil/Gain", offsetof(Parameters_DP,
    nu_yaw_hil_Gain), 30, 1, 2, 476, "", 0 },

  { 239,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_DP, Gain_Gain_e), 59, 1, 2, 478, "", 0 },

  { 240,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_DP, Gain1_Gain_i), 59, 1, 2, 480, "", 0 },

  { 241,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_DP, Gain_Gain_h), 59, 1, 2, 482, "", 0 },

  { 242,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_DP, Gain1_Gain_a), 59, 1, 2, 484, "", 0 },

  { 243,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_DP, Gain_Gain_f), 59, 1, 2, 486, "", 0 },

  { 244,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_DP, Gain1_Gain_o), 59, 1, 2, 488, "", 0 },

  { 245,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_DP, Gain_Gain_o), 59, 1, 2, 490, "", 0 },

  { 246,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_DP, Gain1_Gain_it), 59, 1, 2, 492, "", 0 },

  { 247,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_DP, Gain_Gain_k), 59, 1, 2, 494, "", 0 },

  { 248,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_DP, Gain1_Gain_aq), 59, 1, 2, 496, "", 0 },
};

static int NI_ParamListSize = 249;
static int NI_ParamDimList[] = {
  1, 1,                                /* dp/Naviagation Systems/Controller Input Selector/Value */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain */
  1, 1,                                /* dp/Plants/Enable Linear Simulator/Value */
  1, 1,                                /* dp/Naviagation Systems/etadot_surge/Gain */
  1, 1,                                /* dp/Naviagation Systems/etadot_sway/Gain */
  1, 1,                                /* dp/Naviagation Systems/etadot_yaw/Gain */
  1, 1,                                /* dp/Naviagation Systems/eta_surge/Gain */
  1, 1,                                /* dp/Naviagation Systems/eta_sway/Gain */
  1, 1,                                /* dp/Naviagation Systems/eta_yaw/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain */
  3, 3,                                /* dp/Naviagation Systems/Qualisys 6 DOF/Constant1/Value */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain */
  1, 1,                                /* dp/Naviagation Systems/nu_surge/Gain */
  1, 1,                                /* dp/Naviagation Systems/nu_sway/Gain */
  1, 1,                                /* dp/Naviagation Systems/nu_yaw/Gain */
  1, 1,                                /* dp/HMI/DP Input/x_d/Value */
  1, 1,                                /* dp/Guidance Systems/DP/eta_d DP N/Gain */
  1, 1,                                /* dp/HMI/DP Input/y_d/Value */
  1, 1,                                /* dp/Guidance Systems/DP/eta_d DP E/Gain */
  1, 1,                                /* dp/HMI/DP Input/psi_d/Value */
  1, 1,                                /* dp/HMI/DP Input/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* dp/Guidance Systems/DP/eta_d DP Psi/Gain */
  1, 1,                                /* dp/Control Systems/Control Mode/Value */
  1, 1,                                /* dp/Control Systems/PS3 input/AS_LY/Value */
  1, 1,                                /* dp/Control Systems/PS3 input/ScalingLY/Gain */
  1, 1,                                /* dp/Control Systems/PS3 u input control/PS3 u_1/Gain */
  1, 1,                                /* dp/Control Systems/PS3 input/AS_LX/Value */
  1, 1,                                /* dp/Control Systems/PS3 input/ScalingLX/Gain */
  1, 1,                                /* dp/Control Systems/PS3 u input control/PS3 u_2/Gain */
  1, 1,                                /* dp/Control Systems/PS3 input/AS_RY/Value */
  1, 1,                                /* dp/Control Systems/PS3 input/ScalingRY/Gain */
  1, 1,                                /* dp/Control Systems/PS3 u input control/PS3 u_3/Gain */
  1, 1,                                /* dp/Control Systems/PS3 input/AS_RX/Value */
  1, 1,                                /* dp/Control Systems/PS3 input/Scaling_RX/Gain */
  1, 1,                                /* dp/Control Systems/PS3 u input control/PS3 u_4/Gain */
  1, 1,                                /* dp/Control Systems/PS3 input/L2/Value */
  1, 1,                                /* dp/Control Systems/PS3 input/R2/Value */
  1, 1,                                /* dp/Control Systems/PS3 u input control/PS3 u_5/Gain */
  1, 1,                                /* dp/Control Systems/PS3 input/PS3_BT_Power/Value */
  1, 1,                                /* dp/Control Systems/PS3 input/PS3_VSP_Speed/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value */
  3, 3,                                /* dp/Control Systems/DP control/DP controller/Kp/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/K_p_surge_scale/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/K_p_sway_scale/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/K_p_yaw_scale/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/Reset_DP_integrator/Value */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/Integrator/InitialCondition */
  3, 3,                                /* dp/Control Systems/DP control/DP controller/Ki/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/K_i_surge_scale/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/K_i_sway_scale/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/K_i_yaw_scale/Gain */
  3, 3,                                /* dp/Control Systems/DP control/DP controller/Kd/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/K_d_surge_scale/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/K_d_sway_scale/Gain */
  1, 1,                                /* dp/Control Systems/DP control/DP controller/K_d_yaw_scale/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/LowerValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone/UpperValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/LowerValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone/UpperValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Constant/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/LowerValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone/UpperValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/LowerValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone/UpperValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/LowerValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone/UpperValue */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* dp/Control Systems/DP control/Saturation/UpperLimit */
  1, 1,                                /* dp/Control Systems/DP control/Saturation/LowerLimit */
  1, 1,                                /* dp/Control Systems/DP control/BT_power_limit/Value */
  1, 1,                                /* dp/Control Systems/DP control/VSP_speeds/Value */
  1, 1,                                /* dp/Control Systems/Saturation/UpperLimit */
  1, 1,                                /* dp/Control Systems/Saturation/LowerLimit */
  1, 1,                                /* dp/HMI/Battery Bow Thruster/Gain */
  1, 1,                                /* dp/HMI/Battery Servo/Gain */
  1, 1,                                /* dp/HMI/Battery Main/Gain */
  1, 1,                                /* dp/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS/Gain */
  1, 1,                                /* dp/Plants/saturation/Saturation/UpperLimit */
  1, 1,                                /* dp/Plants/saturation/Saturation/LowerLimit */
  1, 1,                                /* dp/Plants/saturation/Saturation1/UpperLimit */
  1, 1,                                /* dp/Plants/saturation/Saturation1/LowerLimit */
  1, 1,                                /* dp/Plants/saturation/Saturation2/UpperLimit */
  1, 1,                                /* dp/Plants/saturation/Saturation2/LowerLimit */
  1, 1,                                /* dp/Plants/saturation/plant tau_surge/Gain */
  1, 1,                                /* dp/Plants/saturation/plant tau_sway/Gain */
  1, 1,                                /* dp/Plants/saturation/plant tau_yaw/Gain */
  1, 1,                                /* dp/Plants/plant u_1/Gain */
  1, 1,                                /* dp/Plants/plant u_2/Gain */
  1, 1,                                /* dp/Plants/plant u_3/Gain */
  1, 1,                                /* dp/Plants/plant u_4/Gain */
  1, 1,                                /* dp/Plants/plant u_5/Gain */
  1, 1,                                /* dp/Plants/plant BT power/Gain */
  1, 1,                                /* dp/Plants/plant VSP speed/Gain */
  1, 1,                                /* dp/Plants/Enable CSE1/Value */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/Constant/Value */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/Constant1/Value */
  1, 1,                                /* dp/Plants/CSE1/Bow Thruster/Neg/Gain */
  1, 1,                                /* dp/Plants/CSE1/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* dp/Plants/CSE1/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* dp/Plants/CSE1/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* dp/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* dp/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* dp/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* dp/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_r/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_v/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/X_u/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_v/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_r/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_12/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_13/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_21/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_31/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/Reset Linear Simulator integrator/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/I_z/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/X_udot/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_21/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_31/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_12/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_vdot/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/x_g/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_vdot/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_13/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_rdot/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_rdot/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* dp/Plants/Linear Simulator/eta_surge_hil/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/eta_sway_hil/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/eta_yaw_hil/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/etadot_surge_hil/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/etadot_sway_hil/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/etadot_yaw_hil/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/nu_surge_hil/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/nu_sway_hil/Gain */
  1, 1,                                /* dp/Plants/Linear Simulator/nu_yaw_hil/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 243;
static NI_Signal NI_SigList[] = {
  { 0, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In", 0, "", offsetof
    (BlockIO_DP, QTMIn), BLOCKIO_SIG, 33, 9, 2, 0, 0 },

  { 1, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error", 0, "", offsetof
    (BlockIO_DP, QTMIn2Error), BLOCKIO_SIG, 30, 1, 2, 2, 0 },

  { 2, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual", 0, "", offsetof
    (BlockIO_DP, QTMIn9Residual), BLOCKIO_SIG, 30, 1, 2, 4, 0 },

  { 3, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In3", 0, "", offsetof
    (BlockIO_DP, QTMIn3), BLOCKIO_SIG, 30, 1, 2, 6, 0 },

  { 4, "dp/Naviagation Systems/Qualisys 6 DOF/mm2m x", 0, "", offsetof
    (BlockIO_DP, mm2mx), BLOCKIO_SIG, 30, 1, 2, 8, 0 },

  { 5, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In4", 0, "", offsetof
    (BlockIO_DP, QTMIn4), BLOCKIO_SIG, 30, 1, 2, 10, 0 },

  { 6, "dp/Naviagation Systems/Qualisys 6 DOF/mm2m y", 0, "", offsetof
    (BlockIO_DP, mm2my), BLOCKIO_SIG, 30, 1, 2, 12, 0 },

  { 7, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In6", 0, "", offsetof
    (BlockIO_DP, QTMIn6), BLOCKIO_SIG, 30, 1, 2, 14, 0 },

  { 8, "dp/Naviagation Systems/Qualisys 6 DOF/d2r yaw", 0, "", offsetof
    (BlockIO_DP, d2ryaw), BLOCKIO_SIG, 30, 1, 2, 16, 0 },

  { 9, "dp/Naviagation Systems/Qualisys 6 DOF/Derivative1", 0, "", offsetof
    (BlockIO_DP, Derivative1), BLOCKIO_SIG, 20, 3, 2, 18, 0 },

  { 10, "dp/Naviagation Systems/Etadot Switch", 0, "", offsetof(BlockIO_DP,
    EtadotSwitch), BLOCKIO_SIG, 20, 3, 2, 20, 0 },

  { 11, "dp/Naviagation Systems/etadot_surge", 0, "", offsetof(BlockIO_DP,
    etadot_surge), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "dp/Naviagation Systems/etadot_sway", 0, "", offsetof(BlockIO_DP,
    etadot_sway), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "dp/Naviagation Systems/etadot_yaw", 0, "", offsetof(BlockIO_DP,
    etadot_yaw), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "dp/Naviagation Systems/Eta Switch", 0, "", offsetof(BlockIO_DP,
    EtaSwitch), BLOCKIO_SIG, 20, 3, 2, 28, 0 },

  { 15, "dp/Naviagation Systems/eta_surge", 0, "", offsetof(BlockIO_DP,
    eta_surge), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "dp/Naviagation Systems/eta_sway", 0, "", offsetof(BlockIO_DP, eta_sway),
    BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17, "dp/Naviagation Systems/eta_yaw", 0, "", offsetof(BlockIO_DP, eta_yaw),
    BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In8", 0, "", offsetof
    (BlockIO_DP, QTMIn8), BLOCKIO_SIG, 30, 1, 2, 36, 0 },

  { 19, "dp/Naviagation Systems/Qualisys 6 DOF/d2r roll", 0, "", offsetof
    (BlockIO_DP, d2rroll), BLOCKIO_SIG, 30, 1, 2, 38, 0 },

  { 20, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In7", 0, "", offsetof
    (BlockIO_DP, QTMIn7), BLOCKIO_SIG, 30, 1, 2, 40, 0 },

  { 21, "dp/Naviagation Systems/Qualisys 6 DOF/d2r pitch", 0, "", offsetof
    (BlockIO_DP, d2rpitch), BLOCKIO_SIG, 30, 1, 2, 42, 0 },

  { 22,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_DP, sintheta), BLOCKIO_SIG, 20, 3, 2, 44, 0 },

  { 23,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_DP, costheta), BLOCKIO_SIG, 20, 3, 2, 46, 0 },

  { 24,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_DP, R11), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_DP, R21), BLOCKIO_SIG, 0, 1, 2, 50, 0 },

  { 26,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_DP, R31), BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_DP, R12), BLOCKIO_SIG, 0, 1, 2, 54, 0 },

  { 28,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_DP, R22), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_DP, R32), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_DP, R13), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_DP, R23), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_DP, R33), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33,
    "dp/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_DP, Reshape9x13x3), BLOCKIO_SIG, 32, 9, 2, 66, 0 },

  { 34, "dp/Naviagation Systems/Qualisys 6 DOF/Matrix Concatenate2", 0, "",
    offsetof(BlockIO_DP, MatrixConcatenate2), BLOCKIO_SIG, 37, 36, 2, 68, 0 },

  { 35, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In5", 0, "", offsetof
    (BlockIO_DP, QTMIn5), BLOCKIO_SIG, 30, 1, 2, 70, 0 },

  { 36, "dp/Naviagation Systems/Qualisys 6 DOF/mm2m z", 0, "", offsetof
    (BlockIO_DP, mm2mz), BLOCKIO_SIG, 30, 1, 2, 72, 0 },

  { 37, "dp/Naviagation Systems/Qualisys 6 DOF/Derivative", 0, "", offsetof
    (BlockIO_DP, Derivative), BLOCKIO_SIG, 29, 6, 2, 74, 0 },

  { 38, "dp/Naviagation Systems/Qualisys 6 DOF/Product", 0, "", offsetof
    (BlockIO_DP, Product), BLOCKIO_SIG, 29, 6, 2, 76, 0 },

  { 39, "dp/Naviagation Systems/Nu Switch", 0, "", offsetof(BlockIO_DP, NuSwitch),
    BLOCKIO_SIG, 20, 3, 2, 78, 0 },

  { 40, "dp/Naviagation Systems/nu_surge", 0, "", offsetof(BlockIO_DP, nu_surge),
    BLOCKIO_SIG, 0, 1, 2, 80, 0 },

  { 41, "dp/Naviagation Systems/nu_sway", 0, "", offsetof(BlockIO_DP, nu_sway),
    BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42, "dp/Naviagation Systems/nu_yaw", 0, "", offsetof(BlockIO_DP, nu_yaw),
    BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43, "dp/Guidance Systems/DP/eta_d DP N", 0, "", offsetof(BlockIO_DP,
    eta_dDPN), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44, "dp/Guidance Systems/DP/eta_d DP E", 0, "", offsetof(BlockIO_DP,
    eta_dDPE), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "dp/HMI/DP Input/Degrees to Radians/Gain1", 0, "", offsetof(BlockIO_DP,
    Gain1), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46, "dp/Guidance Systems/DP/eta_d DP Psi", 0, "", offsetof(BlockIO_DP,
    eta_dDPPsi), BLOCKIO_SIG, 0, 1, 2, 92, 0 },

  { 47, "dp/Control Systems/PS3 input/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_DP,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48, "dp/Control Systems/PS3 u input control/PS3 u_1", 0, "u_1", offsetof
    (BlockIO_DP, u_1), BLOCKIO_SIG, 0, 1, 2, 96, 0 },

  { 49, "dp/Control Systems/PS3 input/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_DP,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 98, 0 },

  { 50, "dp/Control Systems/PS3 u input control/PS3 u_2", 0, "u_2", offsetof
    (BlockIO_DP, u_2), BLOCKIO_SIG, 0, 1, 2, 100, 0 },

  { 51, "dp/Control Systems/PS3 input/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_DP,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52, "dp/Control Systems/PS3 u input control/PS3 u_3", 0, "u_3", offsetof
    (BlockIO_DP, u_3), BLOCKIO_SIG, 0, 1, 2, 104, 0 },

  { 53, "dp/Control Systems/PS3 input/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_DP,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 106, 0 },

  { 54, "dp/Control Systems/PS3 u input control/PS3 u_4", 0, "u_4", offsetof
    (BlockIO_DP, u_4), BLOCKIO_SIG, 0, 1, 2, 108, 0 },

  { 55, "dp/Control Systems/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_DP, BowThrusterdirection),
    BLOCKIO_SIG, 0, 1, 2, 110, 0 },

  { 56, "dp/Control Systems/PS3 u input control/PS3 u_5", 0, "u_5", offsetof
    (BlockIO_DP, u_5), BLOCKIO_SIG, 0, 1, 2, 112, 0 },

  { 57,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_DP, l_x1), BLOCKIO_SIG, 0, 1, 2, 114, 0 },

  { 58,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_DP, l_y2), BLOCKIO_SIG, 0, 1, 2, 116, 0 },

  { 59,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_DP, l_x2), BLOCKIO_SIG, 0, 1, 2, 118, 0 },

  { 60, "dp/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_DP, x5), BLOCKIO_SIG, 25, 15, 2, 120, 0 },

  { 61,
    "dp/Control Systems/DP control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_DP, Pseudoinverse), BLOCKIO_SIG, 24, 15, 2, 122, 0 },

  { 62, "dp/Control Systems/DP control/DP controller/yaw angle", 0, "psi",
    offsetof(BlockIO_DP, psi), BLOCKIO_SIG, 0, 1, 2, 124, 0 },

  { 63,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_DP, Saturation), BLOCKIO_SIG, 0, 1, 2, 126, 0 },

  { 64,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_DP, Sign), BLOCKIO_SIG, 0, 1, 2, 128, 0 },

  { 65,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_DP, Gain), BLOCKIO_SIG, 0, 1, 2, 130, 0 },

  { 66,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_DP, Sum1), BLOCKIO_SIG, 0, 1, 2, 132, 0 },

  { 67,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_DP, MathFunction), BLOCKIO_SIG, 0, 1, 2, 134, 0 },

  { 68,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum", 0,
    "", offsetof(BlockIO_DP, Sum), BLOCKIO_SIG, 0, 1, 2, 136, 0 },

  { 69, "dp/Control Systems/DP control/DP controller/Sum2", 0,
    "regulation error", offsetof(BlockIO_DP, regulationerror), BLOCKIO_SIG, 20,
    3, 2, 138, 0 },

  { 70,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_DP, Saturation_e), BLOCKIO_SIG, 0, 1, 2, 140, 0 },

  { 71,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sign", 0,
    "", offsetof(BlockIO_DP, Sign_p), BLOCKIO_SIG, 0, 1, 2, 142, 0 },

  { 72,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain", 0,
    "", offsetof(BlockIO_DP, Gain_b), BLOCKIO_SIG, 0, 1, 2, 144, 0 },

  { 73,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum1", 0,
    "", offsetof(BlockIO_DP, Sum1_e), BLOCKIO_SIG, 0, 1, 2, 146, 0 },

  { 74,
    "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_DP, MathFunction_k), BLOCKIO_SIG, 0, 1, 2, 148, 0 },

  { 75, "dp/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_DP, Sum_a), BLOCKIO_SIG, 0, 1, 2, 150, 0 },

  { 76,
    "dp/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_DP, Row1), BLOCKIO_SIG, 0, 1, 2, 152, 0 },

  { 77,
    "dp/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_DP, Row2), BLOCKIO_SIG, 0, 1, 2, 154, 0 },

  { 78,
    "dp/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_DP, Row3), BLOCKIO_SIG, 0, 1, 2, 156, 0 },

  { 79, "dp/Control Systems/DP control/DP controller/Kp", 0, "", offsetof
    (BlockIO_DP, Kp), BLOCKIO_SIG, 20, 3, 2, 158, 0 },

  { 80, "dp/Control Systems/DP control/DP controller/K_p_surge_scale", 0, "",
    offsetof(BlockIO_DP, K_p_surge_scale), BLOCKIO_SIG, 0, 1, 2, 160, 0 },

  { 81, "dp/Control Systems/DP control/DP controller/K_p_sway_scale", 0, "",
    offsetof(BlockIO_DP, K_p_sway_scale), BLOCKIO_SIG, 0, 1, 2, 162, 0 },

  { 82, "dp/Control Systems/DP control/DP controller/K_p_yaw_scale", 0, "",
    offsetof(BlockIO_DP, K_p_yaw_scale), BLOCKIO_SIG, 0, 1, 2, 164, 0 },

  { 83, "dp/Control Systems/DP control/DP controller/Integrator", 0, "",
    offsetof(BlockIO_DP, Integrator), BLOCKIO_SIG, 20, 3, 2, 166, 0 },

  { 84, "dp/Control Systems/DP control/DP controller/Ki", 0, "", offsetof
    (BlockIO_DP, Ki), BLOCKIO_SIG, 20, 3, 2, 168, 0 },

  { 85, "dp/Control Systems/DP control/DP controller/K_i_surge_scale", 0, "",
    offsetof(BlockIO_DP, K_i_surge_scale), BLOCKIO_SIG, 0, 1, 2, 170, 0 },

  { 86, "dp/Control Systems/DP control/DP controller/K_i_sway_scale", 0, "",
    offsetof(BlockIO_DP, K_i_sway_scale), BLOCKIO_SIG, 0, 1, 2, 172, 0 },

  { 87, "dp/Control Systems/DP control/DP controller/K_i_yaw_scale", 0, "",
    offsetof(BlockIO_DP, K_i_yaw_scale), BLOCKIO_SIG, 0, 1, 2, 174, 0 },

  { 88, "dp/Control Systems/DP control/DP controller/Sum3", 0, "", offsetof
    (BlockIO_DP, Sum3), BLOCKIO_SIG, 20, 3, 2, 176, 0 },

  { 89, "dp/Control Systems/DP control/DP controller/Kd", 0, "", offsetof
    (BlockIO_DP, Kd), BLOCKIO_SIG, 20, 3, 2, 178, 0 },

  { 90, "dp/Control Systems/DP control/DP controller/K_d_surge_scale", 0, "",
    offsetof(BlockIO_DP, K_d_surge_scale), BLOCKIO_SIG, 0, 1, 2, 180, 0 },

  { 91, "dp/Control Systems/DP control/DP controller/K_d_sway_scale", 0, "",
    offsetof(BlockIO_DP, K_d_sway_scale), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92, "dp/Control Systems/DP control/DP controller/K_d_yaw_scale", 0, "",
    offsetof(BlockIO_DP, K_d_yaw_scale), BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93, "dp/Control Systems/DP control/DP controller/Sum1", 0, "", offsetof
    (BlockIO_DP, Sum1_d), BLOCKIO_SIG, 20, 3, 2, 186, 0 },

  { 94, "dp/Control Systems/DP control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_DP, Product_n), BLOCKIO_SIG, 23, 5, 2, 188, 0 },

  { 95,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Dead Zone",
    0, "", offsetof(BlockIO_DP, DeadZone), BLOCKIO_SIG, 0, 1, 2, 190, 0 },

  { 96,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_DP, f_10), BLOCKIO_SIG, 0, 1, 2, 192, 0 },

  { 97,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_DP, f_10_e), BLOCKIO_SIG, 0, 1, 2, 194, 0 },

  { 98,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_DP, MultiportSwitch), BLOCKIO_SIG, 0, 1, 2, 196, 0 },

  { 99,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Dead Zone",
    0, "", offsetof(BlockIO_DP, DeadZone_i), BLOCKIO_SIG, 0, 1, 2, 198, 0 },

  { 100,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_DP, f_20), BLOCKIO_SIG, 0, 1, 2, 200, 0 },

  { 101,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_DP, f_20_h), BLOCKIO_SIG, 0, 1, 2, 202, 0 },

  { 102,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_DP, MultiportSwitch_a), BLOCKIO_SIG, 0, 1, 2, 204, 0
  },

  { 103,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Dead Zone",
    0, "", offsetof(BlockIO_DP, DeadZone_o), BLOCKIO_SIG, 0, 1, 2, 206, 0 },

  { 104,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_DP, f_30), BLOCKIO_SIG, 0, 1, 2, 208, 0 },

  { 105,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_DP, f_30_m), BLOCKIO_SIG, 0, 1, 2, 210, 0 },

  { 106,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_DP, MultiportSwitch_m), BLOCKIO_SIG, 0, 1, 2, 212, 0
  },

  { 107,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Dead Zone",
    0, "", offsetof(BlockIO_DP, DeadZone_n), BLOCKIO_SIG, 0, 1, 2, 214, 0 },

  { 108,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_DP, f_40), BLOCKIO_SIG, 0, 1, 2, 216, 0 },

  { 109,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_DP, f_40_l), BLOCKIO_SIG, 0, 1, 2, 218, 0 },

  { 110,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_DP, MultiportSwitch_o), BLOCKIO_SIG, 0, 1, 2, 220, 0
  },

  { 111,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Dead Zone",
    0, "", offsetof(BlockIO_DP, DeadZone_d), BLOCKIO_SIG, 0, 1, 2, 222, 0 },

  { 112,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_DP, f_50), BLOCKIO_SIG, 0, 1, 2, 224, 0 },

  { 113,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_DP, f_50_m), BLOCKIO_SIG, 0, 1, 2, 226, 0 },

  { 114,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_DP, MultiportSwitch_h), BLOCKIO_SIG, 0, 1, 2, 228, 0
  },

  { 115, "dp/Control Systems/DP control/Saturation", 0, "", offsetof(BlockIO_DP,
    Saturation_a), BLOCKIO_SIG, 23, 5, 2, 230, 0 },

  { 116, "dp/Control Systems/Thruster setting Switch", 0, "", offsetof
    (BlockIO_DP, ThrustersettingSwitch), BLOCKIO_SIG, 21, 7, 2, 232, 0 },

  { 117, "dp/Control Systems/Saturation", 0, "", offsetof(BlockIO_DP,
    Saturation_j), BLOCKIO_SIG, 21, 7, 2, 234, 0 },

  { 118, "dp/HMI/SIT zAI0", 0, "", offsetof(BlockIO_DP, SITzAI0), BLOCKIO_SIG, 0,
    1, 2, 236, 0 },

  { 119, "dp/HMI/Battery Bow Thruster", 0, "", offsetof(BlockIO_DP,
    BatteryBowThruster), BLOCKIO_SIG, 0, 1, 2, 238, 0 },

  { 120, "dp/HMI/SIT zAI1", 0, "", offsetof(BlockIO_DP, SITzAI1), BLOCKIO_SIG, 0,
    1, 2, 240, 0 },

  { 121, "dp/HMI/Battery Servo", 0, "", offsetof(BlockIO_DP, BatteryServo),
    BLOCKIO_SIG, 0, 1, 2, 242, 0 },

  { 122, "dp/HMI/SIT zAI2", 0, "", offsetof(BlockIO_DP, SITzAI2), BLOCKIO_SIG, 0,
    1, 2, 244, 0 },

  { 123, "dp/HMI/Battery Main", 0, "", offsetof(BlockIO_DP, BatteryMain),
    BLOCKIO_SIG, 0, 1, 2, 246, 0 },

  { 124, "dp/Naviagation Systems/Qualisys 6 DOF/QTM In1 FPS", 0, "", offsetof
    (BlockIO_DP, QTMIn1FPS), BLOCKIO_SIG, 30, 1, 2, 248, 0 },

  { 125, "dp/Plants/saturation/Saturation", 0, "", offsetof(BlockIO_DP,
    Saturation_l), BLOCKIO_SIG, 0, 1, 2, 250, 0 },

  { 126, "dp/Plants/saturation/Saturation1", 0, "", offsetof(BlockIO_DP,
    Saturation1), BLOCKIO_SIG, 0, 1, 2, 252, 0 },

  { 127, "dp/Plants/saturation/Saturation2", 0, "", offsetof(BlockIO_DP,
    Saturation2), BLOCKIO_SIG, 0, 1, 2, 254, 0 },

  { 128, "dp/Plants/saturation/plant tau_surge", 0, "", offsetof(BlockIO_DP,
    planttau_surge), BLOCKIO_SIG, 0, 1, 2, 256, 0 },

  { 129, "dp/Plants/saturation/plant tau_sway", 0, "", offsetof(BlockIO_DP,
    planttau_sway), BLOCKIO_SIG, 0, 1, 2, 258, 0 },

  { 130, "dp/Plants/saturation/plant tau_yaw", 0, "", offsetof(BlockIO_DP,
    planttau_yaw), BLOCKIO_SIG, 0, 1, 2, 260, 0 },

  { 131, "dp/Plants/plant u_1", 0, "", offsetof(BlockIO_DP, plantu_1),
    BLOCKIO_SIG, 0, 1, 2, 262, 0 },

  { 132, "dp/Plants/plant u_2", 0, "", offsetof(BlockIO_DP, plantu_2),
    BLOCKIO_SIG, 0, 1, 2, 264, 0 },

  { 133, "dp/Plants/plant u_3", 0, "", offsetof(BlockIO_DP, plantu_3),
    BLOCKIO_SIG, 0, 1, 2, 266, 0 },

  { 134, "dp/Plants/plant u_4", 0, "", offsetof(BlockIO_DP, plantu_4),
    BLOCKIO_SIG, 0, 1, 2, 268, 0 },

  { 135, "dp/Plants/plant u_5", 0, "", offsetof(BlockIO_DP, plantu_5),
    BLOCKIO_SIG, 0, 1, 2, 270, 0 },

  { 136, "dp/Plants/plant BT power", 0, "", offsetof(BlockIO_DP, plantBTpower),
    BLOCKIO_SIG, 0, 1, 2, 272, 0 },

  { 137, "dp/Plants/plant VSP speed", 0, "", offsetof(BlockIO_DP, plantVSPspeed),
    BLOCKIO_SIG, 0, 1, 2, 274, 0 },

  { 138, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r", 0, "",
    offsetof(BlockIO_DP, N_r), BLOCKIO_SIG, 0, 1, 2, 276, 0 },

  { 139, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v", 0, "",
    offsetof(BlockIO_DP, N_v), BLOCKIO_SIG, 0, 1, 2, 278, 0 },

  { 140, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u", 0, "",
    offsetof(BlockIO_DP, X_u), BLOCKIO_SIG, 0, 1, 2, 280, 0 },

  { 141, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v", 0, "",
    offsetof(BlockIO_DP, Y_v), BLOCKIO_SIG, 0, 1, 2, 282, 0 },

  { 142, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr", 0, "",
    offsetof(BlockIO_DP, Y_vr), BLOCKIO_SIG, 0, 1, 2, 284, 0 },

  { 143,
    "dp/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Linear Dampning matrix",
    0, "", offsetof(BlockIO_DP, LinearDampningmatrix), BLOCKIO_SIG, 32, 9, 2,
    286, 0 },

  { 144, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0",
    0, "", offsetof(BlockIO_DP, psi_0), BLOCKIO_SIG, 0, 1, 2, 288, 0 },

  { 145, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0", 0,
    "", offsetof(BlockIO_DP, x_0), BLOCKIO_SIG, 0, 1, 2, 290, 0 },

  { 146, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0", 0,
    "", offsetof(BlockIO_DP, y_0), BLOCKIO_SIG, 0, 1, 2, 292, 0 },

  { 147, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0", 0,
    "", offsetof(BlockIO_DP, r_0), BLOCKIO_SIG, 0, 1, 2, 294, 0 },

  { 148, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0", 0,
    "", offsetof(BlockIO_DP, u_0), BLOCKIO_SIG, 0, 1, 2, 296, 0 },

  { 149, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0", 0,
    "", offsetof(BlockIO_DP, v_0), BLOCKIO_SIG, 0, 1, 2, 298, 0 },

  { 150, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Integrator", 0, "",
    offsetof(BlockIO_DP, Integrator_d), BLOCKIO_SIG, 20, 3, 2, 300, 0 },

  { 151, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Integrator1", 0, "",
    offsetof(BlockIO_DP, Integrator1), BLOCKIO_SIG, 20, 3, 2, 302, 0 },

  { 152, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_11", 0, "",
    offsetof(BlockIO_DP, M_11), BLOCKIO_SIG, 0, 1, 2, 304, 0 },

  { 153, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_22", 0, "",
    offsetof(BlockIO_DP, M_22), BLOCKIO_SIG, 0, 1, 2, 306, 0 },

  { 154, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m x_g", 0, "",
    offsetof(BlockIO_DP, mx_g), BLOCKIO_SIG, 0, 1, 2, 308, 0 },

  { 155, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_32", 0, "",
    offsetof(BlockIO_DP, M_32), BLOCKIO_SIG, 0, 1, 2, 310, 0 },

  { 156, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_23", 0, "",
    offsetof(BlockIO_DP, M_23), BLOCKIO_SIG, 0, 1, 2, 312, 0 },

  { 157, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_33", 0, "",
    offsetof(BlockIO_DP, M_33), BLOCKIO_SIG, 0, 1, 2, 314, 0 },

  { 158, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M", 0, "",
    offsetof(BlockIO_DP, M), BLOCKIO_SIG, 32, 9, 2, 316, 0 },

  { 159, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Inverse", 0,
    "", offsetof(BlockIO_DP, Inverse), BLOCKIO_SIG, 32, 9, 2, 318, 0 },

  { 160, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Product1", 0, "",
    offsetof(BlockIO_DP, Product1), BLOCKIO_SIG, 20, 3, 2, 320, 0 },

  { 161, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R11", 0, "",
    offsetof(BlockIO_DP, R11_i), BLOCKIO_SIG, 0, 1, 2, 322, 0 },

  { 162, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R21", 0, "",
    offsetof(BlockIO_DP, R21_e), BLOCKIO_SIG, 0, 1, 2, 324, 0 },

  { 163, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R12", 0, "",
    offsetof(BlockIO_DP, R12_a), BLOCKIO_SIG, 0, 1, 2, 326, 0 },

  { 164, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R22", 0, "",
    offsetof(BlockIO_DP, R22_f), BLOCKIO_SIG, 0, 1, 2, 328, 0 },

  { 165, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R(psi)", 0,
    "", offsetof(BlockIO_DP, Rpsi), BLOCKIO_SIG, 32, 9, 2, 330, 0 },

  { 166, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Product3", 0, "",
    offsetof(BlockIO_DP, Product3), BLOCKIO_SIG, 20, 3, 2, 332, 0 },

  { 167, "dp/Plants/Linear Simulator/eta_surge_hil", 0, "", offsetof(BlockIO_DP,
    eta_surge_hil), BLOCKIO_SIG, 0, 1, 2, 334, 0 },

  { 168, "dp/Plants/Linear Simulator/eta_sway_hil", 0, "", offsetof(BlockIO_DP,
    eta_sway_hil), BLOCKIO_SIG, 0, 1, 2, 336, 0 },

  { 169, "dp/Plants/Linear Simulator/eta_yaw_hil", 0, "", offsetof(BlockIO_DP,
    eta_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 338, 0 },

  { 170, "dp/Plants/Linear Simulator/etadot_surge_hil", 0, "", offsetof
    (BlockIO_DP, etadot_surge_hil), BLOCKIO_SIG, 0, 1, 2, 340, 0 },

  { 171, "dp/Plants/Linear Simulator/etadot_sway_hil", 0, "", offsetof
    (BlockIO_DP, etadot_sway_hil), BLOCKIO_SIG, 0, 1, 2, 342, 0 },

  { 172, "dp/Plants/Linear Simulator/etadot_yaw_hil", 0, "", offsetof(BlockIO_DP,
    etadot_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 344, 0 },

  { 173, "dp/Plants/Linear Simulator/nu_surge_hil", 0, "", offsetof(BlockIO_DP,
    nu_surge_hil), BLOCKIO_SIG, 0, 1, 2, 346, 0 },

  { 174, "dp/Plants/Linear Simulator/nu_sway_hil", 0, "", offsetof(BlockIO_DP,
    nu_sway_hil), BLOCKIO_SIG, 0, 1, 2, 348, 0 },

  { 175, "dp/Plants/Linear Simulator/nu_yaw_hil", 0, "", offsetof(BlockIO_DP,
    nu_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 350, 0 },

  { 176, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Sum", 0, "",
    offsetof(BlockIO_DP, Sum_k), BLOCKIO_SIG, 20, 3, 2, 352, 0 },

  { 177, "dp/Plants/Linear Simulator/Linear Vessel Dynamics/Product2", 0, "",
    offsetof(BlockIO_DP, Product2), BLOCKIO_SIG, 20, 3, 2, 354, 0 },

  { 178, "dp/Plants/CSE1/Bow Thruster/BT_D_Gain1", 0, "", offsetof(BlockIO_DP,
    BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2, 356, 0 },

  { 179, "dp/Plants/CSE1/Bow Thruster/BT_D_Gain2", 0, "", offsetof(BlockIO_DP,
    BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2, 358, 0 },

  { 180, "dp/Plants/CSE1/Bow Thruster/Add", 0, "", offsetof(BlockIO_DP, Add),
    BLOCKIO_SIG, 0, 1, 2, 360, 0 },

  { 181, "dp/Plants/CSE1/Bow Thruster/BT_L_Gain1", 0, "", offsetof(BlockIO_DP,
    BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2, 362, 0 },

  { 182, "dp/Plants/CSE1/Bow Thruster/BT_L_Gain2", 0, "", offsetof(BlockIO_DP,
    BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2, 364, 0 },

  { 183, "dp/Plants/CSE1/Bow Thruster/Neg", 0, "", offsetof(BlockIO_DP, Neg),
    BLOCKIO_SIG, 0, 1, 2, 366, 0 },

  { 184, "dp/Plants/CSE1/Bow Thruster/Sum1", 0, "", offsetof(BlockIO_DP, Sum1_h),
    BLOCKIO_SIG, 0, 1, 2, 368, 0 },

  { 185, "dp/Plants/CSE1/Bow Thruster/Sum2", 0, "", offsetof(BlockIO_DP, Sum2),
    BLOCKIO_SIG, 0, 1, 2, 370, 0 },

  { 186, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch", 0, "",
    offsetof(BlockIO_DP, Switch), BLOCKIO_SIG, 0, 1, 2, 372, 0 },

  { 187, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch2", 0, "",
    offsetof(BlockIO_DP, Switch2), BLOCKIO_SIG, 0, 1, 2, 374, 0 },

  { 188, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch", 0, "",
    offsetof(BlockIO_DP, Switch_j), BLOCKIO_SIG, 0, 1, 2, 376, 0 },

  { 189, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch2", 0, "",
    offsetof(BlockIO_DP, Switch2_m), BLOCKIO_SIG, 0, 1, 2, 378, 0 },

  { 190, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch", 0, "",
    offsetof(BlockIO_DP, Switch_h), BLOCKIO_SIG, 0, 1, 2, 380, 0 },

  { 191, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch2", 0, "",
    offsetof(BlockIO_DP, Switch2_a), BLOCKIO_SIG, 0, 1, 2, 382, 0 },

  { 192, "dp/Plants/CSE1/Voith Schneider Propeller /Sign", 0, "", offsetof
    (BlockIO_DP, Sign_a), BLOCKIO_SIG, 0, 1, 2, 384, 0 },

  { 193, "dp/Plants/CSE1/Voith Schneider Propeller /Product1", 0, "Port VPS_X",
    offsetof(BlockIO_DP, PortVPS_X), BLOCKIO_SIG, 0, 1, 2, 386, 0 },

  { 194, "dp/Plants/CSE1/Voith Schneider Propeller /-x", 0, "Port VPS_X",
    offsetof(BlockIO_DP, PortVPS_X_p), BLOCKIO_SIG, 0, 1, 2, 388, 0 },

  { 195, "dp/Plants/CSE1/Voith Schneider Propeller /Product2", 0, "Port VSP_Y",
    offsetof(BlockIO_DP, PortVSP_Y), BLOCKIO_SIG, 0, 1, 2, 390, 0 },

  { 196, "dp/Plants/CSE1/Voith Schneider Propeller /-y", 0, "Port VSP_Y",
    offsetof(BlockIO_DP, PortVSP_Y_d), BLOCKIO_SIG, 0, 1, 2, 392, 0 },

  { 197, "dp/Plants/CSE1/Voith Schneider Propeller /Product3", 0,
    "Starboard VSP_X", offsetof(BlockIO_DP, StarboardVSP_X), BLOCKIO_SIG, 0, 1,
    2, 394, 0 },

  { 198, "dp/Plants/CSE1/Voith Schneider Propeller /Product4", 0,
    "Starboard VSP_Y", offsetof(BlockIO_DP, StarboardVSP_Y), BLOCKIO_SIG, 0, 1,
    2, 396, 0 },

  { 199, "dp/Plants/CSE1/Voith Schneider Propeller /Servo1", 0, "", offsetof
    (BlockIO_DP, Servo1), BLOCKIO_SIG, 0, 1, 2, 398, 0 },

  { 200, "dp/Plants/CSE1/Voith Schneider Propeller /Servo2", 0, "", offsetof
    (BlockIO_DP, Servo2), BLOCKIO_SIG, 0, 1, 2, 400, 0 },

  { 201, "dp/Plants/CSE1/Voith Schneider Propeller /Servo3", 0, "", offsetof
    (BlockIO_DP, Servo3), BLOCKIO_SIG, 0, 1, 2, 402, 0 },

  { 202, "dp/Plants/CSE1/Voith Schneider Propeller /Servo4", 0, "", offsetof
    (BlockIO_DP, Servo4), BLOCKIO_SIG, 0, 1, 2, 404, 0 },

  { 203, "dp/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain", 0, "",
    offsetof(BlockIO_DP, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2, 406, 0 },

  { 204, "dp/Plants/CSE1/Voith Schneider Propeller /Sum", 0, "", offsetof
    (BlockIO_DP, Sum_n), BLOCKIO_SIG, 0, 1, 2, 408, 0 },

  { 205, "dp/Plants/CSE1/Voith Schneider Propeller /VSPS Port", 0, "", offsetof
    (BlockIO_DP, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 410, 0 },

  { 206, "dp/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard", 0, "",
    offsetof(BlockIO_DP, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2, 412, 0 },

  { 207,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_DP, Gain_bj), BLOCKIO_SIG, 15, 1, 2, 414, 0 },

  { 208,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_DP, Gain1_p), BLOCKIO_SIG, 15, 1, 2, 416, 0 },

  { 209,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_DP, Sum_h), BLOCKIO_SIG, 15, 1, 2, 418, 0 },

  { 210,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_DP, Gain_m), BLOCKIO_SIG, 15, 1, 2, 420, 0 },

  { 211,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_DP, Gain1_e), BLOCKIO_SIG, 15, 1, 2, 422, 0 },

  { 212,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_DP, Sum_e), BLOCKIO_SIG, 15, 1, 2, 424, 0 },

  { 213,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_DP, Gain_p), BLOCKIO_SIG, 15, 1, 2, 426, 0 },

  { 214,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_DP, Gain1_n), BLOCKIO_SIG, 15, 1, 2, 428, 0 },

  { 215,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_DP, Sum_ao), BLOCKIO_SIG, 15, 1, 2, 430, 0 },

  { 216,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_DP, Gain_h), BLOCKIO_SIG, 15, 1, 2, 432, 0 },

  { 217,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_DP, Gain1_d), BLOCKIO_SIG, 15, 1, 2, 434, 0 },

  { 218,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_DP, Sum_l), BLOCKIO_SIG, 15, 1, 2, 436, 0 },

  { 219,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_DP, Gain_m3), BLOCKIO_SIG, 15, 1, 2, 438, 0 },

  { 220,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_DP, Gain1_j), BLOCKIO_SIG, 15, 1, 2, 440, 0 },

  { 221,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_DP, Sum_p), BLOCKIO_SIG, 15, 1, 2, 442, 0 },

  { 222,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare), BLOCKIO_SIG, 3, 1, 2, 444, 0 },

  { 223,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_c), BLOCKIO_SIG, 3, 1, 2, 446, 0 },

  { 224,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_o), BLOCKIO_SIG, 3, 1, 2, 448, 0 },

  { 225,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_p), BLOCKIO_SIG, 3, 1, 2, 450, 0 },

  { 226,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 1/Compare",
    0, "", offsetof(BlockIO_DP, Compare_cj), BLOCKIO_SIG, 3, 1, 2, 452, 0 },

  { 227,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_i), BLOCKIO_SIG, 3, 1, 2, 454, 0 },

  { 228,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_is), BLOCKIO_SIG, 3, 1, 2, 456, 0 },

  { 229,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_p1), BLOCKIO_SIG, 3, 1, 2, 458, 0 },

  { 230,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_og), BLOCKIO_SIG, 3, 1, 2, 460, 0 },

  { 231,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_j), BLOCKIO_SIG, 3, 1, 2, 462, 0 },

  { 232,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_jt), BLOCKIO_SIG, 3, 1, 2, 464, 0 },

  { 233,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_g), BLOCKIO_SIG, 3, 1, 2, 466, 0 },

  { 234,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_b), BLOCKIO_SIG, 3, 1, 2, 468, 0 },

  { 235,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_d), BLOCKIO_SIG, 3, 1, 2, 470, 0 },

  { 236,
    "dp/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_DP, Compare_n), BLOCKIO_SIG, 3, 1, 2, 472, 0 },

  { 237, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic/LowerRelop1", 0, "",
    offsetof(BlockIO_DP, LowerRelop1), BLOCKIO_SIG, 8, 1, 2, 474, 0 },

  { 238, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic/UpperRelop", 0, "",
    offsetof(BlockIO_DP, UpperRelop), BLOCKIO_SIG, 8, 1, 2, 476, 0 },

  { 239, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic1/LowerRelop1", 0, "",
    offsetof(BlockIO_DP, LowerRelop1_b), BLOCKIO_SIG, 8, 1, 2, 478, 0 },

  { 240, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic1/UpperRelop", 0, "",
    offsetof(BlockIO_DP, UpperRelop_b), BLOCKIO_SIG, 8, 1, 2, 480, 0 },

  { 241, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic2/LowerRelop1", 0, "",
    offsetof(BlockIO_DP, LowerRelop1_bd), BLOCKIO_SIG, 8, 1, 2, 482, 0 },

  { 242, "dp/Plants/CSE1/Bow Thruster/Saturation Dynamic2/UpperRelop", 0, "",
    offsetof(BlockIO_DP, UpperRelop_h), BLOCKIO_SIG, 8, 1, 2, 484, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 6, 6, 1, 1, 1, 1, 1, 6, 1, 6,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 5, 5, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1,
  1, 1, 1, 1, 1, 3, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 7,
  1, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 3, 3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

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

static char* NI_CompiledModelName = "dp";
static char* NI_CompiledModelVersion = "1.21";
static char* NI_CompiledModelDateTime = "Sun Mar 16 18:55:56 2014";

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
   The undef allows us to access the real DP_P
   In the rest of the code DP_P is redefine to be the read-side
   of rtParameter.
 */
#undef DP_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &DP_P, sizeof(Parameters_DP));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka DP_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_DP));
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
             (Parameters_DP));

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
           (Parameters_DP));
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

#endif                                 // of NI_ROOTMODEL_DP
