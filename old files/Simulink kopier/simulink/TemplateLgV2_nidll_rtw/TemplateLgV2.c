/*
 * TemplateLgV2.c
 *
 * Real-Time Workshop code generation for Simulink model "TemplateLgV2.mdl".
 *
 * Model Version              : 1.114
 * Real-Time Workshop version : 7.3  (R2009a)  15-Jan-2009
 * C source code generated on : Sun Mar 30 09:44:38 2014
 *
 * Target selection: nidll.tlc
 *   Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TemplateLgV2.h"
#include "TemplateLgV2_private.h"

/* Block signals (auto storage) */
BlockIO_TemplateLgV2 TemplateLgV2_B;

/* Continuous states */
ContinuousStates_TemplateLgV2 TemplateLgV2_X;

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
D_Work_TemplateLgV2 TemplateLgV2_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_TemplateLgV2 TemplateLgV2_PrevZCSigState;

/* Real-time model */
RT_MODEL_TemplateLgV2 TemplateLgV2_M_;
RT_MODEL_TemplateLgV2 *TemplateLgV2_M = &TemplateLgV2_M_;

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
  int_T nXc = 26;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y,x,
                nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  TemplateLgV2_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  TemplateLgV2_output(0);
  TemplateLgV2_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++)
    hB[i] = h * rt_ODE5_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  TemplateLgV2_output(0);
  TemplateLgV2_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++)
    hB[i] = h * rt_ODE5_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  TemplateLgV2_output(0);
  TemplateLgV2_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++)
    hB[i] = h * rt_ODE5_B[3][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  TemplateLgV2_output(0);
  TemplateLgV2_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++)
    hB[i] = h * rt_ODE5_B[4][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  TemplateLgV2_output(0);
  TemplateLgV2_derivatives();

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
void TemplateLgV2_output(int_T tid)
{
  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(TemplateLgV2_M)) {
    TemplateLgV2_M->Timing.t[0] = rtsiGetT(&TemplateLgV2_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&TemplateLgV2_M->solverInfo,
                          ((TemplateLgV2_M->Timing.clockTick0+1)*
      TemplateLgV2_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  {
    real_T tmp;
    real_T tmp_0[7];
    int32_T i;
    real_T tmp_1[9];
    real_T tmp_2[4];
    real_T tmp_3[6];
    real_T tmp_4[3];
    real_T tmp_5[18];
    int32_T tmp_6;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Constant: '<S1>/tauxscale' */
      TemplateLgV2_B.tauxscale = TemplateLgV2_P.tauxscale_Value;

      /* Constant: '<S1>/tauyscale' */
      TemplateLgV2_B.tauyscale = TemplateLgV2_P.tauyscale_Value;

      /* Constant: '<S1>/tauyawscale' */
      TemplateLgV2_B.tauyawscale = TemplateLgV2_P.tauyawscale_Value;

      /* Constant: '<S4>/Initial psi [rad]' */
      TemplateLgV2_B.Initialpsirad = TemplateLgV2_P.Initialpsirad_Value;

      /* Constant: '<S4>/Initial x [m]' */
      TemplateLgV2_B.Initialxm = TemplateLgV2_P.Initialxm_Value;

      /* Constant: '<S4>/Initial y [m]' */
      TemplateLgV2_B.Initialym = TemplateLgV2_P.Initialym_Value;

      /* Constant: '<S4>/Initial r [rad//s]' */
      TemplateLgV2_B.Initialrrads = TemplateLgV2_P.Initialrrads_Value;

      /* Constant: '<S4>/Initial u [m//s]' */
      TemplateLgV2_B.Initialums = TemplateLgV2_P.Initialums_Value;

      /* Constant: '<S4>/Initial v [m//s]' */
      TemplateLgV2_B.Initialvms = TemplateLgV2_P.Initialvms_Value;

      /* Gain: '<S6>/ScalingLX' incorporates:
       *  Constant: '<S6>/AS_LX [-] '
       */
      TemplateLgV2_B.xpositionofleftanalogstick11 =
        TemplateLgV2_P.ScalingLX_Gain * TemplateLgV2_P.AS_LX_Value;

      /* Gain: '<S6>/ScalingLY' incorporates:
       *  Constant: '<S6>/AS_LY [-]'
       */
      TemplateLgV2_B.ypositionofleftanalogstick11 =
        TemplateLgV2_P.ScalingLY_Gain * TemplateLgV2_P.AS_LY_Value;

      /* Gain: '<S6>/Scaling_RX' incorporates:
       *  Constant: '<S6>/AS_RX [-]'
       */
      TemplateLgV2_B.xpositionofrightanalogstick11 =
        TemplateLgV2_P.Scaling_RX_Gain * TemplateLgV2_P.AS_RX_Value;

      /* Gain: '<S6>/ScalingRY' incorporates:
       *  Constant: '<S6>/AS_RY [-]'
       */
      TemplateLgV2_B.ypositionofrightanalogstick11 =
        TemplateLgV2_P.ScalingRY_Gain * TemplateLgV2_P.AS_RY_Value;

      /* Gain: '<S12>/Gain1' incorporates:
       *  Constant: '<S7>/setpointpsi [deg]'
       */
      TemplateLgV2_B.Gain1 = TemplateLgV2_P.Gain1_Gain *
        TemplateLgV2_P.setpointpsideg_Value;

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
      TemplateLgV2_B.ux3[0] = TemplateLgV2_P.ctrl1Kdx_Value;
      TemplateLgV2_B.ux3[1] = TemplateLgV2_P.u_Value_o;
      TemplateLgV2_B.ux3[2] = TemplateLgV2_P.u_Value_a;
      TemplateLgV2_B.ux3[3] = TemplateLgV2_P.u_Value;
      TemplateLgV2_B.ux3[4] = TemplateLgV2_P.ctrl1Kdy_Value;
      TemplateLgV2_B.ux3[5] = TemplateLgV2_P.u_Value_i;
      TemplateLgV2_B.ux3[6] = TemplateLgV2_P.u_Value_g;
      TemplateLgV2_B.ux3[7] = TemplateLgV2_P.u_Value_c;
      TemplateLgV2_B.ux3[8] = TemplateLgV2_P.ctrl1Kdpsi_Value;

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
      TemplateLgV2_B.ux3_b[0] = TemplateLgV2_P.ctrl1Kix_Value;
      TemplateLgV2_B.ux3_b[1] = TemplateLgV2_P.u_Value_ig;
      TemplateLgV2_B.ux3_b[2] = TemplateLgV2_P.u_Value_p;
      TemplateLgV2_B.ux3_b[3] = TemplateLgV2_P.u_Value_j;
      TemplateLgV2_B.ux3_b[4] = TemplateLgV2_P.ctrl1Kiy_Value;
      TemplateLgV2_B.ux3_b[5] = TemplateLgV2_P.u_Value_iy;
      TemplateLgV2_B.ux3_b[6] = TemplateLgV2_P.u_Value_b;
      TemplateLgV2_B.ux3_b[7] = TemplateLgV2_P.u_Value_d;
      TemplateLgV2_B.ux3_b[8] = TemplateLgV2_P.ctrl1Kipsi_Value;

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
      TemplateLgV2_B.ux3_b2[0] = TemplateLgV2_P.ctrl1Kpx_Value;
      TemplateLgV2_B.ux3_b2[1] = TemplateLgV2_P.u_Value_du;
      TemplateLgV2_B.ux3_b2[2] = TemplateLgV2_P.u_Value_e;
      TemplateLgV2_B.ux3_b2[3] = TemplateLgV2_P.u_Value_av;
      TemplateLgV2_B.ux3_b2[4] = TemplateLgV2_P.ctrl1Kpy_Value;
      TemplateLgV2_B.ux3_b2[5] = TemplateLgV2_P.u_Value_in;
      TemplateLgV2_B.ux3_b2[6] = TemplateLgV2_P.u_Value_c0;
      TemplateLgV2_B.ux3_b2[7] = TemplateLgV2_P.u_Value_oe;
      TemplateLgV2_B.ux3_b2[8] = TemplateLgV2_P.ctrl1Kppsi_Value;

      /* Reshape: '<S16>/[2x2]' incorporates:
       *  Constant: '<S16>/12'
       *  Constant: '<S16>/21'
       *  Constant: '<S9>/Gamma_q_Surge'
       *  Constant: '<S9>/Gamma_q_Sway'
       */
      TemplateLgV2_B.ux2[0] = TemplateLgV2_P.Gamma_q_Surge_Value;
      TemplateLgV2_B.ux2[1] = TemplateLgV2_P.u_Value_k;
      TemplateLgV2_B.ux2[2] = TemplateLgV2_P.u_Value_bs;
      TemplateLgV2_B.ux2[3] = TemplateLgV2_P.Gamma_q_Sway_Value;

      /* Constant: '<S9>/Initial q_x' */
      TemplateLgV2_B.Initialq_x = TemplateLgV2_P.Initialq_x_Value;

      /* Constant: '<S9>/Initial q_y' */
      TemplateLgV2_B.Initialq_y = TemplateLgV2_P.Initialq_y_Value;

      /* Constant: '<S9>/Initial s' */
      TemplateLgV2_B.Initials = TemplateLgV2_P.Initials_Value;

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
      TemplateLgV2_B.ux3_h[0] = TemplateLgV2_P.ctrl2Kdx_Value;
      TemplateLgV2_B.ux3_h[1] = TemplateLgV2_P.u_Value_n;
      TemplateLgV2_B.ux3_h[2] = TemplateLgV2_P.u_Value_f;
      TemplateLgV2_B.ux3_h[3] = TemplateLgV2_P.u_Value_ap;
      TemplateLgV2_B.ux3_h[4] = TemplateLgV2_P.ctrl2Kdy_Value;
      TemplateLgV2_B.ux3_h[5] = TemplateLgV2_P.u_Value_h;
      TemplateLgV2_B.ux3_h[6] = TemplateLgV2_P.u_Value_l;
      TemplateLgV2_B.ux3_h[7] = TemplateLgV2_P.u_Value_ls;
      TemplateLgV2_B.ux3_h[8] = TemplateLgV2_P.ctrl2Kdpsi_Value;

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
      TemplateLgV2_B.ux3_e[0] = TemplateLgV2_P.ctrl2Kix_Value;
      TemplateLgV2_B.ux3_e[1] = TemplateLgV2_P.u_Value_ds;
      TemplateLgV2_B.ux3_e[2] = TemplateLgV2_P.u_Value_ni;
      TemplateLgV2_B.ux3_e[3] = TemplateLgV2_P.u_Value_f0;
      TemplateLgV2_B.ux3_e[4] = TemplateLgV2_P.ctrl2Kiy_Value;
      TemplateLgV2_B.ux3_e[5] = TemplateLgV2_P.u_Value_iq;
      TemplateLgV2_B.ux3_e[6] = TemplateLgV2_P.u_Value_dm;
      TemplateLgV2_B.ux3_e[7] = TemplateLgV2_P.u_Value_hl;
      TemplateLgV2_B.ux3_e[8] = TemplateLgV2_P.ctrl2Kipsi_Value;

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
      TemplateLgV2_B.ux3_m[0] = TemplateLgV2_P.ctrl2Kpx_Value;
      TemplateLgV2_B.ux3_m[1] = TemplateLgV2_P.u_Value_cd;
      TemplateLgV2_B.ux3_m[2] = TemplateLgV2_P.u_Value_al;
      TemplateLgV2_B.ux3_m[3] = TemplateLgV2_P.u_Value_ht;
      TemplateLgV2_B.ux3_m[4] = TemplateLgV2_P.ctrl2Kpy_Value;
      TemplateLgV2_B.ux3_m[5] = TemplateLgV2_P.u_Value_cv;
      TemplateLgV2_B.ux3_m[6] = TemplateLgV2_P.u_Value_fu;
      TemplateLgV2_B.ux3_m[7] = TemplateLgV2_P.u_Value_oz;
      TemplateLgV2_B.ux3_m[8] = TemplateLgV2_P.ctrl2Kppsi_Value;

      /* Gain: '<S28>/-l_x1' incorporates:
       *  Constant: '<S28>/l_x1'
       */
      TemplateLgV2_B.l_x1 = TemplateLgV2_P.l_x1_Gain * TemplateLgV2_P.l_x1_Value;

      /* Gain: '<S28>/-l_x2' incorporates:
       *  Constant: '<S28>/l_x2'
       */
      TemplateLgV2_B.l_x2 = TemplateLgV2_P.l_x2_Gain * TemplateLgV2_P.l_x2_Value;

      /* Gain: '<S28>/-l_y2' incorporates:
       *  Constant: '<S28>/l_y2'
       */
      TemplateLgV2_B.l_y2 = TemplateLgV2_P.l_y2_Gain * TemplateLgV2_P.l_y2_Value;

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
      TemplateLgV2_B.x5[0] = TemplateLgV2_P.B_11_Value;
      TemplateLgV2_B.x5[1] = TemplateLgV2_P.B_21_Value;
      TemplateLgV2_B.x5[2] = TemplateLgV2_P.l_y1_Value;
      TemplateLgV2_B.x5[3] = TemplateLgV2_P.B_12_Value;
      TemplateLgV2_B.x5[4] = TemplateLgV2_P.B_22_Value;
      TemplateLgV2_B.x5[5] = TemplateLgV2_B.l_x1;
      TemplateLgV2_B.x5[6] = TemplateLgV2_P.B_13_Value;
      TemplateLgV2_B.x5[7] = TemplateLgV2_P.B_23_Value;
      TemplateLgV2_B.x5[8] = TemplateLgV2_B.l_y2;
      TemplateLgV2_B.x5[9] = TemplateLgV2_P.B_14_Value;
      TemplateLgV2_B.x5[10] = TemplateLgV2_P.B_24_Value;
      TemplateLgV2_B.x5[11] = TemplateLgV2_B.l_x2;
      TemplateLgV2_B.x5[12] = TemplateLgV2_P.B_15_Value;
      TemplateLgV2_B.x5[13] = TemplateLgV2_P.B_25_Value;
      TemplateLgV2_B.x5[14] = TemplateLgV2_P.l_x3_Value;

      /* Gain: '<S27>/-N_r' incorporates:
       *  Constant: '<S27>/N_r'
       */
      TemplateLgV2_B.N_r = TemplateLgV2_P.N_r_Gain * TemplateLgV2_P.N_r_Value;

      /* Gain: '<S27>/-N_v' incorporates:
       *  Constant: '<S27>/N_v'
       */
      TemplateLgV2_B.N_v = TemplateLgV2_P.N_v_Gain * TemplateLgV2_P.N_v_Value;

      /* Gain: '<S27>/-X_u' incorporates:
       *  Constant: '<S27>/X_u'
       */
      TemplateLgV2_B.X_u = TemplateLgV2_P.X_u_Gain * TemplateLgV2_P.X_u_Value;

      /* Gain: '<S27>/-Y_v' incorporates:
       *  Constant: '<S27>/Y_v'
       */
      TemplateLgV2_B.Y_v = TemplateLgV2_P.Y_v_Gain * TemplateLgV2_P.Y_v_Value;

      /* Gain: '<S27>/-Y_vr' incorporates:
       *  Constant: '<S27>/Y_r'
       */
      TemplateLgV2_B.Y_vr = TemplateLgV2_P.Y_vr_Gain * TemplateLgV2_P.Y_r_Value;

      /* Reshape: '<S27>/Linear Dampning matrix' incorporates:
       *  Constant: '<S27>/D_L_12'
       *  Constant: '<S27>/D_L_13'
       *  Constant: '<S27>/D_L_21'
       *  Constant: '<S27>/D_L_31'
       */
      TemplateLgV2_B.LinearDampningmatrix[0] = TemplateLgV2_B.X_u;
      TemplateLgV2_B.LinearDampningmatrix[1] = TemplateLgV2_P.D_L_21_Value;
      TemplateLgV2_B.LinearDampningmatrix[2] = TemplateLgV2_P.D_L_31_Value;
      TemplateLgV2_B.LinearDampningmatrix[3] = TemplateLgV2_P.D_L_12_Value;
      TemplateLgV2_B.LinearDampningmatrix[4] = TemplateLgV2_B.Y_v;
      TemplateLgV2_B.LinearDampningmatrix[5] = TemplateLgV2_B.N_v;
      TemplateLgV2_B.LinearDampningmatrix[6] = TemplateLgV2_P.D_L_13_Value;
      TemplateLgV2_B.LinearDampningmatrix[7] = TemplateLgV2_B.Y_vr;
      TemplateLgV2_B.LinearDampningmatrix[8] = TemplateLgV2_B.N_r;

      /* Sum: '<S26>/M_11' incorporates:
       *  Constant: '<S26>/X_udot'
       *  Constant: '<S26>/m'
       */
      TemplateLgV2_B.M_11 = TemplateLgV2_P.m_Value - TemplateLgV2_P.X_udot_Value;

      /* Sum: '<S26>/M_22' incorporates:
       *  Constant: '<S26>/Y_vdot'
       *  Constant: '<S26>/m'
       */
      TemplateLgV2_B.M_22 = TemplateLgV2_P.m_Value - TemplateLgV2_P.Y_vdot_Value;

      /* Product: '<S26>/m x_g' incorporates:
       *  Constant: '<S26>/m'
       *  Constant: '<S26>/x_g'
       */
      TemplateLgV2_B.mx_g = TemplateLgV2_P.m_Value * TemplateLgV2_P.x_g_Value;

      /* Sum: '<S26>/M_32' incorporates:
       *  Constant: '<S26>/N_vdot'
       */
      TemplateLgV2_B.M_32 = TemplateLgV2_B.mx_g - TemplateLgV2_P.N_vdot_Value;

      /* Sum: '<S26>/M_23' incorporates:
       *  Constant: '<S26>/Y_rdot'
       */
      TemplateLgV2_B.M_23 = TemplateLgV2_B.mx_g - TemplateLgV2_P.Y_rdot_Value;

      /* Sum: '<S26>/M_33' incorporates:
       *  Constant: '<S26>/I_z'
       *  Constant: '<S26>/N_rdot'
       */
      TemplateLgV2_B.M_33 = TemplateLgV2_P.I_z_Value -
        TemplateLgV2_P.N_rdot_Value;

      /* Reshape: '<S26>/3x3' incorporates:
       *  Constant: '<S26>/M_12'
       *  Constant: '<S26>/M_13'
       *  Constant: '<S26>/M_21'
       *  Constant: '<S26>/M_31'
       */
      TemplateLgV2_B.x3[0] = TemplateLgV2_B.M_11;
      TemplateLgV2_B.x3[1] = TemplateLgV2_P.M_21_Value;
      TemplateLgV2_B.x3[2] = TemplateLgV2_P.M_31_Value;
      TemplateLgV2_B.x3[3] = TemplateLgV2_P.M_12_Value;
      TemplateLgV2_B.x3[4] = TemplateLgV2_B.M_22;
      TemplateLgV2_B.x3[5] = TemplateLgV2_B.M_32;
      TemplateLgV2_B.x3[6] = TemplateLgV2_P.M_13_Value;
      TemplateLgV2_B.x3[7] = TemplateLgV2_B.M_23;
      TemplateLgV2_B.x3[8] = TemplateLgV2_B.M_33;

      /* Gain: '<S74>/-l_x1' incorporates:
       *  Constant: '<S74>/l_x1'
       */
      TemplateLgV2_B.l_x1_k = TemplateLgV2_P.l_x1_Gain_b *
        TemplateLgV2_P.l_x1_Value_e;

      /* Gain: '<S74>/-l_y2' incorporates:
       *  Constant: '<S74>/l_y2'
       */
      TemplateLgV2_B.l_y2_n = TemplateLgV2_P.l_y2_Gain_h *
        TemplateLgV2_P.l_y2_Value_e;

      /* Gain: '<S74>/-l_x2' incorporates:
       *  Constant: '<S74>/l_x2'
       */
      TemplateLgV2_B.l_x2_f = TemplateLgV2_P.l_x2_Gain_a *
        TemplateLgV2_P.l_x2_Value_j;

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
      TemplateLgV2_B.x5_j[0] = TemplateLgV2_P.T_e11_Value;
      TemplateLgV2_B.x5_j[1] = TemplateLgV2_P.T_e21_Value;
      TemplateLgV2_B.x5_j[2] = TemplateLgV2_P.l_y1_Value_b;
      TemplateLgV2_B.x5_j[3] = TemplateLgV2_P.T_e12_Value;
      TemplateLgV2_B.x5_j[4] = TemplateLgV2_P.T_e22_Value;
      TemplateLgV2_B.x5_j[5] = TemplateLgV2_B.l_x1_k;
      TemplateLgV2_B.x5_j[6] = TemplateLgV2_P.T_e13_Value;
      TemplateLgV2_B.x5_j[7] = TemplateLgV2_P.T_e23_Value;
      TemplateLgV2_B.x5_j[8] = TemplateLgV2_B.l_y2_n;
      TemplateLgV2_B.x5_j[9] = TemplateLgV2_P.T_e14_Value;
      TemplateLgV2_B.x5_j[10] = TemplateLgV2_P.T_e24_Value;
      TemplateLgV2_B.x5_j[11] = TemplateLgV2_B.l_x2_f;
      TemplateLgV2_B.x5_j[12] = TemplateLgV2_P.T_e15_Value;
      TemplateLgV2_B.x5_j[13] = TemplateLgV2_P.T_e25_Value;
      TemplateLgV2_B.x5_j[14] = TemplateLgV2_P.l_x3_Value_f;

      /* Gain: '<S32>/PS3 u_1' */
      TemplateLgV2_B.u_1 = TemplateLgV2_P.PS3u_1_Gain *
        TemplateLgV2_B.ypositionofleftanalogstick11;

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
      LookUp_real_T_real_T( &(TemplateLgV2_B.u_1tof_1),
                           TemplateLgV2_P.u_1tof_1_YData, TemplateLgV2_B.u_1,
                           TemplateLgV2_P.u_1tof_1_XData, 18U);

      /* Gain: '<S32>/PS3 u_2' */
      TemplateLgV2_B.u_2 = TemplateLgV2_P.PS3u_2_Gain *
        TemplateLgV2_B.xpositionofleftanalogstick11;

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
      LookUp_real_T_real_T( &(TemplateLgV2_B.u_2tof_2),
                           TemplateLgV2_P.u_2tof_2_YData, TemplateLgV2_B.u_2,
                           TemplateLgV2_P.u_2tof_2_XData, 20U);

      /* Gain: '<S32>/PS3 u_3' */
      TemplateLgV2_B.u_3 = TemplateLgV2_P.PS3u_3_Gain *
        TemplateLgV2_B.ypositionofrightanalogstick11;

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
      LookUp_real_T_real_T( &(TemplateLgV2_B.u_3tof_3),
                           TemplateLgV2_P.u_3tof_3_YData, TemplateLgV2_B.u_3,
                           TemplateLgV2_P.u_3tof_3_XData, 18U);

      /* Gain: '<S32>/PS3 u_4' */
      TemplateLgV2_B.u_4 = TemplateLgV2_P.PS3u_4_Gain *
        TemplateLgV2_B.xpositionofrightanalogstick11;

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
      LookUp_real_T_real_T( &(TemplateLgV2_B.u_4tof_4),
                           TemplateLgV2_P.u_4tof_4_YData, TemplateLgV2_B.u_4,
                           TemplateLgV2_P.u_4tof_4_XData, 16U);

      /* Sum: '<S32>/Add' incorporates:
       *  Constant: '<S6>/L2 [-]'
       *  Constant: '<S6>/R2 [-]'
       */
      TemplateLgV2_B.BowThrusterdirection = TemplateLgV2_P.L2_Value +
        TemplateLgV2_P.R2_Value;

      /* Gain: '<S32>/PS3 u_5' */
      TemplateLgV2_B.u_5 = TemplateLgV2_P.PS3u_5_Gain *
        TemplateLgV2_B.BowThrusterdirection;

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
      LookUp_real_T_real_T( &(TemplateLgV2_B.u_5tof_5),
                           TemplateLgV2_P.u_5tof_5_YData, TemplateLgV2_B.u_5,
                           TemplateLgV2_P.u_5tof_5_XData, 6U);

      /* SignalConversion: '<S72>/TmpHiddenBufferAtProductInport2' */
      TemplateLgV2_B.TmpHiddenBufferAtProductInport2[0] =
        TemplateLgV2_B.u_1tof_1;
      TemplateLgV2_B.TmpHiddenBufferAtProductInport2[1] =
        TemplateLgV2_B.u_2tof_2;
      TemplateLgV2_B.TmpHiddenBufferAtProductInport2[2] =
        TemplateLgV2_B.u_3tof_3;
      TemplateLgV2_B.TmpHiddenBufferAtProductInport2[3] =
        TemplateLgV2_B.u_4tof_4;
      TemplateLgV2_B.TmpHiddenBufferAtProductInport2[4] =
        TemplateLgV2_B.u_5tof_5;

      /* Product: '<S72>/Product' */
      for (i = 0; i < 3; i++) {
        TemplateLgV2_B.Product[i] = 0.0;
        for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
          TemplateLgV2_B.Product[i] = TemplateLgV2_B.x5_j[3 * tmp_6 + i] *
            TemplateLgV2_B.TmpHiddenBufferAtProductInport2[tmp_6] +
            TemplateLgV2_B.Product[i];
        }
      }
    }

    /* Gain: '<S166>/QTM In3 x-coord [mm]' */
    TemplateLgV2_B.QTMIn3xcoordmm = TemplateLgV2_P.QTMIn3xcoordmm_Gain *
      TemplateLgV2_B.QTMIn[2];

    /* Gain: '<S166>/mm2m x' */
    TemplateLgV2_B.mm2mx = TemplateLgV2_P.mm2mx_Gain *
      TemplateLgV2_B.QTMIn3xcoordmm;

    /* Gain: '<S166>/QTM In4 y-coord [mm]' */
    TemplateLgV2_B.QTMIn4ycoordmm = TemplateLgV2_P.QTMIn4ycoordmm_Gain *
      TemplateLgV2_B.QTMIn[3];

    /* Gain: '<S166>/mm2m y' */
    TemplateLgV2_B.mm2my = TemplateLgV2_P.mm2my_Gain *
      TemplateLgV2_B.QTMIn4ycoordmm;

    /* Gain: '<S166>/QTM In6 yaw [deg]' */
    TemplateLgV2_B.QTMIn6yawdeg = TemplateLgV2_P.QTMIn6yawdeg_Gain *
      TemplateLgV2_B.QTMIn[5];

    /* Gain: '<S166>/d2r yaw' */
    TemplateLgV2_B.d2ryaw = TemplateLgV2_P.d2ryaw_Gain *
      TemplateLgV2_B.QTMIn6yawdeg;

    /* Outputs for enable SubSystem: '<S25>/Linear Simulator' incorporates:
     *  Constant: '<S4>/Enable Linear Simulator'
     *  EnablePort: '<S192>/Enable'
     */
    if (rtmIsMajorTimeStep(TemplateLgV2_M) && rtmIsMajorTimeStep(TemplateLgV2_M))
    {
      if (TemplateLgV2_P.EnableLinearSimulator_Value > 0.0) {
        if (TemplateLgV2_DWork.LinearSimulator_MODE == SUBSYS_DISABLED) {
          /* Integrator Block: '<S200>/Integrator' */
          if (rtmIsFirstInitCond(TemplateLgV2_M)) {
            TemplateLgV2_X.Integrator_CSTATE_e[0] = 0.0;
            TemplateLgV2_X.Integrator_CSTATE_e[1] = 0.0;
            TemplateLgV2_X.Integrator_CSTATE_e[2] = 0.0;
          }

          TemplateLgV2_DWork.Integrator_IWORK_d.IcNeedsLoading = 1;

          /* Integrator Block: '<S200>/Integrator1' */
          if (rtmIsFirstInitCond(TemplateLgV2_M)) {
            TemplateLgV2_X.Integrator1_CSTATE_p[0] = 0.0;
            TemplateLgV2_X.Integrator1_CSTATE_p[1] = 0.0;
            TemplateLgV2_X.Integrator1_CSTATE_p[2] = 0.0;
          }

          TemplateLgV2_DWork.Integrator1_IWORK_l.IcNeedsLoading = 1;
          TemplateLgV2_DWork.LinearSimulator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (TemplateLgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
          TemplateLgV2_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (TemplateLgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Integrator Block: '<S200>/Integrator'
       */
      if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE_o,
                           TemplateLgV2_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || TemplateLgV2_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            TemplateLgV2_DWork.Integrator_IWORK_d.IcNeedsLoading) {
          TemplateLgV2_X.Integrator_CSTATE_e[0] = TemplateLgV2_B.Initialums;
          TemplateLgV2_X.Integrator_CSTATE_e[1] = TemplateLgV2_B.Initialvms;
          TemplateLgV2_X.Integrator_CSTATE_e[2] = TemplateLgV2_B.Initialrrads;
        }

        TemplateLgV2_DWork.Integrator_IWORK_d.IcNeedsLoading = 0;
      }

      TemplateLgV2_B.Integrator_h[0] = TemplateLgV2_X.Integrator_CSTATE_e[0];
      TemplateLgV2_B.Integrator_h[1] = TemplateLgV2_X.Integrator_CSTATE_e[1];
      TemplateLgV2_B.Integrator_h[2] = TemplateLgV2_X.Integrator_CSTATE_e[2];

      /* Integrator Block: '<S200>/Integrator1'
       */
      if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
        ZCEventType zcEvent;
        zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                           &TemplateLgV2_PrevZCSigState.Integrator1_Reset_ZCE_c,
                           TemplateLgV2_P.ResetLinearSimulatorintegrator_);

        /* evaluate zero-crossings and the level of the reset signal */
        if (zcEvent || TemplateLgV2_P.ResetLinearSimulatorintegrator_ != 0.0 ||
            TemplateLgV2_DWork.Integrator1_IWORK_l.IcNeedsLoading) {
          TemplateLgV2_X.Integrator1_CSTATE_p[0] = TemplateLgV2_B.Initialxm;
          TemplateLgV2_X.Integrator1_CSTATE_p[1] = TemplateLgV2_B.Initialym;
          TemplateLgV2_X.Integrator1_CSTATE_p[2] = TemplateLgV2_B.Initialpsirad;
        }

        TemplateLgV2_DWork.Integrator1_IWORK_l.IcNeedsLoading = 0;
      }

      TemplateLgV2_B.Integrator1_p[0] = TemplateLgV2_X.Integrator1_CSTATE_p[0];
      TemplateLgV2_B.Integrator1_p[1] = TemplateLgV2_X.Integrator1_CSTATE_p[1];
      TemplateLgV2_B.Integrator1_p[2] = TemplateLgV2_X.Integrator1_CSTATE_p[2];

      /* Fcn: '<S201>/R11' */
      TemplateLgV2_B.R11_h = cos(TemplateLgV2_B.Integrator1_p[2]);

      /* Fcn: '<S201>/R21' */
      TemplateLgV2_B.R21_f = sin(TemplateLgV2_B.Integrator1_p[2]);

      /* Fcn: '<S201>/R12' */
      TemplateLgV2_B.R12_c = -1.0 * sin(TemplateLgV2_B.Integrator1_p[2]);

      /* Fcn: '<S201>/R22' */
      TemplateLgV2_B.R22_p = cos(TemplateLgV2_B.Integrator1_p[2]);

      /* Reshape: '<S201>/R(psi)' incorporates:
       *  Constant: '<S201>/R13'
       *  Constant: '<S201>/R23'
       *  Constant: '<S201>/R31'
       *  Constant: '<S201>/R32'
       *  Constant: '<S201>/R33'
       */
      TemplateLgV2_B.Rpsi_k[0] = TemplateLgV2_B.R11_h;
      TemplateLgV2_B.Rpsi_k[1] = TemplateLgV2_B.R21_f;
      TemplateLgV2_B.Rpsi_k[2] = TemplateLgV2_P.R31_Value_p;
      TemplateLgV2_B.Rpsi_k[3] = TemplateLgV2_B.R12_c;
      TemplateLgV2_B.Rpsi_k[4] = TemplateLgV2_B.R22_p;
      TemplateLgV2_B.Rpsi_k[5] = TemplateLgV2_P.R32_Value_k;
      TemplateLgV2_B.Rpsi_k[6] = TemplateLgV2_P.R13_Value_g;
      TemplateLgV2_B.Rpsi_k[7] = TemplateLgV2_P.R23_Value_n;
      TemplateLgV2_B.Rpsi_k[8] = TemplateLgV2_P.R33_Value_j;
    }

    /* end of Outputs for SubSystem: '<S25>/Linear Simulator' */

    /* MultiPortSwitch: '<S167>/eta Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)TemplateLgV2_P.ControlInputSelector_Value == 0) {
      TemplateLgV2_B.etaSwitch[0] = TemplateLgV2_B.mm2mx;
      TemplateLgV2_B.etaSwitch[1] = TemplateLgV2_B.mm2my;
      TemplateLgV2_B.etaSwitch[2] = TemplateLgV2_B.d2ryaw;
    } else {
      TemplateLgV2_B.etaSwitch[0] = TemplateLgV2_B.Integrator1_p[0];
      TemplateLgV2_B.etaSwitch[1] = TemplateLgV2_B.Integrator1_p[1];
      TemplateLgV2_B.etaSwitch[2] = TemplateLgV2_B.Integrator1_p[2];
    }

    /* Fcn: '<S30>/yaw angle' */
    TemplateLgV2_B.psi = TemplateLgV2_B.etaSwitch[2];

    /* Saturate: '<S36>/Saturation' */
    tmp = TemplateLgV2_B.psi;
    TemplateLgV2_B.Saturation = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat, TemplateLgV2_P.Saturation_UpperSat);

    /* Signum: '<S36>/Sign' */
    TemplateLgV2_B.Sign = rt_SIGNd_snf(TemplateLgV2_B.Saturation);

    /* Gain: '<S36>/Gain' */
    TemplateLgV2_B.Gain = TemplateLgV2_P.Gain_Gain * TemplateLgV2_B.Sign;

    /* Sum: '<S36>/Sum1' */
    TemplateLgV2_B.Sum1 = TemplateLgV2_B.Saturation + TemplateLgV2_B.Gain;

    /* Math: '<S36>/Math Function' incorporates:
     *  Constant: '<S36>/Constant'
     */
    TemplateLgV2_B.MathFunction = rt_rem_snf(TemplateLgV2_B.Sum1,
      TemplateLgV2_P.Constant_Value);

    /* Sum: '<S36>/Sum' */
    TemplateLgV2_B.Sum = TemplateLgV2_B.MathFunction - TemplateLgV2_B.Gain;

    /* Sum: '<S30>/Sum2' incorporates:
     *  Constant: '<S7>/setpointx [m]'
     *  Constant: '<S7>/setpointy [m]'
     */
    TemplateLgV2_B.Sum2[0] = TemplateLgV2_P.setpointxm_Value -
      TemplateLgV2_B.etaSwitch[0];
    TemplateLgV2_B.Sum2[1] = TemplateLgV2_P.setpointym_Value -
      TemplateLgV2_B.etaSwitch[1];
    TemplateLgV2_B.Sum2[2] = TemplateLgV2_B.Gain1 - TemplateLgV2_B.etaSwitch[2];

    /* Saturate: '<S35>/Saturation' */
    tmp = TemplateLgV2_B.Sum2[2];
    TemplateLgV2_B.Saturation_b = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_a, TemplateLgV2_P.Saturation_UpperSat_p);

    /* Signum: '<S35>/Sign' */
    TemplateLgV2_B.Sign_g = rt_SIGNd_snf(TemplateLgV2_B.Saturation_b);

    /* Gain: '<S35>/Gain' */
    TemplateLgV2_B.Gain_b = TemplateLgV2_P.Gain_Gain_i * TemplateLgV2_B.Sign_g;

    /* Sum: '<S35>/Sum1' */
    TemplateLgV2_B.Sum1_b = TemplateLgV2_B.Saturation_b + TemplateLgV2_B.Gain_b;

    /* Math: '<S35>/Math Function' incorporates:
     *  Constant: '<S35>/Constant'
     */
    TemplateLgV2_B.MathFunction_j = rt_rem_snf(TemplateLgV2_B.Sum1_b,
      TemplateLgV2_P.Constant_Value_p);

    /* Sum: '<S35>/Sum' */
    TemplateLgV2_B.Sum_l = TemplateLgV2_B.MathFunction_j - TemplateLgV2_B.Gain_b;

    /* Fcn: '<S34>/Row1' */
    TemplateLgV2_B.Row1 = cos(TemplateLgV2_B.Sum) * TemplateLgV2_B.Sum2[0] + sin
      (TemplateLgV2_B.Sum) * TemplateLgV2_B.Sum2[1];

    /* Fcn: '<S34>/Row2' */
    TemplateLgV2_B.Row2 = (-sin(TemplateLgV2_B.Sum)) * TemplateLgV2_B.Sum2[0] +
      cos(TemplateLgV2_B.Sum) * TemplateLgV2_B.Sum2[1];

    /* Fcn: '<S34>/Row3' */
    TemplateLgV2_B.Row3 = TemplateLgV2_B.Sum_l;

    /* SignalConversion: '<S30>/TmpHiddenBufferAtProductInport2' */
    TemplateLgV2_B.TmpHiddenBufferAtProductInpor_f[0] = TemplateLgV2_B.Row1;
    TemplateLgV2_B.TmpHiddenBufferAtProductInpor_f[1] = TemplateLgV2_B.Row2;
    TemplateLgV2_B.TmpHiddenBufferAtProductInpor_f[2] = TemplateLgV2_B.Row3;

    /* Product: '<S30>/Product' */
    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.Product_n[i] = 0.0;
      TemplateLgV2_B.Product_n[i] = TemplateLgV2_B.ux3_b2[i] *
        TemplateLgV2_B.TmpHiddenBufferAtProductInpor_f[0] +
        TemplateLgV2_B.Product_n[i];
      TemplateLgV2_B.Product_n[i] = TemplateLgV2_B.ux3_b2[i + 3] *
        TemplateLgV2_B.TmpHiddenBufferAtProductInpor_f[1] +
        TemplateLgV2_B.Product_n[i];
      TemplateLgV2_B.Product_n[i] = TemplateLgV2_B.ux3_b2[i + 6] *
        TemplateLgV2_B.TmpHiddenBufferAtProductInpor_f[2] +
        TemplateLgV2_B.Product_n[i];
    }

    /* Integrator Block: '<S30>/Integrator'
     */
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE,
                         TemplateLgV2_P.ctrl1ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateLgV2_P.ctrl1ResetIntegrator_Value != 0.0) {
        TemplateLgV2_X.Integrator_CSTATE[0] = TemplateLgV2_P.Integrator_IC;
        TemplateLgV2_X.Integrator_CSTATE[1] = TemplateLgV2_P.Integrator_IC;
        TemplateLgV2_X.Integrator_CSTATE[2] = TemplateLgV2_P.Integrator_IC;
      }
    }

    TemplateLgV2_B.Integrator[0] = TemplateLgV2_X.Integrator_CSTATE[0];
    TemplateLgV2_B.Integrator[1] = TemplateLgV2_X.Integrator_CSTATE[1];
    TemplateLgV2_B.Integrator[2] = TemplateLgV2_X.Integrator_CSTATE[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S30>/Product1' */
      TemplateLgV2_B.Product1[i] = 0.0;
      TemplateLgV2_B.Product1[i] = TemplateLgV2_B.ux3_b[i] *
        TemplateLgV2_B.Integrator[0] + TemplateLgV2_B.Product1[i];
      TemplateLgV2_B.Product1[i] = TemplateLgV2_B.ux3_b[i + 3] *
        TemplateLgV2_B.Integrator[1] + TemplateLgV2_B.Product1[i];
      TemplateLgV2_B.Product1[i] = TemplateLgV2_B.ux3_b[i + 6] *
        TemplateLgV2_B.Integrator[2] + TemplateLgV2_B.Product1[i];

      /* Sum: '<S30>/Sum3' */
      TemplateLgV2_B.Sum3[i] = TemplateLgV2_B.Product_n[i] +
        TemplateLgV2_B.Product1[i];
    }

    /* Integrator Block: '<S169>/Integrator4'
     */
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateLgV2_PrevZCSigState.Integrator4_Reset_ZCE,
                         TemplateLgV2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateLgV2_P.ctrl2ResetIntegrator_Value != 0.0) {
        TemplateLgV2_X.Integrator4_CSTATE[0] = TemplateLgV2_P.Integrator4_IC;
        TemplateLgV2_X.Integrator4_CSTATE[1] = TemplateLgV2_P.Integrator4_IC;
        TemplateLgV2_X.Integrator4_CSTATE[2] = TemplateLgV2_P.Integrator4_IC;
      }
    }

    TemplateLgV2_B.nu[0] = TemplateLgV2_X.Integrator4_CSTATE[0];
    TemplateLgV2_B.nu[1] = TemplateLgV2_X.Integrator4_CSTATE[1];
    TemplateLgV2_B.nu[2] = TemplateLgV2_X.Integrator4_CSTATE[2];

    /* MultiPortSwitch: '<S167>/nu Switch' incorporates:
     *  Constant: '<S1>/Control Input Selector'
     */
    if ((int32_T)TemplateLgV2_P.ControlInputSelector_Value == 0) {
      TemplateLgV2_B.nuSwitch[0] = TemplateLgV2_B.nu[0];
      TemplateLgV2_B.nuSwitch[1] = TemplateLgV2_B.nu[1];
      TemplateLgV2_B.nuSwitch[2] = TemplateLgV2_B.nu[2];
    } else {
      TemplateLgV2_B.nuSwitch[0] = TemplateLgV2_B.Integrator_h[0];
      TemplateLgV2_B.nuSwitch[1] = TemplateLgV2_B.Integrator_h[1];
      TemplateLgV2_B.nuSwitch[2] = TemplateLgV2_B.Integrator_h[2];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S30>/Product2' */
      TemplateLgV2_B.Product2[i] = 0.0;
      TemplateLgV2_B.Product2[i] = TemplateLgV2_B.ux3[i] *
        TemplateLgV2_B.nuSwitch[0] + TemplateLgV2_B.Product2[i];
      TemplateLgV2_B.Product2[i] = TemplateLgV2_B.ux3[i + 3] *
        TemplateLgV2_B.nuSwitch[1] + TemplateLgV2_B.Product2[i];
      TemplateLgV2_B.Product2[i] = TemplateLgV2_B.ux3[i + 6] *
        TemplateLgV2_B.nuSwitch[2] + TemplateLgV2_B.Product2[i];

      /* Sum: '<S30>/Sum1' */
      TemplateLgV2_B.Sum1_g[i] = TemplateLgV2_B.Sum3[i] -
        TemplateLgV2_B.Product2[i];
    }

    /* Trigonometry: '<S41>/R11' */
    TemplateLgV2_B.R11 = cos(TemplateLgV2_B.etaSwitch[2]);

    /* Trigonometry: '<S41>/R21' */
    TemplateLgV2_B.R21 = sin(TemplateLgV2_B.etaSwitch[2]);

    /* Trigonometry: '<S41>/R12' */
    TemplateLgV2_B.R12 = sin(TemplateLgV2_B.etaSwitch[2]);

    /* Gain: '<S41>/-1' */
    TemplateLgV2_B.u = TemplateLgV2_P.u_Gain * TemplateLgV2_B.R12;

    /* Trigonometry: '<S41>/R22' */
    TemplateLgV2_B.R22 = cos(TemplateLgV2_B.etaSwitch[2]);

    /* Reshape: '<S41>/R(psi)' incorporates:
     *  Constant: '<S41>/R13'
     *  Constant: '<S41>/R23'
     *  Constant: '<S41>/R31'
     *  Constant: '<S41>/R32'
     *  Constant: '<S41>/R33'
     */
    TemplateLgV2_B.Rpsi[0] = TemplateLgV2_B.R11;
    TemplateLgV2_B.Rpsi[1] = TemplateLgV2_B.R21;
    TemplateLgV2_B.Rpsi[2] = TemplateLgV2_P.R31_Value;
    TemplateLgV2_B.Rpsi[3] = TemplateLgV2_B.u;
    TemplateLgV2_B.Rpsi[4] = TemplateLgV2_B.R22;
    TemplateLgV2_B.Rpsi[5] = TemplateLgV2_P.R32_Value;
    TemplateLgV2_B.Rpsi[6] = TemplateLgV2_P.R13_Value;
    TemplateLgV2_B.Rpsi[7] = TemplateLgV2_P.R23_Value;
    TemplateLgV2_B.Rpsi[8] = TemplateLgV2_P.R33_Value;

    /* Math: '<S61>/Math Function' */
    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.MathFunction_k[3 * i] = TemplateLgV2_B.Rpsi[i];
      TemplateLgV2_B.MathFunction_k[1 + 3 * i] = TemplateLgV2_B.Rpsi[i + 3];
      TemplateLgV2_B.MathFunction_k[2 + 3 * i] = TemplateLgV2_B.Rpsi[i + 6];
    }

    /* Integrator Block: '<S50>/Integrator'
     */
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE_l,
                         TemplateLgV2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateLgV2_P.ctrl2ResetIntegrator_Value != 0.0) {
        TemplateLgV2_X.Integrator_CSTATE_a[0] = TemplateLgV2_P.Integrator_IC_m[0];
        TemplateLgV2_X.Integrator_CSTATE_a[1] = TemplateLgV2_P.Integrator_IC_m[1];
        TemplateLgV2_X.Integrator_CSTATE_a[2] = TemplateLgV2_P.Integrator_IC_m[2];
      }
    }

    TemplateLgV2_B.Integrator_g[0] = TemplateLgV2_X.Integrator_CSTATE_a[0];
    TemplateLgV2_B.Integrator_g[1] = TemplateLgV2_X.Integrator_CSTATE_a[1];
    TemplateLgV2_B.Integrator_g[2] = TemplateLgV2_X.Integrator_CSTATE_a[2];

    /* Product: '<S39>/Product' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] + TemplateLgV2_B.ux3_e[3 *
          tmp_6] * TemplateLgV2_B.MathFunction_k[i];
        tmp_1[i + 3 * tmp_6] = TemplateLgV2_B.ux3_e[3 * tmp_6 + 1] *
          TemplateLgV2_B.MathFunction_k[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = TemplateLgV2_B.ux3_e[3 * tmp_6 + 2] *
          TemplateLgV2_B.MathFunction_k[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.Product_e[i] = 0.0;
      TemplateLgV2_B.Product_e[i] = tmp_1[i] * TemplateLgV2_B.Integrator_g[0] +
        TemplateLgV2_B.Product_e[i];
      TemplateLgV2_B.Product_e[i] = tmp_1[i + 3] * TemplateLgV2_B.Integrator_g[1]
        + TemplateLgV2_B.Product_e[i];
      TemplateLgV2_B.Product_e[i] = tmp_1[i + 6] * TemplateLgV2_B.Integrator_g[2]
        + TemplateLgV2_B.Product_e[i];

      /* Gain: '<S39>/Gain' */
      TemplateLgV2_B.Gain_d[i] = TemplateLgV2_P.Gain_Gain_d *
        TemplateLgV2_B.Product_e[i];
    }

    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Gain: '<S39>/4' incorporates:
       *  Constant: '<S9>/kappa_1'
       */
      TemplateLgV2_B.u_j = TemplateLgV2_P._Gain * TemplateLgV2_P.kappa_1_Value;

      /* Product: '<S39>/Divide' incorporates:
       *  Constant: '<S39>/1'
       */
      TemplateLgV2_B.Divide = TemplateLgV2_P._Value / TemplateLgV2_B.u_j;
      for (i = 0; i < 9; i++) {
        /* Sum: '<S39>/Add1' */
        TemplateLgV2_B.Add1[i] = TemplateLgV2_B.ux3_h[i] + TemplateLgV2_B.Divide;

        /* Product: '<S31>/Product1' incorporates:
         *  Constant: '<S40>/Constant'
         *  Constant: '<S9>/kappa_1'
         */
        TemplateLgV2_B.Product1_j[i] = TemplateLgV2_P.kappa_1_Value *
          TemplateLgV2_P.Constant_Value_i[i];

        /* Sum: '<S31>/Add3' */
        TemplateLgV2_B.Add3[i] = TemplateLgV2_B.ux3_m[i] +
          TemplateLgV2_B.Product1_j[i];
      }
    }

    /* Saturate: '<S69>/Saturation' */
    tmp = TemplateLgV2_B.etaSwitch[2];
    TemplateLgV2_B.Saturation_j = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_j, TemplateLgV2_P.Saturation_UpperSat_k);

    /* Signum: '<S69>/Sign' */
    TemplateLgV2_B.Sign_k = rt_SIGNd_snf(TemplateLgV2_B.Saturation_j);

    /* Gain: '<S69>/Gain' */
    TemplateLgV2_B.Gain_dc = TemplateLgV2_P.Gain_Gain_k * TemplateLgV2_B.Sign_k;

    /* Sum: '<S69>/Sum1' */
    TemplateLgV2_B.Sum1_c = TemplateLgV2_B.Saturation_j + TemplateLgV2_B.Gain_dc;

    /* Math: '<S69>/Math Function' incorporates:
     *  Constant: '<S69>/Constant'
     */
    TemplateLgV2_B.MathFunction_kz = rt_rem_snf(TemplateLgV2_B.Sum1_c,
      TemplateLgV2_P.Constant_Value_m);

    /* Sum: '<S69>/Sum' */
    TemplateLgV2_B.Sum_e = TemplateLgV2_B.MathFunction_kz -
      TemplateLgV2_B.Gain_dc;

    /* Integrator Block: '<S42>/Integrator'
     */
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE_i,
                         TemplateLgV2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateLgV2_P.ctrl2ResetIntegrator_Value != 0.0 ||
          TemplateLgV2_DWork.Integrator_IWORK.IcNeedsLoading) {
        TemplateLgV2_X.Integrator_CSTATE_d[0] = TemplateLgV2_B.Initialq_x;
        TemplateLgV2_X.Integrator_CSTATE_d[1] = TemplateLgV2_B.Initialq_y;
      }

      TemplateLgV2_DWork.Integrator_IWORK.IcNeedsLoading = 0;
    }

    TemplateLgV2_B.Integrator_e[0] = TemplateLgV2_X.Integrator_CSTATE_d[0];
    TemplateLgV2_B.Integrator_e[1] = TemplateLgV2_X.Integrator_CSTATE_d[1];

    /* SignalConversion: '<S106>/ConcatBufferAtVector ConcatenateIn1' */
    TemplateLgV2_B.VectorConcatenate[0] = TemplateLgV2_B.Integrator_e[0];
    TemplateLgV2_B.VectorConcatenate[1] = TemplateLgV2_B.Integrator_e[1];
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Sum: '<S159>/x_2 - x_1' incorporates:
       *  Constant: '<S11>/x_1 [m]'
       *  Constant: '<S11>/x_2 [m]'
       */
      TemplateLgV2_B.x_2x_1 = TemplateLgV2_P.x_2m_Value -
        TemplateLgV2_P.x_1m_Value;

      /* Sum: '<S159>/y_2 - y_1' incorporates:
       *  Constant: '<S11>/y_1 [m]'
       *  Constant: '<S11>/y_2 [m]'
       */
      TemplateLgV2_B.y_2y_1 = TemplateLgV2_P.y_2m_Value -
        TemplateLgV2_P.y_1m_Value;

      /* SignalConversion: '<S160>/TmpHiddenBufferAtProductInport2' */
      TemplateLgV2_B.TmpHiddenBufferAtProductInpor_n[0] = TemplateLgV2_B.x_2x_1;
      TemplateLgV2_B.TmpHiddenBufferAtProductInpor_n[1] = TemplateLgV2_B.y_2y_1;

      /* Saturate: '<S142>/Saturation' incorporates:
       *  Constant: '<S5>/Path Selector  [-]'
       */
      tmp = TemplateLgV2_P.PathSelector_Value;
      TemplateLgV2_B.Saturation_i = rt_SATURATE(tmp,
        TemplateLgV2_P.Saturation_LowerSat_l,
        TemplateLgV2_P.Saturation_UpperSat_m);

      /* Rounding: '<S142>/Rounding Function' */
      TemplateLgV2_B.RoundingFunction = floor(TemplateLgV2_B.Saturation_i);

      /* Product: '<S152>/Product' */
      TemplateLgV2_B.Product_j[0] =
        TemplateLgV2_B.TmpHiddenBufferAtProductInpor_n[0] *
        TemplateLgV2_B.RoundingFunction;
      TemplateLgV2_B.Product_j[1] =
        TemplateLgV2_B.TmpHiddenBufferAtProductInpor_n[1] *
        TemplateLgV2_B.RoundingFunction;
    }

    /* Integrator Block: '<S42>/Integrator1'
     */
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateLgV2_PrevZCSigState.Integrator1_Reset_ZCE,
                         TemplateLgV2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateLgV2_P.ctrl2ResetIntegrator_Value != 0.0 ||
          TemplateLgV2_DWork.Integrator1_IWORK.IcNeedsLoading) {
        TemplateLgV2_X.Integrator1_CSTATE = TemplateLgV2_B.Initials;
      }

      TemplateLgV2_DWork.Integrator1_IWORK.IcNeedsLoading = 0;
    }

    TemplateLgV2_B.Integrator1 = TemplateLgV2_X.Integrator1_CSTATE;

    /* Product: '<S145>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    TemplateLgV2_B.Product2_i = TemplateLgV2_B.Integrator1 *
      TemplateLgV2_P.k_Value;

    /* Trigonometry: '<S145>/sin(s)' */
    TemplateLgV2_B.sins = sin(TemplateLgV2_B.Product2_i);

    /* Product: '<S145>/Product' incorporates:
     *  Constant: '<S10>/k [-]'
     *  Constant: '<S10>/r_x [m]'
     */
    TemplateLgV2_B.Product_ei = TemplateLgV2_P.r_xm_Value * TemplateLgV2_B.sins *
      TemplateLgV2_P.k_Value;

    /* Gain: '<S145>/Gain' */
    TemplateLgV2_B.Gain_m = TemplateLgV2_P.Gain_Gain_p *
      TemplateLgV2_B.Product_ei;

    /* Trigonometry: '<S145>/cos(s)' */
    TemplateLgV2_B.coss = cos(TemplateLgV2_B.Product2_i);

    /* Product: '<S145>/Product1' incorporates:
     *  Constant: '<S10>/k [-]'
     *  Constant: '<S10>/r_y [m]'
     */
    TemplateLgV2_B.Product1_l = TemplateLgV2_P.r_ym_Value * TemplateLgV2_B.coss *
      TemplateLgV2_P.k_Value;

    /* SignalConversion: '<S148>/TmpHiddenBufferAtProductInport2' */
    TemplateLgV2_B.TmpHiddenBufferAtProductInpo_fu[0] = TemplateLgV2_B.Gain_m;
    TemplateLgV2_B.TmpHiddenBufferAtProductInpo_fu[1] =
      TemplateLgV2_B.Product1_l;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Sum: '<S152>/Subract' incorporates:
       *  Constant: '<S152>/Constant'
       */
      TemplateLgV2_B.Subract = TemplateLgV2_P.Constant_Value_o -
        TemplateLgV2_B.RoundingFunction;
    }

    /* Product: '<S152>/Product1' */
    TemplateLgV2_B.Product1_h[0] =
      TemplateLgV2_B.TmpHiddenBufferAtProductInpo_fu[0] * TemplateLgV2_B.Subract;

    /* Sum: '<S152>/Add' */
    TemplateLgV2_B.Add[0] = TemplateLgV2_B.Product_j[0] +
      TemplateLgV2_B.Product1_h[0];

    /* Product: '<S152>/Product1' */
    TemplateLgV2_B.Product1_h[1] =
      TemplateLgV2_B.TmpHiddenBufferAtProductInpo_fu[1] * TemplateLgV2_B.Subract;

    /* Sum: '<S152>/Add' */
    TemplateLgV2_B.Add[1] = TemplateLgV2_B.Product_j[1] +
      TemplateLgV2_B.Product1_h[1];

    /* Trigonometry: '<S97>/Trigonometric Function' */
    TemplateLgV2_B.TrigonometricFunction = rt_atan2_snf(TemplateLgV2_B.Add[1],
      TemplateLgV2_B.Add[0]);

    /* Saturate: '<S100>/Saturation' */
    tmp = TemplateLgV2_B.TrigonometricFunction;
    TemplateLgV2_B.Saturation_f = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_i, TemplateLgV2_P.Saturation_UpperSat_l);

    /* Signum: '<S100>/Sign' */
    TemplateLgV2_B.Sign_gh = rt_SIGNd_snf(TemplateLgV2_B.Saturation_f);

    /* Gain: '<S100>/Gain' */
    TemplateLgV2_B.Gain_bz = TemplateLgV2_P.Gain_Gain_n * TemplateLgV2_B.Sign_gh;

    /* Sum: '<S100>/Sum1' */
    TemplateLgV2_B.Sum1_n = TemplateLgV2_B.Saturation_f + TemplateLgV2_B.Gain_bz;

    /* Math: '<S100>/Math Function' incorporates:
     *  Constant: '<S100>/Constant'
     */
    TemplateLgV2_B.MathFunction_i = rt_rem_snf(TemplateLgV2_B.Sum1_n,
      TemplateLgV2_P.Constant_Value_l);

    /* Sum: '<S100>/Sum' */
    TemplateLgV2_B.Sum_g = TemplateLgV2_B.MathFunction_i -
      TemplateLgV2_B.Gain_bz;

    /* Saturate: '<S128>/Saturation' */
    tmp = TemplateLgV2_B.Sum_g;
    TemplateLgV2_B.Saturation_n = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_h, TemplateLgV2_P.Saturation_UpperSat_n);

    /* Signum: '<S128>/Sign' */
    TemplateLgV2_B.Sign_ga = rt_SIGNd_snf(TemplateLgV2_B.Saturation_n);

    /* Gain: '<S128>/Gain' */
    TemplateLgV2_B.Gain_dx = TemplateLgV2_P.Gain_Gain_h * TemplateLgV2_B.Sign_ga;

    /* Sum: '<S128>/Sum1' */
    TemplateLgV2_B.Sum1_e = TemplateLgV2_B.Saturation_n + TemplateLgV2_B.Gain_dx;

    /* Math: '<S128>/Math Function' incorporates:
     *  Constant: '<S128>/Constant'
     */
    TemplateLgV2_B.MathFunction_a = rt_rem_snf(TemplateLgV2_B.Sum1_e,
      TemplateLgV2_P.Constant_Value_lt);

    /* Sum: '<S128>/Sum' */
    TemplateLgV2_B.Sum_f = TemplateLgV2_B.MathFunction_a -
      TemplateLgV2_B.Gain_dx;

    /* Outputs for atomic SubSystem: '<S105>/R_2' */

    /* Trigonometry: '<S131>/R11' */
    TemplateLgV2_B.R11_f = cos(TemplateLgV2_B.Sum_g);

    /* Trigonometry: '<S131>/R21' */
    TemplateLgV2_B.R21_d = sin(TemplateLgV2_B.Sum_g);

    /* Gain: '<S131>/R12' */
    TemplateLgV2_B.R12_h = TemplateLgV2_P.R12_Gain * TemplateLgV2_B.R21_d;

    /* Gain: '<S131>/R22' */
    TemplateLgV2_B.R22_l = TemplateLgV2_P.R22_Gain * TemplateLgV2_B.R11_f;

    /* Reshape: '<S131>/R_2(psi_d)' */
    TemplateLgV2_B.R_2psi_d[0] = TemplateLgV2_B.R11_f;
    TemplateLgV2_B.R_2psi_d[1] = TemplateLgV2_B.R21_d;
    TemplateLgV2_B.R_2psi_d[2] = TemplateLgV2_B.R12_h;
    TemplateLgV2_B.R_2psi_d[3] = TemplateLgV2_B.R22_l;

    /* end of Outputs for SubSystem: '<S105>/R_2' */

    /* Math: '<S132>/Math Function' */
    TemplateLgV2_B.MathFunction_e[0] = TemplateLgV2_B.R_2psi_d[0];
    TemplateLgV2_B.MathFunction_e[1] = TemplateLgV2_B.R_2psi_d[2];
    TemplateLgV2_B.MathFunction_e[2] = TemplateLgV2_B.R_2psi_d[1];
    TemplateLgV2_B.MathFunction_e[3] = TemplateLgV2_B.R_2psi_d[3];
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Sum: '<S158>/x_2 - x_1' incorporates:
       *  Constant: '<S11>/x_1 [m]'
       *  Constant: '<S11>/x_2 [m]'
       */
      TemplateLgV2_B.x_2x_1_f = TemplateLgV2_P.x_2m_Value -
        TemplateLgV2_P.x_1m_Value;
    }

    /* Product: '<S158>/(x_2 - x_1) * s' */
    TemplateLgV2_B.x_2x_1s = TemplateLgV2_B.x_2x_1_f *
      TemplateLgV2_B.Integrator1;

    /* Sum: '<S158>/(x_2 - x_1) * s + x_1' incorporates:
     *  Constant: '<S11>/x_1 [m]'
     */
    TemplateLgV2_B.x_2x_1sx_1 = TemplateLgV2_B.x_2x_1s +
      TemplateLgV2_P.x_1m_Value;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Sum: '<S158>/y_2 - y_1' incorporates:
       *  Constant: '<S11>/y_1 [m]'
       *  Constant: '<S11>/y_2 [m]'
       */
      TemplateLgV2_B.y_2y_1_g = TemplateLgV2_P.y_2m_Value -
        TemplateLgV2_P.y_1m_Value;
    }

    /* Product: '<S158>/(y_2 - y_1) * s' */
    TemplateLgV2_B.y_2y_1s = TemplateLgV2_B.y_2y_1_g *
      TemplateLgV2_B.Integrator1;

    /* Sum: '<S158>/(y_2 - y_1) * s + y_1' incorporates:
     *  Constant: '<S11>/y_1 [m]'
     */
    TemplateLgV2_B.y_2y_1sy_1 = TemplateLgV2_B.y_2y_1s +
      TemplateLgV2_P.y_1m_Value;

    /* Product: '<S151>/Product' */
    TemplateLgV2_B.Product_ny[0] = TemplateLgV2_B.x_2x_1sx_1 *
      TemplateLgV2_B.RoundingFunction;
    TemplateLgV2_B.Product_ny[1] = TemplateLgV2_B.y_2y_1sy_1 *
      TemplateLgV2_B.RoundingFunction;

    /* Product: '<S144>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    TemplateLgV2_B.Product2_m = TemplateLgV2_B.Integrator1 *
      TemplateLgV2_P.k_Value;

    /* Trigonometry: '<S144>/cos(s)' */
    TemplateLgV2_B.coss_l = cos(TemplateLgV2_B.Product2_m);

    /* Product: '<S144>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    TemplateLgV2_B.Product_o = TemplateLgV2_P.r_xm_Value * TemplateLgV2_B.coss_l;

    /* Sum: '<S144>/Add' incorporates:
     *  Constant: '<S10>/x_0 [m]'
     */
    TemplateLgV2_B.Add_p = TemplateLgV2_B.Product_o + TemplateLgV2_P.x_0m_Value;

    /* Trigonometry: '<S144>/sin(s)' */
    TemplateLgV2_B.sins_h = sin(TemplateLgV2_B.Product2_m);

    /* Product: '<S144>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    TemplateLgV2_B.Product1_b = TemplateLgV2_P.r_ym_Value *
      TemplateLgV2_B.sins_h;

    /* Sum: '<S144>/Add1' incorporates:
     *  Constant: '<S10>/y_0 [m]'
     */
    TemplateLgV2_B.Add1_d = TemplateLgV2_B.Product1_b +
      TemplateLgV2_P.y_0m_Value;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Sum: '<S151>/Subract' incorporates:
       *  Constant: '<S151>/Constant'
       */
      TemplateLgV2_B.Subract_a = TemplateLgV2_P.Constant_Value_a -
        TemplateLgV2_B.RoundingFunction;
    }

    /* Product: '<S151>/Product1' */
    TemplateLgV2_B.Product1_lc[0] = TemplateLgV2_B.Add_p *
      TemplateLgV2_B.Subract_a;
    TemplateLgV2_B.Product1_lc[1] = TemplateLgV2_B.Add1_d *
      TemplateLgV2_B.Subract_a;

    /* Sum: '<S151>/Add' */
    TemplateLgV2_B.Add_k[0] = TemplateLgV2_B.Product_ny[0] +
      TemplateLgV2_B.Product1_lc[0];
    TemplateLgV2_B.Add_k[1] = TemplateLgV2_B.Product_ny[1] +
      TemplateLgV2_B.Product1_lc[1];

    /* RelationalOperator: '<S156>/LowerRelop1' incorporates:
     *  Constant: '<S5>/x_dmax [m]'
     */
    TemplateLgV2_B.LowerRelop1 = (TemplateLgV2_B.Add_k[0] >
      TemplateLgV2_P.x_dmaxm_Value);

    /* RelationalOperator: '<S156>/UpperRelop' incorporates:
     *  Constant: '<S5>/x_dmin [m]'
     */
    TemplateLgV2_B.UpperRelop = (TemplateLgV2_B.Add_k[0] <
      TemplateLgV2_P.x_dminm_Value);

    /* Switch: '<S156>/Switch' incorporates:
     *  Constant: '<S5>/x_dmin [m]'
     */
    if (TemplateLgV2_B.UpperRelop) {
      TemplateLgV2_B.Switch = TemplateLgV2_P.x_dminm_Value;
    } else {
      TemplateLgV2_B.Switch = TemplateLgV2_B.Add_k[0];
    }

    /* Switch: '<S156>/Switch2' incorporates:
     *  Constant: '<S5>/x_dmax [m]'
     */
    if (TemplateLgV2_B.LowerRelop1) {
      TemplateLgV2_B.Switch2 = TemplateLgV2_P.x_dmaxm_Value;
    } else {
      TemplateLgV2_B.Switch2 = TemplateLgV2_B.Switch;
    }

    /* RelationalOperator: '<S157>/LowerRelop1' incorporates:
     *  Constant: '<S5>/y_dmax [m]'
     */
    TemplateLgV2_B.LowerRelop1_c = (TemplateLgV2_B.Add_k[1] >
      TemplateLgV2_P.y_dmaxm_Value);

    /* RelationalOperator: '<S157>/UpperRelop' incorporates:
     *  Constant: '<S5>/y_dmin [m]'
     */
    TemplateLgV2_B.UpperRelop_g = (TemplateLgV2_B.Add_k[1] <
      TemplateLgV2_P.y_dminm_Value);

    /* Switch: '<S157>/Switch' incorporates:
     *  Constant: '<S5>/y_dmin [m]'
     */
    if (TemplateLgV2_B.UpperRelop_g) {
      TemplateLgV2_B.Switch_b = TemplateLgV2_P.y_dminm_Value;
    } else {
      TemplateLgV2_B.Switch_b = TemplateLgV2_B.Add_k[1];
    }

    /* Switch: '<S157>/Switch2' incorporates:
     *  Constant: '<S5>/y_dmax [m]'
     */
    if (TemplateLgV2_B.LowerRelop1_c) {
      TemplateLgV2_B.Switch2_i = TemplateLgV2_P.y_dmaxm_Value;
    } else {
      TemplateLgV2_B.Switch2_i = TemplateLgV2_B.Switch_b;
    }

    /* Sum: '<S94>/Subtract' */
    TemplateLgV2_B.Subtract[0] = TemplateLgV2_B.Integrator_e[0] -
      TemplateLgV2_B.Switch2;
    TemplateLgV2_B.Subtract[1] = TemplateLgV2_B.Integrator_e[1] -
      TemplateLgV2_B.Switch2_i;

    /* Product: '<S105>/epsilon' */
    TemplateLgV2_B.epsilon[0] = 0.0;
    TemplateLgV2_B.epsilon[0] = TemplateLgV2_B.MathFunction_e[0] *
      TemplateLgV2_B.Subtract[0] + TemplateLgV2_B.epsilon[0];
    TemplateLgV2_B.epsilon[0] = TemplateLgV2_B.MathFunction_e[2] *
      TemplateLgV2_B.Subtract[1] + TemplateLgV2_B.epsilon[0];
    TemplateLgV2_B.epsilon[1] = 0.0;
    TemplateLgV2_B.epsilon[1] = TemplateLgV2_B.MathFunction_e[1] *
      TemplateLgV2_B.Subtract[0] + TemplateLgV2_B.epsilon[1];
    TemplateLgV2_B.epsilon[1] = TemplateLgV2_B.MathFunction_e[3] *
      TemplateLgV2_B.Subtract[1] + TemplateLgV2_B.epsilon[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector' */
    {
      const byte_T *u = (byte_T *)TemplateLgV2_B.epsilon;/* input port */
      const int32_T *index = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&TemplateLgV2_B.MultiportSelector;
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
    TemplateLgV2_B.TrigonometricFunction_i = rt_atan2_snf
      (TemplateLgV2_B.MultiportSelector, TemplateLgV2_P.Deltam_Value);

    /* Saturate: '<S129>/Saturation' */
    tmp = TemplateLgV2_B.TrigonometricFunction_i;
    TemplateLgV2_B.Saturation_ig = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_e, TemplateLgV2_P.Saturation_UpperSat_o);

    /* Signum: '<S129>/Sign' */
    TemplateLgV2_B.Sign_p = rt_SIGNd_snf(TemplateLgV2_B.Saturation_ig);

    /* Gain: '<S129>/Gain' */
    TemplateLgV2_B.Gain_mb = TemplateLgV2_P.Gain_Gain_c * TemplateLgV2_B.Sign_p;

    /* Sum: '<S129>/Sum1' */
    TemplateLgV2_B.Sum1_p = TemplateLgV2_B.Saturation_ig +
      TemplateLgV2_B.Gain_mb;

    /* Math: '<S129>/Math Function' incorporates:
     *  Constant: '<S129>/Constant'
     */
    TemplateLgV2_B.MathFunction_g = rt_rem_snf(TemplateLgV2_B.Sum1_p,
      TemplateLgV2_P.Constant_Value_ia);

    /* Sum: '<S129>/Sum' */
    TemplateLgV2_B.Sum_h = TemplateLgV2_B.MathFunction_g -
      TemplateLgV2_B.Gain_mb;

    /* Sum: '<S122>/Subtract' */
    TemplateLgV2_B.Subtract_c = TemplateLgV2_B.Sum_f - TemplateLgV2_B.Sum_h;

    /* Saturate: '<S130>/Saturation' */
    tmp = TemplateLgV2_B.Subtract_c;
    TemplateLgV2_B.Saturation_l = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_c,
      TemplateLgV2_P.Saturation_UpperSat_kp);

    /* Signum: '<S130>/Sign' */
    TemplateLgV2_B.Sign_gq = rt_SIGNd_snf(TemplateLgV2_B.Saturation_l);

    /* Gain: '<S130>/Gain' */
    TemplateLgV2_B.Gain_o = TemplateLgV2_P.Gain_Gain_b * TemplateLgV2_B.Sign_gq;

    /* Sum: '<S130>/Sum1' */
    TemplateLgV2_B.Sum1_b0 = TemplateLgV2_B.Saturation_l + TemplateLgV2_B.Gain_o;

    /* Math: '<S130>/Math Function' incorporates:
     *  Constant: '<S130>/Constant'
     */
    TemplateLgV2_B.MathFunction_j0 = rt_rem_snf(TemplateLgV2_B.Sum1_b0,
      TemplateLgV2_P.Constant_Value_e);

    /* Sum: '<S130>/Sum' */
    TemplateLgV2_B.Sum_a = TemplateLgV2_B.MathFunction_j0 -
      TemplateLgV2_B.Gain_o;

    /* SignalConversion: '<S106>/ConcatBufferAtVector ConcatenateIn2' */
    TemplateLgV2_B.VectorConcatenate[2] = TemplateLgV2_B.Sum_a;

    /* Sum: '<S48>/Subtract' */
    TemplateLgV2_B.Subtract_d[0] = TemplateLgV2_B.etaSwitch[0] -
      TemplateLgV2_B.VectorConcatenate[0];
    TemplateLgV2_B.Subtract_d[1] = TemplateLgV2_B.etaSwitch[1] -
      TemplateLgV2_B.VectorConcatenate[1];
    TemplateLgV2_B.Subtract_d[2] = TemplateLgV2_B.Sum_e -
      TemplateLgV2_B.VectorConcatenate[2];

    /* Saturate: '<S70>/Saturation' */
    tmp = TemplateLgV2_B.Subtract_d[2];
    TemplateLgV2_B.Saturation_m = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_h3,
      TemplateLgV2_P.Saturation_UpperSat_i);

    /* Signum: '<S70>/Sign' */
    TemplateLgV2_B.Sign_d = rt_SIGNd_snf(TemplateLgV2_B.Saturation_m);

    /* Gain: '<S70>/Gain' */
    TemplateLgV2_B.Gain_f = TemplateLgV2_P.Gain_Gain_o * TemplateLgV2_B.Sign_d;

    /* Sum: '<S70>/Sum1' */
    TemplateLgV2_B.Sum1_m = TemplateLgV2_B.Saturation_m + TemplateLgV2_B.Gain_f;

    /* Math: '<S70>/Math Function' incorporates:
     *  Constant: '<S70>/Constant'
     */
    TemplateLgV2_B.MathFunction_p = rt_rem_snf(TemplateLgV2_B.Sum1_m,
      TemplateLgV2_P.Constant_Value_o0);

    /* Sum: '<S70>/Sum' */
    TemplateLgV2_B.Sum_ag = TemplateLgV2_B.MathFunction_p -
      TemplateLgV2_B.Gain_f;

    /* SignalConversion: '<S48>/TmpHiddenBufferAtProductInport2' */
    TemplateLgV2_B.TmpHiddenBufferAtProductInpo_nx[0] =
      TemplateLgV2_B.Subtract_d[0];
    TemplateLgV2_B.TmpHiddenBufferAtProductInpo_nx[1] =
      TemplateLgV2_B.Subtract_d[1];
    TemplateLgV2_B.TmpHiddenBufferAtProductInpo_nx[2] = TemplateLgV2_B.Sum_ag;

    /* Product: '<S48>/Product' */
    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.Product_a[i] = 0.0;
      TemplateLgV2_B.Product_a[i] = TemplateLgV2_B.MathFunction_k[i] *
        TemplateLgV2_B.TmpHiddenBufferAtProductInpo_nx[0] +
        TemplateLgV2_B.Product_a[i];
      TemplateLgV2_B.Product_a[i] = TemplateLgV2_B.MathFunction_k[i + 3] *
        TemplateLgV2_B.TmpHiddenBufferAtProductInpo_nx[1] +
        TemplateLgV2_B.Product_a[i];
      TemplateLgV2_B.Product_a[i] = TemplateLgV2_B.MathFunction_k[i + 6] *
        TemplateLgV2_B.TmpHiddenBufferAtProductInpo_nx[2] +
        TemplateLgV2_B.Product_a[i];
    }

    /* Product: '<S44>/Product1' */
    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.Product1_g[i] = 0.0;
      TemplateLgV2_B.Product1_g[i] = TemplateLgV2_B.Add3[i] *
        TemplateLgV2_B.Product_a[0] + TemplateLgV2_B.Product1_g[i];
      TemplateLgV2_B.Product1_g[i] = TemplateLgV2_B.Add3[i + 3] *
        TemplateLgV2_B.Product_a[1] + TemplateLgV2_B.Product1_g[i];
      TemplateLgV2_B.Product1_g[i] = TemplateLgV2_B.Add3[i + 6] *
        TemplateLgV2_B.Product_a[2] + TemplateLgV2_B.Product1_g[i];
    }

    /* Trigonometry: '<S107>/f_qx' */
    TemplateLgV2_B.f_qx = cos(TemplateLgV2_B.Sum_a);

    /* Trigonometry: '<S107>/f_qy' */
    TemplateLgV2_B.f_qy = sin(TemplateLgV2_B.Sum_a);

    /* SignalConversion: '<S107>/TmpHiddenBufferAtProductInport1' */
    TemplateLgV2_B.TmpHiddenBufferAtProductInport1[0] = TemplateLgV2_B.f_qx;
    TemplateLgV2_B.TmpHiddenBufferAtProductInport1[1] = TemplateLgV2_B.f_qy;

    /* Product: '<S107>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateLgV2_B.Product_l[0] =
      TemplateLgV2_B.TmpHiddenBufferAtProductInport1[0] *
      TemplateLgV2_P.u_dm_Value;
    TemplateLgV2_B.Product_l[1] =
      TemplateLgV2_B.TmpHiddenBufferAtProductInport1[1] *
      TemplateLgV2_P.u_dm_Value;

    /* SignalConversion: '<S51>/ConcatBufferAtVector ConcatenateIn1' */
    TemplateLgV2_B.VectorConcatenate_l[0] = TemplateLgV2_B.Product_l[0];
    TemplateLgV2_B.VectorConcatenate_l[1] = TemplateLgV2_B.Product_l[1];
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S123>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.Delta2 = tmp * tmp;
    }

    /* Math: '<S123>/epsilon_n^2' */
    tmp = TemplateLgV2_B.MultiportSelector;
    TemplateLgV2_B.epsilon_n2 = tmp * tmp;

    /* Sum: '<S123>/Add' */
    TemplateLgV2_B.Add_b = TemplateLgV2_B.Delta2 + TemplateLgV2_B.epsilon_n2;

    /* Product: '<S123>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Divide_d = TemplateLgV2_P.Deltam_Value / TemplateLgV2_B.Add_b;

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector1' */
    {
      const byte_T *u = (byte_T *)TemplateLgV2_B.MathFunction_e;/* input port */
      const int32_T *index = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)TemplateLgV2_B.MultiportSelector1;
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
    TemplateLgV2_B.Product_p[0] = TemplateLgV2_B.Divide_d *
      TemplateLgV2_B.MultiportSelector1[0];

    /* Gain: '<S123>/-1' */
    TemplateLgV2_B.u_c[0] = TemplateLgV2_P.u_Gain_m * TemplateLgV2_B.Product_p[0];

    /* Product: '<S123>/Product' */
    TemplateLgV2_B.Product_p[1] = TemplateLgV2_B.Divide_d *
      TemplateLgV2_B.MultiportSelector1[1];

    /* Gain: '<S123>/-1' */
    TemplateLgV2_B.u_c[1] = TemplateLgV2_P.u_Gain_m * TemplateLgV2_B.Product_p[1];

    /* Product: '<S51>/Product' */
    tmp = TemplateLgV2_B.u_c[0] * TemplateLgV2_B.Product_l[0];
    tmp += TemplateLgV2_B.u_c[1] * TemplateLgV2_B.Product_l[1];
    TemplateLgV2_B.VectorConcatenate_l[2] = tmp;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Constant: '<S57>/0_2x1' */
      TemplateLgV2_B.VectorConcatenate_a[0] = TemplateLgV2_P._2x1_Value[0];
      TemplateLgV2_B.VectorConcatenate_a[1] = TemplateLgV2_P._2x1_Value[1];

      /* Product: '<S153>/Product' incorporates:
       *  Constant: '<S143>/0_2x1'
       */
      TemplateLgV2_B.Product_g[0] = TemplateLgV2_P._2x1_Value_h[0] *
        TemplateLgV2_B.RoundingFunction;
      TemplateLgV2_B.Product_g[1] = TemplateLgV2_P._2x1_Value_h[1] *
        TemplateLgV2_B.RoundingFunction;
    }

    /* Product: '<S146>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    TemplateLgV2_B.Product2_l = TemplateLgV2_B.Integrator1 *
      TemplateLgV2_P.k_Value;

    /* Trigonometry: '<S146>/cos(s)' */
    TemplateLgV2_B.coss_f = cos(TemplateLgV2_B.Product2_l);
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S146>/Math Function' incorporates:
       *  Constant: '<S10>/k [-]'
       */
      tmp = TemplateLgV2_P.k_Value;
      TemplateLgV2_B.MathFunction_f = tmp * tmp;
    }

    /* Product: '<S146>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    TemplateLgV2_B.Product_go = TemplateLgV2_P.r_xm_Value *
      TemplateLgV2_B.coss_f * TemplateLgV2_B.MathFunction_f;

    /* Gain: '<S146>/Gain' */
    TemplateLgV2_B.Gain_j = TemplateLgV2_P.Gain_Gain_l *
      TemplateLgV2_B.Product_go;

    /* Trigonometry: '<S146>/sin(s)' */
    TemplateLgV2_B.sins_n = sin(TemplateLgV2_B.Product2_l);

    /* Product: '<S146>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    TemplateLgV2_B.Product1_i = TemplateLgV2_P.r_ym_Value *
      TemplateLgV2_B.sins_n * TemplateLgV2_B.MathFunction_f;

    /* Gain: '<S146>/Gain1' */
    TemplateLgV2_B.Gain1_f = TemplateLgV2_P.Gain1_Gain_e *
      TemplateLgV2_B.Product1_i;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Sum: '<S153>/Subract' incorporates:
       *  Constant: '<S153>/Constant'
       */
      TemplateLgV2_B.Subract_d = TemplateLgV2_P.Constant_Value_ltw -
        TemplateLgV2_B.RoundingFunction;
    }

    /* Product: '<S153>/Product1' */
    TemplateLgV2_B.Product1_c[0] = TemplateLgV2_B.Gain_j *
      TemplateLgV2_B.Subract_d;
    TemplateLgV2_B.Product1_c[1] = TemplateLgV2_B.Gain1_f *
      TemplateLgV2_B.Subract_d;

    /* Sum: '<S153>/Add' */
    TemplateLgV2_B.Add_o[0] = TemplateLgV2_B.Product_g[0] +
      TemplateLgV2_B.Product1_c[0];
    TemplateLgV2_B.Add_o[1] = TemplateLgV2_B.Product_g[1] +
      TemplateLgV2_B.Product1_c[1];

    /* Product: '<S98>/x_d^s * y_d^s^2' */
    TemplateLgV2_B.x_dsy_ds2 = TemplateLgV2_B.Add[0] * TemplateLgV2_B.Add_o[1];

    /* Product: '<S98>/x_d^s^2 * y_d^s' */
    TemplateLgV2_B.x_ds2y_ds = TemplateLgV2_B.Add_o[0] * TemplateLgV2_B.Add[1];

    /* Sum: '<S98>/( x_d^s * y_d^s^2 ) - ( x_d^s^2 * y_d^s ) ' */
    TemplateLgV2_B.x_dsy_ds2x_ds2y_ds = TemplateLgV2_B.x_dsy_ds2 -
      TemplateLgV2_B.x_ds2y_ds;

    /* Math: '<S98>/( x_d^s )^2' */
    tmp = TemplateLgV2_B.Add[0];
    TemplateLgV2_B.x_ds2 = tmp * tmp;

    /* Math: '<S98>/( y_d^s )^2' */
    tmp = TemplateLgV2_B.Add[1];
    TemplateLgV2_B.y_ds2 = tmp * tmp;

    /* Sum: '<S98>/( x_d^s )^2 + ( y_d^s )^2' */
    TemplateLgV2_B.x_ds2y_ds2 = TemplateLgV2_B.x_ds2 + TemplateLgV2_B.y_ds2;

    /* Product: '<S98>/Divide' */
    TemplateLgV2_B.Divide_c = TemplateLgV2_B.x_dsy_ds2x_ds2y_ds /
      TemplateLgV2_B.x_ds2y_ds2;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S126>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.Delta2_i = tmp * tmp;
    }

    /* Math: '<S126>/epsilon_n^2' */
    tmp = TemplateLgV2_B.MultiportSelector;
    TemplateLgV2_B.epsilon_n2_h = tmp * tmp;

    /* Sum: '<S126>/Add' */
    TemplateLgV2_B.Add_l = TemplateLgV2_B.Delta2_i + TemplateLgV2_B.epsilon_n2_h;

    /* Product: '<S126>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Divide_e = TemplateLgV2_P.Deltam_Value / TemplateLgV2_B.Add_l;

    /* Outputs for atomic SubSystem: '<S105>/S_2' */

    /* Gain: '<S133>/S12' */
    TemplateLgV2_B.S12_e4 = TemplateLgV2_P.S12_Gain_h * TemplateLgV2_B.Divide_c;

    /* Reshape: '<S133>/S_2(psi_d^s)' incorporates:
     *  Constant: '<S133>/0'
     */
    TemplateLgV2_B.S_2psi_ds[0] = TemplateLgV2_P._Value_g;
    TemplateLgV2_B.S_2psi_ds[1] = TemplateLgV2_B.Divide_c;
    TemplateLgV2_B.S_2psi_ds[2] = TemplateLgV2_B.S12_e4;
    TemplateLgV2_B.S_2psi_ds[3] = TemplateLgV2_P._Value_g;

    /* end of Outputs for SubSystem: '<S105>/S_2' */

    /* Math: '<S136>/Math Function' */
    TemplateLgV2_B.MathFunction_fh[0] = TemplateLgV2_B.S_2psi_ds[0];
    TemplateLgV2_B.MathFunction_fh[1] = TemplateLgV2_B.S_2psi_ds[2];
    TemplateLgV2_B.MathFunction_fh[2] = TemplateLgV2_B.S_2psi_ds[1];
    TemplateLgV2_B.MathFunction_fh[3] = TemplateLgV2_B.S_2psi_ds[3];

    /* Product: '<S138>/Product' */
    for (i = 0; i < 2; i++) {
      tmp_2[i] = 0.0;
      tmp_2[i] += TemplateLgV2_B.MathFunction_fh[i] *
        TemplateLgV2_B.MathFunction_e[0];
      tmp_2[i] += TemplateLgV2_B.MathFunction_fh[i + 2] *
        TemplateLgV2_B.MathFunction_e[1];
      tmp_2[i + 2] = 0.0;
      tmp_2[i + 2] += TemplateLgV2_B.MathFunction_fh[i] *
        TemplateLgV2_B.MathFunction_e[2];
      tmp_2[i + 2] += TemplateLgV2_B.MathFunction_fh[i + 2] *
        TemplateLgV2_B.MathFunction_e[3];
    }

    TemplateLgV2_B.Product_oe[0] = 0.0;
    TemplateLgV2_B.Product_oe[0] = tmp_2[0] * TemplateLgV2_B.Subtract[0] +
      TemplateLgV2_B.Product_oe[0];
    TemplateLgV2_B.Product_oe[0] = tmp_2[2] * TemplateLgV2_B.Subtract[1] +
      TemplateLgV2_B.Product_oe[0];

    /* Product: '<S138>/Product1' */
    TemplateLgV2_B.Product1_f[0] = 0.0;
    TemplateLgV2_B.Product1_f[0] = TemplateLgV2_B.MathFunction_e[0] *
      TemplateLgV2_B.Add[0] + TemplateLgV2_B.Product1_f[0];
    TemplateLgV2_B.Product1_f[0] = TemplateLgV2_B.MathFunction_e[2] *
      TemplateLgV2_B.Add[1] + TemplateLgV2_B.Product1_f[0];

    /* Sum: '<S138>/Subtract1' */
    TemplateLgV2_B.Subtract1[0] = TemplateLgV2_B.Product_oe[0] -
      TemplateLgV2_B.Product1_f[0];
    TemplateLgV2_B.Product_oe[1] = 0.0;
    TemplateLgV2_B.Product_oe[1] = tmp_2[1] * TemplateLgV2_B.Subtract[0] +
      TemplateLgV2_B.Product_oe[1];
    TemplateLgV2_B.Product_oe[1] = tmp_2[3] * TemplateLgV2_B.Subtract[1] +
      TemplateLgV2_B.Product_oe[1];

    /* Product: '<S138>/Product1' */
    TemplateLgV2_B.Product1_f[1] = 0.0;
    TemplateLgV2_B.Product1_f[1] = TemplateLgV2_B.MathFunction_e[1] *
      TemplateLgV2_B.Add[0] + TemplateLgV2_B.Product1_f[1];
    TemplateLgV2_B.Product1_f[1] = TemplateLgV2_B.MathFunction_e[3] *
      TemplateLgV2_B.Add[1] + TemplateLgV2_B.Product1_f[1];

    /* Sum: '<S138>/Subtract1' */
    TemplateLgV2_B.Subtract1[1] = TemplateLgV2_B.Product_oe[1] -
      TemplateLgV2_B.Product1_f[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector2' */
    {
      const byte_T *u = (byte_T *)TemplateLgV2_B.Subtract1;/* input port */
      const int32_T *index = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&TemplateLgV2_B.MultiportSelector2;
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
    TemplateLgV2_B.Product_ex = TemplateLgV2_B.Divide_e *
      TemplateLgV2_B.MultiportSelector2;

    /* Sum: '<S126>/Subtract' */
    TemplateLgV2_B.Subtract_k = TemplateLgV2_B.Divide_c -
      TemplateLgV2_B.Product_ex;

    /* Math: '<S111>/epsilon_n^2' */
    tmp = TemplateLgV2_B.MultiportSelector;
    TemplateLgV2_B.epsilon_n2_j = tmp * tmp;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S111>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.Delta2_n = tmp * tmp;
    }

    /* Sum: '<S111>/Add' */
    TemplateLgV2_B.Add_i = TemplateLgV2_B.epsilon_n2_j + TemplateLgV2_B.Delta2_n;

    /* Math: '<S111>/sqrt' */
    tmp = TemplateLgV2_B.Add_i;
    if (tmp < 0.0) {
      TemplateLgV2_B.sqrt_m = -sqrt(-tmp);
    } else {
      TemplateLgV2_B.sqrt_m = sqrt(tmp);
    }

    /* Product: '<S111>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Divide_dn = TemplateLgV2_P.Deltam_Value /
      TemplateLgV2_B.sqrt_m;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S161>/Math Function' */
      TemplateLgV2_B.MathFunction_o[0] =
        TemplateLgV2_B.TmpHiddenBufferAtProductInpor_n[0];
      TemplateLgV2_B.MathFunction_o[1] =
        TemplateLgV2_B.TmpHiddenBufferAtProductInpor_n[1];

      /* Product: '<S160>/Product' */
      tmp = TemplateLgV2_B.MathFunction_o[0] *
        TemplateLgV2_B.TmpHiddenBufferAtProductInpor_n[0];
      tmp += TemplateLgV2_B.MathFunction_o[1] *
        TemplateLgV2_B.TmpHiddenBufferAtProductInpor_n[1];
      TemplateLgV2_B.Product_nyn = tmp;

      /* Math: '<S160>/sqrt' */
      tmp = TemplateLgV2_B.Product_nyn;
      if (tmp < 0.0) {
        TemplateLgV2_B.sqrt_c = -sqrt(-tmp);
      } else {
        TemplateLgV2_B.sqrt_c = sqrt(tmp);
      }

      /* Product: '<S155>/Product' */
      TemplateLgV2_B.Product_i = TemplateLgV2_B.sqrt_c *
        TemplateLgV2_B.RoundingFunction;
    }

    /* Math: '<S149>/Math Function' */
    TemplateLgV2_B.MathFunction_kk[0] =
      TemplateLgV2_B.TmpHiddenBufferAtProductInpo_fu[0];
    TemplateLgV2_B.MathFunction_kk[1] =
      TemplateLgV2_B.TmpHiddenBufferAtProductInpo_fu[1];

    /* Product: '<S148>/Product' */
    tmp = TemplateLgV2_B.MathFunction_kk[0] *
      TemplateLgV2_B.TmpHiddenBufferAtProductInpo_fu[0];
    tmp += TemplateLgV2_B.MathFunction_kk[1] *
      TemplateLgV2_B.TmpHiddenBufferAtProductInpo_fu[1];
    TemplateLgV2_B.Product_b = tmp;

    /* Math: '<S148>/sqrt' */
    tmp = TemplateLgV2_B.Product_b;
    if (tmp < 0.0) {
      TemplateLgV2_B.sqrt_j = -sqrt(-tmp);
    } else {
      TemplateLgV2_B.sqrt_j = sqrt(tmp);
    }

    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Sum: '<S155>/Subract' incorporates:
       *  Constant: '<S155>/Constant'
       */
      TemplateLgV2_B.Subract_o = TemplateLgV2_P.Constant_Value_ay -
        TemplateLgV2_B.RoundingFunction;
    }

    /* Product: '<S155>/Product1' */
    TemplateLgV2_B.Product1_g0 = TemplateLgV2_B.sqrt_j *
      TemplateLgV2_B.Subract_o;

    /* Sum: '<S155>/Add' */
    TemplateLgV2_B.Add_d = TemplateLgV2_B.Product_i + TemplateLgV2_B.Product1_g0;

    /* Product: '<S162>/Divide' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateLgV2_B.Divide_b = TemplateLgV2_P.u_dm_Value / TemplateLgV2_B.Add_d;

    /* Product: '<S111>/Product' */
    TemplateLgV2_B.Product_c = TemplateLgV2_B.Divide_dn *
      TemplateLgV2_B.Divide_b;

    /* Math: '<S118>/Math Function' */
    TemplateLgV2_B.MathFunction_fi[0] = TemplateLgV2_B.Add[0];

    /* Product: '<S115>/Divide' */
    TemplateLgV2_B.Divide_h[0] = TemplateLgV2_B.MathFunction_fi[0] /
      TemplateLgV2_B.Add_d;

    /* Math: '<S118>/Math Function' */
    TemplateLgV2_B.MathFunction_fi[1] = TemplateLgV2_B.Add[1];

    /* Product: '<S115>/Divide' */
    TemplateLgV2_B.Divide_h[1] = TemplateLgV2_B.MathFunction_fi[1] /
      TemplateLgV2_B.Add_d;

    /* Product: '<S115>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    tmp = TemplateLgV2_P.my_Value * TemplateLgV2_B.Divide_h[0] *
      TemplateLgV2_B.Subtract[0];
    tmp += TemplateLgV2_P.my_Value * TemplateLgV2_B.Divide_h[1] *
      TemplateLgV2_B.Subtract[1];
    TemplateLgV2_B.Product_k = tmp;

    /* Gain: '<S115>/Gain' */
    TemplateLgV2_B.Gain_p = TemplateLgV2_P.Gain_Gain_a *
      TemplateLgV2_B.Product_k;

    /* Sum: '<S111>/Subtract' */
    TemplateLgV2_B.Subtract_o = TemplateLgV2_B.Product_c - TemplateLgV2_B.Gain_p;

    /* Product: '<S57>/Product' */
    TemplateLgV2_B.VectorConcatenate_a[2] = TemplateLgV2_B.Subtract_k *
      TemplateLgV2_B.Subtract_o;

    /* Sum: '<S44>/Add' */
    TemplateLgV2_B.Add_m[0] = TemplateLgV2_B.VectorConcatenate_l[0] +
      TemplateLgV2_B.VectorConcatenate_a[0];
    TemplateLgV2_B.Add_m[1] = TemplateLgV2_B.VectorConcatenate_l[1] +
      TemplateLgV2_B.VectorConcatenate_a[1];
    TemplateLgV2_B.Add_m[2] = TemplateLgV2_B.VectorConcatenate_l[2] +
      TemplateLgV2_B.VectorConcatenate_a[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S44>/Product2' */
      TemplateLgV2_B.Product2_a[i] = 0.0;
      TemplateLgV2_B.Product2_a[i] = TemplateLgV2_B.MathFunction_k[i] *
        TemplateLgV2_B.Add_m[0] + TemplateLgV2_B.Product2_a[i];
      TemplateLgV2_B.Product2_a[i] = TemplateLgV2_B.MathFunction_k[i + 3] *
        TemplateLgV2_B.Add_m[1] + TemplateLgV2_B.Product2_a[i];
      TemplateLgV2_B.Product2_a[i] = TemplateLgV2_B.MathFunction_k[i + 6] *
        TemplateLgV2_B.Add_m[2] + TemplateLgV2_B.Product2_a[i];

      /* Sum: '<S44>/Sum' */
      TemplateLgV2_B.Sum_b[i] = TemplateLgV2_B.Product2_a[i] -
        TemplateLgV2_B.Product1_g[i];

      /* Sum: '<S49>/Subtract' */
      TemplateLgV2_B.Subtract_i[i] = TemplateLgV2_B.nuSwitch[i] -
        TemplateLgV2_B.Sum_b[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S39>/Product1' */
      TemplateLgV2_B.Product1_a[i] = 0.0;
      TemplateLgV2_B.Product1_a[i] = TemplateLgV2_B.Add1[i] *
        TemplateLgV2_B.Subtract_i[0] + TemplateLgV2_B.Product1_a[i];
      TemplateLgV2_B.Product1_a[i] = TemplateLgV2_B.Add1[i + 3] *
        TemplateLgV2_B.Subtract_i[1] + TemplateLgV2_B.Product1_a[i];
      TemplateLgV2_B.Product1_a[i] = TemplateLgV2_B.Add1[i + 6] *
        TemplateLgV2_B.Subtract_i[2] + TemplateLgV2_B.Product1_a[i];

      /* Gain: '<S39>/Gain1' */
      TemplateLgV2_B.Gain1_k[i] = TemplateLgV2_P.Gain1_Gain_k *
        TemplateLgV2_B.Product1_a[i];

      /* Product: '<S39>/Product2' */
      TemplateLgV2_B.Product2_d[i] = 0.0;
      TemplateLgV2_B.Product2_d[i] = TemplateLgV2_B.LinearDampningmatrix[i] *
        TemplateLgV2_B.nuSwitch[0] + TemplateLgV2_B.Product2_d[i];
      TemplateLgV2_B.Product2_d[i] = TemplateLgV2_B.LinearDampningmatrix[i + 3] *
        TemplateLgV2_B.nuSwitch[1] + TemplateLgV2_B.Product2_d[i];
      TemplateLgV2_B.Product2_d[i] = TemplateLgV2_B.LinearDampningmatrix[i + 6] *
        TemplateLgV2_B.nuSwitch[2] + TemplateLgV2_B.Product2_d[i];
    }

    /* Gain: '<S65>/S12' */
    TemplateLgV2_B.S12 = TemplateLgV2_P.S12_Gain * TemplateLgV2_B.nuSwitch[2];

    /* Reshape: '<S65>/S(r)' incorporates:
     *  Constant: '<S65>/R31'
     *  Constant: '<S65>/S11'
     *  Constant: '<S65>/S13'
     *  Constant: '<S65>/S22'
     *  Constant: '<S65>/S23'
     *  Constant: '<S65>/S32'
     *  Constant: '<S65>/S33'
     */
    TemplateLgV2_B.Sr[0] = TemplateLgV2_P.S11_Value;
    TemplateLgV2_B.Sr[1] = TemplateLgV2_B.nuSwitch[2];
    TemplateLgV2_B.Sr[2] = TemplateLgV2_P.R31_Value_b;
    TemplateLgV2_B.Sr[3] = TemplateLgV2_B.S12;
    TemplateLgV2_B.Sr[4] = TemplateLgV2_P.S22_Value;
    TemplateLgV2_B.Sr[5] = TemplateLgV2_P.S32_Value;
    TemplateLgV2_B.Sr[6] = TemplateLgV2_P.S13_Value;
    TemplateLgV2_B.Sr[7] = TemplateLgV2_P.S23_Value;
    TemplateLgV2_B.Sr[8] = TemplateLgV2_P.S33_Value;

    /* Math: '<S66>/Math Function' */
    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.MathFunction_h[3 * i] = TemplateLgV2_B.Sr[i];
      TemplateLgV2_B.MathFunction_h[1 + 3 * i] = TemplateLgV2_B.Sr[i + 3];
      TemplateLgV2_B.MathFunction_h[2 + 3 * i] = TemplateLgV2_B.Sr[i + 6];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S47>/Product' */
      TemplateLgV2_B.Product_af[i] = 0.0;
      TemplateLgV2_B.Product_af[i] = TemplateLgV2_B.MathFunction_h[i] *
        TemplateLgV2_B.Product_a[0] + TemplateLgV2_B.Product_af[i];
      TemplateLgV2_B.Product_af[i] = TemplateLgV2_B.MathFunction_h[i + 3] *
        TemplateLgV2_B.Product_a[1] + TemplateLgV2_B.Product_af[i];
      TemplateLgV2_B.Product_af[i] = TemplateLgV2_B.MathFunction_h[i + 6] *
        TemplateLgV2_B.Product_a[2] + TemplateLgV2_B.Product_af[i];

      /* Sum: '<S47>/Add' */
      TemplateLgV2_B.Add_iq[i] = TemplateLgV2_B.Product_af[i] +
        TemplateLgV2_B.nuSwitch[i];
    }

    for (i = 0; i < 3; i++) {
      /* Product: '<S47>/Product2' */
      TemplateLgV2_B.Product2_n[i] = 0.0;
      TemplateLgV2_B.Product2_n[i] = TemplateLgV2_B.Add3[i] *
        TemplateLgV2_B.Add_iq[0] + TemplateLgV2_B.Product2_n[i];
      TemplateLgV2_B.Product2_n[i] = TemplateLgV2_B.Add3[i + 3] *
        TemplateLgV2_B.Add_iq[1] + TemplateLgV2_B.Product2_n[i];
      TemplateLgV2_B.Product2_n[i] = TemplateLgV2_B.Add3[i + 6] *
        TemplateLgV2_B.Add_iq[2] + TemplateLgV2_B.Product2_n[i];

      /* Sum: '<S47>/Add1' */
      TemplateLgV2_B.Add1_b[i] = TemplateLgV2_B.VectorConcatenate_l[i] +
        TemplateLgV2_B.VectorConcatenate_a[i];
    }

    /* Product: '<S47>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] +
          TemplateLgV2_B.MathFunction_k[3 * tmp_6] *
          TemplateLgV2_B.MathFunction_h[i];
        tmp_1[i + 3 * tmp_6] = TemplateLgV2_B.MathFunction_k[3 * tmp_6 + 1] *
          TemplateLgV2_B.MathFunction_h[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = TemplateLgV2_B.MathFunction_k[3 * tmp_6 + 2] *
          TemplateLgV2_B.MathFunction_h[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.Product3[i] = 0.0;
      TemplateLgV2_B.Product3[i] = tmp_1[i] * TemplateLgV2_B.Add1_b[0] +
        TemplateLgV2_B.Product3[i];
      TemplateLgV2_B.Product3[i] = tmp_1[i + 3] * TemplateLgV2_B.Add1_b[1] +
        TemplateLgV2_B.Product3[i];
      TemplateLgV2_B.Product3[i] = tmp_1[i + 6] * TemplateLgV2_B.Add1_b[2] +
        TemplateLgV2_B.Product3[i];
    }

    /* Trigonometry: '<S110>/Trigonometric Function' */
    TemplateLgV2_B.TrigonometricFunction_a = cos(TemplateLgV2_B.Sum_a);

    /* Trigonometry: '<S110>/Trigonometric Function1' */
    TemplateLgV2_B.TrigonometricFunction1 = sin(TemplateLgV2_B.Sum_a);

    /* Derivative Block: '<S96>/Derivative' */
    {
      real_T t = TemplateLgV2_M->Timing.t[0];
      real_T timeStampA = TemplateLgV2_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = TemplateLgV2_DWork.Derivative_RWORK.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        TemplateLgV2_B.Derivative = 0.0;
      } else {
        real_T deltaT;
        real_T *lastBank = &TemplateLgV2_DWork.Derivative_RWORK.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 2;
          }
        } else if (timeStampA >= t) {
          lastBank += 2;
        }

        deltaT = t - *lastBank++;
        TemplateLgV2_B.Derivative = (TemplateLgV2_P.u_dm_Value - *lastBank++) /
          deltaT;
      }
    }

    /* Product: '<S110>/Product' */
    TemplateLgV2_B.Product_p3[0] = TemplateLgV2_B.TrigonometricFunction_a *
      TemplateLgV2_B.Derivative;
    TemplateLgV2_B.Product_p3[1] = TemplateLgV2_B.TrigonometricFunction1 *
      TemplateLgV2_B.Derivative;

    /* SignalConversion: '<S54>/ConcatBufferAtVector ConcatenateIn1' */
    TemplateLgV2_B.VectorConcatenate_g[0] = TemplateLgV2_B.Product_p3[0];
    TemplateLgV2_B.VectorConcatenate_g[1] = TemplateLgV2_B.Product_p3[1];

    /* Product: '<S54>/Product1' */
    tmp = TemplateLgV2_B.u_c[0] * TemplateLgV2_B.Product_p3[0];
    tmp += TemplateLgV2_B.u_c[1] * TemplateLgV2_B.Product_p3[1];
    TemplateLgV2_B.VectorConcatenate_g[2] = tmp;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Constant: '<S60>/0_2x1' */
      TemplateLgV2_B.VectorConcatenate_c[0] = TemplateLgV2_P._2x1_Value_a[0];
      TemplateLgV2_B.VectorConcatenate_c[1] = TemplateLgV2_P._2x1_Value_a[1];
    }

    /* Math: '<S114>/epsilon_n^2' */
    tmp = TemplateLgV2_B.MultiportSelector;
    TemplateLgV2_B.epsilon_n2_b = tmp * tmp;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S114>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.Delta2_p = tmp * tmp;
    }

    /* Sum: '<S114>/Add' */
    TemplateLgV2_B.Add_e = TemplateLgV2_B.epsilon_n2_b + TemplateLgV2_B.Delta2_p;

    /* Math: '<S114>/sqrt' */
    tmp = TemplateLgV2_B.Add_e;
    if (tmp < 0.0) {
      TemplateLgV2_B.sqrt_o = -sqrt(-tmp);
    } else {
      TemplateLgV2_B.sqrt_o = sqrt(tmp);
    }

    /* Product: '<S114>/Divide' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Divide_i = TemplateLgV2_P.Deltam_Value /
      TemplateLgV2_B.sqrt_o;

    /* Product: '<S164>/Divide' */
    TemplateLgV2_B.Divide_m = TemplateLgV2_B.Derivative / TemplateLgV2_B.Add_d;

    /* Product: '<S114>/Product' */
    TemplateLgV2_B.Product_ll = TemplateLgV2_B.Divide_i *
      TemplateLgV2_B.Divide_m;

    /* Product: '<S60>/Product1' */
    TemplateLgV2_B.VectorConcatenate_c[2] = TemplateLgV2_B.Subtract_k *
      TemplateLgV2_B.Product_ll;

    /* Sum: '<S47>/Add2' */
    TemplateLgV2_B.Add2[0] = TemplateLgV2_B.VectorConcatenate_g[0] +
      TemplateLgV2_B.VectorConcatenate_c[0];
    TemplateLgV2_B.Add2[1] = TemplateLgV2_B.VectorConcatenate_g[1] +
      TemplateLgV2_B.VectorConcatenate_c[1];
    TemplateLgV2_B.Add2[2] = TemplateLgV2_B.VectorConcatenate_g[2] +
      TemplateLgV2_B.VectorConcatenate_c[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S47>/Product4' */
      TemplateLgV2_B.Product4[i] = 0.0;
      TemplateLgV2_B.Product4[i] = TemplateLgV2_B.MathFunction_k[i] *
        TemplateLgV2_B.Add2[0] + TemplateLgV2_B.Product4[i];
      TemplateLgV2_B.Product4[i] = TemplateLgV2_B.MathFunction_k[i + 3] *
        TemplateLgV2_B.Add2[1] + TemplateLgV2_B.Product4[i];
      TemplateLgV2_B.Product4[i] = TemplateLgV2_B.MathFunction_k[i + 6] *
        TemplateLgV2_B.Add2[2] + TemplateLgV2_B.Product4[i];

      /* Sum: '<S47>/Sum' */
      TemplateLgV2_B.Sum_n[i] = (TemplateLgV2_B.Product3[i] -
        TemplateLgV2_B.Product2_n[i]) + TemplateLgV2_B.Product4[i];
    }

    /* Product: '<S39>/Product4' */
    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.Product4_d[i] = 0.0;
      TemplateLgV2_B.Product4_d[i] = TemplateLgV2_B.x3[i] *
        TemplateLgV2_B.Sum_n[0] + TemplateLgV2_B.Product4_d[i];
      TemplateLgV2_B.Product4_d[i] = TemplateLgV2_B.x3[i + 3] *
        TemplateLgV2_B.Sum_n[1] + TemplateLgV2_B.Product4_d[i];
      TemplateLgV2_B.Product4_d[i] = TemplateLgV2_B.x3[i + 6] *
        TemplateLgV2_B.Sum_n[2] + TemplateLgV2_B.Product4_d[i];
    }

    /* Concatenate: '<S106>/Matrix Concatenate' incorporates:
     *  Constant: '<S140>/Constant'
     */
    TemplateLgV2_B.MatrixConcatenate[0] = TemplateLgV2_P.Constant_Value_e1[0];
    TemplateLgV2_B.MatrixConcatenate[1] = TemplateLgV2_P.Constant_Value_e1[1];
    TemplateLgV2_B.MatrixConcatenate[3] = TemplateLgV2_P.Constant_Value_e1[2];
    TemplateLgV2_B.MatrixConcatenate[4] = TemplateLgV2_P.Constant_Value_e1[3];
    TemplateLgV2_B.MatrixConcatenate[2] = TemplateLgV2_B.u_c[0];
    TemplateLgV2_B.MatrixConcatenate[5] = TemplateLgV2_B.u_c[1];

    /* Product: '<S45>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] +
          TemplateLgV2_B.MathFunction_k[3 * tmp_6] * TemplateLgV2_B.Add3[i];
        tmp_1[i + 3 * tmp_6] = TemplateLgV2_B.MathFunction_k[3 * tmp_6 + 1] *
          TemplateLgV2_B.Add3[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = TemplateLgV2_B.MathFunction_k[3 * tmp_6 + 2] *
          TemplateLgV2_B.Add3[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 2; tmp_6++) {
        TemplateLgV2_B.Product3_l[i + 3 * tmp_6] = 0.0;
        TemplateLgV2_B.Product3_l[i + 3 * tmp_6] = TemplateLgV2_B.Product3_l[3 *
          tmp_6 + i] + TemplateLgV2_B.MatrixConcatenate[3 * tmp_6] * tmp_1[i];
        TemplateLgV2_B.Product3_l[i + 3 * tmp_6] =
          TemplateLgV2_B.MatrixConcatenate[3 * tmp_6 + 1] * tmp_1[i + 3] +
          TemplateLgV2_B.Product3_l[3 * tmp_6 + i];
        TemplateLgV2_B.Product3_l[i + 3 * tmp_6] =
          TemplateLgV2_B.MatrixConcatenate[3 * tmp_6 + 2] * tmp_1[i + 6] +
          TemplateLgV2_B.Product3_l[3 * tmp_6 + i];
      }
    }

    /* Trigonometry: '<S108>/Trigonometric Function1' */
    TemplateLgV2_B.TrigonometricFunction1_g = sin(TemplateLgV2_B.Sum_a);

    /* Gain: '<S108>/Gain' */
    TemplateLgV2_B.Gain_h = TemplateLgV2_P.Gain_Gain_cz *
      TemplateLgV2_B.TrigonometricFunction1_g;

    /* Trigonometry: '<S108>/Trigonometric Function' */
    TemplateLgV2_B.TrigonometricFunction_o = cos(TemplateLgV2_B.Sum_a);

    /* Product: '<S108>/Product1' */
    TemplateLgV2_B.Product1_ip[0] = TemplateLgV2_B.Gain_h * TemplateLgV2_B.u_c[0];

    /* Product: '<S108>/Product2' */
    TemplateLgV2_B.Product2_f[0] = TemplateLgV2_B.TrigonometricFunction_o *
      TemplateLgV2_B.u_c[0];

    /* Product: '<S108>/Product1' */
    TemplateLgV2_B.Product1_ip[1] = TemplateLgV2_B.Gain_h * TemplateLgV2_B.u_c[1];

    /* Product: '<S108>/Product2' */
    TemplateLgV2_B.Product2_f[1] = TemplateLgV2_B.TrigonometricFunction_o *
      TemplateLgV2_B.u_c[1];

    /* Concatenate: '<S108>/Matrix Concatenate' */
    TemplateLgV2_B.MatrixConcatenate_g[0] = TemplateLgV2_B.Product1_ip[0];
    TemplateLgV2_B.MatrixConcatenate_g[2] = TemplateLgV2_B.Product1_ip[1];
    TemplateLgV2_B.MatrixConcatenate_g[1] = TemplateLgV2_B.Product2_f[0];
    TemplateLgV2_B.MatrixConcatenate_g[3] = TemplateLgV2_B.Product2_f[1];

    /* Product: '<S108>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateLgV2_B.Product_m[0] = TemplateLgV2_B.MatrixConcatenate_g[0] *
      TemplateLgV2_P.u_dm_Value;
    TemplateLgV2_B.Product_m[1] = TemplateLgV2_B.MatrixConcatenate_g[1] *
      TemplateLgV2_P.u_dm_Value;
    TemplateLgV2_B.Product_m[2] = TemplateLgV2_B.MatrixConcatenate_g[2] *
      TemplateLgV2_P.u_dm_Value;
    TemplateLgV2_B.Product_m[3] = TemplateLgV2_B.MatrixConcatenate_g[3] *
      TemplateLgV2_P.u_dm_Value;

    /* Product: '<S124>/Product2' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Product2_b = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.MultiportSelector;

    /* Math: '<S55>/Math Function' */
    TemplateLgV2_B.MathFunction_pu[0] = TemplateLgV2_B.Product_l[0];

    /* Math: '<S124>/Math Function' */
    TemplateLgV2_B.MathFunction_c[0] = TemplateLgV2_B.MultiportSelector1[0];

    /* Math: '<S55>/Math Function' */
    TemplateLgV2_B.MathFunction_pu[1] = TemplateLgV2_B.Product_l[1];

    /* Math: '<S124>/Math Function' */
    TemplateLgV2_B.MathFunction_c[1] = TemplateLgV2_B.MultiportSelector1[1];

    /* Product: '<S124>/Product3' */
    TemplateLgV2_B.Product3_m[0] = 0.0;
    TemplateLgV2_B.Product3_m[0] = TemplateLgV2_B.MathFunction_c[0] *
      TemplateLgV2_B.MultiportSelector1[0] + TemplateLgV2_B.Product3_m[0];
    TemplateLgV2_B.Product3_m[2] = 0.0;
    TemplateLgV2_B.Product3_m[2] = TemplateLgV2_B.MathFunction_c[0] *
      TemplateLgV2_B.MultiportSelector1[1] + TemplateLgV2_B.Product3_m[2];
    TemplateLgV2_B.Product3_m[1] = 0.0;
    TemplateLgV2_B.Product3_m[1] = TemplateLgV2_B.MathFunction_c[1] *
      TemplateLgV2_B.MultiportSelector1[0] + TemplateLgV2_B.Product3_m[1];
    TemplateLgV2_B.Product3_m[3] = 0.0;
    TemplateLgV2_B.Product3_m[3] = TemplateLgV2_B.MathFunction_c[1] *
      TemplateLgV2_B.MultiportSelector1[1] + TemplateLgV2_B.Product3_m[3];

    /* Product: '<S124>/Product4' */
    TemplateLgV2_B.Product4_c[0] = TemplateLgV2_B.Product2_b *
      TemplateLgV2_B.Product3_m[0];

    /* Gain: '<S124>/2' */
    TemplateLgV2_B.u_f[0] = TemplateLgV2_P._Gain_i * TemplateLgV2_B.Product4_c[0];

    /* Product: '<S124>/Product4' */
    TemplateLgV2_B.Product4_c[1] = TemplateLgV2_B.Product2_b *
      TemplateLgV2_B.Product3_m[1];

    /* Gain: '<S124>/2' */
    TemplateLgV2_B.u_f[1] = TemplateLgV2_P._Gain_i * TemplateLgV2_B.Product4_c[1];

    /* Product: '<S124>/Product4' */
    TemplateLgV2_B.Product4_c[2] = TemplateLgV2_B.Product2_b *
      TemplateLgV2_B.Product3_m[2];

    /* Gain: '<S124>/2' */
    TemplateLgV2_B.u_f[2] = TemplateLgV2_P._Gain_i * TemplateLgV2_B.Product4_c[2];

    /* Product: '<S124>/Product4' */
    TemplateLgV2_B.Product4_c[3] = TemplateLgV2_B.Product2_b *
      TemplateLgV2_B.Product3_m[3];

    /* Gain: '<S124>/2' */
    TemplateLgV2_B.u_f[3] = TemplateLgV2_P._Gain_i * TemplateLgV2_B.Product4_c[3];
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S124>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.Delta2_c = tmp * tmp;
    }

    /* Math: '<S124>/epsilon_n^2' */
    tmp = TemplateLgV2_B.MultiportSelector;
    TemplateLgV2_B.epsilon_n2_o = tmp * tmp;

    /* Sum: '<S124>/Add' */
    TemplateLgV2_B.Add_g = TemplateLgV2_B.Delta2_c + TemplateLgV2_B.epsilon_n2_o;

    /* Math: '<S124>/( )^2' */
    tmp = TemplateLgV2_B.Add_g;
    TemplateLgV2_B.u_l = tmp * tmp;

    /* Product: '<S124>/Divide' */
    TemplateLgV2_B.Divide_f[0] = TemplateLgV2_B.u_f[0] / TemplateLgV2_B.u_l;
    TemplateLgV2_B.Divide_f[1] = TemplateLgV2_B.u_f[1] / TemplateLgV2_B.u_l;
    TemplateLgV2_B.Divide_f[2] = TemplateLgV2_B.u_f[2] / TemplateLgV2_B.u_l;
    TemplateLgV2_B.Divide_f[3] = TemplateLgV2_B.u_f[3] / TemplateLgV2_B.u_l;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Product: '<S124>/Product1' incorporates:
       *  Constant: '<S105>/0_2x2'
       *  Constant: '<S5>/Delta [m]'
       */
      TemplateLgV2_B.Product1_o[0] = TemplateLgV2_P.Deltam_Value *
        TemplateLgV2_P._2x2_Value[0];
      TemplateLgV2_B.Product1_o[1] = TemplateLgV2_P.Deltam_Value *
        TemplateLgV2_P._2x2_Value[1];
      TemplateLgV2_B.Product1_o[2] = TemplateLgV2_P.Deltam_Value *
        TemplateLgV2_P._2x2_Value[2];
      TemplateLgV2_B.Product1_o[3] = TemplateLgV2_P.Deltam_Value *
        TemplateLgV2_P._2x2_Value[3];
    }

    /* Product: '<S124>/Divide1' */
    TemplateLgV2_B.Divide1[0] = TemplateLgV2_B.Product1_o[0] /
      TemplateLgV2_B.Add_g;

    /* Sum: '<S124>/Subtract' */
    TemplateLgV2_B.Subtract_n[0] = TemplateLgV2_B.Divide_f[0] -
      TemplateLgV2_B.Divide1[0];

    /* Product: '<S124>/Divide1' */
    TemplateLgV2_B.Divide1[1] = TemplateLgV2_B.Product1_o[1] /
      TemplateLgV2_B.Add_g;

    /* Sum: '<S124>/Subtract' */
    TemplateLgV2_B.Subtract_n[1] = TemplateLgV2_B.Divide_f[1] -
      TemplateLgV2_B.Divide1[1];

    /* Product: '<S124>/Divide1' */
    TemplateLgV2_B.Divide1[2] = TemplateLgV2_B.Product1_o[2] /
      TemplateLgV2_B.Add_g;

    /* Sum: '<S124>/Subtract' */
    TemplateLgV2_B.Subtract_n[2] = TemplateLgV2_B.Divide_f[2] -
      TemplateLgV2_B.Divide1[2];

    /* Product: '<S124>/Divide1' */
    TemplateLgV2_B.Divide1[3] = TemplateLgV2_B.Product1_o[3] /
      TemplateLgV2_B.Add_g;

    /* Sum: '<S124>/Subtract' */
    TemplateLgV2_B.Subtract_n[3] = TemplateLgV2_B.Divide_f[3] -
      TemplateLgV2_B.Divide1[3];

    /* Math: '<S56>/Math Function' */
    TemplateLgV2_B.MathFunction_n[0] = TemplateLgV2_B.Subtract_n[0];
    TemplateLgV2_B.MathFunction_n[1] = TemplateLgV2_B.Subtract_n[2];
    TemplateLgV2_B.MathFunction_n[2] = TemplateLgV2_B.Subtract_n[1];
    TemplateLgV2_B.MathFunction_n[3] = TemplateLgV2_B.Subtract_n[3];

    /* Product: '<S52>/Product' */
    TemplateLgV2_B.Product_f[0] = 0.0;
    TemplateLgV2_B.Product_f[0] = TemplateLgV2_B.MathFunction_pu[0] *
      TemplateLgV2_B.MathFunction_n[0] + TemplateLgV2_B.Product_f[0];
    TemplateLgV2_B.Product_f[0] = TemplateLgV2_B.MathFunction_pu[1] *
      TemplateLgV2_B.MathFunction_n[1] + TemplateLgV2_B.Product_f[0];

    /* Product: '<S52>/Product1' */
    TemplateLgV2_B.Product1_a4[0] = 0.0;
    TemplateLgV2_B.Product1_a4[0] = TemplateLgV2_B.u_c[0] *
      TemplateLgV2_B.Product_m[0] + TemplateLgV2_B.Product1_a4[0];
    TemplateLgV2_B.Product1_a4[0] = TemplateLgV2_B.u_c[1] *
      TemplateLgV2_B.Product_m[1] + TemplateLgV2_B.Product1_a4[0];

    /* Sum: '<S52>/Add' */
    TemplateLgV2_B.Add_ob[0] = TemplateLgV2_B.Product_f[0] +
      TemplateLgV2_B.Product1_a4[0];

    /* Product: '<S52>/Product' */
    TemplateLgV2_B.Product_f[1] = 0.0;
    TemplateLgV2_B.Product_f[1] = TemplateLgV2_B.MathFunction_pu[0] *
      TemplateLgV2_B.MathFunction_n[2] + TemplateLgV2_B.Product_f[1];
    TemplateLgV2_B.Product_f[1] = TemplateLgV2_B.MathFunction_pu[1] *
      TemplateLgV2_B.MathFunction_n[3] + TemplateLgV2_B.Product_f[1];

    /* Product: '<S52>/Product1' */
    TemplateLgV2_B.Product1_a4[1] = 0.0;
    TemplateLgV2_B.Product1_a4[1] = TemplateLgV2_B.u_c[0] *
      TemplateLgV2_B.Product_m[2] + TemplateLgV2_B.Product1_a4[1];
    TemplateLgV2_B.Product1_a4[1] = TemplateLgV2_B.u_c[1] *
      TemplateLgV2_B.Product_m[3] + TemplateLgV2_B.Product1_a4[1];

    /* Sum: '<S52>/Add' */
    TemplateLgV2_B.Add_ob[1] = TemplateLgV2_B.Product_f[1] +
      TemplateLgV2_B.Product1_a4[1];

    /* Concatenate: '<S52>/Matrix Concatenate' */
    TemplateLgV2_B.MatrixConcatenate_p[0] = TemplateLgV2_B.Product_m[0];
    TemplateLgV2_B.MatrixConcatenate_p[1] = TemplateLgV2_B.Product_m[1];
    TemplateLgV2_B.MatrixConcatenate_p[3] = TemplateLgV2_B.Product_m[2];
    TemplateLgV2_B.MatrixConcatenate_p[4] = TemplateLgV2_B.Product_m[3];
    TemplateLgV2_B.MatrixConcatenate_p[2] = TemplateLgV2_B.Add_ob[0];
    TemplateLgV2_B.MatrixConcatenate_p[5] = TemplateLgV2_B.Add_ob[1];

    /* Product: '<S125>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Product_d[0] = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.MultiportSelector * TemplateLgV2_B.MultiportSelector2 *
      TemplateLgV2_B.MultiportSelector1[0];

    /* Gain: '<S125>/2' */
    TemplateLgV2_B.u_d[0] = TemplateLgV2_P._Gain_o * TemplateLgV2_B.Product_d[0];

    /* Product: '<S125>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Product_d[1] = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.MultiportSelector * TemplateLgV2_B.MultiportSelector2 *
      TemplateLgV2_B.MultiportSelector1[1];

    /* Gain: '<S125>/2' */
    TemplateLgV2_B.u_d[1] = TemplateLgV2_P._Gain_o * TemplateLgV2_B.Product_d[1];
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S125>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.Delta2_g = tmp * tmp;
    }

    /* Math: '<S125>/epsilon_n^2' */
    tmp = TemplateLgV2_B.MultiportSelector;
    TemplateLgV2_B.epsilon_n2_f = tmp * tmp;

    /* Sum: '<S125>/Add' */
    TemplateLgV2_B.Add_g2 = TemplateLgV2_B.Delta2_g +
      TemplateLgV2_B.epsilon_n2_f;

    /* Math: '<S125>/( )^2' */
    tmp = TemplateLgV2_B.Add_g2;
    TemplateLgV2_B.u_o = tmp * tmp;

    /* Product: '<S125>/Divide' */
    TemplateLgV2_B.Divide_mz[0] = TemplateLgV2_B.u_d[0] / TemplateLgV2_B.u_o;
    TemplateLgV2_B.Divide_mz[1] = TemplateLgV2_B.u_d[1] / TemplateLgV2_B.u_o;

    /* Product: '<S137>/Product1' */
    for (i = 0; i < 2; i++) {
      TemplateLgV2_B.Product1_bd[i] = 0.0;
      TemplateLgV2_B.Product1_bd[i] = TemplateLgV2_B.MathFunction_fh[i] *
        TemplateLgV2_B.MathFunction_e[0] + TemplateLgV2_B.Product1_bd[i];
      TemplateLgV2_B.Product1_bd[i] = TemplateLgV2_B.MathFunction_fh[i + 2] *
        TemplateLgV2_B.MathFunction_e[1] + TemplateLgV2_B.Product1_bd[i];
      TemplateLgV2_B.Product1_bd[i + 2] = 0.0;
      TemplateLgV2_B.Product1_bd[i + 2] = TemplateLgV2_B.Product1_bd[i + 2] +
        TemplateLgV2_B.MathFunction_fh[i] * TemplateLgV2_B.MathFunction_e[2];
      TemplateLgV2_B.Product1_bd[i + 2] = TemplateLgV2_B.MathFunction_fh[i + 2] *
        TemplateLgV2_B.MathFunction_e[3] + TemplateLgV2_B.Product1_bd[i + 2];
    }

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector3' */
    {
      const byte_T *u = (byte_T *)TemplateLgV2_B.Product1_bd;/* input port */
      const int32_T *index = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)TemplateLgV2_B.MultiportSelector3;
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
    TemplateLgV2_B.Product1_e[0] = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.MultiportSelector3[0];

    /* Product: '<S125>/Divide1' */
    TemplateLgV2_B.Divide1_p[0] = TemplateLgV2_B.Product1_e[0] /
      TemplateLgV2_B.Add_g2;

    /* Sum: '<S125>/Subtract' */
    TemplateLgV2_B.Subtract_p[0] = TemplateLgV2_B.Divide_mz[0] -
      TemplateLgV2_B.Divide1_p[0];

    /* Product: '<S58>/Product' */
    TemplateLgV2_B.Product_mw[0] = TemplateLgV2_B.Subtract_p[0] *
      TemplateLgV2_B.Subtract_o;

    /* Product: '<S112>/Product1' */
    TemplateLgV2_B.Product1_hh[0] = TemplateLgV2_B.MultiportSelector *
      TemplateLgV2_B.MultiportSelector1[0];

    /* Product: '<S125>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Product1_e[1] = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.MultiportSelector3[1];

    /* Product: '<S125>/Divide1' */
    TemplateLgV2_B.Divide1_p[1] = TemplateLgV2_B.Product1_e[1] /
      TemplateLgV2_B.Add_g2;

    /* Sum: '<S125>/Subtract' */
    TemplateLgV2_B.Subtract_p[1] = TemplateLgV2_B.Divide_mz[1] -
      TemplateLgV2_B.Divide1_p[1];

    /* Product: '<S58>/Product' */
    TemplateLgV2_B.Product_mw[1] = TemplateLgV2_B.Subtract_p[1] *
      TemplateLgV2_B.Subtract_o;

    /* Product: '<S112>/Product1' */
    TemplateLgV2_B.Product1_hh[1] = TemplateLgV2_B.MultiportSelector *
      TemplateLgV2_B.MultiportSelector1[1];

    /* Math: '<S112>/epsilon_n^2' */
    tmp = TemplateLgV2_B.MultiportSelector;
    TemplateLgV2_B.epsilon_n2_h1 = tmp * tmp;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S112>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.Delta2_f = tmp * tmp;
    }

    /* Sum: '<S112>/Add' */
    TemplateLgV2_B.Add_obi = TemplateLgV2_B.epsilon_n2_h1 +
      TemplateLgV2_B.Delta2_f;

    /* Math: '<S112>/^3//2' incorporates:
     *  Constant: '<S112>/3//2'
     */
    if ((TemplateLgV2_B.Add_obi < 0.0) && (TemplateLgV2_P.u_Value_m > floor
         (TemplateLgV2_P.u_Value_m))) {
      TemplateLgV2_B.u2 = -rt_pow_snf(-TemplateLgV2_B.Add_obi,
        TemplateLgV2_P.u_Value_m);
    } else {
      TemplateLgV2_B.u2 = rt_pow_snf(TemplateLgV2_B.Add_obi,
        TemplateLgV2_P.u_Value_m);
    }

    /* Product: '<S112>/Divide' */
    TemplateLgV2_B.Divide_n[0] = TemplateLgV2_B.Product1_hh[0] /
      TemplateLgV2_B.u2;

    /* Product: '<S112>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Product_dg[0] = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.Divide_n[0] * TemplateLgV2_B.Divide_b;

    /* Math: '<S119>/Math Function' */
    TemplateLgV2_B.MathFunction_l[0] = TemplateLgV2_B.Add[0];

    /* Product: '<S116>/Divide' */
    TemplateLgV2_B.Divide_hd[0] = TemplateLgV2_B.MathFunction_l[0] /
      TemplateLgV2_B.Add_d;

    /* Product: '<S116>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    TemplateLgV2_B.Product_fe[0] = TemplateLgV2_P.my_Value *
      TemplateLgV2_B.Divide_hd[0];

    /* Gain: '<S116>/Gain' */
    TemplateLgV2_B.Gain_a[0] = TemplateLgV2_P.Gain_Gain_bm *
      TemplateLgV2_B.Product_fe[0];

    /* Sum: '<S112>/Sum' */
    TemplateLgV2_B.Sum_fb[0] = (0.0 - TemplateLgV2_B.Product_dg[0]) -
      TemplateLgV2_B.Gain_a[0];

    /* Product: '<S58>/Product1' */
    TemplateLgV2_B.Product1_k[0] = TemplateLgV2_B.Subtract_k *
      TemplateLgV2_B.Sum_fb[0];

    /* Sum: '<S58>/Add' */
    TemplateLgV2_B.Add_dn[0] = TemplateLgV2_B.Product_mw[0] +
      TemplateLgV2_B.Product1_k[0];

    /* Product: '<S112>/Divide' */
    TemplateLgV2_B.Divide_n[1] = TemplateLgV2_B.Product1_hh[1] /
      TemplateLgV2_B.u2;

    /* Product: '<S112>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Product_dg[1] = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.Divide_n[1] * TemplateLgV2_B.Divide_b;

    /* Math: '<S119>/Math Function' */
    TemplateLgV2_B.MathFunction_l[1] = TemplateLgV2_B.Add[1];

    /* Product: '<S116>/Divide' */
    TemplateLgV2_B.Divide_hd[1] = TemplateLgV2_B.MathFunction_l[1] /
      TemplateLgV2_B.Add_d;

    /* Product: '<S116>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    TemplateLgV2_B.Product_fe[1] = TemplateLgV2_P.my_Value *
      TemplateLgV2_B.Divide_hd[1];

    /* Gain: '<S116>/Gain' */
    TemplateLgV2_B.Gain_a[1] = TemplateLgV2_P.Gain_Gain_bm *
      TemplateLgV2_B.Product_fe[1];

    /* Sum: '<S112>/Sum' */
    TemplateLgV2_B.Sum_fb[1] = (0.0 - TemplateLgV2_B.Product_dg[1]) -
      TemplateLgV2_B.Gain_a[1];

    /* Product: '<S58>/Product1' */
    TemplateLgV2_B.Product1_k[1] = TemplateLgV2_B.Subtract_k *
      TemplateLgV2_B.Sum_fb[1];

    /* Sum: '<S58>/Add' */
    TemplateLgV2_B.Add_dn[1] = TemplateLgV2_B.Product_mw[1] +
      TemplateLgV2_B.Product1_k[1];

    /* Concatenate: '<S58>/Matrix Concatenate' incorporates:
     *  Constant: '<S58>/0_2x2'
     */
    TemplateLgV2_B.MatrixConcatenate_ps[0] = TemplateLgV2_P._2x2_Value_g[0];
    TemplateLgV2_B.MatrixConcatenate_ps[1] = TemplateLgV2_P._2x2_Value_g[1];
    TemplateLgV2_B.MatrixConcatenate_ps[3] = TemplateLgV2_P._2x2_Value_g[2];
    TemplateLgV2_B.MatrixConcatenate_ps[4] = TemplateLgV2_P._2x2_Value_g[3];
    TemplateLgV2_B.MatrixConcatenate_ps[2] = TemplateLgV2_B.Add_dn[0];
    TemplateLgV2_B.MatrixConcatenate_ps[5] = TemplateLgV2_B.Add_dn[1];

    /* Sum: '<S45>/Add2' */
    for (i = 0; i < 6; i++) {
      TemplateLgV2_B.Add2_c[i] = TemplateLgV2_B.MatrixConcatenate_p[i] +
        TemplateLgV2_B.MatrixConcatenate_ps[i];
    }

    /* Product: '<S45>/Product4' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 2; tmp_6++) {
        TemplateLgV2_B.Product4_p[i + 3 * tmp_6] = 0.0;
        TemplateLgV2_B.Product4_p[i + 3 * tmp_6] = TemplateLgV2_B.Product4_p[3 *
          tmp_6 + i] + TemplateLgV2_B.Add2_c[3 * tmp_6] *
          TemplateLgV2_B.MathFunction_k[i];
        TemplateLgV2_B.Product4_p[i + 3 * tmp_6] = TemplateLgV2_B.Add2_c[3 *
          tmp_6 + 1] * TemplateLgV2_B.MathFunction_k[i + 3] +
          TemplateLgV2_B.Product4_p[3 * tmp_6 + i];
        TemplateLgV2_B.Product4_p[i + 3 * tmp_6] = TemplateLgV2_B.Add2_c[3 *
          tmp_6 + 2] * TemplateLgV2_B.MathFunction_k[i + 6] +
          TemplateLgV2_B.Product4_p[3 * tmp_6 + i];
      }
    }

    /* Sum: '<S45>/Add3' */
    for (i = 0; i < 6; i++) {
      TemplateLgV2_B.Add3_i[i] = TemplateLgV2_B.Product3_l[i] +
        TemplateLgV2_B.Product4_p[i];
    }

    /* Integrator Block: '<S42>/Integrator2'
     */
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateLgV2_PrevZCSigState.Integrator2_Reset_ZCE,
                         TemplateLgV2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateLgV2_P.ctrl2ResetIntegrator_Value != 0.0) {
        TemplateLgV2_X.Integrator2_CSTATE[0] = TemplateLgV2_P.Integrator2_IC;
        TemplateLgV2_X.Integrator2_CSTATE[1] = TemplateLgV2_P.Integrator2_IC;
      }
    }

    TemplateLgV2_B.Integrator2[0] = TemplateLgV2_X.Integrator2_CSTATE[0];
    TemplateLgV2_B.Integrator2[1] = TemplateLgV2_X.Integrator2_CSTATE[1];

    /* Sum: '<S39>/Add2' */
    TemplateLgV2_B.Add2_ct[0] = TemplateLgV2_B.Integrator2[0] +
      TemplateLgV2_B.Product_l[0];
    TemplateLgV2_B.Add2_ct[1] = TemplateLgV2_B.Integrator2[1] +
      TemplateLgV2_B.Product_l[1];

    /* Product: '<S39>/Product5' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 2; tmp_6++) {
        tmp_3[i + 3 * tmp_6] = 0.0;
        tmp_3[i + 3 * tmp_6] = tmp_3[3 * tmp_6 + i] + TemplateLgV2_B.Add3_i[3 *
          tmp_6] * TemplateLgV2_B.x3[i];
        tmp_3[i + 3 * tmp_6] = TemplateLgV2_B.Add3_i[3 * tmp_6 + 1] *
          TemplateLgV2_B.x3[i + 3] + tmp_3[3 * tmp_6 + i];
        tmp_3[i + 3 * tmp_6] = TemplateLgV2_B.Add3_i[3 * tmp_6 + 2] *
          TemplateLgV2_B.x3[i + 6] + tmp_3[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.Product5[i] = 0.0;
      TemplateLgV2_B.Product5[i] = tmp_3[i] * TemplateLgV2_B.Add2_ct[0] +
        TemplateLgV2_B.Product5[i];
      TemplateLgV2_B.Product5[i] = tmp_3[i + 3] * TemplateLgV2_B.Add2_ct[1] +
        TemplateLgV2_B.Product5[i];
    }

    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Constant: '<S106>/0_2x1' */
      TemplateLgV2_B.VectorConcatenate1[0] = TemplateLgV2_P._2x1_Value_hc[0];
      TemplateLgV2_B.VectorConcatenate1[1] = TemplateLgV2_P._2x1_Value_hc[1];
    }

    /* SignalConversion: '<S106>/ConcatBufferAtVector Concatenate1In2' */
    TemplateLgV2_B.VectorConcatenate1[2] = TemplateLgV2_B.Subtract_k;

    /* Product: '<S46>/Product3' */
    for (i = 0; i < 3; i++) {
      for (tmp_6 = 0; tmp_6 < 3; tmp_6++) {
        tmp_1[i + 3 * tmp_6] = 0.0;
        tmp_1[i + 3 * tmp_6] = tmp_1[3 * tmp_6 + i] +
          TemplateLgV2_B.MathFunction_k[3 * tmp_6] * TemplateLgV2_B.Add3[i];
        tmp_1[i + 3 * tmp_6] = TemplateLgV2_B.MathFunction_k[3 * tmp_6 + 1] *
          TemplateLgV2_B.Add3[i + 3] + tmp_1[3 * tmp_6 + i];
        tmp_1[i + 3 * tmp_6] = TemplateLgV2_B.MathFunction_k[3 * tmp_6 + 2] *
          TemplateLgV2_B.Add3[i + 6] + tmp_1[3 * tmp_6 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.Product3_lv[i] = 0.0;
      TemplateLgV2_B.Product3_lv[i] = tmp_1[i] *
        TemplateLgV2_B.VectorConcatenate1[0] + TemplateLgV2_B.Product3_lv[i];
      TemplateLgV2_B.Product3_lv[i] = tmp_1[i + 3] *
        TemplateLgV2_B.VectorConcatenate1[1] + TemplateLgV2_B.Product3_lv[i];
      TemplateLgV2_B.Product3_lv[i] = tmp_1[i + 6] *
        TemplateLgV2_B.VectorConcatenate1[2] + TemplateLgV2_B.Product3_lv[i];
    }

    /* Trigonometry: '<S109>/Trigonometric Function1' */
    TemplateLgV2_B.TrigonometricFunction1_h = sin(TemplateLgV2_B.Sum_a);

    /* Gain: '<S109>/Gain' */
    TemplateLgV2_B.Gain_c = TemplateLgV2_P.Gain_Gain_e *
      TemplateLgV2_B.TrigonometricFunction1_h;

    /* Product: '<S109>/Product1' */
    TemplateLgV2_B.Product1_kn = TemplateLgV2_B.Gain_c *
      TemplateLgV2_B.Subtract_k;

    /* Trigonometry: '<S109>/Trigonometric Function' */
    TemplateLgV2_B.TrigonometricFunction_f = cos(TemplateLgV2_B.Sum_a);

    /* Product: '<S109>/Product2' */
    TemplateLgV2_B.Product2_iw = TemplateLgV2_B.TrigonometricFunction_f *
      TemplateLgV2_B.Subtract_k;

    /* SignalConversion: '<S109>/TmpHiddenBufferAtProductInport1' */
    TemplateLgV2_B.TmpHiddenBufferAtProductInpor_i[0] =
      TemplateLgV2_B.Product1_kn;
    TemplateLgV2_B.TmpHiddenBufferAtProductInpor_i[1] =
      TemplateLgV2_B.Product2_iw;

    /* Product: '<S109>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateLgV2_B.Product_ec[0] =
      TemplateLgV2_B.TmpHiddenBufferAtProductInpor_i[0] *
      TemplateLgV2_P.u_dm_Value;
    TemplateLgV2_B.Product_ec[1] =
      TemplateLgV2_B.TmpHiddenBufferAtProductInpor_i[1] *
      TemplateLgV2_P.u_dm_Value;

    /* SignalConversion: '<S53>/ConcatBufferAtVector ConcatenateIn1' */
    TemplateLgV2_B.VectorConcatenate_av[0] = TemplateLgV2_B.Product_ec[0];
    TemplateLgV2_B.VectorConcatenate_av[1] = TemplateLgV2_B.Product_ec[1];

    /* Product: '<S53>/Product' */
    tmp = TemplateLgV2_B.Subtract_p[0] * TemplateLgV2_B.Product_l[0];
    tmp += TemplateLgV2_B.Subtract_p[1] * TemplateLgV2_B.Product_l[1];
    TemplateLgV2_B.Product_np = tmp;

    /* Product: '<S53>/Product1' */
    tmp = TemplateLgV2_B.u_c[0] * TemplateLgV2_B.Product_ec[0];
    tmp += TemplateLgV2_B.u_c[1] * TemplateLgV2_B.Product_ec[1];
    TemplateLgV2_B.Product1_lh = tmp;

    /* Sum: '<S53>/Add' */
    TemplateLgV2_B.VectorConcatenate_av[2] = TemplateLgV2_B.Product_np +
      TemplateLgV2_B.Product1_lh;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Constant: '<S59>/0_2x1' */
      TemplateLgV2_B.VectorConcatenate_h[0] = TemplateLgV2_P._2x1_Value_n[0];
      TemplateLgV2_B.VectorConcatenate_h[1] = TemplateLgV2_P._2x1_Value_n[1];

      /* Product: '<S154>/Product' incorporates:
       *  Constant: '<S143>/0_2x1'
       */
      TemplateLgV2_B.Product_fc[0] = TemplateLgV2_P._2x1_Value_h[0] *
        TemplateLgV2_B.RoundingFunction;
      TemplateLgV2_B.Product_fc[1] = TemplateLgV2_P._2x1_Value_h[1] *
        TemplateLgV2_B.RoundingFunction;
    }

    /* Product: '<S147>/Product2' incorporates:
     *  Constant: '<S10>/k [-]'
     */
    TemplateLgV2_B.Product2_e = TemplateLgV2_B.Integrator1 *
      TemplateLgV2_P.k_Value;

    /* Trigonometry: '<S147>/sin(s)3' */
    TemplateLgV2_B.sins3 = sin(TemplateLgV2_B.Product2_e);
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S147>/Math Function' incorporates:
       *  Constant: '<S10>/k [-]'
       *  Constant: '<S147>/Constant'
       */
      if ((TemplateLgV2_P.k_Value < 0.0) && (TemplateLgV2_P.Constant_Value_on >
           floor(TemplateLgV2_P.Constant_Value_on))) {
        TemplateLgV2_B.MathFunction_b = -rt_pow_snf(-TemplateLgV2_P.k_Value,
          TemplateLgV2_P.Constant_Value_on);
      } else {
        TemplateLgV2_B.MathFunction_b = rt_pow_snf(TemplateLgV2_P.k_Value,
          TemplateLgV2_P.Constant_Value_on);
      }
    }

    /* Product: '<S147>/Product' incorporates:
     *  Constant: '<S10>/r_x [m]'
     */
    TemplateLgV2_B.Product_lg = TemplateLgV2_P.r_xm_Value * TemplateLgV2_B.sins3
      * TemplateLgV2_B.MathFunction_b;

    /* Trigonometry: '<S147>/cos(s)3' */
    TemplateLgV2_B.coss3 = cos(TemplateLgV2_B.Product2_e);

    /* Product: '<S147>/Product1' incorporates:
     *  Constant: '<S10>/r_y [m]'
     */
    TemplateLgV2_B.Product1_kz = TemplateLgV2_P.r_ym_Value *
      TemplateLgV2_B.coss3 * TemplateLgV2_B.MathFunction_b;

    /* Gain: '<S147>/Gain' */
    TemplateLgV2_B.Gain_dq = TemplateLgV2_P.Gain_Gain_pm *
      TemplateLgV2_B.Product1_kz;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Sum: '<S154>/Subract' incorporates:
       *  Constant: '<S154>/Constant'
       */
      TemplateLgV2_B.Subract_m = TemplateLgV2_P.Constant_Value_ap -
        TemplateLgV2_B.RoundingFunction;
    }

    /* Product: '<S154>/Product1' */
    TemplateLgV2_B.Product1_jv[0] = TemplateLgV2_B.Product_lg *
      TemplateLgV2_B.Subract_m;
    TemplateLgV2_B.Product1_jv[1] = TemplateLgV2_B.Gain_dq *
      TemplateLgV2_B.Subract_m;

    /* Sum: '<S154>/Add' */
    TemplateLgV2_B.Add_ms[0] = TemplateLgV2_B.Product_fc[0] +
      TemplateLgV2_B.Product1_jv[0];
    TemplateLgV2_B.Add_ms[1] = TemplateLgV2_B.Product_fc[1] +
      TemplateLgV2_B.Product1_jv[1];

    /* Product: '<S99>/x_d^s * y_d^s^3 ' */
    TemplateLgV2_B.x_dsy_ds3 = TemplateLgV2_B.Add[0] * TemplateLgV2_B.Add_ms[1];

    /* Product: '<S99>/x_d^s^3 * y_d^s' */
    TemplateLgV2_B.x_ds3y_ds = TemplateLgV2_B.Add_ms[0] * TemplateLgV2_B.Add[1];

    /* Sum: '<S99>/( x_d^s * y_d^s^3  ) - ( x_d^s^3 * y_d^s )' */
    TemplateLgV2_B.x_dsy_ds3x_ds3y_ds = TemplateLgV2_B.x_dsy_ds3 -
      TemplateLgV2_B.x_ds3y_ds;

    /* Product: '<S99>/Product1' */
    TemplateLgV2_B.Product1_kr = TemplateLgV2_B.x_dsy_ds3x_ds3y_ds *
      TemplateLgV2_B.x_ds2y_ds2;

    /* Product: '<S99>/x_d^s * x_d^s^2' */
    TemplateLgV2_B.x_dsx_ds2 = TemplateLgV2_B.Add[0] * TemplateLgV2_B.Add_o[0];

    /* Product: '<S99>/y_d^s * y_d^s^2' */
    TemplateLgV2_B.y_dsy_ds2 = TemplateLgV2_B.Add[1] * TemplateLgV2_B.Add_o[1];

    /* Sum: '<S99>/( x_d^s * x_d^s^2 ) + ( x_d^s^3 * y_d^s )' */
    TemplateLgV2_B.x_dsx_ds2x_ds3y_ds = TemplateLgV2_B.x_dsx_ds2 +
      TemplateLgV2_B.y_dsy_ds2;

    /* Gain: '<S99>/+ 2' */
    TemplateLgV2_B.u_e = TemplateLgV2_P.u_Gain_c *
      TemplateLgV2_B.x_dsx_ds2x_ds3y_ds;

    /* Product: '<S99>/Product2' */
    TemplateLgV2_B.Product2_az = TemplateLgV2_B.x_dsy_ds2x_ds2y_ds *
      TemplateLgV2_B.u_e;

    /* Sum: '<S99>/Subtract' */
    TemplateLgV2_B.Subtract_oo = TemplateLgV2_B.Product1_kr -
      TemplateLgV2_B.Product2_az;

    /* Math: '<S99>/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2' */
    tmp = TemplateLgV2_B.x_ds2y_ds2;
    TemplateLgV2_B.x_ds2y_ds22 = tmp * tmp;

    /* Product: '<S99>/Divide' */
    TemplateLgV2_B.Divide_o = TemplateLgV2_B.Subtract_oo /
      TemplateLgV2_B.x_ds2y_ds22;

    /* Math: '<S127>/(epsilon_n^s)^2' */
    tmp = TemplateLgV2_B.MultiportSelector2;
    TemplateLgV2_B.epsilon_ns2 = tmp * tmp;

    /* Product: '<S127>/Product' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Product_iu = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.MultiportSelector * TemplateLgV2_B.epsilon_ns2;

    /* Gain: '<S127>/2' */
    TemplateLgV2_B.u_lx = TemplateLgV2_P._Gain_j * TemplateLgV2_B.Product_iu;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S127>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.Delta2_ct = tmp * tmp;
    }

    /* Math: '<S127>/epsilon_n^2' */
    tmp = TemplateLgV2_B.MultiportSelector;
    TemplateLgV2_B.epsilon_n2_o4 = tmp * tmp;

    /* Sum: '<S127>/Add' */
    TemplateLgV2_B.Add_lv = TemplateLgV2_B.Delta2_ct +
      TemplateLgV2_B.epsilon_n2_o4;

    /* Math: '<S127>/( )^2' */
    tmp = TemplateLgV2_B.Add_lv;
    TemplateLgV2_B.u_b = tmp * tmp;

    /* Product: '<S127>/Divide' */
    TemplateLgV2_B.Divide_j = TemplateLgV2_B.u_lx / TemplateLgV2_B.u_b;

    /* Outputs for atomic SubSystem: '<S105>/S_2(psi_d^s^2)' */

    /* Gain: '<S134>/S12' */
    TemplateLgV2_B.S12_e = TemplateLgV2_P.S12_Gain_p * TemplateLgV2_B.Divide_o;

    /* Reshape: '<S134>/S_2(psi_d^s^2)' incorporates:
     *  Constant: '<S134>/0'
     */
    TemplateLgV2_B.S_2psi_ds2[0] = TemplateLgV2_P._Value_c;
    TemplateLgV2_B.S_2psi_ds2[1] = TemplateLgV2_B.Divide_o;
    TemplateLgV2_B.S_2psi_ds2[2] = TemplateLgV2_B.S12_e;
    TemplateLgV2_B.S_2psi_ds2[3] = TemplateLgV2_P._Value_c;

    /* end of Outputs for SubSystem: '<S105>/S_2(psi_d^s^2)' */

    /* Math: '<S135>/Math Function' */
    TemplateLgV2_B.MathFunction_c2[0] = TemplateLgV2_B.S_2psi_ds2[0];
    TemplateLgV2_B.MathFunction_c2[1] = TemplateLgV2_B.S_2psi_ds2[2];
    TemplateLgV2_B.MathFunction_c2[2] = TemplateLgV2_B.S_2psi_ds2[1];
    TemplateLgV2_B.MathFunction_c2[3] = TemplateLgV2_B.S_2psi_ds2[3];

    /* Product: '<S139>/Product' */
    for (i = 0; i < 2; i++) {
      TemplateLgV2_B.Product_aa[i] = 0.0;
      TemplateLgV2_B.Product_aa[i] = TemplateLgV2_B.MathFunction_fh[i] *
        TemplateLgV2_B.MathFunction_fh[0] + TemplateLgV2_B.Product_aa[i];
      TemplateLgV2_B.Product_aa[i] = TemplateLgV2_B.MathFunction_fh[i + 2] *
        TemplateLgV2_B.MathFunction_fh[1] + TemplateLgV2_B.Product_aa[i];
      TemplateLgV2_B.Product_aa[i + 2] = 0.0;
      TemplateLgV2_B.Product_aa[i + 2] = TemplateLgV2_B.Product_aa[i + 2] +
        TemplateLgV2_B.MathFunction_fh[i] * TemplateLgV2_B.MathFunction_fh[2];
      TemplateLgV2_B.Product_aa[i + 2] = TemplateLgV2_B.MathFunction_fh[i + 2] *
        TemplateLgV2_B.MathFunction_fh[3] + TemplateLgV2_B.Product_aa[i + 2];
    }

    /* Sum: '<S139>/Add' */
    TemplateLgV2_B.Add_a[0] = TemplateLgV2_B.MathFunction_c2[0] +
      TemplateLgV2_B.Product_aa[0];
    TemplateLgV2_B.Add_a[1] = TemplateLgV2_B.MathFunction_c2[1] +
      TemplateLgV2_B.Product_aa[1];
    TemplateLgV2_B.Add_a[2] = TemplateLgV2_B.MathFunction_c2[2] +
      TemplateLgV2_B.Product_aa[2];
    TemplateLgV2_B.Add_a[3] = TemplateLgV2_B.MathFunction_c2[3] +
      TemplateLgV2_B.Product_aa[3];

    /* Product: '<S139>/Product1' */
    for (i = 0; i < 2; i++) {
      tmp_2[i] = 0.0;
      tmp_2[i] += TemplateLgV2_B.Add_a[i] * TemplateLgV2_B.MathFunction_e[0];
      tmp_2[i] += TemplateLgV2_B.Add_a[i + 2] * TemplateLgV2_B.MathFunction_e[1];
      tmp_2[i + 2] = 0.0;
      tmp_2[i + 2] += TemplateLgV2_B.Add_a[i] * TemplateLgV2_B.MathFunction_e[2];
      tmp_2[i + 2] += TemplateLgV2_B.Add_a[i + 2] *
        TemplateLgV2_B.MathFunction_e[3];
    }

    TemplateLgV2_B.Product1_gi[0] = 0.0;
    TemplateLgV2_B.Product1_gi[0] = tmp_2[0] * TemplateLgV2_B.Subtract[0] +
      TemplateLgV2_B.Product1_gi[0];
    TemplateLgV2_B.Product1_gi[0] = tmp_2[2] * TemplateLgV2_B.Subtract[1] +
      TemplateLgV2_B.Product1_gi[0];
    TemplateLgV2_B.Product1_gi[1] = 0.0;
    TemplateLgV2_B.Product1_gi[1] = tmp_2[1] * TemplateLgV2_B.Subtract[0] +
      TemplateLgV2_B.Product1_gi[1];
    TemplateLgV2_B.Product1_gi[1] = tmp_2[3] * TemplateLgV2_B.Subtract[1] +
      TemplateLgV2_B.Product1_gi[1];

    /* Product: '<S139>/Product2' */
    for (i = 0; i < 2; i++) {
      tmp_2[i] = 0.0;
      tmp_2[i] += TemplateLgV2_B.MathFunction_fh[i] *
        TemplateLgV2_B.MathFunction_e[0];
      tmp_2[i] += TemplateLgV2_B.MathFunction_fh[i + 2] *
        TemplateLgV2_B.MathFunction_e[1];
      tmp_2[i + 2] = 0.0;
      tmp_2[i + 2] += TemplateLgV2_B.MathFunction_fh[i] *
        TemplateLgV2_B.MathFunction_e[2];
      tmp_2[i + 2] += TemplateLgV2_B.MathFunction_fh[i + 2] *
        TemplateLgV2_B.MathFunction_e[3];
    }

    TemplateLgV2_B.Product2_j[0] = 0.0;
    TemplateLgV2_B.Product2_j[0] = tmp_2[0] * TemplateLgV2_B.Add[0] +
      TemplateLgV2_B.Product2_j[0];
    TemplateLgV2_B.Product2_j[0] = tmp_2[2] * TemplateLgV2_B.Add[1] +
      TemplateLgV2_B.Product2_j[0];

    /* Gain: '<S139>/2' */
    TemplateLgV2_B.u_m[0] = TemplateLgV2_P._Gain_d * TemplateLgV2_B.Product2_j[0];

    /* Product: '<S139>/Product3' */
    TemplateLgV2_B.Product3_mb[0] = 0.0;
    TemplateLgV2_B.Product3_mb[0] = TemplateLgV2_B.MathFunction_e[0] *
      TemplateLgV2_B.Add_o[0] + TemplateLgV2_B.Product3_mb[0];
    TemplateLgV2_B.Product3_mb[0] = TemplateLgV2_B.MathFunction_e[2] *
      TemplateLgV2_B.Add_o[1] + TemplateLgV2_B.Product3_mb[0];

    /* Sum: '<S139>/Sum' */
    TemplateLgV2_B.Sum_b0[0] = (TemplateLgV2_B.Product1_gi[0] -
      TemplateLgV2_B.u_m[0]) - TemplateLgV2_B.Product3_mb[0];

    /* Gain: '<S139>/Gain' */
    TemplateLgV2_B.Gain_fw[0] = TemplateLgV2_P.Gain_Gain_g *
      TemplateLgV2_B.Sum_b0[0];
    TemplateLgV2_B.Product2_j[1] = 0.0;
    TemplateLgV2_B.Product2_j[1] = tmp_2[1] * TemplateLgV2_B.Add[0] +
      TemplateLgV2_B.Product2_j[1];
    TemplateLgV2_B.Product2_j[1] = tmp_2[3] * TemplateLgV2_B.Add[1] +
      TemplateLgV2_B.Product2_j[1];

    /* Gain: '<S139>/2' */
    TemplateLgV2_B.u_m[1] = TemplateLgV2_P._Gain_d * TemplateLgV2_B.Product2_j[1];

    /* Product: '<S139>/Product3' */
    TemplateLgV2_B.Product3_mb[1] = 0.0;
    TemplateLgV2_B.Product3_mb[1] = TemplateLgV2_B.MathFunction_e[1] *
      TemplateLgV2_B.Add_o[0] + TemplateLgV2_B.Product3_mb[1];
    TemplateLgV2_B.Product3_mb[1] = TemplateLgV2_B.MathFunction_e[3] *
      TemplateLgV2_B.Add_o[1] + TemplateLgV2_B.Product3_mb[1];

    /* Sum: '<S139>/Sum' */
    TemplateLgV2_B.Sum_b0[1] = (TemplateLgV2_B.Product1_gi[1] -
      TemplateLgV2_B.u_m[1]) - TemplateLgV2_B.Product3_mb[1];

    /* Gain: '<S139>/Gain' */
    TemplateLgV2_B.Gain_fw[1] = TemplateLgV2_P.Gain_Gain_g *
      TemplateLgV2_B.Sum_b0[1];

    /* Signal Processing Blockset Multi-port Selector (sdspmultiportsel) - '<S105>/Multiport Selector4' */
    {
      const byte_T *u = (byte_T *)TemplateLgV2_B.Gain_fw;/* input port */
      const int32_T *index = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int32_T *length = (const int32_T *)&TemplateLgV2_ConstP.pooled1;
      const int_T numRowsThisOutput = *length++;
      const int_T bytesPerOutCol = numRowsThisOutput * sizeof(real_T);
      byte_T *y = (byte_T *)&TemplateLgV2_B.MultiportSelector4;
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
    TemplateLgV2_B.Product1_ci = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.MultiportSelector4;

    /* Product: '<S127>/Divide1' */
    TemplateLgV2_B.Divide1_o = TemplateLgV2_B.Product1_ci /
      TemplateLgV2_B.Add_lv;

    /* Sum: '<S127>/Sum' */
    TemplateLgV2_B.Sum_d = (TemplateLgV2_B.Divide_o + TemplateLgV2_B.Divide_j) -
      TemplateLgV2_B.Divide1_o;

    /* Product: '<S59>/Product' */
    TemplateLgV2_B.Product_cw = TemplateLgV2_B.Sum_d * TemplateLgV2_B.Subtract_o;

    /* Math: '<S165>/Math Function' */
    TemplateLgV2_B.MathFunction_bf[0] = TemplateLgV2_B.Add[0];
    TemplateLgV2_B.MathFunction_bf[1] = TemplateLgV2_B.Add[1];

    /* Product: '<S163>/Product1' */
    tmp = TemplateLgV2_B.MathFunction_bf[0] * TemplateLgV2_B.Add_o[0];
    tmp += TemplateLgV2_B.MathFunction_bf[1] * TemplateLgV2_B.Add_o[1];
    TemplateLgV2_B.Product1_iw = tmp;

    /* Math: '<S163>/|p_d^s|^3' incorporates:
     *  Constant: '<S163>/Constant'
     */
    if ((TemplateLgV2_B.Add_d < 0.0) && (TemplateLgV2_P.Constant_Value_op >
         floor(TemplateLgV2_P.Constant_Value_op))) {
      TemplateLgV2_B.p_ds3 = -rt_pow_snf(-TemplateLgV2_B.Add_d,
        TemplateLgV2_P.Constant_Value_op);
    } else {
      TemplateLgV2_B.p_ds3 = rt_pow_snf(TemplateLgV2_B.Add_d,
        TemplateLgV2_P.Constant_Value_op);
    }

    /* Product: '<S163>/Divide' */
    TemplateLgV2_B.Divide_eo = TemplateLgV2_B.Product1_iw / TemplateLgV2_B.p_ds3;

    /* Product: '<S163>/Product' incorporates:
     *  Constant: '<S5>/u_d [m]'
     */
    TemplateLgV2_B.Product_pe = TemplateLgV2_B.Divide_eo *
      TemplateLgV2_P.u_dm_Value;

    /* Gain: '<S163>/Gain' */
    TemplateLgV2_B.Gain_i = TemplateLgV2_P.Gain_Gain_dc *
      TemplateLgV2_B.Product_pe;

    /* Math: '<S113>/epsilon_n^2' */
    tmp = TemplateLgV2_B.MultiportSelector;
    TemplateLgV2_B.epsilon_n2_l = tmp * tmp;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Math: '<S113>/Delta^2' incorporates:
       *  Constant: '<S5>/Delta [m]'
       */
      tmp = TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.Delta2_im = tmp * tmp;
    }

    /* Sum: '<S113>/Add' */
    TemplateLgV2_B.Add_i4 = TemplateLgV2_B.epsilon_n2_l +
      TemplateLgV2_B.Delta2_im;

    /* Math: '<S113>/Math Function' */
    tmp = TemplateLgV2_B.Add_i4;
    if (tmp < 0.0) {
      TemplateLgV2_B.MathFunction_io = -sqrt(-tmp);
    } else {
      TemplateLgV2_B.MathFunction_io = sqrt(tmp);
    }

    /* Product: '<S113>/Divide' */
    TemplateLgV2_B.Divide_g = TemplateLgV2_B.Gain_i /
      TemplateLgV2_B.MathFunction_io;

    /* Product: '<S113>/Product1' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Product1_m = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.Divide_g;

    /* Product: '<S113>/Product2' */
    TemplateLgV2_B.Product2_e3 = TemplateLgV2_B.MultiportSelector *
      TemplateLgV2_B.MultiportSelector2;

    /* Math: '<S113>/^3//2' incorporates:
     *  Constant: '<S113>/3//2'
     */
    if ((TemplateLgV2_B.Add_i4 < 0.0) && (TemplateLgV2_P.u_Value_pn > floor
         (TemplateLgV2_P.u_Value_pn))) {
      TemplateLgV2_B.u2_m = -rt_pow_snf(-TemplateLgV2_B.Add_i4,
        TemplateLgV2_P.u_Value_pn);
    } else {
      TemplateLgV2_B.u2_m = rt_pow_snf(TemplateLgV2_B.Add_i4,
        TemplateLgV2_P.u_Value_pn);
    }

    /* Product: '<S113>/Divide1' */
    TemplateLgV2_B.Divide1_g = TemplateLgV2_B.Product2_e3 / TemplateLgV2_B.u2_m;

    /* Product: '<S113>/Product3' incorporates:
     *  Constant: '<S5>/Delta [m]'
     */
    TemplateLgV2_B.Product3_a = TemplateLgV2_P.Deltam_Value *
      TemplateLgV2_B.Divide1_g * TemplateLgV2_B.Divide_b;

    /* Product: '<S117>/Product1' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    TemplateLgV2_B.Product1_ii = TemplateLgV2_P.my_Value * TemplateLgV2_B.Add_d;

    /* Math: '<S121>/Math Function' */
    TemplateLgV2_B.MathFunction_no[0] = TemplateLgV2_B.Add_o[0];

    /* Product: '<S117>/Divide2' */
    TemplateLgV2_B.Divide2[0] = TemplateLgV2_B.MathFunction_no[0] /
      TemplateLgV2_B.Add_d;

    /* Math: '<S120>/Math Function' */
    TemplateLgV2_B.MathFunction_jk[0] = TemplateLgV2_B.Add[0];

    /* Math: '<S121>/Math Function' */
    TemplateLgV2_B.MathFunction_no[1] = TemplateLgV2_B.Add_o[1];

    /* Product: '<S117>/Divide2' */
    TemplateLgV2_B.Divide2[1] = TemplateLgV2_B.MathFunction_no[1] /
      TemplateLgV2_B.Add_d;

    /* Math: '<S120>/Math Function' */
    TemplateLgV2_B.MathFunction_jk[1] = TemplateLgV2_B.Add[1];

    /* Product: '<S117>/Product2' */
    tmp = TemplateLgV2_B.MathFunction_no[0] * TemplateLgV2_B.Add[0];
    tmp += TemplateLgV2_B.MathFunction_no[1] * TemplateLgV2_B.Add[1];
    TemplateLgV2_B.Product2_nl[0] = tmp * TemplateLgV2_B.MathFunction_jk[0];
    TemplateLgV2_B.Product2_nl[1] = tmp * TemplateLgV2_B.MathFunction_jk[1];

    /* Math: '<S117>/Math Function' incorporates:
     *  Constant: '<S117>/Constant'
     */
    if ((TemplateLgV2_B.Add_d < 0.0) && (TemplateLgV2_P.Constant_Value_f > floor
         (TemplateLgV2_P.Constant_Value_f))) {
      TemplateLgV2_B.MathFunction_po = -rt_pow_snf(-TemplateLgV2_B.Add_d,
        TemplateLgV2_P.Constant_Value_f);
    } else {
      TemplateLgV2_B.MathFunction_po = rt_pow_snf(TemplateLgV2_B.Add_d,
        TemplateLgV2_P.Constant_Value_f);
    }

    /* Product: '<S117>/Divide1' */
    TemplateLgV2_B.Divide1_pb[0] = TemplateLgV2_B.Product2_nl[0] /
      TemplateLgV2_B.MathFunction_po;

    /* Sum: '<S117>/Subtract1' */
    TemplateLgV2_B.Subtract1_f[0] = TemplateLgV2_B.Divide2[0] -
      TemplateLgV2_B.Divide1_pb[0];

    /* Product: '<S117>/Divide1' */
    TemplateLgV2_B.Divide1_pb[1] = TemplateLgV2_B.Product2_nl[1] /
      TemplateLgV2_B.MathFunction_po;

    /* Sum: '<S117>/Subtract1' */
    TemplateLgV2_B.Subtract1_f[1] = TemplateLgV2_B.Divide2[1] -
      TemplateLgV2_B.Divide1_pb[1];

    /* Product: '<S117>/Product' incorporates:
     *  Constant: '<S5>/my [-]'
     */
    tmp = TemplateLgV2_P.my_Value * TemplateLgV2_B.Subtract1_f[0] *
      TemplateLgV2_B.Subtract[0];
    tmp += TemplateLgV2_P.my_Value * TemplateLgV2_B.Subtract1_f[1] *
      TemplateLgV2_B.Subtract[1];
    TemplateLgV2_B.Product_dl = tmp;

    /* Sum: '<S117>/Subtract' */
    TemplateLgV2_B.Subtract_g = TemplateLgV2_B.Product1_ii -
      TemplateLgV2_B.Product_dl;

    /* Sum: '<S113>/Sum' */
    TemplateLgV2_B.Sum_h2 = (TemplateLgV2_B.Product1_m -
      TemplateLgV2_B.Product3_a) - TemplateLgV2_B.Subtract_g;

    /* Product: '<S59>/Product1' */
    TemplateLgV2_B.Product1_ok = TemplateLgV2_B.Subtract_k *
      TemplateLgV2_B.Sum_h2;

    /* Sum: '<S59>/Add' */
    TemplateLgV2_B.VectorConcatenate_h[2] = TemplateLgV2_B.Product_cw +
      TemplateLgV2_B.Product1_ok;

    /* Sum: '<S46>/Add2' */
    TemplateLgV2_B.Add2_l[0] = TemplateLgV2_B.VectorConcatenate_av[0] +
      TemplateLgV2_B.VectorConcatenate_h[0];
    TemplateLgV2_B.Add2_l[1] = TemplateLgV2_B.VectorConcatenate_av[1] +
      TemplateLgV2_B.VectorConcatenate_h[1];
    TemplateLgV2_B.Add2_l[2] = TemplateLgV2_B.VectorConcatenate_av[2] +
      TemplateLgV2_B.VectorConcatenate_h[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S46>/Product4' */
      TemplateLgV2_B.Product4_h[i] = 0.0;
      TemplateLgV2_B.Product4_h[i] = TemplateLgV2_B.MathFunction_k[i] *
        TemplateLgV2_B.Add2_l[0] + TemplateLgV2_B.Product4_h[i];
      TemplateLgV2_B.Product4_h[i] = TemplateLgV2_B.MathFunction_k[i + 3] *
        TemplateLgV2_B.Add2_l[1] + TemplateLgV2_B.Product4_h[i];
      TemplateLgV2_B.Product4_h[i] = TemplateLgV2_B.MathFunction_k[i + 6] *
        TemplateLgV2_B.Add2_l[2] + TemplateLgV2_B.Product4_h[i];

      /* Sum: '<S46>/Add3' */
      TemplateLgV2_B.Add3_k[i] = TemplateLgV2_B.Product3_lv[i] +
        TemplateLgV2_B.Product4_h[i];
    }

    for (i = 0; i < 3; i++) {
      tmp_4[i] = 0.0;
      tmp = tmp_4[i];
      tmp += TemplateLgV2_B.x3[i] * TemplateLgV2_B.Add3_k[0];
      tmp_4[i] = tmp;
      tmp = tmp_4[i];
      tmp += TemplateLgV2_B.x3[i + 3] * TemplateLgV2_B.Add3_k[1];
      tmp_4[i] = tmp;
      tmp = tmp_4[i];
      tmp += TemplateLgV2_B.x3[i + 6] * TemplateLgV2_B.Add3_k[2];
      tmp_4[i] = tmp;
      TemplateLgV2_B.Product6[i] = tmp_4[i] * TemplateLgV2_B.Subtract_o;

      /* Sum: '<S39>/Sum' */
      TemplateLgV2_B.Sum_eq[i] = ((((TemplateLgV2_B.Gain_d[i] +
        TemplateLgV2_B.Gain1_k[i]) + TemplateLgV2_B.Product2_d[i]) +
        TemplateLgV2_B.Product4_d[i]) + TemplateLgV2_B.Product5[i]) +
        TemplateLgV2_B.Product6[i];
    }

    /* MultiPortSwitch: '<S29>/tau Switch' incorporates:
     *  Constant: '<S1>/Control Mode Selector'
     */
    switch ((int32_T)TemplateLgV2_P.ControlModeSelector_Value) {
     case 0:
      TemplateLgV2_B.tauSwitch[0] = TemplateLgV2_B.Product[0];
      TemplateLgV2_B.tauSwitch[1] = TemplateLgV2_B.Product[1];
      TemplateLgV2_B.tauSwitch[2] = TemplateLgV2_B.Product[2];
      break;

     case 1:
      TemplateLgV2_B.tauSwitch[0] = TemplateLgV2_B.Sum1_g[0];
      TemplateLgV2_B.tauSwitch[1] = TemplateLgV2_B.Sum1_g[1];
      TemplateLgV2_B.tauSwitch[2] = TemplateLgV2_B.Sum1_g[2];
      break;

     default:
      TemplateLgV2_B.tauSwitch[0] = TemplateLgV2_B.Sum_eq[0];
      TemplateLgV2_B.tauSwitch[1] = TemplateLgV2_B.Sum_eq[1];
      TemplateLgV2_B.tauSwitch[2] = TemplateLgV2_B.Sum_eq[2];
      break;
    }

    /* Sum: '<S42>/Add' */
    TemplateLgV2_B.Add_h[0] = TemplateLgV2_B.Integrator2[0] +
      TemplateLgV2_B.Product_l[0];
    TemplateLgV2_B.Add_h[1] = TemplateLgV2_B.Integrator2[1] +
      TemplateLgV2_B.Product_l[1];

    /* Math: '<S63>/Math Function' */
    TemplateLgV2_B.MathFunction_kp[0] = TemplateLgV2_B.Product_a[0];
    TemplateLgV2_B.MathFunction_kp[1] = TemplateLgV2_B.Product_a[1];
    TemplateLgV2_B.MathFunction_kp[2] = TemplateLgV2_B.Product_a[2];

    /* Product: '<S43>/Product' */
    for (i = 0; i < 3; i++) {
      tmp_4[i] = 0.0;
      tmp = tmp_4[i];
      tmp += TemplateLgV2_B.MathFunction_k[3 * i] *
        TemplateLgV2_B.MathFunction_kp[0];
      tmp_4[i] = tmp;
      tmp = tmp_4[i];
      tmp += TemplateLgV2_B.MathFunction_k[3 * i + 1] *
        TemplateLgV2_B.MathFunction_kp[1];
      tmp_4[i] = tmp;
      tmp = tmp_4[i];
      tmp += TemplateLgV2_B.MathFunction_k[3 * i + 2] *
        TemplateLgV2_B.MathFunction_kp[2];
      tmp_4[i] = tmp;
    }

    for (i = 0; i < 2; i++) {
      TemplateLgV2_B.Product_feo[i] = 0.0;
      TemplateLgV2_B.Product_feo[i] = TemplateLgV2_B.MatrixConcatenate[3 * i] *
        tmp_4[0] + TemplateLgV2_B.Product_feo[i];
      TemplateLgV2_B.Product_feo[i] = TemplateLgV2_B.MatrixConcatenate[3 * i + 1]
        * tmp_4[1] + TemplateLgV2_B.Product_feo[i];
      TemplateLgV2_B.Product_feo[i] = TemplateLgV2_B.MatrixConcatenate[3 * i + 2]
        * tmp_4[2] + TemplateLgV2_B.Product_feo[i];

      /* Gain: '<S43>/Gain' */
      TemplateLgV2_B.Gain_l[i] = TemplateLgV2_P.Gain_Gain_gd *
        TemplateLgV2_B.Product_feo[i];

      /* Math: '<S62>/Math Function' */
      TemplateLgV2_B.MathFunction_jk0[i] = TemplateLgV2_B.Gain_l[i];
    }

    /* Product: '<S42>/Product' */
    TemplateLgV2_B.Product_fj[0] = 0.0;
    TemplateLgV2_B.Product_fj[0] = TemplateLgV2_B.ux2[0] *
      TemplateLgV2_B.MathFunction_jk0[0] + TemplateLgV2_B.Product_fj[0];
    TemplateLgV2_B.Product_fj[0] = TemplateLgV2_B.ux2[2] *
      TemplateLgV2_B.MathFunction_jk0[1] + TemplateLgV2_B.Product_fj[0];

    /* Sum: '<S42>/Add1' */
    TemplateLgV2_B.Add1_o[0] = TemplateLgV2_B.Integrator2[0] +
      TemplateLgV2_B.Product_fj[0];

    /* Product: '<S42>/Product1' incorporates:
     *  Constant: '<S9>/lambda_q'
     */
    TemplateLgV2_B.Product1_lb[0] = TemplateLgV2_P.lambda_q_Value *
      TemplateLgV2_B.Add1_o[0];

    /* Gain: '<S42>/Gain' */
    TemplateLgV2_B.Gain_jz[0] = TemplateLgV2_P.Gain_Gain_pr *
      TemplateLgV2_B.Product1_lb[0];

    /* Product: '<S42>/Product' */
    TemplateLgV2_B.Product_fj[1] = 0.0;
    TemplateLgV2_B.Product_fj[1] = TemplateLgV2_B.ux2[1] *
      TemplateLgV2_B.MathFunction_jk0[0] + TemplateLgV2_B.Product_fj[1];
    TemplateLgV2_B.Product_fj[1] = TemplateLgV2_B.ux2[3] *
      TemplateLgV2_B.MathFunction_jk0[1] + TemplateLgV2_B.Product_fj[1];

    /* Sum: '<S42>/Add1' */
    TemplateLgV2_B.Add1_o[1] = TemplateLgV2_B.Integrator2[1] +
      TemplateLgV2_B.Product_fj[1];

    /* Product: '<S42>/Product1' incorporates:
     *  Constant: '<S9>/lambda_q'
     */
    TemplateLgV2_B.Product1_lb[1] = TemplateLgV2_P.lambda_q_Value *
      TemplateLgV2_B.Add1_o[1];

    /* Gain: '<S42>/Gain' */
    TemplateLgV2_B.Gain_jz[1] = TemplateLgV2_P.Gain_Gain_pr *
      TemplateLgV2_B.Product1_lb[1];

    /* Product: '<S50>/Product' */
    for (i = 0; i < 3; i++) {
      TemplateLgV2_B.Product_jo[i] = 0.0;
      TemplateLgV2_B.Product_jo[i] = TemplateLgV2_B.Rpsi[i] *
        TemplateLgV2_B.Subtract_i[0] + TemplateLgV2_B.Product_jo[i];
      TemplateLgV2_B.Product_jo[i] = TemplateLgV2_B.Rpsi[i + 3] *
        TemplateLgV2_B.Subtract_i[1] + TemplateLgV2_B.Product_jo[i];
      TemplateLgV2_B.Product_jo[i] = TemplateLgV2_B.Rpsi[i + 6] *
        TemplateLgV2_B.Subtract_i[2] + TemplateLgV2_B.Product_jo[i];
    }

    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* S-Function (sdsppinv): '<S76>/Pseudoinverse' */
      /* Copy input to temporary space */
      memcpy((void *)(&TemplateLgV2_DWork.Pseudoinverse_X[0]), (void *)
             (&TemplateLgV2_B.x5[0]), 15U * sizeof(real_T));

      /* Call SVD */
      i = MWDSP_SVD_D(&TemplateLgV2_DWork.Pseudoinverse_X[0], 3, 5,
                      &TemplateLgV2_DWork.Pseudoinverse_S[0],
                      &TemplateLgV2_DWork.Inverse_DWORK3[0],
                      &TemplateLgV2_DWork.Pseudoinverse_WORK[0],
                      &TemplateLgV2_DWork.Pseudoinverse_U[0],
                      &TemplateLgV2_DWork.Pseudoinverse_V[0], 1);

      /* Only call 'pinv' function if SVD succeeded */
      if (i == 0) {
        MWDSPCG_Pseudoinverse_D(&TemplateLgV2_DWork.Pseudoinverse_S[0],
          &TemplateLgV2_DWork.Pseudoinverse_U[0],
          &TemplateLgV2_DWork.Pseudoinverse_V[0], &TemplateLgV2_B.Pseudoinverse
          [0], (const int32_T)3, (const int32_T)5);
      }
    }

    /* Product: '<S76>/Product' */
    for (i = 0; i < 5; i++) {
      TemplateLgV2_B.Product_gz[i] = 0.0;
      TemplateLgV2_B.Product_gz[i] = TemplateLgV2_B.Pseudoinverse[i] *
        TemplateLgV2_B.tauSwitch[0] + TemplateLgV2_B.Product_gz[i];
      TemplateLgV2_B.Product_gz[i] = TemplateLgV2_B.Pseudoinverse[i + 5] *
        TemplateLgV2_B.tauSwitch[1] + TemplateLgV2_B.Product_gz[i];
      TemplateLgV2_B.Product_gz[i] = TemplateLgV2_B.Pseudoinverse[i + 10] *
        TemplateLgV2_B.tauSwitch[2] + TemplateLgV2_B.Product_gz[i];
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
    LookUp_real_T_real_T( &(TemplateLgV2_B.f_1tou_1),
                         TemplateLgV2_P.f_1tou_1_YData,
                         TemplateLgV2_B.Product_gz[0],
                         TemplateLgV2_P.f_1tou_1_XData, 38U);

    /* Sum: '<S77>/Sum' incorporates:
     *  Constant: '<S1>/offset u1'
     */
    TemplateLgV2_B.Sum_es = TemplateLgV2_P.offsetu1_Value +
      TemplateLgV2_B.f_1tou_1;

    /* RelationalOperator: '<S83>/Compare' incorporates:
     *  Constant: '<S83>/Constant'
     */
    TemplateLgV2_B.Compare = (TemplateLgV2_B.Product_gz[1] <
      TemplateLgV2_P.Constant_Value_lx);

    /* RelationalOperator: '<S85>/Compare' incorporates:
     *  Constant: '<S85>/Constant'
     */
    TemplateLgV2_B.Compare_d = (TemplateLgV2_B.Product_gz[1] >=
      TemplateLgV2_P.Constant_Value_k);

    /* RelationalOperator: '<S84>/Compare' incorporates:
     *  Constant: '<S84>/Constant'
     */
    TemplateLgV2_B.Compare_p = (TemplateLgV2_B.Product_gz[1] <
      TemplateLgV2_P.Constant_Value_mf);

    /* Logic: '<S79>/Logical Operator' */
    TemplateLgV2_B.LogicalOperator = ((TemplateLgV2_B.Compare_d != 0) &&
      (TemplateLgV2_B.Compare_p != 0));

    /* Sum: '<S79>/Sum1' */
    TemplateLgV2_B.Sum1_h = (uint8_T)(TemplateLgV2_B.LogicalOperator +
      TemplateLgV2_B.LogicalOperator);

    /* RelationalOperator: '<S86>/Compare' incorporates:
     *  Constant: '<S86>/Constant'
     */
    TemplateLgV2_B.Compare_i = (TemplateLgV2_B.Product_gz[1] >=
      TemplateLgV2_P.Constant_Value_kd);

    /* Gain: '<S79>/Gain1' */
    TemplateLgV2_B.Gain1_e = (uint16_T)(TemplateLgV2_P.Gain1_Gain_p *
      TemplateLgV2_B.Compare_i);

    /* Sum: '<S79>/Sum' */
    TemplateLgV2_B.Sum_iy = (uint16_T)(uint32_T)(((TemplateLgV2_B.Compare << 6)
      + (TemplateLgV2_B.Sum1_h << 6)) + TemplateLgV2_B.Gain1_e);

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
    LookUp_real_T_real_T( &(TemplateLgV2_B.f_2000391),
                         TemplateLgV2_P.f_2000391_YData,
                         TemplateLgV2_B.Product_gz[1],
                         TemplateLgV2_P.f_2000391_XData, 10U);

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
    LookUp_real_T_real_T( &(TemplateLgV2_B.f_2006731f_2000391),
                         TemplateLgV2_P.f_2006731f_2000391_YData,
                         TemplateLgV2_B.Product_gz[1],
                         TemplateLgV2_P.f_2006731f_2000391_XData, 2U);

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
    LookUp_real_T_real_T( &(TemplateLgV2_B.f_2006731),
                         TemplateLgV2_P.f_2006731_YData,
                         TemplateLgV2_B.Product_gz[1],
                         TemplateLgV2_P.f_2006731_XData, 17U);

    /* MultiPortSwitch: '<S79>/Multiport Switch' */
    switch ((int32_T)((uint32_T)(int32_T)TemplateLgV2_B.Sum_iy >> 6)) {
     case 1:
      TemplateLgV2_B.MultiportSwitch = TemplateLgV2_B.f_2000391;
      break;

     case 2:
      TemplateLgV2_B.MultiportSwitch = TemplateLgV2_B.f_2006731f_2000391;
      break;

     default:
      TemplateLgV2_B.MultiportSwitch = TemplateLgV2_B.f_2006731;
      break;
    }

    /* Sum: '<S77>/Sum1' incorporates:
     *  Constant: '<S1>/offset u2'
     */
    TemplateLgV2_B.Sum1_l = TemplateLgV2_P.offsetu2_Value +
      TemplateLgV2_B.MultiportSwitch;

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
    LookUp_real_T_real_T( &(TemplateLgV2_B.f_3tou_3),
                         TemplateLgV2_P.f_3tou_3_YData,
                         TemplateLgV2_B.Product_gz[2],
                         TemplateLgV2_P.f_3tou_3_XData, 38U);

    /* Sum: '<S77>/Sum2' incorporates:
     *  Constant: '<S1>/offset u3'
     */
    TemplateLgV2_B.Sum2_e = TemplateLgV2_P.offsetu3_Value +
      TemplateLgV2_B.f_3tou_3;

    /* RelationalOperator: '<S87>/Compare' incorporates:
     *  Constant: '<S87>/Constant'
     */
    TemplateLgV2_B.Compare_h = (TemplateLgV2_B.Product_gz[3] <
      TemplateLgV2_P.Constant_Value_d);

    /* RelationalOperator: '<S88>/Compare' incorporates:
     *  Constant: '<S88>/Constant'
     */
    TemplateLgV2_B.Compare_c = (TemplateLgV2_B.Product_gz[3] >=
      TemplateLgV2_P.Constant_Value_ls);

    /* Gain: '<S81>/Gain' */
    TemplateLgV2_B.Gain_mj = (uint16_T)(TemplateLgV2_P.Gain_Gain_k3 *
      TemplateLgV2_B.Compare_c);

    /* Sum: '<S81>/Sum' */
    TemplateLgV2_B.Sum_bm = (uint16_T)(uint32_T)((TemplateLgV2_B.Compare_h << 6)
      + TemplateLgV2_B.Gain_mj);

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
    LookUp_real_T_real_T( &(TemplateLgV2_B.f_400451),
                         TemplateLgV2_P.f_400451_YData,
                         TemplateLgV2_B.Product_gz[3],
                         TemplateLgV2_P.f_400451_XData, 14U);

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
    LookUp_real_T_real_T( &(TemplateLgV2_B.f_400451_l),
                         TemplateLgV2_P.f_400451_YData_a,
                         TemplateLgV2_B.Product_gz[3],
                         TemplateLgV2_P.f_400451_XData_h, 12U);

    /* MultiPortSwitch: '<S81>/Multiport Switch' */
    if ((int32_T)((uint32_T)(int32_T)TemplateLgV2_B.Sum_bm >> 6) == 1) {
      TemplateLgV2_B.MultiportSwitch_p = TemplateLgV2_B.f_400451;
    } else {
      TemplateLgV2_B.MultiportSwitch_p = TemplateLgV2_B.f_400451_l;
    }

    /* Sum: '<S77>/Sum3' incorporates:
     *  Constant: '<S1>/offset u4'
     */
    TemplateLgV2_B.Sum3_a = TemplateLgV2_B.MultiportSwitch_p +
      TemplateLgV2_P.offsetu4_Value;

    /* DeadZone Block: '<S82>/Dead Zone +-0.01'
     */
    if (TemplateLgV2_B.Product_gz[4] >= TemplateLgV2_P.DeadZone001_End) {
      TemplateLgV2_B.DeadZone001 = TemplateLgV2_B.Product_gz[4] -
        TemplateLgV2_P.DeadZone001_End;
    } else if (TemplateLgV2_B.Product_gz[4] > TemplateLgV2_P.DeadZone001_Start)
    {
      TemplateLgV2_B.DeadZone001 = 0.0;
    } else {
      TemplateLgV2_B.DeadZone001 = TemplateLgV2_B.Product_gz[4] -
        TemplateLgV2_P.DeadZone001_Start;
    }

    /* RelationalOperator: '<S89>/Compare' incorporates:
     *  Constant: '<S89>/Constant'
     */
    TemplateLgV2_B.Compare_k = (TemplateLgV2_B.DeadZone001 <
      TemplateLgV2_P.Constant_Value_g);

    /* RelationalOperator: '<S91>/Compare' */
    TemplateLgV2_B.Compare_i2 = (TemplateLgV2_B.DeadZone001 == 0.0);

    /* Gain: '<S82>/Gain' */
    TemplateLgV2_B.Gain_n = (uint16_T)(TemplateLgV2_P.Gain_Gain_cg *
      TemplateLgV2_B.Compare_i2);

    /* RelationalOperator: '<S90>/Compare' incorporates:
     *  Constant: '<S90>/Constant'
     */
    TemplateLgV2_B.Compare_e = (TemplateLgV2_B.DeadZone001 >
      TemplateLgV2_P.Constant_Value_n);

    /* Gain: '<S82>/Gain1' */
    TemplateLgV2_B.Gain1_l = (uint16_T)(TemplateLgV2_P.Gain1_Gain_h *
      TemplateLgV2_B.Compare_e);

    /* Sum: '<S82>/Sum' */
    TemplateLgV2_B.Sum_m = (uint16_T)(uint32_T)(((TemplateLgV2_B.Compare_k << 6)
      + TemplateLgV2_B.Gain_n) + TemplateLgV2_B.Gain1_l);

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
    LookUp_real_T_real_T( &(TemplateLgV2_B.f_50), TemplateLgV2_P.f_50_YData,
                         TemplateLgV2_B.Product_gz[4], TemplateLgV2_P.f_50_XData,
                         9U);

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
    LookUp_real_T_real_T( &(TemplateLgV2_B.f_50_g), TemplateLgV2_P.f_50_YData_d,
                         TemplateLgV2_B.Product_gz[4],
                         TemplateLgV2_P.f_50_XData_f, 9U);

    /* MultiPortSwitch: '<S82>/Multiport Switch' incorporates:
     *  Constant: '<S82>/f_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)TemplateLgV2_B.Sum_m >> 6)) {
     case 1:
      TemplateLgV2_B.MultiportSwitch_k = TemplateLgV2_B.f_50;
      break;

     case 2:
      TemplateLgV2_B.MultiportSwitch_k = TemplateLgV2_P.f_50_Value;
      break;

     default:
      TemplateLgV2_B.MultiportSwitch_k = TemplateLgV2_B.f_50_g;
      break;
    }

    /* Saturate: '<S33>/Saturation' incorporates:
     *  Constant: '<S75>/BT_power_limit'
     *  Constant: '<S75>/VSP_speeds'
     */
    tmp_0[0] = TemplateLgV2_B.Sum_es;
    tmp_0[1] = TemplateLgV2_B.Sum1_l;
    tmp_0[2] = TemplateLgV2_B.Sum2_e;
    tmp_0[3] = TemplateLgV2_B.Sum3_a;
    tmp_0[4] = TemplateLgV2_B.MultiportSwitch_k;
    tmp_0[5] = TemplateLgV2_P.BT_power_limit_Value;
    tmp_0[6] = TemplateLgV2_P.VSP_speeds_Value;
    for (i = 0; i < 7; i++) {
      TemplateLgV2_B.Saturation_bg[i] = rt_SATURATE(tmp_0[i],
        TemplateLgV2_P.Saturation_LowerSat_b,
        TemplateLgV2_P.Saturation_UpperSat_kpo);
    }

    /* Gain: '<S166>/QTM In2 Error' */
    TemplateLgV2_B.QTMIn2Error = TemplateLgV2_P.QTMIn2Error_Gain *
      TemplateLgV2_B.QTMIn[1];

    /* Gain: '<S166>/QTM In9 Residual' */
    TemplateLgV2_B.QTMIn9Residual = TemplateLgV2_P.QTMIn9Residual_Gain *
      TemplateLgV2_B.QTMIn[8];
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Saturate: '<S193>/Saturation' incorporates:
       *  Constant: '<S1>/Control Mode Selector'
       */
      tmp = TemplateLgV2_P.ControlModeSelector_Value;
      TemplateLgV2_B.Saturation_lh = rt_SATURATE(tmp,
        TemplateLgV2_P.Saturation_LowerSat_hx,
        TemplateLgV2_P.Saturation_UpperSat_f);
    }

    /* MultiPortSwitch: '<S193>/tau Switch' incorporates:
     *  Constant: '<S6>/PS3_BT_Power  [-]'
     *  Constant: '<S6>/PS3_VSP_Speed  [-]'
     */
    if ((int32_T)TemplateLgV2_B.Saturation_lh == 0) {
      TemplateLgV2_B.tauSwitch_j[0] = TemplateLgV2_B.u_1;
      TemplateLgV2_B.tauSwitch_j[1] = TemplateLgV2_B.u_2;
      TemplateLgV2_B.tauSwitch_j[2] = TemplateLgV2_B.u_3;
      TemplateLgV2_B.tauSwitch_j[3] = TemplateLgV2_B.u_4;
      TemplateLgV2_B.tauSwitch_j[4] = TemplateLgV2_B.u_5;
      TemplateLgV2_B.tauSwitch_j[5] = TemplateLgV2_P.PS3_BT_Power_Value;
      TemplateLgV2_B.tauSwitch_j[6] = TemplateLgV2_P.PS3_VSP_Speed_Value;
    } else {
      for (i = 0; i < 7; i++) {
        TemplateLgV2_B.tauSwitch_j[i] = TemplateLgV2_B.Saturation_bg[i];
      }
    }

    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* SignalConversion: '<S22>/TmpHiddenBufferAtTo FileInport1' incorporates:
       *  Constant: '<S1>/Control Input Selector'
       *  Constant: '<S1>/Control Mode Selector'
       *  Constant: '<S5>/Delta [m]'
       *  Constant: '<S5>/Path Selector  [-]'
       *  Constant: '<S5>/my [-]'
       *  Constant: '<S5>/u_d [m]'
       *  Constant: '<S9>/Gamma_q_Surge'
       *  Constant: '<S9>/Gamma_q_Sway'
       *  Constant: '<S9>/ctrl2Kdpsi'
       *  Constant: '<S9>/ctrl2Kdx'
       *  Constant: '<S9>/ctrl2Kdy'
       *  Constant: '<S9>/ctrl2Kipsi'
       *  Constant: '<S9>/ctrl2Kix'
       *  Constant: '<S9>/ctrl2Kiy'
       *  Constant: '<S9>/ctrl2Kppsi'
       *  Constant: '<S9>/ctrl2Kpx'
       *  Constant: '<S9>/ctrl2Kpy'
       *  Constant: '<S9>/kappa_1'
       *  Constant: '<S9>/lambda_q'
       */
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[0] =
        TemplateLgV2_P.ControlModeSelector_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[1] =
        TemplateLgV2_P.ControlInputSelector_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[2] =
        TemplateLgV2_P.PathSelector_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[3] =
        TemplateLgV2_B.QTMIn2Error;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[4] =
        TemplateLgV2_B.QTMIn9Residual;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[5] =
        TemplateLgV2_B.etaSwitch[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[6] =
        TemplateLgV2_B.etaSwitch[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[7] =
        TemplateLgV2_B.etaSwitch[2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[8] =
        TemplateLgV2_B.nuSwitch[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[9] =
        TemplateLgV2_B.nuSwitch[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[10] =
        TemplateLgV2_B.nuSwitch[2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[11] =
        TemplateLgV2_B.VectorConcatenate[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[12] =
        TemplateLgV2_B.VectorConcatenate[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[13] =
        TemplateLgV2_B.VectorConcatenate[2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[14] =
        TemplateLgV2_B.Integrator2[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[15] =
        TemplateLgV2_B.Integrator2[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[16] = TemplateLgV2_B.Switch2;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[17] =
        TemplateLgV2_B.Switch2_i;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[18] = TemplateLgV2_B.Sum_g;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[19] =
        TemplateLgV2_P.u_dm_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[20] =
        TemplateLgV2_B.Divide_b;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[21] =
        TemplateLgV2_B.Integrator1;
      for (i = 0; i < 7; i++) {
        TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[i + 22] =
          TemplateLgV2_B.tauSwitch_j[i];
      }

      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[29] =
        TemplateLgV2_B.tauSwitch[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[30] =
        TemplateLgV2_B.tauSwitch[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[31] =
        TemplateLgV2_B.tauSwitch[2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[32] = TemplateLgV2_B.Gain_d
        [0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[33] = TemplateLgV2_B.Gain_d
        [1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[34] = TemplateLgV2_B.Gain_d
        [2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[35] =
        TemplateLgV2_B.Gain1_k[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[36] =
        TemplateLgV2_B.Gain1_k[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[37] =
        TemplateLgV2_B.Gain1_k[2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[38] =
        TemplateLgV2_B.Product2_d[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[39] =
        TemplateLgV2_B.Product2_d[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[40] =
        TemplateLgV2_B.Product2_d[2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[41] =
        TemplateLgV2_B.Product4_d[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[42] =
        TemplateLgV2_B.Product4_d[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[43] =
        TemplateLgV2_B.Product4_d[2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[44] =
        TemplateLgV2_B.Product5[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[45] =
        TemplateLgV2_B.Product5[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[46] =
        TemplateLgV2_B.Product5[2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[47] =
        TemplateLgV2_B.Product6[0];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[48] =
        TemplateLgV2_B.Product6[1];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[49] =
        TemplateLgV2_B.Product6[2];
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[50] =
        TemplateLgV2_P.kappa_1_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[51] =
        TemplateLgV2_P.ctrl2Kpx_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[52] =
        TemplateLgV2_P.ctrl2Kpy_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[53] =
        TemplateLgV2_P.ctrl2Kppsi_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[54] =
        TemplateLgV2_P.ctrl2Kix_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[55] =
        TemplateLgV2_P.ctrl2Kiy_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[56] =
        TemplateLgV2_P.ctrl2Kipsi_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[57] =
        TemplateLgV2_P.ctrl2Kdx_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[58] =
        TemplateLgV2_P.ctrl2Kdy_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[59] =
        TemplateLgV2_P.ctrl2Kdpsi_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[60] =
        TemplateLgV2_P.Gamma_q_Surge_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[61] =
        TemplateLgV2_P.Gamma_q_Sway_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[62] =
        TemplateLgV2_P.lambda_q_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[63] =
        TemplateLgV2_P.Deltam_Value;
      TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[64] =
        TemplateLgV2_P.my_Value;

      /* ToFile Block: '<S22>/To File'
       */
      if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
        if (!(++TemplateLgV2_DWork.ToFile_IWORK.Decimation % 1) &&
            (TemplateLgV2_DWork.ToFile_IWORK.Count*66)+1 < 100000000 ) {
          real_T u[66];
          FILE *fp = (FILE *) TemplateLgV2_DWork.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            TemplateLgV2_DWork.ToFile_IWORK.Decimation = 0;
            u[0] = TemplateLgV2_M->Timing.t[1];
            u[1] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[0];
            u[2] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[1];
            u[3] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[2];
            u[4] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[3];
            u[5] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[4];
            u[6] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[5];
            u[7] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[6];
            u[8] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[7];
            u[9] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[8];
            u[10] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[9];
            u[11] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[10];
            u[12] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[11];
            u[13] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[12];
            u[14] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[13];
            u[15] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[14];
            u[16] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[15];
            u[17] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[16];
            u[18] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[17];
            u[19] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[18];
            u[20] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[19];
            u[21] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[20];
            u[22] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[21];
            u[23] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[22];
            u[24] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[23];
            u[25] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[24];
            u[26] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[25];
            u[27] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[26];
            u[28] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[27];
            u[29] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[28];
            u[30] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[29];
            u[31] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[30];
            u[32] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[31];
            u[33] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[32];
            u[34] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[33];
            u[35] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[34];
            u[36] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[35];
            u[37] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[36];
            u[38] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[37];
            u[39] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[38];
            u[40] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[39];
            u[41] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[40];
            u[42] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[41];
            u[43] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[42];
            u[44] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[43];
            u[45] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[44];
            u[46] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[45];
            u[47] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[46];
            u[48] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[47];
            u[49] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[48];
            u[50] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[49];
            u[51] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[50];
            u[52] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[51];
            u[53] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[52];
            u[54] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[53];
            u[55] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[54];
            u[56] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[55];
            u[57] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[56];
            u[58] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[57];
            u[59] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[58];
            u[60] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[59];
            u[61] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[60];
            u[62] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[61];
            u[63] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[62];
            u[64] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[63];
            u[65] = TemplateLgV2_B.TmpHiddenBufferAtToFileInport1[64];
            if (fwrite(u, sizeof(real_T), 66, fp) != 66) {
              rtmSetErrorStatus(TemplateLgV2_M,
                                "Error writing to MAT-file LgV2_data.mat");
              return;
            }

            if (((++TemplateLgV2_DWork.ToFile_IWORK.Count)*66)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file LgV2_data.mat.\n");
            }
          }
        }
      }
    }

    /* Gain: '<S166>/QTM In5 z-coord [mm]' */
    TemplateLgV2_B.QTMIn5zcoordmm = TemplateLgV2_P.QTMIn5zcoordmm_Gain *
      TemplateLgV2_B.QTMIn[4];

    /* Gain: '<S166>/mm2m z' */
    TemplateLgV2_B.mm2mz = TemplateLgV2_P.mm2mz_Gain *
      TemplateLgV2_B.QTMIn5zcoordmm;

    /* Gain: '<S166>/QTM In8 roll [deg]' */
    TemplateLgV2_B.QTMIn8rolldeg = TemplateLgV2_P.QTMIn8rolldeg_Gain *
      TemplateLgV2_B.QTMIn[7];

    /* Gain: '<S166>/d2r roll' */
    TemplateLgV2_B.d2rroll = TemplateLgV2_P.d2rroll_Gain *
      TemplateLgV2_B.QTMIn8rolldeg;

    /* Gain: '<S166>/QTM In7 pitch [deg]' */
    TemplateLgV2_B.QTMIn7pitchdeg = TemplateLgV2_P.QTMIn7pitchdeg_Gain *
      TemplateLgV2_B.QTMIn[6];

    /* Gain: '<S166>/d2r pitch' */
    TemplateLgV2_B.d2rpitch = TemplateLgV2_P.d2rpitch_Gain *
      TemplateLgV2_B.QTMIn7pitchdeg;

    /* Derivative Block: '<S166>/Derivative' */
    {
      real_T t = TemplateLgV2_M->Timing.t[0];
      real_T timeStampA = TemplateLgV2_DWork.Derivative_RWORK_k.TimeStampA;
      real_T timeStampB = TemplateLgV2_DWork.Derivative_RWORK_k.TimeStampB;
      if (timeStampA >= t && timeStampB >= t) {
        {
          int_T i1;
          real_T *y0 = TemplateLgV2_B.Derivative_h;
          for (i1=0; i1 < 6; i1++) {
            y0[i1] = 0.0;
          }
        }
      } else {
        real_T deltaT;
        real_T *lastBank = &TemplateLgV2_DWork.Derivative_RWORK_k.TimeStampA;
        if (timeStampA < timeStampB) {
          if (timeStampB < t) {
            lastBank += 7;
          }
        } else if (timeStampA >= t) {
          lastBank += 7;
        }

        deltaT = t - *lastBank++;
        TemplateLgV2_B.Derivative_h[0] = (TemplateLgV2_B.mm2mx - *lastBank++) /
          deltaT;
        TemplateLgV2_B.Derivative_h[1] = (TemplateLgV2_B.mm2my - *lastBank++) /
          deltaT;
        TemplateLgV2_B.Derivative_h[2] = (TemplateLgV2_B.mm2mz - *lastBank++) /
          deltaT;
        TemplateLgV2_B.Derivative_h[3] = (TemplateLgV2_B.d2rroll - *lastBank++) /
          deltaT;
        TemplateLgV2_B.Derivative_h[4] = (TemplateLgV2_B.d2rpitch - *lastBank++)
          / deltaT;
        TemplateLgV2_B.Derivative_h[5] = (TemplateLgV2_B.d2ryaw - *lastBank++) /
          deltaT;
      }
    }

    /* Trigonometry: '<S168>/sin(theta)' */
    TemplateLgV2_B.sintheta[0] = sin(TemplateLgV2_B.d2rroll);
    TemplateLgV2_B.sintheta[1] = sin(TemplateLgV2_B.d2rpitch);
    TemplateLgV2_B.sintheta[2] = sin(TemplateLgV2_B.d2ryaw);

    /* Trigonometry: '<S168>/cos(theta)' */
    TemplateLgV2_B.costheta[0] = cos(TemplateLgV2_B.d2rroll);
    TemplateLgV2_B.costheta[1] = cos(TemplateLgV2_B.d2rpitch);
    TemplateLgV2_B.costheta[2] = cos(TemplateLgV2_B.d2ryaw);

    /* Fcn: '<S168>/R11' */
    TemplateLgV2_B.R11_o = TemplateLgV2_B.costheta[1] * TemplateLgV2_B.costheta
      [2];

    /* Fcn: '<S168>/R12' */
    TemplateLgV2_B.R12_p = TemplateLgV2_B.costheta[1] * TemplateLgV2_B.sintheta
      [2];

    /* Fcn: '<S168>/R13' */
    TemplateLgV2_B.R13 = -TemplateLgV2_B.sintheta[1];

    /* Fcn: '<S168>/R21 ' */
    TemplateLgV2_B.R21_h = TemplateLgV2_B.sintheta[0] * TemplateLgV2_B.sintheta
      [1] * TemplateLgV2_B.costheta[2] + (-TemplateLgV2_B.costheta[0]) *
      TemplateLgV2_B.sintheta[2];

    /* Fcn: '<S168>/R22' */
    TemplateLgV2_B.R22_o = TemplateLgV2_B.sintheta[0] * TemplateLgV2_B.sintheta
      [1] * TemplateLgV2_B.sintheta[2] + TemplateLgV2_B.costheta[0] *
      TemplateLgV2_B.costheta[2];

    /* Fcn: '<S168>/R23' */
    TemplateLgV2_B.R23 = TemplateLgV2_B.sintheta[0] * TemplateLgV2_B.costheta[1];

    /* Fcn: '<S168>/R31 ' */
    TemplateLgV2_B.R31 = TemplateLgV2_B.costheta[0] * TemplateLgV2_B.sintheta[1]
      * TemplateLgV2_B.costheta[2] + TemplateLgV2_B.sintheta[0] *
      TemplateLgV2_B.sintheta[2];

    /* Fcn: '<S168>/R32' */
    TemplateLgV2_B.R32 = TemplateLgV2_B.costheta[0] * TemplateLgV2_B.sintheta[1]
      * TemplateLgV2_B.sintheta[2] + (-TemplateLgV2_B.sintheta[0]) *
      TemplateLgV2_B.costheta[2];

    /* Fcn: '<S168>/R33' */
    TemplateLgV2_B.R33 = TemplateLgV2_B.costheta[0] * TemplateLgV2_B.costheta[1];

    /* Reshape: '<S168>/Reshape 9x1->3x3' */
    TemplateLgV2_B.Reshape9x13x3[0] = TemplateLgV2_B.R11_o;
    TemplateLgV2_B.Reshape9x13x3[1] = TemplateLgV2_B.R21_h;
    TemplateLgV2_B.Reshape9x13x3[2] = TemplateLgV2_B.R31;
    TemplateLgV2_B.Reshape9x13x3[3] = TemplateLgV2_B.R12_p;
    TemplateLgV2_B.Reshape9x13x3[4] = TemplateLgV2_B.R22_o;
    TemplateLgV2_B.Reshape9x13x3[5] = TemplateLgV2_B.R32;
    TemplateLgV2_B.Reshape9x13x3[6] = TemplateLgV2_B.R13;
    TemplateLgV2_B.Reshape9x13x3[7] = TemplateLgV2_B.R23;
    TemplateLgV2_B.Reshape9x13x3[8] = TemplateLgV2_B.R33;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Product Block: '<S166>/Inverse' */
      {
        static const int_T dims[3] = { 3, 3, 3 };

        rt_MatDivRR_Dbl(TemplateLgV2_B.Inverse, TemplateLgV2_B.x3,
                        &TemplateLgV2_DWork.Inverse_DWORK4[0], (real_T*)
                        &TemplateLgV2_DWork.Pseudoinverse_X[0],
                        &TemplateLgV2_DWork.Inverse_DWORK2[0], (real_T*)
                        &TemplateLgV2_DWork.Inverse_DWORK3[0],
                        &dims[0]);
      }
    }

    /* Concatenate: '<S166>/Matrix Concatenate' incorporates:
     *  Constant: '<S166>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_5[6 * i] = TemplateLgV2_B.Reshape9x13x3[3 * i];
      tmp_5[1 + 6 * i] = TemplateLgV2_B.Reshape9x13x3[3 * i + 1];
      tmp_5[2 + 6 * i] = TemplateLgV2_B.Reshape9x13x3[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_5[3 + 6 * i] = TemplateLgV2_P.Constant1_Value[3 * i];
      tmp_5[4 + 6 * i] = TemplateLgV2_P.Constant1_Value[3 * i + 1];
      tmp_5[5 + 6 * i] = TemplateLgV2_P.Constant1_Value[3 * i + 2];
    }

    memcpy((void *)(&TemplateLgV2_B.MatrixConcatenate2[0]), (void *)&tmp_5[0],
           18U * sizeof(real_T));

    /* Concatenate: '<S166>/Matrix Concatenate1' incorporates:
     *  Constant: '<S166>/Constant1'
     */
    for (i = 0; i < 3; i++) {
      tmp_5[6 * i] = TemplateLgV2_P.Constant1_Value[3 * i];
      tmp_5[1 + 6 * i] = TemplateLgV2_P.Constant1_Value[3 * i + 1];
      tmp_5[2 + 6 * i] = TemplateLgV2_P.Constant1_Value[3 * i + 2];
    }

    for (i = 0; i < 3; i++) {
      tmp_5[3 + 6 * i] = TemplateLgV2_B.Reshape9x13x3[3 * i];
      tmp_5[4 + 6 * i] = TemplateLgV2_B.Reshape9x13x3[3 * i + 1];
      tmp_5[5 + 6 * i] = TemplateLgV2_B.Reshape9x13x3[3 * i + 2];
    }

    memcpy((void *)(&TemplateLgV2_B.MatrixConcatenate2[18]), (void *)&tmp_5[0],
           18U * sizeof(real_T));

    /* Product: '<S166>/Product' */
    for (i = 0; i < 6; i++) {
      TemplateLgV2_B.Product_i3[i] = 0.0;
      for (tmp_6 = 0; tmp_6 < 6; tmp_6++) {
        TemplateLgV2_B.Product_i3[i] = TemplateLgV2_B.MatrixConcatenate2[6 *
          tmp_6 + i] * TemplateLgV2_B.Derivative_h[tmp_6] +
          TemplateLgV2_B.Product_i3[i];
      }
    }

    /* Gain: '<S166>/QTM In1 FN' */
    TemplateLgV2_B.QTMIn1FN = TemplateLgV2_P.QTMIn1FN_Gain *
      TemplateLgV2_B.QTMIn[0];

    /* Integrator Block: '<S169>/Integrator'
     */
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      ZCEventType zcEvent;
      zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE_m,
                         TemplateLgV2_P.ctrl2ResetIntegrator_Value);

      /* evaluate zero-crossings and the level of the reset signal */
      if (zcEvent || TemplateLgV2_P.ctrl2ResetIntegrator_Value != 0.0 ||
          TemplateLgV2_DWork.Integrator_IWORK_c.IcNeedsLoading) {
        TemplateLgV2_X.Integrator_CSTATE_o[0] = TemplateLgV2_B.mm2mx;
        TemplateLgV2_X.Integrator_CSTATE_o[1] = TemplateLgV2_B.mm2my;
        TemplateLgV2_X.Integrator_CSTATE_o[2] = TemplateLgV2_B.d2ryaw;
      }

      TemplateLgV2_DWork.Integrator_IWORK_c.IcNeedsLoading = 0;
    }

    TemplateLgV2_B.eta[0] = TemplateLgV2_X.Integrator_CSTATE_o[0];
    TemplateLgV2_B.eta[1] = TemplateLgV2_X.Integrator_CSTATE_o[1];
    TemplateLgV2_B.eta[2] = TemplateLgV2_X.Integrator_CSTATE_o[2];

    /* Integrator: '<S169>/Integrator3' */
    TemplateLgV2_B.bias[0] = TemplateLgV2_X.Integrator3_CSTATE[0];
    TemplateLgV2_B.bias[1] = TemplateLgV2_X.Integrator3_CSTATE[1];
    TemplateLgV2_B.bias[2] = TemplateLgV2_X.Integrator3_CSTATE[2];

    /* Saturate: '<S174>/Saturation' */
    tmp = TemplateLgV2_B.eta[2];
    TemplateLgV2_B.Saturation_d = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_n,
      TemplateLgV2_P.Saturation_UpperSat_l3);

    /* Signum: '<S174>/Sign' */
    TemplateLgV2_B.Sign_i = rt_SIGNd_snf(TemplateLgV2_B.Saturation_d);

    /* Gain: '<S174>/Gain' */
    TemplateLgV2_B.Gain_bj = TemplateLgV2_P.Gain_Gain_kx * TemplateLgV2_B.Sign_i;

    /* Sum: '<S174>/Sum1' */
    TemplateLgV2_B.Sum1_nt = TemplateLgV2_B.Saturation_d +
      TemplateLgV2_B.Gain_bj;

    /* Math: '<S174>/Math Function' incorporates:
     *  Constant: '<S174>/Constant'
     */
    TemplateLgV2_B.MathFunction_gq = rt_rem_snf(TemplateLgV2_B.Sum1_nt,
      TemplateLgV2_P.Constant_Value_pa);

    /* Sum: '<S174>/Sum' */
    TemplateLgV2_B.Sum_i = TemplateLgV2_B.MathFunction_gq -
      TemplateLgV2_B.Gain_bj;

    /* Sum: '<S169>/Sum2' */
    TemplateLgV2_B.Sum2_h[0] = TemplateLgV2_B.mm2mx - TemplateLgV2_B.eta[0];
    TemplateLgV2_B.Sum2_h[1] = TemplateLgV2_B.mm2my - TemplateLgV2_B.eta[1];
    TemplateLgV2_B.Sum2_h[2] = TemplateLgV2_B.d2ryaw - TemplateLgV2_B.Sum_i;

    /* Saturate: '<S175>/Saturation' */
    tmp = TemplateLgV2_B.Sum2_h[2];
    TemplateLgV2_B.Saturation_a = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_il,
      TemplateLgV2_P.Saturation_UpperSat_ii);

    /* Signum: '<S175>/Sign' */
    TemplateLgV2_B.Sign_pa = rt_SIGNd_snf(TemplateLgV2_B.Saturation_a);

    /* Gain: '<S175>/Gain' */
    TemplateLgV2_B.Gain_cg = TemplateLgV2_P.Gain_Gain_lw *
      TemplateLgV2_B.Sign_pa;

    /* Sum: '<S175>/Sum1' */
    TemplateLgV2_B.Sum1_a = TemplateLgV2_B.Saturation_a + TemplateLgV2_B.Gain_cg;

    /* Math: '<S175>/Math Function' incorporates:
     *  Constant: '<S175>/Constant'
     */
    TemplateLgV2_B.MathFunction_le = rt_rem_snf(TemplateLgV2_B.Sum1_a,
      TemplateLgV2_P.Constant_Value_an);

    /* Sum: '<S175>/Sum' */
    TemplateLgV2_B.Sum_dt = TemplateLgV2_B.MathFunction_le -
      TemplateLgV2_B.Gain_cg;

    /* SignalConversion: '<S169>/TmpHiddenBufferAtK2Inport1' */
    TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[0] = TemplateLgV2_B.Sum2_h[0];
    TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[1] = TemplateLgV2_B.Sum2_h[1];
    TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[2] = TemplateLgV2_B.Sum_dt;
    for (i = 0; i < 3; i++) {
      /* Gain: '<S169>/K2' */
      TemplateLgV2_B.K2[i] = 0.0;
      TemplateLgV2_B.K2[i] = TemplateLgV2_P.K2_Gain[i] *
        TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[0] + TemplateLgV2_B.K2[i];
      TemplateLgV2_B.K2[i] = TemplateLgV2_P.K2_Gain[i + 3] *
        TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[1] + TemplateLgV2_B.K2[i];
      TemplateLgV2_B.K2[i] = TemplateLgV2_P.K2_Gain[i + 6] *
        TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[2] + TemplateLgV2_B.K2[i];

      /* Gain: '<S169>/K3' */
      TemplateLgV2_B.K3[i] = 0.0;
      TemplateLgV2_B.K3[i] = TemplateLgV2_P.K3_Gain[i] *
        TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[0] + TemplateLgV2_B.K3[i];
      TemplateLgV2_B.K3[i] = TemplateLgV2_P.K3_Gain[i + 3] *
        TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[1] + TemplateLgV2_B.K3[i];
      TemplateLgV2_B.K3[i] = TemplateLgV2_P.K3_Gain[i + 6] *
        TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[2] + TemplateLgV2_B.K3[i];

      /* Gain: '<S169>/K4' */
      TemplateLgV2_B.K4[i] = 0.0;
      TemplateLgV2_B.K4[i] = TemplateLgV2_P.K4_Gain[i] *
        TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[0] + TemplateLgV2_B.K4[i];
      TemplateLgV2_B.K4[i] = TemplateLgV2_P.K4_Gain[i + 3] *
        TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[1] + TemplateLgV2_B.K4[i];
      TemplateLgV2_B.K4[i] = TemplateLgV2_P.K4_Gain[i + 6] *
        TemplateLgV2_B.TmpHiddenBufferAtK2Inport1[2] + TemplateLgV2_B.K4[i];
    }

    /* Fcn: '<S172>/Row1' */
    TemplateLgV2_B.Row1_b = cos(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.K4[0] +
      sin(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.K4[1];

    /* Fcn: '<S172>/Row2' */
    TemplateLgV2_B.Row2_k = (-sin(TemplateLgV2_B.d2ryaw)) * TemplateLgV2_B.K4[0]
      + cos(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.K4[1];

    /* Fcn: '<S172>/Row3' */
    TemplateLgV2_B.Row3_m = TemplateLgV2_B.K4[2];

    /* Fcn: '<S173>/Row1' */
    TemplateLgV2_B.Row1_a = cos(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.bias[0]
      + sin(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.bias[1];

    /* Fcn: '<S173>/Row2' */
    TemplateLgV2_B.Row2_c = (-sin(TemplateLgV2_B.d2ryaw)) * TemplateLgV2_B.bias
      [0] + cos(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.bias[1];

    /* Fcn: '<S173>/Row3' */
    TemplateLgV2_B.Row3_j = TemplateLgV2_B.bias[2];

    /* Lookup Block: '<S177>/u_1 to f_1'
     * About '<S177>/u_1 to f_1 :'
     * Lookup Block: '<S177>/u_1 to f_1'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateLgV2_B.u_1tof_1_l),
                         TemplateLgV2_P.u_1tof_1_YData_d,
                         TemplateLgV2_B.Saturation_bg[0],
                         TemplateLgV2_P.u_1tof_1_XData_g, 38U);

    /* RelationalOperator: '<S182>/Compare' incorporates:
     *  Constant: '<S182>/Constant'
     */
    TemplateLgV2_B.Compare_ip = (TemplateLgV2_B.Saturation_bg[1] <
      TemplateLgV2_P.Constant_Value_h);

    /* RelationalOperator: '<S184>/Compare' incorporates:
     *  Constant: '<S184>/Constant'
     */
    TemplateLgV2_B.Compare_en = (TemplateLgV2_B.Saturation_bg[1] >=
      TemplateLgV2_P.Constant_Value_fq);

    /* RelationalOperator: '<S183>/Compare' incorporates:
     *  Constant: '<S183>/Constant'
     */
    TemplateLgV2_B.Compare_o = (TemplateLgV2_B.Saturation_bg[1] <
      TemplateLgV2_P.Constant_Value_i0);

    /* Logic: '<S178>/Logical Operator' */
    TemplateLgV2_B.LogicalOperator_n = ((TemplateLgV2_B.Compare_en != 0) &&
      (TemplateLgV2_B.Compare_o != 0));

    /* Sum: '<S178>/Sum1' */
    TemplateLgV2_B.Sum1_o = (uint8_T)(TemplateLgV2_B.LogicalOperator_n +
      TemplateLgV2_B.LogicalOperator_n);

    /* RelationalOperator: '<S185>/Compare' incorporates:
     *  Constant: '<S185>/Constant'
     */
    TemplateLgV2_B.Compare_dk = (TemplateLgV2_B.Saturation_bg[1] >=
      TemplateLgV2_P.Constant_Value_j);

    /* Gain: '<S178>/Gain1' */
    TemplateLgV2_B.Gain1_h = (uint16_T)(TemplateLgV2_P.Gain1_Gain_c *
      TemplateLgV2_B.Compare_dk);

    /* Sum: '<S178>/Sum' */
    TemplateLgV2_B.Sum_fk = (uint16_T)(uint32_T)(((TemplateLgV2_B.Compare_ip <<
      6) + (TemplateLgV2_B.Sum1_o << 6)) + TemplateLgV2_B.Gain1_h);

    /* Lookup Block: '<S178>/u_2 < -0.5'
     * About '<S178>/u_2 < -0.5 :'
     * Lookup Block: '<S178>/u_2 < -0.5'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateLgV2_B.u_205), TemplateLgV2_P.u_205_YData,
                         TemplateLgV2_B.Saturation_bg[1],
                         TemplateLgV2_P.u_205_XData, 10U);

    /* Lookup Block: '<S178>/u_2 < -0.1 && u_2 >= -0.2'
     * About '<S178>/u_2 < -0.1 && u_2 >= -0.2 :'
     * Lookup Block: '<S178>/u_2 < -0.1 && u_2 >= -0.2'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateLgV2_B.u_201u_202),
                         TemplateLgV2_P.u_201u_202_YData,
                         TemplateLgV2_B.Saturation_bg[1],
                         TemplateLgV2_P.u_201u_202_XData, 2U);

    /* Lookup Block: '<S178>/u_2 => 0'
     * About '<S178>/u_2 => 0 :'
     * Lookup Block: '<S178>/u_2 => 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateLgV2_B.u_20), TemplateLgV2_P.u_20_YData,
                         TemplateLgV2_B.Saturation_bg[1],
                         TemplateLgV2_P.u_20_XData, 17U);

    /* MultiPortSwitch: '<S178>/Multiport Switch' */
    switch ((int32_T)((uint32_T)(int32_T)TemplateLgV2_B.Sum_fk >> 6)) {
     case 1:
      TemplateLgV2_B.MultiportSwitch_c = TemplateLgV2_B.u_205;
      break;

     case 2:
      TemplateLgV2_B.MultiportSwitch_c = TemplateLgV2_B.u_201u_202;
      break;

     default:
      TemplateLgV2_B.MultiportSwitch_c = TemplateLgV2_B.u_20;
      break;
    }

    /* Lookup Block: '<S179>/u_3 to f_3'
     * About '<S179>/u_3 to f_3 :'
     * Lookup Block: '<S179>/u_3 to f_3'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateLgV2_B.u_3tof_3_c),
                         TemplateLgV2_P.u_3tof_3_YData_m,
                         TemplateLgV2_B.Saturation_bg[2],
                         TemplateLgV2_P.u_3tof_3_XData_p, 38U);

    /* RelationalOperator: '<S186>/Compare' incorporates:
     *  Constant: '<S186>/Constant'
     */
    TemplateLgV2_B.Compare_eu = (TemplateLgV2_B.Saturation_bg[3] <
      TemplateLgV2_P.Constant_Value_fc);

    /* RelationalOperator: '<S187>/Compare' incorporates:
     *  Constant: '<S187>/Constant'
     */
    TemplateLgV2_B.Compare_h3 = (TemplateLgV2_B.Saturation_bg[3] >=
      TemplateLgV2_P.Constant_Value_le);

    /* Gain: '<S180>/Gain' */
    TemplateLgV2_B.Gain_pn = (uint16_T)(TemplateLgV2_P.Gain_Gain_cs *
      TemplateLgV2_B.Compare_h3);

    /* Sum: '<S180>/Sum' */
    TemplateLgV2_B.Sum_fl = (uint16_T)(uint32_T)((TemplateLgV2_B.Compare_eu << 6)
      + TemplateLgV2_B.Gain_pn);

    /* Lookup Block: '<S180>/u_4 < -0.1'
     * About '<S180>/u_4 < -0.1 :'
     * Lookup Block: '<S180>/u_4 < -0.1'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateLgV2_B.u_401), TemplateLgV2_P.u_401_YData,
                         TemplateLgV2_B.Saturation_bg[3],
                         TemplateLgV2_P.u_401_XData, 14U);

    /* Lookup Block: '<S180>/u_4 >= -0.1'
     * About '<S180>/u_4 >= -0.1 :'
     * Lookup Block: '<S180>/u_4 >= -0.1'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateLgV2_B.u_401_o),
                         TemplateLgV2_P.u_401_YData_p,
                         TemplateLgV2_B.Saturation_bg[3],
                         TemplateLgV2_P.u_401_XData_g, 12U);

    /* MultiPortSwitch: '<S180>/Multiport Switch' */
    if ((int32_T)((uint32_T)(int32_T)TemplateLgV2_B.Sum_fl >> 6) == 1) {
      TemplateLgV2_B.MultiportSwitch_g = TemplateLgV2_B.u_401;
    } else {
      TemplateLgV2_B.MultiportSwitch_g = TemplateLgV2_B.u_401_o;
    }

    /* DeadZone Block: '<S181>/Dead Zone +-0.01'
     */
    if (TemplateLgV2_B.Saturation_bg[4] >= TemplateLgV2_P.DeadZone001_End_n) {
      TemplateLgV2_B.DeadZone001_b = TemplateLgV2_B.Saturation_bg[4] -
        TemplateLgV2_P.DeadZone001_End_n;
    } else if (TemplateLgV2_B.Saturation_bg[4] >
               TemplateLgV2_P.DeadZone001_Start_a) {
      TemplateLgV2_B.DeadZone001_b = 0.0;
    } else {
      TemplateLgV2_B.DeadZone001_b = TemplateLgV2_B.Saturation_bg[4] -
        TemplateLgV2_P.DeadZone001_Start_a;
    }

    /* RelationalOperator: '<S188>/Compare' incorporates:
     *  Constant: '<S188>/Constant'
     */
    TemplateLgV2_B.Compare_ib = (TemplateLgV2_B.DeadZone001_b <
      TemplateLgV2_P.Constant_Value_jz);

    /* RelationalOperator: '<S190>/Compare' */
    TemplateLgV2_B.Compare_c4 = (TemplateLgV2_B.DeadZone001_b == 0.0);

    /* Gain: '<S181>/Gain' */
    TemplateLgV2_B.Gain_pf = (uint16_T)(TemplateLgV2_P.Gain_Gain_j *
      TemplateLgV2_B.Compare_c4);

    /* RelationalOperator: '<S189>/Compare' incorporates:
     *  Constant: '<S189>/Constant'
     */
    TemplateLgV2_B.Compare_l = (TemplateLgV2_B.DeadZone001_b >
      TemplateLgV2_P.Constant_Value_am);

    /* Gain: '<S181>/Gain1' */
    TemplateLgV2_B.Gain1_m = (uint16_T)(TemplateLgV2_P.Gain1_Gain_pu *
      TemplateLgV2_B.Compare_l);

    /* Sum: '<S181>/Sum' */
    TemplateLgV2_B.Sum_dx = (uint16_T)(uint32_T)(((TemplateLgV2_B.Compare_ib <<
      6) + TemplateLgV2_B.Gain_pf) + TemplateLgV2_B.Gain1_m);

    /* Lookup Block: '<S181>/u_5 < 0'
     * About '<S181>/u_5 < 0 :'
     * Lookup Block: '<S181>/u_5 < 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateLgV2_B.u_50), TemplateLgV2_P.u_50_YData,
                         TemplateLgV2_B.Saturation_bg[4],
                         TemplateLgV2_P.u_50_XData, 9U);

    /* Lookup Block: '<S181>/u_5 > 0'
     * About '<S181>/u_5 > 0 :'
     * Lookup Block: '<S181>/u_5 > 0'
     * Input0  Data Type:  Floating Point real_T
     * Output0 Data Type:  Floating Point real_T
     * Lookup Method: Linear_Endpoint
     *
     * XData parameter uses the same data type and scaling as Input0
     * YData parameter uses the same data type and scaling as Output0


     */
    LookUp_real_T_real_T( &(TemplateLgV2_B.u_50_f), TemplateLgV2_P.u_50_YData_g,
                         TemplateLgV2_B.Saturation_bg[4],
                         TemplateLgV2_P.u_50_XData_i, 9U);

    /* MultiPortSwitch: '<S181>/Multiport Switch' incorporates:
     *  Constant: '<S181>/u_5 = 0'
     */
    switch ((int32_T)((uint32_T)(int32_T)TemplateLgV2_B.Sum_dx >> 6)) {
     case 1:
      TemplateLgV2_B.MultiportSwitch_m = TemplateLgV2_B.u_50;
      break;

     case 2:
      TemplateLgV2_B.MultiportSwitch_m = TemplateLgV2_P.u_50_Value;
      break;

     default:
      TemplateLgV2_B.MultiportSwitch_m = TemplateLgV2_B.u_50_f;
      break;
    }

    /* SignalConversion: '<S170>/TmpHiddenBufferAtProduct1Inport2' */
    TemplateLgV2_B.TmpHiddenBufferAtProduct1Inport[0] =
      TemplateLgV2_B.u_1tof_1_l;
    TemplateLgV2_B.TmpHiddenBufferAtProduct1Inport[1] =
      TemplateLgV2_B.MultiportSwitch_c;
    TemplateLgV2_B.TmpHiddenBufferAtProduct1Inport[2] =
      TemplateLgV2_B.u_3tof_3_c;
    TemplateLgV2_B.TmpHiddenBufferAtProduct1Inport[3] =
      TemplateLgV2_B.MultiportSwitch_g;
    TemplateLgV2_B.TmpHiddenBufferAtProduct1Inport[4] =
      TemplateLgV2_B.MultiportSwitch_m;

    /* Sum: '<S169>/Sum1' */
    for (i = 0; i < 3; i++) {
      /* Product: '<S170>/Product1' */
      TemplateLgV2_B.Product1_h0[i] = 0.0;
      for (tmp_6 = 0; tmp_6 < 5; tmp_6++) {
        TemplateLgV2_B.Product1_h0[i] = TemplateLgV2_B.x5[3 * tmp_6 + i] *
          TemplateLgV2_B.TmpHiddenBufferAtProduct1Inport[tmp_6] +
          TemplateLgV2_B.Product1_h0[i];
      }

      /* Product: '<S169>/Product1' */
      TemplateLgV2_B.Product1_gb[i] = 0.0;
      TemplateLgV2_B.Product1_gb[i] = TemplateLgV2_B.LinearDampningmatrix[i] *
        TemplateLgV2_B.nu[0] + TemplateLgV2_B.Product1_gb[i];
      TemplateLgV2_B.Product1_gb[i] = TemplateLgV2_B.LinearDampningmatrix[i + 3]
        * TemplateLgV2_B.nu[1] + TemplateLgV2_B.Product1_gb[i];
      TemplateLgV2_B.Product1_gb[i] = TemplateLgV2_B.LinearDampningmatrix[i + 6]
        * TemplateLgV2_B.nu[2] + TemplateLgV2_B.Product1_gb[i];
    }

    TemplateLgV2_B.Sum1_ab[0] = TemplateLgV2_B.Row1_a +
      TemplateLgV2_B.Product1_h0[0];
    TemplateLgV2_B.Sum1_ab[1] = TemplateLgV2_B.Row2_c +
      TemplateLgV2_B.Product1_h0[1];
    TemplateLgV2_B.Sum1_ab[2] = TemplateLgV2_B.Row3_j +
      TemplateLgV2_B.Product1_h0[2];

    /* Sum: '<S169>/Sum8' */
    TemplateLgV2_B.Sum8[0] = (TemplateLgV2_B.Row1_b + TemplateLgV2_B.Sum1_ab[0])
      - TemplateLgV2_B.Product1_gb[0];
    TemplateLgV2_B.Sum8[1] = (TemplateLgV2_B.Row2_k + TemplateLgV2_B.Sum1_ab[1])
      - TemplateLgV2_B.Product1_gb[1];
    TemplateLgV2_B.Sum8[2] = (TemplateLgV2_B.Row3_m + TemplateLgV2_B.Sum1_ab[2])
      - TemplateLgV2_B.Product1_gb[2];

    /* Fcn: '<S171>/Fcn' */
    TemplateLgV2_B.x_dot = cos(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.nu[0] -
      sin(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.nu[1];

    /* Fcn: '<S171>/Fcn1' */
    TemplateLgV2_B.y_dot = sin(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.nu[0] +
      cos(TemplateLgV2_B.d2ryaw) * TemplateLgV2_B.nu[1];

    /* Fcn: '<S171>/Fcn2' */
    TemplateLgV2_B.psi_dot = TemplateLgV2_B.nu[2];

    /* Sum: '<S169>/Sum3' */
    TemplateLgV2_B.Sum3_c[0] = TemplateLgV2_B.K2[0] + TemplateLgV2_B.x_dot;
    TemplateLgV2_B.Sum3_c[1] = TemplateLgV2_B.K2[1] + TemplateLgV2_B.y_dot;
    TemplateLgV2_B.Sum3_c[2] = TemplateLgV2_B.K2[2] + TemplateLgV2_B.psi_dot;
    for (i = 0; i < 3; i++) {
      /* Product: '<S169>/Product' */
      TemplateLgV2_B.Product_o2[i] = 0.0;
      TemplateLgV2_B.Product_o2[i] = TemplateLgV2_B.Inverse[i] *
        TemplateLgV2_B.Sum8[0] + TemplateLgV2_B.Product_o2[i];
      TemplateLgV2_B.Product_o2[i] = TemplateLgV2_B.Inverse[i + 3] *
        TemplateLgV2_B.Sum8[1] + TemplateLgV2_B.Product_o2[i];
      TemplateLgV2_B.Product_o2[i] = TemplateLgV2_B.Inverse[i + 6] *
        TemplateLgV2_B.Sum8[2] + TemplateLgV2_B.Product_o2[i];

      /* Gain: '<S169>/inv(T_b)' */
      TemplateLgV2_B.invT_b[i] = 0.0;
      TemplateLgV2_B.invT_b[i] = TemplateLgV2_P.invT_b_Gain[i] *
        TemplateLgV2_B.bias[0] + TemplateLgV2_B.invT_b[i];
      TemplateLgV2_B.invT_b[i] = TemplateLgV2_P.invT_b_Gain[i + 3] *
        TemplateLgV2_B.bias[1] + TemplateLgV2_B.invT_b[i];
      TemplateLgV2_B.invT_b[i] = TemplateLgV2_P.invT_b_Gain[i + 6] *
        TemplateLgV2_B.bias[2] + TemplateLgV2_B.invT_b[i];

      /* Sum: '<S169>/Sum7' */
      TemplateLgV2_B.Sum7[i] = TemplateLgV2_B.K3[i] - TemplateLgV2_B.invT_b[i];
    }

    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
    }

    /* Outputs for enable SubSystem: '<S25>/CSE1 actuator' incorporates:
     *  Constant: '<S1>/Enable CSE1'
     *  EnablePort: '<S191>/Enable'
     */
    if (rtmIsMajorTimeStep(TemplateLgV2_M) && rtmIsMajorTimeStep(TemplateLgV2_M))
    {
      if (TemplateLgV2_P.EnableCSE1_Value > 0.0) {
        if (TemplateLgV2_DWork.CSE1actuator_MODE == SUBSYS_DISABLED) {
          TemplateLgV2_DWork.CSE1actuator_MODE = SUBSYS_ENABLED;
        }
      } else {
        if (TemplateLgV2_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
          TemplateLgV2_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;
        }
      }
    }

    if (TemplateLgV2_DWork.CSE1actuator_MODE == SUBSYS_ENABLED) {
      /* Gain: '<S195>/BT_D_Gain1' */
      TemplateLgV2_B.BT_D_Gain1 = TemplateLgV2_P.BT_D_Gain1_Gain *
        TemplateLgV2_B.tauSwitch_j[4];

      /* Gain: '<S195>/BT_D_Gain2' */
      TemplateLgV2_B.BT_D_Gain2 = TemplateLgV2_P.BT_D_Gain2_Gain *
        TemplateLgV2_B.tauSwitch_j[4];

      /* Sum: '<S195>/Add' incorporates:
       *  Constant: '<S195>/BT_Power_Offset1'
       */
      TemplateLgV2_B.Add_a1 = (TemplateLgV2_B.BT_D_Gain1 +
        TemplateLgV2_P.BT_Power_Offset1_Value) + TemplateLgV2_B.BT_D_Gain2;

      /* Gain: '<S195>/BT_L_Gain1' */
      TemplateLgV2_B.BT_L_Gain1 = TemplateLgV2_P.BT_L_Gain1_Gain *
        TemplateLgV2_B.tauSwitch_j[5];

      /* Gain: '<S195>/BT_L_Gain2' */
      TemplateLgV2_B.BT_L_Gain2 = TemplateLgV2_P.BT_L_Gain2_Gain *
        TemplateLgV2_B.tauSwitch_j[5];

      /* Gain: '<S195>/Neg' */
      TemplateLgV2_B.Neg = TemplateLgV2_P.Neg_Gain * TemplateLgV2_B.tauSwitch_j
        [5];
      if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      }

      /* Sum: '<S195>/Sum1' incorporates:
       *  Constant: '<S195>/BT_Power_Offset2'
       */
      TemplateLgV2_B.Sum1_g4 = TemplateLgV2_B.BT_L_Gain1 +
        TemplateLgV2_P.BT_Power_Offset2_Value;

      /* RelationalOperator: '<S197>/LowerRelop1' */
      TemplateLgV2_B.LowerRelop1_m = (TemplateLgV2_B.Add_a1 >
        TemplateLgV2_B.Sum1_g4);

      /* Sum: '<S195>/Sum2' incorporates:
       *  Constant: '<S195>/BT_Power_Offset3'
       */
      TemplateLgV2_B.Sum2_n = TemplateLgV2_B.BT_L_Gain2 +
        TemplateLgV2_P.BT_Power_Offset3_Value;

      /* RelationalOperator: '<S197>/UpperRelop' */
      TemplateLgV2_B.UpperRelop_l = (TemplateLgV2_B.Add_a1 <
        TemplateLgV2_B.Sum2_n);

      /* Switch: '<S197>/Switch' */
      if (TemplateLgV2_B.UpperRelop_l) {
        TemplateLgV2_B.Switch_l = TemplateLgV2_B.Sum2_n;
      } else {
        TemplateLgV2_B.Switch_l = TemplateLgV2_B.Add_a1;
      }

      /* Switch: '<S197>/Switch2' */
      if (TemplateLgV2_B.LowerRelop1_m) {
        TemplateLgV2_B.Switch2_p = TemplateLgV2_B.Sum1_g4;
      } else {
        TemplateLgV2_B.Switch2_p = TemplateLgV2_B.Switch_l;
      }

      if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      }

      /* RelationalOperator: '<S198>/LowerRelop1' incorporates:
       *  Constant: '<S195>/Constant'
       */
      TemplateLgV2_B.LowerRelop1_mk = (TemplateLgV2_B.tauSwitch_j[4] >
        TemplateLgV2_P.Constant_Value_ol);

      /* RelationalOperator: '<S198>/UpperRelop' */
      TemplateLgV2_B.UpperRelop_n = (TemplateLgV2_B.tauSwitch_j[4] <
        TemplateLgV2_B.Neg);

      /* Switch: '<S198>/Switch' */
      if (TemplateLgV2_B.UpperRelop_n) {
        TemplateLgV2_B.Switch_h = TemplateLgV2_B.Neg;
      } else {
        TemplateLgV2_B.Switch_h = TemplateLgV2_B.tauSwitch_j[4];
      }

      /* Switch: '<S198>/Switch2' incorporates:
       *  Constant: '<S195>/Constant'
       */
      if (TemplateLgV2_B.LowerRelop1_mk) {
        TemplateLgV2_B.Switch2_o = TemplateLgV2_P.Constant_Value_ol;
      } else {
        TemplateLgV2_B.Switch2_o = TemplateLgV2_B.Switch_h;
      }

      if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      }

      /* RelationalOperator: '<S199>/LowerRelop1' */
      TemplateLgV2_B.LowerRelop1_d = (TemplateLgV2_B.tauSwitch_j[4] >
        TemplateLgV2_B.tauSwitch_j[5]);

      /* RelationalOperator: '<S199>/UpperRelop' incorporates:
       *  Constant: '<S195>/Constant1'
       */
      TemplateLgV2_B.UpperRelop_o = (TemplateLgV2_B.tauSwitch_j[4] <
        TemplateLgV2_P.Constant1_Value_l);

      /* Switch: '<S199>/Switch' incorporates:
       *  Constant: '<S195>/Constant1'
       */
      if (TemplateLgV2_B.UpperRelop_o) {
        TemplateLgV2_B.Switch_a = TemplateLgV2_P.Constant1_Value_l;
      } else {
        TemplateLgV2_B.Switch_a = TemplateLgV2_B.tauSwitch_j[4];
      }

      /* Switch: '<S199>/Switch2' */
      if (TemplateLgV2_B.LowerRelop1_d) {
        TemplateLgV2_B.Switch2_n = TemplateLgV2_B.tauSwitch_j[5];
      } else {
        TemplateLgV2_B.Switch2_n = TemplateLgV2_B.Switch_a;
      }

      /* Signum: '<S196>/Sign' */
      TemplateLgV2_B.Sign_c = rt_SIGNd_snf(TemplateLgV2_B.tauSwitch_j[6]);

      /* Product: '<S196>/Product1' */
      TemplateLgV2_B.PortVPS_X = TemplateLgV2_B.tauSwitch_j[1] *
        TemplateLgV2_B.Sign_c;

      /* Gain: '<S196>/-x' */
      TemplateLgV2_B.PortVPS_X_o = TemplateLgV2_P.x_Gain *
        TemplateLgV2_B.PortVPS_X;

      /* Product: '<S196>/Product2' */
      TemplateLgV2_B.PortVSP_Y = TemplateLgV2_B.tauSwitch_j[0] *
        TemplateLgV2_B.Sign_c;

      /* Gain: '<S196>/-y' */
      TemplateLgV2_B.PortVSP_Y_f = TemplateLgV2_P.y_Gain *
        TemplateLgV2_B.PortVSP_Y;

      /* Product: '<S196>/Product3' */
      TemplateLgV2_B.StarboardVSP_X = TemplateLgV2_B.tauSwitch_j[3] *
        TemplateLgV2_B.Sign_c;

      /* Product: '<S196>/Product4' */
      TemplateLgV2_B.StarboardVSP_Y = TemplateLgV2_B.tauSwitch_j[2] *
        TemplateLgV2_B.Sign_c;

      /* Lookup2D: '<S196>/Servo1' */
      TemplateLgV2_B.Servo1 = rt_Lookup2D_Normal((const real_T *)
        (&TemplateLgV2_P.Servo1_RowIdx[0]), 3, (const real_T *)
        (&TemplateLgV2_P.Servo1_ColIdx[0]), 3, (const real_T *)
        (&TemplateLgV2_P.Servo1_Table[0]), (const real_T)
        TemplateLgV2_B.PortVPS_X_o, (const real_T)TemplateLgV2_B.PortVSP_Y_f);

      /* Lookup2D: '<S196>/Servo2' */
      TemplateLgV2_B.Servo2 = rt_Lookup2D_Normal((const real_T *)
        (&TemplateLgV2_P.Servo2_RowIdx[0]), 3, (const real_T *)
        (&TemplateLgV2_P.Servo2_ColIdx[0]), 3, (const real_T *)
        (&TemplateLgV2_P.Servo2_Table[0]), (const real_T)
        TemplateLgV2_B.PortVPS_X_o, (const real_T)TemplateLgV2_B.PortVSP_Y_f);

      /* Lookup2D: '<S196>/Servo3' */
      TemplateLgV2_B.Servo3 = rt_Lookup2D_Normal((const real_T *)
        (&TemplateLgV2_P.Servo3_RowIdx[0]), 3, (const real_T *)
        (&TemplateLgV2_P.Servo3_ColIdx[0]), 3, (const real_T *)
        (&TemplateLgV2_P.Servo3_Table[0]), (const real_T)
        TemplateLgV2_B.StarboardVSP_X, (const real_T)
        TemplateLgV2_B.StarboardVSP_Y);

      /* Lookup2D: '<S196>/Servo4' */
      TemplateLgV2_B.Servo4 = rt_Lookup2D_Normal((const real_T *)
        (&TemplateLgV2_P.Servo4_RowIdx[0]), 3, (const real_T *)
        (&TemplateLgV2_P.Servo4_ColIdx[0]), 3, (const real_T *)
        (&TemplateLgV2_P.Servo4_Table[0]), (const real_T)
        TemplateLgV2_B.StarboardVSP_X, (const real_T)
        TemplateLgV2_B.StarboardVSP_Y);

      /* Gain: '<S196>/VPS_Speed_Gain' */
      TemplateLgV2_B.VPS_Speed_Gain = TemplateLgV2_P.VPS_Speed_Gain_Gain *
        TemplateLgV2_B.tauSwitch_j[6];

      /* Sum: '<S196>/Sum' incorporates:
       *  Constant: '<S196>/VPS_Power_Offset'
       */
      TemplateLgV2_B.Sum_ie = TemplateLgV2_B.VPS_Speed_Gain +
        TemplateLgV2_P.VPS_Power_Offset_Value;

      /* Gain: '<S196>/VSPS Port' */
      TemplateLgV2_B.VSPSPort = TemplateLgV2_P.VSPSPort_Gain *
        TemplateLgV2_B.Sum_ie;

      /* Gain: '<S196>/VSPS Starboard' */
      TemplateLgV2_B.VSPSStarboard = TemplateLgV2_P.VSPSStarboard_Gain *
        TemplateLgV2_B.Sum_ie;
    }

    /* end of Outputs for SubSystem: '<S25>/CSE1 actuator' */
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Product Block: '<S25>/Inverse' */
      {
        static const int_T dims[3] = { 3, 3, 3 };

        rt_MatDivRR_Dbl(TemplateLgV2_B.Inverse_e, TemplateLgV2_B.x3,
                        &TemplateLgV2_DWork.Inverse_DWORK4_e[0], (real_T*)
                        &TemplateLgV2_DWork.Pseudoinverse_X[0],
                        &TemplateLgV2_DWork.Inverse_DWORK2[0], (real_T*)
                        &TemplateLgV2_DWork.Inverse_DWORK3[0],
                        &dims[0]);
      }
    }

    /* Saturate: '<S194>/Saturation' */
    tmp = TemplateLgV2_B.tauSwitch[0];
    TemplateLgV2_B.Saturation_o = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation_LowerSat_im,
      TemplateLgV2_P.Saturation_UpperSat_il);

    /* Saturate: '<S194>/Saturation1' */
    tmp = TemplateLgV2_B.tauSwitch[1];
    TemplateLgV2_B.Saturation1 = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation1_LowerSat, TemplateLgV2_P.Saturation1_UpperSat);

    /* Saturate: '<S194>/Saturation2' */
    tmp = TemplateLgV2_B.tauSwitch[2];
    TemplateLgV2_B.Saturation2 = rt_SATURATE(tmp,
      TemplateLgV2_P.Saturation2_LowerSat, TemplateLgV2_P.Saturation2_UpperSat);

    /* Gain: '<S194>/plant tau_surge' */
    TemplateLgV2_B.planttau_surge = TemplateLgV2_P.planttau_surge_Gain *
      TemplateLgV2_B.Saturation_o;

    /* Gain: '<S194>/plant tau_sway' */
    TemplateLgV2_B.planttau_sway = TemplateLgV2_P.planttau_sway_Gain *
      TemplateLgV2_B.Saturation1;

    /* Gain: '<S194>/plant tau_yaw' */
    TemplateLgV2_B.planttau_yaw = TemplateLgV2_P.planttau_yaw_Gain *
      TemplateLgV2_B.Saturation2;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
      /* Gain: '<S202>/Battery Bow Thruster' */
      TemplateLgV2_B.BatteryBowThruster = TemplateLgV2_P.BatteryBowThruster_Gain
        * TemplateLgV2_B.SITzAI0;

      /* Gain: '<S202>/Battery Main' */
      TemplateLgV2_B.BatteryMain = TemplateLgV2_P.BatteryMain_Gain *
        TemplateLgV2_B.SITzAI2;

      /* Gain: '<S202>/Battery Servo' */
      TemplateLgV2_B.BatteryServo = TemplateLgV2_P.BatteryServo_Gain *
        TemplateLgV2_B.SITzAI1;
    }

    /* Gain: '<S203>/plant BT power' */
    TemplateLgV2_B.plantBTpower = TemplateLgV2_P.plantBTpower_Gain *
      TemplateLgV2_B.tauSwitch_j[5];

    /* Gain: '<S203>/plant VSP speed' */
    TemplateLgV2_B.plantVSPspeed = TemplateLgV2_P.plantVSPspeed_Gain *
      TemplateLgV2_B.tauSwitch_j[6];

    /* Gain: '<S203>/plant u_1' */
    TemplateLgV2_B.plantu_1 = TemplateLgV2_P.plantu_1_Gain *
      TemplateLgV2_B.tauSwitch_j[0];

    /* Gain: '<S203>/plant u_2' */
    TemplateLgV2_B.plantu_2 = TemplateLgV2_P.plantu_2_Gain *
      TemplateLgV2_B.tauSwitch_j[1];

    /* Gain: '<S203>/plant u_3' */
    TemplateLgV2_B.plantu_3 = TemplateLgV2_P.plantu_3_Gain *
      TemplateLgV2_B.tauSwitch_j[2];

    /* Gain: '<S203>/plant u_4' */
    TemplateLgV2_B.plantu_4 = TemplateLgV2_P.plantu_4_Gain *
      TemplateLgV2_B.tauSwitch_j[3];

    /* Gain: '<S203>/plant u_5' */
    TemplateLgV2_B.plantu_5 = TemplateLgV2_P.plantu_5_Gain *
      TemplateLgV2_B.tauSwitch_j[4];

    /* Gain: '<S203>/fact1' */
    TemplateLgV2_B.fact1 = TemplateLgV2_P.fact1_Gain *
      TemplateLgV2_B.Product_gz[0];

    /* Gain: '<S203>/fact2' */
    TemplateLgV2_B.fact2 = TemplateLgV2_P.fact2_Gain *
      TemplateLgV2_B.Product_gz[1];

    /* Gain: '<S203>/fact3' */
    TemplateLgV2_B.fact3 = TemplateLgV2_P.fact3_Gain *
      TemplateLgV2_B.Product_gz[2];

    /* Gain: '<S203>/fact4' */
    TemplateLgV2_B.fact4 = TemplateLgV2_P.fact4_Gain *
      TemplateLgV2_B.Product_gz[3];

    /* Gain: '<S203>/fact5' */
    TemplateLgV2_B.fact5 = TemplateLgV2_P.fact5_Gain *
      TemplateLgV2_B.Product_gz[4];

    /* Gain: '<S203>/taux' */
    TemplateLgV2_B.taux = TemplateLgV2_P.taux_Gain * TemplateLgV2_B.tauSwitch[0];

    /* Gain: '<S203>/tauy' */
    TemplateLgV2_B.tauy = TemplateLgV2_P.tauy_Gain * TemplateLgV2_B.tauSwitch[1];

    /* Gain: '<S203>/tauyaw' */
    TemplateLgV2_B.tauyaw = TemplateLgV2_P.tauyaw_Gain *
      TemplateLgV2_B.tauSwitch[2];

    /* Gain: '<S203>/omega_qy' */
    TemplateLgV2_B.omega_qy = TemplateLgV2_P.omega_qy_Gain *
      TemplateLgV2_B.Integrator2[1];

    /* Gain: '<S203>/omegaqx' */
    TemplateLgV2_B.omegaqx = TemplateLgV2_P.omegaqx_Gain *
      TemplateLgV2_B.Integrator2[0];

    /* Gain: '<S204>/CSE1_r [deg//s]' */
    TemplateLgV2_B.CSE1_rdegs = TemplateLgV2_P.CSE1_rdegs_Gain *
      TemplateLgV2_B.nuSwitch[2];

    /* Gain: '<S204>/CSE1_u [m//s]' */
    TemplateLgV2_B.CSE1_ums = TemplateLgV2_P.CSE1_ums_Gain *
      TemplateLgV2_B.nuSwitch[0];

    /* Gain: '<S204>/CSE1_v [m//s]' */
    TemplateLgV2_B.CSE1_vms = TemplateLgV2_P.CSE1_vms_Gain *
      TemplateLgV2_B.nuSwitch[1];

    /* Gain: '<S204>/QS Error' */
    TemplateLgV2_B.QSError = TemplateLgV2_P.QSError_Gain *
      TemplateLgV2_B.QTMIn2Error;

    /* Gain: '<S204>/QS Frame' */
    TemplateLgV2_B.QSFrame = TemplateLgV2_P.QSFrame_Gain *
      TemplateLgV2_B.QTMIn1FN;

    /* Sum: '<S205>/Sum' */
    TemplateLgV2_B.Sum_j[0] = TemplateLgV2_B.etaSwitch[0] -
      TemplateLgV2_B.Switch2;
    TemplateLgV2_B.Sum_j[1] = TemplateLgV2_B.etaSwitch[1] -
      TemplateLgV2_B.Switch2_i;
    TemplateLgV2_B.Sum_j[2] = TemplateLgV2_B.etaSwitch[2] - TemplateLgV2_B.Sum_g;

    /* Sum: '<S205>/Sum1' */
    TemplateLgV2_B.Sum1_m2[0] = TemplateLgV2_B.VectorConcatenate[0] -
      TemplateLgV2_B.Switch2;
    TemplateLgV2_B.Sum1_m2[1] = TemplateLgV2_B.VectorConcatenate[1] -
      TemplateLgV2_B.Switch2_i;
    TemplateLgV2_B.Sum1_m2[2] = TemplateLgV2_B.VectorConcatenate[2] -
      TemplateLgV2_B.Sum_g;

    /* Gain: '<S203>/tau1' */
    TemplateLgV2_B.tau1[0] = TemplateLgV2_P.tau1_Gain * TemplateLgV2_B.Gain_d[0];

    /* Gain: '<S203>/tau2' */
    TemplateLgV2_B.tau2[0] = TemplateLgV2_P.tau2_Gain * TemplateLgV2_B.Gain1_k[0];

    /* Gain: '<S203>/tau3' */
    TemplateLgV2_B.tau3[0] = TemplateLgV2_P.tau3_Gain *
      TemplateLgV2_B.Product2_d[0];

    /* Gain: '<S203>/tau4' */
    TemplateLgV2_B.tau4[0] = TemplateLgV2_P.tau4_Gain *
      TemplateLgV2_B.Product4_d[0];

    /* Gain: '<S203>/tau5' */
    TemplateLgV2_B.tau5[0] = TemplateLgV2_P.tau5_Gain * TemplateLgV2_B.Product5
      [0];

    /* Gain: '<S203>/tau6' */
    TemplateLgV2_B.tau6[0] = TemplateLgV2_P.tau6_Gain * TemplateLgV2_B.Product6
      [0];

    /* Sum: '<S205>/Sum2' */
    TemplateLgV2_B.Sum2_c[0] = TemplateLgV2_B.VectorConcatenate[0] -
      TemplateLgV2_B.etaSwitch[0];

    /* Gain: '<S203>/tau1' */
    TemplateLgV2_B.tau1[1] = TemplateLgV2_P.tau1_Gain * TemplateLgV2_B.Gain_d[1];

    /* Gain: '<S203>/tau2' */
    TemplateLgV2_B.tau2[1] = TemplateLgV2_P.tau2_Gain * TemplateLgV2_B.Gain1_k[1];

    /* Gain: '<S203>/tau3' */
    TemplateLgV2_B.tau3[1] = TemplateLgV2_P.tau3_Gain *
      TemplateLgV2_B.Product2_d[1];

    /* Gain: '<S203>/tau4' */
    TemplateLgV2_B.tau4[1] = TemplateLgV2_P.tau4_Gain *
      TemplateLgV2_B.Product4_d[1];

    /* Gain: '<S203>/tau5' */
    TemplateLgV2_B.tau5[1] = TemplateLgV2_P.tau5_Gain * TemplateLgV2_B.Product5
      [1];

    /* Gain: '<S203>/tau6' */
    TemplateLgV2_B.tau6[1] = TemplateLgV2_P.tau6_Gain * TemplateLgV2_B.Product6
      [1];

    /* Sum: '<S205>/Sum2' */
    TemplateLgV2_B.Sum2_c[1] = TemplateLgV2_B.VectorConcatenate[1] -
      TemplateLgV2_B.etaSwitch[1];

    /* Gain: '<S203>/tau1' */
    TemplateLgV2_B.tau1[2] = TemplateLgV2_P.tau1_Gain * TemplateLgV2_B.Gain_d[2];

    /* Gain: '<S203>/tau2' */
    TemplateLgV2_B.tau2[2] = TemplateLgV2_P.tau2_Gain * TemplateLgV2_B.Gain1_k[2];

    /* Gain: '<S203>/tau3' */
    TemplateLgV2_B.tau3[2] = TemplateLgV2_P.tau3_Gain *
      TemplateLgV2_B.Product2_d[2];

    /* Gain: '<S203>/tau4' */
    TemplateLgV2_B.tau4[2] = TemplateLgV2_P.tau4_Gain *
      TemplateLgV2_B.Product4_d[2];

    /* Gain: '<S203>/tau5' */
    TemplateLgV2_B.tau5[2] = TemplateLgV2_P.tau5_Gain * TemplateLgV2_B.Product5
      [2];

    /* Gain: '<S203>/tau6' */
    TemplateLgV2_B.tau6[2] = TemplateLgV2_P.tau6_Gain * TemplateLgV2_B.Product6
      [2];

    /* Sum: '<S205>/Sum2' */
    TemplateLgV2_B.Sum2_c[2] = TemplateLgV2_B.VectorConcatenate[2] -
      TemplateLgV2_B.etaSwitch[2];

    /* Gain: '<S205>/psi [deg]' */
    TemplateLgV2_B.psideg = TemplateLgV2_P.psideg_Gain *
      TemplateLgV2_B.etaSwitch[2];

    /* Gain: '<S205>/psi-psid [deg]' */
    TemplateLgV2_B.psipsiddeg = TemplateLgV2_P.psipsiddeg_Gain *
      TemplateLgV2_B.Sum_j[2];

    /* Gain: '<S205>/psiLOS-psi [deg]' */
    TemplateLgV2_B.psiLOSpsideg = TemplateLgV2_P.psiLOSpsideg_Gain *
      TemplateLgV2_B.Sum2_c[2];

    /* Gain: '<S205>/psiLOS-psid [deg]' */
    TemplateLgV2_B.psiLOSpsiddeg = TemplateLgV2_P.psiLOSpsiddeg_Gain *
      TemplateLgV2_B.Sum1_m2[2];

    /* Gain: '<S205>/psi_LOS [deg]' */
    TemplateLgV2_B.psi_LOSdeg = TemplateLgV2_P.psi_LOSdeg_Gain *
      TemplateLgV2_B.VectorConcatenate[2];

    /* Gain: '<S205>/psid [deg]' */
    TemplateLgV2_B.psiddeg = TemplateLgV2_P.psiddeg_Gain * TemplateLgV2_B.Sum_g;

    /* Gain: '<S205>/psi_plot' */
    TemplateLgV2_B.psi_plot[0] = TemplateLgV2_P.psi_plot_Gain *
      TemplateLgV2_B.psideg;
    TemplateLgV2_B.psi_plot[1] = TemplateLgV2_P.psi_plot_Gain *
      TemplateLgV2_B.psi_LOSdeg;
    TemplateLgV2_B.psi_plot[2] = TemplateLgV2_P.psi_plot_Gain *
      TemplateLgV2_B.psiddeg;

    /* Gain: '<S205>/qx [m]' */
    TemplateLgV2_B.qxm = TemplateLgV2_P.qxm_Gain *
      TemplateLgV2_B.VectorConcatenate[0];

    /* Gain: '<S205>/qx-x [m]' */
    TemplateLgV2_B.qxxm = TemplateLgV2_P.qxxm_Gain * TemplateLgV2_B.Sum2_c[0];

    /* Gain: '<S205>/qx-xd [m]1' */
    TemplateLgV2_B.qxxdm1 = TemplateLgV2_P.qxxdm1_Gain * TemplateLgV2_B.Sum1_m2
      [0];

    /* Gain: '<S205>/qy [m]' */
    TemplateLgV2_B.qym = TemplateLgV2_P.qym_Gain *
      TemplateLgV2_B.VectorConcatenate[1];

    /* Gain: '<S205>/qy-y [m]' */
    TemplateLgV2_B.qyym = TemplateLgV2_P.qyym_Gain * TemplateLgV2_B.Sum2_c[1];

    /* Gain: '<S205>/qy-yd [m]1' */
    TemplateLgV2_B.qyydm1 = TemplateLgV2_P.qyydm1_Gain * TemplateLgV2_B.Sum1_m2
      [1];

    /* Gain: '<S205>/x [m]' */
    TemplateLgV2_B.xm = TemplateLgV2_P.xm_Gain * TemplateLgV2_B.etaSwitch[0];

    /* Gain: '<S205>/x-xd [m]' */
    TemplateLgV2_B.xxdm = TemplateLgV2_P.xxdm_Gain * TemplateLgV2_B.Sum_j[0];

    /* Gain: '<S205>/xd [m]' */
    TemplateLgV2_B.xdm = TemplateLgV2_P.xdm_Gain * TemplateLgV2_B.Switch2;

    /* Gain: '<S205>/x_plot' */
    TemplateLgV2_B.x_plot[0] = TemplateLgV2_P.x_plot_Gain * TemplateLgV2_B.xm;
    TemplateLgV2_B.x_plot[1] = TemplateLgV2_P.x_plot_Gain * TemplateLgV2_B.qxm;
    TemplateLgV2_B.x_plot[2] = TemplateLgV2_P.x_plot_Gain * TemplateLgV2_B.xdm;

    /* Gain: '<S205>/y [m]' */
    TemplateLgV2_B.ym = TemplateLgV2_P.ym_Gain * TemplateLgV2_B.etaSwitch[1];

    /* Gain: '<S205>/y-yd [m]' */
    TemplateLgV2_B.yydm = TemplateLgV2_P.yydm_Gain * TemplateLgV2_B.Sum_j[1];

    /* Gain: '<S205>/yd [m]' */
    TemplateLgV2_B.ydm = TemplateLgV2_P.ydm_Gain * TemplateLgV2_B.Switch2_i;

    /* Gain: '<S205>/y_plot' */
    TemplateLgV2_B.y_plot[0] = TemplateLgV2_P.y_plot_Gain * TemplateLgV2_B.ym;
    TemplateLgV2_B.y_plot[1] = TemplateLgV2_P.y_plot_Gain * TemplateLgV2_B.qym;
    TemplateLgV2_B.y_plot[2] = TemplateLgV2_P.y_plot_Gain * TemplateLgV2_B.ydm;

    /* Gain: '<S205>/splot' */
    TemplateLgV2_B.splot = TemplateLgV2_P.splot_Gain *
      TemplateLgV2_B.Integrator1;
    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void TemplateLgV2_update(int_T tid)
{
  {
    int32_T tmp;

    /* Update for enable SubSystem: '<S25>/Linear Simulator' incorporates:
     *  Update for EnablePort: '<S192>/Enable'
     */
    if (TemplateLgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S200>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        TemplateLgV2_B.Product1_fr[tmp] = 0.0;
        TemplateLgV2_B.Product1_fr[tmp] =
          TemplateLgV2_B.LinearDampningmatrix[tmp] *
          TemplateLgV2_B.Integrator_h[0] + TemplateLgV2_B.Product1_fr[tmp];
        TemplateLgV2_B.Product1_fr[tmp] =
          TemplateLgV2_B.LinearDampningmatrix[tmp + 3] *
          TemplateLgV2_B.Integrator_h[1] + TemplateLgV2_B.Product1_fr[tmp];
        TemplateLgV2_B.Product1_fr[tmp] =
          TemplateLgV2_B.LinearDampningmatrix[tmp + 6] *
          TemplateLgV2_B.Integrator_h[2] + TemplateLgV2_B.Product1_fr[tmp];
      }

      /* Sum: '<S200>/Sum' */
      TemplateLgV2_B.Sum_c[0] = TemplateLgV2_B.planttau_surge -
        TemplateLgV2_B.Product1_fr[0];
      TemplateLgV2_B.Sum_c[1] = TemplateLgV2_B.planttau_sway -
        TemplateLgV2_B.Product1_fr[1];
      TemplateLgV2_B.Sum_c[2] = TemplateLgV2_B.planttau_yaw -
        TemplateLgV2_B.Product1_fr[2];
      for (tmp = 0; tmp < 3; tmp++) {
        /* Product: '<S200>/Product2' */
        TemplateLgV2_B.Product2_o[tmp] = 0.0;
        TemplateLgV2_B.Product2_o[tmp] = TemplateLgV2_B.Inverse_e[tmp] *
          TemplateLgV2_B.Sum_c[0] + TemplateLgV2_B.Product2_o[tmp];
        TemplateLgV2_B.Product2_o[tmp] = TemplateLgV2_B.Inverse_e[tmp + 3] *
          TemplateLgV2_B.Sum_c[1] + TemplateLgV2_B.Product2_o[tmp];
        TemplateLgV2_B.Product2_o[tmp] = TemplateLgV2_B.Inverse_e[tmp + 6] *
          TemplateLgV2_B.Sum_c[2] + TemplateLgV2_B.Product2_o[tmp];

        /* Product: '<S200>/Product3' */
        TemplateLgV2_B.Product3_al[tmp] = 0.0;
        TemplateLgV2_B.Product3_al[tmp] = TemplateLgV2_B.Rpsi_k[tmp] *
          TemplateLgV2_B.Integrator_h[0] + TemplateLgV2_B.Product3_al[tmp];
        TemplateLgV2_B.Product3_al[tmp] = TemplateLgV2_B.Rpsi_k[tmp + 3] *
          TemplateLgV2_B.Integrator_h[1] + TemplateLgV2_B.Product3_al[tmp];
        TemplateLgV2_B.Product3_al[tmp] = TemplateLgV2_B.Rpsi_k[tmp + 6] *
          TemplateLgV2_B.Integrator_h[2] + TemplateLgV2_B.Product3_al[tmp];
      }
    }

    /* end of Update for SubSystem: '<S25>/Linear Simulator' */

    /* Derivative Block: '<S96>/Derivative' */
    {
      real_T timeStampA = TemplateLgV2_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = TemplateLgV2_DWork.Derivative_RWORK.TimeStampB;
      real_T *lastBank = &TemplateLgV2_DWork.Derivative_RWORK.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 2;
        } else if (timeStampA >= timeStampB) {
          lastBank += 2;
        }
      }

      *lastBank++ = TemplateLgV2_M->Timing.t[0];
      *lastBank++ = TemplateLgV2_P.u_dm_Value;
    }

    /* Derivative Block: '<S166>/Derivative' */
    {
      real_T timeStampA = TemplateLgV2_DWork.Derivative_RWORK_k.TimeStampA;
      real_T timeStampB = TemplateLgV2_DWork.Derivative_RWORK_k.TimeStampB;
      real_T *lastBank = &TemplateLgV2_DWork.Derivative_RWORK_k.TimeStampA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastBank += 7;
        } else if (timeStampA >= timeStampB) {
          lastBank += 7;
        }
      }

      *lastBank++ = TemplateLgV2_M->Timing.t[0];
      *lastBank++ = TemplateLgV2_B.mm2mx;
      *lastBank++ = TemplateLgV2_B.mm2my;
      *lastBank++ = TemplateLgV2_B.mm2mz;
      *lastBank++ = TemplateLgV2_B.d2rroll;
      *lastBank++ = TemplateLgV2_B.d2rpitch;
      *lastBank++ = TemplateLgV2_B.d2ryaw;
    }

    if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
    }
  }

  if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
    rt_ertODEUpdateContinuousStates(&TemplateLgV2_M->solverInfo);
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
  if (!(++TemplateLgV2_M->Timing.clockTick0))
    ++TemplateLgV2_M->Timing.clockTickH0;
  TemplateLgV2_M->Timing.t[0] = TemplateLgV2_M->Timing.clockTick0 *
    TemplateLgV2_M->Timing.stepSize0 + TemplateLgV2_M->Timing.clockTickH0 *
    TemplateLgV2_M->Timing.stepSize0 * 4294967296.0;
  if (rtmIsMajorTimeStep(TemplateLgV2_M)) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++TemplateLgV2_M->Timing.clockTick1))
      ++TemplateLgV2_M->Timing.clockTickH1;
    TemplateLgV2_M->Timing.t[1] = TemplateLgV2_M->Timing.clockTick1 *
      TemplateLgV2_M->Timing.stepSize1 + TemplateLgV2_M->Timing.clockTickH1 *
      TemplateLgV2_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void TemplateLgV2_derivatives(void)
{
  {
    int32_T tmp;

    /* Derivatives for enable SubSystem: '<S25>/Linear Simulator' */
    if (TemplateLgV2_DWork.LinearSimulator_MODE == SUBSYS_ENABLED) {
      /* Product: '<S200>/Product1' */
      for (tmp = 0; tmp < 3; tmp++) {
        TemplateLgV2_B.Product1_fr[tmp] = 0.0;
        TemplateLgV2_B.Product1_fr[tmp] =
          TemplateLgV2_B.LinearDampningmatrix[tmp] *
          TemplateLgV2_B.Integrator_h[0] + TemplateLgV2_B.Product1_fr[tmp];
        TemplateLgV2_B.Product1_fr[tmp] =
          TemplateLgV2_B.LinearDampningmatrix[tmp + 3] *
          TemplateLgV2_B.Integrator_h[1] + TemplateLgV2_B.Product1_fr[tmp];
        TemplateLgV2_B.Product1_fr[tmp] =
          TemplateLgV2_B.LinearDampningmatrix[tmp + 6] *
          TemplateLgV2_B.Integrator_h[2] + TemplateLgV2_B.Product1_fr[tmp];
      }

      /* Sum: '<S200>/Sum' */
      TemplateLgV2_B.Sum_c[0] = TemplateLgV2_B.planttau_surge -
        TemplateLgV2_B.Product1_fr[0];
      TemplateLgV2_B.Sum_c[1] = TemplateLgV2_B.planttau_sway -
        TemplateLgV2_B.Product1_fr[1];
      TemplateLgV2_B.Sum_c[2] = TemplateLgV2_B.planttau_yaw -
        TemplateLgV2_B.Product1_fr[2];
      for (tmp = 0; tmp < 3; tmp++) {
        /* Product: '<S200>/Product2' */
        TemplateLgV2_B.Product2_o[tmp] = 0.0;
        TemplateLgV2_B.Product2_o[tmp] = TemplateLgV2_B.Inverse_e[tmp] *
          TemplateLgV2_B.Sum_c[0] + TemplateLgV2_B.Product2_o[tmp];
        TemplateLgV2_B.Product2_o[tmp] = TemplateLgV2_B.Inverse_e[tmp + 3] *
          TemplateLgV2_B.Sum_c[1] + TemplateLgV2_B.Product2_o[tmp];
        TemplateLgV2_B.Product2_o[tmp] = TemplateLgV2_B.Inverse_e[tmp + 6] *
          TemplateLgV2_B.Sum_c[2] + TemplateLgV2_B.Product2_o[tmp];

        /* Product: '<S200>/Product3' */
        TemplateLgV2_B.Product3_al[tmp] = 0.0;
        TemplateLgV2_B.Product3_al[tmp] = TemplateLgV2_B.Rpsi_k[tmp] *
          TemplateLgV2_B.Integrator_h[0] + TemplateLgV2_B.Product3_al[tmp];
        TemplateLgV2_B.Product3_al[tmp] = TemplateLgV2_B.Rpsi_k[tmp + 3] *
          TemplateLgV2_B.Integrator_h[1] + TemplateLgV2_B.Product3_al[tmp];
        TemplateLgV2_B.Product3_al[tmp] = TemplateLgV2_B.Rpsi_k[tmp + 6] *
          TemplateLgV2_B.Integrator_h[2] + TemplateLgV2_B.Product3_al[tmp];
      }

      /* Integrator Block: '<S200>/Integrator' */
      {
        if (TemplateLgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_e[0] = TemplateLgV2_B.Product2_o[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_e[0] = 0.0;
        }

        if (TemplateLgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_e[1] = TemplateLgV2_B.Product2_o[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_e[1] = 0.0;
        }

        if (TemplateLgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_e[2] = TemplateLgV2_B.Product2_o[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator_CSTATE_e[2] = 0.0;
        }
      }

      /* Integrator Block: '<S200>/Integrator1' */
      {
        if (TemplateLgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_p[0] = TemplateLgV2_B.Product3_al[0];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_p[0] = 0.0;
        }

        if (TemplateLgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_p[1] = TemplateLgV2_B.Product3_al[1];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_p[1] = 0.0;
        }

        if (TemplateLgV2_P.ResetLinearSimulatorintegrator_== 0.0) {
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_p[2] = TemplateLgV2_B.Product3_al[2];
        } else {
          /* level reset is active*/
          ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
            ->Integrator1_CSTATE_p[2] = 0.0;
        }
      }
    } else {
      {
        real_T *dx;
        int_T i;
        dx = &(((StateDerivatives_TemplateLgV2 *)
                TemplateLgV2_M->ModelData.derivs)->Integrator_CSTATE_e[0]);
        for (i=0; i < 6; i++) {
          dx[i] = 0.0;
        }
      }
    }

    /* end of Derivatives for SubSystem: '<S25>/Linear Simulator' */

    /* Integrator Block: '<S30>/Integrator' */
    {
      if (TemplateLgV2_P.ctrl1ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE[0] =
          TemplateLgV2_B.TmpHiddenBufferAtProductInpor_f[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE[0] = 0.0;
      }

      if (TemplateLgV2_P.ctrl1ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE[1] =
          TemplateLgV2_B.TmpHiddenBufferAtProductInpor_f[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE[1] = 0.0;
      }

      if (TemplateLgV2_P.ctrl1ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE[2] =
          TemplateLgV2_B.TmpHiddenBufferAtProductInpor_f[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE[2] = 0.0;
      }
    }

    /* Integrator Block: '<S169>/Integrator4' */
    {
      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator4_CSTATE[0] = TemplateLgV2_B.Product_o2[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator4_CSTATE[0] = 0.0;
      }

      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator4_CSTATE[1] = TemplateLgV2_B.Product_o2[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator4_CSTATE[1] = 0.0;
      }

      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator4_CSTATE[2] = TemplateLgV2_B.Product_o2[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator4_CSTATE[2] = 0.0;
      }
    }

    /* Integrator Block: '<S50>/Integrator' */
    {
      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_a[0] = TemplateLgV2_B.Product_jo[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_a[0] = 0.0;
      }

      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_a[1] = TemplateLgV2_B.Product_jo[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_a[1] = 0.0;
      }

      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_a[2] = TemplateLgV2_B.Product_jo[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_a[2] = 0.0;
      }
    }

    /* Integrator Block: '<S42>/Integrator' */
    {
      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_d[0] = TemplateLgV2_B.Add_h[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_d[0] = 0.0;
      }

      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_d[1] = TemplateLgV2_B.Add_h[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_d[1] = 0.0;
      }
    }

    /* Integrator Block: '<S42>/Integrator1' */
    {
      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator1_CSTATE = TemplateLgV2_B.Subtract_o;
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator1_CSTATE = 0.0;
      }
    }

    /* Integrator Block: '<S42>/Integrator2' */
    {
      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = TemplateLgV2_B.Gain_jz[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator2_CSTATE[0] = 0.0;
      }

      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = TemplateLgV2_B.Gain_jz[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator2_CSTATE[1] = 0.0;
      }
    }

    /* Integrator Block: '<S169>/Integrator' */
    {
      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_o[0] = TemplateLgV2_B.Sum3_c[0];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_o[0] = 0.0;
      }

      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_o[1] = TemplateLgV2_B.Sum3_c[1];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_o[1] = 0.0;
      }

      if (TemplateLgV2_P.ctrl2ResetIntegrator_Value== 0.0) {
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_o[2] = TemplateLgV2_B.Sum3_c[2];
      } else {
        /* level reset is active*/
        ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
          ->Integrator_CSTATE_o[2] = 0.0;
      }
    }

    /* Derivatives for Integrator: '<S169>/Integrator3' */
    ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
      ->Integrator3_CSTATE[0] = TemplateLgV2_B.Sum7[0];
    ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
      ->Integrator3_CSTATE[1] = TemplateLgV2_B.Sum7[1];
    ((StateDerivatives_TemplateLgV2 *) TemplateLgV2_M->ModelData.derivs)
      ->Integrator3_CSTATE[2] = TemplateLgV2_B.Sum7[2];
  }
}

/* Model initialize function */
void TemplateLgV2_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)TemplateLgV2_M,0,
                sizeof(RT_MODEL_TemplateLgV2));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&TemplateLgV2_M->solverInfo,
                          &TemplateLgV2_M->Timing.simTimeStep);
    rtsiSetTPtr(&TemplateLgV2_M->solverInfo, &rtmGetTPtr(TemplateLgV2_M));
    rtsiSetStepSizePtr(&TemplateLgV2_M->solverInfo,
                       &TemplateLgV2_M->Timing.stepSize0);
    rtsiSetdXPtr(&TemplateLgV2_M->solverInfo, &TemplateLgV2_M->ModelData.derivs);
    rtsiSetContStatesPtr(&TemplateLgV2_M->solverInfo,
                         &TemplateLgV2_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&TemplateLgV2_M->solverInfo,
      &TemplateLgV2_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&TemplateLgV2_M->solverInfo, (&rtmGetErrorStatus
      (TemplateLgV2_M)));
    rtsiSetRTModelPtr(&TemplateLgV2_M->solverInfo, TemplateLgV2_M);
  }

  rtsiSetSimTimeStep(&TemplateLgV2_M->solverInfo, MAJOR_TIME_STEP);
  TemplateLgV2_M->ModelData.intgData.y = TemplateLgV2_M->ModelData.odeY;
  TemplateLgV2_M->ModelData.intgData.f[0] = TemplateLgV2_M->ModelData.odeF[0];
  TemplateLgV2_M->ModelData.intgData.f[1] = TemplateLgV2_M->ModelData.odeF[1];
  TemplateLgV2_M->ModelData.intgData.f[2] = TemplateLgV2_M->ModelData.odeF[2];
  TemplateLgV2_M->ModelData.intgData.f[3] = TemplateLgV2_M->ModelData.odeF[3];
  TemplateLgV2_M->ModelData.intgData.f[4] = TemplateLgV2_M->ModelData.odeF[4];
  TemplateLgV2_M->ModelData.intgData.f[5] = TemplateLgV2_M->ModelData.odeF[5];
  TemplateLgV2_M->ModelData.contStates = ((real_T *) &TemplateLgV2_X);
  rtsiSetSolverData(&TemplateLgV2_M->solverInfo, (void *)
                    &TemplateLgV2_M->ModelData.intgData);
  rtsiSetSolverName(&TemplateLgV2_M->solverInfo,"ode5");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = TemplateLgV2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    TemplateLgV2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    TemplateLgV2_M->Timing.sampleTimes =
      (&TemplateLgV2_M->Timing.sampleTimesArray[0]);
    TemplateLgV2_M->Timing.offsetTimes =
      (&TemplateLgV2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    TemplateLgV2_M->Timing.sampleTimes[0] = (0.0);
    TemplateLgV2_M->Timing.sampleTimes[1] = (0.1);

    /* task offsets */
    TemplateLgV2_M->Timing.offsetTimes[0] = (0.0);
    TemplateLgV2_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(TemplateLgV2_M, &TemplateLgV2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = TemplateLgV2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    TemplateLgV2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(TemplateLgV2_M, -1);
  TemplateLgV2_M->Timing.stepSize0 = 0.1;
  TemplateLgV2_M->Timing.stepSize1 = 0.1;
  rtmSetFirstInitCond(TemplateLgV2_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    TemplateLgV2_M->rtwLogInfo = &rt_DataLoggingInfo;
    rtliSetLogXSignalInfo(TemplateLgV2_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(TemplateLgV2_M->rtwLogInfo, (NULL));
    rtliSetLogT(TemplateLgV2_M->rtwLogInfo, "");
    rtliSetLogX(TemplateLgV2_M->rtwLogInfo, "");
    rtliSetLogXFinal(TemplateLgV2_M->rtwLogInfo, "");
    rtliSetSigLog(TemplateLgV2_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(TemplateLgV2_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(TemplateLgV2_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(TemplateLgV2_M->rtwLogInfo, 0);
    rtliSetLogDecimation(TemplateLgV2_M->rtwLogInfo, 1);
    rtliSetLogY(TemplateLgV2_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(TemplateLgV2_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(TemplateLgV2_M->rtwLogInfo, (NULL));
  }

  TemplateLgV2_M->solverInfoPtr = (&TemplateLgV2_M->solverInfo);
  TemplateLgV2_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&TemplateLgV2_M->solverInfo, 0.1);
  rtsiSetSolverMode(&TemplateLgV2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  TemplateLgV2_M->ModelData.blockIO = ((void *) &TemplateLgV2_B);
  (void) memset(((void *) &TemplateLgV2_B),0,
                sizeof(BlockIO_TemplateLgV2));

  /* parameters */
  TemplateLgV2_M->ModelData.defaultParam = ((real_T *) &TemplateLgV2_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &TemplateLgV2_X;
    TemplateLgV2_M->ModelData.contStates = (x);
    (void) memset((void *)x,0,
                  sizeof(ContinuousStates_TemplateLgV2));
  }

  /* states (dwork) */
  TemplateLgV2_M->Work.dwork = ((void *) &TemplateLgV2_DWork);
  (void) memset((void *)&TemplateLgV2_DWork, 0,
                sizeof(D_Work_TemplateLgV2));
  TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  TemplateLgV2_PrevZCSigState.Integrator4_Reset_ZCE = UNINITIALIZED_ZCSIG;
  TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE_l = UNINITIALIZED_ZCSIG;
  TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE_i = UNINITIALIZED_ZCSIG;
  TemplateLgV2_PrevZCSigState.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  TemplateLgV2_PrevZCSigState.Integrator2_Reset_ZCE = UNINITIALIZED_ZCSIG;
  TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE_m = UNINITIALIZED_ZCSIG;
  TemplateLgV2_PrevZCSigState.Integrator_Reset_ZCE_o = UNINITIALIZED_ZCSIG;
  TemplateLgV2_PrevZCSigState.Integrator1_Reset_ZCE_c = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void TemplateLgV2_terminate(void)
{
  /* ToFile Block: '<S22>/To File' */
  {
    FILE *fp = (FILE *) TemplateLgV2_DWork.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      const char *fileName = "LgV2_data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(TemplateLgV2_M, "Error closing MAT-file LgV2_data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(TemplateLgV2_M,
                          "Error reopening MAT-file LgV2_data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 66, TemplateLgV2_DWork.ToFile_IWORK.Count,
           "LgV2_data")) {
        rtmSetErrorStatus(TemplateLgV2_M,
                          "Error writing header for LgV2_data to MAT-file LgV2_data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(TemplateLgV2_M, "Error closing MAT-file LgV2_data.mat");
        return;
      }

      TemplateLgV2_DWork.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  TemplateLgV2_output(tid);
}

void MdlUpdate(int_T tid)
{
  TemplateLgV2_update(tid);
}

void MdlInitializeSizes(void)
{
  TemplateLgV2_M->Sizes.numContStates = (26);/* Number of continuous states */
  TemplateLgV2_M->Sizes.numY = (0);    /* Number of model outputs */
  TemplateLgV2_M->Sizes.numU = (0);    /* Number of model inputs */
  TemplateLgV2_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  TemplateLgV2_M->Sizes.numSampTimes = (2);/* Number of sample times */
  TemplateLgV2_M->Sizes.numBlocks = (979);/* Number of blocks */
  TemplateLgV2_M->Sizes.numBlockIO = (714);/* Number of block outputs */
  TemplateLgV2_M->Sizes.numBlockPrms = (1419);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* Integrator Block: '<S30>/Integrator' */
  TemplateLgV2_X.Integrator_CSTATE[0] = TemplateLgV2_P.Integrator_IC;
  TemplateLgV2_X.Integrator_CSTATE[1] = TemplateLgV2_P.Integrator_IC;
  TemplateLgV2_X.Integrator_CSTATE[2] = TemplateLgV2_P.Integrator_IC;

  /* Integrator Block: '<S169>/Integrator4' */
  TemplateLgV2_X.Integrator4_CSTATE[0] = TemplateLgV2_P.Integrator4_IC;
  TemplateLgV2_X.Integrator4_CSTATE[1] = TemplateLgV2_P.Integrator4_IC;
  TemplateLgV2_X.Integrator4_CSTATE[2] = TemplateLgV2_P.Integrator4_IC;

  /* Integrator Block: '<S50>/Integrator' */
  TemplateLgV2_X.Integrator_CSTATE_a[0] = TemplateLgV2_P.Integrator_IC_m[0];
  TemplateLgV2_X.Integrator_CSTATE_a[1] = TemplateLgV2_P.Integrator_IC_m[1];
  TemplateLgV2_X.Integrator_CSTATE_a[2] = TemplateLgV2_P.Integrator_IC_m[2];

  /* Integrator Block: '<S42>/Integrator' */
  if (rtmIsFirstInitCond(TemplateLgV2_M)) {
    TemplateLgV2_X.Integrator_CSTATE_d[0] = 0.0;
    TemplateLgV2_X.Integrator_CSTATE_d[1] = 0.0;
  }

  TemplateLgV2_DWork.Integrator_IWORK.IcNeedsLoading = 1;

  /* Integrator Block: '<S42>/Integrator1' */
  if (rtmIsFirstInitCond(TemplateLgV2_M)) {
    TemplateLgV2_X.Integrator1_CSTATE = 0.0;
  }

  TemplateLgV2_DWork.Integrator1_IWORK.IcNeedsLoading = 1;

  /* Derivative Block: '<S96>/Derivative' */
  TemplateLgV2_DWork.Derivative_RWORK.TimeStampA = rtInf;
  TemplateLgV2_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* Integrator Block: '<S42>/Integrator2' */
  TemplateLgV2_X.Integrator2_CSTATE[0] = TemplateLgV2_P.Integrator2_IC;
  TemplateLgV2_X.Integrator2_CSTATE[1] = TemplateLgV2_P.Integrator2_IC;

  /* Derivative Block: '<S166>/Derivative' */
  TemplateLgV2_DWork.Derivative_RWORK_k.TimeStampA = rtInf;
  TemplateLgV2_DWork.Derivative_RWORK_k.TimeStampB = rtInf;

  /* Integrator Block: '<S169>/Integrator' */
  if (rtmIsFirstInitCond(TemplateLgV2_M)) {
    TemplateLgV2_X.Integrator_CSTATE_o[0] = 0.0;
    TemplateLgV2_X.Integrator_CSTATE_o[1] = 0.0;
    TemplateLgV2_X.Integrator_CSTATE_o[2] = 0.0;
  }

  TemplateLgV2_DWork.Integrator_IWORK_c.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<S169>/Integrator3' */
  TemplateLgV2_X.Integrator3_CSTATE[0] = TemplateLgV2_P.Integrator3_IC;
  TemplateLgV2_X.Integrator3_CSTATE[1] = TemplateLgV2_P.Integrator3_IC;
  TemplateLgV2_X.Integrator3_CSTATE[2] = TemplateLgV2_P.Integrator3_IC;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(TemplateLgV2_M)) {
    rtmSetFirstInitCond(TemplateLgV2_M, 0);
  }
}

void MdlStart(void)
{
  /* Start for Constant: '<S4>/Initial psi [rad]' */
  TemplateLgV2_B.Initialpsirad = TemplateLgV2_P.Initialpsirad_Value;

  /* Start for Constant: '<S4>/Initial x [m]' */
  TemplateLgV2_B.Initialxm = TemplateLgV2_P.Initialxm_Value;

  /* Start for Constant: '<S4>/Initial y [m]' */
  TemplateLgV2_B.Initialym = TemplateLgV2_P.Initialym_Value;

  /* Start for Constant: '<S4>/Initial r [rad//s]' */
  TemplateLgV2_B.Initialrrads = TemplateLgV2_P.Initialrrads_Value;

  /* Start for Constant: '<S4>/Initial u [m//s]' */
  TemplateLgV2_B.Initialums = TemplateLgV2_P.Initialums_Value;

  /* Start for Constant: '<S4>/Initial v [m//s]' */
  TemplateLgV2_B.Initialvms = TemplateLgV2_P.Initialvms_Value;

  /* Start for Constant: '<S9>/Initial q_x' */
  TemplateLgV2_B.Initialq_x = TemplateLgV2_P.Initialq_x_Value;

  /* Start for Constant: '<S9>/Initial q_y' */
  TemplateLgV2_B.Initialq_y = TemplateLgV2_P.Initialq_y_Value;

  /* Start for Constant: '<S9>/Initial s' */
  TemplateLgV2_B.Initials = TemplateLgV2_P.Initials_Value;

  /* Start for enable SubSystem: '<S25>/Linear Simulator' */
  TemplateLgV2_DWork.LinearSimulator_MODE = SUBSYS_DISABLED;

  /* Integrator Block: '<S200>/Integrator' */
  if (rtmIsFirstInitCond(TemplateLgV2_M)) {
    TemplateLgV2_X.Integrator_CSTATE_e[0] = 0.0;
    TemplateLgV2_X.Integrator_CSTATE_e[1] = 0.0;
    TemplateLgV2_X.Integrator_CSTATE_e[2] = 0.0;
  }

  TemplateLgV2_DWork.Integrator_IWORK_d.IcNeedsLoading = 1;

  /* Integrator Block: '<S200>/Integrator1' */
  if (rtmIsFirstInitCond(TemplateLgV2_M)) {
    TemplateLgV2_X.Integrator1_CSTATE_p[0] = 0.0;
    TemplateLgV2_X.Integrator1_CSTATE_p[1] = 0.0;
    TemplateLgV2_X.Integrator1_CSTATE_p[2] = 0.0;
  }

  TemplateLgV2_DWork.Integrator1_IWORK_l.IcNeedsLoading = 1;

  /* end of Start for SubSystem: '<S25>/Linear Simulator' */

  /* ToFile Block: '<S22>/To File' */
  {
    const char *fileName = "LgV2_data.mat";
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(TemplateLgV2_M, "Error creating .mat file LgV2_data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,66,0,"LgV2_data")) {
      rtmSetErrorStatus(TemplateLgV2_M,
                        "Error writing mat file header to file LgV2_data.mat");
      return;
    }

    TemplateLgV2_DWork.ToFile_IWORK.Count = 0;
    TemplateLgV2_DWork.ToFile_IWORK.Decimation = -1;
    TemplateLgV2_DWork.ToFile_PWORK.FilePtr = fp;
  }

  /* Create Identity Matrix for Block: '<S166>/Inverse' */
  {
    int_T i;
    real_T *dWork = &TemplateLgV2_DWork.Inverse_DWORK4[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &TemplateLgV2_DWork.Inverse_DWORK4[0];
    while (dWork < &TemplateLgV2_DWork.Inverse_DWORK4[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  /* Start for enable SubSystem: '<S25>/CSE1 actuator' */
  TemplateLgV2_DWork.CSE1actuator_MODE = SUBSYS_DISABLED;

  /* end of Start for SubSystem: '<S25>/CSE1 actuator' */

  /* Create Identity Matrix for Block: '<S25>/Inverse' */
  {
    int_T i;
    real_T *dWork = &TemplateLgV2_DWork.Inverse_DWORK4_e[0];
    for (i = 0; i < 9; i++) {
      *dWork++ = 0.0;
    }

    dWork = &TemplateLgV2_DWork.Inverse_DWORK4_e[0];
    while (dWork < &TemplateLgV2_DWork.Inverse_DWORK4_e[0]+9) {
      *dWork = 1;
      dWork += 4;
    }
  }

  MdlInitialize();
}

RT_MODEL_TemplateLgV2 *TemplateLgV2(void)
{
  TemplateLgV2_initialize(1);
  return TemplateLgV2_M;
}

void MdlTerminate(void)
{
  TemplateLgV2_terminate();
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
#ifdef NI_ROOTMODEL_TemplateLgV2
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
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,10,Complex);

   case 48:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,11,Complex);

   case 49:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 50:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 51:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 63:
    //Type is matrix. Call GetValueByDataType on its contained type
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 82:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,10,Complex);

   case 48:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,11,Complex);

   case 49:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 50:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 51:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 63:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 82:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern TemplateLgV2_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Main Subsystems/Naviagation/Input from SIT/QTM In
  if (TaskSampleHit[0]) {
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(TemplateLgV2_B.QTMIn, count, data[index++], 49, 0);
    }
  } else {
    index += 9;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI0
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&TemplateLgV2_B.SITzAI0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&TemplateLgV2_B.SITzAI1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Main Subsystems/Naviagation/Input from SIT/SIT zAI2
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&TemplateLgV2_B.SITzAI2, 0, data[index++], 0, 0);
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
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Switch2_p,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Servo1,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Servo2,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Servo3,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Servo4,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.VSPSPort,0,0,0);
  } else {
    index += 1;
  }

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.VSPSStarboard,0,
      0,0);
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
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Switch2_p,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM4 Servo1: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Servo1,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM5 Servo2: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Servo2,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM6 Servo3: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Servo3,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM7 Servo4: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.Servo4,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM1 VSPS Port: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.VSPSPort,0,0,0);

  // Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /SIT PWM2 VSPS Starboard: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&TemplateLgV2_B.VSPSStarboard,0,0,
    0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] = {
  { 0, "templatelgv2/Inputs from LabVIEW/Control Input Selector/Value", offsetof
    (Parameters_TemplateLgV2, ControlInputSelector_Value), 31, 1, 2, 0, "", 0 },

  { 1, "templatelgv2/Inputs from LabVIEW/Control Mode Selector/Value", offsetof
    (Parameters_TemplateLgV2, ControlModeSelector_Value), 31, 1, 2, 2, "", 0 },

  { 2, "templatelgv2/Inputs from LabVIEW/Enable CSE1/Value", offsetof
    (Parameters_TemplateLgV2, EnableCSE1_Value), 31, 1, 2, 4, "", 0 },

  { 3, "templatelgv2/Inputs from LabVIEW/tauxscale/Value", offsetof
    (Parameters_TemplateLgV2, tauxscale_Value), 31, 1, 2, 6, "", 0 },

  { 4, "templatelgv2/Inputs from LabVIEW/tauyscale/Value", offsetof
    (Parameters_TemplateLgV2, tauyscale_Value), 31, 1, 2, 8, "", 0 },

  { 5, "templatelgv2/Inputs from LabVIEW/tauyawscale/Value", offsetof
    (Parameters_TemplateLgV2, tauyawscale_Value), 31, 1, 2, 10, "", 0 },

  { 6, "templatelgv2/Inputs from LabVIEW/offset u1/Value", offsetof
    (Parameters_TemplateLgV2, offsetu1_Value), 31, 1, 2, 12, "", 0 },

  { 7, "templatelgv2/Inputs from LabVIEW/offset u2/Value", offsetof
    (Parameters_TemplateLgV2, offsetu2_Value), 31, 1, 2, 14, "", 0 },

  { 8, "templatelgv2/Inputs from LabVIEW/offset u3/Value", offsetof
    (Parameters_TemplateLgV2, offsetu3_Value), 31, 1, 2, 16, "", 0 },

  { 9, "templatelgv2/Inputs from LabVIEW/offset u4/Value", offsetof
    (Parameters_TemplateLgV2, offsetu4_Value), 31, 1, 2, 18, "", 0 },

  { 10,
    "templatelgv2/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value",
    offsetof(Parameters_TemplateLgV2, EnableLinearSimulator_Value), 31, 1, 2, 20,
    "", 0 },

  { 11,
    "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value",
    offsetof(Parameters_TemplateLgV2, Initialpsirad_Value), 31, 1, 2, 22, "", 0
  },

  { 12, "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value",
    offsetof(Parameters_TemplateLgV2, Initialxm_Value), 31, 1, 2, 24, "", 0 },

  { 13, "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value",
    offsetof(Parameters_TemplateLgV2, Initialym_Value), 31, 1, 2, 26, "", 0 },

  { 14,
    "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value",
    offsetof(Parameters_TemplateLgV2, Initialrrads_Value), 31, 1, 2, 28, "", 0 },

  { 15,
    "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value",
    offsetof(Parameters_TemplateLgV2, Initialums_Value), 31, 1, 2, 30, "", 0 },

  { 16,
    "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value",
    offsetof(Parameters_TemplateLgV2, Initialvms_Value), 31, 1, 2, 32, "", 0 },

  { 17,
    "templatelgv2/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value",
    offsetof(Parameters_TemplateLgV2, ResetLinearSimulatorintegrator_), 31, 1, 2,
    34, "", 0 },

  { 18, "templatelgv2/Inputs from LabVIEW/Path/Delta [m]/Value", offsetof
    (Parameters_TemplateLgV2, Deltam_Value), 31, 1, 2, 36, "", 0 },

  { 19, "templatelgv2/Inputs from LabVIEW/Path/Path Selector  [-]/Value",
    offsetof(Parameters_TemplateLgV2, PathSelector_Value), 31, 1, 2, 38, "", 0 },

  { 20, "templatelgv2/Inputs from LabVIEW/Path/my [-]/Value", offsetof
    (Parameters_TemplateLgV2, my_Value), 31, 1, 2, 40, "", 0 },

  { 21, "templatelgv2/Inputs from LabVIEW/Path/u_d [m]/Value", offsetof
    (Parameters_TemplateLgV2, u_dm_Value), 31, 1, 2, 42, "", 0 },

  { 22, "templatelgv2/Inputs from LabVIEW/Path/x_dmax [m]/Value", offsetof
    (Parameters_TemplateLgV2, x_dmaxm_Value), 31, 1, 2, 44, "", 0 },

  { 23, "templatelgv2/Inputs from LabVIEW/Path/x_dmin [m]/Value", offsetof
    (Parameters_TemplateLgV2, x_dminm_Value), 31, 1, 2, 46, "", 0 },

  { 24, "templatelgv2/Inputs from LabVIEW/Path/y_dmax [m]/Value", offsetof
    (Parameters_TemplateLgV2, y_dmaxm_Value), 31, 1, 2, 48, "", 0 },

  { 25, "templatelgv2/Inputs from LabVIEW/Path/y_dmin [m]/Value", offsetof
    (Parameters_TemplateLgV2, y_dminm_Value), 31, 1, 2, 50, "", 0 },

  { 26, "templatelgv2/Inputs from LabVIEW/Path/Ellipse/k [-]/Value", offsetof
    (Parameters_TemplateLgV2, k_Value), 31, 1, 2, 52, "", 0 },

  { 27, "templatelgv2/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value", offsetof
    (Parameters_TemplateLgV2, r_xm_Value), 31, 1, 2, 54, "", 0 },

  { 28, "templatelgv2/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value", offsetof
    (Parameters_TemplateLgV2, r_ym_Value), 31, 1, 2, 56, "", 0 },

  { 29, "templatelgv2/Inputs from LabVIEW/Path/Ellipse/x_0 [m]/Value", offsetof
    (Parameters_TemplateLgV2, x_0m_Value), 31, 1, 2, 58, "", 0 },

  { 30, "templatelgv2/Inputs from LabVIEW/Path/Ellipse/y_0 [m]/Value", offsetof
    (Parameters_TemplateLgV2, y_0m_Value), 31, 1, 2, 60, "", 0 },

  { 31, "templatelgv2/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value", offsetof
    (Parameters_TemplateLgV2, x_1m_Value), 31, 1, 2, 62, "", 0 },

  { 32, "templatelgv2/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value", offsetof
    (Parameters_TemplateLgV2, x_2m_Value), 31, 1, 2, 64, "", 0 },

  { 33, "templatelgv2/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value", offsetof
    (Parameters_TemplateLgV2, y_1m_Value), 31, 1, 2, 66, "", 0 },

  { 34, "templatelgv2/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value", offsetof
    (Parameters_TemplateLgV2, y_2m_Value), 31, 1, 2, 68, "", 0 },

  { 35, "templatelgv2/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value",
    offsetof(Parameters_TemplateLgV2, AS_LX_Value), 31, 1, 2, 70, "", 0 },

  { 36, "templatelgv2/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain", offsetof
    (Parameters_TemplateLgV2, ScalingLX_Gain), 31, 1, 2, 72, "", 0 },

  { 37, "templatelgv2/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value",
    offsetof(Parameters_TemplateLgV2, AS_LY_Value), 31, 1, 2, 74, "", 0 },

  { 38, "templatelgv2/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain", offsetof
    (Parameters_TemplateLgV2, ScalingLY_Gain), 31, 1, 2, 76, "", 0 },

  { 39, "templatelgv2/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value",
    offsetof(Parameters_TemplateLgV2, AS_RX_Value), 31, 1, 2, 78, "", 0 },

  { 40, "templatelgv2/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain",
    offsetof(Parameters_TemplateLgV2, Scaling_RX_Gain), 31, 1, 2, 80, "", 0 },

  { 41, "templatelgv2/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value",
    offsetof(Parameters_TemplateLgV2, AS_RY_Value), 31, 1, 2, 82, "", 0 },

  { 42, "templatelgv2/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain", offsetof
    (Parameters_TemplateLgV2, ScalingRY_Gain), 31, 1, 2, 84, "", 0 },

  { 43, "templatelgv2/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value",
    offsetof(Parameters_TemplateLgV2, PS3_BT_Power_Value), 31, 1, 2, 86, "", 0 },

  { 44, "templatelgv2/Inputs from LabVIEW/PlayStation3/L2 [-]/Value", offsetof
    (Parameters_TemplateLgV2, L2_Value), 31, 1, 2, 88, "", 0 },

  { 45, "templatelgv2/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value",
    offsetof(Parameters_TemplateLgV2, PS3_VSP_Speed_Value), 31, 1, 2, 90, "", 0
  },

  { 46, "templatelgv2/Inputs from LabVIEW/PlayStation3/R2 [-]/Value", offsetof
    (Parameters_TemplateLgV2, R2_Value), 31, 1, 2, 92, "", 0 },

  { 47, "templatelgv2/Inputs from LabVIEW/Setpoint/setpointpsi [deg]/Value",
    offsetof(Parameters_TemplateLgV2, setpointpsideg_Value), 31, 1, 2, 94, "", 0
  },

  { 48,
    "templatelgv2/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1/Gain",
    offsetof(Parameters_TemplateLgV2, Gain1_Gain), 31, 1, 2, 96, "", 0 },

  { 49, "templatelgv2/Inputs from LabVIEW/Setpoint/setpointx [m]/Value",
    offsetof(Parameters_TemplateLgV2, setpointxm_Value), 31, 1, 2, 98, "", 0 },

  { 50, "templatelgv2/Inputs from LabVIEW/Setpoint/setpointy [m]/Value",
    offsetof(Parameters_TemplateLgV2, setpointym_Value), 31, 1, 2, 100, "", 0 },

  { 51, "templatelgv2/Inputs from LabVIEW/ctrl1/Kd/12/Value", offsetof
    (Parameters_TemplateLgV2, u_Value), 31, 1, 2, 102, "", 0 },

  { 52, "templatelgv2/Inputs from LabVIEW/ctrl1/Kd/13/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_g), 31, 1, 2, 104, "", 0 },

  { 53, "templatelgv2/Inputs from LabVIEW/ctrl1/Kd/21/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_o), 31, 1, 2, 106, "", 0 },

  { 54, "templatelgv2/Inputs from LabVIEW/ctrl1/Kd/23/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_c), 31, 1, 2, 108, "", 0 },

  { 55, "templatelgv2/Inputs from LabVIEW/ctrl1/Kd/31/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_a), 31, 1, 2, 110, "", 0 },

  { 56, "templatelgv2/Inputs from LabVIEW/ctrl1/Kd/32/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_i), 31, 1, 2, 112, "", 0 },

  { 57, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kdx/Value", offsetof
    (Parameters_TemplateLgV2, ctrl1Kdx_Value), 31, 1, 2, 114, "", 0 },

  { 58, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kdy/Value", offsetof
    (Parameters_TemplateLgV2, ctrl1Kdy_Value), 31, 1, 2, 116, "", 0 },

  { 59, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kdpsi/Value", offsetof
    (Parameters_TemplateLgV2, ctrl1Kdpsi_Value), 31, 1, 2, 118, "", 0 },

  { 60, "templatelgv2/Inputs from LabVIEW/ctrl1/Ki/12/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_j), 31, 1, 2, 120, "", 0 },

  { 61, "templatelgv2/Inputs from LabVIEW/ctrl1/Ki/13/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_b), 31, 1, 2, 122, "", 0 },

  { 62, "templatelgv2/Inputs from LabVIEW/ctrl1/Ki/21/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_ig), 31, 1, 2, 124, "", 0 },

  { 63, "templatelgv2/Inputs from LabVIEW/ctrl1/Ki/23/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_d), 31, 1, 2, 126, "", 0 },

  { 64, "templatelgv2/Inputs from LabVIEW/ctrl1/Ki/31/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_p), 31, 1, 2, 128, "", 0 },

  { 65, "templatelgv2/Inputs from LabVIEW/ctrl1/Ki/32/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_iy), 31, 1, 2, 130, "", 0 },

  { 66, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kix/Value", offsetof
    (Parameters_TemplateLgV2, ctrl1Kix_Value), 31, 1, 2, 132, "", 0 },

  { 67, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kiy/Value", offsetof
    (Parameters_TemplateLgV2, ctrl1Kiy_Value), 31, 1, 2, 134, "", 0 },

  { 68, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kipsi/Value", offsetof
    (Parameters_TemplateLgV2, ctrl1Kipsi_Value), 31, 1, 2, 136, "", 0 },

  { 69, "templatelgv2/Inputs from LabVIEW/ctrl1/Kp/12/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_av), 31, 1, 2, 138, "", 0 },

  { 70, "templatelgv2/Inputs from LabVIEW/ctrl1/Kp/13/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_c0), 31, 1, 2, 140, "", 0 },

  { 71, "templatelgv2/Inputs from LabVIEW/ctrl1/Kp/21/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_du), 31, 1, 2, 142, "", 0 },

  { 72, "templatelgv2/Inputs from LabVIEW/ctrl1/Kp/23/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_oe), 31, 1, 2, 144, "", 0 },

  { 73, "templatelgv2/Inputs from LabVIEW/ctrl1/Kp/31/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_e), 31, 1, 2, 146, "", 0 },

  { 74, "templatelgv2/Inputs from LabVIEW/ctrl1/Kp/32/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_in), 31, 1, 2, 148, "", 0 },

  { 75, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kpx/Value", offsetof
    (Parameters_TemplateLgV2, ctrl1Kpx_Value), 31, 1, 2, 150, "", 0 },

  { 76, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kpy/Value", offsetof
    (Parameters_TemplateLgV2, ctrl1Kpy_Value), 31, 1, 2, 152, "", 0 },

  { 77, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kppsi/Value", offsetof
    (Parameters_TemplateLgV2, ctrl1Kppsi_Value), 31, 1, 2, 154, "", 0 },

  { 78, "templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1 Reset Integrator/Value",
    offsetof(Parameters_TemplateLgV2, ctrl1ResetIntegrator_Value), 31, 1, 2, 156,
    "", 0 },

  { 79, "templatelgv2/Inputs from LabVIEW/ctrl2/Gamma_q/12/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_bs), 31, 1, 2, 158, "", 0 },

  { 80, "templatelgv2/Inputs from LabVIEW/ctrl2/Gamma_q/21/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_k), 31, 1, 2, 160, "", 0 },

  { 81, "templatelgv2/Inputs from LabVIEW/ctrl2/Gamma_q_Surge/Value", offsetof
    (Parameters_TemplateLgV2, Gamma_q_Surge_Value), 31, 1, 2, 162, "", 0 },

  { 82, "templatelgv2/Inputs from LabVIEW/ctrl2/Gamma_q_Sway/Value", offsetof
    (Parameters_TemplateLgV2, Gamma_q_Sway_Value), 31, 1, 2, 164, "", 0 },

  { 83, "templatelgv2/Inputs from LabVIEW/ctrl2/Initial q_x/Value", offsetof
    (Parameters_TemplateLgV2, Initialq_x_Value), 31, 1, 2, 166, "", 0 },

  { 84, "templatelgv2/Inputs from LabVIEW/ctrl2/Initial q_y/Value", offsetof
    (Parameters_TemplateLgV2, Initialq_y_Value), 31, 1, 2, 168, "", 0 },

  { 85, "templatelgv2/Inputs from LabVIEW/ctrl2/Initial s/Value", offsetof
    (Parameters_TemplateLgV2, Initials_Value), 31, 1, 2, 170, "", 0 },

  { 86, "templatelgv2/Inputs from LabVIEW/ctrl2/K_d/12/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_ap), 31, 1, 2, 172, "", 0 },

  { 87, "templatelgv2/Inputs from LabVIEW/ctrl2/K_d/13/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_l), 31, 1, 2, 174, "", 0 },

  { 88, "templatelgv2/Inputs from LabVIEW/ctrl2/K_d/21/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_n), 31, 1, 2, 176, "", 0 },

  { 89, "templatelgv2/Inputs from LabVIEW/ctrl2/K_d/23/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_ls), 31, 1, 2, 178, "", 0 },

  { 90, "templatelgv2/Inputs from LabVIEW/ctrl2/K_d/31/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_f), 31, 1, 2, 180, "", 0 },

  { 91, "templatelgv2/Inputs from LabVIEW/ctrl2/K_d/32/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_h), 31, 1, 2, 182, "", 0 },

  { 92, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kdx/Value", offsetof
    (Parameters_TemplateLgV2, ctrl2Kdx_Value), 31, 1, 2, 184, "", 0 },

  { 93, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kdy/Value", offsetof
    (Parameters_TemplateLgV2, ctrl2Kdy_Value), 31, 1, 2, 186, "", 0 },

  { 94, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kdpsi/Value", offsetof
    (Parameters_TemplateLgV2, ctrl2Kdpsi_Value), 31, 1, 2, 188, "", 0 },

  { 95, "templatelgv2/Inputs from LabVIEW/ctrl2/K_i/12/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_f0), 31, 1, 2, 190, "", 0 },

  { 96, "templatelgv2/Inputs from LabVIEW/ctrl2/K_i/13/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_dm), 31, 1, 2, 192, "", 0 },

  { 97, "templatelgv2/Inputs from LabVIEW/ctrl2/K_i/21/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_ds), 31, 1, 2, 194, "", 0 },

  { 98, "templatelgv2/Inputs from LabVIEW/ctrl2/K_i/23/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_hl), 31, 1, 2, 196, "", 0 },

  { 99, "templatelgv2/Inputs from LabVIEW/ctrl2/K_i/31/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_ni), 31, 1, 2, 198, "", 0 },

  { 100, "templatelgv2/Inputs from LabVIEW/ctrl2/K_i/32/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_iq), 31, 1, 2, 200, "", 0 },

  { 101, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kix/Value", offsetof
    (Parameters_TemplateLgV2, ctrl2Kix_Value), 31, 1, 2, 202, "", 0 },

  { 102, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kiy/Value", offsetof
    (Parameters_TemplateLgV2, ctrl2Kiy_Value), 31, 1, 2, 204, "", 0 },

  { 103, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kipsi/Value", offsetof
    (Parameters_TemplateLgV2, ctrl2Kipsi_Value), 31, 1, 2, 206, "", 0 },

  { 104, "templatelgv2/Inputs from LabVIEW/ctrl2/K_p/12/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_ht), 31, 1, 2, 208, "", 0 },

  { 105, "templatelgv2/Inputs from LabVIEW/ctrl2/K_p/13/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_fu), 31, 1, 2, 210, "", 0 },

  { 106, "templatelgv2/Inputs from LabVIEW/ctrl2/K_p/21/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_cd), 31, 1, 2, 212, "", 0 },

  { 107, "templatelgv2/Inputs from LabVIEW/ctrl2/K_p/23/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_oz), 31, 1, 2, 214, "", 0 },

  { 108, "templatelgv2/Inputs from LabVIEW/ctrl2/K_p/31/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_al), 31, 1, 2, 216, "", 0 },

  { 109, "templatelgv2/Inputs from LabVIEW/ctrl2/K_p/32/Value", offsetof
    (Parameters_TemplateLgV2, u_Value_cv), 31, 1, 2, 218, "", 0 },

  { 110, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kpx/Value", offsetof
    (Parameters_TemplateLgV2, ctrl2Kpx_Value), 31, 1, 2, 220, "", 0 },

  { 111, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kpy/Value", offsetof
    (Parameters_TemplateLgV2, ctrl2Kpy_Value), 31, 1, 2, 222, "", 0 },

  { 112, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kppsi/Value", offsetof
    (Parameters_TemplateLgV2, ctrl2Kppsi_Value), 31, 1, 2, 224, "", 0 },

  { 113, "templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2 Reset Integrator/Value",
    offsetof(Parameters_TemplateLgV2, ctrl2ResetIntegrator_Value), 31, 1, 2, 226,
    "", 0 },

  { 114, "templatelgv2/Inputs from LabVIEW/ctrl2/kappa_1/Value", offsetof
    (Parameters_TemplateLgV2, kappa_1_Value), 31, 1, 2, 228, "", 0 },

  { 115, "templatelgv2/Inputs from LabVIEW/ctrl2/lambda_q/Value", offsetof
    (Parameters_TemplateLgV2, lambda_q_Value), 31, 1, 2, 230, "", 0 },

  { 116,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value",
    offsetof(Parameters_TemplateLgV2, l_x1_Value), 31, 1, 2, 232, "", 0 },

  { 117,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain",
    offsetof(Parameters_TemplateLgV2, l_x1_Gain), 31, 1, 2, 234, "", 0 },

  { 118,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value",
    offsetof(Parameters_TemplateLgV2, l_x2_Value), 31, 1, 2, 236, "", 0 },

  { 119,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain",
    offsetof(Parameters_TemplateLgV2, l_x2_Gain), 31, 1, 2, 238, "", 0 },

  { 120,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value",
    offsetof(Parameters_TemplateLgV2, l_y2_Value), 31, 1, 2, 240, "", 0 },

  { 121,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain",
    offsetof(Parameters_TemplateLgV2, l_y2_Gain), 31, 1, 2, 242, "", 0 },

  { 122,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value",
    offsetof(Parameters_TemplateLgV2, B_11_Value), 31, 1, 2, 244, "", 0 },

  { 123,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value",
    offsetof(Parameters_TemplateLgV2, B_21_Value), 31, 1, 2, 246, "", 0 },

  { 124,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value",
    offsetof(Parameters_TemplateLgV2, l_y1_Value), 31, 1, 2, 248, "", 0 },

  { 125,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value",
    offsetof(Parameters_TemplateLgV2, B_12_Value), 31, 1, 2, 250, "", 0 },

  { 126,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value",
    offsetof(Parameters_TemplateLgV2, B_22_Value), 31, 1, 2, 252, "", 0 },

  { 127,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value",
    offsetof(Parameters_TemplateLgV2, B_13_Value), 31, 1, 2, 254, "", 0 },

  { 128,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value",
    offsetof(Parameters_TemplateLgV2, B_23_Value), 31, 1, 2, 256, "", 0 },

  { 129,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value",
    offsetof(Parameters_TemplateLgV2, B_14_Value), 31, 1, 2, 258, "", 0 },

  { 130,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value",
    offsetof(Parameters_TemplateLgV2, B_24_Value), 31, 1, 2, 260, "", 0 },

  { 131,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value",
    offsetof(Parameters_TemplateLgV2, B_15_Value), 31, 1, 2, 262, "", 0 },

  { 132,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value",
    offsetof(Parameters_TemplateLgV2, B_25_Value), 31, 1, 2, 264, "", 0 },

  { 133,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value",
    offsetof(Parameters_TemplateLgV2, l_x3_Value), 31, 1, 2, 266, "", 0 },

  { 134,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value",
    offsetof(Parameters_TemplateLgV2, N_r_Value), 31, 1, 2, 268, "", 0 },

  { 135,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain",
    offsetof(Parameters_TemplateLgV2, N_r_Gain), 31, 1, 2, 270, "", 0 },

  { 136,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value",
    offsetof(Parameters_TemplateLgV2, N_v_Value), 31, 1, 2, 272, "", 0 },

  { 137,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain",
    offsetof(Parameters_TemplateLgV2, N_v_Gain), 31, 1, 2, 274, "", 0 },

  { 138,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value",
    offsetof(Parameters_TemplateLgV2, X_u_Value), 31, 1, 2, 276, "", 0 },

  { 139,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain",
    offsetof(Parameters_TemplateLgV2, X_u_Gain), 31, 1, 2, 278, "", 0 },

  { 140,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value",
    offsetof(Parameters_TemplateLgV2, Y_v_Value), 31, 1, 2, 280, "", 0 },

  { 141,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain",
    offsetof(Parameters_TemplateLgV2, Y_v_Gain), 31, 1, 2, 282, "", 0 },

  { 142,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value",
    offsetof(Parameters_TemplateLgV2, Y_r_Value), 31, 1, 2, 284, "", 0 },

  { 143,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain",
    offsetof(Parameters_TemplateLgV2, Y_vr_Gain), 31, 1, 2, 286, "", 0 },

  { 144,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value",
    offsetof(Parameters_TemplateLgV2, D_L_12_Value), 31, 1, 2, 288, "", 0 },

  { 145,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value",
    offsetof(Parameters_TemplateLgV2, D_L_13_Value), 31, 1, 2, 290, "", 0 },

  { 146,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value",
    offsetof(Parameters_TemplateLgV2, D_L_21_Value), 31, 1, 2, 292, "", 0 },

  { 147,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value",
    offsetof(Parameters_TemplateLgV2, D_L_31_Value), 31, 1, 2, 294, "", 0 },

  { 148,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value",
    offsetof(Parameters_TemplateLgV2, m_Value), 31, 1, 2, 296, "", 0 },

  { 149,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value",
    offsetof(Parameters_TemplateLgV2, X_udot_Value), 31, 1, 2, 298, "", 0 },

  { 150,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value",
    offsetof(Parameters_TemplateLgV2, M_21_Value), 31, 1, 2, 300, "", 0 },

  { 151,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value",
    offsetof(Parameters_TemplateLgV2, M_31_Value), 31, 1, 2, 302, "", 0 },

  { 152,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value",
    offsetof(Parameters_TemplateLgV2, M_12_Value), 31, 1, 2, 304, "", 0 },

  { 153,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value",
    offsetof(Parameters_TemplateLgV2, Y_vdot_Value), 31, 1, 2, 306, "", 0 },

  { 154,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value",
    offsetof(Parameters_TemplateLgV2, x_g_Value), 31, 1, 2, 308, "", 0 },

  { 155,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value",
    offsetof(Parameters_TemplateLgV2, N_vdot_Value), 31, 1, 2, 310, "", 0 },

  { 156,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value",
    offsetof(Parameters_TemplateLgV2, M_13_Value), 31, 1, 2, 312, "", 0 },

  { 157,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value",
    offsetof(Parameters_TemplateLgV2, Y_rdot_Value), 31, 1, 2, 314, "", 0 },

  { 158,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value",
    offsetof(Parameters_TemplateLgV2, I_z_Value), 31, 1, 2, 316, "", 0 },

  { 159,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value",
    offsetof(Parameters_TemplateLgV2, N_rdot_Value), 31, 1, 2, 318, "", 0 },

  { 160,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value",
    offsetof(Parameters_TemplateLgV2, T_e11_Value), 31, 1, 2, 320, "", 0 },

  { 161,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value",
    offsetof(Parameters_TemplateLgV2, T_e21_Value), 31, 1, 2, 322, "", 0 },

  { 162,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value",
    offsetof(Parameters_TemplateLgV2, l_y1_Value_b), 31, 1, 2, 324, "", 0 },

  { 163,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value",
    offsetof(Parameters_TemplateLgV2, T_e12_Value), 31, 1, 2, 326, "", 0 },

  { 164,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value",
    offsetof(Parameters_TemplateLgV2, T_e22_Value), 31, 1, 2, 328, "", 0 },

  { 165,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value",
    offsetof(Parameters_TemplateLgV2, l_x1_Value_e), 31, 1, 2, 330, "", 0 },

  { 166,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain",
    offsetof(Parameters_TemplateLgV2, l_x1_Gain_b), 31, 1, 2, 332, "", 0 },

  { 167,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value",
    offsetof(Parameters_TemplateLgV2, T_e13_Value), 31, 1, 2, 334, "", 0 },

  { 168,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value",
    offsetof(Parameters_TemplateLgV2, T_e23_Value), 31, 1, 2, 336, "", 0 },

  { 169,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value",
    offsetof(Parameters_TemplateLgV2, l_y2_Value_e), 31, 1, 2, 338, "", 0 },

  { 170,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain",
    offsetof(Parameters_TemplateLgV2, l_y2_Gain_h), 31, 1, 2, 340, "", 0 },

  { 171,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value",
    offsetof(Parameters_TemplateLgV2, T_e14_Value), 31, 1, 2, 342, "", 0 },

  { 172,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value",
    offsetof(Parameters_TemplateLgV2, T_e24_Value), 31, 1, 2, 344, "", 0 },

  { 173,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value",
    offsetof(Parameters_TemplateLgV2, l_x2_Value_j), 31, 1, 2, 346, "", 0 },

  { 174,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain",
    offsetof(Parameters_TemplateLgV2, l_x2_Gain_a), 31, 1, 2, 348, "", 0 },

  { 175,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value",
    offsetof(Parameters_TemplateLgV2, T_e15_Value), 31, 1, 2, 350, "", 0 },

  { 176,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value",
    offsetof(Parameters_TemplateLgV2, T_e25_Value), 31, 1, 2, 352, "", 0 },

  { 177,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value",
    offsetof(Parameters_TemplateLgV2, l_x3_Value_f), 31, 1, 2, 354, "", 0 },

  { 178, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain",
    offsetof(Parameters_TemplateLgV2, PS3u_1_Gain), 31, 1, 2, 356, "", 0 },

  { 179,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues",
    offsetof(Parameters_TemplateLgV2, u_1tof_1_XData), 72, 19, 2, 358, "", 0 },

  { 180,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table",
    offsetof(Parameters_TemplateLgV2, u_1tof_1_YData), 72, 19, 2, 360, "", 0 },

  { 181, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain",
    offsetof(Parameters_TemplateLgV2, PS3u_2_Gain), 31, 1, 2, 362, "", 0 },

  { 182,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues",
    offsetof(Parameters_TemplateLgV2, u_2tof_2_XData), 73, 21, 2, 364, "", 0 },

  { 183,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table",
    offsetof(Parameters_TemplateLgV2, u_2tof_2_YData), 73, 21, 2, 366, "", 0 },

  { 184, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain",
    offsetof(Parameters_TemplateLgV2, PS3u_3_Gain), 31, 1, 2, 368, "", 0 },

  { 185,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues",
    offsetof(Parameters_TemplateLgV2, u_3tof_3_XData), 72, 19, 2, 370, "", 0 },

  { 186,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table",
    offsetof(Parameters_TemplateLgV2, u_3tof_3_YData), 72, 19, 2, 372, "", 0 },

  { 187, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain",
    offsetof(Parameters_TemplateLgV2, PS3u_4_Gain), 31, 1, 2, 374, "", 0 },

  { 188,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues",
    offsetof(Parameters_TemplateLgV2, u_4tof_4_XData), 74, 17, 2, 376, "", 0 },

  { 189,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table",
    offsetof(Parameters_TemplateLgV2, u_4tof_4_YData), 74, 17, 2, 378, "", 0 },

  { 190, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain",
    offsetof(Parameters_TemplateLgV2, PS3u_5_Gain), 31, 1, 2, 380, "", 0 },

  { 191,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues",
    offsetof(Parameters_TemplateLgV2, u_5tof_5_XData), 75, 7, 2, 382, "", 0 },

  { 192,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table",
    offsetof(Parameters_TemplateLgV2, u_5tof_5_YData), 75, 7, 2, 384, "", 0 },

  { 193,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain",
    offsetof(Parameters_TemplateLgV2, QTMIn3xcoordmm_Gain), 31, 1, 2, 386, "", 0
  },

  { 194, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain",
    offsetof(Parameters_TemplateLgV2, mm2mx_Gain), 31, 1, 2, 388, "", 0 },

  { 195,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain",
    offsetof(Parameters_TemplateLgV2, QTMIn4ycoordmm_Gain), 31, 1, 2, 390, "", 0
  },

  { 196, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain",
    offsetof(Parameters_TemplateLgV2, mm2my_Gain), 31, 1, 2, 392, "", 0 },

  { 197,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain",
    offsetof(Parameters_TemplateLgV2, QTMIn6yawdeg_Gain), 31, 1, 2, 394, "", 0 },

  { 198, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain",
    offsetof(Parameters_TemplateLgV2, d2ryaw_Gain), 31, 1, 2, 396, "", 0 },

  { 199,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat), 31, 1, 2, 398, "", 0
  },

  { 200,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat), 31, 1, 2, 400, "", 0
  },

  { 201,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain), 31, 1, 2, 402, "", 0 },

  { 202,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value), 31, 1, 2, 404, "", 0 },

  { 203,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_p), 31, 1, 2, 406, "",
    0 },

  { 204,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_a), 31, 1, 2, 408, "",
    0 },

  { 205,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_i), 31, 1, 2, 410, "", 0 },

  { 206,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_p), 31, 1, 2, 412, "", 0 },

  { 207,
    "templatelgv2/Main Subsystems/Control/DP control/Integrator/InitialCondition",
    offsetof(Parameters_TemplateLgV2, Integrator_IC), 31, 1, 2, 414, "", 0 },

  { 208,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator4/InitialCondition",
    offsetof(Parameters_TemplateLgV2, Integrator4_IC), 31, 1, 2, 416, "", 0 },

  { 209, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R31/Value", offsetof
    (Parameters_TemplateLgV2, R31_Value), 31, 1, 2, 418, "", 0 },

  { 210, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/-1/Gain", offsetof
    (Parameters_TemplateLgV2, u_Gain), 31, 1, 2, 420, "", 0 },

  { 211, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R32/Value", offsetof
    (Parameters_TemplateLgV2, R32_Value), 31, 1, 2, 422, "", 0 },

  { 212, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R13/Value", offsetof
    (Parameters_TemplateLgV2, R13_Value), 31, 1, 2, 424, "", 0 },

  { 213, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R23/Value", offsetof
    (Parameters_TemplateLgV2, R23_Value), 31, 1, 2, 426, "", 0 },

  { 214, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R33/Value", offsetof
    (Parameters_TemplateLgV2, R33_Value), 31, 1, 2, 428, "", 0 },

  { 215,
    "templatelgv2/Main Subsystems/Control/LgV2/zeta/Integrator/InitialCondition",
    offsetof(Parameters_TemplateLgV2, Integrator_IC_m), 28, 3, 2, 430, "", 0 },

  { 216, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_d), 31, 1, 2, 432, "", 0 },

  { 217, "templatelgv2/Main Subsystems/Control/LgV2/Control law/1/Value",
    offsetof(Parameters_TemplateLgV2, _Value), 31, 1, 2, 434, "", 0 },

  { 218, "templatelgv2/Main Subsystems/Control/LgV2/Control law/4/Gain",
    offsetof(Parameters_TemplateLgV2, _Gain), 31, 1, 2, 436, "", 0 },

  { 219, "templatelgv2/Main Subsystems/Control/LgV2/I/Constant/Value", offsetof
    (Parameters_TemplateLgV2, Constant_Value_i), 22, 9, 2, 438, "", 0 },

  { 220,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_k), 31, 1, 2, 440, "",
    0 },

  { 221,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_j), 31, 1, 2, 442, "",
    0 },

  { 222,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_k), 31, 1, 2, 444, "", 0 },

  { 223,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_m), 31, 1, 2, 446, "", 0 },

  { 224,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_m), 31, 1, 2, 448, "",
    0 },

  { 225,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_l), 31, 1, 2, 450, "",
    0 },

  { 226,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_p), 31, 1, 2, 452, "", 0 },

  { 227,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_o), 31, 1, 2, 454, "", 0 },

  { 228,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_l), 31, 1, 2, 456, "",
    0 },

  { 229,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_i), 31, 1, 2, 458, "",
    0 },

  { 230,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_n), 31, 1, 2, 460, "", 0 },

  { 231,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_l), 31, 1, 2, 462, "", 0 },

  { 232,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_n), 31, 1, 2, 464, "",
    0 },

  { 233,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_h), 31, 1, 2, 466, "",
    0 },

  { 234,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_h), 31, 1, 2, 468, "", 0 },

  { 235,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_lt), 31, 1, 2, 470, "", 0 },

  { 236,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_a), 31, 1, 2, 472, "", 0 },

  { 237,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_o), 31, 1, 2, 474, "",
    0 },

  { 238,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_e), 31, 1, 2, 476, "",
    0 },

  { 239,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_c), 31, 1, 2, 478, "", 0 },

  { 240,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_ia), 31, 1, 2, 480, "", 0 },

  { 241,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_kp), 31, 1, 2, 482, "",
    0 },

  { 242,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_c), 31, 1, 2, 484, "",
    0 },

  { 243,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_b), 31, 1, 2, 486, "", 0 },

  { 244,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_e), 31, 1, 2, 488, "", 0 },

  { 245,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_i), 31, 1, 2, 490, "",
    0 },

  { 246,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_h3), 31, 1, 2, 492, "",
    0 },

  { 247,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_o), 31, 1, 2, 494, "", 0 },

  { 248,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_o0), 31, 1, 2, 496, "", 0 },

  { 249,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain",
    offsetof(Parameters_TemplateLgV2, u_Gain_m), 31, 1, 2, 498, "", 0 },

  { 250,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq/0_2x1/Value",
    offsetof(Parameters_TemplateLgV2, _2x1_Value), 32, 2, 2, 500, "", 0 },

  { 251,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value",
    offsetof(Parameters_TemplateLgV2, _2x1_Value_h), 32, 2, 2, 502, "", 0 },

  { 252,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_l), 31, 1, 2, 504, "", 0 },

  { 253,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain",
    offsetof(Parameters_TemplateLgV2, Gain1_Gain_e), 31, 1, 2, 506, "", 0 },

  { 254,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_ltw), 31, 1, 2, 508, "", 0
  },

  { 255,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_ay), 31, 1, 2, 510, "", 0 },

  { 256,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_a), 31, 1, 2, 512, "", 0 },

  { 257, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Gain1/Gain",
    offsetof(Parameters_TemplateLgV2, Gain1_Gain_k), 31, 1, 2, 514, "", 0 },

  { 258, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S11/Value",
    offsetof(Parameters_TemplateLgV2, S11_Value), 31, 1, 2, 516, "", 0 },

  { 259, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/R31/Value",
    offsetof(Parameters_TemplateLgV2, R31_Value_b), 31, 1, 2, 518, "", 0 },

  { 260, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S12/Gain",
    offsetof(Parameters_TemplateLgV2, S12_Gain), 31, 1, 2, 520, "", 0 },

  { 261, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S22/Value",
    offsetof(Parameters_TemplateLgV2, S22_Value), 31, 1, 2, 522, "", 0 },

  { 262, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S32/Value",
    offsetof(Parameters_TemplateLgV2, S32_Value), 31, 1, 2, 524, "", 0 },

  { 263, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S13/Value",
    offsetof(Parameters_TemplateLgV2, S13_Value), 31, 1, 2, 526, "", 0 },

  { 264, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S23/Value",
    offsetof(Parameters_TemplateLgV2, S23_Value), 31, 1, 2, 528, "", 0 },

  { 265, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S33/Value",
    offsetof(Parameters_TemplateLgV2, S33_Value), 31, 1, 2, 530, "", 0 },

  { 266,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq/0_2x1/Value",
    offsetof(Parameters_TemplateLgV2, _2x1_Value_a), 32, 2, 2, 532, "", 0 },

  { 267,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_e1), 24, 4, 2, 534, "", 0 },

  { 268,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_cz), 31, 1, 2, 536, "", 0 },

  { 269,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain",
    offsetof(Parameters_TemplateLgV2, _Gain_i), 31, 1, 2, 538, "", 0 },

  { 270,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value",
    offsetof(Parameters_TemplateLgV2, _2x2_Value), 24, 4, 2, 540, "", 0 },

  { 271,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/0_2x2/Value",
    offsetof(Parameters_TemplateLgV2, _2x2_Value_g), 24, 4, 2, 542, "", 0 },

  { 272,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain",
    offsetof(Parameters_TemplateLgV2, _Gain_o), 31, 1, 2, 544, "", 0 },

  { 273,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value",
    offsetof(Parameters_TemplateLgV2, u_Value_m), 31, 1, 2, 546, "", 0 },

  { 274,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_bm), 31, 1, 2, 548, "", 0 },

  { 275,
    "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Integrator2/InitialCondition",
    offsetof(Parameters_TemplateLgV2, Integrator2_IC), 31, 1, 2, 550, "", 0 },

  { 276,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value",
    offsetof(Parameters_TemplateLgV2, _2x1_Value_hc), 32, 2, 2, 552, "", 0 },

  { 277,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_e), 31, 1, 2, 554, "", 0 },

  { 278,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/0_2x1/Value",
    offsetof(Parameters_TemplateLgV2, _2x1_Value_n), 32, 2, 2, 556, "", 0 },

  { 279,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_on), 31, 1, 2, 558, "", 0 },

  { 280,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_pm), 31, 1, 2, 560, "", 0 },

  { 281,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_ap), 31, 1, 2, 562, "", 0 },

  { 282,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain",
    offsetof(Parameters_TemplateLgV2, u_Gain_c), 31, 1, 2, 564, "", 0 },

  { 283,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain",
    offsetof(Parameters_TemplateLgV2, _Gain_j), 31, 1, 2, 566, "", 0 },

  { 284,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain",
    offsetof(Parameters_TemplateLgV2, _Gain_d), 31, 1, 2, 568, "", 0 },

  { 285,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_g), 31, 1, 2, 570, "", 0 },

  { 286,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_op), 31, 1, 2, 572, "", 0 },

  { 287,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_dc), 31, 1, 2, 574, "", 0 },

  { 288,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value",
    offsetof(Parameters_TemplateLgV2, u_Value_pn), 31, 1, 2, 576, "", 0 },

  { 289,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_f), 31, 1, 2, 578, "", 0 },

  { 290, "templatelgv2/Main Subsystems/Control/LgV2/V_1^q/Gain/Gain", offsetof
    (Parameters_TemplateLgV2, Gain_Gain_gd), 31, 1, 2, 580, "", 0 },

  { 291, "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_pr), 31, 1, 2, 582, "", 0 },

  { 292,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues",
    offsetof(Parameters_TemplateLgV2, f_1tou_1_XData), 76, 39, 2, 584, "", 0 },

  { 293,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table",
    offsetof(Parameters_TemplateLgV2, f_1tou_1_YData), 76, 39, 2, 586, "", 0 },

  { 294,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_lx), 31, 1, 2, 588, "", 0 },

  { 295,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_k), 31, 1, 2, 590, "", 0 },

  { 296,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_mf), 31, 1, 2, 592, "", 0 },

  { 297,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_kd), 31, 1, 2, 594, "", 0 },

  { 298,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues",
    offsetof(Parameters_TemplateLgV2, f_2000391_XData), 77, 11, 2, 596, "", 0 },

  { 299,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table",
    offsetof(Parameters_TemplateLgV2, f_2000391_YData), 77, 11, 2, 598, "", 0 },

  { 300,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues",
    offsetof(Parameters_TemplateLgV2, f_2006731f_2000391_XData), 28, 3, 2, 600,
    "", 0 },

  { 301,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table",
    offsetof(Parameters_TemplateLgV2, f_2006731f_2000391_YData), 28, 3, 2, 602,
    "", 0 },

  { 302,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues",
    offsetof(Parameters_TemplateLgV2, f_2006731_XData), 78, 18, 2, 604, "", 0 },

  { 303,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table",
    offsetof(Parameters_TemplateLgV2, f_2006731_YData), 78, 18, 2, 606, "", 0 },

  { 304,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues",
    offsetof(Parameters_TemplateLgV2, f_3tou_3_XData), 76, 39, 2, 608, "", 0 },

  { 305,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table",
    offsetof(Parameters_TemplateLgV2, f_3tou_3_YData), 76, 39, 2, 610, "", 0 },

  { 306,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_d), 31, 1, 2, 612, "", 0 },

  { 307,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_ls), 31, 1, 2, 614, "", 0 },

  { 308,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues",
    offsetof(Parameters_TemplateLgV2, f_400451_XData), 79, 15, 2, 616, "", 0 },

  { 309,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table",
    offsetof(Parameters_TemplateLgV2, f_400451_YData), 79, 15, 2, 618, "", 0 },

  { 310,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues",
    offsetof(Parameters_TemplateLgV2, f_400451_XData_h), 80, 13, 2, 620, "", 0 },

  { 311,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table",
    offsetof(Parameters_TemplateLgV2, f_400451_YData_a), 80, 13, 2, 622, "", 0 },

  { 312,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_TemplateLgV2, DeadZone001_Start), 31, 1, 2, 624, "", 0 },

  { 313,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_TemplateLgV2, DeadZone001_End), 31, 1, 2, 626, "", 0 },

  { 314,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_g), 31, 1, 2, 628, "", 0 },

  { 315,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_n), 31, 1, 2, 630, "", 0 },

  { 316,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues",
    offsetof(Parameters_TemplateLgV2, f_50_XData), 81, 10, 2, 632, "", 0 },

  { 317,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table",
    offsetof(Parameters_TemplateLgV2, f_50_YData), 81, 10, 2, 634, "", 0 },

  { 318,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value",
    offsetof(Parameters_TemplateLgV2, f_50_Value), 31, 1, 2, 636, "", 0 },

  { 319,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues",
    offsetof(Parameters_TemplateLgV2, f_50_XData_f), 81, 10, 2, 638, "", 0 },

  { 320,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table",
    offsetof(Parameters_TemplateLgV2, f_50_YData_d), 81, 10, 2, 640, "", 0 },

  { 321,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value",
    offsetof(Parameters_TemplateLgV2, BT_power_limit_Value), 31, 1, 2, 642, "",
    0 },

  { 322,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value",
    offsetof(Parameters_TemplateLgV2, VSP_speeds_Value), 31, 1, 2, 644, "", 0 },

  { 323,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_kpo), 31, 1, 2, 646,
    "", 0 },

  { 324,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_b), 31, 1, 2, 648, "",
    0 },

  { 325,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain",
    offsetof(Parameters_TemplateLgV2, QTMIn2Error_Gain), 31, 1, 2, 650, "", 0 },

  { 326,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain",
    offsetof(Parameters_TemplateLgV2, QTMIn9Residual_Gain), 31, 1, 2, 652, "", 0
  },

  { 327,
    "templatelgv2/Main Subsystems/Plant/Thruster setting workaround/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_f), 31, 1, 2, 654, "",
    0 },

  { 328,
    "templatelgv2/Main Subsystems/Plant/Thruster setting workaround/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_hx), 31, 1, 2, 656, "",
    0 },

  { 329,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Constant1/Value",
    offsetof(Parameters_TemplateLgV2, Constant1_Value), 22, 9, 2, 658, "", 0 },

  { 330,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain",
    offsetof(Parameters_TemplateLgV2, QTMIn5zcoordmm_Gain), 31, 1, 2, 660, "", 0
  },

  { 331, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain",
    offsetof(Parameters_TemplateLgV2, mm2mz_Gain), 31, 1, 2, 662, "", 0 },

  { 332,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain",
    offsetof(Parameters_TemplateLgV2, QTMIn8rolldeg_Gain), 31, 1, 2, 664, "", 0
  },

  { 333, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain",
    offsetof(Parameters_TemplateLgV2, d2rroll_Gain), 31, 1, 2, 666, "", 0 },

  { 334,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain",
    offsetof(Parameters_TemplateLgV2, QTMIn7pitchdeg_Gain), 31, 1, 2, 668, "", 0
  },

  { 335,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain",
    offsetof(Parameters_TemplateLgV2, d2rpitch_Gain), 31, 1, 2, 670, "", 0 },

  { 336,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In1 FN/Gain",
    offsetof(Parameters_TemplateLgV2, QTMIn1FN_Gain), 31, 1, 2, 672, "", 0 },

  { 337,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator3/InitialCondition",
    offsetof(Parameters_TemplateLgV2, Integrator3_IC), 31, 1, 2, 674, "", 0 },

  { 338,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_l3), 31, 1, 2, 676, "",
    0 },

  { 339,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_n), 31, 1, 2, 678, "",
    0 },

  { 340,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_kx), 31, 1, 2, 680, "", 0 },

  { 341,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_pa), 31, 1, 2, 682, "", 0 },

  { 342,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_ii), 31, 1, 2, 684, "",
    0 },

  { 343,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_il), 31, 1, 2, 686, "",
    0 },

  { 344,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_lw), 31, 1, 2, 688, "", 0 },

  { 345,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_an), 31, 1, 2, 690, "", 0 },

  { 346,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K2/Gain",
    offsetof(Parameters_TemplateLgV2, K2_Gain), 22, 9, 2, 692, "", 0 },

  { 347,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K3/Gain",
    offsetof(Parameters_TemplateLgV2, K3_Gain), 22, 9, 2, 694, "", 0 },

  { 348,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K4/Gain",
    offsetof(Parameters_TemplateLgV2, K4_Gain), 22, 9, 2, 696, "", 0 },

  { 349,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues",
    offsetof(Parameters_TemplateLgV2, u_1tof_1_XData_g), 76, 39, 2, 698, "", 0 },

  { 350,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table",
    offsetof(Parameters_TemplateLgV2, u_1tof_1_YData_d), 76, 39, 2, 700, "", 0 },

  { 351,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_h), 31, 1, 2, 702, "", 0 },

  { 352,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_fq), 31, 1, 2, 704, "", 0 },

  { 353,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_i0), 31, 1, 2, 706, "", 0 },

  { 354,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_j), 31, 1, 2, 708, "", 0 },

  { 355,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues",
    offsetof(Parameters_TemplateLgV2, u_205_XData), 77, 11, 2, 710, "", 0 },

  { 356,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table",
    offsetof(Parameters_TemplateLgV2, u_205_YData), 77, 11, 2, 712, "", 0 },

  { 357,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues",
    offsetof(Parameters_TemplateLgV2, u_201u_202_XData), 28, 3, 2, 714, "", 0 },

  { 358,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table",
    offsetof(Parameters_TemplateLgV2, u_201u_202_YData), 28, 3, 2, 716, "", 0 },

  { 359,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues",
    offsetof(Parameters_TemplateLgV2, u_20_XData), 78, 18, 2, 718, "", 0 },

  { 360,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table",
    offsetof(Parameters_TemplateLgV2, u_20_YData), 78, 18, 2, 720, "", 0 },

  { 361,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues",
    offsetof(Parameters_TemplateLgV2, u_3tof_3_XData_p), 76, 39, 2, 722, "", 0 },

  { 362,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table",
    offsetof(Parameters_TemplateLgV2, u_3tof_3_YData_m), 76, 39, 2, 724, "", 0 },

  { 363,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_fc), 31, 1, 2, 726, "", 0 },

  { 364,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_le), 31, 1, 2, 728, "", 0 },

  { 365,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues",
    offsetof(Parameters_TemplateLgV2, u_401_XData), 79, 15, 2, 730, "", 0 },

  { 366,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table",
    offsetof(Parameters_TemplateLgV2, u_401_YData), 79, 15, 2, 732, "", 0 },

  { 367,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues",
    offsetof(Parameters_TemplateLgV2, u_401_XData_g), 80, 13, 2, 734, "", 0 },

  { 368,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table",
    offsetof(Parameters_TemplateLgV2, u_401_YData_p), 80, 13, 2, 736, "", 0 },

  { 369,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue",
    offsetof(Parameters_TemplateLgV2, DeadZone001_Start_a), 31, 1, 2, 738, "", 0
  },

  { 370,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue",
    offsetof(Parameters_TemplateLgV2, DeadZone001_End_n), 31, 1, 2, 740, "", 0 },

  { 371,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_jz), 31, 1, 2, 742, "", 0 },

  { 372,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_am), 31, 1, 2, 744, "", 0 },

  { 373,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues",
    offsetof(Parameters_TemplateLgV2, u_50_XData), 81, 10, 2, 746, "", 0 },

  { 374,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table",
    offsetof(Parameters_TemplateLgV2, u_50_YData), 81, 10, 2, 748, "", 0 },

  { 375,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value",
    offsetof(Parameters_TemplateLgV2, u_50_Value), 31, 1, 2, 750, "", 0 },

  { 376,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues",
    offsetof(Parameters_TemplateLgV2, u_50_XData_i), 81, 10, 2, 752, "", 0 },

  { 377,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table",
    offsetof(Parameters_TemplateLgV2, u_50_YData_g), 81, 10, 2, 754, "", 0 },

  { 378,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/inv(T_b)/Gain",
    offsetof(Parameters_TemplateLgV2, invT_b_Gain), 22, 9, 2, 756, "", 0 },

  { 379, "templatelgv2/Main Subsystems/Plant/saturation/Saturation/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_UpperSat_il), 31, 1, 2, 758, "",
    0 },

  { 380, "templatelgv2/Main Subsystems/Plant/saturation/Saturation/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation_LowerSat_im), 31, 1, 2, 760, "",
    0 },

  { 381, "templatelgv2/Main Subsystems/Plant/saturation/Saturation1/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation1_UpperSat), 31, 1, 2, 762, "",
    0 },

  { 382, "templatelgv2/Main Subsystems/Plant/saturation/Saturation1/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation1_LowerSat), 31, 1, 2, 764, "",
    0 },

  { 383, "templatelgv2/Main Subsystems/Plant/saturation/Saturation2/UpperLimit",
    offsetof(Parameters_TemplateLgV2, Saturation2_UpperSat), 31, 1, 2, 766, "",
    0 },

  { 384, "templatelgv2/Main Subsystems/Plant/saturation/Saturation2/LowerLimit",
    offsetof(Parameters_TemplateLgV2, Saturation2_LowerSat), 31, 1, 2, 768, "",
    0 },

  { 385, "templatelgv2/Main Subsystems/Plant/saturation/plant tau_surge/Gain",
    offsetof(Parameters_TemplateLgV2, planttau_surge_Gain), 31, 1, 2, 770, "", 0
  },

  { 386, "templatelgv2/Main Subsystems/Plant/saturation/plant tau_sway/Gain",
    offsetof(Parameters_TemplateLgV2, planttau_sway_Gain), 31, 1, 2, 772, "", 0
  },

  { 387, "templatelgv2/Main Subsystems/Plant/saturation/plant tau_yaw/Gain",
    offsetof(Parameters_TemplateLgV2, planttau_yaw_Gain), 31, 1, 2, 774, "", 0 },

  { 388,
    "templatelgv2/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain",
    offsetof(Parameters_TemplateLgV2, BatteryBowThruster_Gain), 31, 1, 2, 776,
    "", 0 },

  { 389, "templatelgv2/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain",
    offsetof(Parameters_TemplateLgV2, BatteryMain_Gain), 31, 1, 2, 778, "", 0 },

  { 390, "templatelgv2/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain",
    offsetof(Parameters_TemplateLgV2, BatteryServo_Gain), 31, 1, 2, 780, "", 0 },

  { 391, "templatelgv2/Outputs to LabVIEW/Command/tau1/Gain", offsetof
    (Parameters_TemplateLgV2, tau1_Gain), 31, 1, 2, 782, "", 0 },

  { 392, "templatelgv2/Outputs to LabVIEW/Command/tau2/Gain", offsetof
    (Parameters_TemplateLgV2, tau2_Gain), 31, 1, 2, 784, "", 0 },

  { 393, "templatelgv2/Outputs to LabVIEW/Command/tau3/Gain", offsetof
    (Parameters_TemplateLgV2, tau3_Gain), 31, 1, 2, 786, "", 0 },

  { 394, "templatelgv2/Outputs to LabVIEW/Command/tau4/Gain", offsetof
    (Parameters_TemplateLgV2, tau4_Gain), 31, 1, 2, 788, "", 0 },

  { 395, "templatelgv2/Outputs to LabVIEW/Command/tau5/Gain", offsetof
    (Parameters_TemplateLgV2, tau5_Gain), 31, 1, 2, 790, "", 0 },

  { 396, "templatelgv2/Outputs to LabVIEW/Command/tau6/Gain", offsetof
    (Parameters_TemplateLgV2, tau6_Gain), 31, 1, 2, 792, "", 0 },

  { 397, "templatelgv2/Outputs to LabVIEW/Command/plant BT power/Gain", offsetof
    (Parameters_TemplateLgV2, plantBTpower_Gain), 31, 1, 2, 794, "", 0 },

  { 398, "templatelgv2/Outputs to LabVIEW/Command/plant VSP speed/Gain",
    offsetof(Parameters_TemplateLgV2, plantVSPspeed_Gain), 31, 1, 2, 796, "", 0
  },

  { 399, "templatelgv2/Outputs to LabVIEW/Command/plant u_1/Gain", offsetof
    (Parameters_TemplateLgV2, plantu_1_Gain), 31, 1, 2, 798, "", 0 },

  { 400, "templatelgv2/Outputs to LabVIEW/Command/plant u_2/Gain", offsetof
    (Parameters_TemplateLgV2, plantu_2_Gain), 31, 1, 2, 800, "", 0 },

  { 401, "templatelgv2/Outputs to LabVIEW/Command/plant u_3/Gain", offsetof
    (Parameters_TemplateLgV2, plantu_3_Gain), 31, 1, 2, 802, "", 0 },

  { 402, "templatelgv2/Outputs to LabVIEW/Command/plant u_4/Gain", offsetof
    (Parameters_TemplateLgV2, plantu_4_Gain), 31, 1, 2, 804, "", 0 },

  { 403, "templatelgv2/Outputs to LabVIEW/Command/plant u_5/Gain", offsetof
    (Parameters_TemplateLgV2, plantu_5_Gain), 31, 1, 2, 806, "", 0 },

  { 404, "templatelgv2/Outputs to LabVIEW/Command/fact1/Gain", offsetof
    (Parameters_TemplateLgV2, fact1_Gain), 31, 1, 2, 808, "", 0 },

  { 405, "templatelgv2/Outputs to LabVIEW/Command/fact2/Gain", offsetof
    (Parameters_TemplateLgV2, fact2_Gain), 31, 1, 2, 810, "", 0 },

  { 406, "templatelgv2/Outputs to LabVIEW/Command/fact3/Gain", offsetof
    (Parameters_TemplateLgV2, fact3_Gain), 31, 1, 2, 812, "", 0 },

  { 407, "templatelgv2/Outputs to LabVIEW/Command/fact4/Gain", offsetof
    (Parameters_TemplateLgV2, fact4_Gain), 31, 1, 2, 814, "", 0 },

  { 408, "templatelgv2/Outputs to LabVIEW/Command/fact5/Gain", offsetof
    (Parameters_TemplateLgV2, fact5_Gain), 31, 1, 2, 816, "", 0 },

  { 409, "templatelgv2/Outputs to LabVIEW/Command/taux/Gain", offsetof
    (Parameters_TemplateLgV2, taux_Gain), 31, 1, 2, 818, "", 0 },

  { 410, "templatelgv2/Outputs to LabVIEW/Command/tauy/Gain", offsetof
    (Parameters_TemplateLgV2, tauy_Gain), 31, 1, 2, 820, "", 0 },

  { 411, "templatelgv2/Outputs to LabVIEW/Command/tauyaw/Gain", offsetof
    (Parameters_TemplateLgV2, tauyaw_Gain), 31, 1, 2, 822, "", 0 },

  { 412, "templatelgv2/Outputs to LabVIEW/Command/omega_qy/Gain", offsetof
    (Parameters_TemplateLgV2, omega_qy_Gain), 31, 1, 2, 824, "", 0 },

  { 413, "templatelgv2/Outputs to LabVIEW/Command/omegaqx/Gain", offsetof
    (Parameters_TemplateLgV2, omegaqx_Gain), 31, 1, 2, 826, "", 0 },

  { 414, "templatelgv2/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain",
    offsetof(Parameters_TemplateLgV2, CSE1_rdegs_Gain), 31, 1, 2, 828, "", 0 },

  { 415, "templatelgv2/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain",
    offsetof(Parameters_TemplateLgV2, CSE1_ums_Gain), 31, 1, 2, 830, "", 0 },

  { 416, "templatelgv2/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain",
    offsetof(Parameters_TemplateLgV2, CSE1_vms_Gain), 31, 1, 2, 832, "", 0 },

  { 417, "templatelgv2/Outputs to LabVIEW/Naviagtion/QS Error/Gain", offsetof
    (Parameters_TemplateLgV2, QSError_Gain), 31, 1, 2, 834, "", 0 },

  { 418, "templatelgv2/Outputs to LabVIEW/Naviagtion/QS Frame/Gain", offsetof
    (Parameters_TemplateLgV2, QSFrame_Gain), 31, 1, 2, 836, "", 0 },

  { 419, "templatelgv2/Outputs to LabVIEW/Visualization/psi [deg]/Gain",
    offsetof(Parameters_TemplateLgV2, psideg_Gain), 31, 1, 2, 838, "", 0 },

  { 420, "templatelgv2/Outputs to LabVIEW/Visualization/psi-psid [deg]/Gain",
    offsetof(Parameters_TemplateLgV2, psipsiddeg_Gain), 31, 1, 2, 840, "", 0 },

  { 421, "templatelgv2/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]/Gain",
    offsetof(Parameters_TemplateLgV2, psiLOSpsideg_Gain), 31, 1, 2, 842, "", 0 },

  { 422, "templatelgv2/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]/Gain",
    offsetof(Parameters_TemplateLgV2, psiLOSpsiddeg_Gain), 31, 1, 2, 844, "", 0
  },

  { 423, "templatelgv2/Outputs to LabVIEW/Visualization/psi_LOS [deg]/Gain",
    offsetof(Parameters_TemplateLgV2, psi_LOSdeg_Gain), 31, 1, 2, 846, "", 0 },

  { 424, "templatelgv2/Outputs to LabVIEW/Visualization/psid [deg]/Gain",
    offsetof(Parameters_TemplateLgV2, psiddeg_Gain), 31, 1, 2, 848, "", 0 },

  { 425, "templatelgv2/Outputs to LabVIEW/Visualization/psi_plot/Gain", offsetof
    (Parameters_TemplateLgV2, psi_plot_Gain), 31, 1, 2, 850, "", 0 },

  { 426, "templatelgv2/Outputs to LabVIEW/Visualization/qx [m]/Gain", offsetof
    (Parameters_TemplateLgV2, qxm_Gain), 31, 1, 2, 852, "", 0 },

  { 427, "templatelgv2/Outputs to LabVIEW/Visualization/qx-x [m]/Gain", offsetof
    (Parameters_TemplateLgV2, qxxm_Gain), 31, 1, 2, 854, "", 0 },

  { 428, "templatelgv2/Outputs to LabVIEW/Visualization/qx-xd [m]1/Gain",
    offsetof(Parameters_TemplateLgV2, qxxdm1_Gain), 31, 1, 2, 856, "", 0 },

  { 429, "templatelgv2/Outputs to LabVIEW/Visualization/qy [m]/Gain", offsetof
    (Parameters_TemplateLgV2, qym_Gain), 31, 1, 2, 858, "", 0 },

  { 430, "templatelgv2/Outputs to LabVIEW/Visualization/qy-y [m]/Gain", offsetof
    (Parameters_TemplateLgV2, qyym_Gain), 31, 1, 2, 860, "", 0 },

  { 431, "templatelgv2/Outputs to LabVIEW/Visualization/qy-yd [m]1/Gain",
    offsetof(Parameters_TemplateLgV2, qyydm1_Gain), 31, 1, 2, 862, "", 0 },

  { 432, "templatelgv2/Outputs to LabVIEW/Visualization/x [m]/Gain", offsetof
    (Parameters_TemplateLgV2, xm_Gain), 31, 1, 2, 864, "", 0 },

  { 433, "templatelgv2/Outputs to LabVIEW/Visualization/x-xd [m]/Gain", offsetof
    (Parameters_TemplateLgV2, xxdm_Gain), 31, 1, 2, 866, "", 0 },

  { 434, "templatelgv2/Outputs to LabVIEW/Visualization/xd [m]/Gain", offsetof
    (Parameters_TemplateLgV2, xdm_Gain), 31, 1, 2, 868, "", 0 },

  { 435, "templatelgv2/Outputs to LabVIEW/Visualization/x_plot/Gain", offsetof
    (Parameters_TemplateLgV2, x_plot_Gain), 31, 1, 2, 870, "", 0 },

  { 436, "templatelgv2/Outputs to LabVIEW/Visualization/y [m]/Gain", offsetof
    (Parameters_TemplateLgV2, ym_Gain), 31, 1, 2, 872, "", 0 },

  { 437, "templatelgv2/Outputs to LabVIEW/Visualization/y-yd [m]/Gain", offsetof
    (Parameters_TemplateLgV2, yydm_Gain), 31, 1, 2, 874, "", 0 },

  { 438, "templatelgv2/Outputs to LabVIEW/Visualization/yd [m]/Gain", offsetof
    (Parameters_TemplateLgV2, ydm_Gain), 31, 1, 2, 876, "", 0 },

  { 439, "templatelgv2/Outputs to LabVIEW/Visualization/y_plot/Gain", offsetof
    (Parameters_TemplateLgV2, y_plot_Gain), 31, 1, 2, 878, "", 0 },

  { 440, "templatelgv2/Outputs to LabVIEW/Visualization/splot/Gain", offsetof
    (Parameters_TemplateLgV2, splot_Gain), 31, 1, 2, 880, "", 0 },

  { 441,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain",
    offsetof(Parameters_TemplateLgV2, R12_Gain), 31, 1, 2, 882, "", 0 },

  { 442,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain",
    offsetof(Parameters_TemplateLgV2, R22_Gain), 31, 1, 2, 884, "", 0 },

  { 443,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value",
    offsetof(Parameters_TemplateLgV2, _Value_g), 31, 1, 2, 886, "", 0 },

  { 444,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain",
    offsetof(Parameters_TemplateLgV2, S12_Gain_h), 31, 1, 2, 888, "", 0 },

  { 445,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value",
    offsetof(Parameters_TemplateLgV2, _Value_c), 31, 1, 2, 890, "", 0 },

  { 446,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain",
    offsetof(Parameters_TemplateLgV2, S12_Gain_p), 31, 1, 2, 892, "", 0 },

  { 447,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain",
    offsetof(Parameters_TemplateLgV2, BT_D_Gain1_Gain), 31, 1, 2, 894, "", 0 },

  { 448,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value",
    offsetof(Parameters_TemplateLgV2, BT_Power_Offset1_Value), 31, 1, 2, 896, "",
    0 },

  { 449,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain",
    offsetof(Parameters_TemplateLgV2, BT_D_Gain2_Gain), 31, 1, 2, 898, "", 0 },

  { 450,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain",
    offsetof(Parameters_TemplateLgV2, BT_L_Gain1_Gain), 31, 1, 2, 900, "", 0 },

  { 451,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain",
    offsetof(Parameters_TemplateLgV2, BT_L_Gain2_Gain), 31, 1, 2, 902, "", 0 },

  { 452,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value",
    offsetof(Parameters_TemplateLgV2, BT_Power_Offset2_Value), 31, 1, 2, 904, "",
    0 },

  { 453,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value",
    offsetof(Parameters_TemplateLgV2, BT_Power_Offset3_Value), 31, 1, 2, 906, "",
    0 },

  { 454,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value",
    offsetof(Parameters_TemplateLgV2, Constant_Value_ol), 31, 1, 2, 908, "", 0 },

  { 455,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value",
    offsetof(Parameters_TemplateLgV2, Constant1_Value_l), 31, 1, 2, 910, "", 0 },

  { 456,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain",
    offsetof(Parameters_TemplateLgV2, Neg_Gain), 31, 1, 2, 912, "", 0 },

  { 457,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain",
    offsetof(Parameters_TemplateLgV2, x_Gain), 31, 1, 2, 914, "", 0 },

  { 458,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain",
    offsetof(Parameters_TemplateLgV2, y_Gain), 31, 1, 2, 916, "", 0 },

  { 459,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex",
    offsetof(Parameters_TemplateLgV2, Servo1_RowIdx), 33, 3, 2, 918, "", 0 },

  { 460,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex",
    offsetof(Parameters_TemplateLgV2, Servo1_ColIdx), 33, 3, 2, 920, "", 0 },

  { 461,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table",
    offsetof(Parameters_TemplateLgV2, Servo1_Table), 22, 9, 2, 922, "", 0 },

  { 462,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex",
    offsetof(Parameters_TemplateLgV2, Servo2_RowIdx), 33, 3, 2, 924, "", 0 },

  { 463,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex",
    offsetof(Parameters_TemplateLgV2, Servo2_ColIdx), 33, 3, 2, 926, "", 0 },

  { 464,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table",
    offsetof(Parameters_TemplateLgV2, Servo2_Table), 22, 9, 2, 928, "", 0 },

  { 465,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex",
    offsetof(Parameters_TemplateLgV2, Servo3_RowIdx), 33, 3, 2, 930, "", 0 },

  { 466,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex",
    offsetof(Parameters_TemplateLgV2, Servo3_ColIdx), 33, 3, 2, 932, "", 0 },

  { 467,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table",
    offsetof(Parameters_TemplateLgV2, Servo3_Table), 22, 9, 2, 934, "", 0 },

  { 468,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex",
    offsetof(Parameters_TemplateLgV2, Servo4_RowIdx), 33, 3, 2, 936, "", 0 },

  { 469,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex",
    offsetof(Parameters_TemplateLgV2, Servo4_ColIdx), 33, 3, 2, 938, "", 0 },

  { 470,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table",
    offsetof(Parameters_TemplateLgV2, Servo4_Table), 22, 9, 2, 940, "", 0 },

  { 471,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain",
    offsetof(Parameters_TemplateLgV2, VPS_Speed_Gain_Gain), 31, 1, 2, 942, "", 0
  },

  { 472,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value",
    offsetof(Parameters_TemplateLgV2, VPS_Power_Offset_Value), 31, 1, 2, 944, "",
    0 },

  { 473,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain",
    offsetof(Parameters_TemplateLgV2, VSPSPort_Gain), 31, 1, 2, 946, "", 0 },

  { 474,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain",
    offsetof(Parameters_TemplateLgV2, VSPSStarboard_Gain), 31, 1, 2, 948, "", 0
  },

  { 475,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value",
    offsetof(Parameters_TemplateLgV2, R31_Value_p), 31, 1, 2, 950, "", 0 },

  { 476,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value",
    offsetof(Parameters_TemplateLgV2, R32_Value_k), 31, 1, 2, 952, "", 0 },

  { 477,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value",
    offsetof(Parameters_TemplateLgV2, R13_Value_g), 31, 1, 2, 954, "", 0 },

  { 478,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value",
    offsetof(Parameters_TemplateLgV2, R23_Value_n), 31, 1, 2, 956, "", 0 },

  { 479,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value",
    offsetof(Parameters_TemplateLgV2, R33_Value_j), 31, 1, 2, 958, "", 0 },

  { 480,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_TemplateLgV2, Gain1_Gain_p), 38, 1, 2, 960, "", 0 },

  { 481,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_k3), 38, 1, 2, 962, "", 0 },

  { 482,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_cg), 38, 1, 2, 964, "", 0 },

  { 483,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_TemplateLgV2, Gain1_Gain_h), 38, 1, 2, 966, "", 0 },

  { 484,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain",
    offsetof(Parameters_TemplateLgV2, Gain1_Gain_c), 38, 1, 2, 968, "", 0 },

  { 485,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_cs), 38, 1, 2, 970, "", 0 },

  { 486,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain",
    offsetof(Parameters_TemplateLgV2, Gain_Gain_j), 38, 1, 2, 972, "", 0 },

  { 487,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain",
    offsetof(Parameters_TemplateLgV2, Gain1_Gain_pu), 38, 1, 2, 974, "", 0 },
};

static int NI_ParamListSize = 488;
static int NI_ParamDimList[] = {
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Control Input Selector/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Control Mode Selector/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Enable CSE1/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/tauxscale/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/tauyscale/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/tauyawscale/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/offset u1/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/offset u2/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/offset u3/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/offset u4/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Linear Simulator/Enable Linear Simulator/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial x [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial y [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Linear Simulator/Reset Linear Simulator integrator/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Delta [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Path Selector  [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/my [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/u_d [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/x_dmax [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/x_dmin [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/y_dmax [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/y_dmin [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Ellipse/k [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Ellipse/r_x [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Ellipse/r_y [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Ellipse/x_0 [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Ellipse/y_0 [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Linear/x_1 [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Linear/x_2 [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Linear/y_1 [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Path/Linear/y_2 [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/AS_LX [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/ScalingLX/Gain */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/AS_LY [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/ScalingLY/Gain */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/AS_RX [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/Scaling_RX/Gain */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/AS_RY [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/ScalingRY/Gain */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/PS3_BT_Power  [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/L2 [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/PS3_VSP_Speed  [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/PlayStation3/R2 [-]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Setpoint/setpointpsi [deg]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1/Gain */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Setpoint/setpointx [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/Setpoint/setpointy [m]/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kd/12/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kd/13/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kd/21/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kd/23/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kd/31/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kd/32/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kdx/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kdy/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kdpsi/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Ki/12/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Ki/13/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Ki/21/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Ki/23/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Ki/31/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Ki/32/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kix/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kiy/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kipsi/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kp/12/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kp/13/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kp/21/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kp/23/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kp/31/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/Kp/32/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kpx/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kpy/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1Kppsi/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl1/ctrl1 Reset Integrator/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/Gamma_q/12/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/Gamma_q/21/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/Gamma_q_Surge/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/Gamma_q_Sway/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/Initial q_x/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/Initial q_y/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/Initial s/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_d/12/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_d/13/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_d/21/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_d/23/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_d/31/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_d/32/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kdx/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kdy/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kdpsi/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_i/12/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_i/13/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_i/21/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_i/23/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_i/31/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_i/32/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kix/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kiy/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kipsi/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_p/12/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_p/13/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_p/21/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_p/23/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_p/31/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/K_p/32/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kpx/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kpy/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2Kppsi/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/ctrl2 Reset Integrator/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/kappa_1/Value */
  1, 1,                                /* templatelgv2/Inputs from LabVIEW/ctrl2/lambda_q/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x2/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y2/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_11/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_21/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_y1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_12/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_22/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_13/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_23/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_14/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_24/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_15/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/B_25/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/l_x3/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_r/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/N_v/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/X_u/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_v/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Y_r/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_12/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_13/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_21/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/D_L_31/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/X_udot/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_21/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_31/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_12/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_vdot/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/x_g/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_vdot/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_13/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/Y_rdot/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/I_z/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/N_rdot/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e11/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e21/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e12/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e22/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e13/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e23/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_y2/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e14/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e24/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x2/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e15/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/T_e25/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/l_x3/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_1/Gain */
  19, 1,                               /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/InputValues */
  19, 1,                               /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_2/Gain */
  21, 1,                               /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/InputValues */
  21, 1,                               /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_3/Gain */
  19, 1,                               /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/InputValues */
  19, 1,                               /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_4/Gain */
  17, 1,                               /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/InputValues */
  17, 1,                               /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_5/Gain */
  1, 7,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/InputValues */
  1, 7,                                /* templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/mm2m x/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/mm2m y/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/d2r yaw/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/DP control/Integrator/InitialCondition */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator4/InitialCondition */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R31/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/R(psi)/-1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R32/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R13/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R23/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R33/Value */
  3, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/zeta/Integrator/InitialCondition */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/Control law/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/Control law/1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/Control law/4/Gain */
  3, 3,                                /* templatelgv2/Main Subsystems/Control/LgV2/I/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1/Gain */
  2, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq/0_2x1/Value */
  2, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/0_2x1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/Control law/Gain1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S11/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/R31/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S12/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S22/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S32/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S13/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S23/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S33/Value */
  2, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq/0_2x1/Value */
  2, 2,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/I/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2/Gain */
  2, 2,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/0_2x2/Value */
  2, 2,                                /* templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/0_2x2/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/3//2/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/Update laws/Integrator2/InitialCondition */
  2, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/0_2x1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain/Gain */
  2, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/0_2x1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/3//2/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/V_1^q/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/LgV2/Update laws/Gain/Gain */
  1, 39,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/InputValues */
  1, 39,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/InputValues */
  11, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391/Table */
  3, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/InputValues */
  3, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391/Table */
  18, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/InputValues */
  18, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731/Table */
  1, 39,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/InputValues */
  1, 39,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/InputValues */
  15, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451/Table */
  13, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/InputValues */
  13, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/InputValues */
  10, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 = 0/Value */
  10, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/InputValues */
  10, 1,                               /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/BT_power_limit/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/VSP_speeds/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/Thruster setting workaround/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/Thruster setting workaround/Saturation/LowerLimit */
  3, 3,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/Constant1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/mm2m z/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/d2r roll/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/d2r pitch/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In1 FN/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator3/InitialCondition */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Constant/Value */
  3, 3,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K2/Gain */
  3, 3,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K3/Gain */
  3, 3,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K4/Gain */
  1, 39,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/InputValues */
  1, 39,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Constant/Value */
  11, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/InputValues */
  11, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5/Table */
  3, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/InputValues */
  3, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2/Table */
  18, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/InputValues */
  18, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0/Table */
  1, 39,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/InputValues */
  1, 39,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Constant/Value */
  15, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/InputValues */
  15, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1/Table */
  13, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/InputValues */
  13, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/LowerValue */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01/UpperValue */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Constant/Value */
  10, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/InputValues */
  10, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 = 0/Value */
  10, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/InputValues */
  10, 1,                               /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0/Table */
  3, 3,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/inv(T_b)/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/saturation/Saturation/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/saturation/Saturation/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/saturation/Saturation1/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/saturation/Saturation1/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/saturation/Saturation2/UpperLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/saturation/Saturation2/LowerLimit */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/saturation/plant tau_surge/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/saturation/plant tau_sway/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/saturation/plant tau_yaw/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Battery Voltage/Battery Main/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Battery Voltage/Battery Servo/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/tau1/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/tau2/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/tau3/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/tau4/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/tau5/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/tau6/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/plant BT power/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/plant VSP speed/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/plant u_1/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/plant u_2/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/plant u_3/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/plant u_4/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/plant u_5/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/fact1/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/fact2/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/fact3/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/fact4/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/fact5/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/taux/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/tauy/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/tauyaw/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/omega_qy/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Command/omegaqx/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Naviagtion/QS Error/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Naviagtion/QS Frame/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/psi [deg]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/psi-psid [deg]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/psi_LOS [deg]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/psid [deg]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/psi_plot/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/qx [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/qx-x [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/qx-xd [m]1/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/qy [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/qy-y [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/qy-yd [m]1/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/x [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/x-xd [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/xd [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/x_plot/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/y [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/y-yd [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/yd [m]/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/y_plot/Gain */
  1, 1,                                /* templatelgv2/Outputs to LabVIEW/Visualization/splot/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/0/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/0/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset2/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_Power_Offset3/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Constant1/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y/Gain */
  1, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/RowIndex */
  1, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/ColumnIndex */
  3, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1/Table */
  1, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/RowIndex */
  1, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/ColumnIndex */
  3, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2/Table */
  1, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/RowIndex */
  1, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/ColumnIndex */
  3, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3/Table */
  1, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/RowIndex */
  1, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/ColumnIndex */
  3, 3,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4/Table */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Power_Offset/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R31/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R32/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R13/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R23/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R33/Value */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain/Gain */
  1, 1,                                /* templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1/Gain */
};

static int NI_VariablesListSize = 0;
static char *NI_VariablesList[] = {
  ""
};

static int NI_SigListSize = 704;
static NI_Signal NI_SigList[] = {
  { 0, "templatelgv2/Inputs from LabVIEW/tauxscale", 0, "", offsetof
    (BlockIO_TemplateLgV2, tauxscale), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "templatelgv2/Inputs from LabVIEW/tauyscale", 0, "", offsetof
    (BlockIO_TemplateLgV2, tauyscale), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "templatelgv2/Inputs from LabVIEW/tauyawscale", 0, "", offsetof
    (BlockIO_TemplateLgV2, tauyawscale), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial psi [rad]", 0,
    "", offsetof(BlockIO_TemplateLgV2, Initialpsirad), BLOCKIO_SIG, 0, 1, 2, 6,
    0 },

  { 4, "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial x [m]", 0, "",
    offsetof(BlockIO_TemplateLgV2, Initialxm), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial y [m]", 0, "",
    offsetof(BlockIO_TemplateLgV2, Initialym), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial r [rad//s]", 0,
    "", offsetof(BlockIO_TemplateLgV2, Initialrrads), BLOCKIO_SIG, 0, 1, 2, 12,
    0 },

  { 7, "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial u [m//s]", 0,
    "", offsetof(BlockIO_TemplateLgV2, Initialums), BLOCKIO_SIG, 0, 1, 2, 14, 0
  },

  { 8, "templatelgv2/Inputs from LabVIEW/Linear Simulator/Initial v [m//s]", 0,
    "", offsetof(BlockIO_TemplateLgV2, Initialvms), BLOCKIO_SIG, 0, 1, 2, 16, 0
  },

  { 9, "templatelgv2/Inputs from LabVIEW/PlayStation3/ScalingLX", 0,
    "x-position of left analog stick [-1,1]", offsetof(BlockIO_TemplateLgV2,
    xpositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 18, 0 },

  { 10, "templatelgv2/Inputs from LabVIEW/PlayStation3/ScalingLY", 0,
    "y-position of left analog stick [-1,1]", offsetof(BlockIO_TemplateLgV2,
    ypositionofleftanalogstick11), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "templatelgv2/Inputs from LabVIEW/PlayStation3/Scaling_RX", 0,
    "x-position of right analog stick  [-1,1]", offsetof(BlockIO_TemplateLgV2,
    xpositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "templatelgv2/Inputs from LabVIEW/PlayStation3/ScalingRY", 0,
    "y-position of right analog stick [-1,1]", offsetof(BlockIO_TemplateLgV2,
    ypositionofrightanalogstick11), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "templatelgv2/Inputs from LabVIEW/Setpoint/Degrees to Radians/Gain1", 0,
    "", offsetof(BlockIO_TemplateLgV2, Gain1), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "templatelgv2/Inputs from LabVIEW/ctrl1/Kd/[3x3]", 0, "", offsetof
    (BlockIO_TemplateLgV2, ux3), BLOCKIO_SIG, 22, 9, 2, 28, 0 },

  { 15, "templatelgv2/Inputs from LabVIEW/ctrl1/Ki/[3x3]", 0, "", offsetof
    (BlockIO_TemplateLgV2, ux3_b), BLOCKIO_SIG, 22, 9, 2, 30, 0 },

  { 16, "templatelgv2/Inputs from LabVIEW/ctrl1/Kp/[3x3]", 0, "", offsetof
    (BlockIO_TemplateLgV2, ux3_b2), BLOCKIO_SIG, 22, 9, 2, 32, 0 },

  { 17, "templatelgv2/Inputs from LabVIEW/ctrl2/Gamma_q/[2x2]", 0, "", offsetof
    (BlockIO_TemplateLgV2, ux2), BLOCKIO_SIG, 24, 4, 2, 34, 0 },

  { 18, "templatelgv2/Inputs from LabVIEW/ctrl2/Initial q_x", 0, "", offsetof
    (BlockIO_TemplateLgV2, Initialq_x), BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "templatelgv2/Inputs from LabVIEW/ctrl2/Initial q_y", 0, "", offsetof
    (BlockIO_TemplateLgV2, Initialq_y), BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20, "templatelgv2/Inputs from LabVIEW/ctrl2/Initial s", 0, "", offsetof
    (BlockIO_TemplateLgV2, Initials), BLOCKIO_SIG, 0, 1, 2, 40, 0 },

  { 21, "templatelgv2/Inputs from LabVIEW/ctrl2/K_d/[3x3]", 0, "", offsetof
    (BlockIO_TemplateLgV2, ux3_h), BLOCKIO_SIG, 22, 9, 2, 42, 0 },

  { 22, "templatelgv2/Inputs from LabVIEW/ctrl2/K_i/[3x3]", 0, "", offsetof
    (BlockIO_TemplateLgV2, ux3_e), BLOCKIO_SIG, 22, 9, 2, 44, 0 },

  { 23, "templatelgv2/Inputs from LabVIEW/ctrl2/K_p/[3x3]", 0, "", offsetof
    (BlockIO_TemplateLgV2, ux3_m), BLOCKIO_SIG, 22, 9, 2, 46, 0 },

  { 24,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x1",
    0, "", offsetof(BlockIO_TemplateLgV2, l_x1), BLOCKIO_SIG, 0, 1, 2, 48, 0 },

  { 25,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_x2",
    0, "", offsetof(BlockIO_TemplateLgV2, l_x2), BLOCKIO_SIG, 0, 1, 2, 50, 0 },

  { 26,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/-l_y2",
    0, "", offsetof(BlockIO_TemplateLgV2, l_y2), BLOCKIO_SIG, 0, 1, 2, 52, 0 },

  { 27,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Thruster configuration matrix/3x5",
    0, "", offsetof(BlockIO_TemplateLgV2, x5), BLOCKIO_SIG, 26, 15, 2, 54, 0 },

  { 28,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_r",
    0, "", offsetof(BlockIO_TemplateLgV2, N_r), BLOCKIO_SIG, 0, 1, 2, 56, 0 },

  { 29,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-N_v",
    0, "", offsetof(BlockIO_TemplateLgV2, N_v), BLOCKIO_SIG, 0, 1, 2, 58, 0 },

  { 30,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-X_u",
    0, "", offsetof(BlockIO_TemplateLgV2, X_u), BLOCKIO_SIG, 0, 1, 2, 60, 0 },

  { 31,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_v",
    0, "", offsetof(BlockIO_TemplateLgV2, Y_v), BLOCKIO_SIG, 0, 1, 2, 62, 0 },

  { 32,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/-Y_vr",
    0, "", offsetof(BlockIO_TemplateLgV2, Y_vr), BLOCKIO_SIG, 0, 1, 2, 64, 0 },

  { 33,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Linear hydrodynamic dampning matrix/Linear Dampning matrix",
    0, "", offsetof(BlockIO_TemplateLgV2, LinearDampningmatrix), BLOCKIO_SIG, 22,
    9, 2, 66, 0 },

  { 34,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_11",
    0, "", offsetof(BlockIO_TemplateLgV2, M_11), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_22",
    0, "", offsetof(BlockIO_TemplateLgV2, M_22), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/m x_g",
    0, "", offsetof(BlockIO_TemplateLgV2, mx_g), BLOCKIO_SIG, 0, 1, 2, 72, 0 },

  { 37,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_32",
    0, "", offsetof(BlockIO_TemplateLgV2, M_32), BLOCKIO_SIG, 0, 1, 2, 74, 0 },

  { 38,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_23",
    0, "", offsetof(BlockIO_TemplateLgV2, M_23), BLOCKIO_SIG, 0, 1, 2, 76, 0 },

  { 39,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/M_33",
    0, "", offsetof(BlockIO_TemplateLgV2, M_33), BLOCKIO_SIG, 0, 1, 2, 78, 0 },

  { 40,
    "templatelgv2/Main Subsystems/C//S Enterprise 1 Matrices/Inertia matrix/3x3",
    0, "", offsetof(BlockIO_TemplateLgV2, x3), BLOCKIO_SIG, 22, 9, 2, 80, 0 },

  { 41,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x1",
    0, "", offsetof(BlockIO_TemplateLgV2, l_x1_k), BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_y2",
    0, "", offsetof(BlockIO_TemplateLgV2, l_y2_n), BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/-l_x2",
    0, "", offsetof(BlockIO_TemplateLgV2, l_x2_f), BLOCKIO_SIG, 0, 1, 2, 86, 0 },

  { 44,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/T_e/3x5",
    0, "", offsetof(BlockIO_TemplateLgV2, x5_j), BLOCKIO_SIG, 26, 15, 2, 88, 0 },

  { 45, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_1", 0,
    "u_1", offsetof(BlockIO_TemplateLgV2, u_1), BLOCKIO_SIG, 0, 1, 2, 90, 0 },

  { 46,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_1 to f_1",
    0, "", offsetof(BlockIO_TemplateLgV2, u_1tof_1), BLOCKIO_SIG, 0, 1, 2, 92, 0
  },

  { 47, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_2", 0,
    "u_2", offsetof(BlockIO_TemplateLgV2, u_2), BLOCKIO_SIG, 0, 1, 2, 94, 0 },

  { 48,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_2 to f_2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_2tof_2), BLOCKIO_SIG, 0, 1, 2, 96, 0
  },

  { 49, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_3", 0,
    "u_3", offsetof(BlockIO_TemplateLgV2, u_3), BLOCKIO_SIG, 0, 1, 2, 98, 0 },

  { 50,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_3 to f_3",
    0, "", offsetof(BlockIO_TemplateLgV2, u_3tof_3), BLOCKIO_SIG, 0, 1, 2, 100,
    0 },

  { 51, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_4", 0,
    "u_4", offsetof(BlockIO_TemplateLgV2, u_4), BLOCKIO_SIG, 0, 1, 2, 102, 0 },

  { 52,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_4 to f_4",
    0, "", offsetof(BlockIO_TemplateLgV2, u_4tof_4), BLOCKIO_SIG, 0, 1, 2, 104,
    0 },

  { 53, "templatelgv2/Main Subsystems/Control/PS3 u input control/Add", 0,
    "Bow Thruster direction", offsetof(BlockIO_TemplateLgV2,
    BowThrusterdirection), BLOCKIO_SIG, 0, 1, 2, 106, 0 },

  { 54, "templatelgv2/Main Subsystems/Control/PS3 u input control/PS3 u_5", 0,
    "u_5", offsetof(BlockIO_TemplateLgV2, u_5), BLOCKIO_SIG, 0, 1, 2, 108, 0 },

  { 55,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/u_act to f_act/u_5 to f_5",
    0, "", offsetof(BlockIO_TemplateLgV2, u_5tof_5), BLOCKIO_SIG, 0, 1, 2, 110,
    0 },

  { 56,
    "templatelgv2/Main Subsystems/Control/PS3 u input control/Subsystem/f_act to tau/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product), BLOCKIO_SIG, 20, 3, 2, 112,
    0 },

  { 57, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In", 0, "",
    offsetof(BlockIO_TemplateLgV2, QTMIn), BLOCKIO_SIG, 49, 9, 2, 114, 0 },

  { 58,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In3 x-coord [mm]",
    0, "", offsetof(BlockIO_TemplateLgV2, QTMIn3xcoordmm), BLOCKIO_SIG, 31, 1, 2,
    116, 0 },

  { 59, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/mm2m x", 0, "",
    offsetof(BlockIO_TemplateLgV2, mm2mx), BLOCKIO_SIG, 31, 1, 2, 118, 0 },

  { 60,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In4 y-coord [mm]",
    0, "", offsetof(BlockIO_TemplateLgV2, QTMIn4ycoordmm), BLOCKIO_SIG, 31, 1, 2,
    120, 0 },

  { 61, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/mm2m y", 0, "",
    offsetof(BlockIO_TemplateLgV2, mm2my), BLOCKIO_SIG, 31, 1, 2, 122, 0 },

  { 62,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In6 yaw [deg]",
    0, "", offsetof(BlockIO_TemplateLgV2, QTMIn6yawdeg), BLOCKIO_SIG, 31, 1, 2,
    124, 0 },

  { 63, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/d2r yaw", 0, "",
    offsetof(BlockIO_TemplateLgV2, d2ryaw), BLOCKIO_SIG, 31, 1, 2, 126, 0 },

  { 64, "templatelgv2/Main Subsystems/Naviagation/Navigation Switch/eta Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, etaSwitch), BLOCKIO_SIG, 20, 3, 2, 128,
    0 },

  { 65, "templatelgv2/Main Subsystems/Control/DP control/yaw angle", 0, "psi",
    offsetof(BlockIO_TemplateLgV2, psi), BLOCKIO_SIG, 0, 1, 2, 130, 0 },

  { 66,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation), BLOCKIO_SIG, 0, 1, 2, 132,
    0 },

  { 67,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign), BLOCKIO_SIG, 0, 1, 2, 134, 0 },

  { 68,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain), BLOCKIO_SIG, 0, 1, 2, 136, 0 },

  { 69,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1), BLOCKIO_SIG, 0, 1, 2, 138, 0 },

  { 70,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction), BLOCKIO_SIG, 0, 1, 2,
    140, 0 },

  { 71,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum), BLOCKIO_SIG, 0, 1, 2, 142, 0 },

  { 72, "templatelgv2/Main Subsystems/Control/DP control/Sum2", 0, "", offsetof
    (BlockIO_TemplateLgV2, Sum2), BLOCKIO_SIG, 20, 3, 2, 144, 0 },

  { 73,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_b), BLOCKIO_SIG, 0, 1, 2,
    146, 0 },

  { 74,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_g), BLOCKIO_SIG, 0, 1, 2, 148, 0
  },

  { 75,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_b), BLOCKIO_SIG, 0, 1, 2, 150, 0
  },

  { 76,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_b), BLOCKIO_SIG, 0, 1, 2, 152, 0
  },

  { 77,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_j), BLOCKIO_SIG, 0, 1, 2,
    154, 0 },

  { 78,
    "templatelgv2/Main Subsystems/Control/DP control/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_l), BLOCKIO_SIG, 0, 1, 2, 156, 0 },

  { 79,
    "templatelgv2/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_TemplateLgV2, Row1), BLOCKIO_SIG, 0, 1, 2, 158, 0 },

  { 80,
    "templatelgv2/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_TemplateLgV2, Row2), BLOCKIO_SIG, 0, 1, 2, 160, 0 },

  { 81,
    "templatelgv2/Main Subsystems/Control/DP control/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_TemplateLgV2, Row3), BLOCKIO_SIG, 0, 1, 2, 162, 0 },

  { 82, "templatelgv2/Main Subsystems/Control/DP control/Product", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product_n), BLOCKIO_SIG, 20, 3, 2, 164, 0 },

  { 83, "templatelgv2/Main Subsystems/Control/DP control/Integrator", 0, "",
    offsetof(BlockIO_TemplateLgV2, Integrator), BLOCKIO_SIG, 20, 3, 2, 166, 0 },

  { 84, "templatelgv2/Main Subsystems/Control/DP control/Product1", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product1), BLOCKIO_SIG, 20, 3, 2, 168, 0 },

  { 85, "templatelgv2/Main Subsystems/Control/DP control/Sum3", 0, "", offsetof
    (BlockIO_TemplateLgV2, Sum3), BLOCKIO_SIG, 20, 3, 2, 170, 0 },

  { 86,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator4",
    0, "nu", offsetof(BlockIO_TemplateLgV2, nu), BLOCKIO_SIG, 20, 3, 2, 172, 0 },

  { 87, "templatelgv2/Main Subsystems/Naviagation/Navigation Switch/nu Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, nuSwitch), BLOCKIO_SIG, 20, 3, 2, 174,
    0 },

  { 88, "templatelgv2/Main Subsystems/Control/DP control/Product2", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product2), BLOCKIO_SIG, 20, 3, 2, 176, 0 },

  { 89, "templatelgv2/Main Subsystems/Control/DP control/Sum1", 0, "", offsetof
    (BlockIO_TemplateLgV2, Sum1_g), BLOCKIO_SIG, 20, 3, 2, 178, 0 },

  { 90, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R11", 0, "", offsetof
    (BlockIO_TemplateLgV2, R11), BLOCKIO_SIG, 0, 1, 2, 180, 0 },

  { 91, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R21", 0, "", offsetof
    (BlockIO_TemplateLgV2, R21), BLOCKIO_SIG, 0, 1, 2, 182, 0 },

  { 92, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R12", 0, "", offsetof
    (BlockIO_TemplateLgV2, R12), BLOCKIO_SIG, 0, 1, 2, 184, 0 },

  { 93, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/-1", 0, "", offsetof
    (BlockIO_TemplateLgV2, u), BLOCKIO_SIG, 0, 1, 2, 186, 0 },

  { 94, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R22", 0, "", offsetof
    (BlockIO_TemplateLgV2, R22), BLOCKIO_SIG, 0, 1, 2, 188, 0 },

  { 95, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R(psi)", 0, "",
    offsetof(BlockIO_TemplateLgV2, Rpsi), BLOCKIO_SIG, 22, 9, 2, 190, 0 },

  { 96, "templatelgv2/Main Subsystems/Control/LgV2/R(psi)/R^T/Math Function", 0,
    "", offsetof(BlockIO_TemplateLgV2, MathFunction_k), BLOCKIO_SIG, 22, 9, 2,
    192, 0 },

  { 97, "templatelgv2/Main Subsystems/Control/LgV2/zeta/Integrator", 0, "",
    offsetof(BlockIO_TemplateLgV2, Integrator_g), BLOCKIO_SIG, 28, 3, 2, 194, 0
  },

  { 98, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Product", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product_e), BLOCKIO_SIG, 28, 3, 2, 196, 0 },

  { 99, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Gain", 0, "",
    offsetof(BlockIO_TemplateLgV2, Gain_d), BLOCKIO_SIG, 28, 3, 2, 198, 0 },

  { 100, "templatelgv2/Main Subsystems/Control/LgV2/Control law/4", 0, "",
    offsetof(BlockIO_TemplateLgV2, u_j), BLOCKIO_SIG, 0, 1, 2, 200, 0 },

  { 101, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Divide", 0, "",
    offsetof(BlockIO_TemplateLgV2, Divide), BLOCKIO_SIG, 0, 1, 2, 202, 0 },

  { 102, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Add1", 0, "",
    offsetof(BlockIO_TemplateLgV2, Add1), BLOCKIO_SIG, 22, 9, 2, 204, 0 },

  { 103, "templatelgv2/Main Subsystems/Control/LgV2/Product1", 0, "", offsetof
    (BlockIO_TemplateLgV2, Product1_j), BLOCKIO_SIG, 22, 9, 2, 206, 0 },

  { 104, "templatelgv2/Main Subsystems/Control/LgV2/Add3", 0, "", offsetof
    (BlockIO_TemplateLgV2, Add3), BLOCKIO_SIG, 22, 9, 2, 208, 0 },

  { 105,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_j), BLOCKIO_SIG, 0, 1, 2,
    210, 0 },

  { 106,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_k), BLOCKIO_SIG, 0, 1, 2, 212, 0
  },

  { 107,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_dc), BLOCKIO_SIG, 0, 1, 2, 214, 0
  },

  { 108,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_c), BLOCKIO_SIG, 0, 1, 2, 216, 0
  },

  { 109,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_kz), BLOCKIO_SIG, 0, 1, 2,
    218, 0 },

  { 110,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_e), BLOCKIO_SIG, 0, 1, 2, 220, 0 },

  { 111, "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Integrator", 0,
    "", offsetof(BlockIO_TemplateLgV2, Integrator_e), BLOCKIO_SIG, 25, 2, 2, 222,
    0 },

  { 112,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/x_2 - x_1",
    0, "", offsetof(BlockIO_TemplateLgV2, x_2x_1), BLOCKIO_SIG, 0, 1, 2, 224, 0
  },

  { 113,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d^s eq/y_2 - y_1",
    0, "", offsetof(BlockIO_TemplateLgV2, y_2y_1), BLOCKIO_SIG, 0, 1, 2, 226, 0
  },

  { 114,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_i), BLOCKIO_SIG, 0, 1, 2,
    228, 0 },

  { 115,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Rounding Function",
    0, "", offsetof(BlockIO_TemplateLgV2, RoundingFunction), BLOCKIO_SIG, 0, 1,
    2, 230, 0 },

  { 116,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_j), BLOCKIO_SIG, 25, 2, 2, 232,
    0 },

  { 117, "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Integrator1", 0,
    "", offsetof(BlockIO_TemplateLgV2, Integrator1), BLOCKIO_SIG, 0, 1, 2, 234,
    0 },

  { 118,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_i), BLOCKIO_SIG, 0, 1, 2, 236,
    0 },

  { 119,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/sin(s)",
    0, "", offsetof(BlockIO_TemplateLgV2, sins), BLOCKIO_SIG, 0, 1, 2, 238, 0 },

  { 120,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_ei), BLOCKIO_SIG, 0, 1, 2, 240,
    0 },

  { 121,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_m), BLOCKIO_SIG, 0, 1, 2, 242, 0
  },

  { 122,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/cos(s)",
    0, "", offsetof(BlockIO_TemplateLgV2, coss), BLOCKIO_SIG, 0, 1, 2, 244, 0 },

  { 123,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_l), BLOCKIO_SIG, 0, 1, 2, 246,
    0 },

  { 124,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Subract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subract), BLOCKIO_SIG, 0, 1, 2, 248, 0
  },

  { 125,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_h), BLOCKIO_SIG, 25, 2, 2,
    250, 0 },

  { 126,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s selcetor/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add), BLOCKIO_SIG, 25, 2, 2, 252, 0 },

  { 127,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateLgV2, TrigonometricFunction), BLOCKIO_SIG, 0,
    1, 2, 254, 0 },

  { 128,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_f), BLOCKIO_SIG, 0, 1, 2,
    256, 0 },

  { 129,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_gh), BLOCKIO_SIG, 0, 1, 2, 258, 0
  },

  { 130,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_bz), BLOCKIO_SIG, 0, 1, 2, 260, 0
  },

  { 131,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_n), BLOCKIO_SIG, 0, 1, 2, 262, 0
  },

  { 132,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_i), BLOCKIO_SIG, 0, 1, 2,
    264, 0 },

  { 133,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_g), BLOCKIO_SIG, 0, 1, 2, 266, 0 },

  { 134,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_n), BLOCKIO_SIG, 0, 1, 2,
    268, 0 },

  { 135,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_ga), BLOCKIO_SIG, 0, 1, 2, 270, 0
  },

  { 136,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_dx), BLOCKIO_SIG, 0, 1, 2, 272, 0
  },

  { 137,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_e), BLOCKIO_SIG, 0, 1, 2, 274, 0
  },

  { 138,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_a), BLOCKIO_SIG, 0, 1, 2,
    276, 0 },

  { 139,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_f), BLOCKIO_SIG, 0, 1, 2, 278, 0 },

  { 140,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2^T/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_e), BLOCKIO_SIG, 24, 4, 2,
    280, 0 },

  { 141,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/x_2 - x_1",
    0, "", offsetof(BlockIO_TemplateLgV2, x_2x_1_f), BLOCKIO_SIG, 0, 1, 2, 282,
    0 },

  { 142,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s",
    0, "", offsetof(BlockIO_TemplateLgV2, x_2x_1s), BLOCKIO_SIG, 0, 1, 2, 284, 0
  },

  { 143,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(x_2 - x_1) + s + x_1",
    0, "", offsetof(BlockIO_TemplateLgV2, x_2x_1sx_1), BLOCKIO_SIG, 0, 1, 2, 286,
    0 },

  { 144,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/y_2 - y_1",
    0, "", offsetof(BlockIO_TemplateLgV2, y_2y_1_g), BLOCKIO_SIG, 0, 1, 2, 288,
    0 },

  { 145,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s",
    0, "", offsetof(BlockIO_TemplateLgV2, y_2y_1s), BLOCKIO_SIG, 0, 1, 2, 290, 0
  },

  { 146,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/p_d eq/(y_2 - y_1) + s + y_1",
    0, "", offsetof(BlockIO_TemplateLgV2, y_2y_1sy_1), BLOCKIO_SIG, 0, 1, 2, 292,
    0 },

  { 147,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_ny), BLOCKIO_SIG, 25, 2, 2,
    294, 0 },

  { 148,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_m), BLOCKIO_SIG, 0, 1, 2, 296,
    0 },

  { 149,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/cos(s)",
    0, "", offsetof(BlockIO_TemplateLgV2, coss_l), BLOCKIO_SIG, 0, 1, 2, 298, 0
  },

  { 150,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_o), BLOCKIO_SIG, 0, 1, 2, 300,
    0 },

  { 151,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_p), BLOCKIO_SIG, 0, 1, 2, 302, 0 },

  { 152,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/sin(s)",
    0, "", offsetof(BlockIO_TemplateLgV2, sins_h), BLOCKIO_SIG, 0, 1, 2, 304, 0
  },

  { 153,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_b), BLOCKIO_SIG, 0, 1, 2, 306,
    0 },

  { 154,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d eq/Add1",
    0, "", offsetof(BlockIO_TemplateLgV2, Add1_d), BLOCKIO_SIG, 0, 1, 2, 308, 0
  },

  { 155,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Subract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subract_a), BLOCKIO_SIG, 0, 1, 2, 310,
    0 },

  { 156,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_lc), BLOCKIO_SIG, 25, 2, 2,
    312, 0 },

  { 157,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d selcetor/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_k), BLOCKIO_SIG, 25, 2, 2, 314, 0
  },

  { 158,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch), BLOCKIO_SIG, 0, 1, 2, 316, 0
  },

  { 159,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/Switch2",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch2), BLOCKIO_SIG, 0, 1, 2, 318, 0
  },

  { 160,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch_b), BLOCKIO_SIG, 0, 1, 2, 320,
    0 },

  { 161,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/Switch2",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch2_i), BLOCKIO_SIG, 0, 1, 2, 322,
    0 },

  { 162,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Subtract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract), BLOCKIO_SIG, 25, 2, 2, 324,
    0 },

  { 163,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon), BLOCKIO_SIG, 25, 2, 2, 326,
    0 },

  { 164,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSelector), BLOCKIO_SIG, 31, 1,
    2, 328, 0 },

  { 165,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateLgV2, TrigonometricFunction_i), BLOCKIO_SIG,
    31, 1, 2, 330, 0 },

  { 166,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_ig), BLOCKIO_SIG, 31, 1, 2,
    332, 0 },

  { 167,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_p), BLOCKIO_SIG, 31, 1, 2, 334, 0
  },

  { 168,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_mb), BLOCKIO_SIG, 31, 1, 2, 336,
    0 },

  { 169,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_p), BLOCKIO_SIG, 31, 1, 2, 338, 0
  },

  { 170,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_g), BLOCKIO_SIG, 31, 1, 2,
    340, 0 },

  { 171,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_h), BLOCKIO_SIG, 31, 1, 2, 342, 0
  },

  { 172,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/Subtract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract_c), BLOCKIO_SIG, 0, 1, 2, 344,
    0 },

  { 173,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_l), BLOCKIO_SIG, 0, 1, 2,
    346, 0 },

  { 174,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_gq), BLOCKIO_SIG, 0, 1, 2, 348, 0
  },

  { 175,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_o), BLOCKIO_SIG, 0, 1, 2, 350, 0
  },

  { 176,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_b0), BLOCKIO_SIG, 0, 1, 2, 352, 0
  },

  { 177,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_j0), BLOCKIO_SIG, 0, 1, 2,
    354, 0 },

  { 178,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los eq/rad to [-pi pi]2/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_a), BLOCKIO_SIG, 0, 1, 2, 356, 0 },

  { 179,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, VectorConcatenate), BLOCKIO_SIG, 20, 3,
    2, 358, 0 },

  { 180, "templatelgv2/Main Subsystems/Control/LgV2/z_1/Subtract", 0, "",
    offsetof(BlockIO_TemplateLgV2, Subtract_d), BLOCKIO_SIG, 20, 3, 2, 360, 0 },

  { 181,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_m), BLOCKIO_SIG, 0, 1, 2,
    362, 0 },

  { 182,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_d), BLOCKIO_SIG, 0, 1, 2, 364, 0
  },

  { 183,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_f), BLOCKIO_SIG, 0, 1, 2, 366, 0
  },

  { 184,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_m), BLOCKIO_SIG, 0, 1, 2, 368, 0
  },

  { 185,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_p), BLOCKIO_SIG, 0, 1, 2,
    370, 0 },

  { 186,
    "templatelgv2/Main Subsystems/Control/LgV2/z_1/Heading to -pi//pi1/rad to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_ag), BLOCKIO_SIG, 0, 1, 2, 372, 0
  },

  { 187, "templatelgv2/Main Subsystems/Control/LgV2/z_1/Product", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product_a), BLOCKIO_SIG, 20, 3, 2, 374, 0 },

  { 188, "templatelgv2/Main Subsystems/Control/LgV2/alpha/Product1", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product1_g), BLOCKIO_SIG, 20, 3, 2, 376, 0 },

  { 189,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qx",
    0, "", offsetof(BlockIO_TemplateLgV2, f_qx), BLOCKIO_SIG, 0, 1, 2, 378, 0 },

  { 190,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/f_qy",
    0, "", offsetof(BlockIO_TemplateLgV2, f_qy), BLOCKIO_SIG, 0, 1, 2, 380, 0 },

  { 191,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_l), BLOCKIO_SIG, 25, 2, 2, 382,
    0 },

  { 192,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateLgV2, Delta2), BLOCKIO_SIG, 0, 1, 2, 384, 0
  },

  { 193,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_n2), BLOCKIO_SIG, 31, 1, 2,
    386, 0 },

  { 194,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_b), BLOCKIO_SIG, 31, 1, 2, 388, 0
  },

  { 195,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_d), BLOCKIO_SIG, 31, 1, 2, 390,
    0 },

  { 196,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector1",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSelector1), BLOCKIO_SIG, 29,
    2, 2, 392, 0 },

  { 197,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_p), BLOCKIO_SIG, 29, 2, 2, 394,
    0 },

  { 198,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q eq/-1",
    0, "", offsetof(BlockIO_TemplateLgV2, u_c), BLOCKIO_SIG, 29, 2, 2, 396, 0 },

  { 199,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, VectorConcatenate_l), BLOCKIO_SIG, 20,
    3, 2, 398, 0 },

  { 200,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_g), BLOCKIO_SIG, 32, 2, 2, 400,
    0 },

  { 201,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_l), BLOCKIO_SIG, 0, 1, 2, 402,
    0 },

  { 202,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/cos(s)",
    0, "", offsetof(BlockIO_TemplateLgV2, coss_f), BLOCKIO_SIG, 0, 1, 2, 404, 0
  },

  { 203,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_f), BLOCKIO_SIG, 0, 1, 2,
    406, 0 },

  { 204,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_go), BLOCKIO_SIG, 0, 1, 2, 408,
    0 },

  { 205,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_j), BLOCKIO_SIG, 0, 1, 2, 410, 0
  },

  { 206,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/sin(s)",
    0, "", offsetof(BlockIO_TemplateLgV2, sins_n), BLOCKIO_SIG, 0, 1, 2, 412, 0
  },

  { 207,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_i), BLOCKIO_SIG, 0, 1, 2, 414,
    0 },

  { 208,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^2 eq/Gain1",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain1_f), BLOCKIO_SIG, 0, 1, 2, 416, 0
  },

  { 209,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Subract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subract_d), BLOCKIO_SIG, 0, 1, 2, 418,
    0 },

  { 210,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_c), BLOCKIO_SIG, 25, 2, 2,
    420, 0 },

  { 211,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^2 selcetor/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_o), BLOCKIO_SIG, 32, 2, 2, 422, 0
  },

  { 212,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_TemplateLgV2, x_dsy_ds2), BLOCKIO_SIG, 31, 1, 2, 424,
    0 },

  { 213,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/x_d^s^2 + y_d^s",
    0, "", offsetof(BlockIO_TemplateLgV2, x_ds2y_ds), BLOCKIO_SIG, 31, 1, 2, 426,
    0 },

  { 214,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s + y_d^s^2 ) - ( x_d^s^2 + y_d^s )",
    0, "", offsetof(BlockIO_TemplateLgV2, x_dsy_ds2x_ds2y_ds), BLOCKIO_SIG, 31,
    1, 2, 428, 0 },

  { 215,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2",
    0, "", offsetof(BlockIO_TemplateLgV2, x_ds2), BLOCKIO_SIG, 0, 1, 2, 430, 0 },

  { 216,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( y_d^s )^2",
    0, "", offsetof(BlockIO_TemplateLgV2, y_ds2), BLOCKIO_SIG, 0, 1, 2, 432, 0 },

  { 217,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/( x_d^s )^2 + ( y_d^s )^2",
    0, "", offsetof(BlockIO_TemplateLgV2, x_ds2y_ds2), BLOCKIO_SIG, 0, 1, 2, 434,
    0 },

  { 218,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_c), BLOCKIO_SIG, 31, 1, 2, 436,
    0 },

  { 219,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateLgV2, Delta2_i), BLOCKIO_SIG, 0, 1, 2, 438,
    0 },

  { 220,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_n2_h), BLOCKIO_SIG, 31, 1, 2,
    440, 0 },

  { 221,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_l), BLOCKIO_SIG, 31, 1, 2, 442, 0
  },

  { 222,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_e), BLOCKIO_SIG, 31, 1, 2, 444,
    0 },

  { 223,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2^T/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_fh), BLOCKIO_SIG, 24, 4,
    2, 446, 0 },

  { 224,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_oe), BLOCKIO_SIG, 25, 2, 2,
    448, 0 },

  { 225,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_f), BLOCKIO_SIG, 25, 2, 2,
    450, 0 },

  { 226,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s eq/Subtract1",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract1), BLOCKIO_SIG, 25, 2, 2, 452,
    0 },

  { 227,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector2",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSelector2), BLOCKIO_SIG, 31,
    1, 2, 454, 0 },

  { 228,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_ex), BLOCKIO_SIG, 31, 1, 2,
    456, 0 },

  { 229,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s eq/Subtract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract_k), BLOCKIO_SIG, 31, 1, 2,
    458, 0 },

  { 230,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_n2_j), BLOCKIO_SIG, 31, 1, 2,
    460, 0 },

  { 231,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateLgV2, Delta2_n), BLOCKIO_SIG, 0, 1, 2, 462,
    0 },

  { 232,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_i), BLOCKIO_SIG, 31, 1, 2, 464, 0
  },

  { 233,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/sqrt",
    0, "", offsetof(BlockIO_TemplateLgV2, sqrt_m), BLOCKIO_SIG, 31, 1, 2, 466, 0
  },

  { 234,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_dn), BLOCKIO_SIG, 31, 1, 2, 468,
    0 },

  { 235,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_o), BLOCKIO_SIG, 29, 2, 2,
    470, 0 },

  { 236,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_nyn), BLOCKIO_SIG, 0, 1, 2,
    472, 0 },

  { 237,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Straight path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_TemplateLgV2, sqrt_c), BLOCKIO_SIG, 0, 1, 2, 474, 0
  },

  { 238,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_i), BLOCKIO_SIG, 0, 1, 2, 476,
    0 },

  { 239,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_kk), BLOCKIO_SIG, 29, 2,
    2, 478, 0 },

  { 240,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_b), BLOCKIO_SIG, 0, 1, 2, 480,
    0 },

  { 241,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/|p_d^s| eq/sqrt",
    0, "", offsetof(BlockIO_TemplateLgV2, sqrt_j), BLOCKIO_SIG, 0, 1, 2, 482, 0
  },

  { 242,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Subract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subract_o), BLOCKIO_SIG, 0, 1, 2, 484,
    0 },

  { 243,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_g0), BLOCKIO_SIG, 0, 1, 2,
    486, 0 },

  { 244,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor1/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_d), BLOCKIO_SIG, 0, 1, 2, 488, 0 },

  { 245,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_b), BLOCKIO_SIG, 0, 1, 2, 490,
    0 },

  { 246,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_c), BLOCKIO_SIG, 0, 1, 2, 492,
    0 },

  { 247,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_fi), BLOCKIO_SIG, 29, 2,
    2, 494, 0 },

  { 248,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_h), BLOCKIO_SIG, 29, 2, 2, 496,
    0 },

  { 249,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_k), BLOCKIO_SIG, 0, 1, 2, 498,
    0 },

  { 250,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s eq/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_p), BLOCKIO_SIG, 0, 1, 2, 500, 0
  },

  { 251,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s eq/Subtract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract_o), BLOCKIO_SIG, 0, 1, 2, 502,
    0 },

  { 252,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, VectorConcatenate_a), BLOCKIO_SIG, 28,
    3, 2, 504, 0 },

  { 253, "templatelgv2/Main Subsystems/Control/LgV2/alpha/Add", 0, "", offsetof
    (BlockIO_TemplateLgV2, Add_m), BLOCKIO_SIG, 28, 3, 2, 506, 0 },

  { 254, "templatelgv2/Main Subsystems/Control/LgV2/alpha/Product2", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product2_a), BLOCKIO_SIG, 28, 3, 2, 508, 0 },

  { 255, "templatelgv2/Main Subsystems/Control/LgV2/alpha/Sum", 0, "", offsetof
    (BlockIO_TemplateLgV2, Sum_b), BLOCKIO_SIG, 28, 3, 2, 510, 0 },

  { 256, "templatelgv2/Main Subsystems/Control/LgV2/z_2/Subtract", 0, "",
    offsetof(BlockIO_TemplateLgV2, Subtract_i), BLOCKIO_SIG, 28, 3, 2, 512, 0 },

  { 257, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Product1", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product1_a), BLOCKIO_SIG, 28, 3, 2, 514, 0 },

  { 258, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Gain1", 0, "",
    offsetof(BlockIO_TemplateLgV2, Gain1_k), BLOCKIO_SIG, 28, 3, 2, 516, 0 },

  { 259, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Product2", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product2_d), BLOCKIO_SIG, 20, 3, 2, 518, 0 },

  { 260, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S12", 0, "",
    offsetof(BlockIO_TemplateLgV2, S12), BLOCKIO_SIG, 0, 1, 2, 520, 0 },

  { 261, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S(r)/S(r)", 0, "",
    offsetof(BlockIO_TemplateLgV2, Sr), BLOCKIO_SIG, 22, 9, 2, 522, 0 },

  { 262, "templatelgv2/Main Subsystems/Control/LgV2/sigma/S^T/S^T/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_h), BLOCKIO_SIG, 22, 9, 2,
    524, 0 },

  { 263, "templatelgv2/Main Subsystems/Control/LgV2/sigma/Product", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product_af), BLOCKIO_SIG, 20, 3, 2, 526, 0 },

  { 264, "templatelgv2/Main Subsystems/Control/LgV2/sigma/Add", 0, "", offsetof
    (BlockIO_TemplateLgV2, Add_iq), BLOCKIO_SIG, 20, 3, 2, 528, 0 },

  { 265, "templatelgv2/Main Subsystems/Control/LgV2/sigma/Product2", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product2_n), BLOCKIO_SIG, 20, 3, 2, 530, 0 },

  { 266, "templatelgv2/Main Subsystems/Control/LgV2/sigma/Add1", 0, "", offsetof
    (BlockIO_TemplateLgV2, Add1_b), BLOCKIO_SIG, 28, 3, 2, 532, 0 },

  { 267, "templatelgv2/Main Subsystems/Control/LgV2/sigma/Product3", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product3), BLOCKIO_SIG, 28, 3, 2, 534, 0 },

  { 268,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateLgV2, TrigonometricFunction_a), BLOCKIO_SIG,
    0, 1, 2, 536, 0 },

  { 269,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_TemplateLgV2, TrigonometricFunction1), BLOCKIO_SIG,
    0, 1, 2, 538, 0 },

  { 270,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/Derivative",
    0, "", offsetof(BlockIO_TemplateLgV2, Derivative), BLOCKIO_SIG, 0, 1, 2, 540,
    0 },

  { 271,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^t eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_p3), BLOCKIO_SIG, 25, 2, 2,
    542, 0 },

  { 272,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, VectorConcatenate_g), BLOCKIO_SIG, 20,
    3, 2, 544, 0 },

  { 273,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_n2_b), BLOCKIO_SIG, 31, 1, 2,
    546, 0 },

  { 274,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateLgV2, Delta2_p), BLOCKIO_SIG, 0, 1, 2, 548,
    0 },

  { 275,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_e), BLOCKIO_SIG, 31, 1, 2, 550, 0
  },

  { 276,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/sqrt",
    0, "", offsetof(BlockIO_TemplateLgV2, sqrt_o), BLOCKIO_SIG, 31, 1, 2, 552, 0
  },

  { 277,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_i), BLOCKIO_SIG, 31, 1, 2, 554,
    0 },

  { 278,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^t eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_m), BLOCKIO_SIG, 0, 1, 2, 556,
    0 },

  { 279,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^t eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_ll), BLOCKIO_SIG, 0, 1, 2, 558,
    0 },

  { 280,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^t eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, VectorConcatenate_c), BLOCKIO_SIG, 28,
    3, 2, 560, 0 },

  { 281, "templatelgv2/Main Subsystems/Control/LgV2/sigma/Add2", 0, "", offsetof
    (BlockIO_TemplateLgV2, Add2), BLOCKIO_SIG, 28, 3, 2, 562, 0 },

  { 282, "templatelgv2/Main Subsystems/Control/LgV2/sigma/Product4", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product4), BLOCKIO_SIG, 28, 3, 2, 564, 0 },

  { 283, "templatelgv2/Main Subsystems/Control/LgV2/sigma/Sum", 0, "", offsetof
    (BlockIO_TemplateLgV2, Sum_n), BLOCKIO_SIG, 28, 3, 2, 566, 0 },

  { 284, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Product4", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product4_d), BLOCKIO_SIG, 28, 3, 2, 568, 0 },

  { 285,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Matrix Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, MatrixConcatenate), BLOCKIO_SIG, 30, 6,
    2, 570, 0 },

  { 286, "templatelgv2/Main Subsystems/Control/LgV2/alpha^q/Product3", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product3_l), BLOCKIO_SIG, 30, 6, 2, 572, 0 },

  { 287,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_TemplateLgV2, TrigonometricFunction1_g), BLOCKIO_SIG,
    0, 1, 2, 574, 0 },

  { 288,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_h), BLOCKIO_SIG, 0, 1, 2, 576, 0
  },

  { 289,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_ip), BLOCKIO_SIG, 29, 2, 2,
    578, 0 },

  { 290,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateLgV2, TrigonometricFunction_o), BLOCKIO_SIG,
    0, 1, 2, 580, 0 },

  { 291,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_f), BLOCKIO_SIG, 29, 2, 2,
    582, 0 },

  { 292,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, MatrixConcatenate_g), BLOCKIO_SIG, 24,
    4, 2, 584, 0 },

  { 293,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^q eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_m), BLOCKIO_SIG, 24, 4, 2, 586,
    0 },

  { 294,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/f_q^T/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_pu), BLOCKIO_SIG, 29, 2,
    2, 588, 0 },

  { 295,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_b), BLOCKIO_SIG, 31, 1, 2,
    590, 0 },

  { 296,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_c), BLOCKIO_SIG, 32, 2, 2,
    592, 0 },

  { 297,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product3",
    0, "", offsetof(BlockIO_TemplateLgV2, Product3_m), BLOCKIO_SIG, 24, 4, 2,
    594, 0 },

  { 298,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product4",
    0, "", offsetof(BlockIO_TemplateLgV2, Product4_c), BLOCKIO_SIG, 24, 4, 2,
    596, 0 },

  { 299,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_f), BLOCKIO_SIG, 24, 4, 2, 598, 0 },

  { 300,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateLgV2, Delta2_c), BLOCKIO_SIG, 0, 1, 2, 600,
    0 },

  { 301,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_n2_o), BLOCKIO_SIG, 31, 1, 2,
    602, 0 },

  { 302,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_g), BLOCKIO_SIG, 31, 1, 2, 604, 0
  },

  { 303,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/( )^2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_l), BLOCKIO_SIG, 31, 1, 2, 606, 0 },

  { 304,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_f), BLOCKIO_SIG, 24, 4, 2, 608,
    0 },

  { 305,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_o), BLOCKIO_SIG, 24, 4, 2,
    610, 0 },

  { 306,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Divide1",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide1), BLOCKIO_SIG, 24, 4, 2, 612,
    0 },

  { 307,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^q^2 eq/Subtract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract_n), BLOCKIO_SIG, 24, 4, 2,
    614, 0 },

  { 308,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/psi_los^q^2T/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_n), BLOCKIO_SIG, 24, 4, 2,
    616, 0 },

  { 309,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_f), BLOCKIO_SIG, 29, 2, 2, 618,
    0 },

  { 310,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_a4), BLOCKIO_SIG, 29, 2, 2,
    620, 0 },

  { 311,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_ob), BLOCKIO_SIG, 29, 2, 2, 622, 0
  },

  { 312,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, MatrixConcatenate_p), BLOCKIO_SIG, 30,
    6, 2, 624, 0 },

  { 313,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_d), BLOCKIO_SIG, 29, 2, 2, 626,
    0 },

  { 314,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_d), BLOCKIO_SIG, 29, 2, 2, 628, 0 },

  { 315,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Delta^2",
    0, "", offsetof(BlockIO_TemplateLgV2, Delta2_g), BLOCKIO_SIG, 0, 1, 2, 630,
    0 },

  { 316,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_n2_f), BLOCKIO_SIG, 31, 1, 2,
    632, 0 },

  { 317,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_g2), BLOCKIO_SIG, 31, 1, 2, 634, 0
  },

  { 318,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/( )^2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_o), BLOCKIO_SIG, 31, 1, 2, 636, 0 },

  { 319,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_mz), BLOCKIO_SIG, 29, 2, 2, 638,
    0 },

  { 320,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^qs = epsilon^sq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_bd), BLOCKIO_SIG, 24, 4, 2,
    640, 0 },

  { 321,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector3",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSelector3), BLOCKIO_SIG, 29,
    2, 2, 642, 0 },

  { 322,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_e), BLOCKIO_SIG, 29, 2, 2,
    644, 0 },

  { 323,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Divide1",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide1_p), BLOCKIO_SIG, 29, 2, 2, 646,
    0 },

  { 324,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^qs = psi_los^sq/Subtract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract_p), BLOCKIO_SIG, 29, 2, 2,
    648, 0 },

  { 325,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_mw), BLOCKIO_SIG, 29, 2, 2,
    650, 0 },

  { 326,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_hh), BLOCKIO_SIG, 29, 2, 2,
    652, 0 },

  { 327,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_n2_h1), BLOCKIO_SIG, 31, 1, 2,
    654, 0 },

  { 328,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateLgV2, Delta2_f), BLOCKIO_SIG, 0, 1, 2, 656,
    0 },

  { 329,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_obi), BLOCKIO_SIG, 31, 1, 2, 658,
    0 },

  { 330,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/^3//2",
    0, "", offsetof(BlockIO_TemplateLgV2, u2), BLOCKIO_SIG, 31, 1, 2, 660, 0 },

  { 331,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_n), BLOCKIO_SIG, 29, 2, 2, 662,
    0 },

  { 332,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_dg), BLOCKIO_SIG, 29, 2, 2,
    664, 0 },

  { 333,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Transpose/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_l), BLOCKIO_SIG, 29, 2, 2,
    666, 0 },

  { 334,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_hd), BLOCKIO_SIG, 29, 2, 2, 668,
    0 },

  { 335,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_fe), BLOCKIO_SIG, 29, 2, 2,
    670, 0 },

  { 336,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^q eq/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_a), BLOCKIO_SIG, 29, 2, 2, 672, 0
  },

  { 337,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^q eq/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_fb), BLOCKIO_SIG, 29, 2, 2, 674, 0
  },

  { 338,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_k), BLOCKIO_SIG, 29, 2, 2,
    676, 0 },

  { 339,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_dn), BLOCKIO_SIG, 29, 2, 2, 678, 0
  },

  { 340,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^q eq/Matrix Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, MatrixConcatenate_ps), BLOCKIO_SIG, 30,
    6, 2, 680, 0 },

  { 341, "templatelgv2/Main Subsystems/Control/LgV2/alpha^q/Add2", 0, "",
    offsetof(BlockIO_TemplateLgV2, Add2_c), BLOCKIO_SIG, 30, 6, 2, 682, 0 },

  { 342, "templatelgv2/Main Subsystems/Control/LgV2/alpha^q/Product4", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product4_p), BLOCKIO_SIG, 30, 6, 2, 684, 0 },

  { 343, "templatelgv2/Main Subsystems/Control/LgV2/alpha^q/Add3", 0, "",
    offsetof(BlockIO_TemplateLgV2, Add3_i), BLOCKIO_SIG, 30, 6, 2, 686, 0 },

  { 344, "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Integrator2", 0,
    "", offsetof(BlockIO_TemplateLgV2, Integrator2), BLOCKIO_SIG, 32, 2, 2, 688,
    0 },

  { 345, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Add2", 0, "",
    offsetof(BlockIO_TemplateLgV2, Add2_ct), BLOCKIO_SIG, 32, 2, 2, 690, 0 },

  { 346, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Product5", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product5), BLOCKIO_SIG, 28, 3, 2, 692, 0 },

  { 347,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Virtual Vessel/Vector Concatenate1",
    0, "", offsetof(BlockIO_TemplateLgV2, VectorConcatenate1), BLOCKIO_SIG, 28,
    3, 2, 694, 0 },

  { 348, "templatelgv2/Main Subsystems/Control/LgV2/alpha^s/Product3", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product3_lv), BLOCKIO_SIG, 28, 3, 2, 696, 0 },

  { 349,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function1",
    0, "", offsetof(BlockIO_TemplateLgV2, TrigonometricFunction1_h), BLOCKIO_SIG,
    0, 1, 2, 698, 0 },

  { 350,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_c), BLOCKIO_SIG, 0, 1, 2, 700, 0
  },

  { 351,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_kn), BLOCKIO_SIG, 31, 1, 2,
    702, 0 },

  { 352,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Trigonometric Function",
    0, "", offsetof(BlockIO_TemplateLgV2, TrigonometricFunction_f), BLOCKIO_SIG,
    0, 1, 2, 704, 0 },

  { 353,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_iw), BLOCKIO_SIG, 31, 1, 2,
    706, 0 },

  { 354,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic LOS assigment for qdot/f_q^s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_ec), BLOCKIO_SIG, 25, 2, 2,
    708, 0 },

  { 355,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_np), BLOCKIO_SIG, 0, 1, 2, 710,
    0 },

  { 356,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_lh), BLOCKIO_SIG, 0, 1, 2,
    712, 0 },

  { 357,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxilary functions g_q/g_q^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, VectorConcatenate_av), BLOCKIO_SIG, 20,
    3, 2, 714, 0 },

  { 358,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_fc), BLOCKIO_SIG, 32, 2, 2,
    716, 0 },

  { 359,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_e), BLOCKIO_SIG, 0, 1, 2, 718,
    0 },

  { 360,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/sin(s)3",
    0, "", offsetof(BlockIO_TemplateLgV2, sins3), BLOCKIO_SIG, 0, 1, 2, 720, 0 },

  { 361,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_b), BLOCKIO_SIG, 0, 1, 2,
    722, 0 },

  { 362,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_lg), BLOCKIO_SIG, 0, 1, 2, 724,
    0 },

  { 363,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/cos(s)3",
    0, "", offsetof(BlockIO_TemplateLgV2, coss3), BLOCKIO_SIG, 0, 1, 2, 726, 0 },

  { 364,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_kz), BLOCKIO_SIG, 0, 1, 2,
    728, 0 },

  { 365,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Ellipse path/p_d^s^3 eq/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_dq), BLOCKIO_SIG, 0, 1, 2, 730, 0
  },

  { 366,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Subract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subract_m), BLOCKIO_SIG, 0, 1, 2, 732,
    0 },

  { 367,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_jv), BLOCKIO_SIG, 25, 2, 2,
    734, 0 },

  { 368,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/p_d^s^3 selcetor/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_ms), BLOCKIO_SIG, 32, 2, 2, 736, 0
  },

  { 369,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + y_d^s^3",
    0, "", offsetof(BlockIO_TemplateLgV2, x_dsy_ds3), BLOCKIO_SIG, 31, 1, 2, 738,
    0 },

  { 370,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s^3 + y_d^s",
    0, "", offsetof(BlockIO_TemplateLgV2, x_ds3y_ds), BLOCKIO_SIG, 31, 1, 2, 740,
    0 },

  { 371,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + y_d^s^3  ) - ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_TemplateLgV2, x_dsy_ds3x_ds3y_ds), BLOCKIO_SIG, 31,
    1, 2, 742, 0 },

  { 372,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_kr), BLOCKIO_SIG, 31, 1, 2,
    744, 0 },

  { 373,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/x_d^s + x_d^s^2",
    0, "", offsetof(BlockIO_TemplateLgV2, x_dsx_ds2), BLOCKIO_SIG, 31, 1, 2, 746,
    0 },

  { 374,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/y_d^s + y_d^s^2",
    0, "", offsetof(BlockIO_TemplateLgV2, y_dsy_ds2), BLOCKIO_SIG, 31, 1, 2, 748,
    0 },

  { 375,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/( x_d^s + x_d^s^2 ) + ( x_d^s^3 + y_d^s )",
    0, "", offsetof(BlockIO_TemplateLgV2, x_dsx_ds2x_ds3y_ds), BLOCKIO_SIG, 31,
    1, 2, 750, 0 },

  { 376,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/+ 2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_e), BLOCKIO_SIG, 31, 1, 2, 752, 0 },

  { 377,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_az), BLOCKIO_SIG, 31, 1, 2,
    754, 0 },

  { 378,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Subtract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract_oo), BLOCKIO_SIG, 31, 1, 2,
    756, 0 },

  { 379,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/[ ( x_d^s )^2 + ( y_d^s )^2 ]^2",
    0, "", offsetof(BlockIO_TemplateLgV2, x_ds2y_ds22), BLOCKIO_SIG, 0, 1, 2,
    758, 0 },

  { 380,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Heading/psi_d^s^2 eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_o), BLOCKIO_SIG, 31, 1, 2, 760,
    0 },

  { 381,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/(epsilon_n^s)^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_ns2), BLOCKIO_SIG, 31, 1, 2,
    762, 0 },

  { 382,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_iu), BLOCKIO_SIG, 31, 1, 2,
    764, 0 },

  { 383,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_lx), BLOCKIO_SIG, 31, 1, 2, 766, 0 },

  { 384,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateLgV2, Delta2_ct), BLOCKIO_SIG, 0, 1, 2, 768,
    0 },

  { 385,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_n2_o4), BLOCKIO_SIG, 31, 1, 2,
    770, 0 },

  { 386,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_lv), BLOCKIO_SIG, 31, 1, 2, 772, 0
  },

  { 387,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/( )^2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_b), BLOCKIO_SIG, 31, 1, 2, 774, 0 },

  { 388,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_j), BLOCKIO_SIG, 31, 1, 2, 776,
    0 },

  { 389,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)^T/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_c2), BLOCKIO_SIG, 24, 4,
    2, 778, 0 },

  { 390,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_aa), BLOCKIO_SIG, 24, 4, 2,
    780, 0 },

  { 391,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_a), BLOCKIO_SIG, 24, 4, 2, 782, 0
  },

  { 392,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_gi), BLOCKIO_SIG, 25, 2, 2,
    784, 0 },

  { 393,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_j), BLOCKIO_SIG, 25, 2, 2,
    786, 0 },

  { 394,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_m), BLOCKIO_SIG, 25, 2, 2, 788, 0 },

  { 395,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Product3",
    0, "", offsetof(BlockIO_TemplateLgV2, Product3_mb), BLOCKIO_SIG, 32, 2, 2,
    790, 0 },

  { 396,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_b0), BLOCKIO_SIG, 32, 2, 2, 792, 0
  },

  { 397,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/epsilon^s^2 eq/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_fw), BLOCKIO_SIG, 32, 2, 2, 794,
    0 },

  { 398,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/Multiport Selector4",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSelector4), BLOCKIO_SIG, 31,
    1, 2, 796, 0 },

  { 399,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_ci), BLOCKIO_SIG, 31, 1, 2,
    798, 0 },

  { 400,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Divide1",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide1_o), BLOCKIO_SIG, 31, 1, 2, 800,
    0 },

  { 401,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/LOS heading/psi_los^s^2 eq/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_d), BLOCKIO_SIG, 31, 1, 2, 802, 0
  },

  { 402,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_cw), BLOCKIO_SIG, 0, 1, 2, 804,
    0 },

  { 403,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/p_d^s^T/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_bf), BLOCKIO_SIG, 29, 2,
    2, 806, 0 },

  { 404,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_iw), BLOCKIO_SIG, 31, 1, 2,
    808, 0 },

  { 405,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/|p_d^s|^3",
    0, "", offsetof(BlockIO_TemplateLgV2, p_ds3), BLOCKIO_SIG, 0, 1, 2, 810, 0 },

  { 406,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_eo), BLOCKIO_SIG, 0, 1, 2, 812,
    0 },

  { 407,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_pe), BLOCKIO_SIG, 0, 1, 2, 814,
    0 },

  { 408,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Speed assigment/v_s^s eq/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_i), BLOCKIO_SIG, 0, 1, 2, 816, 0
  },

  { 409,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/epsilon_n^2",
    0, "", offsetof(BlockIO_TemplateLgV2, epsilon_n2_l), BLOCKIO_SIG, 31, 1, 2,
    818, 0 },

  { 410,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Delta^2",
    0, "", offsetof(BlockIO_TemplateLgV2, Delta2_im), BLOCKIO_SIG, 0, 1, 2, 820,
    0 },

  { 411,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Add",
    0, "", offsetof(BlockIO_TemplateLgV2, Add_i4), BLOCKIO_SIG, 31, 1, 2, 822, 0
  },

  { 412,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_io), BLOCKIO_SIG, 31, 1,
    2, 824, 0 },

  { 413,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide_g), BLOCKIO_SIG, 0, 1, 2, 826,
    0 },

  { 414,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_m), BLOCKIO_SIG, 0, 1, 2, 828,
    0 },

  { 415,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_e3), BLOCKIO_SIG, 31, 1, 2,
    830, 0 },

  { 416,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/^3//2",
    0, "", offsetof(BlockIO_TemplateLgV2, u2_m), BLOCKIO_SIG, 31, 1, 2, 832, 0 },

  { 417,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Divide1",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide1_g), BLOCKIO_SIG, 31, 1, 2, 834,
    0 },

  { 418,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Product3",
    0, "", offsetof(BlockIO_TemplateLgV2, Product3_a), BLOCKIO_SIG, 0, 1, 2, 836,
    0 },

  { 419,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_ii), BLOCKIO_SIG, 0, 1, 2,
    838, 0 },

  { 420,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose2/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_no), BLOCKIO_SIG, 29, 2,
    2, 840, 0 },

  { 421,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide2",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide2), BLOCKIO_SIG, 29, 2, 2, 842,
    0 },

  { 422,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Transpose1/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_jk), BLOCKIO_SIG, 29, 2,
    2, 844, 0 },

  { 423,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_nl), BLOCKIO_SIG, 29, 2, 2,
    846, 0 },

  { 424,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_po), BLOCKIO_SIG, 0, 1, 2,
    848, 0 },

  { 425,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Divide1",
    0, "", offsetof(BlockIO_TemplateLgV2, Divide1_pb), BLOCKIO_SIG, 29, 2, 2,
    850, 0 },

  { 426,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract1",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract1_f), BLOCKIO_SIG, 29, 2, 2,
    852, 0 },

  { 427,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_dl), BLOCKIO_SIG, 0, 1, 2, 854,
    0 },

  { 428,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Gradient update law for sdot/omega_s^s eq/Subtract",
    0, "", offsetof(BlockIO_TemplateLgV2, Subtract_g), BLOCKIO_SIG, 0, 1, 2, 856,
    0 },

  { 429,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Dynamic assigment for sdot/f_s^s eq/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_h2), BLOCKIO_SIG, 0, 1, 2, 858, 0
  },

  { 430,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_ok), BLOCKIO_SIG, 0, 1, 2,
    860, 0 },

  { 431,
    "templatelgv2/Main Subsystems/Control/LgV2/Auxiliary function g_s/g_s^s eq/Vector Concatenate",
    0, "", offsetof(BlockIO_TemplateLgV2, VectorConcatenate_h), BLOCKIO_SIG, 28,
    3, 2, 862, 0 },

  { 432, "templatelgv2/Main Subsystems/Control/LgV2/alpha^s/Add2", 0, "",
    offsetof(BlockIO_TemplateLgV2, Add2_l), BLOCKIO_SIG, 28, 3, 2, 864, 0 },

  { 433, "templatelgv2/Main Subsystems/Control/LgV2/alpha^s/Product4", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product4_h), BLOCKIO_SIG, 28, 3, 2, 866, 0 },

  { 434, "templatelgv2/Main Subsystems/Control/LgV2/alpha^s/Add3", 0, "",
    offsetof(BlockIO_TemplateLgV2, Add3_k), BLOCKIO_SIG, 28, 3, 2, 868, 0 },

  { 435, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Product6", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product6), BLOCKIO_SIG, 20, 3, 2, 870, 0 },

  { 436, "templatelgv2/Main Subsystems/Control/LgV2/Control law/Sum", 0, "",
    offsetof(BlockIO_TemplateLgV2, Sum_eq), BLOCKIO_SIG, 28, 3, 2, 872, 0 },

  { 437, "templatelgv2/Main Subsystems/Control/Control Switch/tau Switch", 0, "",
    offsetof(BlockIO_TemplateLgV2, tauSwitch), BLOCKIO_SIG, 28, 3, 2, 874, 0 },

  { 438, "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Add", 0, "",
    offsetof(BlockIO_TemplateLgV2, Add_h), BLOCKIO_SIG, 32, 2, 2, 876, 0 },

  { 439,
    "templatelgv2/Main Subsystems/Control/LgV2/V_1^q/Transpose/Math Function", 0,
    "", offsetof(BlockIO_TemplateLgV2, MathFunction_kp), BLOCKIO_SIG, 33, 3, 2,
    878, 0 },

  { 440, "templatelgv2/Main Subsystems/Control/LgV2/V_1^q/Product", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product_feo), BLOCKIO_SIG, 29, 2, 2, 880, 0 },

  { 441, "templatelgv2/Main Subsystems/Control/LgV2/V_1^q/Gain", 0, "", offsetof
    (BlockIO_TemplateLgV2, Gain_l), BLOCKIO_SIG, 29, 2, 2, 882, 0 },

  { 442,
    "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Transpose/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_jk0), BLOCKIO_SIG, 32, 2,
    2, 884, 0 },

  { 443, "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Product", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product_fj), BLOCKIO_SIG, 32, 2, 2, 886, 0 },

  { 444, "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Add1", 0, "",
    offsetof(BlockIO_TemplateLgV2, Add1_o), BLOCKIO_SIG, 32, 2, 2, 888, 0 },

  { 445, "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Product1", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product1_lb), BLOCKIO_SIG, 32, 2, 2, 890, 0 },

  { 446, "templatelgv2/Main Subsystems/Control/LgV2/Update laws/Gain", 0, "",
    offsetof(BlockIO_TemplateLgV2, Gain_jz), BLOCKIO_SIG, 32, 2, 2, 892, 0 },

  { 447, "templatelgv2/Main Subsystems/Control/LgV2/zeta/Product", 0, "",
    offsetof(BlockIO_TemplateLgV2, Product_jo), BLOCKIO_SIG, 28, 3, 2, 894, 0 },

  { 448,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/tau to f_act/Pseudoinverse",
    0, "", offsetof(BlockIO_TemplateLgV2, Pseudoinverse), BLOCKIO_SIG, 41, 15, 2,
    896, 0 },

  { 449,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/tau to f_act/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_gz), BLOCKIO_SIG, 37, 5, 2,
    898, 0 },

  { 450,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_1 to u_1 VSP speed 0.3/f_1 to u_1",
    0, "", offsetof(BlockIO_TemplateLgV2, f_1tou_1), BLOCKIO_SIG, 31, 1, 2, 900,
    0 },

  { 451,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_es), BLOCKIO_SIG, 31, 1, 2, 902, 0
  },

  { 452,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.00391",
    0, "", offsetof(BlockIO_TemplateLgV2, f_2000391), BLOCKIO_SIG, 31, 1, 2, 904,
    0 },

  { 453,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 < 0.06731 && f_2 >= 0.00391",
    0, "", offsetof(BlockIO_TemplateLgV2, f_2006731f_2000391), BLOCKIO_SIG, 31,
    1, 2, 906, 0 },

  { 454,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/f_2 => 0.06731",
    0, "", offsetof(BlockIO_TemplateLgV2, f_2006731), BLOCKIO_SIG, 31, 1, 2, 908,
    0 },

  { 455,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSwitch), BLOCKIO_SIG, 31, 1,
    2, 910, 0 },

  { 456,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_l), BLOCKIO_SIG, 31, 1, 2, 912, 0
  },

  { 457,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_3 to u_3 VSP speed 0.3/f_3 to u_3",
    0, "", offsetof(BlockIO_TemplateLgV2, f_3tou_3), BLOCKIO_SIG, 31, 1, 2, 914,
    0 },

  { 458,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum2",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum2_e), BLOCKIO_SIG, 31, 1, 2, 916, 0
  },

  { 459,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 < 0.0451",
    0, "", offsetof(BlockIO_TemplateLgV2, f_400451), BLOCKIO_SIG, 31, 1, 2, 918,
    0 },

  { 460,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/f_4 >= 0.0451",
    0, "", offsetof(BlockIO_TemplateLgV2, f_400451_l), BLOCKIO_SIG, 31, 1, 2,
    920, 0 },

  { 461,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSwitch_p), BLOCKIO_SIG, 31, 1,
    2, 922, 0 },

  { 462,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/Sum3",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum3_a), BLOCKIO_SIG, 31, 1, 2, 924, 0
  },

  { 463,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_TemplateLgV2, DeadZone001), BLOCKIO_SIG, 31, 1, 2,
    926, 0 },

  { 464,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 < 0",
    0, "", offsetof(BlockIO_TemplateLgV2, f_50), BLOCKIO_SIG, 31, 1, 2, 928, 0 },

  { 465,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/f_5 > 0",
    0, "", offsetof(BlockIO_TemplateLgV2, f_50_g), BLOCKIO_SIG, 31, 1, 2, 930, 0
  },

  { 466,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSwitch_k), BLOCKIO_SIG, 31, 1,
    2, 932, 0 },

  { 467, "templatelgv2/Main Subsystems/Control/Thruster allocation/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_bg), BLOCKIO_SIG, 35, 7, 2,
    934, 0 },

  { 468, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In2 Error",
    0, "", offsetof(BlockIO_TemplateLgV2, QTMIn2Error), BLOCKIO_SIG, 31, 1, 2,
    936, 0 },

  { 469,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In9 Residual",
    0, "", offsetof(BlockIO_TemplateLgV2, QTMIn9Residual), BLOCKIO_SIG, 31, 1, 2,
    938, 0 },

  { 470,
    "templatelgv2/Main Subsystems/Plant/Thruster setting workaround/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_lh), BLOCKIO_SIG, 0, 1, 2,
    940, 0 },

  { 471,
    "templatelgv2/Main Subsystems/Plant/Thruster setting workaround/tau Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, tauSwitch_j), BLOCKIO_SIG, 35, 7, 2,
    942, 0 },

  { 472,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In5 z-coord [mm]",
    0, "", offsetof(BlockIO_TemplateLgV2, QTMIn5zcoordmm), BLOCKIO_SIG, 31, 1, 2,
    944, 0 },

  { 473, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/mm2m z", 0, "",
    offsetof(BlockIO_TemplateLgV2, mm2mz), BLOCKIO_SIG, 31, 1, 2, 946, 0 },

  { 474,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In8 roll [deg]",
    0, "", offsetof(BlockIO_TemplateLgV2, QTMIn8rolldeg), BLOCKIO_SIG, 31, 1, 2,
    948, 0 },

  { 475, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/d2r roll", 0,
    "", offsetof(BlockIO_TemplateLgV2, d2rroll), BLOCKIO_SIG, 31, 1, 2, 950, 0 },

  { 476,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In7 pitch [deg]",
    0, "", offsetof(BlockIO_TemplateLgV2, QTMIn7pitchdeg), BLOCKIO_SIG, 31, 1, 2,
    952, 0 },

  { 477, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/d2r pitch", 0,
    "", offsetof(BlockIO_TemplateLgV2, d2rpitch), BLOCKIO_SIG, 31, 1, 2, 954, 0
  },

  { 478, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Derivative", 0,
    "", offsetof(BlockIO_TemplateLgV2, Derivative_h), BLOCKIO_SIG, 34, 6, 2, 956,
    0 },

  { 479,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/sin(theta)",
    0, "", offsetof(BlockIO_TemplateLgV2, sintheta), BLOCKIO_SIG, 20, 3, 2, 958,
    0 },

  { 480,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/cos(theta)",
    0, "", offsetof(BlockIO_TemplateLgV2, costheta), BLOCKIO_SIG, 20, 3, 2, 960,
    0 },

  { 481,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R11",
    0, "", offsetof(BlockIO_TemplateLgV2, R11_o), BLOCKIO_SIG, 0, 1, 2, 962, 0 },

  { 482,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R12",
    0, "", offsetof(BlockIO_TemplateLgV2, R12_p), BLOCKIO_SIG, 0, 1, 2, 964, 0 },

  { 483,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R13",
    0, "", offsetof(BlockIO_TemplateLgV2, R13), BLOCKIO_SIG, 0, 1, 2, 966, 0 },

  { 484,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R21",
    0, "", offsetof(BlockIO_TemplateLgV2, R21_h), BLOCKIO_SIG, 0, 1, 2, 968, 0 },

  { 485,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R22",
    0, "", offsetof(BlockIO_TemplateLgV2, R22_o), BLOCKIO_SIG, 0, 1, 2, 970, 0 },

  { 486,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R23",
    0, "", offsetof(BlockIO_TemplateLgV2, R23), BLOCKIO_SIG, 0, 1, 2, 972, 0 },

  { 487,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R31",
    0, "", offsetof(BlockIO_TemplateLgV2, R31), BLOCKIO_SIG, 0, 1, 2, 974, 0 },

  { 488,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R32",
    0, "", offsetof(BlockIO_TemplateLgV2, R32), BLOCKIO_SIG, 0, 1, 2, 976, 0 },

  { 489,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/R33",
    0, "", offsetof(BlockIO_TemplateLgV2, R33), BLOCKIO_SIG, 0, 1, 2, 978, 0 },

  { 490,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Euler angles to inverse rotation matrix/Reshape 9x1->3x3",
    0, "", offsetof(BlockIO_TemplateLgV2, Reshape9x13x3), BLOCKIO_SIG, 22, 9, 2,
    980, 0 },

  { 491, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Inverse", 0,
    "", offsetof(BlockIO_TemplateLgV2, Inverse), BLOCKIO_SIG, 22, 9, 2, 982, 0 },

  { 492,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Matrix Concatenate2",
    0, "", offsetof(BlockIO_TemplateLgV2, MatrixConcatenate2), BLOCKIO_SIG, 53,
    36, 2, 984, 0 },

  { 493, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/Product", 0,
    "", offsetof(BlockIO_TemplateLgV2, Product_i3), BLOCKIO_SIG, 34, 6, 2, 986,
    0 },

  { 494, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/QTM In1 FN", 0,
    "", offsetof(BlockIO_TemplateLgV2, QTMIn1FN), BLOCKIO_SIG, 31, 1, 2, 988, 0
  },

  { 495,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator",
    0, "eta", offsetof(BlockIO_TemplateLgV2, eta), BLOCKIO_SIG, 20, 3, 2, 990, 0
  },

  { 496,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Integrator3",
    0, "bias", offsetof(BlockIO_TemplateLgV2, bias), BLOCKIO_SIG, 20, 3, 2, 992,
    0 },

  { 497,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_d), BLOCKIO_SIG, 0, 1, 2,
    994, 0 },

  { 498,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_i), BLOCKIO_SIG, 0, 1, 2, 996, 0
  },

  { 499,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_bj), BLOCKIO_SIG, 0, 1, 2, 998, 0
  },

  { 500,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_nt), BLOCKIO_SIG, 0, 1, 2, 1000,
    0 },

  { 501,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_gq), BLOCKIO_SIG, 0, 1, 2,
    1002, 0 },

  { 502,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_i), BLOCKIO_SIG, 0, 1, 2, 1004, 0
  },

  { 503,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum2",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum2_h), BLOCKIO_SIG, 20, 3, 2, 1006,
    0 },

  { 504,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Saturation",
    0, "", offsetof(BlockIO_TemplateLgV2, Saturation_a), BLOCKIO_SIG, 0, 1, 2,
    1008, 0 },

  { 505,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_pa), BLOCKIO_SIG, 0, 1, 2, 1010,
    0 },

  { 506,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_cg), BLOCKIO_SIG, 0, 1, 2, 1012,
    0 },

  { 507,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_a), BLOCKIO_SIG, 0, 1, 2, 1014, 0
  },

  { 508,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Math Function",
    0, "", offsetof(BlockIO_TemplateLgV2, MathFunction_le), BLOCKIO_SIG, 0, 1, 2,
    1016, 0 },

  { 509,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/[-inf inf] to [-pi pi]1/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_dt), BLOCKIO_SIG, 0, 1, 2, 1018, 0
  },

  { 510,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K2",
    0, "", offsetof(BlockIO_TemplateLgV2, K2), BLOCKIO_SIG, 20, 3, 2, 1020, 0 },

  { 511,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K3",
    0, "", offsetof(BlockIO_TemplateLgV2, K3), BLOCKIO_SIG, 20, 3, 2, 1022, 0 },

  { 512,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/K4",
    0, "", offsetof(BlockIO_TemplateLgV2, K4), BLOCKIO_SIG, 20, 3, 2, 1024, 0 },

  { 513,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw/Row1",
    0, "", offsetof(BlockIO_TemplateLgV2, Row1_b), BLOCKIO_SIG, 0, 1, 2, 1026, 0
  },

  { 514,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw/Row2",
    0, "", offsetof(BlockIO_TemplateLgV2, Row2_k), BLOCKIO_SIG, 0, 1, 2, 1028, 0
  },

  { 515,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw/Row3",
    0, "", offsetof(BlockIO_TemplateLgV2, Row3_m), BLOCKIO_SIG, 0, 1, 2, 1030, 0
  },

  { 516,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1/Row1",
    0, "", offsetof(BlockIO_TemplateLgV2, Row1_a), BLOCKIO_SIG, 0, 1, 2, 1032, 0
  },

  { 517,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1/Row2",
    0, "", offsetof(BlockIO_TemplateLgV2, Row2_c), BLOCKIO_SIG, 0, 1, 2, 1034, 0
  },

  { 518,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Transposed rotation  matrix in yaw1/Row3",
    0, "", offsetof(BlockIO_TemplateLgV2, Row3_j), BLOCKIO_SIG, 0, 1, 2, 1036, 0
  },

  { 519,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_1 to f_1 VSP speed 0.3/u_1 to f_1",
    0, "", offsetof(BlockIO_TemplateLgV2, u_1tof_1_l), BLOCKIO_SIG, 0, 1, 2,
    1038, 0 },

  { 520,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.5",
    0, "", offsetof(BlockIO_TemplateLgV2, u_205), BLOCKIO_SIG, 0, 1, 2, 1040, 0
  },

  { 521,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 < -0.1 && u_2 >= -0.2",
    0, "", offsetof(BlockIO_TemplateLgV2, u_201u_202), BLOCKIO_SIG, 0, 1, 2,
    1042, 0 },

  { 522,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/u_2 => 0",
    0, "", offsetof(BlockIO_TemplateLgV2, u_20), BLOCKIO_SIG, 0, 1, 2, 1044, 0 },

  { 523,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSwitch_c), BLOCKIO_SIG, 0, 1,
    2, 1046, 0 },

  { 524,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_3 to f_3 VSP speed 0.3/u_3 to f_3",
    0, "", offsetof(BlockIO_TemplateLgV2, u_3tof_3_c), BLOCKIO_SIG, 0, 1, 2,
    1048, 0 },

  { 525,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 < -0.1",
    0, "", offsetof(BlockIO_TemplateLgV2, u_401), BLOCKIO_SIG, 0, 1, 2, 1050, 0
  },

  { 526,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/u_4 >= -0.1",
    0, "", offsetof(BlockIO_TemplateLgV2, u_401_o), BLOCKIO_SIG, 0, 1, 2, 1052,
    0 },

  { 527,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSwitch_g), BLOCKIO_SIG, 0, 1,
    2, 1054, 0 },

  { 528,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Dead Zone +-0.01",
    0, "", offsetof(BlockIO_TemplateLgV2, DeadZone001_b), BLOCKIO_SIG, 0, 1, 2,
    1056, 0 },

  { 529,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 < 0",
    0, "", offsetof(BlockIO_TemplateLgV2, u_50), BLOCKIO_SIG, 0, 1, 2, 1058, 0 },

  { 530,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/u_5 > 0",
    0, "", offsetof(BlockIO_TemplateLgV2, u_50_f), BLOCKIO_SIG, 0, 1, 2, 1060, 0
  },

  { 531,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Multiport Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, MultiportSwitch_m), BLOCKIO_SIG, 0, 1,
    2, 1062, 0 },

  { 532,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_h0), BLOCKIO_SIG, 20, 3, 2,
    1064, 0 },

  { 533,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_ab), BLOCKIO_SIG, 20, 3, 2, 1066,
    0 },

  { 534,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_gb), BLOCKIO_SIG, 20, 3, 2,
    1068, 0 },

  { 535,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum8",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum8), BLOCKIO_SIG, 20, 3, 2, 1070, 0
  },

  { 536,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Product",
    0, "", offsetof(BlockIO_TemplateLgV2, Product_o2), BLOCKIO_SIG, 20, 3, 2,
    1072, 0 },

  { 537,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1/Fcn",
    0, "x_dot", offsetof(BlockIO_TemplateLgV2, x_dot), BLOCKIO_SIG, 0, 1, 2,
    1074, 0 },

  { 538,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1/Fcn1",
    0, "y_dot", offsetof(BlockIO_TemplateLgV2, y_dot), BLOCKIO_SIG, 0, 1, 2,
    1076, 0 },

  { 539,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Rotation matrix in yaw 1/Fcn2",
    0, "psi_dot", offsetof(BlockIO_TemplateLgV2, psi_dot), BLOCKIO_SIG, 0, 1, 2,
    1078, 0 },

  { 540,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum3",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum3_c), BLOCKIO_SIG, 20, 3, 2, 1080,
    0 },

  { 541,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/inv(T_b)",
    0, "", offsetof(BlockIO_TemplateLgV2, invT_b), BLOCKIO_SIG, 20, 3, 2, 1082,
    0 },

  { 542,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/passive low speed observer/Sum7",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum7), BLOCKIO_SIG, 20, 3, 2, 1084, 0
  },

  { 543, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/SIT zAI0", 0,
    "", offsetof(BlockIO_TemplateLgV2, SITzAI0), BLOCKIO_SIG, 0, 1, 2, 1086, 0 },

  { 544, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/SIT zAI1", 0,
    "", offsetof(BlockIO_TemplateLgV2, SITzAI1), BLOCKIO_SIG, 0, 1, 2, 1088, 0 },

  { 545, "templatelgv2/Main Subsystems/Naviagation/Input from SIT/SIT zAI2", 0,
    "", offsetof(BlockIO_TemplateLgV2, SITzAI2), BLOCKIO_SIG, 0, 1, 2, 1090, 0 },

  { 546, "templatelgv2/Main Subsystems/Plant/Inverse", 0, "", offsetof
    (BlockIO_TemplateLgV2, Inverse_e), BLOCKIO_SIG, 22, 9, 2, 1092, 0 },

  { 547, "templatelgv2/Main Subsystems/Plant/saturation/Saturation", 0, "",
    offsetof(BlockIO_TemplateLgV2, Saturation_o), BLOCKIO_SIG, 31, 1, 2, 1094, 0
  },

  { 548, "templatelgv2/Main Subsystems/Plant/saturation/Saturation1", 0, "",
    offsetof(BlockIO_TemplateLgV2, Saturation1), BLOCKIO_SIG, 31, 1, 2, 1096, 0
  },

  { 549, "templatelgv2/Main Subsystems/Plant/saturation/Saturation2", 0, "",
    offsetof(BlockIO_TemplateLgV2, Saturation2), BLOCKIO_SIG, 31, 1, 2, 1098, 0
  },

  { 550, "templatelgv2/Main Subsystems/Plant/saturation/plant tau_surge", 0, "",
    offsetof(BlockIO_TemplateLgV2, planttau_surge), BLOCKIO_SIG, 31, 1, 2, 1100,
    0 },

  { 551, "templatelgv2/Main Subsystems/Plant/saturation/plant tau_sway", 0, "",
    offsetof(BlockIO_TemplateLgV2, planttau_sway), BLOCKIO_SIG, 31, 1, 2, 1102,
    0 },

  { 552, "templatelgv2/Main Subsystems/Plant/saturation/plant tau_yaw", 0, "",
    offsetof(BlockIO_TemplateLgV2, planttau_yaw), BLOCKIO_SIG, 31, 1, 2, 1104, 0
  },

  { 553, "templatelgv2/Outputs to LabVIEW/Battery Voltage/Battery Bow Thruster",
    0, "", offsetof(BlockIO_TemplateLgV2, BatteryBowThruster), BLOCKIO_SIG, 0, 1,
    2, 1106, 0 },

  { 554, "templatelgv2/Outputs to LabVIEW/Battery Voltage/Battery Main", 0, "",
    offsetof(BlockIO_TemplateLgV2, BatteryMain), BLOCKIO_SIG, 0, 1, 2, 1108, 0 },

  { 555, "templatelgv2/Outputs to LabVIEW/Battery Voltage/Battery Servo", 0, "",
    offsetof(BlockIO_TemplateLgV2, BatteryServo), BLOCKIO_SIG, 0, 1, 2, 1110, 0
  },

  { 556, "templatelgv2/Outputs to LabVIEW/Command/tau1", 0, "", offsetof
    (BlockIO_TemplateLgV2, tau1), BLOCKIO_SIG, 28, 3, 2, 1112, 0 },

  { 557, "templatelgv2/Outputs to LabVIEW/Command/tau2", 0, "", offsetof
    (BlockIO_TemplateLgV2, tau2), BLOCKIO_SIG, 28, 3, 2, 1114, 0 },

  { 558, "templatelgv2/Outputs to LabVIEW/Command/tau3", 0, "", offsetof
    (BlockIO_TemplateLgV2, tau3), BLOCKIO_SIG, 20, 3, 2, 1116, 0 },

  { 559, "templatelgv2/Outputs to LabVIEW/Command/tau4", 0, "", offsetof
    (BlockIO_TemplateLgV2, tau4), BLOCKIO_SIG, 28, 3, 2, 1118, 0 },

  { 560, "templatelgv2/Outputs to LabVIEW/Command/tau5", 0, "", offsetof
    (BlockIO_TemplateLgV2, tau5), BLOCKIO_SIG, 28, 3, 2, 1120, 0 },

  { 561, "templatelgv2/Outputs to LabVIEW/Command/tau6", 0, "", offsetof
    (BlockIO_TemplateLgV2, tau6), BLOCKIO_SIG, 20, 3, 2, 1122, 0 },

  { 562, "templatelgv2/Outputs to LabVIEW/Command/plant BT power", 0, "",
    offsetof(BlockIO_TemplateLgV2, plantBTpower), BLOCKIO_SIG, 0, 1, 2, 1124, 0
  },

  { 563, "templatelgv2/Outputs to LabVIEW/Command/plant VSP speed", 0, "",
    offsetof(BlockIO_TemplateLgV2, plantVSPspeed), BLOCKIO_SIG, 0, 1, 2, 1126, 0
  },

  { 564, "templatelgv2/Outputs to LabVIEW/Command/plant u_1", 0, "", offsetof
    (BlockIO_TemplateLgV2, plantu_1), BLOCKIO_SIG, 0, 1, 2, 1128, 0 },

  { 565, "templatelgv2/Outputs to LabVIEW/Command/plant u_2", 0, "", offsetof
    (BlockIO_TemplateLgV2, plantu_2), BLOCKIO_SIG, 0, 1, 2, 1130, 0 },

  { 566, "templatelgv2/Outputs to LabVIEW/Command/plant u_3", 0, "", offsetof
    (BlockIO_TemplateLgV2, plantu_3), BLOCKIO_SIG, 0, 1, 2, 1132, 0 },

  { 567, "templatelgv2/Outputs to LabVIEW/Command/plant u_4", 0, "", offsetof
    (BlockIO_TemplateLgV2, plantu_4), BLOCKIO_SIG, 0, 1, 2, 1134, 0 },

  { 568, "templatelgv2/Outputs to LabVIEW/Command/plant u_5", 0, "", offsetof
    (BlockIO_TemplateLgV2, plantu_5), BLOCKIO_SIG, 0, 1, 2, 1136, 0 },

  { 569, "templatelgv2/Outputs to LabVIEW/Command/fact1", 0, "", offsetof
    (BlockIO_TemplateLgV2, fact1), BLOCKIO_SIG, 31, 1, 2, 1138, 0 },

  { 570, "templatelgv2/Outputs to LabVIEW/Command/fact2", 0, "", offsetof
    (BlockIO_TemplateLgV2, fact2), BLOCKIO_SIG, 31, 1, 2, 1140, 0 },

  { 571, "templatelgv2/Outputs to LabVIEW/Command/fact3", 0, "", offsetof
    (BlockIO_TemplateLgV2, fact3), BLOCKIO_SIG, 31, 1, 2, 1142, 0 },

  { 572, "templatelgv2/Outputs to LabVIEW/Command/fact4", 0, "", offsetof
    (BlockIO_TemplateLgV2, fact4), BLOCKIO_SIG, 31, 1, 2, 1144, 0 },

  { 573, "templatelgv2/Outputs to LabVIEW/Command/fact5", 0, "", offsetof
    (BlockIO_TemplateLgV2, fact5), BLOCKIO_SIG, 31, 1, 2, 1146, 0 },

  { 574, "templatelgv2/Outputs to LabVIEW/Command/taux", 0, "", offsetof
    (BlockIO_TemplateLgV2, taux), BLOCKIO_SIG, 31, 1, 2, 1148, 0 },

  { 575, "templatelgv2/Outputs to LabVIEW/Command/tauy", 0, "", offsetof
    (BlockIO_TemplateLgV2, tauy), BLOCKIO_SIG, 31, 1, 2, 1150, 0 },

  { 576, "templatelgv2/Outputs to LabVIEW/Command/tauyaw", 0, "", offsetof
    (BlockIO_TemplateLgV2, tauyaw), BLOCKIO_SIG, 31, 1, 2, 1152, 0 },

  { 577, "templatelgv2/Outputs to LabVIEW/Command/omega_qy", 0, "", offsetof
    (BlockIO_TemplateLgV2, omega_qy), BLOCKIO_SIG, 31, 1, 2, 1154, 0 },

  { 578, "templatelgv2/Outputs to LabVIEW/Command/omegaqx", 0, "", offsetof
    (BlockIO_TemplateLgV2, omegaqx), BLOCKIO_SIG, 31, 1, 2, 1156, 0 },

  { 579, "templatelgv2/Outputs to LabVIEW/Naviagtion/CSE1_r [deg//s]", 0, "",
    offsetof(BlockIO_TemplateLgV2, CSE1_rdegs), BLOCKIO_SIG, 0, 1, 2, 1158, 0 },

  { 580, "templatelgv2/Outputs to LabVIEW/Naviagtion/CSE1_u [m//s]", 0, "",
    offsetof(BlockIO_TemplateLgV2, CSE1_ums), BLOCKIO_SIG, 0, 1, 2, 1160, 0 },

  { 581, "templatelgv2/Outputs to LabVIEW/Naviagtion/CSE1_v [m//s]", 0, "",
    offsetof(BlockIO_TemplateLgV2, CSE1_vms), BLOCKIO_SIG, 0, 1, 2, 1162, 0 },

  { 582, "templatelgv2/Outputs to LabVIEW/Naviagtion/QS Error", 0, "", offsetof
    (BlockIO_TemplateLgV2, QSError), BLOCKIO_SIG, 31, 1, 2, 1164, 0 },

  { 583, "templatelgv2/Outputs to LabVIEW/Naviagtion/QS Frame", 0, "", offsetof
    (BlockIO_TemplateLgV2, QSFrame), BLOCKIO_SIG, 31, 1, 2, 1166, 0 },

  { 584, "templatelgv2/Outputs to LabVIEW/Visualization/Sum", 0, "", offsetof
    (BlockIO_TemplateLgV2, Sum_j), BLOCKIO_SIG, 20, 3, 2, 1168, 0 },

  { 585, "templatelgv2/Outputs to LabVIEW/Visualization/Sum1", 0, "", offsetof
    (BlockIO_TemplateLgV2, Sum1_m2), BLOCKIO_SIG, 20, 3, 2, 1170, 0 },

  { 586, "templatelgv2/Outputs to LabVIEW/Visualization/Sum2", 0, "", offsetof
    (BlockIO_TemplateLgV2, Sum2_c), BLOCKIO_SIG, 20, 3, 2, 1172, 0 },

  { 587, "templatelgv2/Outputs to LabVIEW/Visualization/psi [deg]", 0, "",
    offsetof(BlockIO_TemplateLgV2, psideg), BLOCKIO_SIG, 0, 1, 2, 1174, 0 },

  { 588, "templatelgv2/Outputs to LabVIEW/Visualization/psi-psid [deg]", 0, "",
    offsetof(BlockIO_TemplateLgV2, psipsiddeg), BLOCKIO_SIG, 0, 1, 2, 1176, 0 },

  { 589, "templatelgv2/Outputs to LabVIEW/Visualization/psiLOS-psi [deg]", 0, "",
    offsetof(BlockIO_TemplateLgV2, psiLOSpsideg), BLOCKIO_SIG, 0, 1, 2, 1178, 0
  },

  { 590, "templatelgv2/Outputs to LabVIEW/Visualization/psiLOS-psid [deg]", 0,
    "", offsetof(BlockIO_TemplateLgV2, psiLOSpsiddeg), BLOCKIO_SIG, 0, 1, 2,
    1180, 0 },

  { 591, "templatelgv2/Outputs to LabVIEW/Visualization/psi_LOS [deg]", 0, "",
    offsetof(BlockIO_TemplateLgV2, psi_LOSdeg), BLOCKIO_SIG, 0, 1, 2, 1182, 0 },

  { 592, "templatelgv2/Outputs to LabVIEW/Visualization/psid [deg]", 0, "",
    offsetof(BlockIO_TemplateLgV2, psiddeg), BLOCKIO_SIG, 0, 1, 2, 1184, 0 },

  { 593, "templatelgv2/Outputs to LabVIEW/Visualization/psi_plot", 0, "",
    offsetof(BlockIO_TemplateLgV2, psi_plot), BLOCKIO_SIG, 20, 3, 2, 1186, 0 },

  { 594, "templatelgv2/Outputs to LabVIEW/Visualization/qx [m]", 0, "", offsetof
    (BlockIO_TemplateLgV2, qxm), BLOCKIO_SIG, 0, 1, 2, 1188, 0 },

  { 595, "templatelgv2/Outputs to LabVIEW/Visualization/qx-x [m]", 0, "",
    offsetof(BlockIO_TemplateLgV2, qxxm), BLOCKIO_SIG, 0, 1, 2, 1190, 0 },

  { 596, "templatelgv2/Outputs to LabVIEW/Visualization/qx-xd [m]1", 0, "",
    offsetof(BlockIO_TemplateLgV2, qxxdm1), BLOCKIO_SIG, 0, 1, 2, 1192, 0 },

  { 597, "templatelgv2/Outputs to LabVIEW/Visualization/qy [m]", 0, "", offsetof
    (BlockIO_TemplateLgV2, qym), BLOCKIO_SIG, 0, 1, 2, 1194, 0 },

  { 598, "templatelgv2/Outputs to LabVIEW/Visualization/qy-y [m]", 0, "",
    offsetof(BlockIO_TemplateLgV2, qyym), BLOCKIO_SIG, 0, 1, 2, 1196, 0 },

  { 599, "templatelgv2/Outputs to LabVIEW/Visualization/qy-yd [m]1", 0, "",
    offsetof(BlockIO_TemplateLgV2, qyydm1), BLOCKIO_SIG, 0, 1, 2, 1198, 0 },

  { 600, "templatelgv2/Outputs to LabVIEW/Visualization/x [m]", 0, "", offsetof
    (BlockIO_TemplateLgV2, xm), BLOCKIO_SIG, 0, 1, 2, 1200, 0 },

  { 601, "templatelgv2/Outputs to LabVIEW/Visualization/x-xd [m]", 0, "",
    offsetof(BlockIO_TemplateLgV2, xxdm), BLOCKIO_SIG, 0, 1, 2, 1202, 0 },

  { 602, "templatelgv2/Outputs to LabVIEW/Visualization/xd [m]", 0, "", offsetof
    (BlockIO_TemplateLgV2, xdm), BLOCKIO_SIG, 0, 1, 2, 1204, 0 },

  { 603, "templatelgv2/Outputs to LabVIEW/Visualization/x_plot", 0, "", offsetof
    (BlockIO_TemplateLgV2, x_plot), BLOCKIO_SIG, 20, 3, 2, 1206, 0 },

  { 604, "templatelgv2/Outputs to LabVIEW/Visualization/y [m]", 0, "", offsetof
    (BlockIO_TemplateLgV2, ym), BLOCKIO_SIG, 0, 1, 2, 1208, 0 },

  { 605, "templatelgv2/Outputs to LabVIEW/Visualization/y-yd [m]", 0, "",
    offsetof(BlockIO_TemplateLgV2, yydm), BLOCKIO_SIG, 0, 1, 2, 1210, 0 },

  { 606, "templatelgv2/Outputs to LabVIEW/Visualization/yd [m]", 0, "", offsetof
    (BlockIO_TemplateLgV2, ydm), BLOCKIO_SIG, 0, 1, 2, 1212, 0 },

  { 607, "templatelgv2/Outputs to LabVIEW/Visualization/y_plot", 0, "", offsetof
    (BlockIO_TemplateLgV2, y_plot), BLOCKIO_SIG, 20, 3, 2, 1214, 0 },

  { 608, "templatelgv2/Outputs to LabVIEW/Visualization/splot", 0, "", offsetof
    (BlockIO_TemplateLgV2, splot), BLOCKIO_SIG, 0, 1, 2, 1216, 0 },

  { 609,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator",
    0, "", offsetof(BlockIO_TemplateLgV2, Integrator_h), BLOCKIO_SIG, 20, 3, 2,
    1218, 0 },

  { 610,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Integrator1",
    0, "", offsetof(BlockIO_TemplateLgV2, Integrator1_p), BLOCKIO_SIG, 20, 3, 2,
    1220, 0 },

  { 611,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R11",
    0, "", offsetof(BlockIO_TemplateLgV2, R11_h), BLOCKIO_SIG, 0, 1, 2, 1222, 0
  },

  { 612,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R21",
    0, "", offsetof(BlockIO_TemplateLgV2, R21_f), BLOCKIO_SIG, 0, 1, 2, 1224, 0
  },

  { 613,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R12",
    0, "", offsetof(BlockIO_TemplateLgV2, R12_c), BLOCKIO_SIG, 0, 1, 2, 1226, 0
  },

  { 614,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R22",
    0, "", offsetof(BlockIO_TemplateLgV2, R22_p), BLOCKIO_SIG, 0, 1, 2, 1228, 0
  },

  { 615,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/R(psi)/R(psi)",
    0, "", offsetof(BlockIO_TemplateLgV2, Rpsi_k), BLOCKIO_SIG, 22, 9, 2, 1230,
    0 },

  { 616,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product1",
    0, "", offsetof(BlockIO_TemplateLgV2, Product1_fr), BLOCKIO_SIG, 20, 3, 2,
    1232, 0 },

  { 617,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_c), BLOCKIO_SIG, 20, 3, 2, 1234, 0
  },

  { 618,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product2",
    0, "", offsetof(BlockIO_TemplateLgV2, Product2_o), BLOCKIO_SIG, 20, 3, 2,
    1236, 0 },

  { 619,
    "templatelgv2/Main Subsystems/Plant/Linear Simulator/Linear Vessel Dynamics/Product3",
    0, "", offsetof(BlockIO_TemplateLgV2, Product3_al), BLOCKIO_SIG, 20, 3, 2,
    1238, 0 },

  { 620,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain1",
    0, "", offsetof(BlockIO_TemplateLgV2, BT_D_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1240, 0 },

  { 621,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_D_Gain2",
    0, "", offsetof(BlockIO_TemplateLgV2, BT_D_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1242, 0 },

  { 622, "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Add", 0,
    "", offsetof(BlockIO_TemplateLgV2, Add_a1), BLOCKIO_SIG, 0, 1, 2, 1244, 0 },

  { 623,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain1",
    0, "", offsetof(BlockIO_TemplateLgV2, BT_L_Gain1), BLOCKIO_SIG, 0, 1, 2,
    1246, 0 },

  { 624,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/BT_L_Gain2",
    0, "", offsetof(BlockIO_TemplateLgV2, BT_L_Gain2), BLOCKIO_SIG, 0, 1, 2,
    1248, 0 },

  { 625, "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Neg", 0,
    "", offsetof(BlockIO_TemplateLgV2, Neg), BLOCKIO_SIG, 0, 1, 2, 1250, 0 },

  { 626, "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum1", 0,
    "", offsetof(BlockIO_TemplateLgV2, Sum1_g4), BLOCKIO_SIG, 0, 1, 2, 1252, 0 },

  { 627, "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Sum2", 0,
    "", offsetof(BlockIO_TemplateLgV2, Sum2_n), BLOCKIO_SIG, 0, 1, 2, 1254, 0 },

  { 628,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch_l), BLOCKIO_SIG, 0, 1, 2, 1256,
    0 },

  { 629,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/Switch2",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch2_p), BLOCKIO_SIG, 0, 1, 2, 1258,
    0 },

  { 630,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch_h), BLOCKIO_SIG, 0, 1, 2, 1260,
    0 },

  { 631,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/Switch2",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch2_o), BLOCKIO_SIG, 0, 1, 2, 1262,
    0 },

  { 632,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch_a), BLOCKIO_SIG, 0, 1, 2, 1264,
    0 },

  { 633,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/Switch2",
    0, "", offsetof(BlockIO_TemplateLgV2, Switch2_n), BLOCKIO_SIG, 0, 1, 2, 1266,
    0 },

  { 634,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sign",
    0, "", offsetof(BlockIO_TemplateLgV2, Sign_c), BLOCKIO_SIG, 0, 1, 2, 1268, 0
  },

  { 635,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product1",
    0, "Port VPS_X", offsetof(BlockIO_TemplateLgV2, PortVPS_X), BLOCKIO_SIG, 0,
    1, 2, 1270, 0 },

  { 636,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-x",
    0, "Port VPS_X", offsetof(BlockIO_TemplateLgV2, PortVPS_X_o), BLOCKIO_SIG, 0,
    1, 2, 1272, 0 },

  { 637,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product2",
    0, "Port VSP_Y", offsetof(BlockIO_TemplateLgV2, PortVSP_Y), BLOCKIO_SIG, 0,
    1, 2, 1274, 0 },

  { 638,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /-y",
    0, "Port VSP_Y", offsetof(BlockIO_TemplateLgV2, PortVSP_Y_f), BLOCKIO_SIG, 0,
    1, 2, 1276, 0 },

  { 639,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product3",
    0, "Starboard VSP_X", offsetof(BlockIO_TemplateLgV2, StarboardVSP_X),
    BLOCKIO_SIG, 0, 1, 2, 1278, 0 },

  { 640,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Product4",
    0, "Starboard VSP_Y", offsetof(BlockIO_TemplateLgV2, StarboardVSP_Y),
    BLOCKIO_SIG, 0, 1, 2, 1280, 0 },

  { 641,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo1",
    0, "", offsetof(BlockIO_TemplateLgV2, Servo1), BLOCKIO_SIG, 0, 1, 2, 1282, 0
  },

  { 642,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo2",
    0, "", offsetof(BlockIO_TemplateLgV2, Servo2), BLOCKIO_SIG, 0, 1, 2, 1284, 0
  },

  { 643,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo3",
    0, "", offsetof(BlockIO_TemplateLgV2, Servo3), BLOCKIO_SIG, 0, 1, 2, 1286, 0
  },

  { 644,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Servo4",
    0, "", offsetof(BlockIO_TemplateLgV2, Servo4), BLOCKIO_SIG, 0, 1, 2, 1288, 0
  },

  { 645,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VPS_Speed_Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, VPS_Speed_Gain), BLOCKIO_SIG, 0, 1, 2,
    1290, 0 },

  { 646,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_ie), BLOCKIO_SIG, 0, 1, 2, 1292, 0
  },

  { 647,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Port",
    0, "", offsetof(BlockIO_TemplateLgV2, VSPSPort), BLOCKIO_SIG, 0, 1, 2, 1294,
    0 },

  { 648,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Voith Schneider Propeller /VSPS Starboard",
    0, "", offsetof(BlockIO_TemplateLgV2, VSPSStarboard), BLOCKIO_SIG, 0, 1, 2,
    1296, 0 },

  { 649,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S12",
    0, "", offsetof(BlockIO_TemplateLgV2, S12_e), BLOCKIO_SIG, 31, 1, 2, 1298, 0
  },

  { 650,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2(psi_d^s^2)/S_2(psi_d^s^2)",
    0, "", offsetof(BlockIO_TemplateLgV2, S_2psi_ds2), BLOCKIO_SIG, 24, 4, 2,
    1300, 0 },

  { 651,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S12",
    0, "", offsetof(BlockIO_TemplateLgV2, S12_e4), BLOCKIO_SIG, 31, 1, 2, 1302,
    0 },

  { 652,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/S_2/S_2(psi_d^s)",
    0, "", offsetof(BlockIO_TemplateLgV2, S_2psi_ds), BLOCKIO_SIG, 24, 4, 2,
    1304, 0 },

  { 653,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R11",
    0, "", offsetof(BlockIO_TemplateLgV2, R11_f), BLOCKIO_SIG, 0, 1, 2, 1306, 0
  },

  { 654,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R21",
    0, "", offsetof(BlockIO_TemplateLgV2, R21_d), BLOCKIO_SIG, 0, 1, 2, 1308, 0
  },

  { 655,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R12",
    0, "", offsetof(BlockIO_TemplateLgV2, R12_h), BLOCKIO_SIG, 0, 1, 2, 1310, 0
  },

  { 656,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R22",
    0, "", offsetof(BlockIO_TemplateLgV2, R22_l), BLOCKIO_SIG, 0, 1, 2, 1312, 0
  },

  { 657,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Line-Of-Sight/Position error signals/R_2/R_2(psi_d)",
    0, "", offsetof(BlockIO_TemplateLgV2, R_2psi_d), BLOCKIO_SIG, 24, 4, 2, 1314,
    0 },

  { 658,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain1_e), BLOCKIO_SIG, 39, 1, 2, 1316,
    0 },

  { 659,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_iy), BLOCKIO_SIG, 39, 1, 2, 1318,
    0 },

  { 660,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_mj), BLOCKIO_SIG, 39, 1, 2, 1320,
    0 },

  { 661,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_bm), BLOCKIO_SIG, 39, 1, 2, 1322,
    0 },

  { 662,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_n), BLOCKIO_SIG, 39, 1, 2, 1324,
    0 },

  { 663,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain1_l), BLOCKIO_SIG, 39, 1, 2, 1326,
    0 },

  { 664,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_m), BLOCKIO_SIG, 39, 1, 2, 1328, 0
  },

  { 665,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Gain1",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain1_h), BLOCKIO_SIG, 15, 1, 2, 1330,
    0 },

  { 666,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_fk), BLOCKIO_SIG, 15, 1, 2, 1332,
    0 },

  { 667,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_pn), BLOCKIO_SIG, 15, 1, 2, 1334,
    0 },

  { 668,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_fl), BLOCKIO_SIG, 15, 1, 2, 1336,
    0 },

  { 669,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain_pf), BLOCKIO_SIG, 15, 1, 2, 1338,
    0 },

  { 670,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Gain1",
    0, "", offsetof(BlockIO_TemplateLgV2, Gain1_m), BLOCKIO_SIG, 15, 1, 2, 1340,
    0 },

  { 671,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/Sum",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum_dx), BLOCKIO_SIG, 15, 1, 2, 1342,
    0 },

  { 672,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare), BLOCKIO_SIG, 38, 1, 2, 1344,
    0 },

  { 673,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_d), BLOCKIO_SIG, 38, 1, 2,
    1346, 0 },

  { 674,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_p), BLOCKIO_SIG, 38, 1, 2,
    1348, 0 },

  { 675,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_h), BLOCKIO_SIG, 38, 1, 2, 1350,
    0 },

  { 676,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_i), BLOCKIO_SIG, 38, 1, 2,
    1352, 0 },

  { 677,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_h), BLOCKIO_SIG, 38, 1, 2,
    1354, 0 },

  { 678,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_4 to u_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_c), BLOCKIO_SIG, 38, 1, 2,
    1356, 0 },

  { 679,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_k), BLOCKIO_SIG, 38, 1, 2,
    1358, 0 },

  { 680,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_i2), BLOCKIO_SIG, 38, 1, 2,
    1360, 0 },

  { 681,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_5 to u_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_e), BLOCKIO_SIG, 38, 1, 2,
    1362, 0 },

  { 682,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_ip), BLOCKIO_SIG, 3, 1, 2,
    1364, 0 },

  { 683,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.00391/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_en), BLOCKIO_SIG, 3, 1, 2,
    1366, 0 },

  { 684,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If < 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_o), BLOCKIO_SIG, 3, 1, 2, 1368,
    0 },

  { 685,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Sum1",
    0, "", offsetof(BlockIO_TemplateLgV2, Sum1_o), BLOCKIO_SIG, 3, 1, 2, 1370, 0
  },

  { 686,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/If >= 0.06731/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_dk), BLOCKIO_SIG, 3, 1, 2,
    1372, 0 },

  { 687,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If < 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_eu), BLOCKIO_SIG, 3, 1, 2,
    1374, 0 },

  { 688,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_4 to f_4 VSP speed 0.3/If >= 0.0451/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_h3), BLOCKIO_SIG, 3, 1, 2,
    1376, 0 },

  { 689,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If < 0/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_ib), BLOCKIO_SIG, 3, 1, 2,
    1378, 0 },

  { 690,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/if == 0/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_c4), BLOCKIO_SIG, 3, 1, 2,
    1380, 0 },

  { 691,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_5 to f_5 BT power 0.4/If > 0/Compare",
    0, "", offsetof(BlockIO_TemplateLgV2, Compare_l), BLOCKIO_SIG, 3, 1, 2, 1382,
    0 },

  { 692,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateLgV2, LowerRelop1), BLOCKIO_SIG, 8, 1, 2,
    1384, 0 },

  { 693,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation x/UpperRelop",
    0, "", offsetof(BlockIO_TemplateLgV2, UpperRelop), BLOCKIO_SIG, 8, 1, 2,
    1386, 0 },

  { 694,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateLgV2, LowerRelop1_c), BLOCKIO_SIG, 8, 1, 2,
    1388, 0 },

  { 695,
    "templatelgv2/Main Subsystems/Guidance/Line-Of-Sight Path-Following/Path/Path Switch workaround + limiter/Limiter/Saturation y/UpperRelop",
    0, "", offsetof(BlockIO_TemplateLgV2, UpperRelop_g), BLOCKIO_SIG, 8, 1, 2,
    1390, 0 },

  { 696,
    "templatelgv2/Main Subsystems/Control/Thruster allocation/VSP030 BT040/f_act to u_act/f_2 to u_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_TemplateLgV2, LogicalOperator), BLOCKIO_SIG, 40, 1,
    2, 1392, 0 },

  { 697,
    "templatelgv2/Main Subsystems/Naviagation/Input from SIT/u_act to tau/u_act to f_act/u_2 to f_2 VSP speed 0.3/Logical Operator",
    0, "", offsetof(BlockIO_TemplateLgV2, LogicalOperator_n), BLOCKIO_SIG, 8, 1,
    2, 1394, 0 },

  { 698,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateLgV2, LowerRelop1_m), BLOCKIO_SIG, 8, 1, 2,
    1396, 0 },

  { 699,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic/UpperRelop",
    0, "", offsetof(BlockIO_TemplateLgV2, UpperRelop_l), BLOCKIO_SIG, 8, 1, 2,
    1398, 0 },

  { 700,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateLgV2, LowerRelop1_mk), BLOCKIO_SIG, 8, 1, 2,
    1400, 0 },

  { 701,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic1/UpperRelop",
    0, "", offsetof(BlockIO_TemplateLgV2, UpperRelop_n), BLOCKIO_SIG, 8, 1, 2,
    1402, 0 },

  { 702,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/LowerRelop1",
    0, "", offsetof(BlockIO_TemplateLgV2, LowerRelop1_d), BLOCKIO_SIG, 8, 1, 2,
    1404, 0 },

  { 703,
    "templatelgv2/Main Subsystems/Plant/CSE1 actuator/Bow Thruster/Saturation Dynamic2/UpperRelop",
    0, "", offsetof(BlockIO_TemplateLgV2, UpperRelop_o), BLOCKIO_SIG, 8, 1, 2,
    1406, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 3, 3, 3, 3, 3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
  1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3,
  3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 2, 1, 2, 1, 2, 1, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3,
  1, 1, 3, 3, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 3,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 2,
  3, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 1, 1, 2, 1, 2, 2, 2, 2,
  2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2,
  3, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2,
  1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
  1, 2, 1, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2, 1, 2, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
  2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 3, 1, 3, 1, 2, 1, 1, 3, 1, 2, 1, 2,
  2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 1, 5, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7,
  1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 3, 1, 3,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 6, 6, 1, 6,
  1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
  1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1,
  3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 3,
  3, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
  1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 3,
  1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, };

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

static char* NI_CompiledModelName = "templatelgv2";
static char* NI_CompiledModelVersion = "1.114";
static char* NI_CompiledModelDateTime = "Sun Mar 30 09:44:37 2014";

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
   The undef allows us to access the real TemplateLgV2_P
   In the rest of the code TemplateLgV2_P is redefine to be the read-side
   of rtParameter.
 */
#undef TemplateLgV2_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &TemplateLgV2_P, sizeof(Parameters_TemplateLgV2));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka TemplateLgV2_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(Parameters_TemplateLgV2));
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
             (Parameters_TemplateLgV2));

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
           (Parameters_TemplateLgV2));
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

#endif                                 // of NI_ROOTMODEL_TemplateLgV2
