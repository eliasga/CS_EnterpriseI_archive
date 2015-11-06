/*
 * NLPIDVersion2.c
 *
 * Real-Time Workshop code generation for Simulink model "NLPIDVersion2.mdl".
 *
 * Model Version              : 1.89
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Mon Mar 24 18:40:28 2014
 *
 * Target selection: nidll_vxworks.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "NLPIDVersion2.h"
#include "NLPIDVersion2_private.h"

/* Block signals (auto storage) */
BlockIO_NLPIDVersion2 NLPIDVersion2_B;

/* Continuous states */
ContinuousStates_NLPIDVersion2 NLPIDVersion2_X;

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
D_Work_NLPIDVersion2 NLPIDVersion2_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_NLPIDVersion2 NLPIDVersion2_PrevZCSigState;

/* Real-time model */
RT_MODEL_NLPIDVersion2 NLPIDVersion2_M_;
RT_MODEL_NLPIDVersion2 *NLPIDVersion2_M = &NLPIDVersion2_M_;

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
  NLPIDVersion2_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  NLPIDVersion2_output(0);
  NLPIDVersion2_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE5_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  NLPIDVersion2_output(0);
  NLPIDVersion2_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++)
    hB[i] = h * rt_ODE5_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  NLPIDVersion2_output(0);
  NLPIDVersion2_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++)
    hB[i] = h * rt_ODE5_B[3][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  NLPIDVersion2_output(0);
  NLPIDVersion2_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++)
    hB[i] = h * rt_ODE5_B[4][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  NLPIDVersion2_output(0);
  NLPIDVersion2_derivatives();

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
void NLPIDVersion2_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(NLPIDVersion2_M)) {
    NLPIDVersion2_M->Timing.t[0] = rtsiGetT(&NLPIDVersion2_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&NLPIDVersion2_M->solverInfo,
                          ((NLPIDVersion2_M->Timing.clockTick0+1)*
      NLPIDVersion2_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T tmp;
    real_T tmp_0[7];
    int32_T i;
    real_T tmp_1[18];
    real_T tmp_2[9];
    real_T tmp_3[4];
    real_T tmp_4[9];
    real_T tmp_5[6];
    int32_T tmp_6;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Constant: '<S4>/Initial psi [rad]' */
      NLPIDVersion2_B.Initialpsirad = NLPIDVersion2_P.Initialpsirad_Value;

      /* Constant: '<S4>/Initial x [m]' */
      NLPIDVersion2_B.Initialxm = NLPIDVersion2_P.Initialxm_Value;

      /* Constant: '<S4>/Initial y [m]' */
      NLPIDVersion2_B.Initialym = NLPIDVersion2_P.Initialym_Value;

      /* Constant: '<S4>/Initial r [rad//s]' */
      NLPIDVersion2_B.Initialrrads = NLPIDVersion2_P.Initialrrads_Value;

      /* Constant: '<S4>/Initial u [m//s]' */
      NLPIDVersion2_B.Initialums = NLPIDVersion2_P.Initialums_Value;

      /* Constant: '<S4>/Initial v [m//s]' */
      NLPIDVersion2_B.Initialvms = NLPIDVersion2_P.Initialvms_Value;

      /* Gain: '<S6>/ScalingLX' incorporates:
       *  Constant: '<S6>/AS_LX [-] '
       */
      NLPIDVersion2_B.xpositionofleftanalogstick11 =
        NLPIDVersion2_P.ScalingLX_Gain * NLPIDVersion2_P.AS_LX_Value;

      /* Gain: '<S6>/ScalingLY' incorporates:
       *  Constant: '<S6>/AS_LY [-]'
       */
      NLPIDVersion2_B.ypositionofleftanalogstick11 =
        NLPIDVersion2_P.ScalingLY_Gain * NLPIDVersion2_P.AS_LY_Value;

      /* Gain: '<S6>/Scaling_RX' incorporates:
       *  Constant: '<S6>/AS_RX [-]'
       */
      NLPIDVersion2_B.xpositionofrightanalogstick11 =
        NLPIDVersion2_P.Scaling_RX_Gain * NLPIDVersion2_P.AS_RX_Value;

      /* Gain: '<S6>/ScalingRY' incorporates:
       *  Constant: '<S6>/AS_RY [-]'
       */
      NLPIDVersion2_B.ypositionofrightanalogstick11 =
        NLPIDVersion2_P.ScalingRY_Gain * NLPIDVersion2_P.AS_RY_Value;

      /* Gain: '<S12>/Gain1' incorporates:
       *  Constant: '<S7>/setpointpsi [deg]'
       */
      NLPIDVersion2_B.Gain1 = NLPIDVersion2_P.Gain1_Gain *
        NLPIDVersion2_P.setpointpsideg_Value;

      /* Reshape: '<S13>/[3x3]' incorporates:
       *  Constant: '<S13>/12'
       *  Constant: '<S13>/13'
       *  Constant: '<S13>/21'
       *  Constant: '<S13>/23'
       *  Constant: '<S13>/31'
       *  Constant: '<S13>/32'
       *  Constant: '<S8>/ctrl1Kdpsi'
       *  Constant: '<S8>/ctrl1Kdx'
       *  Constant: '<S8>/ctrl1Kdy'
       */
      NLPIDVersion2_B.ux3[0] = NLPIDVersion2_P.ctrl1Kdx_Value;
      NLPIDVersion2_B.ux3[1] = NLPIDVersion2_P.u_Value_k0;
      NLPIDVersion2_B.ux3[2] = NLPIDVersion2_P.u_Value_o;
      NLPIDVersion2_B.ux3[3] = NLPIDVersion2_P.u_Value;
      NLPIDVersion2_B.ux3[4] = NLPIDVersion2_P.ctrl1Kdy_Value;
      NLPIDVersion2_B.ux3[5] = NLPIDVersion2_P.u_Value_oz;
      NLPIDVersion2_B.ux3[6] = NLPIDVersion2_P.u_Value_k;
      NLPIDVersion2_B.ux3[7] = NLPIDVersion2_P.u_Value_j;
      NLPIDVersion2_B.ux3[8] = NLPIDVersion2_P.ctrl1Kdpsi_Value;

      /* Reshape: '<S14>/[3x3]' incorporates:
       *  Constant: '<S14>/12'
       *  Constant: '<S14>/13'
       *  Constant: '<S14>/21'
       *  Constant: '<S14>/23'
       *  Constant: '<S14>/31'
       *  Constant: '<S14>/32'
       *  Constant: '<S8>/ctrl1Kipsi'
       *  Constant: '<S8>/ctrl1Kix'
       *  Constant: '<S8>/ctrl1Kiy'
       */
      NLPIDVersion2_B.ux3_a[0] = NLPIDVersion2_P.ctrl1Kix_Value;
      NLPIDVersion2_B.ux3_a[1] = NLPIDVersion2_P.u_Value_b;
      NLPIDVersion2_B.ux3_a[2] = NLPIDVersion2_P.u_Value_m;
      NLPIDVersion2_B.ux3_a[3] = NLPIDVersion2_P.u_Value_a;
      NLPIDVersion2_B.ux3_a[4] = NLPIDVersion2_P.ctrl1Kiy_Value;
      NLPIDVersion2_B.ux3_a[5] = NLPIDVersion2_P.u_Value_ea;
      NLPIDVersion2_B.ux3_a[6] = NLPIDVersion2_P.u_Value_e;
      NLPIDVersion2_B.ux3_a[7] = NLPIDVersion2_P.u_Value_f;
      NLPIDVersion2_B.ux3_a[8] = NLPIDVersion2_P.ctrl1Kipsi_Value;

      /* Reshape: '<S15>/[3x3]' incorporates:
       *  Constant: '<S15>/12'
       *  Constant: '<S15>/13'
       *  Constant: '<S15>/21'
       *  Constant: '<S15>/23'
       *  Constant: '<S15>/31'
       *  Constant: '<S15>/32'
       *  Constant: '<S8>/ctrl1Kppsi'
       *  Constant: '<S8>/ctrl1Kpx'
       *  Constant: '<S8>/ctrl1Kpy'
       */
      NLPIDVersion2_B.ux3_i[0] = NLPIDVersion2_P.ctrl1Kpx_Value;
      NLPIDVersion2_B.ux3_i[1] = NLPIDVersion2_P.u_Value_b4;
      NLPIDVersion2_B.ux3_i[2] = NLPIDVersion2_P.u_Value_i;
      NLPIDVersion2_B.ux3_i[3] = NLPIDVersion2_P.u_Value_et;
      NLPIDVersion2_B.ux3_i[4] = NLPIDVersion2_P.ctrl1Kpy_Value;
      NLPIDVersion2_B.ux3_i[5] = NLPIDVersion2_P.u_Value_aw;
      NLPIDVersion2_B.ux3_i[6] = NLPIDVersion2_P.u_Value_c;
      NLPIDVersion2_B.ux3_i[7] = NLPIDVersion2_P.u_Value_n;
      NLPIDVersion2_B.ux3_i[8] = NLPIDVersion2_P.ctrl1Kppsi_Value;

      /* Reshape: '<S16>/[2x2]' incorporates:
       *  Constant: '<S16>/12'
       *  Constant: '<S16>/21'
       *  Constant: '<S9>/Gamma_q_Surge'
       *  Constant: '<S9>/Gamma_q_Sway'
       */
      NLPIDVersion2_B.ux2[0] = NLPIDVersion2_P.Gamma_q_Surge_Value;
      NLPIDVersion2_B.ux2[1] = NLPIDVersion2_P.u_Value_kp;
      NLPIDVersion2_B.ux2[2] = NLPIDVersion2_P.u_Value_p;
      NLPIDVersion2_B.ux2[3] = NLPIDVersion2_P.Gamma_q_Sway_Value;

      /* Constant: '<S9>/Initial q_x' */
      NLPIDVersion2_B.Initialq_x = NLPIDVersion2_P.Initialq_x_Value;

      /* Constant: '<S9>/Initial q_y' */
      NLPIDVersion2_B.Initialq_y = NLPIDVersion2_P.Initialq_y_Value;

      /* Constant: '<S9>/Initial s' */
      NLPIDVersion2_B.Initials = NLPIDVersion2_P.Initials_Value;

      /* Reshape: '<S17>/[3x3]' incorporates:
       *  Constant: '<S17>/12'
       *  Constant: '<S17>/13'
       *  Constant: '<S17>/21'
       *  Constant: '<S17>/23'
       *  Constant: '<S17>/31'
       *  Constant: '<S17>/32'
       *  Constant: '<S9>/ctrl2Kdpsi'
       *  Constant: '<S9>/ctrl2Kdx'
       *  Constant: '<S9>/ctrl2Kdy'
       */
      NLPIDVersion2_B.ux3_ip[0] = NLPIDVersion2_P.ctrl2Kdx_Value;
      NLPIDVersion2_B.ux3_ip[1] = NLPIDVersion2_P.u_Value_fr;
      NLPIDVersion2_B.ux3_ip[2] = NLPIDVersion2_P.u_Value_ka;
      NLPIDVersion2_B.ux3_ip[3] = NLPIDVersion2_P.u_Value_l;
      NLPIDVersion2_B.ux3_ip[4] = NLPIDVersion2_P.ctrl2Kdy_Value;
      NLPIDVersion2_B.ux3_ip[5] = NLPIDVersion2_P.u_Value_hp;
      NLPIDVersion2_B.ux3_ip[6] = NLPIDVersion2_P.u_Value_h;
      NLPIDVersion2_B.ux3_ip[7] = NLPIDVersion2_P.u_Value_hr;
      NLPIDVersion2_B.ux3_ip[8] = NLPIDVersion2_P.ctrl2Kdpsi_Value;

      /* Reshape: '<S18>/[3x3]' incorporates:
       *  Constant: '<S18>/12'
       *  Constant: '<S18>/13'
       *  Constant: '<S18>/21'
       *  Constant: '<S18>/23'
       *  Constant: '<S18>/31'
       *  Constant: '<S18>/32'
       *  Constant: '<S9>/ctrl2Kipsi'
       *  Constant: '<S9>/ctrl2Kix'
       *  Constant: '<S9>/ctrl2Kiy'
       */
      NLPIDVersion2_B.ux3_p[0] = NLPIDVersion2_P.ctrl2Kix_Value;
      NLPIDVersion2_B.ux3_p[1] = NLPIDVersion2_P.u_Value_nj;
      NLPIDVersion2_B.ux3_p[2] = NLPIDVersion2_P.u_Value_ho;
      NLPIDVersion2_B.ux3_p[3] = NLPIDVersion2_P.u_Value_bm;
      NLPIDVersion2_B.ux3_p[4] = NLPIDVersion2_P.ctrl2Kiy_Value;
      NLPIDVersion2_B.ux3_p[5] = NLPIDVersion2_P.u_Value_cj;
      NLPIDVersion2_B.ux3_p[6] = NLPIDVersion2_P.u_Value_li;
      NLPIDVersion2_B.ux3_p[7] = NLPIDVersion2_P.u_Value_fn;
      NLPIDVersion2_B.ux3_p[8] = NLPIDVersion2_P.ctrl2Kipsi_Value;

      /* Reshape: '<S19>/[3x3]' incorporates:
       *  Constant: '<S19>/12'
       *  Constant: '<S19>/13'
       *  Constant: '<S19>/21'
       *  Constant: '<S19>/23'
       *  Constant: '<S19>/31'
       *  Constant: '<S19>/32'
       *  Constant: '<S9>/ctrl2Kppsi'
       *  Constant: '<S9>/ctrl2Kpx'
       *  Constant: '<S9>/ctrl2Kpy'
       */
      NLPIDVersion2_B.ux3_g[0] = NLPIDVersion2_P.ctrl2Kpx_Value;
      NLPIDVersion2_B.ux3_g[1] = NLPIDVersion2_P.u_Value_aq;
      NLPIDVersion2_B.ux3_g[2] = NLPIDVersion2_P.u_Value_fv;
      NLPIDVersion2_B.ux3_g[3] = NLPIDVersion2_P.u_Value_pl;
      NLPIDVersion2_B.ux3_g[4] = NLPIDVersion2_P.ctrl2Kpy_Value;
      NLPIDVersion2_B.ux3_g[5] = NLPIDVersion2_P.u_Value_h3;
      NLPIDVersion2_B.ux3_g[6] = NLPIDVersion2_P.u_Value_jh;
      NLPIDVersion2_B.ux3_g[7] = NLPIDVersion2_P.u_Value_fe;
      NLPIDVersion2_B.ux3_g[8] = NLPIDVersion2_P.ctrl2Kppsi_Value;

      /* Constant: '<S9>/kappa_1' */
      NLPIDVersion2_B.kappa_1 = NLPIDVersion2_P.kappa_1_Value;

      /* Gain: '<S28>/-l_x1' incorporates:
       *  Constant: '<S28>/l_x1'
       */
      NLPIDVersion2_B.l_x1 = NLPIDVersion2_P.l_x1_Gain *
        NLPIDVersion2_P.l_x1_Value;

      /* Gain: '<S28>/-l_x2' incorporates:
       *  Constant: '<S28>/l_x2'
       */
      NLPIDVersion2_B.l_x2 = NLPIDVersion2_P.l_x2_Gain *
        NLPIDVersion2_P.l_x2_Value;

      /* Gain: '<S28>/-l_y2' incorporates:
       *  Constant: '<S28>/l_y2'
       */
      NLPIDVersion2_B.l_y2 = NLPIDVersion2_P.l_y2_Gain *
        NLPIDVersion2_P.l_y2_Value;

      /* Reshape: '<S28>/3x5' incorporates:
       *  Constant: '<S28>/B_11'
       *  Constant: '<S28>/B_12'
       *  Constant: '<S28>/B_13'
       *  Constant: '<S28>/B_14'
       *  Constant: '<S28>/B_15'
       *  Constant: '<S28>/B_21'
       *  Constant: '<S28>/B_22'
       *  Constant: '<S28>/B_23'
       *  Constant: '<S28>/B_24'
       *  Constant: '<S28>/B_25'
       *  Constant: '<S28>/l_x3'
       *  Constant: '<S28>/l_y1'
       */
      NLPIDVersion2_B.x5[0] = NLPIDVersion2_P.B_11_Value;
      NLPIDVersion2_B.x5[1] = NLPIDVersion2_P.B_21_Value;
      NLPIDVersion2_B.x5[2] = NLPIDVersion2_P.l_y1_Value;
      NLPIDVersion2_B.x5[3] = NLPIDVersion2_P.B_12_Value;
      NLPIDVersion2_B.x5[4] = NLPIDVersion2_P.B_22_Value;
      NLPIDVersion2_B.x5[5] = NLPIDVersion2_B.l_x1;
      NLPIDVersion2_B.x5[6] = NLPIDVersion2_P.B_13_Value;
      NLPIDVersion2_B.x5[7] = NLPIDVersion2_P.B_23_Value;
      NLPIDVersion2_B.x5[8] = NLPIDVersion2_B.l_y2;
      NLPIDVersion2_B.x5[9] = NLPIDVersion2_P.B_14_Value;
      NLPIDVersion2_B.x5[10] = NLPIDVersion2_P.B_24_Value;
      NLPIDVersion2_B.x5[11] = NLPIDVersion2_B.l_x2;
      NLPIDVersion2_B.x5[12] = NLPIDVersion2_P.B_15_Value;
      NLPIDVersion2_B.x5[13] = NLPIDVersion2_P.B_25_Value;
      NLPIDVersion2_B.x5[14] = NLPIDVersion2_P.l_x3_Value;

      /* Gain: '<S27>/-N_r' incorporates:
       *  Constant: '<S27>/N_r'
       */
      NLPIDVersion2_B.N_r = NLPIDVersion2_P.N_r_Gain * NLPIDVersion2_P.N_r_Value;

      /* Gain: '<S27>/-N_v' incorporates:
       *  Constant: '<S27>/N_v'
       */
      NLPIDVersion2_B.N_v = NLPIDVersion2_P.N_v_Gain * NLPIDVersion2_P.N_v_Value;

      /* Gain: '<S27>/-X_u' incorporates:
       *  Constant: '<S27>/X_u'
       */
      NLPIDVersion2_B.X_u = NLPIDVersion2_P.X_u_Gain * NLPIDVersion2_P.X_u_Value;

      /* Gain: '<S27>/-Y_v' incorporates:
       *  Constant: '<S27>/Y_v'
       */
      NLPIDVersion2_B.Y_v = NLPIDVersion2_P.Y_v_Gain * NLPIDVersion2_P.Y_v_Value;

      /* Gain: '<S27>/-Y_vr' incorporates:
       *  Constant: '<S27>/Y_r'
       */
      NLPIDVersion2_B.Y_vr = NLPIDVersion2_P.Y_vr_Gain *
        NLPIDVersion2_P.Y_r_Value;

      /* Reshape: '<S27>/Linear Dampning matrix' incorporates:
       *  Constant: '<S27>/D_L_12'
       *  Constant: '<S27>/D_L_13'
       *  Constant: '<S27>/D_L_21'
       *  Constant: '<S27>/D_L_31'
       */
      NLPIDVersion2_B.LinearDampningmatrix[0] = NLPIDVersion2_B.X_u;
      NLPIDVersion2_B.LinearDampningmatrix[1] = NLPIDVersion2_P.D_L_21_Value;
      NLPIDVersion2_B.LinearDampningmatrix[2] = NLPIDVersion2_P.D_L_31_Value;
      NLPIDVersion2_B.LinearDampningmatrix[3] = NLPIDVersion2_P.D_L_12_Value;
      NLPIDVersion2_B.LinearDampningmatrix[4] = NLPIDVersion2_B.Y_v;
      NLPIDVersion2_B.LinearDampningmatrix[5] = NLPIDVersion2_B.N_v;
      NLPIDVersion2_B.LinearDampningmatrix[6] = NLPIDVersion2_P.D_L_13_Value;
      NLPIDVersion2_B.LinearDampningmatrix[7] = NLPIDVersion2_B.Y_vr;
      NLPIDVersion2_B.LinearDampningmatrix[8] = NLPIDVersion2_B.N_r;

      /* Sum: '<S26>/M_11' incorporates:
       *  Constant: '<S26>/X_udot'
       *  Constant: '<S26>/m'
       */
      NLPIDVersion2_B.M_11 = NLPIDVersion2_P.m_Value -
        NLPIDVersion2_P.X_udot_Value;

      /* Sum: '<S26>/M_22' incorporates:
       *  Constant: '<S26>/Y_vdot'
       *  Constant: '<S26>/m'
       */
      NLPIDVersion2_B.M_22 = NLPIDVersion2_P.m_Value -
        NLPIDVersion2_P.Y_vdot_Value;

      /* Product: '<S26>/m x_g' incorporates:
       *  Constant: '<S26>/m'
       *  Constant: '<S26>/x_g'
       */
      NLPIDVersion2_B.mx_g = NLPIDVersion2_P.m_Value * NLPIDVersion2_P.x_g_Value;

      /* Sum: '<S26>/M_32' incorporates:
       *  Constant: '<S26>/N_vdot'
       */
      NLPIDVersion2_B.M_32 = NLPIDVersion2_B.mx_g - NLPIDVersion2_P.N_vdot_Value;

      /* Sum: '<S26>/M_23' incorporates:
       *  Constant: '<S26>/Y_rdot'
       */
      NLPIDVersion2_B.M_23 = NLPIDVersion2_B.mx_g - NLPIDVersion2_P.Y_rdot_Value;

      /* Sum: '<S26>/M_33' incorporates:
       *  Constant: '<S26>/I_z'
       *  Constant: '<S26>/N_rdot'
       */
      NLPIDVersion2_B.M_33 = NLPIDVersion2_P.I_z_Value -
        NLPIDVersion2_P.N_rdot_Value;

      /* Reshape: '<S26>/3x3' incorporates:
       *  Constant: '<S26>/M_12'
       *  Constant: '<S26>/M_13'
       *  Constant: '<S26>/M_21'
       *  Constant: '<S26>/M_31'
       */
      NLPIDVersion2_B.x3[0] = NLPIDVersion2_B.M_11;
      NLPIDVersion2_B.x3[1] = NLPIDVersion2_P.M_21_Value;
      NLPIDVersion2_B.x3[2] = NLPIDVersion2_P.M_31_Value;
      NLPIDVersion2_B.x3[3] = NLPIDVersion2_P.M_12_Value;
      NLPIDVersion2_B.x3[4] = NLPIDVersion2_B.M_22;
      NLPIDVersion2_B.x3[5] = NLPIDVersion2_B.M_32;
      NLPIDVersion2_B.x3[6] = NLPIDVersion2_P.M_13_Value;
      NLPIDVersion2_B.x3[7] = NLPIDVersion2_B.M_23;
      NLPIDVersion2_B.x3[8] = NLPIDVersion2_B.M_33;

      /* Gain: '<S74>/-l_x1' incorporates:
       *  Constant: '<S74>/l_x1'
       */
      NLPIDVersion2_B.l_x1_f = NLPIDVersion2_P.l_x1_Gain_h *
        NLPIDVersion2_P.l_x1_Value_n;

      /* Gain: '<S74>/-l_y2' incorporates:
       *  Constant: '<S74>/l_y2'
       */
      NLPIDVersion2_B.l_y2_d = NLPIDVersion2_P.l_y2_Gain_g *
        NLPIDVersion2_P.l_y2_Value_n;

      /* Gain: '<S74>/-l_x2' incorporates:
       *  Constant: '<S74>/l_x2'
       */
      NLPIDVersion2_B.l_x2_d = NLPIDVersion2_P.l_x2_Gain_c *
        NLPIDVersion2_P.l_x2_Value_e;

      /* Reshape: '<S74>/3x5' incorporates:
       *  Constant: '<S74>/T_e11'
       *  Constant: '<S74>/T_e12'
       *  Constant: '<S74>/T_e13'
       *  Constant: '<S74>/T_e14'
       *  Constant: '<S74>/T_e15'
       *  Constant: '<S74>/T_e21'
       *  Constant: '<S74>/T_e22'
       *  Constant: '<S74>/T_e23'
       *  Constant: '<S74>/T_e24'
       *  Constant: '<S74>/T_e25'
       *  Constant: '<S74>/l_x3'
       *  Constant: '<S74>/l_y1'
       */
      NLPIDVersion2_B.x5_p[0] = NLPIDVersion2_P.T_e11_Value;
      NLPIDVersion2_B.x5_p[1] = NLPIDVersion2_P.T_e21_Value;
      NLPIDVersion2_B.x5_p[2] = NLPIDVersion2_P.l_y1_Value_o;
      NLPIDVersion2_B.x5_p[3] = NLPIDVersion2_P.T_e12_Value;
      NLPIDVersion2_B.x5_p[4] = NLPIDVersion2_P.T_e22_Value;
      NLPIDVersion2_B.x5_p[5] = NLPIDVersion2_B.l_x1_f;
      NLPIDVersion2_B.x5_p[6] = NLPIDVersion2_P.T_e13_Value;
      NLPIDVersion2_B.x5_p[7] = NLPIDVersion2_P.T_e23_Value;
      NLPIDVersion2_B.x5_p[8] = NLPIDVersion2_B.l_y2_d;
      NLPIDVersion2_B.x5_p[9] = NLPIDVersion2_P.T_e14_Value;
      NLPIDVersion2_B.x5_p[10] = NLPIDVersion2_P.T_e24_Value;
      NLPIDVersion2_B.x5_p[11] = NLPIDVersion2_B.l_x2_d;
      NLPIDVersion2_B.x5_p[12] = NLPIDVersion2_P.T_e15_Value;
      NLPIDVersion2_B.x5_p[13] = NLPIDVersion2_P.T_e25_Value;
      NLPIDVersion2_B.x5_p[14] = NLPIDVersion2_P.l_x3_Value_o;

      /* Gain: '<S32>/PS3 u_1' */
      NLPIDVersion2_B.u_1 = NLPIDVersion2_P.PS3u_1_Gain *
        NLPIDVersion2_B.ypositionofleftanalogstick11;

      /* Lookup Block: '<S73>/u_1 to f_1'
       * About '<S73>/u_1 to f_1 :'
       * Lookup Block: '<S73>/u_1 to f_1'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPIDVersion2_B.u_1tof_1),
                           NLPIDVersion2_P.u_1tof_1_YData, NLPIDVersion2_B.u_1,
                           NLPIDVersion2_P.u_1tof_1_XData, 18U);

      /* Gain: '<S32>/PS3 u_2' */
      NLPIDVersion2_B.u_2 = NLPIDVersion2_P.PS3u_2_Gain *
        NLPIDVersion2_B.xpositionofleftanalogstick11;

      /* Lookup Block: '<S73>/u_2 to f_2'
       * About '<S73>/u_2 to f_2 :'
       * Lookup Block: '<S73>/u_2 to f_2'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPIDVersion2_B.u_2tof_2),
                           NLPIDVersion2_P.u_2tof_2_YData, NLPIDVersion2_B.u_2,
                           NLPIDVersion2_P.u_2tof_2_XData, 20U);

      /* Gain: '<S32>/PS3 u_3' */
      NLPIDVersion2_B.u_3 = NLPIDVersion2_P.PS3u_3_Gain *
        NLPIDVersion2_B.ypositionofrightanalogstick11;

      /* Lookup Block: '<S73>/u_3 to f_3'
       * About '<S73>/u_3 to f_3 :'
       * Lookup Block: '<S73>/u_3 to f_3'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPIDVersion2_B.u_3tof_3),
                           NLPIDVersion2_P.u_3tof_3_YData, NLPIDVersion2_B.u_3,
                           NLPIDVersion2_P.u_3tof_3_XData, 18U);

      /* Gain: '<S32>/PS3 u_4' */
      NLPIDVersion2_B.u_4 = NLPIDVersion2_P.PS3u_4_Gain *
        NLPIDVersion2_B.xpositionofrightanalogstick11;

      /* Lookup Block: '<S73>/u_4 to f_4'
       * About '<S73>/u_4 to f_4 :'
       * Lookup Block: '<S73>/u_4 to f_4'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPIDVersion2_B.u_4tof_4),
                           NLPIDVersion2_P.u_4tof_4_YData, NLPIDVersion2_B.u_4,
                           NLPIDVersion2_P.u_4tof_4_XData, 16U);

      /* Sum: '<S32>/Add' incorporates:
       *  Constant: '<S6>/L2 [-]'
       *  Constant: '<S6>/R2 [-]'
       */
      NLPIDVersion2_B.BowThrusterdirection = NLPIDVersion2_P.L2_Value +
        NLPIDVersion2_P.R2_Value;

      /* Gain: '<S32>/PS3 u_5' */
      NLPIDVersion2_B.u_5 = NLPIDVersion2_P.PS3u_5_Gain *
        NLPIDVersion2_B.BowThrusterdirection;

      /* Lookup Block: '<S73>/u_5 to f_5'
       * About '<S73>/u_5 to f_5 :'
       * Lookup Block: '<S73>/u_5 to f_5'
       * Input0  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       * XData parameter uses the same data type and scaling as Input0
       * YData parameter uses the same data type and scaling as Output0


       */
      LookUp_real_T_real_T( &(NLPIDVersion2_B.u_5tof_5),
                           NLPIDVersion2_P.u_5tof_5_YData, NLPIDVersion2_B.u_5,
                           NLPIDVersion2_P.u_5tof_5_XData, 6U);

      /* SignalConversion: '<S72>/TmpHiddenBufferAtProductInport2' */
      NLPIDVersion2_B.TmpHiddenBufferAtProductInport2[0] =
        NLPIDVersion2_B.u_1tof_1;
      NLPIDVersion2_B.TmpHiddenBufferAtProductInport2[1] =
        NLPIDVersion2_B.u_2tof_2;
      NLPIDVersion2_B.TmpHiddenBufferAtProductInport2[2] =
        NLPIDVersion2_B.u_3tof_3;
      NLPIDVersion2_B.TmpHiddenBufferAtProductInport2[3] =
        NLPIDVersion2_B.u_4tof_4;
      NLPIDVersion2_B.TmpHiddenBufferAtProductInport2[4] =
        NLPIDVersion2_B.u_5tof_5;

      /* Product: '<S72>/Product' */
      for (i = 0; i < 3; i++) {
        NLPIDVersion2_B.Product[i] = 0.0;
        for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
          NLPIDVersion2_B.Product[i] = NLPIDVersion2_B.x5_p[3 * tmp_6 + i] *
            NLPIDVersion2_B.TmpHiddenBufferAtProductInport2[tmp_6] +
            NLPIDVersion2_B.Product[i];
        }
      }
    }

    /* Gain: '<S166>/QTM In3 x-coord [mm]' */
    NLPIDVersion2_B.QTMIn3xcoordmm = NLPIDVersion2_P.QTMIn3xcoordmm_Gain *
      NLPIDVersion2_B.QTMIn[2];

    /* Gain: '<S166>/mm2m x' */
    NLPIDVersion2_B.mm2mx = NLPIDVersion2_P.mm2mx_Gain *
      NLPIDVersion2_B.QTMIn3xcoordmm;

    /* Gain: '<S166>/QTM In4 y-coord [mm]' */
    NLPIDVersion2_B.QTMIn4ycoordmm = NLPIDVersion2_P.QTMIn4ycoordmm_Gain *
      NLPIDVersion2_B.QTMIn[3];

    /* Gain: '<S166>/mm2m y' */
    NLPIDVersion2_B.mm2my = NLPIDVersion2_P.mm2my_Gain *
      NLPIDVersion2_B.QTMIn4ycoordmm;

    /* Gain: '<S166>/QTM In6 yaw [deg]' */
    NLPIDVersion2_B.QTMIn6yawdeg = NLPIDVersion2_P.QTMIn6yawdeg_Gain *
      NLPIDVersion2_B.QTMIn[5];

    /* Gain: '<S166>/d2r yaw' */
    NLPIDVersion2_B.d2ryaw = NLPIDVersion2_P.d2ryaw_Gain *
      NLPIDVersion2_B.QTMIn6yawdeg;

    /* Outputs for enable SubSystem: '<S25>/Linear Simulator' incorporates:
     *  Constant: '<S4>/Enable Linear Simulator'
     *  EnablePort: '<S170>/Enable'
     */
    if (rtmIsMajorTimeStep(NLPIDVersion2_M) && rtmIsMajorTimeStep
        (NLPIDVersion2_M)) {
      if (NLPIDVersion2_P.EnableLinearSimulator_Value > 0.0) {
        if (NLPIDVersion2_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S178>/Integrator' */
          if (rtmIsFirstInitCond(NLPIDVersion2_M)) {
            NLPIDVersion2_X.Integrator_CSTATE_d[0] = 0.0;
            NLPIDVersion2_X.Integrator_CSTATE_d[1] = 0.0;
            NLPIDVersion2_X.Integrator_CSTATE_d[2] = 0.0;
          }

          NLPIDVersion2_DWork.Integrator_IWORK_c.IcNeedsLoading = 1;

          /* Integrator Block: '<S178>/Integrator1' */
          if (rtmIsFirstInitCond(NLPIDVersion2_M)) {
            NLPIDVersion2_X.Integrator1_CSTATE_h[0] = 0.0;
            NLPIDVersion2_X.Integrator1_CSTATE_h[1] = 0.0;
            NLPIDVersion2_X.Integrator1_CSTATE_h[2] = 0.0;
          }

          NLPIDVersion2_DWork.Integrator1_IWORK_b.IcNeedsLoading = 1;
          NLPIDVersion2_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (NLPIDVersion2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
          NLPIDVersion2_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (NLPIDVersion2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Integrator Block: '<S178>/Integrator'
       */
      if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &NLPIDVersion2_PrevZCSigState.Integrator_Reset_ZCE_f,
                           NLPIDVersion2_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || NLPIDVersion2_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            NLPIDVersion2_DWork.Integrator_IWORK_c.IcNeedsLoading) {
          NLPIDVersion2_X.Integrator_CSTATE_d[0] = NLPIDVersion2_B.Initialums;
          NLPIDVersion2_X.Integrator_CSTATE_d[1] = NLPIDVersion2_B.Initialvms;
          NLPIDVersion2_X.Integrator_CSTATE_d[2] = NLPIDVersion2_B.Initialrrads;
        }

        NLPIDVersion2_DWork.Integrator_IWORK_c.IcNeedsLoading = 0;
      }

      NLPIDVersion2_B.Integrator_d[0] = NLPIDVersion2_X.Integrator_CSTATE_d[0];
      NLPIDVersion2_B.Integrator_d[1] = NLPIDVersion2_X.Integrator_CSTATE_d[1];
      NLPIDVersion2_B.Integrator_d[2] = NLPIDVersion2_X.Integrator_CSTATE_d[2];

      /* Integrator Block: '<S178>/Integrator1'
       */
      if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &NLPIDVersion2_PrevZCSigState.Integrator1_Reset_ZCE_j,
                           NLPIDVersion2_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || NLPIDVersion2_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            NLPIDVersion2_DWork.Integrator1_IWORK_b.IcNeedsLoading) {
          NLPIDVersion2_X.Integrator1_CSTATE_h[0] = NLPIDVersion2_B.Initialxm;
          NLPIDVersion2_X.Integrator1_CSTATE_h[1] = NLPIDVersion2_B.Initialym;
          NLPIDVersion2_X.Integrator1_CSTATE_h[2] =
            NLPIDVersion2_B.Initialpsirad;
        }

        NLPIDVersion2_DWork.Integrator1_IWORK_b.IcNeedsLoading = 0;
      }

      NLPIDVersion2_B.Integrator1_n[0] = NLPIDVersion2_X.Integrator1_CSTATE_h[0];
      NLPIDVersion2_B.Integrator1_n[1] = NLPIDVersion2_X.Integrator1_CSTATE_h[1];
      NLPIDVersion2_B.Integrator1_n[2] = NLPIDVersion2_X.Integrator1_CSTATE_h[2];

      /* Fcn: '<S179>/R11' */
      NLPIDVersion2_B.R11_p = cos(NLPIDVersion2_B.Integrator1_n[2]);

      /* Fcn: '<S179>/R21' */
      NLPIDVersion2_B.R21_b = sin(NLPIDVersion2_B.Integrator1_n[2]);

      /* Fcn: '<S179>/R12' */
      NLPIDVersion2_B.R12_o = -1.0 * sin(NLPIDVersion2_B.Integrator1_n[2]);

      /* Fcn: '<S179>/R22' */
      NLPIDVersion2_B.R22_px = cos(NLPIDVersion2_B.Integrator1_n[2]);

      /* Reshape: '<S179>/R(psi)' incorporates:
       *  Constant: '<S179>/R13'
       *  Constant: '<S179>/R23'
       *  Constant: '<S179>/R31'
       *  Constant: '<S179>/R32'
       *  Constant: '<S179>/R33'
       */
      NLPIDVersion2_B.Rpsi_b[0] = NLPIDVersion2_B.R11_p;
      NLPIDVersion2_B.Rpsi_b[1] = NLPIDVersion2_B.R21_b;
      NLPIDVersion2_B.Rpsi_b[2] = NLPIDVersion2_P.R31_Value_m;
      NLPIDVersion2_B.Rpsi_b[3] = NLPIDVersion2_B.R12_o;
      NLPIDVersion2_B.Rpsi_b[4] = NLPIDVersion2_B.R22_px;
      NLPIDVersion2_B.Rpsi_b[5] = NLPIDVersion2_P.R32_Value_d;
      NLPIDVersion2_B.Rpsi_b[6] = NLPIDVersion2_P.R13_Value_l;
      NLPIDVersion2_B.Rpsi_b[7] = NLPIDVersion2_P.R23_Value_c;
      NLPIDVersion2_B.Rpsi_b[8] = NLPIDVersion2_P.R33_Value_b;

      /* Product: '<S178>/Product3' */
      for (i = 0; i < 3; i++) {
        NLPIDVersion2_B.Product3_mm[i] = 0.0;
        NLPIDVersion2_B.Product3_mm[i] = NLPIDVersion2_B.Rpsi_b[i] *
          NLPIDVersion2_B.Integrator_d[0] + NLPIDVersion2_B.Product3_mm[i];
        NLPIDVersion2_B.Product3_mm[i] = NLPIDVersion2_B.Rpsi_b[i + 3] *
          NLPIDVersion2_B.Integrator_d[1] + NLPIDVersion2_B.Product3_mm[i];
        NLPIDVersion2_B.Product3_mm[i] = NLPIDVersion2_B.Rpsi_b[i + 6] *
          NLPIDVersion2_B.Integrator_d[2] + NLPIDVersion2_B.Product3_mm[i];
      }
    }

    /* end of Outputs for SubSystem: '<S25>/Linear Simulator' */

    /* MultiPortSwitch: '<S167>/eta Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)NLPIDVersion2_P.ControlInputSelector_Value == 0) {
      NLPIDVersion2_B.etaSwitch[0] = NLPIDVersion2_B.mm2mx;
      NLPIDVersion2_B.etaSwitch[1] = NLPIDVersion2_B.mm2my;
      NLPIDVersion2_B.etaSwitch[2] = NLPIDVersion2_B.d2ryaw;
    } else {
      NLPIDVersion2_B.etaSwitch[0] = NLPIDVersion2_B.Integrator1_n[0];
      NLPIDVersion2_B.etaSwitch[1] = NLPIDVersion2_B.Integrator1_n[1];
      NLPIDVersion2_B.etaSwitch[2] = NLPIDVersion2_B.Integrator1_n[2];
    }

    /* Fcn: '<S30>/yaw angle' */
    NLPIDVersion2_B.psi = NLPIDVersion2_B.etaSwitch[2];

    /* Saturate: '<S36>/Saturation' */
    tmp = NLPIDVersion2_B.psi;
    NLPIDVersion2_B.Saturation = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation_LowerSat, NLPIDVersion2_P.Saturation_UpperSat);

    /* Signum: '<S36>/Sign' */
    NLPIDVersion2_B.Sign = rt_SIGNd_snf(NLPIDVersion2_B.Saturation);

    /* Gain: '<S36>/Gain' */
    NLPIDVersion2_B.Gain = NLPIDVersion2_P.Gain_Gain * NLPIDVersion2_B.Sign;

    /* Sum: '<S36>/Sum1' */
    NLPIDVersion2_B.Sum1 = NLPIDVersion2_B.Saturation + NLPIDVersion2_B.Gain;

    /* Math: '<S36>/Math Function' incorporates:
     *  Constant: '<S36>/Constant'
     */
    NLPIDVersion2_B.MathFunction = rt_rem_snf(NLPIDVersion2_B.Sum1,
      NLPIDVersion2_P.Constant_Value);

    /* Sum: '<S36>/Sum' */
    NLPIDVersion2_B.Sum = NLPIDVersion2_B.MathFunction - NLPIDVersion2_B.Gain;

    /* Sum: '<S30>/Sum2' incorporates:
     *  Constant: '<S7>/setpointx [m]'
     *  Constant: '<S7>/setpointy [m]'
     */
    NLPIDVersion2_B.Sum2[0] = NLPIDVersion2_P.setpointxm_Value -
      NLPIDVersion2_B.etaSwitch[0];
    NLPIDVersion2_B.Sum2[1] = NLPIDVersion2_P.setpointym_Value -
      NLPIDVersion2_B.etaSwitch[1];
    NLPIDVersion2_B.Sum2[2] = NLPIDVersion2_B.Gain1 - NLPIDVersion2_B.etaSwitch
      [2];

    /* Saturate: '<S35>/Saturation' */
    tmp = NLPIDVersion2_B.Sum2[2];
    NLPIDVersion2_B.Saturation_d = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation_LowerSat_f,
      NLPIDVersion2_P.Saturation_UpperSat_i);

    /* Signum: '<S35>/Sign' */
    NLPIDVersion2_B.Sign_h = rt_SIGNd_snf(NLPIDVersion2_B.Saturation_d);

    /* Gain: '<S35>/Gain' */
    NLPIDVersion2_B.Gain_g = NLPIDVersion2_P.Gain_Gain_n *
      NLPIDVersion2_B.Sign_h;

    /* Sum: '<S35>/Sum1' */
    NLPIDVersion2_B.Sum1_j = NLPIDVersion2_B.Saturation_d +
      NLPIDVersion2_B.Gain_g;

    /* Math: '<S35>/Math Function' incorporates:
     *  Constant: '<S35>/Constant'
     */
    NLPIDVersion2_B.MathFunction_a = rt_rem_snf(NLPIDVersion2_B.Sum1_j,
      NLPIDVersion2_P.Constant_Value_o);

    /* Sum: '<S35>/Sum' */
    NLPIDVersion2_B.Sum_l = NLPIDVersion2_B.MathFunction_a -
      NLPIDVersion2_B.Gain_g;

    /* Fcn: '<S34>/Row1' */
    NLPIDVersion2_B.Row1 = cos(NLPIDVersion2_B.Sum) * NLPIDVersion2_B.Sum2[0] +
      sin(NLPIDVersion2_B.Sum) * NLPIDVersion2_B.Sum2[1];

    /* Fcn: '<S34>/Row2' */
    NLPIDVersion2_B.Row2 = (-sin(NLPIDVersion2_B.Sum)) * NLPIDVersion2_B.Sum2[0]
      + cos(NLPIDVersion2_B.Sum) * NLPIDVersion2_B.Sum2[1];

    /* Fcn: '<S34>/Row3' */
    NLPIDVersion2_B.Row3 = NLPIDVersion2_B.Sum_l;

    /* SignalConversion: '<S30>/TmpHiddenBufferAtProductInport2' */
    NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_e[0] = NLPIDVersion2_B.Row1;
    NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_e[1] = NLPIDVersion2_B.Row2;
    NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_e[2] = NLPIDVersion2_B.Row3;

    /* Product: '<S30>/Product' */
    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.Product_i[i] = 0.0;
      NLPIDVersion2_B.Product_i[i] = NLPIDVersion2_B.ux3_i[i] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_e[0] +
        NLPIDVersion2_B.Product_i[i];
      NLPIDVersion2_B.Product_i[i] = NLPIDVersion2_B.ux3_i[i + 3] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_e[1] +
        NLPIDVersion2_B.Product_i[i];
      NLPIDVersion2_B.Product_i[i] = NLPIDVersion2_B.ux3_i[i + 6] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_e[2] +
        NLPIDVersion2_B.Product_i[i];
    }

    /* Integrator Block: '<S30>/Integrator'
     */
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &NLPIDVersion2_PrevZCSigState.Integrator_Reset_ZCE,
                         NLPIDVersion2_P.ctrl1ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || NLPIDVersion2_P.ctrl1ResetIntegrator_Value != 0.0) {
        NLPIDVersion2_X.Integrator_CSTATE[0] = NLPIDVersion2_P.Integrator_IC;
        NLPIDVersion2_X.Integrator_CSTATE[1] = NLPIDVersion2_P.Integrator_IC;
        NLPIDVersion2_X.Integrator_CSTATE[2] = NLPIDVersion2_P.Integrator_IC;
      }
    }

    NLPIDVersion2_B.Integrator[0] = NLPIDVersion2_X.Integrator_CSTATE[0];
    NLPIDVersion2_B.Integrator[1] = NLPIDVersion2_X.Integrator_CSTATE[1];
    NLPIDVersion2_B.Integrator[2] = NLPIDVersion2_X.Integrator_CSTATE[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S30>/Product1' */
      NLPIDVersion2_B.Product1[i] = 0.0;
      NLPIDVersion2_B.Product1[i] = NLPIDVersion2_B.ux3_a[i] *
        NLPIDVersion2_B.Integrator[0] + NLPIDVersion2_B.Product1[i];
      NLPIDVersion2_B.Product1[i] = NLPIDVersion2_B.ux3_a[i + 3] *
        NLPIDVersion2_B.Integrator[1] + NLPIDVersion2_B.Product1[i];
      NLPIDVersion2_B.Product1[i] = NLPIDVersion2_B.ux3_a[i + 6] *
        NLPIDVersion2_B.Integrator[2] + NLPIDVersion2_B.Product1[i];

      /* Sum: '<S30>/Sum3' */
      NLPIDVersion2_B.Sum3[i] = NLPIDVersion2_B.Product_i[i] +
        NLPIDVersion2_B.Product1[i];
    }

    /* Gain: '<S166>/QTM In8 roll [deg]' */
    NLPIDVersion2_B.QTMIn8rolldeg = NLPIDVersion2_P.QTMIn8rolldeg_Gain *
      NLPIDVersion2_B.QTMIn[7];

    /* Gain: '<S166>/d2r roll' */
    NLPIDVersion2_B.d2rroll = NLPIDVersion2_P.d2rroll_Gain *
      NLPIDVersion2_B.QTMIn8rolldeg;

    /* Gain: '<S166>/QTM In7 pitch [deg]' */
    NLPIDVersion2_B.QTMIn7pitchdeg = NLPIDVersion2_P.QTMIn7pitchdeg_Gain *
      NLPIDVersion2_B.QTMIn[6];

    /* Gain: '<S166>/d2r pitch' */
    NLPIDVersion2_B.d2rpitch = NLPIDVersion2_P.d2rpitch_Gain *
      NLPIDVersion2_B.QTMIn7pitchdeg;

    /* Trigonometry: '<S168>/sin(theta)' */
    NLPIDVersion2_B.sintheta[0] = sin(NLPIDVersion2_B.d2rroll);
    NLPIDVersion2_B.sintheta[1] = sin(NLPIDVersion2_B.d2rpitch);
    NLPIDVersion2_B.sintheta[2] = sin(NLPIDVersion2_B.d2ryaw);

    /* Trigonometry: '<S168>/cos(theta)' */
    NLPIDVersion2_B.costheta[0] = cos(NLPIDVersion2_B.d2rroll);
    NLPIDVersion2_B.costheta[1] = cos(NLPIDVersion2_B.d2rpitch);
    NLPIDVersion2_B.costheta[2] = cos(NLPIDVersion2_B.d2ryaw);

    /* Fcn: '<S168>/R11' */
    NLPIDVersion2_B.R11 = NLPIDVersion2_B.costheta[1] *
      NLPIDVersion2_B.costheta[2];

    /* Fcn: '<S168>/R21 ' */
    NLPIDVersion2_B.R21 = NLPIDVersion2_B.sintheta[0] *
      NLPIDVersion2_B.sintheta[1] * NLPIDVersion2_B.costheta[2] +
      (-NLPIDVersion2_B.costheta[0]) * NLPIDVersion2_B.sintheta[2];

    /* Fcn: '<S168>/R31 ' */
    NLPIDVersion2_B.R31 = NLPIDVersion2_B.costheta[0] *
      NLPIDVersion2_B.sintheta[1] * NLPIDVersion2_B.costheta[2] +
      NLPIDVersion2_B.sintheta[0] * NLPIDVersion2_B.sintheta[2];

    /* Fcn: '<S168>/R12' */
    NLPIDVersion2_B.R12 = NLPIDVersion2_B.costheta[1] *
      NLPIDVersion2_B.sintheta[2];

    /* Fcn: '<S168>/R22' */
    NLPIDVersion2_B.R22 = NLPIDVersion2_B.sintheta[0] *
      NLPIDVersion2_B.sintheta[1] * NLPIDVersion2_B.sintheta[2] +
      NLPIDVersion2_B.costheta[0] * NLPIDVersion2_B.costheta[2];

    /* Fcn: '<S168>/R32' */
    NLPIDVersion2_B.R32 = NLPIDVersion2_B.costheta[0] *
      NLPIDVersion2_B.sintheta[1] * NLPIDVersion2_B.sintheta[2] +
      (-NLPIDVersion2_B.sintheta[0]) * NLPIDVersion2_B.costheta[2];

    /* Fcn: '<S168>/R13' */
    NLPIDVersion2_B.R13 = -NLPIDVersion2_B.sintheta[1];

    /* Fcn: '<S168>/R23' */
    NLPIDVersion2_B.R23 = NLPIDVersion2_B.sintheta[0] *
      NLPIDVersion2_B.costheta[1];

    /* Fcn: '<S168>/R33' */
    NLPIDVersion2_B.R33 = NLPIDVersion2_B.costheta[0] *
      NLPIDVersion2_B.costheta[1];

    /* Reshape: '<S168>/Reshape 9x1->3x3' */
    NLPIDVersion2_B.Reshape9x13x3[0] = NLPIDVersion2_B.R11;
    NLPIDVersion2_B.Reshape9x13x3[1] = NLPIDVersion2_B.R21;
    NLPIDVersion2_B.Reshape9x13x3[2] = NLPIDVersion2_B.R31;
    NLPIDVersion2_B.Reshape9x13x3[3] = NLPIDVersion2_B.R12;
    NLPIDVersion2_B.Reshape9x13x3[4] = NLPIDVersion2_B.R22;
    NLPIDVersion2_B.Reshape9x13x3[5] = NLPIDVersion2_B.R32;
    NLPIDVersion2_B.Reshape9x13x3[6] = NLPIDVersion2_B.R13;
    NLPIDVersion2_B.Reshape9x13x3[7] = NLPIDVersion2_B.R23;
    NLPIDVersion2_B.Reshape9x13x3[8] = NLPIDVersion2_B.R33;

    /* Concatenate: '<S166>/Matrix Concatenate' incorporates:
     *  Constant: '<S166>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = NLPIDVersion2_B.Reshape9x13x3[3 * i];
      tmp_1[1 + 6 * i] = NLPIDVersion2_B.Reshape9x13x3[3 * i + 1];
      tmp_1[2 + 6 * i] = NLPIDVersion2_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = NLPIDVersion2_P.Constant1_Value[3 * i];
      tmp_1[4 + 6 * i] = NLPIDVersion2_P.Constant1_Value[3 * i + 1];
      tmp_1[5 + 6 * i] = NLPIDVersion2_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&NLPIDVersion2_B.MatrixConcatenate2[0]), (void *)&tmp_1[0],
           18U * sizeof(real_T));

    /* Concatenate: '<S166>/Matrix Concatenate1' incorporates:
     *  Constant: '<S166>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_1[6 * i] = NLPIDVersion2_P.Constant1_Value[3 * i];
      tmp_1[1 + 6 * i] = NLPIDVersion2_P.Constant1_Value[3 * i + 1];
      tmp_1[2 + 6 * i] = NLPIDVersion2_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_1[3 + 6 * i] = NLPIDVersion2_B.Reshape9x13x3[3 * i];
      tmp_1[4 + 6 * i] = NLPIDVersion2_B.Reshape9x13x3[3 * i + 1];
      tmp_1[5 + 6 * i] = NLPIDVersion2_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&NLPIDVersion2_B.MatrixConcatenate2[18]), (void *)&tmp_1[0],
           18U * sizeof(real_T));

    /* Gain: '<S166>/QTM In5 z-coord [mm]' */
    NLPIDVersion2_B.QTMIn5zcoordmm = NLPIDVersion2_P.QTMIn5zcoordmm_Gain *
      NLPIDVersion2_B.QTMIn[4];

    /* Gain: '<S166>/mm2m z' */
    NLPIDVersion2_B.mm2mz = NLPIDVersion2_P.mm2mz_Gain *
      NLPIDVersion2_B.QTMIn5zcoordmm;

    /* Derivative Block: '<S166>/Derivative' */
    {
      real_T t = NLPIDVersion2_M->Timing.t[0];
      real_T timeStampA = NLPIDVersion2_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = NLPIDVersion2_DWork.Derivative_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = NLPIDVersion2_B.Derivative;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank = &NLPIDVersion2_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        NLPIDVersion2_B.Derivative[0] = (NLPIDVersion2_B.mm2mx - *lastBank++) /
          deltaT;
        NLPIDVersion2_B.Derivative[1] = (NLPIDVersion2_B.mm2my - *lastBank++) /
          deltaT;
        NLPIDVersion2_B.Derivative[2] = (NLPIDVersion2_B.mm2mz - *lastBank++) /
          deltaT;
        NLPIDVersion2_B.Derivative[3] = (NLPIDVersion2_B.d2rroll - *lastBank++) /
          deltaT;
        NLPIDVersion2_B.Derivative[4] = (NLPIDVersion2_B.d2rpitch - *lastBank++)
          / deltaT;
        NLPIDVersion2_B.Derivative[5] = (NLPIDVersion2_B.d2ryaw - *lastBank++) /
          deltaT;
      }
    }

    /* Product: '<S166>/Product' */
    for (i = 0; i < 6; i++) {
      NLPIDVersion2_B.Product_l[i] = 0.0;
      for (tmp_6 = 0; tmp_6 < 6; tmp_6++) {
        NLPIDVersion2_B.Product_l[i] = NLPIDVersion2_B.MatrixConcatenate2[6 *
          tmp_6 + i] * NLPIDVersion2_B.Derivative[tmp_6] +
          NLPIDVersion2_B.Product_l[i];
      }
    }

    /* MultiPortSwitch: '<S167>/nu Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)NLPIDVersion2_P.ControlInputSelector_Value == 0) {
      NLPIDVersion2_B.nuSwitch[0] = NLPIDVersion2_B.Product_l[0];
      NLPIDVersion2_B.nuSwitch[1] = NLPIDVersion2_B.Product_l[1];
      NLPIDVersion2_B.nuSwitch[2] = NLPIDVersion2_B.Product_l[5];
    } else {
      NLPIDVersion2_B.nuSwitch[0] = NLPIDVersion2_B.Integrator_d[0];
      NLPIDVersion2_B.nuSwitch[1] = NLPIDVersion2_B.Integrator_d[1];
      NLPIDVersion2_B.nuSwitch[2] = NLPIDVersion2_B.Integrator_d[2];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S30>/Product2' */
      NLPIDVersion2_B.Product2[i] = 0.0;
      NLPIDVersion2_B.Product2[i] = NLPIDVersion2_B.ux3[i] *
        NLPIDVersion2_B.nuSwitch[0] + NLPIDVersion2_B.Product2[i];
      NLPIDVersion2_B.Product2[i] = NLPIDVersion2_B.ux3[i + 3] *
        NLPIDVersion2_B.nuSwitch[1] + NLPIDVersion2_B.Product2[i];
      NLPIDVersion2_B.Product2[i] = NLPIDVersion2_B.ux3[i + 6] *
        NLPIDVersion2_B.nuSwitch[2] + NLPIDVersion2_B.Product2[i];

      /* Sum: '<S30>/Sum1' */
      NLPIDVersion2_B.Sum1_f[i] = NLPIDVersion2_B.Sum3[i] -
        NLPIDVersion2_B.Product2[i];
    }

    /* Trigonometry: '<S40>/R11' */
    NLPIDVersion2_B.R11_h = cos(NLPIDVersion2_B.etaSwitch[2]);

    /* Trigonometry: '<S40>/R21' */
    NLPIDVersion2_B.R21_c = sin(NLPIDVersion2_B.etaSwitch[2]);

    /* Trigonometry: '<S40>/R12' */
    NLPIDVersion2_B.R12_p = sin(NLPIDVersion2_B.etaSwitch[2]);

    /* Gain: '<S40>/-1' */
    NLPIDVersion2_B.u = NLPIDVersion2_P.u_Gain * NLPIDVersion2_B.R12_p;

    /* Trigonometry: '<S40>/R22' */
    NLPIDVersion2_B.R22_p = cos(NLPIDVersion2_B.etaSwitch[2]);

    /* Reshape: '<S40>/R(psi)' incorporates:
     *  Constant: '<S40>/R13'
     *  Constant: '<S40>/R23'
     *  Constant: '<S40>/R31'
     *  Constant: '<S40>/R32'
     *  Constant: '<S40>/R33'
     */
    NLPIDVersion2_B.Rpsi[0] = NLPIDVersion2_B.R11_h;
    NLPIDVersion2_B.Rpsi[1] = NLPIDVersion2_B.R21_c;
    NLPIDVersion2_B.Rpsi[2] = NLPIDVersion2_P.R31_Value;
    NLPIDVersion2_B.Rpsi[3] = NLPIDVersion2_B.u;
    NLPIDVersion2_B.Rpsi[4] = NLPIDVersion2_B.R22_p;
    NLPIDVersion2_B.Rpsi[5] = NLPIDVersion2_P.R32_Value;
    NLPIDVersion2_B.Rpsi[6] = NLPIDVersion2_P.R13_Value;
    NLPIDVersion2_B.Rpsi[7] = NLPIDVersion2_P.R23_Value;
    NLPIDVersion2_B.Rpsi[8] = NLPIDVersion2_P.R33_Value;

    /* Math: '<S62>/Math Function' */
    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.MathFunction_m[3 * i] = NLPIDVersion2_B.Rpsi[i];
      NLPIDVersion2_B.MathFunction_m[1 + 3 * i] = NLPIDVersion2_B.Rpsi[i + 3];
      NLPIDVersion2_B.MathFunction_m[2 + 3 * i] = NLPIDVersion2_B.Rpsi[i + 6];
    }

    /* Saturate: '<S69>/Saturation' */
    tmp = NLPIDVersion2_B.etaSwitch[2];
    NLPIDVersion2_B.Saturation_p = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation_LowerSat_m,
      NLPIDVersion2_P.Saturation_UpperSat_f);

    /* Signum: '<S69>/Sign' */
    NLPIDVersion2_B.Sign_f = rt_SIGNd_snf(NLPIDVersion2_B.Saturation_p);

    /* Gain: '<S69>/Gain' */
    NLPIDVersion2_B.Gain_f = NLPIDVersion2_P.Gain_Gain_k *
      NLPIDVersion2_B.Sign_f;

    /* Sum: '<S69>/Sum1' */
    NLPIDVersion2_B.Sum1_b = NLPIDVersion2_B.Saturation_p +
      NLPIDVersion2_B.Gain_f;

    /* Math: '<S69>/Math Function' incorporates:
     *  Constant: '<S69>/Constant'
     */
    NLPIDVersion2_B.MathFunction_p = rt_rem_snf(NLPIDVersion2_B.Sum1_b,
      NLPIDVersion2_P.Constant_Value_l);

    /* Sum: '<S69>/Sum' */
    NLPIDVersion2_B.Sum_p = NLPIDVersion2_B.MathFunction_p -
      NLPIDVersion2_B.Gain_f;

    /* Integrator Block: '<S41>/Integrator'
     */
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &NLPIDVersion2_PrevZCSigState.Integrator_Reset_ZCE_j,
                         NLPIDVersion2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || NLPIDVersion2_P.ctrl2ResetIntegrator_Value != 0.0 ||
          NLPIDVersion2_DWork.Integrator_IWORK.IcNeedsLoading) {
        NLPIDVersion2_X.Integrator_CSTATE_p[0] = NLPIDVersion2_B.Initialq_x;
        NLPIDVersion2_X.Integrator_CSTATE_p[1] = NLPIDVersion2_B.Initialq_y;
      }

      NLPIDVersion2_DWork.Integrator_IWORK.IcNeedsLoading = 0;
    }

    NLPIDVersion2_B.Integrator_k[0] = NLPIDVersion2_X.Integrator_CSTATE_p[0];
    NLPIDVersion2_B.Integrator_k[1] = NLPIDVersion2_X.Integrator_CSTATE_p[1];

    /* SignalConversion: '<S106>/ConcatBufferAtVector ConcatenateIn1' */
    NLPIDVersion2_B.VectorConcatenate[0] = NLPIDVersion2_B.Integrator_k[0];
    NLPIDVersion2_B.VectorConcatenate[1] = NLPIDVersion2_B.Integrator_k[1];
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Sum: '<S159>/x_2 - x_1' incorporates:
       *  Constant: '<S11>/x_1 [m]'
       *  Constant: '<S11>/x_2 [m]'
       */
      NLPIDVersion2_B.x_2x_1 = NLPIDVersion2_P.x_2m_Value -
        NLPIDVersion2_P.x_1m_Value;

      /* Sum: '<S159>/y_2 - y_1' incorporates:
       *  Constant: '<S11>/y_1 [m]'
       *  Constant: '<S11>/y_2 [m]'
       */
      NLPIDVersion2_B.y_2y_1 = NLPIDVersion2_P.y_2m_Value -
        NLPIDVersion2_P.y_1m_Value;

      /* SignalConversion: '<S160>/TmpHiddenBufferAtProductInport2' */
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_b[0] =
        NLPIDVersion2_B.x_2x_1;
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_b[1] =
        NLPIDVersion2_B.y_2y_1;

      /* Saturate: '<S142>/Saturation' incorporates:
       *  Constant: '<S5>/Path Selector  [-]'
       */
      tmp = NLPIDVersion2_P.PathSelector_Value;
      NLPIDVersion2_B.Saturation_i = rt_SATURATE(tmp,
        NLPIDVersion2_P.Saturation_LowerSat_k,
        NLPIDVersion2_P.Saturation_UpperSat_j);

      /* Rounding: '<S142>/Rounding Function' */
      NLPIDVersion2_B.RoundingFunction = floor(NLPIDVersion2_B.Saturation_i);

      /* Product: '<S152>/Product' */
      NLPIDVersion2_B.Product_c[0] =
        NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_b[0] *
        NLPIDVersion2_B.RoundingFunction;
      NLPIDVersion2_B.Product_c[1] =
        NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_b[1] *
        NLPIDVersion2_B.RoundingFunction;
    }

    /* Integrator Block: '<S41>/Integrator1'
     */
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &NLPIDVersion2_PrevZCSigState.Integrator1_Reset_ZCE,
                         NLPIDVersion2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || NLPIDVersion2_P.ctrl2ResetIntegrator_Value != 0.0 ||
          NLPIDVersion2_DWork.Integrator1_IWORK.IcNeedsLoading) {
        NLPIDVersion2_X.Integrator1_CSTATE = NLPIDVersion2_B.Initials;
      }

      NLPIDVersion2_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
    }

    NLPIDVersion2_B.Integrator1 = NLPIDVersion2_X.Integrator1_CSTATE;

    /* Product: '<S145>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    NLPIDVersion2_B.Product2_i = NLPIDVersion2_B.Integrator1 *
      NLPIDVersion2_P.k_Value;

    /* Trigonometry: '<S145>/sin(s)' */
    NLPIDVersion2_B.sins = sin(NLPIDVersion2_B.Product2_i);

    /* Product: '<S145>/Product' incorporates:
     *  Constant: '<S10>/k [-]'
     *  Constant: '<S10>/r_x [m]'
     */
    NLPIDVersion2_B.Product_id = NLPIDVersion2_P.r_xm_Value *
      NLPIDVersion2_B.sins * NLPIDVersion2_P.k_Value;

    /* Gain: '<S145>/Gain' */
    NLPIDVersion2_B.Gain_k = NLPIDVersion2_P.Gain_Gain_o *
      NLPIDVersion2_B.Product_id;

    /* Trigonometry: '<S145>/cos(s)' */
    NLPIDVersion2_B.coss = cos(NLPIDVersion2_B.Product2_i);

    /* Product: '<S145>/Product1' incorporates:
     *  Constant: '<S10>/k [-]'
     *  Constant: '<S10>/r_y [m]'
     */
    NLPIDVersion2_B.Product1_p = NLPIDVersion2_P.r_ym_Value *
      NLPIDVersion2_B.coss * NLPIDVersion2_P.k_Value;

    /* SignalConversion: '<S148>/TmpHiddenBufferAtProductInport2' */
    NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_n[0] = NLPIDVersion2_B.Gain_k;
    NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_n[1] =
      NLPIDVersion2_B.Product1_p;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Sum: '<S152>/Subract' incorporates:
       *  Constant: '<S152>/Constant'
       */
      NLPIDVersion2_B.Subract = NLPIDVersion2_P.Constant_Value_g -
        NLPIDVersion2_B.RoundingFunction;
    }

    /* Product: '<S152>/Product1' */
    NLPIDVersion2_B.Product1_d[0] =
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_n[0] *
      NLPIDVersion2_B.Subract;

    /* Sum: '<S152>/Add' */
    NLPIDVersion2_B.Add[0] = NLPIDVersion2_B.Product_c[0] +
      NLPIDVersion2_B.Product1_d[0];

    /* Product: '<S152>/Product1' */
    NLPIDVersion2_B.Product1_d[1] =
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_n[1] *
      NLPIDVersion2_B.Subract;

    /* Sum: '<S152>/Add' */
    NLPIDVersion2_B.Add[1] = NLPIDVersion2_B.Product_c[1] +
      NLPIDVersion2_B.Product1_d[1];

    /* Trigonometry: '<S97>/Trigonometric Function' */
    NLPIDVersion2_B.TrigonometricFunction = rt_atan2_snf(NLPIDVersion2_B.Add[1],
      NLPIDVersion2_B.Add[0]);

    /* Saturate: '<S100>/Saturation' */
    tmp = NLPIDVersion2_B.TrigonometricFunction;
    NLPIDVersion2_B.Saturation_o = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation_LowerSat_o,
      NLPIDVersion2_P.Saturation_UpperSat_m);

    /* Signum: '<S100>/Sign' */
    NLPIDVersion2_B.Sign_c = rt_SIGNd_snf(NLPIDVersion2_B.Saturation_o);

    /* Gain: '<S100>/Gain' */
    NLPIDVersion2_B.Gain_a = NLPIDVersion2_P.Gain_Gain_p *
      NLPIDVersion2_B.Sign_c;

    /* Sum: '<S100>/Sum1' */
    NLPIDVersion2_B.Sum1_fu = NLPIDVersion2_B.Saturation_o +
      NLPIDVersion2_B.Gain_a;

    /* Math: '<S100>/Math Function' incorporates:
     *  Constant: '<S100>/Constant'
     */
    NLPIDVersion2_B.MathFunction_c = rt_rem_snf(NLPIDVersion2_B.Sum1_fu,
      NLPIDVersion2_P.Constant_Value_p);

    /* Sum: '<S100>/Sum' */
    NLPIDVersion2_B.Sum_pi = NLPIDVersion2_B.MathFunction_c -
      NLPIDVersion2_B.Gain_a;

    /* Saturate: '<S128>/Saturation' */
    tmp = NLPIDVersion2_B.Sum_pi;
    NLPIDVersion2_B.Saturation_n = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation_LowerSat_p,
      NLPIDVersion2_P.Saturation_UpperSat_h);

    /* Signum: '<S128>/Sign' */
    NLPIDVersion2_B.Sign_hb = rt_SIGNd_snf(NLPIDVersion2_B.Saturation_n);

    /* Gain: '<S128>/Gain' */
    NLPIDVersion2_B.Gain_l = NLPIDVersion2_P.Gain_Gain_b *
      NLPIDVersion2_B.Sign_hb;

    /* Sum: '<S128>/Sum1' */
    NLPIDVersion2_B.Sum1_n = NLPIDVersion2_B.Saturation_n +
      NLPIDVersion2_B.Gain_l;

    /* Math: '<S128>/Math Function' incorporates:
     *  Constant: '<S128>/Constant'
     */
    NLPIDVersion2_B.MathFunction_me = rt_rem_snf(NLPIDVersion2_B.Sum1_n,
      NLPIDVersion2_P.Constant_Value_a);

    /* Sum: '<S128>/Sum' */
    NLPIDVersion2_B.Sum_e = NLPIDVersion2_B.MathFunction_me -
      NLPIDVersion2_B.Gain_l;

    /* Outputs for atomic SubSystem: '<S105>/R_2' */

    /* Trigonometry: '<S131>/R11' */
    NLPIDVersion2_B.R11_j = cos(NLPIDVersion2_B.Sum_pi);

    /* Trigonometry: '<S131>/R21' */
    NLPIDVersion2_B.R21_f = sin(NLPIDVersion2_B.Sum_pi);

    /* Gain: '<S131>/R12' */
    NLPIDVersion2_B.R12_d = NLPIDVersion2_P.R12_Gain * NLPIDVersion2_B.R21_f;

    /* Gain: '<S131>/R22' */
    NLPIDVersion2_B.R22_j = NLPIDVersion2_P.R22_Gain * NLPIDVersion2_B.R11_j;

    /* Reshape: '<S131>/R_2(psi_d)' */
    NLPIDVersion2_B.R_2psi_d[0] = NLPIDVersion2_B.R11_j;
    NLPIDVersion2_B.R_2psi_d[1] = NLPIDVersion2_B.R21_f;
    NLPIDVersion2_B.R_2psi_d[2] = NLPIDVersion2_B.R12_d;
    NLPIDVersion2_B.R_2psi_d[3] = NLPIDVersion2_B.R22_j;

    /* end of Outputs for SubSystem: '<S105>/R_2' */

    /* Math: '<S132>/Math Function' */
    NLPIDVersion2_B.MathFunction_o[0] = NLPIDVersion2_B.R_2psi_d[0];
    NLPIDVersion2_B.MathFunction_o[1] = NLPIDVersion2_B.R_2psi_d[2];
    NLPIDVersion2_B.MathFunction_o[2] = NLPIDVersion2_B.R_2psi_d[1];
    NLPIDVersion2_B.MathFunction_o[3] = NLPIDVersion2_B.R_2psi_d[3];
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Sum: '<S158>/x_2 - x_1' incorporates:
       *  Constant: '<S11>/x_1 [m]'
       *  Constant: '<S11>/x_2 [m]'
       */
      NLPIDVersion2_B.x_2x_1_j = NLPIDVersion2_P.x_2m_Value -
        NLPIDVersion2_P.x_1m_Value;
    }

    /* Product: '<S158>/(x_2 - x_1) * s' */
    NLPIDVersion2_B.x_2x_1s = NLPIDVersion2_B.x_2x_1_j *
      NLPIDVersion2_B.Integrator1;

    /* Sum: '<S158>/(x_2 - x_1) * s + x_1' incorporates:
     *  Constant: '<S11>/x_1 [m]'
     */
    NLPIDVersion2_B.x_2x_1sx_1 = NLPIDVersion2_B.x_2x_1s +
      NLPIDVersion2_P.x_1m_Value;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Sum: '<S158>/y_2 - y_1' incorporates:
       *  Constant: '<S11>/y_1 [m]'
       *  Constant: '<S11>/y_2 [m]'
       */
      NLPIDVersion2_B.y_2y_1_j = NLPIDVersion2_P.y_2m_Value -
        NLPIDVersion2_P.y_1m_Value;
    }

    /* Product: '<S158>/(y_2 - y_1) * s' */
    NLPIDVersion2_B.y_2y_1s = NLPIDVersion2_B.y_2y_1_j *
      NLPIDVersion2_B.Integrator1;

    /* Sum: '<S158>/(y_2 - y_1) * s + y_1' incorporates:
     *  Constant: '<S11>/y_1 [m]'
     */
    NLPIDVersion2_B.y_2y_1sy_1 = NLPIDVersion2_B.y_2y_1s +
      NLPIDVersion2_P.y_1m_Value;

    /* Product: '<S151>/Product' */
    NLPIDVersion2_B.Product_b[0] = NLPIDVersion2_B.x_2x_1sx_1 *
      NLPIDVersion2_B.RoundingFunction;
    NLPIDVersion2_B.Product_b[1] = NLPIDVersion2_B.y_2y_1sy_1 *
      NLPIDVersion2_B.RoundingFunction;

    /* Product: '<S144>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    NLPIDVersion2_B.Product2_n = NLPIDVersion2_B.Integrator1 *
      NLPIDVersion2_P.k_Value;

    /* Trigonometry: '<S144>/cos(s)' */
    NLPIDVersion2_B.coss_p = cos(NLPIDVersion2_B.Product2_n);

    /* Product: '<S144>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    NLPIDVersion2_B.Product_bm = NLPIDVersion2_P.r_xm_Value *
      NLPIDVersion2_B.coss_p;

    /* Sum: '<S144>/Add' incorporates:
     *  Constant: '<S10>/x_0 [m]'
     */
    NLPIDVersion2_B.Add_p = NLPIDVersion2_B.Product_bm +
      NLPIDVersion2_P.x_0m_Value;

    /* Trigonometry: '<S144>/sin(s)' */
    NLPIDVersion2_B.sins_k = sin(NLPIDVersion2_B.Product2_n);

    /* Product: '<S144>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    NLPIDVersion2_B.Product1_e = NLPIDVersion2_P.r_ym_Value *
      NLPIDVersion2_B.sins_k;

    /* Sum: '<S144>/Add1' incorporates:
     *  Constant: '<S10>/y_0 [m]'
     */
    NLPIDVersion2_B.Add1 = NLPIDVersion2_B.Product1_e +
      NLPIDVersion2_P.y_0m_Value;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Sum: '<S151>/Subract' incorporates:
       *  Constant: '<S151>/Constant'
       */
      NLPIDVersion2_B.Subract_c = NLPIDVersion2_P.Constant_Value_j -
        NLPIDVersion2_B.RoundingFunction;
    }

    /* Product: '<S151>/Product1' */
    NLPIDVersion2_B.Product1_m[0] = NLPIDVersion2_B.Add_p *
      NLPIDVersion2_B.Subract_c;
    NLPIDVersion2_B.Product1_m[1] = NLPIDVersion2_B.Add1 *
      NLPIDVersion2_B.Subract_c;

    /* Sum: '<S151>/Add' */
    NLPIDVersion2_B.Add_n[0] = NLPIDVersion2_B.Product_b[0] +
      NLPIDVersion2_B.Product1_m[0];
    NLPIDVersion2_B.Add_n[1] = NLPIDVersion2_B.Product_b[1] +
      NLPIDVersion2_B.Product1_m[1];

    /* RelationalOperator: '<S156>/LowerRelop1' incorporates:
     *  Constant: '<S5>/x_dmax [m]'
     */
    NLPIDVersion2_B.LowerRelop1 = (NLPIDVersion2_B.Add_n[0] >
      NLPIDVersion2_P.x_dmaxm_Value);

    /* RelationalOperator: '<S156>/UpperRelop' incorporates:
     *  Constant: '<S5>/x_dmin [m]'
     */
    NLPIDVersion2_B.UpperRelop = (NLPIDVersion2_B.Add_n[0] <
      NLPIDVersion2_P.x_dminm_Value);

    /* Switch: '<S156>/Switch' incorporates:
     *  Constant: '<S5>/x_dmin [m]'
     */
    if (NLPIDVersion2_B.UpperRelop) {
      NLPIDVersion2_B.Switch = NLPIDVersion2_P.x_dminm_Value;
    } else {
      NLPIDVersion2_B.Switch = NLPIDVersion2_B.Add_n[0];
    }

    /* Switch: '<S156>/Switch2' incorporates:
     *  Constant: '<S5>/x_dmax [m]'
     */
    if (NLPIDVersion2_B.LowerRelop1) {
      NLPIDVersion2_B.Switch2 = NLPIDVersion2_P.x_dmaxm_Value;
    } else {
      NLPIDVersion2_B.Switch2 = NLPIDVersion2_B.Switch;
    }

    /* RelationalOperator: '<S157>/LowerRelop1' incorporates:
     *  Constant: '<S5>/y_dmax [m]'
     */
    NLPIDVersion2_B.LowerRelop1_a = (NLPIDVersion2_B.Add_n[1] >
      NLPIDVersion2_P.y_dmaxm_Value);

    /* RelationalOperator: '<S157>/UpperRelop' incorporates:
     *  Constant: '<S5>/y_dmin [m]'
     */
    NLPIDVersion2_B.UpperRelop_e = (NLPIDVersion2_B.Add_n[1] <
      NLPIDVersion2_P.y_dminm_Value);

    /* Switch: '<S157>/Switch' incorporates:
     *  Constant: '<S5>/y_dmin [m]'
     */
    if (NLPIDVersion2_B.UpperRelop_e) {
      NLPIDVersion2_B.Switch_e = NLPIDVersion2_P.y_dminm_Value;
    } else {
      NLPIDVersion2_B.Switch_e = NLPIDVersion2_B.Add_n[1];
    }

    /* Switch: '<S157>/Switch2' incorporates:
     *  Constant: '<S5>/y_dmax [m]'
     */
    if (NLPIDVersion2_B.LowerRelop1_a) {
      NLPIDVersion2_B.Switch2_b = NLPIDVersion2_P.y_dmaxm_Value;
    } else {
      NLPIDVersion2_B.Switch2_b = NLPIDVersion2_B.Switch_e;
    }

    /* Sum: '<S94>/Subtract' */
    NLPIDVersion2_B.Subtract[0] = NLPIDVersion2_B.Integrator_k[0] -
      NLPIDVersion2_B.Switch2;
    NLPIDVersion2_B.Subtract[1] = NLPIDVersion2_B.Integrator_k[1] -
      NLPIDVersion2_B.Switch2_b;

    /* Product: '<S105>/epsilon' */
    NLPIDVersion2_B.epsilon[0] = 0.0;
    NLPIDVersion2_B.epsilon[0] = NLPIDVersion2_B.MathFunction_o[0] *
      NLPIDVersion2_B.Subtract[0] + NLPIDVersion2_B.epsilon[0];
    NLPIDVersion2_B.epsilon[0] = NLPIDVersion2_B.MathFunction_o[2] *
      NLPIDVersion2_B.Subtract[1] + NLPIDVersion2_B.epsilon[0];
    NLPIDVersion2_B.epsilon[1] = 0.0;
    NLPIDVersion2_B.epsilon[1] = NLPIDVersion2_B.MathFunction_o[1] *
      NLPIDVersion2_B.Subtract[0] + NLPIDVersion2_B.epsilon[1];
    NLPIDVersion2_B.epsilon[1] = NLPIDVersion2_B.MathFunction_o[3] *
      NLPIDVersion2_B.Subtract[1] + NLPIDVersion2_B.epsilon[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector' */
    {
      const byte_T *u = (byte_T *)NLPIDVersion2_B.epsilon;/* input port */
      const int32_T *index = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&NLPIDVersion2_B.MultiportSelector;
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
    }                                  /* end <S105>/Multiport Selector */

    /* Trigonometry: '<S122>/Trigonometric Function' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.TrigonometricFunction_m = rt_atan2_snf
      (NLPIDVersion2_B.MultiportSelector, NLPIDVersion2_P.Deltam_Value);

    /* Saturate: '<S129>/Saturation' */
    tmp = NLPIDVersion2_B.TrigonometricFunction_m;
    NLPIDVersion2_B.Saturation_ns = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation_LowerSat_mg,
      NLPIDVersion2_P.Saturation_UpperSat_d);

    /* Signum: '<S129>/Sign' */
    NLPIDVersion2_B.Sign_cn = rt_SIGNd_snf(NLPIDVersion2_B.Saturation_ns);

    /* Gain: '<S129>/Gain' */
    NLPIDVersion2_B.Gain_h = NLPIDVersion2_P.Gain_Gain_j *
      NLPIDVersion2_B.Sign_cn;

    /* Sum: '<S129>/Sum1' */
    NLPIDVersion2_B.Sum1_n1 = NLPIDVersion2_B.Saturation_ns +
      NLPIDVersion2_B.Gain_h;

    /* Math: '<S129>/Math Function' incorporates:
     *  Constant: '<S129>/Constant'
     */
    NLPIDVersion2_B.MathFunction_c5 = rt_rem_snf(NLPIDVersion2_B.Sum1_n1,
      NLPIDVersion2_P.Constant_Value_lh);

    /* Sum: '<S129>/Sum' */
    NLPIDVersion2_B.Sum_o = NLPIDVersion2_B.MathFunction_c5 -
      NLPIDVersion2_B.Gain_h;

    /* Sum: '<S122>/Subtract' */
    NLPIDVersion2_B.Subtract_h = NLPIDVersion2_B.Sum_e - NLPIDVersion2_B.Sum_o;

    /* Saturate: '<S130>/Saturation' */
    tmp = NLPIDVersion2_B.Subtract_h;
    NLPIDVersion2_B.Saturation_a = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation_LowerSat_b,
      NLPIDVersion2_P.Saturation_UpperSat_e);

    /* Signum: '<S130>/Sign' */
    NLPIDVersion2_B.Sign_n = rt_SIGNd_snf(NLPIDVersion2_B.Saturation_a);

    /* Gain: '<S130>/Gain' */
    NLPIDVersion2_B.Gain_ai = NLPIDVersion2_P.Gain_Gain_d *
      NLPIDVersion2_B.Sign_n;

    /* Sum: '<S130>/Sum1' */
    NLPIDVersion2_B.Sum1_c = NLPIDVersion2_B.Saturation_a +
      NLPIDVersion2_B.Gain_ai;

    /* Math: '<S130>/Math Function' incorporates:
     *  Constant: '<S130>/Constant'
     */
    NLPIDVersion2_B.MathFunction_g = rt_rem_snf(NLPIDVersion2_B.Sum1_c,
      NLPIDVersion2_P.Constant_Value_ac);

    /* Sum: '<S130>/Sum' */
    NLPIDVersion2_B.Sum_d = NLPIDVersion2_B.MathFunction_g -
      NLPIDVersion2_B.Gain_ai;

    /* SignalConversion: '<S106>/ConcatBufferAtVector ConcatenateIn2' */
    NLPIDVersion2_B.VectorConcatenate[2] = NLPIDVersion2_B.Sum_d;

    /* Sum: '<S44>/Subtract' */
    NLPIDVersion2_B.Subtract_f[0] = NLPIDVersion2_B.etaSwitch[0] -
      NLPIDVersion2_B.VectorConcatenate[0];
    NLPIDVersion2_B.Subtract_f[1] = NLPIDVersion2_B.etaSwitch[1] -
      NLPIDVersion2_B.VectorConcatenate[1];
    NLPIDVersion2_B.Subtract_f[2] = NLPIDVersion2_B.Sum_p -
      NLPIDVersion2_B.VectorConcatenate[2];

    /* Saturate: '<S70>/Saturation' */
    tmp = NLPIDVersion2_B.Subtract_f[2];
    NLPIDVersion2_B.Saturation_o4 = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation_LowerSat_l,
      NLPIDVersion2_P.Saturation_UpperSat_n);

    /* Signum: '<S70>/Sign' */
    NLPIDVersion2_B.Sign_j = rt_SIGNd_snf(NLPIDVersion2_B.Saturation_o4);

    /* Gain: '<S70>/Gain' */
    NLPIDVersion2_B.Gain_ag = NLPIDVersion2_P.Gain_Gain_g *
      NLPIDVersion2_B.Sign_j;

    /* Sum: '<S70>/Sum1' */
    NLPIDVersion2_B.Sum1_d = NLPIDVersion2_B.Saturation_o4 +
      NLPIDVersion2_B.Gain_ag;

    /* Math: '<S70>/Math Function' incorporates:
     *  Constant: '<S70>/Constant'
     */
    NLPIDVersion2_B.MathFunction_j = rt_rem_snf(NLPIDVersion2_B.Sum1_d,
      NLPIDVersion2_P.Constant_Value_f);

    /* Sum: '<S70>/Sum' */
    NLPIDVersion2_B.Sum_a = NLPIDVersion2_B.MathFunction_j -
      NLPIDVersion2_B.Gain_ag;

    /* SignalConversion: '<S59>/TmpHiddenBufferAtProductInport3' */
    NLPIDVersion2_B.TmpHiddenBufferAtProductInport3[0] =
      NLPIDVersion2_B.Subtract_f[0];
    NLPIDVersion2_B.TmpHiddenBufferAtProductInport3[1] =
      NLPIDVersion2_B.Subtract_f[1];
    NLPIDVersion2_B.TmpHiddenBufferAtProductInport3[2] = NLPIDVersion2_B.Sum_a;

    /* Product: '<S59>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + NLPIDVersion2_B.ux3_g[3 *
          tmp_6] * NLPIDVersion2_B.MathFunction_m[i];
        tmp_2[i + 3 * tmp_6] = NLPIDVersion2_B.ux3_g[3 * tmp_6 + 1] *
          NLPIDVersion2_B.MathFunction_m[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = NLPIDVersion2_B.ux3_g[3 * tmp_6 + 2] *
          NLPIDVersion2_B.MathFunction_m[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.Product_k[i] = 0.0;
      NLPIDVersion2_B.Product_k[i] = tmp_2[i] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInport3[0] +
        NLPIDVersion2_B.Product_k[i];
      NLPIDVersion2_B.Product_k[i] = tmp_2[i + 3] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInport3[1] +
        NLPIDVersion2_B.Product_k[i];
      NLPIDVersion2_B.Product_k[i] = tmp_2[i + 6] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInport3[2] +
        NLPIDVersion2_B.Product_k[i];
    }

    /* Integrator Block: '<S46>/Integrator'
     */
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &NLPIDVersion2_PrevZCSigState.Integrator_Reset_ZCE_l,
                         NLPIDVersion2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || NLPIDVersion2_P.ctrl2ResetIntegrator_Value != 0.0) {
        NLPIDVersion2_X.Integrator_CSTATE_c[0] =
          NLPIDVersion2_P.Integrator_IC_g[0];
        NLPIDVersion2_X.Integrator_CSTATE_c[1] =
          NLPIDVersion2_P.Integrator_IC_g[1];
        NLPIDVersion2_X.Integrator_CSTATE_c[2] =
          NLPIDVersion2_P.Integrator_IC_g[2];
      }
    }

    NLPIDVersion2_B.Integrator_kk[0] = NLPIDVersion2_X.Integrator_CSTATE_c[0];
    NLPIDVersion2_B.Integrator_kk[1] = NLPIDVersion2_X.Integrator_CSTATE_c[1];
    NLPIDVersion2_B.Integrator_kk[2] = NLPIDVersion2_X.Integrator_CSTATE_c[2];

    /* Product: '<S59>/Product1' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] + NLPIDVersion2_B.ux3_p[3 *
          tmp_6] * NLPIDVersion2_B.MathFunction_m[i];
        tmp_2[i + 3 * tmp_6] = NLPIDVersion2_B.ux3_p[3 * tmp_6 + 1] *
          NLPIDVersion2_B.MathFunction_m[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = NLPIDVersion2_B.ux3_p[3 * tmp_6 + 2] *
          NLPIDVersion2_B.MathFunction_m[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.Product1_k[i] = 0.0;
      NLPIDVersion2_B.Product1_k[i] = tmp_2[i] * NLPIDVersion2_B.Integrator_kk[0]
        + NLPIDVersion2_B.Product1_k[i];
      NLPIDVersion2_B.Product1_k[i] = tmp_2[i + 3] *
        NLPIDVersion2_B.Integrator_kk[1] + NLPIDVersion2_B.Product1_k[i];
      NLPIDVersion2_B.Product1_k[i] = tmp_2[i + 6] *
        NLPIDVersion2_B.Integrator_kk[2] + NLPIDVersion2_B.Product1_k[i];
    }

    /* Trigonometry: '<S107>/f_qx' */
    NLPIDVersion2_B.f_qx = cos(NLPIDVersion2_B.Sum_d);

    /* Trigonometry: '<S107>/f_qy' */
    NLPIDVersion2_B.f_qy = sin(NLPIDVersion2_B.Sum_d);

    /* SignalConversion: '<S107>/TmpHiddenBufferAtProductInport1' */
    NLPIDVersion2_B.TmpHiddenBufferAtProductInport1[0] = NLPIDVersion2_B.f_qx;
    NLPIDVersion2_B.TmpHiddenBufferAtProductInport1[1] = NLPIDVersion2_B.f_qy;

    /* Product: '<S107>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    NLPIDVersion2_B.Product_kv[0] =
      NLPIDVersion2_B.TmpHiddenBufferAtProductInport1[0] *
      NLPIDVersion2_P.u_dm_Value;
    NLPIDVersion2_B.Product_kv[1] =
      NLPIDVersion2_B.TmpHiddenBufferAtProductInport1[1] *
      NLPIDVersion2_P.u_dm_Value;

    /* SignalConversion: '<S47>/ConcatBufferAtVector ConcatenateIn1' */
    NLPIDVersion2_B.VectorConcatenate_p[0] = NLPIDVersion2_B.Product_kv[0];
    NLPIDVersion2_B.VectorConcatenate_p[1] = NLPIDVersion2_B.Product_kv[1];
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S123>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = NLPIDVersion2_P.Deltam_Value;
      NLPIDVersion2_B.Delta2 = tmp * tmp;
    }

    /* Math: '<S123>/epsilon_n^2' */
    tmp = NLPIDVersion2_B.MultiportSelector;
    NLPIDVersion2_B.epsilon_n2 = tmp * tmp;

    /* Sum: '<S123>/Add' */
    NLPIDVersion2_B.Add_o = NLPIDVersion2_B.Delta2 + NLPIDVersion2_B.epsilon_n2;

    /* Product: '<S123>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Divide = NLPIDVersion2_P.Deltam_Value /
      NLPIDVersion2_B.Add_o;

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector1' */
    {
      const byte_T *u = (byte_T *)NLPIDVersion2_B.MathFunction_o;/* input port */
      const int32_T *index = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)NLPIDVersion2_B.MultiportSelector1;
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
    }                                  /* end <S105>/Multiport Selector1 */

    /* Product: '<S123>/Product' */
    NLPIDVersion2_B.Product_ch[0] = NLPIDVersion2_B.Divide *
      NLPIDVersion2_B.MultiportSelector1[0];

    /* Gain: '<S123>/-1' */
    NLPIDVersion2_B.u_o[0] = NLPIDVersion2_P.u_Gain_m *
      NLPIDVersion2_B.Product_ch[0];

    /* Product: '<S123>/Product' */
    NLPIDVersion2_B.Product_ch[1] = NLPIDVersion2_B.Divide *
      NLPIDVersion2_B.MultiportSelector1[1];

    /* Gain: '<S123>/-1' */
    NLPIDVersion2_B.u_o[1] = NLPIDVersion2_P.u_Gain_m *
      NLPIDVersion2_B.Product_ch[1];

    /* Product: '<S47>/Product' */
    tmp = NLPIDVersion2_B.u_o[0] * NLPIDVersion2_B.Product_kv[0];
    tmp += NLPIDVersion2_B.u_o[1] * NLPIDVersion2_B.Product_kv[1];
    NLPIDVersion2_B.VectorConcatenate_p[2] = tmp;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Constant: '<S53>/0_2x1' */
      NLPIDVersion2_B.VectorConcatenate_d[0] = NLPIDVersion2_P._2x1_Value[0];
      NLPIDVersion2_B.VectorConcatenate_d[1] = NLPIDVersion2_P._2x1_Value[1];

      /* Product: '<S153>/Product' incorporates:
       *  Constant: '<S143>/0_2x1'
       */
      NLPIDVersion2_B.Product_ca[0] = NLPIDVersion2_P._2x1_Value_i[0] *
        NLPIDVersion2_B.RoundingFunction;
      NLPIDVersion2_B.Product_ca[1] = NLPIDVersion2_P._2x1_Value_i[1] *
        NLPIDVersion2_B.RoundingFunction;
    }

    /* Product: '<S146>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    NLPIDVersion2_B.Product2_b = NLPIDVersion2_B.Integrator1 *
      NLPIDVersion2_P.k_Value;

    /* Trigonometry: '<S146>/cos(s)' */
    NLPIDVersion2_B.coss_f = cos(NLPIDVersion2_B.Product2_b);
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S146>/Math Function' incorporates:
       *  Constant: '<S10>/k [-]'
       */
      tmp = NLPIDVersion2_P.k_Value;
      NLPIDVersion2_B.MathFunction_mn = tmp * tmp;
    }

    /* Product: '<S146>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    NLPIDVersion2_B.Product_a = NLPIDVersion2_P.r_xm_Value *
      NLPIDVersion2_B.coss_f * NLPIDVersion2_B.MathFunction_mn;

    /* Gain: '<S146>/Gain' */
    NLPIDVersion2_B.Gain_i = NLPIDVersion2_P.Gain_Gain_pn *
      NLPIDVersion2_B.Product_a;

    /* Trigonometry: '<S146>/sin(s)' */
    NLPIDVersion2_B.sins_m = sin(NLPIDVersion2_B.Product2_b);

    /* Product: '<S146>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    NLPIDVersion2_B.Product1_o = NLPIDVersion2_P.r_ym_Value *
      NLPIDVersion2_B.sins_m * NLPIDVersion2_B.MathFunction_mn;

    /* Gain: '<S146>/Gain1' */
    NLPIDVersion2_B.Gain1_h = NLPIDVersion2_P.Gain1_Gain_h *
      NLPIDVersion2_B.Product1_o;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Sum: '<S153>/Subract' incorporates:
       *  Constant: '<S153>/Constant'
       */
      NLPIDVersion2_B.Subract_j = NLPIDVersion2_P.Constant_Value_i -
        NLPIDVersion2_B.RoundingFunction;
    }

    /* Product: '<S153>/Product1' */
    NLPIDVersion2_B.Product1_kh[0] = NLPIDVersion2_B.Gain_i *
      NLPIDVersion2_B.Subract_j;
    NLPIDVersion2_B.Product1_kh[1] = NLPIDVersion2_B.Gain1_h *
      NLPIDVersion2_B.Subract_j;

    /* Sum: '<S153>/Add' */
    NLPIDVersion2_B.Add_l[0] = NLPIDVersion2_B.Product_ca[0] +
      NLPIDVersion2_B.Product1_kh[0];
    NLPIDVersion2_B.Add_l[1] = NLPIDVersion2_B.Product_ca[1] +
      NLPIDVersion2_B.Product1_kh[1];

    /* Product: '<S98>/x_d^s * y_d^s^2' */
    NLPIDVersion2_B.x_dsy_ds2 = NLPIDVersion2_B.Add[0] * NLPIDVersion2_B.Add_l[1];

    /* Product: '<S98>/x_d^s^2 * y_d^s' */
    NLPIDVersion2_B.x_ds2y_ds = NLPIDVersion2_B.Add_l[0] * NLPIDVersion2_B.Add[1];

    /* Sum: '<S98>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
    NLPIDVersion2_B.x_dsy_ds2x_ds2y_ds = NLPIDVersion2_B.x_dsy_ds2 -
      NLPIDVersion2_B.x_ds2y_ds;

    /* Math: '<S98>/( x_d^s )^2' */
    tmp = NLPIDVersion2_B.Add[0];
    NLPIDVersion2_B.x_ds2 = tmp * tmp;

    /* Math: '<S98>/( y_d^s )^2' */
    tmp = NLPIDVersion2_B.Add[1];
    NLPIDVersion2_B.y_ds2 = tmp * tmp;

    /* Sum: '<S98>/( x_d^s )^2 + ( y_d^s )^2' */
    NLPIDVersion2_B.x_ds2y_ds2 = NLPIDVersion2_B.x_ds2 + NLPIDVersion2_B.y_ds2;

    /* Product: '<S98>/Divide' */
    NLPIDVersion2_B.Divide_l = NLPIDVersion2_B.x_dsy_ds2x_ds2y_ds /
      NLPIDVersion2_B.x_ds2y_ds2;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S126>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = NLPIDVersion2_P.Deltam_Value;
      NLPIDVersion2_B.Delta2_n = tmp * tmp;
    }

    /* Math: '<S126>/epsilon_n^2' */
    tmp = NLPIDVersion2_B.MultiportSelector;
    NLPIDVersion2_B.epsilon_n2_c = tmp * tmp;

    /* Sum: '<S126>/Add' */
    NLPIDVersion2_B.Add_m = NLPIDVersion2_B.Delta2_n +
      NLPIDVersion2_B.epsilon_n2_c;

    /* Product: '<S126>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Divide_i = NLPIDVersion2_P.Deltam_Value /
      NLPIDVersion2_B.Add_m;

    /* Outputs for atomic SubSystem: '<S105>/S_2' */

    /* Gain: '<S133>/S12' */
    NLPIDVersion2_B.S12_b = NLPIDVersion2_P.S12_Gain_c *
      NLPIDVersion2_B.Divide_l;

    /* Reshape: '<S133>/S_2(psi_d^s)' incorporates:
     *  Constant: '<S133>/0'
     */
    NLPIDVersion2_B.S_2psi_ds[0] = NLPIDVersion2_P._Value;
    NLPIDVersion2_B.S_2psi_ds[1] = NLPIDVersion2_B.Divide_l;
    NLPIDVersion2_B.S_2psi_ds[2] = NLPIDVersion2_B.S12_b;
    NLPIDVersion2_B.S_2psi_ds[3] = NLPIDVersion2_P._Value;

    /* end of Outputs for SubSystem: '<S105>/S_2' */

    /* Math: '<S136>/Math Function' */
    NLPIDVersion2_B.MathFunction_d[0] = NLPIDVersion2_B.S_2psi_ds[0];
    NLPIDVersion2_B.MathFunction_d[1] = NLPIDVersion2_B.S_2psi_ds[2];
    NLPIDVersion2_B.MathFunction_d[2] = NLPIDVersion2_B.S_2psi_ds[1];
    NLPIDVersion2_B.MathFunction_d[3] = NLPIDVersion2_B.S_2psi_ds[3];

    /* Product: '<S138>/Product' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += NLPIDVersion2_B.MathFunction_d[i] *
        NLPIDVersion2_B.MathFunction_o[0];
      tmp_3[i] += NLPIDVersion2_B.MathFunction_d[i + 2] *
        NLPIDVersion2_B.MathFunction_o[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += NLPIDVersion2_B.MathFunction_d[i] *
        NLPIDVersion2_B.MathFunction_o[2];
      tmp_3[i + 2] += NLPIDVersion2_B.MathFunction_d[i + 2] *
        NLPIDVersion2_B.MathFunction_o[3];
    }

    NLPIDVersion2_B.Product_d[0] = 0.0;
    NLPIDVersion2_B.Product_d[0] = tmp_3[0] * NLPIDVersion2_B.Subtract[0] +
      NLPIDVersion2_B.Product_d[0];
    NLPIDVersion2_B.Product_d[0] = tmp_3[2] * NLPIDVersion2_B.Subtract[1] +
      NLPIDVersion2_B.Product_d[0];

    /* Product: '<S138>/Product1' */
    NLPIDVersion2_B.Product1_h[0] = 0.0;
    NLPIDVersion2_B.Product1_h[0] = NLPIDVersion2_B.MathFunction_o[0] *
      NLPIDVersion2_B.Add[0] + NLPIDVersion2_B.Product1_h[0];
    NLPIDVersion2_B.Product1_h[0] = NLPIDVersion2_B.MathFunction_o[2] *
      NLPIDVersion2_B.Add[1] + NLPIDVersion2_B.Product1_h[0];

    /* Sum: '<S138>/Subtract1' */
    NLPIDVersion2_B.Subtract1[0] = NLPIDVersion2_B.Product_d[0] -
      NLPIDVersion2_B.Product1_h[0];
    NLPIDVersion2_B.Product_d[1] = 0.0;
    NLPIDVersion2_B.Product_d[1] = tmp_3[1] * NLPIDVersion2_B.Subtract[0] +
      NLPIDVersion2_B.Product_d[1];
    NLPIDVersion2_B.Product_d[1] = tmp_3[3] * NLPIDVersion2_B.Subtract[1] +
      NLPIDVersion2_B.Product_d[1];

    /* Product: '<S138>/Product1' */
    NLPIDVersion2_B.Product1_h[1] = 0.0;
    NLPIDVersion2_B.Product1_h[1] = NLPIDVersion2_B.MathFunction_o[1] *
      NLPIDVersion2_B.Add[0] + NLPIDVersion2_B.Product1_h[1];
    NLPIDVersion2_B.Product1_h[1] = NLPIDVersion2_B.MathFunction_o[3] *
      NLPIDVersion2_B.Add[1] + NLPIDVersion2_B.Product1_h[1];

    /* Sum: '<S138>/Subtract1' */
    NLPIDVersion2_B.Subtract1[1] = NLPIDVersion2_B.Product_d[1] -
      NLPIDVersion2_B.Product1_h[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector2' */
    {
      const byte_T *u = (byte_T *)NLPIDVersion2_B.Subtract1;/* input port */
      const int32_T *index = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&NLPIDVersion2_B.MultiportSelector2;
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
    }                                  /* end <S105>/Multiport Selector2 */

    /* Product: '<S126>/Product' */
    NLPIDVersion2_B.Product_le = NLPIDVersion2_B.Divide_i *
      NLPIDVersion2_B.MultiportSelector2;

    /* Sum: '<S126>/Subtract' */
    NLPIDVersion2_B.Subtract_b = NLPIDVersion2_B.Divide_l -
      NLPIDVersion2_B.Product_le;

    /* Math: '<S111>/epsilon_n^2' */
    tmp = NLPIDVersion2_B.MultiportSelector;
    NLPIDVersion2_B.epsilon_n2_e = tmp * tmp;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S111>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = NLPIDVersion2_P.Deltam_Value;
      NLPIDVersion2_B.Delta2_b = tmp * tmp;
    }

    /* Sum: '<S111>/Add' */
    NLPIDVersion2_B.Add_ma = NLPIDVersion2_B.epsilon_n2_e +
      NLPIDVersion2_B.Delta2_b;

    /* Math: '<S111>/sqrt' */
    tmp = NLPIDVersion2_B.Add_ma;
    if (tmp < 0.0) {
      NLPIDVersion2_B.sqrt_c = -sqrt(-tmp);
    } else {
      NLPIDVersion2_B.sqrt_c = sqrt(tmp);
    }

    /* Product: '<S111>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Divide_m = NLPIDVersion2_P.Deltam_Value /
      NLPIDVersion2_B.sqrt_c;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S161>/Math Function' */
      NLPIDVersion2_B.MathFunction_my[0] =
        NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_b[0];
      NLPIDVersion2_B.MathFunction_my[1] =
        NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_b[1];

      /* Product: '<S160>/Product' */
      tmp = NLPIDVersion2_B.MathFunction_my[0] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_b[0];
      tmp += NLPIDVersion2_B.MathFunction_my[1] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_b[1];
      NLPIDVersion2_B.Product_o = tmp;

      /* Math: '<S160>/sqrt' */
      tmp = NLPIDVersion2_B.Product_o;
      if (tmp < 0.0) {
        NLPIDVersion2_B.sqrt_d = -sqrt(-tmp);
      } else {
        NLPIDVersion2_B.sqrt_d = sqrt(tmp);
      }

      /* Product: '<S155>/Product' */
      NLPIDVersion2_B.Product_j = NLPIDVersion2_B.sqrt_d *
        NLPIDVersion2_B.RoundingFunction;
    }

    /* Math: '<S149>/Math Function' */
    NLPIDVersion2_B.MathFunction_e[0] =
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_n[0];
    NLPIDVersion2_B.MathFunction_e[1] =
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_n[1];

    /* Product: '<S148>/Product' */
    tmp = NLPIDVersion2_B.MathFunction_e[0] *
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_n[0];
    tmp += NLPIDVersion2_B.MathFunction_e[1] *
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_n[1];
    NLPIDVersion2_B.Product_j0 = tmp;

    /* Math: '<S148>/sqrt' */
    tmp = NLPIDVersion2_B.Product_j0;
    if (tmp < 0.0) {
      NLPIDVersion2_B.sqrt_b = -sqrt(-tmp);
    } else {
      NLPIDVersion2_B.sqrt_b = sqrt(tmp);
    }

    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Sum: '<S155>/Subract' incorporates:
       *  Constant: '<S155>/Constant'
       */
      NLPIDVersion2_B.Subract_m = NLPIDVersion2_P.Constant_Value_d -
        NLPIDVersion2_B.RoundingFunction;
    }

    /* Product: '<S155>/Product1' */
    NLPIDVersion2_B.Product1_a = NLPIDVersion2_B.sqrt_b *
      NLPIDVersion2_B.Subract_m;

    /* Sum: '<S155>/Add' */
    NLPIDVersion2_B.Add_pj = NLPIDVersion2_B.Product_j +
      NLPIDVersion2_B.Product1_a;

    /* Product: '<S162>/Divide' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    NLPIDVersion2_B.Divide_n = NLPIDVersion2_P.u_dm_Value /
      NLPIDVersion2_B.Add_pj;

    /* Product: '<S111>/Product' */
    NLPIDVersion2_B.Product_h = NLPIDVersion2_B.Divide_m *
      NLPIDVersion2_B.Divide_n;

    /* Math: '<S118>/Math Function' */
    NLPIDVersion2_B.MathFunction_pb[0] = NLPIDVersion2_B.Add[0];

    /* Product: '<S115>/Divide' */
    NLPIDVersion2_B.Divide_f[0] = NLPIDVersion2_B.MathFunction_pb[0] /
      NLPIDVersion2_B.Add_pj;

    /* Math: '<S118>/Math Function' */
    NLPIDVersion2_B.MathFunction_pb[1] = NLPIDVersion2_B.Add[1];

    /* Product: '<S115>/Divide' */
    NLPIDVersion2_B.Divide_f[1] = NLPIDVersion2_B.MathFunction_pb[1] /
      NLPIDVersion2_B.Add_pj;

    /* Product: '<S115>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    tmp = NLPIDVersion2_P.my_Value * NLPIDVersion2_B.Divide_f[0] *
      NLPIDVersion2_B.Subtract[0];
    tmp += NLPIDVersion2_P.my_Value * NLPIDVersion2_B.Divide_f[1] *
      NLPIDVersion2_B.Subtract[1];
    NLPIDVersion2_B.Product_ar = tmp;

    /* Gain: '<S115>/Gain' */
    NLPIDVersion2_B.Gain_hz = NLPIDVersion2_P.Gain_Gain_e *
      NLPIDVersion2_B.Product_ar;

    /* Sum: '<S111>/Subtract' */
    NLPIDVersion2_B.Subtract_a = NLPIDVersion2_B.Product_h -
      NLPIDVersion2_B.Gain_hz;

    /* Product: '<S53>/Product' */
    NLPIDVersion2_B.VectorConcatenate_d[2] = NLPIDVersion2_B.Subtract_b *
      NLPIDVersion2_B.Subtract_a;

    /* Sum: '<S45>/Add' */
    NLPIDVersion2_B.Add_lh[0] = NLPIDVersion2_B.VectorConcatenate_p[0] +
      NLPIDVersion2_B.VectorConcatenate_d[0];
    NLPIDVersion2_B.Add_lh[1] = NLPIDVersion2_B.VectorConcatenate_p[1] +
      NLPIDVersion2_B.VectorConcatenate_d[1];
    NLPIDVersion2_B.Add_lh[2] = NLPIDVersion2_B.VectorConcatenate_p[2] +
      NLPIDVersion2_B.VectorConcatenate_d[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S43>/Product' */
      NLPIDVersion2_B.Product_dv[i] = 0.0;
      NLPIDVersion2_B.Product_dv[i] = NLPIDVersion2_B.MathFunction_m[i] *
        NLPIDVersion2_B.Add_lh[0] + NLPIDVersion2_B.Product_dv[i];
      NLPIDVersion2_B.Product_dv[i] = NLPIDVersion2_B.MathFunction_m[i + 3] *
        NLPIDVersion2_B.Add_lh[1] + NLPIDVersion2_B.Product_dv[i];
      NLPIDVersion2_B.Product_dv[i] = NLPIDVersion2_B.MathFunction_m[i + 6] *
        NLPIDVersion2_B.Add_lh[2] + NLPIDVersion2_B.Product_dv[i];

      /* Sum: '<S43>/Subtract' */
      NLPIDVersion2_B.Subtract_e[i] = NLPIDVersion2_B.nuSwitch[i] -
        NLPIDVersion2_B.Product_dv[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S59>/Product2' */
      NLPIDVersion2_B.Product2_ie[i] = 0.0;
      NLPIDVersion2_B.Product2_ie[i] = NLPIDVersion2_B.ux3_ip[i] *
        NLPIDVersion2_B.Subtract_e[0] + NLPIDVersion2_B.Product2_ie[i];
      NLPIDVersion2_B.Product2_ie[i] = NLPIDVersion2_B.ux3_ip[i + 3] *
        NLPIDVersion2_B.Subtract_e[1] + NLPIDVersion2_B.Product2_ie[i];
      NLPIDVersion2_B.Product2_ie[i] = NLPIDVersion2_B.ux3_ip[i + 6] *
        NLPIDVersion2_B.Subtract_e[2] + NLPIDVersion2_B.Product2_ie[i];

      /* Sum: '<S59>/Sum' */
      NLPIDVersion2_B.Sum_j[i] = ((0.0 - NLPIDVersion2_B.Product_k[i]) -
        NLPIDVersion2_B.Product1_k[i]) - NLPIDVersion2_B.Product2_ie[i];

      /* Product: '<S58>/Product1' */
      NLPIDVersion2_B.Product1_al[i] = 0.0;
      NLPIDVersion2_B.Product1_al[i] = NLPIDVersion2_B.LinearDampningmatrix[i] *
        NLPIDVersion2_B.nuSwitch[0] + NLPIDVersion2_B.Product1_al[i];
      NLPIDVersion2_B.Product1_al[i] = NLPIDVersion2_B.LinearDampningmatrix[i +
        3] * NLPIDVersion2_B.nuSwitch[1] + NLPIDVersion2_B.Product1_al[i];
      NLPIDVersion2_B.Product1_al[i] = NLPIDVersion2_B.LinearDampningmatrix[i +
        6] * NLPIDVersion2_B.nuSwitch[2] + NLPIDVersion2_B.Product1_al[i];
    }

    /* Trigonometry: '<S108>/Trigonometric Function1' */
    NLPIDVersion2_B.TrigonometricFunction1 = sin(NLPIDVersion2_B.Sum_d);

    /* Gain: '<S108>/Gain' */
    NLPIDVersion2_B.Gain_e = NLPIDVersion2_P.Gain_Gain_f *
      NLPIDVersion2_B.TrigonometricFunction1;

    /* Trigonometry: '<S108>/Trigonometric Function' */
    NLPIDVersion2_B.TrigonometricFunction_l = cos(NLPIDVersion2_B.Sum_d);

    /* Product: '<S108>/Product1' */
    NLPIDVersion2_B.Product1_du[0] = NLPIDVersion2_B.Gain_e *
      NLPIDVersion2_B.u_o[0];

    /* Product: '<S108>/Product2' */
    NLPIDVersion2_B.Product2_j[0] = NLPIDVersion2_B.TrigonometricFunction_l *
      NLPIDVersion2_B.u_o[0];

    /* Product: '<S108>/Product1' */
    NLPIDVersion2_B.Product1_du[1] = NLPIDVersion2_B.Gain_e *
      NLPIDVersion2_B.u_o[1];

    /* Product: '<S108>/Product2' */
    NLPIDVersion2_B.Product2_j[1] = NLPIDVersion2_B.TrigonometricFunction_l *
      NLPIDVersion2_B.u_o[1];

    /* Concatenate: '<S108>/Matrix Concatenate' */
    NLPIDVersion2_B.MatrixConcatenate[0] = NLPIDVersion2_B.Product1_du[0];
    NLPIDVersion2_B.MatrixConcatenate[2] = NLPIDVersion2_B.Product1_du[1];
    NLPIDVersion2_B.MatrixConcatenate[1] = NLPIDVersion2_B.Product2_j[0];
    NLPIDVersion2_B.MatrixConcatenate[3] = NLPIDVersion2_B.Product2_j[1];

    /* Product: '<S108>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    NLPIDVersion2_B.Product_aw[0] = NLPIDVersion2_B.MatrixConcatenate[0] *
      NLPIDVersion2_P.u_dm_Value;
    NLPIDVersion2_B.Product_aw[1] = NLPIDVersion2_B.MatrixConcatenate[1] *
      NLPIDVersion2_P.u_dm_Value;
    NLPIDVersion2_B.Product_aw[2] = NLPIDVersion2_B.MatrixConcatenate[2] *
      NLPIDVersion2_P.u_dm_Value;
    NLPIDVersion2_B.Product_aw[3] = NLPIDVersion2_B.MatrixConcatenate[3] *
      NLPIDVersion2_P.u_dm_Value;

    /* Product: '<S124>/Product2' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product2_l = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.MultiportSelector;

    /* Math: '<S51>/Math Function' */
    NLPIDVersion2_B.MathFunction_k[0] = NLPIDVersion2_B.Product_kv[0];

    /* Math: '<S124>/Math Function' */
    NLPIDVersion2_B.MathFunction_h[0] = NLPIDVersion2_B.MultiportSelector1[0];

    /* Math: '<S51>/Math Function' */
    NLPIDVersion2_B.MathFunction_k[1] = NLPIDVersion2_B.Product_kv[1];

    /* Math: '<S124>/Math Function' */
    NLPIDVersion2_B.MathFunction_h[1] = NLPIDVersion2_B.MultiportSelector1[1];

    /* Product: '<S124>/Product3' */
    NLPIDVersion2_B.Product3[0] = 0.0;
    NLPIDVersion2_B.Product3[0] = NLPIDVersion2_B.MathFunction_h[0] *
      NLPIDVersion2_B.MultiportSelector1[0] + NLPIDVersion2_B.Product3[0];
    NLPIDVersion2_B.Product3[2] = 0.0;
    NLPIDVersion2_B.Product3[2] = NLPIDVersion2_B.MathFunction_h[0] *
      NLPIDVersion2_B.MultiportSelector1[1] + NLPIDVersion2_B.Product3[2];
    NLPIDVersion2_B.Product3[1] = 0.0;
    NLPIDVersion2_B.Product3[1] = NLPIDVersion2_B.MathFunction_h[1] *
      NLPIDVersion2_B.MultiportSelector1[0] + NLPIDVersion2_B.Product3[1];
    NLPIDVersion2_B.Product3[3] = 0.0;
    NLPIDVersion2_B.Product3[3] = NLPIDVersion2_B.MathFunction_h[1] *
      NLPIDVersion2_B.MultiportSelector1[1] + NLPIDVersion2_B.Product3[3];

    /* Product: '<S124>/Product4' */
    NLPIDVersion2_B.Product4[0] = NLPIDVersion2_B.Product2_l *
      NLPIDVersion2_B.Product3[0];

    /* Gain: '<S124>/2' */
    NLPIDVersion2_B.u_m[0] = NLPIDVersion2_P._Gain * NLPIDVersion2_B.Product4[0];

    /* Product: '<S124>/Product4' */
    NLPIDVersion2_B.Product4[1] = NLPIDVersion2_B.Product2_l *
      NLPIDVersion2_B.Product3[1];

    /* Gain: '<S124>/2' */
    NLPIDVersion2_B.u_m[1] = NLPIDVersion2_P._Gain * NLPIDVersion2_B.Product4[1];

    /* Product: '<S124>/Product4' */
    NLPIDVersion2_B.Product4[2] = NLPIDVersion2_B.Product2_l *
      NLPIDVersion2_B.Product3[2];

    /* Gain: '<S124>/2' */
    NLPIDVersion2_B.u_m[2] = NLPIDVersion2_P._Gain * NLPIDVersion2_B.Product4[2];

    /* Product: '<S124>/Product4' */
    NLPIDVersion2_B.Product4[3] = NLPIDVersion2_B.Product2_l *
      NLPIDVersion2_B.Product3[3];

    /* Gain: '<S124>/2' */
    NLPIDVersion2_B.u_m[3] = NLPIDVersion2_P._Gain * NLPIDVersion2_B.Product4[3];
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S124>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = NLPIDVersion2_P.Deltam_Value;
      NLPIDVersion2_B.Delta2_g = tmp * tmp;
    }

    /* Math: '<S124>/epsilon_n^2' */
    tmp = NLPIDVersion2_B.MultiportSelector;
    NLPIDVersion2_B.epsilon_n2_i = tmp * tmp;

    /* Sum: '<S124>/Add' */
    NLPIDVersion2_B.Add_i = NLPIDVersion2_B.Delta2_g +
      NLPIDVersion2_B.epsilon_n2_i;

    /* Math: '<S124>/( )^2' */
    tmp = NLPIDVersion2_B.Add_i;
    NLPIDVersion2_B.u_n = tmp * tmp;

    /* Product: '<S124>/Divide' */
    NLPIDVersion2_B.Divide_k[0] = NLPIDVersion2_B.u_m[0] / NLPIDVersion2_B.u_n;
    NLPIDVersion2_B.Divide_k[1] = NLPIDVersion2_B.u_m[1] / NLPIDVersion2_B.u_n;
    NLPIDVersion2_B.Divide_k[2] = NLPIDVersion2_B.u_m[2] / NLPIDVersion2_B.u_n;
    NLPIDVersion2_B.Divide_k[3] = NLPIDVersion2_B.u_m[3] / NLPIDVersion2_B.u_n;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Product: '<S124>/Product1' incorporates:
       *  Constant: '<S105>/0_2x2'
       *  Constant: '<S5>/Delta [m]'
       */
      NLPIDVersion2_B.Product1_i[0] = NLPIDVersion2_P.Deltam_Value *
        NLPIDVersion2_P._2x2_Value[0];
      NLPIDVersion2_B.Product1_i[1] = NLPIDVersion2_P.Deltam_Value *
        NLPIDVersion2_P._2x2_Value[1];
      NLPIDVersion2_B.Product1_i[2] = NLPIDVersion2_P.Deltam_Value *
        NLPIDVersion2_P._2x2_Value[2];
      NLPIDVersion2_B.Product1_i[3] = NLPIDVersion2_P.Deltam_Value *
        NLPIDVersion2_P._2x2_Value[3];
    }

    /* Product: '<S124>/Divide1' */
    NLPIDVersion2_B.Divide1[0] = NLPIDVersion2_B.Product1_i[0] /
      NLPIDVersion2_B.Add_i;

    /* Sum: '<S124>/Subtract' */
    NLPIDVersion2_B.Subtract_m[0] = NLPIDVersion2_B.Divide_k[0] -
      NLPIDVersion2_B.Divide1[0];

    /* Product: '<S124>/Divide1' */
    NLPIDVersion2_B.Divide1[1] = NLPIDVersion2_B.Product1_i[1] /
      NLPIDVersion2_B.Add_i;

    /* Sum: '<S124>/Subtract' */
    NLPIDVersion2_B.Subtract_m[1] = NLPIDVersion2_B.Divide_k[1] -
      NLPIDVersion2_B.Divide1[1];

    /* Product: '<S124>/Divide1' */
    NLPIDVersion2_B.Divide1[2] = NLPIDVersion2_B.Product1_i[2] /
      NLPIDVersion2_B.Add_i;

    /* Sum: '<S124>/Subtract' */
    NLPIDVersion2_B.Subtract_m[2] = NLPIDVersion2_B.Divide_k[2] -
      NLPIDVersion2_B.Divide1[2];

    /* Product: '<S124>/Divide1' */
    NLPIDVersion2_B.Divide1[3] = NLPIDVersion2_B.Product1_i[3] /
      NLPIDVersion2_B.Add_i;

    /* Sum: '<S124>/Subtract' */
    NLPIDVersion2_B.Subtract_m[3] = NLPIDVersion2_B.Divide_k[3] -
      NLPIDVersion2_B.Divide1[3];

    /* Math: '<S52>/Math Function' */
    NLPIDVersion2_B.MathFunction_av[0] = NLPIDVersion2_B.Subtract_m[0];
    NLPIDVersion2_B.MathFunction_av[1] = NLPIDVersion2_B.Subtract_m[2];
    NLPIDVersion2_B.MathFunction_av[2] = NLPIDVersion2_B.Subtract_m[1];
    NLPIDVersion2_B.MathFunction_av[3] = NLPIDVersion2_B.Subtract_m[3];

    /* Product: '<S48>/Product' */
    NLPIDVersion2_B.Product_hb[0] = 0.0;
    NLPIDVersion2_B.Product_hb[0] = NLPIDVersion2_B.MathFunction_k[0] *
      NLPIDVersion2_B.MathFunction_av[0] + NLPIDVersion2_B.Product_hb[0];
    NLPIDVersion2_B.Product_hb[0] = NLPIDVersion2_B.MathFunction_k[1] *
      NLPIDVersion2_B.MathFunction_av[1] + NLPIDVersion2_B.Product_hb[0];

    /* Product: '<S48>/Product1' */
    NLPIDVersion2_B.Product1_mc[0] = 0.0;
    NLPIDVersion2_B.Product1_mc[0] = NLPIDVersion2_B.u_o[0] *
      NLPIDVersion2_B.Product_aw[0] + NLPIDVersion2_B.Product1_mc[0];
    NLPIDVersion2_B.Product1_mc[0] = NLPIDVersion2_B.u_o[1] *
      NLPIDVersion2_B.Product_aw[1] + NLPIDVersion2_B.Product1_mc[0];

    /* Sum: '<S48>/Add' */
    NLPIDVersion2_B.Add_d[0] = NLPIDVersion2_B.Product_hb[0] +
      NLPIDVersion2_B.Product1_mc[0];

    /* Product: '<S48>/Product' */
    NLPIDVersion2_B.Product_hb[1] = 0.0;
    NLPIDVersion2_B.Product_hb[1] = NLPIDVersion2_B.MathFunction_k[0] *
      NLPIDVersion2_B.MathFunction_av[2] + NLPIDVersion2_B.Product_hb[1];
    NLPIDVersion2_B.Product_hb[1] = NLPIDVersion2_B.MathFunction_k[1] *
      NLPIDVersion2_B.MathFunction_av[3] + NLPIDVersion2_B.Product_hb[1];

    /* Product: '<S48>/Product1' */
    NLPIDVersion2_B.Product1_mc[1] = 0.0;
    NLPIDVersion2_B.Product1_mc[1] = NLPIDVersion2_B.u_o[0] *
      NLPIDVersion2_B.Product_aw[2] + NLPIDVersion2_B.Product1_mc[1];
    NLPIDVersion2_B.Product1_mc[1] = NLPIDVersion2_B.u_o[1] *
      NLPIDVersion2_B.Product_aw[3] + NLPIDVersion2_B.Product1_mc[1];

    /* Sum: '<S48>/Add' */
    NLPIDVersion2_B.Add_d[1] = NLPIDVersion2_B.Product_hb[1] +
      NLPIDVersion2_B.Product1_mc[1];

    /* Concatenate: '<S48>/Matrix Concatenate' */
    NLPIDVersion2_B.MatrixConcatenate_j[0] = NLPIDVersion2_B.Product_aw[0];
    NLPIDVersion2_B.MatrixConcatenate_j[1] = NLPIDVersion2_B.Product_aw[1];
    NLPIDVersion2_B.MatrixConcatenate_j[3] = NLPIDVersion2_B.Product_aw[2];
    NLPIDVersion2_B.MatrixConcatenate_j[4] = NLPIDVersion2_B.Product_aw[3];
    NLPIDVersion2_B.MatrixConcatenate_j[2] = NLPIDVersion2_B.Add_d[0];
    NLPIDVersion2_B.MatrixConcatenate_j[5] = NLPIDVersion2_B.Add_d[1];

    /* Product: '<S125>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product_f[0] = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.MultiportSelector * NLPIDVersion2_B.MultiportSelector2 *
      NLPIDVersion2_B.MultiportSelector1[0];

    /* Gain: '<S125>/2' */
    NLPIDVersion2_B.u_e[0] = NLPIDVersion2_P._Gain_m *
      NLPIDVersion2_B.Product_f[0];

    /* Product: '<S125>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product_f[1] = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.MultiportSelector * NLPIDVersion2_B.MultiportSelector2 *
      NLPIDVersion2_B.MultiportSelector1[1];

    /* Gain: '<S125>/2' */
    NLPIDVersion2_B.u_e[1] = NLPIDVersion2_P._Gain_m *
      NLPIDVersion2_B.Product_f[1];
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S125>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = NLPIDVersion2_P.Deltam_Value;
      NLPIDVersion2_B.Delta2_o = tmp * tmp;
    }

    /* Math: '<S125>/epsilon_n^2' */
    tmp = NLPIDVersion2_B.MultiportSelector;
    NLPIDVersion2_B.epsilon_n2_ia = tmp * tmp;

    /* Sum: '<S125>/Add' */
    NLPIDVersion2_B.Add_ox = NLPIDVersion2_B.Delta2_o +
      NLPIDVersion2_B.epsilon_n2_ia;

    /* Math: '<S125>/( )^2' */
    tmp = NLPIDVersion2_B.Add_ox;
    NLPIDVersion2_B.u_og = tmp * tmp;

    /* Product: '<S125>/Divide' */
    NLPIDVersion2_B.Divide_e[0] = NLPIDVersion2_B.u_e[0] / NLPIDVersion2_B.u_og;
    NLPIDVersion2_B.Divide_e[1] = NLPIDVersion2_B.u_e[1] / NLPIDVersion2_B.u_og;

    /* Product: '<S137>/Product1' */
    for (i = 0; i < 2; i++) {
      NLPIDVersion2_B.Product1_ez[i] = 0.0;
      NLPIDVersion2_B.Product1_ez[i] = NLPIDVersion2_B.MathFunction_d[i] *
        NLPIDVersion2_B.MathFunction_o[0] + NLPIDVersion2_B.Product1_ez[i];
      NLPIDVersion2_B.Product1_ez[i] = NLPIDVersion2_B.MathFunction_d[i + 2] *
        NLPIDVersion2_B.MathFunction_o[1] + NLPIDVersion2_B.Product1_ez[i];
      NLPIDVersion2_B.Product1_ez[i + 2] = 0.0;
      NLPIDVersion2_B.Product1_ez[i + 2] = NLPIDVersion2_B.Product1_ez[i + 2] +
        NLPIDVersion2_B.MathFunction_d[i] * NLPIDVersion2_B.MathFunction_o[2];
      NLPIDVersion2_B.Product1_ez[i + 2] = NLPIDVersion2_B.MathFunction_d[i + 2]
        * NLPIDVersion2_B.MathFunction_o[3] + NLPIDVersion2_B.Product1_ez[i + 2];
    }

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector3' */
    {
      const byte_T *u = (byte_T *)NLPIDVersion2_B.Product1_ez;/* input port */
      const int32_T *index = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)NLPIDVersion2_B.MultiportSelector3;
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
    }                                  /* end <S105>/Multiport Selector3 */

    /* Product: '<S125>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product1_ka[0] = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.MultiportSelector3[0];

    /* Product: '<S125>/Divide1' */
    NLPIDVersion2_B.Divide1_a[0] = NLPIDVersion2_B.Product1_ka[0] /
      NLPIDVersion2_B.Add_ox;

    /* Sum: '<S125>/Subtract' */
    NLPIDVersion2_B.Subtract_n[0] = NLPIDVersion2_B.Divide_e[0] -
      NLPIDVersion2_B.Divide1_a[0];

    /* Product: '<S54>/Product' */
    NLPIDVersion2_B.Product_b4[0] = NLPIDVersion2_B.Subtract_n[0] *
      NLPIDVersion2_B.Subtract_a;

    /* Product: '<S112>/Product1' */
    NLPIDVersion2_B.Product1_ex[0] = NLPIDVersion2_B.MultiportSelector *
      NLPIDVersion2_B.MultiportSelector1[0];

    /* Product: '<S125>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product1_ka[1] = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.MultiportSelector3[1];

    /* Product: '<S125>/Divide1' */
    NLPIDVersion2_B.Divide1_a[1] = NLPIDVersion2_B.Product1_ka[1] /
      NLPIDVersion2_B.Add_ox;

    /* Sum: '<S125>/Subtract' */
    NLPIDVersion2_B.Subtract_n[1] = NLPIDVersion2_B.Divide_e[1] -
      NLPIDVersion2_B.Divide1_a[1];

    /* Product: '<S54>/Product' */
    NLPIDVersion2_B.Product_b4[1] = NLPIDVersion2_B.Subtract_n[1] *
      NLPIDVersion2_B.Subtract_a;

    /* Product: '<S112>/Product1' */
    NLPIDVersion2_B.Product1_ex[1] = NLPIDVersion2_B.MultiportSelector *
      NLPIDVersion2_B.MultiportSelector1[1];

    /* Math: '<S112>/epsilon_n^2' */
    tmp = NLPIDVersion2_B.MultiportSelector;
    NLPIDVersion2_B.epsilon_n2_iw = tmp * tmp;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S112>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = NLPIDVersion2_P.Deltam_Value;
      NLPIDVersion2_B.Delta2_nh = tmp * tmp;
    }

    /* Sum: '<S112>/Add' */
    NLPIDVersion2_B.Add_li = NLPIDVersion2_B.epsilon_n2_iw +
      NLPIDVersion2_B.Delta2_nh;

    /* Math: '<S112>/^3//2' incorporates:
     *  Constant: '<S112>/3//2'
     */
    if ((NLPIDVersion2_B.Add_li < 0.0) && (NLPIDVersion2_P.u_Value_h4 > floor
         (NLPIDVersion2_P.u_Value_h4))) {
      NLPIDVersion2_B.u2 = -rt_pow_snf(-NLPIDVersion2_B.Add_li,
        NLPIDVersion2_P.u_Value_h4);
    } else {
      NLPIDVersion2_B.u2 = rt_pow_snf(NLPIDVersion2_B.Add_li,
        NLPIDVersion2_P.u_Value_h4);
    }

    /* Product: '<S112>/Divide' */
    NLPIDVersion2_B.Divide_b[0] = NLPIDVersion2_B.Product1_ex[0] /
      NLPIDVersion2_B.u2;

    /* Product: '<S112>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product_cm[0] = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.Divide_b[0] * NLPIDVersion2_B.Divide_n;

    /* Math: '<S119>/Math Function' */
    NLPIDVersion2_B.MathFunction_pj[0] = NLPIDVersion2_B.Add[0];

    /* Product: '<S116>/Divide' */
    NLPIDVersion2_B.Divide_a[0] = NLPIDVersion2_B.MathFunction_pj[0] /
      NLPIDVersion2_B.Add_pj;

    /* Product: '<S116>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    NLPIDVersion2_B.Product_la[0] = NLPIDVersion2_P.my_Value *
      NLPIDVersion2_B.Divide_a[0];

    /* Gain: '<S116>/Gain' */
    NLPIDVersion2_B.Gain_p[0] = NLPIDVersion2_P.Gain_Gain_c *
      NLPIDVersion2_B.Product_la[0];

    /* Sum: '<S112>/Sum' */
    NLPIDVersion2_B.Sum_f[0] = (0.0 - NLPIDVersion2_B.Product_cm[0]) -
      NLPIDVersion2_B.Gain_p[0];

    /* Product: '<S54>/Product1' */
    NLPIDVersion2_B.Product1_b[0] = NLPIDVersion2_B.Subtract_b *
      NLPIDVersion2_B.Sum_f[0];

    /* Sum: '<S54>/Add' */
    NLPIDVersion2_B.Add_mt[0] = NLPIDVersion2_B.Product_b4[0] +
      NLPIDVersion2_B.Product1_b[0];

    /* Product: '<S112>/Divide' */
    NLPIDVersion2_B.Divide_b[1] = NLPIDVersion2_B.Product1_ex[1] /
      NLPIDVersion2_B.u2;

    /* Product: '<S112>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product_cm[1] = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.Divide_b[1] * NLPIDVersion2_B.Divide_n;

    /* Math: '<S119>/Math Function' */
    NLPIDVersion2_B.MathFunction_pj[1] = NLPIDVersion2_B.Add[1];

    /* Product: '<S116>/Divide' */
    NLPIDVersion2_B.Divide_a[1] = NLPIDVersion2_B.MathFunction_pj[1] /
      NLPIDVersion2_B.Add_pj;

    /* Product: '<S116>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    NLPIDVersion2_B.Product_la[1] = NLPIDVersion2_P.my_Value *
      NLPIDVersion2_B.Divide_a[1];

    /* Gain: '<S116>/Gain' */
    NLPIDVersion2_B.Gain_p[1] = NLPIDVersion2_P.Gain_Gain_c *
      NLPIDVersion2_B.Product_la[1];

    /* Sum: '<S112>/Sum' */
    NLPIDVersion2_B.Sum_f[1] = (0.0 - NLPIDVersion2_B.Product_cm[1]) -
      NLPIDVersion2_B.Gain_p[1];

    /* Product: '<S54>/Product1' */
    NLPIDVersion2_B.Product1_b[1] = NLPIDVersion2_B.Subtract_b *
      NLPIDVersion2_B.Sum_f[1];

    /* Sum: '<S54>/Add' */
    NLPIDVersion2_B.Add_mt[1] = NLPIDVersion2_B.Product_b4[1] +
      NLPIDVersion2_B.Product1_b[1];

    /* Concatenate: '<S54>/Matrix Concatenate' incorporates:
     *  Constant: '<S54>/0_2x2'
     */
    NLPIDVersion2_B.MatrixConcatenate_k[0] = NLPIDVersion2_P._2x2_Value_m[0];
    NLPIDVersion2_B.MatrixConcatenate_k[1] = NLPIDVersion2_P._2x2_Value_m[1];
    NLPIDVersion2_B.MatrixConcatenate_k[3] = NLPIDVersion2_P._2x2_Value_m[2];
    NLPIDVersion2_B.MatrixConcatenate_k[4] = NLPIDVersion2_P._2x2_Value_m[3];
    NLPIDVersion2_B.MatrixConcatenate_k[2] = NLPIDVersion2_B.Add_mt[0];
    NLPIDVersion2_B.MatrixConcatenate_k[5] = NLPIDVersion2_B.Add_mt[1];

    /* Sum: '<S64>/Add' */
    for (i = 0; i < 6; i++) {
      NLPIDVersion2_B.Add_g[i] = NLPIDVersion2_B.MatrixConcatenate_j[i] +
        NLPIDVersion2_B.MatrixConcatenate_k[i];
    }

    /* Integrator Block: '<S41>/Integrator2'
     */
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &NLPIDVersion2_PrevZCSigState.Integrator2_Reset_ZCE,
                         NLPIDVersion2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || NLPIDVersion2_P.ctrl2ResetIntegrator_Value != 0.0) {
        NLPIDVersion2_X.Integrator2_CSTATE[0] = NLPIDVersion2_P.Integrator2_IC;
        NLPIDVersion2_X.Integrator2_CSTATE[1] = NLPIDVersion2_P.Integrator2_IC;
      }
    }

    NLPIDVersion2_B.Integrator2[0] = NLPIDVersion2_X.Integrator2_CSTATE[0];
    NLPIDVersion2_B.Integrator2[1] = NLPIDVersion2_X.Integrator2_CSTATE[1];

    /* Sum: '<S41>/Add1' */
    NLPIDVersion2_B.Add1_f[0] = NLPIDVersion2_B.Integrator2[0] +
      NLPIDVersion2_B.Product_kv[0];
    NLPIDVersion2_B.Add1_f[1] = NLPIDVersion2_B.Integrator2[1] +
      NLPIDVersion2_B.Product_kv[1];

    /* Product: '<S42>/Product' */
    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.Product_ju[i] = 0.0;
      NLPIDVersion2_B.Product_ju[i] = NLPIDVersion2_B.Add_g[i] *
        NLPIDVersion2_B.Add1_f[0] + NLPIDVersion2_B.Product_ju[i];
      NLPIDVersion2_B.Product_ju[i] = NLPIDVersion2_B.Add_g[i + 3] *
        NLPIDVersion2_B.Add1_f[1] + NLPIDVersion2_B.Product_ju[i];
    }

    /* Trigonometry: '<S109>/Trigonometric Function1' */
    NLPIDVersion2_B.TrigonometricFunction1_j = sin(NLPIDVersion2_B.Sum_d);

    /* Gain: '<S109>/Gain' */
    NLPIDVersion2_B.Gain_j = NLPIDVersion2_P.Gain_Gain_c4 *
      NLPIDVersion2_B.TrigonometricFunction1_j;

    /* Product: '<S109>/Product1' */
    NLPIDVersion2_B.Product1_ak = NLPIDVersion2_B.Gain_j *
      NLPIDVersion2_B.Subtract_b;

    /* Trigonometry: '<S109>/Trigonometric Function' */
    NLPIDVersion2_B.TrigonometricFunction_n = cos(NLPIDVersion2_B.Sum_d);

    /* Product: '<S109>/Product2' */
    NLPIDVersion2_B.Product2_bn = NLPIDVersion2_B.TrigonometricFunction_n *
      NLPIDVersion2_B.Subtract_b;

    /* SignalConversion: '<S109>/TmpHiddenBufferAtProductInport1' */
    NLPIDVersion2_B.TmpHiddenBufferAtProductInpo_ep[0] =
      NLPIDVersion2_B.Product1_ak;
    NLPIDVersion2_B.TmpHiddenBufferAtProductInpo_ep[1] =
      NLPIDVersion2_B.Product2_bn;

    /* Product: '<S109>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    NLPIDVersion2_B.Product_an[0] =
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpo_ep[0] *
      NLPIDVersion2_P.u_dm_Value;
    NLPIDVersion2_B.Product_an[1] =
      NLPIDVersion2_B.TmpHiddenBufferAtProductInpo_ep[1] *
      NLPIDVersion2_P.u_dm_Value;

    /* SignalConversion: '<S49>/ConcatBufferAtVector ConcatenateIn1' */
    NLPIDVersion2_B.VectorConcatenate_c[0] = NLPIDVersion2_B.Product_an[0];
    NLPIDVersion2_B.VectorConcatenate_c[1] = NLPIDVersion2_B.Product_an[1];

    /* Product: '<S49>/Product' */
    tmp = NLPIDVersion2_B.Subtract_n[0] * NLPIDVersion2_B.Product_kv[0];
    tmp += NLPIDVersion2_B.Subtract_n[1] * NLPIDVersion2_B.Product_kv[1];
    NLPIDVersion2_B.Product_jb = tmp;

    /* Product: '<S49>/Product1' */
    tmp = NLPIDVersion2_B.u_o[0] * NLPIDVersion2_B.Product_an[0];
    tmp += NLPIDVersion2_B.u_o[1] * NLPIDVersion2_B.Product_an[1];
    NLPIDVersion2_B.Product1_aj = tmp;

    /* Sum: '<S49>/Add' */
    NLPIDVersion2_B.VectorConcatenate_c[2] = NLPIDVersion2_B.Product_jb +
      NLPIDVersion2_B.Product1_aj;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Constant: '<S55>/0_2x1' */
      NLPIDVersion2_B.VectorConcatenate_j[0] = NLPIDVersion2_P._2x1_Value_ig[0];
      NLPIDVersion2_B.VectorConcatenate_j[1] = NLPIDVersion2_P._2x1_Value_ig[1];

      /* Product: '<S154>/Product' incorporates:
       *  Constant: '<S143>/0_2x1'
       */
      NLPIDVersion2_B.Product_bf[0] = NLPIDVersion2_P._2x1_Value_i[0] *
        NLPIDVersion2_B.RoundingFunction;
      NLPIDVersion2_B.Product_bf[1] = NLPIDVersion2_P._2x1_Value_i[1] *
        NLPIDVersion2_B.RoundingFunction;
    }

    /* Product: '<S147>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    NLPIDVersion2_B.Product2_e = NLPIDVersion2_B.Integrator1 *
      NLPIDVersion2_P.k_Value;

    /* Trigonometry: '<S147>/sin(s)3' */
    NLPIDVersion2_B.sins3 = sin(NLPIDVersion2_B.Product2_e);
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S147>/Math Function' incorporates:
       *  Constant: '<S10>/k [-]'
       *  Constant: '<S147>/Constant'
       */
      if ((NLPIDVersion2_P.k_Value < 0.0) && (NLPIDVersion2_P.Constant_Value_ji >
           floor(NLPIDVersion2_P.Constant_Value_ji))) {
        NLPIDVersion2_B.MathFunction_i = -rt_pow_snf(-NLPIDVersion2_P.k_Value,
          NLPIDVersion2_P.Constant_Value_ji);
      } else {
        NLPIDVersion2_B.MathFunction_i = rt_pow_snf(NLPIDVersion2_P.k_Value,
          NLPIDVersion2_P.Constant_Value_ji);
      }
    }

    /* Product: '<S147>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    NLPIDVersion2_B.Product_m = NLPIDVersion2_P.r_xm_Value *
      NLPIDVersion2_B.sins3 * NLPIDVersion2_B.MathFunction_i;

    /* Trigonometry: '<S147>/cos(s)3' */
    NLPIDVersion2_B.coss3 = cos(NLPIDVersion2_B.Product2_e);

    /* Product: '<S147>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    NLPIDVersion2_B.Product1_ou = NLPIDVersion2_P.r_ym_Value *
      NLPIDVersion2_B.coss3 * NLPIDVersion2_B.MathFunction_i;

    /* Gain: '<S147>/Gain' */
    NLPIDVersion2_B.Gain_n = NLPIDVersion2_P.Gain_Gain_gz *
      NLPIDVersion2_B.Product1_ou;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Sum: '<S154>/Subract' incorporates:
       *  Constant: '<S154>/Constant'
       */
      NLPIDVersion2_B.Subract_k = NLPIDVersion2_P.Constant_Value_n -
        NLPIDVersion2_B.RoundingFunction;
    }

    /* Product: '<S154>/Product1' */
    NLPIDVersion2_B.Product1_ic[0] = NLPIDVersion2_B.Product_m *
      NLPIDVersion2_B.Subract_k;
    NLPIDVersion2_B.Product1_ic[1] = NLPIDVersion2_B.Gain_n *
      NLPIDVersion2_B.Subract_k;

    /* Sum: '<S154>/Add' */
    NLPIDVersion2_B.Add_of[0] = NLPIDVersion2_B.Product_bf[0] +
      NLPIDVersion2_B.Product1_ic[0];
    NLPIDVersion2_B.Add_of[1] = NLPIDVersion2_B.Product_bf[1] +
      NLPIDVersion2_B.Product1_ic[1];

    /* Product: '<S99>/x_d^s * y_d^s^3 ' */
    NLPIDVersion2_B.x_dsy_ds3 = NLPIDVersion2_B.Add[0] * NLPIDVersion2_B.Add_of
      [1];

    /* Product: '<S99>/x_d^s^3 * y_d^s' */
    NLPIDVersion2_B.x_ds3y_ds = NLPIDVersion2_B.Add_of[0] * NLPIDVersion2_B.Add
      [1];

    /* Sum: '<S99>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
    NLPIDVersion2_B.x_dsy_ds3x_ds3y_ds = NLPIDVersion2_B.x_dsy_ds3 -
      NLPIDVersion2_B.x_ds3y_ds;

    /* Product: '<S99>/Product1' */
    NLPIDVersion2_B.Product1_dg = NLPIDVersion2_B.x_dsy_ds3x_ds3y_ds *
      NLPIDVersion2_B.x_ds2y_ds2;

    /* Product: '<S99>/x_d^s * x_d^s^2' */
    NLPIDVersion2_B.x_dsx_ds2 = NLPIDVersion2_B.Add[0] * NLPIDVersion2_B.Add_l[0];

    /* Product: '<S99>/y_d^s * y_d^s^2' */
    NLPIDVersion2_B.y_dsy_ds2 = NLPIDVersion2_B.Add[1] * NLPIDVersion2_B.Add_l[1];

    /* Sum: '<S99>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
    NLPIDVersion2_B.x_dsx_ds2x_ds3y_ds = NLPIDVersion2_B.x_dsx_ds2 +
      NLPIDVersion2_B.y_dsy_ds2;

    /* Gain: '<S99>/+ 2' */
    NLPIDVersion2_B.u_k = NLPIDVersion2_P.u_Gain_k *
      NLPIDVersion2_B.x_dsx_ds2x_ds3y_ds;

    /* Product: '<S99>/Product2' */
    NLPIDVersion2_B.Product2_ey = NLPIDVersion2_B.x_dsy_ds2x_ds2y_ds *
      NLPIDVersion2_B.u_k;

    /* Sum: '<S99>/Subtract' */
    NLPIDVersion2_B.Subtract_ar = NLPIDVersion2_B.Product1_dg -
      NLPIDVersion2_B.Product2_ey;

    /* Math: '<S99>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
    tmp = NLPIDVersion2_B.x_ds2y_ds2;
    NLPIDVersion2_B.x_ds2y_ds22 = tmp * tmp;

    /* Product: '<S99>/Divide' */
    NLPIDVersion2_B.Divide_li = NLPIDVersion2_B.Subtract_ar /
      NLPIDVersion2_B.x_ds2y_ds22;

    /* Math: '<S127>/(epsilon_n^s)^2' */
    tmp = NLPIDVersion2_B.MultiportSelector2;
    NLPIDVersion2_B.epsilon_ns2 = tmp * tmp;

    /* Product: '<S127>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product_lo = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.MultiportSelector * NLPIDVersion2_B.epsilon_ns2;

    /* Gain: '<S127>/2' */
    NLPIDVersion2_B.u_p = NLPIDVersion2_P._Gain_j * NLPIDVersion2_B.Product_lo;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S127>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = NLPIDVersion2_P.Deltam_Value;
      NLPIDVersion2_B.Delta2_nhl = tmp * tmp;
    }

    /* Math: '<S127>/epsilon_n^2' */
    tmp = NLPIDVersion2_B.MultiportSelector;
    NLPIDVersion2_B.epsilon_n2_n = tmp * tmp;

    /* Sum: '<S127>/Add' */
    NLPIDVersion2_B.Add_dv = NLPIDVersion2_B.Delta2_nhl +
      NLPIDVersion2_B.epsilon_n2_n;

    /* Math: '<S127>/( )^2' */
    tmp = NLPIDVersion2_B.Add_dv;
    NLPIDVersion2_B.u_d = tmp * tmp;

    /* Product: '<S127>/Divide' */
    NLPIDVersion2_B.Divide_ng = NLPIDVersion2_B.u_p / NLPIDVersion2_B.u_d;

    /* Outputs for atomic SubSystem: '<S105>/S_2(psi_d^s^2)' */

    /* Gain: '<S134>/S12' */
    NLPIDVersion2_B.S12_c = NLPIDVersion2_P.S12_Gain_g *
      NLPIDVersion2_B.Divide_li;

    /* Reshape: '<S134>/S_2(psi_d^s^2)' incorporates:
     *  Constant: '<S134>/0'
     */
    NLPIDVersion2_B.S_2psi_ds2[0] = NLPIDVersion2_P._Value_m;
    NLPIDVersion2_B.S_2psi_ds2[1] = NLPIDVersion2_B.Divide_li;
    NLPIDVersion2_B.S_2psi_ds2[2] = NLPIDVersion2_B.S12_c;
    NLPIDVersion2_B.S_2psi_ds2[3] = NLPIDVersion2_P._Value_m;

    /* end of Outputs for SubSystem: '<S105>/S_2(psi_d^s^2)' */

    /* Math: '<S135>/Math Function' */
    NLPIDVersion2_B.MathFunction_ce[0] = NLPIDVersion2_B.S_2psi_ds2[0];
    NLPIDVersion2_B.MathFunction_ce[1] = NLPIDVersion2_B.S_2psi_ds2[2];
    NLPIDVersion2_B.MathFunction_ce[2] = NLPIDVersion2_B.S_2psi_ds2[1];
    NLPIDVersion2_B.MathFunction_ce[3] = NLPIDVersion2_B.S_2psi_ds2[3];

    /* Product: '<S139>/Product' */
    for (i = 0; i < 2; i++) {
      NLPIDVersion2_B.Product_mi[i] = 0.0;
      NLPIDVersion2_B.Product_mi[i] = NLPIDVersion2_B.MathFunction_d[i] *
        NLPIDVersion2_B.MathFunction_d[0] + NLPIDVersion2_B.Product_mi[i];
      NLPIDVersion2_B.Product_mi[i] = NLPIDVersion2_B.MathFunction_d[i + 2] *
        NLPIDVersion2_B.MathFunction_d[1] + NLPIDVersion2_B.Product_mi[i];
      NLPIDVersion2_B.Product_mi[i + 2] = 0.0;
      NLPIDVersion2_B.Product_mi[i + 2] = NLPIDVersion2_B.Product_mi[i + 2] +
        NLPIDVersion2_B.MathFunction_d[i] * NLPIDVersion2_B.MathFunction_d[2];
      NLPIDVersion2_B.Product_mi[i + 2] = NLPIDVersion2_B.MathFunction_d[i + 2] *
        NLPIDVersion2_B.MathFunction_d[3] + NLPIDVersion2_B.Product_mi[i + 2];
    }

    /* Sum: '<S139>/Add' */
    NLPIDVersion2_B.Add_gb[0] = NLPIDVersion2_B.MathFunction_ce[0] +
      NLPIDVersion2_B.Product_mi[0];
    NLPIDVersion2_B.Add_gb[1] = NLPIDVersion2_B.MathFunction_ce[1] +
      NLPIDVersion2_B.Product_mi[1];
    NLPIDVersion2_B.Add_gb[2] = NLPIDVersion2_B.MathFunction_ce[2] +
      NLPIDVersion2_B.Product_mi[2];
    NLPIDVersion2_B.Add_gb[3] = NLPIDVersion2_B.MathFunction_ce[3] +
      NLPIDVersion2_B.Product_mi[3];

    /* Product: '<S139>/Product1' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += NLPIDVersion2_B.Add_gb[i] * NLPIDVersion2_B.MathFunction_o[0];
      tmp_3[i] += NLPIDVersion2_B.Add_gb[i + 2] *
        NLPIDVersion2_B.MathFunction_o[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += NLPIDVersion2_B.Add_gb[i] *
        NLPIDVersion2_B.MathFunction_o[2];
      tmp_3[i + 2] += NLPIDVersion2_B.Add_gb[i + 2] *
        NLPIDVersion2_B.MathFunction_o[3];
    }

    NLPIDVersion2_B.Product1_ph[0] = 0.0;
    NLPIDVersion2_B.Product1_ph[0] = tmp_3[0] * NLPIDVersion2_B.Subtract[0] +
      NLPIDVersion2_B.Product1_ph[0];
    NLPIDVersion2_B.Product1_ph[0] = tmp_3[2] * NLPIDVersion2_B.Subtract[1] +
      NLPIDVersion2_B.Product1_ph[0];
    NLPIDVersion2_B.Product1_ph[1] = 0.0;
    NLPIDVersion2_B.Product1_ph[1] = tmp_3[1] * NLPIDVersion2_B.Subtract[0] +
      NLPIDVersion2_B.Product1_ph[1];
    NLPIDVersion2_B.Product1_ph[1] = tmp_3[3] * NLPIDVersion2_B.Subtract[1] +
      NLPIDVersion2_B.Product1_ph[1];

    /* Product: '<S139>/Product2' */
    for (i = 0; i < 2; i++) {
      tmp_3[i] = 0.0;
      tmp_3[i] += NLPIDVersion2_B.MathFunction_d[i] *
        NLPIDVersion2_B.MathFunction_o[0];
      tmp_3[i] += NLPIDVersion2_B.MathFunction_d[i + 2] *
        NLPIDVersion2_B.MathFunction_o[1];
      tmp_3[i + 2] = 0.0;
      tmp_3[i + 2] += NLPIDVersion2_B.MathFunction_d[i] *
        NLPIDVersion2_B.MathFunction_o[2];
      tmp_3[i + 2] += NLPIDVersion2_B.MathFunction_d[i + 2] *
        NLPIDVersion2_B.MathFunction_o[3];
    }

    NLPIDVersion2_B.Product2_c[0] = 0.0;
    NLPIDVersion2_B.Product2_c[0] = tmp_3[0] * NLPIDVersion2_B.Add[0] +
      NLPIDVersion2_B.Product2_c[0];
    NLPIDVersion2_B.Product2_c[0] = tmp_3[2] * NLPIDVersion2_B.Add[1] +
      NLPIDVersion2_B.Product2_c[0];

    /* Gain: '<S139>/2' */
    NLPIDVersion2_B.u_a[0] = NLPIDVersion2_P._Gain_f *
      NLPIDVersion2_B.Product2_c[0];

    /* Product: '<S139>/Product3' */
    NLPIDVersion2_B.Product3_b[0] = 0.0;
    NLPIDVersion2_B.Product3_b[0] = NLPIDVersion2_B.MathFunction_o[0] *
      NLPIDVersion2_B.Add_l[0] + NLPIDVersion2_B.Product3_b[0];
    NLPIDVersion2_B.Product3_b[0] = NLPIDVersion2_B.MathFunction_o[2] *
      NLPIDVersion2_B.Add_l[1] + NLPIDVersion2_B.Product3_b[0];

    /* Sum: '<S139>/Sum' */
    NLPIDVersion2_B.Sum_m[0] = (NLPIDVersion2_B.Product1_ph[0] -
      NLPIDVersion2_B.u_a[0]) - NLPIDVersion2_B.Product3_b[0];

    /* Gain: '<S139>/Gain' */
    NLPIDVersion2_B.Gain_b[0] = NLPIDVersion2_P.Gain_Gain_cv *
      NLPIDVersion2_B.Sum_m[0];
    NLPIDVersion2_B.Product2_c[1] = 0.0;
    NLPIDVersion2_B.Product2_c[1] = tmp_3[1] * NLPIDVersion2_B.Add[0] +
      NLPIDVersion2_B.Product2_c[1];
    NLPIDVersion2_B.Product2_c[1] = tmp_3[3] * NLPIDVersion2_B.Add[1] +
      NLPIDVersion2_B.Product2_c[1];

    /* Gain: '<S139>/2' */
    NLPIDVersion2_B.u_a[1] = NLPIDVersion2_P._Gain_f *
      NLPIDVersion2_B.Product2_c[1];

    /* Product: '<S139>/Product3' */
    NLPIDVersion2_B.Product3_b[1] = 0.0;
    NLPIDVersion2_B.Product3_b[1] = NLPIDVersion2_B.MathFunction_o[1] *
      NLPIDVersion2_B.Add_l[0] + NLPIDVersion2_B.Product3_b[1];
    NLPIDVersion2_B.Product3_b[1] = NLPIDVersion2_B.MathFunction_o[3] *
      NLPIDVersion2_B.Add_l[1] + NLPIDVersion2_B.Product3_b[1];

    /* Sum: '<S139>/Sum' */
    NLPIDVersion2_B.Sum_m[1] = (NLPIDVersion2_B.Product1_ph[1] -
      NLPIDVersion2_B.u_a[1]) - NLPIDVersion2_B.Product3_b[1];

    /* Gain: '<S139>/Gain' */
    NLPIDVersion2_B.Gain_b[1] = NLPIDVersion2_P.Gain_Gain_cv *
      NLPIDVersion2_B.Sum_m[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector4' */
    {
      const byte_T *u = (byte_T *)NLPIDVersion2_B.Gain_b;/* input port */
      const int32_T *index = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&NLPIDVersion2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&NLPIDVersion2_B.MultiportSelector4;
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
    }                                  /* end <S105>/Multiport Selector4 */

    /* Product: '<S127>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product1_mi = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.MultiportSelector4;

    /* Product: '<S127>/Divide1' */
    NLPIDVersion2_B.Divide1_n = NLPIDVersion2_B.Product1_mi /
      NLPIDVersion2_B.Add_dv;

    /* Sum: '<S127>/Sum' */
    NLPIDVersion2_B.Sum_k = (NLPIDVersion2_B.Divide_li +
      NLPIDVersion2_B.Divide_ng) - NLPIDVersion2_B.Divide1_n;

    /* Product: '<S55>/Product' */
    NLPIDVersion2_B.Product_fu = NLPIDVersion2_B.Sum_k *
      NLPIDVersion2_B.Subtract_a;

    /* Math: '<S165>/Math Function' */
    NLPIDVersion2_B.MathFunction_pg[0] = NLPIDVersion2_B.Add[0];
    NLPIDVersion2_B.MathFunction_pg[1] = NLPIDVersion2_B.Add[1];

    /* Product: '<S163>/Product1' */
    tmp = NLPIDVersion2_B.MathFunction_pg[0] * NLPIDVersion2_B.Add_l[0];
    tmp += NLPIDVersion2_B.MathFunction_pg[1] * NLPIDVersion2_B.Add_l[1];
    NLPIDVersion2_B.Product1_j = tmp;

    /* Math: '<S163>/|p_d^s|^3' incorporates:
     *  Constant: '<S163>/Constant'
     */
    if ((NLPIDVersion2_B.Add_pj < 0.0) && (NLPIDVersion2_P.Constant_Value_m >
         floor(NLPIDVersion2_P.Constant_Value_m))) {
      NLPIDVersion2_B.p_ds3 = -rt_pow_snf(-NLPIDVersion2_B.Add_pj,
        NLPIDVersion2_P.Constant_Value_m);
    } else {
      NLPIDVersion2_B.p_ds3 = rt_pow_snf(NLPIDVersion2_B.Add_pj,
        NLPIDVersion2_P.Constant_Value_m);
    }

    /* Product: '<S163>/Divide' */
    NLPIDVersion2_B.Divide_lp = NLPIDVersion2_B.Product1_j /
      NLPIDVersion2_B.p_ds3;

    /* Product: '<S163>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    NLPIDVersion2_B.Product_p = NLPIDVersion2_B.Divide_lp *
      NLPIDVersion2_P.u_dm_Value;

    /* Gain: '<S163>/Gain' */
    NLPIDVersion2_B.Gain_o = NLPIDVersion2_P.Gain_Gain_eu *
      NLPIDVersion2_B.Product_p;

    /* Math: '<S113>/epsilon_n^2' */
    tmp = NLPIDVersion2_B.MultiportSelector;
    NLPIDVersion2_B.epsilon_n2_p = tmp * tmp;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S113>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = NLPIDVersion2_P.Deltam_Value;
      NLPIDVersion2_B.Delta2_j = tmp * tmp;
    }

    /* Sum: '<S113>/Add' */
    NLPIDVersion2_B.Add_b = NLPIDVersion2_B.epsilon_n2_p +
      NLPIDVersion2_B.Delta2_j;

    /* Math: '<S113>/Math Function' */
    tmp = NLPIDVersion2_B.Add_b;
    if (tmp < 0.0) {
      NLPIDVersion2_B.MathFunction_ds = -sqrt(-tmp);
    } else {
      NLPIDVersion2_B.MathFunction_ds = sqrt(tmp);
    }

    /* Product: '<S113>/Divide' */
    NLPIDVersion2_B.Divide_lpt = NLPIDVersion2_B.Gain_o /
      NLPIDVersion2_B.MathFunction_ds;

    /* Product: '<S113>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product1_ap = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.Divide_lpt;

    /* Product: '<S113>/Product2' */
    NLPIDVersion2_B.Product2_e1 = NLPIDVersion2_B.MultiportSelector *
      NLPIDVersion2_B.MultiportSelector2;

    /* Math: '<S113>/^3//2' incorporates:
     *  Constant: '<S113>/3//2'
     */
    if ((NLPIDVersion2_B.Add_b < 0.0) && (NLPIDVersion2_P.u_Value_jk > floor
         (NLPIDVersion2_P.u_Value_jk))) {
      NLPIDVersion2_B.u2_d = -rt_pow_snf(-NLPIDVersion2_B.Add_b,
        NLPIDVersion2_P.u_Value_jk);
    } else {
      NLPIDVersion2_B.u2_d = rt_pow_snf(NLPIDVersion2_B.Add_b,
        NLPIDVersion2_P.u_Value_jk);
    }

    /* Product: '<S113>/Divide1' */
    NLPIDVersion2_B.Divide1_no = NLPIDVersion2_B.Product2_e1 /
      NLPIDVersion2_B.u2_d;

    /* Product: '<S113>/Product3' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Product3_m = NLPIDVersion2_P.Deltam_Value *
      NLPIDVersion2_B.Divide1_no * NLPIDVersion2_B.Divide_n;

    /* Product: '<S117>/Product1' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    NLPIDVersion2_B.Product1_n = NLPIDVersion2_P.my_Value *
      NLPIDVersion2_B.Add_pj;

    /* Math: '<S121>/Math Function' */
    NLPIDVersion2_B.MathFunction_il[0] = NLPIDVersion2_B.Add_l[0];

    /* Product: '<S117>/Divide2' */
    NLPIDVersion2_B.Divide2[0] = NLPIDVersion2_B.MathFunction_il[0] /
      NLPIDVersion2_B.Add_pj;

    /* Math: '<S120>/Math Function' */
    NLPIDVersion2_B.MathFunction_ht[0] = NLPIDVersion2_B.Add[0];

    /* Math: '<S121>/Math Function' */
    NLPIDVersion2_B.MathFunction_il[1] = NLPIDVersion2_B.Add_l[1];

    /* Product: '<S117>/Divide2' */
    NLPIDVersion2_B.Divide2[1] = NLPIDVersion2_B.MathFunction_il[1] /
      NLPIDVersion2_B.Add_pj;

    /* Math: '<S120>/Math Function' */
    NLPIDVersion2_B.MathFunction_ht[1] = NLPIDVersion2_B.Add[1];

    /* Product: '<S117>/Product2' */
    tmp = NLPIDVersion2_B.MathFunction_il[0] * NLPIDVersion2_B.Add[0];
    tmp += NLPIDVersion2_B.MathFunction_il[1] * NLPIDVersion2_B.Add[1];
    NLPIDVersion2_B.Product2_e1e[0] = tmp * NLPIDVersion2_B.MathFunction_ht[0];
    NLPIDVersion2_B.Product2_e1e[1] = tmp * NLPIDVersion2_B.MathFunction_ht[1];

    /* Math: '<S117>/Math Function' incorporates:
     *  Constant: '<S117>/Constant'
     */
    if ((NLPIDVersion2_B.Add_pj < 0.0) && (NLPIDVersion2_P.Constant_Value_gy >
         floor(NLPIDVersion2_P.Constant_Value_gy))) {
      NLPIDVersion2_B.MathFunction_c4 = -rt_pow_snf(-NLPIDVersion2_B.Add_pj,
        NLPIDVersion2_P.Constant_Value_gy);
    } else {
      NLPIDVersion2_B.MathFunction_c4 = rt_pow_snf(NLPIDVersion2_B.Add_pj,
        NLPIDVersion2_P.Constant_Value_gy);
    }

    /* Product: '<S117>/Divide1' */
    NLPIDVersion2_B.Divide1_o[0] = NLPIDVersion2_B.Product2_e1e[0] /
      NLPIDVersion2_B.MathFunction_c4;

    /* Sum: '<S117>/Subtract1' */
    NLPIDVersion2_B.Subtract1_j[0] = NLPIDVersion2_B.Divide2[0] -
      NLPIDVersion2_B.Divide1_o[0];

    /* Product: '<S117>/Divide1' */
    NLPIDVersion2_B.Divide1_o[1] = NLPIDVersion2_B.Product2_e1e[1] /
      NLPIDVersion2_B.MathFunction_c4;

    /* Sum: '<S117>/Subtract1' */
    NLPIDVersion2_B.Subtract1_j[1] = NLPIDVersion2_B.Divide2[1] -
      NLPIDVersion2_B.Divide1_o[1];

    /* Product: '<S117>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    tmp = NLPIDVersion2_P.my_Value * NLPIDVersion2_B.Subtract1_j[0] *
      NLPIDVersion2_B.Subtract[0];
    tmp += NLPIDVersion2_P.my_Value * NLPIDVersion2_B.Subtract1_j[1] *
      NLPIDVersion2_B.Subtract[1];
    NLPIDVersion2_B.Product_hd = tmp;

    /* Sum: '<S117>/Subtract' */
    NLPIDVersion2_B.Subtract_ny = NLPIDVersion2_B.Product1_n -
      NLPIDVersion2_B.Product_hd;

    /* Sum: '<S113>/Sum' */
    NLPIDVersion2_B.Sum_ax = (NLPIDVersion2_B.Product1_ap -
      NLPIDVersion2_B.Product3_m) - NLPIDVersion2_B.Subtract_ny;

    /* Product: '<S55>/Product1' */
    NLPIDVersion2_B.Product1_pf = NLPIDVersion2_B.Subtract_b *
      NLPIDVersion2_B.Sum_ax;

    /* Sum: '<S55>/Add' */
    NLPIDVersion2_B.VectorConcatenate_j[2] = NLPIDVersion2_B.Product_fu +
      NLPIDVersion2_B.Product1_pf;

    /* Sum: '<S65>/Add1' */
    NLPIDVersion2_B.Add1_d[0] = NLPIDVersion2_B.VectorConcatenate_c[0] +
      NLPIDVersion2_B.VectorConcatenate_j[0];

    /* Product: '<S42>/Product1' */
    NLPIDVersion2_B.Product1_c[0] = NLPIDVersion2_B.Add1_d[0] *
      NLPIDVersion2_B.Subtract_a;

    /* Sum: '<S65>/Add1' */
    NLPIDVersion2_B.Add1_d[1] = NLPIDVersion2_B.VectorConcatenate_c[1] +
      NLPIDVersion2_B.VectorConcatenate_j[1];

    /* Product: '<S42>/Product1' */
    NLPIDVersion2_B.Product1_c[1] = NLPIDVersion2_B.Add1_d[1] *
      NLPIDVersion2_B.Subtract_a;

    /* Sum: '<S65>/Add1' */
    NLPIDVersion2_B.Add1_d[2] = NLPIDVersion2_B.VectorConcatenate_c[2] +
      NLPIDVersion2_B.VectorConcatenate_j[2];

    /* Product: '<S42>/Product1' */
    NLPIDVersion2_B.Product1_c[2] = NLPIDVersion2_B.Add1_d[2] *
      NLPIDVersion2_B.Subtract_a;

    /* Trigonometry: '<S110>/Trigonometric Function' */
    NLPIDVersion2_B.TrigonometricFunction_h = cos(NLPIDVersion2_B.Sum_d);

    /* Trigonometry: '<S110>/Trigonometric Function1' */
    NLPIDVersion2_B.TrigonometricFunction1_g = sin(NLPIDVersion2_B.Sum_d);

    /* Derivative Block: '<S96>/Derivative' */
    {
      real_T t = NLPIDVersion2_M->Timing.t[0];
      real_T timeStampA = NLPIDVersion2_DWork.Derivative_RWORK_g.TimeStampA;
      real_T timeStampB = NLPIDVersion2_DWork.Derivative_RWORK_g.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        NLPIDVersion2_B.Derivative_h = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &NLPIDVersion2_DWork.Derivative_RWORK_g.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 2;
          }
        } else if (timeStampA >= t) {
          lastBank += 2;
        }

        deltaT = t - *lastBank++;
        NLPIDVersion2_B.Derivative_h = (NLPIDVersion2_P.u_dm_Value - *lastBank++)
          / deltaT;
      }
    }

    /* Product: '<S110>/Product' */
    NLPIDVersion2_B.Product_ae[0] = NLPIDVersion2_B.TrigonometricFunction_h *
      NLPIDVersion2_B.Derivative_h;
    NLPIDVersion2_B.Product_ae[1] = NLPIDVersion2_B.TrigonometricFunction1_g *
      NLPIDVersion2_B.Derivative_h;

    /* SignalConversion: '<S50>/ConcatBufferAtVector ConcatenateIn1' */
    NLPIDVersion2_B.VectorConcatenate_g[0] = NLPIDVersion2_B.Product_ae[0];
    NLPIDVersion2_B.VectorConcatenate_g[1] = NLPIDVersion2_B.Product_ae[1];

    /* Product: '<S50>/Product1' */
    tmp = NLPIDVersion2_B.u_o[0] * NLPIDVersion2_B.Product_ae[0];
    tmp += NLPIDVersion2_B.u_o[1] * NLPIDVersion2_B.Product_ae[1];
    NLPIDVersion2_B.VectorConcatenate_g[2] = tmp;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Constant: '<S56>/0_2x1' */
      NLPIDVersion2_B.VectorConcatenate_o[0] = NLPIDVersion2_P._2x1_Value_h[0];
      NLPIDVersion2_B.VectorConcatenate_o[1] = NLPIDVersion2_P._2x1_Value_h[1];
    }

    /* Math: '<S114>/epsilon_n^2' */
    tmp = NLPIDVersion2_B.MultiportSelector;
    NLPIDVersion2_B.epsilon_n2_nb = tmp * tmp;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Math: '<S114>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = NLPIDVersion2_P.Deltam_Value;
      NLPIDVersion2_B.Delta2_gb = tmp * tmp;
    }

    /* Sum: '<S114>/Add' */
    NLPIDVersion2_B.Add_gm = NLPIDVersion2_B.epsilon_n2_nb +
      NLPIDVersion2_B.Delta2_gb;

    /* Math: '<S114>/sqrt' */
    tmp = NLPIDVersion2_B.Add_gm;
    if (tmp < 0.0) {
      NLPIDVersion2_B.sqrt_p = -sqrt(-tmp);
    } else {
      NLPIDVersion2_B.sqrt_p = sqrt(tmp);
    }

    /* Product: '<S114>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    NLPIDVersion2_B.Divide_mc = NLPIDVersion2_P.Deltam_Value /
      NLPIDVersion2_B.sqrt_p;

    /* Product: '<S164>/Divide' */
    NLPIDVersion2_B.Divide_d = NLPIDVersion2_B.Derivative_h /
      NLPIDVersion2_B.Add_pj;

    /* Product: '<S114>/Product' */
    NLPIDVersion2_B.Product_e = NLPIDVersion2_B.Divide_mc *
      NLPIDVersion2_B.Divide_d;

    /* Product: '<S56>/Product1' */
    NLPIDVersion2_B.VectorConcatenate_o[2] = NLPIDVersion2_B.Subtract_b *
      NLPIDVersion2_B.Product_e;

    /* Sum: '<S66>/Add' */
    NLPIDVersion2_B.Add_nb[0] = NLPIDVersion2_B.VectorConcatenate_g[0] +
      NLPIDVersion2_B.VectorConcatenate_o[0];

    /* Sum: '<S42>/Sum' */
    NLPIDVersion2_B.Sum_e2[0] = (NLPIDVersion2_B.Product_ju[0] +
      NLPIDVersion2_B.Product1_c[0]) + NLPIDVersion2_B.Add_nb[0];

    /* Sum: '<S66>/Add' */
    NLPIDVersion2_B.Add_nb[1] = NLPIDVersion2_B.VectorConcatenate_g[1] +
      NLPIDVersion2_B.VectorConcatenate_o[1];

    /* Sum: '<S42>/Sum' */
    NLPIDVersion2_B.Sum_e2[1] = (NLPIDVersion2_B.Product_ju[1] +
      NLPIDVersion2_B.Product1_c[1]) + NLPIDVersion2_B.Add_nb[1];

    /* Sum: '<S66>/Add' */
    NLPIDVersion2_B.Add_nb[2] = NLPIDVersion2_B.VectorConcatenate_g[2] +
      NLPIDVersion2_B.VectorConcatenate_o[2];

    /* Sum: '<S42>/Sum' */
    NLPIDVersion2_B.Sum_e2[2] = (NLPIDVersion2_B.Product_ju[2] +
      NLPIDVersion2_B.Product1_c[2]) + NLPIDVersion2_B.Add_nb[2];

    /* Product: '<S57>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] +
          NLPIDVersion2_B.MathFunction_m[3 * tmp_6] * NLPIDVersion2_B.x3[i];
        tmp_2[i + 3 * tmp_6] = NLPIDVersion2_B.MathFunction_m[3 * tmp_6 + 1] *
          NLPIDVersion2_B.x3[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = NLPIDVersion2_B.MathFunction_m[3 * tmp_6 + 2] *
          NLPIDVersion2_B.x3[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.Product_d4[i] = 0.0;
      NLPIDVersion2_B.Product_d4[i] = tmp_2[i] * NLPIDVersion2_B.Sum_e2[0] +
        NLPIDVersion2_B.Product_d4[i];
      NLPIDVersion2_B.Product_d4[i] = tmp_2[i + 3] * NLPIDVersion2_B.Sum_e2[1] +
        NLPIDVersion2_B.Product_d4[i];
      NLPIDVersion2_B.Product_d4[i] = tmp_2[i + 6] * NLPIDVersion2_B.Sum_e2[2] +
        NLPIDVersion2_B.Product_d4[i];
    }

    /* Gain: '<S60>/S12' */
    NLPIDVersion2_B.S12 = NLPIDVersion2_P.S12_Gain * NLPIDVersion2_B.nuSwitch[2];

    /* Reshape: '<S60>/S(r)' incorporates:
     *  Constant: '<S60>/R31'
     *  Constant: '<S60>/S11'
     *  Constant: '<S60>/S13'
     *  Constant: '<S60>/S22'
     *  Constant: '<S60>/S23'
     *  Constant: '<S60>/S32'
     *  Constant: '<S60>/S33'
     */
    NLPIDVersion2_B.Sr[0] = NLPIDVersion2_P.S11_Value;
    NLPIDVersion2_B.Sr[1] = NLPIDVersion2_B.nuSwitch[2];
    NLPIDVersion2_B.Sr[2] = NLPIDVersion2_P.R31_Value_l;
    NLPIDVersion2_B.Sr[3] = NLPIDVersion2_B.S12;
    NLPIDVersion2_B.Sr[4] = NLPIDVersion2_P.S22_Value;
    NLPIDVersion2_B.Sr[5] = NLPIDVersion2_P.S32_Value;
    NLPIDVersion2_B.Sr[6] = NLPIDVersion2_P.S13_Value;
    NLPIDVersion2_B.Sr[7] = NLPIDVersion2_P.S23_Value;
    NLPIDVersion2_B.Sr[8] = NLPIDVersion2_P.S33_Value;

    /* Math: '<S61>/Math Function' */
    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.MathFunction_n[3 * i] = NLPIDVersion2_B.Sr[i];
      NLPIDVersion2_B.MathFunction_n[1 + 3 * i] = NLPIDVersion2_B.Sr[i + 3];
      NLPIDVersion2_B.MathFunction_n[2 + 3 * i] = NLPIDVersion2_B.Sr[i + 6];
    }

    /* Product: '<S57>/Product1' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_2[i + 3 * tmp_6] = 0.0;
        tmp_2[i + 3 * tmp_6] = tmp_2[3 * tmp_6 + i] +
          NLPIDVersion2_B.MathFunction_n[3 * tmp_6] * NLPIDVersion2_B.x3[i];
        tmp_2[i + 3 * tmp_6] = NLPIDVersion2_B.MathFunction_n[3 * tmp_6 + 1] *
          NLPIDVersion2_B.x3[i + 3] + tmp_2[3 * tmp_6 + i];
        tmp_2[i + 3 * tmp_6] = NLPIDVersion2_B.MathFunction_n[3 * tmp_6 + 2] *
          NLPIDVersion2_B.x3[i + 6] + tmp_2[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_4[i + 3 * tmp_6] = 0.0;
        tmp_4[i + 3 * tmp_6] = tmp_4[3 * tmp_6 + i] +
          NLPIDVersion2_B.MathFunction_m[3 * tmp_6] * tmp_2[i];
        tmp_4[i + 3 * tmp_6] = NLPIDVersion2_B.MathFunction_m[3 * tmp_6 + 1] *
          tmp_2[i + 3] + tmp_4[3 * tmp_6 + i];
        tmp_4[i + 3 * tmp_6] = NLPIDVersion2_B.MathFunction_m[3 * tmp_6 + 2] *
          tmp_2[i + 6] + tmp_4[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.Product1_l[i] = 0.0;
      NLPIDVersion2_B.Product1_l[i] = tmp_4[i] * NLPIDVersion2_B.Add_lh[0] +
        NLPIDVersion2_B.Product1_l[i];
      NLPIDVersion2_B.Product1_l[i] = tmp_4[i + 3] * NLPIDVersion2_B.Add_lh[1] +
        NLPIDVersion2_B.Product1_l[i];
      NLPIDVersion2_B.Product1_l[i] = tmp_4[i + 6] * NLPIDVersion2_B.Add_lh[2] +
        NLPIDVersion2_B.Product1_l[i];

      /* Sum: '<S57>/Subtract' */
      NLPIDVersion2_B.Subtract_j[i] = NLPIDVersion2_B.Product_d4[i] -
        NLPIDVersion2_B.Product1_l[i];

      /* Sum: '<S39>/Sum' */
      NLPIDVersion2_B.Sum_fj[i] = (NLPIDVersion2_B.Sum_j[i] +
        NLPIDVersion2_B.Product1_al[i]) + NLPIDVersion2_B.Subtract_j[i];
    }

    /* MultiPortSwitch: '<S29>/tau Switch' incorporates:
     *  Constant: '<S1>/Control Mode Selector'
     */
    switch ((int32_T)NLPIDVersion2_P.ControlModeSelector_Value) {
     case 0:
      NLPIDVersion2_B.tauSwitch[0] = NLPIDVersion2_B.Product[0];
      NLPIDVersion2_B.tauSwitch[1] = NLPIDVersion2_B.Product[1];
      NLPIDVersion2_B.tauSwitch[2] = NLPIDVersion2_B.Product[2];
      break;

     case 1:
      NLPIDVersion2_B.tauSwitch[0] = NLPIDVersion2_B.Sum1_f[0];
      NLPIDVersion2_B.tauSwitch[1] = NLPIDVersion2_B.Sum1_f[1];
      NLPIDVersion2_B.tauSwitch[2] = NLPIDVersion2_B.Sum1_f[2];
      break;

     default:
      NLPIDVersion2_B.tauSwitch[0] = NLPIDVersion2_B.Sum_fj[0];
      NLPIDVersion2_B.tauSwitch[1] = NLPIDVersion2_B.Sum_fj[1];
      NLPIDVersion2_B.tauSwitch[2] = NLPIDVersion2_B.Sum_fj[2];
      break;
    }

    /* Concatenate: '<S106>/Matrix Concatenate' incorporates:
     *  Constant: '<S140>/Constant'
     */
    NLPIDVersion2_B.MatrixConcatenate_b[0] = NLPIDVersion2_P.Constant_Value_jd[0];
    NLPIDVersion2_B.MatrixConcatenate_b[1] = NLPIDVersion2_P.Constant_Value_jd[1];
    NLPIDVersion2_B.MatrixConcatenate_b[3] = NLPIDVersion2_P.Constant_Value_jd[2];
    NLPIDVersion2_B.MatrixConcatenate_b[4] = NLPIDVersion2_P.Constant_Value_jd[3];
    NLPIDVersion2_B.MatrixConcatenate_b[2] = NLPIDVersion2_B.u_o[0];
    NLPIDVersion2_B.MatrixConcatenate_b[5] = NLPIDVersion2_B.u_o[1];

    /* Math: '<S63>/Math Function' */
    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.MathFunction_k1[i << 1] =
        NLPIDVersion2_B.MatrixConcatenate_b[i];
      NLPIDVersion2_B.MathFunction_k1[1 + (i << 1)] =
        NLPIDVersion2_B.MatrixConcatenate_b[i + 3];
    }

    /* Product: '<S41>/Product2' */
    for (i = 0; i < 2; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_5[i + (tmp_6 << 1)] = 0.0;
        tmp_5[i + (tmp_6 << 1)] = tmp_5[(tmp_6 << 1) + i] +
          NLPIDVersion2_B.ux3_g[3 * tmp_6] * NLPIDVersion2_B.MathFunction_k1[i];
        tmp_5[i + (tmp_6 << 1)] = NLPIDVersion2_B.ux3_g[3 * tmp_6 + 1] *
          NLPIDVersion2_B.MathFunction_k1[i + 2] + tmp_5[(tmp_6 << 1) + i];
        tmp_5[i + (tmp_6 << 1)] = NLPIDVersion2_B.ux3_g[3 * tmp_6 + 2] *
          NLPIDVersion2_B.MathFunction_k1[i + 4] + tmp_5[(tmp_6 << 1) + i];
      }
    }

    for (i = 0; i < 2; i++) {
      NLPIDVersion2_B.Product2_g[i] = 0.0;
      NLPIDVersion2_B.Product2_g[i] = tmp_5[i] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInport3[0] +
        NLPIDVersion2_B.Product2_g[i];
      NLPIDVersion2_B.Product2_g[i] = tmp_5[i + 2] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInport3[1] +
        NLPIDVersion2_B.Product2_g[i];
      NLPIDVersion2_B.Product2_g[i] = tmp_5[i + 4] *
        NLPIDVersion2_B.TmpHiddenBufferAtProductInport3[2] +
        NLPIDVersion2_B.Product2_g[i];
    }

    /* Product: '<S41>/Product3' */
    NLPIDVersion2_B.Product3_mf[0] = 0.0;
    NLPIDVersion2_B.Product3_mf[0] = NLPIDVersion2_B.ux2[0] *
      NLPIDVersion2_B.Product2_g[0] + NLPIDVersion2_B.Product3_mf[0];
    NLPIDVersion2_B.Product3_mf[0] = NLPIDVersion2_B.ux2[2] *
      NLPIDVersion2_B.Product2_g[1] + NLPIDVersion2_B.Product3_mf[0];

    /* Sum: '<S41>/Subtract' */
    NLPIDVersion2_B.Subtract_as[0] = NLPIDVersion2_B.Integrator2[0] -
      NLPIDVersion2_B.Product3_mf[0];

    /* Product: '<S41>/Product4' incorporates:
     *  Constant: '<S9>/lambda_q'
     */
    NLPIDVersion2_B.Product4_m[0] = NLPIDVersion2_P.lambda_q_Value *
      NLPIDVersion2_B.Subtract_as[0];

    /* Gain: '<S41>/Gain' */
    NLPIDVersion2_B.Gain_pp[0] = NLPIDVersion2_P.Gain_Gain_i *
      NLPIDVersion2_B.Product4_m[0];

    /* Product: '<S41>/Product3' */
    NLPIDVersion2_B.Product3_mf[1] = 0.0;
    NLPIDVersion2_B.Product3_mf[1] = NLPIDVersion2_B.ux2[1] *
      NLPIDVersion2_B.Product2_g[0] + NLPIDVersion2_B.Product3_mf[1];
    NLPIDVersion2_B.Product3_mf[1] = NLPIDVersion2_B.ux2[3] *
      NLPIDVersion2_B.Product2_g[1] + NLPIDVersion2_B.Product3_mf[1];

    /* Sum: '<S41>/Subtract' */
    NLPIDVersion2_B.Subtract_as[1] = NLPIDVersion2_B.Integrator2[1] -
      NLPIDVersion2_B.Product3_mf[1];

    /* Product: '<S41>/Product4' incorporates:
     *  Constant: '<S9>/lambda_q'
     */
    NLPIDVersion2_B.Product4_m[1] = NLPIDVersion2_P.lambda_q_Value *
      NLPIDVersion2_B.Subtract_as[1];

    /* Gain: '<S41>/Gain' */
    NLPIDVersion2_B.Gain_pp[1] = NLPIDVersion2_P.Gain_Gain_i *
      NLPIDVersion2_B.Product4_m[1];

    /* Product: '<S46>/Product' */
    for (i = 0; i < 3; i++) {
      NLPIDVersion2_B.Product_og[i] = 0.0;
      NLPIDVersion2_B.Product_og[i] = NLPIDVersion2_B.Rpsi[i] *
        NLPIDVersion2_B.Subtract_e[0] + NLPIDVersion2_B.Product_og[i];
      NLPIDVersion2_B.Product_og[i] = NLPIDVersion2_B.Rpsi[i + 3] *
        NLPIDVersion2_B.Subtract_e[1] + NLPIDVersion2_B.Product_og[i];
      NLPIDVersion2_B.Product_og[i] = NLPIDVersion2_B.Rpsi[i + 6] *
        NLPIDVersion2_B.Subtract_e[2] + NLPIDVersion2_B.Product_og[i];
    }

    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* S-Function (sdsppinv): '<S76>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&NLPIDVersion2_DWork.Pseudoinverse_X[0]), (void *)
             (&NLPIDVersion2_B.x5[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&NLPIDVersion2_DWork.Pseudoinverse_X[0], 3, 5,
                      &NLPIDVersion2_DWork.Pseudoinverse_S[0],
                      &NLPIDVersion2_DWork.Inverse_DWORK3[0],
                      &NLPIDVersion2_DWork.Pseudoinverse_WORK[0],
                      &NLPIDVersion2_DWork.Pseudoinverse_U[0],
                      &NLPIDVersion2_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&NLPIDVersion2_DWork.Pseudoinverse_S[0],
          &NLPIDVersion2_DWork.Pseudoinverse_U[0],
          &NLPIDVersion2_DWork.Pseudoinverse_V[0],
          &NLPIDVersion2_B.Pseudoinverse[0], (const int32_T)3, (const int32_T)5);
      }
    }

    /* Product: '<S76>/Product' */
    for (i = 0; i < 5; i++) {
      NLPIDVersion2_B.Product_m2[i] = 0.0;
      NLPIDVersion2_B.Product_m2[i] = NLPIDVersion2_B.Pseudoinverse[i] *
        NLPIDVersion2_B.tauSwitch[0] + NLPIDVersion2_B.Product_m2[i];
      NLPIDVersion2_B.Product_m2[i] = NLPIDVersion2_B.Pseudoinverse[i + 5] *
        NLPIDVersion2_B.tauSwitch[1] + NLPIDVersion2_B.Product_m2[i];
      NLPIDVersion2_B.Product_m2[i] = NLPIDVersion2_B.Pseudoinverse[i + 10] *
        NLPIDVersion2_B.tauSwitch[2] + NLPIDVersion2_B.Product_m2[i];
    }

    /* Lookup Block: '<S78>/f_1 to u_1'
     * About '<S78>/f_1 to u_1 :'
     * Lookup Block: '<S78>/f_1 to u_1'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPIDVersion2_B.f_1tou_1),
                         NLPIDVersion2_P.f_1tou_1_YData,
                         NLPIDVersion2_B.Product_m2[0],
                         NLPIDVersion2_P.f_1tou_1_XData, 38U);

    /* RelationalOperator: '<S83>/Compare' incorporates:
     *  Constant: '<S83>/Constant'
     */
    NLPIDVersion2_B.Compare = (NLPIDVersion2_B.Product_m2[1] <
      NLPIDVersion2_P.Constant_Value_c);

    /* RelationalOperator: '<S85>/Compare' incorporates:
     *  Constant: '<S85>/Constant'
     */
    NLPIDVersion2_B.Compare_o = (NLPIDVersion2_B.Product_m2[1] >=
      NLPIDVersion2_P.Constant_Value_go);

    /* RelationalOperator: '<S84>/Compare' incorporates:
     *  Constant: '<S84>/Constant'
     */
    NLPIDVersion2_B.Compare_c = (NLPIDVersion2_B.Product_m2[1] <
      NLPIDVersion2_P.Constant_Value_l1);

    /* Logic: '<S79>/Logical Operator' */
    NLPIDVersion2_B.LogicalOperator = ((NLPIDVersion2_B.Compare_o != 0) &&
      (NLPIDVersion2_B.Compare_c != 0));

    /* Sum: '<S79>/Sum1' */
    NLPIDVersion2_B.Sum1_l = (uint8_T)(NLPIDVersion2_B.LogicalOperator +
      NLPIDVersion2_B.LogicalOperator);

    /* RelationalOperator: '<S86>/Compare' incorporates:
     *  Constant: '<S86>/Constant'
     */
    NLPIDVersion2_B.Compare_f = (NLPIDVersion2_B.Product_m2[1] >=
      NLPIDVersion2_P.Constant_Value_k);

    /* Gain: '<S79>/Gain1' */
    NLPIDVersion2_B.Gain1_g = (uint16_T)(NLPIDVersion2_P.Gain1_Gain_n *
      NLPIDVersion2_B.Compare_f);

    /* Sum: '<S79>/Sum' */
    NLPIDVersion2_B.Sum_cg = (uint16_T)(uint32_T)(((NLPIDVersion2_B.Compare << 6)
      + (NLPIDVersion2_B.Sum1_l << 6)) + NLPIDVersion2_B.Gain1_g);

    /* Lookup Block: '<S79>/f_2 < 0.00391'
     * About '<S79>/f_2 < 0.00391 :'
     * Lookup Block: '<S79>/f_2 < 0.00391'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPIDVersion2_B.f_2000391),
                         NLPIDVersion2_P.f_2000391_YData,
                         NLPIDVersion2_B.Product_m2[1],
                         NLPIDVersion2_P.f_2000391_XData, 10U);

    /* Lookup Block: '<S79>/f_2 < 0.06731 && f_2 >= 0.00391'
     * About '<S79>/f_2 < 0.06731 && f_2 >= 0.00391 :'
     * Lookup Block: '<S79>/f_2 < 0.06731 && f_2 >= 0.00391'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPIDVersion2_B.f_2006731f_2000391),
                         NLPIDVersion2_P.f_2006731f_2000391_YData,
                         NLPIDVersion2_B.Product_m2[1],
                         NLPIDVersion2_P.f_2006731f_2000391_XData, 2U);

    /* Lookup Block: '<S79>/f_2 => 0.06731'
     * About '<S79>/f_2 => 0.06731 :'
     * Lookup Block: '<S79>/f_2 => 0.06731'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPIDVersion2_B.f_2006731),
                         NLPIDVersion2_P.f_2006731_YData,
                         NLPIDVersion2_B.Product_m2[1],
                         NLPIDVersion2_P.f_2006731_XData, 17U);

    /* MultiPortSwitch: '<S79>/Multiport Switch' */
    switch ((int32_T)((uint32_T)(int32_T)NLPIDVersion2_B.Sum_cg >> 6)) {
     case 1:
      NLPIDVersion2_B.MultiportSwitch = NLPIDVersion2_B.f_2000391;
      break;

     case 2:
      NLPIDVersion2_B.MultiportSwitch = NLPIDVersion2_B.f_2006731f_2000391;
      break;

     default:
      NLPIDVersion2_B.MultiportSwitch = NLPIDVersion2_B.f_2006731;
      break;
    }

    /* Lookup Block: '<S80>/f_3 to u_3'
     * About '<S80>/f_3 to u_3 :'
     * Lookup Block: '<S80>/f_3 to u_3'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPIDVersion2_B.f_3tou_3),
                         NLPIDVersion2_P.f_3tou_3_YData,
                         NLPIDVersion2_B.Product_m2[2],
                         NLPIDVersion2_P.f_3tou_3_XData, 38U);

    /* RelationalOperator: '<S87>/Compare' incorporates:
     *  Constant: '<S87>/Constant'
     */
    NLPIDVersion2_B.Compare_b = (NLPIDVersion2_B.Product_m2[3] <
      NLPIDVersion2_P.Constant_Value_al);

    /* RelationalOperator: '<S88>/Compare' incorporates:
     *  Constant: '<S88>/Constant'
     */
    NLPIDVersion2_B.Compare_m = (NLPIDVersion2_B.Product_m2[3] >=
      NLPIDVersion2_P.Constant_Value_nq);

    /* Gain: '<S81>/Gain' */
    NLPIDVersion2_B.Gain_m = (uint16_T)(NLPIDVersion2_P.Gain_Gain_l *
      NLPIDVersion2_B.Compare_m);

    /* Sum: '<S81>/Sum' */
    NLPIDVersion2_B.Sum_e5 = (uint16_T)(uint32_T)((NLPIDVersion2_B.Compare_b <<
      6) + NLPIDVersion2_B.Gain_m);

    /* Lookup Block: '<S81>/f_4 < 0.0451'
     * About '<S81>/f_4 < 0.0451 :'
     * Lookup Block: '<S81>/f_4 < 0.0451'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPIDVersion2_B.f_400451),
                         NLPIDVersion2_P.f_400451_YData,
                         NLPIDVersion2_B.Product_m2[3],
                         NLPIDVersion2_P.f_400451_XData, 14U);

    /* Lookup Block: '<S81>/f_4 >= 0.0451 '
     * About '<S81>/f_4 >= 0.0451  :'
     * Lookup Block: '<S81>/f_4 >= 0.0451 '
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPIDVersion2_B.f_400451_o),
                         NLPIDVersion2_P.f_400451_YData_p,
                         NLPIDVersion2_B.Product_m2[3],
                         NLPIDVersion2_P.f_400451_XData_e, 12U);

    /* MultiPortSwitch: '<S81>/Multiport Switch' */
    if ((int32_T)((uint32_T)(int32_T)NLPIDVersion2_B.Sum_e5 >> 6) == 1) {
      NLPIDVersion2_B.MultiportSwitch_m = NLPIDVersion2_B.f_400451;
    } else {
      NLPIDVersion2_B.MultiportSwitch_m = NLPIDVersion2_B.f_400451_o;
    }

    /* DeadZone Block: '<S82>/Dead Zone +-0.01'
     */
    if (NLPIDVersion2_B.Product_m2[4] >= NLPIDVersion2_P.DeadZone001_End) {
      NLPIDVersion2_B.DeadZone001 = NLPIDVersion2_B.Product_m2[4] -
        NLPIDVersion2_P.DeadZone001_End;
    } else if (NLPIDVersion2_B.Product_m2[4] > NLPIDVersion2_P.DeadZone001_Start)
    {
      NLPIDVersion2_B.DeadZone001 = 0.0;
    } else {
      NLPIDVersion2_B.DeadZone001 = NLPIDVersion2_B.Product_m2[4] -
        NLPIDVersion2_P.DeadZone001_Start;
    }

    /* RelationalOperator: '<S89>/Compare' incorporates:
     *  Constant: '<S89>/Constant'
     */
    NLPIDVersion2_B.Compare_p = (NLPIDVersion2_B.DeadZone001 <
      NLPIDVersion2_P.Constant_Value_b);

    /* RelationalOperator: '<S91>/Compare' */
    NLPIDVersion2_B.Compare_oc = (NLPIDVersion2_B.DeadZone001 == 0.0);

    /* Gain: '<S82>/Gain' */
    NLPIDVersion2_B.Gain_bl = (uint16_T)(NLPIDVersion2_P.Gain_Gain_fd *
      NLPIDVersion2_B.Compare_oc);

    /* RelationalOperator: '<S90>/Compare' incorporates:
     *  Constant: '<S90>/Constant'
     */
    NLPIDVersion2_B.Compare_a = (NLPIDVersion2_B.DeadZone001 >
      NLPIDVersion2_P.Constant_Value_fz);

    /* Gain: '<S82>/Gain1' */
    NLPIDVersion2_B.Gain1_c = (uint16_T)(NLPIDVersion2_P.Gain1_Gain_i *
      NLPIDVersion2_B.Compare_a);

    /* Sum: '<S82>/Sum' */
    NLPIDVersion2_B.Sum_lj = (uint16_T)(uint32_T)(((NLPIDVersion2_B.Compare_p <<
      6) + NLPIDVersion2_B.Gain_bl) + NLPIDVersion2_B.Gain1_c);

    /* Lookup Block: '<S82>/f_5 < 0'
     * About '<S82>/f_5 < 0 :'
     * Lookup Block: '<S82>/f_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPIDVersion2_B.f_50), NLPIDVersion2_P.f_50_YData,
                         NLPIDVersion2_B.Product_m2[4],
                         NLPIDVersion2_P.f_50_XData, 9U);

    /* Lookup Block: '<S82>/f_5 > 0'
     * About '<S82>/f_5 > 0 :'
     * Lookup Block: '<S82>/f_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(NLPIDVersion2_B.f_50_j),
                         NLPIDVersion2_P.f_50_YData_c,
                         NLPIDVersion2_B.Product_m2[4],
                         NLPIDVersion2_P.f_50_XData_k, 9U);

    /* MultiPortSwitch: '<S82>/Multiport Switch' incorporates:
     *  Constant: '<S82>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)NLPIDVersion2_B.Sum_lj >> 6)) {
     case 1:
      NLPIDVersion2_B.MultiportSwitch_d = NLPIDVersion2_B.f_50;
      break;

     case 2:
      NLPIDVersion2_B.MultiportSwitch_d = NLPIDVersion2_P.f_50_Value;
      break;

     default:
      NLPIDVersion2_B.MultiportSwitch_d = NLPIDVersion2_B.f_50_j;
      break;
    }

    /* Saturate: '<S33>/Saturation' incorporates:
     *  Constant: '<S75>/BT_power_limit'
     *  Constant: '<S75>/VSP_speeds'
     */
    tmp_0[0] = NLPIDVersion2_B.f_1tou_1;
    tmp_0[1] = NLPIDVersion2_B.MultiportSwitch;
    tmp_0[2] = NLPIDVersion2_B.f_3tou_3;
    tmp_0[3] = NLPIDVersion2_B.MultiportSwitch_m;
    tmp_0[4] = NLPIDVersion2_B.MultiportSwitch_d;
    tmp_0[5] = NLPIDVersion2_P.BT_power_limit_Value;
    tmp_0[6] = NLPIDVersion2_P.VSP_speeds_Value;
    for (i = 0; i < 7; i++) {
      NLPIDVersion2_B.Saturation_j[i] = rt_SATURATE(tmp_0[i],
        NLPIDVersion2_P.Saturation_LowerSat_j,
        NLPIDVersion2_P.Saturation_UpperSat_il);
    }

    /* Gain: '<S166>/QTM In2 Error' */
    NLPIDVersion2_B.QTMIn2Error = NLPIDVersion2_P.QTMIn2Error_Gain *
      NLPIDVersion2_B.QTMIn[1];

    /* Gain: '<S166>/QTM In9 Residual' */
    NLPIDVersion2_B.QTMIn9Residual = NLPIDVersion2_P.QTMIn9Residual_Gain *
      NLPIDVersion2_B.QTMIn[8];

    /* Derivative Block: '<S166>/Derivative1' */
    {
      real_T t = NLPIDVersion2_M->Timing.t[0];
      real_T timeStampA = NLPIDVersion2_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = NLPIDVersion2_DWork.Derivative1_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        NLPIDVersion2_B.Derivative1[0] = 0.0;
        NLPIDVersion2_B.Derivative1[1] = 0.0;
        NLPIDVersion2_B.Derivative1[2] = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &NLPIDVersion2_DWork.Derivative1_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 4;
          }
        } else if (timeStampA >= t) {
          lastBank += 4;
        }

        deltaT = t - *lastBank++;
        NLPIDVersion2_B.Derivative1[0] = (NLPIDVersion2_B.mm2mx - *lastBank++) /
          deltaT;
        NLPIDVersion2_B.Derivative1[1] = (NLPIDVersion2_B.mm2my - *lastBank++) /
          deltaT;
        NLPIDVersion2_B.Derivative1[2] = (NLPIDVersion2_B.d2ryaw - *lastBank++) /
          deltaT;
      }
    }

    /* MultiPortSwitch: '<S167>/etadot Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)NLPIDVersion2_P.ControlInputSelector_Value == 0) {
      NLPIDVersion2_B.etadotSwitch[0] = NLPIDVersion2_B.Derivative1[0];
      NLPIDVersion2_B.etadotSwitch[1] = NLPIDVersion2_B.Derivative1[1];
      NLPIDVersion2_B.etadotSwitch[2] = NLPIDVersion2_B.Derivative1[2];
    } else {
      NLPIDVersion2_B.etadotSwitch[0] = NLPIDVersion2_B.Product3_mm[0];
      NLPIDVersion2_B.etadotSwitch[1] = NLPIDVersion2_B.Product3_mm[1];
      NLPIDVersion2_B.etadotSwitch[2] = NLPIDVersion2_B.Product3_mm[2];
    }

    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Saturate: '<S171>/Saturation' incorporates:
       *  Constant: '<S1>/Control Mode Selector'
       */
      tmp = NLPIDVersion2_P.ControlModeSelector_Value;
      NLPIDVersion2_B.Saturation_ja = rt_SATURATE(tmp,
        NLPIDVersion2_P.Saturation_LowerSat_b2,
        NLPIDVersion2_P.Saturation_UpperSat_k);
    }

    /* MultiPortSwitch: '<S171>/tau Switch' incorporates:
     *  Constant: '<S6>/PS3_BT_Power  [-]'
     *  Constant: '<S6>/PS3_VSP_Speed  [-]'
     */
    if ((int32_T)NLPIDVersion2_B.Saturation_ja == 0) {
      NLPIDVersion2_B.tauSwitch_m[0] = NLPIDVersion2_B.u_1;
      NLPIDVersion2_B.tauSwitch_m[1] = NLPIDVersion2_B.u_2;
      NLPIDVersion2_B.tauSwitch_m[2] = NLPIDVersion2_B.u_3;
      NLPIDVersion2_B.tauSwitch_m[3] = NLPIDVersion2_B.u_4;
      NLPIDVersion2_B.tauSwitch_m[4] = NLPIDVersion2_B.u_5;
      NLPIDVersion2_B.tauSwitch_m[5] = NLPIDVersion2_P.PS3_BT_Power_Value;
      NLPIDVersion2_B.tauSwitch_m[6] = NLPIDVersion2_P.PS3_VSP_Speed_Value;
    } else {
      for (i = 0; i < 7; i++) {
        NLPIDVersion2_B.tauSwitch_m[i] = NLPIDVersion2_B.Saturation_j[i];
      }
    }

    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* SignalConversion: '<S22>/TmpHiddenBufferAtTo FileInport1' incorporates:
       *  Constant: '<S1>/Control Input Selector'
       *  Constant: '<S1>/Control Mode Selector'
       *  Constant: '<S5>/Path Selector  [-]'
       *  Constant: '<S5>/u_d [m]'
       *  Constant: '<S7>/setpointx [m]'
       *  Constant: '<S7>/setpointy [m]'
       */
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[0] =
        NLPIDVersion2_P.ControlInputSelector_Value;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[1] =
        NLPIDVersion2_B.QTMIn2Error;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[2] =
        NLPIDVersion2_B.QTMIn9Residual;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[3] =
        NLPIDVersion2_B.etadotSwitch[0];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[4] =
        NLPIDVersion2_B.etadotSwitch[1];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[5] =
        NLPIDVersion2_B.etadotSwitch[2];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[6] =
        NLPIDVersion2_B.etaSwitch[0];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[7] =
        NLPIDVersion2_B.etaSwitch[1];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[8] =
        NLPIDVersion2_B.etaSwitch[2];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[9] =
        NLPIDVersion2_B.nuSwitch[0];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[10] =
        NLPIDVersion2_B.nuSwitch[1];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[11] =
        NLPIDVersion2_B.nuSwitch[2];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[12] =
        NLPIDVersion2_P.setpointxm_Value;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[13] =
        NLPIDVersion2_P.setpointym_Value;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[14] = NLPIDVersion2_B.Gain1;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[15] =
        NLPIDVersion2_B.VectorConcatenate[0];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[16] =
        NLPIDVersion2_B.VectorConcatenate[1];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[17] =
        NLPIDVersion2_B.VectorConcatenate[2];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[18] =
        NLPIDVersion2_P.PathSelector_Value;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[19] =
        NLPIDVersion2_B.Switch2;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[20] =
        NLPIDVersion2_B.Switch2_b;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[21] =
        NLPIDVersion2_B.Sum_pi;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[22] =
        NLPIDVersion2_P.u_dm_Value;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[23] =
        NLPIDVersion2_B.Divide_n;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[24] =
        NLPIDVersion2_B.Integrator1;
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[25] =
        NLPIDVersion2_P.ControlModeSelector_Value;
      for (i = 0; i < 7; i++) {
        NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[i + 26] =
          NLPIDVersion2_B.tauSwitch_m[i];
      }

      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[33] =
        NLPIDVersion2_B.tauSwitch[0];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[34] =
        NLPIDVersion2_B.tauSwitch[1];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[35] =
        NLPIDVersion2_B.tauSwitch[2];
      NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[36] = 0.0;

      /* ToFile Block: '<S22>/To File'
       */
      if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
        if (!(++NLPIDVersion2_DWork.ToFile_IWORK.Decimation % 1) &&
            (NLPIDVersion2_DWork.ToFile_IWORK.Count*38)+1 < 100000000 ) {
          real_T u[38];
          FILE *fp = (FILE *) NLPIDVersion2_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            NLPIDVersion2_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = NLPIDVersion2_M->Timing.t[1];
            u[1] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[13];
            u[15] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[14];
            u[16] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[15];
            u[17] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[16];
            u[18] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[17];
            u[19] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[18];
            u[20] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[19];
            u[21] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[20];
            u[22] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[21];
            u[23] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[22];
            u[24] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[23];
            u[25] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[24];
            u[26] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[25];
            u[27] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[26];
            u[28] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[27];
            u[29] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[28];
            u[30] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[29];
            u[31] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[30];
            u[32] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[31];
            u[33] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[32];
            u[34] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[33];
            u[35] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[34];
            u[36] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[35];
            u[37] = NLPIDVersion2_B.TmpHiddenBufferAtToFileInport1[36];
            if (fwrite(u, sizeof(real_T), 38, fp) != 38) {
              rtmSetErrorStatus(NLPIDVersion2_M,
                                "Error writing to MAT-file Template_data.mat");
              return;
            }

            if (((++NLPIDVersion2_DWork.ToFile_IWORK.Count)*38)+1 >= 100000000)
            {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file Template_data.mat.\n");
            }
          }
        }
      }

      /* Constant: '<S106>/0_2x1' */
      NLPIDVersion2_B.VectorConcatenate1[0] = NLPIDVersion2_P._2x1_Value_l[0];
      NLPIDVersion2_B.VectorConcatenate1[1] = NLPIDVersion2_P._2x1_Value_l[1];
    }

    /* SignalConversion: '<S106>/ConcatBufferAtVector Concatenate1In2' */
    NLPIDVersion2_B.VectorConcatenate1[2] = NLPIDVersion2_B.Subtract_b;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
    }

    /* Gain: '<S166>/QTM In1 FPS' */
    NLPIDVersion2_B.QTMIn1FPS = NLPIDVersion2_P.QTMIn1FPS_Gain *
      NLPIDVersion2_B.QTMIn[0];
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
    }

    /* Outputs for enable SubSystem: '<S25>/CSE1 actuator' incorporates:
     *  Constant: '<S1>/Enable CSE1'
     *  EnablePort: '<S169>/Enable'
     */
    if (rtmIsMajorTimeStep(NLPIDVersion2_M) && rtmIsMajorTimeStep
        (NLPIDVersion2_M)) {
      if (NLPIDVersion2_P.EnableCSE1_Value > 0.0) {
        if (NLPIDVersion2_DWork.CSE1actuator_MODE == SUBSYS_DISABLED) {
          NLPIDVersion2_DWork.CSE1actuator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (NLPIDVersion2_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
          NLPIDVersion2_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (NLPIDVersion2_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S173>/BT_D_Gain1' */
      NLPIDVersion2_B.BT_D_Gain1 = NLPIDVersion2_P.BT_D_Gain1_Gain *
        NLPIDVersion2_B.tauSwitch_m[4];

      /* Gain: '<S173>/BT_D_Gain2' */
      NLPIDVersion2_B.BT_D_Gain2 = NLPIDVersion2_P.BT_D_Gain2_Gain *
        NLPIDVersion2_B.tauSwitch_m[4];

      /* Sum: '<S173>/Add' incorporates:
       *  Constant: '<S173>/BT_Power_Offset1'
       */
      NLPIDVersion2_B.Add_e = (NLPIDVersion2_B.BT_D_Gain1 +
        NLPIDVersion2_P.BT_Power_Offset1_Value) + NLPIDVersion2_B.BT_D_Gain2;

      /* Gain: '<S173>/BT_L_Gain1' */
      NLPIDVersion2_B.BT_L_Gain1 = NLPIDVersion2_P.BT_L_Gain1_Gain *
        NLPIDVersion2_B.tauSwitch_m[5];

      /* Gain: '<S173>/BT_L_Gain2' */
      NLPIDVersion2_B.BT_L_Gain2 = NLPIDVersion2_P.BT_L_Gain2_Gain *
        NLPIDVersion2_B.tauSwitch_m[5];

      /* Gain: '<S173>/Neg' */
      NLPIDVersion2_B.Neg = NLPIDVersion2_P.Neg_Gain *
        NLPIDVersion2_B.tauSwitch_m[5];
      if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      }

      /* Sum: '<S173>/Sum1' incorporates:
       *  Constant: '<S173>/BT_Power_Offset2'
       */
      NLPIDVersion2_B.Sum1_cw = NLPIDVersion2_B.BT_L_Gain1 +
        NLPIDVersion2_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S175>/LowerRelop1' */
      NLPIDVersion2_B.LowerRelop1_j = (NLPIDVersion2_B.Add_e >
        NLPIDVersion2_B.Sum1_cw);

      /* Sum: '<S173>/Sum2' incorporates:
       *  Constant: '<S173>/BT_Power_Offset3'
       */
      NLPIDVersion2_B.Sum2_d = NLPIDVersion2_B.BT_L_Gain2 +
        NLPIDVersion2_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S175>/UpperRelop' */
      NLPIDVersion2_B.UpperRelop_f = (NLPIDVersion2_B.Add_e <
        NLPIDVersion2_B.Sum2_d);

      /* Switch: '<S175>/Switch' */
      if (NLPIDVersion2_B.UpperRelop_f) {
        NLPIDVersion2_B.Switch_k = NLPIDVersion2_B.Sum2_d;
      } else {
        NLPIDVersion2_B.Switch_k = NLPIDVersion2_B.Add_e;
      }

      /* Switch: '<S175>/Switch2' */
      if (NLPIDVersion2_B.LowerRelop1_j) {
        NLPIDVersion2_B.Switch2_o = NLPIDVersion2_B.Sum1_cw;
      } else {
        NLPIDVersion2_B.Switch2_o = NLPIDVersion2_B.Switch_k;
      }

      if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      }

      /* RelationalOperator: '<S176>/LowerRelop1' incorporates:
       *  Constant: '<S173>/Constant'
       */
      NLPIDVersion2_B.LowerRelop1_l = (NLPIDVersion2_B.tauSwitch_m[4] >
        NLPIDVersion2_P.Constant_Value_h);

      /* RelationalOperator: '<S176>/UpperRelop' */
      NLPIDVersion2_B.UpperRelop_b = (NLPIDVersion2_B.tauSwitch_m[4] <
        NLPIDVersion2_B.Neg);

      /* Switch: '<S176>/Switch' */
      if (NLPIDVersion2_B.UpperRelop_b) {
        NLPIDVersion2_B.Switch_g = NLPIDVersion2_B.Neg;
      } else {
        NLPIDVersion2_B.Switch_g = NLPIDVersion2_B.tauSwitch_m[4];
      }

      /* Switch: '<S176>/Switch2' incorporates:
       *  Constant: '<S173>/Constant'
       */
      if (NLPIDVersion2_B.LowerRelop1_l) {
        NLPIDVersion2_B.Switch2_n = NLPIDVersion2_P.Constant_Value_h;
      } else {
        NLPIDVersion2_B.Switch2_n = NLPIDVersion2_B.Switch_g;
      }

      if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      }

      /* RelationalOperator: '<S177>/LowerRelop1' */
      NLPIDVersion2_B.LowerRelop1_n = (NLPIDVersion2_B.tauSwitch_m[4] >
        NLPIDVersion2_B.tauSwitch_m[5]);

      /* RelationalOperator: '<S177>/UpperRelop' incorporates:
       *  Constant: '<S173>/Constant1'
       */
      NLPIDVersion2_B.UpperRelop_m = (NLPIDVersion2_B.tauSwitch_m[4] <
        NLPIDVersion2_P.Constant1_Value_i);

      /* Switch: '<S177>/Switch' incorporates:
       *  Constant: '<S173>/Constant1'
       */
      if (NLPIDVersion2_B.UpperRelop_m) {
        NLPIDVersion2_B.Switch_b = NLPIDVersion2_P.Constant1_Value_i;
      } else {
        NLPIDVersion2_B.Switch_b = NLPIDVersion2_B.tauSwitch_m[4];
      }

      /* Switch: '<S177>/Switch2' */
      if (NLPIDVersion2_B.LowerRelop1_n) {
        NLPIDVersion2_B.Switch2_g = NLPIDVersion2_B.tauSwitch_m[5];
      } else {
        NLPIDVersion2_B.Switch2_g = NLPIDVersion2_B.Switch_b;
      }

      /* Signum: '<S174>/Sign' */
      NLPIDVersion2_B.Sign_i = rt_SIGNd_snf(NLPIDVersion2_B.tauSwitch_m[6]);

      /* Product: '<S174>/Product1' */
      NLPIDVersion2_B.PortVPS_X = NLPIDVersion2_B.tauSwitch_m[1] *
        NLPIDVersion2_B.Sign_i;

      /* Gain: '<S174>/-x' */
      NLPIDVersion2_B.PortVPS_X_e = NLPIDVersion2_P.x_Gain *
        NLPIDVersion2_B.PortVPS_X;

      /* Product: '<S174>/Product2' */
      NLPIDVersion2_B.PortVSP_Y = NLPIDVersion2_B.tauSwitch_m[0] *
        NLPIDVersion2_B.Sign_i;

      /* Gain: '<S174>/-y' */
      NLPIDVersion2_B.PortVSP_Y_m = NLPIDVersion2_P.y_Gain *
        NLPIDVersion2_B.PortVSP_Y;

      /* Product: '<S174>/Product3' */
      NLPIDVersion2_B.StarboardVSP_X = NLPIDVersion2_B.tauSwitch_m[3] *
        NLPIDVersion2_B.Sign_i;

      /* Product: '<S174>/Product4' */
      NLPIDVersion2_B.StarboardVSP_Y = NLPIDVersion2_B.tauSwitch_m[2] *
        NLPIDVersion2_B.Sign_i;

      /* Lookup2D: '<S174>/Servo1' */
      NLPIDVersion2_B.Servo1 = rt_Lookup2D_Normal((const real_T *)
        (&NLPIDVersion2_P.Servo1_RowIdx[0]), 3, (const real_T *)
        (&NLPIDVersion2_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&NLPIDVersion2_P.Servo1_Table[0]), (const real_T)
        NLPIDVersion2_B.PortVPS_X_e, (const real_T)NLPIDVersion2_B.PortVSP_Y_m);

      /* Lookup2D: '<S174>/Servo2' */
      NLPIDVersion2_B.Servo2 = rt_Lookup2D_Normal((const real_T *)
        (&NLPIDVersion2_P.Servo2_RowIdx[0]), 3, (const real_T *)
        (&NLPIDVersion2_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&NLPIDVersion2_P.Servo2_Table[0]), (const real_T)
        NLPIDVersion2_B.PortVPS_X_e, (const real_T)NLPIDVersion2_B.PortVSP_Y_m);

      /* Lookup2D: '<S174>/Servo3' */
      NLPIDVersion2_B.Servo3 = rt_Lookup2D_Normal((const real_T *)
        (&NLPIDVersion2_P.Servo3_RowIdx[0]), 3, (const real_T *)
        (&NLPIDVersion2_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&NLPIDVersion2_P.Servo3_Table[0]), (const real_T)
        NLPIDVersion2_B.StarboardVSP_X, (const real_T)
        NLPIDVersion2_B.StarboardVSP_Y);

      /* Lookup2D: '<S174>/Servo4' */
      NLPIDVersion2_B.Servo4 = rt_Lookup2D_Normal((const real_T *)
        (&NLPIDVersion2_P.Servo4_RowIdx[0]), 3, (const real_T *)
        (&NLPIDVersion2_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&NLPIDVersion2_P.Servo4_Table[0]), (const real_T)
        NLPIDVersion2_B.StarboardVSP_X, (const real_T)
        NLPIDVersion2_B.StarboardVSP_Y);

      /* Gain: '<S174>/VPS_Speed_Gain' */
      NLPIDVersion2_B.VPS_Speed_Gain = NLPIDVersion2_P.VPS_Speed_Gain_Gain *
        NLPIDVersion2_B.tauSwitch_m[6];

      /* Sum: '<S174>/Sum' incorporates:
       *  Constant: '<S174>/VPS_Power_Offset'
       */
      NLPIDVersion2_B.Sum_c = NLPIDVersion2_B.VPS_Speed_Gain +
        NLPIDVersion2_P.VPS_Power_Offset_Value;

      /* Gain: '<S174>/VSPS Port' */
      NLPIDVersion2_B.VSPSPort = NLPIDVersion2_P.VSPSPort_Gain *
        NLPIDVersion2_B.Sum_c;

      /* Gain: '<S174>/VSPS Starboard' */
      NLPIDVersion2_B.VSPSStarboard = NLPIDVersion2_P.VSPSStarboard_Gain *
        NLPIDVersion2_B.Sum_c;
    }

    /* end of Outputs for SubSystem: '<S25>/CSE1 actuator' */
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Product Block: '<S25>/Inverse' */
      {
        static const int_T dims[3] = { 3, 3, 3 };

        rt_MatDivRR_Dbl(NLPIDVersion2_B.Inverse, NLPIDVersion2_B.x3,
                        &NLPIDVersion2_DWork.Inverse_DWORK4[0], (real_T*)
                        &NLPIDVersion2_DWork.Pseudoinverse_X[0],
                        &NLPIDVersion2_DWork.Inverse_DWORK2[0], (real_T*)
                        &NLPIDVersion2_DWork.Inverse_DWORK3[0],
                        &dims[0]);
      }
    }

    /* Saturate: '<S172>/Saturation' */
    tmp = NLPIDVersion2_B.tauSwitch[0];
    NLPIDVersion2_B.Saturation_ay = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation_LowerSat_pr,
      NLPIDVersion2_P.Saturation_UpperSat_ez);

    /* Saturate: '<S172>/Saturation1' */
    tmp = NLPIDVersion2_B.tauSwitch[1];
    NLPIDVersion2_B.Saturation1 = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation1_LowerSat, NLPIDVersion2_P.Saturation1_UpperSat);

    /* Saturate: '<S172>/Saturation2' */
    tmp = NLPIDVersion2_B.tauSwitch[2];
    NLPIDVersion2_B.Saturation2 = rt_SATURATE(tmp,
      NLPIDVersion2_P.Saturation2_LowerSat, NLPIDVersion2_P.Saturation2_UpperSat);

    /* Gain: '<S172>/plant tau_surge' */
    NLPIDVersion2_B.planttau_surge = NLPIDVersion2_P.planttau_surge_Gain *
      NLPIDVersion2_B.Saturation_ay;

    /* Gain: '<S172>/plant tau_sway' */
    NLPIDVersion2_B.planttau_sway = NLPIDVersion2_P.planttau_sway_Gain *
      NLPIDVersion2_B.Saturation1;

    /* Gain: '<S172>/plant tau_yaw' */
    NLPIDVersion2_B.planttau_yaw = NLPIDVersion2_P.planttau_yaw_Gain *
      NLPIDVersion2_B.Saturation2;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
      /* Gain: '<S180>/Battery Bow Thruster' */
      NLPIDVersion2_B.BatteryBowThruster =
        NLPIDVersion2_P.BatteryBowThruster_Gain * NLPIDVersion2_B.SITzAI0;

      /* Gain: '<S180>/Battery Main' */
      NLPIDVersion2_B.BatteryMain = NLPIDVersion2_P.BatteryMain_Gain *
        NLPIDVersion2_B.SITzAI2;

      /* Gain: '<S180>/Battery Servo' */
      NLPIDVersion2_B.BatteryServo = NLPIDVersion2_P.BatteryServo_Gain *
        NLPIDVersion2_B.SITzAI1;

      /* Gain: '<S181>/omega_qy' */
      NLPIDVersion2_B.omega_qy = NLPIDVersion2_P.omega_qy_Gain * 0.0;

      /* Gain: '<S181>/omegaqx' */
      NLPIDVersion2_B.omegaqx = NLPIDVersion2_P.omegaqx_Gain * 0.0;
    }

    /* Gain: '<S181>/plant BT power' */
    NLPIDVersion2_B.plantBTpower = NLPIDVersion2_P.plantBTpower_Gain *
      NLPIDVersion2_B.tauSwitch_m[5];

    /* Gain: '<S181>/plant VSP speed' */
    NLPIDVersion2_B.plantVSPspeed = NLPIDVersion2_P.plantVSPspeed_Gain *
      NLPIDVersion2_B.tauSwitch_m[6];

    /* Gain: '<S181>/plant u_1' */
    NLPIDVersion2_B.plantu_1 = NLPIDVersion2_P.plantu_1_Gain *
      NLPIDVersion2_B.tauSwitch_m[0];

    /* Gain: '<S181>/plant u_2' */
    NLPIDVersion2_B.plantu_2 = NLPIDVersion2_P.plantu_2_Gain *
      NLPIDVersion2_B.tauSwitch_m[1];

    /* Gain: '<S181>/plant u_3' */
    NLPIDVersion2_B.plantu_3 = NLPIDVersion2_P.plantu_3_Gain *
      NLPIDVersion2_B.tauSwitch_m[2];

    /* Gain: '<S181>/plant u_4' */
    NLPIDVersion2_B.plantu_4 = NLPIDVersion2_P.plantu_4_Gain *
      NLPIDVersion2_B.tauSwitch_m[3];

    /* Gain: '<S181>/plant u_5' */
    NLPIDVersion2_B.plantu_5 = NLPIDVersion2_P.plantu_5_Gain *
      NLPIDVersion2_B.tauSwitch_m[4];

    /* Gain: '<S181>/fact1' */
    NLPIDVersion2_B.fact1 = NLPIDVersion2_P.fact1_Gain *
      NLPIDVersion2_B.Product_m2[0];

    /* Gain: '<S181>/fact2' */
    NLPIDVersion2_B.fact2 = NLPIDVersion2_P.fact2_Gain *
      NLPIDVersion2_B.Product_m2[1];

    /* Gain: '<S181>/fact3' */
    NLPIDVersion2_B.fact3 = NLPIDVersion2_P.fact3_Gain *
      NLPIDVersion2_B.Product_m2[2];

    /* Gain: '<S181>/fact4' */
    NLPIDVersion2_B.fact4 = NLPIDVersion2_P.fact4_Gain *
      NLPIDVersion2_B.Product_m2[3];

    /* Gain: '<S181>/fact5' */
    NLPIDVersion2_B.fact5 = NLPIDVersion2_P.fact5_Gain *
      NLPIDVersion2_B.Product_m2[4];

    /* Gain: '<S181>/taux' */
    NLPIDVersion2_B.taux = NLPIDVersion2_P.taux_Gain *
      NLPIDVersion2_B.tauSwitch[0];

    /* Gain: '<S181>/tauy' */
    NLPIDVersion2_B.tauy = NLPIDVersion2_P.tauy_Gain *
      NLPIDVersion2_B.tauSwitch[1];

    /* Gain: '<S181>/tauyaw' */
    NLPIDVersion2_B.tauyaw = NLPIDVersion2_P.tauyaw_Gain *
      NLPIDVersion2_B.tauSwitch[2];

    /* Gain: '<S182>/CSE1_r [deg//s]' */
    NLPIDVersion2_B.CSE1_rdegs = NLPIDVersion2_P.CSE1_rdegs_Gain *
      NLPIDVersion2_B.nuSwitch[2];

    /* Gain: '<S182>/CSE1_u [m//s]' */
    NLPIDVersion2_B.CSE1_ums = NLPIDVersion2_P.CSE1_ums_Gain *
      NLPIDVersion2_B.nuSwitch[0];

    /* Gain: '<S182>/CSE1_v [m//s]' */
    NLPIDVersion2_B.CSE1_vms = NLPIDVersion2_P.CSE1_vms_Gain *
      NLPIDVersion2_B.nuSwitch[1];

    /* Sum: '<S183>/Sum' */
    NLPIDVersion2_B.Sum_fc[0] = NLPIDVersion2_B.etaSwitch[0] -
      NLPIDVersion2_B.Switch2;
    NLPIDVersion2_B.Sum_fc[1] = NLPIDVersion2_B.etaSwitch[1] -
      NLPIDVersion2_B.Switch2_b;
    NLPIDVersion2_B.Sum_fc[2] = NLPIDVersion2_B.etaSwitch[2] -
      NLPIDVersion2_B.Sum_pi;

    /* Sum: '<S183>/Sum1' */
    NLPIDVersion2_B.Sum1_nv[0] = NLPIDVersion2_B.VectorConcatenate[0] -
      NLPIDVersion2_B.Switch2;
    NLPIDVersion2_B.Sum1_nv[1] = NLPIDVersion2_B.VectorConcatenate[1] -
      NLPIDVersion2_B.Switch2_b;
    NLPIDVersion2_B.Sum1_nv[2] = NLPIDVersion2_B.VectorConcatenate[2] -
      NLPIDVersion2_B.Sum_pi;

    /* Sum: '<S183>/Sum2' */
    NLPIDVersion2_B.Sum2_o[0] = NLPIDVersion2_B.VectorConcatenate[0] -
      NLPIDVersion2_B.etaSwitch[0];
    NLPIDVersion2_B.Sum2_o[1] = NLPIDVersion2_B.VectorConcatenate[1] -
      NLPIDVersion2_B.etaSwitch[1];
    NLPIDVersion2_B.Sum2_o[2] = NLPIDVersion2_B.VectorConcatenate[2] -
      NLPIDVersion2_B.etaSwitch[2];

    /* Gain: '<S183>/psi [deg]' */
    NLPIDVersion2_B.psideg = NLPIDVersion2_P.psideg_Gain *
      NLPIDVersion2_B.etaSwitch[2];

    /* Gain: '<S183>/psi-psid [deg]' */
    NLPIDVersion2_B.psipsiddeg = NLPIDVersion2_P.psipsiddeg_Gain *
      NLPIDVersion2_B.Sum_fc[2];

    /* Gain: '<S183>/psiLOS-psi [deg]' */
    NLPIDVersion2_B.psiLOSpsideg = NLPIDVersion2_P.psiLOSpsideg_Gain *
      NLPIDVersion2_B.Sum2_o[2];

    /* Gain: '<S183>/psiLOS-psid [deg]' */
    NLPIDVersion2_B.psiLOSpsiddeg = NLPIDVersion2_P.psiLOSpsiddeg_Gain *
      NLPIDVersion2_B.Sum1_nv[2];

    /* Gain: '<S183>/psi_LOS [deg]' */
    NLPIDVersion2_B.psi_LOSdeg = NLPIDVersion2_P.psi_LOSdeg_Gain *
      NLPIDVersion2_B.VectorConcatenate[2];

    /* Gain: '<S183>/psid [deg]' */
    NLPIDVersion2_B.psiddeg = NLPIDVersion2_P.psiddeg_Gain *
      NLPIDVersion2_B.Sum_pi;

    /* Gain: '<S183>/psi_plot' */
    NLPIDVersion2_B.psi_plot[0] = NLPIDVersion2_P.psi_plot_Gain *
      NLPIDVersion2_B.psideg;
    NLPIDVersion2_B.psi_plot[1] = NLPIDVersion2_P.psi_plot_Gain *
      NLPIDVersion2_B.psi_LOSdeg;
    NLPIDVersion2_B.psi_plot[2] = NLPIDVersion2_P.psi_plot_Gain *
      NLPIDVersion2_B.psiddeg;

    /* Gain: '<S183>/qx [m]' */
    NLPIDVersion2_B.qxm = NLPIDVersion2_P.qxm_Gain *
      NLPIDVersion2_B.VectorConcatenate[0];

    /* Gain: '<S183>/qx-x [m]' */
    NLPIDVersion2_B.qxxm = NLPIDVersion2_P.qxxm_Gain * NLPIDVersion2_B.Sum2_o[0];

    /* Gain: '<S183>/qx-xd [m]1' */
    NLPIDVersion2_B.qxxdm1 = NLPIDVersion2_P.qxxdm1_Gain *
      NLPIDVersion2_B.Sum1_nv[0];

    /* Gain: '<S183>/qy [m]' */
    NLPIDVersion2_B.qym = NLPIDVersion2_P.qym_Gain *
      NLPIDVersion2_B.VectorConcatenate[1];

    /* Gain: '<S183>/qy-y [m]' */
    NLPIDVersion2_B.qyym = NLPIDVersion2_P.qyym_Gain * NLPIDVersion2_B.Sum2_o[1];

    /* Gain: '<S183>/qy-yd [m]1' */
    NLPIDVersion2_B.qyydm1 = NLPIDVersion2_P.qyydm1_Gain *
      NLPIDVersion2_B.Sum1_nv[1];

    /* Gain: '<S183>/x [m]' */
    NLPIDVersion2_B.xm = NLPIDVersion2_P.xm_Gain * NLPIDVersion2_B.etaSwitch[0];

    /* Gain: '<S183>/x-xd [m]' */
    NLPIDVersion2_B.xxdm = NLPIDVersion2_P.xxdm_Gain * NLPIDVersion2_B.Sum_fc[0];

    /* Gain: '<S183>/xd [m]' */
    NLPIDVersion2_B.xdm = NLPIDVersion2_P.xdm_Gain * NLPIDVersion2_B.Switch2;

    /* Gain: '<S183>/x_plot' */
    NLPIDVersion2_B.x_plot[0] = NLPIDVersion2_P.x_plot_Gain * NLPIDVersion2_B.xm;
    NLPIDVersion2_B.x_plot[1] = NLPIDVersion2_P.x_plot_Gain *
      NLPIDVersion2_B.qxm;
    NLPIDVersion2_B.x_plot[2] = NLPIDVersion2_P.x_plot_Gain *
      NLPIDVersion2_B.xdm;

    /* Gain: '<S183>/y [m]' */
    NLPIDVersion2_B.ym = NLPIDVersion2_P.ym_Gain * NLPIDVersion2_B.etaSwitch[1];

    /* Gain: '<S183>/y-yd [m]' */
    NLPIDVersion2_B.yydm = NLPIDVersion2_P.yydm_Gain * NLPIDVersion2_B.Sum_fc[1];

    /* Gain: '<S183>/yd [m]' */
    NLPIDVersion2_B.ydm = NLPIDVersion2_P.ydm_Gain * NLPIDVersion2_B.Switch2_b;

    /* Gain: '<S183>/y_plot' */
    NLPIDVersion2_B.y_plot[0] = NLPIDVersion2_P.y_plot_Gain * NLPIDVersion2_B.ym;
    NLPIDVersion2_B.y_plot[1] = NLPIDVersion2_P.y_plot_Gain *
      NLPIDVersion2_B.qym;
    NLPIDVersion2_B.y_plot[2] = NLPIDVersion2_P.y_plot_Gain *
      NLPIDVersion2_B.ydm;
    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void NLPIDVersion2_update(int_T tid)
{
  {
    int32_T tmp;

    /* Update for enable SubSystem: '<S25>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S170>/Enable'
     */
    if (NLPIDVersion2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S178>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        NLPIDVersion2_B.Product1_dk[tmp] = 0.0;
        NLPIDVersion2_B.Product1_dk[tmp] =
          NLPIDVersion2_B.LinearDampningmatrix[tmp] *
          NLPIDVersion2_B.Integrator_d[0] + NLPIDVersion2_B.Product1_dk[tmp];
        NLPIDVersion2_B.Product1_dk[tmp] =
          NLPIDVersion2_B.LinearDampningmatrix[tmp + 3] *
          NLPIDVersion2_B.Integrator_d[1] + NLPIDVersion2_B.Product1_dk[tmp];
        NLPIDVersion2_B.Product1_dk[tmp] =
          NLPIDVersion2_B.LinearDampningmatrix[tmp + 6] *
          NLPIDVersion2_B.Integrator_d[2] + NLPIDVersion2_B.Product1_dk[tmp];
      }

      /* Sum: '<S178>/Sum' */
      NLPIDVersion2_B.Sum_lb[0] = NLPIDVersion2_B.planttau_surge -
        NLPIDVersion2_B.Product1_dk[0];
      NLPIDVersion2_B.Sum_lb[1] = NLPIDVersion2_B.planttau_sway -
        NLPIDVersion2_B.Product1_dk[1];
      NLPIDVersion2_B.Sum_lb[2] = NLPIDVersion2_B.planttau_yaw -
        NLPIDVersion2_B.Product1_dk[2];

      /* Product: '<S178>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        NLPIDVersion2_B.Product2_ca[tmp] = 0.0;
        NLPIDVersion2_B.Product2_ca[tmp] = NLPIDVersion2_B.Inverse[tmp] *
          NLPIDVersion2_B.Sum_lb[0] + NLPIDVersion2_B.Product2_ca[tmp];
        NLPIDVersion2_B.Product2_ca[tmp] = NLPIDVersion2_B.Inverse[tmp + 3] *
          NLPIDVersion2_B.Sum_lb[1] + NLPIDVersion2_B.Product2_ca[tmp];
        NLPIDVersion2_B.Product2_ca[tmp] = NLPIDVersion2_B.Inverse[tmp + 6] *
          NLPIDVersion2_B.Sum_lb[2] + NLPIDVersion2_B.Product2_ca[tmp];
      }
    }

    /* end of Update for SubSystem: '<S25>/Linear Simulator' */

    /* Derivative Block: '<S166>/Derivative' */
    {
      real_T timeStampA = NLPIDVersion2_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = NLPIDVersion2_DWork.Derivative_RWORK.TimeStampB;
      real_T *lastBank = &NLPIDVersion2_DWork.Derivative_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = NLPIDVersion2_M->Timing.t[0];
      *lastBank++ = NLPIDVersion2_B.mm2mx;
      *lastBank++ = NLPIDVersion2_B.mm2my;
      *lastBank++ = NLPIDVersion2_B.mm2mz;
      *lastBank++ = NLPIDVersion2_B.d2rroll;
      *lastBank++ = NLPIDVersion2_B.d2rpitch;
      *lastBank++ = NLPIDVersion2_B.d2ryaw;
    }

    /* Derivative Block: '<S96>/Derivative' */
    {
      real_T timeStampA = NLPIDVersion2_DWork.Derivative_RWORK_g.TimeStampA;
      real_T timeStampB = NLPIDVersion2_DWork.Derivative_RWORK_g.TimeStampB;
      real_T *lastBank = &NLPIDVersion2_DWork.Derivative_RWORK_g.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 2;
        } else if (timeStampA >= timeStampB) {
          lastBank += 2;
        }
      }

      *lastBank++ = NLPIDVersion2_M->Timing.t[0];
      *lastBank++ = NLPIDVersion2_P.u_dm_Value;
    }

    /* Derivative Block: '<S166>/Derivative1' */
    {
      real_T timeStampA = NLPIDVersion2_DWork.Derivative1_RWORK.TimeStampA;
      real_T timeStampB = NLPIDVersion2_DWork.Derivative1_RWORK.TimeStampB;
      real_T *lastBank = &NLPIDVersion2_DWork.Derivative1_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 4;
        } else if (timeStampA >= timeStampB) {
          lastBank += 4;
        }
      }

      *lastBank++ = NLPIDVersion2_M->Timing.t[0];
      *lastBank++ = NLPIDVersion2_B.mm2mx;
      *lastBank++ = NLPIDVersion2_B.mm2my;
      *lastBank++ = NLPIDVersion2_B.d2ryaw;
    }

    if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
    }
  }

  if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
    rt_ertODEUpdateContinuousStates(&NLPIDVersion2_M->solverInfo);
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
  if (!(++NLPIDVersion2_M->Timing.clockTick0))
    ++NLPIDVersion2_M->Timing.clockTickH0;
  NLPIDVersion2_M->Timing.t[0] = NLPIDVersion2_M->Timing.clockTick0 *
    NLPIDVersion2_M->Timing.stepSize0 + NLPIDVersion2_M->Timing.clockTickH0 *
    NLPIDVersion2_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(NLPIDVersion2_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++NLPIDVersion2_M->Timing.clockTick1))
      ++NLPIDVersion2_M->Timing.clockTickH1;
    NLPIDVersion2_M->Timing.t[1] = NLPIDVersion2_M->Timing.clockTick1 *
      NLPIDVersion2_M->Timing.stepSize1 + NLPIDVersion2_M->Timing.clockTickH1 *
      NLPIDVersion2_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void NLPIDVersion2_derivatives(void)
{
  {
    int32_T tmp;

    /* Derivatives for enable SubSystem: '<S25>/Linear Simulator' */
    if (NLPIDVersion2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S178>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        NLPIDVersion2_B.Product1_dk[tmp] = 0.0;
        NLPIDVersion2_B.Product1_dk[tmp] =
          NLPIDVersion2_B.LinearDampningmatrix[tmp] *
          NLPIDVersion2_B.Integrator_d[0] + NLPIDVersion2_B.Product1_dk[tmp];
        NLPIDVersion2_B.Product1_dk[tmp] =
          NLPIDVersion2_B.LinearDampningmatrix[tmp + 3] *
          NLPIDVersion2_B.Integrator_d[1] + NLPIDVersion2_B.Product1_dk[tmp];
        NLPIDVersion2_B.Product1_dk[tmp] =
          NLPIDVersion2_B.LinearDampningmatrix[tmp + 6] *
          NLPIDVersion2_B.Integrator_d[2] + NLPIDVersion2_B.Product1_dk[tmp];
      }

      /* Sum: '<S178>/Sum' */
      NLPIDVersion2_B.Sum_lb[0] = NLPIDVersion2_B.planttau_surge -
        NLPIDVersion2_B.Product1_dk[0];
      NLPIDVersion2_B.Sum_lb[1] = NLPIDVersion2_B.planttau_sway -
        NLPIDVersion2_B.Product1_dk[1];
      NLPIDVersion2_B.Sum_lb[2] = NLPIDVersion2_B.planttau_yaw -
        NLPIDVersion2_B.Product1_dk[2];

      /* Product: '<S178>/Product2' */
      for (tmp = 0; tmp < 3; tmp++) {
        NLPIDVersion2_B.Product2_ca[tmp] = 0.0;
        NLPIDVersion2_B.Product2_ca[tmp] = NLPIDVersion2_B.Inverse[tmp] *
          NLPIDVersion2_B.Sum_lb[0] + NLPIDVersion2_B.Product2_ca[tmp];
        NLPIDVersion2_B.Product2_ca[tmp] = NLPIDVersion2_B.Inverse[tmp + 3] *
          NLPIDVersion2_B.Sum_lb[1] + NLPIDVersion2_B.Product2_ca[tmp];
        NLPIDVersion2_B.Product2_ca[tmp] = NLPIDVersion2_B.Inverse[tmp + 6] *
          NLPIDVersion2_B.Sum_lb[2] + NLPIDVersion2_B.Product2_ca[tmp];
      }

      /* Integrator Block: '<S178>/Integrator' */
      {
        if (NLPIDVersion2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator_CSTATE_d[0] = NLPIDVersion2_B.Product2_ca[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator_CSTATE_d[0] = 0.0;
        }

        if (NLPIDVersion2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator_CSTATE_d[1] = NLPIDVersion2_B.Product2_ca[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator_CSTATE_d[1] = 0.0;
        }

        if (NLPIDVersion2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator_CSTATE_d[2] = NLPIDVersion2_B.Product2_ca[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator_CSTATE_d[2] = 0.0;
        }
      }

      /* Integrator Block: '<S178>/Integrator1' */
      {
        if (NLPIDVersion2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator1_CSTATE_h[0] = NLPIDVersion2_B.Product3_mm[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator1_CSTATE_h[0] = 0.0;
        }

        if (NLPIDVersion2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator1_CSTATE_h[1] = NLPIDVersion2_B.Product3_mm[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator1_CSTATE_h[1] = 0.0;
        }

        if (NLPIDVersion2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator1_CSTATE_h[2] = NLPIDVersion2_B.Product3_mm[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs
            )->Integrator1_CSTATE_h[2] = 0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_NLPIDVersion2 *)
                NLPIDVersion2_M->ModelData.derivs)->Integrator_CSTATE_d[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S25>/Linear Simulator' */

    /* Integrator Block: '<S30>/Integrator' */
    {
      if (NLPIDVersion2_P.ctrl1ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE[0] =
          NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_e[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = 0.0;
      }

      if (NLPIDVersion2_P.ctrl1ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE[1] =
          NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_e[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = 0.0;
      }

      if (NLPIDVersion2_P.ctrl1ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE[2] =
          NLPIDVersion2_B.TmpHiddenBufferAtProductInpor_e[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE[2] = 0.0;
      }
    }

    /* Integrator Block: '<S41>/Integrator' */
    {
      if (NLPIDVersion2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_p[0] = NLPIDVersion2_B.Add1_f[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_p[0] = 0.0;
      }

      if (NLPIDVersion2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_p[1] = NLPIDVersion2_B.Add1_f[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_p[1] = 0.0;
      }
    }

    /* Integrator Block: '<S41>/Integrator1' */
    {
      if (NLPIDVersion2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator1_CSTATE = NLPIDVersion2_B.Subtract_a;
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator1_CSTATE = 0.0;
      }
    }

    /* Integrator Block: '<S46>/Integrator' */
    {
      if (NLPIDVersion2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_c[0] = NLPIDVersion2_B.Product_og[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_c[0] = 0.0;
      }

      if (NLPIDVersion2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_c[1] = NLPIDVersion2_B.Product_og[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_c[1] = 0.0;
      }

      if (NLPIDVersion2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_c[2] = NLPIDVersion2_B.Product_og[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator_CSTATE_c[2] = 0.0;
      }
    }

    /* Integrator Block: '<S41>/Integrator2' */
    {
      if (NLPIDVersion2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = NLPIDVersion2_B.Gain_pp[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = 0.0;
      }

      if (NLPIDVersion2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = NLPIDVersion2_B.Gain_pp[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_NLPIDVersion2 *) NLPIDVersion2_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = 0.0;
      }
    }
  }
}

/* Model initialize function */
void NLPIDVersion2_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)NLPIDVersion2_M,0,
                sizeof(RT_MODEL_NLPIDVersion2));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&NLPIDVersion2_M->solverInfo,
                          &NLPIDVersion2_M->Timing.simTimeStep);
    rtsiSetTPtr(&NLPIDVersion2_M->solverInfo, &rtmGetTPtr(NLPIDVersion2_M));
    rtsiSetStepSizePtr(&NLPIDVersion2_M->solverInfo,
                       &NLPIDVersion2_M->Timing.stepSize0);
    rtsiSetdXPtr(&NLPIDVersion2_M->solverInfo,
                 &NLPIDVersion2_M->ModelData.derivs);
    rtsiSetContStatesPtr(&NLPIDVersion2_M->solverInfo,
                         &NLPIDVersion2_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&NLPIDVersion2_M->solverInfo,
      &NLPIDVersion2_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&NLPIDVersion2_M->solverInfo, (&rtmGetErrorStatus
      (NLPIDVersion2_M)));
    rtsiSetRTModelPtr(&NLPIDVersion2_M->solverInfo, NLPIDVersion2_M);
  }

  rtsiSetSimTimeStep(&NLPIDVersion2_M->solverInfo, MAJOR_TIME_STEP);
  NLPIDVersion2_M->ModelData.intgData.y = NLPIDVersion2_M->ModelData.odeY;
  NLPIDVersion2_M->ModelData.intgData.f[0] = NLPIDVersion2_M->ModelData.odeF[0];
  NLPIDVersion2_M->ModelData.intgData.f[1] = NLPIDVersion2_M->ModelData.odeF[1];
  NLPIDVersion2_M->ModelData.intgData.f[2] = NLPIDVersion2_M->ModelData.odeF[2];
  NLPIDVersion2_M->ModelData.intgData.f[3] = NLPIDVersion2_M->ModelData.odeF[3];
  NLPIDVersion2_M->ModelData.intgData.f[4] = NLPIDVersion2_M->ModelData.odeF[4];
  NLPIDVersion2_M->ModelData.intgData.f[5] = NLPIDVersion2_M->ModelData.odeF[5];
  NLPIDVersion2_M->ModelData.contStates = ((real_T *) &NLPIDVersion2_X);
  rtsiSetSolverData(&NLPIDVersion2_M->solverInfo, (void *)
                    &NLPIDVersion2_M->ModelData.intgData);
  rtsiSetSolverName(&NLPIDVersion2_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = NLPIDVersion2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    NLPIDVersion2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    NLPIDVersion2_M->Timing.sampleTimes =
      (&NLPIDVersion2_M->Timing.sampleTimesArray[0]);
    NLPIDVersion2_M->Timing.offsetTimes =
      (&NLPIDVersion2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    NLPIDVersion2_M->Timing.sampleTimes[0] = (0.0);
    NLPIDVersion2_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    NLPIDVersion2_M->Timing.offsetTimes[0] = (0.0);
    NLPIDVersion2_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(NLPIDVersion2_M, &NLPIDVersion2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = NLPIDVersion2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    NLPIDVersion2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(NLPIDVersion2_M, -1);
  NLPIDVersion2_M->Timing.stepSize0 = 0.1;
  NLPIDVersion2_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(NLPIDVersion2_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    NLPIDVersion2_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(NLPIDVersion2_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(NLPIDVersion2_M->rtwLogInfo, (NULL));
    rtliSetLogT(NLPIDVersion2_M->rtwLogInfo, "");
    rtliSetLogX(NLPIDVersion2_M->rtwLogInfo, "");
    rtliSetLogXFinal(NLPIDVersion2_M->rtwLogInfo, "");
    rtliSetSigLog(NLPIDVersion2_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(NLPIDVersion2_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(NLPIDVersion2_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(NLPIDVersion2_M->rtwLogInfo, 0);
    rtliSetLogDecimation(NLPIDVersion2_M->rtwLogInfo, 1);
    rtliSetLogY(NLPIDVersion2_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(NLPIDVersion2_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(NLPIDVersion2_M->rtwLogInfo, (NULL));
  }

  NLPIDVersion2_M->solverInfoPtr = (&NLPIDVersion2_M->solverInfo);
  NLPIDVersion2_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&NLPIDVersion2_M->solverInfo, 0.1);
  rtsiSetSolverMode(&NLPIDVersion2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  NLPIDVersion2_M->ModelData.blockIO = ((void *) &NLPIDVersion2_B);
  (void) memset(((void *) &NLPIDVersion2_B),0,
                sizeof(BlockIO_NLPIDVersion2));

  /* parameters */
  NLPIDVersion2_M->ModelData.defaultParam = ((real_T *) &NLPIDVersion2_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &NLPIDVersion2_X;
    NLPIDVersion2_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_NLPIDVersion2));
  }

  /* states (dwork) */
  NLPIDVersion2_M->Work.dwork = ((void *) &NLPIDVersion2_DWork);
  (void) memset((void *)&NLPIDVersion2_DWork, 0,
                sizeof(D_Work_NLPIDVersion2));
  NLPIDVersion2_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  NLPIDVersion2_PrevZCSigState.Integrator_Reset_ZCE_j = UNINITIALIZED_ZCSIG;
  NLPIDVersion2_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  NLPIDVersion2_PrevZCSigState.Integrator_Reset_ZCE_l = UNINITIALIZED_ZCSIG;
  NLPIDVersion2_PrevZCSigState.Integrator2_Reset_ZCE = UNINITIALIZED_ZCSIG;
  NLPIDVersion2_PrevZCSigState.Integrator_Reset_ZCE_f = UNINITIALIZED_ZCSIG;
  NLPIDVersion2_PrevZCSigState.Integrator1_Reset_ZCE_j = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void NLPIDVersion2_terminate(void)
{
  /* ToFile Block: '<S22>/To File' */
  {
    FILE *fp = (FILE *) NLPIDVersion2_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "Template_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(NLPIDVersion2_M,
                          "Error closing MAT-file Template_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(NLPIDVersion2_M,
                          "Error reopening MAT-file Template_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 38, NLPIDVersion2_DWork.ToFile_IWORK.Count,
           "Template_data")) {
        rtmSetErrorStatus(NLPIDVersion2_M,
                          "Error writing header for Template_data to MAT-file Template_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(NLPIDVersion2_M,
                          "Error closing MAT-file Template_data.mat");
        return;
      }

      NLPIDVersion2_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  NLPIDVersion2_output(tid);
}

void MdlUpdate(int_T tid)
{
  NLPIDVersion2_update(tid);
}

void MdlInitializeSizes(void)
{
  NLPIDVersion2_M->Sizes.numContStates = (17);/* Number of continuous states */
  NLPIDVersion2_M->Sizes.numY = (0);   /* Number of model outputs */
  NLPIDVersion2_M->Sizes.numU = (0);   /* Number of model inputs */
  NLPIDVersion2_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  NLPIDVersion2_M->Sizes.numSampTimes = (2);/* Number of sample times */
  NLPIDVersion2_M->Sizes.numBlocks = (857);/* Number of blocks */
  NLPIDVersion2_M->Sizes.numBlockIO = (610);/* Number of block outputs */
  NLPIDVersion2_M->Sizes.numBlockPrms = (1012);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* Integrator Block: '<S30>/Integrator' */
  NLPIDVersion2_X.Integrator_CSTATE[0] = NLPIDVersion2_P.Integrator_IC;
  NLPIDVersion2_X.Integrator_CSTATE[1] = NLPIDVersion2_P.Integrator_IC;
  NLPIDVersion2_X.Integrator_CSTATE[2] = NLPIDVersion2_P.Integrator_IC;

  /* Derivative Block: '<S166>/Derivative' */
  NLPIDVersion2_DWork.Derivative_RWORK.TimeStampA = rtInf;
  NLPIDVersion2_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* Integrator Block: '<S41>/Integrator' */
  if (rtmIsFirstInitCond(NLPIDVersion2_M)) {
    NLPIDVersion2_X.Integrator_CSTATE_p[0] = 0.0;
    NLPIDVersion2_X.Integrator_CSTATE_p[1] = 0.0;
  }

  NLPIDVersion2_DWork.Integrator_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S41>/Integrator1' */
  if (rtmIsFirstInitCond(NLPIDVersion2_M)) {
    NLPIDVersion2_X.Integrator1_CSTATE = 0.0;
  }

  NLPIDVersion2_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S46>/Integrator' */
  NLPIDVersion2_X.Integrator_CSTATE_c[0] = NLPIDVersion2_P.Integrator_IC_g[0];
  NLPIDVersion2_X.Integrator_CSTATE_c[1] = NLPIDVersion2_P.Integrator_IC_g[1];
  NLPIDVersion2_X.Integrator_CSTATE_c[2] = NLPIDVersion2_P.Integrator_IC_g[2];

  /* Integrator Block: '<S41>/Integrator2' */
  NLPIDVersion2_X.Integrator2_CSTATE[0] = NLPIDVersion2_P.Integrator2_IC;
  NLPIDVersion2_X.Integrator2_CSTATE[1] = NLPIDVersion2_P.Integrator2_IC;

  /* Derivative Block: '<S96>/Derivative' */
  NLPIDVersion2_DWork.Derivative_RWORK_g.TimeStampA = rtInf;
  NLPIDVersion2_DWork.Derivative_RWORK_g.TimeStampB = rtInf;

  /* Derivative Block: '<S166>/Derivative1' */
  NLPIDVersion2_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  NLPIDVersion2_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(NLPIDVersion2_M)) {
    rtmSetFirstInitCond(NLPIDVersion2_M, 0);
  }
}

void MdlStart(void)
{
  /* Start for Constant: '<S4>/Initial psi [rad]' */
  NLPIDVersion2_B.Initialpsirad = NLPIDVersion2_P.Initialpsirad_Value;

  /* Start for Constant: '<S4>/Initial x [m]' */
  NLPIDVersion2_B.Initialxm = NLPIDVersion2_P.Initialxm_Value;

  /* Start for Constant: '<S4>/Initial y [m]' */
  NLPIDVersion2_B.Initialym = NLPIDVersion2_P.Initialym_Value;

  /* Start for Constant: '<S4>/Initial r [rad//s]' */
  NLPIDVersion2_B.Initialrrads = NLPIDVersion2_P.Initialrrads_Value;

  /* Start for Constant: '<S4>/Initial u [m//s]' */
  NLPIDVersion2_B.Initialums = NLPIDVersion2_P.Initialums_Value;

  /* Start for Constant: '<S4>/Initial v [m//s]' */
  NLPIDVersion2_B.Initialvms = NLPIDVersion2_P.Initialvms_Value;

  /* Start for Constant: '<S9>/Initial q_x' */
  NLPIDVersion2_B.Initialq_x = NLPIDVersion2_P.Initialq_x_Value;

  /* Start for Constant: '<S9>/Initial q_y' */
  NLPIDVersion2_B.Initialq_y = NLPIDVersion2_P.Initialq_y_Value;

  /* Start for Constant: '<S9>/Initial s' */
  NLPIDVersion2_B.Initials = NLPIDVersion2_P.Initials_Value;

  /* Start for enable SubSystem: '<S25>/Linear Simulator' */
  NLPIDVersion2_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

  /* Integrator Block: '<S178>/Integrator' */
  if (rtmIsFirstInitCond(NLPIDVersion2_M)) {
    NLPIDVersion2_X.Integrator_CSTATE_d[0] = 0.0;
    NLPIDVersion2_X.Integrator_CSTATE_d[1] = 0.0;
    NLPIDVersion2_X.Integrator_CSTATE_d[2] = 0.0;
  }

  NLPIDVersion2_DWork.Integrator_IWORK_c.IcNeedsLoading = 1;

  /* Integrator Block: '<S178>/Integrator1' */
  if (rtmIsFirstInitCond(NLPIDVersion2_M)) {
    NLPIDVersion2_X.Integrator1_CSTATE_h[0] = 0.0;
    NLPIDVersion2_X.Integrator1_CSTATE_h[1] = 0.0;
    NLPIDVersion2_X.Integrator1_CSTATE_h[2] = 0.0;
  }

  NLPIDVersion2_DWork.Integrator1_IWORK_b.IcNeedsLoading = 1;

  /* end of Start for SubSystem: '<S25>/Linear Simulator' */

  /* ToFile Block: '<S22>/To File' */
  {
    const char *fileName = "Template_data.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(NLPIDVersion2_M,
                        "Error creating .mat file Template_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,38,0,"Template_data")) {
      rtmSetErrorStatus(NLPIDVersion2_M,
                        "Error writing mat file header to file Template_data.mat");
      return;
    }

    NLPIDVersion2_DWork.ToFile_IWORK.Count = 0;
    NLPIDVersion2_DWork.ToFile_IWORK.Decimation = -1;
    NLPIDVersion2_DWork.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for enable SubSystem: '<S25>/CSE1 actuator' */
  NLPIDVersion2_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;

  /* end of Start for SubSystem: '<S25>/CSE1 actuator' */

  /* Create Identity Matrix for Block: '<S25>/Inverse' */
  {
    int_T i;
    real_T *dWork = &NLPIDVersion2_DWork.Inverse_DWORK4[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &NLPIDVersion2_DWork.Inverse_DWORK4[0];
    while (dWork < &NLPIDVersion2_DWork.Inverse_DWORK4[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  MdlInitialize();
}

RT_MODEL_NLPIDVersion2 *NLPIDVersion2(void)
{
  NLPIDVersion2_initialize(1);
  return NLPIDVersion2_M;
}

void MdlTerminate(void)
{
  NLPIDVersion2_terminate();
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
#ifdef NI_ROOTMODEL_NLPIDVersion2
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
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 38:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,15,Complex);

   case 39:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,10,Complex);

   case 45:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,11,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 53:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 62:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 63:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 64:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 82:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 83:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 84:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 38:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,15,Complex);

   case 39:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,10,Complex);

   case 45:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,11,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 53:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 62:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 63:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 64:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 82:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 83:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 84:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern NLPIDVersion2_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Main Subsystems/Naviagation/Input from SIT/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(NLPIDVersion2_B.QTMIn, count, data[index++], 46, 0);
    }
  } else {
    index += 9;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&NLPIDVersion2_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&NLPIDVersion2_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&NLPIDVersion2_B.SITzAI2, 0, data[index++], 0, 0);
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

  // Main Subsystems/Plant/CSE1 actuator/Bow Thruster/SIT PWM0 BT: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Switch2_o,0,0,
      0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.VSPSStarboard,
      0,0,0);
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

  // Main Subsystems/Plant/CSE1 actuator/Bow Thruster/SIT PWM0 BT: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Switch2_o,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Servo1,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Servo2,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Servo3,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.Servo4,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.VSPSPort,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&NLPIDVersion2_B.VSPSStarboard,0,
    0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "nlpidversion2/Inputs from LabVIEW/Control Input Selector/Value",
    offsetof(Parameters_NLPIDVersion2, ControlInputSelector_Value), 31, 1, 2, 0,
    "", 0 },

  { 1, "nlpidversion2/Inputs from LabVIEW/Control Mode Selector/Value", offsetof
    (Parameters_NLPIDVersion2, ControlModeSelector_Value), 31, 1, 2, 2, "", 0 },

  { 2, "nlpidversion2/Inputs from LabVIEW/Enable CSE1/Value", offsetof
    (Parameters_NLPIDVersion2, EnableCSE1_Value), 31, 1, 2, 4, "", 0 },

  { 3,
    "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value",
    offsetof(Parameters_NLPIDVersion2, EnableLinearSimulator_Value), 31, 1, 2, 6,
    "", 0 },

  { 4,
    "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value",
    offsetof(Parameters_NLPIDVersion2, Initialpsirad_Value), 31, 1, 2, 8, "", 0
  },

  { 5, "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value",
    offsetof(Parameters_NLPIDVersion2, Initialxm_Value), 31, 1, 2, 10, "", 0 },

  { 6, "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value",
    offsetof(Parameters_NLPIDVersion2, Initialym_Value), 31, 1, 2, 12, "", 0 },

  { 7,
    "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value",
    offsetof(Parameters_NLPIDVersion2, Initialrrads_Value), 31, 1, 2, 14, "", 0
  },

  { 8,
    "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value",
    offsetof(Parameters_NLPIDVersion2, Initialums_Value), 31, 1, 2, 16, "", 0 },

  { 9,
    "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value",
    offsetof(Parameters_NLPIDVersion2, Initialvms_Value), 31, 1, 2, 18, "", 0 },

  { 10,
    "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_NLPIDVersion2, ResetLinearSimulatorintegrator_), 31, 1,
    2, 20, "", 0 },

  { 11, "nlpidversion2/Inputs from LabVIEW/Path/Delta [m]/Value", offsetof
    (Parameters_NLPIDVersion2, Deltam_Value), 31, 1, 2, 22, "", 0 },

  { 12, "nlpidversion2/Inputs from LabVIEW/Path/Path Selector  [-]/Value",
    offsetof(Parameters_NLPIDVersion2, PathSelector_Value), 31, 1, 2, 24, "", 0
  },

  { 13, "nlpidversion2/Inputs from LabVIEW/Path/my [-]/Value", offsetof
    (Parameters_NLPIDVersion2, my_Value), 31, 1, 2, 26, "", 0 },

  { 14, "nlpidversion2/Inputs from LabVIEW/Path/u_d [m]/Value", offsetof
    (Parameters_NLPIDVersion2, u_dm_Value), 31, 1, 2, 28, "", 0 },

  { 15, "nlpidversion2/Inputs from LabVIEW/Path/x_dmax [m]/Value", offsetof
    (Parameters_NLPIDVersion2, x_dmaxm_Value), 31, 1, 2, 30, "", 0 },

  { 16, "nlpidversion2/Inputs from LabVIEW/Path/x_dmin [m]/Value", offsetof
    (Parameters_NLPIDVersion2, x_dminm_Value), 31, 1, 2, 32, "", 0 },

  { 17, "nlpidversion2/Inputs from LabVIEW/Path/y_dmax [m]/Value", offsetof
    (Parameters_NLPIDVersion2, y_dmaxm_Value), 31, 1, 2, 34, "", 0 },

  { 18, "nlpidversion2/Inputs from LabVIEW/Path/y_dmin [m]/Value", offsetof
    (Parameters_NLPIDVersion2, y_dminm_Value), 31, 1, 2, 36, "", 0 },

  { 19, "nlpidversion2/Inputs from LabVIEW/Path/Ellipse/k [-]/Value", offsetof
    (Parameters_NLPIDVersion2, k_Value), 31, 1, 2, 38, "", 0 },

  { 20, "nlpidversion2/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value", offsetof
    (Parameters_NLPIDVersion2, r_xm_Value), 31, 1, 2, 40, "", 0 },

  { 21, "nlpidversion2/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value", offsetof
    (Parameters_NLPIDVersion2, r_ym_Value), 31, 1, 2, 42, "", 0 },

  { 22, "nlpidversion2/Inputs from LabVIEW/Path/Ellipse/x_0 [m]/Value", offsetof
    (Parameters_NLPIDVersion2, x_0m_Value), 31, 1, 2, 44, "", 0 },

  { 23, "nlpidversion2/Inputs from LabVIEW/Path/Ellipse/y_0 [m]/Value", offsetof
    (Parameters_NLPIDVersion2, y_0m_Value), 31, 1, 2, 46, "", 0 },

  { 24, "nlpidversion2/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value", offsetof
    (Parameters_NLPIDVersion2, x_1m_Value), 31, 1, 2, 48, "", 0 },

  { 25, "nlpidversion2/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value", offsetof
    (Parameters_NLPIDVersion2, x_2m_Value), 31, 1, 2, 50, "", 0 },

  { 26, "nlpidversion2/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value", offsetof
    (Parameters_NLPIDVersion2, y_1m_Value), 31, 1, 2, 52, "", 0 },

  { 27, "nlpidversion2/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value", offsetof
    (Parameters_NLPIDVersion2, y_2m_Value), 31, 1, 2, 54, "", 0 },

  { 28, "nlpidversion2/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value",
    offsetof(Parameters_NLPIDVersion2, AS_LX_Value), 31, 1, 2, 56, "", 0 },

  { 29, "nlpidversion2/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain",
    offsetof(Parameters_NLPIDVersion2, ScalingLX_Gain), 31, 1, 2, 58, "", 0 },

  { 30, "nlpidversion2/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value",
    offsetof(Parameters_NLPIDVersion2, AS_LY_Value), 31, 1, 2, 60, "", 0 },

  { 31, "nlpidversion2/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain",
    offsetof(Parameters_NLPIDVersion2, ScalingLY_Gain), 31, 1, 2, 62, "", 0 },

  { 32, "nlpidversion2/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value",
    offsetof(Parameters_NLPIDVersion2, AS_RX_Value), 31, 1, 2, 64, "", 0 },

  { 33, "nlpidversion2/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain",
    offsetof(Parameters_NLPIDVersion2, Scaling_RX_Gain), 31, 1, 2, 66, "", 0 },

  { 34, "nlpidversion2/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value",
    offsetof(Parameters_NLPIDVersion2, AS_RY_Value), 31, 1, 2, 68, "", 0 },

  { 35, "nlpidversion2/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain",
    offsetof(Parameters_NLPIDVersion2, ScalingRY_Gain), 31, 1, 2, 70, "", 0 },

  { 36, "nlpidversion2/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value",
    offsetof(Parameters_NLPIDVersion2, PS3_BT_Power_Value), 31, 1, 2, 72, "", 0
  },

  { 37, "nlpidversion2/Inputs from LabVIEW/PlayStation3/L2 [-]/Value", offsetof
    (Parameters_NLPIDVersion2, L2_Value), 31, 1, 2, 74, "", 0 },

  { 38,
    "nlpidversion2/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value",
    offsetof(Parameters_NLPIDVersion2, PS3_VSP_Speed_Value), 31, 1, 2, 76, "", 0
  },

  { 39, "nlpidversion2/Inputs from LabVIEW/PlayStation3/R2 [-]/Value", offsetof
    (Parameters_NLPIDVersion2, R2_Value), 31, 1, 2, 78, "", 0 },

  { 40, "nlpidversion2/Inputs from LabVIEW/Setpoint/setpointpsi [deg]/Value",
    offsetof(Parameters_NLPIDVersion2, setpointpsideg_Value), 31, 1, 2, 80, "",
    0 },

  { 41,
    "nlpidversion2/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain1_Gain), 31, 1, 2, 82, "", 0 },

  { 42, "nlpidversion2/Inputs from LabVIEW/Setpoint/setpointx [m]/Value",
    offsetof(Parameters_NLPIDVersion2, setpointxm_Value), 31, 1, 2, 84, "", 0 },

  { 43, "nlpidversion2/Inputs from LabVIEW/Setpoint/setpointy [m]/Value",
    offsetof(Parameters_NLPIDVersion2, setpointym_Value), 31, 1, 2, 86, "", 0 },

  { 44,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/12/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value), 31, 1, 2, 88, "", 0 },

  { 45,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/13/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_k), 31, 1, 2, 90, "", 0 },

  { 46,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/21/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_k0), 31, 1, 2, 92, "", 0 },

  { 47,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/23/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_j), 31, 1, 2, 94, "", 0 },

  { 48,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/31/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_o), 31, 1, 2, 96, "", 0 },

  { 49,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/32/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_oz), 31, 1, 2, 98, "", 0 },

  { 50,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kdx/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1Kdx_Value), 31, 1, 2, 100, "", 0 },

  { 51,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kdy/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1Kdy_Value), 31, 1, 2, 102, "", 0 },

  { 52,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kdpsi/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1Kdpsi_Value), 31, 1, 2, 104, "", 0 },

  { 53,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/12/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_a), 31, 1, 2, 106, "", 0 },

  { 54,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/13/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_e), 31, 1, 2, 108, "", 0 },

  { 55,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/21/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_b), 31, 1, 2, 110, "", 0 },

  { 56,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/23/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_f), 31, 1, 2, 112, "", 0 },

  { 57,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/31/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_m), 31, 1, 2, 114, "", 0 },

  { 58,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/32/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_ea), 31, 1, 2, 116, "", 0 },

  { 59,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kix/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1Kix_Value), 31, 1, 2, 118, "", 0 },

  { 60,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kiy/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1Kiy_Value), 31, 1, 2, 120, "", 0 },

  { 61,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kipsi/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1Kipsi_Value), 31, 1, 2, 122, "", 0 },

  { 62,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/12/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_et), 31, 1, 2, 124, "", 0 },

  { 63,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/13/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_c), 31, 1, 2, 126, "", 0 },

  { 64,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/21/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_b4), 31, 1, 2, 128, "", 0 },

  { 65,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/23/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_n), 31, 1, 2, 130, "", 0 },

  { 66,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/31/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_i), 31, 1, 2, 132, "", 0 },

  { 67,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/32/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_aw), 31, 1, 2, 134, "", 0 },

  { 68,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kpx/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1Kpx_Value), 31, 1, 2, 136, "", 0 },

  { 69,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kpy/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1Kpy_Value), 31, 1, 2, 138, "", 0 },

  { 70,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kppsi/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1Kppsi_Value), 31, 1, 2, 140, "", 0 },

  { 71,
    "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1 Reset Integrator/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl1ResetIntegrator_Value), 31, 1, 2,
    142, "", 0 },

  { 72,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q/12/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_p), 31, 1, 2, 144, "", 0 },

  { 73,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q/21/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_kp), 31, 1, 2, 146, "", 0 },

  { 74,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q_Surge/Value",
    offsetof(Parameters_NLPIDVersion2, Gamma_q_Surge_Value), 31, 1, 2, 148, "",
    0 },

  { 75,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q_Sway/Value",
    offsetof(Parameters_NLPIDVersion2, Gamma_q_Sway_Value), 31, 1, 2, 150, "", 0
  },

  { 76,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Initial q_x/Value",
    offsetof(Parameters_NLPIDVersion2, Initialq_x_Value), 31, 1, 2, 152, "", 0 },

  { 77,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Initial q_y/Value",
    offsetof(Parameters_NLPIDVersion2, Initialq_y_Value), 31, 1, 2, 154, "", 0 },

  { 78,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Initial s/Value",
    offsetof(Parameters_NLPIDVersion2, Initials_Value), 31, 1, 2, 156, "", 0 },

  { 79,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/12/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_l), 31, 1, 2, 158, "", 0 },

  { 80,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/13/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_h), 31, 1, 2, 160, "", 0 },

  { 81,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/21/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_fr), 31, 1, 2, 162, "", 0 },

  { 82,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/23/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_hr), 31, 1, 2, 164, "", 0 },

  { 83,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/31/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_ka), 31, 1, 2, 166, "", 0 },

  { 84,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/32/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_hp), 31, 1, 2, 168, "", 0 },

  { 85,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kdx/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2Kdx_Value), 31, 1, 2, 170, "", 0 },

  { 86,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kdy/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2Kdy_Value), 31, 1, 2, 172, "", 0 },

  { 87,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kdpsi/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2Kdpsi_Value), 31, 1, 2, 174, "", 0 },

  { 88,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/12/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_bm), 31, 1, 2, 176, "", 0 },

  { 89,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/13/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_li), 31, 1, 2, 178, "", 0 },

  { 90,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/21/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_nj), 31, 1, 2, 180, "", 0 },

  { 91,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/23/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_fn), 31, 1, 2, 182, "", 0 },

  { 92,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/31/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_ho), 31, 1, 2, 184, "", 0 },

  { 93,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/32/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_cj), 31, 1, 2, 186, "", 0 },

  { 94,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kix/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2Kix_Value), 31, 1, 2, 188, "", 0 },

  { 95,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kiy/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2Kiy_Value), 31, 1, 2, 190, "", 0 },

  { 96,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kipsi/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2Kipsi_Value), 31, 1, 2, 192, "", 0 },

  { 97,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/12/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_pl), 31, 1, 2, 194, "", 0 },

  { 98,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/13/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_jh), 31, 1, 2, 196, "", 0 },

  { 99,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/21/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_aq), 31, 1, 2, 198, "", 0 },

  { 100,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/23/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_fe), 31, 1, 2, 200, "", 0 },

  { 101,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/31/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_fv), 31, 1, 2, 202, "", 0 },

  { 102,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/32/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_h3), 31, 1, 2, 204, "", 0 },

  { 103,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kpx/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2Kpx_Value), 31, 1, 2, 206, "", 0 },

  { 104,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kpy/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2Kpy_Value), 31, 1, 2, 208, "", 0 },

  { 105,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kppsi/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2Kppsi_Value), 31, 1, 2, 210, "", 0 },

  { 106,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2 Reset Integrator/Value",
    offsetof(Parameters_NLPIDVersion2, ctrl2ResetIntegrator_Value), 31, 1, 2,
    212, "", 0 },

  { 107,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/kappa_1/Value",
    offsetof(Parameters_NLPIDVersion2, kappa_1_Value), 31, 1, 2, 214, "", 0 },

  { 108,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/lambda_q/Value",
    offsetof(Parameters_NLPIDVersion2, lambda_q_Value), 31, 1, 2, 216, "", 0 },

  { 109,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value",
    offsetof(Parameters_NLPIDVersion2, l_x1_Value), 31, 1, 2, 218, "", 0 },

  { 110,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain",
    offsetof(Parameters_NLPIDVersion2, l_x1_Gain), 31, 1, 2, 220, "", 0 },

  { 111,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value",
    offsetof(Parameters_NLPIDVersion2, l_x2_Value), 31, 1, 2, 222, "", 0 },

  { 112,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain",
    offsetof(Parameters_NLPIDVersion2, l_x2_Gain), 31, 1, 2, 224, "", 0 },

  { 113,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value",
    offsetof(Parameters_NLPIDVersion2, l_y2_Value), 31, 1, 2, 226, "", 0 },

  { 114,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain",
    offsetof(Parameters_NLPIDVersion2, l_y2_Gain), 31, 1, 2, 228, "", 0 },

  { 115,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value",
    offsetof(Parameters_NLPIDVersion2, B_11_Value), 31, 1, 2, 230, "", 0 },

  { 116,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value",
    offsetof(Parameters_NLPIDVersion2, B_21_Value), 31, 1, 2, 232, "", 0 },

  { 117,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value",
    offsetof(Parameters_NLPIDVersion2, l_y1_Value), 31, 1, 2, 234, "", 0 },

  { 118,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value",
    offsetof(Parameters_NLPIDVersion2, B_12_Value), 31, 1, 2, 236, "", 0 },

  { 119,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value",
    offsetof(Parameters_NLPIDVersion2, B_22_Value), 31, 1, 2, 238, "", 0 },

  { 120,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value",
    offsetof(Parameters_NLPIDVersion2, B_13_Value), 31, 1, 2, 240, "", 0 },

  { 121,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value",
    offsetof(Parameters_NLPIDVersion2, B_23_Value), 31, 1, 2, 242, "", 0 },

  { 122,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value",
    offsetof(Parameters_NLPIDVersion2, B_14_Value), 31, 1, 2, 244, "", 0 },

  { 123,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value",
    offsetof(Parameters_NLPIDVersion2, B_24_Value), 31, 1, 2, 246, "", 0 },

  { 124,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value",
    offsetof(Parameters_NLPIDVersion2, B_15_Value), 31, 1, 2, 248, "", 0 },

  { 125,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value",
    offsetof(Parameters_NLPIDVersion2, B_25_Value), 31, 1, 2, 250, "", 0 },

  { 126,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value",
    offsetof(Parameters_NLPIDVersion2, l_x3_Value), 31, 1, 2, 252, "", 0 },

  { 127,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value",
    offsetof(Parameters_NLPIDVersion2, N_r_Value), 31, 1, 2, 254, "", 0 },

  { 128,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain",
    offsetof(Parameters_NLPIDVersion2, N_r_Gain), 31, 1, 2, 256, "", 0 },

  { 129,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value",
    offsetof(Parameters_NLPIDVersion2, N_v_Value), 31, 1, 2, 258, "", 0 },

  { 130,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain",
    offsetof(Parameters_NLPIDVersion2, N_v_Gain), 31, 1, 2, 260, "", 0 },

  { 131,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value",
    offsetof(Parameters_NLPIDVersion2, X_u_Value), 31, 1, 2, 262, "", 0 },

  { 132,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain",
    offsetof(Parameters_NLPIDVersion2, X_u_Gain), 31, 1, 2, 264, "", 0 },

  { 133,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value",
    offsetof(Parameters_NLPIDVersion2, Y_v_Value), 31, 1, 2, 266, "", 0 },

  { 134,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain",
    offsetof(Parameters_NLPIDVersion2, Y_v_Gain), 31, 1, 2, 268, "", 0 },

  { 135,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value",
    offsetof(Parameters_NLPIDVersion2, Y_r_Value), 31, 1, 2, 270, "", 0 },

  { 136,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain",
    offsetof(Parameters_NLPIDVersion2, Y_vr_Gain), 31, 1, 2, 272, "", 0 },

  { 137,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value",
    offsetof(Parameters_NLPIDVersion2, D_L_12_Value), 31, 1, 2, 274, "", 0 },

  { 138,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value",
    offsetof(Parameters_NLPIDVersion2, D_L_13_Value), 31, 1, 2, 276, "", 0 },

  { 139,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value",
    offsetof(Parameters_NLPIDVersion2, D_L_21_Value), 31, 1, 2, 278, "", 0 },

  { 140,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value",
    offsetof(Parameters_NLPIDVersion2, D_L_31_Value), 31, 1, 2, 280, "", 0 },

  { 141,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value",
    offsetof(Parameters_NLPIDVersion2, m_Value), 31, 1, 2, 282, "", 0 },

  { 142,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value",
    offsetof(Parameters_NLPIDVersion2, X_udot_Value), 31, 1, 2, 284, "", 0 },

  { 143,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value",
    offsetof(Parameters_NLPIDVersion2, M_21_Value), 31, 1, 2, 286, "", 0 },

  { 144,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value",
    offsetof(Parameters_NLPIDVersion2, M_31_Value), 31, 1, 2, 288, "", 0 },

  { 145,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value",
    offsetof(Parameters_NLPIDVersion2, M_12_Value), 31, 1, 2, 290, "", 0 },

  { 146,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value",
    offsetof(Parameters_NLPIDVersion2, Y_vdot_Value), 31, 1, 2, 292, "", 0 },

  { 147,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value",
    offsetof(Parameters_NLPIDVersion2, x_g_Value), 31, 1, 2, 294, "", 0 },

  { 148,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value",
    offsetof(Parameters_NLPIDVersion2, N_vdot_Value), 31, 1, 2, 296, "", 0 },

  { 149,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value",
    offsetof(Parameters_NLPIDVersion2, M_13_Value), 31, 1, 2, 298, "", 0 },

  { 150,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value",
    offsetof(Parameters_NLPIDVersion2, Y_rdot_Value), 31, 1, 2, 300, "", 0 },

  { 151,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value",
    offsetof(Parameters_NLPIDVersion2, I_z_Value), 31, 1, 2, 302, "", 0 },

  { 152,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value",
    offsetof(Parameters_NLPIDVersion2, N_rdot_Value), 31, 1, 2, 304, "", 0 },

  { 153,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value",
    offsetof(Parameters_NLPIDVersion2, T_e11_Value), 31, 1, 2, 306, "", 0 },

  { 154,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value",
    offsetof(Parameters_NLPIDVersion2, T_e21_Value), 31, 1, 2, 308, "", 0 },

  { 155,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value",
    offsetof(Parameters_NLPIDVersion2, l_y1_Value_o), 31, 1, 2, 310, "", 0 },

  { 156,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value",
    offsetof(Parameters_NLPIDVersion2, T_e12_Value), 31, 1, 2, 312, "", 0 },

  { 157,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value",
    offsetof(Parameters_NLPIDVersion2, T_e22_Value), 31, 1, 2, 314, "", 0 },

  { 158,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value",
    offsetof(Parameters_NLPIDVersion2, l_x1_Value_n), 31, 1, 2, 316, "", 0 },

  { 159,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain",
    offsetof(Parameters_NLPIDVersion2, l_x1_Gain_h), 31, 1, 2, 318, "", 0 },

  { 160,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value",
    offsetof(Parameters_NLPIDVersion2, T_e13_Value), 31, 1, 2, 320, "", 0 },

  { 161,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value",
    offsetof(Parameters_NLPIDVersion2, T_e23_Value), 31, 1, 2, 322, "", 0 },

  { 162,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value",
    offsetof(Parameters_NLPIDVersion2, l_y2_Value_n), 31, 1, 2, 324, "", 0 },

  { 163,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain",
    offsetof(Parameters_NLPIDVersion2, l_y2_Gain_g), 31, 1, 2, 326, "", 0 },

  { 164,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value",
    offsetof(Parameters_NLPIDVersion2, T_e14_Value), 31, 1, 2, 328, "", 0 },

  { 165,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value",
    offsetof(Parameters_NLPIDVersion2, T_e24_Value), 31, 1, 2, 330, "", 0 },

  { 166,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value",
    offsetof(Parameters_NLPIDVersion2, l_x2_Value_e), 31, 1, 2, 332, "", 0 },

  { 167,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain",
    offsetof(Parameters_NLPIDVersion2, l_x2_Gain_c), 31, 1, 2, 334, "", 0 },

  { 168,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value",
    offsetof(Parameters_NLPIDVersion2, T_e15_Value), 31, 1, 2, 336, "", 0 },

  { 169,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value",
    offsetof(Parameters_NLPIDVersion2, T_e25_Value), 31, 1, 2, 338, "", 0 },

  { 170,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value",
    offsetof(Parameters_NLPIDVersion2, l_x3_Value_o), 31, 1, 2, 340, "", 0 },

  { 171,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain",
    offsetof(Parameters_NLPIDVersion2, PS3u_1_Gain), 31, 1, 2, 342, "", 0 },

  { 172,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues",
    offsetof(Parameters_NLPIDVersion2, u_1tof_1_XData), 73, 19, 2, 344, "", 0 },

  { 173,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table",
    offsetof(Parameters_NLPIDVersion2, u_1tof_1_YData), 73, 19, 2, 346, "", 0 },

  { 174,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain",
    offsetof(Parameters_NLPIDVersion2, PS3u_2_Gain), 31, 1, 2, 348, "", 0 },

  { 175,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues",
    offsetof(Parameters_NLPIDVersion2, u_2tof_2_XData), 74, 21, 2, 350, "", 0 },

  { 176,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table",
    offsetof(Parameters_NLPIDVersion2, u_2tof_2_YData), 74, 21, 2, 352, "", 0 },

  { 177,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain",
    offsetof(Parameters_NLPIDVersion2, PS3u_3_Gain), 31, 1, 2, 354, "", 0 },

  { 178,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues",
    offsetof(Parameters_NLPIDVersion2, u_3tof_3_XData), 73, 19, 2, 356, "", 0 },

  { 179,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table",
    offsetof(Parameters_NLPIDVersion2, u_3tof_3_YData), 73, 19, 2, 358, "", 0 },

  { 180,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain",
    offsetof(Parameters_NLPIDVersion2, PS3u_4_Gain), 31, 1, 2, 360, "", 0 },

  { 181,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues",
    offsetof(Parameters_NLPIDVersion2, u_4tof_4_XData), 75, 17, 2, 362, "", 0 },

  { 182,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table",
    offsetof(Parameters_NLPIDVersion2, u_4tof_4_YData), 75, 17, 2, 364, "", 0 },

  { 183,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain",
    offsetof(Parameters_NLPIDVersion2, PS3u_5_Gain), 31, 1, 2, 366, "", 0 },

  { 184,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues",
    offsetof(Parameters_NLPIDVersion2, u_5tof_5_XData), 76, 7, 2, 368, "", 0 },

  { 185,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table",
    offsetof(Parameters_NLPIDVersion2, u_5tof_5_YData), 76, 7, 2, 370, "", 0 },

  { 186,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain",
    offsetof(Parameters_NLPIDVersion2, QTMIn3xcoordmm_Gain), 31, 1, 2, 372, "",
    0 },

  { 187, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain",
    offsetof(Parameters_NLPIDVersion2, mm2mx_Gain), 31, 1, 2, 374, "", 0 },

  { 188,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain",
    offsetof(Parameters_NLPIDVersion2, QTMIn4ycoordmm_Gain), 31, 1, 2, 376, "",
    0 },

  { 189, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain",
    offsetof(Parameters_NLPIDVersion2, mm2my_Gain), 31, 1, 2, 378, "", 0 },

  { 190,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain",
    offsetof(Parameters_NLPIDVersion2, QTMIn6yawdeg_Gain), 31, 1, 2, 380, "", 0
  },

  { 191, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain",
    offsetof(Parameters_NLPIDVersion2, d2ryaw_Gain), 31, 1, 2, 382, "", 0 },

  { 192,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat), 31, 1, 2, 384, "",
    0 },

  { 193,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat), 31, 1, 2, 386, "",
    0 },

  { 194,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain), 31, 1, 2, 388, "", 0 },

  { 195,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value), 31, 1, 2, 390, "", 0 },

  { 196,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_i), 31, 1, 2, 392, "",
    0 },

  { 197,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_f), 31, 1, 2, 394, "",
    0 },

  { 198,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_n), 31, 1, 2, 396, "", 0 },

  { 199,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_o), 31, 1, 2, 398, "", 0 },

  { 200,
    "nlpidversion2/Main Subsystems/Control/DP control/Integrator/InitialCondition",
    offsetof(Parameters_NLPIDVersion2, Integrator_IC), 31, 1, 2, 400, "", 0 },

  { 201,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain",
    offsetof(Parameters_NLPIDVersion2, QTMIn8rolldeg_Gain), 31, 1, 2, 402, "", 0
  },

  { 202,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain",
    offsetof(Parameters_NLPIDVersion2, d2rroll_Gain), 31, 1, 2, 404, "", 0 },

  { 203,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain",
    offsetof(Parameters_NLPIDVersion2, QTMIn7pitchdeg_Gain), 31, 1, 2, 406, "",
    0 },

  { 204,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain",
    offsetof(Parameters_NLPIDVersion2, d2rpitch_Gain), 31, 1, 2, 408, "", 0 },

  { 205,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Constant1/Value",
    offsetof(Parameters_NLPIDVersion2, Constant1_Value), 22, 9, 2, 410, "", 0 },

  { 206,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain",
    offsetof(Parameters_NLPIDVersion2, QTMIn5zcoordmm_Gain), 31, 1, 2, 412, "",
    0 },

  { 207, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain",
    offsetof(Parameters_NLPIDVersion2, mm2mz_Gain), 31, 1, 2, 414, "", 0 },

  { 208, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R31/Value",
    offsetof(Parameters_NLPIDVersion2, R31_Value), 31, 1, 2, 416, "", 0 },

  { 209, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/-1/Gain",
    offsetof(Parameters_NLPIDVersion2, u_Gain), 31, 1, 2, 418, "", 0 },

  { 210, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R32/Value",
    offsetof(Parameters_NLPIDVersion2, R32_Value), 31, 1, 2, 420, "", 0 },

  { 211, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R13/Value",
    offsetof(Parameters_NLPIDVersion2, R13_Value), 31, 1, 2, 422, "", 0 },

  { 212, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R23/Value",
    offsetof(Parameters_NLPIDVersion2, R23_Value), 31, 1, 2, 424, "", 0 },

  { 213, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R33/Value",
    offsetof(Parameters_NLPIDVersion2, R33_Value), 31, 1, 2, 426, "", 0 },

  { 214,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_f), 31, 1, 2, 428, "",
    0 },

  { 215,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_m), 31, 1, 2, 430, "",
    0 },

  { 216,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_k), 31, 1, 2, 432, "", 0 },

  { 217,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_l), 31, 1, 2, 434, "", 0 },

  { 218,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_j), 31, 1, 2, 436, "",
    0 },

  { 219,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_k), 31, 1, 2, 438, "",
    0 },

  { 220,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_o), 31, 1, 2, 440, "", 0 },

  { 221,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_g), 31, 1, 2, 442, "", 0 },

  { 222,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_m), 31, 1, 2, 444, "",
    0 },

  { 223,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_o), 31, 1, 2, 446, "",
    0 },

  { 224,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_p), 31, 1, 2, 448, "", 0 },

  { 225,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_p), 31, 1, 2, 450, "", 0 },

  { 226,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_h), 31, 1, 2, 452, "",
    0 },

  { 227,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_p), 31, 1, 2, 454, "",
    0 },

  { 228,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_b), 31, 1, 2, 456, "", 0 },

  { 229,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_a), 31, 1, 2, 458, "", 0 },

  { 230,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_j), 31, 1, 2, 460, "", 0 },

  { 231,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_d), 31, 1, 2, 462, "",
    0 },

  { 232,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_mg), 31, 1, 2, 464,
    "", 0 },

  { 233,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_j), 31, 1, 2, 466, "", 0 },

  { 234,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_lh), 31, 1, 2, 468, "", 0
  },

  { 235,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_e), 31, 1, 2, 470, "",
    0 },

  { 236,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_b), 31, 1, 2, 472, "",
    0 },

  { 237,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_d), 31, 1, 2, 474, "", 0 },

  { 238,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_ac), 31, 1, 2, 476, "", 0
  },

  { 239,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_n), 31, 1, 2, 478, "",
    0 },

  { 240,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_l), 31, 1, 2, 480, "",
    0 },

  { 241,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_g), 31, 1, 2, 482, "", 0 },

  { 242,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_f), 31, 1, 2, 484, "", 0 },

  { 243,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/zeta/Integrator/InitialCondition",
    offsetof(Parameters_NLPIDVersion2, Integrator_IC_g), 28, 3, 2, 486, "", 0 },

  { 244,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain",
    offsetof(Parameters_NLPIDVersion2, u_Gain_m), 31, 1, 2, 488, "", 0 },

  { 245,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s eq/0_2x1/Value",
    offsetof(Parameters_NLPIDVersion2, _2x1_Value), 32, 2, 2, 490, "", 0 },

  { 246,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value",
    offsetof(Parameters_NLPIDVersion2, _2x1_Value_i), 32, 2, 2, 492, "", 0 },

  { 247,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_pn), 31, 1, 2, 494, "", 0 },

  { 248,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain1_Gain_h), 31, 1, 2, 496, "", 0 },

  { 249,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_i), 31, 1, 2, 498, "", 0 },

  { 250,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_d), 31, 1, 2, 500, "", 0 },

  { 251,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_e), 31, 1, 2, 502, "", 0 },

  { 252,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_f), 31, 1, 2, 504, "", 0 },

  { 253,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain",
    offsetof(Parameters_NLPIDVersion2, _Gain), 31, 1, 2, 506, "", 0 },

  { 254,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value",
    offsetof(Parameters_NLPIDVersion2, _2x2_Value), 24, 4, 2, 508, "", 0 },

  { 255,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/0_2x2/Value",
    offsetof(Parameters_NLPIDVersion2, _2x2_Value_m), 24, 4, 2, 510, "", 0 },

  { 256,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain",
    offsetof(Parameters_NLPIDVersion2, _Gain_m), 31, 1, 2, 512, "", 0 },

  { 257,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_h4), 31, 1, 2, 514, "", 0 },

  { 258,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_c), 31, 1, 2, 516, "", 0 },

  { 259,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator2/InitialCondition",
    offsetof(Parameters_NLPIDVersion2, Integrator2_IC), 31, 1, 2, 518, "", 0 },

  { 260,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_c4), 31, 1, 2, 520, "", 0 },

  { 261,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/0_2x1/Value",
    offsetof(Parameters_NLPIDVersion2, _2x1_Value_ig), 32, 2, 2, 522, "", 0 },

  { 262,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_ji), 31, 1, 2, 524, "", 0
  },

  { 263,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_gz), 31, 1, 2, 526, "", 0 },

  { 264,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_n), 31, 1, 2, 528, "", 0 },

  { 265,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain",
    offsetof(Parameters_NLPIDVersion2, u_Gain_k), 31, 1, 2, 530, "", 0 },

  { 266,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain",
    offsetof(Parameters_NLPIDVersion2, _Gain_j), 31, 1, 2, 532, "", 0 },

  { 267,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain",
    offsetof(Parameters_NLPIDVersion2, _Gain_f), 31, 1, 2, 534, "", 0 },

  { 268,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_cv), 31, 1, 2, 536, "", 0 },

  { 269,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_m), 31, 1, 2, 538, "", 0 },

  { 270,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_eu), 31, 1, 2, 540, "", 0 },

  { 271,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value",
    offsetof(Parameters_NLPIDVersion2, u_Value_jk), 31, 1, 2, 542, "", 0 },

  { 272,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_gy), 31, 1, 2, 544, "", 0
  },

  { 273,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^t eq/0_2x1/Value",
    offsetof(Parameters_NLPIDVersion2, _2x1_Value_h), 32, 2, 2, 546, "", 0 },

  { 274,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S11/Value",
    offsetof(Parameters_NLPIDVersion2, S11_Value), 31, 1, 2, 548, "", 0 },

  { 275,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/R31/Value",
    offsetof(Parameters_NLPIDVersion2, R31_Value_l), 31, 1, 2, 550, "", 0 },

  { 276,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S12/Gain",
    offsetof(Parameters_NLPIDVersion2, S12_Gain), 31, 1, 2, 552, "", 0 },

  { 277,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S22/Value",
    offsetof(Parameters_NLPIDVersion2, S22_Value), 31, 1, 2, 554, "", 0 },

  { 278,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S32/Value",
    offsetof(Parameters_NLPIDVersion2, S32_Value), 31, 1, 2, 556, "", 0 },

  { 279,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S13/Value",
    offsetof(Parameters_NLPIDVersion2, S13_Value), 31, 1, 2, 558, "", 0 },

  { 280,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S23/Value",
    offsetof(Parameters_NLPIDVersion2, S23_Value), 31, 1, 2, 560, "", 0 },

  { 281,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S33/Value",
    offsetof(Parameters_NLPIDVersion2, S33_Value), 31, 1, 2, 562, "", 0 },

  { 282,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_jd), 24, 4, 2, 564, "", 0
  },

  { 283,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_i), 31, 1, 2, 566, "", 0 },

  { 284,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues",
    offsetof(Parameters_NLPIDVersion2, f_1tou_1_XData), 77, 39, 2, 568, "", 0 },

  { 285,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table",
    offsetof(Parameters_NLPIDVersion2, f_1tou_1_YData), 77, 39, 2, 570, "", 0 },

  { 286,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_c), 31, 1, 2, 572, "", 0 },

  { 287,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_go), 31, 1, 2, 574, "", 0
  },

  { 288,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_l1), 31, 1, 2, 576, "", 0
  },

  { 289,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_k), 31, 1, 2, 578, "", 0 },

  { 290,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues",
    offsetof(Parameters_NLPIDVersion2, f_2000391_XData), 78, 11, 2, 580, "", 0 },

  { 291,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table",
    offsetof(Parameters_NLPIDVersion2, f_2000391_YData), 78, 11, 2, 582, "", 0 },

  { 292,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues",
    offsetof(Parameters_NLPIDVersion2, f_2006731f_2000391_XData), 28, 3, 2, 584,
    "", 0 },

  { 293,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table",
    offsetof(Parameters_NLPIDVersion2, f_2006731f_2000391_YData), 28, 3, 2, 586,
    "", 0 },

  { 294,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues",
    offsetof(Parameters_NLPIDVersion2, f_2006731_XData), 79, 18, 2, 588, "", 0 },

  { 295,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table",
    offsetof(Parameters_NLPIDVersion2, f_2006731_YData), 79, 18, 2, 590, "", 0 },

  { 296,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues",
    offsetof(Parameters_NLPIDVersion2, f_3tou_3_XData), 77, 39, 2, 592, "", 0 },

  { 297,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table",
    offsetof(Parameters_NLPIDVersion2, f_3tou_3_YData), 77, 39, 2, 594, "", 0 },

  { 298,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_al), 31, 1, 2, 596, "", 0
  },

  { 299,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_nq), 31, 1, 2, 598, "", 0
  },

  { 300,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues",
    offsetof(Parameters_NLPIDVersion2, f_400451_XData), 80, 15, 2, 600, "", 0 },

  { 301,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table",
    offsetof(Parameters_NLPIDVersion2, f_400451_YData), 80, 15, 2, 602, "", 0 },

  { 302,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues",
    offsetof(Parameters_NLPIDVersion2, f_400451_XData_e), 81, 13, 2, 604, "", 0
  },

  { 303,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table",
    offsetof(Parameters_NLPIDVersion2, f_400451_YData_p), 81, 13, 2, 606, "", 0
  },

  { 304,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_NLPIDVersion2, DeadZone001_Start), 31, 1, 2, 608, "", 0
  },

  { 305,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_NLPIDVersion2, DeadZone001_End), 31, 1, 2, 610, "", 0 },

  { 306,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_b), 31, 1, 2, 612, "", 0 },

  { 307,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_fz), 31, 1, 2, 614, "", 0
  },

  { 308,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues",
    offsetof(Parameters_NLPIDVersion2, f_50_XData), 82, 10, 2, 616, "", 0 },

  { 309,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table",
    offsetof(Parameters_NLPIDVersion2, f_50_YData), 82, 10, 2, 618, "", 0 },

  { 310,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value",
    offsetof(Parameters_NLPIDVersion2, f_50_Value), 31, 1, 2, 620, "", 0 },

  { 311,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues",
    offsetof(Parameters_NLPIDVersion2, f_50_XData_k), 82, 10, 2, 622, "", 0 },

  { 312,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table",
    offsetof(Parameters_NLPIDVersion2, f_50_YData_c), 82, 10, 2, 624, "", 0 },

  { 313,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value",
    offsetof(Parameters_NLPIDVersion2, BT_power_limit_Value), 31, 1, 2, 626, "",
    0 },

  { 314,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value",
    offsetof(Parameters_NLPIDVersion2, VSP_speeds_Value), 31, 1, 2, 628, "", 0 },

  { 315,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_il), 31, 1, 2, 630,
    "", 0 },

  { 316,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_j), 31, 1, 2, 632, "",
    0 },

  { 317,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain",
    offsetof(Parameters_NLPIDVersion2, QTMIn2Error_Gain), 31, 1, 2, 634, "", 0 },

  { 318,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain",
    offsetof(Parameters_NLPIDVersion2, QTMIn9Residual_Gain), 31, 1, 2, 636, "",
    0 },

  { 319,
    "nlpidversion2/Main Subsystems/Plant/Thruster setting workaround/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_k), 31, 1, 2, 638, "",
    0 },

  { 320,
    "nlpidversion2/Main Subsystems/Plant/Thruster setting workaround/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_b2), 31, 1, 2, 640,
    "", 0 },

  { 321,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value",
    offsetof(Parameters_NLPIDVersion2, _2x1_Value_l), 32, 2, 2, 642, "", 0 },

  { 322,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In1 FPS/Gain",
    offsetof(Parameters_NLPIDVersion2, QTMIn1FPS_Gain), 31, 1, 2, 644, "", 0 },

  { 323, "nlpidversion2/Main Subsystems/Plant/saturation/Saturation/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_UpperSat_ez), 31, 1, 2, 646,
    "", 0 },

  { 324, "nlpidversion2/Main Subsystems/Plant/saturation/Saturation/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation_LowerSat_pr), 31, 1, 2, 648,
    "", 0 },

  { 325, "nlpidversion2/Main Subsystems/Plant/saturation/Saturation1/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation1_UpperSat), 31, 1, 2, 650, "",
    0 },

  { 326, "nlpidversion2/Main Subsystems/Plant/saturation/Saturation1/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation1_LowerSat), 31, 1, 2, 652, "",
    0 },

  { 327, "nlpidversion2/Main Subsystems/Plant/saturation/Saturation2/UpperLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation2_UpperSat), 31, 1, 2, 654, "",
    0 },

  { 328, "nlpidversion2/Main Subsystems/Plant/saturation/Saturation2/LowerLimit",
    offsetof(Parameters_NLPIDVersion2, Saturation2_LowerSat), 31, 1, 2, 656, "",
    0 },

  { 329, "nlpidversion2/Main Subsystems/Plant/saturation/plant tau_surge/Gain",
    offsetof(Parameters_NLPIDVersion2, planttau_surge_Gain), 31, 1, 2, 658, "",
    0 },

  { 330, "nlpidversion2/Main Subsystems/Plant/saturation/plant tau_sway/Gain",
    offsetof(Parameters_NLPIDVersion2, planttau_sway_Gain), 31, 1, 2, 660, "", 0
  },

  { 331, "nlpidversion2/Main Subsystems/Plant/saturation/plant tau_yaw/Gain",
    offsetof(Parameters_NLPIDVersion2, planttau_yaw_Gain), 31, 1, 2, 662, "", 0
  },

  { 332,
    "nlpidversion2/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain",
    offsetof(Parameters_NLPIDVersion2, BatteryBowThruster_Gain), 31, 1, 2, 664,
    "", 0 },

  { 333, "nlpidversion2/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain",
    offsetof(Parameters_NLPIDVersion2, BatteryMain_Gain), 31, 1, 2, 666, "", 0 },

  { 334, "nlpidversion2/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain",
    offsetof(Parameters_NLPIDVersion2, BatteryServo_Gain), 31, 1, 2, 668, "", 0
  },

  { 335, "nlpidversion2/Outputs to LabVIEW/Command/omega_qy/Gain", offsetof
    (Parameters_NLPIDVersion2, omega_qy_Gain), 31, 1, 2, 670, "", 0 },

  { 336, "nlpidversion2/Outputs to LabVIEW/Command/omegaqx/Gain", offsetof
    (Parameters_NLPIDVersion2, omegaqx_Gain), 31, 1, 2, 672, "", 0 },

  { 337, "nlpidversion2/Outputs to LabVIEW/Command/plant BT power/Gain",
    offsetof(Parameters_NLPIDVersion2, plantBTpower_Gain), 31, 1, 2, 674, "", 0
  },

  { 338, "nlpidversion2/Outputs to LabVIEW/Command/plant VSP speed/Gain",
    offsetof(Parameters_NLPIDVersion2, plantVSPspeed_Gain), 31, 1, 2, 676, "", 0
  },

  { 339, "nlpidversion2/Outputs to LabVIEW/Command/plant u_1/Gain", offsetof
    (Parameters_NLPIDVersion2, plantu_1_Gain), 31, 1, 2, 678, "", 0 },

  { 340, "nlpidversion2/Outputs to LabVIEW/Command/plant u_2/Gain", offsetof
    (Parameters_NLPIDVersion2, plantu_2_Gain), 31, 1, 2, 680, "", 0 },

  { 341, "nlpidversion2/Outputs to LabVIEW/Command/plant u_3/Gain", offsetof
    (Parameters_NLPIDVersion2, plantu_3_Gain), 31, 1, 2, 682, "", 0 },

  { 342, "nlpidversion2/Outputs to LabVIEW/Command/plant u_4/Gain", offsetof
    (Parameters_NLPIDVersion2, plantu_4_Gain), 31, 1, 2, 684, "", 0 },

  { 343, "nlpidversion2/Outputs to LabVIEW/Command/plant u_5/Gain", offsetof
    (Parameters_NLPIDVersion2, plantu_5_Gain), 31, 1, 2, 686, "", 0 },

  { 344, "nlpidversion2/Outputs to LabVIEW/Command/fact1/Gain", offsetof
    (Parameters_NLPIDVersion2, fact1_Gain), 31, 1, 2, 688, "", 0 },

  { 345, "nlpidversion2/Outputs to LabVIEW/Command/fact2/Gain", offsetof
    (Parameters_NLPIDVersion2, fact2_Gain), 31, 1, 2, 690, "", 0 },

  { 346, "nlpidversion2/Outputs to LabVIEW/Command/fact3/Gain", offsetof
    (Parameters_NLPIDVersion2, fact3_Gain), 31, 1, 2, 692, "", 0 },

  { 347, "nlpidversion2/Outputs to LabVIEW/Command/fact4/Gain", offsetof
    (Parameters_NLPIDVersion2, fact4_Gain), 31, 1, 2, 694, "", 0 },

  { 348, "nlpidversion2/Outputs to LabVIEW/Command/fact5/Gain", offsetof
    (Parameters_NLPIDVersion2, fact5_Gain), 31, 1, 2, 696, "", 0 },

  { 349, "nlpidversion2/Outputs to LabVIEW/Command/taux/Gain", offsetof
    (Parameters_NLPIDVersion2, taux_Gain), 31, 1, 2, 698, "", 0 },

  { 350, "nlpidversion2/Outputs to LabVIEW/Command/tauy/Gain", offsetof
    (Parameters_NLPIDVersion2, tauy_Gain), 31, 1, 2, 700, "", 0 },

  { 351, "nlpidversion2/Outputs to LabVIEW/Command/tauyaw/Gain", offsetof
    (Parameters_NLPIDVersion2, tauyaw_Gain), 31, 1, 2, 702, "", 0 },

  { 352, "nlpidversion2/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain",
    offsetof(Parameters_NLPIDVersion2, CSE1_rdegs_Gain), 31, 1, 2, 704, "", 0 },

  { 353, "nlpidversion2/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain",
    offsetof(Parameters_NLPIDVersion2, CSE1_ums_Gain), 31, 1, 2, 706, "", 0 },

  { 354, "nlpidversion2/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain",
    offsetof(Parameters_NLPIDVersion2, CSE1_vms_Gain), 31, 1, 2, 708, "", 0 },

  { 355, "nlpidversion2/Outputs to LabVIEW/Visualization/psi [deg]/Gain",
    offsetof(Parameters_NLPIDVersion2, psideg_Gain), 31, 1, 2, 710, "", 0 },

  { 356, "nlpidversion2/Outputs to LabVIEW/Visualization/psi-psid [deg]/Gain",
    offsetof(Parameters_NLPIDVersion2, psipsiddeg_Gain), 31, 1, 2, 712, "", 0 },

  { 357, "nlpidversion2/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]/Gain",
    offsetof(Parameters_NLPIDVersion2, psiLOSpsideg_Gain), 31, 1, 2, 714, "", 0
  },

  { 358, "nlpidversion2/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]/Gain",
    offsetof(Parameters_NLPIDVersion2, psiLOSpsiddeg_Gain), 31, 1, 2, 716, "", 0
  },

  { 359, "nlpidversion2/Outputs to LabVIEW/Visualization/psi_LOS [deg]/Gain",
    offsetof(Parameters_NLPIDVersion2, psi_LOSdeg_Gain), 31, 1, 2, 718, "", 0 },

  { 360, "nlpidversion2/Outputs to LabVIEW/Visualization/psid [deg]/Gain",
    offsetof(Parameters_NLPIDVersion2, psiddeg_Gain), 31, 1, 2, 720, "", 0 },

  { 361, "nlpidversion2/Outputs to LabVIEW/Visualization/psi_plot/Gain",
    offsetof(Parameters_NLPIDVersion2, psi_plot_Gain), 31, 1, 2, 722, "", 0 },

  { 362, "nlpidversion2/Outputs to LabVIEW/Visualization/qx [m]/Gain", offsetof
    (Parameters_NLPIDVersion2, qxm_Gain), 31, 1, 2, 724, "", 0 },

  { 363, "nlpidversion2/Outputs to LabVIEW/Visualization/qx-x [m]/Gain",
    offsetof(Parameters_NLPIDVersion2, qxxm_Gain), 31, 1, 2, 726, "", 0 },

  { 364, "nlpidversion2/Outputs to LabVIEW/Visualization/qx-xd [m]1/Gain",
    offsetof(Parameters_NLPIDVersion2, qxxdm1_Gain), 31, 1, 2, 728, "", 0 },

  { 365, "nlpidversion2/Outputs to LabVIEW/Visualization/qy [m]/Gain", offsetof
    (Parameters_NLPIDVersion2, qym_Gain), 31, 1, 2, 730, "", 0 },

  { 366, "nlpidversion2/Outputs to LabVIEW/Visualization/qy-y [m]/Gain",
    offsetof(Parameters_NLPIDVersion2, qyym_Gain), 31, 1, 2, 732, "", 0 },

  { 367, "nlpidversion2/Outputs to LabVIEW/Visualization/qy-yd [m]1/Gain",
    offsetof(Parameters_NLPIDVersion2, qyydm1_Gain), 31, 1, 2, 734, "", 0 },

  { 368, "nlpidversion2/Outputs to LabVIEW/Visualization/x [m]/Gain", offsetof
    (Parameters_NLPIDVersion2, xm_Gain), 31, 1, 2, 736, "", 0 },

  { 369, "nlpidversion2/Outputs to LabVIEW/Visualization/x-xd [m]/Gain",
    offsetof(Parameters_NLPIDVersion2, xxdm_Gain), 31, 1, 2, 738, "", 0 },

  { 370, "nlpidversion2/Outputs to LabVIEW/Visualization/xd [m]/Gain", offsetof
    (Parameters_NLPIDVersion2, xdm_Gain), 31, 1, 2, 740, "", 0 },

  { 371, "nlpidversion2/Outputs to LabVIEW/Visualization/x_plot/Gain", offsetof
    (Parameters_NLPIDVersion2, x_plot_Gain), 31, 1, 2, 742, "", 0 },

  { 372, "nlpidversion2/Outputs to LabVIEW/Visualization/y [m]/Gain", offsetof
    (Parameters_NLPIDVersion2, ym_Gain), 31, 1, 2, 744, "", 0 },

  { 373, "nlpidversion2/Outputs to LabVIEW/Visualization/y-yd [m]/Gain",
    offsetof(Parameters_NLPIDVersion2, yydm_Gain), 31, 1, 2, 746, "", 0 },

  { 374, "nlpidversion2/Outputs to LabVIEW/Visualization/yd [m]/Gain", offsetof
    (Parameters_NLPIDVersion2, ydm_Gain), 31, 1, 2, 748, "", 0 },

  { 375, "nlpidversion2/Outputs to LabVIEW/Visualization/y_plot/Gain", offsetof
    (Parameters_NLPIDVersion2, y_plot_Gain), 31, 1, 2, 750, "", 0 },

  { 376,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain",
    offsetof(Parameters_NLPIDVersion2, R12_Gain), 31, 1, 2, 752, "", 0 },

  { 377,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain",
    offsetof(Parameters_NLPIDVersion2, R22_Gain), 31, 1, 2, 754, "", 0 },

  { 378,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value",
    offsetof(Parameters_NLPIDVersion2, _Value), 31, 1, 2, 756, "", 0 },

  { 379,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain",
    offsetof(Parameters_NLPIDVersion2, S12_Gain_c), 31, 1, 2, 758, "", 0 },

  { 380,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value",
    offsetof(Parameters_NLPIDVersion2, _Value_m), 31, 1, 2, 760, "", 0 },

  { 381,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain",
    offsetof(Parameters_NLPIDVersion2, S12_Gain_g), 31, 1, 2, 762, "", 0 },

  { 382,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain",
    offsetof(Parameters_NLPIDVersion2, BT_D_Gain1_Gain), 31, 1, 2, 764, "", 0 },

  { 383,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value",
    offsetof(Parameters_NLPIDVersion2, BT_Power_Offset1_Value), 31, 1, 2, 766,
    "", 0 },

  { 384,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain",
    offsetof(Parameters_NLPIDVersion2, BT_D_Gain2_Gain), 31, 1, 2, 768, "", 0 },

  { 385,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain",
    offsetof(Parameters_NLPIDVersion2, BT_L_Gain1_Gain), 31, 1, 2, 770, "", 0 },

  { 386,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain",
    offsetof(Parameters_NLPIDVersion2, BT_L_Gain2_Gain), 31, 1, 2, 772, "", 0 },

  { 387,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value",
    offsetof(Parameters_NLPIDVersion2, BT_Power_Offset2_Value), 31, 1, 2, 774,
    "", 0 },

  { 388,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value",
    offsetof(Parameters_NLPIDVersion2, BT_Power_Offset3_Value), 31, 1, 2, 776,
    "", 0 },

  { 389,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value",
    offsetof(Parameters_NLPIDVersion2, Constant_Value_h), 31, 1, 2, 778, "", 0 },

  { 390,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value",
    offsetof(Parameters_NLPIDVersion2, Constant1_Value_i), 31, 1, 2, 780, "", 0
  },

  { 391,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain",
    offsetof(Parameters_NLPIDVersion2, Neg_Gain), 31, 1, 2, 782, "", 0 },

  { 392,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain",
    offsetof(Parameters_NLPIDVersion2, x_Gain), 31, 1, 2, 784, "", 0 },

  { 393,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain",
    offsetof(Parameters_NLPIDVersion2, y_Gain), 31, 1, 2, 786, "", 0 },

  { 394,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex",
    offsetof(Parameters_NLPIDVersion2, Servo1_RowIdx), 83, 3, 2, 788, "", 0 },

  { 395,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_NLPIDVersion2, Servo1_ColIdx), 83, 3, 2, 790, "", 0 },

  { 396,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table",
    offsetof(Parameters_NLPIDVersion2, Servo1_Table), 22, 9, 2, 792, "", 0 },

  { 397,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex",
    offsetof(Parameters_NLPIDVersion2, Servo2_RowIdx), 83, 3, 2, 794, "", 0 },

  { 398,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_NLPIDVersion2, Servo2_ColIdx), 83, 3, 2, 796, "", 0 },

  { 399,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table",
    offsetof(Parameters_NLPIDVersion2, Servo2_Table), 22, 9, 2, 798, "", 0 },

  { 400,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex",
    offsetof(Parameters_NLPIDVersion2, Servo3_RowIdx), 83, 3, 2, 800, "", 0 },

  { 401,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_NLPIDVersion2, Servo3_ColIdx), 83, 3, 2, 802, "", 0 },

  { 402,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table",
    offsetof(Parameters_NLPIDVersion2, Servo3_Table), 22, 9, 2, 804, "", 0 },

  { 403,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex",
    offsetof(Parameters_NLPIDVersion2, Servo4_RowIdx), 83, 3, 2, 806, "", 0 },

  { 404,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_NLPIDVersion2, Servo4_ColIdx), 83, 3, 2, 808, "", 0 },

  { 405,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table",
    offsetof(Parameters_NLPIDVersion2, Servo4_Table), 22, 9, 2, 810, "", 0 },

  { 406,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, VPS_Speed_Gain_Gain), 31, 1, 2, 812, "",
    0 },

  { 407,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_NLPIDVersion2, VPS_Power_Offset_Value), 31, 1, 2, 814,
    "", 0 },

  { 408,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain",
    offsetof(Parameters_NLPIDVersion2, VSPSPort_Gain), 31, 1, 2, 816, "", 0 },

  { 409,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_NLPIDVersion2, VSPSStarboard_Gain), 31, 1, 2, 818, "", 0
  },

  { 410,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_NLPIDVersion2, R31_Value_m), 31, 1, 2, 820, "", 0 },

  { 411,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_NLPIDVersion2, R32_Value_d), 31, 1, 2, 822, "", 0 },

  { 412,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_NLPIDVersion2, R13_Value_l), 31, 1, 2, 824, "", 0 },

  { 413,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_NLPIDVersion2, R23_Value_c), 31, 1, 2, 826, "", 0 },

  { 414,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_NLPIDVersion2, R33_Value_b), 31, 1, 2, 828, "", 0 },

  { 415,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain1_Gain_n), 37, 1, 2, 830, "", 0 },

  { 416,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_l), 37, 1, 2, 832, "", 0 },

  { 417,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain_Gain_fd), 37, 1, 2, 834, "", 0 },

  { 418,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_NLPIDVersion2, Gain1_Gain_i), 37, 1, 2, 836, "", 0 },
};

static int NI_ParamListSize = 419;
static int NI_ParamDimList[] = {
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Control Input Selector/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Control Mode Selector/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Enable CSE1/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Delta [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Path Selector  [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/my [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/u_d [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/x_dmax [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/x_dmin [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/y_dmax [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/y_dmin [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Ellipse/k [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Ellipse/x_0 [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Ellipse/y_0 [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/L2 [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/PlayStation3/R2 [-]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Setpoint/setpointpsi [deg]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Setpoint/setpointx [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/Setpoint/setpointy [m]/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/12/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/13/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/21/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/23/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/31/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/32/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kdx/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kdy/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kdpsi/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/12/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/13/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/21/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/23/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/31/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/32/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kix/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kiy/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kipsi/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/12/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/13/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/21/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/23/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/31/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/32/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kpx/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kpy/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1Kppsi/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/ctrl1 Reset Integrator/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q/12/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q/21/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q_Surge/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q_Sway/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Initial q_x/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Initial q_y/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Initial s/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/12/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/13/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/21/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/23/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/31/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/32/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kdx/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kdy/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kdpsi/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/12/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/13/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/21/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/23/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/31/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/32/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kix/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kiy/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kipsi/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/12/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/13/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/21/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/23/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/31/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/32/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kpx/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kpy/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2Kppsi/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/ctrl2 Reset Integrator/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/kappa_1/Value */
  1, 1,                                /* nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/lambda_q/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain */
  19, 1,                               /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues */
  19, 1,                               /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain */
  21, 1,                               /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues */
  21, 1,                               /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain */
  19, 1,                               /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues */
  19, 1,                               /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain */
  17, 1,                               /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues */
  17, 1,                               /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain */
  1, 7,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues */
  1, 7,                                /* nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/DP control/Integrator/InitialCondition */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain */
  3, 3,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Constant1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R31/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/-1/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R32/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R13/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R23/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R33/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value */
  3, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/zeta/Integrator/InitialCondition */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain */
  2, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s eq/0_2x1/Value */
  2, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain */
  2, 2,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value */
  2, 2,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/0_2x2/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator2/InitialCondition */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain */
  2, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/0_2x1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value */
  2, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^t eq/0_2x1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S11/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/R31/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S12/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S22/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S32/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S13/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S23/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S33/Value */
  2, 2,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Gain/Gain */
  1, 39,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues */
  1, 39,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues */
  11, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table */
  3, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues */
  3, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table */
  18, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues */
  18, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table */
  1, 39,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues */
  1, 39,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues */
  15, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table */
  13, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues */
  13, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues */
  10, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value */
  10, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues */
  10, 1,                               /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/Thruster setting workaround/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/Thruster setting workaround/Saturation/LowerLimit */
  2, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In1 FPS/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/saturation/Saturation/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/saturation/Saturation/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/saturation/Saturation1/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/saturation/Saturation1/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/saturation/Saturation2/UpperLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/saturation/Saturation2/LowerLimit */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/saturation/plant tau_surge/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/saturation/plant tau_sway/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/saturation/plant tau_yaw/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/omega_qy/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/omegaqx/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/plant BT power/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/plant VSP speed/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/plant u_1/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/plant u_2/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/plant u_3/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/plant u_4/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/plant u_5/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/fact1/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/fact2/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/fact3/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/fact4/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/fact5/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/taux/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/tauy/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Command/tauyaw/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/psi [deg]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/psi-psid [deg]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/psi_LOS [deg]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/psid [deg]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/psi_plot/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/qx [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/qx-x [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/qx-xd [m]1/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/qy [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/qy-y [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/qy-yd [m]1/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/x [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/x-xd [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/xd [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/x_plot/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/y [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/y-yd [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/yd [m]/Gain */
  1, 1,                                /* nlpidversion2/Outputs to LabVIEW/Visualization/y_plot/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 602;
static NI_Signal NI_SigList[] = {
  { 0, "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Initialpsirad), BLOCKIO_SIG, 0, 1, 2, 0,
    0 },

  { 1, "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial x [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Initialxm), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial y [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Initialym), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]",
    0, "", offsetof(BlockIO_NLPIDVersion2, Initialrrads), BLOCKIO_SIG, 0, 1, 2,
    6, 0 },

  { 4, "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Initialums), BLOCKIO_SIG, 0, 1, 2, 8, 0
  },

  { 5, "nlpidversion2/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Initialvms), BLOCKIO_SIG, 0, 1, 2, 10, 0
  },

  { 6, "nlpidversion2/Inputs from LabVIEW/PlayStation3/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_NLPIDVersion2,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "nlpidversion2/Inputs from LabVIEW/PlayStation3/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_NLPIDVersion2,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "nlpidversion2/Inputs from LabVIEW/PlayStation3/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_NLPIDVersion2,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 16, 0 },

  { 9, "nlpidversion2/Inputs from LabVIEW/PlayStation3/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_NLPIDVersion2,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "nlpidversion2/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Gain1), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kd/[3x3]",
    0, "", offsetof(BlockIO_NLPIDVersion2, ux3), BLOCKIO_SIG, 22, 9, 2, 22, 0 },

  { 12, "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Ki/[3x3]",
    0, "", offsetof(BlockIO_NLPIDVersion2, ux3_a), BLOCKIO_SIG, 22, 9, 2, 24, 0
  },

  { 13, "nlpidversion2/Inputs from LabVIEW/ctrl1: Dynamic Positioning/Kp/[3x3]",
    0, "", offsetof(BlockIO_NLPIDVersion2, ux3_i), BLOCKIO_SIG, 22, 9, 2, 26, 0
  },

  { 14,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Gamma_q/[2x2]",
    0, "", offsetof(BlockIO_NLPIDVersion2, ux2), BLOCKIO_SIG, 24, 4, 2, 28, 0 },

  { 15,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Initial q_x",
    0, "", offsetof(BlockIO_NLPIDVersion2, Initialq_x), BLOCKIO_SIG, 0, 1, 2, 30,
    0 },

  { 16,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Initial q_y",
    0, "", offsetof(BlockIO_NLPIDVersion2, Initialq_y), BLOCKIO_SIG, 0, 1, 2, 32,
    0 },

  { 17,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/Initial s",
    0, "", offsetof(BlockIO_NLPIDVersion2, Initials), BLOCKIO_SIG, 0, 1, 2, 34,
    0 },

  { 18,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_d/[3x3]",
    0, "", offsetof(BlockIO_NLPIDVersion2, ux3_ip), BLOCKIO_SIG, 22, 9, 2, 36, 0
  },

  { 19,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_i/[3x3]",
    0, "", offsetof(BlockIO_NLPIDVersion2, ux3_p), BLOCKIO_SIG, 22, 9, 2, 38, 0
  },

  { 20,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/K_p/[3x3]",
    0, "", offsetof(BlockIO_NLPIDVersion2, ux3_g), BLOCKIO_SIG, 22, 9, 2, 40, 0
  },

  { 21,
    "nlpidversion2/Inputs from LabVIEW/ctrl2: LOS LgV backstepping II/kappa_1",
    0, "", offsetof(BlockIO_NLPIDVersion2, kappa_1), BLOCKIO_SIG, 0, 1, 2, 42, 0
  },

  { 22,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1",
    0, "", offsetof(BlockIO_NLPIDVersion2, l_x1), BLOCKIO_SIG, 0, 1, 2, 44, 0 },

  { 23,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2",
    0, "", offsetof(BlockIO_NLPIDVersion2, l_x2), BLOCKIO_SIG, 0, 1, 2, 46, 0 },

  { 24,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2",
    0, "", offsetof(BlockIO_NLPIDVersion2, l_y2), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/3x5",
    0, "", offsetof(BlockIO_NLPIDVersion2, x5), BLOCKIO_SIG, 26, 15, 2, 50, 0 },

  { 26,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r",
    0, "", offsetof(BlockIO_NLPIDVersion2, N_r), BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v",
    0, "", offsetof(BlockIO_NLPIDVersion2, N_v), BLOCKIO_SIG, 0, 1, 2, 54, 0 },

  { 28,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u",
    0, "", offsetof(BlockIO_NLPIDVersion2, X_u), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v",
    0, "", offsetof(BlockIO_NLPIDVersion2, Y_v), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr",
    0, "", offsetof(BlockIO_NLPIDVersion2, Y_vr), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Linear Dampning matrix",
    0, "", offsetof(BlockIO_NLPIDVersion2, LinearDampningmatrix), BLOCKIO_SIG,
    22, 9, 2, 62, 0 },

  { 32,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_11",
    0, "", offsetof(BlockIO_NLPIDVersion2, M_11), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_22",
    0, "", offsetof(BlockIO_NLPIDVersion2, M_22), BLOCKIO_SIG, 0, 1, 2, 66, 0 },

  { 34,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m x_g",
    0, "", offsetof(BlockIO_NLPIDVersion2, mx_g), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_32",
    0, "", offsetof(BlockIO_NLPIDVersion2, M_32), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_23",
    0, "", offsetof(BlockIO_NLPIDVersion2, M_23), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_33",
    0, "", offsetof(BlockIO_NLPIDVersion2, M_33), BLOCKIO_SIG, 0, 1, 2, 74, 0 },

  { 38,
    "nlpidversion2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/3x3",
    0, "", offsetof(BlockIO_NLPIDVersion2, x3), BLOCKIO_SIG, 22, 9, 2, 76, 0 },

  { 39,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1",
    0, "", offsetof(BlockIO_NLPIDVersion2, l_x1_f), BLOCKIO_SIG, 0, 1, 2, 78, 0
  },

  { 40,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2",
    0, "", offsetof(BlockIO_NLPIDVersion2, l_y2_d), BLOCKIO_SIG, 0, 1, 2, 80, 0
  },

  { 41,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2",
    0, "", offsetof(BlockIO_NLPIDVersion2, l_x2_d), BLOCKIO_SIG, 0, 1, 2, 82, 0
  },

  { 42,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/3x5",
    0, "", offsetof(BlockIO_NLPIDVersion2, x5_p), BLOCKIO_SIG, 26, 15, 2, 84, 0
  },

  { 43, "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_1", 0,
    "u_1", offsetof(BlockIO_NLPIDVersion2, u_1), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_1tof_1), BLOCKIO_SIG, 0, 1, 2, 88,
    0 },

  { 45, "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_2", 0,
    "u_2", offsetof(BlockIO_NLPIDVersion2, u_2), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_2tof_2), BLOCKIO_SIG, 0, 1, 2, 92,
    0 },

  { 47, "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_3", 0,
    "u_3", offsetof(BlockIO_NLPIDVersion2, u_3), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_3tof_3), BLOCKIO_SIG, 0, 1, 2, 96,
    0 },

  { 49, "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_4", 0,
    "u_4", offsetof(BlockIO_NLPIDVersion2, u_4), BLOCKIO_SIG, 0, 1, 2, 98, 0 },

  { 50,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_4tof_4), BLOCKIO_SIG, 0, 1, 2, 100,
    0 },

  { 51, "nlpidversion2/Main Subsystems/Control/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_NLPIDVersion2,
    BowThrusterdirection), BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52, "nlpidversion2/Main Subsystems/Control/PS3 u input control/PS3 u_5", 0,
    "u_5", offsetof(BlockIO_NLPIDVersion2, u_5), BLOCKIO_SIG, 0, 1, 2, 104, 0 },

  { 53,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_5tof_5), BLOCKIO_SIG, 0, 1, 2, 106,
    0 },

  { 54,
    "nlpidversion2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product), BLOCKIO_SIG, 20, 3, 2, 108,
    0 },

  { 55, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In", 0, "",
    offsetof(BlockIO_NLPIDVersion2, QTMIn), BLOCKIO_SIG, 46, 9, 2, 110, 0 },

  { 56,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]",
    0, "", offsetof(BlockIO_NLPIDVersion2, QTMIn3xcoordmm), BLOCKIO_SIG, 31, 1,
    2, 112, 0 },

  { 57, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/mm2m x", 0, "",
    offsetof(BlockIO_NLPIDVersion2, mm2mx), BLOCKIO_SIG, 31, 1, 2, 114, 0 },

  { 58,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]",
    0, "", offsetof(BlockIO_NLPIDVersion2, QTMIn4ycoordmm), BLOCKIO_SIG, 31, 1,
    2, 116, 0 },

  { 59, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/mm2m y", 0, "",
    offsetof(BlockIO_NLPIDVersion2, mm2my), BLOCKIO_SIG, 31, 1, 2, 118, 0 },

  { 60,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]",
    0, "", offsetof(BlockIO_NLPIDVersion2, QTMIn6yawdeg), BLOCKIO_SIG, 31, 1, 2,
    120, 0 },

  { 61, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/d2r yaw", 0,
    "", offsetof(BlockIO_NLPIDVersion2, d2ryaw), BLOCKIO_SIG, 31, 1, 2, 122, 0 },

  { 62, "nlpidversion2/Main Subsystems/Naviagation/Navigation Switch/eta Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, etaSwitch), BLOCKIO_SIG, 20, 3, 2,
    124, 0 },

  { 63, "nlpidversion2/Main Subsystems/Control/DP control/yaw angle", 0, "psi",
    offsetof(BlockIO_NLPIDVersion2, psi), BLOCKIO_SIG, 0, 1, 2, 126, 0 },

  { 64,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation), BLOCKIO_SIG, 0, 1, 2,
    128, 0 },

  { 65,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sign), BLOCKIO_SIG, 0, 1, 2, 130, 0 },

  { 66,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain), BLOCKIO_SIG, 0, 1, 2, 132, 0 },

  { 67,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1), BLOCKIO_SIG, 0, 1, 2, 134, 0 },

  { 68,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction), BLOCKIO_SIG, 0, 1, 2,
    136, 0 },

  { 69,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum), BLOCKIO_SIG, 0, 1, 2, 138, 0 },

  { 70, "nlpidversion2/Main Subsystems/Control/DP control/Sum2", 0, "", offsetof
    (BlockIO_NLPIDVersion2, Sum2), BLOCKIO_SIG, 20, 3, 2, 140, 0 },

  { 71,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_d), BLOCKIO_SIG, 0, 1, 2,
    142, 0 },

  { 72,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sign_h), BLOCKIO_SIG, 0, 1, 2, 144, 0
  },

  { 73,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_g), BLOCKIO_SIG, 0, 1, 2, 146, 0
  },

  { 74,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1_j), BLOCKIO_SIG, 0, 1, 2, 148, 0
  },

  { 75,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_a), BLOCKIO_SIG, 0, 1, 2,
    150, 0 },

  { 76,
    "nlpidversion2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_l), BLOCKIO_SIG, 0, 1, 2, 152, 0
  },

  { 77,
    "nlpidversion2/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Row1), BLOCKIO_SIG, 0, 1, 2, 154, 0 },

  { 78,
    "nlpidversion2/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Row2), BLOCKIO_SIG, 0, 1, 2, 156, 0 },

  { 79,
    "nlpidversion2/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_NLPIDVersion2, Row3), BLOCKIO_SIG, 0, 1, 2, 158, 0 },

  { 80, "nlpidversion2/Main Subsystems/Control/DP control/Product", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Product_i), BLOCKIO_SIG, 20, 3, 2, 160, 0 },

  { 81, "nlpidversion2/Main Subsystems/Control/DP control/Integrator", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Integrator), BLOCKIO_SIG, 20, 3, 2, 162, 0 },

  { 82, "nlpidversion2/Main Subsystems/Control/DP control/Product1", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Product1), BLOCKIO_SIG, 20, 3, 2, 164, 0 },

  { 83, "nlpidversion2/Main Subsystems/Control/DP control/Sum3", 0, "", offsetof
    (BlockIO_NLPIDVersion2, Sum3), BLOCKIO_SIG, 20, 3, 2, 166, 0 },

  { 84,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]",
    0, "", offsetof(BlockIO_NLPIDVersion2, QTMIn8rolldeg), BLOCKIO_SIG, 31, 1, 2,
    168, 0 },

  { 85, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/d2r roll", 0,
    "", offsetof(BlockIO_NLPIDVersion2, d2rroll), BLOCKIO_SIG, 31, 1, 2, 170, 0
  },

  { 86,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]",
    0, "", offsetof(BlockIO_NLPIDVersion2, QTMIn7pitchdeg), BLOCKIO_SIG, 31, 1,
    2, 172, 0 },

  { 87, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/d2r pitch", 0,
    "", offsetof(BlockIO_NLPIDVersion2, d2rpitch), BLOCKIO_SIG, 31, 1, 2, 174, 0
  },

  { 88,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_NLPIDVersion2, sintheta), BLOCKIO_SIG, 20, 3, 2, 176,
    0 },

  { 89,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_NLPIDVersion2, costheta), BLOCKIO_SIG, 20, 3, 2, 178,
    0 },

  { 90,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_NLPIDVersion2, R11), BLOCKIO_SIG, 0, 1, 2, 180, 0 },

  { 91,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_NLPIDVersion2, R21), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_NLPIDVersion2, R31), BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_NLPIDVersion2, R12), BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_NLPIDVersion2, R22), BLOCKIO_SIG, 0, 1, 2, 188, 0 },

  { 95,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_NLPIDVersion2, R32), BLOCKIO_SIG, 0, 1, 2, 190, 0 },

  { 96,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_NLPIDVersion2, R13), BLOCKIO_SIG, 0, 1, 2, 192, 0 },

  { 97,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_NLPIDVersion2, R23), BLOCKIO_SIG, 0, 1, 2, 194, 0 },

  { 98,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_NLPIDVersion2, R33), BLOCKIO_SIG, 0, 1, 2, 196, 0 },

  { 99,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_NLPIDVersion2, Reshape9x13x3), BLOCKIO_SIG, 22, 9, 2,
    198, 0 },

  { 100,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Matrix Concatenate2",
    0, "", offsetof(BlockIO_NLPIDVersion2, MatrixConcatenate2), BLOCKIO_SIG, 51,
    36, 2, 200, 0 },

  { 101,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]",
    0, "", offsetof(BlockIO_NLPIDVersion2, QTMIn5zcoordmm), BLOCKIO_SIG, 31, 1,
    2, 202, 0 },

  { 102, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/mm2m z", 0,
    "", offsetof(BlockIO_NLPIDVersion2, mm2mz), BLOCKIO_SIG, 31, 1, 2, 204, 0 },

  { 103, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Derivative",
    0, "", offsetof(BlockIO_NLPIDVersion2, Derivative), BLOCKIO_SIG, 47, 6, 2,
    206, 0 },

  { 104, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Product", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Product_l), BLOCKIO_SIG, 47, 6, 2, 208,
    0 },

  { 105, "nlpidversion2/Main Subsystems/Naviagation/Navigation Switch/nu Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, nuSwitch), BLOCKIO_SIG, 20, 3, 2, 210,
    0 },

  { 106, "nlpidversion2/Main Subsystems/Control/DP control/Product2", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Product2), BLOCKIO_SIG, 20, 3, 2, 212, 0 },

  { 107, "nlpidversion2/Main Subsystems/Control/DP control/Sum1", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Sum1_f), BLOCKIO_SIG, 20, 3, 2, 214, 0 },

  { 108, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R11", 0, "",
    offsetof(BlockIO_NLPIDVersion2, R11_h), BLOCKIO_SIG, 0, 1, 2, 216, 0 },

  { 109, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R21", 0, "",
    offsetof(BlockIO_NLPIDVersion2, R21_c), BLOCKIO_SIG, 0, 1, 2, 218, 0 },

  { 110, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R12", 0, "",
    offsetof(BlockIO_NLPIDVersion2, R12_p), BLOCKIO_SIG, 0, 1, 2, 220, 0 },

  { 111, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/-1", 0, "",
    offsetof(BlockIO_NLPIDVersion2, u), BLOCKIO_SIG, 0, 1, 2, 222, 0 },

  { 112, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R22", 0, "",
    offsetof(BlockIO_NLPIDVersion2, R22_p), BLOCKIO_SIG, 0, 1, 2, 224, 0 },

  { 113, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R(psi)", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Rpsi), BLOCKIO_SIG, 22, 9, 2, 226, 0 },

  { 114,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/R(psi)/R^T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_m), BLOCKIO_SIG, 22, 9,
    2, 228, 0 },

  { 115,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_p), BLOCKIO_SIG, 0, 1, 2,
    230, 0 },

  { 116,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sign_f), BLOCKIO_SIG, 0, 1, 2, 232, 0
  },

  { 117,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_f), BLOCKIO_SIG, 0, 1, 2, 234, 0
  },

  { 118,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1_b), BLOCKIO_SIG, 0, 1, 2, 236, 0
  },

  { 119,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_p), BLOCKIO_SIG, 0, 1, 2,
    238, 0 },

  { 120,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_p), BLOCKIO_SIG, 0, 1, 2, 240, 0
  },

  { 121,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator",
    0, "", offsetof(BlockIO_NLPIDVersion2, Integrator_k), BLOCKIO_SIG, 25, 2, 2,
    242, 0 },

  { 122,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/x_2 - x_1",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_2x_1), BLOCKIO_SIG, 0, 1, 2, 244, 0
  },

  { 123,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/y_2 - y_1",
    0, "", offsetof(BlockIO_NLPIDVersion2, y_2y_1), BLOCKIO_SIG, 0, 1, 2, 246, 0
  },

  { 124,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_i), BLOCKIO_SIG, 0, 1, 2,
    248, 0 },

  { 125,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Rounding Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, RoundingFunction), BLOCKIO_SIG, 0, 1,
    2, 250, 0 },

  { 126,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_c), BLOCKIO_SIG, 25, 2, 2,
    252, 0 },

  { 127,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Integrator1), BLOCKIO_SIG, 0, 1, 2,
    254, 0 },

  { 128,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_i), BLOCKIO_SIG, 0, 1, 2,
    256, 0 },

  { 129,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/sin(s)",
    0, "", offsetof(BlockIO_NLPIDVersion2, sins), BLOCKIO_SIG, 0, 1, 2, 258, 0 },

  { 130,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_id), BLOCKIO_SIG, 0, 1, 2,
    260, 0 },

  { 131,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_k), BLOCKIO_SIG, 0, 1, 2, 262, 0
  },

  { 132,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/cos(s)",
    0, "", offsetof(BlockIO_NLPIDVersion2, coss), BLOCKIO_SIG, 0, 1, 2, 264, 0 },

  { 133,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_p), BLOCKIO_SIG, 0, 1, 2,
    266, 0 },

  { 134,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Subract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subract), BLOCKIO_SIG, 0, 1, 2, 268,
    0 },

  { 135,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_d), BLOCKIO_SIG, 25, 2, 2,
    270, 0 },

  { 136,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add), BLOCKIO_SIG, 25, 2, 2, 272, 0 },

  { 137,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, TrigonometricFunction), BLOCKIO_SIG,
    0, 1, 2, 274, 0 },

  { 138,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_o), BLOCKIO_SIG, 0, 1, 2,
    276, 0 },

  { 139,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sign_c), BLOCKIO_SIG, 0, 1, 2, 278, 0
  },

  { 140,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_a), BLOCKIO_SIG, 0, 1, 2, 280, 0
  },

  { 141,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1_fu), BLOCKIO_SIG, 0, 1, 2, 282,
    0 },

  { 142,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_c), BLOCKIO_SIG, 0, 1, 2,
    284, 0 },

  { 143,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_pi), BLOCKIO_SIG, 0, 1, 2, 286, 0
  },

  { 144,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_n), BLOCKIO_SIG, 0, 1, 2,
    288, 0 },

  { 145,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sign_hb), BLOCKIO_SIG, 0, 1, 2, 290,
    0 },

  { 146,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_l), BLOCKIO_SIG, 0, 1, 2, 292, 0
  },

  { 147,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1_n), BLOCKIO_SIG, 0, 1, 2, 294, 0
  },

  { 148,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_me), BLOCKIO_SIG, 0, 1,
    2, 296, 0 },

  { 149,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_e), BLOCKIO_SIG, 0, 1, 2, 298, 0
  },

  { 150,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2^T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_o), BLOCKIO_SIG, 24, 4,
    2, 300, 0 },

  { 151,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/x_2 - x_1",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_2x_1_j), BLOCKIO_SIG, 0, 1, 2, 302,
    0 },

  { 152,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_2x_1s), BLOCKIO_SIG, 0, 1, 2, 304,
    0 },

  { 153,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s + x_1",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_2x_1sx_1), BLOCKIO_SIG, 0, 1, 2,
    306, 0 },

  { 154,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/y_2 - y_1",
    0, "", offsetof(BlockIO_NLPIDVersion2, y_2y_1_j), BLOCKIO_SIG, 0, 1, 2, 308,
    0 },

  { 155,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s",
    0, "", offsetof(BlockIO_NLPIDVersion2, y_2y_1s), BLOCKIO_SIG, 0, 1, 2, 310,
    0 },

  { 156,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s + y_1",
    0, "", offsetof(BlockIO_NLPIDVersion2, y_2y_1sy_1), BLOCKIO_SIG, 0, 1, 2,
    312, 0 },

  { 157,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_b), BLOCKIO_SIG, 25, 2, 2,
    314, 0 },

  { 158,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_n), BLOCKIO_SIG, 0, 1, 2,
    316, 0 },

  { 159,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/cos(s)",
    0, "", offsetof(BlockIO_NLPIDVersion2, coss_p), BLOCKIO_SIG, 0, 1, 2, 318, 0
  },

  { 160,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_bm), BLOCKIO_SIG, 0, 1, 2,
    320, 0 },

  { 161,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_p), BLOCKIO_SIG, 0, 1, 2, 322, 0
  },

  { 162,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/sin(s)",
    0, "", offsetof(BlockIO_NLPIDVersion2, sins_k), BLOCKIO_SIG, 0, 1, 2, 324, 0
  },

  { 163,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_e), BLOCKIO_SIG, 0, 1, 2,
    326, 0 },

  { 164,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add1), BLOCKIO_SIG, 0, 1, 2, 328, 0 },

  { 165,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Subract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subract_c), BLOCKIO_SIG, 0, 1, 2, 330,
    0 },

  { 166,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_m), BLOCKIO_SIG, 25, 2, 2,
    332, 0 },

  { 167,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_n), BLOCKIO_SIG, 25, 2, 2, 334, 0
  },

  { 168,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch), BLOCKIO_SIG, 0, 1, 2, 336, 0
  },

  { 169,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch2), BLOCKIO_SIG, 0, 1, 2, 338,
    0 },

  { 170,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch_e), BLOCKIO_SIG, 0, 1, 2, 340,
    0 },

  { 171,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch2_b), BLOCKIO_SIG, 0, 1, 2, 342,
    0 },

  { 172,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract), BLOCKIO_SIG, 25, 2, 2, 344,
    0 },

  { 173,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon), BLOCKIO_SIG, 25, 2, 2, 346,
    0 },

  { 174,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector",
    0, "", offsetof(BlockIO_NLPIDVersion2, MultiportSelector), BLOCKIO_SIG, 31,
    1, 2, 348, 0 },

  { 175,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, TrigonometricFunction_m), BLOCKIO_SIG,
    31, 1, 2, 350, 0 },

  { 176,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_ns), BLOCKIO_SIG, 31, 1, 2,
    352, 0 },

  { 177,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sign_cn), BLOCKIO_SIG, 31, 1, 2, 354,
    0 },

  { 178,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_h), BLOCKIO_SIG, 31, 1, 2, 356,
    0 },

  { 179,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1_n1), BLOCKIO_SIG, 31, 1, 2, 358,
    0 },

  { 180,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_c5), BLOCKIO_SIG, 31, 1,
    2, 360, 0 },

  { 181,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_o), BLOCKIO_SIG, 31, 1, 2, 362, 0
  },

  { 182,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract_h), BLOCKIO_SIG, 0, 1, 2,
    364, 0 },

  { 183,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_a), BLOCKIO_SIG, 0, 1, 2,
    366, 0 },

  { 184,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sign",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sign_n), BLOCKIO_SIG, 0, 1, 2, 368, 0
  },

  { 185,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_ai), BLOCKIO_SIG, 0, 1, 2, 370,
    0 },

  { 186,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1_c), BLOCKIO_SIG, 0, 1, 2, 372, 0
  },

  { 187,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_g), BLOCKIO_SIG, 0, 1, 2,
    374, 0 },

  { 188,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_d), BLOCKIO_SIG, 0, 1, 2, 376, 0
  },

  { 189,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, VectorConcatenate), BLOCKIO_SIG, 20,
    3, 2, 378, 0 },

  { 190, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Subtract", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Subtract_f), BLOCKIO_SIG, 20, 3, 2, 380,
    0 },

  { 191,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_o4), BLOCKIO_SIG, 0, 1, 2,
    382, 0 },

  { 192,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sign_j), BLOCKIO_SIG, 0, 1, 2, 384, 0
  },

  { 193,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_ag), BLOCKIO_SIG, 0, 1, 2, 386,
    0 },

  { 194,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1_d), BLOCKIO_SIG, 0, 1, 2, 388, 0
  },

  { 195,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_j), BLOCKIO_SIG, 0, 1, 2,
    390, 0 },

  { 196,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e_1/Heading to -pi//pi1/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_a), BLOCKIO_SIG, 0, 1, 2, 392, 0
  },

  { 197,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_k), BLOCKIO_SIG, 20, 3, 2,
    394, 0 },

  { 198, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/zeta/Integrator",
    0, "", offsetof(BlockIO_NLPIDVersion2, Integrator_kk), BLOCKIO_SIG, 28, 3, 2,
    396, 0 },

  { 199,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_k), BLOCKIO_SIG, 28, 3, 2,
    398, 0 },

  { 200,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qx",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_qx), BLOCKIO_SIG, 0, 1, 2, 400, 0 },

  { 201,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qy",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_qy), BLOCKIO_SIG, 0, 1, 2, 402, 0 },

  { 202,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_kv), BLOCKIO_SIG, 25, 2, 2,
    404, 0 },

  { 203,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Delta^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Delta2), BLOCKIO_SIG, 0, 1, 2, 406, 0
  },

  { 204,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_n2), BLOCKIO_SIG, 31, 1, 2,
    408, 0 },

  { 205,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_o), BLOCKIO_SIG, 31, 1, 2, 410, 0
  },

  { 206,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide), BLOCKIO_SIG, 31, 1, 2, 412,
    0 },

  { 207,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector1",
    0, "", offsetof(BlockIO_NLPIDVersion2, MultiportSelector1), BLOCKIO_SIG, 29,
    2, 2, 414, 0 },

  { 208,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_ch), BLOCKIO_SIG, 29, 2, 2,
    416, 0 },

  { 209,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_o), BLOCKIO_SIG, 29, 2, 2, 418, 0 },

  { 210,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, VectorConcatenate_p), BLOCKIO_SIG, 20,
    3, 2, 420, 0 },

  { 211,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_ca), BLOCKIO_SIG, 32, 2, 2,
    422, 0 },

  { 212,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_b), BLOCKIO_SIG, 0, 1, 2,
    424, 0 },

  { 213,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/cos(s)",
    0, "", offsetof(BlockIO_NLPIDVersion2, coss_f), BLOCKIO_SIG, 0, 1, 2, 426, 0
  },

  { 214,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_mn), BLOCKIO_SIG, 0, 1,
    2, 428, 0 },

  { 215,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_a), BLOCKIO_SIG, 0, 1, 2, 430,
    0 },

  { 216,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_i), BLOCKIO_SIG, 0, 1, 2, 432, 0
  },

  { 217,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/sin(s)",
    0, "", offsetof(BlockIO_NLPIDVersion2, sins_m), BLOCKIO_SIG, 0, 1, 2, 434, 0
  },

  { 218,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_o), BLOCKIO_SIG, 0, 1, 2,
    436, 0 },

  { 219,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain1_h), BLOCKIO_SIG, 0, 1, 2, 438,
    0 },

  { 220,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Subract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subract_j), BLOCKIO_SIG, 0, 1, 2, 440,
    0 },

  { 221,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_kh), BLOCKIO_SIG, 25, 2, 2,
    442, 0 },

  { 222,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_l), BLOCKIO_SIG, 32, 2, 2, 444, 0
  },

  { 223,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_dsy_ds2), BLOCKIO_SIG, 31, 1, 2,
    446, 0 },

  { 224,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s^2 + y_d^s",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_ds2y_ds), BLOCKIO_SIG, 31, 1, 2,
    448, 0 },

  { 225,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s + y_d^s^2 ) - ( x_d^s^2 + y_d^s )",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_dsy_ds2x_ds2y_ds), BLOCKIO_SIG, 31,
    1, 2, 450, 0 },

  { 226,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_ds2), BLOCKIO_SIG, 0, 1, 2, 452, 0
  },

  { 227,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( y_d^s )^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, y_ds2), BLOCKIO_SIG, 0, 1, 2, 454, 0
  },

  { 228,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2 + ( y_d^s )^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_ds2y_ds2), BLOCKIO_SIG, 0, 1, 2,
    456, 0 },

  { 229,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_l), BLOCKIO_SIG, 31, 1, 2, 458,
    0 },

  { 230,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Delta^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Delta2_n), BLOCKIO_SIG, 0, 1, 2, 460,
    0 },

  { 231,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_n2_c), BLOCKIO_SIG, 31, 1, 2,
    462, 0 },

  { 232,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_m), BLOCKIO_SIG, 31, 1, 2, 464, 0
  },

  { 233,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_i), BLOCKIO_SIG, 31, 1, 2, 466,
    0 },

  { 234,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2^T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_d), BLOCKIO_SIG, 24, 4,
    2, 468, 0 },

  { 235,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_d), BLOCKIO_SIG, 25, 2, 2,
    470, 0 },

  { 236,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_h), BLOCKIO_SIG, 25, 2, 2,
    472, 0 },

  { 237,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Subtract1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract1), BLOCKIO_SIG, 25, 2, 2,
    474, 0 },

  { 238,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector2",
    0, "", offsetof(BlockIO_NLPIDVersion2, MultiportSelector2), BLOCKIO_SIG, 31,
    1, 2, 476, 0 },

  { 239,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_le), BLOCKIO_SIG, 31, 1, 2,
    478, 0 },

  { 240,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract_b), BLOCKIO_SIG, 31, 1, 2,
    480, 0 },

  { 241,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_n2_e), BLOCKIO_SIG, 31, 1, 2,
    482, 0 },

  { 242,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Delta^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Delta2_b), BLOCKIO_SIG, 0, 1, 2, 484,
    0 },

  { 243,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_ma), BLOCKIO_SIG, 31, 1, 2, 486,
    0 },

  { 244,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/sqrt",
    0, "", offsetof(BlockIO_NLPIDVersion2, sqrt_c), BLOCKIO_SIG, 31, 1, 2, 488,
    0 },

  { 245,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_m), BLOCKIO_SIG, 31, 1, 2, 490,
    0 },

  { 246,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_my), BLOCKIO_SIG, 29, 2,
    2, 492, 0 },

  { 247,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_o), BLOCKIO_SIG, 0, 1, 2, 494,
    0 },

  { 248,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_NLPIDVersion2, sqrt_d), BLOCKIO_SIG, 0, 1, 2, 496, 0
  },

  { 249,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_j), BLOCKIO_SIG, 0, 1, 2, 498,
    0 },

  { 250,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_e), BLOCKIO_SIG, 29, 2,
    2, 500, 0 },

  { 251,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_j0), BLOCKIO_SIG, 0, 1, 2,
    502, 0 },

  { 252,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_NLPIDVersion2, sqrt_b), BLOCKIO_SIG, 0, 1, 2, 504, 0
  },

  { 253,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Subract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subract_m), BLOCKIO_SIG, 0, 1, 2, 506,
    0 },

  { 254,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_a), BLOCKIO_SIG, 0, 1, 2,
    508, 0 },

  { 255,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_pj), BLOCKIO_SIG, 0, 1, 2, 510, 0
  },

  { 256,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_n), BLOCKIO_SIG, 0, 1, 2, 512,
    0 },

  { 257,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_h), BLOCKIO_SIG, 0, 1, 2, 514,
    0 },

  { 258,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_pb), BLOCKIO_SIG, 29, 2,
    2, 516, 0 },

  { 259,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_f), BLOCKIO_SIG, 29, 2, 2, 518,
    0 },

  { 260,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_ar), BLOCKIO_SIG, 0, 1, 2,
    520, 0 },

  { 261,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_hz), BLOCKIO_SIG, 0, 1, 2, 522,
    0 },

  { 262,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract_a), BLOCKIO_SIG, 0, 1, 2,
    524, 0 },

  { 263,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, VectorConcatenate_d), BLOCKIO_SIG, 28,
    3, 2, 526, 0 },

  { 264, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/v_d/Add", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Add_lh), BLOCKIO_SIG, 28, 3, 2, 528, 0 },

  { 265, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e2/Product", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Product_dv), BLOCKIO_SIG, 28, 3, 2, 530, 0 },

  { 266, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/e2/Subtract", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Subtract_e), BLOCKIO_SIG, 28, 3, 2, 532,
    0 },

  { 267,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_ie), BLOCKIO_SIG, 28, 3, 2,
    534, 0 },

  { 268,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_PID/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_j), BLOCKIO_SIG, 28, 3, 2, 536, 0
  },

  { 269,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FL/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_al), BLOCKIO_SIG, 20, 3, 2,
    538, 0 },

  { 270,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_NLPIDVersion2, TrigonometricFunction1), BLOCKIO_SIG,
    0, 1, 2, 540, 0 },

  { 271,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_e), BLOCKIO_SIG, 0, 1, 2, 542, 0
  },

  { 272,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_du), BLOCKIO_SIG, 29, 2, 2,
    544, 0 },

  { 273,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, TrigonometricFunction_l), BLOCKIO_SIG,
    0, 1, 2, 546, 0 },

  { 274,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_j), BLOCKIO_SIG, 29, 2, 2,
    548, 0 },

  { 275,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, MatrixConcatenate), BLOCKIO_SIG, 24,
    4, 2, 550, 0 },

  { 276,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_aw), BLOCKIO_SIG, 24, 4, 2,
    552, 0 },

  { 277,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/f_q^T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_k), BLOCKIO_SIG, 29, 2,
    2, 554, 0 },

  { 278,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_l), BLOCKIO_SIG, 31, 1, 2,
    556, 0 },

  { 279,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_h), BLOCKIO_SIG, 32, 2,
    2, 558, 0 },

  { 280,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product3",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product3), BLOCKIO_SIG, 24, 4, 2, 560,
    0 },

  { 281,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product4",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product4), BLOCKIO_SIG, 24, 4, 2, 562,
    0 },

  { 282,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_m), BLOCKIO_SIG, 24, 4, 2, 564, 0 },

  { 283,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Delta^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Delta2_g), BLOCKIO_SIG, 0, 1, 2, 566,
    0 },

  { 284,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_n2_i), BLOCKIO_SIG, 31, 1, 2,
    568, 0 },

  { 285,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_i), BLOCKIO_SIG, 31, 1, 2, 570, 0
  },

  { 286,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/( )^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_n), BLOCKIO_SIG, 31, 1, 2, 572, 0 },

  { 287,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_k), BLOCKIO_SIG, 24, 4, 2, 574,
    0 },

  { 288,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_i), BLOCKIO_SIG, 24, 4, 2,
    576, 0 },

  { 289,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide1), BLOCKIO_SIG, 24, 4, 2, 578,
    0 },

  { 290,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract_m), BLOCKIO_SIG, 24, 4, 2,
    580, 0 },

  { 291,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/psi_los^q^2T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_av), BLOCKIO_SIG, 24, 4,
    2, 582, 0 },

  { 292,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_hb), BLOCKIO_SIG, 29, 2, 2,
    584, 0 },

  { 293,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_mc), BLOCKIO_SIG, 29, 2, 2,
    586, 0 },

  { 294,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_d), BLOCKIO_SIG, 29, 2, 2, 588, 0
  },

  { 295,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, MatrixConcatenate_j), BLOCKIO_SIG, 30,
    6, 2, 590, 0 },

  { 296,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_f), BLOCKIO_SIG, 29, 2, 2,
    592, 0 },

  { 297,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_e), BLOCKIO_SIG, 29, 2, 2, 594, 0 },

  { 298,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Delta^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Delta2_o), BLOCKIO_SIG, 0, 1, 2, 596,
    0 },

  { 299,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_n2_ia), BLOCKIO_SIG, 31, 1, 2,
    598, 0 },

  { 300,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_ox), BLOCKIO_SIG, 31, 1, 2, 600,
    0 },

  { 301,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/( )^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_og), BLOCKIO_SIG, 31, 1, 2, 602, 0
  },

  { 302,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_e), BLOCKIO_SIG, 29, 2, 2, 604,
    0 },

  { 303,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_ez), BLOCKIO_SIG, 24, 4, 2,
    606, 0 },

  { 304,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector3",
    0, "", offsetof(BlockIO_NLPIDVersion2, MultiportSelector3), BLOCKIO_SIG, 29,
    2, 2, 608, 0 },

  { 305,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_ka), BLOCKIO_SIG, 29, 2, 2,
    610, 0 },

  { 306,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide1_a), BLOCKIO_SIG, 29, 2, 2,
    612, 0 },

  { 307,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract_n), BLOCKIO_SIG, 29, 2, 2,
    614, 0 },

  { 308,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_b4), BLOCKIO_SIG, 29, 2, 2,
    616, 0 },

  { 309,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_ex), BLOCKIO_SIG, 29, 2, 2,
    618, 0 },

  { 310,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_n2_iw), BLOCKIO_SIG, 31, 1, 2,
    620, 0 },

  { 311,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Delta^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Delta2_nh), BLOCKIO_SIG, 0, 1, 2, 622,
    0 },

  { 312,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_li), BLOCKIO_SIG, 31, 1, 2, 624,
    0 },

  { 313,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/^3//2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u2), BLOCKIO_SIG, 31, 1, 2, 626, 0 },

  { 314,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_b), BLOCKIO_SIG, 29, 2, 2, 628,
    0 },

  { 315,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_cm), BLOCKIO_SIG, 29, 2, 2,
    630, 0 },

  { 316,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_pj), BLOCKIO_SIG, 29, 2,
    2, 632, 0 },

  { 317,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_a), BLOCKIO_SIG, 29, 2, 2, 634,
    0 },

  { 318,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_la), BLOCKIO_SIG, 29, 2, 2,
    636, 0 },

  { 319,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_p), BLOCKIO_SIG, 29, 2, 2, 638,
    0 },

  { 320,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_f), BLOCKIO_SIG, 29, 2, 2, 640, 0
  },

  { 321,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_b), BLOCKIO_SIG, 29, 2, 2,
    642, 0 },

  { 322,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_mt), BLOCKIO_SIG, 29, 2, 2, 644,
    0 },

  { 323,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, MatrixConcatenate_k), BLOCKIO_SIG, 30,
    6, 2, 646, 0 },

  { 324, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/a_d/v_d^q/Add", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Add_g), BLOCKIO_SIG, 30, 6, 2, 648, 0 },

  { 325,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Integrator2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Integrator2), BLOCKIO_SIG, 25, 2, 2,
    650, 0 },

  { 326, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Add1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add1_f), BLOCKIO_SIG, 25, 2, 2, 652,
    0 },

  { 327, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/a_d/Product", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Product_ju), BLOCKIO_SIG, 20, 3, 2, 654,
    0 },

  { 328,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_NLPIDVersion2, TrigonometricFunction1_j),
    BLOCKIO_SIG, 0, 1, 2, 656, 0 },

  { 329,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_j), BLOCKIO_SIG, 0, 1, 2, 658, 0
  },

  { 330,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_ak), BLOCKIO_SIG, 31, 1, 2,
    660, 0 },

  { 331,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, TrigonometricFunction_n), BLOCKIO_SIG,
    0, 1, 2, 662, 0 },

  { 332,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_bn), BLOCKIO_SIG, 31, 1, 2,
    664, 0 },

  { 333,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_an), BLOCKIO_SIG, 25, 2, 2,
    666, 0 },

  { 334,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_jb), BLOCKIO_SIG, 0, 1, 2,
    668, 0 },

  { 335,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_aj), BLOCKIO_SIG, 0, 1, 2,
    670, 0 },

  { 336,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, VectorConcatenate_c), BLOCKIO_SIG, 20,
    3, 2, 672, 0 },

  { 337,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_bf), BLOCKIO_SIG, 32, 2, 2,
    674, 0 },

  { 338,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_e), BLOCKIO_SIG, 0, 1, 2,
    676, 0 },

  { 339,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/sin(s)3",
    0, "", offsetof(BlockIO_NLPIDVersion2, sins3), BLOCKIO_SIG, 0, 1, 2, 678, 0
  },

  { 340,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_i), BLOCKIO_SIG, 0, 1, 2,
    680, 0 },

  { 341,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_m), BLOCKIO_SIG, 0, 1, 2, 682,
    0 },

  { 342,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/cos(s)3",
    0, "", offsetof(BlockIO_NLPIDVersion2, coss3), BLOCKIO_SIG, 0, 1, 2, 684, 0
  },

  { 343,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_ou), BLOCKIO_SIG, 0, 1, 2,
    686, 0 },

  { 344,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_n), BLOCKIO_SIG, 0, 1, 2, 688, 0
  },

  { 345,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Subract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subract_k), BLOCKIO_SIG, 0, 1, 2, 690,
    0 },

  { 346,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_ic), BLOCKIO_SIG, 25, 2, 2,
    692, 0 },

  { 347,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_of), BLOCKIO_SIG, 32, 2, 2, 694,
    0 },

  { 348,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + y_d^s^3",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_dsy_ds3), BLOCKIO_SIG, 31, 1, 2,
    696, 0 },

  { 349,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s^3 + y_d^s",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_ds3y_ds), BLOCKIO_SIG, 31, 1, 2,
    698, 0 },

  { 350,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + y_d^s^3  ) - ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_dsy_ds3x_ds3y_ds), BLOCKIO_SIG, 31,
    1, 2, 700, 0 },

  { 351,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_dg), BLOCKIO_SIG, 31, 1, 2,
    702, 0 },

  { 352,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + x_d^s^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_dsx_ds2), BLOCKIO_SIG, 31, 1, 2,
    704, 0 },

  { 353,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/y_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, y_dsy_ds2), BLOCKIO_SIG, 31, 1, 2,
    706, 0 },

  { 354,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + x_d^s^2 ) + ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_dsx_ds2x_ds3y_ds), BLOCKIO_SIG, 31,
    1, 2, 708, 0 },

  { 355,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_k), BLOCKIO_SIG, 31, 1, 2, 710, 0 },

  { 356,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_ey), BLOCKIO_SIG, 31, 1, 2,
    712, 0 },

  { 357,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract_ar), BLOCKIO_SIG, 31, 1, 2,
    714, 0 },

  { 358,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, x_ds2y_ds22), BLOCKIO_SIG, 0, 1, 2,
    716, 0 },

  { 359,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_li), BLOCKIO_SIG, 31, 1, 2,
    718, 0 },

  { 360,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/(epsilon_n^s)^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_ns2), BLOCKIO_SIG, 31, 1, 2,
    720, 0 },

  { 361,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_lo), BLOCKIO_SIG, 31, 1, 2,
    722, 0 },

  { 362,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_p), BLOCKIO_SIG, 31, 1, 2, 724, 0 },

  { 363,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Delta^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Delta2_nhl), BLOCKIO_SIG, 0, 1, 2,
    726, 0 },

  { 364,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_n2_n), BLOCKIO_SIG, 31, 1, 2,
    728, 0 },

  { 365,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_dv), BLOCKIO_SIG, 31, 1, 2, 730,
    0 },

  { 366,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/( )^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_d), BLOCKIO_SIG, 31, 1, 2, 732, 0 },

  { 367,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_ng), BLOCKIO_SIG, 31, 1, 2,
    734, 0 },

  { 368,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_ce), BLOCKIO_SIG, 24, 4,
    2, 736, 0 },

  { 369,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_mi), BLOCKIO_SIG, 24, 4, 2,
    738, 0 },

  { 370,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_gb), BLOCKIO_SIG, 24, 4, 2, 740,
    0 },

  { 371,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_ph), BLOCKIO_SIG, 25, 2, 2,
    742, 0 },

  { 372,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_c), BLOCKIO_SIG, 25, 2, 2,
    744, 0 },

  { 373,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u_a), BLOCKIO_SIG, 25, 2, 2, 746, 0 },

  { 374,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product3",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product3_b), BLOCKIO_SIG, 32, 2, 2,
    748, 0 },

  { 375,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_m), BLOCKIO_SIG, 32, 2, 2, 750, 0
  },

  { 376,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_b), BLOCKIO_SIG, 32, 2, 2, 752,
    0 },

  { 377,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector4",
    0, "", offsetof(BlockIO_NLPIDVersion2, MultiportSelector4), BLOCKIO_SIG, 31,
    1, 2, 754, 0 },

  { 378,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_mi), BLOCKIO_SIG, 31, 1, 2,
    756, 0 },

  { 379,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide1_n), BLOCKIO_SIG, 31, 1, 2,
    758, 0 },

  { 380,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_k), BLOCKIO_SIG, 31, 1, 2, 760, 0
  },

  { 381,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_fu), BLOCKIO_SIG, 31, 1, 2,
    762, 0 },

  { 382,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_pg), BLOCKIO_SIG, 29, 2,
    2, 764, 0 },

  { 383,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_j), BLOCKIO_SIG, 31, 1, 2,
    766, 0 },

  { 384,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/|p_d^s|^3",
    0, "", offsetof(BlockIO_NLPIDVersion2, p_ds3), BLOCKIO_SIG, 0, 1, 2, 768, 0
  },

  { 385,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_lp), BLOCKIO_SIG, 31, 1, 2,
    770, 0 },

  { 386,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_p), BLOCKIO_SIG, 31, 1, 2,
    772, 0 },

  { 387,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_o), BLOCKIO_SIG, 31, 1, 2, 774,
    0 },

  { 388,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_n2_p), BLOCKIO_SIG, 31, 1, 2,
    776, 0 },

  { 389,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Delta^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Delta2_j), BLOCKIO_SIG, 0, 1, 2, 778,
    0 },

  { 390,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_b), BLOCKIO_SIG, 31, 1, 2, 780, 0
  },

  { 391,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_ds), BLOCKIO_SIG, 31, 1,
    2, 782, 0 },

  { 392,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_lpt), BLOCKIO_SIG, 31, 1, 2,
    784, 0 },

  { 393,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_ap), BLOCKIO_SIG, 31, 1, 2,
    786, 0 },

  { 394,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_e1), BLOCKIO_SIG, 31, 1, 2,
    788, 0 },

  { 395,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/^3//2",
    0, "", offsetof(BlockIO_NLPIDVersion2, u2_d), BLOCKIO_SIG, 31, 1, 2, 790, 0
  },

  { 396,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide1_no), BLOCKIO_SIG, 31, 1, 2,
    792, 0 },

  { 397,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product3",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product3_m), BLOCKIO_SIG, 31, 1, 2,
    794, 0 },

  { 398,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_n), BLOCKIO_SIG, 0, 1, 2,
    796, 0 },

  { 399,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_il), BLOCKIO_SIG, 29, 2,
    2, 798, 0 },

  { 400,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide2), BLOCKIO_SIG, 29, 2, 2, 800,
    0 },

  { 401,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_ht), BLOCKIO_SIG, 29, 2,
    2, 802, 0 },

  { 402,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_e1e), BLOCKIO_SIG, 29, 2, 2,
    804, 0 },

  { 403,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_c4), BLOCKIO_SIG, 0, 1,
    2, 806, 0 },

  { 404,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide1_o), BLOCKIO_SIG, 29, 2, 2,
    808, 0 },

  { 405,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract1_j), BLOCKIO_SIG, 29, 2, 2,
    810, 0 },

  { 406,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_hd), BLOCKIO_SIG, 0, 1, 2,
    812, 0 },

  { 407,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract_ny), BLOCKIO_SIG, 0, 1, 2,
    814, 0 },

  { 408,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_ax), BLOCKIO_SIG, 31, 1, 2, 816,
    0 },

  { 409,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_pf), BLOCKIO_SIG, 31, 1, 2,
    818, 0 },

  { 410,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, VectorConcatenate_j), BLOCKIO_SIG, 28,
    3, 2, 820, 0 },

  { 411, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/a_d/v_d^s/Add1", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Add1_d), BLOCKIO_SIG, 28, 3, 2, 822, 0 },

  { 412, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/a_d/Product1", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Product1_c), BLOCKIO_SIG, 20, 3, 2, 824,
    0 },

  { 413,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, TrigonometricFunction_h), BLOCKIO_SIG,
    0, 1, 2, 826, 0 },

  { 414,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_NLPIDVersion2, TrigonometricFunction1_g),
    BLOCKIO_SIG, 0, 1, 2, 828, 0 },

  { 415,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/Derivative",
    0, "", offsetof(BlockIO_NLPIDVersion2, Derivative_h), BLOCKIO_SIG, 0, 1, 2,
    830, 0 },

  { 416,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_ae), BLOCKIO_SIG, 25, 2, 2,
    832, 0 },

  { 417,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxilary functions g_q/g_q^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, VectorConcatenate_g), BLOCKIO_SIG, 20,
    3, 2, 834, 0 },

  { 418,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/epsilon_n^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, epsilon_n2_nb), BLOCKIO_SIG, 31, 1, 2,
    836, 0 },

  { 419,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Delta^2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Delta2_gb), BLOCKIO_SIG, 0, 1, 2, 838,
    0 },

  { 420,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Add",
    0, "", offsetof(BlockIO_NLPIDVersion2, Add_gm), BLOCKIO_SIG, 31, 1, 2, 840,
    0 },

  { 421,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/sqrt",
    0, "", offsetof(BlockIO_NLPIDVersion2, sqrt_p), BLOCKIO_SIG, 31, 1, 2, 842,
    0 },

  { 422,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_mc), BLOCKIO_SIG, 31, 1, 2,
    844, 0 },

  { 423,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^t eq/Divide",
    0, "", offsetof(BlockIO_NLPIDVersion2, Divide_d), BLOCKIO_SIG, 0, 1, 2, 846,
    0 },

  { 424,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_e), BLOCKIO_SIG, 31, 1, 2,
    848, 0 },

  { 425,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Auxiliary function g_s/g_s^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, VectorConcatenate_o), BLOCKIO_SIG, 28,
    3, 2, 850, 0 },

  { 426, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/a_d/v_d^t/Add", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Add_nb), BLOCKIO_SIG, 28, 3, 2, 852, 0 },

  { 427, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/a_d/Sum", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Sum_e2), BLOCKIO_SIG, 28, 3, 2, 854, 0 },

  { 428,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_d4), BLOCKIO_SIG, 28, 3, 2,
    856, 0 },

  { 429,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S12",
    0, "", offsetof(BlockIO_NLPIDVersion2, S12), BLOCKIO_SIG, 0, 1, 2, 858, 0 },

  { 430,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S(r)",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sr), BLOCKIO_SIG, 22, 9, 2, 860, 0 },

  { 431,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/S(r)^T/S^T/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_n), BLOCKIO_SIG, 22, 9,
    2, 862, 0 },

  { 432,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_l), BLOCKIO_SIG, 28, 3, 2,
    864, 0 },

  { 433,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/tau_FF/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract_j), BLOCKIO_SIG, 28, 3, 2,
    866, 0 },

  { 434, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Control law/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_fj), BLOCKIO_SIG, 28, 3, 2, 868,
    0 },

  { 435, "nlpidversion2/Main Subsystems/Control/Control Switch/tau Switch", 0,
    "", offsetof(BlockIO_NLPIDVersion2, tauSwitch), BLOCKIO_SIG, 28, 3, 2, 870,
    0 },

  { 436,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Matrix Concatenate",
    0, "", offsetof(BlockIO_NLPIDVersion2, MatrixConcatenate_b), BLOCKIO_SIG, 30,
    6, 2, 872, 0 },

  { 437,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Transpose/Math Function",
    0, "", offsetof(BlockIO_NLPIDVersion2, MathFunction_k1), BLOCKIO_SIG, 33, 6,
    2, 874, 0 },

  { 438,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_g), BLOCKIO_SIG, 25, 2, 2,
    876, 0 },

  { 439,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Product3",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product3_mf), BLOCKIO_SIG, 25, 2, 2,
    878, 0 },

  { 440,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Subtract",
    0, "", offsetof(BlockIO_NLPIDVersion2, Subtract_as), BLOCKIO_SIG, 25, 2, 2,
    880, 0 },

  { 441,
    "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Product4",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product4_m), BLOCKIO_SIG, 25, 2, 2,
    882, 0 },

  { 442, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/Update laws/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_pp), BLOCKIO_SIG, 25, 2, 2, 884,
    0 },

  { 443, "nlpidversion2/Main Subsystems/Control/Nonlinear PID/zeta/Product", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Product_og), BLOCKIO_SIG, 28, 3, 2, 886,
    0 },

  { 444,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_NLPIDVersion2, Pseudoinverse), BLOCKIO_SIG, 40, 15,
    2, 888, 0 },

  { 445,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product_m2), BLOCKIO_SIG, 36, 5, 2,
    890, 0 },

  { 446,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_1tou_1), BLOCKIO_SIG, 31, 1, 2, 892,
    0 },

  { 447,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_2000391), BLOCKIO_SIG, 31, 1, 2,
    894, 0 },

  { 448,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_2006731f_2000391), BLOCKIO_SIG, 31,
    1, 2, 896, 0 },

  { 449,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_2006731), BLOCKIO_SIG, 31, 1, 2,
    898, 0 },

  { 450,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, MultiportSwitch), BLOCKIO_SIG, 31, 1,
    2, 900, 0 },

  { 451,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_3tou_3), BLOCKIO_SIG, 31, 1, 2, 902,
    0 },

  { 452,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_400451), BLOCKIO_SIG, 31, 1, 2, 904,
    0 },

  { 453,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_400451_o), BLOCKIO_SIG, 31, 1, 2,
    906, 0 },

  { 454,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, MultiportSwitch_m), BLOCKIO_SIG, 31,
    1, 2, 908, 0 },

  { 455,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_NLPIDVersion2, DeadZone001), BLOCKIO_SIG, 31, 1, 2,
    910, 0 },

  { 456,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_50), BLOCKIO_SIG, 31, 1, 2, 912, 0
  },

  { 457,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0",
    0, "", offsetof(BlockIO_NLPIDVersion2, f_50_j), BLOCKIO_SIG, 31, 1, 2, 914,
    0 },

  { 458,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, MultiportSwitch_d), BLOCKIO_SIG, 31,
    1, 2, 916, 0 },

  { 459, "nlpidversion2/Main Subsystems/Control/Thruster allocation/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_j), BLOCKIO_SIG, 34, 7, 2,
    918, 0 },

  { 460,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error", 0,
    "", offsetof(BlockIO_NLPIDVersion2, QTMIn2Error), BLOCKIO_SIG, 31, 1, 2, 920,
    0 },

  { 461,
    "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual",
    0, "", offsetof(BlockIO_NLPIDVersion2, QTMIn9Residual), BLOCKIO_SIG, 31, 1,
    2, 922, 0 },

  { 462, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/Derivative1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Derivative1), BLOCKIO_SIG, 20, 3, 2,
    924, 0 },

  { 463,
    "nlpidversion2/Main Subsystems/Naviagation/Navigation Switch/etadot Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, etadotSwitch), BLOCKIO_SIG, 20, 3, 2,
    926, 0 },

  { 464,
    "nlpidversion2/Main Subsystems/Plant/Thruster setting workaround/Saturation",
    0, "", offsetof(BlockIO_NLPIDVersion2, Saturation_ja), BLOCKIO_SIG, 0, 1, 2,
    928, 0 },

  { 465,
    "nlpidversion2/Main Subsystems/Plant/Thruster setting workaround/tau Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, tauSwitch_m), BLOCKIO_SIG, 34, 7, 2,
    930, 0 },

  { 466,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate1",
    0, "", offsetof(BlockIO_NLPIDVersion2, VectorConcatenate1), BLOCKIO_SIG, 28,
    3, 2, 932, 0 },

  { 467, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/QTM In1 FPS",
    0, "", offsetof(BlockIO_NLPIDVersion2, QTMIn1FPS), BLOCKIO_SIG, 31, 1, 2,
    934, 0 },

  { 468, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/SIT zAI0", 0,
    "", offsetof(BlockIO_NLPIDVersion2, SITzAI0), BLOCKIO_SIG, 0, 1, 2, 936, 0 },

  { 469, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/SIT zAI1", 0,
    "", offsetof(BlockIO_NLPIDVersion2, SITzAI1), BLOCKIO_SIG, 0, 1, 2, 938, 0 },

  { 470, "nlpidversion2/Main Subsystems/Naviagation/Input from SIT/SIT zAI2", 0,
    "", offsetof(BlockIO_NLPIDVersion2, SITzAI2), BLOCKIO_SIG, 0, 1, 2, 940, 0 },

  { 471, "nlpidversion2/Main Subsystems/Plant/Inverse", 0, "", offsetof
    (BlockIO_NLPIDVersion2, Inverse), BLOCKIO_SIG, 22, 9, 2, 942, 0 },

  { 472, "nlpidversion2/Main Subsystems/Plant/saturation/Saturation", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Saturation_ay), BLOCKIO_SIG, 31, 1, 2, 944,
    0 },

  { 473, "nlpidversion2/Main Subsystems/Plant/saturation/Saturation1", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Saturation1), BLOCKIO_SIG, 31, 1, 2, 946, 0
  },

  { 474, "nlpidversion2/Main Subsystems/Plant/saturation/Saturation2", 0, "",
    offsetof(BlockIO_NLPIDVersion2, Saturation2), BLOCKIO_SIG, 31, 1, 2, 948, 0
  },

  { 475, "nlpidversion2/Main Subsystems/Plant/saturation/plant tau_surge", 0, "",
    offsetof(BlockIO_NLPIDVersion2, planttau_surge), BLOCKIO_SIG, 31, 1, 2, 950,
    0 },

  { 476, "nlpidversion2/Main Subsystems/Plant/saturation/plant tau_sway", 0, "",
    offsetof(BlockIO_NLPIDVersion2, planttau_sway), BLOCKIO_SIG, 31, 1, 2, 952,
    0 },

  { 477, "nlpidversion2/Main Subsystems/Plant/saturation/plant tau_yaw", 0, "",
    offsetof(BlockIO_NLPIDVersion2, planttau_yaw), BLOCKIO_SIG, 31, 1, 2, 954, 0
  },

  { 478, "nlpidversion2/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster",
    0, "", offsetof(BlockIO_NLPIDVersion2, BatteryBowThruster), BLOCKIO_SIG, 0,
    1, 2, 956, 0 },

  { 479, "nlpidversion2/Outputs to LabVIEW/Battery Voltage/Battery Main", 0, "",
    offsetof(BlockIO_NLPIDVersion2, BatteryMain), BLOCKIO_SIG, 0, 1, 2, 958, 0 },

  { 480, "nlpidversion2/Outputs to LabVIEW/Battery Voltage/Battery Servo", 0, "",
    offsetof(BlockIO_NLPIDVersion2, BatteryServo), BLOCKIO_SIG, 0, 1, 2, 960, 0
  },

  { 481, "nlpidversion2/Outputs to LabVIEW/Command/omega_qy", 0, "", offsetof
    (BlockIO_NLPIDVersion2, omega_qy), BLOCKIO_SIG, 0, 1, 2, 962, 0 },

  { 482, "nlpidversion2/Outputs to LabVIEW/Command/omegaqx", 0, "", offsetof
    (BlockIO_NLPIDVersion2, omegaqx), BLOCKIO_SIG, 0, 1, 2, 964, 0 },

  { 483, "nlpidversion2/Outputs to LabVIEW/Command/plant BT power", 0, "",
    offsetof(BlockIO_NLPIDVersion2, plantBTpower), BLOCKIO_SIG, 0, 1, 2, 966, 0
  },

  { 484, "nlpidversion2/Outputs to LabVIEW/Command/plant VSP speed", 0, "",
    offsetof(BlockIO_NLPIDVersion2, plantVSPspeed), BLOCKIO_SIG, 0, 1, 2, 968, 0
  },

  { 485, "nlpidversion2/Outputs to LabVIEW/Command/plant u_1", 0, "", offsetof
    (BlockIO_NLPIDVersion2, plantu_1), BLOCKIO_SIG, 0, 1, 2, 970, 0 },

  { 486, "nlpidversion2/Outputs to LabVIEW/Command/plant u_2", 0, "", offsetof
    (BlockIO_NLPIDVersion2, plantu_2), BLOCKIO_SIG, 0, 1, 2, 972, 0 },

  { 487, "nlpidversion2/Outputs to LabVIEW/Command/plant u_3", 0, "", offsetof
    (BlockIO_NLPIDVersion2, plantu_3), BLOCKIO_SIG, 0, 1, 2, 974, 0 },

  { 488, "nlpidversion2/Outputs to LabVIEW/Command/plant u_4", 0, "", offsetof
    (BlockIO_NLPIDVersion2, plantu_4), BLOCKIO_SIG, 0, 1, 2, 976, 0 },

  { 489, "nlpidversion2/Outputs to LabVIEW/Command/plant u_5", 0, "", offsetof
    (BlockIO_NLPIDVersion2, plantu_5), BLOCKIO_SIG, 0, 1, 2, 978, 0 },

  { 490, "nlpidversion2/Outputs to LabVIEW/Command/fact1", 0, "", offsetof
    (BlockIO_NLPIDVersion2, fact1), BLOCKIO_SIG, 31, 1, 2, 980, 0 },

  { 491, "nlpidversion2/Outputs to LabVIEW/Command/fact2", 0, "", offsetof
    (BlockIO_NLPIDVersion2, fact2), BLOCKIO_SIG, 31, 1, 2, 982, 0 },

  { 492, "nlpidversion2/Outputs to LabVIEW/Command/fact3", 0, "", offsetof
    (BlockIO_NLPIDVersion2, fact3), BLOCKIO_SIG, 31, 1, 2, 984, 0 },

  { 493, "nlpidversion2/Outputs to LabVIEW/Command/fact4", 0, "", offsetof
    (BlockIO_NLPIDVersion2, fact4), BLOCKIO_SIG, 31, 1, 2, 986, 0 },

  { 494, "nlpidversion2/Outputs to LabVIEW/Command/fact5", 0, "", offsetof
    (BlockIO_NLPIDVersion2, fact5), BLOCKIO_SIG, 31, 1, 2, 988, 0 },

  { 495, "nlpidversion2/Outputs to LabVIEW/Command/taux", 0, "", offsetof
    (BlockIO_NLPIDVersion2, taux), BLOCKIO_SIG, 31, 1, 2, 990, 0 },

  { 496, "nlpidversion2/Outputs to LabVIEW/Command/tauy", 0, "", offsetof
    (BlockIO_NLPIDVersion2, tauy), BLOCKIO_SIG, 31, 1, 2, 992, 0 },

  { 497, "nlpidversion2/Outputs to LabVIEW/Command/tauyaw", 0, "", offsetof
    (BlockIO_NLPIDVersion2, tauyaw), BLOCKIO_SIG, 31, 1, 2, 994, 0 },

  { 498, "nlpidversion2/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, CSE1_rdegs), BLOCKIO_SIG, 0, 1, 2, 996, 0 },

  { 499, "nlpidversion2/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, CSE1_ums), BLOCKIO_SIG, 0, 1, 2, 998, 0 },

  { 500, "nlpidversion2/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, CSE1_vms), BLOCKIO_SIG, 0, 1, 2, 1000, 0 },

  { 501, "nlpidversion2/Outputs to LabVIEW/Visualization/Sum", 0, "", offsetof
    (BlockIO_NLPIDVersion2, Sum_fc), BLOCKIO_SIG, 20, 3, 2, 1002, 0 },

  { 502, "nlpidversion2/Outputs to LabVIEW/Visualization/Sum1", 0, "", offsetof
    (BlockIO_NLPIDVersion2, Sum1_nv), BLOCKIO_SIG, 20, 3, 2, 1004, 0 },

  { 503, "nlpidversion2/Outputs to LabVIEW/Visualization/Sum2", 0, "", offsetof
    (BlockIO_NLPIDVersion2, Sum2_o), BLOCKIO_SIG, 20, 3, 2, 1006, 0 },

  { 504, "nlpidversion2/Outputs to LabVIEW/Visualization/psi [deg]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, psideg), BLOCKIO_SIG, 0, 1, 2, 1008, 0 },

  { 505, "nlpidversion2/Outputs to LabVIEW/Visualization/psi-psid [deg]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, psipsiddeg), BLOCKIO_SIG, 0, 1, 2, 1010, 0 },

  { 506, "nlpidversion2/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]", 0,
    "", offsetof(BlockIO_NLPIDVersion2, psiLOSpsideg), BLOCKIO_SIG, 0, 1, 2,
    1012, 0 },

  { 507, "nlpidversion2/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]", 0,
    "", offsetof(BlockIO_NLPIDVersion2, psiLOSpsiddeg), BLOCKIO_SIG, 0, 1, 2,
    1014, 0 },

  { 508, "nlpidversion2/Outputs to LabVIEW/Visualization/psi_LOS [deg]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, psi_LOSdeg), BLOCKIO_SIG, 0, 1, 2, 1016, 0 },

  { 509, "nlpidversion2/Outputs to LabVIEW/Visualization/psid [deg]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, psiddeg), BLOCKIO_SIG, 0, 1, 2, 1018, 0 },

  { 510, "nlpidversion2/Outputs to LabVIEW/Visualization/psi_plot", 0, "",
    offsetof(BlockIO_NLPIDVersion2, psi_plot), BLOCKIO_SIG, 20, 3, 2, 1020, 0 },

  { 511, "nlpidversion2/Outputs to LabVIEW/Visualization/qx [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, qxm), BLOCKIO_SIG, 0, 1, 2, 1022, 0 },

  { 512, "nlpidversion2/Outputs to LabVIEW/Visualization/qx-x [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, qxxm), BLOCKIO_SIG, 0, 1, 2, 1024, 0 },

  { 513, "nlpidversion2/Outputs to LabVIEW/Visualization/qx-xd [m]1", 0, "",
    offsetof(BlockIO_NLPIDVersion2, qxxdm1), BLOCKIO_SIG, 0, 1, 2, 1026, 0 },

  { 514, "nlpidversion2/Outputs to LabVIEW/Visualization/qy [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, qym), BLOCKIO_SIG, 0, 1, 2, 1028, 0 },

  { 515, "nlpidversion2/Outputs to LabVIEW/Visualization/qy-y [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, qyym), BLOCKIO_SIG, 0, 1, 2, 1030, 0 },

  { 516, "nlpidversion2/Outputs to LabVIEW/Visualization/qy-yd [m]1", 0, "",
    offsetof(BlockIO_NLPIDVersion2, qyydm1), BLOCKIO_SIG, 0, 1, 2, 1032, 0 },

  { 517, "nlpidversion2/Outputs to LabVIEW/Visualization/x [m]", 0, "", offsetof
    (BlockIO_NLPIDVersion2, xm), BLOCKIO_SIG, 0, 1, 2, 1034, 0 },

  { 518, "nlpidversion2/Outputs to LabVIEW/Visualization/x-xd [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, xxdm), BLOCKIO_SIG, 0, 1, 2, 1036, 0 },

  { 519, "nlpidversion2/Outputs to LabVIEW/Visualization/xd [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, xdm), BLOCKIO_SIG, 0, 1, 2, 1038, 0 },

  { 520, "nlpidversion2/Outputs to LabVIEW/Visualization/x_plot", 0, "",
    offsetof(BlockIO_NLPIDVersion2, x_plot), BLOCKIO_SIG, 20, 3, 2, 1040, 0 },

  { 521, "nlpidversion2/Outputs to LabVIEW/Visualization/y [m]", 0, "", offsetof
    (BlockIO_NLPIDVersion2, ym), BLOCKIO_SIG, 0, 1, 2, 1042, 0 },

  { 522, "nlpidversion2/Outputs to LabVIEW/Visualization/y-yd [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, yydm), BLOCKIO_SIG, 0, 1, 2, 1044, 0 },

  { 523, "nlpidversion2/Outputs to LabVIEW/Visualization/yd [m]", 0, "",
    offsetof(BlockIO_NLPIDVersion2, ydm), BLOCKIO_SIG, 0, 1, 2, 1046, 0 },

  { 524, "nlpidversion2/Outputs to LabVIEW/Visualization/y_plot", 0, "",
    offsetof(BlockIO_NLPIDVersion2, y_plot), BLOCKIO_SIG, 20, 3, 2, 1048, 0 },

  { 525,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator",
    0, "", offsetof(BlockIO_NLPIDVersion2, Integrator_d), BLOCKIO_SIG, 20, 3, 2,
    1050, 0 },

  { 526,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Integrator1_n), BLOCKIO_SIG, 20, 3, 2,
    1052, 0 },

  { 527,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R11",
    0, "", offsetof(BlockIO_NLPIDVersion2, R11_p), BLOCKIO_SIG, 0, 1, 2, 1054, 0
  },

  { 528,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R21",
    0, "", offsetof(BlockIO_NLPIDVersion2, R21_b), BLOCKIO_SIG, 0, 1, 2, 1056, 0
  },

  { 529,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R12",
    0, "", offsetof(BlockIO_NLPIDVersion2, R12_o), BLOCKIO_SIG, 0, 1, 2, 1058, 0
  },

  { 530,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R22",
    0, "", offsetof(BlockIO_NLPIDVersion2, R22_px), BLOCKIO_SIG, 0, 1, 2, 1060,
    0 },

  { 531,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R(psi)",
    0, "", offsetof(BlockIO_NLPIDVersion2, Rpsi_b), BLOCKIO_SIG, 22, 9, 2, 1062,
    0 },

  { 532,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product3",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product3_mm), BLOCKIO_SIG, 20, 3, 2,
    1064, 0 },

  { 533,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product1_dk), BLOCKIO_SIG, 20, 3, 2,
    1066, 0 },

  { 534,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_lb), BLOCKIO_SIG, 20, 3, 2, 1068,
    0 },

  { 535,
    "nlpidversion2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Product2_ca), BLOCKIO_SIG, 20, 3, 2,
    1070, 0 },

  { 536,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1",
    0, "", offsetof(BlockIO_NLPIDVersion2, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1072, 0 },

  { 537,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2",
    0, "", offsetof(BlockIO_NLPIDVersion2, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1074, 0 },

  { 538, "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Add", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Add_e), BLOCKIO_SIG, 0, 1, 2, 1076, 0 },

  { 539,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1",
    0, "", offsetof(BlockIO_NLPIDVersion2, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1078, 0 },

  { 540,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2",
    0, "", offsetof(BlockIO_NLPIDVersion2, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1080, 0 },

  { 541, "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg", 0,
    "", offsetof(BlockIO_NLPIDVersion2, Neg), BLOCKIO_SIG, 0, 1, 2, 1082, 0 },

  { 542, "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1_cw), BLOCKIO_SIG, 0, 1, 2, 1084,
    0 },

  { 543, "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum2_d), BLOCKIO_SIG, 0, 1, 2, 1086,
    0 },

  { 544,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch_k), BLOCKIO_SIG, 0, 1, 2, 1088,
    0 },

  { 545,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch2_o), BLOCKIO_SIG, 0, 1, 2,
    1090, 0 },

  { 546,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch_g), BLOCKIO_SIG, 0, 1, 2, 1092,
    0 },

  { 547,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch2_n), BLOCKIO_SIG, 0, 1, 2,
    1094, 0 },

  { 548,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch_b), BLOCKIO_SIG, 0, 1, 2, 1096,
    0 },

  { 549,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Switch2_g), BLOCKIO_SIG, 0, 1, 2,
    1098, 0 },

  { 550,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sign",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sign_i), BLOCKIO_SIG, 0, 1, 2, 1100,
    0 },

  { 551,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product1",
    0, "Port VPS_X", offsetof(BlockIO_NLPIDVersion2, PortVPS_X), BLOCKIO_SIG, 0,
    1, 2, 1102, 0 },

  { 552,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x",
    0, "Port VPS_X", offsetof(BlockIO_NLPIDVersion2, PortVPS_X_e), BLOCKIO_SIG,
    0, 1, 2, 1104, 0 },

  { 553,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product2",
    0, "Port VSP_Y", offsetof(BlockIO_NLPIDVersion2, PortVSP_Y), BLOCKIO_SIG, 0,
    1, 2, 1106, 0 },

  { 554,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y",
    0, "Port VSP_Y", offsetof(BlockIO_NLPIDVersion2, PortVSP_Y_m), BLOCKIO_SIG,
    0, 1, 2, 1108, 0 },

  { 555,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product3",
    0, "Starboard VSP_X", offsetof(BlockIO_NLPIDVersion2, StarboardVSP_X),
    BLOCKIO_SIG, 0, 1, 2, 1110, 0 },

  { 556,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product4",
    0, "Starboard VSP_Y", offsetof(BlockIO_NLPIDVersion2, StarboardVSP_Y),
    BLOCKIO_SIG, 0, 1, 2, 1112, 0 },

  { 557,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Servo1), BLOCKIO_SIG, 0, 1, 2, 1114,
    0 },

  { 558,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2",
    0, "", offsetof(BlockIO_NLPIDVersion2, Servo2), BLOCKIO_SIG, 0, 1, 2, 1116,
    0 },

  { 559,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3",
    0, "", offsetof(BlockIO_NLPIDVersion2, Servo3), BLOCKIO_SIG, 0, 1, 2, 1118,
    0 },

  { 560,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4",
    0, "", offsetof(BlockIO_NLPIDVersion2, Servo4), BLOCKIO_SIG, 0, 1, 2, 1120,
    0 },

  { 561,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2,
    1122, 0 },

  { 562,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_c), BLOCKIO_SIG, 0, 1, 2, 1124, 0
  },

  { 563,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port",
    0, "", offsetof(BlockIO_NLPIDVersion2, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 1126,
    0 },

  { 564,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard",
    0, "", offsetof(BlockIO_NLPIDVersion2, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2,
    1128, 0 },

  { 565,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12",
    0, "", offsetof(BlockIO_NLPIDVersion2, S12_c), BLOCKIO_SIG, 31, 1, 2, 1130,
    0 },

  { 566,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S_2(psi_d^s^2)",
    0, "", offsetof(BlockIO_NLPIDVersion2, S_2psi_ds2), BLOCKIO_SIG, 24, 4, 2,
    1132, 0 },

  { 567,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12",
    0, "", offsetof(BlockIO_NLPIDVersion2, S12_b), BLOCKIO_SIG, 31, 1, 2, 1134,
    0 },

  { 568,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S_2(psi_d^s)",
    0, "", offsetof(BlockIO_NLPIDVersion2, S_2psi_ds), BLOCKIO_SIG, 24, 4, 2,
    1136, 0 },

  { 569,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R11",
    0, "", offsetof(BlockIO_NLPIDVersion2, R11_j), BLOCKIO_SIG, 0, 1, 2, 1138, 0
  },

  { 570,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R21",
    0, "", offsetof(BlockIO_NLPIDVersion2, R21_f), BLOCKIO_SIG, 0, 1, 2, 1140, 0
  },

  { 571,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12",
    0, "", offsetof(BlockIO_NLPIDVersion2, R12_d), BLOCKIO_SIG, 0, 1, 2, 1142, 0
  },

  { 572,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22",
    0, "", offsetof(BlockIO_NLPIDVersion2, R22_j), BLOCKIO_SIG, 0, 1, 2, 1144, 0
  },

  { 573,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R_2(psi_d)",
    0, "", offsetof(BlockIO_NLPIDVersion2, R_2psi_d), BLOCKIO_SIG, 24, 4, 2,
    1146, 0 },

  { 574,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain1_g), BLOCKIO_SIG, 38, 1, 2, 1148,
    0 },

  { 575,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_cg), BLOCKIO_SIG, 38, 1, 2, 1150,
    0 },

  { 576,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_m), BLOCKIO_SIG, 38, 1, 2, 1152,
    0 },

  { 577,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_e5), BLOCKIO_SIG, 38, 1, 2, 1154,
    0 },

  { 578,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain_bl), BLOCKIO_SIG, 38, 1, 2, 1156,
    0 },

  { 579,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Gain1_c), BLOCKIO_SIG, 38, 1, 2, 1158,
    0 },

  { 580,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum_lj), BLOCKIO_SIG, 38, 1, 2, 1160,
    0 },

  { 581,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_NLPIDVersion2, Compare), BLOCKIO_SIG, 37, 1, 2, 1162,
    0 },

  { 582,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_NLPIDVersion2, Compare_o), BLOCKIO_SIG, 37, 1, 2,
    1164, 0 },

  { 583,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_NLPIDVersion2, Compare_c), BLOCKIO_SIG, 37, 1, 2,
    1166, 0 },

  { 584,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_NLPIDVersion2, Sum1_l), BLOCKIO_SIG, 37, 1, 2, 1168,
    0 },

  { 585,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_NLPIDVersion2, Compare_f), BLOCKIO_SIG, 37, 1, 2,
    1170, 0 },

  { 586,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_NLPIDVersion2, Compare_b), BLOCKIO_SIG, 37, 1, 2,
    1172, 0 },

  { 587,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_NLPIDVersion2, Compare_m), BLOCKIO_SIG, 37, 1, 2,
    1174, 0 },

  { 588,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_NLPIDVersion2, Compare_p), BLOCKIO_SIG, 37, 1, 2,
    1176, 0 },

  { 589,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_NLPIDVersion2, Compare_oc), BLOCKIO_SIG, 37, 1, 2,
    1178, 0 },

  { 590,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_NLPIDVersion2, Compare_a), BLOCKIO_SIG, 37, 1, 2,
    1180, 0 },

  { 591,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/LowerRelop1",
    0, "", offsetof(BlockIO_NLPIDVersion2, LowerRelop1), BLOCKIO_SIG, 8, 1, 2,
    1182, 0 },

  { 592,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/UpperRelop",
    0, "", offsetof(BlockIO_NLPIDVersion2, UpperRelop), BLOCKIO_SIG, 8, 1, 2,
    1184, 0 },

  { 593,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/LowerRelop1",
    0, "", offsetof(BlockIO_NLPIDVersion2, LowerRelop1_a), BLOCKIO_SIG, 8, 1, 2,
    1186, 0 },

  { 594,
    "nlpidversion2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/UpperRelop",
    0, "", offsetof(BlockIO_NLPIDVersion2, UpperRelop_e), BLOCKIO_SIG, 8, 1, 2,
    1188, 0 },

  { 595,
    "nlpidversion2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_NLPIDVersion2, LogicalOperator), BLOCKIO_SIG, 39, 1,
    2, 1190, 0 },

  { 596,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_NLPIDVersion2, LowerRelop1_j), BLOCKIO_SIG, 8, 1, 2,
    1192, 0 },

  { 597,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_NLPIDVersion2, UpperRelop_f), BLOCKIO_SIG, 8, 1, 2,
    1194, 0 },

  { 598,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/LowerRelop1",
    0, "", offsetof(BlockIO_NLPIDVersion2, LowerRelop1_l), BLOCKIO_SIG, 8, 1, 2,
    1196, 0 },

  { 599,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/UpperRelop",
    0, "", offsetof(BlockIO_NLPIDVersion2, UpperRelop_b), BLOCKIO_SIG, 8, 1, 2,
    1198, 0 },

  { 600,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/LowerRelop1",
    0, "", offsetof(BlockIO_NLPIDVersion2, LowerRelop1_n), BLOCKIO_SIG, 8, 1, 2,
    1200, 0 },

  { 601,
    "nlpidversion2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/UpperRelop",
    0, "", offsetof(BlockIO_NLPIDVersion2, UpperRelop_m), BLOCKIO_SIG, 8, 1, 2,
    1202, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
  3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 5,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3,
  1, 1, 1, 1, 1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 3, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 6, 6, 1, 1, 1, 1, 1, 6,
  1, 6, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 2, 1, 2, 1, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2,
  1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 2, 3, 2,
  1, 2, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 2, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2,
  1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
  1, 1, 3, 3, 3, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 2, 2, 3, 1, 2, 1, 2, 1, 2, 1, 2,
  1, 2, 3, 1, 5, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 7, 3, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 3,
  1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize = 11;
static NI_ExternalIO NI_ExtList[] = {
  { 0, "Main Subsystems/Naviagation/Input from SIT/QTM In", 0, EXT_IN, 9, 9, 1 },

  { 1, "Main Subsystems/Naviagation/Input from SIT/SIT zAI0", 1, EXT_IN, 1, 1, 1
  },

  { 2, "Main Subsystems/Naviagation/Input from SIT/SIT zAI1", 1, EXT_IN, 1, 1, 1
  },

  { 3, "Main Subsystems/Naviagation/Input from SIT/SIT zAI2", 1, EXT_IN, 1, 1, 1
  },

  { 0, "Main Subsystems/Plant/CSE1 actuator/Bow Thruster/SIT PWM0 BT", 0,
    EXT_OUT, 1, 1, 1 },

  { 1,
    "Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1",
    0, EXT_OUT, 1, 1, 1 },

  { 2,
    "Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2",
    0, EXT_OUT, 1, 1, 1 },

  { 3,
    "Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3",
    0, EXT_OUT, 1, 1, 1 },

  { 4,
    "Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4",
    0, EXT_OUT, 1, 1, 1 },

  { 5,
    "Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port",
    0, EXT_OUT, 1, 1, 1 },

  { 6,
    "Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard",
    0, EXT_OUT, 1, 1, 1 },

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

static char* NI_CompiledModelName = "nlpidversion2";
static char* NI_CompiledModelVersion = "1.89";
static char* NI_CompiledModelDateTime = "Mon Mar 24 18:40:26 2014";

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
   The undef allows us to access the real NLPIDVersion2_P
   In the rest of the code NLPIDVersion2_P is redefine to be the read-side
   of rtParameter.
 */
#undef NLPIDVersion2_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &NLPIDVersion2_P, sizeof(Parameters_NLPIDVersion2));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka NLPIDVersion2_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_NLPIDVersion2));
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
             (Parameters_NLPIDVersion2));

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
           (Parameters_NLPIDVersion2));
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

#endif                                 // of NI_ROOTMODEL_NLPIDVersion2
