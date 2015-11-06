/*
 * CSE1_CV3_1Straight.c
 *
 * Real-Time Workshop code generation for Simulink model "CSE1_CV3_1Straight.mdl".
 *
 * Model Version              : 1.296
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Fri Feb 14 09:47:35 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CSE1_CV3_1Straight.h"
#include "CSE1_CV3_1Straight_private.h"

/* Block signals (auto storage) */
BlockIO_CSE1_CV3_1Straight CSE1_CV3_1Straight_B;

/* Continuous states */
ContinuousStates_CSE1_CV3_1Stra CSE1_CV3_1Straight_X;

/* Block states (auto storage) */
D_Work_CSE1_CV3_1Straight CSE1_CV3_1Straight_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_CSE1_CV3_1Strai CSE1_CV3_1Straig_PrevZCSigState;

/* Real-time model */
RT_MODEL_CSE1_CV3_1Straight CSE1_CV3_1Straight_M_;
RT_MODEL_CSE1_CV3_1Straight *CSE1_CV3_1Straight_M = &CSE1_CV3_1Straight_M_;

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
  int_T nXc = 43;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y,x,
                nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  CSE1_CV3_1Straight_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++)
    x[i] = y[i] + (temp*f0[i]);
  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  CSE1_CV3_1Straight_output(0);
  CSE1_CV3_1Straight_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++)
    x[i] = y[i] + (temp*f1[i]);
  rtsiSetdX(si, f2);
  CSE1_CV3_1Straight_output(0);
  CSE1_CV3_1Straight_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++)
    x[i] = y[i] + (h*f2[i]);
  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  CSE1_CV3_1Straight_output(0);
  CSE1_CV3_1Straight_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void CSE1_CV3_1Straight_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(CSE1_CV3_1Straight_M)) {
    CSE1_CV3_1Straight_M->Timing.t[0] = rtsiGetT
      (&CSE1_CV3_1Straight_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&CSE1_CV3_1Straight_M->solverInfo,
                          ((CSE1_CV3_1Straight_M->Timing.clockTick0+1)*
      CSE1_CV3_1Straight_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T tmp[5];
    real_T tmp_0;
    int32_T i;
    real_T tmp_1[18];
    real_T tmp_2[4];
    real_T tmp_3[4];
    real_T tmp_4[9];
    real_T tmp_5[6];
    real_T tmp_6[3];
    real_T tmp_7[9];
    int32_T tmp_8;

    /* Gain: '<S289>/QTM In9 Residual' */
    CSE1_CV3_1Straight_B.QTMIn9Residual =
      CSE1_CV3_1Straight_P.QTMIn9Residual_Gain * CSE1_CV3_1Straight_B.QTMIn[8];

    /* Gain: '<S289>/QTM In3' */
    CSE1_CV3_1Straight_B.QTMIn3 = CSE1_CV3_1Straight_P.QTMIn3_Gain *
      CSE1_CV3_1Straight_B.QTMIn[2];

    /* Gain: '<S289>/mm2m x' */
    CSE1_CV3_1Straight_B.mm2mx = CSE1_CV3_1Straight_P.mm2mx_Gain *
      CSE1_CV3_1Straight_B.QTMIn3;

    /* Gain: '<S289>/QTM In4' */
    CSE1_CV3_1Straight_B.QTMIn4 = CSE1_CV3_1Straight_P.QTMIn4_Gain *
      CSE1_CV3_1Straight_B.QTMIn[3];

    /* Gain: '<S289>/mm2m y' */
    CSE1_CV3_1Straight_B.mm2my = CSE1_CV3_1Straight_P.mm2my_Gain *
      CSE1_CV3_1Straight_B.QTMIn4;

    /* Gain: '<S289>/QTM In6' */
    CSE1_CV3_1Straight_B.QTMIn6 = CSE1_CV3_1Straight_P.QTMIn6_Gain *
      CSE1_CV3_1Straight_B.QTMIn[5];

    /* Gain: '<S289>/d2r yaw' */
    CSE1_CV3_1Straight_B.d2ryaw = CSE1_CV3_1Straight_P.d2ryaw_Gain *
      CSE1_CV3_1Straight_B.QTMIn6;

    /* Outputs for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Constant: '<S5>/Enable Linear Simulator'
     *  EnablePort: '<S296>/Enable'
     */
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M) && rtmIsMajorTimeStep
        (CSE1_CV3_1Straight_M)) {
      if (CSE1_CV3_1Straight_P.EnableLinearSimulator_Value > 0.0) {
        if (CSE1_CV3_1Straight_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S309>/Integrator' */
          if (rtmIsFirstInitCond(CSE1_CV3_1Straight_M)) {
            CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[0] = 0.0;
            CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[1] = 0.0;
            CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[2] = 0.0;
          }

          CSE1_CV3_1Straight_DWork.Integrator_IWORK_c.IcNeedsLoading = 1;

          /* Integrator Block: '<S309>/Integrator1' */
          if (rtmIsFirstInitCond(CSE1_CV3_1Straight_M)) {
            CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[0] = 0.0;
            CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[1] = 0.0;
            CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[2] = 0.0;
          }

          CSE1_CV3_1Straight_DWork.Integrator1_IWORK_f.IcNeedsLoading = 1;
          CSE1_CV3_1Straight_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (CSE1_CV3_1Straight_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
          CSE1_CV3_1Straight_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (CSE1_CV3_1Straight_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Gain: '<S310>/-N_r' incorporates:
         *  Constant: '<S310>/N_r'
         */
        CSE1_CV3_1Straight_B.N_r_g = CSE1_CV3_1Straight_P.N_r_Gain_i *
          CSE1_CV3_1Straight_P.N_r_Value_j;

        /* Gain: '<S310>/-N_v' incorporates:
         *  Constant: '<S310>/N_v'
         */
        CSE1_CV3_1Straight_B.N_v_k = CSE1_CV3_1Straight_P.N_v_Gain_l *
          CSE1_CV3_1Straight_P.N_v_Value_c;

        /* Gain: '<S310>/-X_u' incorporates:
         *  Constant: '<S310>/X_u'
         */
        CSE1_CV3_1Straight_B.X_u_h = CSE1_CV3_1Straight_P.X_u_Gain_k *
          CSE1_CV3_1Straight_P.X_u_Value_m;

        /* Gain: '<S310>/-Y_v' incorporates:
         *  Constant: '<S310>/Y_v'
         */
        CSE1_CV3_1Straight_B.Y_v_n = CSE1_CV3_1Straight_P.Y_v_Gain_d2 *
          CSE1_CV3_1Straight_P.Y_v_Value_kr;

        /* Gain: '<S310>/-Y_vr' incorporates:
         *  Constant: '<S310>/Y_r'
         */
        CSE1_CV3_1Straight_B.Y_vr_c = CSE1_CV3_1Straight_P.Y_vr_Gain_j *
          CSE1_CV3_1Straight_P.Y_r_Value_m;

        /* Reshape: '<S310>/Linear Dampning matrix' incorporates:
         *  Constant: '<S310>/D_L_12'
         *  Constant: '<S310>/D_L_13'
         *  Constant: '<S310>/D_L_21'
         *  Constant: '<S310>/D_L_31'
         */
        CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[0] =
          CSE1_CV3_1Straight_B.X_u_h;
        CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[1] =
          CSE1_CV3_1Straight_P.D_L_21_Value_a;
        CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[2] =
          CSE1_CV3_1Straight_P.D_L_31_Value_k;
        CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[3] =
          CSE1_CV3_1Straight_P.D_L_12_Value_a;
        CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[4] =
          CSE1_CV3_1Straight_B.Y_v_n;
        CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[5] =
          CSE1_CV3_1Straight_B.N_v_k;
        CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[6] =
          CSE1_CV3_1Straight_P.D_L_13_Value_k;
        CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[7] =
          CSE1_CV3_1Straight_B.Y_vr_c;
        CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[8] =
          CSE1_CV3_1Straight_B.N_r_g;

        /* Constant: '<S311>/psi_0' */
        CSE1_CV3_1Straight_B.psi_0 = CSE1_CV3_1Straight_P.psi_0_Value;

        /* Constant: '<S311>/x_0' */
        CSE1_CV3_1Straight_B.x_0 = CSE1_CV3_1Straight_P.x_0_Value;

        /* Constant: '<S311>/y_0' */
        CSE1_CV3_1Straight_B.y_0 = CSE1_CV3_1Straight_P.y_0_Value;

        /* Constant: '<S312>/r_0' */
        CSE1_CV3_1Straight_B.r_0 = CSE1_CV3_1Straight_P.r_0_Value;

        /* Constant: '<S312>/u_0' */
        CSE1_CV3_1Straight_B.u_0 = CSE1_CV3_1Straight_P.u_0_Value;

        /* Constant: '<S312>/v_0' */
        CSE1_CV3_1Straight_B.v_0 = CSE1_CV3_1Straight_P.v_0_Value;
      }

      /* Integrator Block: '<S309>/Integrator'
       */
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &CSE1_CV3_1Straig_PrevZCSigState.Integrator_Reset_ZCE_p,
                           CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_ !=
            0.0 || CSE1_CV3_1Straight_DWork.Integrator_IWORK_c.IcNeedsLoading) {
          CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[0] =
            CSE1_CV3_1Straight_B.u_0;
          CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[1] =
            CSE1_CV3_1Straight_B.v_0;
          CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[2] =
            CSE1_CV3_1Straight_B.r_0;
        }

        CSE1_CV3_1Straight_DWork.Integrator_IWORK_c.IcNeedsLoading = 0;
      }

      CSE1_CV3_1Straight_B.Integrator_e[0] =
        CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[0];
      CSE1_CV3_1Straight_B.Integrator_e[1] =
        CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[1];
      CSE1_CV3_1Straight_B.Integrator_e[2] =
        CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[2];

      /* Integrator Block: '<S309>/Integrator1'
       */
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &CSE1_CV3_1Straig_PrevZCSigState.Integrator1_Reset_ZCE_j,
                           CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_ !=
            0.0 || CSE1_CV3_1Straight_DWork.Integrator1_IWORK_f.IcNeedsLoading)
        {
          CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[0] =
            CSE1_CV3_1Straight_B.x_0;
          CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[1] =
            CSE1_CV3_1Straight_B.y_0;
          CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[2] =
            CSE1_CV3_1Straight_B.psi_0;
        }

        CSE1_CV3_1Straight_DWork.Integrator1_IWORK_f.IcNeedsLoading = 0;
      }

      CSE1_CV3_1Straight_B.Integrator1_o[0] =
        CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[0];
      CSE1_CV3_1Straight_B.Integrator1_o[1] =
        CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[1];
      CSE1_CV3_1Straight_B.Integrator1_o[2] =
        CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[2];
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Sum: '<S313>/M_11' incorporates:
         *  Constant: '<S313>/X_udot'
         *  Constant: '<S313>/m'
         */
        CSE1_CV3_1Straight_B.M_11_a = CSE1_CV3_1Straight_P.m_Value_d -
          CSE1_CV3_1Straight_P.X_udot_Value_b;

        /* Sum: '<S313>/M_22' incorporates:
         *  Constant: '<S313>/Y_vdot'
         *  Constant: '<S313>/m'
         */
        CSE1_CV3_1Straight_B.M_22_f = CSE1_CV3_1Straight_P.m_Value_d -
          CSE1_CV3_1Straight_P.Y_vdot_Value_i;

        /* Product: '<S313>/m x_g' incorporates:
         *  Constant: '<S313>/m'
         *  Constant: '<S313>/x_g'
         */
        CSE1_CV3_1Straight_B.mx_g_p = CSE1_CV3_1Straight_P.m_Value_d *
          CSE1_CV3_1Straight_P.x_g_Value_p;

        /* Sum: '<S313>/M_32' incorporates:
         *  Constant: '<S313>/N_vdot'
         */
        CSE1_CV3_1Straight_B.M_32_l = CSE1_CV3_1Straight_B.mx_g_p -
          CSE1_CV3_1Straight_P.N_vdot_Value_d;

        /* Sum: '<S313>/M_23' incorporates:
         *  Constant: '<S313>/Y_rdot'
         */
        CSE1_CV3_1Straight_B.M_23_j = CSE1_CV3_1Straight_B.mx_g_p -
          CSE1_CV3_1Straight_P.Y_rdot_Value_e;

        /* Sum: '<S313>/M_33' incorporates:
         *  Constant: '<S313>/I_z'
         *  Constant: '<S313>/N_rdot'
         */
        CSE1_CV3_1Straight_B.M_33_a = CSE1_CV3_1Straight_P.I_z_Value_a -
          CSE1_CV3_1Straight_P.N_rdot_Value_h;

        /* Reshape: '<S313>/M' incorporates:
         *  Constant: '<S313>/M_12'
         *  Constant: '<S313>/M_13'
         *  Constant: '<S313>/M_21'
         *  Constant: '<S313>/M_31'
         */
        CSE1_CV3_1Straight_B.M[0] = CSE1_CV3_1Straight_B.M_11_a;
        CSE1_CV3_1Straight_B.M[1] = CSE1_CV3_1Straight_P.M_21_Value_c;
        CSE1_CV3_1Straight_B.M[2] = CSE1_CV3_1Straight_P.M_31_Value_j;
        CSE1_CV3_1Straight_B.M[3] = CSE1_CV3_1Straight_P.M_12_Value_h;
        CSE1_CV3_1Straight_B.M[4] = CSE1_CV3_1Straight_B.M_22_f;
        CSE1_CV3_1Straight_B.M[5] = CSE1_CV3_1Straight_B.M_32_l;
        CSE1_CV3_1Straight_B.M[6] = CSE1_CV3_1Straight_P.M_13_Value_g;
        CSE1_CV3_1Straight_B.M[7] = CSE1_CV3_1Straight_B.M_23_j;
        CSE1_CV3_1Straight_B.M[8] = CSE1_CV3_1Straight_B.M_33_a;

        /* Product Block: '<S313>/Inverse' */
        {
          static const int_T dims[3] = { 3, 3, 3 };

          rt_MatDivRR_Dbl(CSE1_CV3_1Straight_B.Inverse, CSE1_CV3_1Straight_B.M,
                          &CSE1_CV3_1Straight_DWork.Inverse_DWORK4[0], (real_T*)
                          &CSE1_CV3_1Straight_DWork.Pseudoinverse_X[0],
                          &CSE1_CV3_1Straight_DWork.Inverse_DWORK2[0], (real_T*)
                          &CSE1_CV3_1Straight_DWork.Inverse_DWORK3[0],
                          &dims[0]);
        }
      }

      /* Fcn: '<S314>/R11' */
      CSE1_CV3_1Straight_B.R11_d = cos(CSE1_CV3_1Straight_B.Integrator1_o[2]);

      /* Fcn: '<S314>/R21' */
      CSE1_CV3_1Straight_B.R21_e = sin(CSE1_CV3_1Straight_B.Integrator1_o[2]);

      /* Fcn: '<S314>/R12' */
      CSE1_CV3_1Straight_B.R12_a = -1.0 * sin
        (CSE1_CV3_1Straight_B.Integrator1_o[2]);

      /* Fcn: '<S314>/R22' */
      CSE1_CV3_1Straight_B.R22_g = cos(CSE1_CV3_1Straight_B.Integrator1_o[2]);

      /* Reshape: '<S314>/R(psi)' incorporates:
       *  Constant: '<S314>/R13'
       *  Constant: '<S314>/R23'
       *  Constant: '<S314>/R31'
       *  Constant: '<S314>/R32'
       *  Constant: '<S314>/R33'
       */
      CSE1_CV3_1Straight_B.Rpsi_a[0] = CSE1_CV3_1Straight_B.R11_d;
      CSE1_CV3_1Straight_B.Rpsi_a[1] = CSE1_CV3_1Straight_B.R21_e;
      CSE1_CV3_1Straight_B.Rpsi_a[2] = CSE1_CV3_1Straight_P.R31_Value_f;
      CSE1_CV3_1Straight_B.Rpsi_a[3] = CSE1_CV3_1Straight_B.R12_a;
      CSE1_CV3_1Straight_B.Rpsi_a[4] = CSE1_CV3_1Straight_B.R22_g;
      CSE1_CV3_1Straight_B.Rpsi_a[5] = CSE1_CV3_1Straight_P.R32_Value_ag;
      CSE1_CV3_1Straight_B.Rpsi_a[6] = CSE1_CV3_1Straight_P.R13_Value_e;
      CSE1_CV3_1Straight_B.Rpsi_a[7] = CSE1_CV3_1Straight_P.R23_Value_p;
      CSE1_CV3_1Straight_B.Rpsi_a[8] = CSE1_CV3_1Straight_P.R33_Value_en;
      for (i = 0; i < 3; i++) {
        /* Product: '<S309>/Product1' */
        CSE1_CV3_1Straight_B.Product1_ha[i] = 0.0;
        CSE1_CV3_1Straight_B.Product1_ha[i] =
          CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[i] *
          CSE1_CV3_1Straight_B.Integrator_e[0] +
          CSE1_CV3_1Straight_B.Product1_ha[i];
        CSE1_CV3_1Straight_B.Product1_ha[i] =
          CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[i + 3] *
          CSE1_CV3_1Straight_B.Integrator_e[1] +
          CSE1_CV3_1Straight_B.Product1_ha[i];
        CSE1_CV3_1Straight_B.Product1_ha[i] =
          CSE1_CV3_1Straight_B.LinearDampningmatrix_pr[i + 6] *
          CSE1_CV3_1Straight_B.Integrator_e[2] +
          CSE1_CV3_1Straight_B.Product1_ha[i];

        /* Product: '<S309>/Product3' */
        CSE1_CV3_1Straight_B.Product3_j[i] = 0.0;
        CSE1_CV3_1Straight_B.Product3_j[i] = CSE1_CV3_1Straight_B.Rpsi_a[i] *
          CSE1_CV3_1Straight_B.Integrator_e[0] +
          CSE1_CV3_1Straight_B.Product3_j[i];
        CSE1_CV3_1Straight_B.Product3_j[i] = CSE1_CV3_1Straight_B.Rpsi_a[i + 3] *
          CSE1_CV3_1Straight_B.Integrator_e[1] +
          CSE1_CV3_1Straight_B.Product3_j[i];
        CSE1_CV3_1Straight_B.Product3_j[i] = CSE1_CV3_1Straight_B.Rpsi_a[i + 6] *
          CSE1_CV3_1Straight_B.Integrator_e[2] +
          CSE1_CV3_1Straight_B.Product3_j[i];
      }

      /* Gain: '<S296>/eta_surge_hil' */
      CSE1_CV3_1Straight_B.eta_surge_hil =
        CSE1_CV3_1Straight_P.eta_surge_hil_Gain *
        CSE1_CV3_1Straight_B.Integrator1_o[0];

      /* Gain: '<S296>/eta_sway_hil' */
      CSE1_CV3_1Straight_B.eta_sway_hil = CSE1_CV3_1Straight_P.eta_sway_hil_Gain
        * CSE1_CV3_1Straight_B.Integrator1_o[1];

      /* Gain: '<S296>/eta_yaw_hil' */
      CSE1_CV3_1Straight_B.eta_yaw_hil = CSE1_CV3_1Straight_P.eta_yaw_hil_Gain *
        CSE1_CV3_1Straight_B.Integrator1_o[2];

      /* Gain: '<S296>/etadot_surge_hil' */
      CSE1_CV3_1Straight_B.etadot_surge_hil =
        CSE1_CV3_1Straight_P.etadot_surge_hil_Gain *
        CSE1_CV3_1Straight_B.Product3_j[0];

      /* Gain: '<S296>/etadot_sway_hil' */
      CSE1_CV3_1Straight_B.etadot_sway_hil =
        CSE1_CV3_1Straight_P.etadot_sway_hil_Gain *
        CSE1_CV3_1Straight_B.Product3_j[1];

      /* Gain: '<S296>/etadot_yaw_hil' */
      CSE1_CV3_1Straight_B.etadot_yaw_hil =
        CSE1_CV3_1Straight_P.etadot_yaw_hil_Gain *
        CSE1_CV3_1Straight_B.Product3_j[2];

      /* Gain: '<S296>/nu_surge_hil' */
      CSE1_CV3_1Straight_B.nu_surge_hil = CSE1_CV3_1Straight_P.nu_surge_hil_Gain
        * CSE1_CV3_1Straight_B.Integrator_e[0];

      /* Gain: '<S296>/nu_sway_hil' */
      CSE1_CV3_1Straight_B.nu_sway_hil = CSE1_CV3_1Straight_P.nu_sway_hil_Gain *
        CSE1_CV3_1Straight_B.Integrator_e[1];

      /* Gain: '<S296>/nu_yaw_hil' */
      CSE1_CV3_1Straight_B.nu_yaw_hil = CSE1_CV3_1Straight_P.nu_yaw_hil_Gain *
        CSE1_CV3_1Straight_B.Integrator_e[2];
    }

    /* end of Outputs for SubSystem: '<S5>/Linear Simulator' */

    /* MultiPortSwitch: '<S4>/Eta Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)CSE1_CV3_1Straight_P.ControllerInputSelector_Value == 0) {
      CSE1_CV3_1Straight_B.EtaSwitch[0] = CSE1_CV3_1Straight_B.mm2mx;
      CSE1_CV3_1Straight_B.EtaSwitch[1] = CSE1_CV3_1Straight_B.mm2my;
      CSE1_CV3_1Straight_B.EtaSwitch[2] = CSE1_CV3_1Straight_B.d2ryaw;
    } else {
      CSE1_CV3_1Straight_B.EtaSwitch[0] = CSE1_CV3_1Straight_B.eta_surge_hil;
      CSE1_CV3_1Straight_B.EtaSwitch[1] = CSE1_CV3_1Straight_B.eta_sway_hil;
      CSE1_CV3_1Straight_B.EtaSwitch[2] = CSE1_CV3_1Straight_B.eta_yaw_hil;
    }

    /* Gain: '<S4>/eta_surge' */
    CSE1_CV3_1Straight_B.eta_surge = CSE1_CV3_1Straight_P.eta_surge_Gain *
      CSE1_CV3_1Straight_B.EtaSwitch[0];

    /* Gain: '<S4>/eta_sway' */
    CSE1_CV3_1Straight_B.eta_sway = CSE1_CV3_1Straight_P.eta_sway_Gain *
      CSE1_CV3_1Straight_B.EtaSwitch[1];

    /* Gain: '<S4>/eta_yaw' */
    CSE1_CV3_1Straight_B.eta_yaw = CSE1_CV3_1Straight_P.eta_yaw_Gain *
      CSE1_CV3_1Straight_B.EtaSwitch[2];

    /* Gain: '<S289>/QTM In8' */
    CSE1_CV3_1Straight_B.QTMIn8 = CSE1_CV3_1Straight_P.QTMIn8_Gain *
      CSE1_CV3_1Straight_B.QTMIn[7];

    /* Gain: '<S289>/d2r roll' */
    CSE1_CV3_1Straight_B.d2rroll = CSE1_CV3_1Straight_P.d2rroll_Gain *
      CSE1_CV3_1Straight_B.QTMIn8;

    /* Gain: '<S289>/QTM In7' */
    CSE1_CV3_1Straight_B.QTMIn7 = CSE1_CV3_1Straight_P.QTMIn7_Gain *
      CSE1_CV3_1Straight_B.QTMIn[6];

    /* Gain: '<S289>/d2r pitch' */
    CSE1_CV3_1Straight_B.d2rpitch = CSE1_CV3_1Straight_P.d2rpitch_Gain *
      CSE1_CV3_1Straight_B.QTMIn7;

    /* Trigonometry: '<S290>/sin(theta)' */
    CSE1_CV3_1Straight_B.sintheta[0] = sin(CSE1_CV3_1Straight_B.d2rroll);
    CSE1_CV3_1Straight_B.sintheta[1] = sin(CSE1_CV3_1Straight_B.d2rpitch);
    CSE1_CV3_1Straight_B.sintheta[2] = sin(CSE1_CV3_1Straight_B.d2ryaw);

    /* Trigonometry: '<S290>/cos(theta)' */
    CSE1_CV3_1Straight_B.costheta[0] = cos(CSE1_CV3_1Straight_B.d2rroll);
    CSE1_CV3_1Straight_B.costheta[1] = cos(CSE1_CV3_1Straight_B.d2rpitch);
    CSE1_CV3_1Straight_B.costheta[2] = cos(CSE1_CV3_1Straight_B.d2ryaw);

    /* Fcn: '<S290>/R11' */
    CSE1_CV3_1Straight_B.R11 = CSE1_CV3_1Straight_B.costheta[1] *
      CSE1_CV3_1Straight_B.costheta[2];

    /* Fcn: '<S290>/R21 ' */
    CSE1_CV3_1Straight_B.R21 = CSE1_CV3_1Straight_B.sintheta[0] *
      CSE1_CV3_1Straight_B.sintheta[1] * CSE1_CV3_1Straight_B.costheta[2] +
      (-CSE1_CV3_1Straight_B.costheta[0]) * CSE1_CV3_1Straight_B.sintheta[2];

    /* Fcn: '<S290>/R31 ' */
    CSE1_CV3_1Straight_B.R31 = CSE1_CV3_1Straight_B.costheta[0] *
      CSE1_CV3_1Straight_B.sintheta[1] * CSE1_CV3_1Straight_B.costheta[2] +
      CSE1_CV3_1Straight_B.sintheta[0] * CSE1_CV3_1Straight_B.sintheta[2];

    /* Fcn: '<S290>/R12' */
    CSE1_CV3_1Straight_B.R12 = CSE1_CV3_1Straight_B.costheta[1] *
      CSE1_CV3_1Straight_B.sintheta[2];

    /* Fcn: '<S290>/R22' */
    CSE1_CV3_1Straight_B.R22 = CSE1_CV3_1Straight_B.sintheta[0] *
      CSE1_CV3_1Straight_B.sintheta[1] * CSE1_CV3_1Straight_B.sintheta[2] +
      CSE1_CV3_1Straight_B.costheta[0] * CSE1_CV3_1Straight_B.costheta[2];

    /* Fcn: '<S290>/R32' */
    CSE1_CV3_1Straight_B.R32 = CSE1_CV3_1Straight_B.costheta[0] *
      CSE1_CV3_1Straight_B.sintheta[1] * CSE1_CV3_1Straight_B.sintheta[2] +
      (-CSE1_CV3_1Straight_B.sintheta[0]) * CSE1_CV3_1Straight_B.costheta[2];

    /* Fcn: '<S290>/R13' */
    CSE1_CV3_1Straight_B.R13 = -CSE1_CV3_1Straight_B.sintheta[1];

    /* Fcn: '<S290>/R23' */
    CSE1_CV3_1Straight_B.R23 = CSE1_CV3_1Straight_B.sintheta[0] *
      CSE1_CV3_1Straight_B.costheta[1];

    /* Fcn: '<S290>/R33' */
    CSE1_CV3_1Straight_B.R33 = CSE1_CV3_1Straight_B.costheta[0] *
      CSE1_CV3_1Straight_B.costheta[1];

    /* Reshape: '<S290>/Reshape 9x1->3x3' */
    CSE1_CV3_1Straight_B.Reshape9x13x3[0] = CSE1_CV3_1Straight_B.R11;
    CSE1_CV3_1Straight_B.Reshape9x13x3[1] = CSE1_CV3_1Straight_B.R21;
    CSE1_CV3_1Straight_B.Reshape9x13x3[2] = CSE1_CV3_1Straight_B.R31;
    CSE1_CV3_1Straight_B.Reshape9x13x3[3] = CSE1_CV3_1Straight_B.R12;
    CSE1_CV3_1Straight_B.Reshape9x13x3[4] = CSE1_CV3_1Straight_B.R22;
    CSE1_CV3_1Straight_B.Reshape9x13x3[5] = CSE1_CV3_1Straight_B.R32;
    CSE1_CV3_1Straight_B.Reshape9x13x3[6] = CSE1_CV3_1Straight_B.R13;
    CSE1_CV3_1Straight_B.Reshape9x13x3[7] = CSE1_CV3_1Straight_B.R23;
    CSE1_CV3_1Straight_B.Reshape9x13x3[8] = CSE1_CV3_1Straight_B.R33;

    /* Concatenate: '<S289>/Matrix Concatenate' incorporates:
     *  Constant: '<S289>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = CSE1_CV3_1Straight_B.Reshape9x13x3[3 * i];
      tmp_1[1 + 6 * i] = CSE1_CV3_1Straight_B.Reshape9x13x3[3 * i + 1];
      tmp_1[2 + 6 * i] = CSE1_CV3_1Straight_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = CSE1_CV3_1Straight_P.Constant1_Value[3 * i];
      tmp_1[4 + 6 * i] = CSE1_CV3_1Straight_P.Constant1_Value[3 * i + 1];
      tmp_1[5 + 6 * i] = CSE1_CV3_1Straight_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&CSE1_CV3_1Straight_B.MatrixConcatenate2[0]), (void *)
           &tmp_1[0], 18U * sizeof(real_T));

    /* Concatenate: '<S289>/Matrix Concatenate1' incorporates:
     *  Constant: '<S289>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = CSE1_CV3_1Straight_P.Constant1_Value[3 * i];
      tmp_1[1 + 6 * i] = CSE1_CV3_1Straight_P.Constant1_Value[3 * i + 1];
      tmp_1[2 + 6 * i] = CSE1_CV3_1Straight_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = CSE1_CV3_1Straight_B.Reshape9x13x3[3 * i];
      tmp_1[4 + 6 * i] = CSE1_CV3_1Straight_B.Reshape9x13x3[3 * i + 1];
      tmp_1[5 + 6 * i] = CSE1_CV3_1Straight_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&CSE1_CV3_1Straight_B.MatrixConcatenate2[18]), (void *)
           &tmp_1[0], 18U * sizeof(real_T));

    /* Gain: '<S289>/QTM In5' */
    CSE1_CV3_1Straight_B.QTMIn5 = CSE1_CV3_1Straight_P.QTMIn5_Gain *
      CSE1_CV3_1Straight_B.QTMIn[4];

    /* Gain: '<S289>/mm2m z' */
    CSE1_CV3_1Straight_B.mm2mz = CSE1_CV3_1Straight_P.mm2mz_Gain *
      CSE1_CV3_1Straight_B.QTMIn5;

    /* Derivative Block: '<S289>/nu' */
    {
      real_T t = CSE1_CV3_1Straight_M->Timing.t[0];
      real_T timeStampA = CSE1_CV3_1Straight_DWork.nu_RWORK.TimeStampA;
      real_T timeStampB = CSE1_CV3_1Straight_DWork.nu_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = CSE1_CV3_1Straight_B.nu;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank = &CSE1_CV3_1Straight_DWork.nu_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        CSE1_CV3_1Straight_B.nu[0] = (CSE1_CV3_1Straight_B.mm2mx - *lastBank++) /
          deltaT;
        CSE1_CV3_1Straight_B.nu[1] = (CSE1_CV3_1Straight_B.mm2my - *lastBank++) /
          deltaT;
        CSE1_CV3_1Straight_B.nu[2] = (CSE1_CV3_1Straight_B.mm2mz - *lastBank++) /
          deltaT;
        CSE1_CV3_1Straight_B.nu[3] = (CSE1_CV3_1Straight_B.d2rroll - *lastBank++)
          / deltaT;
        CSE1_CV3_1Straight_B.nu[4] = (CSE1_CV3_1Straight_B.d2rpitch - *lastBank
          ++) / deltaT;
        CSE1_CV3_1Straight_B.nu[5] = (CSE1_CV3_1Straight_B.d2ryaw - *lastBank++)
          / deltaT;
      }
    }

    /* Product: '<S289>/Product' */
    for (i = 0; i < 6; i++) {
      CSE1_CV3_1Straight_B.Product[i] = 0.0;
      for (tmp_8 = 0; tmp_8 < 6; tmp_8++) {
        CSE1_CV3_1Straight_B.Product[i] =
          CSE1_CV3_1Straight_B.MatrixConcatenate2[6 * tmp_8 + i] *
          CSE1_CV3_1Straight_B.nu[tmp_8] + CSE1_CV3_1Straight_B.Product[i];
      }
    }

    /* MultiPortSwitch: '<S4>/Nu Switch' incorporates:
     *  Constant: '<S4>/Controller Input Selector'
     */
    if ((int32_T)CSE1_CV3_1Straight_P.ControllerInputSelector_Value == 0) {
      CSE1_CV3_1Straight_B.NuSwitch[0] = CSE1_CV3_1Straight_B.Product[0];
      CSE1_CV3_1Straight_B.NuSwitch[1] = CSE1_CV3_1Straight_B.Product[1];
      CSE1_CV3_1Straight_B.NuSwitch[2] = CSE1_CV3_1Straight_B.Product[5];
    } else {
      CSE1_CV3_1Straight_B.NuSwitch[0] = CSE1_CV3_1Straight_B.nu_surge_hil;
      CSE1_CV3_1Straight_B.NuSwitch[1] = CSE1_CV3_1Straight_B.nu_sway_hil;
      CSE1_CV3_1Straight_B.NuSwitch[2] = CSE1_CV3_1Straight_B.nu_yaw_hil;
    }

    /* Gain: '<S4>/nu_surge' */
    CSE1_CV3_1Straight_B.nu_surge = CSE1_CV3_1Straight_P.nu_surge_Gain *
      CSE1_CV3_1Straight_B.NuSwitch[0];

    /* Gain: '<S4>/nu_sway' */
    CSE1_CV3_1Straight_B.nu_sway = CSE1_CV3_1Straight_P.nu_sway_Gain *
      CSE1_CV3_1Straight_B.NuSwitch[1];

    /* Gain: '<S4>/nu_yaw' */
    CSE1_CV3_1Straight_B.nu_yaw = CSE1_CV3_1Straight_P.nu_yaw_Gain *
      CSE1_CV3_1Straight_B.NuSwitch[2];
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Gain: '<S288>/Gain1' incorporates:
       *  Constant: '<S286>/psi_d'
       */
      CSE1_CV3_1Straight_B.Gain1 = CSE1_CV3_1Straight_P.Gain1_Gain *
        CSE1_CV3_1Straight_P.psi_d_Value;
    }

    /* TransferFcn Block: '<S219>/Transfer Fcn' */
    CSE1_CV3_1Straight_B.TransferFcn = CSE1_CV3_1Straight_P.TransferFcn_C*
      CSE1_CV3_1Straight_X.TransferFcn_CSTATE;

    /* TransferFcn Block: '<S219>/Transfer Fcn1' */
    CSE1_CV3_1Straight_B.TransferFcn1 = CSE1_CV3_1Straight_P.TransferFcn1_C*
      CSE1_CV3_1Straight_X.TransferFcn1_CSTATE;

    /* TransferFcn Block: '<S219>/Transfer Fcn2' */
    CSE1_CV3_1Straight_B.TransferFcn2 = CSE1_CV3_1Straight_P.TransferFcn2_C*
      CSE1_CV3_1Straight_X.TransferFcn2_CSTATE;

    /* MultiPortSwitch: '<S219>/Multiport Switch' incorporates:
     *  Constant: '<S219>/Enable eta_d LPF'
     *  Constant: '<S286>/x_d'
     *  Constant: '<S286>/y_d'
     */
    if ((int32_T)CSE1_CV3_1Straight_P.Enableeta_dLPF_Value == 0) {
      CSE1_CV3_1Straight_B.MultiportSwitch[0] = CSE1_CV3_1Straight_P.x_d_Value;
      CSE1_CV3_1Straight_B.MultiportSwitch[1] = CSE1_CV3_1Straight_P.y_d_Value;
      CSE1_CV3_1Straight_B.MultiportSwitch[2] = CSE1_CV3_1Straight_B.Gain1;
    } else {
      CSE1_CV3_1Straight_B.MultiportSwitch[0] = CSE1_CV3_1Straight_B.TransferFcn;
      CSE1_CV3_1Straight_B.MultiportSwitch[1] =
        CSE1_CV3_1Straight_B.TransferFcn1;
      CSE1_CV3_1Straight_B.MultiportSwitch[2] =
        CSE1_CV3_1Straight_B.TransferFcn2;
    }

    /* Gain: '<S219>/eta_d DP N' */
    CSE1_CV3_1Straight_B.eta_dDPN = CSE1_CV3_1Straight_P.eta_dDPN_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch[0];

    /* Gain: '<S219>/eta_d DP E' */
    CSE1_CV3_1Straight_B.eta_dDPE = CSE1_CV3_1Straight_P.eta_dDPE_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch[1];

    /* Gain: '<S219>/eta_d DP Psi' */
    CSE1_CV3_1Straight_B.eta_dDPPsi = CSE1_CV3_1Straight_P.eta_dDPPsi_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch[2];
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* RelationalOperator: '<S13>/Compare' incorporates:
       *  Constant: '<S13>/Constant'
       *  Constant: '<S1>/Control Mode'
       */
      CSE1_CV3_1Straight_B.Compare = (CSE1_CV3_1Straight_P.ControlMode_Value ==
        CSE1_CV3_1Straight_P.Constant_Value);

      /* Constant: '<S105>/q_x_0' */
      CSE1_CV3_1Straight_B.q_x_0 = CSE1_CV3_1Straight_P.q_x_0_Value;

      /* Constant: '<S105>/q_y_0' */
      CSE1_CV3_1Straight_B.q_y_0 = CSE1_CV3_1Straight_P.q_y_0_Value;
    }

    /* Integrator Block: '<S62>/Integrator'
     */
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &CSE1_CV3_1Straig_PrevZCSigState.Integrator_Reset_ZCE,
                         CSE1_CV3_1Straight_P.Resetq_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || CSE1_CV3_1Straight_P.Resetq_Value != 0.0 ||
          CSE1_CV3_1Straight_DWork.Integrator_IWORK.IcNeedsLoading) {
        CSE1_CV3_1Straight_X.Integrator_CSTATE[0] = CSE1_CV3_1Straight_B.q_x_0;
        CSE1_CV3_1Straight_X.Integrator_CSTATE[1] = CSE1_CV3_1Straight_B.q_y_0;
      }

      CSE1_CV3_1Straight_DWork.Integrator_IWORK.IcNeedsLoading = 0;
    }

    CSE1_CV3_1Straight_B.Integrator[0] = CSE1_CV3_1Straight_X.Integrator_CSTATE
      [0];
    CSE1_CV3_1Straight_B.Integrator[1] = CSE1_CV3_1Straight_X.Integrator_CSTATE
      [1];
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Constant: '<S187>/q_x_0' */
      CSE1_CV3_1Straight_B.q_x_0_c = CSE1_CV3_1Straight_P.q_x_0_Value_n;

      /* Constant: '<S187>/q_y_0' */
      CSE1_CV3_1Straight_B.q_y_0_p = CSE1_CV3_1Straight_P.q_y_0_Value_n;
    }

    /* Integrator Block: '<S135>/Integrator'
     */
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &CSE1_CV3_1Straig_PrevZCSigState.Integrator_Reset_ZCE_o,
                         CSE1_CV3_1Straight_P.Resetq_Value_d);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || CSE1_CV3_1Straight_P.Resetq_Value_d != 0.0 ||
          CSE1_CV3_1Straight_DWork.Integrator_IWORK_j.IcNeedsLoading) {
        CSE1_CV3_1Straight_X.Integrator_CSTATE_g[0] =
          CSE1_CV3_1Straight_B.q_x_0_c;
        CSE1_CV3_1Straight_X.Integrator_CSTATE_g[1] =
          CSE1_CV3_1Straight_B.q_y_0_p;
      }

      CSE1_CV3_1Straight_DWork.Integrator_IWORK_j.IcNeedsLoading = 0;
    }

    CSE1_CV3_1Straight_B.Integrator_i[0] =
      CSE1_CV3_1Straight_X.Integrator_CSTATE_g[0];
    CSE1_CV3_1Straight_B.Integrator_i[1] =
      CSE1_CV3_1Straight_X.Integrator_CSTATE_g[1];

    /* MultiPortSwitch: '<S1>/q switch' */
    if (CSE1_CV3_1Straight_B.Compare == 0) {
      CSE1_CV3_1Straight_B.qswitch[0] = CSE1_CV3_1Straight_B.Integrator[0];
      CSE1_CV3_1Straight_B.qswitch[1] = CSE1_CV3_1Straight_B.Integrator[1];
    } else {
      CSE1_CV3_1Straight_B.qswitch[0] = CSE1_CV3_1Straight_B.Integrator_i[0];
      CSE1_CV3_1Straight_B.qswitch[1] = CSE1_CV3_1Straight_B.Integrator_i[1];
    }

    /* Gain: '<S1>/q_x gain' */
    CSE1_CV3_1Straight_B.q_xgain = CSE1_CV3_1Straight_P.q_xgain_Gain *
      CSE1_CV3_1Straight_B.qswitch[0];

    /* Gain: '<S1>/q_y gain' */
    CSE1_CV3_1Straight_B.q_ygain = CSE1_CV3_1Straight_P.q_ygain_Gain *
      CSE1_CV3_1Straight_B.qswitch[1];
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Constant: '<S62>/s_0' */
      CSE1_CV3_1Straight_B.s_0 = CSE1_CV3_1Straight_P.s_0_Value;
    }

    /* Integrator Block: '<S62>/Integrator1'
     */
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &CSE1_CV3_1Straig_PrevZCSigState.Integrator1_Reset_ZCE,
                         CSE1_CV3_1Straight_P.Resets_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || CSE1_CV3_1Straight_P.Resets_Value != 0.0 ||
          CSE1_CV3_1Straight_DWork.Integrator1_IWORK.IcNeedsLoading) {
        CSE1_CV3_1Straight_X.Integrator1_CSTATE = CSE1_CV3_1Straight_B.s_0;
      }

      CSE1_CV3_1Straight_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
    }

    CSE1_CV3_1Straight_B.Integrator1 = CSE1_CV3_1Straight_X.Integrator1_CSTATE;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Constant: '<S135>/s_0' */
      CSE1_CV3_1Straight_B.s_0_d = CSE1_CV3_1Straight_P.s_0_Value_c;
    }

    /* Integrator Block: '<S135>/Integrator1'
     */
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &CSE1_CV3_1Straig_PrevZCSigState.Integrator1_Reset_ZCE_m,
                         CSE1_CV3_1Straight_P.Resets_Value_c);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || CSE1_CV3_1Straight_P.Resets_Value_c != 0.0 ||
          CSE1_CV3_1Straight_DWork.Integrator1_IWORK_h.IcNeedsLoading) {
        CSE1_CV3_1Straight_X.Integrator1_CSTATE_g = CSE1_CV3_1Straight_B.s_0_d;
      }

      CSE1_CV3_1Straight_DWork.Integrator1_IWORK_h.IcNeedsLoading = 0;
    }

    CSE1_CV3_1Straight_B.Integrator1_f =
      CSE1_CV3_1Straight_X.Integrator1_CSTATE_g;

    /* MultiPortSwitch: '<S1>/s switch' */
    if (CSE1_CV3_1Straight_B.Compare == 0) {
      CSE1_CV3_1Straight_B.sswitch = CSE1_CV3_1Straight_B.Integrator1;
    } else {
      CSE1_CV3_1Straight_B.sswitch = CSE1_CV3_1Straight_B.Integrator1_f;
    }

    /* Gain: '<S1>/s gain' */
    CSE1_CV3_1Straight_B.sgain = CSE1_CV3_1Straight_P.sgain_Gain *
      CSE1_CV3_1Straight_B.sswitch;

    /* Outputs for enable SubSystem: '<S2>/Path-following' incorporates:
     *  Constant: '<S2>/Enable Path'
     *  EnablePort: '<S220>/Enable'
     */
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M) && rtmIsMajorTimeStep
        (CSE1_CV3_1Straight_M)) {
      if (CSE1_CV3_1Straight_P.EnablePath_Value > 0.0) {
        if (CSE1_CV3_1Straight_DWork.Pathfollowing_MODE == SUBSYS_DISABLED) {
          CSE1_CV3_1Straight_DWork.Pathfollowing_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (CSE1_CV3_1Straight_DWork.Pathfollowing_MODE == SUBSYS_ENABLED) {
          CSE1_CV3_1Straight_DWork.Pathfollowing_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (CSE1_CV3_1Straight_DWork.Pathfollowing_MODE == SUBSYS_ENABLED) {
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Sum: '<S279>/y_2 - y_1' incorporates:
         *  Constant: '<S287>/y_1'
         *  Constant: '<S287>/y_2'
         */
        CSE1_CV3_1Straight_B.y_2y_1 = CSE1_CV3_1Straight_P.y_2_Value -
          CSE1_CV3_1Straight_P.y_1_Value;

        /* Sum: '<S279>/x_2 - x_1' incorporates:
         *  Constant: '<S287>/x_1'
         *  Constant: '<S287>/x_2'
         */
        CSE1_CV3_1Straight_B.x_2x_1 = CSE1_CV3_1Straight_P.x_2_Value -
          CSE1_CV3_1Straight_P.x_1_Value;

        /* Trigonometry: '<S225>/Trigonometric Function' */
        CSE1_CV3_1Straight_B.TrigonometricFunction = rt_atan2_snf
          (CSE1_CV3_1Straight_B.y_2y_1, CSE1_CV3_1Straight_B.x_2x_1);

        /* Gain: '<S230>/Gain' */
        CSE1_CV3_1Straight_B.Gain_hk = CSE1_CV3_1Straight_P.Gain_Gain_i *
          CSE1_CV3_1Straight_B.TrigonometricFunction;

        /* Saturate: '<S228>/Saturation' */
        tmp_0 = CSE1_CV3_1Straight_B.Gain_hk;
        CSE1_CV3_1Straight_B.Saturation_d = rt_SATURATE(tmp_0,
          CSE1_CV3_1Straight_P.Saturation_LowerSat_j,
          CSE1_CV3_1Straight_P.Saturation_UpperSat_lj);

        /* Signum: '<S228>/Sign' */
        CSE1_CV3_1Straight_B.Sign_h = rt_SIGNd_snf
          (CSE1_CV3_1Straight_B.Saturation_d);

        /* Gain: '<S228>/Gain' */
        CSE1_CV3_1Straight_B.Gain_dt = CSE1_CV3_1Straight_P.Gain_Gain_m *
          CSE1_CV3_1Straight_B.Sign_h;

        /* Sum: '<S228>/Sum1' */
        CSE1_CV3_1Straight_B.Sum1_hi = CSE1_CV3_1Straight_B.Saturation_d +
          CSE1_CV3_1Straight_B.Gain_dt;

        /* Math: '<S228>/Math Function' incorporates:
         *  Constant: '<S228>/Constant'
         */
        CSE1_CV3_1Straight_B.MathFunction_lk = rt_rem_snf
          (CSE1_CV3_1Straight_B.Sum1_hi, CSE1_CV3_1Straight_P.Constant_Value_km);

        /* Sum: '<S228>/Sum' */
        CSE1_CV3_1Straight_B.Sum_j = CSE1_CV3_1Straight_B.MathFunction_lk -
          CSE1_CV3_1Straight_B.Gain_dt;

        /* Gain: '<S229>/Gain1' */
        CSE1_CV3_1Straight_B.Gain1_o = CSE1_CV3_1Straight_P.Gain1_Gain_hm *
          CSE1_CV3_1Straight_B.Sum_j;

        /* Math: '<S226>/( x_d^s )^2' */
        tmp_0 = CSE1_CV3_1Straight_B.x_2x_1;
        CSE1_CV3_1Straight_B.x_ds2 = tmp_0 * tmp_0;

        /* Math: '<S226>/( y_d^s )^2' */
        tmp_0 = CSE1_CV3_1Straight_B.y_2y_1;
        CSE1_CV3_1Straight_B.y_ds2 = tmp_0 * tmp_0;

        /* Sum: '<S226>/( x_d^s )^2 + ( y_d^s )^2' */
        CSE1_CV3_1Straight_B.x_ds2y_ds2 = CSE1_CV3_1Straight_B.x_ds2 +
          CSE1_CV3_1Straight_B.y_ds2;

        /* Product: '<S226>/x_d^s * y_d^s^2' incorporates:
         *  Constant: '<S277>/0_2x1'
         */
        CSE1_CV3_1Straight_B.x_dsy_ds2 = CSE1_CV3_1Straight_B.x_2x_1 *
          CSE1_CV3_1Straight_P._2x1_Value_e;

        /* Product: '<S226>/x_d^s^2 * y_d^s' incorporates:
         *  Constant: '<S277>/0_2x1'
         */
        CSE1_CV3_1Straight_B.x_ds2y_ds = CSE1_CV3_1Straight_P._2x1_Value_e *
          CSE1_CV3_1Straight_B.y_2y_1;

        /* Sum: '<S226>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
        CSE1_CV3_1Straight_B.x_dsy_ds2x_ds2y_ds = CSE1_CV3_1Straight_B.x_dsy_ds2
          - CSE1_CV3_1Straight_B.x_ds2y_ds;

        /* Product: '<S226>/Divide' */
        CSE1_CV3_1Straight_B.Divide_g = CSE1_CV3_1Straight_B.x_dsy_ds2x_ds2y_ds /
          CSE1_CV3_1Straight_B.x_ds2y_ds2;

        /* Product: '<S227>/x_d^s * x_d^s^2' incorporates:
         *  Constant: '<S277>/0_2x1'
         */
        CSE1_CV3_1Straight_B.x_dsx_ds2 = CSE1_CV3_1Straight_B.x_2x_1 *
          CSE1_CV3_1Straight_P._2x1_Value_e;

        /* Product: '<S227>/y_d^s * y_d^s^2' incorporates:
         *  Constant: '<S277>/0_2x1'
         */
        CSE1_CV3_1Straight_B.y_dsy_ds2 = CSE1_CV3_1Straight_B.y_2y_1 *
          CSE1_CV3_1Straight_P._2x1_Value_e;

        /* Sum: '<S227>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
        CSE1_CV3_1Straight_B.x_dsx_ds2x_ds3y_ds = CSE1_CV3_1Straight_B.x_dsx_ds2
          + CSE1_CV3_1Straight_B.y_dsy_ds2;

        /* Product: '<S227>/x_d^s * y_d^s^3 ' incorporates:
         *  Constant: '<S277>/0_2x1'
         */
        CSE1_CV3_1Straight_B.x_dsy_ds3 = CSE1_CV3_1Straight_B.x_2x_1 *
          CSE1_CV3_1Straight_P._2x1_Value_e;

        /* Product: '<S227>/x_d^s^3 * y_d^s' incorporates:
         *  Constant: '<S277>/0_2x1'
         */
        CSE1_CV3_1Straight_B.x_ds3y_ds = CSE1_CV3_1Straight_P._2x1_Value_e *
          CSE1_CV3_1Straight_B.y_2y_1;

        /* Sum: '<S227>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
        CSE1_CV3_1Straight_B.x_dsy_ds3x_ds3y_ds = CSE1_CV3_1Straight_B.x_dsy_ds3
          - CSE1_CV3_1Straight_B.x_ds3y_ds;

        /* Gain: '<S227>/+ 2' */
        CSE1_CV3_1Straight_B.u_b = CSE1_CV3_1Straight_P.u_Gain_k *
          CSE1_CV3_1Straight_B.x_dsx_ds2x_ds3y_ds;

        /* Product: '<S227>/Product1' */
        CSE1_CV3_1Straight_B.Product1_j =
          CSE1_CV3_1Straight_B.x_dsy_ds3x_ds3y_ds *
          CSE1_CV3_1Straight_B.x_ds2y_ds2;

        /* Product: '<S227>/Product2' */
        CSE1_CV3_1Straight_B.Product2_ft =
          CSE1_CV3_1Straight_B.x_dsy_ds2x_ds2y_ds * CSE1_CV3_1Straight_B.u_b;

        /* Sum: '<S227>/Subtract' */
        CSE1_CV3_1Straight_B.Subtract_e = CSE1_CV3_1Straight_B.Product1_j -
          CSE1_CV3_1Straight_B.Product2_ft;

        /* Math: '<S227>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
        tmp_0 = CSE1_CV3_1Straight_B.x_ds2y_ds2;
        CSE1_CV3_1Straight_B.x_ds2y_ds22 = tmp_0 * tmp_0;

        /* Product: '<S227>/Divide' */
        CSE1_CV3_1Straight_B.Divide_n = CSE1_CV3_1Straight_B.Subtract_e /
          CSE1_CV3_1Straight_B.x_ds2y_ds22;
      }

      /* Inport: '<S220>/q' */
      CSE1_CV3_1Straight_B.q[0] = CSE1_CV3_1Straight_B.q_xgain;
      CSE1_CV3_1Straight_B.q[1] = CSE1_CV3_1Straight_B.q_ygain;

      /* SignalConversion: '<S231>/ConcatBufferAtVector ConcatenateIn1' */
      CSE1_CV3_1Straight_B.VectorConcatenate_dn[0] = CSE1_CV3_1Straight_B.q[0];
      CSE1_CV3_1Straight_B.VectorConcatenate_dn[1] = CSE1_CV3_1Straight_B.q[1];
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Gain: '<S263>/Gain' */
        CSE1_CV3_1Straight_B.Gain_p = CSE1_CV3_1Straight_P.Gain_Gain_oi *
          CSE1_CV3_1Straight_B.Gain1_o;

        /* Saturate: '<S259>/Saturation' */
        tmp_0 = CSE1_CV3_1Straight_B.Gain_p;
        CSE1_CV3_1Straight_B.Saturation_oo = rt_SATURATE(tmp_0,
          CSE1_CV3_1Straight_P.Saturation_LowerSat_hv,
          CSE1_CV3_1Straight_P.Saturation_UpperSat_i);

        /* Signum: '<S259>/Sign' */
        CSE1_CV3_1Straight_B.Sign_j = rt_SIGNd_snf
          (CSE1_CV3_1Straight_B.Saturation_oo);

        /* Gain: '<S259>/Gain' */
        CSE1_CV3_1Straight_B.Gain_g3 = CSE1_CV3_1Straight_P.Gain_Gain_ib *
          CSE1_CV3_1Straight_B.Sign_j;

        /* Sum: '<S259>/Sum1' */
        CSE1_CV3_1Straight_B.Sum1_b = CSE1_CV3_1Straight_B.Saturation_oo +
          CSE1_CV3_1Straight_B.Gain_g3;

        /* Math: '<S259>/Math Function' incorporates:
         *  Constant: '<S259>/Constant'
         */
        CSE1_CV3_1Straight_B.MathFunction_lx = rt_rem_snf
          (CSE1_CV3_1Straight_B.Sum1_b, CSE1_CV3_1Straight_P.Constant_Value_bc);

        /* Sum: '<S259>/Sum' */
        CSE1_CV3_1Straight_B.Sum_if = CSE1_CV3_1Straight_B.MathFunction_lx -
          CSE1_CV3_1Straight_B.Gain_g3;

        /* Gain: '<S262>/Gain1' */
        CSE1_CV3_1Straight_B.Gain1_oo = CSE1_CV3_1Straight_P.Gain1_Gain_a *
          CSE1_CV3_1Straight_B.Sum_if;

        /* Outputs for atomic SubSystem: '<S236>/R_2' */

        /* Trigonometry: '<S268>/R11' */
        CSE1_CV3_1Straight_B.R11_au = cos(CSE1_CV3_1Straight_B.Gain1_o);

        /* Trigonometry: '<S268>/R21' */
        CSE1_CV3_1Straight_B.R21_f = sin(CSE1_CV3_1Straight_B.Gain1_o);

        /* Gain: '<S268>/R12' */
        CSE1_CV3_1Straight_B.R12_e = CSE1_CV3_1Straight_P.R12_Gain *
          CSE1_CV3_1Straight_B.R21_f;

        /* Gain: '<S268>/R22' */
        CSE1_CV3_1Straight_B.R22_j = CSE1_CV3_1Straight_P.R22_Gain *
          CSE1_CV3_1Straight_B.R11_au;

        /* Reshape: '<S268>/R_2(psi_d)' */
        CSE1_CV3_1Straight_B.R_2psi_d[0] = CSE1_CV3_1Straight_B.R11_au;
        CSE1_CV3_1Straight_B.R_2psi_d[1] = CSE1_CV3_1Straight_B.R21_f;
        CSE1_CV3_1Straight_B.R_2psi_d[2] = CSE1_CV3_1Straight_B.R12_e;
        CSE1_CV3_1Straight_B.R_2psi_d[3] = CSE1_CV3_1Straight_B.R22_j;

        /* end of Outputs for SubSystem: '<S236>/R_2' */

        /* Math: '<S269>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_id[0] = CSE1_CV3_1Straight_B.R_2psi_d
          [0];
        CSE1_CV3_1Straight_B.MathFunction_id[1] = CSE1_CV3_1Straight_B.R_2psi_d
          [2];
        CSE1_CV3_1Straight_B.MathFunction_id[2] = CSE1_CV3_1Straight_B.R_2psi_d
          [1];
        CSE1_CV3_1Straight_B.MathFunction_id[3] = CSE1_CV3_1Straight_B.R_2psi_d
          [3];

        /* Sum: '<S278>/x_2 - x_1' incorporates:
         *  Constant: '<S287>/x_1'
         *  Constant: '<S287>/x_2'
         */
        CSE1_CV3_1Straight_B.x_2x_1_c = CSE1_CV3_1Straight_P.x_2_Value -
          CSE1_CV3_1Straight_P.x_1_Value;
      }

      /* Product: '<S278>/(x_2 - x_1) * s' */
      CSE1_CV3_1Straight_B.x_2x_1s = CSE1_CV3_1Straight_B.x_2x_1_c *
        CSE1_CV3_1Straight_B.sgain;

      /* Sum: '<S278>/(x_2 - x_1) * s + x_1' incorporates:
       *  Constant: '<S287>/x_1'
       */
      CSE1_CV3_1Straight_B.x_2x_1sx_1 = CSE1_CV3_1Straight_B.x_2x_1s +
        CSE1_CV3_1Straight_P.x_1_Value;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Sum: '<S278>/y_2 - y_1' incorporates:
         *  Constant: '<S287>/y_1'
         *  Constant: '<S287>/y_2'
         */
        CSE1_CV3_1Straight_B.y_2y_1_e = CSE1_CV3_1Straight_P.y_2_Value -
          CSE1_CV3_1Straight_P.y_1_Value;
      }

      /* Product: '<S278>/(y_2 - y_1) * s' */
      CSE1_CV3_1Straight_B.y_2y_1s = CSE1_CV3_1Straight_B.y_2y_1_e *
        CSE1_CV3_1Straight_B.sgain;

      /* Sum: '<S278>/(y_2 - y_1) * s + y_1' incorporates:
       *  Constant: '<S287>/y_1'
       */
      CSE1_CV3_1Straight_B.y_2y_1sy_1 = CSE1_CV3_1Straight_B.y_2y_1s +
        CSE1_CV3_1Straight_P.y_1_Value;

      /* Sum: '<S236>/q - p_d' */
      CSE1_CV3_1Straight_B.qp_d[0] = CSE1_CV3_1Straight_B.q[0] -
        CSE1_CV3_1Straight_B.x_2x_1sx_1;
      CSE1_CV3_1Straight_B.qp_d[1] = CSE1_CV3_1Straight_B.q[1] -
        CSE1_CV3_1Straight_B.y_2y_1sy_1;

      /* Product: '<S236>/epsilon' */
      CSE1_CV3_1Straight_B.epsilon[0] = 0.0;
      CSE1_CV3_1Straight_B.epsilon[0] = CSE1_CV3_1Straight_B.MathFunction_id[0] *
        CSE1_CV3_1Straight_B.qp_d[0] + CSE1_CV3_1Straight_B.epsilon[0];
      CSE1_CV3_1Straight_B.epsilon[0] = CSE1_CV3_1Straight_B.MathFunction_id[2] *
        CSE1_CV3_1Straight_B.qp_d[1] + CSE1_CV3_1Straight_B.epsilon[0];
      CSE1_CV3_1Straight_B.epsilon[1] = 0.0;
      CSE1_CV3_1Straight_B.epsilon[1] = CSE1_CV3_1Straight_B.MathFunction_id[1] *
        CSE1_CV3_1Straight_B.qp_d[0] + CSE1_CV3_1Straight_B.epsilon[1];
      CSE1_CV3_1Straight_B.epsilon[1] = CSE1_CV3_1Straight_B.MathFunction_id[3] *
        CSE1_CV3_1Straight_B.qp_d[1] + CSE1_CV3_1Straight_B.epsilon[1];

      /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S236>/Multiport Selector' */
      {
        const byte_T *u = (byte_T *)CSE1_CV3_1Straight_B.epsilon;/* input port */
        const int32_T *index = (const int32_T *)
          &CSE1_CV3_1Straight_ConstP.pooled1;
        const int32_T *length = (const int32_T *)
          &CSE1_CV3_1Straight_ConstP.pooled1;
        const int_T numRowsThisOutput = *length++;
        const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
        byte_T *y = (byte_T *)&CSE1_CV3_1Straight_B.MultiportSelector;
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
        }                              /* output row loop */
      }                                /* end <S236>/Multiport Selector */

      /* Trigonometry: '<S253>/Trigonometric Function' incorporates:
       *  Constant: '<S220>/Delta'
       */
      CSE1_CV3_1Straight_B.TrigonometricFunction_a = rt_atan2_snf
        (CSE1_CV3_1Straight_B.MultiportSelector,
         CSE1_CV3_1Straight_P.Delta_Value);

      /* Gain: '<S265>/Gain' */
      CSE1_CV3_1Straight_B.Gain_fe = CSE1_CV3_1Straight_P.Gain_Gain_nv *
        CSE1_CV3_1Straight_B.TrigonometricFunction_a;

      /* Saturate: '<S260>/Saturation' */
      tmp_0 = CSE1_CV3_1Straight_B.Gain_fe;
      CSE1_CV3_1Straight_B.Saturation_e4 = rt_SATURATE(tmp_0,
        CSE1_CV3_1Straight_P.Saturation_LowerSat_o4,
        CSE1_CV3_1Straight_P.Saturation_UpperSat_a);

      /* Signum: '<S260>/Sign' */
      CSE1_CV3_1Straight_B.Sign_a = rt_SIGNd_snf
        (CSE1_CV3_1Straight_B.Saturation_e4);

      /* Gain: '<S260>/Gain' */
      CSE1_CV3_1Straight_B.Gain_ih = CSE1_CV3_1Straight_P.Gain_Gain_e1 *
        CSE1_CV3_1Straight_B.Sign_a;

      /* Sum: '<S260>/Sum1' */
      CSE1_CV3_1Straight_B.Sum1_d = CSE1_CV3_1Straight_B.Saturation_e4 +
        CSE1_CV3_1Straight_B.Gain_ih;

      /* Math: '<S260>/Math Function' incorporates:
       *  Constant: '<S260>/Constant'
       */
      CSE1_CV3_1Straight_B.MathFunction_nj = rt_rem_snf
        (CSE1_CV3_1Straight_B.Sum1_d, CSE1_CV3_1Straight_P.Constant_Value_ab);

      /* Sum: '<S260>/Sum' */
      CSE1_CV3_1Straight_B.Sum_n4 = CSE1_CV3_1Straight_B.MathFunction_nj -
        CSE1_CV3_1Straight_B.Gain_ih;

      /* Gain: '<S264>/Gain1' */
      CSE1_CV3_1Straight_B.Gain1_os = CSE1_CV3_1Straight_P.Gain1_Gain_jx *
        CSE1_CV3_1Straight_B.Sum_n4;

      /* Sum: '<S253>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_p = CSE1_CV3_1Straight_B.Gain1_oo -
        CSE1_CV3_1Straight_B.Gain1_os;

      /* Gain: '<S267>/Gain' */
      CSE1_CV3_1Straight_B.Gain_cc = CSE1_CV3_1Straight_P.Gain_Gain_dn *
        CSE1_CV3_1Straight_B.Subtract_p;

      /* Saturate: '<S261>/Saturation' */
      tmp_0 = CSE1_CV3_1Straight_B.Gain_cc;
      CSE1_CV3_1Straight_B.Saturation_j = rt_SATURATE(tmp_0,
        CSE1_CV3_1Straight_P.Saturation_LowerSat_g,
        CSE1_CV3_1Straight_P.Saturation_UpperSat_b);

      /* Signum: '<S261>/Sign' */
      CSE1_CV3_1Straight_B.Sign_p = rt_SIGNd_snf
        (CSE1_CV3_1Straight_B.Saturation_j);

      /* Gain: '<S261>/Gain' */
      CSE1_CV3_1Straight_B.Gain_k = CSE1_CV3_1Straight_P.Gain_Gain_p *
        CSE1_CV3_1Straight_B.Sign_p;

      /* Sum: '<S261>/Sum1' */
      CSE1_CV3_1Straight_B.Sum1_pd = CSE1_CV3_1Straight_B.Saturation_j +
        CSE1_CV3_1Straight_B.Gain_k;

      /* Math: '<S261>/Math Function' incorporates:
       *  Constant: '<S261>/Constant'
       */
      CSE1_CV3_1Straight_B.MathFunction_ie = rt_rem_snf
        (CSE1_CV3_1Straight_B.Sum1_pd, CSE1_CV3_1Straight_P.Constant_Value_nd1);

      /* Sum: '<S261>/Sum' */
      CSE1_CV3_1Straight_B.Sum_ne = CSE1_CV3_1Straight_B.MathFunction_ie -
        CSE1_CV3_1Straight_B.Gain_k;

      /* Gain: '<S266>/Gain1' */
      CSE1_CV3_1Straight_B.Gain1_i = CSE1_CV3_1Straight_P.Gain1_Gain_p *
        CSE1_CV3_1Straight_B.Sum_ne;

      /* SignalConversion: '<S231>/ConcatBufferAtVector ConcatenateIn2' */
      CSE1_CV3_1Straight_B.VectorConcatenate_dn[2] =
        CSE1_CV3_1Straight_B.Gain1_i;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S254>/Math Function' incorporates:
         *  Constant: '<S220>/Delta'
         */
        tmp_0 = CSE1_CV3_1Straight_P.Delta_Value;
        CSE1_CV3_1Straight_B.MathFunction_ew1 = tmp_0 * tmp_0;
      }

      /* Math: '<S254>/Math Function1' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector;
      CSE1_CV3_1Straight_B.MathFunction1 = tmp_0 * tmp_0;

      /* Sum: '<S254>/Add' */
      CSE1_CV3_1Straight_B.Add_k = CSE1_CV3_1Straight_B.MathFunction_ew1 +
        CSE1_CV3_1Straight_B.MathFunction1;

      /* Product: '<S254>/Divide' */
      CSE1_CV3_1Straight_B.Divide_o = CSE1_CV3_1Straight_B.MathFunction_ew1 /
        CSE1_CV3_1Straight_B.Add_k;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S236>/Multiport Selector1' */
        {
          const byte_T *u = (byte_T *)CSE1_CV3_1Straight_B.MathFunction_id;/* input port */
          const int32_T *index = (const int32_T *)
            &CSE1_CV3_1Straight_ConstP.pooled1;
          const int32_T *length = (const int32_T *)
            &CSE1_CV3_1Straight_ConstP.pooled1;
          const int_T numRowsThisOutput = *length++;
          const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
          byte_T *y = (byte_T *)CSE1_CV3_1Straight_B.MultiportSelector1;
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
                     (u + (sampleIdx * (2 * sizeof(real_T))) +
                      inputRowOffsetBytes),
                     sizeof(real_T) );
            }
          }                            /* output row loop */
        }                              /* end <S236>/Multiport Selector1 */
      }

      /* Product: '<S254>/Product' */
      CSE1_CV3_1Straight_B.Product_m2[0] = CSE1_CV3_1Straight_B.Divide_o *
        CSE1_CV3_1Straight_B.MultiportSelector1[0];

      /* Gain: '<S254>/Gain' */
      CSE1_CV3_1Straight_B.Gain_l[0] = CSE1_CV3_1Straight_P.Gain_Gain_pi *
        CSE1_CV3_1Straight_B.Product_m2[0];

      /* Product: '<S254>/Product' */
      CSE1_CV3_1Straight_B.Product_m2[1] = CSE1_CV3_1Straight_B.Divide_o *
        CSE1_CV3_1Straight_B.MultiportSelector1[1];

      /* Gain: '<S254>/Gain' */
      CSE1_CV3_1Straight_B.Gain_l[1] = CSE1_CV3_1Straight_P.Gain_Gain_pi *
        CSE1_CV3_1Straight_B.Product_m2[1];

      /* Concatenate: '<S231>/Matrix Concatenate' incorporates:
       *  Constant: '<S237>/Constant'
       */
      CSE1_CV3_1Straight_B.MatrixConcatenate_oj[0] =
        CSE1_CV3_1Straight_P.Constant_Value_p1[0];
      CSE1_CV3_1Straight_B.MatrixConcatenate_oj[1] =
        CSE1_CV3_1Straight_P.Constant_Value_p1[1];
      CSE1_CV3_1Straight_B.MatrixConcatenate_oj[3] =
        CSE1_CV3_1Straight_P.Constant_Value_p1[2];
      CSE1_CV3_1Straight_B.MatrixConcatenate_oj[4] =
        CSE1_CV3_1Straight_P.Constant_Value_p1[3];
      CSE1_CV3_1Straight_B.MatrixConcatenate_oj[2] =
        CSE1_CV3_1Straight_B.Gain_l[0];
      CSE1_CV3_1Straight_B.MatrixConcatenate_oj[5] =
        CSE1_CV3_1Straight_B.Gain_l[1];
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Constant: '<S231>/0_2x1' */
        CSE1_CV3_1Straight_B.VectorConcatenate1[0] =
          CSE1_CV3_1Straight_P._2x1_Value_pc[0];
        CSE1_CV3_1Straight_B.VectorConcatenate1[1] =
          CSE1_CV3_1Straight_P._2x1_Value_pc[1];

        /* Math: '<S257>/Math Function' incorporates:
         *  Constant: '<S220>/Delta'
         */
        tmp_0 = CSE1_CV3_1Straight_P.Delta_Value;
        CSE1_CV3_1Straight_B.MathFunction_p = tmp_0 * tmp_0;
      }

      /* Math: '<S257>/Math Function1' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector;
      CSE1_CV3_1Straight_B.MathFunction1_i = tmp_0 * tmp_0;

      /* Sum: '<S257>/Add' */
      CSE1_CV3_1Straight_B.Add_jd = CSE1_CV3_1Straight_B.MathFunction_p +
        CSE1_CV3_1Straight_B.MathFunction1_i;

      /* Product: '<S257>/Divide' */
      CSE1_CV3_1Straight_B.Divide_g5 = CSE1_CV3_1Straight_B.MathFunction_p /
        CSE1_CV3_1Straight_B.Add_jd;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Outputs for atomic SubSystem: '<S236>/S_2' */

        /* Gain: '<S270>/S12' */
        CSE1_CV3_1Straight_B.S12_m = CSE1_CV3_1Straight_P.S12_Gain_b *
          CSE1_CV3_1Straight_B.Divide_g;

        /* Reshape: '<S270>/S_2(psi_d^s)' incorporates:
         *  Constant: '<S270>/0'
         */
        CSE1_CV3_1Straight_B.S_2psi_ds[0] = CSE1_CV3_1Straight_P._Value_m;
        CSE1_CV3_1Straight_B.S_2psi_ds[1] = CSE1_CV3_1Straight_B.Divide_g;
        CSE1_CV3_1Straight_B.S_2psi_ds[2] = CSE1_CV3_1Straight_B.S12_m;
        CSE1_CV3_1Straight_B.S_2psi_ds[3] = CSE1_CV3_1Straight_P._Value_m;

        /* end of Outputs for SubSystem: '<S236>/S_2' */

        /* Math: '<S273>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_h2[0] =
          CSE1_CV3_1Straight_B.S_2psi_ds[0];
        CSE1_CV3_1Straight_B.MathFunction_h2[1] =
          CSE1_CV3_1Straight_B.S_2psi_ds[2];
        CSE1_CV3_1Straight_B.MathFunction_h2[2] =
          CSE1_CV3_1Straight_B.S_2psi_ds[1];
        CSE1_CV3_1Straight_B.MathFunction_h2[3] =
          CSE1_CV3_1Straight_B.S_2psi_ds[3];
      }

      /* Product: '<S275>/Product' */
      for (i = 0; i < 2; i++) {
        tmp_2[i] = 0.0;
        tmp_2[i] += CSE1_CV3_1Straight_B.MathFunction_h2[i] *
          CSE1_CV3_1Straight_B.MathFunction_id[0];
        tmp_2[i] += CSE1_CV3_1Straight_B.MathFunction_h2[i + 2] *
          CSE1_CV3_1Straight_B.MathFunction_id[1];
        tmp_2[i + 2] = 0.0;
        tmp_2[i + 2] += CSE1_CV3_1Straight_B.MathFunction_h2[i] *
          CSE1_CV3_1Straight_B.MathFunction_id[2];
        tmp_2[i + 2] += CSE1_CV3_1Straight_B.MathFunction_h2[i + 2] *
          CSE1_CV3_1Straight_B.MathFunction_id[3];
      }

      CSE1_CV3_1Straight_B.Product_ky[0] = 0.0;
      CSE1_CV3_1Straight_B.Product_ky[0] = tmp_2[0] * CSE1_CV3_1Straight_B.qp_d
        [0] + CSE1_CV3_1Straight_B.Product_ky[0];
      CSE1_CV3_1Straight_B.Product_ky[0] = tmp_2[2] * CSE1_CV3_1Straight_B.qp_d
        [1] + CSE1_CV3_1Straight_B.Product_ky[0];
      CSE1_CV3_1Straight_B.Product_ky[1] = 0.0;
      CSE1_CV3_1Straight_B.Product_ky[1] = tmp_2[1] * CSE1_CV3_1Straight_B.qp_d
        [0] + CSE1_CV3_1Straight_B.Product_ky[1];
      CSE1_CV3_1Straight_B.Product_ky[1] = tmp_2[3] * CSE1_CV3_1Straight_B.qp_d
        [1] + CSE1_CV3_1Straight_B.Product_ky[1];
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* SignalConversion: '<S249>/TmpHiddenBufferAtMath FunctionInport1' */
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0] =
          CSE1_CV3_1Straight_B.x_2x_1;
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1] =
          CSE1_CV3_1Straight_B.y_2y_1;

        /* Product: '<S275>/Product1' */
        CSE1_CV3_1Straight_B.Product1_e[0] = 0.0;
        CSE1_CV3_1Straight_B.Product1_e[0] =
          CSE1_CV3_1Straight_B.MathFunction_id[0] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0] +
          CSE1_CV3_1Straight_B.Product1_e[0];
        CSE1_CV3_1Straight_B.Product1_e[0] =
          CSE1_CV3_1Straight_B.MathFunction_id[2] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1] +
          CSE1_CV3_1Straight_B.Product1_e[0];
        CSE1_CV3_1Straight_B.Product1_e[1] = 0.0;
        CSE1_CV3_1Straight_B.Product1_e[1] =
          CSE1_CV3_1Straight_B.MathFunction_id[1] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0] +
          CSE1_CV3_1Straight_B.Product1_e[1];
        CSE1_CV3_1Straight_B.Product1_e[1] =
          CSE1_CV3_1Straight_B.MathFunction_id[3] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1] +
          CSE1_CV3_1Straight_B.Product1_e[1];
      }

      /* Sum: '<S275>/Subtract1' */
      CSE1_CV3_1Straight_B.Subtract1[0] = CSE1_CV3_1Straight_B.Product_ky[0] -
        CSE1_CV3_1Straight_B.Product1_e[0];
      CSE1_CV3_1Straight_B.Subtract1[1] = CSE1_CV3_1Straight_B.Product_ky[1] -
        CSE1_CV3_1Straight_B.Product1_e[1];

      /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S236>/Multiport Selector2' */
      {
        const byte_T *u = (byte_T *)CSE1_CV3_1Straight_B.Subtract1;/* input port */
        const int32_T *index = (const int32_T *)
          &CSE1_CV3_1Straight_ConstP.pooled1;
        const int32_T *length = (const int32_T *)
          &CSE1_CV3_1Straight_ConstP.pooled1;
        const int_T numRowsThisOutput = *length++;
        const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
        byte_T *y = (byte_T *)&CSE1_CV3_1Straight_B.MultiportSelector2;
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
        }                              /* output row loop */
      }                                /* end <S236>/Multiport Selector2 */

      /* Product: '<S257>/Product' */
      CSE1_CV3_1Straight_B.Product_l2 = CSE1_CV3_1Straight_B.Divide_g5 *
        CSE1_CV3_1Straight_B.MultiportSelector2;

      /* Sum: '<S257>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_n = CSE1_CV3_1Straight_B.Divide_g -
        CSE1_CV3_1Straight_B.Product_l2;

      /* SignalConversion: '<S231>/ConcatBufferAtVector Concatenate1In2' */
      CSE1_CV3_1Straight_B.VectorConcatenate1[2] =
        CSE1_CV3_1Straight_B.Subtract_n;

      /* Trigonometry: '<S238>/f_qx' */
      CSE1_CV3_1Straight_B.f_qx = cos(CSE1_CV3_1Straight_B.Gain1_i);

      /* Trigonometry: '<S238>/f_qy' */
      CSE1_CV3_1Straight_B.f_qy = sin(CSE1_CV3_1Straight_B.Gain1_i);

      /* SignalConversion: '<S238>/TmpHiddenBufferAtProductInport1' */
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport1[0] =
        CSE1_CV3_1Straight_B.f_qx;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport1[1] =
        CSE1_CV3_1Straight_B.f_qy;

      /* Trigonometry: '<S239>/Trigonometric Function1' */
      CSE1_CV3_1Straight_B.TrigonometricFunction1 = sin
        (CSE1_CV3_1Straight_B.Gain1_i);

      /* Gain: '<S239>/Gain' */
      CSE1_CV3_1Straight_B.Gain_n = CSE1_CV3_1Straight_P.Gain_Gain_ghk *
        CSE1_CV3_1Straight_B.TrigonometricFunction1;

      /* Trigonometry: '<S239>/Trigonometric Function' */
      CSE1_CV3_1Straight_B.TrigonometricFunction_b = cos
        (CSE1_CV3_1Straight_B.Gain1_i);

      /* Product: '<S238>/Product' incorporates:
       *  Constant: '<S287>/u_d'
       */
      CSE1_CV3_1Straight_B.Product_dm[0] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport1[0] *
        CSE1_CV3_1Straight_P.u_d_Value;

      /* Product: '<S239>/Product1' */
      CSE1_CV3_1Straight_B.Product1_m4[0] = CSE1_CV3_1Straight_B.Gain_n *
        CSE1_CV3_1Straight_B.Gain_l[0];

      /* Product: '<S239>/Product2' */
      CSE1_CV3_1Straight_B.Product2_cb[0] =
        CSE1_CV3_1Straight_B.TrigonometricFunction_b *
        CSE1_CV3_1Straight_B.Gain_l[0];

      /* Product: '<S238>/Product' incorporates:
       *  Constant: '<S287>/u_d'
       */
      CSE1_CV3_1Straight_B.Product_dm[1] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport1[1] *
        CSE1_CV3_1Straight_P.u_d_Value;

      /* Product: '<S239>/Product1' */
      CSE1_CV3_1Straight_B.Product1_m4[1] = CSE1_CV3_1Straight_B.Gain_n *
        CSE1_CV3_1Straight_B.Gain_l[1];

      /* Product: '<S239>/Product2' */
      CSE1_CV3_1Straight_B.Product2_cb[1] =
        CSE1_CV3_1Straight_B.TrigonometricFunction_b *
        CSE1_CV3_1Straight_B.Gain_l[1];

      /* Concatenate: '<S239>/Matrix Concatenate' */
      CSE1_CV3_1Straight_B.MatrixConcatenate_d[0] =
        CSE1_CV3_1Straight_B.Product1_m4[0];
      CSE1_CV3_1Straight_B.MatrixConcatenate_d[2] =
        CSE1_CV3_1Straight_B.Product1_m4[1];
      CSE1_CV3_1Straight_B.MatrixConcatenate_d[1] =
        CSE1_CV3_1Straight_B.Product2_cb[0];
      CSE1_CV3_1Straight_B.MatrixConcatenate_d[3] =
        CSE1_CV3_1Straight_B.Product2_cb[1];

      /* Product: '<S239>/Product' incorporates:
       *  Constant: '<S287>/u_d'
       */
      CSE1_CV3_1Straight_B.Product_d4[0] =
        CSE1_CV3_1Straight_B.MatrixConcatenate_d[0] *
        CSE1_CV3_1Straight_P.u_d_Value;
      CSE1_CV3_1Straight_B.Product_d4[1] =
        CSE1_CV3_1Straight_B.MatrixConcatenate_d[1] *
        CSE1_CV3_1Straight_P.u_d_Value;
      CSE1_CV3_1Straight_B.Product_d4[2] =
        CSE1_CV3_1Straight_B.MatrixConcatenate_d[2] *
        CSE1_CV3_1Straight_P.u_d_Value;
      CSE1_CV3_1Straight_B.Product_d4[3] =
        CSE1_CV3_1Straight_B.MatrixConcatenate_d[3] *
        CSE1_CV3_1Straight_P.u_d_Value;

      /* Trigonometry: '<S240>/Trigonometric Function1' */
      CSE1_CV3_1Straight_B.TrigonometricFunction1_p = sin
        (CSE1_CV3_1Straight_B.Gain1_i);

      /* Gain: '<S240>/Gain' */
      CSE1_CV3_1Straight_B.Gain_ba = CSE1_CV3_1Straight_P.Gain_Gain_ma *
        CSE1_CV3_1Straight_B.TrigonometricFunction1_p;

      /* Product: '<S240>/Product1' */
      CSE1_CV3_1Straight_B.Product1_j0 = CSE1_CV3_1Straight_B.Gain_ba *
        CSE1_CV3_1Straight_B.Subtract_n;

      /* Trigonometry: '<S240>/Trigonometric Function' */
      CSE1_CV3_1Straight_B.TrigonometricFunction_a2 = cos
        (CSE1_CV3_1Straight_B.Gain1_i);

      /* Product: '<S240>/Product2' */
      CSE1_CV3_1Straight_B.Product2_e =
        CSE1_CV3_1Straight_B.TrigonometricFunction_a2 *
        CSE1_CV3_1Straight_B.Subtract_n;

      /* SignalConversion: '<S240>/TmpHiddenBufferAtProductInport1' */
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpo_kh[0] =
        CSE1_CV3_1Straight_B.Product1_j0;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpo_kh[1] =
        CSE1_CV3_1Straight_B.Product2_e;

      /* Product: '<S240>/Product' incorporates:
       *  Constant: '<S287>/u_d'
       */
      CSE1_CV3_1Straight_B.Product_l0[0] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpo_kh[0] *
        CSE1_CV3_1Straight_P.u_d_Value;
      CSE1_CV3_1Straight_B.Product_l0[1] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpo_kh[1] *
        CSE1_CV3_1Straight_P.u_d_Value;

      /* Trigonometry: '<S241>/Trigonometric Function' */
      CSE1_CV3_1Straight_B.TrigonometricFunction_b3 = cos
        (CSE1_CV3_1Straight_B.Gain1_i);

      /* Trigonometry: '<S241>/Trigonometric Function1' */
      CSE1_CV3_1Straight_B.TrigonometricFunction1_l = sin
        (CSE1_CV3_1Straight_B.Gain1_i);

      /* Derivative Block: '<S224>/Derivative' */
      {
        real_T t = CSE1_CV3_1Straight_M->Timing.t[0];
        real_T timeStampA = CSE1_CV3_1Straight_DWork.Derivative_RWORK.TimeStampA;
        real_T timeStampB = CSE1_CV3_1Straight_DWork.Derivative_RWORK.TimeStampB;
        if (timeStampA >= t && timeStampB >= t) {
          CSE1_CV3_1Straight_B.Derivative = 0.0;
        } else {
          real_T deltaT;
          real_T *lastBank =
            &CSE1_CV3_1Straight_DWork.Derivative_RWORK.TimeStampA;
          if (timeStampA < timeStampB) {
            if (timeStampB < t) {
              lastBank += 2;
            }
          } else if (timeStampA >= t) {
            lastBank += 2;
          }

          deltaT = t - *lastBank++;
          CSE1_CV3_1Straight_B.Derivative = (CSE1_CV3_1Straight_P.u_d_Value -
            *lastBank++) / deltaT;
        }
      }

      /* Product: '<S241>/Product' */
      CSE1_CV3_1Straight_B.Product_of[0] =
        CSE1_CV3_1Straight_B.TrigonometricFunction_b3 *
        CSE1_CV3_1Straight_B.Derivative;
      CSE1_CV3_1Straight_B.Product_of[1] =
        CSE1_CV3_1Straight_B.TrigonometricFunction1_l *
        CSE1_CV3_1Straight_B.Derivative;

      /* Math: '<S242>/epsilon_n^2' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector;
      CSE1_CV3_1Straight_B.epsilon_n2 = tmp_0 * tmp_0;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S242>/Delta^2' incorporates:
         *  Constant: '<S220>/Delta'
         */
        tmp_0 = CSE1_CV3_1Straight_P.Delta_Value;
        CSE1_CV3_1Straight_B.Delta2 = tmp_0 * tmp_0;
      }

      /* Sum: '<S242>/Add' */
      CSE1_CV3_1Straight_B.Add_j0 = CSE1_CV3_1Straight_B.epsilon_n2 +
        CSE1_CV3_1Straight_B.Delta2;

      /* Math: '<S242>/sqrt' */
      tmp_0 = CSE1_CV3_1Straight_B.Add_j0;
      if (tmp_0 < 0.0) {
        CSE1_CV3_1Straight_B.sqrt_m = -sqrt(-tmp_0);
      } else {
        CSE1_CV3_1Straight_B.sqrt_m = sqrt(tmp_0);
      }

      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      }

      /* Product: '<S242>/Divide' incorporates:
       *  Constant: '<S220>/Delta'
       */
      CSE1_CV3_1Straight_B.Divide_k = CSE1_CV3_1Straight_P.Delta_Value /
        CSE1_CV3_1Straight_B.sqrt_m;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S281>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_o[0] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0];
        CSE1_CV3_1Straight_B.MathFunction_o[1] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1];

        /* Product: '<S280>/Product' */
        tmp_0 = CSE1_CV3_1Straight_B.MathFunction_o[0] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0];
        tmp_0 += CSE1_CV3_1Straight_B.MathFunction_o[1] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1];
        CSE1_CV3_1Straight_B.Product_ho = tmp_0;

        /* Math: '<S280>/sqrt' */
        tmp_0 = CSE1_CV3_1Straight_B.Product_ho;
        if (tmp_0 < 0.0) {
          CSE1_CV3_1Straight_B.sqrt_g = -sqrt(-tmp_0);
        } else {
          CSE1_CV3_1Straight_B.sqrt_g = sqrt(tmp_0);
        }

        /* Product: '<S282>/Divide' incorporates:
         *  Constant: '<S287>/u_d'
         */
        CSE1_CV3_1Straight_B.Divide_j = CSE1_CV3_1Straight_P.u_d_Value /
          CSE1_CV3_1Straight_B.sqrt_g;
      }

      /* Product: '<S242>/Product' */
      CSE1_CV3_1Straight_B.Product_mk = CSE1_CV3_1Straight_B.Divide_k *
        CSE1_CV3_1Straight_B.Divide_j;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S249>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_pj[0] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0];

        /* Product: '<S246>/Divide' */
        CSE1_CV3_1Straight_B.Divide_i[0] = CSE1_CV3_1Straight_B.MathFunction_pj
          [0] / CSE1_CV3_1Straight_B.sqrt_g;

        /* Math: '<S249>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_pj[1] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1];

        /* Product: '<S246>/Divide' */
        CSE1_CV3_1Straight_B.Divide_i[1] = CSE1_CV3_1Straight_B.MathFunction_pj
          [1] / CSE1_CV3_1Straight_B.sqrt_g;
      }

      /* Sum: '<S234>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_a1[0] = CSE1_CV3_1Straight_B.q[0] -
        CSE1_CV3_1Straight_B.x_2x_1sx_1;
      CSE1_CV3_1Straight_B.Subtract_a1[1] = CSE1_CV3_1Straight_B.q[1] -
        CSE1_CV3_1Straight_B.y_2y_1sy_1;

      /* Product: '<S246>/Product' incorporates:
       *  Constant: '<S220>/my'
       */
      tmp_0 = CSE1_CV3_1Straight_P.my_Value * CSE1_CV3_1Straight_B.Divide_i[0] *
        CSE1_CV3_1Straight_B.Subtract_a1[0];
      tmp_0 += CSE1_CV3_1Straight_P.my_Value * CSE1_CV3_1Straight_B.Divide_i[1] *
        CSE1_CV3_1Straight_B.Subtract_a1[1];
      CSE1_CV3_1Straight_B.Product_ct = tmp_0;

      /* Gain: '<S246>/Gain' */
      CSE1_CV3_1Straight_B.Gain_mj = CSE1_CV3_1Straight_P.Gain_Gain_eo *
        CSE1_CV3_1Straight_B.Product_ct;

      /* Sum: '<S242>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_g = CSE1_CV3_1Straight_B.Product_mk -
        CSE1_CV3_1Straight_B.Gain_mj;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      }

      /* Math: '<S243>/epsilon_n^2' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector;
      CSE1_CV3_1Straight_B.epsilon_n2_a = tmp_0 * tmp_0;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S243>/Delta^2' incorporates:
         *  Constant: '<S220>/Delta'
         */
        tmp_0 = CSE1_CV3_1Straight_P.Delta_Value;
        CSE1_CV3_1Straight_B.Delta2_a = tmp_0 * tmp_0;
      }

      /* Sum: '<S243>/Add' */
      CSE1_CV3_1Straight_B.Add_e = CSE1_CV3_1Straight_B.epsilon_n2_a +
        CSE1_CV3_1Straight_B.Delta2_a;

      /* Product: '<S243>/Product1' */
      CSE1_CV3_1Straight_B.Product1_c[0] =
        CSE1_CV3_1Straight_B.MultiportSelector *
        CSE1_CV3_1Straight_B.MultiportSelector1[0];
      CSE1_CV3_1Straight_B.Product1_c[1] =
        CSE1_CV3_1Straight_B.MultiportSelector *
        CSE1_CV3_1Straight_B.MultiportSelector1[1];

      /* Math: '<S243>/^3//2' incorporates:
       *  Constant: '<S243>/3//2'
       */
      if ((CSE1_CV3_1Straight_B.Add_e < 0.0) && (CSE1_CV3_1Straight_P.u_Value_m1
           > floor(CSE1_CV3_1Straight_P.u_Value_m1))) {
        CSE1_CV3_1Straight_B.u2 = -rt_pow_snf(-CSE1_CV3_1Straight_B.Add_e,
          CSE1_CV3_1Straight_P.u_Value_m1);
      } else {
        CSE1_CV3_1Straight_B.u2 = rt_pow_snf(CSE1_CV3_1Straight_B.Add_e,
          CSE1_CV3_1Straight_P.u_Value_m1);
      }

      /* Product: '<S243>/Divide' */
      CSE1_CV3_1Straight_B.Divide_m[0] = CSE1_CV3_1Straight_B.Product1_c[0] /
        CSE1_CV3_1Straight_B.u2;

      /* Product: '<S243>/Product' incorporates:
       *  Constant: '<S220>/Delta'
       */
      CSE1_CV3_1Straight_B.Product_jc[0] = CSE1_CV3_1Straight_P.Delta_Value *
        CSE1_CV3_1Straight_B.Divide_m[0] * CSE1_CV3_1Straight_B.Divide_j;

      /* Product: '<S243>/Divide' */
      CSE1_CV3_1Straight_B.Divide_m[1] = CSE1_CV3_1Straight_B.Product1_c[1] /
        CSE1_CV3_1Straight_B.u2;

      /* Product: '<S243>/Product' incorporates:
       *  Constant: '<S220>/Delta'
       */
      CSE1_CV3_1Straight_B.Product_jc[1] = CSE1_CV3_1Straight_P.Delta_Value *
        CSE1_CV3_1Straight_B.Divide_m[1] * CSE1_CV3_1Straight_B.Divide_j;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S250>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_e0[0] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0];

        /* Product: '<S247>/Divide' */
        CSE1_CV3_1Straight_B.Divide_d[0] = CSE1_CV3_1Straight_B.MathFunction_e0
          [0] / CSE1_CV3_1Straight_B.sqrt_g;

        /* Product: '<S247>/Product' incorporates:
         *  Constant: '<S220>/my'
         */
        CSE1_CV3_1Straight_B.Product_ff[0] = CSE1_CV3_1Straight_P.my_Value *
          CSE1_CV3_1Straight_B.Divide_d[0];

        /* Gain: '<S247>/Gain' */
        CSE1_CV3_1Straight_B.Gain_is[0] = CSE1_CV3_1Straight_P.Gain_Gain_oz *
          CSE1_CV3_1Straight_B.Product_ff[0];

        /* Math: '<S250>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_e0[1] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1];

        /* Product: '<S247>/Divide' */
        CSE1_CV3_1Straight_B.Divide_d[1] = CSE1_CV3_1Straight_B.MathFunction_e0
          [1] / CSE1_CV3_1Straight_B.sqrt_g;

        /* Product: '<S247>/Product' incorporates:
         *  Constant: '<S220>/my'
         */
        CSE1_CV3_1Straight_B.Product_ff[1] = CSE1_CV3_1Straight_P.my_Value *
          CSE1_CV3_1Straight_B.Divide_d[1];

        /* Gain: '<S247>/Gain' */
        CSE1_CV3_1Straight_B.Gain_is[1] = CSE1_CV3_1Straight_P.Gain_Gain_oz *
          CSE1_CV3_1Straight_B.Product_ff[1];
      }

      /* Sum: '<S243>/Sum' */
      CSE1_CV3_1Straight_B.Sum_id[0] = (0.0 - CSE1_CV3_1Straight_B.Product_jc[0])
        - CSE1_CV3_1Straight_B.Gain_is[0];
      CSE1_CV3_1Straight_B.Sum_id[1] = (0.0 - CSE1_CV3_1Straight_B.Product_jc[1])
        - CSE1_CV3_1Straight_B.Gain_is[1];

      /* Math: '<S244>/epsilon_n^2' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector;
      CSE1_CV3_1Straight_B.epsilon_n2_j = tmp_0 * tmp_0;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S244>/Delta^2' incorporates:
         *  Constant: '<S220>/Delta'
         */
        tmp_0 = CSE1_CV3_1Straight_P.Delta_Value;
        CSE1_CV3_1Straight_B.Delta2_b = tmp_0 * tmp_0;
      }

      /* Sum: '<S244>/Add' */
      CSE1_CV3_1Straight_B.Add_bt = CSE1_CV3_1Straight_B.epsilon_n2_j +
        CSE1_CV3_1Straight_B.Delta2_b;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S285>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_b[0] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0];
        CSE1_CV3_1Straight_B.MathFunction_b[1] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1];

        /* SignalConversion: '<S252>/TmpHiddenBufferAtMath FunctionInport1' incorporates:
         *  Constant: '<S277>/0_2x1'
         */
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[0] =
          CSE1_CV3_1Straight_P._2x1_Value_e;
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[1] =
          CSE1_CV3_1Straight_P._2x1_Value_e;

        /* Product: '<S283>/Product1' */
        tmp_0 = CSE1_CV3_1Straight_B.MathFunction_b[0] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[0];
        tmp_0 += CSE1_CV3_1Straight_B.MathFunction_b[1] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[1];
        CSE1_CV3_1Straight_B.Product1_oy = tmp_0;

        /* Math: '<S283>/|p_d^s|^3' incorporates:
         *  Constant: '<S283>/Constant'
         */
        if ((CSE1_CV3_1Straight_B.sqrt_g < 0.0) &&
            (CSE1_CV3_1Straight_P.Constant_Value_po > floor
             (CSE1_CV3_1Straight_P.Constant_Value_po))) {
          CSE1_CV3_1Straight_B.p_ds3 = -rt_pow_snf(-CSE1_CV3_1Straight_B.sqrt_g,
            CSE1_CV3_1Straight_P.Constant_Value_po);
        } else {
          CSE1_CV3_1Straight_B.p_ds3 = rt_pow_snf(CSE1_CV3_1Straight_B.sqrt_g,
            CSE1_CV3_1Straight_P.Constant_Value_po);
        }

        /* Product: '<S283>/Divide' */
        CSE1_CV3_1Straight_B.Divide_p = CSE1_CV3_1Straight_B.Product1_oy /
          CSE1_CV3_1Straight_B.p_ds3;

        /* Product: '<S283>/Product' incorporates:
         *  Constant: '<S287>/u_d'
         */
        CSE1_CV3_1Straight_B.Product_g = CSE1_CV3_1Straight_B.Divide_p *
          CSE1_CV3_1Straight_P.u_d_Value;

        /* Gain: '<S283>/Gain' */
        CSE1_CV3_1Straight_B.Gain_a = CSE1_CV3_1Straight_P.Gain_Gain_o2 *
          CSE1_CV3_1Straight_B.Product_g;
      }

      /* Math: '<S244>/Math Function' */
      tmp_0 = CSE1_CV3_1Straight_B.Add_bt;
      if (tmp_0 < 0.0) {
        CSE1_CV3_1Straight_B.MathFunction_ig = -sqrt(-tmp_0);
      } else {
        CSE1_CV3_1Straight_B.MathFunction_ig = sqrt(tmp_0);
      }

      /* Product: '<S244>/Divide' */
      CSE1_CV3_1Straight_B.Divide_o4 = CSE1_CV3_1Straight_B.Gain_a /
        CSE1_CV3_1Straight_B.MathFunction_ig;

      /* Product: '<S244>/Product2' */
      CSE1_CV3_1Straight_B.Product2_l = CSE1_CV3_1Straight_B.MultiportSelector *
        CSE1_CV3_1Straight_B.MultiportSelector2;

      /* Math: '<S244>/^3//2' incorporates:
       *  Constant: '<S244>/3//2'
       */
      if ((CSE1_CV3_1Straight_B.Add_bt < 0.0) &&
          (CSE1_CV3_1Straight_P.u_Value_on > floor
           (CSE1_CV3_1Straight_P.u_Value_on))) {
        CSE1_CV3_1Straight_B.u2_g = -rt_pow_snf(-CSE1_CV3_1Straight_B.Add_bt,
          CSE1_CV3_1Straight_P.u_Value_on);
      } else {
        CSE1_CV3_1Straight_B.u2_g = rt_pow_snf(CSE1_CV3_1Straight_B.Add_bt,
          CSE1_CV3_1Straight_P.u_Value_on);
      }

      /* Product: '<S244>/Divide1' */
      CSE1_CV3_1Straight_B.Divide1 = CSE1_CV3_1Straight_B.Product2_l /
        CSE1_CV3_1Straight_B.u2_g;

      /* Product: '<S244>/Product1' incorporates:
       *  Constant: '<S220>/Delta'
       */
      CSE1_CV3_1Straight_B.Product1_p = CSE1_CV3_1Straight_P.Delta_Value *
        CSE1_CV3_1Straight_B.Divide_o4;

      /* Product: '<S244>/Product3' incorporates:
       *  Constant: '<S220>/Delta'
       */
      CSE1_CV3_1Straight_B.Product3_g = CSE1_CV3_1Straight_P.Delta_Value *
        CSE1_CV3_1Straight_B.Divide1 * CSE1_CV3_1Straight_B.Divide_j;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Product: '<S248>/Product1' incorporates:
         *  Constant: '<S220>/my'
         */
        CSE1_CV3_1Straight_B.Product1_bo = CSE1_CV3_1Straight_P.my_Value *
          CSE1_CV3_1Straight_B.sqrt_g;

        /* Math: '<S252>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_gl[0] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[0];

        /* Product: '<S248>/Divide2' */
        CSE1_CV3_1Straight_B.Divide2[0] = CSE1_CV3_1Straight_B.MathFunction_gl[0]
          / CSE1_CV3_1Straight_B.sqrt_g;

        /* Math: '<S251>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_bi[0] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0];

        /* Math: '<S252>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_gl[1] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[1];

        /* Product: '<S248>/Divide2' */
        CSE1_CV3_1Straight_B.Divide2[1] = CSE1_CV3_1Straight_B.MathFunction_gl[1]
          / CSE1_CV3_1Straight_B.sqrt_g;

        /* Math: '<S251>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_bi[1] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1];

        /* Product: '<S248>/Product2' */
        tmp_0 = CSE1_CV3_1Straight_B.MathFunction_gl[0] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0];
        tmp_0 += CSE1_CV3_1Straight_B.MathFunction_gl[1] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1];
        CSE1_CV3_1Straight_B.Product2_o[0] = tmp_0 *
          CSE1_CV3_1Straight_B.MathFunction_bi[0];
        CSE1_CV3_1Straight_B.Product2_o[1] = tmp_0 *
          CSE1_CV3_1Straight_B.MathFunction_bi[1];

        /* Math: '<S248>/Math Function' incorporates:
         *  Constant: '<S248>/Constant'
         */
        if ((CSE1_CV3_1Straight_B.sqrt_g < 0.0) &&
            (CSE1_CV3_1Straight_P.Constant_Value_nh > floor
             (CSE1_CV3_1Straight_P.Constant_Value_nh))) {
          CSE1_CV3_1Straight_B.MathFunction_lc = -rt_pow_snf
            (-CSE1_CV3_1Straight_B.sqrt_g,
             CSE1_CV3_1Straight_P.Constant_Value_nh);
        } else {
          CSE1_CV3_1Straight_B.MathFunction_lc = rt_pow_snf
            (CSE1_CV3_1Straight_B.sqrt_g, CSE1_CV3_1Straight_P.Constant_Value_nh);
        }

        /* Product: '<S248>/Divide1' */
        CSE1_CV3_1Straight_B.Divide1_d[0] = CSE1_CV3_1Straight_B.Product2_o[0] /
          CSE1_CV3_1Straight_B.MathFunction_lc;

        /* Sum: '<S248>/Subtract1' */
        CSE1_CV3_1Straight_B.Subtract1_m[0] = CSE1_CV3_1Straight_B.Divide2[0] -
          CSE1_CV3_1Straight_B.Divide1_d[0];

        /* Product: '<S248>/Divide1' */
        CSE1_CV3_1Straight_B.Divide1_d[1] = CSE1_CV3_1Straight_B.Product2_o[1] /
          CSE1_CV3_1Straight_B.MathFunction_lc;

        /* Sum: '<S248>/Subtract1' */
        CSE1_CV3_1Straight_B.Subtract1_m[1] = CSE1_CV3_1Straight_B.Divide2[1] -
          CSE1_CV3_1Straight_B.Divide1_d[1];
      }

      /* Product: '<S248>/Product' incorporates:
       *  Constant: '<S220>/my'
       */
      tmp_0 = CSE1_CV3_1Straight_P.my_Value * CSE1_CV3_1Straight_B.Subtract1_m[0]
        * CSE1_CV3_1Straight_B.Subtract_a1[0];
      tmp_0 += CSE1_CV3_1Straight_P.my_Value * CSE1_CV3_1Straight_B.Subtract1_m
        [1] * CSE1_CV3_1Straight_B.Subtract_a1[1];
      CSE1_CV3_1Straight_B.Product_bi = tmp_0;

      /* Sum: '<S248>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_nx = CSE1_CV3_1Straight_B.Product1_bo -
        CSE1_CV3_1Straight_B.Product_bi;

      /* Sum: '<S244>/Sum' */
      CSE1_CV3_1Straight_B.Sum_oq = (CSE1_CV3_1Straight_B.Product1_p -
        CSE1_CV3_1Straight_B.Product3_g) - CSE1_CV3_1Straight_B.Subtract_nx;

      /* Math: '<S245>/epsilon_n^2' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector;
      CSE1_CV3_1Straight_B.epsilon_n2_m = tmp_0 * tmp_0;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S245>/Delta^2' incorporates:
         *  Constant: '<S220>/Delta'
         */
        tmp_0 = CSE1_CV3_1Straight_P.Delta_Value;
        CSE1_CV3_1Straight_B.Delta2_f = tmp_0 * tmp_0;
      }

      /* Sum: '<S245>/Add' */
      CSE1_CV3_1Straight_B.Add_f = CSE1_CV3_1Straight_B.epsilon_n2_m +
        CSE1_CV3_1Straight_B.Delta2_f;

      /* Math: '<S245>/sqrt' */
      tmp_0 = CSE1_CV3_1Straight_B.Add_f;
      if (tmp_0 < 0.0) {
        CSE1_CV3_1Straight_B.sqrt_c = -sqrt(-tmp_0);
      } else {
        CSE1_CV3_1Straight_B.sqrt_c = sqrt(tmp_0);
      }

      /* Product: '<S245>/Divide' incorporates:
       *  Constant: '<S220>/Delta'
       */
      CSE1_CV3_1Straight_B.Divide_h = CSE1_CV3_1Straight_P.Delta_Value /
        CSE1_CV3_1Straight_B.sqrt_c;

      /* Product: '<S284>/Divide' */
      CSE1_CV3_1Straight_B.Divide_b = CSE1_CV3_1Straight_B.Derivative /
        CSE1_CV3_1Straight_B.sqrt_g;

      /* Product: '<S245>/Product' */
      CSE1_CV3_1Straight_B.Product_gd = CSE1_CV3_1Straight_B.Divide_h *
        CSE1_CV3_1Straight_B.Divide_b;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S255>/Math Function' incorporates:
         *  Constant: '<S220>/Delta'
         */
        tmp_0 = CSE1_CV3_1Straight_P.Delta_Value;
        CSE1_CV3_1Straight_B.MathFunction_ka = tmp_0 * tmp_0;
      }

      /* Math: '<S255>/Math Function1' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector;
      CSE1_CV3_1Straight_B.MathFunction1_c = tmp_0 * tmp_0;

      /* Sum: '<S255>/Add' */
      CSE1_CV3_1Straight_B.Add_hs = CSE1_CV3_1Straight_B.MathFunction_ka +
        CSE1_CV3_1Straight_B.MathFunction1_c;

      /* Product: '<S255>/Product1' incorporates:
       *  Constant: '<S236>/0_2x2'
       */
      CSE1_CV3_1Straight_B.Product1_pa[0] = CSE1_CV3_1Straight_P._2x2_Value_b[0]
        * CSE1_CV3_1Straight_B.Add_hs;
      CSE1_CV3_1Straight_B.Product1_pa[1] = CSE1_CV3_1Straight_P._2x2_Value_b[1]
        * CSE1_CV3_1Straight_B.Add_hs;
      CSE1_CV3_1Straight_B.Product1_pa[2] = CSE1_CV3_1Straight_P._2x2_Value_b[2]
        * CSE1_CV3_1Straight_B.Add_hs;
      CSE1_CV3_1Straight_B.Product1_pa[3] = CSE1_CV3_1Straight_P._2x2_Value_b[3]
        * CSE1_CV3_1Straight_B.Add_hs;

      /* Product: '<S255>/Product2' incorporates:
       *  Constant: '<S255>/2'
       */
      CSE1_CV3_1Straight_B.Product2_j = CSE1_CV3_1Straight_P._Value_d *
        CSE1_CV3_1Straight_B.MultiportSelector;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S255>/Math Function3' */
        CSE1_CV3_1Straight_B.MathFunction3[0] =
          CSE1_CV3_1Straight_B.MultiportSelector1[0];
        CSE1_CV3_1Straight_B.MathFunction3[1] =
          CSE1_CV3_1Straight_B.MultiportSelector1[1];

        /* Product: '<S255>/Product3' */
        CSE1_CV3_1Straight_B.Product3_k[0] = 0.0;
        CSE1_CV3_1Straight_B.Product3_k[0] = CSE1_CV3_1Straight_B.MathFunction3
          [0] * CSE1_CV3_1Straight_B.MultiportSelector1[0] +
          CSE1_CV3_1Straight_B.Product3_k[0];
        CSE1_CV3_1Straight_B.Product3_k[2] = 0.0;
        CSE1_CV3_1Straight_B.Product3_k[2] = CSE1_CV3_1Straight_B.MathFunction3
          [0] * CSE1_CV3_1Straight_B.MultiportSelector1[1] +
          CSE1_CV3_1Straight_B.Product3_k[2];
        CSE1_CV3_1Straight_B.Product3_k[1] = 0.0;
        CSE1_CV3_1Straight_B.Product3_k[1] = CSE1_CV3_1Straight_B.MathFunction3
          [1] * CSE1_CV3_1Straight_B.MultiportSelector1[0] +
          CSE1_CV3_1Straight_B.Product3_k[1];
        CSE1_CV3_1Straight_B.Product3_k[3] = 0.0;
        CSE1_CV3_1Straight_B.Product3_k[3] = CSE1_CV3_1Straight_B.MathFunction3
          [1] * CSE1_CV3_1Straight_B.MultiportSelector1[1] +
          CSE1_CV3_1Straight_B.Product3_k[3];
      }

      /* Math: '<S255>/Math Function2' */
      tmp_0 = CSE1_CV3_1Straight_B.Add_hs;
      CSE1_CV3_1Straight_B.MathFunction2 = tmp_0 * tmp_0;

      /* Product: '<S255>/Product4' */
      CSE1_CV3_1Straight_B.Product4_p[0] = CSE1_CV3_1Straight_B.Product2_j *
        CSE1_CV3_1Straight_B.Product3_k[0];

      /* Sum: '<S255>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_b[0] = CSE1_CV3_1Straight_B.Product1_pa[0] -
        CSE1_CV3_1Straight_B.Product4_p[0];

      /* Product: '<S255>/Divide' */
      CSE1_CV3_1Straight_B.Divide_m4[0] = CSE1_CV3_1Straight_B.Subtract_b[0] /
        CSE1_CV3_1Straight_B.MathFunction2;

      /* Product: '<S255>/Product' */
      CSE1_CV3_1Straight_B.Product_nq[0] = CSE1_CV3_1Straight_B.MathFunction_ka *
        CSE1_CV3_1Straight_B.Divide_m4[0];

      /* Product: '<S255>/Product4' */
      CSE1_CV3_1Straight_B.Product4_p[1] = CSE1_CV3_1Straight_B.Product2_j *
        CSE1_CV3_1Straight_B.Product3_k[1];

      /* Sum: '<S255>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_b[1] = CSE1_CV3_1Straight_B.Product1_pa[1] -
        CSE1_CV3_1Straight_B.Product4_p[1];

      /* Product: '<S255>/Divide' */
      CSE1_CV3_1Straight_B.Divide_m4[1] = CSE1_CV3_1Straight_B.Subtract_b[1] /
        CSE1_CV3_1Straight_B.MathFunction2;

      /* Product: '<S255>/Product' */
      CSE1_CV3_1Straight_B.Product_nq[1] = CSE1_CV3_1Straight_B.MathFunction_ka *
        CSE1_CV3_1Straight_B.Divide_m4[1];

      /* Product: '<S255>/Product4' */
      CSE1_CV3_1Straight_B.Product4_p[2] = CSE1_CV3_1Straight_B.Product2_j *
        CSE1_CV3_1Straight_B.Product3_k[2];

      /* Sum: '<S255>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_b[2] = CSE1_CV3_1Straight_B.Product1_pa[2] -
        CSE1_CV3_1Straight_B.Product4_p[2];

      /* Product: '<S255>/Divide' */
      CSE1_CV3_1Straight_B.Divide_m4[2] = CSE1_CV3_1Straight_B.Subtract_b[2] /
        CSE1_CV3_1Straight_B.MathFunction2;

      /* Product: '<S255>/Product' */
      CSE1_CV3_1Straight_B.Product_nq[2] = CSE1_CV3_1Straight_B.MathFunction_ka *
        CSE1_CV3_1Straight_B.Divide_m4[2];

      /* Product: '<S255>/Product4' */
      CSE1_CV3_1Straight_B.Product4_p[3] = CSE1_CV3_1Straight_B.Product2_j *
        CSE1_CV3_1Straight_B.Product3_k[3];

      /* Sum: '<S255>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_b[3] = CSE1_CV3_1Straight_B.Product1_pa[3] -
        CSE1_CV3_1Straight_B.Product4_p[3];

      /* Product: '<S255>/Divide' */
      CSE1_CV3_1Straight_B.Divide_m4[3] = CSE1_CV3_1Straight_B.Subtract_b[3] /
        CSE1_CV3_1Straight_B.MathFunction2;

      /* Product: '<S255>/Product' */
      CSE1_CV3_1Straight_B.Product_nq[3] = CSE1_CV3_1Straight_B.MathFunction_ka *
        CSE1_CV3_1Straight_B.Divide_m4[3];
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S256>/Math Function' incorporates:
         *  Constant: '<S220>/Delta'
         */
        tmp_0 = CSE1_CV3_1Straight_P.Delta_Value;
        CSE1_CV3_1Straight_B.MathFunction_igu = tmp_0 * tmp_0;
      }

      /* Math: '<S256>/Math Function1' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector;
      CSE1_CV3_1Straight_B.MathFunction1_n = tmp_0 * tmp_0;

      /* Sum: '<S256>/Add' */
      CSE1_CV3_1Straight_B.Add_bd = CSE1_CV3_1Straight_B.MathFunction_igu +
        CSE1_CV3_1Straight_B.MathFunction1_n;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Product: '<S274>/Product1' */
        for (i = 0; i < 2; i++) {
          CSE1_CV3_1Straight_B.Product1_fw[i] = 0.0;
          CSE1_CV3_1Straight_B.Product1_fw[i] =
            CSE1_CV3_1Straight_B.MathFunction_h2[i] *
            CSE1_CV3_1Straight_B.MathFunction_id[0] +
            CSE1_CV3_1Straight_B.Product1_fw[i];
          CSE1_CV3_1Straight_B.Product1_fw[i] =
            CSE1_CV3_1Straight_B.MathFunction_h2[i + 2] *
            CSE1_CV3_1Straight_B.MathFunction_id[1] +
            CSE1_CV3_1Straight_B.Product1_fw[i];
          CSE1_CV3_1Straight_B.Product1_fw[i + 2] = 0.0;
          CSE1_CV3_1Straight_B.Product1_fw[i + 2] =
            CSE1_CV3_1Straight_B.Product1_fw[i + 2] +
            CSE1_CV3_1Straight_B.MathFunction_h2[i] *
            CSE1_CV3_1Straight_B.MathFunction_id[2];
          CSE1_CV3_1Straight_B.Product1_fw[i + 2] =
            CSE1_CV3_1Straight_B.MathFunction_h2[i + 2] *
            CSE1_CV3_1Straight_B.MathFunction_id[3] +
            CSE1_CV3_1Straight_B.Product1_fw[i + 2];
        }

        /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S236>/Multiport Selector3' */
        {
          const byte_T *u = (byte_T *)CSE1_CV3_1Straight_B.Product1_fw;/* input port */
          const int32_T *index = (const int32_T *)
            &CSE1_CV3_1Straight_ConstP.pooled1;
          const int32_T *length = (const int32_T *)
            &CSE1_CV3_1Straight_ConstP.pooled1;
          const int_T numRowsThisOutput = *length++;
          const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
          byte_T *y = (byte_T *)CSE1_CV3_1Straight_B.MultiportSelector3;
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
                     (u + (sampleIdx * (2 * sizeof(real_T))) +
                      inputRowOffsetBytes),
                     sizeof(real_T) );
            }
          }                            /* output row loop */
        }                              /* end <S236>/Multiport Selector3 */
      }

      /* Math: '<S256>/Math Function2' */
      tmp_0 = CSE1_CV3_1Straight_B.Add_bd;
      CSE1_CV3_1Straight_B.MathFunction2_i = tmp_0 * tmp_0;

      /* Product: '<S256>/Product1' */
      CSE1_CV3_1Straight_B.Product1_m3[0] =
        CSE1_CV3_1Straight_B.MultiportSelector3[0] * CSE1_CV3_1Straight_B.Add_bd;

      /* Product: '<S256>/Product2' incorporates:
       *  Constant: '<S256>/2'
       */
      CSE1_CV3_1Straight_B.Product2_k1[0] = CSE1_CV3_1Straight_P._Value_mn *
        CSE1_CV3_1Straight_B.MultiportSelector *
        CSE1_CV3_1Straight_B.MultiportSelector2 *
        CSE1_CV3_1Straight_B.MultiportSelector1[0];

      /* Sum: '<S256>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_js[0] = CSE1_CV3_1Straight_B.Product1_m3[0]
        - CSE1_CV3_1Straight_B.Product2_k1[0];

      /* Product: '<S256>/Divide' */
      CSE1_CV3_1Straight_B.Divide_b4[0] = CSE1_CV3_1Straight_B.Subtract_js[0] /
        CSE1_CV3_1Straight_B.MathFunction2_i;

      /* Product: '<S256>/Product' */
      CSE1_CV3_1Straight_B.Product_gz[0] = CSE1_CV3_1Straight_B.MathFunction_igu
        * CSE1_CV3_1Straight_B.Divide_b4[0];

      /* Product: '<S256>/Product1' */
      CSE1_CV3_1Straight_B.Product1_m3[1] =
        CSE1_CV3_1Straight_B.MultiportSelector3[1] * CSE1_CV3_1Straight_B.Add_bd;

      /* Product: '<S256>/Product2' incorporates:
       *  Constant: '<S256>/2'
       */
      CSE1_CV3_1Straight_B.Product2_k1[1] = CSE1_CV3_1Straight_P._Value_mn *
        CSE1_CV3_1Straight_B.MultiportSelector *
        CSE1_CV3_1Straight_B.MultiportSelector2 *
        CSE1_CV3_1Straight_B.MultiportSelector1[1];

      /* Sum: '<S256>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_js[1] = CSE1_CV3_1Straight_B.Product1_m3[1]
        - CSE1_CV3_1Straight_B.Product2_k1[1];

      /* Product: '<S256>/Divide' */
      CSE1_CV3_1Straight_B.Divide_b4[1] = CSE1_CV3_1Straight_B.Subtract_js[1] /
        CSE1_CV3_1Straight_B.MathFunction2_i;

      /* Product: '<S256>/Product' */
      CSE1_CV3_1Straight_B.Product_gz[1] = CSE1_CV3_1Straight_B.MathFunction_igu
        * CSE1_CV3_1Straight_B.Divide_b4[1];
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Math: '<S258>/Math Function' incorporates:
         *  Constant: '<S220>/Delta'
         */
        tmp_0 = CSE1_CV3_1Straight_P.Delta_Value;
        CSE1_CV3_1Straight_B.MathFunction_hv = tmp_0 * tmp_0;
      }

      /* Math: '<S258>/Math Function1' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector;
      CSE1_CV3_1Straight_B.MathFunction1_f = tmp_0 * tmp_0;

      /* Sum: '<S258>/Add' */
      CSE1_CV3_1Straight_B.Add_cn = CSE1_CV3_1Straight_B.MathFunction_hv +
        CSE1_CV3_1Straight_B.MathFunction1_f;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Outputs for atomic SubSystem: '<S236>/S_2(psi_d^s^2)' */

        /* Gain: '<S271>/S12' */
        CSE1_CV3_1Straight_B.S12_e = CSE1_CV3_1Straight_P.S12_Gain_p *
          CSE1_CV3_1Straight_B.Divide_n;

        /* Reshape: '<S271>/S_2(psi_d^s^2)' incorporates:
         *  Constant: '<S271>/0'
         */
        CSE1_CV3_1Straight_B.S_2psi_ds2[0] = CSE1_CV3_1Straight_P._Value_p;
        CSE1_CV3_1Straight_B.S_2psi_ds2[1] = CSE1_CV3_1Straight_B.Divide_n;
        CSE1_CV3_1Straight_B.S_2psi_ds2[2] = CSE1_CV3_1Straight_B.S12_e;
        CSE1_CV3_1Straight_B.S_2psi_ds2[3] = CSE1_CV3_1Straight_P._Value_p;

        /* end of Outputs for SubSystem: '<S236>/S_2(psi_d^s^2)' */

        /* Math: '<S272>/Math Function' */
        CSE1_CV3_1Straight_B.MathFunction_o5[0] =
          CSE1_CV3_1Straight_B.S_2psi_ds2[0];
        CSE1_CV3_1Straight_B.MathFunction_o5[1] =
          CSE1_CV3_1Straight_B.S_2psi_ds2[2];
        CSE1_CV3_1Straight_B.MathFunction_o5[2] =
          CSE1_CV3_1Straight_B.S_2psi_ds2[1];
        CSE1_CV3_1Straight_B.MathFunction_o5[3] =
          CSE1_CV3_1Straight_B.S_2psi_ds2[3];
      }

      /* Product: '<S276>/Product' */
      for (i = 0; i < 2; i++) {
        tmp_2[i] = 0.0;
        tmp_2[i] += CSE1_CV3_1Straight_B.MathFunction_o5[i] *
          CSE1_CV3_1Straight_B.MathFunction_id[0];
        tmp_2[i] += CSE1_CV3_1Straight_B.MathFunction_o5[i + 2] *
          CSE1_CV3_1Straight_B.MathFunction_id[1];
        tmp_2[i + 2] = 0.0;
        tmp_2[i + 2] += CSE1_CV3_1Straight_B.MathFunction_o5[i] *
          CSE1_CV3_1Straight_B.MathFunction_id[2];
        tmp_2[i + 2] += CSE1_CV3_1Straight_B.MathFunction_o5[i + 2] *
          CSE1_CV3_1Straight_B.MathFunction_id[3];
      }

      CSE1_CV3_1Straight_B.Product_fm[0] = 0.0;
      CSE1_CV3_1Straight_B.Product_fm[0] = tmp_2[0] * CSE1_CV3_1Straight_B.qp_d
        [0] + CSE1_CV3_1Straight_B.Product_fm[0];
      CSE1_CV3_1Straight_B.Product_fm[0] = tmp_2[2] * CSE1_CV3_1Straight_B.qp_d
        [1] + CSE1_CV3_1Straight_B.Product_fm[0];
      CSE1_CV3_1Straight_B.Product_fm[1] = 0.0;
      CSE1_CV3_1Straight_B.Product_fm[1] = tmp_2[1] * CSE1_CV3_1Straight_B.qp_d
        [0] + CSE1_CV3_1Straight_B.Product_fm[1];
      CSE1_CV3_1Straight_B.Product_fm[1] = tmp_2[3] * CSE1_CV3_1Straight_B.qp_d
        [1] + CSE1_CV3_1Straight_B.Product_fm[1];

      /* Product: '<S276>/Product1' */
      for (i = 0; i < 2; i++) {
        tmp_2[i] = 0.0;
        tmp_2[i] += CSE1_CV3_1Straight_B.MathFunction_h2[i] *
          CSE1_CV3_1Straight_B.MathFunction_h2[0];
        tmp_2[i] += CSE1_CV3_1Straight_B.MathFunction_h2[i + 2] *
          CSE1_CV3_1Straight_B.MathFunction_h2[1];
        tmp_2[i + 2] = 0.0;
        tmp_2[i + 2] += CSE1_CV3_1Straight_B.MathFunction_h2[i] *
          CSE1_CV3_1Straight_B.MathFunction_h2[2];
        tmp_2[i + 2] += CSE1_CV3_1Straight_B.MathFunction_h2[i + 2] *
          CSE1_CV3_1Straight_B.MathFunction_h2[3];
      }

      for (i = 0; i < 2; i++) {
        tmp_3[i] = 0.0;
        tmp_3[i] += tmp_2[i] * CSE1_CV3_1Straight_B.MathFunction_id[0];
        tmp_3[i] += tmp_2[i + 2] * CSE1_CV3_1Straight_B.MathFunction_id[1];
        tmp_3[i + 2] = 0.0;
        tmp_3[i + 2] += tmp_2[i] * CSE1_CV3_1Straight_B.MathFunction_id[2];
        tmp_3[i + 2] += tmp_2[i + 2] * CSE1_CV3_1Straight_B.MathFunction_id[3];
      }

      CSE1_CV3_1Straight_B.Product1_cv[0] = 0.0;
      CSE1_CV3_1Straight_B.Product1_cv[0] = tmp_3[0] *
        CSE1_CV3_1Straight_B.qp_d[0] + CSE1_CV3_1Straight_B.Product1_cv[0];
      CSE1_CV3_1Straight_B.Product1_cv[0] = tmp_3[2] *
        CSE1_CV3_1Straight_B.qp_d[1] + CSE1_CV3_1Straight_B.Product1_cv[0];
      CSE1_CV3_1Straight_B.Product1_cv[1] = 0.0;
      CSE1_CV3_1Straight_B.Product1_cv[1] = tmp_3[1] *
        CSE1_CV3_1Straight_B.qp_d[0] + CSE1_CV3_1Straight_B.Product1_cv[1];
      CSE1_CV3_1Straight_B.Product1_cv[1] = tmp_3[3] *
        CSE1_CV3_1Straight_B.qp_d[1] + CSE1_CV3_1Straight_B.Product1_cv[1];
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        /* Product: '<S276>/Product2' */
        for (i = 0; i < 2; i++) {
          tmp_2[i] = 0.0;
          tmp_2[i] += CSE1_CV3_1Straight_B.MathFunction_h2[i] *
            CSE1_CV3_1Straight_B.MathFunction_id[0];
          tmp_2[i] += CSE1_CV3_1Straight_B.MathFunction_h2[i + 2] *
            CSE1_CV3_1Straight_B.MathFunction_id[1];
          tmp_2[i + 2] = 0.0;
          tmp_2[i + 2] += CSE1_CV3_1Straight_B.MathFunction_h2[i] *
            CSE1_CV3_1Straight_B.MathFunction_id[2];
          tmp_2[i + 2] += CSE1_CV3_1Straight_B.MathFunction_h2[i + 2] *
            CSE1_CV3_1Straight_B.MathFunction_id[3];
        }

        CSE1_CV3_1Straight_B.Product2_cp[0] = 0.0;
        CSE1_CV3_1Straight_B.Product2_cp[0] = tmp_2[0] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0] +
          CSE1_CV3_1Straight_B.Product2_cp[0];
        CSE1_CV3_1Straight_B.Product2_cp[0] = tmp_2[2] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1] +
          CSE1_CV3_1Straight_B.Product2_cp[0];

        /* Gain: '<S276>/2' */
        CSE1_CV3_1Straight_B.u_n[0] = CSE1_CV3_1Straight_P._Gain_a *
          CSE1_CV3_1Straight_B.Product2_cp[0];

        /* Product: '<S276>/Product3' */
        CSE1_CV3_1Straight_B.Product3_f[0] = 0.0;
        CSE1_CV3_1Straight_B.Product3_f[0] =
          CSE1_CV3_1Straight_B.MathFunction_id[0] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[0] +
          CSE1_CV3_1Straight_B.Product3_f[0];
        CSE1_CV3_1Straight_B.Product3_f[0] =
          CSE1_CV3_1Straight_B.MathFunction_id[2] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[1] +
          CSE1_CV3_1Straight_B.Product3_f[0];
        CSE1_CV3_1Straight_B.Product2_cp[1] = 0.0;
        CSE1_CV3_1Straight_B.Product2_cp[1] = tmp_2[1] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[0] +
          CSE1_CV3_1Straight_B.Product2_cp[1];
        CSE1_CV3_1Straight_B.Product2_cp[1] = tmp_2[3] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunctionIn[1] +
          CSE1_CV3_1Straight_B.Product2_cp[1];

        /* Gain: '<S276>/2' */
        CSE1_CV3_1Straight_B.u_n[1] = CSE1_CV3_1Straight_P._Gain_a *
          CSE1_CV3_1Straight_B.Product2_cp[1];

        /* Product: '<S276>/Product3' */
        CSE1_CV3_1Straight_B.Product3_f[1] = 0.0;
        CSE1_CV3_1Straight_B.Product3_f[1] =
          CSE1_CV3_1Straight_B.MathFunction_id[1] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[0] +
          CSE1_CV3_1Straight_B.Product3_f[1];
        CSE1_CV3_1Straight_B.Product3_f[1] =
          CSE1_CV3_1Straight_B.MathFunction_id[3] *
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtMathFunction_o[1] +
          CSE1_CV3_1Straight_B.Product3_f[1];
      }

      /* Sum: '<S276>/Sum' */
      CSE1_CV3_1Straight_B.Sum_mf[0] = ((CSE1_CV3_1Straight_B.Product_fm[0] +
        CSE1_CV3_1Straight_B.Product1_cv[0]) - CSE1_CV3_1Straight_B.u_n[0]) -
        CSE1_CV3_1Straight_B.Product3_f[0];

      /* Gain: '<S276>/Gain' */
      CSE1_CV3_1Straight_B.Gain_il[0] = CSE1_CV3_1Straight_P.Gain_Gain_f *
        CSE1_CV3_1Straight_B.Sum_mf[0];

      /* Sum: '<S276>/Sum' */
      CSE1_CV3_1Straight_B.Sum_mf[1] = ((CSE1_CV3_1Straight_B.Product_fm[1] +
        CSE1_CV3_1Straight_B.Product1_cv[1]) - CSE1_CV3_1Straight_B.u_n[1]) -
        CSE1_CV3_1Straight_B.Product3_f[1];

      /* Gain: '<S276>/Gain' */
      CSE1_CV3_1Straight_B.Gain_il[1] = CSE1_CV3_1Straight_P.Gain_Gain_f *
        CSE1_CV3_1Straight_B.Sum_mf[1];

      /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S236>/Multiport Selector4' */
      {
        const byte_T *u = (byte_T *)CSE1_CV3_1Straight_B.Gain_il;/* input port */
        const int32_T *index = (const int32_T *)
          &CSE1_CV3_1Straight_ConstP.pooled1;
        const int32_T *length = (const int32_T *)
          &CSE1_CV3_1Straight_ConstP.pooled1;
        const int_T numRowsThisOutput = *length++;
        const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
        byte_T *y = (byte_T *)&CSE1_CV3_1Straight_B.MultiportSelector4;
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
        }                              /* output row loop */
      }                                /* end <S236>/Multiport Selector4 */

      /* Product: '<S258>/Product1' */
      CSE1_CV3_1Straight_B.Product1_k = CSE1_CV3_1Straight_B.MultiportSelector4 *
        CSE1_CV3_1Straight_B.Add_cn;

      /* Product: '<S258>/Product2' incorporates:
       *  Constant: '<S258>/2'
       */
      CSE1_CV3_1Straight_B.Product2_h = CSE1_CV3_1Straight_P._Value_h *
        CSE1_CV3_1Straight_B.MultiportSelector;

      /* Math: '<S258>/Math Function3' */
      tmp_0 = CSE1_CV3_1Straight_B.MultiportSelector2;
      CSE1_CV3_1Straight_B.MathFunction3_n = tmp_0 * tmp_0;

      /* Product: '<S258>/Product4' */
      CSE1_CV3_1Straight_B.Product4_k = CSE1_CV3_1Straight_B.Product2_h *
        CSE1_CV3_1Straight_B.MathFunction3_n;

      /* Sum: '<S258>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_jo = CSE1_CV3_1Straight_B.Product1_k -
        CSE1_CV3_1Straight_B.Product4_k;

      /* Math: '<S258>/Math Function2' */
      tmp_0 = CSE1_CV3_1Straight_B.Add_cn;
      CSE1_CV3_1Straight_B.MathFunction2_e = tmp_0 * tmp_0;

      /* Product: '<S258>/Divide' */
      CSE1_CV3_1Straight_B.Divide_m5 = CSE1_CV3_1Straight_B.Subtract_jo /
        CSE1_CV3_1Straight_B.MathFunction2_e;

      /* Product: '<S258>/Product' */
      CSE1_CV3_1Straight_B.Product_fa = CSE1_CV3_1Straight_B.MathFunction_hv *
        CSE1_CV3_1Straight_B.Divide_m5;

      /* Sum: '<S258>/Subtract1' */
      CSE1_CV3_1Straight_B.Subtract1_g = CSE1_CV3_1Straight_B.Divide_n -
        CSE1_CV3_1Straight_B.Product_fa;
    }

    /* end of Outputs for SubSystem: '<S2>/Path-following' */

    /* Gain: '<S2>/path x_d' */
    CSE1_CV3_1Straight_B.pathx_d = CSE1_CV3_1Straight_P.pathx_d_Gain *
      CSE1_CV3_1Straight_B.x_2x_1sx_1;

    /* Gain: '<S2>/path y_d' */
    CSE1_CV3_1Straight_B.pathy_d = CSE1_CV3_1Straight_P.pathy_d_Gain *
      CSE1_CV3_1Straight_B.y_2y_1sy_1;

    /* Gain: '<S2>/path psi_d' */
    CSE1_CV3_1Straight_B.pathpsi_d = CSE1_CV3_1Straight_P.pathpsi_d_Gain *
      CSE1_CV3_1Straight_B.Gain1_o;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Gain: '<S11>/LabVIEW u_1' incorporates:
       *  Constant: '<S11>/u1'
       */
      CSE1_CV3_1Straight_B.LabVIEWu_1 = CSE1_CV3_1Straight_P.LabVIEWu_1_Gain *
        CSE1_CV3_1Straight_P.u1_Value;

      /* Gain: '<S11>/LabVIEW u_2' incorporates:
       *  Constant: '<S11>/u2'
       */
      CSE1_CV3_1Straight_B.LabVIEWu_2 = CSE1_CV3_1Straight_P.LabVIEWu_2_Gain *
        CSE1_CV3_1Straight_P.u2_Value;

      /* Gain: '<S11>/LabVIEW u_3' incorporates:
       *  Constant: '<S11>/u3'
       */
      CSE1_CV3_1Straight_B.LabVIEWu_3 = CSE1_CV3_1Straight_P.LabVIEWu_3_Gain *
        CSE1_CV3_1Straight_P.u3_Value;

      /* Gain: '<S11>/LabVIEW u_4' incorporates:
       *  Constant: '<S11>/u4'
       */
      CSE1_CV3_1Straight_B.LabVIEWu_4 = CSE1_CV3_1Straight_P.LabVIEWu_4_Gain *
        CSE1_CV3_1Straight_P.u4_Value;

      /* Gain: '<S11>/LabVIEW u_5' incorporates:
       *  Constant: '<S11>/u5'
       */
      CSE1_CV3_1Straight_B.LabVIEWu_5 = CSE1_CV3_1Straight_P.LabVIEWu_5_Gain *
        CSE1_CV3_1Straight_P.u5_Value;

      /* Gain: '<S10>/ScalingLY' incorporates:
       *  Constant: '<S10>/AS_LY'
       */
      CSE1_CV3_1Straight_B.ypositionofleftanalogstick11 =
        CSE1_CV3_1Straight_P.ScalingLY_Gain * CSE1_CV3_1Straight_P.AS_LY_Value;

      /* Gain: '<S8>/PS3 u_1' */
      CSE1_CV3_1Straight_B.u_1 = CSE1_CV3_1Straight_P.PS3u_1_Gain *
        CSE1_CV3_1Straight_B.ypositionofleftanalogstick11;

      /* Gain: '<S10>/ScalingLX' incorporates:
       *  Constant: '<S10>/AS_LX'
       */
      CSE1_CV3_1Straight_B.xpositionofleftanalogstick11 =
        CSE1_CV3_1Straight_P.ScalingLX_Gain * CSE1_CV3_1Straight_P.AS_LX_Value;

      /* Gain: '<S8>/PS3 u_2' */
      CSE1_CV3_1Straight_B.u_2 = CSE1_CV3_1Straight_P.PS3u_2_Gain *
        CSE1_CV3_1Straight_B.xpositionofleftanalogstick11;

      /* Gain: '<S10>/ScalingRY' incorporates:
       *  Constant: '<S10>/AS_RY'
       */
      CSE1_CV3_1Straight_B.ypositionofrightanalogstick11 =
        CSE1_CV3_1Straight_P.ScalingRY_Gain * CSE1_CV3_1Straight_P.AS_RY_Value;

      /* Gain: '<S8>/PS3 u_3' */
      CSE1_CV3_1Straight_B.u_3 = CSE1_CV3_1Straight_P.PS3u_3_Gain *
        CSE1_CV3_1Straight_B.ypositionofrightanalogstick11;

      /* Gain: '<S10>/Scaling_RX' incorporates:
       *  Constant: '<S10>/AS_RX'
       */
      CSE1_CV3_1Straight_B.xpositionofrightanalogstick11 =
        CSE1_CV3_1Straight_P.Scaling_RX_Gain * CSE1_CV3_1Straight_P.AS_RX_Value;

      /* Gain: '<S8>/PS3 u_4' */
      CSE1_CV3_1Straight_B.u_4 = CSE1_CV3_1Straight_P.PS3u_4_Gain *
        CSE1_CV3_1Straight_B.xpositionofrightanalogstick11;

      /* Sum: '<S8>/Add' incorporates:
       *  Constant: '<S10>/L2'
       *  Constant: '<S10>/R2'
       */
      CSE1_CV3_1Straight_B.BowThrusterdirection = CSE1_CV3_1Straight_P.L2_Value
        + CSE1_CV3_1Straight_P.R2_Value;

      /* Gain: '<S8>/PS3 u_5' */
      CSE1_CV3_1Straight_B.u_5 = CSE1_CV3_1Straight_P.PS3u_5_Gain *
        CSE1_CV3_1Straight_B.BowThrusterdirection;

      /* Gain: '<S218>/-l_x1' incorporates:
       *  Constant: '<S218>/l_x1'
       */
      CSE1_CV3_1Straight_B.l_x1 = CSE1_CV3_1Straight_P.l_x1_Gain *
        CSE1_CV3_1Straight_P.l_x1_Value;

      /* Gain: '<S218>/-l_y2' incorporates:
       *  Constant: '<S218>/l_y2'
       */
      CSE1_CV3_1Straight_B.l_y2 = CSE1_CV3_1Straight_P.l_y2_Gain *
        CSE1_CV3_1Straight_P.l_y2_Value;

      /* Gain: '<S218>/-l_x2' incorporates:
       *  Constant: '<S218>/l_x2'
       */
      CSE1_CV3_1Straight_B.l_x2 = CSE1_CV3_1Straight_P.l_x2_Gain *
        CSE1_CV3_1Straight_P.l_x2_Value;

      /* Reshape: '<S218>/3x5' incorporates:
       *  Constant: '<S218>/T_e11'
       *  Constant: '<S218>/T_e12'
       *  Constant: '<S218>/T_e13'
       *  Constant: '<S218>/T_e14'
       *  Constant: '<S218>/T_e15'
       *  Constant: '<S218>/T_e21'
       *  Constant: '<S218>/T_e22'
       *  Constant: '<S218>/T_e23'
       *  Constant: '<S218>/T_e24'
       *  Constant: '<S218>/T_e25'
       *  Constant: '<S218>/l_x3'
       *  Constant: '<S218>/l_y1'
       */
      CSE1_CV3_1Straight_B.x5[0] = CSE1_CV3_1Straight_P.T_e11_Value;
      CSE1_CV3_1Straight_B.x5[1] = CSE1_CV3_1Straight_P.T_e21_Value;
      CSE1_CV3_1Straight_B.x5[2] = CSE1_CV3_1Straight_P.l_y1_Value;
      CSE1_CV3_1Straight_B.x5[3] = CSE1_CV3_1Straight_P.T_e12_Value;
      CSE1_CV3_1Straight_B.x5[4] = CSE1_CV3_1Straight_P.T_e22_Value;
      CSE1_CV3_1Straight_B.x5[5] = CSE1_CV3_1Straight_B.l_x1;
      CSE1_CV3_1Straight_B.x5[6] = CSE1_CV3_1Straight_P.T_e13_Value;
      CSE1_CV3_1Straight_B.x5[7] = CSE1_CV3_1Straight_P.T_e23_Value;
      CSE1_CV3_1Straight_B.x5[8] = CSE1_CV3_1Straight_B.l_y2;
      CSE1_CV3_1Straight_B.x5[9] = CSE1_CV3_1Straight_P.T_e14_Value;
      CSE1_CV3_1Straight_B.x5[10] = CSE1_CV3_1Straight_P.T_e24_Value;
      CSE1_CV3_1Straight_B.x5[11] = CSE1_CV3_1Straight_B.l_x2;
      CSE1_CV3_1Straight_B.x5[12] = CSE1_CV3_1Straight_P.T_e15_Value;
      CSE1_CV3_1Straight_B.x5[13] = CSE1_CV3_1Straight_P.T_e25_Value;
      CSE1_CV3_1Straight_B.x5[14] = CSE1_CV3_1Straight_P.l_x3_Value;

      /* S-Function (sdsppinv): '<S197>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&CSE1_CV3_1Straight_DWork.Pseudoinverse_X[0]), (void *)
             (&CSE1_CV3_1Straight_B.x5[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&CSE1_CV3_1Straight_DWork.Pseudoinverse_X[0], 3, 5,
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_S[0],
                      &CSE1_CV3_1Straight_DWork.Inverse_DWORK3[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_WORK[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_U[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&CSE1_CV3_1Straight_DWork.Pseudoinverse_S[0],
          &CSE1_CV3_1Straight_DWork.Pseudoinverse_U[0],
          &CSE1_CV3_1Straight_DWork.Pseudoinverse_V[0],
          &CSE1_CV3_1Straight_B.Pseudoinverse[0], (const int32_T)3, (const
          int32_T)5);
      }

      /* Sum: '<S12>/Sum1' */
      CSE1_CV3_1Straight_B.Sum1 =
        CSE1_CV3_1Straight_B.ypositionofleftanalogstick11 +
        CSE1_CV3_1Straight_B.ypositionofrightanalogstick11;

      /* Gain: '<S12>/tau_surge' */
      CSE1_CV3_1Straight_B.tau_surge = CSE1_CV3_1Straight_P.tau_surge_Gain *
        CSE1_CV3_1Straight_B.Sum1;

      /* Sum: '<S12>/Sum2' */
      CSE1_CV3_1Straight_B.Sum2 =
        CSE1_CV3_1Straight_B.xpositionofleftanalogstick11 +
        CSE1_CV3_1Straight_B.xpositionofrightanalogstick11;

      /* Gain: '<S12>/tau_sway' */
      CSE1_CV3_1Straight_B.tau_sway = CSE1_CV3_1Straight_P.tau_sway_Gain *
        CSE1_CV3_1Straight_B.Sum2;

      /* Sum: '<S12>/Sum' incorporates:
       *  Constant: '<S10>/L2'
       *  Constant: '<S10>/R2'
       */
      CSE1_CV3_1Straight_B.Sum = CSE1_CV3_1Straight_P.L2_Value +
        CSE1_CV3_1Straight_P.R2_Value;

      /* Gain: '<S12>/tau_yaw' */
      CSE1_CV3_1Straight_B.tau_yaw = CSE1_CV3_1Straight_P.tau_yaw_Gain *
        CSE1_CV3_1Straight_B.Sum;

      /* SignalConversion: '<S197>/TmpHiddenBufferAtProductInport2' */
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport2[0] =
        CSE1_CV3_1Straight_B.tau_surge;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport2[1] =
        CSE1_CV3_1Straight_B.tau_sway;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport2[2] =
        CSE1_CV3_1Straight_B.tau_yaw;

      /* Product: '<S197>/Product' */
      for (i = 0; i < 5; i++) {
        CSE1_CV3_1Straight_B.Product_c[i] = 0.0;
        CSE1_CV3_1Straight_B.Product_c[i] = CSE1_CV3_1Straight_B.Pseudoinverse[i]
          * CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport2[0] +
          CSE1_CV3_1Straight_B.Product_c[i];
        CSE1_CV3_1Straight_B.Product_c[i] = CSE1_CV3_1Straight_B.Pseudoinverse[i
          + 5] * CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport2[1] +
          CSE1_CV3_1Straight_B.Product_c[i];
        CSE1_CV3_1Straight_B.Product_c[i] = CSE1_CV3_1Straight_B.Pseudoinverse[i
          + 10] * CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport2[2] +
          CSE1_CV3_1Straight_B.Product_c[i];
      }

      /* RelationalOperator: '<S203>/Compare' incorporates:
       *  Constant: '<S203>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_b = (CSE1_CV3_1Straight_B.Product_c[0] <
        CSE1_CV3_1Straight_P.Constant_Value_m);

      /* RelationalOperator: '<S205>/Compare' */
      CSE1_CV3_1Straight_B.Compare_a = (CSE1_CV3_1Straight_B.Product_c[0] == 0.0);

      /* Gain: '<S198>/Gain' */
      CSE1_CV3_1Straight_B.Gain_nh = (uint16_T)
        (CSE1_CV3_1Straight_P.Gain_Gain_fo * CSE1_CV3_1Straight_B.Compare_a);

      /* RelationalOperator: '<S204>/Compare' incorporates:
       *  Constant: '<S204>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_l = (CSE1_CV3_1Straight_B.Product_c[0] >
        CSE1_CV3_1Straight_P.Constant_Value_e);

      /* Gain: '<S198>/Gain1' */
      CSE1_CV3_1Straight_B.Gain1_ax = (uint16_T)
        (CSE1_CV3_1Straight_P.Gain1_Gain_g * CSE1_CV3_1Straight_B.Compare_l);

      /* Sum: '<S198>/Sum' */
      CSE1_CV3_1Straight_B.Sum_nj = (uint16_T)(uint32_T)
        (((CSE1_CV3_1Straight_B.Compare_b << 6) + CSE1_CV3_1Straight_B.Gain_nh)
         + CSE1_CV3_1Straight_B.Gain1_ax);

      /* Lookup Block: '<S198>/f_1 < 0'
       * About '<S198>/f_1 < 0 :'
       * Lookup Block: '<S198>/f_1 < 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_10),
                           CSE1_CV3_1Straight_P.f_10_YData,
                           CSE1_CV3_1Straight_B.Product_c[0],
                           CSE1_CV3_1Straight_P.f_10_XData, 8U);

      /* Lookup Block: '<S198>/f_1 > 0'
       * About '<S198>/f_1 > 0 :'
       * Lookup Block: '<S198>/f_1 > 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_10_i),
                           CSE1_CV3_1Straight_P.f_10_YData_h,
                           CSE1_CV3_1Straight_B.Product_c[0],
                           CSE1_CV3_1Straight_P.f_10_XData_n, 9U);

      /* MultiPortSwitch: '<S198>/Multiport Switch' incorporates:
       *  Constant: '<S198>/f_1 = 0'
       */
      switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_nj >> 6)) {
       case 1:
        CSE1_CV3_1Straight_B.MultiportSwitch_p = CSE1_CV3_1Straight_B.f_10;
        break;

       case 2:
        CSE1_CV3_1Straight_B.MultiportSwitch_p = CSE1_CV3_1Straight_P.f_10_Value;
        break;

       default:
        CSE1_CV3_1Straight_B.MultiportSwitch_p = CSE1_CV3_1Straight_B.f_10_i;
        break;
      }

      /* RelationalOperator: '<S206>/Compare' incorporates:
       *  Constant: '<S206>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_c = (CSE1_CV3_1Straight_B.Product_c[1] <
        CSE1_CV3_1Straight_P.Constant_Value_n);

      /* RelationalOperator: '<S208>/Compare' */
      CSE1_CV3_1Straight_B.Compare_o = (CSE1_CV3_1Straight_B.Product_c[1] == 0.0);

      /* Gain: '<S199>/Gain' */
      CSE1_CV3_1Straight_B.Gain_jc = (uint16_T)
        (CSE1_CV3_1Straight_P.Gain_Gain_g5 * CSE1_CV3_1Straight_B.Compare_o);

      /* RelationalOperator: '<S207>/Compare' incorporates:
       *  Constant: '<S207>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_e = (CSE1_CV3_1Straight_B.Product_c[1] >
        CSE1_CV3_1Straight_P.Constant_Value_j);

      /* Gain: '<S199>/Gain1' */
      CSE1_CV3_1Straight_B.Gain1_lk = (uint16_T)
        (CSE1_CV3_1Straight_P.Gain1_Gain_gm * CSE1_CV3_1Straight_B.Compare_e);

      /* Sum: '<S199>/Sum' */
      CSE1_CV3_1Straight_B.Sum_a = (uint16_T)(uint32_T)
        (((CSE1_CV3_1Straight_B.Compare_c << 6) + CSE1_CV3_1Straight_B.Gain_jc)
         + CSE1_CV3_1Straight_B.Gain1_lk);

      /* Lookup Block: '<S199>/f_2 < 0'
       * About '<S199>/f_2 < 0 :'
       * Lookup Block: '<S199>/f_2 < 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_20),
                           CSE1_CV3_1Straight_P.f_20_YData,
                           CSE1_CV3_1Straight_B.Product_c[1],
                           CSE1_CV3_1Straight_P.f_20_XData, 10U);

      /* Lookup Block: '<S199>/f_2 > 0'
       * About '<S199>/f_2 > 0 :'
       * Lookup Block: '<S199>/f_2 > 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_20_k),
                           CSE1_CV3_1Straight_P.f_20_YData_c,
                           CSE1_CV3_1Straight_B.Product_c[1],
                           CSE1_CV3_1Straight_P.f_20_XData_e, 9U);

      /* MultiPortSwitch: '<S199>/Multiport Switch' incorporates:
       *  Constant: '<S199>/f_2 = 0'
       */
      switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_a >> 6)) {
       case 1:
        CSE1_CV3_1Straight_B.MultiportSwitch_pq = CSE1_CV3_1Straight_B.f_20;
        break;

       case 2:
        CSE1_CV3_1Straight_B.MultiportSwitch_pq =
          CSE1_CV3_1Straight_P.f_20_Value;
        break;

       default:
        CSE1_CV3_1Straight_B.MultiportSwitch_pq = CSE1_CV3_1Straight_B.f_20_k;
        break;
      }

      /* RelationalOperator: '<S209>/Compare' incorporates:
       *  Constant: '<S209>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_d = (CSE1_CV3_1Straight_B.Product_c[2] <
        CSE1_CV3_1Straight_P.Constant_Value_h);

      /* RelationalOperator: '<S211>/Compare' */
      CSE1_CV3_1Straight_B.Compare_h = (CSE1_CV3_1Straight_B.Product_c[2] == 0.0);

      /* Gain: '<S200>/Gain' */
      CSE1_CV3_1Straight_B.Gain_m4 = (uint16_T)
        (CSE1_CV3_1Straight_P.Gain_Gain_ga * CSE1_CV3_1Straight_B.Compare_h);

      /* RelationalOperator: '<S210>/Compare' incorporates:
       *  Constant: '<S210>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_i = (CSE1_CV3_1Straight_B.Product_c[2] >
        CSE1_CV3_1Straight_P.Constant_Value_mx);

      /* Gain: '<S200>/Gain1' */
      CSE1_CV3_1Straight_B.Gain1_ot = (uint16_T)
        (CSE1_CV3_1Straight_P.Gain1_Gain_af * CSE1_CV3_1Straight_B.Compare_i);

      /* Sum: '<S200>/Sum' */
      CSE1_CV3_1Straight_B.Sum_h = (uint16_T)(uint32_T)
        (((CSE1_CV3_1Straight_B.Compare_d << 6) + CSE1_CV3_1Straight_B.Gain_m4)
         + CSE1_CV3_1Straight_B.Gain1_ot);

      /* Lookup Block: '<S200>/f_3 < 0'
       * About '<S200>/f_3 < 0 :'
       * Lookup Block: '<S200>/f_3 < 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_30),
                           CSE1_CV3_1Straight_P.f_30_YData,
                           CSE1_CV3_1Straight_B.Product_c[2],
                           CSE1_CV3_1Straight_P.f_30_XData, 7U);

      /* Lookup Block: '<S200>/f_3 > 0'
       * About '<S200>/f_3 > 0 :'
       * Lookup Block: '<S200>/f_3 > 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_30_i),
                           CSE1_CV3_1Straight_P.f_30_YData_c,
                           CSE1_CV3_1Straight_B.Product_c[2],
                           CSE1_CV3_1Straight_P.f_30_XData_n, 10U);

      /* MultiPortSwitch: '<S200>/Multiport Switch' incorporates:
       *  Constant: '<S200>/f_3 = 0'
       */
      switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_h >> 6)) {
       case 1:
        CSE1_CV3_1Straight_B.MultiportSwitch_l = CSE1_CV3_1Straight_B.f_30;
        break;

       case 2:
        CSE1_CV3_1Straight_B.MultiportSwitch_l = CSE1_CV3_1Straight_P.f_30_Value;
        break;

       default:
        CSE1_CV3_1Straight_B.MultiportSwitch_l = CSE1_CV3_1Straight_B.f_30_i;
        break;
      }

      /* RelationalOperator: '<S212>/Compare' incorporates:
       *  Constant: '<S212>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_g = (CSE1_CV3_1Straight_B.Product_c[3] <
        CSE1_CV3_1Straight_P.Constant_Value_b);

      /* RelationalOperator: '<S214>/Compare' */
      CSE1_CV3_1Straight_B.Compare_ic = (CSE1_CV3_1Straight_B.Product_c[3] ==
        0.0);

      /* Gain: '<S201>/Gain' */
      CSE1_CV3_1Straight_B.Gain_mu = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_l
        * CSE1_CV3_1Straight_B.Compare_ic);

      /* RelationalOperator: '<S213>/Compare' incorporates:
       *  Constant: '<S213>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_m = (CSE1_CV3_1Straight_B.Product_c[3] >
        CSE1_CV3_1Straight_P.Constant_Value_eu);

      /* Gain: '<S201>/Gain1' */
      CSE1_CV3_1Straight_B.Gain1_g = (uint16_T)
        (CSE1_CV3_1Straight_P.Gain1_Gain_ay * CSE1_CV3_1Straight_B.Compare_m);

      /* Sum: '<S201>/Sum' */
      CSE1_CV3_1Straight_B.Sum_cr = (uint16_T)(uint32_T)
        (((CSE1_CV3_1Straight_B.Compare_g << 6) + CSE1_CV3_1Straight_B.Gain_mu)
         + CSE1_CV3_1Straight_B.Gain1_g);

      /* Lookup Block: '<S201>/f_4 < 0'
       * About '<S201>/f_4 < 0 :'
       * Lookup Block: '<S201>/f_4 < 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_40),
                           CSE1_CV3_1Straight_P.f_40_YData,
                           CSE1_CV3_1Straight_B.Product_c[3],
                           CSE1_CV3_1Straight_P.f_40_XData, 9U);

      /* Lookup Block: '<S201>/f_4 > 0'
       * About '<S201>/f_4 > 0 :'
       * Lookup Block: '<S201>/f_4 > 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_40_n),
                           CSE1_CV3_1Straight_P.f_40_YData_o,
                           CSE1_CV3_1Straight_B.Product_c[3],
                           CSE1_CV3_1Straight_P.f_40_XData_a, 6U);

      /* MultiPortSwitch: '<S201>/Multiport Switch' incorporates:
       *  Constant: '<S201>/f_4 = 0'
       */
      switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_cr >> 6)) {
       case 1:
        CSE1_CV3_1Straight_B.MultiportSwitch_g = CSE1_CV3_1Straight_B.f_40;
        break;

       case 2:
        CSE1_CV3_1Straight_B.MultiportSwitch_g = CSE1_CV3_1Straight_P.f_40_Value;
        break;

       default:
        CSE1_CV3_1Straight_B.MultiportSwitch_g = CSE1_CV3_1Straight_B.f_40_n;
        break;
      }

      /* RelationalOperator: '<S215>/Compare' incorporates:
       *  Constant: '<S215>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_cp = (CSE1_CV3_1Straight_B.Product_c[4] <
        CSE1_CV3_1Straight_P.Constant_Value_f);

      /* RelationalOperator: '<S217>/Compare' */
      CSE1_CV3_1Straight_B.Compare_mo = (CSE1_CV3_1Straight_B.Product_c[4] ==
        0.0);

      /* Gain: '<S202>/Gain' */
      CSE1_CV3_1Straight_B.Gain_j1 = (uint16_T)
        (CSE1_CV3_1Straight_P.Gain_Gain_gh3 * CSE1_CV3_1Straight_B.Compare_mo);

      /* RelationalOperator: '<S216>/Compare' incorporates:
       *  Constant: '<S216>/Constant'
       */
      CSE1_CV3_1Straight_B.Compare_h2 = (CSE1_CV3_1Straight_B.Product_c[4] >
        CSE1_CV3_1Straight_P.Constant_Value_c);

      /* Gain: '<S202>/Gain1' */
      CSE1_CV3_1Straight_B.Gain1_n = (uint16_T)
        (CSE1_CV3_1Straight_P.Gain1_Gain_l * CSE1_CV3_1Straight_B.Compare_h2);

      /* Sum: '<S202>/Sum' */
      CSE1_CV3_1Straight_B.Sum_gp = (uint16_T)(uint32_T)
        (((CSE1_CV3_1Straight_B.Compare_cp << 6) + CSE1_CV3_1Straight_B.Gain_j1)
         + CSE1_CV3_1Straight_B.Gain1_n);

      /* Lookup Block: '<S202>/f_5 < 0'
       * About '<S202>/f_5 < 0 :'
       * Lookup Block: '<S202>/f_5 < 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_50),
                           CSE1_CV3_1Straight_P.f_50_YData,
                           CSE1_CV3_1Straight_B.Product_c[4],
                           CSE1_CV3_1Straight_P.f_50_XData, 2U);

      /* Lookup Block: '<S202>/f_5 > 0'
       * About '<S202>/f_5 > 0 :'
       * Lookup Block: '<S202>/f_5 > 0'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_50_g),
                           CSE1_CV3_1Straight_P.f_50_YData_f,
                           CSE1_CV3_1Straight_B.Product_c[4],
                           CSE1_CV3_1Straight_P.f_50_XData_g, 2U);

      /* MultiPortSwitch: '<S202>/Multiport Switch' incorporates:
       *  Constant: '<S202>/f_5 = 0'
       */
      switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_gp >> 6)) {
       case 1:
        CSE1_CV3_1Straight_B.MultiportSwitch_a = CSE1_CV3_1Straight_B.f_50;
        break;

       case 2:
        CSE1_CV3_1Straight_B.MultiportSwitch_a = CSE1_CV3_1Straight_P.f_50_Value;
        break;

       default:
        CSE1_CV3_1Straight_B.MultiportSwitch_a = CSE1_CV3_1Straight_B.f_50_g;
        break;
      }

      /* Saturate: '<S12>/Saturation' */
      tmp[0] = CSE1_CV3_1Straight_B.MultiportSwitch_p;
      tmp[1] = CSE1_CV3_1Straight_B.MultiportSwitch_pq;
      tmp[2] = CSE1_CV3_1Straight_B.MultiportSwitch_l;
      tmp[3] = CSE1_CV3_1Straight_B.MultiportSwitch_g;
      tmp[4] = CSE1_CV3_1Straight_B.MultiportSwitch_a;
      for (i = 0; i < 5; i++) {
        CSE1_CV3_1Straight_B.Saturation[i] = rt_SATURATE(tmp[i],
          CSE1_CV3_1Straight_P.Saturation_LowerSat,
          CSE1_CV3_1Straight_P.Saturation_UpperSat);
      }

      /* Gain: '<S12>/Joystick u_1' */
      CSE1_CV3_1Straight_B.Joysticku_1 = CSE1_CV3_1Straight_P.Joysticku_1_Gain *
        CSE1_CV3_1Straight_B.Saturation[0];

      /* Gain: '<S12>/Joystick u_2' */
      CSE1_CV3_1Straight_B.Joysticku_2 = CSE1_CV3_1Straight_P.Joysticku_2_Gain *
        CSE1_CV3_1Straight_B.Saturation[1];

      /* Gain: '<S12>/Joystick u_3' */
      CSE1_CV3_1Straight_B.Joysticku_3 = CSE1_CV3_1Straight_P.Joysticku_3_Gain *
        CSE1_CV3_1Straight_B.Saturation[2];

      /* Gain: '<S12>/Joystick u_4' */
      CSE1_CV3_1Straight_B.Joysticku_4 = CSE1_CV3_1Straight_P.Joysticku_4_Gain *
        CSE1_CV3_1Straight_B.Saturation[3];

      /* Gain: '<S12>/Joystick u_5' */
      CSE1_CV3_1Straight_B.Joysticku_5 = CSE1_CV3_1Straight_P.Joysticku_5_Gain *
        CSE1_CV3_1Straight_B.Saturation[4];

      /* Gain: '<S47>/-l_x1' incorporates:
       *  Constant: '<S47>/l_x1'
       */
      CSE1_CV3_1Straight_B.l_x1_k = CSE1_CV3_1Straight_P.l_x1_Gain_g *
        CSE1_CV3_1Straight_P.l_x1_Value_b;

      /* Gain: '<S47>/-l_y2' incorporates:
       *  Constant: '<S47>/l_y2'
       */
      CSE1_CV3_1Straight_B.l_y2_f = CSE1_CV3_1Straight_P.l_y2_Gain_a *
        CSE1_CV3_1Straight_P.l_y2_Value_i;

      /* Gain: '<S47>/-l_x2' incorporates:
       *  Constant: '<S47>/l_x2'
       */
      CSE1_CV3_1Straight_B.l_x2_a = CSE1_CV3_1Straight_P.l_x2_Gain_l *
        CSE1_CV3_1Straight_P.l_x2_Value_j;

      /* Reshape: '<S47>/3x5' incorporates:
       *  Constant: '<S47>/T_e11'
       *  Constant: '<S47>/T_e12'
       *  Constant: '<S47>/T_e13'
       *  Constant: '<S47>/T_e14'
       *  Constant: '<S47>/T_e15'
       *  Constant: '<S47>/T_e21'
       *  Constant: '<S47>/T_e22'
       *  Constant: '<S47>/T_e23'
       *  Constant: '<S47>/T_e24'
       *  Constant: '<S47>/T_e25'
       *  Constant: '<S47>/l_x3'
       *  Constant: '<S47>/l_y1'
       */
      CSE1_CV3_1Straight_B.x5_i[0] = CSE1_CV3_1Straight_P.T_e11_Value_m;
      CSE1_CV3_1Straight_B.x5_i[1] = CSE1_CV3_1Straight_P.T_e21_Value_l;
      CSE1_CV3_1Straight_B.x5_i[2] = CSE1_CV3_1Straight_P.l_y1_Value_c;
      CSE1_CV3_1Straight_B.x5_i[3] = CSE1_CV3_1Straight_P.T_e12_Value_i;
      CSE1_CV3_1Straight_B.x5_i[4] = CSE1_CV3_1Straight_P.T_e22_Value_a;
      CSE1_CV3_1Straight_B.x5_i[5] = CSE1_CV3_1Straight_B.l_x1_k;
      CSE1_CV3_1Straight_B.x5_i[6] = CSE1_CV3_1Straight_P.T_e13_Value_j;
      CSE1_CV3_1Straight_B.x5_i[7] = CSE1_CV3_1Straight_P.T_e23_Value_o;
      CSE1_CV3_1Straight_B.x5_i[8] = CSE1_CV3_1Straight_B.l_y2_f;
      CSE1_CV3_1Straight_B.x5_i[9] = CSE1_CV3_1Straight_P.T_e14_Value_c;
      CSE1_CV3_1Straight_B.x5_i[10] = CSE1_CV3_1Straight_P.T_e24_Value_o;
      CSE1_CV3_1Straight_B.x5_i[11] = CSE1_CV3_1Straight_B.l_x2_a;
      CSE1_CV3_1Straight_B.x5_i[12] = CSE1_CV3_1Straight_P.T_e15_Value_g;
      CSE1_CV3_1Straight_B.x5_i[13] = CSE1_CV3_1Straight_P.T_e25_Value_d;
      CSE1_CV3_1Straight_B.x5_i[14] = CSE1_CV3_1Straight_P.l_x3_Value_o;

      /* S-Function (sdsppinv): '<S26>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&CSE1_CV3_1Straight_DWork.Pseudoinverse_X[0]), (void *)
             (&CSE1_CV3_1Straight_B.x5_i[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&CSE1_CV3_1Straight_DWork.Pseudoinverse_X[0], 3, 5,
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_S[0],
                      &CSE1_CV3_1Straight_DWork.Inverse_DWORK3[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_WORK[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_U[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&CSE1_CV3_1Straight_DWork.Pseudoinverse_S[0],
          &CSE1_CV3_1Straight_DWork.Pseudoinverse_U[0],
          &CSE1_CV3_1Straight_DWork.Pseudoinverse_V[0],
          &CSE1_CV3_1Straight_B.Pseudoinverse_g[0], (const int32_T)3, (const
          int32_T)5);
      }
    }

    /* Integrator: '<S15>/Integrator' */
    CSE1_CV3_1Straight_B.eta[0] = CSE1_CV3_1Straight_X.Integrator_CSTATE_p[0];
    CSE1_CV3_1Straight_B.eta[1] = CSE1_CV3_1Straight_X.Integrator_CSTATE_p[1];
    CSE1_CV3_1Straight_B.eta[2] = CSE1_CV3_1Straight_X.Integrator_CSTATE_p[2];

    /* Saturate: '<S23>/Saturation' */
    tmp_0 = CSE1_CV3_1Straight_B.eta[2];
    CSE1_CV3_1Straight_B.Saturation_c = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation_LowerSat_o,
      CSE1_CV3_1Straight_P.Saturation_UpperSat_j);

    /* Signum: '<S23>/Sign' */
    CSE1_CV3_1Straight_B.Sign = rt_SIGNd_snf(CSE1_CV3_1Straight_B.Saturation_c);

    /* Gain: '<S23>/Gain' */
    CSE1_CV3_1Straight_B.Gain = CSE1_CV3_1Straight_P.Gain_Gain *
      CSE1_CV3_1Straight_B.Sign;

    /* Sum: '<S23>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_k = CSE1_CV3_1Straight_B.Saturation_c +
      CSE1_CV3_1Straight_B.Gain;

    /* Math: '<S23>/Math Function' incorporates:
     *  Constant: '<S23>/Constant'
     */
    CSE1_CV3_1Straight_B.MathFunction = rt_rem_snf(CSE1_CV3_1Straight_B.Sum1_k,
      CSE1_CV3_1Straight_P.Constant_Value_hq);

    /* Sum: '<S23>/Sum' */
    CSE1_CV3_1Straight_B.Sum_m = CSE1_CV3_1Straight_B.MathFunction -
      CSE1_CV3_1Straight_B.Gain;

    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/Enable Filter'
     */
    if ((int32_T)CSE1_CV3_1Straight_P.EnableFilter_Value == 0) {
      CSE1_CV3_1Straight_B.MultiportSwitch_b[0] = CSE1_CV3_1Straight_B.eta_surge;
      CSE1_CV3_1Straight_B.MultiportSwitch_b[1] = CSE1_CV3_1Straight_B.eta_sway;
      CSE1_CV3_1Straight_B.MultiportSwitch_b[2] = CSE1_CV3_1Straight_B.eta_yaw;
    } else {
      CSE1_CV3_1Straight_B.MultiportSwitch_b[0] = CSE1_CV3_1Straight_B.eta[0];
      CSE1_CV3_1Straight_B.MultiportSwitch_b[1] = CSE1_CV3_1Straight_B.eta[1];
      CSE1_CV3_1Straight_B.MultiportSwitch_b[2] = CSE1_CV3_1Straight_B.Sum_m;
    }

    /* Fcn: '<S14>/yaw angle' */
    CSE1_CV3_1Straight_B.psi = CSE1_CV3_1Straight_B.MultiportSwitch_b[2];

    /* Saturate: '<S19>/Saturation' */
    tmp_0 = CSE1_CV3_1Straight_B.psi;
    CSE1_CV3_1Straight_B.Saturation_p = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation_LowerSat_h,
      CSE1_CV3_1Straight_P.Saturation_UpperSat_o);

    /* Signum: '<S19>/Sign' */
    CSE1_CV3_1Straight_B.Sign_o = rt_SIGNd_snf(CSE1_CV3_1Straight_B.Saturation_p);

    /* Gain: '<S19>/Gain' */
    CSE1_CV3_1Straight_B.Gain_c = CSE1_CV3_1Straight_P.Gain_Gain_b *
      CSE1_CV3_1Straight_B.Sign_o;

    /* Sum: '<S19>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_o = CSE1_CV3_1Straight_B.Saturation_p +
      CSE1_CV3_1Straight_B.Gain_c;

    /* Math: '<S19>/Math Function' incorporates:
     *  Constant: '<S19>/Constant'
     */
    CSE1_CV3_1Straight_B.MathFunction_j = rt_rem_snf(CSE1_CV3_1Straight_B.Sum1_o,
      CSE1_CV3_1Straight_P.Constant_Value_k);

    /* Sum: '<S19>/Sum' */
    CSE1_CV3_1Straight_B.Sum_o = CSE1_CV3_1Straight_B.MathFunction_j -
      CSE1_CV3_1Straight_B.Gain_c;

    /* Gain: '<S14>/eta N' */
    CSE1_CV3_1Straight_B.etaN = CSE1_CV3_1Straight_P.etaN_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch_b[0];

    /* Gain: '<S14>/eta E' */
    CSE1_CV3_1Straight_B.etaE = CSE1_CV3_1Straight_P.etaE_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch_b[1];

    /* Gain: '<S14>/eta Psi' */
    CSE1_CV3_1Straight_B.etaPsi = CSE1_CV3_1Straight_P.etaPsi_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch_b[2];

    /* Sum: '<S14>/Sum2' */
    CSE1_CV3_1Straight_B.regulationerror[0] = CSE1_CV3_1Straight_B.eta_dDPN -
      CSE1_CV3_1Straight_B.etaN;
    CSE1_CV3_1Straight_B.regulationerror[1] = CSE1_CV3_1Straight_B.eta_dDPE -
      CSE1_CV3_1Straight_B.etaE;
    CSE1_CV3_1Straight_B.regulationerror[2] = CSE1_CV3_1Straight_B.eta_dDPPsi -
      CSE1_CV3_1Straight_B.etaPsi;

    /* Gain: '<S14>/Reg_e_N_hil' */
    CSE1_CV3_1Straight_B.Reg_e_N_hil = CSE1_CV3_1Straight_P.Reg_e_N_hil_Gain *
      CSE1_CV3_1Straight_B.regulationerror[0];

    /* Gain: '<S14>/Reg_e_E_hil' */
    CSE1_CV3_1Straight_B.Reg_e_E_hil = CSE1_CV3_1Straight_P.Reg_e_E_hil_Gain *
      CSE1_CV3_1Straight_B.regulationerror[1];

    /* Gain: '<S14>/Reg_e_Psi_hil' */
    CSE1_CV3_1Straight_B.Reg_e_Psi_hil = CSE1_CV3_1Straight_P.Reg_e_Psi_hil_Gain
      * CSE1_CV3_1Straight_B.regulationerror[2];

    /* Saturate: '<S18>/Saturation' */
    tmp_0 = CSE1_CV3_1Straight_B.Reg_e_Psi_hil;
    CSE1_CV3_1Straight_B.Saturation_a = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation_LowerSat_hf,
      CSE1_CV3_1Straight_P.Saturation_UpperSat_p);

    /* Signum: '<S18>/Sign' */
    CSE1_CV3_1Straight_B.Sign_m = rt_SIGNd_snf(CSE1_CV3_1Straight_B.Saturation_a);

    /* Gain: '<S18>/Gain' */
    CSE1_CV3_1Straight_B.Gain_ce = CSE1_CV3_1Straight_P.Gain_Gain_e *
      CSE1_CV3_1Straight_B.Sign_m;

    /* Sum: '<S18>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_h = CSE1_CV3_1Straight_B.Saturation_a +
      CSE1_CV3_1Straight_B.Gain_ce;

    /* Math: '<S18>/Math Function' incorporates:
     *  Constant: '<S18>/Constant'
     */
    CSE1_CV3_1Straight_B.MathFunction_e = rt_rem_snf(CSE1_CV3_1Straight_B.Sum1_h,
      CSE1_CV3_1Straight_P.Constant_Value_i);

    /* Sum: '<S18>/Sum' */
    CSE1_CV3_1Straight_B.Sum_i = CSE1_CV3_1Straight_B.MathFunction_e -
      CSE1_CV3_1Straight_B.Gain_ce;

    /* Fcn: '<S17>/Row1' */
    CSE1_CV3_1Straight_B.Row1 = cos(CSE1_CV3_1Straight_B.Sum_o) *
      CSE1_CV3_1Straight_B.Reg_e_N_hil + sin(CSE1_CV3_1Straight_B.Sum_o) *
      CSE1_CV3_1Straight_B.Reg_e_E_hil;

    /* Fcn: '<S17>/Row2' */
    CSE1_CV3_1Straight_B.Row2 = (-sin(CSE1_CV3_1Straight_B.Sum_o)) *
      CSE1_CV3_1Straight_B.Reg_e_N_hil + cos(CSE1_CV3_1Straight_B.Sum_o) *
      CSE1_CV3_1Straight_B.Reg_e_E_hil;

    /* Fcn: '<S17>/Row3' */
    CSE1_CV3_1Straight_B.Row3 = CSE1_CV3_1Straight_B.Sum_i;

    /* SignalConversion: '<S14>/TmpHiddenBufferAtKpInport1' */
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtKpInport1[0] =
      CSE1_CV3_1Straight_B.Row1;
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtKpInport1[1] =
      CSE1_CV3_1Straight_B.Row2;
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtKpInport1[2] =
      CSE1_CV3_1Straight_B.Row3;
    for (i = 0; i < 3; i++) {
      /* Gain: '<S14>/Kp' */
      CSE1_CV3_1Straight_B.Kp[i] = 0.0;
      CSE1_CV3_1Straight_B.Kp[i] = CSE1_CV3_1Straight_P.Kp_Gain[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtKpInport1[0] +
        CSE1_CV3_1Straight_B.Kp[i];
      CSE1_CV3_1Straight_B.Kp[i] = CSE1_CV3_1Straight_P.Kp_Gain[i + 3] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtKpInport1[1] +
        CSE1_CV3_1Straight_B.Kp[i];
      CSE1_CV3_1Straight_B.Kp[i] = CSE1_CV3_1Straight_P.Kp_Gain[i + 6] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtKpInport1[2] +
        CSE1_CV3_1Straight_B.Kp[i];

      /* Product: '<S14>/Product2' incorporates:
       *  Constant: '<S14>/Kp_scale'
       */
      CSE1_CV3_1Straight_B.Product2[i] = CSE1_CV3_1Straight_P.Kp_scale_Value *
        CSE1_CV3_1Straight_B.Kp[i];
    }

    /* Gain: '<S14>/K_p 1' */
    CSE1_CV3_1Straight_B.K_p1 = CSE1_CV3_1Straight_P.K_p1_Gain *
      CSE1_CV3_1Straight_B.Product2[0];

    /* Gain: '<S14>/K_p 2' */
    CSE1_CV3_1Straight_B.K_p2 = CSE1_CV3_1Straight_P.K_p2_Gain *
      CSE1_CV3_1Straight_B.Product2[1];

    /* Gain: '<S14>/K_p 3' */
    CSE1_CV3_1Straight_B.K_p3 = CSE1_CV3_1Straight_P.K_p3_Gain *
      CSE1_CV3_1Straight_B.Product2[2];

    /* Integrator Block: '<S14>/Integrator'
     */
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &CSE1_CV3_1Straig_PrevZCSigState.Integrator_Reset_ZCE_m,
                         CSE1_CV3_1Straight_P.Reset_DP_integrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || CSE1_CV3_1Straight_P.Reset_DP_integrator_Value != 0.0) {
        CSE1_CV3_1Straight_X.Integrator_CSTATE_c[0] =
          CSE1_CV3_1Straight_P.Integrator_IC_g;
        CSE1_CV3_1Straight_X.Integrator_CSTATE_c[1] =
          CSE1_CV3_1Straight_P.Integrator_IC_g;
        CSE1_CV3_1Straight_X.Integrator_CSTATE_c[2] =
          CSE1_CV3_1Straight_P.Integrator_IC_g;
      }
    }

    CSE1_CV3_1Straight_B.Integrator_o[0] =
      CSE1_CV3_1Straight_X.Integrator_CSTATE_c[0];
    CSE1_CV3_1Straight_B.Integrator_o[1] =
      CSE1_CV3_1Straight_X.Integrator_CSTATE_c[1];
    CSE1_CV3_1Straight_B.Integrator_o[2] =
      CSE1_CV3_1Straight_X.Integrator_CSTATE_c[2];

    /* Gain: '<S14>/K_i 1' */
    for (i = 0; i < 3; i++) {
      /* Gain: '<S14>/Ki' */
      CSE1_CV3_1Straight_B.Ki[i] = 0.0;
      CSE1_CV3_1Straight_B.Ki[i] = CSE1_CV3_1Straight_P.Ki_Gain[i] *
        CSE1_CV3_1Straight_B.Integrator_o[0] + CSE1_CV3_1Straight_B.Ki[i];
      CSE1_CV3_1Straight_B.Ki[i] = CSE1_CV3_1Straight_P.Ki_Gain[i + 3] *
        CSE1_CV3_1Straight_B.Integrator_o[1] + CSE1_CV3_1Straight_B.Ki[i];
      CSE1_CV3_1Straight_B.Ki[i] = CSE1_CV3_1Straight_P.Ki_Gain[i + 6] *
        CSE1_CV3_1Straight_B.Integrator_o[2] + CSE1_CV3_1Straight_B.Ki[i];

      /* Product: '<S14>/Product1' incorporates:
       *  Constant: '<S14>/Ki_scale'
       */
      CSE1_CV3_1Straight_B.Product1[i] = CSE1_CV3_1Straight_B.Ki[i] *
        CSE1_CV3_1Straight_P.Ki_scale_Value;

      /* Integrator: '<S15>/Integrator4' */
      CSE1_CV3_1Straight_B.nu_d[i] = CSE1_CV3_1Straight_X.Integrator4_CSTATE[i];
    }

    CSE1_CV3_1Straight_B.K_i1 = CSE1_CV3_1Straight_P.K_i1_Gain *
      CSE1_CV3_1Straight_B.Product1[0];

    /* Gain: '<S14>/K_i 2' */
    CSE1_CV3_1Straight_B.K_i2 = CSE1_CV3_1Straight_P.K_i2_Gain *
      CSE1_CV3_1Straight_B.Product1[1];

    /* Gain: '<S14>/K_i 3' */
    CSE1_CV3_1Straight_B.K_i3 = CSE1_CV3_1Straight_P.K_i3_Gain *
      CSE1_CV3_1Straight_B.Product1[2];

    /* Sum: '<S14>/Sum3' */
    CSE1_CV3_1Straight_B.Sum3[0] = CSE1_CV3_1Straight_B.K_p1 +
      CSE1_CV3_1Straight_B.K_i1;
    CSE1_CV3_1Straight_B.Sum3[1] = CSE1_CV3_1Straight_B.K_p2 +
      CSE1_CV3_1Straight_B.K_i2;
    CSE1_CV3_1Straight_B.Sum3[2] = CSE1_CV3_1Straight_B.K_p3 +
      CSE1_CV3_1Straight_B.K_i3;

    /* SignalConversion: '<S50>/TmpHiddenBufferAtProduct2Inport2' */
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[0] =
      CSE1_CV3_1Straight_B.nu_surge;
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[1] =
      CSE1_CV3_1Straight_B.nu_sway;
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[2] =
      CSE1_CV3_1Straight_B.nu_yaw;

    /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
     *  Constant: '<S6>/Enable Filter'
     */
    if ((int32_T)CSE1_CV3_1Straight_P.EnableFilter_Value == 0) {
      CSE1_CV3_1Straight_B.MultiportSwitch1[0] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[0];
      CSE1_CV3_1Straight_B.MultiportSwitch1[1] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[1];
      CSE1_CV3_1Straight_B.MultiportSwitch1[2] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[2];
    } else {
      CSE1_CV3_1Straight_B.MultiportSwitch1[0] = CSE1_CV3_1Straight_B.nu_d[0];
      CSE1_CV3_1Straight_B.MultiportSwitch1[1] = CSE1_CV3_1Straight_B.nu_d[1];
      CSE1_CV3_1Straight_B.MultiportSwitch1[2] = CSE1_CV3_1Straight_B.nu_d[2];
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S14>/Kd' */
      CSE1_CV3_1Straight_B.Kd[i] = 0.0;
      CSE1_CV3_1Straight_B.Kd[i] = CSE1_CV3_1Straight_P.Kd_Gain[i] *
        CSE1_CV3_1Straight_B.MultiportSwitch1[0] + CSE1_CV3_1Straight_B.Kd[i];
      CSE1_CV3_1Straight_B.Kd[i] = CSE1_CV3_1Straight_P.Kd_Gain[i + 3] *
        CSE1_CV3_1Straight_B.MultiportSwitch1[1] + CSE1_CV3_1Straight_B.Kd[i];
      CSE1_CV3_1Straight_B.Kd[i] = CSE1_CV3_1Straight_P.Kd_Gain[i + 6] *
        CSE1_CV3_1Straight_B.MultiportSwitch1[2] + CSE1_CV3_1Straight_B.Kd[i];

      /* Product: '<S14>/Product' incorporates:
       *  Constant: '<S14>/Kd_scale'
       */
      CSE1_CV3_1Straight_B.Product_l[i] = CSE1_CV3_1Straight_B.Kd[i] *
        CSE1_CV3_1Straight_P.Kd_scale_Value;
    }

    /* Gain: '<S14>/K_d 1' */
    CSE1_CV3_1Straight_B.K_d1 = CSE1_CV3_1Straight_P.K_d1_Gain *
      CSE1_CV3_1Straight_B.Product_l[0];

    /* Gain: '<S14>/K_d 2' */
    CSE1_CV3_1Straight_B.K_d2 = CSE1_CV3_1Straight_P.K_d2_Gain *
      CSE1_CV3_1Straight_B.Product_l[1];

    /* Gain: '<S14>/K_d 3' */
    CSE1_CV3_1Straight_B.K_d3 = CSE1_CV3_1Straight_P.K_d3_Gain *
      CSE1_CV3_1Straight_B.Product_l[2];

    /* Sum: '<S14>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_j[0] = CSE1_CV3_1Straight_B.Sum3[0] -
      CSE1_CV3_1Straight_B.K_d1;
    CSE1_CV3_1Straight_B.Sum1_j[1] = CSE1_CV3_1Straight_B.Sum3[1] -
      CSE1_CV3_1Straight_B.K_d2;
    CSE1_CV3_1Straight_B.Sum1_j[2] = CSE1_CV3_1Straight_B.Sum3[2] -
      CSE1_CV3_1Straight_B.K_d3;

    /* Gain: '<S6>/DP tau_surge' */
    CSE1_CV3_1Straight_B.DPtau_surge = CSE1_CV3_1Straight_P.DPtau_surge_Gain *
      CSE1_CV3_1Straight_B.Sum1_j[0];

    /* Gain: '<S6>/DP tau_sway' */
    CSE1_CV3_1Straight_B.DPtau_sway = CSE1_CV3_1Straight_P.DPtau_sway_Gain *
      CSE1_CV3_1Straight_B.Sum1_j[1];

    /* Gain: '<S6>/DP tau_yaw' */
    CSE1_CV3_1Straight_B.DPtau_yaw = CSE1_CV3_1Straight_P.DPtau_yaw_Gain *
      CSE1_CV3_1Straight_B.Sum1_j[2];

    /* SignalConversion: '<S26>/TmpHiddenBufferAtProductInport2' */
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[0] =
      CSE1_CV3_1Straight_B.DPtau_surge;
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[1] =
      CSE1_CV3_1Straight_B.DPtau_sway;
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[2] =
      CSE1_CV3_1Straight_B.DPtau_yaw;

    /* Product: '<S26>/Product' */
    for (i = 0; i < 5; i++) {
      CSE1_CV3_1Straight_B.Product_f[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_f[i] = CSE1_CV3_1Straight_B.Pseudoinverse_g[i]
        * CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[0] +
        CSE1_CV3_1Straight_B.Product_f[i];
      CSE1_CV3_1Straight_B.Product_f[i] = CSE1_CV3_1Straight_B.Pseudoinverse_g[i
        + 5] * CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[1] +
        CSE1_CV3_1Straight_B.Product_f[i];
      CSE1_CV3_1Straight_B.Product_f[i] = CSE1_CV3_1Straight_B.Pseudoinverse_g[i
        + 10] * CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[2] +
        CSE1_CV3_1Straight_B.Product_f[i];
    }

    /* RelationalOperator: '<S32>/Compare' incorporates:
     *  Constant: '<S32>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_gp = (CSE1_CV3_1Straight_B.Product_f[0] <
      CSE1_CV3_1Straight_P.Constant_Value_o);

    /* RelationalOperator: '<S34>/Compare' */
    CSE1_CV3_1Straight_B.Compare_p = (CSE1_CV3_1Straight_B.Product_f[0] == 0.0);

    /* Gain: '<S27>/Gain' */
    CSE1_CV3_1Straight_B.Gain_hh = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_ja *
      CSE1_CV3_1Straight_B.Compare_p);

    /* RelationalOperator: '<S33>/Compare' incorporates:
     *  Constant: '<S33>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_j = (CSE1_CV3_1Straight_B.Product_f[0] >
      CSE1_CV3_1Straight_P.Constant_Value_ed);

    /* Gain: '<S27>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_i2 = (uint16_T)(CSE1_CV3_1Straight_P.Gain1_Gain_d
      * CSE1_CV3_1Straight_B.Compare_j);

    /* Sum: '<S27>/Sum' */
    CSE1_CV3_1Straight_B.Sum_i2 = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_gp << 6) + CSE1_CV3_1Straight_B.Gain_hh) +
       CSE1_CV3_1Straight_B.Gain1_i2);

    /* Lookup Block: '<S27>/f_1 < 0'
     * About '<S27>/f_1 < 0 :'
     * Lookup Block: '<S27>/f_1 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_10_m),
                         CSE1_CV3_1Straight_P.f_10_YData_f,
                         CSE1_CV3_1Straight_B.Product_f[0],
                         CSE1_CV3_1Straight_P.f_10_XData_o, 8U);

    /* Lookup Block: '<S27>/f_1 > 0'
     * About '<S27>/f_1 > 0 :'
     * Lookup Block: '<S27>/f_1 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_10_l),
                         CSE1_CV3_1Straight_P.f_10_YData_l,
                         CSE1_CV3_1Straight_B.Product_f[0],
                         CSE1_CV3_1Straight_P.f_10_XData_h, 9U);

    /* MultiPortSwitch: '<S27>/Multiport Switch' incorporates:
     *  Constant: '<S27>/f_1 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_i2 >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_i = CSE1_CV3_1Straight_B.f_10_m;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_i = CSE1_CV3_1Straight_P.f_10_Value_c;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_i = CSE1_CV3_1Straight_B.f_10_l;
      break;
    }

    /* Gain: '<S6>/DP u_1' */
    CSE1_CV3_1Straight_B.DPu_1 = CSE1_CV3_1Straight_P.DPu_1_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch_i;

    /* RelationalOperator: '<S35>/Compare' incorporates:
     *  Constant: '<S35>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_ls = (CSE1_CV3_1Straight_B.Product_f[1] <
      CSE1_CV3_1Straight_P.Constant_Value_oa);

    /* RelationalOperator: '<S37>/Compare' */
    CSE1_CV3_1Straight_B.Compare_i3 = (CSE1_CV3_1Straight_B.Product_f[1] == 0.0);

    /* Gain: '<S28>/Gain' */
    CSE1_CV3_1Straight_B.Gain_p4 = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_gm *
      CSE1_CV3_1Straight_B.Compare_i3);

    /* RelationalOperator: '<S36>/Compare' incorporates:
     *  Constant: '<S36>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_n = (CSE1_CV3_1Straight_B.Product_f[1] >
      CSE1_CV3_1Straight_P.Constant_Value_cs);

    /* Gain: '<S28>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_b = (uint16_T)(CSE1_CV3_1Straight_P.Gain1_Gain_l5
      * CSE1_CV3_1Straight_B.Compare_n);

    /* Sum: '<S28>/Sum' */
    CSE1_CV3_1Straight_B.Sum_nt = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_ls << 6) + CSE1_CV3_1Straight_B.Gain_p4) +
       CSE1_CV3_1Straight_B.Gain1_b);

    /* Lookup Block: '<S28>/f_2 < 0'
     * About '<S28>/f_2 < 0 :'
     * Lookup Block: '<S28>/f_2 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_20_d),
                         CSE1_CV3_1Straight_P.f_20_YData_cj,
                         CSE1_CV3_1Straight_B.Product_f[1],
                         CSE1_CV3_1Straight_P.f_20_XData_c, 10U);

    /* Lookup Block: '<S28>/f_2 > 0'
     * About '<S28>/f_2 > 0 :'
     * Lookup Block: '<S28>/f_2 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_20_a),
                         CSE1_CV3_1Straight_P.f_20_YData_h,
                         CSE1_CV3_1Straight_B.Product_f[1],
                         CSE1_CV3_1Straight_P.f_20_XData_d, 9U);

    /* MultiPortSwitch: '<S28>/Multiport Switch' incorporates:
     *  Constant: '<S28>/f_2 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_nt >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_l3 = CSE1_CV3_1Straight_B.f_20_d;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_l3 =
        CSE1_CV3_1Straight_P.f_20_Value_h;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_l3 = CSE1_CV3_1Straight_B.f_20_a;
      break;
    }

    /* Gain: '<S6>/DP u_2' */
    CSE1_CV3_1Straight_B.DPu_2 = CSE1_CV3_1Straight_P.DPu_2_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch_l3;

    /* RelationalOperator: '<S38>/Compare' incorporates:
     *  Constant: '<S38>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_l5 = (CSE1_CV3_1Straight_B.Product_f[2] <
      CSE1_CV3_1Straight_P.Constant_Value_jk);

    /* RelationalOperator: '<S40>/Compare' */
    CSE1_CV3_1Straight_B.Compare_ps = (CSE1_CV3_1Straight_B.Product_f[2] == 0.0);

    /* Gain: '<S29>/Gain' */
    CSE1_CV3_1Straight_B.Gain_lm = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_dx *
      CSE1_CV3_1Straight_B.Compare_ps);

    /* RelationalOperator: '<S39>/Compare' incorporates:
     *  Constant: '<S39>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_ad = (CSE1_CV3_1Straight_B.Product_f[2] >
      CSE1_CV3_1Straight_P.Constant_Value_eq);

    /* Gain: '<S29>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_gb = (uint16_T)
      (CSE1_CV3_1Straight_P.Gain1_Gain_ax * CSE1_CV3_1Straight_B.Compare_ad);

    /* Sum: '<S29>/Sum' */
    CSE1_CV3_1Straight_B.Sum_hj = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_l5 << 6) + CSE1_CV3_1Straight_B.Gain_lm) +
       CSE1_CV3_1Straight_B.Gain1_gb);

    /* Lookup Block: '<S29>/f_3 < 0'
     * About '<S29>/f_3 < 0 :'
     * Lookup Block: '<S29>/f_3 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_30_e),
                         CSE1_CV3_1Straight_P.f_30_YData_o,
                         CSE1_CV3_1Straight_B.Product_f[2],
                         CSE1_CV3_1Straight_P.f_30_XData_h, 7U);

    /* Lookup Block: '<S29>/f_3 > 0'
     * About '<S29>/f_3 > 0 :'
     * Lookup Block: '<S29>/f_3 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_30_f),
                         CSE1_CV3_1Straight_P.f_30_YData_k,
                         CSE1_CV3_1Straight_B.Product_f[2],
                         CSE1_CV3_1Straight_P.f_30_XData_c, 10U);

    /* MultiPortSwitch: '<S29>/Multiport Switch' incorporates:
     *  Constant: '<S29>/f_3 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_hj >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_j = CSE1_CV3_1Straight_B.f_30_e;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_j = CSE1_CV3_1Straight_P.f_30_Value_a;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_j = CSE1_CV3_1Straight_B.f_30_f;
      break;
    }

    /* Gain: '<S6>/DP u_3' */
    CSE1_CV3_1Straight_B.DPu_3 = CSE1_CV3_1Straight_P.DPu_3_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch_j;

    /* RelationalOperator: '<S41>/Compare' incorporates:
     *  Constant: '<S41>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_no = (CSE1_CV3_1Straight_B.Product_f[3] <
      CSE1_CV3_1Straight_P.Constant_Value_nd);

    /* RelationalOperator: '<S43>/Compare' */
    CSE1_CV3_1Straight_B.Compare_d4 = (CSE1_CV3_1Straight_B.Product_f[3] == 0.0);

    /* Gain: '<S30>/Gain' */
    CSE1_CV3_1Straight_B.Gain_gj = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_jb *
      CSE1_CV3_1Straight_B.Compare_d4);

    /* RelationalOperator: '<S42>/Compare' incorporates:
     *  Constant: '<S42>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_k = (CSE1_CV3_1Straight_B.Product_f[3] >
      CSE1_CV3_1Straight_P.Constant_Value_g);

    /* Gain: '<S30>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_ll = (uint16_T)(CSE1_CV3_1Straight_P.Gain1_Gain_f
      * CSE1_CV3_1Straight_B.Compare_k);

    /* Sum: '<S30>/Sum' */
    CSE1_CV3_1Straight_B.Sum_du = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_no << 6) + CSE1_CV3_1Straight_B.Gain_gj) +
       CSE1_CV3_1Straight_B.Gain1_ll);

    /* Lookup Block: '<S30>/f_4 < 0'
     * About '<S30>/f_4 < 0 :'
     * Lookup Block: '<S30>/f_4 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_40_c),
                         CSE1_CV3_1Straight_P.f_40_YData_d,
                         CSE1_CV3_1Straight_B.Product_f[3],
                         CSE1_CV3_1Straight_P.f_40_XData_n, 9U);

    /* Lookup Block: '<S30>/f_4 > 0'
     * About '<S30>/f_4 > 0 :'
     * Lookup Block: '<S30>/f_4 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_40_g),
                         CSE1_CV3_1Straight_P.f_40_YData_dx,
                         CSE1_CV3_1Straight_B.Product_f[3],
                         CSE1_CV3_1Straight_P.f_40_XData_b, 6U);

    /* MultiPortSwitch: '<S30>/Multiport Switch' incorporates:
     *  Constant: '<S30>/f_4 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_du >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_c = CSE1_CV3_1Straight_B.f_40_c;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_c = CSE1_CV3_1Straight_P.f_40_Value_j;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_c = CSE1_CV3_1Straight_B.f_40_g;
      break;
    }

    /* Gain: '<S6>/DP u_4' */
    CSE1_CV3_1Straight_B.DPu_4 = CSE1_CV3_1Straight_P.DPu_4_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch_c;

    /* RelationalOperator: '<S44>/Compare' incorporates:
     *  Constant: '<S44>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_ba = (CSE1_CV3_1Straight_B.Product_f[4] <
      CSE1_CV3_1Straight_P.Constant_Value_hu);

    /* RelationalOperator: '<S46>/Compare' */
    CSE1_CV3_1Straight_B.Compare_mf = (CSE1_CV3_1Straight_B.Product_f[4] == 0.0);

    /* Gain: '<S31>/Gain' */
    CSE1_CV3_1Straight_B.Gain_m0 = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_d3 *
      CSE1_CV3_1Straight_B.Compare_mf);

    /* RelationalOperator: '<S45>/Compare' incorporates:
     *  Constant: '<S45>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_id = (CSE1_CV3_1Straight_B.Product_f[4] >
      CSE1_CV3_1Straight_P.Constant_Value_gz);

    /* Gain: '<S31>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_d = (uint16_T)(CSE1_CV3_1Straight_P.Gain1_Gain_o *
      CSE1_CV3_1Straight_B.Compare_id);

    /* Sum: '<S31>/Sum' */
    CSE1_CV3_1Straight_B.Sum_b = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_ba << 6) + CSE1_CV3_1Straight_B.Gain_m0) +
       CSE1_CV3_1Straight_B.Gain1_d);

    /* Lookup Block: '<S31>/f_5 < 0'
     * About '<S31>/f_5 < 0 :'
     * Lookup Block: '<S31>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_50_o),
                         CSE1_CV3_1Straight_P.f_50_YData_i,
                         CSE1_CV3_1Straight_B.Product_f[4],
                         CSE1_CV3_1Straight_P.f_50_XData_b, 2U);

    /* Lookup Block: '<S31>/f_5 > 0'
     * About '<S31>/f_5 > 0 :'
     * Lookup Block: '<S31>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_50_p),
                         CSE1_CV3_1Straight_P.f_50_YData_b,
                         CSE1_CV3_1Straight_B.Product_f[4],
                         CSE1_CV3_1Straight_P.f_50_XData_gn, 2U);

    /* MultiPortSwitch: '<S31>/Multiport Switch' incorporates:
     *  Constant: '<S31>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_b >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_m = CSE1_CV3_1Straight_B.f_50_o;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_m = CSE1_CV3_1Straight_P.f_50_Value_d;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_m = CSE1_CV3_1Straight_B.f_50_p;
      break;
    }

    /* Gain: '<S6>/DP u_5' */
    CSE1_CV3_1Straight_B.DPu_5 = CSE1_CV3_1Straight_P.DPu_5_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch_m;

    /* Saturate: '<S6>/Saturation' */
    tmp[0] = CSE1_CV3_1Straight_B.DPu_1;
    tmp[1] = CSE1_CV3_1Straight_B.DPu_2;
    tmp[2] = CSE1_CV3_1Straight_B.DPu_3;
    tmp[3] = CSE1_CV3_1Straight_B.DPu_4;
    tmp[4] = CSE1_CV3_1Straight_B.DPu_5;
    for (i = 0; i < 5; i++) {
      CSE1_CV3_1Straight_B.Saturation_cs[i] = rt_SATURATE(tmp[i],
        CSE1_CV3_1Straight_P.Saturation_LowerSat_k,
        CSE1_CV3_1Straight_P.Saturation_UpperSat_ok);
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Gain: '<S103>/-l_x1' incorporates:
       *  Constant: '<S103>/l_x1'
       */
      CSE1_CV3_1Straight_B.l_x1_a = CSE1_CV3_1Straight_P.l_x1_Gain_l *
        CSE1_CV3_1Straight_P.l_x1_Value_e;

      /* Gain: '<S103>/-l_y2' incorporates:
       *  Constant: '<S103>/l_y2'
       */
      CSE1_CV3_1Straight_B.l_y2_i = CSE1_CV3_1Straight_P.l_y2_Gain_n *
        CSE1_CV3_1Straight_P.l_y2_Value_h;

      /* Gain: '<S103>/-l_x2' incorporates:
       *  Constant: '<S103>/l_x2'
       */
      CSE1_CV3_1Straight_B.l_x2_d = CSE1_CV3_1Straight_P.l_x2_Gain_f *
        CSE1_CV3_1Straight_P.l_x2_Value_c;

      /* Reshape: '<S103>/3x5' incorporates:
       *  Constant: '<S103>/T_e11'
       *  Constant: '<S103>/T_e12'
       *  Constant: '<S103>/T_e13'
       *  Constant: '<S103>/T_e14'
       *  Constant: '<S103>/T_e15'
       *  Constant: '<S103>/T_e21'
       *  Constant: '<S103>/T_e22'
       *  Constant: '<S103>/T_e23'
       *  Constant: '<S103>/T_e24'
       *  Constant: '<S103>/T_e25'
       *  Constant: '<S103>/l_x3'
       *  Constant: '<S103>/l_y1'
       */
      CSE1_CV3_1Straight_B.x5_p[0] = CSE1_CV3_1Straight_P.T_e11_Value_d;
      CSE1_CV3_1Straight_B.x5_p[1] = CSE1_CV3_1Straight_P.T_e21_Value_c;
      CSE1_CV3_1Straight_B.x5_p[2] = CSE1_CV3_1Straight_P.l_y1_Value_b;
      CSE1_CV3_1Straight_B.x5_p[3] = CSE1_CV3_1Straight_P.T_e12_Value_c;
      CSE1_CV3_1Straight_B.x5_p[4] = CSE1_CV3_1Straight_P.T_e22_Value_e;
      CSE1_CV3_1Straight_B.x5_p[5] = CSE1_CV3_1Straight_B.l_x1_a;
      CSE1_CV3_1Straight_B.x5_p[6] = CSE1_CV3_1Straight_P.T_e13_Value_b;
      CSE1_CV3_1Straight_B.x5_p[7] = CSE1_CV3_1Straight_P.T_e23_Value_c;
      CSE1_CV3_1Straight_B.x5_p[8] = CSE1_CV3_1Straight_B.l_y2_i;
      CSE1_CV3_1Straight_B.x5_p[9] = CSE1_CV3_1Straight_P.T_e14_Value_p;
      CSE1_CV3_1Straight_B.x5_p[10] = CSE1_CV3_1Straight_P.T_e24_Value_k;
      CSE1_CV3_1Straight_B.x5_p[11] = CSE1_CV3_1Straight_B.l_x2_d;
      CSE1_CV3_1Straight_B.x5_p[12] = CSE1_CV3_1Straight_P.T_e15_Value_n;
      CSE1_CV3_1Straight_B.x5_p[13] = CSE1_CV3_1Straight_P.T_e25_Value_b;
      CSE1_CV3_1Straight_B.x5_p[14] = CSE1_CV3_1Straight_P.l_x3_Value_a;

      /* S-Function (sdsppinv): '<S82>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&CSE1_CV3_1Straight_DWork.Pseudoinverse_X[0]), (void *)
             (&CSE1_CV3_1Straight_B.x5_p[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&CSE1_CV3_1Straight_DWork.Pseudoinverse_X[0], 3, 5,
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_S[0],
                      &CSE1_CV3_1Straight_DWork.Inverse_DWORK3[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_WORK[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_U[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&CSE1_CV3_1Straight_DWork.Pseudoinverse_S[0],
          &CSE1_CV3_1Straight_DWork.Pseudoinverse_U[0],
          &CSE1_CV3_1Straight_DWork.Pseudoinverse_V[0],
          &CSE1_CV3_1Straight_B.Pseudoinverse_o[0], (const int32_T)3, (const
          int32_T)5);
      }
    }

    /* Trigonometry: '<S57>/R11' */
    CSE1_CV3_1Straight_B.R11_a = cos(CSE1_CV3_1Straight_B.eta_yaw);

    /* Trigonometry: '<S57>/R21' */
    CSE1_CV3_1Straight_B.R21_l = sin(CSE1_CV3_1Straight_B.eta_yaw);

    /* Trigonometry: '<S57>/R12' */
    CSE1_CV3_1Straight_B.R12_i = sin(CSE1_CV3_1Straight_B.eta_yaw);

    /* Gain: '<S57>/-1' */
    CSE1_CV3_1Straight_B.u = CSE1_CV3_1Straight_P.u_Gain *
      CSE1_CV3_1Straight_B.R12_i;

    /* Trigonometry: '<S57>/R22' */
    CSE1_CV3_1Straight_B.R22_c = cos(CSE1_CV3_1Straight_B.eta_yaw);

    /* Reshape: '<S57>/R(psi)' incorporates:
     *  Constant: '<S57>/R13'
     *  Constant: '<S57>/R23'
     *  Constant: '<S57>/R31'
     *  Constant: '<S57>/R32'
     *  Constant: '<S57>/R33'
     */
    CSE1_CV3_1Straight_B.Rpsi[0] = CSE1_CV3_1Straight_B.R11_a;
    CSE1_CV3_1Straight_B.Rpsi[1] = CSE1_CV3_1Straight_B.R21_l;
    CSE1_CV3_1Straight_B.Rpsi[2] = CSE1_CV3_1Straight_P.R31_Value;
    CSE1_CV3_1Straight_B.Rpsi[3] = CSE1_CV3_1Straight_B.u;
    CSE1_CV3_1Straight_B.Rpsi[4] = CSE1_CV3_1Straight_B.R22_c;
    CSE1_CV3_1Straight_B.Rpsi[5] = CSE1_CV3_1Straight_P.R32_Value;
    CSE1_CV3_1Straight_B.Rpsi[6] = CSE1_CV3_1Straight_P.R13_Value;
    CSE1_CV3_1Straight_B.Rpsi[7] = CSE1_CV3_1Straight_P.R23_Value;
    CSE1_CV3_1Straight_B.Rpsi[8] = CSE1_CV3_1Straight_P.R33_Value;

    /* Math: '<S58>/Math Function' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.MathFunction_l[3 * i] = CSE1_CV3_1Straight_B.Rpsi[i];
      CSE1_CV3_1Straight_B.MathFunction_l[1 + 3 * i] =
        CSE1_CV3_1Straight_B.Rpsi[i + 3];
      CSE1_CV3_1Straight_B.MathFunction_l[2 + 3 * i] =
        CSE1_CV3_1Straight_B.Rpsi[i + 6];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Reshape: '<S54>/3x3' incorporates:
       *  Constant: '<S54>/12'
       *  Constant: '<S54>/13'
       *  Constant: '<S54>/21'
       *  Constant: '<S54>/23'
       *  Constant: '<S54>/31'
       *  Constant: '<S54>/32'
       *  Constant: '<S7>/K_i_Surge'
       *  Constant: '<S7>/K_i_Sway'
       *  Constant: '<S7>/K_i_Yaw'
       */
      CSE1_CV3_1Straight_B.x3[0] = CSE1_CV3_1Straight_P.K_i_Surge_Value;
      CSE1_CV3_1Straight_B.x3[1] = CSE1_CV3_1Straight_P.u_Value;
      CSE1_CV3_1Straight_B.x3[2] = CSE1_CV3_1Straight_P.u_Value_m;
      CSE1_CV3_1Straight_B.x3[3] = CSE1_CV3_1Straight_P.u_Value_c;
      CSE1_CV3_1Straight_B.x3[4] = CSE1_CV3_1Straight_P.K_i_Sway_Value;
      CSE1_CV3_1Straight_B.x3[5] = CSE1_CV3_1Straight_P.u_Value_d;
      CSE1_CV3_1Straight_B.x3[6] = CSE1_CV3_1Straight_P.u_Value_a;
      CSE1_CV3_1Straight_B.x3[7] = CSE1_CV3_1Straight_P.u_Value_dx;
      CSE1_CV3_1Straight_B.x3[8] = CSE1_CV3_1Straight_P.K_i_Yaw_Value;
    }

    /* Integrator: '<S52>/Integrator' */
    CSE1_CV3_1Straight_B.Integrator_n[0] =
      CSE1_CV3_1Straight_X.Integrator_CSTATE_k[0];
    CSE1_CV3_1Straight_B.Integrator_n[1] =
      CSE1_CV3_1Straight_X.Integrator_CSTATE_k[1];
    CSE1_CV3_1Straight_B.Integrator_n[2] =
      CSE1_CV3_1Straight_X.Integrator_CSTATE_k[2];

    /* Product: '<S50>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_4[i + 3 * tmp_8] = 0.0;
        tmp_4[i + 3 * tmp_8] = tmp_4[3 * tmp_8 + i] + CSE1_CV3_1Straight_B.x3[3 *
          tmp_8] * CSE1_CV3_1Straight_B.MathFunction_l[i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.x3[3 * tmp_8 + 1] *
          CSE1_CV3_1Straight_B.MathFunction_l[i + 3] + tmp_4[3 * tmp_8 + i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.x3[3 * tmp_8 + 2] *
          CSE1_CV3_1Straight_B.MathFunction_l[i + 6] + tmp_4[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product_p[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_p[i] = tmp_4[i] *
        CSE1_CV3_1Straight_B.Integrator_n[0] + CSE1_CV3_1Straight_B.Product_p[i];
      CSE1_CV3_1Straight_B.Product_p[i] = tmp_4[i + 3] *
        CSE1_CV3_1Straight_B.Integrator_n[1] + CSE1_CV3_1Straight_B.Product_p[i];
      CSE1_CV3_1Straight_B.Product_p[i] = tmp_4[i + 6] *
        CSE1_CV3_1Straight_B.Integrator_n[2] + CSE1_CV3_1Straight_B.Product_p[i];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Reshape: '<S53>/3x3' incorporates:
       *  Constant: '<S53>/12'
       *  Constant: '<S53>/13'
       *  Constant: '<S53>/21'
       *  Constant: '<S53>/23'
       *  Constant: '<S53>/31'
       *  Constant: '<S53>/32'
       *  Constant: '<S7>/K_d_Surge'
       *  Constant: '<S7>/K_d_Sway'
       *  Constant: '<S7>/K_d_Yaw'
       */
      CSE1_CV3_1Straight_B.x3_g[0] = CSE1_CV3_1Straight_P.K_d_Surge_Value;
      CSE1_CV3_1Straight_B.x3_g[1] = CSE1_CV3_1Straight_P.u_Value_j;
      CSE1_CV3_1Straight_B.x3_g[2] = CSE1_CV3_1Straight_P.u_Value_n;
      CSE1_CV3_1Straight_B.x3_g[3] = CSE1_CV3_1Straight_P.u_Value_h;
      CSE1_CV3_1Straight_B.x3_g[4] = CSE1_CV3_1Straight_P.K_d_Sway_Value;
      CSE1_CV3_1Straight_B.x3_g[5] = CSE1_CV3_1Straight_P.u_Value_dk;
      CSE1_CV3_1Straight_B.x3_g[6] = CSE1_CV3_1Straight_P.u_Value_o;
      CSE1_CV3_1Straight_B.x3_g[7] = CSE1_CV3_1Straight_P.u_Value_h4;
      CSE1_CV3_1Straight_B.x3_g[8] = CSE1_CV3_1Straight_P.K_d_Yaw_Value;

      /* Gain: '<S50>/4' incorporates:
       *  Constant: '<S7>/kappa_1'
       */
      CSE1_CV3_1Straight_B.u_i = CSE1_CV3_1Straight_P._Gain *
        CSE1_CV3_1Straight_P.kappa_1_Value;

      /* Product: '<S50>/Divide' incorporates:
       *  Constant: '<S50>/1'
       */
      CSE1_CV3_1Straight_B.Divide = CSE1_CV3_1Straight_P._Value /
        CSE1_CV3_1Straight_B.u_i;

      /* Reshape: '<S55>/R(psi)' incorporates:
       *  Constant: '<S55>/12'
       *  Constant: '<S55>/13'
       *  Constant: '<S55>/21'
       *  Constant: '<S55>/23'
       *  Constant: '<S55>/31'
       *  Constant: '<S55>/32'
       *  Constant: '<S7>/K_p_Surge'
       *  Constant: '<S7>/K_p_Sway'
       *  Constant: '<S7>/K_p_Yaw'
       */
      CSE1_CV3_1Straight_B.Rpsi_n[0] = CSE1_CV3_1Straight_P.K_p_Surge_Value;
      CSE1_CV3_1Straight_B.Rpsi_n[1] = CSE1_CV3_1Straight_P.u_Value_hi;
      CSE1_CV3_1Straight_B.Rpsi_n[2] = CSE1_CV3_1Straight_P.u_Value_nb;
      CSE1_CV3_1Straight_B.Rpsi_n[3] = CSE1_CV3_1Straight_P.u_Value_e;
      CSE1_CV3_1Straight_B.Rpsi_n[4] = CSE1_CV3_1Straight_P.K_p_Sway_Value;
      CSE1_CV3_1Straight_B.Rpsi_n[5] = CSE1_CV3_1Straight_P.u_Value_e1;
      CSE1_CV3_1Straight_B.Rpsi_n[6] = CSE1_CV3_1Straight_P.u_Value_jo;
      CSE1_CV3_1Straight_B.Rpsi_n[7] = CSE1_CV3_1Straight_P.u_Value_k;
      CSE1_CV3_1Straight_B.Rpsi_n[8] = CSE1_CV3_1Straight_P.K_p_Yaw_Value;
      for (i = 0; i < 9; i++) {
        /* Sum: '<S50>/Add1' */
        CSE1_CV3_1Straight_B.Add1[i] = CSE1_CV3_1Straight_B.x3_g[i] +
          CSE1_CV3_1Straight_B.Divide;

        /* Product: '<S64>/Product' incorporates:
         *  Constant: '<S107>/Constant'
         *  Constant: '<S7>/kappa_1'
         */
        CSE1_CV3_1Straight_B.Product_n[i] = CSE1_CV3_1Straight_P.kappa_1_Value *
          CSE1_CV3_1Straight_P.Constant_Value_n4[i];

        /* Sum: '<S64>/Subtract' */
        CSE1_CV3_1Straight_B.Subtract[i] = CSE1_CV3_1Straight_B.Rpsi_n[i] -
          CSE1_CV3_1Straight_B.Product_n[i];
      }
    }

    /* Gain: '<S115>/Gain' */
    CSE1_CV3_1Straight_B.Gain_j = CSE1_CV3_1Straight_P.Gain_Gain_o *
      CSE1_CV3_1Straight_B.eta_yaw;

    /* Saturate: '<S113>/Saturation' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_j;
    CSE1_CV3_1Straight_B.Saturation_o = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation_LowerSat_c,
      CSE1_CV3_1Straight_P.Saturation_UpperSat_jx);

    /* Signum: '<S113>/Sign' */
    CSE1_CV3_1Straight_B.Sign_n = rt_SIGNd_snf(CSE1_CV3_1Straight_B.Saturation_o);

    /* Gain: '<S113>/Gain' */
    CSE1_CV3_1Straight_B.Gain_d = CSE1_CV3_1Straight_P.Gain_Gain_d *
      CSE1_CV3_1Straight_B.Sign_n;

    /* Sum: '<S113>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_p = CSE1_CV3_1Straight_B.Saturation_o +
      CSE1_CV3_1Straight_B.Gain_d;

    /* Math: '<S113>/Math Function' incorporates:
     *  Constant: '<S113>/Constant'
     */
    CSE1_CV3_1Straight_B.MathFunction_g = rt_rem_snf(CSE1_CV3_1Straight_B.Sum1_p,
      CSE1_CV3_1Straight_P.Constant_Value_gu);

    /* Sum: '<S113>/Sum' */
    CSE1_CV3_1Straight_B.Sum_n = CSE1_CV3_1Straight_B.MathFunction_g -
      CSE1_CV3_1Straight_B.Gain_d;

    /* Gain: '<S114>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_k = CSE1_CV3_1Straight_P.Gain1_Gain_e *
      CSE1_CV3_1Straight_B.Sum_n;

    /* Gain: '<S2>/q_x' */
    CSE1_CV3_1Straight_B.q_x = CSE1_CV3_1Straight_P.q_x_Gain *
      CSE1_CV3_1Straight_B.VectorConcatenate_dn[0];

    /* Gain: '<S2>/q_y' */
    CSE1_CV3_1Straight_B.q_y = CSE1_CV3_1Straight_P.q_y_Gain *
      CSE1_CV3_1Straight_B.VectorConcatenate_dn[1];

    /* Gain: '<S2>/psi_los' */
    CSE1_CV3_1Straight_B.psi_los = CSE1_CV3_1Straight_P.psi_los_Gain *
      CSE1_CV3_1Straight_B.VectorConcatenate_dn[2];

    /* Sum: '<S68>/Subtract' */
    CSE1_CV3_1Straight_B.Subtract_l[0] = CSE1_CV3_1Straight_B.eta_surge -
      CSE1_CV3_1Straight_B.q_x;
    CSE1_CV3_1Straight_B.Subtract_l[1] = CSE1_CV3_1Straight_B.eta_sway -
      CSE1_CV3_1Straight_B.q_y;
    CSE1_CV3_1Straight_B.Subtract_l[2] = CSE1_CV3_1Straight_B.Gain1_k -
      CSE1_CV3_1Straight_B.psi_los;

    /* Gain: '<S118>/Gain' */
    CSE1_CV3_1Straight_B.Gain_f = CSE1_CV3_1Straight_P.Gain_Gain_a *
      CSE1_CV3_1Straight_B.Subtract_l[2];

    /* Saturate: '<S116>/Saturation' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_f;
    CSE1_CV3_1Straight_B.Saturation_l = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation_LowerSat_p,
      CSE1_CV3_1Straight_P.Saturation_UpperSat_oh);

    /* Signum: '<S116>/Sign' */
    CSE1_CV3_1Straight_B.Sign_i = rt_SIGNd_snf(CSE1_CV3_1Straight_B.Saturation_l);

    /* Gain: '<S116>/Gain' */
    CSE1_CV3_1Straight_B.Gain_h = CSE1_CV3_1Straight_P.Gain_Gain_k *
      CSE1_CV3_1Straight_B.Sign_i;

    /* Sum: '<S116>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_jz = CSE1_CV3_1Straight_B.Saturation_l +
      CSE1_CV3_1Straight_B.Gain_h;

    /* Math: '<S116>/Math Function' incorporates:
     *  Constant: '<S116>/Constant'
     */
    CSE1_CV3_1Straight_B.MathFunction_a = rt_rem_snf
      (CSE1_CV3_1Straight_B.Sum1_jz, CSE1_CV3_1Straight_P.Constant_Value_a);

    /* Sum: '<S116>/Sum' */
    CSE1_CV3_1Straight_B.Sum_g = CSE1_CV3_1Straight_B.MathFunction_a -
      CSE1_CV3_1Straight_B.Gain_h;

    /* Gain: '<S117>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_l = CSE1_CV3_1Straight_P.Gain1_Gain_h *
      CSE1_CV3_1Straight_B.Sum_g;

    /* SignalConversion: '<S68>/TmpHiddenBufferAtProductInport2' */
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_e[0] =
      CSE1_CV3_1Straight_B.Subtract_l[0];
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_e[1] =
      CSE1_CV3_1Straight_B.Subtract_l[1];
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_e[2] =
      CSE1_CV3_1Straight_B.Gain1_l;

    /* Product: '<S68>/Product' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product_j[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_j[i] = CSE1_CV3_1Straight_B.MathFunction_l[i]
        * CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_e[0] +
        CSE1_CV3_1Straight_B.Product_j[i];
      CSE1_CV3_1Straight_B.Product_j[i] = CSE1_CV3_1Straight_B.MathFunction_l[i
        + 3] * CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_e[1] +
        CSE1_CV3_1Straight_B.Product_j[i];
      CSE1_CV3_1Straight_B.Product_j[i] = CSE1_CV3_1Straight_B.MathFunction_l[i
        + 6] * CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_e[2] +
        CSE1_CV3_1Straight_B.Product_j[i];
    }

    /* Product: '<S64>/Product1' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product1_b[i] = 0.0;
      CSE1_CV3_1Straight_B.Product1_b[i] = CSE1_CV3_1Straight_B.Subtract[i] *
        CSE1_CV3_1Straight_B.Product_j[0] + CSE1_CV3_1Straight_B.Product1_b[i];
      CSE1_CV3_1Straight_B.Product1_b[i] = CSE1_CV3_1Straight_B.Subtract[i + 3] *
        CSE1_CV3_1Straight_B.Product_j[1] + CSE1_CV3_1Straight_B.Product1_b[i];
      CSE1_CV3_1Straight_B.Product1_b[i] = CSE1_CV3_1Straight_B.Subtract[i + 6] *
        CSE1_CV3_1Straight_B.Product_j[2] + CSE1_CV3_1Straight_B.Product1_b[i];
    }

    /* SignalConversion: '<S70>/ConcatBufferAtVector ConcatenateIn1' */
    CSE1_CV3_1Straight_B.VectorConcatenate[0] = CSE1_CV3_1Straight_B.Product_dm
      [0];
    CSE1_CV3_1Straight_B.VectorConcatenate[1] = CSE1_CV3_1Straight_B.Product_dm
      [1];

    /* Product: '<S70>/Product' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_l[0] * CSE1_CV3_1Straight_B.Product_dm[0];
    tmp_0 += CSE1_CV3_1Straight_B.Gain_l[1] * CSE1_CV3_1Straight_B.Product_dm[1];
    CSE1_CV3_1Straight_B.VectorConcatenate[2] = tmp_0;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Constant: '<S76>/0_2x1' */
      CSE1_CV3_1Straight_B.VectorConcatenate_n[0] =
        CSE1_CV3_1Straight_P._2x1_Value[0];
      CSE1_CV3_1Straight_B.VectorConcatenate_n[1] =
        CSE1_CV3_1Straight_P._2x1_Value[1];
    }

    /* Product: '<S76>/Product' */
    CSE1_CV3_1Straight_B.VectorConcatenate_n[2] =
      CSE1_CV3_1Straight_B.Subtract_n * CSE1_CV3_1Straight_B.Subtract_g;

    /* Sum: '<S64>/Add' */
    CSE1_CV3_1Straight_B.Add[0] = CSE1_CV3_1Straight_B.VectorConcatenate[0] +
      CSE1_CV3_1Straight_B.VectorConcatenate_n[0];
    CSE1_CV3_1Straight_B.Add[1] = CSE1_CV3_1Straight_B.VectorConcatenate[1] +
      CSE1_CV3_1Straight_B.VectorConcatenate_n[1];
    CSE1_CV3_1Straight_B.Add[2] = CSE1_CV3_1Straight_B.VectorConcatenate[2] +
      CSE1_CV3_1Straight_B.VectorConcatenate_n[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S64>/Product2' */
      CSE1_CV3_1Straight_B.Product2_k[i] = 0.0;
      CSE1_CV3_1Straight_B.Product2_k[i] = CSE1_CV3_1Straight_B.MathFunction_l[i]
        * CSE1_CV3_1Straight_B.Add[0] + CSE1_CV3_1Straight_B.Product2_k[i];
      CSE1_CV3_1Straight_B.Product2_k[i] = CSE1_CV3_1Straight_B.MathFunction_l[i
        + 3] * CSE1_CV3_1Straight_B.Add[1] + CSE1_CV3_1Straight_B.Product2_k[i];
      CSE1_CV3_1Straight_B.Product2_k[i] = CSE1_CV3_1Straight_B.MathFunction_l[i
        + 6] * CSE1_CV3_1Straight_B.Add[2] + CSE1_CV3_1Straight_B.Product2_k[i];

      /* Sum: '<S64>/Sum' */
      CSE1_CV3_1Straight_B.Sum_og[i] = CSE1_CV3_1Straight_B.Product2_k[i] -
        CSE1_CV3_1Straight_B.Product1_b[i];

      /* Sum: '<S69>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_f[i] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[i] -
        CSE1_CV3_1Straight_B.Sum_og[i];
    }

    /* Product: '<S50>/Product1' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product1_a[i] = 0.0;
      CSE1_CV3_1Straight_B.Product1_a[i] = CSE1_CV3_1Straight_B.Add1[i] *
        CSE1_CV3_1Straight_B.Subtract_f[0] + CSE1_CV3_1Straight_B.Product1_a[i];
      CSE1_CV3_1Straight_B.Product1_a[i] = CSE1_CV3_1Straight_B.Add1[i + 3] *
        CSE1_CV3_1Straight_B.Subtract_f[1] + CSE1_CV3_1Straight_B.Product1_a[i];
      CSE1_CV3_1Straight_B.Product1_a[i] = CSE1_CV3_1Straight_B.Add1[i + 6] *
        CSE1_CV3_1Straight_B.Subtract_f[2] + CSE1_CV3_1Straight_B.Product1_a[i];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Gain: '<S80>/-X_u' incorporates:
       *  Constant: '<S80>/X_u'
       */
      CSE1_CV3_1Straight_B.X_u = CSE1_CV3_1Straight_P.X_u_Gain *
        CSE1_CV3_1Straight_P.X_u_Value;

      /* Gain: '<S80>/-Y_v' incorporates:
       *  Constant: '<S80>/Y_v'
       */
      CSE1_CV3_1Straight_B.Y_v = CSE1_CV3_1Straight_P.Y_v_Gain *
        CSE1_CV3_1Straight_P.Y_v_Value;

      /* Gain: '<S80>/-N_v' incorporates:
       *  Constant: '<S80>/N_v'
       */
      CSE1_CV3_1Straight_B.N_v = CSE1_CV3_1Straight_P.N_v_Gain *
        CSE1_CV3_1Straight_P.N_v_Value;

      /* Gain: '<S80>/-Y_vr' incorporates:
       *  Constant: '<S80>/Y_r'
       */
      CSE1_CV3_1Straight_B.Y_vr = CSE1_CV3_1Straight_P.Y_vr_Gain *
        CSE1_CV3_1Straight_P.Y_r_Value;

      /* Gain: '<S80>/-N_r' incorporates:
       *  Constant: '<S80>/N_r'
       */
      CSE1_CV3_1Straight_B.N_r = CSE1_CV3_1Straight_P.N_r_Gain *
        CSE1_CV3_1Straight_P.N_r_Value;

      /* Reshape: '<S80>/Linear Dampning matrix' incorporates:
       *  Constant: '<S80>/D_L_12'
       *  Constant: '<S80>/D_L_13'
       *  Constant: '<S80>/D_L_21'
       *  Constant: '<S80>/D_L_31'
       */
      CSE1_CV3_1Straight_B.LinearDampningmatrix[0] = CSE1_CV3_1Straight_B.X_u;
      CSE1_CV3_1Straight_B.LinearDampningmatrix[1] =
        CSE1_CV3_1Straight_P.D_L_21_Value;
      CSE1_CV3_1Straight_B.LinearDampningmatrix[2] =
        CSE1_CV3_1Straight_P.D_L_31_Value;
      CSE1_CV3_1Straight_B.LinearDampningmatrix[3] =
        CSE1_CV3_1Straight_P.D_L_12_Value;
      CSE1_CV3_1Straight_B.LinearDampningmatrix[4] = CSE1_CV3_1Straight_B.Y_v;
      CSE1_CV3_1Straight_B.LinearDampningmatrix[5] = CSE1_CV3_1Straight_B.N_v;
      CSE1_CV3_1Straight_B.LinearDampningmatrix[6] =
        CSE1_CV3_1Straight_P.D_L_13_Value;
      CSE1_CV3_1Straight_B.LinearDampningmatrix[7] = CSE1_CV3_1Straight_B.Y_vr;
      CSE1_CV3_1Straight_B.LinearDampningmatrix[8] = CSE1_CV3_1Straight_B.N_r;
    }

    /* Product: '<S50>/Product2' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product2_c[i] = 0.0;
      CSE1_CV3_1Straight_B.Product2_c[i] =
        CSE1_CV3_1Straight_B.LinearDampningmatrix[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[0] +
        CSE1_CV3_1Straight_B.Product2_c[i];
      CSE1_CV3_1Straight_B.Product2_c[i] =
        CSE1_CV3_1Straight_B.LinearDampningmatrix[i + 3] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[1] +
        CSE1_CV3_1Straight_B.Product2_c[i];
      CSE1_CV3_1Straight_B.Product2_c[i] =
        CSE1_CV3_1Straight_B.LinearDampningmatrix[i + 6] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[2] +
        CSE1_CV3_1Straight_B.Product2_c[i];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Sum: '<S56>/M_11' incorporates:
       *  Constant: '<S56>/X_udot'
       *  Constant: '<S56>/m'
       */
      CSE1_CV3_1Straight_B.M_11 = CSE1_CV3_1Straight_P.m_Value -
        CSE1_CV3_1Straight_P.X_udot_Value;

      /* Sum: '<S56>/M_22' incorporates:
       *  Constant: '<S56>/Y_vdot'
       *  Constant: '<S56>/m'
       */
      CSE1_CV3_1Straight_B.M_22 = CSE1_CV3_1Straight_P.m_Value -
        CSE1_CV3_1Straight_P.Y_vdot_Value;

      /* Product: '<S56>/m x_g' incorporates:
       *  Constant: '<S56>/m'
       *  Constant: '<S56>/x_g'
       */
      CSE1_CV3_1Straight_B.mx_g = CSE1_CV3_1Straight_P.m_Value *
        CSE1_CV3_1Straight_P.x_g_Value;

      /* Sum: '<S56>/M_32' incorporates:
       *  Constant: '<S56>/N_vdot'
       */
      CSE1_CV3_1Straight_B.M_32 = CSE1_CV3_1Straight_B.mx_g -
        CSE1_CV3_1Straight_P.N_vdot_Value;

      /* Sum: '<S56>/M_23' incorporates:
       *  Constant: '<S56>/Y_rdot'
       */
      CSE1_CV3_1Straight_B.M_23 = CSE1_CV3_1Straight_B.mx_g -
        CSE1_CV3_1Straight_P.Y_rdot_Value;

      /* Sum: '<S56>/M_33' incorporates:
       *  Constant: '<S56>/I_z'
       *  Constant: '<S56>/N_rdot'
       */
      CSE1_CV3_1Straight_B.M_33 = CSE1_CV3_1Straight_P.I_z_Value -
        CSE1_CV3_1Straight_P.N_rdot_Value;

      /* Reshape: '<S56>/3x3' incorporates:
       *  Constant: '<S56>/M_12'
       *  Constant: '<S56>/M_13'
       *  Constant: '<S56>/M_21'
       *  Constant: '<S56>/M_31'
       */
      CSE1_CV3_1Straight_B.x3_p[0] = CSE1_CV3_1Straight_B.M_11;
      CSE1_CV3_1Straight_B.x3_p[1] = CSE1_CV3_1Straight_P.M_21_Value;
      CSE1_CV3_1Straight_B.x3_p[2] = CSE1_CV3_1Straight_P.M_31_Value;
      CSE1_CV3_1Straight_B.x3_p[3] = CSE1_CV3_1Straight_P.M_12_Value;
      CSE1_CV3_1Straight_B.x3_p[4] = CSE1_CV3_1Straight_B.M_22;
      CSE1_CV3_1Straight_B.x3_p[5] = CSE1_CV3_1Straight_B.M_32;
      CSE1_CV3_1Straight_B.x3_p[6] = CSE1_CV3_1Straight_P.M_13_Value;
      CSE1_CV3_1Straight_B.x3_p[7] = CSE1_CV3_1Straight_B.M_23;
      CSE1_CV3_1Straight_B.x3_p[8] = CSE1_CV3_1Straight_B.M_33;
      for (i = 0; i < 9; i++) {
        /* Product: '<S67>/Product1' incorporates:
         *  Constant: '<S110>/Constant'
         *  Constant: '<S7>/kappa_1'
         */
        CSE1_CV3_1Straight_B.Product1_d[i] = CSE1_CV3_1Straight_P.kappa_1_Value *
          CSE1_CV3_1Straight_P.Constant_Value_f1[i];

        /* Sum: '<S67>/Subtract' */
        CSE1_CV3_1Straight_B.Subtract_k[i] = CSE1_CV3_1Straight_B.Rpsi_n[i] -
          CSE1_CV3_1Straight_B.Product1_d[i];
      }
    }

    /* Gain: '<S59>/S12' */
    CSE1_CV3_1Straight_B.S12 = CSE1_CV3_1Straight_P.S12_Gain *
      CSE1_CV3_1Straight_B.nu_yaw;

    /* Reshape: '<S59>/S(r)' incorporates:
     *  Constant: '<S59>/R31'
     *  Constant: '<S59>/S11'
     *  Constant: '<S59>/S13'
     *  Constant: '<S59>/S22'
     *  Constant: '<S59>/S23'
     *  Constant: '<S59>/S32'
     *  Constant: '<S59>/S33'
     */
    CSE1_CV3_1Straight_B.Sr[0] = CSE1_CV3_1Straight_P.S11_Value;
    CSE1_CV3_1Straight_B.Sr[1] = CSE1_CV3_1Straight_B.nu_yaw;
    CSE1_CV3_1Straight_B.Sr[2] = CSE1_CV3_1Straight_P.R31_Value_h;
    CSE1_CV3_1Straight_B.Sr[3] = CSE1_CV3_1Straight_B.S12;
    CSE1_CV3_1Straight_B.Sr[4] = CSE1_CV3_1Straight_P.S22_Value;
    CSE1_CV3_1Straight_B.Sr[5] = CSE1_CV3_1Straight_P.S32_Value;
    CSE1_CV3_1Straight_B.Sr[6] = CSE1_CV3_1Straight_P.S13_Value;
    CSE1_CV3_1Straight_B.Sr[7] = CSE1_CV3_1Straight_P.S23_Value;
    CSE1_CV3_1Straight_B.Sr[8] = CSE1_CV3_1Straight_P.S33_Value;

    /* Math: '<S60>/Math Function' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.MathFunction_k[3 * i] = CSE1_CV3_1Straight_B.Sr[i];
      CSE1_CV3_1Straight_B.MathFunction_k[1 + 3 * i] = CSE1_CV3_1Straight_B.Sr[i
        + 3];
      CSE1_CV3_1Straight_B.MathFunction_k[2 + 3 * i] = CSE1_CV3_1Straight_B.Sr[i
        + 6];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S67>/Product' */
      CSE1_CV3_1Straight_B.Product_fy[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_fy[i] = CSE1_CV3_1Straight_B.MathFunction_k[i]
        * CSE1_CV3_1Straight_B.Product_j[0] + CSE1_CV3_1Straight_B.Product_fy[i];
      CSE1_CV3_1Straight_B.Product_fy[i] = CSE1_CV3_1Straight_B.MathFunction_k[i
        + 3] * CSE1_CV3_1Straight_B.Product_j[1] +
        CSE1_CV3_1Straight_B.Product_fy[i];
      CSE1_CV3_1Straight_B.Product_fy[i] = CSE1_CV3_1Straight_B.MathFunction_k[i
        + 6] * CSE1_CV3_1Straight_B.Product_j[2] +
        CSE1_CV3_1Straight_B.Product_fy[i];

      /* Sum: '<S67>/Add' */
      CSE1_CV3_1Straight_B.Add_j[i] = CSE1_CV3_1Straight_B.Product_fy[i] +
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S67>/Product2' */
      CSE1_CV3_1Straight_B.Product2_d[i] = 0.0;
      CSE1_CV3_1Straight_B.Product2_d[i] = CSE1_CV3_1Straight_B.Subtract_k[i] *
        CSE1_CV3_1Straight_B.Add_j[0] + CSE1_CV3_1Straight_B.Product2_d[i];
      CSE1_CV3_1Straight_B.Product2_d[i] = CSE1_CV3_1Straight_B.Subtract_k[i + 3]
        * CSE1_CV3_1Straight_B.Add_j[1] + CSE1_CV3_1Straight_B.Product2_d[i];
      CSE1_CV3_1Straight_B.Product2_d[i] = CSE1_CV3_1Straight_B.Subtract_k[i + 6]
        * CSE1_CV3_1Straight_B.Add_j[2] + CSE1_CV3_1Straight_B.Product2_d[i];

      /* Sum: '<S67>/Add1' */
      CSE1_CV3_1Straight_B.Add1_o[i] = CSE1_CV3_1Straight_B.VectorConcatenate[i]
        + CSE1_CV3_1Straight_B.VectorConcatenate_n[i];
    }

    /* Product: '<S67>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_4[i + 3 * tmp_8] = 0.0;
        tmp_4[i + 3 * tmp_8] = tmp_4[3 * tmp_8 + i] +
          CSE1_CV3_1Straight_B.MathFunction_l[3 * tmp_8] *
          CSE1_CV3_1Straight_B.MathFunction_k[i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_l[3 * tmp_8 + 1]
          * CSE1_CV3_1Straight_B.MathFunction_k[i + 3] + tmp_4[3 * tmp_8 + i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_l[3 * tmp_8 + 2]
          * CSE1_CV3_1Straight_B.MathFunction_k[i + 6] + tmp_4[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product3[i] = 0.0;
      CSE1_CV3_1Straight_B.Product3[i] = tmp_4[i] * CSE1_CV3_1Straight_B.Add1_o
        [0] + CSE1_CV3_1Straight_B.Product3[i];
      CSE1_CV3_1Straight_B.Product3[i] = tmp_4[i + 3] *
        CSE1_CV3_1Straight_B.Add1_o[1] + CSE1_CV3_1Straight_B.Product3[i];
      CSE1_CV3_1Straight_B.Product3[i] = tmp_4[i + 6] *
        CSE1_CV3_1Straight_B.Add1_o[2] + CSE1_CV3_1Straight_B.Product3[i];
    }

    /* SignalConversion: '<S73>/ConcatBufferAtVector ConcatenateIn1' */
    CSE1_CV3_1Straight_B.VectorConcatenate_o[0] =
      CSE1_CV3_1Straight_B.Product_of[0];
    CSE1_CV3_1Straight_B.VectorConcatenate_o[1] =
      CSE1_CV3_1Straight_B.Product_of[1];

    /* Product: '<S73>/Product1' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_l[0] * CSE1_CV3_1Straight_B.Product_of[0];
    tmp_0 += CSE1_CV3_1Straight_B.Gain_l[1] * CSE1_CV3_1Straight_B.Product_of[1];
    CSE1_CV3_1Straight_B.VectorConcatenate_o[2] = tmp_0;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Constant: '<S79>/0_2x1' */
      CSE1_CV3_1Straight_B.VectorConcatenate_d[0] =
        CSE1_CV3_1Straight_P._2x1_Value_c[0];
      CSE1_CV3_1Straight_B.VectorConcatenate_d[1] =
        CSE1_CV3_1Straight_P._2x1_Value_c[1];
    }

    /* Product: '<S79>/Product1' */
    CSE1_CV3_1Straight_B.VectorConcatenate_d[2] =
      CSE1_CV3_1Straight_B.Subtract_n * CSE1_CV3_1Straight_B.Product_gd;

    /* Sum: '<S67>/Add2' */
    CSE1_CV3_1Straight_B.Add2[0] = CSE1_CV3_1Straight_B.VectorConcatenate_o[0] +
      CSE1_CV3_1Straight_B.VectorConcatenate_d[0];
    CSE1_CV3_1Straight_B.Add2[1] = CSE1_CV3_1Straight_B.VectorConcatenate_o[1] +
      CSE1_CV3_1Straight_B.VectorConcatenate_d[1];
    CSE1_CV3_1Straight_B.Add2[2] = CSE1_CV3_1Straight_B.VectorConcatenate_o[2] +
      CSE1_CV3_1Straight_B.VectorConcatenate_d[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S67>/Product4' */
      CSE1_CV3_1Straight_B.Product4[i] = 0.0;
      CSE1_CV3_1Straight_B.Product4[i] = CSE1_CV3_1Straight_B.MathFunction_l[i] *
        CSE1_CV3_1Straight_B.Add2[0] + CSE1_CV3_1Straight_B.Product4[i];
      CSE1_CV3_1Straight_B.Product4[i] = CSE1_CV3_1Straight_B.MathFunction_l[i +
        3] * CSE1_CV3_1Straight_B.Add2[1] + CSE1_CV3_1Straight_B.Product4[i];
      CSE1_CV3_1Straight_B.Product4[i] = CSE1_CV3_1Straight_B.MathFunction_l[i +
        6] * CSE1_CV3_1Straight_B.Add2[2] + CSE1_CV3_1Straight_B.Product4[i];

      /* Sum: '<S67>/Sum' */
      CSE1_CV3_1Straight_B.Sum_ok[i] = (CSE1_CV3_1Straight_B.Product3[i] -
        CSE1_CV3_1Straight_B.Product2_d[i]) + CSE1_CV3_1Straight_B.Product4[i];
    }

    /* Product: '<S50>/Product4' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product4_d[i] = 0.0;
      CSE1_CV3_1Straight_B.Product4_d[i] = CSE1_CV3_1Straight_B.x3_p[i] *
        CSE1_CV3_1Straight_B.Sum_ok[0] + CSE1_CV3_1Straight_B.Product4_d[i];
      CSE1_CV3_1Straight_B.Product4_d[i] = CSE1_CV3_1Straight_B.x3_p[i + 3] *
        CSE1_CV3_1Straight_B.Sum_ok[1] + CSE1_CV3_1Straight_B.Product4_d[i];
      CSE1_CV3_1Straight_B.Product4_d[i] = CSE1_CV3_1Straight_B.x3_p[i + 6] *
        CSE1_CV3_1Straight_B.Sum_ok[2] + CSE1_CV3_1Straight_B.Product4_d[i];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      for (i = 0; i < 9; i++) {
        /* Product: '<S65>/Product1' incorporates:
         *  Constant: '<S108>/Constant'
         *  Constant: '<S7>/kappa_1'
         */
        CSE1_CV3_1Straight_B.Product1_m[i] = CSE1_CV3_1Straight_P.kappa_1_Value *
          CSE1_CV3_1Straight_P.Constant_Value_p[i];

        /* Sum: '<S65>/Subtract' */
        CSE1_CV3_1Straight_B.Subtract_j[i] = CSE1_CV3_1Straight_B.Rpsi_n[i] -
          CSE1_CV3_1Straight_B.Product1_m[i];
      }
    }

    /* Product: '<S65>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_4[i + 3 * tmp_8] = 0.0;
        tmp_4[i + 3 * tmp_8] = tmp_4[3 * tmp_8 + i] +
          CSE1_CV3_1Straight_B.MathFunction_l[3 * tmp_8] *
          CSE1_CV3_1Straight_B.Subtract_j[i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_l[3 * tmp_8 + 1]
          * CSE1_CV3_1Straight_B.Subtract_j[i + 3] + tmp_4[3 * tmp_8 + i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_l[3 * tmp_8 + 2]
          * CSE1_CV3_1Straight_B.Subtract_j[i + 6] + tmp_4[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 2; tmp_8++) {
        CSE1_CV3_1Straight_B.Product3_e[i + 3 * tmp_8] = 0.0;
        CSE1_CV3_1Straight_B.Product3_e[i + 3 * tmp_8] =
          CSE1_CV3_1Straight_B.Product3_e[3 * tmp_8 + i] +
          CSE1_CV3_1Straight_B.MatrixConcatenate_oj[3 * tmp_8] * tmp_4[i];
        CSE1_CV3_1Straight_B.Product3_e[i + 3 * tmp_8] =
          CSE1_CV3_1Straight_B.MatrixConcatenate_oj[3 * tmp_8 + 1] * tmp_4[i + 3]
          + CSE1_CV3_1Straight_B.Product3_e[3 * tmp_8 + i];
        CSE1_CV3_1Straight_B.Product3_e[i + 3 * tmp_8] =
          CSE1_CV3_1Straight_B.MatrixConcatenate_oj[3 * tmp_8 + 2] * tmp_4[i + 6]
          + CSE1_CV3_1Straight_B.Product3_e[3 * tmp_8 + i];
      }
    }

    /* Math: '<S74>/Math Function' */
    CSE1_CV3_1Straight_B.MathFunction_gw[0] = CSE1_CV3_1Straight_B.Product_dm[0];
    CSE1_CV3_1Straight_B.MathFunction_gw[1] = CSE1_CV3_1Straight_B.Product_dm[1];

    /* Math: '<S75>/Math Function' */
    CSE1_CV3_1Straight_B.MathFunction_n[0] = CSE1_CV3_1Straight_B.Product_nq[0];
    CSE1_CV3_1Straight_B.MathFunction_n[1] = CSE1_CV3_1Straight_B.Product_nq[2];
    CSE1_CV3_1Straight_B.MathFunction_n[2] = CSE1_CV3_1Straight_B.Product_nq[1];
    CSE1_CV3_1Straight_B.MathFunction_n[3] = CSE1_CV3_1Straight_B.Product_nq[3];

    /* Product: '<S71>/Product' */
    CSE1_CV3_1Straight_B.Product_d[0] = 0.0;
    CSE1_CV3_1Straight_B.Product_d[0] = CSE1_CV3_1Straight_B.MathFunction_gw[0] *
      CSE1_CV3_1Straight_B.MathFunction_n[0] + CSE1_CV3_1Straight_B.Product_d[0];
    CSE1_CV3_1Straight_B.Product_d[0] = CSE1_CV3_1Straight_B.MathFunction_gw[1] *
      CSE1_CV3_1Straight_B.MathFunction_n[1] + CSE1_CV3_1Straight_B.Product_d[0];

    /* Product: '<S71>/Product1' */
    CSE1_CV3_1Straight_B.Product1_ad[0] = 0.0;
    CSE1_CV3_1Straight_B.Product1_ad[0] = CSE1_CV3_1Straight_B.Gain_l[0] *
      CSE1_CV3_1Straight_B.Product_d4[0] + CSE1_CV3_1Straight_B.Product1_ad[0];
    CSE1_CV3_1Straight_B.Product1_ad[0] = CSE1_CV3_1Straight_B.Gain_l[1] *
      CSE1_CV3_1Straight_B.Product_d4[1] + CSE1_CV3_1Straight_B.Product1_ad[0];

    /* Sum: '<S71>/Add' */
    CSE1_CV3_1Straight_B.Add_jn[0] = CSE1_CV3_1Straight_B.Product_d[0] +
      CSE1_CV3_1Straight_B.Product1_ad[0];

    /* Product: '<S71>/Product' */
    CSE1_CV3_1Straight_B.Product_d[1] = 0.0;
    CSE1_CV3_1Straight_B.Product_d[1] = CSE1_CV3_1Straight_B.MathFunction_gw[0] *
      CSE1_CV3_1Straight_B.MathFunction_n[2] + CSE1_CV3_1Straight_B.Product_d[1];
    CSE1_CV3_1Straight_B.Product_d[1] = CSE1_CV3_1Straight_B.MathFunction_gw[1] *
      CSE1_CV3_1Straight_B.MathFunction_n[3] + CSE1_CV3_1Straight_B.Product_d[1];

    /* Product: '<S71>/Product1' */
    CSE1_CV3_1Straight_B.Product1_ad[1] = 0.0;
    CSE1_CV3_1Straight_B.Product1_ad[1] = CSE1_CV3_1Straight_B.Gain_l[0] *
      CSE1_CV3_1Straight_B.Product_d4[2] + CSE1_CV3_1Straight_B.Product1_ad[1];
    CSE1_CV3_1Straight_B.Product1_ad[1] = CSE1_CV3_1Straight_B.Gain_l[1] *
      CSE1_CV3_1Straight_B.Product_d4[3] + CSE1_CV3_1Straight_B.Product1_ad[1];

    /* Sum: '<S71>/Add' */
    CSE1_CV3_1Straight_B.Add_jn[1] = CSE1_CV3_1Straight_B.Product_d[1] +
      CSE1_CV3_1Straight_B.Product1_ad[1];

    /* Concatenate: '<S71>/Matrix Concatenate' */
    CSE1_CV3_1Straight_B.MatrixConcatenate[0] = CSE1_CV3_1Straight_B.Product_d4
      [0];
    CSE1_CV3_1Straight_B.MatrixConcatenate[1] = CSE1_CV3_1Straight_B.Product_d4
      [1];
    CSE1_CV3_1Straight_B.MatrixConcatenate[3] = CSE1_CV3_1Straight_B.Product_d4
      [2];
    CSE1_CV3_1Straight_B.MatrixConcatenate[4] = CSE1_CV3_1Straight_B.Product_d4
      [3];
    CSE1_CV3_1Straight_B.MatrixConcatenate[2] = CSE1_CV3_1Straight_B.Add_jn[0];
    CSE1_CV3_1Straight_B.MatrixConcatenate[5] = CSE1_CV3_1Straight_B.Add_jn[1];

    /* Product: '<S77>/Product' */
    CSE1_CV3_1Straight_B.Product_i[0] = CSE1_CV3_1Straight_B.Product_gz[0] *
      CSE1_CV3_1Straight_B.Subtract_g;

    /* Product: '<S77>/Product1' */
    CSE1_CV3_1Straight_B.Product1_h[0] = CSE1_CV3_1Straight_B.Subtract_n *
      CSE1_CV3_1Straight_B.Sum_id[0];

    /* Sum: '<S77>/Add' */
    CSE1_CV3_1Straight_B.Add_o[0] = CSE1_CV3_1Straight_B.Product_i[0] +
      CSE1_CV3_1Straight_B.Product1_h[0];

    /* Product: '<S77>/Product' */
    CSE1_CV3_1Straight_B.Product_i[1] = CSE1_CV3_1Straight_B.Product_gz[1] *
      CSE1_CV3_1Straight_B.Subtract_g;

    /* Product: '<S77>/Product1' */
    CSE1_CV3_1Straight_B.Product1_h[1] = CSE1_CV3_1Straight_B.Subtract_n *
      CSE1_CV3_1Straight_B.Sum_id[1];

    /* Sum: '<S77>/Add' */
    CSE1_CV3_1Straight_B.Add_o[1] = CSE1_CV3_1Straight_B.Product_i[1] +
      CSE1_CV3_1Straight_B.Product1_h[1];

    /* Concatenate: '<S77>/Matrix Concatenate' incorporates:
     *  Constant: '<S77>/0_2x2'
     */
    CSE1_CV3_1Straight_B.MatrixConcatenate_l[0] =
      CSE1_CV3_1Straight_P._2x2_Value[0];
    CSE1_CV3_1Straight_B.MatrixConcatenate_l[1] =
      CSE1_CV3_1Straight_P._2x2_Value[1];
    CSE1_CV3_1Straight_B.MatrixConcatenate_l[3] =
      CSE1_CV3_1Straight_P._2x2_Value[2];
    CSE1_CV3_1Straight_B.MatrixConcatenate_l[4] =
      CSE1_CV3_1Straight_P._2x2_Value[3];
    CSE1_CV3_1Straight_B.MatrixConcatenate_l[2] = CSE1_CV3_1Straight_B.Add_o[0];
    CSE1_CV3_1Straight_B.MatrixConcatenate_l[5] = CSE1_CV3_1Straight_B.Add_o[1];

    /* Sum: '<S65>/Add2' */
    for (i = 0; i < 6; i++) {
      CSE1_CV3_1Straight_B.Add2_c[i] = CSE1_CV3_1Straight_B.MatrixConcatenate[i]
        + CSE1_CV3_1Straight_B.MatrixConcatenate_l[i];
    }

    /* Product: '<S65>/Product4' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 2; tmp_8++) {
        CSE1_CV3_1Straight_B.Product4_l[i + 3 * tmp_8] = 0.0;
        CSE1_CV3_1Straight_B.Product4_l[i + 3 * tmp_8] =
          CSE1_CV3_1Straight_B.Product4_l[3 * tmp_8 + i] +
          CSE1_CV3_1Straight_B.Add2_c[3 * tmp_8] *
          CSE1_CV3_1Straight_B.MathFunction_l[i];
        CSE1_CV3_1Straight_B.Product4_l[i + 3 * tmp_8] =
          CSE1_CV3_1Straight_B.Add2_c[3 * tmp_8 + 1] *
          CSE1_CV3_1Straight_B.MathFunction_l[i + 3] +
          CSE1_CV3_1Straight_B.Product4_l[3 * tmp_8 + i];
        CSE1_CV3_1Straight_B.Product4_l[i + 3 * tmp_8] =
          CSE1_CV3_1Straight_B.Add2_c[3 * tmp_8 + 2] *
          CSE1_CV3_1Straight_B.MathFunction_l[i + 6] +
          CSE1_CV3_1Straight_B.Product4_l[3 * tmp_8 + i];
      }
    }

    /* Sum: '<S65>/Add3' */
    for (i = 0; i < 6; i++) {
      CSE1_CV3_1Straight_B.Add3[i] = CSE1_CV3_1Straight_B.Product3_e[i] +
        CSE1_CV3_1Straight_B.Product4_l[i];
    }

    /* Integrator: '<S62>/Integrator2' */
    CSE1_CV3_1Straight_B.Integrator2[0] =
      CSE1_CV3_1Straight_X.Integrator2_CSTATE[0];

    /* Sum: '<S50>/Add2' */
    CSE1_CV3_1Straight_B.Add2_k[0] = CSE1_CV3_1Straight_B.Integrator2[0] +
      CSE1_CV3_1Straight_B.Product_dm[0];

    /* Integrator: '<S62>/Integrator2' */
    CSE1_CV3_1Straight_B.Integrator2[1] =
      CSE1_CV3_1Straight_X.Integrator2_CSTATE[1];

    /* Sum: '<S50>/Add2' */
    CSE1_CV3_1Straight_B.Add2_k[1] = CSE1_CV3_1Straight_B.Integrator2[1] +
      CSE1_CV3_1Straight_B.Product_dm[1];

    /* Product: '<S50>/Product5' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 2; tmp_8++) {
        tmp_5[i + 3 * tmp_8] = 0.0;
        tmp_5[i + 3 * tmp_8] = tmp_5[3 * tmp_8 + i] + CSE1_CV3_1Straight_B.Add3
          [3 * tmp_8] * CSE1_CV3_1Straight_B.x3_p[i];
        tmp_5[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.Add3[3 * tmp_8 + 1] *
          CSE1_CV3_1Straight_B.x3_p[i + 3] + tmp_5[3 * tmp_8 + i];
        tmp_5[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.Add3[3 * tmp_8 + 2] *
          CSE1_CV3_1Straight_B.x3_p[i + 6] + tmp_5[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product5[i] = 0.0;
      CSE1_CV3_1Straight_B.Product5[i] = tmp_5[i] * CSE1_CV3_1Straight_B.Add2_k
        [0] + CSE1_CV3_1Straight_B.Product5[i];
      CSE1_CV3_1Straight_B.Product5[i] = tmp_5[i + 3] *
        CSE1_CV3_1Straight_B.Add2_k[1] + CSE1_CV3_1Straight_B.Product5[i];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      for (i = 0; i < 9; i++) {
        /* Product: '<S66>/Product1' incorporates:
         *  Constant: '<S109>/Constant'
         *  Constant: '<S7>/kappa_1'
         */
        CSE1_CV3_1Straight_B.Product1_l[i] = CSE1_CV3_1Straight_P.kappa_1_Value *
          CSE1_CV3_1Straight_P.Constant_Value_fj[i];

        /* Sum: '<S66>/Subtract' */
        CSE1_CV3_1Straight_B.Subtract_fp[i] = CSE1_CV3_1Straight_B.Rpsi_n[i] -
          CSE1_CV3_1Straight_B.Product1_l[i];
      }
    }

    /* Product: '<S66>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_4[i + 3 * tmp_8] = 0.0;
        tmp_4[i + 3 * tmp_8] = tmp_4[3 * tmp_8 + i] +
          CSE1_CV3_1Straight_B.MathFunction_l[3 * tmp_8] *
          CSE1_CV3_1Straight_B.Subtract_fp[i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_l[3 * tmp_8 + 1]
          * CSE1_CV3_1Straight_B.Subtract_fp[i + 3] + tmp_4[3 * tmp_8 + i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_l[3 * tmp_8 + 2]
          * CSE1_CV3_1Straight_B.Subtract_fp[i + 6] + tmp_4[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product3_d[i] = 0.0;
      CSE1_CV3_1Straight_B.Product3_d[i] = tmp_4[i] *
        CSE1_CV3_1Straight_B.VectorConcatenate1[0] +
        CSE1_CV3_1Straight_B.Product3_d[i];
      CSE1_CV3_1Straight_B.Product3_d[i] = tmp_4[i + 3] *
        CSE1_CV3_1Straight_B.VectorConcatenate1[1] +
        CSE1_CV3_1Straight_B.Product3_d[i];
      CSE1_CV3_1Straight_B.Product3_d[i] = tmp_4[i + 6] *
        CSE1_CV3_1Straight_B.VectorConcatenate1[2] +
        CSE1_CV3_1Straight_B.Product3_d[i];
    }

    /* SignalConversion: '<S72>/ConcatBufferAtVector ConcatenateIn1' */
    CSE1_CV3_1Straight_B.VectorConcatenate_g[0] =
      CSE1_CV3_1Straight_B.Product_l0[0];
    CSE1_CV3_1Straight_B.VectorConcatenate_g[1] =
      CSE1_CV3_1Straight_B.Product_l0[1];

    /* Product: '<S72>/Product' */
    tmp_0 = CSE1_CV3_1Straight_B.Product_gz[0] *
      CSE1_CV3_1Straight_B.Product_dm[0];
    tmp_0 += CSE1_CV3_1Straight_B.Product_gz[1] *
      CSE1_CV3_1Straight_B.Product_dm[1];
    CSE1_CV3_1Straight_B.Product_o = tmp_0;

    /* Product: '<S72>/Product1' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_l[0] * CSE1_CV3_1Straight_B.Product_l0[0];
    tmp_0 += CSE1_CV3_1Straight_B.Gain_l[1] * CSE1_CV3_1Straight_B.Product_l0[1];
    CSE1_CV3_1Straight_B.Product1_i = tmp_0;

    /* Sum: '<S72>/Add' */
    CSE1_CV3_1Straight_B.VectorConcatenate_g[2] = CSE1_CV3_1Straight_B.Product_o
      + CSE1_CV3_1Straight_B.Product1_i;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Constant: '<S78>/0_2x1' */
      CSE1_CV3_1Straight_B.VectorConcatenate_e[0] =
        CSE1_CV3_1Straight_P._2x1_Value_o[0];
      CSE1_CV3_1Straight_B.VectorConcatenate_e[1] =
        CSE1_CV3_1Straight_P._2x1_Value_o[1];
    }

    /* Product: '<S78>/Product' */
    CSE1_CV3_1Straight_B.Product_a = CSE1_CV3_1Straight_B.Subtract1_g *
      CSE1_CV3_1Straight_B.Subtract_g;

    /* Product: '<S78>/Product1' */
    CSE1_CV3_1Straight_B.Product1_g = CSE1_CV3_1Straight_B.Subtract_n *
      CSE1_CV3_1Straight_B.Sum_oq;

    /* Sum: '<S78>/Add' */
    CSE1_CV3_1Straight_B.VectorConcatenate_e[2] = CSE1_CV3_1Straight_B.Product_a
      + CSE1_CV3_1Straight_B.Product1_g;

    /* Sum: '<S66>/Add2' */
    CSE1_CV3_1Straight_B.Add2_j[0] = CSE1_CV3_1Straight_B.VectorConcatenate_g[0]
      + CSE1_CV3_1Straight_B.VectorConcatenate_e[0];
    CSE1_CV3_1Straight_B.Add2_j[1] = CSE1_CV3_1Straight_B.VectorConcatenate_g[1]
      + CSE1_CV3_1Straight_B.VectorConcatenate_e[1];
    CSE1_CV3_1Straight_B.Add2_j[2] = CSE1_CV3_1Straight_B.VectorConcatenate_g[2]
      + CSE1_CV3_1Straight_B.VectorConcatenate_e[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S66>/Product4' */
      CSE1_CV3_1Straight_B.Product4_c[i] = 0.0;
      CSE1_CV3_1Straight_B.Product4_c[i] = CSE1_CV3_1Straight_B.MathFunction_l[i]
        * CSE1_CV3_1Straight_B.Add2_j[0] + CSE1_CV3_1Straight_B.Product4_c[i];
      CSE1_CV3_1Straight_B.Product4_c[i] = CSE1_CV3_1Straight_B.MathFunction_l[i
        + 3] * CSE1_CV3_1Straight_B.Add2_j[1] +
        CSE1_CV3_1Straight_B.Product4_c[i];
      CSE1_CV3_1Straight_B.Product4_c[i] = CSE1_CV3_1Straight_B.MathFunction_l[i
        + 6] * CSE1_CV3_1Straight_B.Add2_j[2] +
        CSE1_CV3_1Straight_B.Product4_c[i];

      /* Sum: '<S66>/Add3' */
      CSE1_CV3_1Straight_B.Add3_o[i] = CSE1_CV3_1Straight_B.Product3_d[i] +
        CSE1_CV3_1Straight_B.Product4_c[i];
    }

    for (i = 0; i < 3; i++) {
      tmp_6[i] = 0.0;
      tmp_0 = tmp_6[i];
      tmp_0 += CSE1_CV3_1Straight_B.x3_p[i] * CSE1_CV3_1Straight_B.Add3_o[0];
      tmp_6[i] = tmp_0;
      tmp_0 = tmp_6[i];
      tmp_0 += CSE1_CV3_1Straight_B.x3_p[i + 3] * CSE1_CV3_1Straight_B.Add3_o[1];
      tmp_6[i] = tmp_0;
      tmp_0 = tmp_6[i];
      tmp_0 += CSE1_CV3_1Straight_B.x3_p[i + 6] * CSE1_CV3_1Straight_B.Add3_o[2];
      tmp_6[i] = tmp_0;
      CSE1_CV3_1Straight_B.Product6[i] = tmp_6[i] *
        CSE1_CV3_1Straight_B.Subtract_g;

      /* Sum: '<S50>/Sum' */
      CSE1_CV3_1Straight_B.Sum_e[i] = ((((CSE1_CV3_1Straight_B.Product2_c[i] -
        CSE1_CV3_1Straight_B.Product_p[i]) - CSE1_CV3_1Straight_B.Product1_a[i])
        + CSE1_CV3_1Straight_B.Product4_d[i]) + CSE1_CV3_1Straight_B.Product5[i])
        + CSE1_CV3_1Straight_B.Product6[i];
    }

    /* Product: '<S82>/Product' */
    for (i = 0; i < 5; i++) {
      CSE1_CV3_1Straight_B.Product_h[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_h[i] = CSE1_CV3_1Straight_B.Pseudoinverse_o[i]
        * CSE1_CV3_1Straight_B.Sum_e[0] + CSE1_CV3_1Straight_B.Product_h[i];
      CSE1_CV3_1Straight_B.Product_h[i] = CSE1_CV3_1Straight_B.Pseudoinverse_o[i
        + 5] * CSE1_CV3_1Straight_B.Sum_e[1] + CSE1_CV3_1Straight_B.Product_h[i];
      CSE1_CV3_1Straight_B.Product_h[i] = CSE1_CV3_1Straight_B.Pseudoinverse_o[i
        + 10] * CSE1_CV3_1Straight_B.Sum_e[2] + CSE1_CV3_1Straight_B.Product_h[i];
    }

    /* RelationalOperator: '<S88>/Compare' incorporates:
     *  Constant: '<S88>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_ib = (CSE1_CV3_1Straight_B.Product_h[0] <
      CSE1_CV3_1Straight_P.Constant_Value_px);

    /* RelationalOperator: '<S90>/Compare' */
    CSE1_CV3_1Straight_B.Compare_ng = (CSE1_CV3_1Straight_B.Product_h[0] == 0.0);

    /* Gain: '<S83>/Gain' */
    CSE1_CV3_1Straight_B.Gain_fg = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_ps *
      CSE1_CV3_1Straight_B.Compare_ng);

    /* RelationalOperator: '<S89>/Compare' incorporates:
     *  Constant: '<S89>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_kb = (CSE1_CV3_1Straight_B.Product_h[0] >
      CSE1_CV3_1Straight_P.Constant_Value_hh);

    /* Gain: '<S83>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_aq = (uint16_T)
      (CSE1_CV3_1Straight_P.Gain1_Gain_id * CSE1_CV3_1Straight_B.Compare_kb);

    /* Sum: '<S83>/Sum' */
    CSE1_CV3_1Straight_B.Sum_b4 = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_ib << 6) + CSE1_CV3_1Straight_B.Gain_fg) +
       CSE1_CV3_1Straight_B.Gain1_aq);

    /* Lookup Block: '<S83>/f_1 < 0'
     * About '<S83>/f_1 < 0 :'
     * Lookup Block: '<S83>/f_1 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_10_p),
                         CSE1_CV3_1Straight_P.f_10_YData_d,
                         CSE1_CV3_1Straight_B.Product_h[0],
                         CSE1_CV3_1Straight_P.f_10_XData_d, 8U);

    /* Lookup Block: '<S83>/f_1 > 0'
     * About '<S83>/f_1 > 0 :'
     * Lookup Block: '<S83>/f_1 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_10_c),
                         CSE1_CV3_1Straight_P.f_10_YData_i,
                         CSE1_CV3_1Straight_B.Product_h[0],
                         CSE1_CV3_1Straight_P.f_10_XData_hd, 9U);

    /* MultiPortSwitch: '<S83>/Multiport Switch' incorporates:
     *  Constant: '<S83>/f_1 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_b4 >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_id = CSE1_CV3_1Straight_B.f_10_p;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_id =
        CSE1_CV3_1Straight_P.f_10_Value_h;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_id = CSE1_CV3_1Straight_B.f_10_c;
      break;
    }

    /* RelationalOperator: '<S91>/Compare' incorporates:
     *  Constant: '<S91>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_o2 = (CSE1_CV3_1Straight_B.Product_h[1] <
      CSE1_CV3_1Straight_P.Constant_Value_ee);

    /* RelationalOperator: '<S93>/Compare' */
    CSE1_CV3_1Straight_B.Compare_gy = (CSE1_CV3_1Straight_B.Product_h[1] == 0.0);

    /* Gain: '<S84>/Gain' */
    CSE1_CV3_1Straight_B.Gain_ay = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_pu *
      CSE1_CV3_1Straight_B.Compare_gy);

    /* RelationalOperator: '<S92>/Compare' incorporates:
     *  Constant: '<S92>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_ie = (CSE1_CV3_1Straight_B.Product_h[1] >
      CSE1_CV3_1Straight_P.Constant_Value_l);

    /* Gain: '<S84>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_kd = (uint16_T)
      (CSE1_CV3_1Straight_P.Gain1_Gain_j2 * CSE1_CV3_1Straight_B.Compare_ie);

    /* Sum: '<S84>/Sum' */
    CSE1_CV3_1Straight_B.Sum_cb = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_o2 << 6) + CSE1_CV3_1Straight_B.Gain_ay) +
       CSE1_CV3_1Straight_B.Gain1_kd);

    /* Lookup Block: '<S84>/f_2 < 0'
     * About '<S84>/f_2 < 0 :'
     * Lookup Block: '<S84>/f_2 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_20_f),
                         CSE1_CV3_1Straight_P.f_20_YData_k,
                         CSE1_CV3_1Straight_B.Product_h[1],
                         CSE1_CV3_1Straight_P.f_20_XData_f, 10U);

    /* Lookup Block: '<S84>/f_2 > 0'
     * About '<S84>/f_2 > 0 :'
     * Lookup Block: '<S84>/f_2 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_20_h),
                         CSE1_CV3_1Straight_P.f_20_YData_j,
                         CSE1_CV3_1Straight_B.Product_h[1],
                         CSE1_CV3_1Straight_P.f_20_XData_h, 9U);

    /* MultiPortSwitch: '<S84>/Multiport Switch' incorporates:
     *  Constant: '<S84>/f_2 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_cb >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_f = CSE1_CV3_1Straight_B.f_20_f;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_f = CSE1_CV3_1Straight_P.f_20_Value_g;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_f = CSE1_CV3_1Straight_B.f_20_h;
      break;
    }

    /* RelationalOperator: '<S94>/Compare' incorporates:
     *  Constant: '<S94>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_kt = (CSE1_CV3_1Straight_B.Product_h[2] <
      CSE1_CV3_1Straight_P.Constant_Value_bu);

    /* RelationalOperator: '<S96>/Compare' */
    CSE1_CV3_1Straight_B.Compare_nx = (CSE1_CV3_1Straight_B.Product_h[2] == 0.0);

    /* Gain: '<S85>/Gain' */
    CSE1_CV3_1Straight_B.Gain_ma = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_of *
      CSE1_CV3_1Straight_B.Compare_nx);

    /* RelationalOperator: '<S95>/Compare' incorporates:
     *  Constant: '<S95>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_m0 = (CSE1_CV3_1Straight_B.Product_h[2] >
      CSE1_CV3_1Straight_P.Constant_Value_op);

    /* Gain: '<S85>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_gs = (uint16_T)
      (CSE1_CV3_1Straight_P.Gain1_Gain_it * CSE1_CV3_1Straight_B.Compare_m0);

    /* Sum: '<S85>/Sum' */
    CSE1_CV3_1Straight_B.Sum_fv = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_kt << 6) + CSE1_CV3_1Straight_B.Gain_ma) +
       CSE1_CV3_1Straight_B.Gain1_gs);

    /* Lookup Block: '<S85>/f_3 < 0'
     * About '<S85>/f_3 < 0 :'
     * Lookup Block: '<S85>/f_3 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_30_k),
                         CSE1_CV3_1Straight_P.f_30_YData_e,
                         CSE1_CV3_1Straight_B.Product_h[2],
                         CSE1_CV3_1Straight_P.f_30_XData_f, 7U);

    /* Lookup Block: '<S85>/f_3 > 0'
     * About '<S85>/f_3 > 0 :'
     * Lookup Block: '<S85>/f_3 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_30_o),
                         CSE1_CV3_1Straight_P.f_30_YData_kz,
                         CSE1_CV3_1Straight_B.Product_h[2],
                         CSE1_CV3_1Straight_P.f_30_XData_b, 10U);

    /* MultiPortSwitch: '<S85>/Multiport Switch' incorporates:
     *  Constant: '<S85>/f_3 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_fv >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_ga = CSE1_CV3_1Straight_B.f_30_k;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_ga =
        CSE1_CV3_1Straight_P.f_30_Value_c;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_ga = CSE1_CV3_1Straight_B.f_30_o;
      break;
    }

    /* RelationalOperator: '<S97>/Compare' incorporates:
     *  Constant: '<S97>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_idx = (CSE1_CV3_1Straight_B.Product_h[3] <
      CSE1_CV3_1Straight_P.Constant_Value_fv);

    /* RelationalOperator: '<S99>/Compare' */
    CSE1_CV3_1Straight_B.Compare_af = (CSE1_CV3_1Straight_B.Product_h[3] == 0.0);

    /* Gain: '<S86>/Gain' */
    CSE1_CV3_1Straight_B.Gain_ke = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_jf *
      CSE1_CV3_1Straight_B.Compare_af);

    /* RelationalOperator: '<S98>/Compare' incorporates:
     *  Constant: '<S98>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_f = (CSE1_CV3_1Straight_B.Product_h[3] >
      CSE1_CV3_1Straight_P.Constant_Value_ju);

    /* Gain: '<S86>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_e = (uint16_T)(CSE1_CV3_1Straight_P.Gain1_Gain_kr
      * CSE1_CV3_1Straight_B.Compare_f);

    /* Sum: '<S86>/Sum' */
    CSE1_CV3_1Straight_B.Sum_fx = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_idx << 6) + CSE1_CV3_1Straight_B.Gain_ke)
       + CSE1_CV3_1Straight_B.Gain1_e);

    /* Lookup Block: '<S86>/f_4 < 0'
     * About '<S86>/f_4 < 0 :'
     * Lookup Block: '<S86>/f_4 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_40_f),
                         CSE1_CV3_1Straight_P.f_40_YData_d2,
                         CSE1_CV3_1Straight_B.Product_h[3],
                         CSE1_CV3_1Straight_P.f_40_XData_nx, 9U);

    /* Lookup Block: '<S86>/f_4 > 0'
     * About '<S86>/f_4 > 0 :'
     * Lookup Block: '<S86>/f_4 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_40_cs),
                         CSE1_CV3_1Straight_P.f_40_YData_de,
                         CSE1_CV3_1Straight_B.Product_h[3],
                         CSE1_CV3_1Straight_P.f_40_XData_ne, 6U);

    /* MultiPortSwitch: '<S86>/Multiport Switch' incorporates:
     *  Constant: '<S86>/f_4 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_fx >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_me = CSE1_CV3_1Straight_B.f_40_f;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_me =
        CSE1_CV3_1Straight_P.f_40_Value_a;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_me = CSE1_CV3_1Straight_B.f_40_cs;
      break;
    }

    /* RelationalOperator: '<S100>/Compare' incorporates:
     *  Constant: '<S100>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_oe = (CSE1_CV3_1Straight_B.Product_h[4] <
      CSE1_CV3_1Straight_P.Constant_Value_mf);

    /* RelationalOperator: '<S102>/Compare' */
    CSE1_CV3_1Straight_B.Compare_en = (CSE1_CV3_1Straight_B.Product_h[4] == 0.0);

    /* Gain: '<S87>/Gain' */
    CSE1_CV3_1Straight_B.Gain_fo = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_eb *
      CSE1_CV3_1Straight_B.Compare_en);

    /* RelationalOperator: '<S101>/Compare' incorporates:
     *  Constant: '<S101>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_lm = (CSE1_CV3_1Straight_B.Product_h[4] >
      CSE1_CV3_1Straight_P.Constant_Value_edn);

    /* Gain: '<S87>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_nv = (uint16_T)
      (CSE1_CV3_1Straight_P.Gain1_Gain_pn * CSE1_CV3_1Straight_B.Compare_lm);

    /* Sum: '<S87>/Sum' */
    CSE1_CV3_1Straight_B.Sum_ot = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_oe << 6) + CSE1_CV3_1Straight_B.Gain_fo) +
       CSE1_CV3_1Straight_B.Gain1_nv);

    /* Lookup Block: '<S87>/f_5 < 0'
     * About '<S87>/f_5 < 0 :'
     * Lookup Block: '<S87>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_50_f),
                         CSE1_CV3_1Straight_P.f_50_YData_a,
                         CSE1_CV3_1Straight_B.Product_h[4],
                         CSE1_CV3_1Straight_P.f_50_XData_o, 2U);

    /* Lookup Block: '<S87>/f_5 > 0'
     * About '<S87>/f_5 > 0 :'
     * Lookup Block: '<S87>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_50_pk),
                         CSE1_CV3_1Straight_P.f_50_YData_fx,
                         CSE1_CV3_1Straight_B.Product_h[4],
                         CSE1_CV3_1Straight_P.f_50_XData_f, 2U);

    /* MultiPortSwitch: '<S87>/Multiport Switch' incorporates:
     *  Constant: '<S87>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_ot >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_bl = CSE1_CV3_1Straight_B.f_50_f;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_bl =
        CSE1_CV3_1Straight_P.f_50_Value_f;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_bl = CSE1_CV3_1Straight_B.f_50_pk;
      break;
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Gain: '<S185>/-l_x1' incorporates:
       *  Constant: '<S185>/l_x1'
       */
      CSE1_CV3_1Straight_B.l_x1_d = CSE1_CV3_1Straight_P.l_x1_Gain_d *
        CSE1_CV3_1Straight_P.l_x1_Value_ex;

      /* Gain: '<S185>/-l_y2' incorporates:
       *  Constant: '<S185>/l_y2'
       */
      CSE1_CV3_1Straight_B.l_y2_j = CSE1_CV3_1Straight_P.l_y2_Gain_ag *
        CSE1_CV3_1Straight_P.l_y2_Value_l;

      /* Gain: '<S185>/-l_x2' incorporates:
       *  Constant: '<S185>/l_x2'
       */
      CSE1_CV3_1Straight_B.l_x2_l = CSE1_CV3_1Straight_P.l_x2_Gain_i *
        CSE1_CV3_1Straight_P.l_x2_Value_f;

      /* Reshape: '<S185>/3x5' incorporates:
       *  Constant: '<S185>/T_e11'
       *  Constant: '<S185>/T_e12'
       *  Constant: '<S185>/T_e13'
       *  Constant: '<S185>/T_e14'
       *  Constant: '<S185>/T_e15'
       *  Constant: '<S185>/T_e21'
       *  Constant: '<S185>/T_e22'
       *  Constant: '<S185>/T_e23'
       *  Constant: '<S185>/T_e24'
       *  Constant: '<S185>/T_e25'
       *  Constant: '<S185>/l_x3'
       *  Constant: '<S185>/l_y1'
       */
      CSE1_CV3_1Straight_B.x5_ib[0] = CSE1_CV3_1Straight_P.T_e11_Value_o;
      CSE1_CV3_1Straight_B.x5_ib[1] = CSE1_CV3_1Straight_P.T_e21_Value_k;
      CSE1_CV3_1Straight_B.x5_ib[2] = CSE1_CV3_1Straight_P.l_y1_Value_j;
      CSE1_CV3_1Straight_B.x5_ib[3] = CSE1_CV3_1Straight_P.T_e12_Value_a;
      CSE1_CV3_1Straight_B.x5_ib[4] = CSE1_CV3_1Straight_P.T_e22_Value_m;
      CSE1_CV3_1Straight_B.x5_ib[5] = CSE1_CV3_1Straight_B.l_x1_d;
      CSE1_CV3_1Straight_B.x5_ib[6] = CSE1_CV3_1Straight_P.T_e13_Value_o;
      CSE1_CV3_1Straight_B.x5_ib[7] = CSE1_CV3_1Straight_P.T_e23_Value_i;
      CSE1_CV3_1Straight_B.x5_ib[8] = CSE1_CV3_1Straight_B.l_y2_j;
      CSE1_CV3_1Straight_B.x5_ib[9] = CSE1_CV3_1Straight_P.T_e14_Value_e;
      CSE1_CV3_1Straight_B.x5_ib[10] = CSE1_CV3_1Straight_P.T_e24_Value_d;
      CSE1_CV3_1Straight_B.x5_ib[11] = CSE1_CV3_1Straight_B.l_x2_l;
      CSE1_CV3_1Straight_B.x5_ib[12] = CSE1_CV3_1Straight_P.T_e15_Value_c;
      CSE1_CV3_1Straight_B.x5_ib[13] = CSE1_CV3_1Straight_P.T_e25_Value_bl;
      CSE1_CV3_1Straight_B.x5_ib[14] = CSE1_CV3_1Straight_P.l_x3_Value_d;

      /* S-Function (sdsppinv): '<S164>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&CSE1_CV3_1Straight_DWork.Pseudoinverse_X[0]), (void *)
             (&CSE1_CV3_1Straight_B.x5_ib[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&CSE1_CV3_1Straight_DWork.Pseudoinverse_X[0], 3, 5,
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_S[0],
                      &CSE1_CV3_1Straight_DWork.Inverse_DWORK3[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_WORK[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_U[0],
                      &CSE1_CV3_1Straight_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&CSE1_CV3_1Straight_DWork.Pseudoinverse_S[0],
          &CSE1_CV3_1Straight_DWork.Pseudoinverse_U[0],
          &CSE1_CV3_1Straight_DWork.Pseudoinverse_V[0],
          &CSE1_CV3_1Straight_B.Pseudoinverse_f[0], (const int32_T)3, (const
          int32_T)5);
      }
    }

    /* Fcn: '<S132>/R11' */
    CSE1_CV3_1Straight_B.R11_j = cos(CSE1_CV3_1Straight_B.eta_yaw);

    /* Fcn: '<S132>/R21' */
    CSE1_CV3_1Straight_B.R21_b = sin(CSE1_CV3_1Straight_B.eta_yaw);

    /* Fcn: '<S132>/R12' */
    CSE1_CV3_1Straight_B.R12_c = -1.0 * sin(CSE1_CV3_1Straight_B.eta_yaw);

    /* Fcn: '<S132>/R22' */
    CSE1_CV3_1Straight_B.R22_d = cos(CSE1_CV3_1Straight_B.eta_yaw);

    /* Reshape: '<S132>/R(psi)' incorporates:
     *  Constant: '<S132>/R13'
     *  Constant: '<S132>/R23'
     *  Constant: '<S132>/R31'
     *  Constant: '<S132>/R32'
     *  Constant: '<S132>/R33'
     */
    CSE1_CV3_1Straight_B.Rpsi_p[0] = CSE1_CV3_1Straight_B.R11_j;
    CSE1_CV3_1Straight_B.Rpsi_p[1] = CSE1_CV3_1Straight_B.R21_b;
    CSE1_CV3_1Straight_B.Rpsi_p[2] = CSE1_CV3_1Straight_P.R31_Value_e;
    CSE1_CV3_1Straight_B.Rpsi_p[3] = CSE1_CV3_1Straight_B.R12_c;
    CSE1_CV3_1Straight_B.Rpsi_p[4] = CSE1_CV3_1Straight_B.R22_d;
    CSE1_CV3_1Straight_B.Rpsi_p[5] = CSE1_CV3_1Straight_P.R32_Value_a;
    CSE1_CV3_1Straight_B.Rpsi_p[6] = CSE1_CV3_1Straight_P.R13_Value_h;
    CSE1_CV3_1Straight_B.Rpsi_p[7] = CSE1_CV3_1Straight_P.R23_Value_a;
    CSE1_CV3_1Straight_B.Rpsi_p[8] = CSE1_CV3_1Straight_P.R33_Value_e;

    /* Math: '<S133>/Math Function' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.MathFunction_i[3 * i] = CSE1_CV3_1Straight_B.Rpsi_p[i];
      CSE1_CV3_1Straight_B.MathFunction_i[1 + 3 * i] =
        CSE1_CV3_1Straight_B.Rpsi_p[i + 3];
      CSE1_CV3_1Straight_B.MathFunction_i[2 + 3 * i] =
        CSE1_CV3_1Straight_B.Rpsi_p[i + 6];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Reshape: '<S131>/R(psi)' incorporates:
       *  Constant: '<S131>/12'
       *  Constant: '<S131>/13'
       *  Constant: '<S131>/21'
       *  Constant: '<S131>/23'
       *  Constant: '<S131>/31'
       *  Constant: '<S131>/32'
       *  Constant: '<S9>/K_p_Surge'
       *  Constant: '<S9>/K_p_Sway'
       *  Constant: '<S9>/K_p_Yaw'
       */
      CSE1_CV3_1Straight_B.Rpsi_l[0] = CSE1_CV3_1Straight_P.K_p_Surge_Value_c;
      CSE1_CV3_1Straight_B.Rpsi_l[1] = CSE1_CV3_1Straight_P.u_Value_ea;
      CSE1_CV3_1Straight_B.Rpsi_l[2] = CSE1_CV3_1Straight_P.u_Value_am;
      CSE1_CV3_1Straight_B.Rpsi_l[3] = CSE1_CV3_1Straight_P.u_Value_dp;
      CSE1_CV3_1Straight_B.Rpsi_l[4] = CSE1_CV3_1Straight_P.K_p_Sway_Value_o;
      CSE1_CV3_1Straight_B.Rpsi_l[5] = CSE1_CV3_1Straight_P.u_Value_i;
      CSE1_CV3_1Straight_B.Rpsi_l[6] = CSE1_CV3_1Straight_P.u_Value_md;
      CSE1_CV3_1Straight_B.Rpsi_l[7] = CSE1_CV3_1Straight_P.u_Value_ib;
      CSE1_CV3_1Straight_B.Rpsi_l[8] = CSE1_CV3_1Straight_P.K_p_Yaw_Value_j;
    }

    /* Gain: '<S159>/Gain' */
    CSE1_CV3_1Straight_B.Gain_jl = CSE1_CV3_1Straight_P.Gain_Gain_j *
      CSE1_CV3_1Straight_B.eta_yaw;

    /* Saturate: '<S157>/Saturation' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_jl;
    CSE1_CV3_1Straight_B.Saturation_pv = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation_LowerSat_e,
      CSE1_CV3_1Straight_P.Saturation_UpperSat_g);

    /* Signum: '<S157>/Sign' */
    CSE1_CV3_1Straight_B.Sign_mi = rt_SIGNd_snf
      (CSE1_CV3_1Straight_B.Saturation_pv);

    /* Gain: '<S157>/Gain' */
    CSE1_CV3_1Straight_B.Gain_b = CSE1_CV3_1Straight_P.Gain_Gain_kr *
      CSE1_CV3_1Straight_B.Sign_mi;

    /* Sum: '<S157>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_n = CSE1_CV3_1Straight_B.Saturation_pv +
      CSE1_CV3_1Straight_B.Gain_b;

    /* Math: '<S157>/Math Function' incorporates:
     *  Constant: '<S157>/Constant'
     */
    CSE1_CV3_1Straight_B.MathFunction_gi = rt_rem_snf
      (CSE1_CV3_1Straight_B.Sum1_n, CSE1_CV3_1Straight_P.Constant_Value_pw);

    /* Sum: '<S157>/Sum' */
    CSE1_CV3_1Straight_B.Sum_c = CSE1_CV3_1Straight_B.MathFunction_gi -
      CSE1_CV3_1Straight_B.Gain_b;

    /* Gain: '<S158>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_a = CSE1_CV3_1Straight_P.Gain1_Gain_j *
      CSE1_CV3_1Straight_B.Sum_c;

    /* Sum: '<S126>/Subtract' */
    CSE1_CV3_1Straight_B.Subtract_d[0] = CSE1_CV3_1Straight_B.eta_surge -
      CSE1_CV3_1Straight_B.q_x;
    CSE1_CV3_1Straight_B.Subtract_d[1] = CSE1_CV3_1Straight_B.eta_sway -
      CSE1_CV3_1Straight_B.q_y;
    CSE1_CV3_1Straight_B.Subtract_d[2] = CSE1_CV3_1Straight_B.Gain1_a -
      CSE1_CV3_1Straight_B.psi_los;

    /* Gain: '<S162>/Gain' */
    CSE1_CV3_1Straight_B.Gain_f4 = CSE1_CV3_1Straight_P.Gain_Gain_ou *
      CSE1_CV3_1Straight_B.Subtract_d[2];

    /* Saturate: '<S160>/Saturation' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_f4;
    CSE1_CV3_1Straight_B.Saturation_c0 = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation_LowerSat_hs,
      CSE1_CV3_1Straight_P.Saturation_UpperSat_pu);

    /* Signum: '<S160>/Sign' */
    CSE1_CV3_1Straight_B.Sign_i4 = rt_SIGNd_snf
      (CSE1_CV3_1Straight_B.Saturation_c0);

    /* Gain: '<S160>/Gain' */
    CSE1_CV3_1Straight_B.Gain_i = CSE1_CV3_1Straight_P.Gain_Gain_az *
      CSE1_CV3_1Straight_B.Sign_i4;

    /* Sum: '<S160>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_c = CSE1_CV3_1Straight_B.Saturation_c0 +
      CSE1_CV3_1Straight_B.Gain_i;

    /* Math: '<S160>/Math Function' incorporates:
     *  Constant: '<S160>/Constant'
     */
    CSE1_CV3_1Straight_B.MathFunction_li = rt_rem_snf
      (CSE1_CV3_1Straight_B.Sum1_c, CSE1_CV3_1Straight_P.Constant_Value_b4);

    /* Sum: '<S160>/Sum' */
    CSE1_CV3_1Straight_B.Sum_o5 = CSE1_CV3_1Straight_B.MathFunction_li -
      CSE1_CV3_1Straight_B.Gain_i;

    /* Gain: '<S161>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_f = CSE1_CV3_1Straight_P.Gain1_Gain_i *
      CSE1_CV3_1Straight_B.Sum_o5;

    /* SignalConversion: '<S152>/TmpHiddenBufferAtProductInport3' */
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport3[0] =
      CSE1_CV3_1Straight_B.Subtract_d[0];
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport3[1] =
      CSE1_CV3_1Straight_B.Subtract_d[1];
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport3[2] =
      CSE1_CV3_1Straight_B.Gain1_f;

    /* Product: '<S152>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_4[i + 3 * tmp_8] = 0.0;
        tmp_4[i + 3 * tmp_8] = tmp_4[3 * tmp_8 + i] +
          CSE1_CV3_1Straight_B.Rpsi_l[3 * tmp_8] *
          CSE1_CV3_1Straight_B.MathFunction_i[i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.Rpsi_l[3 * tmp_8 + 1] *
          CSE1_CV3_1Straight_B.MathFunction_i[i + 3] + tmp_4[3 * tmp_8 + i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.Rpsi_l[3 * tmp_8 + 2] *
          CSE1_CV3_1Straight_B.MathFunction_i[i + 6] + tmp_4[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product_le[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_le[i] = tmp_4[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport3[0] +
        CSE1_CV3_1Straight_B.Product_le[i];
      CSE1_CV3_1Straight_B.Product_le[i] = tmp_4[i + 3] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport3[1] +
        CSE1_CV3_1Straight_B.Product_le[i];
      CSE1_CV3_1Straight_B.Product_le[i] = tmp_4[i + 6] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport3[2] +
        CSE1_CV3_1Straight_B.Product_le[i];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Reshape: '<S130>/R(psi)' incorporates:
       *  Constant: '<S130>/12'
       *  Constant: '<S130>/13'
       *  Constant: '<S130>/21'
       *  Constant: '<S130>/23'
       *  Constant: '<S130>/31'
       *  Constant: '<S130>/32'
       *  Constant: '<S9>/K_i_Surge'
       *  Constant: '<S9>/K_i_Sway'
       *  Constant: '<S9>/K_i_Yaw'
       */
      CSE1_CV3_1Straight_B.Rpsi_i[0] = CSE1_CV3_1Straight_P.K_i_Surge_Value_f;
      CSE1_CV3_1Straight_B.Rpsi_i[1] = CSE1_CV3_1Straight_P.u_Value_ce;
      CSE1_CV3_1Straight_B.Rpsi_i[2] = CSE1_CV3_1Straight_P.u_Value_jf;
      CSE1_CV3_1Straight_B.Rpsi_i[3] = CSE1_CV3_1Straight_P.u_Value_g;
      CSE1_CV3_1Straight_B.Rpsi_i[4] = CSE1_CV3_1Straight_P.K_i_Sway_Value_m;
      CSE1_CV3_1Straight_B.Rpsi_i[5] = CSE1_CV3_1Straight_P.u_Value_aa;
      CSE1_CV3_1Straight_B.Rpsi_i[6] = CSE1_CV3_1Straight_P.u_Value_mu;
      CSE1_CV3_1Straight_B.Rpsi_i[7] = CSE1_CV3_1Straight_P.u_Value_b;
      CSE1_CV3_1Straight_B.Rpsi_i[8] = CSE1_CV3_1Straight_P.K_i_Yaw_Value_c;
    }

    /* Integrator: '<S9>/zeta' */
    CSE1_CV3_1Straight_B.zeta[0] = CSE1_CV3_1Straight_X.zeta_CSTATE[0];
    CSE1_CV3_1Straight_B.zeta[1] = CSE1_CV3_1Straight_X.zeta_CSTATE[1];
    CSE1_CV3_1Straight_B.zeta[2] = CSE1_CV3_1Straight_X.zeta_CSTATE[2];

    /* Product: '<S152>/Product1' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_4[i + 3 * tmp_8] = 0.0;
        tmp_4[i + 3 * tmp_8] = tmp_4[3 * tmp_8 + i] +
          CSE1_CV3_1Straight_B.Rpsi_i[3 * tmp_8] *
          CSE1_CV3_1Straight_B.MathFunction_i[i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.Rpsi_i[3 * tmp_8 + 1] *
          CSE1_CV3_1Straight_B.MathFunction_i[i + 3] + tmp_4[3 * tmp_8 + i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.Rpsi_i[3 * tmp_8 + 2] *
          CSE1_CV3_1Straight_B.MathFunction_i[i + 6] + tmp_4[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product1_o[i] = 0.0;
      CSE1_CV3_1Straight_B.Product1_o[i] = tmp_4[i] * CSE1_CV3_1Straight_B.zeta
        [0] + CSE1_CV3_1Straight_B.Product1_o[i];
      CSE1_CV3_1Straight_B.Product1_o[i] = tmp_4[i + 3] *
        CSE1_CV3_1Straight_B.zeta[1] + CSE1_CV3_1Straight_B.Product1_o[i];
      CSE1_CV3_1Straight_B.Product1_o[i] = tmp_4[i + 6] *
        CSE1_CV3_1Straight_B.zeta[2] + CSE1_CV3_1Straight_B.Product1_o[i];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Reshape: '<S129>/R(psi)' incorporates:
       *  Constant: '<S129>/12'
       *  Constant: '<S129>/13'
       *  Constant: '<S129>/21'
       *  Constant: '<S129>/23'
       *  Constant: '<S129>/31'
       *  Constant: '<S129>/32'
       *  Constant: '<S9>/K_d_Surge'
       *  Constant: '<S9>/K_d_Sway'
       *  Constant: '<S9>/K_d_Yaw'
       */
      CSE1_CV3_1Straight_B.Rpsi_k[0] = CSE1_CV3_1Straight_P.K_d_Surge_Value_o;
      CSE1_CV3_1Straight_B.Rpsi_k[1] = CSE1_CV3_1Straight_P.u_Value_bk;
      CSE1_CV3_1Straight_B.Rpsi_k[2] = CSE1_CV3_1Straight_P.u_Value_bh;
      CSE1_CV3_1Straight_B.Rpsi_k[3] = CSE1_CV3_1Straight_P.u_Value_p;
      CSE1_CV3_1Straight_B.Rpsi_k[4] = CSE1_CV3_1Straight_P.K_d_Sway_Value_l;
      CSE1_CV3_1Straight_B.Rpsi_k[5] = CSE1_CV3_1Straight_P.u_Value_g0;
      CSE1_CV3_1Straight_B.Rpsi_k[6] = CSE1_CV3_1Straight_P.u_Value_ew;
      CSE1_CV3_1Straight_B.Rpsi_k[7] = CSE1_CV3_1Straight_P.u_Value_bc;
      CSE1_CV3_1Straight_B.Rpsi_k[8] = CSE1_CV3_1Straight_P.K_d_Yaw_Value_f;
    }

    /* SignalConversion: '<S139>/ConcatBufferAtVector ConcatenateIn1' */
    CSE1_CV3_1Straight_B.VectorConcatenate_es[0] =
      CSE1_CV3_1Straight_B.Product_dm[0];
    CSE1_CV3_1Straight_B.VectorConcatenate_es[1] =
      CSE1_CV3_1Straight_B.Product_dm[1];

    /* Product: '<S139>/Product' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_l[0] * CSE1_CV3_1Straight_B.Product_dm[0];
    tmp_0 += CSE1_CV3_1Straight_B.Gain_l[1] * CSE1_CV3_1Straight_B.Product_dm[1];
    CSE1_CV3_1Straight_B.VectorConcatenate_es[2] = tmp_0;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Constant: '<S145>/0_2x1' */
      CSE1_CV3_1Straight_B.VectorConcatenate_oq[0] =
        CSE1_CV3_1Straight_P._2x1_Value_n[0];
      CSE1_CV3_1Straight_B.VectorConcatenate_oq[1] =
        CSE1_CV3_1Straight_P._2x1_Value_n[1];
    }

    /* Product: '<S145>/Product' */
    CSE1_CV3_1Straight_B.VectorConcatenate_oq[2] =
      CSE1_CV3_1Straight_B.Subtract_n * CSE1_CV3_1Straight_B.Subtract_g;

    /* Sum: '<S138>/Add' */
    CSE1_CV3_1Straight_B.Add_p[0] = CSE1_CV3_1Straight_B.VectorConcatenate_es[0]
      + CSE1_CV3_1Straight_B.VectorConcatenate_oq[0];
    CSE1_CV3_1Straight_B.Add_p[1] = CSE1_CV3_1Straight_B.VectorConcatenate_es[1]
      + CSE1_CV3_1Straight_B.VectorConcatenate_oq[1];
    CSE1_CV3_1Straight_B.Add_p[2] = CSE1_CV3_1Straight_B.VectorConcatenate_es[2]
      + CSE1_CV3_1Straight_B.VectorConcatenate_oq[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S137>/Product' */
      CSE1_CV3_1Straight_B.Product_fp[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_fp[i] = CSE1_CV3_1Straight_B.MathFunction_i[i]
        * CSE1_CV3_1Straight_B.Add_p[0] + CSE1_CV3_1Straight_B.Product_fp[i];
      CSE1_CV3_1Straight_B.Product_fp[i] = CSE1_CV3_1Straight_B.MathFunction_i[i
        + 3] * CSE1_CV3_1Straight_B.Add_p[1] + CSE1_CV3_1Straight_B.Product_fp[i];
      CSE1_CV3_1Straight_B.Product_fp[i] = CSE1_CV3_1Straight_B.MathFunction_i[i
        + 6] * CSE1_CV3_1Straight_B.Add_p[2] + CSE1_CV3_1Straight_B.Product_fp[i];

      /* Sum: '<S137>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_ji[i] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[i] -
        CSE1_CV3_1Straight_B.Product_fp[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S152>/Product2' */
      CSE1_CV3_1Straight_B.Product2_b[i] = 0.0;
      CSE1_CV3_1Straight_B.Product2_b[i] = CSE1_CV3_1Straight_B.Rpsi_k[i] *
        CSE1_CV3_1Straight_B.Subtract_ji[0] + CSE1_CV3_1Straight_B.Product2_b[i];
      CSE1_CV3_1Straight_B.Product2_b[i] = CSE1_CV3_1Straight_B.Rpsi_k[i + 3] *
        CSE1_CV3_1Straight_B.Subtract_ji[1] + CSE1_CV3_1Straight_B.Product2_b[i];
      CSE1_CV3_1Straight_B.Product2_b[i] = CSE1_CV3_1Straight_B.Rpsi_k[i + 6] *
        CSE1_CV3_1Straight_B.Subtract_ji[2] + CSE1_CV3_1Straight_B.Product2_b[i];

      /* Sum: '<S152>/Sum' */
      CSE1_CV3_1Straight_B.Sum_f[i] = ((0.0 - CSE1_CV3_1Straight_B.Product_le[i])
        - CSE1_CV3_1Straight_B.Product1_o[i]) -
        CSE1_CV3_1Straight_B.Product2_b[i];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Gain: '<S154>/-X_u' incorporates:
       *  Constant: '<S154>/X_u'
       */
      CSE1_CV3_1Straight_B.X_u_o = CSE1_CV3_1Straight_P.X_u_Gain_p *
        CSE1_CV3_1Straight_P.X_u_Value_c;

      /* Gain: '<S154>/-Y_v' incorporates:
       *  Constant: '<S154>/Y_v'
       */
      CSE1_CV3_1Straight_B.Y_v_g = CSE1_CV3_1Straight_P.Y_v_Gain_d *
        CSE1_CV3_1Straight_P.Y_v_Value_k;

      /* Gain: '<S154>/-N_v' incorporates:
       *  Constant: '<S154>/N_v'
       */
      CSE1_CV3_1Straight_B.N_v_b = CSE1_CV3_1Straight_P.N_v_Gain_a *
        CSE1_CV3_1Straight_P.N_v_Value_g;

      /* Gain: '<S154>/-Y_vr' incorporates:
       *  Constant: '<S154>/Y_r'
       */
      CSE1_CV3_1Straight_B.Y_vr_n = CSE1_CV3_1Straight_P.Y_vr_Gain_b *
        CSE1_CV3_1Straight_P.Y_r_Value_l;

      /* Gain: '<S154>/-N_r' incorporates:
       *  Constant: '<S154>/N_r'
       */
      CSE1_CV3_1Straight_B.N_r_k = CSE1_CV3_1Straight_P.N_r_Gain_j *
        CSE1_CV3_1Straight_P.N_r_Value_o;

      /* Reshape: '<S154>/Linear Dampning matrix' incorporates:
       *  Constant: '<S154>/D_L_12'
       *  Constant: '<S154>/D_L_13'
       *  Constant: '<S154>/D_L_21'
       *  Constant: '<S154>/D_L_31'
       */
      CSE1_CV3_1Straight_B.LinearDampningmatrix_p[0] =
        CSE1_CV3_1Straight_B.X_u_o;
      CSE1_CV3_1Straight_B.LinearDampningmatrix_p[1] =
        CSE1_CV3_1Straight_P.D_L_21_Value_c;
      CSE1_CV3_1Straight_B.LinearDampningmatrix_p[2] =
        CSE1_CV3_1Straight_P.D_L_31_Value_n;
      CSE1_CV3_1Straight_B.LinearDampningmatrix_p[3] =
        CSE1_CV3_1Straight_P.D_L_12_Value_i;
      CSE1_CV3_1Straight_B.LinearDampningmatrix_p[4] =
        CSE1_CV3_1Straight_B.Y_v_g;
      CSE1_CV3_1Straight_B.LinearDampningmatrix_p[5] =
        CSE1_CV3_1Straight_B.N_v_b;
      CSE1_CV3_1Straight_B.LinearDampningmatrix_p[6] =
        CSE1_CV3_1Straight_P.D_L_13_Value_p;
      CSE1_CV3_1Straight_B.LinearDampningmatrix_p[7] =
        CSE1_CV3_1Straight_B.Y_vr_n;
      CSE1_CV3_1Straight_B.LinearDampningmatrix_p[8] =
        CSE1_CV3_1Straight_B.N_r_k;
    }

    /* Product: '<S151>/Product1' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product1_hd[i] = 0.0;
      CSE1_CV3_1Straight_B.Product1_hd[i] =
        CSE1_CV3_1Straight_B.LinearDampningmatrix_p[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[0] +
        CSE1_CV3_1Straight_B.Product1_hd[i];
      CSE1_CV3_1Straight_B.Product1_hd[i] =
        CSE1_CV3_1Straight_B.LinearDampningmatrix_p[i + 3] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[1] +
        CSE1_CV3_1Straight_B.Product1_hd[i];
      CSE1_CV3_1Straight_B.Product1_hd[i] =
        CSE1_CV3_1Straight_B.LinearDampningmatrix_p[i + 6] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProduct2Inport[2] +
        CSE1_CV3_1Straight_B.Product1_hd[i];
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Sum: '<S153>/M_11' incorporates:
       *  Constant: '<S153>/X_udot'
       *  Constant: '<S153>/m'
       */
      CSE1_CV3_1Straight_B.M_11_p = CSE1_CV3_1Straight_P.m_Value_k -
        CSE1_CV3_1Straight_P.X_udot_Value_a;

      /* Sum: '<S153>/M_22' incorporates:
       *  Constant: '<S153>/Y_vdot'
       *  Constant: '<S153>/m'
       */
      CSE1_CV3_1Straight_B.M_22_m = CSE1_CV3_1Straight_P.m_Value_k -
        CSE1_CV3_1Straight_P.Y_vdot_Value_j;

      /* Product: '<S153>/m x_g' incorporates:
       *  Constant: '<S153>/m'
       *  Constant: '<S153>/x_g'
       */
      CSE1_CV3_1Straight_B.mx_g_k = CSE1_CV3_1Straight_P.m_Value_k *
        CSE1_CV3_1Straight_P.x_g_Value_f;

      /* Sum: '<S153>/M_32' incorporates:
       *  Constant: '<S153>/N_vdot'
       */
      CSE1_CV3_1Straight_B.M_32_a = CSE1_CV3_1Straight_B.mx_g_k -
        CSE1_CV3_1Straight_P.N_vdot_Value_g;

      /* Sum: '<S153>/M_23' incorporates:
       *  Constant: '<S153>/Y_rdot'
       */
      CSE1_CV3_1Straight_B.M_23_p = CSE1_CV3_1Straight_B.mx_g_k -
        CSE1_CV3_1Straight_P.Y_rdot_Value_f;

      /* Sum: '<S153>/M_33' incorporates:
       *  Constant: '<S153>/I_z'
       *  Constant: '<S153>/N_rdot'
       */
      CSE1_CV3_1Straight_B.M_33_m = CSE1_CV3_1Straight_P.I_z_Value_o -
        CSE1_CV3_1Straight_P.N_rdot_Value_a;

      /* Reshape: '<S153>/3x3' incorporates:
       *  Constant: '<S153>/M_12'
       *  Constant: '<S153>/M_13'
       *  Constant: '<S153>/M_21'
       *  Constant: '<S153>/M_31'
       */
      CSE1_CV3_1Straight_B.x3_k[0] = CSE1_CV3_1Straight_B.M_11_p;
      CSE1_CV3_1Straight_B.x3_k[1] = CSE1_CV3_1Straight_P.M_21_Value_n;
      CSE1_CV3_1Straight_B.x3_k[2] = CSE1_CV3_1Straight_P.M_31_Value_h;
      CSE1_CV3_1Straight_B.x3_k[3] = CSE1_CV3_1Straight_P.M_12_Value_j;
      CSE1_CV3_1Straight_B.x3_k[4] = CSE1_CV3_1Straight_B.M_22_m;
      CSE1_CV3_1Straight_B.x3_k[5] = CSE1_CV3_1Straight_B.M_32_a;
      CSE1_CV3_1Straight_B.x3_k[6] = CSE1_CV3_1Straight_P.M_13_Value_o;
      CSE1_CV3_1Straight_B.x3_k[7] = CSE1_CV3_1Straight_B.M_23_p;
      CSE1_CV3_1Straight_B.x3_k[8] = CSE1_CV3_1Straight_B.M_33_m;
    }

    /* Math: '<S143>/Math Function' */
    CSE1_CV3_1Straight_B.MathFunction_h[0] = CSE1_CV3_1Straight_B.Product_dm[0];
    CSE1_CV3_1Straight_B.MathFunction_h[1] = CSE1_CV3_1Straight_B.Product_dm[1];

    /* Math: '<S144>/Math Function' */
    CSE1_CV3_1Straight_B.MathFunction_f[0] = CSE1_CV3_1Straight_B.Product_nq[0];
    CSE1_CV3_1Straight_B.MathFunction_f[1] = CSE1_CV3_1Straight_B.Product_nq[2];
    CSE1_CV3_1Straight_B.MathFunction_f[2] = CSE1_CV3_1Straight_B.Product_nq[1];
    CSE1_CV3_1Straight_B.MathFunction_f[3] = CSE1_CV3_1Straight_B.Product_nq[3];

    /* Product: '<S140>/Product' */
    CSE1_CV3_1Straight_B.Product_py[0] = 0.0;
    CSE1_CV3_1Straight_B.Product_py[0] = CSE1_CV3_1Straight_B.MathFunction_h[0] *
      CSE1_CV3_1Straight_B.MathFunction_f[0] + CSE1_CV3_1Straight_B.Product_py[0];
    CSE1_CV3_1Straight_B.Product_py[0] = CSE1_CV3_1Straight_B.MathFunction_h[1] *
      CSE1_CV3_1Straight_B.MathFunction_f[1] + CSE1_CV3_1Straight_B.Product_py[0];

    /* Product: '<S140>/Product1' */
    CSE1_CV3_1Straight_B.Product1_ak[0] = 0.0;
    CSE1_CV3_1Straight_B.Product1_ak[0] = CSE1_CV3_1Straight_B.Gain_l[0] *
      CSE1_CV3_1Straight_B.Product_d4[0] + CSE1_CV3_1Straight_B.Product1_ak[0];
    CSE1_CV3_1Straight_B.Product1_ak[0] = CSE1_CV3_1Straight_B.Gain_l[1] *
      CSE1_CV3_1Straight_B.Product_d4[1] + CSE1_CV3_1Straight_B.Product1_ak[0];

    /* Sum: '<S140>/Add' */
    CSE1_CV3_1Straight_B.Add_l[0] = CSE1_CV3_1Straight_B.Product_py[0] +
      CSE1_CV3_1Straight_B.Product1_ak[0];

    /* Product: '<S140>/Product' */
    CSE1_CV3_1Straight_B.Product_py[1] = 0.0;
    CSE1_CV3_1Straight_B.Product_py[1] = CSE1_CV3_1Straight_B.MathFunction_h[0] *
      CSE1_CV3_1Straight_B.MathFunction_f[2] + CSE1_CV3_1Straight_B.Product_py[1];
    CSE1_CV3_1Straight_B.Product_py[1] = CSE1_CV3_1Straight_B.MathFunction_h[1] *
      CSE1_CV3_1Straight_B.MathFunction_f[3] + CSE1_CV3_1Straight_B.Product_py[1];

    /* Product: '<S140>/Product1' */
    CSE1_CV3_1Straight_B.Product1_ak[1] = 0.0;
    CSE1_CV3_1Straight_B.Product1_ak[1] = CSE1_CV3_1Straight_B.Gain_l[0] *
      CSE1_CV3_1Straight_B.Product_d4[2] + CSE1_CV3_1Straight_B.Product1_ak[1];
    CSE1_CV3_1Straight_B.Product1_ak[1] = CSE1_CV3_1Straight_B.Gain_l[1] *
      CSE1_CV3_1Straight_B.Product_d4[3] + CSE1_CV3_1Straight_B.Product1_ak[1];

    /* Sum: '<S140>/Add' */
    CSE1_CV3_1Straight_B.Add_l[1] = CSE1_CV3_1Straight_B.Product_py[1] +
      CSE1_CV3_1Straight_B.Product1_ak[1];

    /* Concatenate: '<S140>/Matrix Concatenate' */
    CSE1_CV3_1Straight_B.MatrixConcatenate_o[0] =
      CSE1_CV3_1Straight_B.Product_d4[0];
    CSE1_CV3_1Straight_B.MatrixConcatenate_o[1] =
      CSE1_CV3_1Straight_B.Product_d4[1];
    CSE1_CV3_1Straight_B.MatrixConcatenate_o[3] =
      CSE1_CV3_1Straight_B.Product_d4[2];
    CSE1_CV3_1Straight_B.MatrixConcatenate_o[4] =
      CSE1_CV3_1Straight_B.Product_d4[3];
    CSE1_CV3_1Straight_B.MatrixConcatenate_o[2] = CSE1_CV3_1Straight_B.Add_l[0];
    CSE1_CV3_1Straight_B.MatrixConcatenate_o[5] = CSE1_CV3_1Straight_B.Add_l[1];

    /* Product: '<S146>/Product' */
    CSE1_CV3_1Straight_B.Product_b[0] = CSE1_CV3_1Straight_B.Product_gz[0] *
      CSE1_CV3_1Straight_B.Subtract_g;

    /* Product: '<S146>/Product1' */
    CSE1_CV3_1Straight_B.Product1_g2[0] = CSE1_CV3_1Straight_B.Subtract_n *
      CSE1_CV3_1Straight_B.Sum_id[0];

    /* Sum: '<S146>/Add' */
    CSE1_CV3_1Straight_B.Add_d[0] = CSE1_CV3_1Straight_B.Product_b[0] +
      CSE1_CV3_1Straight_B.Product1_g2[0];

    /* Product: '<S146>/Product' */
    CSE1_CV3_1Straight_B.Product_b[1] = CSE1_CV3_1Straight_B.Product_gz[1] *
      CSE1_CV3_1Straight_B.Subtract_g;

    /* Product: '<S146>/Product1' */
    CSE1_CV3_1Straight_B.Product1_g2[1] = CSE1_CV3_1Straight_B.Subtract_n *
      CSE1_CV3_1Straight_B.Sum_id[1];

    /* Sum: '<S146>/Add' */
    CSE1_CV3_1Straight_B.Add_d[1] = CSE1_CV3_1Straight_B.Product_b[1] +
      CSE1_CV3_1Straight_B.Product1_g2[1];

    /* Concatenate: '<S146>/Matrix Concatenate' incorporates:
     *  Constant: '<S146>/0_2x2'
     */
    CSE1_CV3_1Straight_B.MatrixConcatenate_n[0] =
      CSE1_CV3_1Straight_P._2x2_Value_m[0];
    CSE1_CV3_1Straight_B.MatrixConcatenate_n[1] =
      CSE1_CV3_1Straight_P._2x2_Value_m[1];
    CSE1_CV3_1Straight_B.MatrixConcatenate_n[3] =
      CSE1_CV3_1Straight_P._2x2_Value_m[2];
    CSE1_CV3_1Straight_B.MatrixConcatenate_n[4] =
      CSE1_CV3_1Straight_P._2x2_Value_m[3];
    CSE1_CV3_1Straight_B.MatrixConcatenate_n[2] = CSE1_CV3_1Straight_B.Add_d[0];
    CSE1_CV3_1Straight_B.MatrixConcatenate_n[5] = CSE1_CV3_1Straight_B.Add_d[1];

    /* Sum: '<S188>/Add' */
    for (i = 0; i < 6; i++) {
      CSE1_CV3_1Straight_B.Add_b[i] = CSE1_CV3_1Straight_B.MatrixConcatenate_o[i]
        + CSE1_CV3_1Straight_B.MatrixConcatenate_n[i];
    }

    /* Integrator: '<S135>/omega_q' */
    CSE1_CV3_1Straight_B.omega_q[0] = CSE1_CV3_1Straight_X.omega_q_CSTATE[0];

    /* Sum: '<S135>/Add' */
    CSE1_CV3_1Straight_B.Add_po[0] = CSE1_CV3_1Straight_B.omega_q[0] +
      CSE1_CV3_1Straight_B.Product_dm[0];

    /* Integrator: '<S135>/omega_q' */
    CSE1_CV3_1Straight_B.omega_q[1] = CSE1_CV3_1Straight_X.omega_q_CSTATE[1];

    /* Sum: '<S135>/Add' */
    CSE1_CV3_1Straight_B.Add_po[1] = CSE1_CV3_1Straight_B.omega_q[1] +
      CSE1_CV3_1Straight_B.Product_dm[1];

    /* Product: '<S136>/Product' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product_bl[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_bl[i] = CSE1_CV3_1Straight_B.Add_b[i] *
        CSE1_CV3_1Straight_B.Add_po[0] + CSE1_CV3_1Straight_B.Product_bl[i];
      CSE1_CV3_1Straight_B.Product_bl[i] = CSE1_CV3_1Straight_B.Add_b[i + 3] *
        CSE1_CV3_1Straight_B.Add_po[1] + CSE1_CV3_1Straight_B.Product_bl[i];
    }

    /* SignalConversion: '<S141>/ConcatBufferAtVector ConcatenateIn1' */
    CSE1_CV3_1Straight_B.VectorConcatenate_ge[0] =
      CSE1_CV3_1Straight_B.Product_l0[0];
    CSE1_CV3_1Straight_B.VectorConcatenate_ge[1] =
      CSE1_CV3_1Straight_B.Product_l0[1];

    /* Product: '<S141>/Product' */
    tmp_0 = CSE1_CV3_1Straight_B.Product_gz[0] *
      CSE1_CV3_1Straight_B.Product_dm[0];
    tmp_0 += CSE1_CV3_1Straight_B.Product_gz[1] *
      CSE1_CV3_1Straight_B.Product_dm[1];
    CSE1_CV3_1Straight_B.Product_be = tmp_0;

    /* Product: '<S141>/Product1' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_l[0] * CSE1_CV3_1Straight_B.Product_l0[0];
    tmp_0 += CSE1_CV3_1Straight_B.Gain_l[1] * CSE1_CV3_1Straight_B.Product_l0[1];
    CSE1_CV3_1Straight_B.Product1_m5 = tmp_0;

    /* Sum: '<S141>/Add' */
    CSE1_CV3_1Straight_B.VectorConcatenate_ge[2] =
      CSE1_CV3_1Straight_B.Product_be + CSE1_CV3_1Straight_B.Product1_m5;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Constant: '<S147>/0_2x1' */
      CSE1_CV3_1Straight_B.VectorConcatenate_b[0] =
        CSE1_CV3_1Straight_P._2x1_Value_p[0];
      CSE1_CV3_1Straight_B.VectorConcatenate_b[1] =
        CSE1_CV3_1Straight_P._2x1_Value_p[1];
    }

    /* Product: '<S147>/Product' */
    CSE1_CV3_1Straight_B.Product_o2 = CSE1_CV3_1Straight_B.Subtract1_g *
      CSE1_CV3_1Straight_B.Subtract_g;

    /* Product: '<S147>/Product1' */
    CSE1_CV3_1Straight_B.Product1_f = CSE1_CV3_1Straight_B.Subtract_n *
      CSE1_CV3_1Straight_B.Sum_oq;

    /* Sum: '<S147>/Add' */
    CSE1_CV3_1Straight_B.VectorConcatenate_b[2] =
      CSE1_CV3_1Straight_B.Product_o2 + CSE1_CV3_1Straight_B.Product1_f;

    /* Sum: '<S189>/Add1' */
    CSE1_CV3_1Straight_B.Add1_m[0] = CSE1_CV3_1Straight_B.VectorConcatenate_ge[0]
      + CSE1_CV3_1Straight_B.VectorConcatenate_b[0];

    /* Product: '<S136>/Product1' */
    CSE1_CV3_1Straight_B.Product1_n[0] = CSE1_CV3_1Straight_B.Add1_m[0] *
      CSE1_CV3_1Straight_B.Subtract_g;

    /* Sum: '<S189>/Add1' */
    CSE1_CV3_1Straight_B.Add1_m[1] = CSE1_CV3_1Straight_B.VectorConcatenate_ge[1]
      + CSE1_CV3_1Straight_B.VectorConcatenate_b[1];

    /* Product: '<S136>/Product1' */
    CSE1_CV3_1Straight_B.Product1_n[1] = CSE1_CV3_1Straight_B.Add1_m[1] *
      CSE1_CV3_1Straight_B.Subtract_g;

    /* Sum: '<S189>/Add1' */
    CSE1_CV3_1Straight_B.Add1_m[2] = CSE1_CV3_1Straight_B.VectorConcatenate_ge[2]
      + CSE1_CV3_1Straight_B.VectorConcatenate_b[2];

    /* Product: '<S136>/Product1' */
    CSE1_CV3_1Straight_B.Product1_n[2] = CSE1_CV3_1Straight_B.Add1_m[2] *
      CSE1_CV3_1Straight_B.Subtract_g;

    /* SignalConversion: '<S142>/ConcatBufferAtVector ConcatenateIn1' */
    CSE1_CV3_1Straight_B.VectorConcatenate_a[0] =
      CSE1_CV3_1Straight_B.Product_of[0];
    CSE1_CV3_1Straight_B.VectorConcatenate_a[1] =
      CSE1_CV3_1Straight_B.Product_of[1];

    /* Product: '<S142>/Product1' */
    tmp_0 = CSE1_CV3_1Straight_B.Gain_l[0] * CSE1_CV3_1Straight_B.Product_of[0];
    tmp_0 += CSE1_CV3_1Straight_B.Gain_l[1] * CSE1_CV3_1Straight_B.Product_of[1];
    CSE1_CV3_1Straight_B.VectorConcatenate_a[2] = tmp_0;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Constant: '<S148>/0_2x1' */
      CSE1_CV3_1Straight_B.VectorConcatenate_nu[0] =
        CSE1_CV3_1Straight_P._2x1_Value_j[0];
      CSE1_CV3_1Straight_B.VectorConcatenate_nu[1] =
        CSE1_CV3_1Straight_P._2x1_Value_j[1];
    }

    /* Product: '<S148>/Product1' */
    CSE1_CV3_1Straight_B.VectorConcatenate_nu[2] =
      CSE1_CV3_1Straight_B.Subtract_n * CSE1_CV3_1Straight_B.Product_gd;

    /* Sum: '<S190>/Add' */
    CSE1_CV3_1Straight_B.Add_h[0] = CSE1_CV3_1Straight_B.VectorConcatenate_a[0]
      + CSE1_CV3_1Straight_B.VectorConcatenate_nu[0];

    /* Sum: '<S136>/Sum' */
    CSE1_CV3_1Straight_B.Sum_ek[0] = (CSE1_CV3_1Straight_B.Product_bl[0] +
      CSE1_CV3_1Straight_B.Product1_n[0]) + CSE1_CV3_1Straight_B.Add_h[0];

    /* Sum: '<S190>/Add' */
    CSE1_CV3_1Straight_B.Add_h[1] = CSE1_CV3_1Straight_B.VectorConcatenate_a[1]
      + CSE1_CV3_1Straight_B.VectorConcatenate_nu[1];

    /* Sum: '<S136>/Sum' */
    CSE1_CV3_1Straight_B.Sum_ek[1] = (CSE1_CV3_1Straight_B.Product_bl[1] +
      CSE1_CV3_1Straight_B.Product1_n[1]) + CSE1_CV3_1Straight_B.Add_h[1];

    /* Sum: '<S190>/Add' */
    CSE1_CV3_1Straight_B.Add_h[2] = CSE1_CV3_1Straight_B.VectorConcatenate_a[2]
      + CSE1_CV3_1Straight_B.VectorConcatenate_nu[2];

    /* Sum: '<S136>/Sum' */
    CSE1_CV3_1Straight_B.Sum_ek[2] = (CSE1_CV3_1Straight_B.Product_bl[2] +
      CSE1_CV3_1Straight_B.Product1_n[2]) + CSE1_CV3_1Straight_B.Add_h[2];

    /* Product: '<S150>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_4[i + 3 * tmp_8] = 0.0;
        tmp_4[i + 3 * tmp_8] = tmp_4[3 * tmp_8 + i] +
          CSE1_CV3_1Straight_B.MathFunction_i[3 * tmp_8] *
          CSE1_CV3_1Straight_B.x3_k[i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_i[3 * tmp_8 + 1]
          * CSE1_CV3_1Straight_B.x3_k[i + 3] + tmp_4[3 * tmp_8 + i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_i[3 * tmp_8 + 2]
          * CSE1_CV3_1Straight_B.x3_k[i + 6] + tmp_4[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product_c4[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_c4[i] = tmp_4[i] *
        CSE1_CV3_1Straight_B.Sum_ek[0] + CSE1_CV3_1Straight_B.Product_c4[i];
      CSE1_CV3_1Straight_B.Product_c4[i] = tmp_4[i + 3] *
        CSE1_CV3_1Straight_B.Sum_ek[1] + CSE1_CV3_1Straight_B.Product_c4[i];
      CSE1_CV3_1Straight_B.Product_c4[i] = tmp_4[i + 6] *
        CSE1_CV3_1Straight_B.Sum_ek[2] + CSE1_CV3_1Straight_B.Product_c4[i];
    }

    /* Gain: '<S149>/S12' */
    CSE1_CV3_1Straight_B.S12_o = CSE1_CV3_1Straight_P.S12_Gain_m *
      CSE1_CV3_1Straight_B.nu_yaw;

    /* Reshape: '<S149>/S(r)' incorporates:
     *  Constant: '<S149>/R31'
     *  Constant: '<S149>/S11'
     *  Constant: '<S149>/S13'
     *  Constant: '<S149>/S22'
     *  Constant: '<S149>/S23'
     *  Constant: '<S149>/S32'
     *  Constant: '<S149>/S33'
     */
    CSE1_CV3_1Straight_B.Sr_j[0] = CSE1_CV3_1Straight_P.S11_Value_n;
    CSE1_CV3_1Straight_B.Sr_j[1] = CSE1_CV3_1Straight_B.nu_yaw;
    CSE1_CV3_1Straight_B.Sr_j[2] = CSE1_CV3_1Straight_P.R31_Value_j;
    CSE1_CV3_1Straight_B.Sr_j[3] = CSE1_CV3_1Straight_B.S12_o;
    CSE1_CV3_1Straight_B.Sr_j[4] = CSE1_CV3_1Straight_P.S22_Value_l;
    CSE1_CV3_1Straight_B.Sr_j[5] = CSE1_CV3_1Straight_P.S32_Value_m;
    CSE1_CV3_1Straight_B.Sr_j[6] = CSE1_CV3_1Straight_P.S13_Value_p;
    CSE1_CV3_1Straight_B.Sr_j[7] = CSE1_CV3_1Straight_P.S23_Value_p;
    CSE1_CV3_1Straight_B.Sr_j[8] = CSE1_CV3_1Straight_P.S33_Value_l;

    /* Product: '<S150>/Product1' */
    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_4[i + 3 * tmp_8] = 0.0;
        tmp_4[i + 3 * tmp_8] = tmp_4[3 * tmp_8 + i] + CSE1_CV3_1Straight_B.Sr_j
          [3 * tmp_8] * CSE1_CV3_1Straight_B.x3_k[i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.Sr_j[3 * tmp_8 + 1] *
          CSE1_CV3_1Straight_B.x3_k[i + 3] + tmp_4[3 * tmp_8 + i];
        tmp_4[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.Sr_j[3 * tmp_8 + 2] *
          CSE1_CV3_1Straight_B.x3_k[i + 6] + tmp_4[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_7[i + 3 * tmp_8] = 0.0;
        tmp_7[i + 3 * tmp_8] = tmp_7[3 * tmp_8 + i] +
          CSE1_CV3_1Straight_B.MathFunction_i[3 * tmp_8] * tmp_4[i];
        tmp_7[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_i[3 * tmp_8 + 1]
          * tmp_4[i + 3] + tmp_7[3 * tmp_8 + i];
        tmp_7[i + 3 * tmp_8] = CSE1_CV3_1Straight_B.MathFunction_i[3 * tmp_8 + 2]
          * tmp_4[i + 6] + tmp_7[3 * tmp_8 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product1_fg[i] = 0.0;
      CSE1_CV3_1Straight_B.Product1_fg[i] = tmp_7[i] *
        CSE1_CV3_1Straight_B.Add_p[0] + CSE1_CV3_1Straight_B.Product1_fg[i];
      CSE1_CV3_1Straight_B.Product1_fg[i] = tmp_7[i + 3] *
        CSE1_CV3_1Straight_B.Add_p[1] + CSE1_CV3_1Straight_B.Product1_fg[i];
      CSE1_CV3_1Straight_B.Product1_fg[i] = tmp_7[i + 6] *
        CSE1_CV3_1Straight_B.Add_p[2] + CSE1_CV3_1Straight_B.Product1_fg[i];

      /* Sum: '<S150>/Subtract' */
      CSE1_CV3_1Straight_B.Subtract_a[i] = CSE1_CV3_1Straight_B.Product_c4[i] -
        CSE1_CV3_1Straight_B.Product1_fg[i];

      /* Gain: '<S150>/Gain' */
      CSE1_CV3_1Straight_B.Gain_iy[i] = CSE1_CV3_1Straight_P.Gain_Gain_g *
        CSE1_CV3_1Straight_B.Subtract_a[i];

      /* Sum: '<S125>/Sum' */
      CSE1_CV3_1Straight_B.Sum_d[i] = (CSE1_CV3_1Straight_B.Sum_f[i] +
        CSE1_CV3_1Straight_B.Product1_hd[i]) + CSE1_CV3_1Straight_B.Gain_iy[i];
    }

    /* Product: '<S164>/Product' */
    for (i = 0; i < 5; i++) {
      CSE1_CV3_1Straight_B.Product_hy[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_hy[i] =
        CSE1_CV3_1Straight_B.Pseudoinverse_f[i] * CSE1_CV3_1Straight_B.Sum_d[0]
        + CSE1_CV3_1Straight_B.Product_hy[i];
      CSE1_CV3_1Straight_B.Product_hy[i] =
        CSE1_CV3_1Straight_B.Pseudoinverse_f[i + 5] *
        CSE1_CV3_1Straight_B.Sum_d[1] + CSE1_CV3_1Straight_B.Product_hy[i];
      CSE1_CV3_1Straight_B.Product_hy[i] =
        CSE1_CV3_1Straight_B.Pseudoinverse_f[i + 10] *
        CSE1_CV3_1Straight_B.Sum_d[2] + CSE1_CV3_1Straight_B.Product_hy[i];
    }

    /* RelationalOperator: '<S170>/Compare' incorporates:
     *  Constant: '<S170>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_mw = (CSE1_CV3_1Straight_B.Product_hy[0] <
      CSE1_CV3_1Straight_P.Constant_Value_jo);

    /* RelationalOperator: '<S172>/Compare' */
    CSE1_CV3_1Straight_B.Compare_mk = (CSE1_CV3_1Straight_B.Product_hy[0] == 0.0);

    /* Gain: '<S165>/Gain' */
    CSE1_CV3_1Straight_B.Gain_cd = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_of2
      * CSE1_CV3_1Straight_B.Compare_mk);

    /* RelationalOperator: '<S171>/Compare' incorporates:
     *  Constant: '<S171>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_jd = (CSE1_CV3_1Straight_B.Product_hy[0] >
      CSE1_CV3_1Straight_P.Constant_Value_bb);

    /* Gain: '<S165>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_fi = (uint16_T)(CSE1_CV3_1Straight_P.Gain1_Gain_c
      * CSE1_CV3_1Straight_B.Compare_jd);

    /* Sum: '<S165>/Sum' */
    CSE1_CV3_1Straight_B.Sum_dk = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_mw << 6) + CSE1_CV3_1Straight_B.Gain_cd) +
       CSE1_CV3_1Straight_B.Gain1_fi);

    /* Lookup Block: '<S165>/f_1 < 0'
     * About '<S165>/f_1 < 0 :'
     * Lookup Block: '<S165>/f_1 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_10_o),
                         CSE1_CV3_1Straight_P.f_10_YData_k,
                         CSE1_CV3_1Straight_B.Product_hy[0],
                         CSE1_CV3_1Straight_P.f_10_XData_e, 8U);

    /* Lookup Block: '<S165>/f_1 > 0'
     * About '<S165>/f_1 > 0 :'
     * Lookup Block: '<S165>/f_1 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_10_b),
                         CSE1_CV3_1Straight_P.f_10_YData_d0,
                         CSE1_CV3_1Straight_B.Product_hy[0],
                         CSE1_CV3_1Straight_P.f_10_XData_o2, 9U);

    /* MultiPortSwitch: '<S165>/Multiport Switch' incorporates:
     *  Constant: '<S165>/f_1 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_dk >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_ak = CSE1_CV3_1Straight_B.f_10_o;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_ak =
        CSE1_CV3_1Straight_P.f_10_Value_a;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_ak = CSE1_CV3_1Straight_B.f_10_b;
      break;
    }

    /* RelationalOperator: '<S173>/Compare' incorporates:
     *  Constant: '<S173>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_ef = (CSE1_CV3_1Straight_B.Product_hy[1] <
      CSE1_CV3_1Straight_P.Constant_Value_mh);

    /* RelationalOperator: '<S175>/Compare' */
    CSE1_CV3_1Straight_B.Compare_aw = (CSE1_CV3_1Straight_B.Product_hy[1] == 0.0);

    /* Gain: '<S166>/Gain' */
    CSE1_CV3_1Straight_B.Gain_bf = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_j0 *
      CSE1_CV3_1Straight_B.Compare_aw);

    /* RelationalOperator: '<S174>/Compare' incorporates:
     *  Constant: '<S174>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_fe = (CSE1_CV3_1Straight_B.Product_hy[1] >
      CSE1_CV3_1Straight_P.Constant_Value_hm);

    /* Gain: '<S166>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_ea = (uint16_T)
      (CSE1_CV3_1Straight_P.Gain1_Gain_li * CSE1_CV3_1Straight_B.Compare_fe);

    /* Sum: '<S166>/Sum' */
    CSE1_CV3_1Straight_B.Sum_dg = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_ef << 6) + CSE1_CV3_1Straight_B.Gain_bf) +
       CSE1_CV3_1Straight_B.Gain1_ea);

    /* Lookup Block: '<S166>/f_2 < 0'
     * About '<S166>/f_2 < 0 :'
     * Lookup Block: '<S166>/f_2 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_20_p),
                         CSE1_CV3_1Straight_P.f_20_YData_b,
                         CSE1_CV3_1Straight_B.Product_hy[1],
                         CSE1_CV3_1Straight_P.f_20_XData_k, 10U);

    /* Lookup Block: '<S166>/f_2 > 0'
     * About '<S166>/f_2 > 0 :'
     * Lookup Block: '<S166>/f_2 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_20_l),
                         CSE1_CV3_1Straight_P.f_20_YData_f,
                         CSE1_CV3_1Straight_B.Product_hy[1],
                         CSE1_CV3_1Straight_P.f_20_XData_do, 9U);

    /* MultiPortSwitch: '<S166>/Multiport Switch' incorporates:
     *  Constant: '<S166>/f_2 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_dg >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_h = CSE1_CV3_1Straight_B.f_20_p;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_h = CSE1_CV3_1Straight_P.f_20_Value_n;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_h = CSE1_CV3_1Straight_B.f_20_l;
      break;
    }

    /* RelationalOperator: '<S176>/Compare' incorporates:
     *  Constant: '<S176>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_i3y = (CSE1_CV3_1Straight_B.Product_hy[2] <
      CSE1_CV3_1Straight_P.Constant_Value_aa);

    /* RelationalOperator: '<S178>/Compare' */
    CSE1_CV3_1Straight_B.Compare_pt = (CSE1_CV3_1Straight_B.Product_hy[2] == 0.0);

    /* Gain: '<S167>/Gain' */
    CSE1_CV3_1Straight_B.Gain_ls = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_ks *
      CSE1_CV3_1Straight_B.Compare_pt);

    /* RelationalOperator: '<S177>/Compare' incorporates:
     *  Constant: '<S177>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_io = (CSE1_CV3_1Straight_B.Product_hy[2] >
      CSE1_CV3_1Straight_P.Constant_Value_hb);

    /* Gain: '<S167>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_h = (uint16_T)(CSE1_CV3_1Straight_P.Gain1_Gain_dn
      * CSE1_CV3_1Straight_B.Compare_io);

    /* Sum: '<S167>/Sum' */
    CSE1_CV3_1Straight_B.Sum_be = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_i3y << 6) + CSE1_CV3_1Straight_B.Gain_ls)
       + CSE1_CV3_1Straight_B.Gain1_h);

    /* Lookup Block: '<S167>/f_3 < 0'
     * About '<S167>/f_3 < 0 :'
     * Lookup Block: '<S167>/f_3 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_30_fk),
                         CSE1_CV3_1Straight_P.f_30_YData_g,
                         CSE1_CV3_1Straight_B.Product_hy[2],
                         CSE1_CV3_1Straight_P.f_30_XData_hd, 7U);

    /* Lookup Block: '<S167>/f_3 > 0'
     * About '<S167>/f_3 > 0 :'
     * Lookup Block: '<S167>/f_3 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_30_ig),
                         CSE1_CV3_1Straight_P.f_30_YData_f,
                         CSE1_CV3_1Straight_B.Product_hy[2],
                         CSE1_CV3_1Straight_P.f_30_XData_j, 10U);

    /* MultiPortSwitch: '<S167>/Multiport Switch' incorporates:
     *  Constant: '<S167>/f_3 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_be >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_o = CSE1_CV3_1Straight_B.f_30_fk;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_o = CSE1_CV3_1Straight_P.f_30_Value_e;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_o = CSE1_CV3_1Straight_B.f_30_ig;
      break;
    }

    /* RelationalOperator: '<S179>/Compare' incorporates:
     *  Constant: '<S179>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_lj = (CSE1_CV3_1Straight_B.Product_hy[3] <
      CSE1_CV3_1Straight_P.Constant_Value_iv);

    /* RelationalOperator: '<S181>/Compare' */
    CSE1_CV3_1Straight_B.Compare_mz = (CSE1_CV3_1Straight_B.Product_hy[3] == 0.0);

    /* Gain: '<S168>/Gain' */
    CSE1_CV3_1Straight_B.Gain_df = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_jt *
      CSE1_CV3_1Straight_B.Compare_mz);

    /* RelationalOperator: '<S180>/Compare' incorporates:
     *  Constant: '<S180>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_gf = (CSE1_CV3_1Straight_B.Product_hy[3] >
      CSE1_CV3_1Straight_P.Constant_Value_o5);

    /* Gain: '<S168>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_kx = (uint16_T)
      (CSE1_CV3_1Straight_P.Gain1_Gain_io * CSE1_CV3_1Straight_B.Compare_gf);

    /* Sum: '<S168>/Sum' */
    CSE1_CV3_1Straight_B.Sum_jd = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_lj << 6) + CSE1_CV3_1Straight_B.Gain_df) +
       CSE1_CV3_1Straight_B.Gain1_kx);

    /* Lookup Block: '<S168>/f_4 < 0'
     * About '<S168>/f_4 < 0 :'
     * Lookup Block: '<S168>/f_4 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_40_b),
                         CSE1_CV3_1Straight_P.f_40_YData_g,
                         CSE1_CV3_1Straight_B.Product_hy[3],
                         CSE1_CV3_1Straight_P.f_40_XData_l, 9U);

    /* Lookup Block: '<S168>/f_4 > 0'
     * About '<S168>/f_4 > 0 :'
     * Lookup Block: '<S168>/f_4 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_40_l),
                         CSE1_CV3_1Straight_P.f_40_YData_n,
                         CSE1_CV3_1Straight_B.Product_hy[3],
                         CSE1_CV3_1Straight_P.f_40_XData_b2, 6U);

    /* MultiPortSwitch: '<S168>/Multiport Switch' incorporates:
     *  Constant: '<S168>/f_4 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_jd >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_jj = CSE1_CV3_1Straight_B.f_40_b;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_jj =
        CSE1_CV3_1Straight_P.f_40_Value_c;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_jj = CSE1_CV3_1Straight_B.f_40_l;
      break;
    }

    /* RelationalOperator: '<S182>/Compare' incorporates:
     *  Constant: '<S182>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_h4 = (CSE1_CV3_1Straight_B.Product_hy[4] <
      CSE1_CV3_1Straight_P.Constant_Value_h0);

    /* RelationalOperator: '<S184>/Compare' */
    CSE1_CV3_1Straight_B.Compare_ce = (CSE1_CV3_1Straight_B.Product_hy[4] == 0.0);

    /* Gain: '<S169>/Gain' */
    CSE1_CV3_1Straight_B.Gain_ga = (uint16_T)(CSE1_CV3_1Straight_P.Gain_Gain_oz4
      * CSE1_CV3_1Straight_B.Compare_ce);

    /* RelationalOperator: '<S183>/Compare' incorporates:
     *  Constant: '<S183>/Constant'
     */
    CSE1_CV3_1Straight_B.Compare_gt = (CSE1_CV3_1Straight_B.Product_hy[4] >
      CSE1_CV3_1Straight_P.Constant_Value_gq);

    /* Gain: '<S169>/Gain1' */
    CSE1_CV3_1Straight_B.Gain1_c = (uint16_T)(CSE1_CV3_1Straight_P.Gain1_Gain_h0
      * CSE1_CV3_1Straight_B.Compare_gt);

    /* Sum: '<S169>/Sum' */
    CSE1_CV3_1Straight_B.Sum_mh = (uint16_T)(uint32_T)
      (((CSE1_CV3_1Straight_B.Compare_h4 << 6) + CSE1_CV3_1Straight_B.Gain_ga) +
       CSE1_CV3_1Straight_B.Gain1_c);

    /* Lookup Block: '<S169>/f_5 < 0'
     * About '<S169>/f_5 < 0 :'
     * Lookup Block: '<S169>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_50_n),
                         CSE1_CV3_1Straight_P.f_50_YData_o,
                         CSE1_CV3_1Straight_B.Product_hy[4],
                         CSE1_CV3_1Straight_P.f_50_XData_a, 2U);

    /* Lookup Block: '<S169>/f_5 > 0'
     * About '<S169>/f_5 > 0 :'
     * Lookup Block: '<S169>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.f_50_a),
                         CSE1_CV3_1Straight_P.f_50_YData_n,
                         CSE1_CV3_1Straight_B.Product_hy[4],
                         CSE1_CV3_1Straight_P.f_50_XData_l, 2U);

    /* MultiPortSwitch: '<S169>/Multiport Switch' incorporates:
     *  Constant: '<S169>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)CSE1_CV3_1Straight_B.Sum_mh >> 6)) {
     case 1:
      CSE1_CV3_1Straight_B.MultiportSwitch_jb = CSE1_CV3_1Straight_B.f_50_n;
      break;

     case 2:
      CSE1_CV3_1Straight_B.MultiportSwitch_jb =
        CSE1_CV3_1Straight_P.f_50_Value_h;
      break;

     default:
      CSE1_CV3_1Straight_B.MultiportSwitch_jb = CSE1_CV3_1Straight_B.f_50_a;
      break;
    }

    /* MultiPortSwitch: '<S1>/Thruster setting Switch' incorporates:
     *  Constant: '<S10>/PS3_BT_Power'
     *  Constant: '<S10>/PS3_VSP_Speed'
     *  Constant: '<S11>/LabVIEW  BT power'
     *  Constant: '<S11>/LabVIEW VSP speed'
     *  Constant: '<S1>/Control Mode'
     *  Constant: '<S6>/BT_power_limit'
     *  Constant: '<S6>/VSP_speeds'
     *  Constant: '<S7>/BT_power_limit'
     *  Constant: '<S7>/VSP_speeds'
     *  Constant: '<S9>/BT_power_limit'
     *  Constant: '<S9>/VSP_speeds'
     */
    switch ((int32_T)CSE1_CV3_1Straight_P.ControlMode_Value) {
     case 0:
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[0] =
        CSE1_CV3_1Straight_B.LabVIEWu_1;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[1] =
        CSE1_CV3_1Straight_B.LabVIEWu_2;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[2] =
        CSE1_CV3_1Straight_B.LabVIEWu_3;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[3] =
        CSE1_CV3_1Straight_B.LabVIEWu_4;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[4] =
        CSE1_CV3_1Straight_B.LabVIEWu_5;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[5] =
        CSE1_CV3_1Straight_P.LabVIEWBTpower_Value;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[6] =
        CSE1_CV3_1Straight_P.LabVIEWVSPspeed_Value;
      break;

     case 1:
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[0] = CSE1_CV3_1Straight_B.u_1;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[1] = CSE1_CV3_1Straight_B.u_2;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[2] = CSE1_CV3_1Straight_B.u_3;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[3] = CSE1_CV3_1Straight_B.u_4;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[4] = CSE1_CV3_1Straight_B.u_5;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[5] =
        CSE1_CV3_1Straight_P.PS3_BT_Power_Value;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[6] =
        CSE1_CV3_1Straight_P.PS3_VSP_Speed_Value;
      break;

     case 2:
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[0] =
        CSE1_CV3_1Straight_B.Joysticku_1;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[1] =
        CSE1_CV3_1Straight_B.Joysticku_2;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[2] =
        CSE1_CV3_1Straight_B.Joysticku_3;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[3] =
        CSE1_CV3_1Straight_B.Joysticku_4;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[4] =
        CSE1_CV3_1Straight_B.Joysticku_5;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[5] =
        CSE1_CV3_1Straight_P.PS3_BT_Power_Value;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[6] =
        CSE1_CV3_1Straight_P.PS3_VSP_Speed_Value;
      break;

     case 3:
      for (i = 0; i < 5; i++) {
        CSE1_CV3_1Straight_B.ThrustersettingSwitch[i] =
          CSE1_CV3_1Straight_B.Saturation_cs[i];
      }

      CSE1_CV3_1Straight_B.ThrustersettingSwitch[5] =
        CSE1_CV3_1Straight_P.BT_power_limit_Value;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[6] =
        CSE1_CV3_1Straight_P.VSP_speeds_Value;
      break;

     case 4:
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[0] =
        CSE1_CV3_1Straight_B.MultiportSwitch_id;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[1] =
        CSE1_CV3_1Straight_B.MultiportSwitch_f;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[2] =
        CSE1_CV3_1Straight_B.MultiportSwitch_ga;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[3] =
        CSE1_CV3_1Straight_B.MultiportSwitch_me;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[4] =
        CSE1_CV3_1Straight_B.MultiportSwitch_bl;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[5] =
        CSE1_CV3_1Straight_P.BT_power_limit_Value_c;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[6] =
        CSE1_CV3_1Straight_P.VSP_speeds_Value_m;
      break;

     default:
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[0] =
        CSE1_CV3_1Straight_B.MultiportSwitch_ak;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[1] =
        CSE1_CV3_1Straight_B.MultiportSwitch_h;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[2] =
        CSE1_CV3_1Straight_B.MultiportSwitch_o;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[3] =
        CSE1_CV3_1Straight_B.MultiportSwitch_jj;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[4] =
        CSE1_CV3_1Straight_B.MultiportSwitch_jb;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[5] =
        CSE1_CV3_1Straight_P.BT_power_limit_Value_f;
      CSE1_CV3_1Straight_B.ThrustersettingSwitch[6] =
        CSE1_CV3_1Straight_P.VSP_speeds_Value_d;
      break;
    }

    /* Saturate: '<S1>/Saturation' */
    for (i = 0; i < 7; i++) {
      tmp_0 = CSE1_CV3_1Straight_B.ThrustersettingSwitch[i];
      CSE1_CV3_1Straight_B.Saturation_ay[i] = rt_SATURATE(tmp_0,
        CSE1_CV3_1Straight_P.Saturation_LowerSat_n,
        CSE1_CV3_1Straight_P.Saturation_UpperSat_d);
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Gain: '<S194>/-l_x1' incorporates:
       *  Constant: '<S194>/l_x1'
       */
      CSE1_CV3_1Straight_B.l_x1_b = CSE1_CV3_1Straight_P.l_x1_Gain_dp *
        CSE1_CV3_1Straight_P.l_x1_Value_k;

      /* Gain: '<S194>/-l_y2' incorporates:
       *  Constant: '<S194>/l_y2'
       */
      CSE1_CV3_1Straight_B.l_y2_ia = CSE1_CV3_1Straight_P.l_y2_Gain_d *
        CSE1_CV3_1Straight_P.l_y2_Value_o;

      /* Gain: '<S194>/-l_x2' incorporates:
       *  Constant: '<S194>/l_x2'
       */
      CSE1_CV3_1Straight_B.l_x2_j = CSE1_CV3_1Straight_P.l_x2_Gain_c *
        CSE1_CV3_1Straight_P.l_x2_Value_i;

      /* Reshape: '<S194>/3x5' incorporates:
       *  Constant: '<S194>/T_e11'
       *  Constant: '<S194>/T_e12'
       *  Constant: '<S194>/T_e13'
       *  Constant: '<S194>/T_e14'
       *  Constant: '<S194>/T_e15'
       *  Constant: '<S194>/T_e21'
       *  Constant: '<S194>/T_e22'
       *  Constant: '<S194>/T_e23'
       *  Constant: '<S194>/T_e24'
       *  Constant: '<S194>/T_e25'
       *  Constant: '<S194>/l_x3'
       *  Constant: '<S194>/l_y1'
       */
      CSE1_CV3_1Straight_B.x5_h[0] = CSE1_CV3_1Straight_P.T_e11_Value_mi;
      CSE1_CV3_1Straight_B.x5_h[1] = CSE1_CV3_1Straight_P.T_e21_Value_kz;
      CSE1_CV3_1Straight_B.x5_h[2] = CSE1_CV3_1Straight_P.l_y1_Value_cw;
      CSE1_CV3_1Straight_B.x5_h[3] = CSE1_CV3_1Straight_P.T_e12_Value_k;
      CSE1_CV3_1Straight_B.x5_h[4] = CSE1_CV3_1Straight_P.T_e22_Value_i;
      CSE1_CV3_1Straight_B.x5_h[5] = CSE1_CV3_1Straight_B.l_x1_b;
      CSE1_CV3_1Straight_B.x5_h[6] = CSE1_CV3_1Straight_P.T_e13_Value_n;
      CSE1_CV3_1Straight_B.x5_h[7] = CSE1_CV3_1Straight_P.T_e23_Value_p;
      CSE1_CV3_1Straight_B.x5_h[8] = CSE1_CV3_1Straight_B.l_y2_ia;
      CSE1_CV3_1Straight_B.x5_h[9] = CSE1_CV3_1Straight_P.T_e14_Value_b;
      CSE1_CV3_1Straight_B.x5_h[10] = CSE1_CV3_1Straight_P.T_e24_Value_a;
      CSE1_CV3_1Straight_B.x5_h[11] = CSE1_CV3_1Straight_B.l_x2_j;
      CSE1_CV3_1Straight_B.x5_h[12] = CSE1_CV3_1Straight_P.T_e15_Value_f;
      CSE1_CV3_1Straight_B.x5_h[13] = CSE1_CV3_1Straight_P.T_e25_Value_bb;
      CSE1_CV3_1Straight_B.x5_h[14] = CSE1_CV3_1Straight_P.l_x3_Value_i;

      /* Lookup Block: '<S193>/u_1 to f_1'
       * About '<S193>/u_1 to f_1 :'
       * Lookup Block: '<S193>/u_1 to f_1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_1tof_1),
                           CSE1_CV3_1Straight_P.u_1tof_1_YData,
                           CSE1_CV3_1Straight_B.LabVIEWu_1,
                           CSE1_CV3_1Straight_P.u_1tof_1_XData, 18U);

      /* Lookup Block: '<S193>/u_2 to f_2'
       * About '<S193>/u_2 to f_2 :'
       * Lookup Block: '<S193>/u_2 to f_2'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_2tof_2),
                           CSE1_CV3_1Straight_P.u_2tof_2_YData,
                           CSE1_CV3_1Straight_B.LabVIEWu_2,
                           CSE1_CV3_1Straight_P.u_2tof_2_XData, 20U);

      /* Lookup Block: '<S193>/u_3 to f_3'
       * About '<S193>/u_3 to f_3 :'
       * Lookup Block: '<S193>/u_3 to f_3'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_3tof_3),
                           CSE1_CV3_1Straight_P.u_3tof_3_YData,
                           CSE1_CV3_1Straight_B.LabVIEWu_3,
                           CSE1_CV3_1Straight_P.u_3tof_3_XData, 18U);

      /* Lookup Block: '<S193>/u_4 to f_4'
       * About '<S193>/u_4 to f_4 :'
       * Lookup Block: '<S193>/u_4 to f_4'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_4tof_4),
                           CSE1_CV3_1Straight_P.u_4tof_4_YData,
                           CSE1_CV3_1Straight_B.LabVIEWu_4,
                           CSE1_CV3_1Straight_P.u_4tof_4_XData, 16U);

      /* Lookup Block: '<S193>/u_5 to f_5'
       * About '<S193>/u_5 to f_5 :'
       * Lookup Block: '<S193>/u_5 to f_5'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_5tof_5),
                           CSE1_CV3_1Straight_P.u_5tof_5_YData,
                           CSE1_CV3_1Straight_B.LabVIEWu_5,
                           CSE1_CV3_1Straight_P.u_5tof_5_XData, 6U);

      /* SignalConversion: '<S192>/TmpHiddenBufferAtProductInport2' */
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_b[0] =
        CSE1_CV3_1Straight_B.u_1tof_1;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_b[1] =
        CSE1_CV3_1Straight_B.u_2tof_2;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_b[2] =
        CSE1_CV3_1Straight_B.u_3tof_3;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_b[3] =
        CSE1_CV3_1Straight_B.u_4tof_4;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_b[4] =
        CSE1_CV3_1Straight_B.u_5tof_5;

      /* Product: '<S192>/Product' */
      for (i = 0; i < 3; i++) {
        CSE1_CV3_1Straight_B.Product_lh[i] = 0.0;
        for (tmp_8 = 0; tmp_8 < 5; tmp_8++) {
          CSE1_CV3_1Straight_B.Product_lh[i] = CSE1_CV3_1Straight_B.x5_h[3 *
            tmp_8 + i] *
            CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_b[tmp_8] +
            CSE1_CV3_1Straight_B.Product_lh[i];
        }
      }

      /* Gain: '<S122>/-l_x1' incorporates:
       *  Constant: '<S122>/l_x1'
       */
      CSE1_CV3_1Straight_B.l_x1_c = CSE1_CV3_1Straight_P.l_x1_Gain_k *
        CSE1_CV3_1Straight_P.l_x1_Value_o;

      /* Gain: '<S122>/-l_y2' incorporates:
       *  Constant: '<S122>/l_y2'
       */
      CSE1_CV3_1Straight_B.l_y2_d = CSE1_CV3_1Straight_P.l_y2_Gain_b *
        CSE1_CV3_1Straight_P.l_y2_Value_d;

      /* Gain: '<S122>/-l_x2' incorporates:
       *  Constant: '<S122>/l_x2'
       */
      CSE1_CV3_1Straight_B.l_x2_h = CSE1_CV3_1Straight_P.l_x2_Gain_ik *
        CSE1_CV3_1Straight_P.l_x2_Value_a;

      /* Reshape: '<S122>/3x5' incorporates:
       *  Constant: '<S122>/T_e11'
       *  Constant: '<S122>/T_e12'
       *  Constant: '<S122>/T_e13'
       *  Constant: '<S122>/T_e14'
       *  Constant: '<S122>/T_e15'
       *  Constant: '<S122>/T_e21'
       *  Constant: '<S122>/T_e22'
       *  Constant: '<S122>/T_e23'
       *  Constant: '<S122>/T_e24'
       *  Constant: '<S122>/T_e25'
       *  Constant: '<S122>/l_x3'
       *  Constant: '<S122>/l_y1'
       */
      CSE1_CV3_1Straight_B.x5_iw[0] = CSE1_CV3_1Straight_P.T_e11_Value_b;
      CSE1_CV3_1Straight_B.x5_iw[1] = CSE1_CV3_1Straight_P.T_e21_Value_cm;
      CSE1_CV3_1Straight_B.x5_iw[2] = CSE1_CV3_1Straight_P.l_y1_Value_d;
      CSE1_CV3_1Straight_B.x5_iw[3] = CSE1_CV3_1Straight_P.T_e12_Value_d;
      CSE1_CV3_1Straight_B.x5_iw[4] = CSE1_CV3_1Straight_P.T_e22_Value_iv;
      CSE1_CV3_1Straight_B.x5_iw[5] = CSE1_CV3_1Straight_B.l_x1_c;
      CSE1_CV3_1Straight_B.x5_iw[6] = CSE1_CV3_1Straight_P.T_e13_Value_ol;
      CSE1_CV3_1Straight_B.x5_iw[7] = CSE1_CV3_1Straight_P.T_e23_Value_m;
      CSE1_CV3_1Straight_B.x5_iw[8] = CSE1_CV3_1Straight_B.l_y2_d;
      CSE1_CV3_1Straight_B.x5_iw[9] = CSE1_CV3_1Straight_P.T_e14_Value_i;
      CSE1_CV3_1Straight_B.x5_iw[10] = CSE1_CV3_1Straight_P.T_e24_Value_f;
      CSE1_CV3_1Straight_B.x5_iw[11] = CSE1_CV3_1Straight_B.l_x2_h;
      CSE1_CV3_1Straight_B.x5_iw[12] = CSE1_CV3_1Straight_P.T_e15_Value_d;
      CSE1_CV3_1Straight_B.x5_iw[13] = CSE1_CV3_1Straight_P.T_e25_Value_j;
      CSE1_CV3_1Straight_B.x5_iw[14] = CSE1_CV3_1Straight_P.l_x3_Value_l;

      /* Lookup Block: '<S121>/u_1 to f_1'
       * About '<S121>/u_1 to f_1 :'
       * Lookup Block: '<S121>/u_1 to f_1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_1tof_1_p),
                           CSE1_CV3_1Straight_P.u_1tof_1_YData_k,
                           CSE1_CV3_1Straight_B.u_1,
                           CSE1_CV3_1Straight_P.u_1tof_1_XData_p, 18U);

      /* Lookup Block: '<S121>/u_2 to f_2'
       * About '<S121>/u_2 to f_2 :'
       * Lookup Block: '<S121>/u_2 to f_2'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_2tof_2_a),
                           CSE1_CV3_1Straight_P.u_2tof_2_YData_o,
                           CSE1_CV3_1Straight_B.u_2,
                           CSE1_CV3_1Straight_P.u_2tof_2_XData_o, 20U);

      /* Lookup Block: '<S121>/u_3 to f_3'
       * About '<S121>/u_3 to f_3 :'
       * Lookup Block: '<S121>/u_3 to f_3'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_3tof_3_b),
                           CSE1_CV3_1Straight_P.u_3tof_3_YData_i,
                           CSE1_CV3_1Straight_B.u_3,
                           CSE1_CV3_1Straight_P.u_3tof_3_XData_i, 18U);

      /* Lookup Block: '<S121>/u_4 to f_4'
       * About '<S121>/u_4 to f_4 :'
       * Lookup Block: '<S121>/u_4 to f_4'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_4tof_4_p),
                           CSE1_CV3_1Straight_P.u_4tof_4_YData_f,
                           CSE1_CV3_1Straight_B.u_4,
                           CSE1_CV3_1Straight_P.u_4tof_4_XData_d, 16U);

      /* Lookup Block: '<S121>/u_5 to f_5'
       * About '<S121>/u_5 to f_5 :'
       * Lookup Block: '<S121>/u_5 to f_5'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(CSE1_CV3_1Straight_B.u_5tof_5_k),
                           CSE1_CV3_1Straight_P.u_5tof_5_YData_o,
                           CSE1_CV3_1Straight_B.u_5,
                           CSE1_CV3_1Straight_P.u_5tof_5_XData_c, 6U);

      /* SignalConversion: '<S120>/TmpHiddenBufferAtProductInport2' */
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_m[0] =
        CSE1_CV3_1Straight_B.u_1tof_1_p;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_m[1] =
        CSE1_CV3_1Straight_B.u_2tof_2_a;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_m[2] =
        CSE1_CV3_1Straight_B.u_3tof_3_b;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_m[3] =
        CSE1_CV3_1Straight_B.u_4tof_4_p;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_m[4] =
        CSE1_CV3_1Straight_B.u_5tof_5_k;

      /* Product: '<S120>/Product' */
      for (i = 0; i < 3; i++) {
        CSE1_CV3_1Straight_B.Product_m[i] = 0.0;
        for (tmp_8 = 0; tmp_8 < 5; tmp_8++) {
          CSE1_CV3_1Straight_B.Product_m[i] = CSE1_CV3_1Straight_B.x5_iw[3 *
            tmp_8 + i] *
            CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_m[tmp_8] +
            CSE1_CV3_1Straight_B.Product_m[i];
        }
      }
    }

    /* MultiPortSwitch: '<S1>/tau  Switch' incorporates:
     *  Constant: '<S1>/Control Mode'
     */
    switch ((int32_T)CSE1_CV3_1Straight_P.ControlMode_Value) {
     case 0:
      CSE1_CV3_1Straight_B.tauSwitch[0] = CSE1_CV3_1Straight_B.Product_lh[0];
      CSE1_CV3_1Straight_B.tauSwitch[1] = CSE1_CV3_1Straight_B.Product_lh[1];
      CSE1_CV3_1Straight_B.tauSwitch[2] = CSE1_CV3_1Straight_B.Product_lh[2];
      break;

     case 1:
      CSE1_CV3_1Straight_B.tauSwitch[0] = CSE1_CV3_1Straight_B.Product_m[0];
      CSE1_CV3_1Straight_B.tauSwitch[1] = CSE1_CV3_1Straight_B.Product_m[1];
      CSE1_CV3_1Straight_B.tauSwitch[2] = CSE1_CV3_1Straight_B.Product_m[2];
      break;

     case 2:
      CSE1_CV3_1Straight_B.tauSwitch[0] = CSE1_CV3_1Straight_B.tau_surge;
      CSE1_CV3_1Straight_B.tauSwitch[1] = CSE1_CV3_1Straight_B.tau_sway;
      CSE1_CV3_1Straight_B.tauSwitch[2] = CSE1_CV3_1Straight_B.tau_yaw;
      break;

     case 3:
      CSE1_CV3_1Straight_B.tauSwitch[0] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[0];
      CSE1_CV3_1Straight_B.tauSwitch[1] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[1];
      CSE1_CV3_1Straight_B.tauSwitch[2] =
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[2];
      break;

     case 4:
      CSE1_CV3_1Straight_B.tauSwitch[0] = CSE1_CV3_1Straight_B.Sum_e[0];
      CSE1_CV3_1Straight_B.tauSwitch[1] = CSE1_CV3_1Straight_B.Sum_e[1];
      CSE1_CV3_1Straight_B.tauSwitch[2] = CSE1_CV3_1Straight_B.Sum_e[2];
      break;

     default:
      CSE1_CV3_1Straight_B.tauSwitch[0] = CSE1_CV3_1Straight_B.Sum_d[0];
      CSE1_CV3_1Straight_B.tauSwitch[1] = CSE1_CV3_1Straight_B.Sum_d[1];
      CSE1_CV3_1Straight_B.tauSwitch[2] = CSE1_CV3_1Straight_B.Sum_d[2];
      break;
    }

    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* SignalConversion: '<Root>/TmpHiddenBufferAtTo FileInport1' */
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[0] =
        CSE1_CV3_1Straight_B.QTMIn9Residual;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[1] =
        CSE1_CV3_1Straight_B.eta_surge;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[2] =
        CSE1_CV3_1Straight_B.eta_sway;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[3] =
        CSE1_CV3_1Straight_B.eta_yaw;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[4] =
        CSE1_CV3_1Straight_B.nu_surge;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[5] =
        CSE1_CV3_1Straight_B.nu_sway;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[6] =
        CSE1_CV3_1Straight_B.nu_yaw;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[7] =
        CSE1_CV3_1Straight_B.eta_dDPN;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[8] =
        CSE1_CV3_1Straight_B.eta_dDPE;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[9] =
        CSE1_CV3_1Straight_B.eta_dDPPsi;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[10] =
        CSE1_CV3_1Straight_B.pathx_d;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[11] =
        CSE1_CV3_1Straight_B.pathy_d;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[12] =
        CSE1_CV3_1Straight_B.pathpsi_d;
      for (i = 0; i < 7; i++) {
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[i + 13] =
          CSE1_CV3_1Straight_B.Saturation_ay[i];
      }

      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[20] =
        CSE1_CV3_1Straight_B.tauSwitch[0];
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[21] =
        CSE1_CV3_1Straight_B.tauSwitch[1];
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[22] =
        CSE1_CV3_1Straight_B.tauSwitch[2];

      /* ToFile Block: '<Root>/To File'
       */
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        if (!(++CSE1_CV3_1Straight_DWork.ToFile_IWORK.Decimation % 1) &&
            (CSE1_CV3_1Straight_DWork.ToFile_IWORK.Count*24)+1 < 100000000 ) {
          real_T u[24];
          FILE *fp = (FILE *) CSE1_CV3_1Straight_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            CSE1_CV3_1Straight_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = CSE1_CV3_1Straight_M->Timing.t[1];
            u[1] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[13];
            u[15] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[14];
            u[16] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[15];
            u[17] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[16];
            u[18] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[17];
            u[19] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[18];
            u[20] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[19];
            u[21] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[20];
            u[22] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[21];
            u[23] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport1[22];
            if (fwrite(u, sizeof(real_T), 24, fp) != 24) {
              rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                                "Error writing to MAT-file CSE1_data.mat");
              return;
            }

            if (((++CSE1_CV3_1Straight_DWork.ToFile_IWORK.Count)*24)+1 >=
                100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file CSE1_data.mat.\n");
            }
          }
        }
      }
    }

    /* Integrator: '<S15>/Integrator1' */
    CSE1_CV3_1Straight_B.eta_w[0] = CSE1_CV3_1Straight_X.Integrator1_CSTATE_d[0];
    CSE1_CV3_1Straight_B.eta_w[1] = CSE1_CV3_1Straight_X.Integrator1_CSTATE_d[1];
    CSE1_CV3_1Straight_B.eta_w[2] = CSE1_CV3_1Straight_X.Integrator1_CSTATE_d[2];
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* ToFile Block: '<S6>/To File'
       */
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        if (!(++CSE1_CV3_1Straight_DWork.ToFile_IWORK_l.Decimation % 1) &&
            (CSE1_CV3_1Straight_DWork.ToFile_IWORK_l.Count*4)+1 < 100000000 ) {
          real_T u[4];
          FILE *fp = (FILE *) CSE1_CV3_1Straight_DWork.ToFile_PWORK_a.FilePtr;
          if (fp != (NULL)) {
            CSE1_CV3_1Straight_DWork.ToFile_IWORK_l.Decimation = 0;
            u[0] = CSE1_CV3_1Straight_M->Timing.t[1];
            u[1] = CSE1_CV3_1Straight_B.eta_w[0];
            u[2] = CSE1_CV3_1Straight_B.eta_w[1];
            u[3] = CSE1_CV3_1Straight_B.eta_w[2];
            if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
              rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                                "Error writing to MAT-file CSE1_data_eta_w.mat");
              return;
            }

            if (((++CSE1_CV3_1Straight_DWork.ToFile_IWORK_l.Count)*4)+1 >=
                100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file CSE1_data_eta_w.mat.\n");
            }
          }
        }
      }

      /* SignalConversion: '<S14>/TmpHiddenBufferAtTo FileInport1' */
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport_k[0] =
        CSE1_CV3_1Straight_B.Reg_e_N_hil;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport_k[1] =
        CSE1_CV3_1Straight_B.Reg_e_E_hil;
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport_k[2] =
        CSE1_CV3_1Straight_B.Reg_e_Psi_hil;

      /* ToFile Block: '<S14>/To File'
       */
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
        if (!(++CSE1_CV3_1Straight_DWork.ToFile_IWORK_e.Decimation % 1) &&
            (CSE1_CV3_1Straight_DWork.ToFile_IWORK_e.Count*4)+1 < 100000000 ) {
          real_T u[4];
          FILE *fp = (FILE *) CSE1_CV3_1Straight_DWork.ToFile_PWORK_c.FilePtr;
          if (fp != (NULL)) {
            CSE1_CV3_1Straight_DWork.ToFile_IWORK_e.Decimation = 0;
            u[0] = CSE1_CV3_1Straight_M->Timing.t[1];
            u[1] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport_k[0];
            u[2] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport_k[1];
            u[3] = CSE1_CV3_1Straight_B.TmpHiddenBufferAtToFileInport_k[2];
            if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
              rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                                "Error writing to MAT-file CSE1_data_reg_error.mat");
              return;
            }

            if (((++CSE1_CV3_1Straight_DWork.ToFile_IWORK_e.Count)*4)+1 >=
                100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file CSE1_data_reg_error.mat.\n");
            }
          }
        }
      }
    }

    /* Gain: '<S14>/K_d 3 deg' */
    CSE1_CV3_1Straight_B.K_d3deg = CSE1_CV3_1Straight_P.K_d3deg_Gain *
      CSE1_CV3_1Straight_B.Product_l[2];

    /* Gain: '<S14>/K_i 3 deg' */
    CSE1_CV3_1Straight_B.K_i3deg = CSE1_CV3_1Straight_P.K_i3deg_Gain *
      CSE1_CV3_1Straight_B.Product1[2];

    /* Gain: '<S14>/K_p 3 deg' */
    CSE1_CV3_1Straight_B.K_p3deg = CSE1_CV3_1Straight_P.K_p3deg_Gain *
      CSE1_CV3_1Straight_B.Product2[2];

    /* Gain: '<S14>/Reg_e_Psi_deg' */
    CSE1_CV3_1Straight_B.Reg_e_Psi_deg = CSE1_CV3_1Straight_P.Reg_e_Psi_deg_Gain
      * CSE1_CV3_1Straight_B.regulationerror[2];

    /* Gain: '<S14>/eta Psi deg' */
    CSE1_CV3_1Straight_B.etaPsideg = CSE1_CV3_1Straight_P.etaPsideg_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch_b[2];
    for (i = 0; i < 3; i++) {
      /* Gain: '<S15>/Gain1' */
      CSE1_CV3_1Straight_B.Gain1_j[i] = 0.0;
      CSE1_CV3_1Straight_B.Gain1_j[i] = CSE1_CV3_1Straight_P.Gain1_Gain_k[i] *
        CSE1_CV3_1Straight_B.eta_w[0] + CSE1_CV3_1Straight_B.Gain1_j[i];
      CSE1_CV3_1Straight_B.Gain1_j[i] = CSE1_CV3_1Straight_P.Gain1_Gain_k[i + 3]
        * CSE1_CV3_1Straight_B.eta_w[1] + CSE1_CV3_1Straight_B.Gain1_j[i];
      CSE1_CV3_1Straight_B.Gain1_j[i] = CSE1_CV3_1Straight_P.Gain1_Gain_k[i + 6]
        * CSE1_CV3_1Straight_B.eta_w[2] + CSE1_CV3_1Straight_B.Gain1_j[i];

      /* Integrator: '<S15>/Integrator2' */
      CSE1_CV3_1Straight_B.xi_w[i] = CSE1_CV3_1Straight_X.Integrator2_CSTATE_e[i];
    }

    /* Sum: '<S15>/Sum4' */
    CSE1_CV3_1Straight_B.Sum4[0] = CSE1_CV3_1Straight_B.eta_w[0] +
      CSE1_CV3_1Straight_B.eta[0];
    CSE1_CV3_1Straight_B.Sum4[1] = CSE1_CV3_1Straight_B.eta_w[1] +
      CSE1_CV3_1Straight_B.eta[1];
    CSE1_CV3_1Straight_B.Sum4[2] = CSE1_CV3_1Straight_B.eta_w[2] +
      CSE1_CV3_1Straight_B.Sum_m;

    /* Sum: '<S15>/Sum2' */
    CSE1_CV3_1Straight_B.Sum2_a[0] = CSE1_CV3_1Straight_B.eta_surge -
      CSE1_CV3_1Straight_B.Sum4[0];
    CSE1_CV3_1Straight_B.Sum2_a[1] = CSE1_CV3_1Straight_B.eta_sway -
      CSE1_CV3_1Straight_B.Sum4[1];
    CSE1_CV3_1Straight_B.Sum2_a[2] = CSE1_CV3_1Straight_B.eta_yaw -
      CSE1_CV3_1Straight_B.Sum4[2];

    /* Saturate: '<S24>/Saturation' */
    tmp_0 = CSE1_CV3_1Straight_B.Sum2_a[2];
    CSE1_CV3_1Straight_B.Saturation_cy = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation_LowerSat_l,
      CSE1_CV3_1Straight_P.Saturation_UpperSat_l);

    /* Signum: '<S24>/Sign' */
    CSE1_CV3_1Straight_B.Sign_d = rt_SIGNd_snf
      (CSE1_CV3_1Straight_B.Saturation_cy);

    /* Gain: '<S24>/Gain' */
    CSE1_CV3_1Straight_B.Gain_ju = CSE1_CV3_1Straight_P.Gain_Gain_gh *
      CSE1_CV3_1Straight_B.Sign_d;

    /* Sum: '<S24>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_he = CSE1_CV3_1Straight_B.Saturation_cy +
      CSE1_CV3_1Straight_B.Gain_ju;

    /* Math: '<S24>/Math Function' incorporates:
     *  Constant: '<S24>/Constant'
     */
    CSE1_CV3_1Straight_B.MathFunction_kv = rt_rem_snf
      (CSE1_CV3_1Straight_B.Sum1_he, CSE1_CV3_1Straight_P.Constant_Value_pu);

    /* Sum: '<S24>/Sum' */
    CSE1_CV3_1Straight_B.Sum_ez = CSE1_CV3_1Straight_B.MathFunction_kv -
      CSE1_CV3_1Straight_B.Gain_ju;

    /* SignalConversion: '<S15>/TmpHiddenBufferAtK11Inport1' */
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[0] =
      CSE1_CV3_1Straight_B.Sum2_a[0];
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[1] =
      CSE1_CV3_1Straight_B.Sum2_a[1];
    CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[2] =
      CSE1_CV3_1Straight_B.Sum_ez;

    /* Fcn: '<S21>/Row1' */
    for (i = 0; i < 3; i++) {
      /* Gain: '<S15>/Gain2' */
      CSE1_CV3_1Straight_B.Gain2[i] = 0.0;
      CSE1_CV3_1Straight_B.Gain2[i] = CSE1_CV3_1Straight_P.Gain2_Gain[i] *
        CSE1_CV3_1Straight_B.xi_w[0] + CSE1_CV3_1Straight_B.Gain2[i];
      CSE1_CV3_1Straight_B.Gain2[i] = CSE1_CV3_1Straight_P.Gain2_Gain[i + 3] *
        CSE1_CV3_1Straight_B.xi_w[1] + CSE1_CV3_1Straight_B.Gain2[i];
      CSE1_CV3_1Straight_B.Gain2[i] = CSE1_CV3_1Straight_P.Gain2_Gain[i + 6] *
        CSE1_CV3_1Straight_B.xi_w[2] + CSE1_CV3_1Straight_B.Gain2[i];

      /* Gain: '<S15>/K4' */
      CSE1_CV3_1Straight_B.K4[i] = 0.0;
      CSE1_CV3_1Straight_B.K4[i] = CSE1_CV3_1Straight_P.K4_Gain[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[0] +
        CSE1_CV3_1Straight_B.K4[i];
      CSE1_CV3_1Straight_B.K4[i] = CSE1_CV3_1Straight_P.K4_Gain[i + 3] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[1] +
        CSE1_CV3_1Straight_B.K4[i];
      CSE1_CV3_1Straight_B.K4[i] = CSE1_CV3_1Straight_P.K4_Gain[i + 6] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[2] +
        CSE1_CV3_1Straight_B.K4[i];

      /* Integrator: '<S15>/Integrator3' */
      CSE1_CV3_1Straight_B.bias[i] = CSE1_CV3_1Straight_X.Integrator3_CSTATE[i];

      /* Gain: '<S15>/Gain6' */
      CSE1_CV3_1Straight_B.Gain6[i] = 0.0;
      CSE1_CV3_1Straight_B.Gain6[i] = CSE1_CV3_1Straight_P.Gain6_Gain[i] *
        CSE1_CV3_1Straight_B.nu_d[0] + CSE1_CV3_1Straight_B.Gain6[i];
      CSE1_CV3_1Straight_B.Gain6[i] = CSE1_CV3_1Straight_P.Gain6_Gain[i + 3] *
        CSE1_CV3_1Straight_B.nu_d[1] + CSE1_CV3_1Straight_B.Gain6[i];
      CSE1_CV3_1Straight_B.Gain6[i] = CSE1_CV3_1Straight_P.Gain6_Gain[i + 6] *
        CSE1_CV3_1Straight_B.nu_d[2] + CSE1_CV3_1Straight_B.Gain6[i];
    }

    CSE1_CV3_1Straight_B.Row1_i = cos(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.K4[0] + sin(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.K4[1];

    /* Fcn: '<S21>/Row2' */
    CSE1_CV3_1Straight_B.Row2_p = (-sin(CSE1_CV3_1Straight_B.eta_yaw)) *
      CSE1_CV3_1Straight_B.K4[0] + cos(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.K4[1];

    /* Fcn: '<S21>/Row3' */
    CSE1_CV3_1Straight_B.Row3_p = CSE1_CV3_1Straight_B.K4[2];

    /* Fcn: '<S22>/Row1' */
    CSE1_CV3_1Straight_B.Row1_g = cos(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.bias[0] + sin(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.bias[1];

    /* Fcn: '<S22>/Row2' */
    CSE1_CV3_1Straight_B.Row2_a = (-sin(CSE1_CV3_1Straight_B.eta_yaw)) *
      CSE1_CV3_1Straight_B.bias[0] + cos(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.bias[1];

    /* Fcn: '<S22>/Row3' */
    CSE1_CV3_1Straight_B.Row3_l = CSE1_CV3_1Straight_B.bias[2];

    /* Sum: '<S15>/Sum1' */
    CSE1_CV3_1Straight_B.Sum1_cn[0] = CSE1_CV3_1Straight_B.Row1_g +
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[0];
    CSE1_CV3_1Straight_B.Sum1_cn[1] = CSE1_CV3_1Straight_B.Row2_a +
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[1];
    CSE1_CV3_1Straight_B.Sum1_cn[2] = CSE1_CV3_1Straight_B.Row3_l +
      CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInpor_k[2];

    /* Sum: '<S15>/Sum8' */
    CSE1_CV3_1Straight_B.Sum8[0] = (CSE1_CV3_1Straight_B.Row1_i +
      CSE1_CV3_1Straight_B.Sum1_cn[0]) - CSE1_CV3_1Straight_B.Gain6[0];
    CSE1_CV3_1Straight_B.Sum8[1] = (CSE1_CV3_1Straight_B.Row2_p +
      CSE1_CV3_1Straight_B.Sum1_cn[1]) - CSE1_CV3_1Straight_B.Gain6[1];
    CSE1_CV3_1Straight_B.Sum8[2] = (CSE1_CV3_1Straight_B.Row3_p +
      CSE1_CV3_1Straight_B.Sum1_cn[2]) - CSE1_CV3_1Straight_B.Gain6[2];

    /* Fcn: '<S20>/Fcn' */
    CSE1_CV3_1Straight_B.x_dot = cos(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.nu_d[0] - sin(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.nu_d[1];

    /* Fcn: '<S20>/Fcn1' */
    CSE1_CV3_1Straight_B.y_dot = sin(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.nu_d[0] + cos(CSE1_CV3_1Straight_B.eta_yaw) *
      CSE1_CV3_1Straight_B.nu_d[1];

    /* Fcn: '<S20>/Fcn2' */
    CSE1_CV3_1Straight_B.psi_dot = CSE1_CV3_1Straight_B.nu_d[2];

    /* Sum: '<S15>/Sum3' */
    for (i = 0; i < 3; i++) {
      /* Gain: '<S15>/Gain3' */
      CSE1_CV3_1Straight_B.Gain3[i] = 0.0;
      CSE1_CV3_1Straight_B.Gain3[i] = CSE1_CV3_1Straight_P.Gain3_Gain[i] *
        CSE1_CV3_1Straight_B.Sum8[0] + CSE1_CV3_1Straight_B.Gain3[i];
      CSE1_CV3_1Straight_B.Gain3[i] = CSE1_CV3_1Straight_P.Gain3_Gain[i + 3] *
        CSE1_CV3_1Straight_B.Sum8[1] + CSE1_CV3_1Straight_B.Gain3[i];
      CSE1_CV3_1Straight_B.Gain3[i] = CSE1_CV3_1Straight_P.Gain3_Gain[i + 6] *
        CSE1_CV3_1Straight_B.Sum8[2] + CSE1_CV3_1Straight_B.Gain3[i];

      /* Gain: '<S15>/K11' */
      CSE1_CV3_1Straight_B.K11[i] = 0.0;
      CSE1_CV3_1Straight_B.K11[i] = CSE1_CV3_1Straight_P.K11_Gain[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[0] +
        CSE1_CV3_1Straight_B.K11[i];
      CSE1_CV3_1Straight_B.K11[i] = CSE1_CV3_1Straight_P.K11_Gain[i + 3] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[1] +
        CSE1_CV3_1Straight_B.K11[i];
      CSE1_CV3_1Straight_B.K11[i] = CSE1_CV3_1Straight_P.K11_Gain[i + 6] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[2] +
        CSE1_CV3_1Straight_B.K11[i];

      /* Gain: '<S15>/K12' */
      CSE1_CV3_1Straight_B.K12[i] = 0.0;
      CSE1_CV3_1Straight_B.K12[i] = CSE1_CV3_1Straight_P.K12_Gain[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[0] +
        CSE1_CV3_1Straight_B.K12[i];
      CSE1_CV3_1Straight_B.K12[i] = CSE1_CV3_1Straight_P.K12_Gain[i + 3] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[1] +
        CSE1_CV3_1Straight_B.K12[i];
      CSE1_CV3_1Straight_B.K12[i] = CSE1_CV3_1Straight_P.K12_Gain[i + 6] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[2] +
        CSE1_CV3_1Straight_B.K12[i];

      /* Gain: '<S15>/K2' */
      CSE1_CV3_1Straight_B.K2[i] = 0.0;
      CSE1_CV3_1Straight_B.K2[i] = CSE1_CV3_1Straight_P.K2_Gain[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[0] +
        CSE1_CV3_1Straight_B.K2[i];
      CSE1_CV3_1Straight_B.K2[i] = CSE1_CV3_1Straight_P.K2_Gain[i + 3] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[1] +
        CSE1_CV3_1Straight_B.K2[i];
      CSE1_CV3_1Straight_B.K2[i] = CSE1_CV3_1Straight_P.K2_Gain[i + 6] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[2] +
        CSE1_CV3_1Straight_B.K2[i];

      /* Gain: '<S15>/K3' */
      CSE1_CV3_1Straight_B.K3[i] = 0.0;
      CSE1_CV3_1Straight_B.K3[i] = CSE1_CV3_1Straight_P.K3_Gain[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[0] +
        CSE1_CV3_1Straight_B.K3[i];
      CSE1_CV3_1Straight_B.K3[i] = CSE1_CV3_1Straight_P.K3_Gain[i + 3] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[1] +
        CSE1_CV3_1Straight_B.K3[i];
      CSE1_CV3_1Straight_B.K3[i] = CSE1_CV3_1Straight_P.K3_Gain[i + 6] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtK11Inport1[2] +
        CSE1_CV3_1Straight_B.K3[i];

      /* Sum: '<S15>/Sum5' */
      CSE1_CV3_1Straight_B.psi_WF[i] = CSE1_CV3_1Straight_B.K11[i] +
        CSE1_CV3_1Straight_B.eta_w[i];

      /* Sum: '<S15>/Sum6' */
      CSE1_CV3_1Straight_B.Sum6[i] = (CSE1_CV3_1Straight_B.K12[i] -
        CSE1_CV3_1Straight_B.Gain2[i]) - CSE1_CV3_1Straight_B.Gain1_j[i];

      /* Gain: '<S15>/inv(T_b)' */
      CSE1_CV3_1Straight_B.invT_b[i] = 0.0;
      CSE1_CV3_1Straight_B.invT_b[i] = CSE1_CV3_1Straight_P.invT_b_Gain[i] *
        CSE1_CV3_1Straight_B.bias[0] + CSE1_CV3_1Straight_B.invT_b[i];
      CSE1_CV3_1Straight_B.invT_b[i] = CSE1_CV3_1Straight_P.invT_b_Gain[i + 3] *
        CSE1_CV3_1Straight_B.bias[1] + CSE1_CV3_1Straight_B.invT_b[i];
      CSE1_CV3_1Straight_B.invT_b[i] = CSE1_CV3_1Straight_P.invT_b_Gain[i + 6] *
        CSE1_CV3_1Straight_B.bias[2] + CSE1_CV3_1Straight_B.invT_b[i];

      /* Sum: '<S15>/Sum7' */
      CSE1_CV3_1Straight_B.Sum7[i] = CSE1_CV3_1Straight_B.K3[i] -
        CSE1_CV3_1Straight_B.invT_b[i];
    }

    CSE1_CV3_1Straight_B.Sum3_k[0] = CSE1_CV3_1Straight_B.K2[0] +
      CSE1_CV3_1Straight_B.x_dot;
    CSE1_CV3_1Straight_B.Sum3_k[1] = CSE1_CV3_1Straight_B.K2[1] +
      CSE1_CV3_1Straight_B.y_dot;
    CSE1_CV3_1Straight_B.Sum3_k[2] = CSE1_CV3_1Straight_B.K2[2] +
      CSE1_CV3_1Straight_B.psi_dot;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Reshape: '<S51>/2x2' incorporates:
       *  Constant: '<S51>/12'
       *  Constant: '<S51>/21'
       *  Constant: '<S7>/Gamma_q_Surge'
       *  Constant: '<S7>/Gamma_q_Sway'
       */
      CSE1_CV3_1Straight_B.x2[0] = CSE1_CV3_1Straight_P.Gamma_q_Surge_Value;
      CSE1_CV3_1Straight_B.x2[1] = CSE1_CV3_1Straight_P.u_Value_or;
      CSE1_CV3_1Straight_B.x2[2] = CSE1_CV3_1Straight_P.u_Value_eg;
      CSE1_CV3_1Straight_B.x2[3] = CSE1_CV3_1Straight_P.Gamma_q_Sway_Value;
    }

    /* Product: '<S52>/Product' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product_e[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_e[i] = CSE1_CV3_1Straight_B.Rpsi[i] *
        CSE1_CV3_1Straight_B.Subtract_f[0] + CSE1_CV3_1Straight_B.Product_e[i];
      CSE1_CV3_1Straight_B.Product_e[i] = CSE1_CV3_1Straight_B.Rpsi[i + 3] *
        CSE1_CV3_1Straight_B.Subtract_f[1] + CSE1_CV3_1Straight_B.Product_e[i];
      CSE1_CV3_1Straight_B.Product_e[i] = CSE1_CV3_1Straight_B.Rpsi[i + 6] *
        CSE1_CV3_1Straight_B.Subtract_f[2] + CSE1_CV3_1Straight_B.Product_e[i];
    }

    /* Sum: '<S62>/Add' */
    CSE1_CV3_1Straight_B.Add_ov[0] = CSE1_CV3_1Straight_B.Integrator2[0] +
      CSE1_CV3_1Straight_B.Product_dm[0];
    CSE1_CV3_1Straight_B.Add_ov[1] = CSE1_CV3_1Straight_B.Integrator2[1] +
      CSE1_CV3_1Straight_B.Product_dm[1];

    /* Math: '<S106>/Math Function' */
    CSE1_CV3_1Straight_B.MathFunction_ew[0] = CSE1_CV3_1Straight_B.Product_j[0];
    CSE1_CV3_1Straight_B.MathFunction_ew[1] = CSE1_CV3_1Straight_B.Product_j[1];
    CSE1_CV3_1Straight_B.MathFunction_ew[2] = CSE1_CV3_1Straight_B.Product_j[2];

    /* Product: '<S63>/Product' */
    for (i = 0; i < 3; i++) {
      tmp_6[i] = 0.0;
      tmp_0 = tmp_6[i];
      tmp_0 += CSE1_CV3_1Straight_B.MathFunction_l[3 * i] *
        CSE1_CV3_1Straight_B.MathFunction_ew[0];
      tmp_6[i] = tmp_0;
      tmp_0 = tmp_6[i];
      tmp_0 += CSE1_CV3_1Straight_B.MathFunction_l[3 * i + 1] *
        CSE1_CV3_1Straight_B.MathFunction_ew[1];
      tmp_6[i] = tmp_0;
      tmp_0 = tmp_6[i];
      tmp_0 += CSE1_CV3_1Straight_B.MathFunction_l[3 * i + 2] *
        CSE1_CV3_1Straight_B.MathFunction_ew[2];
      tmp_6[i] = tmp_0;
    }

    for (i = 0; i < 2; i++) {
      CSE1_CV3_1Straight_B.Product_au[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_au[i] =
        CSE1_CV3_1Straight_B.MatrixConcatenate_oj[3 * i] * tmp_6[0] +
        CSE1_CV3_1Straight_B.Product_au[i];
      CSE1_CV3_1Straight_B.Product_au[i] =
        CSE1_CV3_1Straight_B.MatrixConcatenate_oj[3 * i + 1] * tmp_6[1] +
        CSE1_CV3_1Straight_B.Product_au[i];
      CSE1_CV3_1Straight_B.Product_au[i] =
        CSE1_CV3_1Straight_B.MatrixConcatenate_oj[3 * i + 2] * tmp_6[2] +
        CSE1_CV3_1Straight_B.Product_au[i];

      /* Gain: '<S63>/Gain' */
      CSE1_CV3_1Straight_B.Gain_m[i] = CSE1_CV3_1Straight_P.Gain_Gain_n *
        CSE1_CV3_1Straight_B.Product_au[i];

      /* Math: '<S104>/Math Function' */
      CSE1_CV3_1Straight_B.MathFunction_m[i] = CSE1_CV3_1Straight_B.Gain_m[i];
    }

    /* Product: '<S62>/Product' */
    CSE1_CV3_1Straight_B.Product_b2[0] = 0.0;
    CSE1_CV3_1Straight_B.Product_b2[0] = CSE1_CV3_1Straight_B.x2[0] *
      CSE1_CV3_1Straight_B.MathFunction_m[0] + CSE1_CV3_1Straight_B.Product_b2[0];
    CSE1_CV3_1Straight_B.Product_b2[0] = CSE1_CV3_1Straight_B.x2[2] *
      CSE1_CV3_1Straight_B.MathFunction_m[1] + CSE1_CV3_1Straight_B.Product_b2[0];

    /* Sum: '<S62>/Add1' */
    CSE1_CV3_1Straight_B.Add1_g[0] = CSE1_CV3_1Straight_B.Integrator2[0] +
      CSE1_CV3_1Straight_B.Product_b2[0];

    /* Product: '<S62>/Product1' incorporates:
     *  Constant: '<S7>/lambda'
     */
    CSE1_CV3_1Straight_B.Product1_ln[0] = CSE1_CV3_1Straight_P.lambda_Value *
      CSE1_CV3_1Straight_B.Add1_g[0];

    /* Gain: '<S62>/Gain' */
    CSE1_CV3_1Straight_B.Gain_fx[0] = CSE1_CV3_1Straight_P.Gain_Gain_h *
      CSE1_CV3_1Straight_B.Product1_ln[0];

    /* Product: '<S62>/Product' */
    CSE1_CV3_1Straight_B.Product_b2[1] = 0.0;
    CSE1_CV3_1Straight_B.Product_b2[1] = CSE1_CV3_1Straight_B.x2[1] *
      CSE1_CV3_1Straight_B.MathFunction_m[0] + CSE1_CV3_1Straight_B.Product_b2[1];
    CSE1_CV3_1Straight_B.Product_b2[1] = CSE1_CV3_1Straight_B.x2[3] *
      CSE1_CV3_1Straight_B.MathFunction_m[1] + CSE1_CV3_1Straight_B.Product_b2[1];

    /* Sum: '<S62>/Add1' */
    CSE1_CV3_1Straight_B.Add1_g[1] = CSE1_CV3_1Straight_B.Integrator2[1] +
      CSE1_CV3_1Straight_B.Product_b2[1];

    /* Product: '<S62>/Product1' incorporates:
     *  Constant: '<S7>/lambda'
     */
    CSE1_CV3_1Straight_B.Product1_ln[1] = CSE1_CV3_1Straight_P.lambda_Value *
      CSE1_CV3_1Straight_B.Add1_g[1];

    /* Gain: '<S62>/Gain' */
    CSE1_CV3_1Straight_B.Gain_fx[1] = CSE1_CV3_1Straight_P.Gain_Gain_h *
      CSE1_CV3_1Straight_B.Product1_ln[1];
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Reshape: '<S127>/2x2' incorporates:
       *  Constant: '<S127>/12'
       *  Constant: '<S127>/21'
       *  Constant: '<S9>/Gamma_q_Surge'
       *  Constant: '<S9>/Gamma_q_Sway'
       */
      CSE1_CV3_1Straight_B.x2_g[0] = CSE1_CV3_1Straight_P.Gamma_q_Surge_Value_a;
      CSE1_CV3_1Straight_B.x2_g[1] = CSE1_CV3_1Straight_P.u_Value_pf;
      CSE1_CV3_1Straight_B.x2_g[2] = CSE1_CV3_1Straight_P.u_Value_cv;
      CSE1_CV3_1Straight_B.x2_g[3] = CSE1_CV3_1Straight_P.Gamma_q_Sway_Value_e;
    }

    /* Product: '<S128>/Product' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.Product_k[i] = 0.0;
      CSE1_CV3_1Straight_B.Product_k[i] = CSE1_CV3_1Straight_B.Rpsi_p[i] *
        CSE1_CV3_1Straight_B.Subtract_ji[0] + CSE1_CV3_1Straight_B.Product_k[i];
      CSE1_CV3_1Straight_B.Product_k[i] = CSE1_CV3_1Straight_B.Rpsi_p[i + 3] *
        CSE1_CV3_1Straight_B.Subtract_ji[1] + CSE1_CV3_1Straight_B.Product_k[i];
      CSE1_CV3_1Straight_B.Product_k[i] = CSE1_CV3_1Straight_B.Rpsi_p[i + 6] *
        CSE1_CV3_1Straight_B.Subtract_ji[2] + CSE1_CV3_1Straight_B.Product_k[i];
    }

    /* Math: '<S186>/Math Function' */
    for (i = 0; i < 3; i++) {
      CSE1_CV3_1Straight_B.MathFunction_ff[i << 1] =
        CSE1_CV3_1Straight_B.MatrixConcatenate_oj[i];
      CSE1_CV3_1Straight_B.MathFunction_ff[1 + (i << 1)] =
        CSE1_CV3_1Straight_B.MatrixConcatenate_oj[i + 3];
    }

    /* Product: '<S135>/Product2' */
    for (i = 0; i < 2; i++) {
      for (tmp_8 = 0; tmp_8 < 3; tmp_8++) {
        tmp_5[i + (tmp_8 << 1)] = 0.0;
        tmp_5[i + (tmp_8 << 1)] = tmp_5[(tmp_8 << 1) + i] +
          CSE1_CV3_1Straight_B.Rpsi_l[3 * tmp_8] *
          CSE1_CV3_1Straight_B.MathFunction_ff[i];
        tmp_5[i + (tmp_8 << 1)] = CSE1_CV3_1Straight_B.Rpsi_l[3 * tmp_8 + 1] *
          CSE1_CV3_1Straight_B.MathFunction_ff[i + 2] + tmp_5[(tmp_8 << 1) + i];
        tmp_5[i + (tmp_8 << 1)] = CSE1_CV3_1Straight_B.Rpsi_l[3 * tmp_8 + 2] *
          CSE1_CV3_1Straight_B.MathFunction_ff[i + 4] + tmp_5[(tmp_8 << 1) + i];
      }
    }

    for (i = 0; i < 2; i++) {
      CSE1_CV3_1Straight_B.Product2_f[i] = 0.0;
      CSE1_CV3_1Straight_B.Product2_f[i] = tmp_5[i] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport3[0] +
        CSE1_CV3_1Straight_B.Product2_f[i];
      CSE1_CV3_1Straight_B.Product2_f[i] = tmp_5[i + 2] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport3[1] +
        CSE1_CV3_1Straight_B.Product2_f[i];
      CSE1_CV3_1Straight_B.Product2_f[i] = tmp_5[i + 4] *
        CSE1_CV3_1Straight_B.TmpHiddenBufferAtProductInport3[2] +
        CSE1_CV3_1Straight_B.Product2_f[i];
    }

    /* Product: '<S135>/Product3' */
    CSE1_CV3_1Straight_B.Product3_a[0] = 0.0;
    CSE1_CV3_1Straight_B.Product3_a[0] = CSE1_CV3_1Straight_B.x2_g[0] *
      CSE1_CV3_1Straight_B.Product2_f[0] + CSE1_CV3_1Straight_B.Product3_a[0];
    CSE1_CV3_1Straight_B.Product3_a[0] = CSE1_CV3_1Straight_B.x2_g[2] *
      CSE1_CV3_1Straight_B.Product2_f[1] + CSE1_CV3_1Straight_B.Product3_a[0];

    /* Sum: '<S135>/Subtract' */
    CSE1_CV3_1Straight_B.Subtract_jg[0] = CSE1_CV3_1Straight_B.omega_q[0] -
      CSE1_CV3_1Straight_B.Product3_a[0];

    /* Product: '<S135>/Product1' incorporates:
     *  Constant: '<S9>/lambda'
     */
    CSE1_CV3_1Straight_B.Product1_gn[0] = CSE1_CV3_1Straight_P.lambda_Value_l *
      CSE1_CV3_1Straight_B.Subtract_jg[0];

    /* Gain: '<S135>/dot omega_q' */
    CSE1_CV3_1Straight_B.dotomega_q[0] = CSE1_CV3_1Straight_P.dotomega_q_Gain *
      CSE1_CV3_1Straight_B.Product1_gn[0];

    /* Product: '<S135>/Product3' */
    CSE1_CV3_1Straight_B.Product3_a[1] = 0.0;
    CSE1_CV3_1Straight_B.Product3_a[1] = CSE1_CV3_1Straight_B.x2_g[1] *
      CSE1_CV3_1Straight_B.Product2_f[0] + CSE1_CV3_1Straight_B.Product3_a[1];
    CSE1_CV3_1Straight_B.Product3_a[1] = CSE1_CV3_1Straight_B.x2_g[3] *
      CSE1_CV3_1Straight_B.Product2_f[1] + CSE1_CV3_1Straight_B.Product3_a[1];

    /* Sum: '<S135>/Subtract' */
    CSE1_CV3_1Straight_B.Subtract_jg[1] = CSE1_CV3_1Straight_B.omega_q[1] -
      CSE1_CV3_1Straight_B.Product3_a[1];

    /* Product: '<S135>/Product1' incorporates:
     *  Constant: '<S9>/lambda'
     */
    CSE1_CV3_1Straight_B.Product1_gn[1] = CSE1_CV3_1Straight_P.lambda_Value_l *
      CSE1_CV3_1Straight_B.Subtract_jg[1];

    /* Gain: '<S135>/dot omega_q' */
    CSE1_CV3_1Straight_B.dotomega_q[1] = CSE1_CV3_1Straight_P.dotomega_q_Gain *
      CSE1_CV3_1Straight_B.Product1_gn[1];

    /* Gain: '<S219>/eta_d Psi deg' */
    CSE1_CV3_1Straight_B.eta_dPsideg = CSE1_CV3_1Straight_P.eta_dPsideg_Gain *
      CSE1_CV3_1Straight_B.MultiportSwitch[2];

    /* Gain: '<S289>/QTM In1 FN' */
    CSE1_CV3_1Straight_B.QTMIn1FN = CSE1_CV3_1Straight_P.QTMIn1FN_Gain *
      CSE1_CV3_1Straight_B.QTMIn[0];

    /* Gain: '<S289>/QTM In2 Error' */
    CSE1_CV3_1Straight_B.QTMIn2Error = CSE1_CV3_1Straight_P.QTMIn2Error_Gain *
      CSE1_CV3_1Straight_B.QTMIn[1];
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      /* Gain: '<S289>/Battery Servo' */
      CSE1_CV3_1Straight_B.BatteryServo = CSE1_CV3_1Straight_P.BatteryServo_Gain
        * CSE1_CV3_1Straight_B.SITzAI1;

      /* Gain: '<S289>/Battery Main' */
      CSE1_CV3_1Straight_B.BatteryMain = CSE1_CV3_1Straight_P.BatteryMain_Gain *
        CSE1_CV3_1Straight_B.SITzAI2;

      /* Gain: '<S289>/Battery Bow Thruster' */
      CSE1_CV3_1Straight_B.BatteryBowThruster =
        CSE1_CV3_1Straight_P.BatteryBowThruster_Gain *
        CSE1_CV3_1Straight_B.SITzAI0;
    }

    /* Saturate: '<S299>/Saturation' */
    tmp_0 = CSE1_CV3_1Straight_B.tauSwitch[0];
    CSE1_CV3_1Straight_B.Saturation_e = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation_LowerSat_o0,
      CSE1_CV3_1Straight_P.Saturation_UpperSat_d0);

    /* Saturate: '<S299>/Saturation1' */
    tmp_0 = CSE1_CV3_1Straight_B.tauSwitch[1];
    CSE1_CV3_1Straight_B.Saturation1 = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation1_LowerSat,
      CSE1_CV3_1Straight_P.Saturation1_UpperSat);

    /* Saturate: '<S299>/Saturation2' */
    tmp_0 = CSE1_CV3_1Straight_B.tauSwitch[2];
    CSE1_CV3_1Straight_B.Saturation2 = rt_SATURATE(tmp_0,
      CSE1_CV3_1Straight_P.Saturation2_LowerSat,
      CSE1_CV3_1Straight_P.Saturation2_UpperSat);

    /* Gain: '<S299>/plant tau_surge' */
    CSE1_CV3_1Straight_B.planttau_surge =
      CSE1_CV3_1Straight_P.planttau_surge_Gain *
      CSE1_CV3_1Straight_B.Saturation_e;

    /* Gain: '<S299>/plant tau_sway' */
    CSE1_CV3_1Straight_B.planttau_sway = CSE1_CV3_1Straight_P.planttau_sway_Gain
      * CSE1_CV3_1Straight_B.Saturation1;

    /* Gain: '<S299>/plant tau_yaw' */
    CSE1_CV3_1Straight_B.planttau_yaw = CSE1_CV3_1Straight_P.planttau_yaw_Gain *
      CSE1_CV3_1Straight_B.Saturation2;

    /* Gain: '<S5>/u_1 plant' */
    CSE1_CV3_1Straight_B.u_1plant = CSE1_CV3_1Straight_P.u_1plant_Gain *
      CSE1_CV3_1Straight_B.Saturation_ay[0];

    /* Gain: '<S5>/u_2 plant' */
    CSE1_CV3_1Straight_B.u_2plant = CSE1_CV3_1Straight_P.u_2plant_Gain *
      CSE1_CV3_1Straight_B.Saturation_ay[1];

    /* Gain: '<S5>/u_3 plant' */
    CSE1_CV3_1Straight_B.u_3plant = CSE1_CV3_1Straight_P.u_3plant_Gain *
      CSE1_CV3_1Straight_B.Saturation_ay[2];

    /* Gain: '<S5>/u_4 plant' */
    CSE1_CV3_1Straight_B.u_4plant = CSE1_CV3_1Straight_P.u_4plant_Gain *
      CSE1_CV3_1Straight_B.Saturation_ay[3];

    /* Gain: '<S5>/u_5 plant' */
    CSE1_CV3_1Straight_B.u_5plant = CSE1_CV3_1Straight_P.u_5plant_Gain *
      CSE1_CV3_1Straight_B.Saturation_ay[4];

    /* Gain: '<S5>/BT power limit plant' */
    CSE1_CV3_1Straight_B.BTpowerlimitplant =
      CSE1_CV3_1Straight_P.BTpowerlimitplant_Gain *
      CSE1_CV3_1Straight_B.Saturation_ay[5];

    /* Gain: '<S5>/VSP speed plant' */
    CSE1_CV3_1Straight_B.VSPspeedplant = CSE1_CV3_1Straight_P.VSPspeedplant_Gain
      * CSE1_CV3_1Straight_B.Saturation_ay[6];

    /* Outputs for enable SubSystem: '<S5>/CSE1' incorporates:
     *  Constant: '<S5>/Enable CSE1'
     *  EnablePort: '<S291>/Enable'
     */
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M) && rtmIsMajorTimeStep
        (CSE1_CV3_1Straight_M)) {
      if (CSE1_CV3_1Straight_P.EnableCSE1_Value > 0.0) {
        if (CSE1_CV3_1Straight_DWork.CSE1_MODE == SUBSYS_DISABLED) {
          CSE1_CV3_1Straight_DWork.CSE1_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (CSE1_CV3_1Straight_DWork.CSE1_MODE == SUBSYS_ENABLED) {
          CSE1_CV3_1Straight_DWork.CSE1_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (CSE1_CV3_1Straight_DWork.CSE1_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S300>/BT_D_Gain1' */
      CSE1_CV3_1Straight_B.BT_D_Gain1 = CSE1_CV3_1Straight_P.BT_D_Gain1_Gain *
        CSE1_CV3_1Straight_B.u_5plant;

      /* Gain: '<S300>/BT_D_Gain2' */
      CSE1_CV3_1Straight_B.BT_D_Gain2 = CSE1_CV3_1Straight_P.BT_D_Gain2_Gain *
        CSE1_CV3_1Straight_B.u_5plant;

      /* Sum: '<S300>/Add' incorporates:
       *  Constant: '<S300>/BT_Power_Offset1'
       */
      CSE1_CV3_1Straight_B.Add_c = (CSE1_CV3_1Straight_B.BT_D_Gain1 +
        CSE1_CV3_1Straight_P.BT_Power_Offset1_Value) +
        CSE1_CV3_1Straight_B.BT_D_Gain2;

      /* Gain: '<S300>/BT_L_Gain1' */
      CSE1_CV3_1Straight_B.BT_L_Gain1 = CSE1_CV3_1Straight_P.BT_L_Gain1_Gain *
        CSE1_CV3_1Straight_B.BTpowerlimitplant;

      /* Gain: '<S300>/BT_L_Gain2' */
      CSE1_CV3_1Straight_B.BT_L_Gain2 = CSE1_CV3_1Straight_P.BT_L_Gain2_Gain *
        CSE1_CV3_1Straight_B.BTpowerlimitplant;

      /* Gain: '<S300>/Neg' */
      CSE1_CV3_1Straight_B.Neg = CSE1_CV3_1Straight_P.Neg_Gain *
        CSE1_CV3_1Straight_B.BTpowerlimitplant;
      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      }

      /* Sum: '<S300>/Sum1' incorporates:
       *  Constant: '<S300>/BT_Power_Offset2'
       */
      CSE1_CV3_1Straight_B.Sum1_cf = CSE1_CV3_1Straight_B.BT_L_Gain1 +
        CSE1_CV3_1Straight_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S302>/LowerRelop1' */
      CSE1_CV3_1Straight_B.LowerRelop1 = (CSE1_CV3_1Straight_B.Add_c >
        CSE1_CV3_1Straight_B.Sum1_cf);

      /* Sum: '<S300>/Sum2' incorporates:
       *  Constant: '<S300>/BT_Power_Offset3'
       */
      CSE1_CV3_1Straight_B.Sum2_b = CSE1_CV3_1Straight_B.BT_L_Gain2 +
        CSE1_CV3_1Straight_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S302>/UpperRelop' */
      CSE1_CV3_1Straight_B.UpperRelop = (CSE1_CV3_1Straight_B.Add_c <
        CSE1_CV3_1Straight_B.Sum2_b);

      /* Switch: '<S302>/Switch' */
      if (CSE1_CV3_1Straight_B.UpperRelop) {
        CSE1_CV3_1Straight_B.Switch = CSE1_CV3_1Straight_B.Sum2_b;
      } else {
        CSE1_CV3_1Straight_B.Switch = CSE1_CV3_1Straight_B.Add_c;
      }

      /* Switch: '<S302>/Switch2' */
      if (CSE1_CV3_1Straight_B.LowerRelop1) {
        CSE1_CV3_1Straight_B.Switch2 = CSE1_CV3_1Straight_B.Sum1_cf;
      } else {
        CSE1_CV3_1Straight_B.Switch2 = CSE1_CV3_1Straight_B.Switch;
      }

      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      }

      /* RelationalOperator: '<S303>/LowerRelop1' incorporates:
       *  Constant: '<S300>/Constant'
       */
      CSE1_CV3_1Straight_B.LowerRelop1_p = (CSE1_CV3_1Straight_B.u_5plant >
        CSE1_CV3_1Straight_P.Constant_Value_j3);

      /* RelationalOperator: '<S303>/UpperRelop' */
      CSE1_CV3_1Straight_B.UpperRelop_e = (CSE1_CV3_1Straight_B.u_5plant <
        CSE1_CV3_1Straight_B.Neg);

      /* Switch: '<S303>/Switch' */
      if (CSE1_CV3_1Straight_B.UpperRelop_e) {
        CSE1_CV3_1Straight_B.Switch_n = CSE1_CV3_1Straight_B.Neg;
      } else {
        CSE1_CV3_1Straight_B.Switch_n = CSE1_CV3_1Straight_B.u_5plant;
      }

      /* Switch: '<S303>/Switch2' incorporates:
       *  Constant: '<S300>/Constant'
       */
      if (CSE1_CV3_1Straight_B.LowerRelop1_p) {
        CSE1_CV3_1Straight_B.Switch2_o = CSE1_CV3_1Straight_P.Constant_Value_j3;
      } else {
        CSE1_CV3_1Straight_B.Switch2_o = CSE1_CV3_1Straight_B.Switch_n;
      }

      if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
      }

      /* RelationalOperator: '<S304>/LowerRelop1' */
      CSE1_CV3_1Straight_B.LowerRelop1_n = (CSE1_CV3_1Straight_B.u_5plant >
        CSE1_CV3_1Straight_B.BTpowerlimitplant);

      /* RelationalOperator: '<S304>/UpperRelop' incorporates:
       *  Constant: '<S300>/Constant1'
       */
      CSE1_CV3_1Straight_B.UpperRelop_j = (CSE1_CV3_1Straight_B.u_5plant <
        CSE1_CV3_1Straight_P.Constant1_Value_f);

      /* Switch: '<S304>/Switch' incorporates:
       *  Constant: '<S300>/Constant1'
       */
      if (CSE1_CV3_1Straight_B.UpperRelop_j) {
        CSE1_CV3_1Straight_B.Switch_e = CSE1_CV3_1Straight_P.Constant1_Value_f;
      } else {
        CSE1_CV3_1Straight_B.Switch_e = CSE1_CV3_1Straight_B.u_5plant;
      }

      /* Switch: '<S304>/Switch2' */
      if (CSE1_CV3_1Straight_B.LowerRelop1_n) {
        CSE1_CV3_1Straight_B.Switch2_a = CSE1_CV3_1Straight_B.BTpowerlimitplant;
      } else {
        CSE1_CV3_1Straight_B.Switch2_a = CSE1_CV3_1Straight_B.Switch_e;
      }

      /* Signum: '<S301>/Sign' */
      CSE1_CV3_1Straight_B.Sign_mc = rt_SIGNd_snf
        (CSE1_CV3_1Straight_B.VSPspeedplant);

      /* Product: '<S301>/Product1' */
      CSE1_CV3_1Straight_B.PortVPS_X = CSE1_CV3_1Straight_B.u_2plant *
        CSE1_CV3_1Straight_B.Sign_mc;

      /* Gain: '<S301>/-x' */
      CSE1_CV3_1Straight_B.PortVPS_X_d = CSE1_CV3_1Straight_P.x_Gain *
        CSE1_CV3_1Straight_B.PortVPS_X;

      /* Product: '<S301>/Product2' */
      CSE1_CV3_1Straight_B.PortVSP_Y = CSE1_CV3_1Straight_B.u_1plant *
        CSE1_CV3_1Straight_B.Sign_mc;

      /* Gain: '<S301>/-y' */
      CSE1_CV3_1Straight_B.PortVSP_Y_p = CSE1_CV3_1Straight_P.y_Gain *
        CSE1_CV3_1Straight_B.PortVSP_Y;

      /* Fcn: '<S305>/x->r' */
      CSE1_CV3_1Straight_B.xr = rt_hypot_snf(CSE1_CV3_1Straight_B.PortVPS_X_d,
        CSE1_CV3_1Straight_B.PortVSP_Y_p);

      /* Fcn: '<S305>/x->theta' */
      CSE1_CV3_1Straight_B.xtheta = rt_atan2_snf
        (CSE1_CV3_1Straight_B.PortVSP_Y_p, CSE1_CV3_1Straight_B.PortVPS_X_d);

      /* Product: '<S301>/Product3' */
      CSE1_CV3_1Straight_B.StarboardVSP_X = CSE1_CV3_1Straight_B.u_4plant *
        CSE1_CV3_1Straight_B.Sign_mc;

      /* Product: '<S301>/Product4' */
      CSE1_CV3_1Straight_B.StarboardVSP_Y = CSE1_CV3_1Straight_B.u_3plant *
        CSE1_CV3_1Straight_B.Sign_mc;

      /* Fcn: '<S306>/x->r' */
      CSE1_CV3_1Straight_B.xr_j = rt_hypot_snf
        (CSE1_CV3_1Straight_B.StarboardVSP_X,
         CSE1_CV3_1Straight_B.StarboardVSP_Y);

      /* Fcn: '<S306>/x->theta' */
      CSE1_CV3_1Straight_B.xtheta_h = rt_atan2_snf
        (CSE1_CV3_1Straight_B.StarboardVSP_Y,
         CSE1_CV3_1Straight_B.StarboardVSP_X);

      /* Gain: '<S307>/Gain' */
      CSE1_CV3_1Straight_B.Gain_e = CSE1_CV3_1Straight_P.Gain_Gain_a3 *
        CSE1_CV3_1Straight_B.xtheta;

      /* Gain: '<S308>/Gain' */
      CSE1_CV3_1Straight_B.Gain_e1 = CSE1_CV3_1Straight_P.Gain_Gain_cy *
        CSE1_CV3_1Straight_B.xtheta_h;

      /* Lookup2D: '<S301>/Servo1' */
      CSE1_CV3_1Straight_B.Servo1 = rt_Lookup2D_Normal((const real_T *)
        (&CSE1_CV3_1Straight_P.Servo1_RowIdx[0]), 3, (const real_T *)
        (&CSE1_CV3_1Straight_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&CSE1_CV3_1Straight_P.Servo1_Table[0]), (const real_T)
        CSE1_CV3_1Straight_B.PortVPS_X_d, (const real_T)
        CSE1_CV3_1Straight_B.PortVSP_Y_p);

      /* Lookup2D: '<S301>/Servo2' */
      CSE1_CV3_1Straight_B.Servo2 = rt_Lookup2D_Normal((const real_T *)
        (&CSE1_CV3_1Straight_P.Servo2_RowIdx[0]), 3, (const real_T *)
        (&CSE1_CV3_1Straight_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&CSE1_CV3_1Straight_P.Servo2_Table[0]), (const real_T)
        CSE1_CV3_1Straight_B.PortVPS_X_d, (const real_T)
        CSE1_CV3_1Straight_B.PortVSP_Y_p);

      /* Lookup2D: '<S301>/Servo3' */
      CSE1_CV3_1Straight_B.Servo3 = rt_Lookup2D_Normal((const real_T *)
        (&CSE1_CV3_1Straight_P.Servo3_RowIdx[0]), 3, (const real_T *)
        (&CSE1_CV3_1Straight_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&CSE1_CV3_1Straight_P.Servo3_Table[0]), (const real_T)
        CSE1_CV3_1Straight_B.StarboardVSP_X, (const real_T)
        CSE1_CV3_1Straight_B.StarboardVSP_Y);

      /* Lookup2D: '<S301>/Servo4' */
      CSE1_CV3_1Straight_B.Servo4 = rt_Lookup2D_Normal((const real_T *)
        (&CSE1_CV3_1Straight_P.Servo4_RowIdx[0]), 3, (const real_T *)
        (&CSE1_CV3_1Straight_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&CSE1_CV3_1Straight_P.Servo4_Table[0]), (const real_T)
        CSE1_CV3_1Straight_B.StarboardVSP_X, (const real_T)
        CSE1_CV3_1Straight_B.StarboardVSP_Y);

      /* Gain: '<S301>/VPS_Speed_Gain' */
      CSE1_CV3_1Straight_B.VPS_Speed_Gain =
        CSE1_CV3_1Straight_P.VPS_Speed_Gain_Gain *
        CSE1_CV3_1Straight_B.VSPspeedplant;

      /* Sum: '<S301>/Sum' incorporates:
       *  Constant: '<S301>/VPS_Power_Offset'
       */
      CSE1_CV3_1Straight_B.Sum_ep = CSE1_CV3_1Straight_B.VPS_Speed_Gain +
        CSE1_CV3_1Straight_P.VPS_Power_Offset_Value;

      /* Gain: '<S301>/VSPS Port' */
      CSE1_CV3_1Straight_B.VSPSPort = CSE1_CV3_1Straight_P.VSPSPort_Gain *
        CSE1_CV3_1Straight_B.Sum_ep;

      /* Gain: '<S301>/VSPS Starboard' */
      CSE1_CV3_1Straight_B.VSPSStarboard =
        CSE1_CV3_1Straight_P.VSPSStarboard_Gain * CSE1_CV3_1Straight_B.Sum_ep;
    }

    /* end of Outputs for SubSystem: '<S5>/CSE1' */

    /* RelationalOperator: '<S292>/Compare' */
    CSE1_CV3_1Straight_B.Compare_oc = (CSE1_CV3_1Straight_B.u_1plant == 0.0);

    /* RelationalOperator: '<S293>/Compare' */
    CSE1_CV3_1Straight_B.Compare_mj = (CSE1_CV3_1Straight_B.u_2plant == 0.0);

    /* RelationalOperator: '<S294>/Compare' */
    CSE1_CV3_1Straight_B.Compare_hr = (CSE1_CV3_1Straight_B.u_3plant == 0.0);

    /* RelationalOperator: '<S295>/Compare' */
    CSE1_CV3_1Straight_B.Compare_e0 = (CSE1_CV3_1Straight_B.u_4plant == 0.0);

    /* Product: '<S5>/Product' */
    CSE1_CV3_1Straight_B.Product_h0 = (uint16_T)(CSE1_CV3_1Straight_B.Compare_oc
      * CSE1_CV3_1Straight_B.Compare_mj);

    /* Trigonometry: '<S5>/trig' */
    CSE1_CV3_1Straight_B.trig = rt_atan2_snf(CSE1_CV3_1Straight_B.u_1plant,
      CSE1_CV3_1Straight_B.u_2plant);

    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/Constant'
     */
    if (CSE1_CV3_1Straight_B.Product_h0 == 0) {
      CSE1_CV3_1Straight_B.MultiportSwitch_pqq = CSE1_CV3_1Straight_B.trig;
    } else {
      CSE1_CV3_1Straight_B.MultiportSwitch_pqq =
        CSE1_CV3_1Straight_P.Constant_Value_n2;
    }

    /* Product: '<S5>/Product1' */
    CSE1_CV3_1Straight_B.Product1_lw = (uint16_T)
      (CSE1_CV3_1Straight_B.Compare_hr * CSE1_CV3_1Straight_B.Compare_e0);

    /* Trigonometry: '<S5>/trig1' */
    CSE1_CV3_1Straight_B.trig1 = rt_atan2_snf(CSE1_CV3_1Straight_B.u_3plant,
      CSE1_CV3_1Straight_B.u_4plant);

    /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    if (CSE1_CV3_1Straight_B.Product1_lw == 0) {
      CSE1_CV3_1Straight_B.MultiportSwitch1_g = CSE1_CV3_1Straight_B.trig1;
    } else {
      CSE1_CV3_1Straight_B.MultiportSwitch1_g =
        CSE1_CV3_1Straight_P.Constant1_Value_k;
    }

    /* Gain: '<S297>/Gain' */
    CSE1_CV3_1Straight_B.Gain_jh = CSE1_CV3_1Straight_P.Gain_Gain_c *
      CSE1_CV3_1Straight_B.MultiportSwitch_pqq;

    /* Gain: '<S298>/Gain' */
    CSE1_CV3_1Straight_B.Gain_g = CSE1_CV3_1Straight_P.Gain_Gain_ee *
      CSE1_CV3_1Straight_B.MultiportSwitch1_g;
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void CSE1_CV3_1Straight_update(int_T tid)
{
  {
    int32_T tmp;

    /* Update for enable SubSystem: '<S5>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S296>/Enable'
     */
    if (CSE1_CV3_1Straight_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Sum: '<S309>/Sum' */
      CSE1_CV3_1Straight_B.Sum_p[0] = CSE1_CV3_1Straight_B.planttau_surge -
        CSE1_CV3_1Straight_B.Product1_ha[0];
      CSE1_CV3_1Straight_B.Sum_p[1] = CSE1_CV3_1Straight_B.planttau_sway -
        CSE1_CV3_1Straight_B.Product1_ha[1];
      CSE1_CV3_1Straight_B.Sum_p[2] = CSE1_CV3_1Straight_B.planttau_yaw -
        CSE1_CV3_1Straight_B.Product1_ha[2];

      /* Product: '<S309>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        CSE1_CV3_1Straight_B.Product2_bi[tmp] = 0.0;
        CSE1_CV3_1Straight_B.Product2_bi[tmp] = CSE1_CV3_1Straight_B.Inverse[tmp]
          * CSE1_CV3_1Straight_B.Sum_p[0] + CSE1_CV3_1Straight_B.Product2_bi[tmp];
        CSE1_CV3_1Straight_B.Product2_bi[tmp] = CSE1_CV3_1Straight_B.Inverse[tmp
          + 3] * CSE1_CV3_1Straight_B.Sum_p[1] +
          CSE1_CV3_1Straight_B.Product2_bi[tmp];
        CSE1_CV3_1Straight_B.Product2_bi[tmp] = CSE1_CV3_1Straight_B.Inverse[tmp
          + 6] * CSE1_CV3_1Straight_B.Sum_p[2] +
          CSE1_CV3_1Straight_B.Product2_bi[tmp];
      }
    }

    /* end of Update for SubSystem: '<S5>/Linear Simulator' */

    /* Derivative Block: '<S289>/nu' */
    {
      real_T timeStampA = CSE1_CV3_1Straight_DWork.nu_RWORK.TimeStampA;
      real_T timeStampB = CSE1_CV3_1Straight_DWork.nu_RWORK.TimeStampB;
      real_T *lastBank = &CSE1_CV3_1Straight_DWork.nu_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = CSE1_CV3_1Straight_M->Timing.t[0];
      *lastBank++ = CSE1_CV3_1Straight_B.mm2mx;
      *lastBank++ = CSE1_CV3_1Straight_B.mm2my;
      *lastBank++ = CSE1_CV3_1Straight_B.mm2mz;
      *lastBank++ = CSE1_CV3_1Straight_B.d2rroll;
      *lastBank++ = CSE1_CV3_1Straight_B.d2rpitch;
      *lastBank++ = CSE1_CV3_1Straight_B.d2ryaw;
    }

    /* Update for enable SubSystem: '<S2>/Path-following' incorporates:
     *  Update for EnablePort: '<S220>/Enable'
     */
    if (CSE1_CV3_1Straight_DWork.Pathfollowing_MODE == SUBSYS_ENABLED) {
      /* Derivative Block: '<S224>/Derivative' */
      {
        real_T timeStampA = CSE1_CV3_1Straight_DWork.Derivative_RWORK.TimeStampA;
        real_T timeStampB = CSE1_CV3_1Straight_DWork.Derivative_RWORK.TimeStampB;
        real_T *lastBank = &CSE1_CV3_1Straight_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA != rtInf) {
          if (timeStampB == rtInf) {
            lastBank += 2;
          } else if (timeStampA >= timeStampB) {
            lastBank += 2;
          }
        }

        *lastBank++ = CSE1_CV3_1Straight_M->Timing.t[0];
        *lastBank++ = CSE1_CV3_1Straight_P.u_d_Value;
      }
    }

    /* end of Update for SubSystem: '<S2>/Path-following' */
    if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
    }
  }

  if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
    rt_ertODEUpdateContinuousStates(&CSE1_CV3_1Straight_M->solverInfo);
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
  if (!(++CSE1_CV3_1Straight_M->Timing.clockTick0))
    ++CSE1_CV3_1Straight_M->Timing.clockTickH0;
  CSE1_CV3_1Straight_M->Timing.t[0] = CSE1_CV3_1Straight_M->Timing.clockTick0 *
    CSE1_CV3_1Straight_M->Timing.stepSize0 +
    CSE1_CV3_1Straight_M->Timing.clockTickH0 *
    CSE1_CV3_1Straight_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(CSE1_CV3_1Straight_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++CSE1_CV3_1Straight_M->Timing.clockTick1))
      ++CSE1_CV3_1Straight_M->Timing.clockTickH1;
    CSE1_CV3_1Straight_M->Timing.t[1] = CSE1_CV3_1Straight_M->Timing.clockTick1 *
      CSE1_CV3_1Straight_M->Timing.stepSize1 +
      CSE1_CV3_1Straight_M->Timing.clockTickH1 *
      CSE1_CV3_1Straight_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void CSE1_CV3_1Straight_derivatives(void)
{
  {
    int32_T tmp;

    /* Derivatives for enable SubSystem: '<S5>/Linear Simulator' */
    if (CSE1_CV3_1Straight_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Sum: '<S309>/Sum' */
      CSE1_CV3_1Straight_B.Sum_p[0] = CSE1_CV3_1Straight_B.planttau_surge -
        CSE1_CV3_1Straight_B.Product1_ha[0];
      CSE1_CV3_1Straight_B.Sum_p[1] = CSE1_CV3_1Straight_B.planttau_sway -
        CSE1_CV3_1Straight_B.Product1_ha[1];
      CSE1_CV3_1Straight_B.Sum_p[2] = CSE1_CV3_1Straight_B.planttau_yaw -
        CSE1_CV3_1Straight_B.Product1_ha[2];

      /* Product: '<S309>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        CSE1_CV3_1Straight_B.Product2_bi[tmp] = 0.0;
        CSE1_CV3_1Straight_B.Product2_bi[tmp] = CSE1_CV3_1Straight_B.Inverse[tmp]
          * CSE1_CV3_1Straight_B.Sum_p[0] + CSE1_CV3_1Straight_B.Product2_bi[tmp];
        CSE1_CV3_1Straight_B.Product2_bi[tmp] = CSE1_CV3_1Straight_B.Inverse[tmp
          + 3] * CSE1_CV3_1Straight_B.Sum_p[1] +
          CSE1_CV3_1Straight_B.Product2_bi[tmp];
        CSE1_CV3_1Straight_B.Product2_bi[tmp] = CSE1_CV3_1Straight_B.Inverse[tmp
          + 6] * CSE1_CV3_1Straight_B.Sum_p[2] +
          CSE1_CV3_1Straight_B.Product2_bi[tmp];
      }

      /* Integrator Block: '<S309>/Integrator' */
      {
        if (CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_cx[0] =
            CSE1_CV3_1Straight_B.Product2_bi[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_cx[0] =
            0.0;
        }

        if (CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_cx[1] =
            CSE1_CV3_1Straight_B.Product2_bi[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_cx[1] =
            0.0;
        }

        if (CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_cx[2] =
            CSE1_CV3_1Straight_B.Product2_bi[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_cx[2] =
            0.0;
        }
      }

      /* Integrator Block: '<S309>/Integrator1' */
      {
        if (CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE_a[0] =
            CSE1_CV3_1Straight_B.Product3_j[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE_a[0] =
            0.0;
        }

        if (CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE_a[1] =
            CSE1_CV3_1Straight_B.Product3_j[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE_a[1] =
            0.0;
        }

        if (CSE1_CV3_1Straight_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE_a[2] =
            CSE1_CV3_1Straight_B.Product3_j[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_CSE1_CV3_1Stra *)
            CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE_a[2] =
            0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_CSE1_CV3_1Stra *)
                CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_cx[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S5>/Linear Simulator' */

    /* TransferFcn Block: '<S219>/Transfer Fcn' */
    {
      ((StateDerivatives_CSE1_CV3_1Stra *)
        CSE1_CV3_1Straight_M->ModelData.derivs)->TransferFcn_CSTATE =
        CSE1_CV3_1Straight_P.x_d_Value;
      ((StateDerivatives_CSE1_CV3_1Stra *)
        CSE1_CV3_1Straight_M->ModelData.derivs)->TransferFcn_CSTATE +=
        (CSE1_CV3_1Straight_P.TransferFcn_A)*
        CSE1_CV3_1Straight_X.TransferFcn_CSTATE;
    }

    /* TransferFcn Block: '<S219>/Transfer Fcn1' */
    {
      ((StateDerivatives_CSE1_CV3_1Stra *)
        CSE1_CV3_1Straight_M->ModelData.derivs)->TransferFcn1_CSTATE =
        CSE1_CV3_1Straight_P.y_d_Value;
      ((StateDerivatives_CSE1_CV3_1Stra *)
        CSE1_CV3_1Straight_M->ModelData.derivs)->TransferFcn1_CSTATE +=
        (CSE1_CV3_1Straight_P.TransferFcn1_A)*
        CSE1_CV3_1Straight_X.TransferFcn1_CSTATE;
    }

    /* TransferFcn Block: '<S219>/Transfer Fcn2' */
    {
      ((StateDerivatives_CSE1_CV3_1Stra *)
        CSE1_CV3_1Straight_M->ModelData.derivs)->TransferFcn2_CSTATE =
        CSE1_CV3_1Straight_B.Gain1;
      ((StateDerivatives_CSE1_CV3_1Stra *)
        CSE1_CV3_1Straight_M->ModelData.derivs)->TransferFcn2_CSTATE +=
        (CSE1_CV3_1Straight_P.TransferFcn2_A)*
        CSE1_CV3_1Straight_X.TransferFcn2_CSTATE;
    }

    /* Integrator Block: '<S62>/Integrator' */
    {
      if (CSE1_CV3_1Straight_P.Resetq_Value== 0.0) {
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE[0] =
          CSE1_CV3_1Straight_B.Add_ov[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE[0] = 0.0;
      }

      if (CSE1_CV3_1Straight_P.Resetq_Value== 0.0) {
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE[1] =
          CSE1_CV3_1Straight_B.Add_ov[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE[1] = 0.0;
      }
    }

    /* Integrator Block: '<S135>/Integrator' */
    {
      if (CSE1_CV3_1Straight_P.Resetq_Value_d== 0.0) {
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_g[0] =
          CSE1_CV3_1Straight_B.Add_po[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_g[0] = 0.0;
      }

      if (CSE1_CV3_1Straight_P.Resetq_Value_d== 0.0) {
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_g[1] =
          CSE1_CV3_1Straight_B.Add_po[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_g[1] = 0.0;
      }
    }

    /* Integrator Block: '<S62>/Integrator1' */
    {
      if (CSE1_CV3_1Straight_P.Resets_Value== 0.0) {
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE =
          CSE1_CV3_1Straight_B.Subtract_g;
      } else {
        /* level reset is active*/
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE = 0.0;
      }
    }

    /* Integrator Block: '<S135>/Integrator1' */
    {
      if (CSE1_CV3_1Straight_P.Resets_Value_c== 0.0) {
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE_g =
          CSE1_CV3_1Straight_B.Subtract_g;
      } else {
        /* level reset is active*/
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator1_CSTATE_g = 0.0;
      }
    }

    /* Derivatives for Integrator: '<S15>/Integrator' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator_CSTATE_p[0] = CSE1_CV3_1Straight_B.Sum3_k[0];
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator_CSTATE_p[1] = CSE1_CV3_1Straight_B.Sum3_k[1];
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator_CSTATE_p[2] = CSE1_CV3_1Straight_B.Sum3_k[2];

    /* Integrator Block: '<S14>/Integrator' */
    {
      if (CSE1_CV3_1Straight_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_c[0] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtKpInport1[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_c[0] = 0.0;
      }

      if (CSE1_CV3_1Straight_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_c[1] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtKpInport1[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_c[1] = 0.0;
      }

      if (CSE1_CV3_1Straight_P.Reset_DP_integrator_Value== 0.0) {
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_c[2] =
          CSE1_CV3_1Straight_B.TmpHiddenBufferAtKpInport1[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_CSE1_CV3_1Stra *)
          CSE1_CV3_1Straight_M->ModelData.derivs)->Integrator_CSTATE_c[2] = 0.0;
      }
    }

    /* Derivatives for Integrator: '<S15>/Integrator4' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator4_CSTATE[0] = CSE1_CV3_1Straight_B.Gain3[0];

    /* Derivatives for Integrator: '<S52>/Integrator' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator_CSTATE_k[0] = CSE1_CV3_1Straight_B.Product_e[0];

    /* Derivatives for Integrator: '<S15>/Integrator4' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator4_CSTATE[1] = CSE1_CV3_1Straight_B.Gain3[1];

    /* Derivatives for Integrator: '<S52>/Integrator' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator_CSTATE_k[1] = CSE1_CV3_1Straight_B.Product_e[1];

    /* Derivatives for Integrator: '<S15>/Integrator4' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator4_CSTATE[2] = CSE1_CV3_1Straight_B.Gain3[2];

    /* Derivatives for Integrator: '<S52>/Integrator' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator_CSTATE_k[2] = CSE1_CV3_1Straight_B.Product_e[2];

    /* Derivatives for Integrator: '<S62>/Integrator2' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator2_CSTATE[0] = CSE1_CV3_1Straight_B.Gain_fx[0];
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator2_CSTATE[1] = CSE1_CV3_1Straight_B.Gain_fx[1];

    /* Derivatives for Integrator: '<S9>/zeta' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->zeta_CSTATE[0] = CSE1_CV3_1Straight_B.Product_k[0];
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->zeta_CSTATE[1] = CSE1_CV3_1Straight_B.Product_k[1];
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->zeta_CSTATE[2] = CSE1_CV3_1Straight_B.Product_k[2];

    /* Derivatives for Integrator: '<S135>/omega_q' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->omega_q_CSTATE[0] = CSE1_CV3_1Straight_B.dotomega_q[0];
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->omega_q_CSTATE[1] = CSE1_CV3_1Straight_B.dotomega_q[1];

    /* Derivatives for Integrator: '<S15>/Integrator1' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator1_CSTATE_d[0] = CSE1_CV3_1Straight_B.Sum6[0];

    /* Derivatives for Integrator: '<S15>/Integrator2' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator2_CSTATE_e[0] = CSE1_CV3_1Straight_B.psi_WF[0];

    /* Derivatives for Integrator: '<S15>/Integrator3' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator3_CSTATE[0] = CSE1_CV3_1Straight_B.Sum7[0];

    /* Derivatives for Integrator: '<S15>/Integrator1' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator1_CSTATE_d[1] = CSE1_CV3_1Straight_B.Sum6[1];

    /* Derivatives for Integrator: '<S15>/Integrator2' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator2_CSTATE_e[1] = CSE1_CV3_1Straight_B.psi_WF[1];

    /* Derivatives for Integrator: '<S15>/Integrator3' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator3_CSTATE[1] = CSE1_CV3_1Straight_B.Sum7[1];

    /* Derivatives for Integrator: '<S15>/Integrator1' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator1_CSTATE_d[2] = CSE1_CV3_1Straight_B.Sum6[2];

    /* Derivatives for Integrator: '<S15>/Integrator2' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator2_CSTATE_e[2] = CSE1_CV3_1Straight_B.psi_WF[2];

    /* Derivatives for Integrator: '<S15>/Integrator3' */
    ((StateDerivatives_CSE1_CV3_1Stra *) CSE1_CV3_1Straight_M->ModelData.derivs
      )->Integrator3_CSTATE[2] = CSE1_CV3_1Straight_B.Sum7[2];
  }
}

/* Model initialize function */
void CSE1_CV3_1Straight_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  CSE1_CV3_1Straight_P.Constant_Value_n2 = rtNaN;
  CSE1_CV3_1Straight_P.Constant1_Value_k = rtNaN;

  /* initialize real-time model */
  (void) memset((void *)CSE1_CV3_1Straight_M,0,
                sizeof(RT_MODEL_CSE1_CV3_1Straight));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&CSE1_CV3_1Straight_M->solverInfo,
                          &CSE1_CV3_1Straight_M->Timing.simTimeStep);
    rtsiSetTPtr(&CSE1_CV3_1Straight_M->solverInfo, &rtmGetTPtr
                (CSE1_CV3_1Straight_M));
    rtsiSetStepSizePtr(&CSE1_CV3_1Straight_M->solverInfo,
                       &CSE1_CV3_1Straight_M->Timing.stepSize0);
    rtsiSetdXPtr(&CSE1_CV3_1Straight_M->solverInfo,
                 &CSE1_CV3_1Straight_M->ModelData.derivs);
    rtsiSetContStatesPtr(&CSE1_CV3_1Straight_M->solverInfo,
                         &CSE1_CV3_1Straight_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&CSE1_CV3_1Straight_M->solverInfo,
      &CSE1_CV3_1Straight_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&CSE1_CV3_1Straight_M->solverInfo, (&rtmGetErrorStatus
                           (CSE1_CV3_1Straight_M)));
    rtsiSetRTModelPtr(&CSE1_CV3_1Straight_M->solverInfo, CSE1_CV3_1Straight_M);
  }

  rtsiSetSimTimeStep(&CSE1_CV3_1Straight_M->solverInfo, MAJOR_TIME_STEP);
  CSE1_CV3_1Straight_M->ModelData.intgData.y =
    CSE1_CV3_1Straight_M->ModelData.odeY;
  CSE1_CV3_1Straight_M->ModelData.intgData.f[0] =
    CSE1_CV3_1Straight_M->ModelData.odeF[0];
  CSE1_CV3_1Straight_M->ModelData.intgData.f[1] =
    CSE1_CV3_1Straight_M->ModelData.odeF[1];
  CSE1_CV3_1Straight_M->ModelData.intgData.f[2] =
    CSE1_CV3_1Straight_M->ModelData.odeF[2];
  CSE1_CV3_1Straight_M->ModelData.intgData.f[3] =
    CSE1_CV3_1Straight_M->ModelData.odeF[3];
  CSE1_CV3_1Straight_M->ModelData.contStates = ((real_T *) &CSE1_CV3_1Straight_X);
  rtsiSetSolverData(&CSE1_CV3_1Straight_M->solverInfo, (void *)
                    &CSE1_CV3_1Straight_M->ModelData.intgData);
  rtsiSetSolverName(&CSE1_CV3_1Straight_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = CSE1_CV3_1Straight_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    CSE1_CV3_1Straight_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    CSE1_CV3_1Straight_M->Timing.sampleTimes =
      (&CSE1_CV3_1Straight_M->Timing.sampleTimesArray[0]);
    CSE1_CV3_1Straight_M->Timing.offsetTimes =
      (&CSE1_CV3_1Straight_M->Timing.offsetTimesArray[0]);

    /* task periods */
    CSE1_CV3_1Straight_M->Timing.sampleTimes[0] = (0.0);
    CSE1_CV3_1Straight_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    CSE1_CV3_1Straight_M->Timing.offsetTimes[0] = (0.0);
    CSE1_CV3_1Straight_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(CSE1_CV3_1Straight_M, &CSE1_CV3_1Straight_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = CSE1_CV3_1Straight_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    CSE1_CV3_1Straight_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(CSE1_CV3_1Straight_M, -1);
  CSE1_CV3_1Straight_M->Timing.stepSize0 = 0.1;
  CSE1_CV3_1Straight_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(CSE1_CV3_1Straight_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    CSE1_CV3_1Straight_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(CSE1_CV3_1Straight_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(CSE1_CV3_1Straight_M->rtwLogInfo, (NULL));
    rtliSetLogT(CSE1_CV3_1Straight_M->rtwLogInfo, "");
    rtliSetLogX(CSE1_CV3_1Straight_M->rtwLogInfo, "");
    rtliSetLogXFinal(CSE1_CV3_1Straight_M->rtwLogInfo, "");
    rtliSetSigLog(CSE1_CV3_1Straight_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(CSE1_CV3_1Straight_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(CSE1_CV3_1Straight_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(CSE1_CV3_1Straight_M->rtwLogInfo, 0);
    rtliSetLogDecimation(CSE1_CV3_1Straight_M->rtwLogInfo, 1);
    rtliSetLogY(CSE1_CV3_1Straight_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(CSE1_CV3_1Straight_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(CSE1_CV3_1Straight_M->rtwLogInfo, (NULL));
  }

  CSE1_CV3_1Straight_M->solverInfoPtr = (&CSE1_CV3_1Straight_M->solverInfo);
  CSE1_CV3_1Straight_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&CSE1_CV3_1Straight_M->solverInfo, 0.1);
  rtsiSetSolverMode(&CSE1_CV3_1Straight_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  CSE1_CV3_1Straight_M->ModelData.blockIO = ((void *) &CSE1_CV3_1Straight_B);
  (void) memset(((void *) &CSE1_CV3_1Straight_B),0,
                sizeof(BlockIO_CSE1_CV3_1Straight));

  /* parameters */
  CSE1_CV3_1Straight_M->ModelData.defaultParam = ((real_T *)
    &CSE1_CV3_1Straight_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &CSE1_CV3_1Straight_X;
    CSE1_CV3_1Straight_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_CSE1_CV3_1Stra));
  }

  /* states (dwork) */
  CSE1_CV3_1Straight_M->Work.dwork = ((void *) &CSE1_CV3_1Straight_DWork);
  (void) memset((void *)&CSE1_CV3_1Straight_DWork, 0,
                sizeof(D_Work_CSE1_CV3_1Straight));
  CSE1_CV3_1Straig_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  CSE1_CV3_1Straig_PrevZCSigState.Integrator_Reset_ZCE_o = UNINITIALIZED_ZCSIG;
  CSE1_CV3_1Straig_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  CSE1_CV3_1Straig_PrevZCSigState.Integrator1_Reset_ZCE_m = UNINITIALIZED_ZCSIG;
  CSE1_CV3_1Straig_PrevZCSigState.Integrator_Reset_ZCE_m = UNINITIALIZED_ZCSIG;
  CSE1_CV3_1Straig_PrevZCSigState.Integrator_Reset_ZCE_p = UNINITIALIZED_ZCSIG;
  CSE1_CV3_1Straig_PrevZCSigState.Integrator1_Reset_ZCE_j = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void CSE1_CV3_1Straight_terminate(void)
{
  /* ToFile Block: '<Root>/To File' */
  {
    FILE *fp = (FILE *) CSE1_CV3_1Straight_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error closing MAT-file CSE1_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error reopening MAT-file CSE1_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 24,
           CSE1_CV3_1Straight_DWork.ToFile_IWORK.Count, "cse1_data")) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error writing header for cse1_data to MAT-file CSE1_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error closing MAT-file CSE1_data.mat");
        return;
      }

      CSE1_CV3_1Straight_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* ToFile Block: '<S6>/To File' */
  {
    FILE *fp = (FILE *) CSE1_CV3_1Straight_DWork.ToFile_PWORK_a.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_data_eta_w.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error closing MAT-file CSE1_data_eta_w.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error reopening MAT-file CSE1_data_eta_w.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4,
           CSE1_CV3_1Straight_DWork.ToFile_IWORK_l.Count, "cse1_data")) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error writing header for cse1_data to MAT-file CSE1_data_eta_w.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error closing MAT-file CSE1_data_eta_w.mat");
        return;
      }

      CSE1_CV3_1Straight_DWork.ToFile_PWORK_a.FilePtr = (NULL);
    }
  }

  /* ToFile Block: '<S14>/To File' */
  {
    FILE *fp = (FILE *) CSE1_CV3_1Straight_DWork.ToFile_PWORK_c.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "CSE1_data_reg_error.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error closing MAT-file CSE1_data_reg_error.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error reopening MAT-file CSE1_data_reg_error.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4,
           CSE1_CV3_1Straight_DWork.ToFile_IWORK_e.Count, "cse1_data_reg_error"))
      {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error writing header for cse1_data_reg_error to MAT-file CSE1_data_reg_error.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                          "Error closing MAT-file CSE1_data_reg_error.mat");
        return;
      }

      CSE1_CV3_1Straight_DWork.ToFile_PWORK_c.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  CSE1_CV3_1Straight_output(tid);
}

void MdlUpdate(int_T tid)
{
  CSE1_CV3_1Straight_update(tid);
}

void MdlInitializeSizes(void)
{
  CSE1_CV3_1Straight_M->Sizes.numContStates = (43);/* Number of continuous states */
  CSE1_CV3_1Straight_M->Sizes.numY = (0);/* Number of model outputs */
  CSE1_CV3_1Straight_M->Sizes.numU = (0);/* Number of model inputs */
  CSE1_CV3_1Straight_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  CSE1_CV3_1Straight_M->Sizes.numSampTimes = (2);/* Number of sample times */
  CSE1_CV3_1Straight_M->Sizes.numBlocks = (1437);/* Number of blocks */
  CSE1_CV3_1Straight_M->Sizes.numBlockIO = (983);/* Number of block outputs */
  CSE1_CV3_1Straight_M->Sizes.numBlockPrms = (2002);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* Derivative Block: '<S289>/nu' */
  CSE1_CV3_1Straight_DWork.nu_RWORK.TimeStampA = rtInf;
  CSE1_CV3_1Straight_DWork.nu_RWORK.TimeStampB = rtInf;

  /* TransferFcn Block: '<S219>/Transfer Fcn' */
  CSE1_CV3_1Straight_X.TransferFcn_CSTATE = 0.0;

  /* TransferFcn Block: '<S219>/Transfer Fcn1' */
  CSE1_CV3_1Straight_X.TransferFcn1_CSTATE = 0.0;

  /* TransferFcn Block: '<S219>/Transfer Fcn2' */
  CSE1_CV3_1Straight_X.TransferFcn2_CSTATE = 0.0;

  /* Integrator Block: '<S62>/Integrator' */
  if (rtmIsFirstInitCond(CSE1_CV3_1Straight_M)) {
    CSE1_CV3_1Straight_X.Integrator_CSTATE[0] = 0.0;
    CSE1_CV3_1Straight_X.Integrator_CSTATE[1] = 0.0;
  }

  CSE1_CV3_1Straight_DWork.Integrator_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S135>/Integrator' */
  if (rtmIsFirstInitCond(CSE1_CV3_1Straight_M)) {
    CSE1_CV3_1Straight_X.Integrator_CSTATE_g[0] = 0.0;
    CSE1_CV3_1Straight_X.Integrator_CSTATE_g[1] = 0.0;
  }

  CSE1_CV3_1Straight_DWork.Integrator_IWORK_j.IcNeedsLoading = 1;

  /* Integrator Block: '<S62>/Integrator1' */
  if (rtmIsFirstInitCond(CSE1_CV3_1Straight_M)) {
    CSE1_CV3_1Straight_X.Integrator1_CSTATE = 0.0;
  }

  CSE1_CV3_1Straight_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S135>/Integrator1' */
  if (rtmIsFirstInitCond(CSE1_CV3_1Straight_M)) {
    CSE1_CV3_1Straight_X.Integrator1_CSTATE_g = 0.0;
  }

  CSE1_CV3_1Straight_DWork.Integrator1_IWORK_h.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<S15>/Integrator' */
  CSE1_CV3_1Straight_X.Integrator_CSTATE_p[0] =
    CSE1_CV3_1Straight_P.Integrator_IC;
  CSE1_CV3_1Straight_X.Integrator_CSTATE_p[1] =
    CSE1_CV3_1Straight_P.Integrator_IC;
  CSE1_CV3_1Straight_X.Integrator_CSTATE_p[2] =
    CSE1_CV3_1Straight_P.Integrator_IC;

  /* Integrator Block: '<S14>/Integrator' */
  CSE1_CV3_1Straight_X.Integrator_CSTATE_c[0] =
    CSE1_CV3_1Straight_P.Integrator_IC_g;
  CSE1_CV3_1Straight_X.Integrator_CSTATE_c[1] =
    CSE1_CV3_1Straight_P.Integrator_IC_g;
  CSE1_CV3_1Straight_X.Integrator_CSTATE_c[2] =
    CSE1_CV3_1Straight_P.Integrator_IC_g;

  /* InitializeConditions for Integrator: '<S15>/Integrator4' */
  CSE1_CV3_1Straight_X.Integrator4_CSTATE[0] =
    CSE1_CV3_1Straight_P.Integrator4_IC;

  /* InitializeConditions for Integrator: '<S52>/Integrator' */
  CSE1_CV3_1Straight_X.Integrator_CSTATE_k[0] =
    CSE1_CV3_1Straight_P.Integrator_IC_b[0];

  /* InitializeConditions for Integrator: '<S15>/Integrator4' */
  CSE1_CV3_1Straight_X.Integrator4_CSTATE[1] =
    CSE1_CV3_1Straight_P.Integrator4_IC;

  /* InitializeConditions for Integrator: '<S52>/Integrator' */
  CSE1_CV3_1Straight_X.Integrator_CSTATE_k[1] =
    CSE1_CV3_1Straight_P.Integrator_IC_b[1];

  /* InitializeConditions for Integrator: '<S15>/Integrator4' */
  CSE1_CV3_1Straight_X.Integrator4_CSTATE[2] =
    CSE1_CV3_1Straight_P.Integrator4_IC;

  /* InitializeConditions for Integrator: '<S52>/Integrator' */
  CSE1_CV3_1Straight_X.Integrator_CSTATE_k[2] =
    CSE1_CV3_1Straight_P.Integrator_IC_b[2];

  /* InitializeConditions for Integrator: '<S62>/Integrator2' */
  CSE1_CV3_1Straight_X.Integrator2_CSTATE[0] =
    CSE1_CV3_1Straight_P.Integrator2_IC;
  CSE1_CV3_1Straight_X.Integrator2_CSTATE[1] =
    CSE1_CV3_1Straight_P.Integrator2_IC;

  /* InitializeConditions for Integrator: '<S9>/zeta' */
  CSE1_CV3_1Straight_X.zeta_CSTATE[0] = CSE1_CV3_1Straight_P.zeta_IC;
  CSE1_CV3_1Straight_X.zeta_CSTATE[1] = CSE1_CV3_1Straight_P.zeta_IC;
  CSE1_CV3_1Straight_X.zeta_CSTATE[2] = CSE1_CV3_1Straight_P.zeta_IC;

  /* InitializeConditions for Integrator: '<S135>/omega_q' */
  CSE1_CV3_1Straight_X.omega_q_CSTATE[0] = CSE1_CV3_1Straight_P.omega_q_IC;
  CSE1_CV3_1Straight_X.omega_q_CSTATE[1] = CSE1_CV3_1Straight_P.omega_q_IC;

  /* InitializeConditions for Integrator: '<S15>/Integrator1' */
  CSE1_CV3_1Straight_X.Integrator1_CSTATE_d[0] =
    CSE1_CV3_1Straight_P.Integrator1_IC;

  /* InitializeConditions for Integrator: '<S15>/Integrator2' */
  CSE1_CV3_1Straight_X.Integrator2_CSTATE_e[0] =
    CSE1_CV3_1Straight_P.Integrator2_IC_g;

  /* InitializeConditions for Integrator: '<S15>/Integrator3' */
  CSE1_CV3_1Straight_X.Integrator3_CSTATE[0] =
    CSE1_CV3_1Straight_P.Integrator3_IC;

  /* InitializeConditions for Integrator: '<S15>/Integrator1' */
  CSE1_CV3_1Straight_X.Integrator1_CSTATE_d[1] =
    CSE1_CV3_1Straight_P.Integrator1_IC;

  /* InitializeConditions for Integrator: '<S15>/Integrator2' */
  CSE1_CV3_1Straight_X.Integrator2_CSTATE_e[1] =
    CSE1_CV3_1Straight_P.Integrator2_IC_g;

  /* InitializeConditions for Integrator: '<S15>/Integrator3' */
  CSE1_CV3_1Straight_X.Integrator3_CSTATE[1] =
    CSE1_CV3_1Straight_P.Integrator3_IC;

  /* InitializeConditions for Integrator: '<S15>/Integrator1' */
  CSE1_CV3_1Straight_X.Integrator1_CSTATE_d[2] =
    CSE1_CV3_1Straight_P.Integrator1_IC;

  /* InitializeConditions for Integrator: '<S15>/Integrator2' */
  CSE1_CV3_1Straight_X.Integrator2_CSTATE_e[2] =
    CSE1_CV3_1Straight_P.Integrator2_IC_g;

  /* InitializeConditions for Integrator: '<S15>/Integrator3' */
  CSE1_CV3_1Straight_X.Integrator3_CSTATE[2] =
    CSE1_CV3_1Straight_P.Integrator3_IC;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(CSE1_CV3_1Straight_M)) {
    rtmSetFirstInitCond(CSE1_CV3_1Straight_M, 0);
  }
}

void MdlStart(void)
{
  /* Start for enable SubSystem: '<S5>/Linear Simulator' */
  CSE1_CV3_1Straight_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

  /* Start for Constant: '<S311>/psi_0' */
  CSE1_CV3_1Straight_B.psi_0 = CSE1_CV3_1Straight_P.psi_0_Value;

  /* Start for Constant: '<S311>/x_0' */
  CSE1_CV3_1Straight_B.x_0 = CSE1_CV3_1Straight_P.x_0_Value;

  /* Start for Constant: '<S311>/y_0' */
  CSE1_CV3_1Straight_B.y_0 = CSE1_CV3_1Straight_P.y_0_Value;

  /* Start for Constant: '<S312>/r_0' */
  CSE1_CV3_1Straight_B.r_0 = CSE1_CV3_1Straight_P.r_0_Value;

  /* Start for Constant: '<S312>/u_0' */
  CSE1_CV3_1Straight_B.u_0 = CSE1_CV3_1Straight_P.u_0_Value;

  /* Start for Constant: '<S312>/v_0' */
  CSE1_CV3_1Straight_B.v_0 = CSE1_CV3_1Straight_P.v_0_Value;

  /* Create Identity Matrix for Block: '<S313>/Inverse' */
  {
    int_T i;
    real_T *dWork = &CSE1_CV3_1Straight_DWork.Inverse_DWORK4[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &CSE1_CV3_1Straight_DWork.Inverse_DWORK4[0];
    while (dWork < &CSE1_CV3_1Straight_DWork.Inverse_DWORK4[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  /* Integrator Block: '<S309>/Integrator' */
  if (rtmIsFirstInitCond(CSE1_CV3_1Straight_M)) {
    CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[0] = 0.0;
    CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[1] = 0.0;
    CSE1_CV3_1Straight_X.Integrator_CSTATE_cx[2] = 0.0;
  }

  CSE1_CV3_1Straight_DWork.Integrator_IWORK_c.IcNeedsLoading = 1;

  /* Integrator Block: '<S309>/Integrator1' */
  if (rtmIsFirstInitCond(CSE1_CV3_1Straight_M)) {
    CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[0] = 0.0;
    CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[1] = 0.0;
    CSE1_CV3_1Straight_X.Integrator1_CSTATE_a[2] = 0.0;
  }

  CSE1_CV3_1Straight_DWork.Integrator1_IWORK_f.IcNeedsLoading = 1;

  /* end of Start for SubSystem: '<S5>/Linear Simulator' */

  /* Start for Constant: '<S105>/q_x_0' */
  CSE1_CV3_1Straight_B.q_x_0 = CSE1_CV3_1Straight_P.q_x_0_Value;

  /* Start for Constant: '<S105>/q_y_0' */
  CSE1_CV3_1Straight_B.q_y_0 = CSE1_CV3_1Straight_P.q_y_0_Value;

  /* Start for Constant: '<S187>/q_x_0' */
  CSE1_CV3_1Straight_B.q_x_0_c = CSE1_CV3_1Straight_P.q_x_0_Value_n;

  /* Start for Constant: '<S187>/q_y_0' */
  CSE1_CV3_1Straight_B.q_y_0_p = CSE1_CV3_1Straight_P.q_y_0_Value_n;

  /* Start for Constant: '<S62>/s_0' */
  CSE1_CV3_1Straight_B.s_0 = CSE1_CV3_1Straight_P.s_0_Value;

  /* Start for Constant: '<S135>/s_0' */
  CSE1_CV3_1Straight_B.s_0_d = CSE1_CV3_1Straight_P.s_0_Value_c;

  /* Start for enable SubSystem: '<S2>/Path-following' */
  CSE1_CV3_1Straight_DWork.Pathfollowing_MODE = SUBSYS_DISABLED;

  /* Derivative Block: '<S224>/Derivative' */
  CSE1_CV3_1Straight_DWork.Derivative_RWORK.TimeStampA = rtInf;
  CSE1_CV3_1Straight_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* end of Start for SubSystem: '<S2>/Path-following' */

  /* ToFile Block: '<Root>/To File' */
  {
    const char *fileName = "CSE1_data.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                        "Error creating .mat file CSE1_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,24,0,"cse1_data")) {
      rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                        "Error writing mat file header to file CSE1_data.mat");
      return;
    }

    CSE1_CV3_1Straight_DWork.ToFile_IWORK.Count = 0;
    CSE1_CV3_1Straight_DWork.ToFile_IWORK.Decimation = -1;
    CSE1_CV3_1Straight_DWork.ToFile_PWORK.FilePtr = fp;
  }

  /* ToFile Block: '<S6>/To File' */
  {
    const char *fileName = "CSE1_data_eta_w.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                        "Error creating .mat file CSE1_data_eta_w.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,4,0,"cse1_data")) {
      rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                        "Error writing mat file header to file CSE1_data_eta_w.mat");
      return;
    }

    CSE1_CV3_1Straight_DWork.ToFile_IWORK_l.Count = 0;
    CSE1_CV3_1Straight_DWork.ToFile_IWORK_l.Decimation = -1;
    CSE1_CV3_1Straight_DWork.ToFile_PWORK_a.FilePtr = fp;
  }

  /* ToFile Block: '<S14>/To File' */
  {
    const char *fileName = "CSE1_data_reg_error.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                        "Error creating .mat file CSE1_data_reg_error.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,4,0,"cse1_data_reg_error")) {
      rtmSetErrorStatus(CSE1_CV3_1Straight_M,
                        "Error writing mat file header to file CSE1_data_reg_error.mat");
      return;
    }

    CSE1_CV3_1Straight_DWork.ToFile_IWORK_e.Count = 0;
    CSE1_CV3_1Straight_DWork.ToFile_IWORK_e.Decimation = -1;
    CSE1_CV3_1Straight_DWork.ToFile_PWORK_c.FilePtr = fp;
  }

  /* Start for enable SubSystem: '<S5>/CSE1' */
  CSE1_CV3_1Straight_DWork.CSE1_MODE = SUBSYS_DISABLED;

  /* end of Start for SubSystem: '<S5>/CSE1' */
  MdlInitialize();
}

RT_MODEL_CSE1_CV3_1Straight *CSE1_CV3_1Straight(void)
{
  CSE1_CV3_1Straight_initialize(1);
  return CSE1_CV3_1Straight_M;
}

void MdlTerminate(void)
{
  CSE1_CV3_1Straight_terminate();
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
#ifdef NI_ROOTMODEL_CSE1_CV3_1Straight
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
    return NIRT_GetValueByDataType(ptr,subindex,10,Complex);

   case 29:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,11,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 39:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 40:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 41:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,15,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 50:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 51:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 52:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 60:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 61:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 62:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 78:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 79:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 80:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 81:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,10,Complex);

   case 29:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,11,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 39:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 40:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 41:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,15,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 50:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 51:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 52:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 60:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 61:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 62:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 78:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 79:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 80:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 81:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern CSE1_CV3_1Straight_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Naviagation Systems/Qualisys 6 DOF/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(CSE1_CV3_1Straight_B.QTMIn, count, data[index++],
        46, 0);
    }
  } else {
    index += 9;
  }

  // Naviagation Systems/Qualisys 6 DOF/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&CSE1_CV3_1Straight_B.SITzAI1, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Naviagation Systems/Qualisys 6 DOF/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&CSE1_CV3_1Straight_B.SITzAI2, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // Naviagation Systems/Qualisys 6 DOF/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&CSE1_CV3_1Straight_B.SITzAI0, 0, data[index++], 0,
      0);
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

  // Plants/CSE1/Bow Thruster/SIT Out5 BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Switch2,0,
      0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out1 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Servo1,0,
      0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out2 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Servo2,0,
      0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out3 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Servo3,0,
      0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out4 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Servo4,0,
      0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out6 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.VSPSPort,
      0,0,0);
  } else {
    index += 1;
  }

  // Plants/CSE1/Voith Schneider Propeller /SIT Out7 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&CSE1_CV3_1Straight_B.VSPSStarboard,0,0,0);
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

  // Plants/CSE1/Bow Thruster/SIT Out5 BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Switch2,0,0,
    0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out1 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Servo1,0,0,
    0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out2 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Servo2,0,0,
    0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out3 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Servo3,0,0,
    0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out4 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.Servo4,0,0,
    0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out6 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&CSE1_CV3_1Straight_B.VSPSPort,0,
    0,0);

  // Plants/CSE1/Voith Schneider Propeller /SIT Out7 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&CSE1_CV3_1Straight_B.VSPSStarboard,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, QTMIn9Residual_Gain), 21, 1, 2, 0,
    "", 0 },

  { 1, "cse1_cv3_1straight/Naviagation Systems/Controller Input Selector/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, ControllerInputSelector_Value), 21,
    1, 2, 2, "", 0 },

  { 2, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, QTMIn3_Gain), 21, 1, 2, 4, "", 0 },

  { 3, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, mm2mx_Gain), 21, 1, 2, 6, "", 0 },

  { 4, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, QTMIn4_Gain), 21, 1, 2, 8, "", 0 },

  { 5, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, mm2my_Gain), 21, 1, 2, 10, "", 0 },

  { 6, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, QTMIn6_Gain), 21, 1, 2, 12, "", 0 },

  { 7, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, d2ryaw_Gain), 21, 1, 2, 14, "", 0 },

  { 8, "cse1_cv3_1straight/Plants/Enable Linear Simulator/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, EnableLinearSimulator_Value), 21, 1, 2, 16,
    "", 0 },

  { 9, "cse1_cv3_1straight/Naviagation Systems/eta_surge/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, eta_surge_Gain), 21, 1, 2, 18, "", 0 },

  { 10, "cse1_cv3_1straight/Naviagation Systems/eta_sway/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, eta_sway_Gain), 21, 1, 2, 20, "", 0 },

  { 11, "cse1_cv3_1straight/Naviagation Systems/eta_yaw/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, eta_yaw_Gain), 21, 1, 2, 22, "", 0 },

  { 12, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, QTMIn8_Gain), 21, 1, 2, 24, "", 0 },

  { 13, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, d2rroll_Gain), 21, 1, 2, 26, "", 0 },

  { 14, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, QTMIn7_Gain), 21, 1, 2, 28, "", 0 },

  { 15, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, d2rpitch_Gain), 21, 1, 2, 30, "", 0
  },

  { 16, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Constant1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant1_Value), 38, 9, 2, 32, "",
    0 },

  { 17, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, QTMIn5_Gain), 21, 1, 2, 34, "", 0 },

  { 18, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, mm2mz_Gain), 21, 1, 2, 36, "", 0 },

  { 19, "cse1_cv3_1straight/Naviagation Systems/nu_surge/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, nu_surge_Gain), 21, 1, 2, 38, "", 0 },

  { 20, "cse1_cv3_1straight/Naviagation Systems/nu_sway/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, nu_sway_Gain), 21, 1, 2, 40, "", 0 },

  { 21, "cse1_cv3_1straight/Naviagation Systems/nu_yaw/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, nu_yaw_Gain), 21, 1, 2, 42, "", 0 },

  { 22, "cse1_cv3_1straight/Guidance Systems/DP/Enable eta_d LPF/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Enableeta_dLPF_Value), 21, 1, 2, 44,
    "", 0 },

  { 23, "cse1_cv3_1straight/HMI/DP Input/x_d/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, x_d_Value), 21, 1, 2, 46, "", 0 },

  { 24, "cse1_cv3_1straight/HMI/DP Input/y_d/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, y_d_Value), 21, 1, 2, 48, "", 0 },

  { 25, "cse1_cv3_1straight/HMI/DP Input/psi_d/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, psi_d_Value), 21, 1, 2, 50, "", 0 },

  { 26, "cse1_cv3_1straight/HMI/DP Input/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain), 21, 1, 2, 52, "", 0 },

  { 27, "cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn/A", offsetof
    (Parameters_CSE1_CV3_1Straight, TransferFcn_A), 21, 1, 2, 54, "", 0 },

  { 28, "cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn/C", offsetof
    (Parameters_CSE1_CV3_1Straight, TransferFcn_C), 21, 1, 2, 56, "", 0 },

  { 29, "cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn1/A", offsetof
    (Parameters_CSE1_CV3_1Straight, TransferFcn1_A), 21, 1, 2, 58, "", 0 },

  { 30, "cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn1/C", offsetof
    (Parameters_CSE1_CV3_1Straight, TransferFcn1_C), 21, 1, 2, 60, "", 0 },

  { 31, "cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn2/A", offsetof
    (Parameters_CSE1_CV3_1Straight, TransferFcn2_A), 21, 1, 2, 62, "", 0 },

  { 32, "cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn2/C", offsetof
    (Parameters_CSE1_CV3_1Straight, TransferFcn2_C), 21, 1, 2, 64, "", 0 },

  { 33, "cse1_cv3_1straight/Guidance Systems/DP/eta_d DP N/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, eta_dDPN_Gain), 21, 1, 2, 66, "", 0 },

  { 34, "cse1_cv3_1straight/Guidance Systems/DP/eta_d DP E/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, eta_dDPE_Gain), 21, 1, 2, 68, "", 0 },

  { 35, "cse1_cv3_1straight/Guidance Systems/DP/eta_d DP Psi/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, eta_dDPPsi_Gain), 21, 1, 2, 70, "", 0 },

  { 36, "cse1_cv3_1straight/Control Systems/Control Mode/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, ControlMode_Value), 21, 1, 2, 72, "", 0 },

  { 37,
    "cse1_cv3_1straight/Control Systems/if Nonlinear PID Control/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value), 21, 1, 2, 74, "", 0
  },

  { 38,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Reset q/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Resetq_Value), 21, 1, 2, 76, "", 0 },

  { 39,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/q_0/q_x_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, q_x_0_Value), 21, 1, 2, 78, "", 0 },

  { 40,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/q_0/q_y_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, q_y_0_Value), 21, 1, 2, 80, "", 0 },

  { 41,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Reset q/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Resetq_Value_d), 21, 1, 2, 82, "", 0
  },

  { 42,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/q_0/q_x_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, q_x_0_Value_n), 21, 1, 2, 84, "", 0
  },

  { 43,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/q_0/q_y_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, q_y_0_Value_n), 21, 1, 2, 86, "", 0
  },

  { 44, "cse1_cv3_1straight/Control Systems/q_x gain/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, q_xgain_Gain), 21, 1, 2, 88, "", 0 },

  { 45, "cse1_cv3_1straight/Control Systems/q_y gain/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, q_ygain_Gain), 21, 1, 2, 90, "", 0 },

  { 46,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Reset s/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Resets_Value), 21, 1, 2, 92, "", 0 },

  { 47, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/s_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, s_0_Value), 21, 1, 2, 94, "", 0 },

  { 48,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Reset s/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Resets_Value_c), 21, 1, 2, 96, "", 0
  },

  { 49, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/s_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, s_0_Value_c), 21, 1, 2, 98, "", 0 },

  { 50, "cse1_cv3_1straight/Control Systems/s gain/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, sgain_Gain), 21, 1, 2, 100, "", 0 },

  { 51, "cse1_cv3_1straight/HMI/Path-following input/u_d/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, u_d_Value), 21, 1, 2, 102, "", 0 },

  { 52, "cse1_cv3_1straight/HMI/Path-following input/x_1/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, x_1_Value), 21, 1, 2, 104, "", 0 },

  { 53, "cse1_cv3_1straight/HMI/Path-following input/y_1/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, y_1_Value), 21, 1, 2, 106, "", 0 },

  { 54, "cse1_cv3_1straight/HMI/Path-following input/x_2/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, x_2_Value), 21, 1, 2, 108, "", 0 },

  { 55, "cse1_cv3_1straight/HMI/Path-following input/y_2/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, y_2_Value), 21, 1, 2, 110, "", 0 },

  { 56, "cse1_cv3_1straight/Guidance Systems/Enable Path/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, EnablePath_Value), 21, 1, 2, 112, "", 0 },

  { 57, "cse1_cv3_1straight/Guidance Systems/path x_d/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, pathx_d_Gain), 21, 1, 2, 114, "", 0 },

  { 58, "cse1_cv3_1straight/Guidance Systems/path y_d/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, pathy_d_Gain), 21, 1, 2, 116, "", 0 },

  { 59, "cse1_cv3_1straight/Guidance Systems/path psi_d/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, pathpsi_d_Gain), 21, 1, 2, 118, "", 0 },

  { 60, "cse1_cv3_1straight/Control Systems/Precision control/u1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u1_Value), 21, 1, 2, 120, "", 0 },

  { 61, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, LabVIEWu_1_Gain), 21, 1, 2, 122, "",
    0 },

  { 62, "cse1_cv3_1straight/Control Systems/Precision control/u2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u2_Value), 21, 1, 2, 124, "", 0 },

  { 63, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, LabVIEWu_2_Gain), 21, 1, 2, 126, "",
    0 },

  { 64, "cse1_cv3_1straight/Control Systems/Precision control/u3/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u3_Value), 21, 1, 2, 128, "", 0 },

  { 65, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_3/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, LabVIEWu_3_Gain), 21, 1, 2, 130, "",
    0 },

  { 66, "cse1_cv3_1straight/Control Systems/Precision control/u4/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u4_Value), 21, 1, 2, 132, "", 0 },

  { 67, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_4/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, LabVIEWu_4_Gain), 21, 1, 2, 134, "",
    0 },

  { 68, "cse1_cv3_1straight/Control Systems/Precision control/u5/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u5_Value), 21, 1, 2, 136, "", 0 },

  { 69, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_5/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, LabVIEWu_5_Gain), 21, 1, 2, 138, "",
    0 },

  { 70,
    "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW  BT power/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, LabVIEWBTpower_Value), 21, 1, 2, 140,
    "", 0 },

  { 71,
    "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW VSP speed/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, LabVIEWVSPspeed_Value), 21, 1, 2,
    142, "", 0 },

  { 72, "cse1_cv3_1straight/Control Systems/PS3 input/AS_LY/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, AS_LY_Value), 21, 1, 2, 144, "", 0 },

  { 73, "cse1_cv3_1straight/Control Systems/PS3 input/ScalingLY/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, ScalingLY_Gain), 21, 1, 2, 146, "", 0 },

  { 74,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, PS3u_1_Gain), 21, 1, 2, 148, "", 0 },

  { 75, "cse1_cv3_1straight/Control Systems/PS3 input/AS_LX/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, AS_LX_Value), 21, 1, 2, 150, "", 0 },

  { 76, "cse1_cv3_1straight/Control Systems/PS3 input/ScalingLX/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, ScalingLX_Gain), 21, 1, 2, 152, "", 0 },

  { 77,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, PS3u_2_Gain), 21, 1, 2, 154, "", 0 },

  { 78, "cse1_cv3_1straight/Control Systems/PS3 input/AS_RY/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, AS_RY_Value), 21, 1, 2, 156, "", 0 },

  { 79, "cse1_cv3_1straight/Control Systems/PS3 input/ScalingRY/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, ScalingRY_Gain), 21, 1, 2, 158, "", 0 },

  { 80,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_3/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, PS3u_3_Gain), 21, 1, 2, 160, "", 0 },

  { 81, "cse1_cv3_1straight/Control Systems/PS3 input/AS_RX/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, AS_RX_Value), 21, 1, 2, 162, "", 0 },

  { 82, "cse1_cv3_1straight/Control Systems/PS3 input/Scaling_RX/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, Scaling_RX_Gain), 21, 1, 2, 164, "", 0 },

  { 83,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_4/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, PS3u_4_Gain), 21, 1, 2, 166, "", 0 },

  { 84, "cse1_cv3_1straight/Control Systems/PS3 input/L2/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, L2_Value), 21, 1, 2, 168, "", 0 },

  { 85, "cse1_cv3_1straight/Control Systems/PS3 input/R2/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, R2_Value), 21, 1, 2, 170, "", 0 },

  { 86,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_5/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, PS3u_5_Gain), 21, 1, 2, 172, "", 0 },

  { 87, "cse1_cv3_1straight/Control Systems/PS3 input/PS3_BT_Power/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, PS3_BT_Power_Value), 21, 1, 2, 174,
    "", 0 },

  { 88, "cse1_cv3_1straight/Control Systems/PS3 input/PS3_VSP_Speed/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, PS3_VSP_Speed_Value), 21, 1, 2, 176,
    "", 0 },

  { 89,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e11_Value), 21, 1, 2, 178, "", 0 },

  { 90,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e21_Value), 21, 1, 2, 180, "", 0 },

  { 91,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y1_Value), 21, 1, 2, 182, "", 0 },

  { 92,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e12_Value), 21, 1, 2, 184, "", 0 },

  { 93,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e22_Value), 21, 1, 2, 186, "", 0 },

  { 94,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Value), 21, 1, 2, 188, "", 0 },

  { 95,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Gain), 21, 1, 2, 190, "", 0 },

  { 96,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e13_Value), 21, 1, 2, 192, "", 0 },

  { 97,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e23_Value), 21, 1, 2, 194, "", 0 },

  { 98,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Value), 21, 1, 2, 196, "", 0 },

  { 99,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Gain), 21, 1, 2, 198, "", 0 },

  { 100,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e14_Value), 21, 1, 2, 200, "", 0 },

  { 101,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e24_Value), 21, 1, 2, 202, "", 0 },

  { 102,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Value), 21, 1, 2, 204, "", 0 },

  { 103,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Gain), 21, 1, 2, 206, "", 0 },

  { 104,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e15_Value), 21, 1, 2, 208, "", 0 },

  { 105,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e25_Value), 21, 1, 2, 210, "", 0 },

  { 106,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x3_Value), 21, 1, 2, 212, "", 0 },

  { 107, "cse1_cv3_1straight/Control Systems/Simple Control/tau_surge/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, tau_surge_Gain), 21, 1, 2, 214, "",
    0 },

  { 108, "cse1_cv3_1straight/Control Systems/Simple Control/tau_sway/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, tau_sway_Gain), 21, 1, 2, 216, "", 0
  },

  { 109, "cse1_cv3_1straight/Control Systems/Simple Control/tau_yaw/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, tau_yaw_Gain), 21, 1, 2, 218, "", 0
  },

  { 110,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_m), 21, 1, 2, 220, "",
    0 },

  { 111,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_e), 21, 1, 2, 222, "",
    0 },

  { 112,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_XData), 46, 9, 2, 224, "", 0 },

  { 113,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_YData), 46, 9, 2, 226, "", 0 },

  { 114,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_Value), 21, 1, 2, 228, "", 0 },

  { 115,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_XData_n), 73, 10, 2, 230, "", 0
  },

  { 116,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_YData_h), 73, 10, 2, 232, "", 0
  },

  { 117,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_n), 21, 1, 2, 234, "",
    0 },

  { 118,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_j), 21, 1, 2, 236, "",
    0 },

  { 119,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_XData), 74, 11, 2, 238, "", 0 },

  { 120,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_YData), 74, 11, 2, 240, "", 0 },

  { 121,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_Value), 21, 1, 2, 242, "", 0 },

  { 122,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_XData_e), 73, 10, 2, 244, "", 0
  },

  { 123,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_YData_c), 73, 10, 2, 246, "", 0
  },

  { 124,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_h), 21, 1, 2, 248, "",
    0 },

  { 125,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_mx), 21, 1, 2, 250,
    "", 0 },

  { 126,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_XData), 75, 8, 2, 252, "", 0 },

  { 127,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_YData), 75, 8, 2, 254, "", 0 },

  { 128,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_Value), 21, 1, 2, 256, "", 0 },

  { 129,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_XData_n), 74, 11, 2, 258, "", 0
  },

  { 130,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_YData_c), 74, 11, 2, 260, "", 0
  },

  { 131,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_b), 21, 1, 2, 262, "",
    0 },

  { 132,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_eu), 21, 1, 2, 264,
    "", 0 },

  { 133,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_XData), 73, 10, 2, 266, "", 0 },

  { 134,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_YData), 73, 10, 2, 268, "", 0 },

  { 135,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_Value), 21, 1, 2, 270, "", 0 },

  { 136,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_XData_a), 76, 7, 2, 272, "", 0
  },

  { 137,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_YData_o), 76, 7, 2, 274, "", 0
  },

  { 138,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_f), 21, 1, 2, 276, "",
    0 },

  { 139,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_c), 21, 1, 2, 278, "",
    0 },

  { 140,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_XData), 26, 3, 2, 280, "", 0 },

  { 141,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_YData), 26, 3, 2, 282, "", 0 },

  { 142,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_Value), 21, 1, 2, 284, "", 0 },

  { 143,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_XData_g), 26, 3, 2, 286, "", 0
  },

  { 144,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_YData_f), 26, 3, 2, 288, "", 0
  },

  { 145,
    "cse1_cv3_1straight/Control Systems/Simple Control/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat), 21, 1, 2, 290,
    "", 0 },

  { 146,
    "cse1_cv3_1straight/Control Systems/Simple Control/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat), 21, 1, 2, 292,
    "", 0 },

  { 147, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Joysticku_1_Gain), 21, 1, 2, 294, "",
    0 },

  { 148, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Joysticku_2_Gain), 21, 1, 2, 296, "",
    0 },

  { 149, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_3/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Joysticku_3_Gain), 21, 1, 2, 298, "",
    0 },

  { 150, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_4/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Joysticku_4_Gain), 21, 1, 2, 300, "",
    0 },

  { 151, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_5/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Joysticku_5_Gain), 21, 1, 2, 302, "",
    0 },

  { 152,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e11_Value_m), 21, 1, 2, 304, "", 0
  },

  { 153,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e21_Value_l), 21, 1, 2, 306, "", 0
  },

  { 154,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y1_Value_c), 21, 1, 2, 308, "", 0
  },

  { 155,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e12_Value_i), 21, 1, 2, 310, "", 0
  },

  { 156,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e22_Value_a), 21, 1, 2, 312, "", 0
  },

  { 157,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Value_b), 21, 1, 2, 314, "", 0
  },

  { 158,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Gain_g), 21, 1, 2, 316, "", 0 },

  { 159,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e13_Value_j), 21, 1, 2, 318, "", 0
  },

  { 160,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e23_Value_o), 21, 1, 2, 320, "", 0
  },

  { 161,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Value_i), 21, 1, 2, 322, "", 0
  },

  { 162,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Gain_a), 21, 1, 2, 324, "", 0 },

  { 163,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e14_Value_c), 21, 1, 2, 326, "", 0
  },

  { 164,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e24_Value_o), 21, 1, 2, 328, "", 0
  },

  { 165,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Value_j), 21, 1, 2, 330, "", 0
  },

  { 166,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Gain_l), 21, 1, 2, 332, "", 0 },

  { 167,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e15_Value_g), 21, 1, 2, 334, "", 0
  },

  { 168,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e25_Value_d), 21, 1, 2, 336, "", 0
  },

  { 169,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x3_Value_o), 21, 1, 2, 338, "", 0
  },

  { 170,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Kp_scale/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Kp_scale_Value), 21, 1, 2, 340, "",
    0 },

  { 171, "cse1_cv3_1straight/Control Systems/DP control/Enable Filter/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, EnableFilter_Value), 21, 1, 2, 342,
    "", 0 },

  { 172,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, Integrator_IC), 21, 1, 2, 344, "", 0
  },

  { 173,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_j), 21, 1, 2,
    346, "", 0 },

  { 174,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_o), 21, 1, 2,
    348, "", 0 },

  { 175,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain), 21, 1, 2, 350, "", 0 },

  { 176,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_hq), 21, 1, 2, 352,
    "", 0 },

  { 177,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_o), 21, 1, 2,
    354, "", 0 },

  { 178,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_h), 21, 1, 2,
    356, "", 0 },

  { 179,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_b), 21, 1, 2, 358, "", 0 },

  { 180,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_k), 21, 1, 2, 360, "",
    0 },

  { 181,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/eta N/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, etaN_Gain), 21, 1, 2, 362, "", 0 },

  { 182,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/eta E/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, etaE_Gain), 21, 1, 2, 364, "", 0 },

  { 183,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/eta Psi/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, etaPsi_Gain), 21, 1, 2, 366, "", 0 },

  { 184,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_N_hil/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Reg_e_N_hil_Gain), 21, 1, 2, 368, "",
    0 },

  { 185,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_E_hil/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Reg_e_E_hil_Gain), 21, 1, 2, 370, "",
    0 },

  { 186,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_Psi_hil/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Reg_e_Psi_hil_Gain), 21, 1, 2, 372,
    "", 0 },

  { 187,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_p), 21, 1, 2,
    374, "", 0 },

  { 188,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_hf), 21, 1, 2,
    376, "", 0 },

  { 189,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_e), 21, 1, 2, 378, "", 0 },

  { 190,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_i), 21, 1, 2, 380, "",
    0 },

  { 191, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Kp/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Kp_Gain), 38, 9, 2, 382, "", 0 },

  { 192,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p1_Gain), 21, 1, 2, 384, "", 0 },

  { 193,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p2_Gain), 21, 1, 2, 386, "", 0 },

  { 194,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 3/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p3_Gain), 21, 1, 2, 388, "", 0 },

  { 195,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Reset_DP_integrator/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Reset_DP_integrator_Value), 21, 1, 2,
    390, "", 0 },

  { 196,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Integrator/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, Integrator_IC_g), 21, 1, 2, 392, "",
    0 },

  { 197, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Ki/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Ki_Gain), 38, 9, 2, 394, "", 0 },

  { 198,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Ki_scale/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Ki_scale_Value), 21, 1, 2, 396, "",
    0 },

  { 199,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i1_Gain), 21, 1, 2, 398, "", 0 },

  { 200,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i2_Gain), 21, 1, 2, 400, "", 0 },

  { 201,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 3/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i3_Gain), 21, 1, 2, 402, "", 0 },

  { 202,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator4/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, Integrator4_IC), 21, 1, 2, 404, "",
    0 },

  { 203, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Kd/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Kd_Gain), 38, 9, 2, 406, "", 0 },

  { 204,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Kd_scale/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Kd_scale_Value), 21, 1, 2, 408, "",
    0 },

  { 205,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d1_Gain), 21, 1, 2, 410, "", 0 },

  { 206,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d2_Gain), 21, 1, 2, 412, "", 0 },

  { 207,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 3/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d3_Gain), 21, 1, 2, 414, "", 0 },

  { 208, "cse1_cv3_1straight/Control Systems/DP control/DP tau_surge/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, DPtau_surge_Gain), 21, 1, 2, 416, "",
    0 },

  { 209, "cse1_cv3_1straight/Control Systems/DP control/DP tau_sway/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, DPtau_sway_Gain), 21, 1, 2, 418, "",
    0 },

  { 210, "cse1_cv3_1straight/Control Systems/DP control/DP tau_yaw/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, DPtau_yaw_Gain), 21, 1, 2, 420, "",
    0 },

  { 211,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_o), 21, 1, 2, 422, "",
    0 },

  { 212,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_ed), 21, 1, 2, 424,
    "", 0 },

  { 213,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_XData_o), 46, 9, 2, 426, "", 0
  },

  { 214,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_YData_f), 46, 9, 2, 428, "", 0
  },

  { 215,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_Value_c), 21, 1, 2, 430, "", 0
  },

  { 216,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_XData_h), 73, 10, 2, 432, "", 0
  },

  { 217,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_YData_l), 73, 10, 2, 434, "", 0
  },

  { 218, "cse1_cv3_1straight/Control Systems/DP control/DP u_1/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, DPu_1_Gain), 21, 1, 2, 436, "", 0 },

  { 219,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_oa), 21, 1, 2, 438,
    "", 0 },

  { 220,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_cs), 21, 1, 2, 440,
    "", 0 },

  { 221,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_XData_c), 74, 11, 2, 442, "", 0
  },

  { 222,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_YData_cj), 74, 11, 2, 444, "",
    0 },

  { 223,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_Value_h), 21, 1, 2, 446, "", 0
  },

  { 224,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_XData_d), 73, 10, 2, 448, "", 0
  },

  { 225,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_YData_h), 73, 10, 2, 450, "", 0
  },

  { 226, "cse1_cv3_1straight/Control Systems/DP control/DP u_2/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, DPu_2_Gain), 21, 1, 2, 452, "", 0 },

  { 227,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_jk), 21, 1, 2, 454,
    "", 0 },

  { 228,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_eq), 21, 1, 2, 456,
    "", 0 },

  { 229,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_XData_h), 75, 8, 2, 458, "", 0
  },

  { 230,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_YData_o), 75, 8, 2, 460, "", 0
  },

  { 231,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_Value_a), 21, 1, 2, 462, "", 0
  },

  { 232,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_XData_c), 74, 11, 2, 464, "", 0
  },

  { 233,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_YData_k), 74, 11, 2, 466, "", 0
  },

  { 234, "cse1_cv3_1straight/Control Systems/DP control/DP u_3/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, DPu_3_Gain), 21, 1, 2, 468, "", 0 },

  { 235,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_nd), 21, 1, 2, 470,
    "", 0 },

  { 236,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_g), 21, 1, 2, 472, "",
    0 },

  { 237,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_XData_n), 73, 10, 2, 474, "", 0
  },

  { 238,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_YData_d), 73, 10, 2, 476, "", 0
  },

  { 239,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_Value_j), 21, 1, 2, 478, "", 0
  },

  { 240,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_XData_b), 76, 7, 2, 480, "", 0
  },

  { 241,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_YData_dx), 76, 7, 2, 482, "", 0
  },

  { 242, "cse1_cv3_1straight/Control Systems/DP control/DP u_4/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, DPu_4_Gain), 21, 1, 2, 484, "", 0 },

  { 243,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_hu), 21, 1, 2, 486,
    "", 0 },

  { 244,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_gz), 21, 1, 2, 488,
    "", 0 },

  { 245,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_XData_b), 26, 3, 2, 490, "", 0
  },

  { 246,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_YData_i), 26, 3, 2, 492, "", 0
  },

  { 247,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_Value_d), 21, 1, 2, 494, "", 0
  },

  { 248,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_XData_gn), 26, 3, 2, 496, "", 0
  },

  { 249,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_YData_b), 26, 3, 2, 498, "", 0
  },

  { 250, "cse1_cv3_1straight/Control Systems/DP control/DP u_5/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, DPu_5_Gain), 21, 1, 2, 500, "", 0 },

  { 251, "cse1_cv3_1straight/Control Systems/DP control/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_ok), 21, 1, 2,
    502, "", 0 },

  { 252, "cse1_cv3_1straight/Control Systems/DP control/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_k), 21, 1, 2,
    504, "", 0 },

  { 253, "cse1_cv3_1straight/Control Systems/DP control/BT_power_limit/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, BT_power_limit_Value), 21, 1, 2, 506,
    "", 0 },

  { 254, "cse1_cv3_1straight/Control Systems/DP control/VSP_speeds/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, VSP_speeds_Value), 21, 1, 2, 508, "",
    0 },

  { 255,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e11_Value_d), 21, 1, 2, 510, "", 0
  },

  { 256,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e21_Value_c), 21, 1, 2, 512, "", 0
  },

  { 257,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y1_Value_b), 21, 1, 2, 514, "", 0
  },

  { 258,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e12_Value_c), 21, 1, 2, 516, "", 0
  },

  { 259,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e22_Value_e), 21, 1, 2, 518, "", 0
  },

  { 260,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Value_e), 21, 1, 2, 520, "", 0
  },

  { 261,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Gain_l), 21, 1, 2, 522, "", 0 },

  { 262,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e13_Value_b), 21, 1, 2, 524, "", 0
  },

  { 263,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e23_Value_c), 21, 1, 2, 526, "", 0
  },

  { 264,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Value_h), 21, 1, 2, 528, "", 0
  },

  { 265,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Gain_n), 21, 1, 2, 530, "", 0 },

  { 266,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e14_Value_p), 21, 1, 2, 532, "", 0
  },

  { 267,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e24_Value_k), 21, 1, 2, 534, "", 0
  },

  { 268,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Value_c), 21, 1, 2, 536, "", 0
  },

  { 269,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Gain_f), 21, 1, 2, 538, "", 0 },

  { 270,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e15_Value_n), 21, 1, 2, 540, "", 0
  },

  { 271,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e25_Value_b), 21, 1, 2, 542, "", 0
  },

  { 272,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x3_Value_a), 21, 1, 2, 544, "", 0
  },

  { 273, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R31_Value), 21, 1, 2, 546, "", 0 },

  { 274, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/-1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Gain), 21, 1, 2, 548, "", 0 },

  { 275, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R32_Value), 21, 1, 2, 550, "", 0 },

  { 276, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R13_Value), 21, 1, 2, 552, "", 0 },

  { 277, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R23_Value), 21, 1, 2, 554, "", 0 },

  { 278, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R33/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R33_Value), 21, 1, 2, 556, "", 0 },

  { 279, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i_Surge/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i_Surge_Value), 21, 1, 2, 558, "",
    0 },

  { 280, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i/21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value), 21, 1, 2, 560, "", 0 },

  { 281, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i/31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_m), 21, 1, 2, 562, "", 0 },

  { 282, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i/12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_c), 21, 1, 2, 564, "", 0 },

  { 283, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i_Sway/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i_Sway_Value), 21, 1, 2, 566, "",
    0 },

  { 284, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i/32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_d), 21, 1, 2, 568, "", 0 },

  { 285, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i/13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_a), 21, 1, 2, 570, "", 0 },

  { 286, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i/23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_dx), 21, 1, 2, 572, "", 0 },

  { 287, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i_Yaw/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i_Yaw_Value), 21, 1, 2, 574, "", 0
  },

  { 288,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Integral action state/Integrator/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, Integrator_IC_b), 26, 3, 2, 576, "",
    0 },

  { 289, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d_Surge/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d_Surge_Value), 21, 1, 2, 578, "",
    0 },

  { 290, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d/21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_j), 21, 1, 2, 580, "", 0 },

  { 291, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d/31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_n), 21, 1, 2, 582, "", 0 },

  { 292, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d/12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_h), 21, 1, 2, 584, "", 0 },

  { 293, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d_Sway/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d_Sway_Value), 21, 1, 2, 586, "",
    0 },

  { 294, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d/32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_dk), 21, 1, 2, 588, "", 0 },

  { 295, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d/13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_o), 21, 1, 2, 590, "", 0 },

  { 296, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d/23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_h4), 21, 1, 2, 592, "", 0 },

  { 297, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d_Yaw/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d_Yaw_Value), 21, 1, 2, 594, "", 0
  },

  { 298, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _Value), 21, 1, 2, 596, "", 0 },

  { 299, "cse1_cv3_1straight/Control Systems/LgV design 2/kappa_1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, kappa_1_Value), 21, 1, 2, 598, "", 0
  },

  { 300, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/4/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, _Gain), 21, 1, 2, 600, "", 0 },

  { 301, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p_Surge/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p_Surge_Value), 21, 1, 2, 602, "",
    0 },

  { 302, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p/21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_hi), 21, 1, 2, 604, "", 0 },

  { 303, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p/31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_nb), 21, 1, 2, 606, "", 0 },

  { 304, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p/12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_e), 21, 1, 2, 608, "", 0 },

  { 305, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p_Sway/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p_Sway_Value), 21, 1, 2, 610, "",
    0 },

  { 306, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p/32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_e1), 21, 1, 2, 612, "", 0 },

  { 307, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p/13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_jo), 21, 1, 2, 614, "", 0 },

  { 308, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p/23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_k), 21, 1, 2, 616, "", 0 },

  { 309, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p_Yaw/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p_Yaw_Value), 21, 1, 2, 618, "", 0
  },

  { 310,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Virtual control/I/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_n4), 38, 9, 2, 620,
    "", 0 },

  { 311,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_o), 21, 1, 2, 622, "", 0 },

  { 312,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_jx), 21, 1, 2,
    624, "", 0 },

  { 313,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_c), 21, 1, 2,
    626, "", 0 },

  { 314,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_d), 21, 1, 2, 628, "", 0 },

  { 315,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_gu), 21, 1, 2, 630,
    "", 0 },

  { 316,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_e), 21, 1, 2, 632, "", 0
  },

  { 317, "cse1_cv3_1straight/Guidance Systems/q_x/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, q_x_Gain), 21, 1, 2, 634, "", 0 },

  { 318, "cse1_cv3_1straight/Guidance Systems/q_y/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, q_y_Gain), 21, 1, 2, 636, "", 0 },

  { 319, "cse1_cv3_1straight/Guidance Systems/psi_los/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, psi_los_Gain), 21, 1, 2, 638, "", 0 },

  { 320,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_a), 21, 1, 2, 640, "", 0 },

  { 321,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_oh), 21, 1, 2,
    642, "", 0 },

  { 322,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_p), 21, 1, 2,
    644, "", 0 },

  { 323,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_k), 21, 1, 2, 646, "", 0 },

  { 324,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_a), 21, 1, 2, 648, "",
    0 },

  { 325,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_h), 21, 1, 2, 650, "", 0
  },

  { 326,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s eq/0_2x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x1_Value), 37, 2, 2, 652, "", 0 },

  { 327,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/X_u/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, X_u_Value), 21, 1, 2, 654, "", 0 },

  { 328,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-X_u/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, X_u_Gain), 21, 1, 2, 656, "", 0 },

  { 329,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/D_L_21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_21_Value), 21, 1, 2, 658, "", 0
  },

  { 330,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/D_L_31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_31_Value), 21, 1, 2, 660, "", 0
  },

  { 331,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/D_L_12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_12_Value), 21, 1, 2, 662, "", 0
  },

  { 332,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/Y_v/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_v_Value), 21, 1, 2, 664, "", 0 },

  { 333,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-Y_v/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_v_Gain), 21, 1, 2, 666, "", 0 },

  { 334,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/N_v/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_v_Value), 21, 1, 2, 668, "", 0 },

  { 335,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-N_v/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, N_v_Gain), 21, 1, 2, 670, "", 0 },

  { 336,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/D_L_13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_13_Value), 21, 1, 2, 672, "", 0
  },

  { 337,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/Y_r/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_r_Value), 21, 1, 2, 674, "", 0 },

  { 338,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-Y_vr/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_vr_Gain), 21, 1, 2, 676, "", 0 },

  { 339,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/N_r/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_r_Value), 21, 1, 2, 678, "", 0 },

  { 340,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-N_r/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, N_r_Gain), 21, 1, 2, 680, "", 0 },

  { 341, "cse1_cv3_1straight/Control Systems/LgV design 2/M/m/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, m_Value), 21, 1, 2, 682, "", 0 },

  { 342, "cse1_cv3_1straight/Control Systems/LgV design 2/M/X_udot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, X_udot_Value), 21, 1, 2, 684, "", 0
  },

  { 343, "cse1_cv3_1straight/Control Systems/LgV design 2/M/M_21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_21_Value), 21, 1, 2, 686, "", 0 },

  { 344, "cse1_cv3_1straight/Control Systems/LgV design 2/M/M_31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_31_Value), 21, 1, 2, 688, "", 0 },

  { 345, "cse1_cv3_1straight/Control Systems/LgV design 2/M/M_12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_12_Value), 21, 1, 2, 690, "", 0 },

  { 346, "cse1_cv3_1straight/Control Systems/LgV design 2/M/Y_vdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_vdot_Value), 21, 1, 2, 692, "", 0
  },

  { 347, "cse1_cv3_1straight/Control Systems/LgV design 2/M/x_g/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, x_g_Value), 21, 1, 2, 694, "", 0 },

  { 348, "cse1_cv3_1straight/Control Systems/LgV design 2/M/N_vdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_vdot_Value), 21, 1, 2, 696, "", 0
  },

  { 349, "cse1_cv3_1straight/Control Systems/LgV design 2/M/M_13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_13_Value), 21, 1, 2, 698, "", 0 },

  { 350, "cse1_cv3_1straight/Control Systems/LgV design 2/M/Y_rdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_rdot_Value), 21, 1, 2, 700, "", 0
  },

  { 351, "cse1_cv3_1straight/Control Systems/LgV design 2/M/I_z/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, I_z_Value), 21, 1, 2, 702, "", 0 },

  { 352, "cse1_cv3_1straight/Control Systems/LgV design 2/M/N_rdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_rdot_Value), 21, 1, 2, 704, "", 0
  },

  { 353,
    "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/I/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_f1), 38, 9, 2, 706,
    "", 0 },

  { 354, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S11/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S11_Value), 21, 1, 2, 708, "", 0 },

  { 355, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/R31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R31_Value_h), 21, 1, 2, 710, "", 0 },

  { 356, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S12/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, S12_Gain), 21, 1, 2, 712, "", 0 },

  { 357, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S22/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S22_Value), 21, 1, 2, 714, "", 0 },

  { 358, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S32_Value), 21, 1, 2, 716, "", 0 },

  { 359, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S13_Value), 21, 1, 2, 718, "", 0 },

  { 360, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S23_Value), 21, 1, 2, 720, "", 0 },

  { 361, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S33/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S33_Value), 21, 1, 2, 722, "", 0 },

  { 362,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^t eq/0_2x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x1_Value_c), 37, 2, 2, 724, "", 0
  },

  { 363,
    "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^q/I/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_p), 38, 9, 2, 726, "",
    0 },

  { 364,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/0_2x2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x2_Value), 22, 4, 2, 728, "", 0 },

  { 365,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Integrator2/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, Integrator2_IC), 21, 1, 2, 730, "",
    0 },

  { 366,
    "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^s/I/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_fj), 38, 9, 2, 732,
    "", 0 },

  { 367,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/0_2x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x1_Value_o), 37, 2, 2, 734, "", 0
  },

  { 368,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_px), 21, 1, 2, 736,
    "", 0 },

  { 369,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_hh), 21, 1, 2, 738,
    "", 0 },

  { 370,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_XData_d), 46, 9, 2, 740, "", 0
  },

  { 371,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_YData_d), 46, 9, 2, 742, "", 0
  },

  { 372,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_Value_h), 21, 1, 2, 744, "", 0
  },

  { 373,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_XData_hd), 73, 10, 2, 746, "",
    0 },

  { 374,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_YData_i), 73, 10, 2, 748, "", 0
  },

  { 375,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_ee), 21, 1, 2, 750,
    "", 0 },

  { 376,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_l), 21, 1, 2, 752, "",
    0 },

  { 377,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_XData_f), 74, 11, 2, 754, "", 0
  },

  { 378,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_YData_k), 74, 11, 2, 756, "", 0
  },

  { 379,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_Value_g), 21, 1, 2, 758, "", 0
  },

  { 380,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_XData_h), 73, 10, 2, 760, "", 0
  },

  { 381,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_YData_j), 73, 10, 2, 762, "", 0
  },

  { 382,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_bu), 21, 1, 2, 764,
    "", 0 },

  { 383,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_op), 21, 1, 2, 766,
    "", 0 },

  { 384,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_XData_f), 75, 8, 2, 768, "", 0
  },

  { 385,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_YData_e), 75, 8, 2, 770, "", 0
  },

  { 386,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_Value_c), 21, 1, 2, 772, "", 0
  },

  { 387,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_XData_b), 74, 11, 2, 774, "", 0
  },

  { 388,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_YData_kz), 74, 11, 2, 776, "",
    0 },

  { 389,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_fv), 21, 1, 2, 778,
    "", 0 },

  { 390,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_ju), 21, 1, 2, 780,
    "", 0 },

  { 391,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_XData_nx), 73, 10, 2, 782, "",
    0 },

  { 392,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_YData_d2), 73, 10, 2, 784, "",
    0 },

  { 393,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_Value_a), 21, 1, 2, 786, "", 0
  },

  { 394,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_XData_ne), 76, 7, 2, 788, "", 0
  },

  { 395,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_YData_de), 76, 7, 2, 790, "", 0
  },

  { 396,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_mf), 21, 1, 2, 792,
    "", 0 },

  { 397,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_edn), 21, 1, 2, 794,
    "", 0 },

  { 398,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_XData_o), 26, 3, 2, 796, "", 0
  },

  { 399,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_YData_a), 26, 3, 2, 798, "", 0
  },

  { 400,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_Value_f), 21, 1, 2, 800, "", 0
  },

  { 401,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_XData_f), 26, 3, 2, 802, "", 0
  },

  { 402,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_YData_fx), 26, 3, 2, 804, "", 0
  },

  { 403, "cse1_cv3_1straight/Control Systems/LgV design 2/BT_power_limit/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, BT_power_limit_Value_c), 21, 1, 2,
    806, "", 0 },

  { 404, "cse1_cv3_1straight/Control Systems/LgV design 2/VSP_speeds/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, VSP_speeds_Value_m), 21, 1, 2, 808,
    "", 0 },

  { 405,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e11/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e11_Value_o), 21, 1, 2, 810, "", 0
  },

  { 406,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e21_Value_k), 21, 1, 2, 812, "", 0
  },

  { 407,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_y1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y1_Value_j), 21, 1, 2, 814, "", 0
  },

  { 408,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e12_Value_a), 21, 1, 2, 816, "", 0
  },

  { 409,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e22/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e22_Value_m), 21, 1, 2, 818, "", 0
  },

  { 410,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Value_ex), 21, 1, 2, 820, "", 0
  },

  { 411,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Gain_d), 21, 1, 2, 822, "", 0 },

  { 412,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e13_Value_o), 21, 1, 2, 824, "", 0
  },

  { 413,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e23_Value_i), 21, 1, 2, 826, "", 0
  },

  { 414,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_y2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Value_l), 21, 1, 2, 828, "", 0
  },

  { 415,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_y2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Gain_ag), 21, 1, 2, 830, "", 0
  },

  { 416,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e14/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e14_Value_e), 21, 1, 2, 832, "", 0
  },

  { 417,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e24/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e24_Value_d), 21, 1, 2, 834, "", 0
  },

  { 418,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Value_f), 21, 1, 2, 836, "", 0
  },

  { 419,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Gain_i), 21, 1, 2, 838, "", 0 },

  { 420,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e15/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e15_Value_c), 21, 1, 2, 840, "", 0
  },

  { 421,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e25/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e25_Value_bl), 21, 1, 2, 842, "",
    0 },

  { 422,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x3/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x3_Value_d), 21, 1, 2, 844, "", 0
  },

  { 423, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R31_Value_e), 21, 1, 2, 846, "", 0 },

  { 424, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R32_Value_a), 21, 1, 2, 848, "", 0 },

  { 425, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R13_Value_h), 21, 1, 2, 850, "", 0 },

  { 426, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R23_Value_a), 21, 1, 2, 852, "", 0 },

  { 427, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R33/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R33_Value_e), 21, 1, 2, 854, "", 0 },

  { 428, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p_Surge/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p_Surge_Value_c), 21, 1, 2, 856,
    "", 0 },

  { 429, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_ea), 21, 1, 2, 858, "", 0 },

  { 430, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_am), 21, 1, 2, 860, "", 0 },

  { 431, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_dp), 21, 1, 2, 862, "", 0 },

  { 432, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p_Sway/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p_Sway_Value_o), 21, 1, 2, 864, "",
    0 },

  { 433, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_i), 21, 1, 2, 866, "", 0 },

  { 434, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_md), 21, 1, 2, 868, "", 0 },

  { 435, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_ib), 21, 1, 2, 870, "", 0 },

  { 436, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p_Yaw/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p_Yaw_Value_j), 21, 1, 2, 872, "",
    0 },

  { 437,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_j), 21, 1, 2, 874, "", 0 },

  { 438,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_g), 21, 1, 2,
    876, "", 0 },

  { 439,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_e), 21, 1, 2,
    878, "", 0 },

  { 440,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_kr), 21, 1, 2, 880, "", 0
  },

  { 441,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_pw), 21, 1, 2, 882,
    "", 0 },

  { 442,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_j), 21, 1, 2, 884, "", 0
  },

  { 443,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_ou), 21, 1, 2, 886, "", 0
  },

  { 444,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_pu), 21, 1, 2,
    888, "", 0 },

  { 445,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_hs), 21, 1, 2,
    890, "", 0 },

  { 446,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_az), 21, 1, 2, 892, "", 0
  },

  { 447,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_b4), 21, 1, 2, 894,
    "", 0 },

  { 448,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_i), 21, 1, 2, 896, "", 0
  },

  { 449, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i_Surge/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i_Surge_Value_f), 21, 1, 2, 898,
    "", 0 },

  { 450, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_ce), 21, 1, 2, 900, "", 0 },

  { 451, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_jf), 21, 1, 2, 902, "", 0 },

  { 452, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_g), 21, 1, 2, 904, "", 0 },

  { 453, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i_Sway/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i_Sway_Value_m), 21, 1, 2, 906, "",
    0 },

  { 454, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_aa), 21, 1, 2, 908, "", 0 },

  { 455, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_mu), 21, 1, 2, 910, "", 0 },

  { 456, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_b), 21, 1, 2, 912, "", 0 },

  { 457, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i_Yaw/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i_Yaw_Value_c), 21, 1, 2, 914, "",
    0 },

  { 458,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/zeta/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, zeta_IC), 21, 1, 2, 916, "", 0 },

  { 459, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d_Surge/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d_Surge_Value_o), 21, 1, 2, 918,
    "", 0 },

  { 460, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_bk), 21, 1, 2, 920, "", 0 },

  { 461, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_bh), 21, 1, 2, 922, "", 0 },

  { 462, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_p), 21, 1, 2, 924, "", 0 },

  { 463, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d_Sway/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d_Sway_Value_l), 21, 1, 2, 926, "",
    0 },

  { 464, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_g0), 21, 1, 2, 928, "", 0 },

  { 465, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_ew), 21, 1, 2, 930, "", 0 },

  { 466, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_bc), 21, 1, 2, 932, "", 0 },

  { 467, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d_Yaw/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d_Yaw_Value_f), 21, 1, 2, 934, "",
    0 },

  { 468,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s eq/0_2x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x1_Value_n), 37, 2, 2, 936, "", 0
  },

  { 469,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/X_u/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, X_u_Value_c), 21, 1, 2, 938, "", 0 },

  { 470,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-X_u/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, X_u_Gain_p), 21, 1, 2, 940, "", 0 },

  { 471,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_21_Value_c), 21, 1, 2, 942, "",
    0 },

  { 472,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_31_Value_n), 21, 1, 2, 944, "",
    0 },

  { 473,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_12_Value_i), 21, 1, 2, 946, "",
    0 },

  { 474,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Y_v/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_v_Value_k), 21, 1, 2, 948, "", 0 },

  { 475,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_v/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_v_Gain_d), 21, 1, 2, 950, "", 0 },

  { 476,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/N_v/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_v_Value_g), 21, 1, 2, 952, "", 0 },

  { 477,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_v/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, N_v_Gain_a), 21, 1, 2, 954, "", 0 },

  { 478,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_13_Value_p), 21, 1, 2, 956, "",
    0 },

  { 479,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Y_r/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_r_Value_l), 21, 1, 2, 958, "", 0 },

  { 480,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_vr/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_vr_Gain_b), 21, 1, 2, 960, "", 0 },

  { 481,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/N_r/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_r_Value_o), 21, 1, 2, 962, "", 0 },

  { 482,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_r/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, N_r_Gain_j), 21, 1, 2, 964, "", 0 },

  { 483,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/m/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, m_Value_k), 21, 1, 2, 966, "", 0 },

  { 484,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/X_udot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, X_udot_Value_a), 21, 1, 2, 968, "",
    0 },

  { 485,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_21_Value_n), 21, 1, 2, 970, "", 0
  },

  { 486,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_31_Value_h), 21, 1, 2, 972, "", 0
  },

  { 487,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_12_Value_j), 21, 1, 2, 974, "", 0
  },

  { 488,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/Y_vdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_vdot_Value_j), 21, 1, 2, 976, "",
    0 },

  { 489,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/x_g/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, x_g_Value_f), 21, 1, 2, 978, "", 0 },

  { 490,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/N_vdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_vdot_Value_g), 21, 1, 2, 980, "",
    0 },

  { 491,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_13_Value_o), 21, 1, 2, 982, "", 0
  },

  { 492,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/Y_rdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_rdot_Value_f), 21, 1, 2, 984, "",
    0 },

  { 493,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/I_z/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, I_z_Value_o), 21, 1, 2, 986, "", 0 },

  { 494,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/N_rdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_rdot_Value_a), 21, 1, 2, 988, "",
    0 },

  { 495,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/0_2x2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x2_Value_m), 22, 4, 2, 990, "", 0
  },

  { 496,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/omega_q/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, omega_q_IC), 21, 1, 2, 992, "", 0 },

  { 497,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/0_2x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x1_Value_p), 37, 2, 2, 994, "", 0
  },

  { 498,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^t eq/0_2x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x1_Value_j), 37, 2, 2, 996, "", 0
  },

  { 499,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S11/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S11_Value_n), 21, 1, 2, 998, "", 0 },

  { 500,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/R31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R31_Value_j), 21, 1, 2, 1000, "", 0
  },

  { 501,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S12/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, S12_Gain_m), 21, 1, 2, 1002, "", 0 },

  { 502,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S22/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S22_Value_l), 21, 1, 2, 1004, "", 0
  },

  { 503,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S32_Value_m), 21, 1, 2, 1006, "", 0
  },

  { 504,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S13_Value_p), 21, 1, 2, 1008, "", 0
  },

  { 505,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S23_Value_p), 21, 1, 2, 1010, "", 0
  },

  { 506,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S33/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, S33_Value_l), 21, 1, 2, 1012, "", 0
  },

  { 507,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_g), 21, 1, 2, 1014, "", 0
  },

  { 508,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_jo), 21, 1, 2, 1016,
    "", 0 },

  { 509,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_bb), 21, 1, 2, 1018,
    "", 0 },

  { 510,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_XData_e), 46, 9, 2, 1020, "", 0
  },

  { 511,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_YData_k), 46, 9, 2, 1022, "", 0
  },

  { 512,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_Value_a), 21, 1, 2, 1024, "", 0
  },

  { 513,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_XData_o2), 73, 10, 2, 1026, "",
    0 },

  { 514,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_10_YData_d0), 73, 10, 2, 1028, "",
    0 },

  { 515,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_mh), 21, 1, 2, 1030,
    "", 0 },

  { 516,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_hm), 21, 1, 2, 1032,
    "", 0 },

  { 517,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_XData_k), 74, 11, 2, 1034, "",
    0 },

  { 518,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_YData_b), 74, 11, 2, 1036, "",
    0 },

  { 519,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_Value_n), 21, 1, 2, 1038, "", 0
  },

  { 520,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_XData_do), 73, 10, 2, 1040, "",
    0 },

  { 521,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_20_YData_f), 73, 10, 2, 1042, "",
    0 },

  { 522,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_aa), 21, 1, 2, 1044,
    "", 0 },

  { 523,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_hb), 21, 1, 2, 1046,
    "", 0 },

  { 524,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_XData_hd), 75, 8, 2, 1048, "",
    0 },

  { 525,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_YData_g), 75, 8, 2, 1050, "", 0
  },

  { 526,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_Value_e), 21, 1, 2, 1052, "", 0
  },

  { 527,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_XData_j), 74, 11, 2, 1054, "",
    0 },

  { 528,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_30_YData_f), 74, 11, 2, 1056, "",
    0 },

  { 529,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_iv), 21, 1, 2, 1058,
    "", 0 },

  { 530,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_o5), 21, 1, 2, 1060,
    "", 0 },

  { 531,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_XData_l), 73, 10, 2, 1062, "",
    0 },

  { 532,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_YData_g), 73, 10, 2, 1064, "",
    0 },

  { 533,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_Value_c), 21, 1, 2, 1066, "", 0
  },

  { 534,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_XData_b2), 76, 7, 2, 1068, "",
    0 },

  { 535,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_40_YData_n), 76, 7, 2, 1070, "", 0
  },

  { 536,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_h0), 21, 1, 2, 1072,
    "", 0 },

  { 537,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_gq), 21, 1, 2, 1074,
    "", 0 },

  { 538,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_XData_a), 26, 3, 2, 1076, "", 0
  },

  { 539,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_YData_o), 26, 3, 2, 1078, "", 0
  },

  { 540,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_Value_h), 21, 1, 2, 1080, "", 0
  },

  { 541,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_XData_l), 26, 3, 2, 1082, "", 0
  },

  { 542,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, f_50_YData_n), 26, 3, 2, 1084, "", 0
  },

  { 543, "cse1_cv3_1straight/Control Systems/Nonlinear PID/BT_power_limit/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, BT_power_limit_Value_f), 21, 1, 2,
    1086, "", 0 },

  { 544, "cse1_cv3_1straight/Control Systems/Nonlinear PID/VSP_speeds/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, VSP_speeds_Value_d), 21, 1, 2, 1088,
    "", 0 },

  { 545, "cse1_cv3_1straight/Control Systems/Saturation/UpperLimit", offsetof
    (Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_d), 21, 1, 2, 1090, "",
    0 },

  { 546, "cse1_cv3_1straight/Control Systems/Saturation/LowerLimit", offsetof
    (Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_n), 21, 1, 2, 1092, "",
    0 },

  { 547,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e11/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e11_Value_mi), 21, 1, 2, 1094, "",
    0 },

  { 548,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e21_Value_kz), 21, 1, 2, 1096, "",
    0 },

  { 549,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_y1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y1_Value_cw), 21, 1, 2, 1098, "",
    0 },

  { 550,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e12_Value_k), 21, 1, 2, 1100, "",
    0 },

  { 551,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e22/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e22_Value_i), 21, 1, 2, 1102, "",
    0 },

  { 552,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Value_k), 21, 1, 2, 1104, "", 0
  },

  { 553,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/-l_x1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Gain_dp), 21, 1, 2, 1106, "", 0
  },

  { 554,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e13_Value_n), 21, 1, 2, 1108, "",
    0 },

  { 555,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e23_Value_p), 21, 1, 2, 1110, "",
    0 },

  { 556,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_y2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Value_o), 21, 1, 2, 1112, "", 0
  },

  { 557,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/-l_y2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Gain_d), 21, 1, 2, 1114, "", 0
  },

  { 558,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e14/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e14_Value_b), 21, 1, 2, 1116, "",
    0 },

  { 559,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e24/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e24_Value_a), 21, 1, 2, 1118, "",
    0 },

  { 560,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_x2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Value_i), 21, 1, 2, 1120, "", 0
  },

  { 561,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/-l_x2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Gain_c), 21, 1, 2, 1122, "", 0
  },

  { 562,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e15/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e15_Value_f), 21, 1, 2, 1124, "",
    0 },

  { 563,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e25/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e25_Value_bb), 21, 1, 2, 1126, "",
    0 },

  { 564,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_x3/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x3_Value_i), 21, 1, 2, 1128, "", 0
  },

  { 565,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_1 to f_1/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_1tof_1_XData), 77, 19, 2, 1130, "",
    0 },

  { 566,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_1 to f_1/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_1tof_1_YData), 77, 19, 2, 1132, "",
    0 },

  { 567,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_2 to f_2/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_2tof_2_XData), 78, 21, 2, 1134, "",
    0 },

  { 568,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_2 to f_2/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_2tof_2_YData), 78, 21, 2, 1136, "",
    0 },

  { 569,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_3 to f_3/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_3tof_3_XData), 77, 19, 2, 1138, "",
    0 },

  { 570,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_3 to f_3/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_3tof_3_YData), 77, 19, 2, 1140, "",
    0 },

  { 571,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_4 to f_4/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_4tof_4_XData), 79, 17, 2, 1142, "",
    0 },

  { 572,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_4 to f_4/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_4tof_4_YData), 79, 17, 2, 1144, "",
    0 },

  { 573,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_5 to f_5/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_5tof_5_XData), 80, 7, 2, 1146, "",
    0 },

  { 574,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_5 to f_5/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_5tof_5_YData), 80, 7, 2, 1148, "",
    0 },

  { 575,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e11/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e11_Value_b), 21, 1, 2, 1150, "",
    0 },

  { 576,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e21_Value_cm), 21, 1, 2, 1152, "",
    0 },

  { 577,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_y1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y1_Value_d), 21, 1, 2, 1154, "", 0
  },

  { 578,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e12_Value_d), 21, 1, 2, 1156, "",
    0 },

  { 579,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e22/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e22_Value_iv), 21, 1, 2, 1158, "",
    0 },

  { 580,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Value_o), 21, 1, 2, 1160, "", 0
  },

  { 581,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/-l_x1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x1_Gain_k), 21, 1, 2, 1162, "", 0
  },

  { 582,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e13_Value_ol), 21, 1, 2, 1164, "",
    0 },

  { 583,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e23_Value_m), 21, 1, 2, 1166, "",
    0 },

  { 584,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_y2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Value_d), 21, 1, 2, 1168, "", 0
  },

  { 585,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/-l_y2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_y2_Gain_b), 21, 1, 2, 1170, "", 0
  },

  { 586,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e14/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e14_Value_i), 21, 1, 2, 1172, "",
    0 },

  { 587,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e24/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e24_Value_f), 21, 1, 2, 1174, "",
    0 },

  { 588,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_x2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Value_a), 21, 1, 2, 1176, "", 0
  },

  { 589,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/-l_x2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x2_Gain_ik), 21, 1, 2, 1178, "", 0
  },

  { 590,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e15/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e15_Value_d), 21, 1, 2, 1180, "",
    0 },

  { 591,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e25/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, T_e25_Value_j), 21, 1, 2, 1182, "",
    0 },

  { 592,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_x3/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, l_x3_Value_l), 21, 1, 2, 1184, "", 0
  },

  { 593,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_1 to f_1/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_1tof_1_XData_p), 77, 19, 2, 1186,
    "", 0 },

  { 594,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_1 to f_1/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_1tof_1_YData_k), 77, 19, 2, 1188,
    "", 0 },

  { 595,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_2 to f_2/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_2tof_2_XData_o), 78, 21, 2, 1190,
    "", 0 },

  { 596,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_2 to f_2/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_2tof_2_YData_o), 78, 21, 2, 1192,
    "", 0 },

  { 597,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_3 to f_3/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_3tof_3_XData_i), 77, 19, 2, 1194,
    "", 0 },

  { 598,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_3 to f_3/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_3tof_3_YData_i), 77, 19, 2, 1196,
    "", 0 },

  { 599,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_4 to f_4/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_4tof_4_XData_d), 79, 17, 2, 1198,
    "", 0 },

  { 600,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_4 to f_4/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_4tof_4_YData_f), 79, 17, 2, 1200,
    "", 0 },

  { 601,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_5 to f_5/InputValues",
    offsetof(Parameters_CSE1_CV3_1Straight, u_5tof_5_XData_c), 80, 7, 2, 1202,
    "", 0 },

  { 602,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_5 to f_5/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, u_5tof_5_YData_o), 80, 7, 2, 1204,
    "", 0 },

  { 603,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator1/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, Integrator1_IC), 21, 1, 2, 1206, "",
    0 },

  { 604,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 3 deg/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_d3deg_Gain), 21, 1, 2, 1208, "", 0
  },

  { 605,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 3 deg/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_i3deg_Gain), 21, 1, 2, 1210, "", 0
  },

  { 606,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 3 deg/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K_p3deg_Gain), 21, 1, 2, 1212, "", 0
  },

  { 607,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_Psi_deg/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Reg_e_Psi_deg_Gain), 21, 1, 2, 1214,
    "", 0 },

  { 608,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/eta Psi deg/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, etaPsideg_Gain), 21, 1, 2, 1216, "",
    0 },

  { 609,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_k), 38, 9, 2, 1218, "", 0
  },

  { 610,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator2/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, Integrator2_IC_g), 21, 1, 2, 1220,
    "", 0 },

  { 611,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain2_Gain), 38, 9, 2, 1222, "", 0 },

  { 612,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_l), 21, 1, 2,
    1224, "", 0 },

  { 613,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_l), 21, 1, 2,
    1226, "", 0 },

  { 614,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_gh), 21, 1, 2, 1228, "", 0
  },

  { 615,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_pu), 21, 1, 2, 1230,
    "", 0 },

  { 616,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K4/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K4_Gain), 38, 9, 2, 1232, "", 0 },

  { 617,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator3/InitialCondition",
    offsetof(Parameters_CSE1_CV3_1Straight, Integrator3_IC), 21, 1, 2, 1234, "",
    0 },

  { 618,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain6/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain6_Gain), 38, 9, 2, 1236, "", 0 },

  { 619,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain3/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain3_Gain), 38, 9, 2, 1238, "", 0 },

  { 620,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K11/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K11_Gain), 38, 9, 2, 1240, "", 0 },

  { 621,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K12/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K12_Gain), 38, 9, 2, 1242, "", 0 },

  { 622,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K2_Gain), 38, 9, 2, 1244, "", 0 },

  { 623,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K3/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, K3_Gain), 38, 9, 2, 1246, "", 0 },

  { 624,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/inv(T_b)/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, invT_b_Gain), 38, 9, 2, 1248, "", 0
  },

  { 625, "cse1_cv3_1straight/Control Systems/LgV design 2/Gamma_q/12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_eg), 21, 1, 2, 1250, "", 0 },

  { 626, "cse1_cv3_1straight/Control Systems/LgV design 2/Gamma_q/21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_or), 21, 1, 2, 1252, "", 0 },

  { 627, "cse1_cv3_1straight/Control Systems/LgV design 2/Gamma_q_Surge/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Gamma_q_Surge_Value), 21, 1, 2, 1254,
    "", 0 },

  { 628, "cse1_cv3_1straight/Control Systems/LgV design 2/Gamma_q_Sway/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Gamma_q_Sway_Value), 21, 1, 2, 1256,
    "", 0 },

  { 629, "cse1_cv3_1straight/Control Systems/LgV design 2/V_1^q/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_n), 21, 1, 2, 1258, "", 0
  },

  { 630, "cse1_cv3_1straight/Control Systems/LgV design 2/lambda/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, lambda_Value), 21, 1, 2, 1260, "", 0
  },

  { 631, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_h), 21, 1, 2, 1262, "", 0
  },

  { 632, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Gamma_q/12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_cv), 21, 1, 2, 1264, "", 0 },

  { 633, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Gamma_q/21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_pf), 21, 1, 2, 1266, "", 0 },

  { 634, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Gamma_q_Surge/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Gamma_q_Surge_Value_a), 21, 1, 2,
    1268, "", 0 },

  { 635, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Gamma_q_Sway/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Gamma_q_Sway_Value_e), 21, 1, 2,
    1270, "", 0 },

  { 636, "cse1_cv3_1straight/Control Systems/Nonlinear PID/lambda/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, lambda_Value_l), 21, 1, 2, 1272, "",
    0 },

  { 637,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/dot omega_q/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, dotomega_q_Gain), 21, 1, 2, 1274, "",
    0 },

  { 638, "cse1_cv3_1straight/Guidance Systems/DP/eta_d Psi deg/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, eta_dPsideg_Gain), 21, 1, 2, 1276, "", 0 },

  { 639, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In1 FN/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, QTMIn1FN_Gain), 21, 1, 2, 1278, "",
    0 },

  { 640,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, QTMIn2Error_Gain), 21, 1, 2, 1280,
    "", 0 },

  { 641,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Battery Servo/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, BatteryServo_Gain), 21, 1, 2, 1282,
    "", 0 },

  { 642,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Battery Main/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, BatteryMain_Gain), 21, 1, 2, 1284,
    "", 0 },

  { 643,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Battery Bow Thruster/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, BatteryBowThruster_Gain), 21, 1, 2,
    1286, "", 0 },

  { 644, "cse1_cv3_1straight/Plants/saturation/Saturation/UpperLimit", offsetof
    (Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_d0), 21, 1, 2, 1288, "",
    0 },

  { 645, "cse1_cv3_1straight/Plants/saturation/Saturation/LowerLimit", offsetof
    (Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_o0), 21, 1, 2, 1290, "",
    0 },

  { 646, "cse1_cv3_1straight/Plants/saturation/Saturation1/UpperLimit", offsetof
    (Parameters_CSE1_CV3_1Straight, Saturation1_UpperSat), 21, 1, 2, 1292, "", 0
  },

  { 647, "cse1_cv3_1straight/Plants/saturation/Saturation1/LowerLimit", offsetof
    (Parameters_CSE1_CV3_1Straight, Saturation1_LowerSat), 21, 1, 2, 1294, "", 0
  },

  { 648, "cse1_cv3_1straight/Plants/saturation/Saturation2/UpperLimit", offsetof
    (Parameters_CSE1_CV3_1Straight, Saturation2_UpperSat), 21, 1, 2, 1296, "", 0
  },

  { 649, "cse1_cv3_1straight/Plants/saturation/Saturation2/LowerLimit", offsetof
    (Parameters_CSE1_CV3_1Straight, Saturation2_LowerSat), 21, 1, 2, 1298, "", 0
  },

  { 650, "cse1_cv3_1straight/Plants/saturation/plant tau_surge/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, planttau_surge_Gain), 21, 1, 2, 1300, "", 0
  },

  { 651, "cse1_cv3_1straight/Plants/saturation/plant tau_sway/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, planttau_sway_Gain), 21, 1, 2, 1302, "", 0 },

  { 652, "cse1_cv3_1straight/Plants/saturation/plant tau_yaw/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, planttau_yaw_Gain), 21, 1, 2, 1304, "", 0 },

  { 653, "cse1_cv3_1straight/Plants/u_1 plant/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, u_1plant_Gain), 21, 1, 2, 1306, "", 0 },

  { 654, "cse1_cv3_1straight/Plants/u_2 plant/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, u_2plant_Gain), 21, 1, 2, 1308, "", 0 },

  { 655, "cse1_cv3_1straight/Plants/u_3 plant/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, u_3plant_Gain), 21, 1, 2, 1310, "", 0 },

  { 656, "cse1_cv3_1straight/Plants/u_4 plant/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, u_4plant_Gain), 21, 1, 2, 1312, "", 0 },

  { 657, "cse1_cv3_1straight/Plants/u_5 plant/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, u_5plant_Gain), 21, 1, 2, 1314, "", 0 },

  { 658, "cse1_cv3_1straight/Plants/BT power limit plant/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, BTpowerlimitplant_Gain), 21, 1, 2, 1316, "",
    0 },

  { 659, "cse1_cv3_1straight/Plants/VSP speed plant/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, VSPspeedplant_Gain), 21, 1, 2, 1318, "", 0 },

  { 660, "cse1_cv3_1straight/Plants/Enable CSE1/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, EnableCSE1_Value), 21, 1, 2, 1320, "", 0 },

  { 661, "cse1_cv3_1straight/Plants/Constant/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, Constant_Value_n2), 21, 1, 2, 1322, "", 0 },

  { 662, "cse1_cv3_1straight/Plants/Constant1/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, Constant1_Value_k), 21, 1, 2, 1324, "", 0 },

  { 663, "cse1_cv3_1straight/Plants/Port VSP direction/Gain/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, Gain_Gain_c), 21, 1, 2, 1326, "", 0 },

  { 664, "cse1_cv3_1straight/Plants/Starboard VSP direction/Gain/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, Gain_Gain_ee), 21, 1, 2, 1328, "", 0 },

  { 665,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R12/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, R12_Gain), 21, 1, 2, 1330, "", 0 },

  { 666,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R22/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, R22_Gain), 21, 1, 2, 1332, "", 0 },

  { 667,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _Value_m), 21, 1, 2, 1334, "", 0 },

  { 668,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S12/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, S12_Gain_b), 21, 1, 2, 1336, "", 0 },

  { 669,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _Value_p), 21, 1, 2, 1338, "", 0 },

  { 670,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, S12_Gain_p), 21, 1, 2, 1340, "", 0 },

  { 671, "cse1_cv3_1straight/Guidance Systems/Path-following/Delta/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Delta_Value), 21, 1, 2, 1342, "", 0
  },

  { 672,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_km), 21, 1, 2, 1344,
    "", 0 },

  { 673,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_i), 21, 1, 2, 1346, "", 0
  },

  { 674,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_lj), 21, 1, 2,
    1348, "", 0 },

  { 675,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_j), 21, 1, 2,
    1350, "", 0 },

  { 676,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_m), 21, 1, 2, 1352, "", 0
  },

  { 677,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_hm), 21, 1, 2, 1354, "",
    0 },

  { 678,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/0_2x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x1_Value_e), 21, 1, 2, 1356, "", 0
  },

  { 679,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/+ 2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Gain_k), 21, 1, 2, 1358, "", 0 },

  { 680,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_oi), 21, 1, 2, 1360, "", 0
  },

  { 681,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_i), 21, 1, 2,
    1362, "", 0 },

  { 682,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_hv), 21, 1, 2,
    1364, "", 0 },

  { 683,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_ib), 21, 1, 2, 1366, "", 0
  },

  { 684,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_bc), 21, 1, 2, 1368,
    "", 0 },

  { 685,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_a), 21, 1, 2, 1370, "", 0
  },

  { 686,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_nv), 21, 1, 2, 1372, "", 0
  },

  { 687,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_a), 21, 1, 2,
    1374, "", 0 },

  { 688,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_o4), 21, 1, 2,
    1376, "", 0 },

  { 689,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_e1), 21, 1, 2, 1378, "", 0
  },

  { 690,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_ab), 21, 1, 2, 1380,
    "", 0 },

  { 691,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_jx), 21, 1, 2, 1382, "",
    0 },

  { 692,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_dn), 21, 1, 2, 1384, "", 0
  },

  { 693,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/UpperLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_UpperSat_b), 21, 1, 2,
    1386, "", 0 },

  { 694,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/LowerLimit",
    offsetof(Parameters_CSE1_CV3_1Straight, Saturation_LowerSat_g), 21, 1, 2,
    1388, "", 0 },

  { 695,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_p), 21, 1, 2, 1390, "", 0
  },

  { 696,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_nd1), 21, 1, 2, 1392,
    "", 0 },

  { 697,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_p), 21, 1, 2, 1394, "", 0
  },

  { 698,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/I/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_p1), 22, 4, 2, 1396,
    "", 0 },

  { 699,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_pi), 21, 1, 2, 1398, "", 0
  },

  { 700,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/0_2x1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x1_Value_pc), 37, 2, 2, 1400, "",
    0 },

  { 701,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_ghk), 21, 1, 2, 1402, "",
    0 },

  { 702,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_ma), 21, 1, 2, 1404, "", 0
  },

  { 703, "cse1_cv3_1straight/Guidance Systems/Path-following/my/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, my_Value), 21, 1, 2, 1406, "", 0 },

  { 704,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_eo), 21, 1, 2, 1408, "", 0
  },

  { 705,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_m1), 21, 1, 2, 1410, "", 0 },

  { 706,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_oz), 21, 1, 2, 1412, "", 0
  },

  { 707,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_Value_on), 21, 1, 2, 1414, "", 0 },

  { 708,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_po), 21, 1, 2, 1416,
    "", 0 },

  { 709,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_o2), 21, 1, 2, 1418, "", 0
  },

  { 710,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Constant_Value_nh), 21, 1, 2, 1420,
    "", 0 },

  { 711,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _Value_d), 21, 1, 2, 1422, "", 0 },

  { 712,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/0_2x2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _2x2_Value_b), 22, 4, 2, 1424, "", 0
  },

  { 713,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _Value_mn), 21, 1, 2, 1426, "", 0 },

  { 714,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, _Value_h), 21, 1, 2, 1428, "", 0 },

  { 715,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, _Gain_a), 21, 1, 2, 1430, "", 0 },

  { 716,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_f), 21, 1, 2, 1432, "", 0
  },

  { 717, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, BT_D_Gain1_Gain), 21, 1, 2, 1434, "", 0 },

  { 718, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, BT_Power_Offset1_Value), 21, 1, 2,
    1436, "", 0 },

  { 719, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, BT_D_Gain2_Gain), 21, 1, 2, 1438, "", 0 },

  { 720, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, BT_L_Gain1_Gain), 21, 1, 2, 1440, "", 0 },

  { 721, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, BT_L_Gain2_Gain), 21, 1, 2, 1442, "", 0 },

  { 722, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, BT_Power_Offset2_Value), 21, 1, 2,
    1444, "", 0 },

  { 723, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, BT_Power_Offset3_Value), 21, 1, 2,
    1446, "", 0 },

  { 724, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Constant/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, Constant_Value_j3), 21, 1, 2, 1448, "", 0 },

  { 725, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Constant1/Value", offsetof
    (Parameters_CSE1_CV3_1Straight, Constant1_Value_f), 21, 1, 2, 1450, "", 0 },

  { 726, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Neg/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, Neg_Gain), 21, 1, 2, 1452, "", 0 },

  { 727, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /-x/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, x_Gain), 21, 1, 2, 1454, "", 0 },

  { 728, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /-y/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, y_Gain), 21, 1, 2, 1456, "", 0 },

  { 729,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_a3), 21, 1, 2, 1458, "", 0
  },

  { 730,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_cy), 21, 1, 2, 1460, "", 0
  },

  { 731,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo1_RowIdx), 42, 3, 2, 1462, "",
    0 },

  { 732,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo1_ColIdx), 42, 3, 2, 1464, "",
    0 },

  { 733,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo1/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo1_Table), 38, 9, 2, 1466, "", 0
  },

  { 734,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo2_RowIdx), 42, 3, 2, 1468, "",
    0 },

  { 735,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo2_ColIdx), 42, 3, 2, 1470, "",
    0 },

  { 736,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo2/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo2_Table), 38, 9, 2, 1472, "", 0
  },

  { 737,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo3_RowIdx), 42, 3, 2, 1474, "",
    0 },

  { 738,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo3_ColIdx), 42, 3, 2, 1476, "",
    0 },

  { 739,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo3/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo3_Table), 38, 9, 2, 1478, "", 0
  },

  { 740,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo4_RowIdx), 42, 3, 2, 1480, "",
    0 },

  { 741,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo4_ColIdx), 42, 3, 2, 1482, "",
    0 },

  { 742,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo4/Table",
    offsetof(Parameters_CSE1_CV3_1Straight, Servo4_Table), 38, 9, 2, 1484, "", 0
  },

  { 743,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, VPS_Speed_Gain_Gain), 21, 1, 2, 1486,
    "", 0 },

  { 744,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, VPS_Power_Offset_Value), 21, 1, 2,
    1488, "", 0 },

  { 745,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, VSPSPort_Gain), 21, 1, 2, 1490, "",
    0 },

  { 746,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, VSPSStarboard_Gain), 21, 1, 2, 1492,
    "", 0 },

  { 747,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_r/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_r_Value_j), 21, 1, 2, 1494, "", 0
  },

  { 748,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, N_r_Gain_i), 21, 1, 2, 1496, "", 0 },

  { 749,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_v/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_v_Value_c), 21, 1, 2, 1498, "", 0
  },

  { 750,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, N_v_Gain_l), 21, 1, 2, 1500, "", 0 },

  { 751,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/X_u/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, X_u_Value_m), 21, 1, 2, 1502, "", 0
  },

  { 752,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, X_u_Gain_k), 21, 1, 2, 1504, "", 0 },

  { 753,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_v/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_v_Value_kr), 21, 1, 2, 1506, "", 0
  },

  { 754,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_v_Gain_d2), 21, 1, 2, 1508, "", 0
  },

  { 755,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_r/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_r_Value_m), 21, 1, 2, 1510, "", 0
  },

  { 756,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_vr_Gain_j), 21, 1, 2, 1512, "", 0
  },

  { 757,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_12_Value_a), 21, 1, 2, 1514, "",
    0 },

  { 758,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_13_Value_k), 21, 1, 2, 1516, "",
    0 },

  { 759,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_21_Value_a), 21, 1, 2, 1518, "",
    0 },

  { 760,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, D_L_31_Value_k), 21, 1, 2, 1520, "",
    0 },

  { 761,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, psi_0_Value), 21, 1, 2, 1522, "", 0
  },

  { 762,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, x_0_Value), 21, 1, 2, 1524, "", 0 },

  { 763,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, y_0_Value), 21, 1, 2, 1526, "", 0 },

  { 764,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, r_0_Value), 21, 1, 2, 1528, "", 0 },

  { 765,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, u_0_Value), 21, 1, 2, 1530, "", 0 },

  { 766,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, v_0_Value), 21, 1, 2, 1532, "", 0 },

  { 767,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, ResetLinearSimulatorintegrator_), 21,
    1, 2, 1534, "", 0 },

  { 768,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/I_z/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, I_z_Value_a), 21, 1, 2, 1536, "", 0
  },

  { 769,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, m_Value_d), 21, 1, 2, 1538, "", 0 },

  { 770,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/X_udot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, X_udot_Value_b), 21, 1, 2, 1540, "",
    0 },

  { 771,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_21/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_21_Value_c), 21, 1, 2, 1542, "", 0
  },

  { 772,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_31_Value_j), 21, 1, 2, 1544, "", 0
  },

  { 773,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_12/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_12_Value_h), 21, 1, 2, 1546, "", 0
  },

  { 774,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_vdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_vdot_Value_i), 21, 1, 2, 1548, "",
    0 },

  { 775,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/x_g/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, x_g_Value_p), 21, 1, 2, 1550, "", 0
  },

  { 776,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_vdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_vdot_Value_d), 21, 1, 2, 1552, "",
    0 },

  { 777,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, M_13_Value_g), 21, 1, 2, 1554, "", 0
  },

  { 778,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_rdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, Y_rdot_Value_e), 21, 1, 2, 1556, "",
    0 },

  { 779,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_rdot/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, N_rdot_Value_h), 21, 1, 2, 1558, "",
    0 },

  { 780,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R31_Value_f), 21, 1, 2, 1560, "", 0
  },

  { 781,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R32_Value_ag), 21, 1, 2, 1562, "", 0
  },

  { 782,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R13_Value_e), 21, 1, 2, 1564, "", 0
  },

  { 783,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R23_Value_p), 21, 1, 2, 1566, "", 0
  },

  { 784,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_CSE1_CV3_1Straight, R33_Value_en), 21, 1, 2, 1568, "", 0
  },

  { 785, "cse1_cv3_1straight/Plants/Linear Simulator/eta_surge_hil/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, eta_surge_hil_Gain), 21, 1, 2, 1570,
    "", 0 },

  { 786, "cse1_cv3_1straight/Plants/Linear Simulator/eta_sway_hil/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, eta_sway_hil_Gain), 21, 1, 2, 1572,
    "", 0 },

  { 787, "cse1_cv3_1straight/Plants/Linear Simulator/eta_yaw_hil/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, eta_yaw_hil_Gain), 21, 1, 2, 1574, "", 0 },

  { 788, "cse1_cv3_1straight/Plants/Linear Simulator/etadot_surge_hil/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, etadot_surge_hil_Gain), 21, 1, 2,
    1576, "", 0 },

  { 789, "cse1_cv3_1straight/Plants/Linear Simulator/etadot_sway_hil/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, etadot_sway_hil_Gain), 21, 1, 2,
    1578, "", 0 },

  { 790, "cse1_cv3_1straight/Plants/Linear Simulator/etadot_yaw_hil/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, etadot_yaw_hil_Gain), 21, 1, 2, 1580,
    "", 0 },

  { 791, "cse1_cv3_1straight/Plants/Linear Simulator/nu_surge_hil/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, nu_surge_hil_Gain), 21, 1, 2, 1582,
    "", 0 },

  { 792, "cse1_cv3_1straight/Plants/Linear Simulator/nu_sway_hil/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, nu_sway_hil_Gain), 21, 1, 2, 1584, "", 0 },

  { 793, "cse1_cv3_1straight/Plants/Linear Simulator/nu_yaw_hil/Gain", offsetof
    (Parameters_CSE1_CV3_1Straight, nu_yaw_hil_Gain), 21, 1, 2, 1586, "", 0 },

  { 794,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_fo), 40, 1, 2, 1588, "", 0
  },

  { 795,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_g), 40, 1, 2, 1590, "", 0
  },

  { 796,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_g5), 40, 1, 2, 1592, "", 0
  },

  { 797,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_gm), 40, 1, 2, 1594, "",
    0 },

  { 798,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_ga), 40, 1, 2, 1596, "", 0
  },

  { 799,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_af), 40, 1, 2, 1598, "",
    0 },

  { 800,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_l), 40, 1, 2, 1600, "", 0
  },

  { 801,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_ay), 40, 1, 2, 1602, "",
    0 },

  { 802,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_gh3), 40, 1, 2, 1604, "",
    0 },

  { 803,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_l), 40, 1, 2, 1606, "", 0
  },

  { 804,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_ja), 40, 1, 2, 1608, "", 0
  },

  { 805,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_d), 40, 1, 2, 1610, "", 0
  },

  { 806,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_gm), 40, 1, 2, 1612, "", 0
  },

  { 807,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_l5), 40, 1, 2, 1614, "",
    0 },

  { 808,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_dx), 40, 1, 2, 1616, "", 0
  },

  { 809,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_ax), 40, 1, 2, 1618, "",
    0 },

  { 810,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_jb), 40, 1, 2, 1620, "", 0
  },

  { 811,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_f), 40, 1, 2, 1622, "", 0
  },

  { 812,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_d3), 40, 1, 2, 1624, "", 0
  },

  { 813,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_o), 40, 1, 2, 1626, "", 0
  },

  { 814,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_ps), 40, 1, 2, 1628, "", 0
  },

  { 815,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_id), 40, 1, 2, 1630, "",
    0 },

  { 816,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_pu), 40, 1, 2, 1632, "", 0
  },

  { 817,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_j2), 40, 1, 2, 1634, "",
    0 },

  { 818,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_of), 40, 1, 2, 1636, "", 0
  },

  { 819,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_it), 40, 1, 2, 1638, "",
    0 },

  { 820,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_jf), 40, 1, 2, 1640, "", 0
  },

  { 821,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_kr), 40, 1, 2, 1642, "",
    0 },

  { 822,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_eb), 40, 1, 2, 1644, "", 0
  },

  { 823,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_pn), 40, 1, 2, 1646, "",
    0 },

  { 824,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_of2), 40, 1, 2, 1648, "",
    0 },

  { 825,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_c), 40, 1, 2, 1650, "", 0
  },

  { 826,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_j0), 40, 1, 2, 1652, "", 0
  },

  { 827,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_li), 40, 1, 2, 1654, "",
    0 },

  { 828,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_ks), 40, 1, 2, 1656, "", 0
  },

  { 829,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_dn), 40, 1, 2, 1658, "",
    0 },

  { 830,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_jt), 40, 1, 2, 1660, "", 0
  },

  { 831,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_io), 40, 1, 2, 1662, "",
    0 },

  { 832,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain_Gain_oz4), 40, 1, 2, 1664, "",
    0 },

  { 833,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain",
    offsetof(Parameters_CSE1_CV3_1Straight, Gain1_Gain_h0), 40, 1, 2, 1666, "",
    0 },
};

static int NI_ParamListSize = 834;
static int NI_ParamDimList[] = {
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Controller Input Selector/Value */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In3/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/mm2m x/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In4/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/mm2m y/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In6/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/d2r yaw/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Enable Linear Simulator/Value */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/eta_surge/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/eta_sway/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/eta_yaw/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In8/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/d2r roll/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In7/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/d2r pitch/Gain */
  3, 3,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Constant1/Value */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In5/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/mm2m z/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/nu_surge/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/nu_sway/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/nu_yaw/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/Enable eta_d LPF/Value */
  1, 1,                                /* cse1_cv3_1straight/HMI/DP Input/x_d/Value */
  1, 1,                                /* cse1_cv3_1straight/HMI/DP Input/y_d/Value */
  1, 1,                                /* cse1_cv3_1straight/HMI/DP Input/psi_d/Value */
  1, 1,                                /* cse1_cv3_1straight/HMI/DP Input/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn/A */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn/C */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn1/A */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn1/C */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn2/A */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn2/C */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/eta_d DP N/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/eta_d DP E/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/eta_d DP Psi/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Control Mode/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/if Nonlinear PID Control/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Reset q/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/q_0/q_x_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/q_0/q_y_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Reset q/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/q_0/q_x_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/q_0/q_y_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/q_x gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/q_y gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Reset s/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/s_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Reset s/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/s_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/s gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/HMI/Path-following input/u_d/Value */
  1, 1,                                /* cse1_cv3_1straight/HMI/Path-following input/x_1/Value */
  1, 1,                                /* cse1_cv3_1straight/HMI/Path-following input/y_1/Value */
  1, 1,                                /* cse1_cv3_1straight/HMI/Path-following input/x_2/Value */
  1, 1,                                /* cse1_cv3_1straight/HMI/Path-following input/y_2/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Enable Path/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/path x_d/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/path y_d/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/path psi_d/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/u1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/u2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/u3/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_3/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/u4/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_4/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/u5/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_5/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/LabVIEW  BT power/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/LabVIEW VSP speed/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/AS_LY/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/ScalingLY/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/AS_LX/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/ScalingLX/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/AS_RY/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/ScalingRY/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_3/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/AS_RX/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/Scaling_RX/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_4/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/L2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/R2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_5/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/PS3_BT_Power/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/PS3 input/PS3_VSP_Speed/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/tau_surge/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/tau_sway/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/tau_yaw/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_3/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_4/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_5/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Kp_scale/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Enable Filter/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator/InitialCondition */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/eta N/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/eta E/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/eta Psi/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_N_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_E_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_Psi_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Constant/Value */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Kp/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 3/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Reset_DP_integrator/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Integrator/InitialCondition */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Ki/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Ki_scale/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 3/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator4/InitialCondition */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Kd/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Kd_scale/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 3/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP tau_surge/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP tau_sway/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP tau_yaw/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP u_1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP u_2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP u_3/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP u_4/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP u_5/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/BT_power_limit/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/VSP_speeds/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/-1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R33/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_i_Surge/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_i/21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_i/31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_i/12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_i_Sway/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_i/32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_i/13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_i/23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_i_Yaw/Value */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Integral action state/Integrator/InitialCondition */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_d_Surge/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_d/21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_d/31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_d/12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_d_Sway/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_d/32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_d/13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_d/23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_d_Yaw/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/kappa_1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/4/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_p_Surge/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_p/21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_p/31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_p/12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_p_Sway/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_p/32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_p/13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_p/23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/K_p_Yaw/Value */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Virtual control/I/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/q_x/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/q_y/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/psi_los/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  2, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s eq/0_2x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/X_u/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-X_u/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/D_L_21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/D_L_31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/D_L_12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/Y_v/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-Y_v/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/N_v/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-N_v/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/D_L_13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/Y_r/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-Y_vr/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/N_r/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-N_r/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/m/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/X_udot/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/M_21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/M_31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/M_12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/Y_vdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/x_g/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/N_vdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/M_13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/Y_rdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/I_z/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/M/N_rdot/Value */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/I/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S11/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/R31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S12/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S22/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S33/Value */
  2, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^t eq/0_2x1/Value */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/alpha^q/I/Constant/Value */
  2, 2,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/0_2x2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Integrator2/InitialCondition */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/alpha^s/I/Constant/Value */
  2, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/0_2x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/BT_power_limit/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/VSP_speeds/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e11/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_y1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e22/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_y2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_y2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e14/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e24/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e15/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/T_e25/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/l_x3/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R33/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p_Surge/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p_Sway/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p_Yaw/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i_Surge/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i_Sway/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i_Yaw/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/zeta/InitialCondition */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d_Surge/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d_Sway/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d_Yaw/Value */
  2, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s eq/0_2x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/X_u/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-X_u/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Y_v/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_v/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/N_v/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_v/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/D_L_13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Y_r/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_vr/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/N_r/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_r/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/m/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/X_udot/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/Y_vdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/x_g/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/N_vdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/Y_rdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/I_z/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/N_rdot/Value */
  2, 2,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/0_2x2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/omega_q/InitialCondition */
  2, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/0_2x1/Value */
  2, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^t eq/0_2x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S11/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/R31/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S12/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S22/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S32/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S33/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Constant/Value */
  9, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/InputValues */
  9, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 = 0/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Constant/Value */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/InputValues */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 = 0/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Constant/Value */
  8, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/InputValues */
  8, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 = 0/Value */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/InputValues */
  11, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Constant/Value */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/InputValues */
  10, 1,                               /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 = 0/Value */
  7, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/InputValues */
  7, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Constant/Value */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/InputValues */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 = 0/Value */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/InputValues */
  3, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/BT_power_limit/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/VSP_speeds/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e11/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_y1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e22/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/-l_x1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_y2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/-l_y2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e14/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e24/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_x2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/-l_x2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e15/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/T_e25/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/l_x3/Value */
  19, 1,                               /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_1 to f_1/InputValues */
  19, 1,                               /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_1 to f_1/Table */
  21, 1,                               /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_2 to f_2/InputValues */
  21, 1,                               /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_2 to f_2/Table */
  19, 1,                               /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_3 to f_3/InputValues */
  19, 1,                               /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_3 to f_3/Table */
  17, 1,                               /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_4 to f_4/InputValues */
  17, 1,                               /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_4 to f_4/Table */
  1, 7,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_5 to f_5/InputValues */
  1, 7,                                /* cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_5 to f_5/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e11/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_y1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e22/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/-l_x1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e13/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e23/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_y2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/-l_y2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e14/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e24/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_x2/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/-l_x2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e15/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/T_e25/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/l_x3/Value */
  19, 1,                               /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_1 to f_1/InputValues */
  19, 1,                               /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_1 to f_1/Table */
  21, 1,                               /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_2 to f_2/InputValues */
  21, 1,                               /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_2 to f_2/Table */
  19, 1,                               /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_3 to f_3/InputValues */
  19, 1,                               /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_3 to f_3/Table */
  17, 1,                               /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_4 to f_4/InputValues */
  17, 1,                               /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_4 to f_4/Table */
  1, 7,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_5 to f_5/InputValues */
  1, 7,                                /* cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_5 to f_5/Table */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator1/InitialCondition */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 3 deg/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 3 deg/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 3 deg/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_Psi_deg/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/DP controller/eta Psi deg/Gain */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator2/InitialCondition */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Constant/Value */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K4/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator3/InitialCondition */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain6/Gain */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain3/Gain */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K11/Gain */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K12/Gain */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K2/Gain */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K3/Gain */
  3, 3,                                /* cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/inv(T_b)/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Gamma_q/12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Gamma_q/21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Gamma_q_Surge/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Gamma_q_Sway/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/V_1^q/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/lambda/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Gamma_q/12/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Gamma_q/21/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Gamma_q_Surge/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Gamma_q_Sway/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/lambda/Value */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/dot omega_q/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/DP/eta_d Psi deg/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In1 FN/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Battery Servo/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Battery Main/Gain */
  1, 1,                                /* cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Battery Bow Thruster/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/saturation/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Plants/saturation/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Plants/saturation/Saturation1/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Plants/saturation/Saturation1/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Plants/saturation/Saturation2/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Plants/saturation/Saturation2/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Plants/saturation/plant tau_surge/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/saturation/plant tau_sway/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/saturation/plant tau_yaw/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/u_1 plant/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/u_2 plant/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/u_3 plant/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/u_4 plant/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/u_5 plant/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/BT power limit plant/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/VSP speed plant/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Enable CSE1/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Constant1/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Port VSP direction/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Starboard VSP direction/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R12/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R22/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/0/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S12/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Delta/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/0_2x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/+ 2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/UpperLimit */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation/LowerLimit */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians/Gain1/Gain */
  2, 2,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/I/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Gain/Gain */
  2, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/0_2x1/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/my/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Value */
  2, 2,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/0_2x2/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Value */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Constant/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Constant1/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Neg/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /-y/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard/Gain/Gain */
  1, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_r/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/N_v/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/X_u/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_v/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Y_r/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_12/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_13/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_21/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/D_L_31/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Reset Linear Simulator integrator/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/I_z/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/X_udot/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_21/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_31/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_12/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_vdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/x_g/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_vdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_13/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Y_rdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/N_rdot/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/eta_surge_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/eta_sway_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/eta_yaw_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/etadot_surge_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/etadot_sway_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/etadot_yaw_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/nu_surge_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/nu_sway_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Plants/Linear Simulator/nu_yaw_hil/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain/Gain */
  1, 1,                                /* cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 968;
static NI_Signal NI_SigList[] = {
  { 0, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn), BLOCKIO_SIG, 46, 9, 2, 0, 0 },

  { 1, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In9 Residual",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn9Residual), BLOCKIO_SIG, 21,
    1, 2, 2, 0 },

  { 2, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In3", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn3), BLOCKIO_SIG, 21, 1, 2, 4, 0 },

  { 3, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/mm2m x", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, mm2mx), BLOCKIO_SIG, 21, 1, 2, 6, 0 },

  { 4, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In4", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn4), BLOCKIO_SIG, 21, 1, 2, 8, 0 },

  { 5, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/mm2m y", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, mm2my), BLOCKIO_SIG, 21, 1, 2, 10, 0 },

  { 6, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In6", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn6), BLOCKIO_SIG, 21, 1, 2, 12, 0 },

  { 7, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/d2r yaw", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, d2ryaw), BLOCKIO_SIG, 21, 1, 2, 14, 0 },

  { 8, "cse1_cv3_1straight/Naviagation Systems/Eta Switch", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, EtaSwitch), BLOCKIO_SIG, 24, 3, 2, 16, 0 },

  { 9, "cse1_cv3_1straight/Naviagation Systems/eta_surge", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, eta_surge), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "cse1_cv3_1straight/Naviagation Systems/eta_sway", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, eta_sway), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "cse1_cv3_1straight/Naviagation Systems/eta_yaw", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, eta_yaw), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In8", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn8), BLOCKIO_SIG, 21, 1, 2, 24, 0 },

  { 13, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/d2r roll", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, d2rroll), BLOCKIO_SIG, 21, 1, 2, 26, 0
  },

  { 14, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In7", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn7), BLOCKIO_SIG, 21, 1, 2, 28, 0 },

  { 15, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/d2r pitch", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, d2rpitch), BLOCKIO_SIG, 21, 1, 2, 30, 0
  },

  { 16,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, sintheta), BLOCKIO_SIG, 24, 3, 2,
    32, 0 },

  { 17,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, costheta), BLOCKIO_SIG, 24, 3, 2,
    34, 0 },

  { 18,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R11), BLOCKIO_SIG, 0, 1, 2, 36,
    0 },

  { 19,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R21), BLOCKIO_SIG, 0, 1, 2, 38,
    0 },

  { 20,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R31), BLOCKIO_SIG, 0, 1, 2, 40,
    0 },

  { 21,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R12), BLOCKIO_SIG, 0, 1, 2, 42,
    0 },

  { 22,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R22), BLOCKIO_SIG, 0, 1, 2, 44,
    0 },

  { 23,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R32), BLOCKIO_SIG, 0, 1, 2, 46,
    0 },

  { 24,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R13), BLOCKIO_SIG, 0, 1, 2, 48,
    0 },

  { 25,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R23), BLOCKIO_SIG, 0, 1, 2, 50,
    0 },

  { 26,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R33), BLOCKIO_SIG, 0, 1, 2, 52,
    0 },

  { 27,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Reshape9x13x3), BLOCKIO_SIG, 38,
    9, 2, 54, 0 },

  { 28,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Matrix Concatenate2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MatrixConcatenate2), BLOCKIO_SIG,
    48, 36, 2, 56, 0 },

  { 29, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In5", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn5), BLOCKIO_SIG, 21, 1, 2, 58, 0 },

  { 30, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/mm2m z", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, mm2mz), BLOCKIO_SIG, 21, 1, 2, 60, 0 },

  { 31, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/nu", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, nu), BLOCKIO_SIG, 43, 6, 2, 62, 0 },

  { 32, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Product", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Product), BLOCKIO_SIG, 43, 6, 2, 64, 0
  },

  { 33, "cse1_cv3_1straight/Naviagation Systems/Nu Switch", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, NuSwitch), BLOCKIO_SIG, 24, 3, 2, 66, 0 },

  { 34, "cse1_cv3_1straight/Naviagation Systems/nu_surge", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, nu_surge), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35, "cse1_cv3_1straight/Naviagation Systems/nu_sway", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, nu_sway), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36, "cse1_cv3_1straight/Naviagation Systems/nu_yaw", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, nu_yaw), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37, "cse1_cv3_1straight/HMI/DP Input/Degrees to Radians/Gain1", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Gain1), BLOCKIO_SIG, 0, 1, 2, 74, 0 },

  { 38, "cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, TransferFcn), BLOCKIO_SIG, 0, 1, 2, 76, 0 },

  { 39, "cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn1", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, TransferFcn1), BLOCKIO_SIG, 0, 1, 2, 78, 0 },

  { 40, "cse1_cv3_1straight/Guidance Systems/DP/Transfer Fcn2", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, TransferFcn2), BLOCKIO_SIG, 0, 1, 2, 80, 0 },

  { 41, "cse1_cv3_1straight/Guidance Systems/DP/Multiport Switch", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch), BLOCKIO_SIG, 24, 3, 2,
    82, 0 },

  { 42, "cse1_cv3_1straight/Guidance Systems/DP/eta_d DP N", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, eta_dDPN), BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43, "cse1_cv3_1straight/Guidance Systems/DP/eta_d DP E", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, eta_dDPE), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44, "cse1_cv3_1straight/Guidance Systems/DP/eta_d DP Psi", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, eta_dDPPsi), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/q_0/q_x_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, q_x_0), BLOCKIO_SIG, 0, 1, 2, 90,
    0 },

  { 46, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/q_0/q_y_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, q_y_0), BLOCKIO_SIG, 0, 1, 2, 92,
    0 },

  { 47, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Integrator",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Integrator), BLOCKIO_SIG, 23, 2,
    2, 94, 0 },

  { 48, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/q_0/q_x_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, q_x_0_c), BLOCKIO_SIG, 0, 1, 2,
    96, 0 },

  { 49, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/q_0/q_y_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, q_y_0_p), BLOCKIO_SIG, 0, 1, 2,
    98, 0 },

  { 50,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Integrator", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Integrator_i), BLOCKIO_SIG, 23, 2,
    2, 100, 0 },

  { 51, "cse1_cv3_1straight/Control Systems/q switch", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, qswitch), BLOCKIO_SIG, 23, 2, 2, 102, 0 },

  { 52, "cse1_cv3_1straight/Control Systems/q_x gain", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, q_xgain), BLOCKIO_SIG, 0, 1, 2, 104, 0 },

  { 53, "cse1_cv3_1straight/Control Systems/q_y gain", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, q_ygain), BLOCKIO_SIG, 0, 1, 2, 106, 0 },

  { 54, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/s_0", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, s_0), BLOCKIO_SIG, 0, 1, 2, 108, 0 },

  { 55,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Integrator1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Integrator1), BLOCKIO_SIG, 21, 1, 2,
    110, 0 },

  { 56, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/s_0", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, s_0_d), BLOCKIO_SIG, 0, 1, 2, 112,
    0 },

  { 57,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Integrator1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Integrator1_f), BLOCKIO_SIG, 21,
    1, 2, 114, 0 },

  { 58, "cse1_cv3_1straight/Control Systems/s switch", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, sswitch), BLOCKIO_SIG, 0, 1, 2, 116, 0 },

  { 59, "cse1_cv3_1straight/Control Systems/s gain", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, sgain), BLOCKIO_SIG, 0, 1, 2, 118, 0 },

  { 60, "cse1_cv3_1straight/Guidance Systems/path x_d", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, pathx_d), BLOCKIO_SIG, 0, 1, 2, 120, 0 },

  { 61, "cse1_cv3_1straight/Guidance Systems/path y_d", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, pathy_d), BLOCKIO_SIG, 0, 1, 2, 122, 0 },

  { 62, "cse1_cv3_1straight/Guidance Systems/path psi_d", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, pathpsi_d), BLOCKIO_SIG, 0, 1, 2, 124, 0 },

  { 63, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, LabVIEWu_1), BLOCKIO_SIG, 0, 1, 2,
    126, 0 },

  { 64, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, LabVIEWu_2), BLOCKIO_SIG, 0, 1, 2,
    128, 0 },

  { 65, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_3", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, LabVIEWu_3), BLOCKIO_SIG, 0, 1, 2,
    130, 0 },

  { 66, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_4", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, LabVIEWu_4), BLOCKIO_SIG, 0, 1, 2,
    132, 0 },

  { 67, "cse1_cv3_1straight/Control Systems/Precision control/LabVIEW u_5", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, LabVIEWu_5), BLOCKIO_SIG, 0, 1, 2,
    134, 0 },

  { 68, "cse1_cv3_1straight/Control Systems/PS3 input/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof
    (BlockIO_CSE1_CV3_1Straight, ypositionofleftanalogstick11), BLOCKIO_SIG, 0,
    1, 2, 136, 0 },

  { 69, "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_1", 0,
    "u_1", offsetof(BlockIO_CSE1_CV3_1Straight, u_1), BLOCKIO_SIG, 0, 1, 2, 138,
    0 },

  { 70, "cse1_cv3_1straight/Control Systems/PS3 input/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof
    (BlockIO_CSE1_CV3_1Straight, xpositionofleftanalogstick11), BLOCKIO_SIG, 0,
    1, 2, 140, 0 },

  { 71, "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_2", 0,
    "u_2", offsetof(BlockIO_CSE1_CV3_1Straight, u_2), BLOCKIO_SIG, 0, 1, 2, 142,
    0 },

  { 72, "cse1_cv3_1straight/Control Systems/PS3 input/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof
    (BlockIO_CSE1_CV3_1Straight, ypositionofrightanalogstick11), BLOCKIO_SIG, 0,
    1, 2, 144, 0 },

  { 73, "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_3", 0,
    "u_3", offsetof(BlockIO_CSE1_CV3_1Straight, u_3), BLOCKIO_SIG, 0, 1, 2, 146,
    0 },

  { 74, "cse1_cv3_1straight/Control Systems/PS3 input/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof
    (BlockIO_CSE1_CV3_1Straight, xpositionofrightanalogstick11), BLOCKIO_SIG, 0,
    1, 2, 148, 0 },

  { 75, "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_4", 0,
    "u_4", offsetof(BlockIO_CSE1_CV3_1Straight, u_4), BLOCKIO_SIG, 0, 1, 2, 150,
    0 },

  { 76, "cse1_cv3_1straight/Control Systems/Manual Thruster control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_CSE1_CV3_1Straight,
    BowThrusterdirection), BLOCKIO_SIG, 0, 1, 2, 152, 0 },

  { 77, "cse1_cv3_1straight/Control Systems/Manual Thruster control/PS3 u_5", 0,
    "u_5", offsetof(BlockIO_CSE1_CV3_1Straight, u_5), BLOCKIO_SIG, 0, 1, 2, 154,
    0 },

  { 78,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x1), BLOCKIO_SIG, 0, 1, 2, 156,
    0 },

  { 79,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_y2), BLOCKIO_SIG, 0, 1, 2, 158,
    0 },

  { 80,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x2), BLOCKIO_SIG, 0, 1, 2, 160,
    0 },

  { 81,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x5), BLOCKIO_SIG, 33, 15, 2, 162,
    0 },

  { 82,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Pseudoinverse), BLOCKIO_SIG, 32,
    15, 2, 164, 0 },

  { 83, "cse1_cv3_1straight/Control Systems/Simple Control/Sum1", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Sum1), BLOCKIO_SIG, 0, 1, 2, 166, 0 },

  { 84, "cse1_cv3_1straight/Control Systems/Simple Control/tau_surge", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, tau_surge), BLOCKIO_SIG, 0, 1, 2, 168,
    0 },

  { 85, "cse1_cv3_1straight/Control Systems/Simple Control/Sum2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Sum2), BLOCKIO_SIG, 0, 1, 2, 170, 0 },

  { 86, "cse1_cv3_1straight/Control Systems/Simple Control/tau_sway", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, tau_sway), BLOCKIO_SIG, 0, 1, 2, 172, 0
  },

  { 87, "cse1_cv3_1straight/Control Systems/Simple Control/Sum", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Sum), BLOCKIO_SIG, 0, 1, 2, 174, 0 },

  { 88, "cse1_cv3_1straight/Control Systems/Simple Control/tau_yaw", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, tau_yaw), BLOCKIO_SIG, 0, 1, 2, 176, 0
  },

  { 89,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_c), BLOCKIO_SIG, 31, 5,
    2, 178, 0 },

  { 90,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_10), BLOCKIO_SIG, 0, 1, 2, 180,
    0 },

  { 91,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_10_i), BLOCKIO_SIG, 0, 1, 2,
    182, 0 },

  { 92,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_p), BLOCKIO_SIG,
    0, 1, 2, 184, 0 },

  { 93,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_20), BLOCKIO_SIG, 0, 1, 2, 186,
    0 },

  { 94,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_20_k), BLOCKIO_SIG, 0, 1, 2,
    188, 0 },

  { 95,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_pq), BLOCKIO_SIG,
    0, 1, 2, 190, 0 },

  { 96,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_30), BLOCKIO_SIG, 0, 1, 2, 192,
    0 },

  { 97,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_30_i), BLOCKIO_SIG, 0, 1, 2,
    194, 0 },

  { 98,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_l), BLOCKIO_SIG,
    0, 1, 2, 196, 0 },

  { 99,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_40), BLOCKIO_SIG, 0, 1, 2, 198,
    0 },

  { 100,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_40_n), BLOCKIO_SIG, 0, 1, 2,
    200, 0 },

  { 101,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_g), BLOCKIO_SIG,
    0, 1, 2, 202, 0 },

  { 102,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_50), BLOCKIO_SIG, 0, 1, 2, 204,
    0 },

  { 103,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_50_g), BLOCKIO_SIG, 0, 1, 2,
    206, 0 },

  { 104,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_a), BLOCKIO_SIG,
    0, 1, 2, 208, 0 },

  { 105, "cse1_cv3_1straight/Control Systems/Simple Control/Saturation", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Saturation), BLOCKIO_SIG, 31, 5, 2, 210,
    0 },

  { 106, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_1", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Joysticku_1), BLOCKIO_SIG, 0, 1, 2, 212,
    0 },

  { 107, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Joysticku_2), BLOCKIO_SIG, 0, 1, 2, 214,
    0 },

  { 108, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_3", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Joysticku_3), BLOCKIO_SIG, 0, 1, 2, 216,
    0 },

  { 109, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_4", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Joysticku_4), BLOCKIO_SIG, 0, 1, 2, 218,
    0 },

  { 110, "cse1_cv3_1straight/Control Systems/Simple Control/Joystick u_5", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Joysticku_5), BLOCKIO_SIG, 0, 1, 2, 220,
    0 },

  { 111,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x1_k), BLOCKIO_SIG, 0, 1, 2,
    222, 0 },

  { 112,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_y2_f), BLOCKIO_SIG, 0, 1, 2,
    224, 0 },

  { 113,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x2_a), BLOCKIO_SIG, 0, 1, 2,
    226, 0 },

  { 114,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x5_i), BLOCKIO_SIG, 33, 15, 2,
    228, 0 },

  { 115,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Pseudoinverse_g), BLOCKIO_SIG,
    32, 15, 2, 230, 0 },

  { 116,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator",
    0, "eta", offsetof(BlockIO_CSE1_CV3_1Straight, eta), BLOCKIO_SIG, 24, 3, 2,
    232, 0 },

  { 117,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_c), BLOCKIO_SIG, 0, 1,
    2, 234, 0 },

  { 118,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign), BLOCKIO_SIG, 0, 1, 2, 236,
    0 },

  { 119,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain), BLOCKIO_SIG, 0, 1, 2, 238,
    0 },

  { 120,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_k), BLOCKIO_SIG, 0, 1, 2,
    240, 0 },

  { 121,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction), BLOCKIO_SIG, 0, 1,
    2, 242, 0 },

  { 122,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_m), BLOCKIO_SIG, 0, 1, 2,
    244, 0 },

  { 123, "cse1_cv3_1straight/Control Systems/DP control/Multiport Switch", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_b), BLOCKIO_SIG, 24, 3,
    2, 246, 0 },

  { 124, "cse1_cv3_1straight/Control Systems/DP control/DP controller/yaw angle",
    0, "psi", offsetof(BlockIO_CSE1_CV3_1Straight, psi), BLOCKIO_SIG, 0, 1, 2,
    248, 0 },

  { 125,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_p), BLOCKIO_SIG, 0, 1,
    2, 250, 0 },

  { 126,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_o), BLOCKIO_SIG, 0, 1, 2,
    252, 0 },

  { 127,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_c), BLOCKIO_SIG, 0, 1, 2,
    254, 0 },

  { 128,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_o), BLOCKIO_SIG, 0, 1, 2,
    256, 0 },

  { 129,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_j), BLOCKIO_SIG, 0,
    1, 2, 258, 0 },

  { 130,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_o), BLOCKIO_SIG, 0, 1, 2,
    260, 0 },

  { 131, "cse1_cv3_1straight/Control Systems/DP control/DP controller/eta N", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, etaN), BLOCKIO_SIG, 0, 1, 2, 262, 0
  },

  { 132, "cse1_cv3_1straight/Control Systems/DP control/DP controller/eta E", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, etaE), BLOCKIO_SIG, 0, 1, 2, 264, 0
  },

  { 133, "cse1_cv3_1straight/Control Systems/DP control/DP controller/eta Psi",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, etaPsi), BLOCKIO_SIG, 0, 1, 2,
    266, 0 },

  { 134, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Sum2", 0,
    "regulation error", offsetof(BlockIO_CSE1_CV3_1Straight, regulationerror),
    BLOCKIO_SIG, 24, 3, 2, 268, 0 },

  { 135,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_N_hil", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Reg_e_N_hil), BLOCKIO_SIG, 0, 1, 2,
    270, 0 },

  { 136,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_E_hil", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Reg_e_E_hil), BLOCKIO_SIG, 0, 1, 2,
    272, 0 },

  { 137,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_Psi_hil",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Reg_e_Psi_hil), BLOCKIO_SIG, 0,
    1, 2, 274, 0 },

  { 138,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_a), BLOCKIO_SIG, 0, 1,
    2, 276, 0 },

  { 139,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_m), BLOCKIO_SIG, 0, 1, 2,
    278, 0 },

  { 140,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_ce), BLOCKIO_SIG, 0, 1, 2,
    280, 0 },

  { 141,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_h), BLOCKIO_SIG, 0, 1, 2,
    282, 0 },

  { 142,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_e), BLOCKIO_SIG, 0,
    1, 2, 284, 0 },

  { 143,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_i), BLOCKIO_SIG, 0, 1, 2,
    286, 0 },

  { 144,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Row1), BLOCKIO_SIG, 0, 1, 2, 288,
    0 },

  { 145,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Row2), BLOCKIO_SIG, 0, 1, 2, 290,
    0 },

  { 146,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Row3), BLOCKIO_SIG, 0, 1, 2, 292,
    0 },

  { 147, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Kp", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Kp), BLOCKIO_SIG, 24, 3, 2, 294, 0 },

  { 148, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2), BLOCKIO_SIG, 24, 3, 2,
    296, 0 },

  { 149, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, K_p1), BLOCKIO_SIG, 0, 1, 2, 298, 0
  },

  { 150, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, K_p2), BLOCKIO_SIG, 0, 1, 2, 300, 0
  },

  { 151, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 3", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, K_p3), BLOCKIO_SIG, 0, 1, 2, 302, 0
  },

  { 152,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Integrator", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Integrator_o), BLOCKIO_SIG, 24, 3,
    2, 304, 0 },

  { 153, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Ki", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Ki), BLOCKIO_SIG, 24, 3, 2, 306, 0 },

  { 154, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1), BLOCKIO_SIG, 24, 3, 2,
    308, 0 },

  { 155, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, K_i1), BLOCKIO_SIG, 0, 1, 2, 310, 0
  },

  { 156, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, K_i2), BLOCKIO_SIG, 0, 1, 2, 312, 0
  },

  { 157, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 3", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, K_i3), BLOCKIO_SIG, 0, 1, 2, 314, 0
  },

  { 158, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Sum3", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum3), BLOCKIO_SIG, 24, 3, 2, 316,
    0 },

  { 159,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator4",
    0, "nu", offsetof(BlockIO_CSE1_CV3_1Straight, nu_d), BLOCKIO_SIG, 24, 3, 2,
    318, 0 },

  { 160, "cse1_cv3_1straight/Control Systems/DP control/Multiport Switch1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch1), BLOCKIO_SIG, 24,
    3, 2, 320, 0 },

  { 161, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Kd", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Kd), BLOCKIO_SIG, 24, 3, 2, 322, 0 },

  { 162, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_l), BLOCKIO_SIG, 24, 3,
    2, 324, 0 },

  { 163, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, K_d1), BLOCKIO_SIG, 0, 1, 2, 326, 0
  },

  { 164, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, K_d2), BLOCKIO_SIG, 0, 1, 2, 328, 0
  },

  { 165, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 3", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, K_d3), BLOCKIO_SIG, 0, 1, 2, 330, 0
  },

  { 166, "cse1_cv3_1straight/Control Systems/DP control/DP controller/Sum1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_j), BLOCKIO_SIG, 24, 3, 2, 332,
    0 },

  { 167, "cse1_cv3_1straight/Control Systems/DP control/DP tau_surge", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, DPtau_surge), BLOCKIO_SIG, 0, 1, 2, 334,
    0 },

  { 168, "cse1_cv3_1straight/Control Systems/DP control/DP tau_sway", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, DPtau_sway), BLOCKIO_SIG, 0, 1, 2, 336,
    0 },

  { 169, "cse1_cv3_1straight/Control Systems/DP control/DP tau_yaw", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, DPtau_yaw), BLOCKIO_SIG, 0, 1, 2, 338,
    0 },

  { 170,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_f), BLOCKIO_SIG, 31, 5,
    2, 340, 0 },

  { 171,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_10_m), BLOCKIO_SIG, 0, 1, 2,
    342, 0 },

  { 172,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_10_l), BLOCKIO_SIG, 0, 1, 2,
    344, 0 },

  { 173,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_i), BLOCKIO_SIG,
    0, 1, 2, 346, 0 },

  { 174, "cse1_cv3_1straight/Control Systems/DP control/DP u_1", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, DPu_1), BLOCKIO_SIG, 0, 1, 2, 348, 0 },

  { 175,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_20_d), BLOCKIO_SIG, 0, 1, 2,
    350, 0 },

  { 176,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_20_a), BLOCKIO_SIG, 0, 1, 2,
    352, 0 },

  { 177,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_l3), BLOCKIO_SIG,
    0, 1, 2, 354, 0 },

  { 178, "cse1_cv3_1straight/Control Systems/DP control/DP u_2", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, DPu_2), BLOCKIO_SIG, 0, 1, 2, 356, 0 },

  { 179,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_30_e), BLOCKIO_SIG, 0, 1, 2,
    358, 0 },

  { 180,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_30_f), BLOCKIO_SIG, 0, 1, 2,
    360, 0 },

  { 181,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_j), BLOCKIO_SIG,
    0, 1, 2, 362, 0 },

  { 182, "cse1_cv3_1straight/Control Systems/DP control/DP u_3", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, DPu_3), BLOCKIO_SIG, 0, 1, 2, 364, 0 },

  { 183,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_40_c), BLOCKIO_SIG, 0, 1, 2,
    366, 0 },

  { 184,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_40_g), BLOCKIO_SIG, 0, 1, 2,
    368, 0 },

  { 185,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_c), BLOCKIO_SIG,
    0, 1, 2, 370, 0 },

  { 186, "cse1_cv3_1straight/Control Systems/DP control/DP u_4", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, DPu_4), BLOCKIO_SIG, 0, 1, 2, 372, 0 },

  { 187,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_50_o), BLOCKIO_SIG, 0, 1, 2,
    374, 0 },

  { 188,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_50_p), BLOCKIO_SIG, 0, 1, 2,
    376, 0 },

  { 189,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_m), BLOCKIO_SIG,
    0, 1, 2, 378, 0 },

  { 190, "cse1_cv3_1straight/Control Systems/DP control/DP u_5", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, DPu_5), BLOCKIO_SIG, 0, 1, 2, 380, 0 },

  { 191, "cse1_cv3_1straight/Control Systems/DP control/Saturation", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_cs), BLOCKIO_SIG, 31, 5, 2,
    382, 0 },

  { 192,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x1_a), BLOCKIO_SIG, 0, 1, 2,
    384, 0 },

  { 193,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_y2_i), BLOCKIO_SIG, 0, 1, 2,
    386, 0 },

  { 194,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x2_d), BLOCKIO_SIG, 0, 1, 2,
    388, 0 },

  { 195,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x5_p), BLOCKIO_SIG, 33, 15, 2,
    390, 0 },

  { 196,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Pseudoinverse_o), BLOCKIO_SIG,
    32, 15, 2, 392, 0 },

  { 197, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R11", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, R11_a), BLOCKIO_SIG, 0, 1, 2, 394, 0 },

  { 198, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R21", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, R21_l), BLOCKIO_SIG, 0, 1, 2, 396, 0 },

  { 199, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R12", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, R12_i), BLOCKIO_SIG, 0, 1, 2, 398, 0 },

  { 200, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/-1", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, u), BLOCKIO_SIG, 0, 1, 2, 400, 0 },

  { 201, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R22", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, R22_c), BLOCKIO_SIG, 0, 1, 2, 402, 0 },

  { 202, "cse1_cv3_1straight/Control Systems/LgV design 2/R(psi)/R(psi)", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Rpsi), BLOCKIO_SIG, 38, 9, 2, 404, 0 },

  { 203, "cse1_cv3_1straight/Control Systems/LgV design 2/R^T/Math Function", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_l), BLOCKIO_SIG, 38, 9,
    2, 406, 0 },

  { 204, "cse1_cv3_1straight/Control Systems/LgV design 2/K_i/3x3", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, x3), BLOCKIO_SIG, 38, 9, 2, 408, 0 },

  { 205,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Integral action state/Integrator",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Integrator_n), BLOCKIO_SIG, 26,
    3, 2, 410, 0 },

  { 206, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_p), BLOCKIO_SIG, 26, 3,
    2, 412, 0 },

  { 207, "cse1_cv3_1straight/Control Systems/LgV design 2/K_d/3x3", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, x3_g), BLOCKIO_SIG, 38, 9, 2, 414, 0 },

  { 208, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/4", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, u_i), BLOCKIO_SIG, 0, 1, 2, 416, 0 },

  { 209, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Divide", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide), BLOCKIO_SIG, 0, 1, 2, 418,
    0 },

  { 210, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Add1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Add1), BLOCKIO_SIG, 38, 9, 2, 420,
    0 },

  { 211, "cse1_cv3_1straight/Control Systems/LgV design 2/K_p/R(psi)", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Rpsi_n), BLOCKIO_SIG, 38, 9, 2, 422, 0
  },

  { 212,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Virtual control/Product", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_n), BLOCKIO_SIG, 38, 9, 2,
    424, 0 },

  { 213,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Virtual control/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract), BLOCKIO_SIG, 38, 9, 2,
    426, 0 },

  { 214,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_j), BLOCKIO_SIG, 0, 1, 2,
    428, 0 },

  { 215,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_o), BLOCKIO_SIG, 0, 1,
    2, 430, 0 },

  { 216,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_n), BLOCKIO_SIG, 0, 1, 2,
    432, 0 },

  { 217,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_d), BLOCKIO_SIG, 0, 1, 2,
    434, 0 },

  { 218,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_p), BLOCKIO_SIG, 0, 1, 2,
    436, 0 },

  { 219,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_g), BLOCKIO_SIG, 0,
    1, 2, 438, 0 },

  { 220,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_n), BLOCKIO_SIG, 0, 1, 2,
    440, 0 },

  { 221,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_k), BLOCKIO_SIG, 0, 1, 2,
    442, 0 },

  { 222, "cse1_cv3_1straight/Guidance Systems/q_x", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, q_x), BLOCKIO_SIG, 0, 1, 2, 444, 0 },

  { 223, "cse1_cv3_1straight/Guidance Systems/q_y", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, q_y), BLOCKIO_SIG, 0, 1, 2, 446, 0 },

  { 224, "cse1_cv3_1straight/Guidance Systems/psi_los", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, psi_los), BLOCKIO_SIG, 0, 1, 2, 448, 0 },

  { 225, "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/Subtract", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_l), BLOCKIO_SIG, 24, 3, 2,
    450, 0 },

  { 226,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_f), BLOCKIO_SIG, 0, 1, 2,
    452, 0 },

  { 227,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_l), BLOCKIO_SIG, 0, 1,
    2, 454, 0 },

  { 228,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_i), BLOCKIO_SIG, 0, 1, 2,
    456, 0 },

  { 229,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_h), BLOCKIO_SIG, 0, 1, 2,
    458, 0 },

  { 230,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_jz), BLOCKIO_SIG, 0, 1, 2,
    460, 0 },

  { 231,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_a), BLOCKIO_SIG, 0,
    1, 2, 462, 0 },

  { 232,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_g), BLOCKIO_SIG, 0, 1, 2,
    464, 0 },

  { 233,
    "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_l), BLOCKIO_SIG, 0, 1, 2,
    466, 0 },

  { 234, "cse1_cv3_1straight/Control Systems/LgV design 2/z_1 eq/Product", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Product_j), BLOCKIO_SIG, 24, 3, 2, 468,
    0 },

  { 235,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Virtual control/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_b), BLOCKIO_SIG, 24, 3,
    2, 470, 0 },

  { 236,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate), BLOCKIO_SIG,
    24, 3, 2, 472, 0 },

  { 237,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_n),
    BLOCKIO_SIG, 26, 3, 2, 474, 0 },

  { 238, "cse1_cv3_1straight/Control Systems/LgV design 2/Virtual control/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add), BLOCKIO_SIG, 26, 3, 2, 476,
    0 },

  { 239,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Virtual control/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_k), BLOCKIO_SIG, 26, 3,
    2, 478, 0 },

  { 240, "cse1_cv3_1straight/Control Systems/LgV design 2/Virtual control/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_og), BLOCKIO_SIG, 26, 3, 2,
    480, 0 },

  { 241, "cse1_cv3_1straight/Control Systems/LgV design 2/z_2 eq/Subtract", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_f), BLOCKIO_SIG, 26, 3, 2,
    482, 0 },

  { 242, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_a), BLOCKIO_SIG, 26, 3,
    2, 484, 0 },

  { 243, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-X_u",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, X_u), BLOCKIO_SIG, 0, 1, 2, 486,
    0 },

  { 244, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-Y_v",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Y_v), BLOCKIO_SIG, 0, 1, 2, 488,
    0 },

  { 245, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-N_v",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, N_v), BLOCKIO_SIG, 0, 1, 2, 490,
    0 },

  { 246, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-Y_vr",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Y_vr), BLOCKIO_SIG, 0, 1, 2, 492,
    0 },

  { 247, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/-N_r",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, N_r), BLOCKIO_SIG, 0, 1, 2, 494,
    0 },

  { 248,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/D_L/Linear Dampning matrix",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, LinearDampningmatrix),
    BLOCKIO_SIG, 38, 9, 2, 496, 0 },

  { 249, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_c), BLOCKIO_SIG, 24, 3,
    2, 498, 0 },

  { 250, "cse1_cv3_1straight/Control Systems/LgV design 2/M/M_11", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, M_11), BLOCKIO_SIG, 0, 1, 2, 500, 0 },

  { 251, "cse1_cv3_1straight/Control Systems/LgV design 2/M/M_22", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, M_22), BLOCKIO_SIG, 0, 1, 2, 502, 0 },

  { 252, "cse1_cv3_1straight/Control Systems/LgV design 2/M/m x_g", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, mx_g), BLOCKIO_SIG, 0, 1, 2, 504, 0 },

  { 253, "cse1_cv3_1straight/Control Systems/LgV design 2/M/M_32", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, M_32), BLOCKIO_SIG, 0, 1, 2, 506, 0 },

  { 254, "cse1_cv3_1straight/Control Systems/LgV design 2/M/M_23", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, M_23), BLOCKIO_SIG, 0, 1, 2, 508, 0 },

  { 255, "cse1_cv3_1straight/Control Systems/LgV design 2/M/M_33", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, M_33), BLOCKIO_SIG, 0, 1, 2, 510, 0 },

  { 256, "cse1_cv3_1straight/Control Systems/LgV design 2/M/3x3", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, x3_p), BLOCKIO_SIG, 38, 9, 2, 512, 0 },

  { 257, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Product1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_d), BLOCKIO_SIG, 38, 9, 2,
    514, 0 },

  { 258, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Subtract", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_k), BLOCKIO_SIG, 38, 9, 2,
    516, 0 },

  { 259, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S12", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, S12), BLOCKIO_SIG, 0, 1, 2, 518, 0 },

  { 260, "cse1_cv3_1straight/Control Systems/LgV design 2/S(r)/S(r)", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Sr), BLOCKIO_SIG, 38, 9, 2, 520, 0 },

  { 261, "cse1_cv3_1straight/Control Systems/LgV design 2/S^T/Math Function", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_k), BLOCKIO_SIG, 38, 9,
    2, 522, 0 },

  { 262, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Product", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_fy), BLOCKIO_SIG, 24, 3, 2,
    524, 0 },

  { 263, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Add", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add_j), BLOCKIO_SIG, 24, 3, 2, 526, 0 },

  { 264, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Product2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_d), BLOCKIO_SIG, 24, 3, 2,
    528, 0 },

  { 265, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Add1", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add1_o), BLOCKIO_SIG, 26, 3, 2, 530, 0
  },

  { 266, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Product3", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product3), BLOCKIO_SIG, 26, 3, 2,
    532, 0 },

  { 267,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_o),
    BLOCKIO_SIG, 24, 3, 2, 534, 0 },

  { 268,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_d),
    BLOCKIO_SIG, 26, 3, 2, 536, 0 },

  { 269, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Add2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add2), BLOCKIO_SIG, 26, 3, 2, 538, 0 },

  { 270, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Product4", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product4), BLOCKIO_SIG, 26, 3, 2,
    540, 0 },

  { 271, "cse1_cv3_1straight/Control Systems/LgV design 2/sigma eq/Sum", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Sum_ok), BLOCKIO_SIG, 26, 3, 2, 542, 0
  },

  { 272, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Product4",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product4_d), BLOCKIO_SIG, 26, 3,
    2, 544, 0 },

  { 273, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^q/Product1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_m), BLOCKIO_SIG, 38, 9, 2,
    546, 0 },

  { 274, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^q/Subtract", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_j), BLOCKIO_SIG, 38, 9, 2,
    548, 0 },

  { 275, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^q/Product3", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product3_e), BLOCKIO_SIG, 25, 6, 2,
    550, 0 },

  { 276,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/f_q^T/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_gw), BLOCKIO_SIG,
    20, 2, 2, 552, 0 },

  { 277,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/psi_los^q^2T/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_n), BLOCKIO_SIG, 22,
    4, 2, 554, 0 },

  { 278,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_d), BLOCKIO_SIG, 20, 2,
    2, 556, 0 },

  { 279,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_ad), BLOCKIO_SIG, 20, 2,
    2, 558, 0 },

  { 280,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_jn), BLOCKIO_SIG, 20, 2, 2,
    560, 0 },

  { 281,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MatrixConcatenate), BLOCKIO_SIG,
    25, 6, 2, 562, 0 },

  { 282,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_i), BLOCKIO_SIG, 20, 2,
    2, 564, 0 },

  { 283,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_h), BLOCKIO_SIG, 20, 2,
    2, 566, 0 },

  { 284,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_o), BLOCKIO_SIG, 20, 2, 2,
    568, 0 },

  { 285,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MatrixConcatenate_l),
    BLOCKIO_SIG, 25, 6, 2, 570, 0 },

  { 286, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^q/Add2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add2_c), BLOCKIO_SIG, 25, 6, 2, 572, 0
  },

  { 287, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^q/Product4", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product4_l), BLOCKIO_SIG, 25, 6, 2,
    574, 0 },

  { 288, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^q/Add3", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add3), BLOCKIO_SIG, 25, 6, 2, 576, 0 },

  { 289,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Integrator2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Integrator2), BLOCKIO_SIG, 37, 2, 2,
    578, 0 },

  { 290, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Add2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Add2_k), BLOCKIO_SIG, 37, 2, 2, 580,
    0 },

  { 291, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Product5",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product5), BLOCKIO_SIG, 26, 3, 2,
    582, 0 },

  { 292, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^s/Product1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_l), BLOCKIO_SIG, 38, 9, 2,
    584, 0 },

  { 293, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^s/Subtract", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_fp), BLOCKIO_SIG, 38, 9, 2,
    586, 0 },

  { 294, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^s/Product3", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product3_d), BLOCKIO_SIG, 26, 3, 2,
    588, 0 },

  { 295,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_o), BLOCKIO_SIG, 0, 1, 2,
    590, 0 },

  { 296,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^s eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_i), BLOCKIO_SIG, 0, 1,
    2, 592, 0 },

  { 297,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxilary functions g_q/g_q^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_g),
    BLOCKIO_SIG, 24, 3, 2, 594, 0 },

  { 298,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_a), BLOCKIO_SIG, 21, 1,
    2, 596, 0 },

  { 299,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_g), BLOCKIO_SIG, 21, 1,
    2, 598, 0 },

  { 300,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Auxiliary function g_s/g_s^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_e),
    BLOCKIO_SIG, 26, 3, 2, 600, 0 },

  { 301, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^s/Add2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add2_j), BLOCKIO_SIG, 26, 3, 2, 602, 0
  },

  { 302, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^s/Product4", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product4_c), BLOCKIO_SIG, 26, 3, 2,
    604, 0 },

  { 303, "cse1_cv3_1straight/Control Systems/LgV design 2/alpha^s/Add3", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add3_o), BLOCKIO_SIG, 26, 3, 2, 606, 0
  },

  { 304, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Product6",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product6), BLOCKIO_SIG, 26, 3, 2,
    608, 0 },

  { 305, "cse1_cv3_1straight/Control Systems/LgV design 2/Control law/Sum", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_e), BLOCKIO_SIG, 26, 3, 2, 610,
    0 },

  { 306,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_h), BLOCKIO_SIG, 39, 5,
    2, 612, 0 },

  { 307,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_10_p), BLOCKIO_SIG, 21, 1, 2,
    614, 0 },

  { 308,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_10_c), BLOCKIO_SIG, 21, 1, 2,
    616, 0 },

  { 309,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_id), BLOCKIO_SIG,
    21, 1, 2, 618, 0 },

  { 310,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_20_f), BLOCKIO_SIG, 21, 1, 2,
    620, 0 },

  { 311,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_20_h), BLOCKIO_SIG, 21, 1, 2,
    622, 0 },

  { 312,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_f), BLOCKIO_SIG,
    21, 1, 2, 624, 0 },

  { 313,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_30_k), BLOCKIO_SIG, 21, 1, 2,
    626, 0 },

  { 314,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_30_o), BLOCKIO_SIG, 21, 1, 2,
    628, 0 },

  { 315,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_ga), BLOCKIO_SIG,
    21, 1, 2, 630, 0 },

  { 316,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_40_f), BLOCKIO_SIG, 21, 1, 2,
    632, 0 },

  { 317,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_40_cs), BLOCKIO_SIG, 21, 1, 2,
    634, 0 },

  { 318,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_me), BLOCKIO_SIG,
    21, 1, 2, 636, 0 },

  { 319,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_50_f), BLOCKIO_SIG, 21, 1, 2,
    638, 0 },

  { 320,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_50_pk), BLOCKIO_SIG, 21, 1, 2,
    640, 0 },

  { 321,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_bl), BLOCKIO_SIG,
    21, 1, 2, 642, 0 },

  { 322,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x1_d), BLOCKIO_SIG, 0, 1, 2,
    644, 0 },

  { 323,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_y2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_y2_j), BLOCKIO_SIG, 0, 1, 2,
    646, 0 },

  { 324,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/-l_x2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x2_l), BLOCKIO_SIG, 0, 1, 2,
    648, 0 },

  { 325,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/T_e/3x5",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x5_ib), BLOCKIO_SIG, 33, 15, 2,
    650, 0 },

  { 326,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Pseudoinverse_f), BLOCKIO_SIG,
    32, 15, 2, 652, 0 },

  { 327, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R11", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, R11_j), BLOCKIO_SIG, 0, 1, 2, 654, 0 },

  { 328, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R21", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, R21_b), BLOCKIO_SIG, 0, 1, 2, 656, 0 },

  { 329, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R12", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, R12_c), BLOCKIO_SIG, 0, 1, 2, 658, 0 },

  { 330, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R22", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, R22_d), BLOCKIO_SIG, 0, 1, 2, 660, 0 },

  { 331, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R(psi)/R(psi)", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Rpsi_p), BLOCKIO_SIG, 38, 9, 2, 662, 0
  },

  { 332, "cse1_cv3_1straight/Control Systems/Nonlinear PID/R^T/Math Function", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_i), BLOCKIO_SIG, 38, 9,
    2, 664, 0 },

  { 333, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_p/R(psi)", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Rpsi_l), BLOCKIO_SIG, 38, 9, 2, 666, 0
  },

  { 334,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_jl), BLOCKIO_SIG, 0, 1, 2,
    668, 0 },

  { 335,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_pv), BLOCKIO_SIG, 0,
    1, 2, 670, 0 },

  { 336,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_mi), BLOCKIO_SIG, 0, 1, 2,
    672, 0 },

  { 337,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_b), BLOCKIO_SIG, 0, 1, 2,
    674, 0 },

  { 338,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_n), BLOCKIO_SIG, 0, 1, 2,
    676, 0 },

  { 339,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_gi), BLOCKIO_SIG, 0,
    1, 2, 678, 0 },

  { 340,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_c), BLOCKIO_SIG, 0, 1, 2,
    680, 0 },

  { 341,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_a), BLOCKIO_SIG, 0, 1, 2,
    682, 0 },

  { 342, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/Subtract", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_d), BLOCKIO_SIG, 24, 3, 2,
    684, 0 },

  { 343,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_f4), BLOCKIO_SIG, 0, 1, 2,
    686, 0 },

  { 344,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_c0), BLOCKIO_SIG, 0,
    1, 2, 688, 0 },

  { 345,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_i4), BLOCKIO_SIG, 0, 1, 2,
    690, 0 },

  { 346,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_i), BLOCKIO_SIG, 0, 1, 2,
    692, 0 },

  { 347,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_c), BLOCKIO_SIG, 0, 1, 2,
    694, 0 },

  { 348,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_li), BLOCKIO_SIG, 0,
    1, 2, 696, 0 },

  { 349,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_o5), BLOCKIO_SIG, 0, 1, 2,
    698, 0 },

  { 350,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Error/heading to pipi1/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_f), BLOCKIO_SIG, 0, 1, 2,
    700, 0 },

  { 351,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_PID/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_le), BLOCKIO_SIG, 24, 3,
    2, 702, 0 },

  { 352, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_i/R(psi)", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Rpsi_i), BLOCKIO_SIG, 38, 9, 2, 704, 0
  },

  { 353, "cse1_cv3_1straight/Control Systems/Nonlinear PID/zeta", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, zeta), BLOCKIO_SIG, 26, 3, 2, 706, 0 },

  { 354,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_PID/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_o), BLOCKIO_SIG, 26, 3,
    2, 708, 0 },

  { 355, "cse1_cv3_1straight/Control Systems/Nonlinear PID/K_d/R(psi)", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Rpsi_k), BLOCKIO_SIG, 38, 9, 2, 710, 0
  },

  { 356,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_es),
    BLOCKIO_SIG, 24, 3, 2, 712, 0 },

  { 357,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_oq),
    BLOCKIO_SIG, 26, 3, 2, 714, 0 },

  { 358, "cse1_cv3_1straight/Control Systems/Nonlinear PID/v_d/Add", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add_p), BLOCKIO_SIG, 26, 3, 2, 716, 0 },

  { 359, "cse1_cv3_1straight/Control Systems/Nonlinear PID/nu tilde/Product", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_fp), BLOCKIO_SIG, 26, 3, 2,
    718, 0 },

  { 360, "cse1_cv3_1straight/Control Systems/Nonlinear PID/nu tilde/Subtract", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_ji), BLOCKIO_SIG, 26, 3, 2,
    720, 0 },

  { 361,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_PID/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_b), BLOCKIO_SIG, 26, 3,
    2, 722, 0 },

  { 362,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_PID/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_f), BLOCKIO_SIG, 26, 3, 2,
    724, 0 },

  { 363,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-X_u",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, X_u_o), BLOCKIO_SIG, 0, 1, 2,
    726, 0 },

  { 364,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_v",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Y_v_g), BLOCKIO_SIG, 0, 1, 2,
    728, 0 },

  { 365,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_v",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, N_v_b), BLOCKIO_SIG, 0, 1, 2,
    730, 0 },

  { 366,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-Y_vr",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Y_vr_n), BLOCKIO_SIG, 0, 1, 2,
    732, 0 },

  { 367,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/-N_r",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, N_r_k), BLOCKIO_SIG, 0, 1, 2,
    734, 0 },

  { 368,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/D_L/Linear Dampning matrix",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, LinearDampningmatrix_p),
    BLOCKIO_SIG, 38, 9, 2, 736, 0 },

  { 369,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FL/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_hd), BLOCKIO_SIG, 24, 3,
    2, 738, 0 },

  { 370,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_11",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_11_p), BLOCKIO_SIG, 0, 1, 2,
    740, 0 },

  { 371,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_22",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_22_m), BLOCKIO_SIG, 0, 1, 2,
    742, 0 },

  { 372,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/m x_g",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, mx_g_k), BLOCKIO_SIG, 0, 1, 2,
    744, 0 },

  { 373,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_32",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_32_a), BLOCKIO_SIG, 0, 1, 2,
    746, 0 },

  { 374,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_23",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_23_p), BLOCKIO_SIG, 0, 1, 2,
    748, 0 },

  { 375,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/M_33",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_33_m), BLOCKIO_SIG, 0, 1, 2,
    750, 0 },

  { 376,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/M/3x3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x3_k), BLOCKIO_SIG, 38, 9, 2,
    752, 0 },

  { 377,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/f_q^T/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_h), BLOCKIO_SIG, 20,
    2, 2, 754, 0 },

  { 378,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/psi_los^q^2^T/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_f), BLOCKIO_SIG, 22,
    4, 2, 756, 0 },

  { 379,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_py), BLOCKIO_SIG, 20, 2,
    2, 758, 0 },

  { 380,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_ak), BLOCKIO_SIG, 20, 2,
    2, 760, 0 },

  { 381,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_l), BLOCKIO_SIG, 20, 2, 2,
    762, 0 },

  { 382,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MatrixConcatenate_o),
    BLOCKIO_SIG, 25, 6, 2, 764, 0 },

  { 383,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_b), BLOCKIO_SIG, 20, 2,
    2, 766, 0 },

  { 384,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_g2), BLOCKIO_SIG, 20, 2,
    2, 768, 0 },

  { 385,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_d), BLOCKIO_SIG, 20, 2, 2,
    770, 0 },

  { 386,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MatrixConcatenate_n),
    BLOCKIO_SIG, 25, 6, 2, 772, 0 },

  { 387, "cse1_cv3_1straight/Control Systems/Nonlinear PID/a_d/v_d^q/Add", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add_b), BLOCKIO_SIG, 25, 6, 2, 774, 0 },

  { 388, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/omega_q",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, omega_q), BLOCKIO_SIG, 23, 2, 2,
    776, 0 },

  { 389, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Add", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_po), BLOCKIO_SIG, 23, 2, 2, 778,
    0 },

  { 390, "cse1_cv3_1straight/Control Systems/Nonlinear PID/a_d/Product", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Product_bl), BLOCKIO_SIG, 24, 3, 2, 780,
    0 },

  { 391,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_be), BLOCKIO_SIG, 0, 1,
    2, 782, 0 },

  { 392,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_m5), BLOCKIO_SIG, 0, 1,
    2, 784, 0 },

  { 393,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_ge),
    BLOCKIO_SIG, 24, 3, 2, 786, 0 },

  { 394,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_o2), BLOCKIO_SIG, 21, 1,
    2, 788, 0 },

  { 395,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_f), BLOCKIO_SIG, 21, 1,
    2, 790, 0 },

  { 396,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_b),
    BLOCKIO_SIG, 26, 3, 2, 792, 0 },

  { 397, "cse1_cv3_1straight/Control Systems/Nonlinear PID/a_d/v_d^s/Add1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Add1_m), BLOCKIO_SIG, 26, 3, 2, 794,
    0 },

  { 398, "cse1_cv3_1straight/Control Systems/Nonlinear PID/a_d/Product1", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Product1_n), BLOCKIO_SIG, 24, 3, 2, 796,
    0 },

  { 399,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxilary functions g_q/g_q^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_a),
    BLOCKIO_SIG, 24, 3, 2, 798, 0 },

  { 400,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Auxiliary function g_s/g_s^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_nu),
    BLOCKIO_SIG, 26, 3, 2, 800, 0 },

  { 401, "cse1_cv3_1straight/Control Systems/Nonlinear PID/a_d/v_d^t/Add", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Add_h), BLOCKIO_SIG, 26, 3, 2, 802, 0 },

  { 402, "cse1_cv3_1straight/Control Systems/Nonlinear PID/a_d/Sum", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Sum_ek), BLOCKIO_SIG, 26, 3, 2, 804, 0
  },

  { 403,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_c4), BLOCKIO_SIG, 26, 3,
    2, 806, 0 },

  { 404, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S12",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, S12_o), BLOCKIO_SIG, 0, 1, 2,
    808, 0 },

  { 405,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/S(r)/S(r)", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Sr_j), BLOCKIO_SIG, 38, 9, 2, 810,
    0 },

  { 406,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_fg), BLOCKIO_SIG, 26, 3,
    2, 812, 0 },

  { 407,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_a), BLOCKIO_SIG, 26, 3,
    2, 814, 0 },

  { 408,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/tau_FF/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_iy), BLOCKIO_SIG, 26, 3, 2,
    816, 0 },

  { 409, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Control law/Sum", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_d), BLOCKIO_SIG, 26, 3, 2, 818,
    0 },

  { 410,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_hy), BLOCKIO_SIG, 39, 5,
    2, 820, 0 },

  { 411,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_10_o), BLOCKIO_SIG, 21, 1, 2,
    822, 0 },

  { 412,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/f_1 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_10_b), BLOCKIO_SIG, 21, 1, 2,
    824, 0 },

  { 413,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_ak), BLOCKIO_SIG,
    21, 1, 2, 826, 0 },

  { 414,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_20_p), BLOCKIO_SIG, 21, 1, 2,
    828, 0 },

  { 415,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/f_2 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_20_l), BLOCKIO_SIG, 21, 1, 2,
    830, 0 },

  { 416,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_h), BLOCKIO_SIG,
    21, 1, 2, 832, 0 },

  { 417,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_30_fk), BLOCKIO_SIG, 21, 1, 2,
    834, 0 },

  { 418,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/f_3 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_30_ig), BLOCKIO_SIG, 21, 1, 2,
    836, 0 },

  { 419,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_o), BLOCKIO_SIG,
    21, 1, 2, 838, 0 },

  { 420,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_40_b), BLOCKIO_SIG, 21, 1, 2,
    840, 0 },

  { 421,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/f_4 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_40_l), BLOCKIO_SIG, 21, 1, 2,
    842, 0 },

  { 422,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_jj), BLOCKIO_SIG,
    21, 1, 2, 844, 0 },

  { 423,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 < 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_50_n), BLOCKIO_SIG, 21, 1, 2,
    846, 0 },

  { 424,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/f_5 > 0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_50_a), BLOCKIO_SIG, 21, 1, 2,
    848, 0 },

  { 425,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Multiport Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSwitch_jb), BLOCKIO_SIG,
    21, 1, 2, 850, 0 },

  { 426, "cse1_cv3_1straight/Control Systems/Thruster setting Switch", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, ThrustersettingSwitch), BLOCKIO_SIG, 27,
    7, 2, 852, 0 },

  { 427, "cse1_cv3_1straight/Control Systems/Saturation", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Saturation_ay), BLOCKIO_SIG, 27, 7, 2, 854, 0 },

  { 428,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/-l_x1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x1_b), BLOCKIO_SIG, 0, 1, 2,
    856, 0 },

  { 429,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/-l_y2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_y2_ia), BLOCKIO_SIG, 0, 1, 2,
    858, 0 },

  { 430,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/-l_x2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x2_j), BLOCKIO_SIG, 0, 1, 2,
    860, 0 },

  { 431,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/T_e/3x5",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x5_h), BLOCKIO_SIG, 33, 15, 2,
    862, 0 },

  { 432,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_1 to f_1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_1tof_1), BLOCKIO_SIG, 0, 1, 2,
    864, 0 },

  { 433,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_2 to f_2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_2tof_2), BLOCKIO_SIG, 0, 1, 2,
    866, 0 },

  { 434,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_3 to f_3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_3tof_3), BLOCKIO_SIG, 0, 1, 2,
    868, 0 },

  { 435,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_4 to f_4",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_4tof_4), BLOCKIO_SIG, 0, 1, 2,
    870, 0 },

  { 436,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/u_act to f_act/u_5 to f_5",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_5tof_5), BLOCKIO_SIG, 0, 1, 2,
    872, 0 },

  { 437,
    "cse1_cv3_1straight/Control Systems/Precision control/Subsystem/f_act to tau/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_lh), BLOCKIO_SIG, 24, 3,
    2, 874, 0 },

  { 438,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/-l_x1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x1_c), BLOCKIO_SIG, 0, 1, 2,
    876, 0 },

  { 439,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/-l_y2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_y2_d), BLOCKIO_SIG, 0, 1, 2,
    878, 0 },

  { 440,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/-l_x2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, l_x2_h), BLOCKIO_SIG, 0, 1, 2,
    880, 0 },

  { 441,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/T_e/3x5",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x5_iw), BLOCKIO_SIG, 33, 15, 2,
    882, 0 },

  { 442,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_1 to f_1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_1tof_1_p), BLOCKIO_SIG, 0, 1,
    2, 884, 0 },

  { 443,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_2 to f_2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_2tof_2_a), BLOCKIO_SIG, 0, 1,
    2, 886, 0 },

  { 444,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_3 to f_3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_3tof_3_b), BLOCKIO_SIG, 0, 1,
    2, 888, 0 },

  { 445,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_4 to f_4",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_4tof_4_p), BLOCKIO_SIG, 0, 1,
    2, 890, 0 },

  { 446,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/u_act to f_act/u_5 to f_5",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_5tof_5_k), BLOCKIO_SIG, 0, 1,
    2, 892, 0 },

  { 447,
    "cse1_cv3_1straight/Control Systems/Manual Thruster control/Subsystem/f_act to tau/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_m), BLOCKIO_SIG, 24, 3,
    2, 894, 0 },

  { 448, "cse1_cv3_1straight/Control Systems/tau  Switch", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, tauSwitch), BLOCKIO_SIG, 26, 3, 2, 896, 0 },

  { 449,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator1",
    0, "eta_w", offsetof(BlockIO_CSE1_CV3_1Straight, eta_w), BLOCKIO_SIG, 24, 3,
    2, 898, 0 },

  { 450, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_d 3 deg",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, K_d3deg), BLOCKIO_SIG, 0, 1, 2,
    900, 0 },

  { 451, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_i 3 deg",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, K_i3deg), BLOCKIO_SIG, 0, 1, 2,
    902, 0 },

  { 452, "cse1_cv3_1straight/Control Systems/DP control/DP controller/K_p 3 deg",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, K_p3deg), BLOCKIO_SIG, 0, 1, 2,
    904, 0 },

  { 453,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/Reg_e_Psi_deg",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Reg_e_Psi_deg), BLOCKIO_SIG, 0,
    1, 2, 906, 0 },

  { 454,
    "cse1_cv3_1straight/Control Systems/DP control/DP controller/eta Psi deg", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, etaPsideg), BLOCKIO_SIG, 0, 1, 2,
    908, 0 },

  { 455,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_j), BLOCKIO_SIG, 24, 3, 2,
    910, 0 },

  { 456,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator2",
    0, "xi_w", offsetof(BlockIO_CSE1_CV3_1Straight, xi_w), BLOCKIO_SIG, 24, 3, 2,
    912, 0 },

  { 457,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain2), BLOCKIO_SIG, 24, 3, 2,
    914, 0 },

  { 458,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Sum4",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum4), BLOCKIO_SIG, 24, 3, 2,
    916, 0 },

  { 459,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Sum2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum2_a), BLOCKIO_SIG, 24, 3, 2,
    918, 0 },

  { 460,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_cy), BLOCKIO_SIG, 0,
    1, 2, 920, 0 },

  { 461,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_d), BLOCKIO_SIG, 0, 1, 2,
    922, 0 },

  { 462,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_ju), BLOCKIO_SIG, 0, 1, 2,
    924, 0 },

  { 463,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_he), BLOCKIO_SIG, 0, 1, 2,
    926, 0 },

  { 464,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_kv), BLOCKIO_SIG, 0,
    1, 2, 928, 0 },

  { 465,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_ez), BLOCKIO_SIG, 0, 1, 2,
    930, 0 },

  { 466,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K4",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, K4), BLOCKIO_SIG, 24, 3, 2, 932,
    0 },

  { 467,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw/Row1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Row1_i), BLOCKIO_SIG, 0, 1, 2,
    934, 0 },

  { 468,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw/Row2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Row2_p), BLOCKIO_SIG, 0, 1, 2,
    936, 0 },

  { 469,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw/Row3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Row3_p), BLOCKIO_SIG, 0, 1, 2,
    938, 0 },

  { 470,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Integrator3",
    0, "bias", offsetof(BlockIO_CSE1_CV3_1Straight, bias), BLOCKIO_SIG, 24, 3, 2,
    940, 0 },

  { 471,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Row1_g), BLOCKIO_SIG, 0, 1, 2,
    942, 0 },

  { 472,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Row2_a), BLOCKIO_SIG, 0, 1, 2,
    944, 0 },

  { 473,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Row3_l), BLOCKIO_SIG, 0, 1, 2,
    946, 0 },

  { 474,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_cn), BLOCKIO_SIG, 24, 3, 2,
    948, 0 },

  { 475,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain6",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain6), BLOCKIO_SIG, 24, 3, 2,
    950, 0 },

  { 476,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Sum8",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum8), BLOCKIO_SIG, 24, 3, 2,
    952, 0 },

  { 477,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Gain3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain3), BLOCKIO_SIG, 24, 3, 2,
    954, 0 },

  { 478,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K11",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, K11), BLOCKIO_SIG, 24, 3, 2, 956,
    0 },

  { 479,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K12",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, K12), BLOCKIO_SIG, 24, 3, 2, 958,
    0 },

  { 480,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, K2), BLOCKIO_SIG, 24, 3, 2, 960,
    0 },

  { 481,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/K3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, K3), BLOCKIO_SIG, 24, 3, 2, 962,
    0 },

  { 482,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1/Fcn",
    0, "x_dot", offsetof(BlockIO_CSE1_CV3_1Straight, x_dot), BLOCKIO_SIG, 0, 1,
    2, 964, 0 },

  { 483,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1/Fcn1",
    0, "y_dot", offsetof(BlockIO_CSE1_CV3_1Straight, y_dot), BLOCKIO_SIG, 0, 1,
    2, 966, 0 },

  { 484,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Rotation matrix in yaw 1/Fcn2",
    0, "psi_dot", offsetof(BlockIO_CSE1_CV3_1Straight, psi_dot), BLOCKIO_SIG, 0,
    1, 2, 968, 0 },

  { 485,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Sum3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum3_k), BLOCKIO_SIG, 24, 3, 2,
    970, 0 },

  { 486,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Sum5",
    0, "psi_WF", offsetof(BlockIO_CSE1_CV3_1Straight, psi_WF), BLOCKIO_SIG, 24,
    3, 2, 972, 0 },

  { 487,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Sum6",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum6), BLOCKIO_SIG, 24, 3, 2,
    974, 0 },

  { 488,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/inv(T_b)",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, invT_b), BLOCKIO_SIG, 24, 3, 2,
    976, 0 },

  { 489,
    "cse1_cv3_1straight/Control Systems/DP control/Passive DP wave filter1/Sum7",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum7), BLOCKIO_SIG, 24, 3, 2,
    978, 0 },

  { 490, "cse1_cv3_1straight/Control Systems/LgV design 2/Gamma_q/2x2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, x2), BLOCKIO_SIG, 22, 4, 2, 980, 0 },

  { 491,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Integral action state/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_e), BLOCKIO_SIG, 26, 3,
    2, 982, 0 },

  { 492, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Add", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_ov), BLOCKIO_SIG, 37, 2, 2, 984,
    0 },

  { 493,
    "cse1_cv3_1straight/Control Systems/LgV design 2/V_1^q/Transpose/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_ew), BLOCKIO_SIG,
    42, 3, 2, 986, 0 },

  { 494, "cse1_cv3_1straight/Control Systems/LgV design 2/V_1^q/Product", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Product_au), BLOCKIO_SIG, 20, 2, 2, 988,
    0 },

  { 495, "cse1_cv3_1straight/Control Systems/LgV design 2/V_1^q/Gain", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Gain_m), BLOCKIO_SIG, 20, 2, 2, 990, 0
  },

  { 496,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Transpose/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_m), BLOCKIO_SIG, 37,
    2, 2, 992, 0 },

  { 497, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_b2), BLOCKIO_SIG, 37, 2,
    2, 994, 0 },

  { 498, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Add1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Add1_g), BLOCKIO_SIG, 37, 2, 2, 996,
    0 },

  { 499, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_ln), BLOCKIO_SIG, 37, 2,
    2, 998, 0 },

  { 500, "cse1_cv3_1straight/Control Systems/LgV design 2/Update laws/Gain", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_fx), BLOCKIO_SIG, 37, 2, 2,
    1000, 0 },

  { 501, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Gamma_q/2x2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, x2_g), BLOCKIO_SIG, 22, 4, 2, 1002, 0 },

  { 502,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Integral action state/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_k), BLOCKIO_SIG, 26, 3,
    2, 1004, 0 },

  { 503,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Transpose/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_ff), BLOCKIO_SIG,
    44, 6, 2, 1006, 0 },

  { 504, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_f), BLOCKIO_SIG, 23, 2,
    2, 1008, 0 },

  { 505, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Product3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product3_a), BLOCKIO_SIG, 23, 2,
    2, 1010, 0 },

  { 506, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_jg), BLOCKIO_SIG, 23, 2,
    2, 1012, 0 },

  { 507, "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_gn), BLOCKIO_SIG, 23, 2,
    2, 1014, 0 },

  { 508,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Update laws/dot omega_q",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, dotomega_q), BLOCKIO_SIG, 23, 2,
    2, 1016, 0 },

  { 509, "cse1_cv3_1straight/Guidance Systems/DP/eta_d Psi deg", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, eta_dPsideg), BLOCKIO_SIG, 0, 1, 2, 1018, 0 },

  { 510, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In1 FN", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn1FN), BLOCKIO_SIG, 21, 1, 2,
    1020, 0 },

  { 511, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/QTM In2 Error",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, QTMIn2Error), BLOCKIO_SIG, 21, 1,
    2, 1022, 0 },

  { 512, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/SIT zAI1", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, SITzAI1), BLOCKIO_SIG, 0, 1, 2, 1024, 0
  },

  { 513, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Battery Servo",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, BatteryServo), BLOCKIO_SIG, 0, 1,
    2, 1026, 0 },

  { 514, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/SIT zAI2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, SITzAI2), BLOCKIO_SIG, 0, 1, 2, 1028, 0
  },

  { 515, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Battery Main", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, BatteryMain), BLOCKIO_SIG, 0, 1, 2,
    1030, 0 },

  { 516, "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/SIT zAI0", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, SITzAI0), BLOCKIO_SIG, 0, 1, 2, 1032, 0
  },

  { 517,
    "cse1_cv3_1straight/Naviagation Systems/Qualisys 6 DOF/Battery Bow Thruster",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, BatteryBowThruster), BLOCKIO_SIG,
    0, 1, 2, 1034, 0 },

  { 518, "cse1_cv3_1straight/Plants/saturation/Saturation", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Saturation_e), BLOCKIO_SIG, 21, 1, 2, 1036, 0 },

  { 519, "cse1_cv3_1straight/Plants/saturation/Saturation1", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Saturation1), BLOCKIO_SIG, 21, 1, 2, 1038, 0 },

  { 520, "cse1_cv3_1straight/Plants/saturation/Saturation2", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Saturation2), BLOCKIO_SIG, 21, 1, 2, 1040, 0 },

  { 521, "cse1_cv3_1straight/Plants/saturation/plant tau_surge", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, planttau_surge), BLOCKIO_SIG, 21, 1, 2, 1042, 0
  },

  { 522, "cse1_cv3_1straight/Plants/saturation/plant tau_sway", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, planttau_sway), BLOCKIO_SIG, 21, 1, 2, 1044, 0
  },

  { 523, "cse1_cv3_1straight/Plants/saturation/plant tau_yaw", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, planttau_yaw), BLOCKIO_SIG, 21, 1, 2, 1046, 0 },

  { 524, "cse1_cv3_1straight/Plants/u_1 plant", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, u_1plant), BLOCKIO_SIG, 0, 1, 2, 1048, 0 },

  { 525, "cse1_cv3_1straight/Plants/u_2 plant", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, u_2plant), BLOCKIO_SIG, 0, 1, 2, 1050, 0 },

  { 526, "cse1_cv3_1straight/Plants/u_3 plant", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, u_3plant), BLOCKIO_SIG, 0, 1, 2, 1052, 0 },

  { 527, "cse1_cv3_1straight/Plants/u_4 plant", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, u_4plant), BLOCKIO_SIG, 0, 1, 2, 1054, 0 },

  { 528, "cse1_cv3_1straight/Plants/u_5 plant", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, u_5plant), BLOCKIO_SIG, 0, 1, 2, 1056, 0 },

  { 529, "cse1_cv3_1straight/Plants/BT power limit plant", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, BTpowerlimitplant), BLOCKIO_SIG, 0, 1, 2, 1058,
    0 },

  { 530, "cse1_cv3_1straight/Plants/VSP speed plant", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, VSPspeedplant), BLOCKIO_SIG, 0, 1, 2, 1060, 0 },

  { 531, "cse1_cv3_1straight/Plants/trig", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, trig), BLOCKIO_SIG, 0, 1, 2, 1062, 0 },

  { 532, "cse1_cv3_1straight/Plants/Multiport Switch", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, MultiportSwitch_pqq), BLOCKIO_SIG, 0, 1, 2,
    1064, 0 },

  { 533, "cse1_cv3_1straight/Plants/trig1", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, trig1), BLOCKIO_SIG, 0, 1, 2, 1066, 0 },

  { 534, "cse1_cv3_1straight/Plants/Multiport Switch1", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, MultiportSwitch1_g), BLOCKIO_SIG, 0, 1, 2, 1068,
    0 },

  { 535, "cse1_cv3_1straight/Plants/Port VSP direction/Gain", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Gain_jh), BLOCKIO_SIG, 0, 1, 2, 1070, 0 },

  { 536, "cse1_cv3_1straight/Plants/Starboard VSP direction/Gain", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Gain_g), BLOCKIO_SIG, 0, 1, 2, 1072, 0
  },

  { 537,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_r",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, N_r_g), BLOCKIO_SIG, 0, 1, 2,
    1074, 0 },

  { 538,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-N_v",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, N_v_k), BLOCKIO_SIG, 0, 1, 2,
    1076, 0 },

  { 539,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-X_u",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, X_u_h), BLOCKIO_SIG, 0, 1, 2,
    1078, 0 },

  { 540,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_v",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Y_v_n), BLOCKIO_SIG, 0, 1, 2,
    1080, 0 },

  { 541,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/-Y_vr",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Y_vr_c), BLOCKIO_SIG, 0, 1, 2,
    1082, 0 },

  { 542,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/D_L/Linear Dampning matrix",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, LinearDampningmatrix_pr),
    BLOCKIO_SIG, 38, 9, 2, 1084, 0 },

  { 543,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/psi_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, psi_0), BLOCKIO_SIG, 0, 1, 2,
    1086, 0 },

  { 544,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/x_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_0), BLOCKIO_SIG, 0, 1, 2, 1088,
    0 },

  { 545,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial eta/y_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, y_0), BLOCKIO_SIG, 0, 1, 2, 1090,
    0 },

  { 546,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/r_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, r_0), BLOCKIO_SIG, 0, 1, 2, 1092,
    0 },

  { 547,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/u_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_0), BLOCKIO_SIG, 0, 1, 2, 1094,
    0 },

  { 548,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Initial nu/v_0",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, v_0), BLOCKIO_SIG, 0, 1, 2, 1096,
    0 },

  { 549,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Integrator",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Integrator_e), BLOCKIO_SIG, 24,
    3, 2, 1098, 0 },

  { 550,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Integrator1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Integrator1_o), BLOCKIO_SIG, 24,
    3, 2, 1100, 0 },

  { 551,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_11",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_11_a), BLOCKIO_SIG, 0, 1, 2,
    1102, 0 },

  { 552,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_22",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_22_f), BLOCKIO_SIG, 0, 1, 2,
    1104, 0 },

  { 553,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/m x_g",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, mx_g_p), BLOCKIO_SIG, 0, 1, 2,
    1106, 0 },

  { 554,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_32",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_32_l), BLOCKIO_SIG, 0, 1, 2,
    1108, 0 },

  { 555,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_23",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_23_j), BLOCKIO_SIG, 0, 1, 2,
    1110, 0 },

  { 556,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M_33",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M_33_a), BLOCKIO_SIG, 0, 1, 2,
    1112, 0 },

  { 557,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/M",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, M), BLOCKIO_SIG, 38, 9, 2, 1114,
    0 },

  { 558,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/M_inv/Inverse",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Inverse), BLOCKIO_SIG, 38, 9, 2,
    1116, 0 },

  { 559,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_ha), BLOCKIO_SIG, 24, 3,
    2, 1118, 0 },

  { 560,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R11",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R11_d), BLOCKIO_SIG, 0, 1, 2,
    1120, 0 },

  { 561,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R21",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R21_e), BLOCKIO_SIG, 0, 1, 2,
    1122, 0 },

  { 562,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R12",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R12_a), BLOCKIO_SIG, 0, 1, 2,
    1124, 0 },

  { 563,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R22",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R22_g), BLOCKIO_SIG, 0, 1, 2,
    1126, 0 },

  { 564,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/R(psi)/R(psi)",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Rpsi_a), BLOCKIO_SIG, 38, 9, 2,
    1128, 0 },

  { 565,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Product3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product3_j), BLOCKIO_SIG, 24, 3,
    2, 1130, 0 },

  { 566, "cse1_cv3_1straight/Plants/Linear Simulator/eta_surge_hil", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, eta_surge_hil), BLOCKIO_SIG, 0, 1, 2,
    1132, 0 },

  { 567, "cse1_cv3_1straight/Plants/Linear Simulator/eta_sway_hil", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, eta_sway_hil), BLOCKIO_SIG, 0, 1, 2,
    1134, 0 },

  { 568, "cse1_cv3_1straight/Plants/Linear Simulator/eta_yaw_hil", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, eta_yaw_hil), BLOCKIO_SIG, 0, 1, 2,
    1136, 0 },

  { 569, "cse1_cv3_1straight/Plants/Linear Simulator/etadot_surge_hil", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, etadot_surge_hil), BLOCKIO_SIG, 0, 1, 2,
    1138, 0 },

  { 570, "cse1_cv3_1straight/Plants/Linear Simulator/etadot_sway_hil", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, etadot_sway_hil), BLOCKIO_SIG, 0, 1, 2,
    1140, 0 },

  { 571, "cse1_cv3_1straight/Plants/Linear Simulator/etadot_yaw_hil", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, etadot_yaw_hil), BLOCKIO_SIG, 0, 1, 2,
    1142, 0 },

  { 572, "cse1_cv3_1straight/Plants/Linear Simulator/nu_surge_hil", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, nu_surge_hil), BLOCKIO_SIG, 0, 1, 2,
    1144, 0 },

  { 573, "cse1_cv3_1straight/Plants/Linear Simulator/nu_sway_hil", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, nu_sway_hil), BLOCKIO_SIG, 0, 1, 2,
    1146, 0 },

  { 574, "cse1_cv3_1straight/Plants/Linear Simulator/nu_yaw_hil", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, nu_yaw_hil), BLOCKIO_SIG, 0, 1, 2, 1148,
    0 },

  { 575, "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_p), BLOCKIO_SIG, 24, 3, 2,
    1150, 0 },

  { 576,
    "cse1_cv3_1straight/Plants/Linear Simulator/Linear Vessel Dynamics/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_bi), BLOCKIO_SIG, 24, 3,
    2, 1152, 0 },

  { 577, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_D_Gain1", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2, 1154,
    0 },

  { 578, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_D_Gain2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2, 1156,
    0 },

  { 579, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Add", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Add_c), BLOCKIO_SIG, 0, 1, 2, 1158, 0 },

  { 580, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_L_Gain1", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2, 1160,
    0 },

  { 581, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/BT_L_Gain2", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2, 1162,
    0 },

  { 582, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Neg", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Neg), BLOCKIO_SIG, 0, 1, 2, 1164, 0 },

  { 583, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Sum1", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Sum1_cf), BLOCKIO_SIG, 0, 1, 2, 1166, 0 },

  { 584, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Sum2", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Sum2_b), BLOCKIO_SIG, 0, 1, 2, 1168, 0 },

  { 585, "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Switch), BLOCKIO_SIG, 0, 1, 2,
    1170, 0 },

  { 586,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic/Switch2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Switch2), BLOCKIO_SIG, 0, 1, 2,
    1172, 0 },

  { 587,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Switch_n), BLOCKIO_SIG, 0, 1, 2,
    1174, 0 },

  { 588,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic1/Switch2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Switch2_o), BLOCKIO_SIG, 0, 1, 2,
    1176, 0 },

  { 589,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Switch_e), BLOCKIO_SIG, 0, 1, 2,
    1178, 0 },

  { 590,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic2/Switch2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Switch2_a), BLOCKIO_SIG, 0, 1, 2,
    1180, 0 },

  { 591, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Sign", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Sign_mc), BLOCKIO_SIG, 0, 1, 2, 1182, 0
  },

  { 592, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Product1", 0,
    "Port VPS_X", offsetof(BlockIO_CSE1_CV3_1Straight, PortVPS_X), BLOCKIO_SIG,
    0, 1, 2, 1184, 0 },

  { 593, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /-x", 0,
    "Port VPS_X", offsetof(BlockIO_CSE1_CV3_1Straight, PortVPS_X_d), BLOCKIO_SIG,
    0, 1, 2, 1186, 0 },

  { 594, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Product2", 0,
    "Port VSP_Y", offsetof(BlockIO_CSE1_CV3_1Straight, PortVSP_Y), BLOCKIO_SIG,
    0, 1, 2, 1188, 0 },

  { 595, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /-y", 0,
    "Port VSP_Y", offsetof(BlockIO_CSE1_CV3_1Straight, PortVSP_Y_p), BLOCKIO_SIG,
    0, 1, 2, 1190, 0 },

  { 596,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Port/x->r",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, xr), BLOCKIO_SIG, 0, 1, 2, 1192,
    0 },

  { 597,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Port/x->theta",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, xtheta), BLOCKIO_SIG, 0, 1, 2,
    1194, 0 },

  { 598, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Product3", 0,
    "Starboard VSP_X", offsetof(BlockIO_CSE1_CV3_1Straight, StarboardVSP_X),
    BLOCKIO_SIG, 0, 1, 2, 1196, 0 },

  { 599, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Product4", 0,
    "Starboard VSP_Y", offsetof(BlockIO_CSE1_CV3_1Straight, StarboardVSP_Y),
    BLOCKIO_SIG, 0, 1, 2, 1198, 0 },

  { 600,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Starboard/x->r",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, xr_j), BLOCKIO_SIG, 0, 1, 2,
    1200, 0 },

  { 601,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Cartesian to Polar Starboard/x->theta",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, xtheta_h), BLOCKIO_SIG, 0, 1, 2,
    1202, 0 },

  { 602,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Port/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_e), BLOCKIO_SIG, 0, 1, 2,
    1204, 0 },

  { 603,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Radians to Degrees Staroard/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_e1), BLOCKIO_SIG, 0, 1, 2,
    1206, 0 },

  { 604, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo1", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Servo1), BLOCKIO_SIG, 0, 1, 2, 1208,
    0 },

  { 605, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo2", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Servo2), BLOCKIO_SIG, 0, 1, 2, 1210,
    0 },

  { 606, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo3", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Servo3), BLOCKIO_SIG, 0, 1, 2, 1212,
    0 },

  { 607, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Servo4", 0,
    "", offsetof(BlockIO_CSE1_CV3_1Straight, Servo4), BLOCKIO_SIG, 0, 1, 2, 1214,
    0 },

  { 608,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VPS_Speed_Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VPS_Speed_Gain), BLOCKIO_SIG, 0,
    1, 2, 1216, 0 },

  { 609, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /Sum", 0, "",
    offsetof(BlockIO_CSE1_CV3_1Straight, Sum_ep), BLOCKIO_SIG, 0, 1, 2, 1218, 0
  },

  { 610, "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VSPS Port",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VSPSPort), BLOCKIO_SIG, 0, 1, 2,
    1220, 0 },

  { 611,
    "cse1_cv3_1straight/Plants/CSE1/Voith Schneider Propeller /VSPS Starboard",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VSPSStarboard), BLOCKIO_SIG, 0,
    1, 2, 1222, 0 },

  { 612,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/p_d^s eq/y_2 - y_1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, y_2y_1), BLOCKIO_SIG, 0, 1, 2,
    1224, 0 },

  { 613,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/p_d^s eq/x_2 - x_1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_2x_1), BLOCKIO_SIG, 0, 1, 2,
    1226, 0 },

  { 614,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/Trigonometric Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, TrigonometricFunction),
    BLOCKIO_SIG, 0, 1, 2, 1228, 0 },

  { 615,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_hk), BLOCKIO_SIG, 0, 1, 2,
    1230, 0 },

  { 616,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_d), BLOCKIO_SIG, 0, 1,
    2, 1232, 0 },

  { 617,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_h), BLOCKIO_SIG, 0, 1, 2,
    1234, 0 },

  { 618,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_dt), BLOCKIO_SIG, 0, 1, 2,
    1236, 0 },

  { 619,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_hi), BLOCKIO_SIG, 0, 1, 2,
    1238, 0 },

  { 620,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_lk), BLOCKIO_SIG, 0,
    1, 2, 1240, 0 },

  { 621,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_j), BLOCKIO_SIG, 0, 1, 2,
    1242, 0 },

  { 622,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d eq/rad to pi2pi/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_o), BLOCKIO_SIG, 0, 1, 2,
    1244, 0 },

  { 623,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s eq/( x_d^s )^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_ds2), BLOCKIO_SIG, 0, 1, 2,
    1246, 0 },

  { 624,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s eq/( y_d^s )^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, y_ds2), BLOCKIO_SIG, 0, 1, 2,
    1248, 0 },

  { 625,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s eq/( x_d^s )^2 + ( y_d^s )^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_ds2y_ds2), BLOCKIO_SIG, 0, 1,
    2, 1250, 0 },

  { 626,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s eq/x_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_dsy_ds2), BLOCKIO_SIG, 0, 1, 2,
    1252, 0 },

  { 627,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s eq/x_d^s^2 + y_d^s",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_ds2y_ds), BLOCKIO_SIG, 0, 1, 2,
    1254, 0 },

  { 628,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s eq/( x_d^s + y_d^s^2 ) - ( x_d^s^2 + y_d^s )",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_dsy_ds2x_ds2y_ds), BLOCKIO_SIG,
    0, 1, 2, 1256, 0 },

  { 629,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_g), BLOCKIO_SIG, 0, 1, 2,
    1258, 0 },

  { 630,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/x_d^s + x_d^s^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_dsx_ds2), BLOCKIO_SIG, 0, 1, 2,
    1260, 0 },

  { 631,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/y_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, y_dsy_ds2), BLOCKIO_SIG, 0, 1, 2,
    1262, 0 },

  { 632,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/( x_d^s + x_d^s^2 ) + ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_dsx_ds2x_ds3y_ds), BLOCKIO_SIG,
    0, 1, 2, 1264, 0 },

  { 633,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/x_d^s + y_d^s^3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_dsy_ds3), BLOCKIO_SIG, 0, 1, 2,
    1266, 0 },

  { 634,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/x_d^s^3 + y_d^s",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_ds3y_ds), BLOCKIO_SIG, 0, 1, 2,
    1268, 0 },

  { 635,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/( x_d^s + y_d^s^3  ) - ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_dsy_ds3x_ds3y_ds), BLOCKIO_SIG,
    0, 1, 2, 1270, 0 },

  { 636,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/+ 2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_b), BLOCKIO_SIG, 0, 1, 2, 1272,
    0 },

  { 637,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_j), BLOCKIO_SIG, 0, 1,
    2, 1274, 0 },

  { 638,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_ft), BLOCKIO_SIG, 0, 1,
    2, 1276, 0 },

  { 639,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_e), BLOCKIO_SIG, 0, 1,
    2, 1278, 0 },

  { 640,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_ds2y_ds22), BLOCKIO_SIG, 0, 1,
    2, 1280, 0 },

  { 641,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Heading/psi_d^s^2 eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_n), BLOCKIO_SIG, 0, 1, 2,
    1282, 0 },

  { 642, "cse1_cv3_1straight/Guidance Systems/Path-following/q", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, q), BLOCKIO_SIG, 23, 2, 2, 1284, 0 },

  { 643,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_p), BLOCKIO_SIG, 0, 1, 2,
    1286, 0 },

  { 644,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_oo), BLOCKIO_SIG, 0,
    1, 2, 1288, 0 },

  { 645,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_j), BLOCKIO_SIG, 0, 1, 2,
    1290, 0 },

  { 646,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_g3), BLOCKIO_SIG, 0, 1, 2,
    1292, 0 },

  { 647,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_b), BLOCKIO_SIG, 0, 1, 2,
    1294, 0 },

  { 648,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_lx), BLOCKIO_SIG, 0,
    1, 2, 1296, 0 },

  { 649,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_if), BLOCKIO_SIG, 0, 1, 2,
    1298, 0 },

  { 650,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi1/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_oo), BLOCKIO_SIG, 0, 1, 2,
    1300, 0 },

  { 651,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2^T/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_id), BLOCKIO_SIG,
    22, 4, 2, 1302, 0 },

  { 652,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/p_d eq/x_2 - x_1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_2x_1_c), BLOCKIO_SIG, 0, 1, 2,
    1304, 0 },

  { 653,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/p_d eq/(x_2 - x_1) + s",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_2x_1s), BLOCKIO_SIG, 0, 1, 2,
    1306, 0 },

  { 654,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/p_d eq/(x_2 - x_1) + s + x_1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, x_2x_1sx_1), BLOCKIO_SIG, 0, 1,
    2, 1308, 0 },

  { 655,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/p_d eq/y_2 - y_1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, y_2y_1_e), BLOCKIO_SIG, 0, 1, 2,
    1310, 0 },

  { 656,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/p_d eq/(y_2 - y_1) + s",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, y_2y_1s), BLOCKIO_SIG, 0, 1, 2,
    1312, 0 },

  { 657,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/p_d eq/(y_2 - y_1) + s + y_1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, y_2y_1sy_1), BLOCKIO_SIG, 0, 1,
    2, 1314, 0 },

  { 658,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/q - p_d",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, qp_d), BLOCKIO_SIG, 23, 2, 2,
    1316, 0 },

  { 659,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, epsilon), BLOCKIO_SIG, 23, 2, 2,
    1318, 0 },

  { 660,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSelector), BLOCKIO_SIG,
    21, 1, 2, 1320, 0 },

  { 661,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/Trigonometric Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, TrigonometricFunction_a),
    BLOCKIO_SIG, 21, 1, 2, 1322, 0 },

  { 662,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_fe), BLOCKIO_SIG, 21, 1, 2,
    1324, 0 },

  { 663,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_e4), BLOCKIO_SIG, 21,
    1, 2, 1326, 0 },

  { 664,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_a), BLOCKIO_SIG, 21, 1, 2,
    1328, 0 },

  { 665,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_ih), BLOCKIO_SIG, 21, 1, 2,
    1330, 0 },

  { 666,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_d), BLOCKIO_SIG, 21, 1, 2,
    1332, 0 },

  { 667,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_nj), BLOCKIO_SIG,
    21, 1, 2, 1334, 0 },

  { 668,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_n4), BLOCKIO_SIG, 21, 1, 2,
    1336, 0 },

  { 669,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi2/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_os), BLOCKIO_SIG, 21, 1, 2,
    1338, 0 },

  { 670,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_p), BLOCKIO_SIG, 21, 1,
    2, 1340, 0 },

  { 671,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Radians to Degrees/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_cc), BLOCKIO_SIG, 21, 1, 2,
    1342, 0 },

  { 672,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Saturation",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Saturation_j), BLOCKIO_SIG, 21,
    1, 2, 1344, 0 },

  { 673,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Sign",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sign_p), BLOCKIO_SIG, 21, 1, 2,
    1346, 0 },

  { 674,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_k), BLOCKIO_SIG, 21, 1, 2,
    1348, 0 },

  { 675,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Sum1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum1_pd), BLOCKIO_SIG, 21, 1, 2,
    1350, 0 },

  { 676,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_ie), BLOCKIO_SIG,
    21, 1, 2, 1352, 0 },

  { 677,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_ne), BLOCKIO_SIG, 21, 1, 2,
    1354, 0 },

  { 678,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los eq/rad to pi2pi3/Degrees to Radians/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_i), BLOCKIO_SIG, 21, 1, 2,
    1356, 0 },

  { 679,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/Vector Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate_dn),
    BLOCKIO_SIG, 24, 3, 2, 1358, 0 },

  { 680,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_ew1), BLOCKIO_SIG,
    0, 1, 2, 1360, 0 },

  { 681,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Math Function1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction1), BLOCKIO_SIG, 21,
    1, 2, 1362, 0 },

  { 682,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_k), BLOCKIO_SIG, 21, 1, 2,
    1364, 0 },

  { 683,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_o), BLOCKIO_SIG, 21, 1, 2,
    1366, 0 },

  { 684,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSelector1), BLOCKIO_SIG,
    20, 2, 2, 1368, 0 },

  { 685,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_m2), BLOCKIO_SIG, 20, 2,
    2, 1370, 0 },

  { 686,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q eq/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_l), BLOCKIO_SIG, 20, 2, 2,
    1372, 0 },

  { 687,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/Matrix Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MatrixConcatenate_oj),
    BLOCKIO_SIG, 25, 6, 2, 1374, 0 },

  { 688,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_p), BLOCKIO_SIG, 0,
    1, 2, 1376, 0 },

  { 689,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Math Function1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction1_i), BLOCKIO_SIG,
    21, 1, 2, 1378, 0 },

  { 690,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_jd), BLOCKIO_SIG, 21, 1, 2,
    1380, 0 },

  { 691,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_g5), BLOCKIO_SIG, 21, 1,
    2, 1382, 0 },

  { 692,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2^T/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_h2), BLOCKIO_SIG,
    22, 4, 2, 1384, 0 },

  { 693,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_ky), BLOCKIO_SIG, 23, 2,
    2, 1386, 0 },

  { 694,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_e), BLOCKIO_SIG, 23, 2,
    2, 1388, 0 },

  { 695,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s eq/Subtract1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract1), BLOCKIO_SIG, 23, 2,
    2, 1390, 0 },

  { 696,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSelector2), BLOCKIO_SIG,
    21, 1, 2, 1392, 0 },

  { 697,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_l2), BLOCKIO_SIG, 21, 1,
    2, 1394, 0 },

  { 698,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s eq/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_n), BLOCKIO_SIG, 21, 1,
    2, 1396, 0 },

  { 699,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/3DOF reference vector/Vector Concatenate1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, VectorConcatenate1), BLOCKIO_SIG,
    26, 3, 2, 1398, 0 },

  { 700,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qx",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_qx), BLOCKIO_SIG, 21, 1, 2,
    1400, 0 },

  { 701,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qy",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, f_qy), BLOCKIO_SIG, 21, 1, 2,
    1402, 0 },

  { 702,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_dm), BLOCKIO_SIG, 23, 2,
    2, 1404, 0 },

  { 703,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, TrigonometricFunction1),
    BLOCKIO_SIG, 21, 1, 2, 1406, 0 },

  { 704,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_n), BLOCKIO_SIG, 21, 1, 2,
    1408, 0 },

  { 705,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_m4), BLOCKIO_SIG, 20, 2,
    2, 1410, 0 },

  { 706,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, TrigonometricFunction_b),
    BLOCKIO_SIG, 21, 1, 2, 1412, 0 },

  { 707,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_cb), BLOCKIO_SIG, 20, 2,
    2, 1414, 0 },

  { 708,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MatrixConcatenate_d),
    BLOCKIO_SIG, 22, 4, 2, 1416, 0 },

  { 709,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_d4), BLOCKIO_SIG, 22, 4,
    2, 1418, 0 },

  { 710,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, TrigonometricFunction1_p),
    BLOCKIO_SIG, 21, 1, 2, 1420, 0 },

  { 711,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_ba), BLOCKIO_SIG, 21, 1, 2,
    1422, 0 },

  { 712,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_j0), BLOCKIO_SIG, 21, 1,
    2, 1424, 0 },

  { 713,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, TrigonometricFunction_a2),
    BLOCKIO_SIG, 21, 1, 2, 1426, 0 },

  { 714,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_e), BLOCKIO_SIG, 21, 1,
    2, 1428, 0 },

  { 715,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_l0), BLOCKIO_SIG, 23, 2,
    2, 1430, 0 },

  { 716,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, TrigonometricFunction_b3),
    BLOCKIO_SIG, 21, 1, 2, 1432, 0 },

  { 717,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, TrigonometricFunction1_l),
    BLOCKIO_SIG, 21, 1, 2, 1434, 0 },

  { 718,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/Derivative",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Derivative), BLOCKIO_SIG, 0, 1,
    2, 1436, 0 },

  { 719,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_of), BLOCKIO_SIG, 23, 2,
    2, 1438, 0 },

  { 720,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, epsilon_n2), BLOCKIO_SIG, 21, 1,
    2, 1440, 0 },

  { 721,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Delta^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Delta2), BLOCKIO_SIG, 0, 1, 2,
    1442, 0 },

  { 722,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_j0), BLOCKIO_SIG, 21, 1, 2,
    1444, 0 },

  { 723,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/sqrt",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, sqrt_m), BLOCKIO_SIG, 21, 1, 2,
    1446, 0 },

  { 724,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_k), BLOCKIO_SIG, 21, 1, 2,
    1448, 0 },

  { 725,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_o), BLOCKIO_SIG, 20,
    2, 2, 1450, 0 },

  { 726,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_ho), BLOCKIO_SIG, 0, 1,
    2, 1452, 0 },

  { 727,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Path/Straight path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, sqrt_g), BLOCKIO_SIG, 0, 1, 2,
    1454, 0 },

  { 728,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_j), BLOCKIO_SIG, 0, 1, 2,
    1456, 0 },

  { 729,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_mk), BLOCKIO_SIG, 21, 1,
    2, 1458, 0 },

  { 730,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_pj), BLOCKIO_SIG,
    20, 2, 2, 1460, 0 },

  { 731,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_i), BLOCKIO_SIG, 20, 2, 2,
    1462, 0 },

  { 732,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_a1), BLOCKIO_SIG, 23, 2,
    2, 1464, 0 },

  { 733,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_ct), BLOCKIO_SIG, 0, 1,
    2, 1466, 0 },

  { 734,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_mj), BLOCKIO_SIG, 0, 1, 2,
    1468, 0 },

  { 735,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_g), BLOCKIO_SIG, 21, 1,
    2, 1470, 0 },

  { 736,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, epsilon_n2_a), BLOCKIO_SIG, 21,
    1, 2, 1472, 0 },

  { 737,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Delta^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Delta2_a), BLOCKIO_SIG, 0, 1, 2,
    1474, 0 },

  { 738,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_e), BLOCKIO_SIG, 21, 1, 2,
    1476, 0 },

  { 739,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_c), BLOCKIO_SIG, 20, 2,
    2, 1478, 0 },

  { 740,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/^3//2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u2), BLOCKIO_SIG, 21, 1, 2, 1480,
    0 },

  { 741,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_m), BLOCKIO_SIG, 20, 2, 2,
    1482, 0 },

  { 742,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_jc), BLOCKIO_SIG, 20, 2,
    2, 1484, 0 },

  { 743,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_e0), BLOCKIO_SIG,
    20, 2, 2, 1486, 0 },

  { 744,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_d), BLOCKIO_SIG, 20, 2, 2,
    1488, 0 },

  { 745,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_ff), BLOCKIO_SIG, 20, 2,
    2, 1490, 0 },

  { 746,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_is), BLOCKIO_SIG, 20, 2, 2,
    1492, 0 },

  { 747,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_id), BLOCKIO_SIG, 20, 2, 2,
    1494, 0 },

  { 748,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, epsilon_n2_j), BLOCKIO_SIG, 21,
    1, 2, 1496, 0 },

  { 749,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Delta^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Delta2_b), BLOCKIO_SIG, 0, 1, 2,
    1498, 0 },

  { 750,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_bt), BLOCKIO_SIG, 21, 1, 2,
    1500, 0 },

  { 751,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_b), BLOCKIO_SIG, 20,
    2, 2, 1502, 0 },

  { 752,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_oy), BLOCKIO_SIG, 0, 1,
    2, 1504, 0 },

  { 753,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/|p_d^s|^3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, p_ds3), BLOCKIO_SIG, 0, 1, 2,
    1506, 0 },

  { 754,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_p), BLOCKIO_SIG, 0, 1, 2,
    1508, 0 },

  { 755,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_g), BLOCKIO_SIG, 0, 1, 2,
    1510, 0 },

  { 756,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^s eq/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_a), BLOCKIO_SIG, 0, 1, 2,
    1512, 0 },

  { 757,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_ig), BLOCKIO_SIG,
    21, 1, 2, 1514, 0 },

  { 758,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_o4), BLOCKIO_SIG, 21, 1,
    2, 1516, 0 },

  { 759,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_l), BLOCKIO_SIG, 21, 1,
    2, 1518, 0 },

  { 760,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/^3//2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u2_g), BLOCKIO_SIG, 21, 1, 2,
    1520, 0 },

  { 761,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide1), BLOCKIO_SIG, 21, 1, 2,
    1522, 0 },

  { 762,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_p), BLOCKIO_SIG, 21, 1,
    2, 1524, 0 },

  { 763,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product3_g), BLOCKIO_SIG, 21, 1,
    2, 1526, 0 },

  { 764,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_bo), BLOCKIO_SIG, 0, 1,
    2, 1528, 0 },

  { 765,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_gl), BLOCKIO_SIG,
    20, 2, 2, 1530, 0 },

  { 766,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide2), BLOCKIO_SIG, 20, 2, 2,
    1532, 0 },

  { 767,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_bi), BLOCKIO_SIG,
    20, 2, 2, 1534, 0 },

  { 768,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_o), BLOCKIO_SIG, 20, 2,
    2, 1536, 0 },

  { 769,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_lc), BLOCKIO_SIG, 0,
    1, 2, 1538, 0 },

  { 770,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide1_d), BLOCKIO_SIG, 20, 2,
    2, 1540, 0 },

  { 771,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract1_m), BLOCKIO_SIG, 20, 2,
    2, 1542, 0 },

  { 772,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_bi), BLOCKIO_SIG, 0, 1,
    2, 1544, 0 },

  { 773,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_nx), BLOCKIO_SIG, 0, 1,
    2, 1546, 0 },

  { 774,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_oq), BLOCKIO_SIG, 21, 1, 2,
    1548, 0 },

  { 775,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/epsilon_n^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, epsilon_n2_m), BLOCKIO_SIG, 21,
    1, 2, 1550, 0 },

  { 776,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Delta^2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Delta2_f), BLOCKIO_SIG, 0, 1, 2,
    1552, 0 },

  { 777,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_f), BLOCKIO_SIG, 21, 1, 2,
    1554, 0 },

  { 778,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/sqrt",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, sqrt_c), BLOCKIO_SIG, 21, 1, 2,
    1556, 0 },

  { 779,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_h), BLOCKIO_SIG, 21, 1, 2,
    1558, 0 },

  { 780,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Speed assigment/v_s^t eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_b), BLOCKIO_SIG, 0, 1, 2,
    1560, 0 },

  { 781,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Dynamic assigment for sdot/f_t eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_gd), BLOCKIO_SIG, 21, 1,
    2, 1562, 0 },

  { 782,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_ka), BLOCKIO_SIG, 0,
    1, 2, 1564, 0 },

  { 783,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction1_c), BLOCKIO_SIG,
    21, 1, 2, 1566, 0 },

  { 784,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_hs), BLOCKIO_SIG, 21, 1, 2,
    1568, 0 },

  { 785,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_pa), BLOCKIO_SIG, 22, 4,
    2, 1570, 0 },

  { 786,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_j), BLOCKIO_SIG, 21, 1,
    2, 1572, 0 },

  { 787,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction3), BLOCKIO_SIG, 37,
    2, 2, 1574, 0 },

  { 788,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product3_k), BLOCKIO_SIG, 22, 4,
    2, 1576, 0 },

  { 789,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product4",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product4_p), BLOCKIO_SIG, 22, 4,
    2, 1578, 0 },

  { 790,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_b), BLOCKIO_SIG, 22, 4,
    2, 1580, 0 },

  { 791,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction2), BLOCKIO_SIG, 21,
    1, 2, 1582, 0 },

  { 792,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_m4), BLOCKIO_SIG, 22, 4,
    2, 1584, 0 },

  { 793,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_nq), BLOCKIO_SIG, 22, 4,
    2, 1586, 0 },

  { 794,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_igu), BLOCKIO_SIG,
    0, 1, 2, 1588, 0 },

  { 795,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Math Function1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction1_n), BLOCKIO_SIG,
    21, 1, 2, 1590, 0 },

  { 796,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_bd), BLOCKIO_SIG, 21, 1, 2,
    1592, 0 },

  { 797,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_fw), BLOCKIO_SIG, 22, 4,
    2, 1594, 0 },

  { 798,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSelector3), BLOCKIO_SIG,
    20, 2, 2, 1596, 0 },

  { 799,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_m3), BLOCKIO_SIG, 20, 2,
    2, 1598, 0 },

  { 800,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_k1), BLOCKIO_SIG, 20, 2,
    2, 1600, 0 },

  { 801,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_js), BLOCKIO_SIG, 20, 2,
    2, 1602, 0 },

  { 802,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Math Function2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction2_i), BLOCKIO_SIG,
    21, 1, 2, 1604, 0 },

  { 803,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_b4), BLOCKIO_SIG, 20, 2,
    2, 1606, 0 },

  { 804,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_gz), BLOCKIO_SIG, 20, 2,
    2, 1608, 0 },

  { 805,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_hv), BLOCKIO_SIG, 0,
    1, 2, 1610, 0 },

  { 806,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Math Function1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction1_f), BLOCKIO_SIG,
    21, 1, 2, 1612, 0 },

  { 807,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Add",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Add_cn), BLOCKIO_SIG, 21, 1, 2,
    1614, 0 },

  { 808,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T/Math Function",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction_o5), BLOCKIO_SIG,
    22, 4, 2, 1616, 0 },

  { 809,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_fm), BLOCKIO_SIG, 23, 2,
    2, 1618, 0 },

  { 810,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_cv), BLOCKIO_SIG, 23, 2,
    2, 1620, 0 },

  { 811,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_cp), BLOCKIO_SIG, 23, 2,
    2, 1622, 0 },

  { 812,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, u_n), BLOCKIO_SIG, 23, 2, 2,
    1624, 0 },

  { 813,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product3_f), BLOCKIO_SIG, 23, 2,
    2, 1626, 0 },

  { 814,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_mf), BLOCKIO_SIG, 23, 2, 2,
    1628, 0 },

  { 815,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_il), BLOCKIO_SIG, 23, 2, 2,
    1630, 0 },

  { 816,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/Multiport Selector4",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MultiportSelector4), BLOCKIO_SIG,
    21, 1, 2, 1632, 0 },

  { 817,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product1_k), BLOCKIO_SIG, 21, 1,
    2, 1634, 0 },

  { 818,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product2_h), BLOCKIO_SIG, 21, 1,
    2, 1636, 0 },

  { 819,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Math Function3",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction3_n), BLOCKIO_SIG,
    21, 1, 2, 1638, 0 },

  { 820,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product4",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product4_k), BLOCKIO_SIG, 21, 1,
    2, 1640, 0 },

  { 821,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Subtract",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract_jo), BLOCKIO_SIG, 21, 1,
    2, 1642, 0 },

  { 822,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Math Function2",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, MathFunction2_e), BLOCKIO_SIG,
    21, 1, 2, 1644, 0 },

  { 823,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Divide_m5), BLOCKIO_SIG, 21, 1,
    2, 1646, 0 },

  { 824,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Product_fa), BLOCKIO_SIG, 21, 1,
    2, 1648, 0 },

  { 825,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Subtract1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Subtract1_g), BLOCKIO_SIG, 21, 1,
    2, 1650, 0 },

  { 826,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, S12_e), BLOCKIO_SIG, 0, 1, 2,
    1652, 0 },

  { 827,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S_2(psi_d^s^2)",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, S_2psi_ds2), BLOCKIO_SIG, 22, 4,
    2, 1654, 0 },

  { 828,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S12",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, S12_m), BLOCKIO_SIG, 0, 1, 2,
    1656, 0 },

  { 829,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/S_2/S_2(psi_d^s)",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, S_2psi_ds), BLOCKIO_SIG, 22, 4,
    2, 1658, 0 },

  { 830,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R11",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R11_au), BLOCKIO_SIG, 0, 1, 2,
    1660, 0 },

  { 831,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R21",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R21_f), BLOCKIO_SIG, 0, 1, 2,
    1662, 0 },

  { 832,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R12",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R12_e), BLOCKIO_SIG, 0, 1, 2,
    1664, 0 },

  { 833,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R22",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R22_j), BLOCKIO_SIG, 0, 1, 2,
    1666, 0 },

  { 834,
    "cse1_cv3_1straight/Guidance Systems/Path-following/Line-Of-Sight/Position error signals/R_2/R_2(psi_d)",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, R_2psi_d), BLOCKIO_SIG, 22, 4, 2,
    1668, 0 },

  { 835, "cse1_cv3_1straight/Plants/Product", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Product_h0), BLOCKIO_SIG, 5, 1, 2, 1670, 0 },

  { 836, "cse1_cv3_1straight/Plants/Product1", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Product1_lw), BLOCKIO_SIG, 5, 1, 2, 1672, 0 },

  { 837,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_nh), BLOCKIO_SIG, 15, 1, 2,
    1674, 0 },

  { 838,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_ax), BLOCKIO_SIG, 15, 1, 2,
    1676, 0 },

  { 839,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_nj), BLOCKIO_SIG, 15, 1, 2,
    1678, 0 },

  { 840,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_jc), BLOCKIO_SIG, 15, 1, 2,
    1680, 0 },

  { 841,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_lk), BLOCKIO_SIG, 15, 1, 2,
    1682, 0 },

  { 842,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_a), BLOCKIO_SIG, 15, 1, 2,
    1684, 0 },

  { 843,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_m4), BLOCKIO_SIG, 15, 1, 2,
    1686, 0 },

  { 844,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_ot), BLOCKIO_SIG, 15, 1, 2,
    1688, 0 },

  { 845,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_h), BLOCKIO_SIG, 15, 1, 2,
    1690, 0 },

  { 846,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_mu), BLOCKIO_SIG, 15, 1, 2,
    1692, 0 },

  { 847,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_g), BLOCKIO_SIG, 15, 1, 2,
    1694, 0 },

  { 848,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_cr), BLOCKIO_SIG, 15, 1, 2,
    1696, 0 },

  { 849,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_j1), BLOCKIO_SIG, 15, 1, 2,
    1698, 0 },

  { 850,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_n), BLOCKIO_SIG, 15, 1, 2,
    1700, 0 },

  { 851,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_gp), BLOCKIO_SIG, 15, 1, 2,
    1702, 0 },

  { 852,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_hh), BLOCKIO_SIG, 15, 1, 2,
    1704, 0 },

  { 853,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_i2), BLOCKIO_SIG, 15, 1, 2,
    1706, 0 },

  { 854,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_i2), BLOCKIO_SIG, 15, 1, 2,
    1708, 0 },

  { 855,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_p4), BLOCKIO_SIG, 15, 1, 2,
    1710, 0 },

  { 856,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_b), BLOCKIO_SIG, 15, 1, 2,
    1712, 0 },

  { 857,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_nt), BLOCKIO_SIG, 15, 1, 2,
    1714, 0 },

  { 858,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_lm), BLOCKIO_SIG, 15, 1, 2,
    1716, 0 },

  { 859,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_gb), BLOCKIO_SIG, 15, 1, 2,
    1718, 0 },

  { 860,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_hj), BLOCKIO_SIG, 15, 1, 2,
    1720, 0 },

  { 861,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_gj), BLOCKIO_SIG, 15, 1, 2,
    1722, 0 },

  { 862,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_ll), BLOCKIO_SIG, 15, 1, 2,
    1724, 0 },

  { 863,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_du), BLOCKIO_SIG, 15, 1, 2,
    1726, 0 },

  { 864,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_m0), BLOCKIO_SIG, 15, 1, 2,
    1728, 0 },

  { 865,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_d), BLOCKIO_SIG, 15, 1, 2,
    1730, 0 },

  { 866,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_b), BLOCKIO_SIG, 15, 1, 2,
    1732, 0 },

  { 867,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_fg), BLOCKIO_SIG, 41, 1, 2,
    1734, 0 },

  { 868,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_aq), BLOCKIO_SIG, 41, 1, 2,
    1736, 0 },

  { 869,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_b4), BLOCKIO_SIG, 41, 1, 2,
    1738, 0 },

  { 870,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_ay), BLOCKIO_SIG, 41, 1, 2,
    1740, 0 },

  { 871,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_kd), BLOCKIO_SIG, 41, 1, 2,
    1742, 0 },

  { 872,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_cb), BLOCKIO_SIG, 41, 1, 2,
    1744, 0 },

  { 873,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_ma), BLOCKIO_SIG, 41, 1, 2,
    1746, 0 },

  { 874,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_gs), BLOCKIO_SIG, 41, 1, 2,
    1748, 0 },

  { 875,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_fv), BLOCKIO_SIG, 41, 1, 2,
    1750, 0 },

  { 876,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_ke), BLOCKIO_SIG, 41, 1, 2,
    1752, 0 },

  { 877,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_e), BLOCKIO_SIG, 41, 1, 2,
    1754, 0 },

  { 878,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_fx), BLOCKIO_SIG, 41, 1, 2,
    1756, 0 },

  { 879,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_fo), BLOCKIO_SIG, 41, 1, 2,
    1758, 0 },

  { 880,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_nv), BLOCKIO_SIG, 41, 1, 2,
    1760, 0 },

  { 881,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_ot), BLOCKIO_SIG, 41, 1, 2,
    1762, 0 },

  { 882,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_cd), BLOCKIO_SIG, 41, 1, 2,
    1764, 0 },

  { 883,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_fi), BLOCKIO_SIG, 41, 1, 2,
    1766, 0 },

  { 884,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_dk), BLOCKIO_SIG, 41, 1, 2,
    1768, 0 },

  { 885,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_bf), BLOCKIO_SIG, 41, 1, 2,
    1770, 0 },

  { 886,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_ea), BLOCKIO_SIG, 41, 1, 2,
    1772, 0 },

  { 887,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_dg), BLOCKIO_SIG, 41, 1, 2,
    1774, 0 },

  { 888,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_ls), BLOCKIO_SIG, 41, 1, 2,
    1776, 0 },

  { 889,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_h), BLOCKIO_SIG, 41, 1, 2,
    1778, 0 },

  { 890,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_be), BLOCKIO_SIG, 41, 1, 2,
    1780, 0 },

  { 891,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_df), BLOCKIO_SIG, 41, 1, 2,
    1782, 0 },

  { 892,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_kx), BLOCKIO_SIG, 41, 1, 2,
    1784, 0 },

  { 893,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_jd), BLOCKIO_SIG, 41, 1, 2,
    1786, 0 },

  { 894,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain_ga), BLOCKIO_SIG, 41, 1, 2,
    1788, 0 },

  { 895,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Gain1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Gain1_c), BLOCKIO_SIG, 41, 1, 2,
    1790, 0 },

  { 896,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/Sum",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Sum_mh), BLOCKIO_SIG, 41, 1, 2,
    1792, 0 },

  { 897, "cse1_cv3_1straight/Control Systems/if Nonlinear PID Control/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare), BLOCKIO_SIG, 3, 1, 2,
    1794, 0 },

  { 898,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_b), BLOCKIO_SIG, 3, 1, 2,
    1796, 0 },

  { 899,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_a), BLOCKIO_SIG, 3, 1, 2,
    1798, 0 },

  { 900,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_l), BLOCKIO_SIG, 3, 1, 2,
    1800, 0 },

  { 901,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_c), BLOCKIO_SIG, 3, 1, 2,
    1802, 0 },

  { 902,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_o), BLOCKIO_SIG, 3, 1, 2,
    1804, 0 },

  { 903,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_e), BLOCKIO_SIG, 3, 1, 2,
    1806, 0 },

  { 904,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_d), BLOCKIO_SIG, 3, 1, 2,
    1808, 0 },

  { 905,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_h), BLOCKIO_SIG, 3, 1, 2,
    1810, 0 },

  { 906,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_i), BLOCKIO_SIG, 3, 1, 2,
    1812, 0 },

  { 907,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_g), BLOCKIO_SIG, 3, 1, 2,
    1814, 0 },

  { 908,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ic), BLOCKIO_SIG, 3, 1,
    2, 1816, 0 },

  { 909,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_m), BLOCKIO_SIG, 3, 1, 2,
    1818, 0 },

  { 910,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_cp), BLOCKIO_SIG, 3, 1,
    2, 1820, 0 },

  { 911,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_mo), BLOCKIO_SIG, 3, 1,
    2, 1822, 0 },

  { 912,
    "cse1_cv3_1straight/Control Systems/Simple Control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_h2), BLOCKIO_SIG, 3, 1,
    2, 1824, 0 },

  { 913,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_gp), BLOCKIO_SIG, 3, 1,
    2, 1826, 0 },

  { 914,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_p), BLOCKIO_SIG, 3, 1, 2,
    1828, 0 },

  { 915,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_j), BLOCKIO_SIG, 3, 1, 2,
    1830, 0 },

  { 916,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ls), BLOCKIO_SIG, 3, 1,
    2, 1832, 0 },

  { 917,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_i3), BLOCKIO_SIG, 3, 1,
    2, 1834, 0 },

  { 918,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_n), BLOCKIO_SIG, 3, 1, 2,
    1836, 0 },

  { 919,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_l5), BLOCKIO_SIG, 3, 1,
    2, 1838, 0 },

  { 920,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ps), BLOCKIO_SIG, 3, 1,
    2, 1840, 0 },

  { 921,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ad), BLOCKIO_SIG, 3, 1,
    2, 1842, 0 },

  { 922,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_no), BLOCKIO_SIG, 3, 1,
    2, 1844, 0 },

  { 923,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_d4), BLOCKIO_SIG, 3, 1,
    2, 1846, 0 },

  { 924,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_k), BLOCKIO_SIG, 3, 1, 2,
    1848, 0 },

  { 925,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ba), BLOCKIO_SIG, 3, 1,
    2, 1850, 0 },

  { 926,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_mf), BLOCKIO_SIG, 3, 1,
    2, 1852, 0 },

  { 927,
    "cse1_cv3_1straight/Control Systems/DP control/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_id), BLOCKIO_SIG, 3, 1,
    2, 1854, 0 },

  { 928,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ib), BLOCKIO_SIG, 40, 1,
    2, 1856, 0 },

  { 929,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ng), BLOCKIO_SIG, 40, 1,
    2, 1858, 0 },

  { 930,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_kb), BLOCKIO_SIG, 40, 1,
    2, 1860, 0 },

  { 931,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_o2), BLOCKIO_SIG, 40, 1,
    2, 1862, 0 },

  { 932,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_gy), BLOCKIO_SIG, 40, 1,
    2, 1864, 0 },

  { 933,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ie), BLOCKIO_SIG, 40, 1,
    2, 1866, 0 },

  { 934,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_kt), BLOCKIO_SIG, 40, 1,
    2, 1868, 0 },

  { 935,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_nx), BLOCKIO_SIG, 40, 1,
    2, 1870, 0 },

  { 936,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_m0), BLOCKIO_SIG, 40, 1,
    2, 1872, 0 },

  { 937,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_idx), BLOCKIO_SIG, 40, 1,
    2, 1874, 0 },

  { 938,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_af), BLOCKIO_SIG, 40, 1,
    2, 1876, 0 },

  { 939,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_f), BLOCKIO_SIG, 40, 1,
    2, 1878, 0 },

  { 940,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_oe), BLOCKIO_SIG, 40, 1,
    2, 1880, 0 },

  { 941,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_en), BLOCKIO_SIG, 40, 1,
    2, 1882, 0 },

  { 942,
    "cse1_cv3_1straight/Control Systems/LgV design 2/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_lm), BLOCKIO_SIG, 40, 1,
    2, 1884, 0 },

  { 943,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_mw), BLOCKIO_SIG, 40, 1,
    2, 1886, 0 },

  { 944,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_mk), BLOCKIO_SIG, 40, 1,
    2, 1888, 0 },

  { 945,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_1 to u_1/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_jd), BLOCKIO_SIG, 40, 1,
    2, 1890, 0 },

  { 946,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ef), BLOCKIO_SIG, 40, 1,
    2, 1892, 0 },

  { 947,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_aw), BLOCKIO_SIG, 40, 1,
    2, 1894, 0 },

  { 948,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_2 to u_2/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_fe), BLOCKIO_SIG, 40, 1,
    2, 1896, 0 },

  { 949,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_i3y), BLOCKIO_SIG, 40, 1,
    2, 1898, 0 },

  { 950,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_pt), BLOCKIO_SIG, 40, 1,
    2, 1900, 0 },

  { 951,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_3 to u_3/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_io), BLOCKIO_SIG, 40, 1,
    2, 1902, 0 },

  { 952,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_lj), BLOCKIO_SIG, 40, 1,
    2, 1904, 0 },

  { 953,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_mz), BLOCKIO_SIG, 40, 1,
    2, 1906, 0 },

  { 954,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_4 to u_4/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_gf), BLOCKIO_SIG, 40, 1,
    2, 1908, 0 },

  { 955,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If < 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_h4), BLOCKIO_SIG, 40, 1,
    2, 1910, 0 },

  { 956,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/if == 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_ce), BLOCKIO_SIG, 40, 1,
    2, 1912, 0 },

  { 957,
    "cse1_cv3_1straight/Control Systems/Nonlinear PID/Thruster allocation/f_act to u_act/f_5 to u_5/If > 0/Compare",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, Compare_gt), BLOCKIO_SIG, 40, 1,
    2, 1914, 0 },

  { 958, "cse1_cv3_1straight/Plants/Compare To Zero/Compare", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Compare_oc), BLOCKIO_SIG, 3, 1, 2, 1916, 0 },

  { 959, "cse1_cv3_1straight/Plants/Compare To Zero1/Compare", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Compare_mj), BLOCKIO_SIG, 3, 1, 2, 1918, 0 },

  { 960, "cse1_cv3_1straight/Plants/Compare To Zero2/Compare", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Compare_hr), BLOCKIO_SIG, 3, 1, 2, 1920, 0 },

  { 961, "cse1_cv3_1straight/Plants/Compare To Zero3/Compare", 0, "", offsetof
    (BlockIO_CSE1_CV3_1Straight, Compare_e0), BLOCKIO_SIG, 3, 1, 2, 1922, 0 },

  { 962,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, LowerRelop1), BLOCKIO_SIG, 8, 1,
    2, 1924, 0 },

  { 963,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, UpperRelop), BLOCKIO_SIG, 8, 1,
    2, 1926, 0 },

  { 964,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic1/LowerRelop1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, LowerRelop1_p), BLOCKIO_SIG, 8,
    1, 2, 1928, 0 },

  { 965,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic1/UpperRelop",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, UpperRelop_e), BLOCKIO_SIG, 8, 1,
    2, 1930, 0 },

  { 966,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic2/LowerRelop1",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, LowerRelop1_n), BLOCKIO_SIG, 8,
    1, 2, 1932, 0 },

  { 967,
    "cse1_cv3_1straight/Plants/CSE1/Bow Thruster/Saturation Dynamic2/UpperRelop",
    0, "", offsetof(BlockIO_CSE1_CV3_1Straight, UpperRelop_j), BLOCKIO_SIG, 8, 1,
    2, 1934, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 3, 3, 6, 6, 1, 1, 1, 1, 1, 6, 1, 6, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 3, 5, 5, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 5, 5, 3, 1, 3,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1,
  1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1,
  3, 5, 5, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 3, 1, 3, 3,
  1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1,
  3, 3, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
  3, 3, 3, 3, 3, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2,
  3, 2, 3, 2, 3, 2, 2, 1, 2, 1, 3, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1,
  1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  3, 5, 5, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 3, 3, 3, 3, 1, 3, 1, 3, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3,
  1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2,
  1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1,
  3, 1, 1, 1, 3, 3, 3, 1, 3, 1, 3, 1, 3, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 7, 1, 1,
  1, 1, 1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 5,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1,
  1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 2, 2, 3, 1, 2, 1, 1, 3,
  1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 3, 1, 2, 3, 1, 2, 1, 2, 1, 2,
  1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 3, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1,
  1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1,
  1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2,
  1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2,
  2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1,
  1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize = 11;
static NI_ExternalIO NI_ExtList[] = {
  { 0, "Naviagation Systems/Qualisys 6 DOF/QTM In", 0, EXT_IN, 9, 9, 1 },

  { 1, "Naviagation Systems/Qualisys 6 DOF/SIT zAI1", 1, EXT_IN, 1, 1, 1 },

  { 2, "Naviagation Systems/Qualisys 6 DOF/SIT zAI2", 1, EXT_IN, 1, 1, 1 },

  { 3, "Naviagation Systems/Qualisys 6 DOF/SIT zAI0", 1, EXT_IN, 1, 1, 1 },

  { 0, "Plants/CSE1/Bow Thruster/SIT Out5 BT", 0, EXT_OUT, 1, 1, 1 },

  { 1, "Plants/CSE1/Voith Schneider Propeller /SIT Out1 Servo1", 0, EXT_OUT, 1,
    1, 1 },

  { 2, "Plants/CSE1/Voith Schneider Propeller /SIT Out2 Servo2", 0, EXT_OUT, 1,
    1, 1 },

  { 3, "Plants/CSE1/Voith Schneider Propeller /SIT Out3 Servo3", 0, EXT_OUT, 1,
    1, 1 },

  { 4, "Plants/CSE1/Voith Schneider Propeller /SIT Out4 Servo4", 0, EXT_OUT, 1,
    1, 1 },

  { 5, "Plants/CSE1/Voith Schneider Propeller /SIT Out6 VSPS Port", 0, EXT_OUT,
    1, 1, 1 },

  { 6, "Plants/CSE1/Voith Schneider Propeller /SIT Out7 VSPS Starboard", 0,
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

static char* NI_CompiledModelName = "cse1_cv3_1straight";
static char* NI_CompiledModelVersion = "1.296";
static char* NI_CompiledModelDateTime = "Fri Feb 14 09:47:35 2014";

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
   The undef allows us to access the real CSE1_CV3_1Straight_P
   In the rest of the code CSE1_CV3_1Straight_P is redefine to be the read-side
   of rtParameter.
 */
#undef CSE1_CV3_1Straight_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &CSE1_CV3_1Straight_P, sizeof
         (Parameters_CSE1_CV3_1Straight));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka CSE1_CV3_1Straight_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof
           (Parameters_CSE1_CV3_1Straight));
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
             (Parameters_CSE1_CV3_1Straight));

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
           (Parameters_CSE1_CV3_1Straight));
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

#endif                                 // of NI_ROOTMODEL_CSE1_CV3_1Straight
